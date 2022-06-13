#ifndef SUISEN_MANHATTAN_MST
#define SUISEN_MANHATTAN_MST

#include <limits>
#include <numeric>
#include <tuple>


#include "library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp"
#include "library/graph/kruscal.hpp"

namespace suisen {
    namespace internal::manhattan_mst {
        template <typename T>
        std::pair<T, int> op(std::pair<T, int> x, std::pair<T, int> y) { return std::max(x, y); };
        template <typename T>
        std::pair<T, int> e() { return { std::numeric_limits<T>::min(), -1 }; };
        template <typename T>
        using PrefixMaxQuery = FenwickTreePrefix<std::pair<T, int>, op<T>, e<T>>;
    } // namespace internal::manhattan_mst

    template <typename WeightType, typename T>
    KruscalMinimumSpanningTree<WeightType> manhattan_mst(std::vector<std::pair<T, T>> points) {
        using namespace internal::manhattan_mst;

        const int n = points.size();
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);

        auto make_edges = [&](KruscalMinimumSpanningTree<WeightType> &mst) {
            std::sort(
                p.begin(), p.end(),
                [&points](int i, int j) {
                    const auto &[xi, yi] = points[i];
                    const auto &[xj, yj] = points[j];
                    return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;
                }
            );

            std::vector<T> comp_x(n);
            for (int i = 0; i < n; ++i) comp_x[i] = points[i].first;
            std::sort(comp_x.begin(), comp_x.end());
            comp_x.erase(std::unique(comp_x.begin(), comp_x.end()), comp_x.end());
            const int m = comp_x.size();

            auto compress = [&](const T& x) { return std::lower_bound(comp_x.begin(), comp_x.end(), x) - comp_x.begin(); };

            PrefixMaxQuery<T> pmq(m);

            for (int i : p) {
                const auto& [x, y] = points[i];
                const int cx = compress(x);
                if (const auto p = pmq.prefix_query(cx + 1); p != e<T>()) {
                    const auto& [v, j] = p;
                    mst.add_edge(i, j, x + y - v);
                }
                pmq.apply(cx, { x + y, i });
            }
        };

        KruscalMinimumSpanningTree<WeightType> mst(n);
        for (int x_rev = 0; x_rev < 2; ++x_rev) {
            for (int y_rev = 0; y_rev < 2; ++y_rev) {
                for (int xy_rev = 0; xy_rev < 2; ++xy_rev) {
                    make_edges(mst);
                    for (auto& [x, y] : points) std::swap(x, y);
                }
                for (auto& [x, _] : points) x = -x;
            }
            for (auto& [_, y] : points) y = -y;
        }
        assert(mst.build());
        return mst;
    }
} // namespace suisen


#endif // SUISEN_MANHATTAN_MST
