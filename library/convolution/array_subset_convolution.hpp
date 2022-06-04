#ifndef SUISEN_ARRAY_SUBSET_CONVOLUTION
#define SUISEN_ARRAY_SUBSET_CONVOLUTION

#include "library/polynomial/array_fps_naive.hpp"
#include "library/transform/subset.hpp"

namespace suisen::array_ranked_subset_transform {
    template <typename T, std::size_t N>
    using polynomial_t = ArrayFPSNaive<T, N>;

    namespace internal {
        template <typename T, std::size_t N>
        std::vector<polynomial_t<T, N>> ranked(const std::vector<T>& a) {
            const int n = a.size();
            assert((-n & n) == n);
            std::vector fs(n, polynomial_t<T, N>{});
            for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];
            return fs;
        }
        template <typename T, std::size_t N>
        std::vector<T> deranked(const std::vector<polynomial_t<T, N>>& polys) {
            const int n = polys.size();
            assert((-n & n) == n);
            std::vector<T> a(n);
            for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];
            return a;
        }
    } // namespace suisen::array_ranked_subset_transform::internal

    template <typename T, std::size_t N>
    std::vector<polynomial_t<T, N>> ranked_zeta(const std::vector<T>& a) {
        auto ranked = internal::ranked<T, N>(a);
        subset_transform::zeta(ranked);
        return ranked;
    }
    template <typename T, std::size_t N>
    std::vector<T> deranked_mobius(std::vector<polynomial_t<T, N>>& ranked) {
        subset_transform::mobius(ranked);
        return internal::deranked<T, N>(ranked);
    }
} // namespace suisen::array_ranked_subset_transform

#endif // SUISEN_ARRAY_SUBSET_CONVOLUTION
