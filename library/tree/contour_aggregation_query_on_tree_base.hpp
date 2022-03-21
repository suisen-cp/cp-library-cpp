#ifndef SUISEN_CONTOUR_QUERY_ON_TREE_BASE
#define SUISEN_CONTOUR_QUERY_ON_TREE_BASE

#include <deque>
#include <map>
#include <tuple>

#include "library/tree/centroid_decomposition.hpp"

namespace suisen {
    template <typename SequenceType>
    struct ContourAggregationQueryOnTreeBase : private CentroidDecomposition {
        using base_type = CentroidDecomposition;
        using base_type::base_type;
        using base_type::add_edge;

        using sequence_type = SequenceType;

        template <typename T>
        void build(const std::vector<T>& dat) {
            const int n = size(), log_n = ceil_log2(n);
            _seq_idx.resize(n, { 0 });
            _sub_idx_dep.resize(n, { { -1, 0 } });
            _sep.resize(n, { 0 });
            _range.resize(n);
            _seq.resize(n);
            for (int i = 0; i < n; ++i) _seq_idx[i].reserve(log_n), _sub_idx_dep.reserve(log_n);
            _tree = base_type::decomp(
                base_type::dummy,
                [&](int centroid, int siz) {
                    std::vector<T> seq_dat{ dat[centroid] };
                    seq_dat.reserve(siz);
                    if (siz > 1) {
                        // (current vertex, parent vertex, component id, depth)
                        std::deque<std::tuple<int, int, int, int>> dq;
                        int sub_root_num = 0;
                        for (int sub_root : (*this)[centroid]) dq.emplace_back(sub_root, centroid, sub_root_num++, 1);
                        _range[centroid].resize(sub_root_num, { { 0, 0 } });
                        while (dq.size()) {
                            const auto [u, p, id, dep] = dq.front();
                            dq.pop_front();
                            const int ord = seq_dat.size();
                            if (int(_sep[centroid].size()) <= dep) _sep[centroid].push_back(ord);
                            if (int(_range[centroid][id].size()) <= dep) _range[centroid][id].emplace_back(ord, ord);
                            ++_range[centroid][id].back().second;
                            _sub_idx_dep[u].emplace_back(id, dep);
                            _seq_idx[u].push_back(ord);
                            seq_dat.push_back(dat[u]);
                            for (int v : (*this)[u]) if (v != p) dq.emplace_back(v, u, id, dep + 1);
                        }
                    }
                    _sep[centroid].push_back(siz);
                    _seq[centroid] = sequence_type(std::move(seq_dat));
                }
            );
        }

        // getter(seq, i)
        template <typename Getter>
        auto get(int u, Getter&& getter) {
            return getter(_seq[u], 0);
        }
        // setter(seq, i)
        template <typename Setter>
        void set(int u, Setter&& setter) {
            for (int i : _seq_idx[u]) setter(_seq[std::exchange(u, _tree.get_parent(u))], i);
        }
        // agg(seq, l, r)
        template <typename Aggregator>
        void prod(int u, int d, Aggregator&& agg) {
            for (auto [sub_idx, sub_dep] : _sub_idx_dep[u]) prod(std::exchange(u, _tree.get_parent(u)), d - sub_dep, sub_idx, agg);
        }

    protected:
        CentroidDecomposition::DecompositionTree _tree;

        std::vector<std::vector<int>> _seq_idx;
        std::vector<std::vector<std::pair<int, int>>> _sub_idx_dep;
        std::vector<std::vector<int>> _sep;
        std::vector<std::vector<std::vector<std::pair<int, int>>>> _range;
        std::vector<sequence_type> _seq;

        template <typename Aggregator>
        void prod(int u, int d, int skip_index, Aggregator&& agg) {
            if (d < 0 or int(_sep[u].size()) <= d + 1) return;
            if (d == 0) {
                agg(_seq[u], 0, 1);
                return;
            }
            int l = _sep[u][d], r = _sep[u][d + 1];
            if (skip_index < 0 or int(_range[u][skip_index].size()) <= d) {
                agg(_seq[u], l, r);
            } else {
                auto [ml, mr] = _range[u][skip_index][d];
                agg(_seq[u], l, ml), agg(_seq[u], mr, r);
            }
        }

        static int ceil_log2(int n) {
            int res = 0;
            while (1 << res < n) ++res;
            return res;
        }
    };
} // namespace suisen


#endif // SUISEN_CONTOUR_QUERY_ON_TREE_BASE
