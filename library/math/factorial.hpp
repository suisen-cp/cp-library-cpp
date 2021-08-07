#ifndef SUISEN_FACTORIAL
#define SUISEN_FACTORIAL

#include <cassert>
#include <vector>

namespace suisen {
template <typename T, typename U = T>
class factorial {
    public:
        factorial() {}
        factorial(int n) { ensure(n); }
        const T& fac(const int i) {
            ensure(i);
            return fac_[i];
        }
        const T& operator()(int i) {
            return fac(i);
        }
        const U& inv(const int i) {
            ensure(i);
            return inv_[i];
        }
        U binom(const int n, const int r) {
            if (n < 0 or r < 0 or n < r) return 0;
            ensure(n);
            return fac_[n] * inv_[r] * inv_[n - r];
        }
        U perm(const int n, const int r) {
            if (n < 0 or r < 0 or n < r) return 0;
            ensure(n);
            return fac_[n] * inv_[n - r];
        }
    private:
        static std::vector<T> fac_;
        static std::vector<U> inv_;
        static void ensure(const int n) {
            int sz = fac_.size();
            if (n + 1 <= sz) return;
            int new_size = std::max(n + 1, sz * 2);
            fac_.resize(new_size), inv_.resize(new_size);
            for (int i = sz; i < new_size; ++i) fac_[i] = fac_[i - 1] * i;
            inv_[new_size - 1] = U(1) / fac_[new_size - 1];
            for (int i = new_size - 1; i > sz; --i) inv_[i - 1] = inv_[i] * i;
        }
};
template <typename T, typename U>
std::vector<T> factorial<T, U>::fac_ {1};
template <typename T, typename U>
std::vector<U> factorial<T, U>::inv_ {1};
} // namespace suisen

#endif // SUISEN_FACTORIAL
