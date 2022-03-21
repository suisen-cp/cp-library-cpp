#ifndef SUISEN_CONTOUR_QUERY_ON_TREE
#define SUISEN_CONTOUR_QUERY_ON_TREE

#include <atcoder/segtree>

#include "library/tree/contour_aggregation_query_on_tree_base.hpp"

namespace suisen {
    template <typename T, T(*op)(T, T), T(*e)()>
    struct ContourAggregationQueryOnTree : ContourAggregationQueryOnTreeBase<atcoder::segtree<T, op, e>> {
        using base_type = ContourAggregationQueryOnTreeBase<atcoder::segtree<T, op, e>>;
        using base_type::base_type;

        T prod(int u, int d) {
            T res = e();
            base_type::prod(u, d, [&res](auto &seg, int l, int r) { res = op(res, seg.prod(l, r)); });
            return res;
        }
        T get(int u) {
            return base_type::get(u, [](auto &seg, int i) { return seg.get(i); });
        }
        void set(int u, const T &val) {
            base_type::set(u, [&val](auto &seg, int i) { seg.set(i, val); });
        }
        template <typename F>
        void apply(int u, F &&f) {
            set(u, f(get(u)));
        }
    };
} // namespace suisen


#endif // SUISEN_CONTOUR_QUERY_ON_TREE
