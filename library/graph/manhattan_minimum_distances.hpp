#ifndef SUISEN_MANHATTAN_MINIMUM_DISTANCES
#define SUISEN_MANHATTAN_MINIMUM_DISTANCES

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

#include "library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp"

namespace suisen {
    namespace internal::manhattan_minimum_distances {
        template <typename T>
        T op(T x, T y) { return std::max(x, y); };
        template <typename T>
        T e() { return std::numeric_limits<T>::min(); };
        template <typename T>
        using PrefixMaxQuery = FenwickTreePrefix<T, op<T>, e<T>>;
    } // namespace internal::manhattan_minimum_distances

    template <typename T>
    std::vector<T> manhattan_minimum_distances(std::vector<std::pair<T, T>> points) {
        using namespace internal::manhattan_minimum_distances;

        const int n = points.size();
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);

        std::vector<T> res(n, std::numeric_limits<T>::max());

        auto sweep = [&] {
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
                if (const auto v = pmq.prefix_query(cx + 1); v != e<T>()) {
                    res[i] = std::min(res[i], x + y - v);
                }
                pmq.apply(cx, x + y);
            }
        };

        for (int x_rev = 0; x_rev < 2; ++x_rev) {
            for (int y_rev = 0; y_rev < 2; ++y_rev) {
                for (int xy_rev = 0; xy_rev < 2; ++xy_rev) {
                    sweep();
                    for (auto& [x, y] : points) std::swap(x, y);
                }
                for (auto& [x, _] : points) x = -x;
            }
            for (auto& [_, y] : points) y = -y;
        }

        return res;
    }
} // namespace suisen


#endif // SUISEN_MANHATTAN_MINIMUM_DISTANCES
