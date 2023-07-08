#ifndef SUISEN_BIPARTITE_MATCHING
#define SUISEN_BIPARTITE_MATCHING

#include <algorithm>
#include <cassert>
#include <deque>
#include <random>
#include <utility>
#include <vector>

namespace suisen {
    struct BipartiteMatching {
        static constexpr int ABSENT = -1;

        BipartiteMatching() = default;
        BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, ABSENT), _to_l(_m, ABSENT), _g(n + m) {}

        void add_edge(int fr, int to) {
            _g[fr].push_back(to), _f = -1;
        }

        // template <bool shuffle = true>
        // int solve_heuristics() {
        //     if (_f >= 0) return _f;

        //     static std::mt19937 rng(std::random_device{}());
        //     if constexpr (shuffle) for (auto& adj : _g) std::shuffle(adj.begin(), adj.end(), rng);

        //     std::vector<int8_t> vis(_n, false);

        //     auto dfs = [&, this](auto dfs, int u) -> bool {
        //         if (std::exchange(vis[u], true)) return false;
        //         for (int v : _g[u]) if (_to_l[v] == ABSENT) return _to_r[u] = v, _to_l[v] = u, true;
        //         for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u] = v, _to_l[v] = u, true;
        //         return false;
        //     };

        //     for (bool upd = true; std::exchange(upd, false);) {
        //         vis.assign(_n, false);
        //         for (int i = 0; i < _n; ++i) if (_to_r[i] == ABSENT) upd |= dfs(dfs, i);
        //     }

        //     return _f = _n - std::count(_to_r.begin(), _to_r.end(), ABSENT);
        // }
    
        int solve() {
            if (_f >= 0) return _f;
            const auto h = reversed_graph();

            std::vector<int> level(_n + _m), iter(_n + _m);
            std::deque<int> que;
            auto bfs = [&] {
                for (int i = 0; i < _n; ++i) {
                    if (_to_r[i] == ABSENT) level[i] = 0, que.push_back(i);
                    else level[i] = -1;
                }
                std::fill(level.begin() + _n, level.end(), -1);
                bool ok = false;
                while (not que.empty()) {
                    const int l = que.front();
                    que.pop_front();
                    for (int r : _g[l]) if (_to_r[l] != r and level[_n + r] < 0) {
                        const int nl = _to_l[r];
                        level[_n + r] = level[l] + 1;
                        if (nl == ABSENT) ok = true;
                        else if (level[nl] < 0) level[nl] = level[l] + 2, que.push_back(nl);
                    }
                }
                return ok;
            };
            auto dfs = [&](auto dfs, const int r) -> bool {
                const int level_v = level[_n + r];
                if (level_v < 0) return false;
                const int dr = h[r].size();
                for (int &i = iter[_n + r]; i < dr; ++i) {
                    const int l = h[r][i];
                    if (level_v <= level[l] or _to_l[r] == l or iter[l] > _m) continue;
                    if (int nr = _to_r[l]; nr == ABSENT) {
                        iter[l] = _m + 1, level[l] = _n + _m;
                        _to_r[l] = r, _to_l[r] = l;
                        return true;
                    } else if (iter[l] <= nr) {
                        iter[l] = nr + 1;
                        if (level[l] > level[_n + nr] and dfs(dfs, nr)) {
                            _to_r[l] = r, _to_l[r] = l;
                            return true;
                        }
                        iter[l] = _m + 1, level[l] = _n + _m;
                    }
                }
                return level[_n + r] = _n + _m, false;
            };
            for (_f = 0; bfs();) {
                std::fill(iter.begin(), iter.end(), 0);
                for (int j = 0; j < _m; ++j) if (_to_l[j] == ABSENT) _f += dfs(dfs, j);
            }
            return _f;
        }

        std::vector<std::pair<int, int>> max_matching() {
            if (_f < 0) solve();
            std::vector<std::pair<int, int>> res;
            res.reserve(_f);
            for (int i = 0; i < _n; ++i) if (_to_r[i] != ABSENT) res.emplace_back(i, _to_r[i]);
            return res;
        }

        std::vector<std::pair<int, int>> min_edge_cover() {
            auto res = max_matching();
            std::vector<bool> vl(_n, false), vr(_n, false);
            for (const auto& [u, v] : res) vl[u] = vr[v] = true;
            for (int u = 0; u < _n; ++u) for (int v : _g[u]) if (not (vl[u] and vr[v])) {
                vl[u] = vr[v] = true;
                res.emplace_back(u, v);
            }
            return res;
        }

        std::vector<int> min_vertex_cover() {
            if (_f < 0) solve();
            std::vector<std::vector<int>> g(_n + _m);
            std::vector<bool> cl(_n, true), cr(_m, false);
            for (int u = 0; u < _n; ++u) for (int v : _g[u]) {
                if (_to_r[u] == v) {
                    g[v + _n].push_back(u);
                    cl[u] = false;
                } else {
                    g[u].push_back(v + _n);
                }
            }
            std::vector<bool> vis(_n + _m, false);
            std::deque<int> dq;
            for (int i = 0; i < _n; ++i) if (cl[i]) {
                dq.push_back(i);
                vis[i] = true;
            }
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : g[u]) {
                    if (vis[v]) continue;
                    vis[v] = true;
                    (v < _n ? cl[v] : cr[v - _n]) = true;
                    dq.push_back(v);
                }
            }
            std::vector<int> res;
            for (int i = 0; i < _n; ++i) if (not cl[i]) res.push_back(i);
            for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n + i);
            return res;
        }

        std::vector<int> max_independent_set() {
            std::vector<bool> use(_n + _m, true);
            for (int v : min_vertex_cover()) use[v] = false;
            std::vector<int> res;
            for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);
            return res;
        }

        int left_size() const { return _n; }
        int right_size() const { return _m; }
        std::pair<int, int> size() const { return { _n, _m }; }

        int right(int l) const { assert(_f >= 0); return _to_r[l]; }
        int left(int r) const { assert(_f >= 0); return _to_l[r]; }

        const auto graph() const { return _g; }

        std::vector<std::vector<int>> reversed_graph() const {
            std::vector<std::vector<int>> h(_m);
            for (int i = 0; i < _n; ++i) for (int j : _g[i]) h[j].push_back(i);
            return h;
        }

    private:
        int _n, _m;
        std::vector<int> _to_r, _to_l;
        std::vector<std::vector<int>> _g;
        int _f = 0;
    };

} // namespace suisen


#endif // SUISEN_BIPARTITE_MATCHING
