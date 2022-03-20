#ifndef SUISEN_CONTOUR_QUERY_ON_TREE
#define SUISEN_CONTOUR_QUERY_ON_TREE

#include <deque>
#include <map>
#include <tuple>

#include <atcoder/segtree>

#include "library/tree/centroid_decomposition.hpp"
#include "library/tree/heavy_light_decomposition.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct ContourAggregationQueryOnTree : private CentroidDecomposition {
        using base_type = CentroidDecomposition;
        using base_type::base_type;
        using base_type::add_edge;

        using segtree_type = atcoder::segtree<T, op, e>;

        void build(const std::vector<T> &dat) {
            _hld = HeavyLightDecomposition(*this);
            _siz.resize(size());
            _sub_root.resize(size());
            _sep.resize(size());
            _range.resize(size());
            _seg.resize(size());
            _tree = base_type::decomp(
                [&](int centroid, int siz) {
                    _siz[centroid] = siz;
                    std::vector<T> vs { dat[centroid] };
                    auto &sep = _sep[centroid];
                    auto &ran = _range[centroid];
                    auto &sub = _sub_root[centroid];
                    // (current vertex, parent vertex, component id, depth)
                    std::deque<std::tuple<int, int, int, int>> dq;
                    for (int sub_root : (*this)[centroid]) sub.push_back(sub_root);
                    std::sort(sub.begin(), sub.end());
                    for (std::size_t i = 0; i < sub.size(); ++i) {
                        dq.emplace_back(sub[i], centroid, i, 1);
                    }
                    sep.push_back(0);
                    ran.resize(sub.size(), { { -1, -1 } });
                    int pre_dep = 0, pre_id = -1;
                    while (dq.size()) {
                        const auto [u, p, id, dep] = dq.front();
                        dq.pop_front();
                        if (pre_dep != dep or pre_id != id) {
                            if (pre_dep != dep) sep.push_back(vs.size());
                            if (pre_id >= 0) {
                                ran[pre_id][pre_dep].second = vs.size();
                            }
                            ran[id].emplace_back(vs.size(), -1);
                            pre_dep = dep, pre_id = id;
                        }
                        vs.push_back(dat[u]);
                        for (int v : (*this)[u]) {
                            if (v == p) continue;
                            dq.emplace_back(v, u, id, dep + 1);
                        }
                    }
                    if (pre_id >= 0) {
                        ran[pre_id][pre_dep].second = vs.size();
                        sep.push_back(vs.size());
                    }
                    _seg[centroid] = segtree_type(std::move(vs));
                }
            );
        }

        T prod(int u, int d) {
            T res = e();
            int skip = -1;
            for (int v = u;;) {
                res = op(res, prod(v, d - _hld.dist(u, v), skip));
                int p = _tree.get_parent(v);
                if (p < 0) break;
                skip = _hld.move_to(p, v, 1);
                v = p;
            }
            return res;
        }

    private:
        HeavyLightDecomposition _hld;

        CentroidDecomposition::DecompositionTree _tree;

        std::vector<int> _siz;
        std::vector<std::vector<int>> _sub_root;
        std::vector<std::vector<int>> _sep;
        std::vector<std::vector<std::vector<std::pair<int, int>>>> _range;
        std::vector<segtree_type> _seg;

        T prod(int u, int d, int skip) {
            if (d == 0) return _seg[u].get(0);
            if (d < 0 or int(_sep[u].size()) <= d + 1) return e();
            int l = _sep[u][d], r = _sep[u][d + 1];
            if (skip < 0) return _seg[u].prod(l, r);
            int skip_index = std::lower_bound(_sub_root[u].begin(), _sub_root[u].end(), skip) - _sub_root[u].begin();
            if (int(_range[u][skip_index].size()) <= d) {
                return _seg[u].prod(l, r);
            } else {
                auto [ml, mr] = _range[u][skip_index][d];
                return op(_seg[u].prod(l, ml), _seg[u].prod(mr, r));
            }
        }
    };
} // namespace suisen


#endif // SUISEN_CONTOUR_QUERY_ON_TREE
