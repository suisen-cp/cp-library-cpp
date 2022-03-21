#ifndef SUISEN_CONTOUR_QUERY_ON_TREE_BASE
#define SUISEN_CONTOUR_QUERY_ON_TREE_BASE

#include <deque>
#include <map>
#include <tuple>

#include "library/tree/centroid_decomposition.hpp"
#include "library/tree/heavy_light_decomposition.hpp"

namespace suisen {
    template <typename SequenceType>
    struct ContourAggregationQueryOnTreeBase : private CentroidDecomposition {
        using base_type = CentroidDecomposition;
        using base_type::base_type;
        using base_type::add_edge;

        using sequence_type = SequenceType;

        template <typename T>
        void build(const std::vector<T> &dat) {
            _hld = HeavyLightDecomposition(*this);
            _idx.resize(size());
            _sub_root.resize(size());
            _sep.resize(size());
            _range.resize(size());
            _seq.resize(size());
            _tree = base_type::decomp(
                base_type::dummy,
                [&](int centroid, int) {
                    _idx[centroid].push_back(0);
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
                        _idx[u].push_back(vs.size());
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
                    _seq[centroid] = sequence_type(std::move(vs));
                }
            );
        }

        // getter(seq, i)
        template <typename Getter>
        auto get(int u, Getter &&getter) {
            return getter(_seq[u], 0);
        }
        // setter(seq, i)
        template <typename Setter>
        void set(int u, Setter &&setter) {
            for (int i : _idx[u]) setter(_seq[std::exchange(u, _tree.get_parent(u))], i);
        }
        // agg(seq, l, r)
        template <typename Aggregator>
        void prod(int u, int d, Aggregator &&agg) {
            for (int v = u, skip = -1;;) {
                prod(v, d - _hld.dist(u, v), skip, agg);
                int p = _tree.get_parent(v);
                if (p < 0) break;
                skip = _hld.move_to(p, v, 1);
                v = p;
            }
        }
        
    protected:
        HeavyLightDecomposition _hld;

        CentroidDecomposition::DecompositionTree _tree;

        std::vector<std::vector<int>> _idx;
        std::vector<std::vector<int>> _sub_root;
        std::vector<std::vector<int>> _sep;
        std::vector<std::vector<std::vector<std::pair<int, int>>>> _range;
        std::vector<sequence_type> _seq;

        template <typename Aggregator>
        void prod(int u, int d, int skip, Aggregator &&agg) {
            if (d == 0) {
                agg(_seq[u], 0, 1);
                return;
            }
            if (d < 0 or int(_sep[u].size()) <= d + 1) return;
            int l = _sep[u][d], r = _sep[u][d + 1];
            if (skip < 0) {
                agg(_seq[u], l, r);
                return;
            }
            int skip_index = std::lower_bound(_sub_root[u].begin(), _sub_root[u].end(), skip) - _sub_root[u].begin();
            if (int(_range[u][skip_index].size()) <= d) {
                agg(_seq[u], l, r);
            } else {
                auto [ml, mr] = _range[u][skip_index][d];
                agg(_seq[u], l, ml);
                agg(_seq[u], mr, r);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_CONTOUR_QUERY_ON_TREE_BASE
