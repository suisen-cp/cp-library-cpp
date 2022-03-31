#ifndef SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE
#define SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE

#include <cstdint>
#include <deque>
#include <map>
#include <queue>
#include <tuple>

#include <atcoder/segtree>

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct RangeContourAggregationQueryOnTree {
        RangeContourAggregationQueryOnTree() {}
        RangeContourAggregationQueryOnTree(int n) : RangeContourAggregationQueryOnTree(std::vector<T>(n, e())) {}
        RangeContourAggregationQueryOnTree(const std::vector<T>& dat) : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _pos(_n), _idx(_n), _dist(_n), _sub(_n), _dat(dat) {}

        using segtree_type = atcoder::segtree<T, op, e>;

        struct SubTree {
            std::vector<int> _sep;
            segtree_type _seq;

            SubTree() {}
            SubTree(
                const std::vector<std::vector<int>> &g,
                const std::vector<int8_t> &removed,
                const int root,
                const std::vector<T> &dat,
                const bool is_right_child,
                std::vector<std::vector<int8_t>> &idx,
                std::vector<std::vector<int>> &pos,
                std::vector<std::vector<int>> &dist
            ) {
                auto is_dummy_vertex = [&](int u) { return u >= int(dat.size()); };
                _sep.push_back(0);
                std::vector<T> reordered_dat;
                std::deque<std::tuple<int, int, int>> dq { { root, -1, 0 } };
                int pre_dist = 0;
                while (dq.size()) {
                    const auto [u, pu, du] = dq.front();
                    dq.pop_front();
                    if (du == pre_dist + 1) {
                        _sep.push_back(reordered_dat.size());
                        pre_dist = du;
                    }
                    bool b = is_dummy_vertex(u);
                    if (not b) {
                        pos[u].push_back(reordered_dat.size());
                        reordered_dat.push_back(dat[u]);
                        idx[u].push_back(is_right_child);
                        dist[u].push_back(du);
                    }
                    for (int v : g[u]) {
                        if (v == pu or removed[v]) continue;
                        if (b) {
                            dq.emplace_front(v, u, du);
                        } else {
                            dq.emplace_back(v, u, du + 1);
                        }
                    }
                }
                _sep.push_back(reordered_dat.size());
                _seq = segtree_type(reordered_dat);
            }

            void set(int i, const T &val) {
                _seq.set(i, val);
            }
            T prod(int dl, int dr) {
                if (dl < 0) dl = 0;
                if (dr >= int(_sep.size())) dr = int(_sep.size()) - 1;
                if (dl >= dr) return e();
                int ql = _sep[dl], qr = _sep[dr];
                return _seq.prod(ql, qr);
            }
        };

        void add_edge(int u, int v) {
            _g[u].push_back(v);
            _g[v].push_back(u);
        }

        void build() {
            std::vector<int> sub(_n, 0);
            std::vector<int> ctr(_n, -1);
            auto rec = [&](auto rec, int r, int siz) -> int {
                int c = -1;
                auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                    sub[u] = 1;
                    for (int v : _g[u]) {
                        if (v == p or _removed[v]) continue;
                        get_centroid(get_centroid, v, u);
                        if (v == c) {
                            sub[u] = siz - sub[c];
                            break;
                        }
                        sub[u] += sub[v];
                    }
                    if (c < 0 and sub[u] * 2 > siz) c = u;
                };
                get_centroid(get_centroid, r, -1);

                _removed[c] = true;
                for (int v : _g[c]) {
                    if (_removed[v]) continue;
                    const int comp_size = sub[v];
                    ctr[v] = rec(rec, v, comp_size);
                    sub[v] = comp_size;
                }

                auto comp = [&](int i, int j) { return sub[i] > sub[j]; };
                std::priority_queue<int, std::vector<int>, decltype(comp)> pq { comp };

                for (int v : _g[c]) {
                    if (_removed[v]) continue;
                    pq.push(v);
                }

                while (pq.size() >= 2) {
                    int u = pq.top();
                    pq.pop();
                    int v = pq.top();
                    pq.pop();
                    if (pq.empty()) {
                        _par[ctr[u]] = _par[ctr[v]] = c;
                        _sub[c][0] = SubTree{ _g, _removed, u, _dat, 0, _idx, _pos, _dist };
                        _sub[c][1] = SubTree{ _g, _removed, v, _dat, 1, _idx, _pos, _dist };
                    } else {
                        int new_node = sub.size();
                        sub.push_back(sub[u] + sub[v]);
                        ctr.push_back(new_node);
                        _par.push_back(-1);
                        _par[ctr[u]] = _par[ctr[v]] = new_node;
                        pq.push(new_node);
                        _removed.push_back(false);
                        _g.emplace_back();
                        _g[new_node].push_back(u);
                        _g[new_node].push_back(v);
                        _sub.emplace_back();
                        _sub[new_node][0] = SubTree{ _g, _removed, u, _dat, 0, _idx, _pos, _dist };
                        _sub[new_node][1] = SubTree{ _g, _removed, v, _dat, 1, _idx, _pos, _dist };
                    }
                }
                if (pq.size()) {
                    int u = pq.top();
                    pq.pop();
                    _par[ctr[u]] = c;
                    _sub[c][0] = SubTree{ _g, _removed, u, _dat, 0, _idx, _pos, _dist };
                }
                _removed[c] = false;
                return c;
            };
            rec(rec, 0, _n);
        }

        T get(int u) {
            return _dat[u];
        }
        void set(int u, const T &val) {
            _dat[u] = val;
            int h = _pos[u].size();
            for (int i = 0, v = _par[u]; i < h; ++i) {
                _sub[std::exchange(v, _par[v])][_idx[u][i]].set(_pos[u][i], val);
            }
        }
        T prod(int u, int dl, int dr) {
            T res = dl <= 0 and 0 < dr ? _dat[u] : e();
            res = op(res, _sub[u][0].prod(dl - 1, dr - 1));
            res = op(res, _sub[u][1].prod(dl - 1, dr - 1));
            int h = _pos[u].size();
            for (int i = 0, v = _par[u]; i < h; ++i) {
                int ql = dl - _dist[u][i] - 2, qr = dr - _dist[u][i] - 2;
                if (v < _n and ql <= -1 and -1 < qr) res = op(res, _dat[v]);
                res = op(res, _sub[std::exchange(v, _par[v])][_idx[u][i] ^ 1].prod(ql, qr));
            }
            return res;
        }

    private:
        int _n;
        std::vector<std::vector<int>> _g;
        std::vector<int> _par;
        std::vector<int8_t> _removed;
        std::vector<std::vector<int>> _pos;
        std::vector<std::vector<int8_t>> _idx;
        std::vector<std::vector<int>> _dist;
        std::vector<std::array<SubTree, 2>> _sub;
        std::vector<T> _dat;
    };
} // namespace suisen


#endif // SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE
