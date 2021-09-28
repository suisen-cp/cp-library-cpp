#ifndef SUISEN_SUBSET_CONVOLUTION
#define SUISEN_SUBSET_CONVOLUTION

#include <vector>

namespace suisen {
    namespace internal::subset_convolution {
        template <typename T>
        std::vector<T>& addeq(std::vector<T> &a, const std::vector<T> &b) {
            const int n = a.size();
            for (int i = 0; i < n; ++i) a[i] += b[i];
            return a;
        }
        template <typename T>
        std::vector<T>& subeq(std::vector<T> &a, const std::vector<T> &b) {
            const int n = a.size();
            for (int i = 0; i < n; ++i) a[i] -= b[i];
            return a;
        }
        template <typename T>
        std::vector<T>& muleq(std::vector<T> &a, const std::vector<T> &b) {
            const int n = a.size();
            for (int i = n - 1; i >= 0; --i) {
                for (int j = n - 1 - i; j > 0; --j) a[i + j] += a[i] * b[j];
                a[i] *= b[0];
            }
            return a;
        }
        template <typename T>
        std::vector<T> add(const std::vector<T> &a, const std::vector<T> &b) {
            std::vector<T> c = a;
            return addeq(c, b);
        }
        template <typename T>
        std::vector<T> sub(const std::vector<T> &a, const std::vector<T> &b) {
            std::vector<T> c = a;
            return subeq(c, b);
        }
        template <typename T>
        std::vector<T> mul(const std::vector<T> &a, const std::vector<T> &b) {
            std::vector<T> c = a;
            return muleq(c, b);
        }

        template <typename T>
        std::vector<std::vector<T>> ranked(const std::vector<T> &a) {
            const int n = a.size();
            assert((-n & n) == n);
            std::vector fs(n, std::vector(__builtin_ctz(n) + 1, T(0)));
            for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];
            return fs;
        }
        template <typename T>
        std::vector<T> deranked(const std::vector<std::vector<T>> &polys) {
            const int n = polys.size();
            assert((-n & n) == n);
            std::vector<T> a(n);
            for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];
            return a;
        }

        template <typename T>
        std::vector<std::vector<T>> ranked_zeta(const std::vector<T> &a) {
            std::vector<std::vector<T>> ranked_a = ranked<T>(a);
            const int n = ranked_a.size();
            for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {
                addeq(ranked_a[i + k], ranked_a[i]);
            }
            return ranked_a;
        }
        template <typename T>
        std::vector<T> deranked_mobius(std::vector<std::vector<T>> &ranked_a) {
            const int n = ranked_a.size();
            for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i) {
                subeq(ranked_a[i + k], ranked_a[i]);
            }
            return deranked<T>(ranked_a);
        }
    } // internal::subset_convolution

    template <typename T>
    std::vector<T> subset_convolution(const std::vector<T> &a, const std::vector<T> &b) {
        using namespace internal::subset_convolution;
        const int n = a.size();
        auto ranked_a = ranked_zeta(a), ranked_b = ranked_zeta(b);
        for (int i = 0; i < n; ++i) muleq(ranked_a[i], ranked_b[i]);
        return deranked_mobius(ranked_a);
    }
} // namespace suisen

#endif // SUISEN_SUBSET_CONVOLUTION
