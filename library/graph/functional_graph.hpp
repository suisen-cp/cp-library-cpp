#ifndef SUISEN_DOUBLING
#define SUISEN_DOUBLING

#include <cassert>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace suisen {
    struct FunctionalGraph {
        struct Doubling;
        template <typename T, T(*)(T, T), T(*)()>
        struct DoublingSum;
        friend struct Doubling;
        template <typename T, T(*op)(T, T), T(*e)()>
        friend struct DoublingSum;

        FunctionalGraph() : FunctionalGraph(0) {}
        FunctionalGraph(int n) : _n(n), _nxt(n) {}
        FunctionalGraph(const std::vector<int>& nxt) : _n(nxt.size()), _nxt(nxt) {}

        const int& operator[](int u) const {
            return _nxt[u];
        }
        int& operator[](int u) {
            return _nxt[u];
        }

        struct Doubling {
            friend struct FunctionalGraph;

            int query(int u, long long d) {
                for (int l = _log; l >= 0; --l) if ((d >> l) & 1) u = _nxt[l][u];
                return u;
            }

            struct BinarySearchResult {
                int v;
                long long step;
                operator std::pair<int, long long>() { return std::pair<int, long long>{ v, step }; }
            };

            template <typename Pred>
            auto max_step(int u, Pred &&f) {
                assert(f(u));
                long long step = 0;
                for (int l = _log; l >= 0; --l) if (int nxt_u = _nxt[l][u]; f(nxt_u)) {
                    u = nxt_u, step |= 1LL << l;
                }
                return BinarySearchResult{ u, step };
            }

            template <typename Pred>
            std::optional<BinarySearchResult> step_until(int u, Pred &&f) {
                if (f(u)) return BinarySearchResult { u, 0 };
                auto [v, step] = max_step(u, [&](int v) { return not f(v); });
                v = _nxt[0][v], ++step;
                if (not f(v)) return std::nullopt;
                return BinarySearchResult{ v, step };
            }

        private:
            int _n, _log;
            std::vector<std::vector<int>> _nxt;

            Doubling(const std::vector<int>& nxt, long long max_step) : _n(nxt.size()), _log(floor_log2(max_step)), _nxt(_log + 1, std::vector<int>(_n)) {
                _nxt[0] = nxt;
                for (int i = 1; i <= _log; ++i) for (int j = 0; j < _n; ++j) {
                    _nxt[i][j] = _nxt[i - 1][_nxt[i - 1][j]];
                }
            }
        };

        template <typename T, T(*op)(T, T), T(*e)()>
        struct DoublingSum : private Doubling {
            friend struct FunctionalGraph;

            struct Result {
                int v;
                T sum;
                operator std::pair<int, T>() { return std::pair<int, T>{ v, sum }; }
            };

            auto query(int u, long long d) {
                T sum = e();
                for (int l = _log; l >= 0; --l) if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u, _nxt[l][u])]);
                return Result{ u, sum };
            }

            struct BinarySearchResult {
                int v;
                T sum;
                long long step;
                operator std::tuple<int, T, long long>() { return std::tuple<int, T, long long>{ v, sum, step }; }
            };

            template <typename Pred>
            auto max_step(int u, Pred &&f) {
                assert(f(e()));
                long long step = 0;
                T sum = e();
                for (int l = _log; l >= 0; --l) {
                    if (T nxt_sum = op(sum, _dat[l][u]); f(nxt_sum)) {
                        sum = std::move(nxt_sum), u = _nxt[l][u], step |= 1LL << l;
                    }
                }
                return BinarySearchResult{ u, sum, step };
            }
            template <typename Pred>
            std::optional<BinarySearchResult> step_until(int u, Pred &&f) {
                if (f(e())) return BinarySearchResult { u, e(), 0 };
                auto [v, sum, step] = max_step(u, [&](const T& v) { return not f(v); });
                sum = op(sum, _dat[0][v]), v = _nxt[0][v], ++step;
                if (not f(sum)) return std::nullopt;
                return BinarySearchResult{ v, sum, step };
            }

        private:
            std::vector<std::vector<T>> _dat;

            DoublingSum(const std::vector<int>& nxt, long long max_step, const std::vector<T>& dat) : Doubling(nxt, max_step), _dat(_log + 1, std::vector<T>(_n, e())) {
                _dat[0] = dat;
                for (int i = 1; i <= _log; ++i) for (int j = 0; j < _n; ++j) {
                    _dat[i][j] = op(_dat[i - 1][j], _dat[i - 1][_nxt[i - 1][j]]);
                }
            }
        };

        Doubling doubling(long long max_step) const {
            return Doubling(_nxt, max_step);
        }

        template <typename T, T(*op)(T, T), T(*e)()>
        DoublingSum<T, op, e> doubling(long long max_step, const std::vector<T>& dat) const {
            return DoublingSum<T, op, e>(_nxt, max_step, dat);
        }

        struct InfinitePath {
            int head_v;
            int head_len;
            int loop_v;
            int loop_len;
            InfinitePath() = default;
            InfinitePath(int head_v, int head_len, int loop_v, int loop_len) : head_v(head_v), head_len(head_len), loop_v(loop_v), loop_len(loop_len) {}
        };

        std::vector<InfinitePath> infinite_paths() const {
            std::vector<InfinitePath> res(_n);

            std::vector<int> vis(_n, _n);
            std::vector<int> dep(_n, 0);

            int time = 0;
            auto dfs = [&](auto dfs, int u) -> int {
                vis[u] = time;
                int v = _nxt[u];
                if (vis[v] == vis[u]) { // found cycle
                    int loop_len = dep[u] - dep[v] + 1;
                    res[u] = { u, 0, u, loop_len };
                    return loop_len - 1;
                } else if (vis[v] < vis[u]) {
                    res[u] = { u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };
                    return 0;
                } else {
                    dep[v] = dep[u] + 1;
                    int c = dfs(dfs, v);
                    if (c > 0) { // in cycle
                        res[u] = { u, 0, u, res[v].loop_len };
                        return c - 1;
                    } else { // out of cycle
                        res[u] = { u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };
                        return 0;
                    }
                }
            };
            for (int i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);
            return res;
        }

        /**
         * Calculates k'th iterate: f(f(f(...f(i)))) for all 0 <= i < N in O(N) time.
         * Reference: https://noshi91.hatenablog.com/entry/2019/09/22/114149
         */
        std::vector<int> kth_iterate(const long long k) {
            assert(k >= 0);
            std::vector<int> res(_n);
            std::vector<int> forest_roots;
            std::vector<std::vector<int>> forest(_n);
            std::vector<std::vector<std::pair<long long, int>>> qs(_n);
            for (const auto& path : infinite_paths()) {
                const int v = path.head_v;
                (path.head_len == 0 ? forest_roots : forest[_nxt[v]]).push_back(v);
                if (path.head_len >= k) continue;
                qs[path.loop_v].emplace_back(k - path.head_len, v);
            }
            std::vector<int> dfs_path(_n);
            auto dfs = [&](auto dfs, int u, int d) -> void {
                dfs_path[d] = u;
                if (d >= k) res[u] = dfs_path[d - k];
                for (int v : forest[u]) dfs(dfs, v, d + 1);
            };
            for (int root : forest_roots) dfs(dfs, root, 0);
            std::vector<int8_t> seen(_n, false);
            for (int root : forest_roots) {
                if (seen[root]) continue;
                std::vector<int> cycle{ root };
                for (int v = _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);
                const int len = cycle.size();
                for (int i = 0; i < len; ++i) {
                    const int s = cycle[i];
                    seen[s] = true;
                    for (const auto& [rem, res_index] : qs[s]) {
                        res[res_index] = cycle[(i + rem) % len];
                    }
                }
            }
            return res;
        }

    private:
        int _n;
        std::vector<int> _nxt;

        static int floor_log2(long long v) {
            int l = 0;
            while (1LL << (l + 1) <= v) ++l;
            return l;
        }
    };
} // namespace suisen


#endif // SUISEN_DOUBLING
