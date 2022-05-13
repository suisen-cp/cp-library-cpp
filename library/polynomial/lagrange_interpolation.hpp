#ifndef SUISEN_INTERPOLATION
#define SUISEN_INTERPOLATION

#include "library/math/product_of_differences.hpp"

namespace suisen {
    // O(N^2+NlogP)
    template <typename T>
    T lagrange_interpolation_naive(const std::vector<T>& xs, const std::vector<T>& ys, const T t) {
        const int n = xs.size();
        assert(int(ys.size()) == n);

        T p{ 1 };
        for (int i = 0; i < n; ++i) p *= t - xs[i];

        T res{ 0 };
        for (int i = 0; i < n; ++i) {
            T w = 1;
            for (int j = 0; j < n; ++j) if (j != i) w *= xs[i] - xs[j];
            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));
        }
        return res;
    }

    // O(N(logN)^2+NlogP)
    template <typename mint>
    mint lagrange_interpolation(const std::vector<mint>& xs, const std::vector<mint>& ys, const mint t) {
        const int n = xs.size();
        assert(int(ys.size()) == n);

        std::vector<FPS<mint>> seg(2 * n);
        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint> {-xs[i], 1};
        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i * 2 + 1];
        seg[1] = seg[1].diff() % seg[1];
        for (int i = 2; i < 2 * n; ++i) seg[i] = seg[i / 2] % seg[i];

        mint p{ 1 };
        for (int i = 0; i < n; ++i) p *= t - xs[i];

        mint res{ 0 };
        for (int i = 0; i < n; ++i) {
            mint w = seg[n + i][0];
            res += ys[i] * (t == xs[i] ? 1 : p / (w * (t - xs[i])));
        }
        return res;
    }

    // x = 0, 1, ...
    template <typename T>
    T lagrange_interpolation(const std::vector<T>& ys, const T t) {
        const int n = ys.size();
        T fac = 1;
        for (int i = 1; i < n; ++i) fac *= i;
        std::vector<T> fci(n), suf(n);
        fci[n - 1] = T(1) / fac;
        suf[n - 1] = 1;
        for (int i = n - 1; i > 0; --i) {
            fci[i - 1] = fci[i] * i;
            suf[i - 1] = suf[i] * (t - i);
        }
        T prf = 1, res = 0;
        for (int i = 0; i < n; ++i) {
            T val = ys[i] * prf * suf[i] * fci[i] * fci[n - i - 1];
            if ((n - 1 - i) & 1) res -= val;
            else                 res += val;
            prf *= t - i;
        }
        return res;
    }
} // namespace suisen

#endif // SUISEN_INTERPOLATION

