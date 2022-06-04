#ifndef SUISEN_SUBSET_CONVOLUTION
#define SUISEN_SUBSET_CONVOLUTION

#ifdef USE_ARRAY_FPS
#include "library/polynomial/array_fps_naive.hpp"
#else
#include "library/polynomial/fps_naive.hpp"
#endif

#include "library/transform/subset.hpp"

namespace suisen {
    namespace ranked_subset_transform {
#ifdef USE_ARRAY_FPS
        template <typename T>
        using polynomial_t = ArrayFPSNaive<T, USE_ARRAY_FPS>;
#else
        template <typename T>
        using polynomial_t = FPSNaive<T>;
#endif

        namespace internal {
            template <typename T>
            std::vector<polynomial_t<T>> ranked(const std::vector<T>& a) {
                const int n = a.size();
                assert((-n & n) == n);
#ifdef USE_ARRAY_FPS
                std::vector fs(n, polynomial_t<T>{});
#else
                std::vector fs(n, polynomial_t<T>(__builtin_ctz(n) + 1, T{ 0 }));
#endif
                for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];
                return fs;
            }
            template <typename T>
            std::vector<T> deranked(const std::vector<polynomial_t<T>>& polys) {
                const int n = polys.size();
                assert((-n & n) == n);
                std::vector<T> a(n);
                for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];
                return a;
            }
        } // suisen::ranked_subset_transform::internal

        template <typename T>
        std::vector<polynomial_t<T>> ranked_zeta(const std::vector<T>& a) {
            std::vector<polynomial_t<T>> ranked = internal::ranked<T>(a);
            subset_transform::zeta(ranked);
            return ranked;
        }
        template <typename T>
        std::vector<T> deranked_mobius(std::vector<polynomial_t<T>>& ranked) {
            subset_transform::mobius(ranked);
            return internal::deranked<T>(ranked);
        }
    } // suisen::ranked_subset_transform

    template <typename T>
    std::vector<T> subset_convolution(const std::vector<T>& a, const std::vector<T>& b) {
        const int n = a.size();
        auto ra = ranked_subset_transform::ranked_zeta(a), rb = ranked_subset_transform::ranked_zeta(b);
        for (int i = 0; i < n; ++i) ra[i] = ra[i].mul(rb[i], ra[i].deg());
        return ranked_subset_transform::deranked_mobius(ra);
    }
} // namespace suisen

#endif // SUISEN_SUBSET_CONVOLUTION
