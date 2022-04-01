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
        RangeContourOperationQueryOnTree(const std::vector<T> &dat) : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _info(_n), _nodes(_n), _dat(dat) {
            _par.reserve(2 * _n);
            for (int i = 0; i < _n; ++i) _info[i].reserve(30);
        }

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
                F res = id();
                for (i += _n; i; i >>= 1) res = composition(res, _laz[i]);
                return res;
            }
        private:
            int _n;
            std::vector<F> _laz;
        };

        using segtree_type = CommutativeDualSegmentTree;

        struct AuxData {
            int segtree_index;
            int8_t child_index;
            int dist;
        };

        struct Node {
            std::vector<int> _sep;
            segtree_type _seq;

            Node() {}
            Node(const std::vector<std::vector<int>>& g, const std::vector<int8_t>& removed, const std::vector<int> &roots, const bool child_index, std::vector<std::vector<AuxData>>& info) {
                _sep.push_back(0);
                std::deque<std::tuple<int, int, int>> dq;
                for (int r : roots) dq.emplace_back(r, -1, 0);
                int pre_dist = 0, cnt = 0;
                while (dq.size()) {
                    const auto [u, pu, du] = dq.front();
                    dq.pop_front();
                    if (du == pre_dist + 1) _sep.push_back(cnt), pre_dist = du;
                    info[u].push_back({ cnt++, child_index, du });
                    for (int v : g[u]) if (v != pu and not removed[v]) dq.emplace_back(v, u, du + 1);
                }
                _sep.push_back(cnt);
                _seq = segtree_type(cnt);
            }

            F get(int i) {
                return _seq.get(i);
            }
            void apply(int dl, int dr, const F& val) {
                dl = std::max(dl, 0);
                dr = std::min(dr, int(_sep.size()) - 1);
                if (dl < dr) _seq.apply(_sep[dl], _sep[dr], val);
            }
        };

        void add_edge(int u, int v) {
            _g[u].push_back(v);
            _g[v].push_back(u);
        }

        void build() {
            std::vector<int> sub_size(_n, 0);
            std::vector<int> ctr(_n, -1);
            sub_size.reserve(2 * _n);
            ctr.reserve(2 * _n);
            std::vector<std::vector<int>> ch(_n);
            ch.reserve(2 * _n);

            auto merge = [&](std::vector<int> &&l, std::vector<int> &&r) -> std::vector<int>&& {
                if (l.size() > r.size()) std::swap(l, r);
                for (int e : l) r.push_back(e);
                return std::move(r);
            };

            auto rec = [&](auto rec, int r, int siz) -> int {
                int c = -1;
                auto get_centroid = [&](auto get_centroid, int u, int p) -> void {
                    sub_size[u] = 1;
                    for (int v : _g[u]) {
                        if (v == p or _removed[v]) continue;
                        get_centroid(get_centroid, v, u);
                        if (v == c) {
                            sub_size[u] = siz - sub_size[c];
                            break;
                        }
                        sub_size[u] += sub_size[v];
                    }
                    if (c < 0 and sub_size[u] * 2 > siz) c = u;
                };
                get_centroid(get_centroid, r, -1);

                _removed[c] = true;
                for (int v : _g[c]) {
                    if (_removed[v]) continue;
                    const int comp_size = sub_size[v];
                    ctr[v] = rec(rec, v, comp_size);
                    sub_size[v] = comp_size;
                }

                auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };
                std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp };

                for (int v : _g[c]) {
                    if (_removed[v]) continue;
                    ch[v] = { v };
                    pq.push(v);
                }

                while (pq.size() >= 2) {
                    const int u = pq.top(); pq.pop();
                    const int v = pq.top(); pq.pop();
                    if (pq.empty()) {
                        _par[ctr[u]] = _par[ctr[v]] = c;
                        _nodes[c][0] = Node{ _g, _removed, ch[u], 0, _info };
                        _nodes[c][1] = Node{ _g, _removed, ch[v], 1, _info };
                        break;
                    }
                    const int new_node = sub_size.size();
                    sub_size.push_back(sub_size[u] + sub_size[v]);
                    ctr.push_back(new_node);
                    _par.push_back(-1);
                    _par[ctr[u]] = _par[ctr[v]] = new_node;
                    _nodes.emplace_back();
                    _nodes[new_node][0] = Node{ _g, _removed, ch[u], 0, _info };
                    _nodes[new_node][1] = Node{ _g, _removed, ch[v], 1, _info };
                    ch.push_back(merge(std::move(ch[u]), std::move(ch[v])));
                    ch[u].clear(), ch[u].shrink_to_fit();
                    ch[v].clear(), ch[v].shrink_to_fit();
                    pq.push(new_node);
                }
                if (pq.size()) {
                    int u = pq.top(); pq.pop();
                    _par[ctr[u]] = c;
                    _nodes[c][0] = Node{ _g, _removed, ch[u], 0, _info };
                }
                _removed[c] = false;
                return c;
            };
            rec(rec, 0, _n);
        }

        T get(int u) {
            F res = id();
            int v = _par[u];
            for (const auto &info : _info[u]) {
                res = composition(res, _nodes[std::exchange(v, _par[v])][info.child_index].get(info.segtree_index));
            }
            return mapping(res, _dat[u]);
        }
        void apply(int u, int dl, int dr, const F& val) {
            if (dl <= 0 and 0 < dr) _dat[u] = mapping(val, _dat[u]);
            _nodes[u][0].apply(dl - 1, dr - 1, val);
            _nodes[u][1].apply(dl - 1, dr - 1, val);
            int v = _par[u];
            for (const auto &info : _info[u]) {
                int ql = dl - info.dist - 2, qr = dr - info.dist - 2;
                if (v < _n and ql <= -1 and -1 < qr) _dat[v] = mapping(val, _dat[v]);
                _nodes[std::exchange(v, _par[v])][info.child_index ^ 1].apply(ql, qr, val);
            }
        }

    private:
        int _n;
        std::vector<std::vector<int>> _g;
        std::vector<int> _par;
        std::vector<int8_t> _removed;
        std::vector<std::vector<AuxData>> _info;
        std::vector<std::array<Node, 2>> _nodes;
        std::vector<T> _dat;
    };
} // namespace suisen

#endif // SUISEN_RANGE_CONTOUR_OPERATION_QUERY_ON_TREE_BASE
