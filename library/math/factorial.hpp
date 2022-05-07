#ifndef SUISEN_FACTORIAL
#define SUISEN_FACTORIAL

#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, typename U = T>
    struct factorial {
        factorial() {}
        factorial(int n) { ensure(n); }

        static void ensure(const int n) {
            int sz = _fac.size();
            if (n + 1 <= sz) return;
            int new_size = std::max(n + 1, sz * 2);
            _fac.resize(new_size), _fac_inv.resize(new_size);
            for (int i = sz; i < new_size; ++i) _fac[i] = _fac[i - 1] * i;
            _fac_inv[new_size - 1] = U(1) / _fac[new_size - 1];
            for (int i = new_size - 1; i > sz; --i) _fac_inv[i - 1] = _fac_inv[i] * i;
        }

        const T& fac(const int i) {
            ensure(i);
            return _fac[i];
        }
        const T& operator()(int i) {
            return fac(i);
        }
        const U& fac_inv(const int i) {
            ensure(i);
            return _fac_inv[i];
        }
        U binom(const int n, const int r) {
            if (n < 0 or r < 0 or n < r) return 0;
            ensure(n);
            return _fac[n] * _fac_inv[r] * _fac_inv[n - r];
        }
        U perm(const int n, const int r) {
            if (n < 0 or r < 0 or n < r) return 0;
            ensure(n);
            return _fac[n] * _fac_inv[n - r];
        }
    private:
        static std::vector<T> _fac;
        static std::vector<U> _fac_inv;
    };
    template <typename T, typename U>
    std::vector<T> factorial<T, U>::_fac{ 1 };
    template <typename T, typename U>
    std::vector<U> factorial<T, U>::_fac_inv{ 1 };
} // namespace suisen

#endif // SUISEN_FACTORIAL
