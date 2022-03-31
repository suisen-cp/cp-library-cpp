#ifndef SUISEN_RANGE_CONTOUR_OPERATION_QUERY_ON_TREE_BASE
#define SUISEN_RANGE_CONTOUR_OPERATION_QUERY_ON_TREE_BASE

#include <cstdint>
#include <deque>
#include <map>
#include <queue>
#include <tuple>

namespace suisen {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct RangeContourOperationQueryOnTree {
        RangeContourOperationQueryOnTree() {}
        RangeContourOperationQueryOnTree(int n, const T &fill_value) : RangeContourOperationQueryOnTree(std::vector<T>(n, fill_value)) {}
        RangeContourOperationQueryOnTree(const std::vector<T> &dat) : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _pos(_n), _idx(_n), _dist(_n), _sub(_n), _dat(dat) {}

        struct CommutativeDualSegmentTree {
            CommutativeDualSegmentTree() {}
            CommutativeDualSegmentTree(int n) : _n(n), _laz(2 * _n, id()) {}
            void apply(int l, int r, const F& f) {
                for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {
                    if (l & 1) _laz[l] = composition(_laz[l], f), ++l;
                    if (r & 1) --r, _laz[r] = composition(_laz[r], f);
                }
            }
            F get(int i) {
                T res = id();
                for (i += _n; i; i >>= 1) res = composition(res, _laz[i]);
                return res;
            }
        private:
            int _n;
            std::vector<F> _laz;
        };

        using segtree_type = CommutativeDualSegmentTree;

        struct SubTree {
            std::vector<int> _sep;
            segtree_type _seq;

            SubTree() {}
            SubTree(
                const std::vector<std::vector<int>>& g,
                const std::vector<int8_t>& removed,
                const int root,
                const bool is_right_child,
                std::vector<std::vector<int8_t>>& idx,
                std::vector<std::vector<int>>& pos,
                std::vector<std::vector<int>>& dist
            ) {
                const int siz = dist.size();
                auto is_dummy_vertex = [&](int u) { return u >= siz; };
                _sep.push_back(0);
                std::deque<std::tuple<int, int, int>> dq{ { root, -1, 0 } };
                int pre_dist = 0, cnt = 0;
                while (dq.size()) {
                    const auto [u, pu, du] = dq.front();
                    dq.pop_front();
                    if (du == pre_dist + 1) {
                        _sep.push_back(cnt);
                        pre_dist = du;
                    }
                    bool b = is_dummy_vertex(u);
                    if (not b) {
                        pos[u].push_back(cnt++);
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
                _sep.push_back(cnt);
                _seq = segtree_type(cnt);
            }

            F get(int i) {
                return _seq.get(i);
            }
            void apply(int dl, int dr, const F& val) {
                if (dl < 0) dl = 0;
                if (dr >= int(_sep.size())) dr = int(_sep.size()) - 1;
                if (dl >= dr) return;
                int ql = _sep[dl], qr = _sep[dr];
                _seq.apply(ql, qr, val);
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
                std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp };

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
                        _sub[c][0] = SubTree{ _g, _removed, u, 0, _idx, _pos, _dist };
                        _sub[c][1] = SubTree{ _g, _removed, v, 1, _idx, _pos, _dist };
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
                        _sub[new_node][0] = SubTree{ _g, _removed, u, 0, _idx, _pos, _dist };
                        _sub[new_node][1] = SubTree{ _g, _removed, v, 1, _idx, _pos, _dist };
                    }
                }
                if (pq.size()) {
                    int u = pq.top();
                    pq.pop();
                    _par[ctr[u]] = c;
                    _sub[c][0] = SubTree{ _g, _removed, u, 0, _idx, _pos, _dist };
                }
                _removed[c] = false;
                return c;
            };
            rec(rec, 0, _n);
        }

        T get(int u) {
            F res = id();
            int h = _pos[u].size();
            for (int i = 0, v = _par[u]; i < h; ++i) {
                res = composition(res, _sub[std::exchange(v, _par[v])][_idx[u][i]].get(_pos[u][i]));
            }
            return mapping(res, _dat[u]);
        }
        void apply(int u, int dl, int dr, const F& val) {
            if (dl <= 0 and 0 < dr) _dat[u] = mapping(val, _dat[u]);
            _sub[u][0].apply(dl - 1, dr - 1, val);
            _sub[u][1].apply(dl - 1, dr - 1, val);
            int h = _pos[u].size();
            for (int i = 0, v = _par[u]; i < h; ++i) {
                int ql = dl - _dist[u][i] - 2, qr = dr - _dist[u][i] - 2;
                if (v < _n and ql <= -1 and -1 < qr) _dat[v] = mapping(val, _dat[v]);
                _sub[std::exchange(v, _par[v])][_idx[u][i] ^ 1].apply(ql, qr, val);
            }
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


#endif // SUISEN_RANGE_CONTOUR_OPERATION_QUERY_ON_TREE_BASE
