#ifndef SUISEN_SUBSET_CONVOLUTION
#define SUISEN_SUBSET_CONVOLUTION

#include "library/polynomial/fps_naive.hpp"

namespace suisen {
    namespace subset_transform {
        template <typename T>
        using polynomial_t = FPSNaive<T>;

        namespace internal {
            template <typename T>
            std::vector<polynomial_t<T>> ranked(const std::vector<T>& a) {
                const int n = a.size();
                assert((-n & n) == n);
                std::vector fs(n, polynomial_t<T>(__builtin_ctz(n) + 1, T{ 0 }));
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
        } // suisen::subset_transform::internal

        template <typename T>
        std::vector<polynomial_t<T>> ranked_zeta(const std::vector<T>& a) {
            std::vector<polynomial_t<T>> ranked_a = internal::ranked<T>(a);
            const int n = ranked_a.size();
            for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {
                ranked_a[i + k] += ranked_a[i];
            }
            return ranked_a;
        }
        template <typename T>
        std::vector<T> deranked_mobius(std::vector<polynomial_t<T>>& ranked_a) {
            const int n = ranked_a.size();
            for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {
                ranked_a[i + k] -= ranked_a[i];
            }
            return internal::deranked<T>(ranked_a);
        }
    } // suisen::subset_transform

    template <typename T>
    std::vector<T> subset_convolution(const std::vector<T>& a, const std::vector<T>& b) {
        const int n = a.size();
        auto ranked_a = subset_transform::ranked_zeta(a), ranked_b = subset_transform::ranked_zeta(b);
        for (int i = 0; i < n; ++i) ranked_a[i] = ranked_a[i].mul(ranked_b[i], ranked_a[i].deg());
        return subset_transform::deranked_mobius(ranked_a);
    }
} // namespace suisen

#endif // SUISEN_SUBSET_CONVOLUTION
