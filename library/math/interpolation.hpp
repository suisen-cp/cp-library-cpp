#ifndef SUISEN_INTERPOLATION
#define SUISEN_INTERPOLATION

#include <vector>
#include "library/math/fps.hpp"

namespace suisen {
template <typename T>
T lagrange_interpolation(const std::vector<T> &ys, const T t) {
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
        if ((n - 1 - i) & 1) {
            res -= val;
        } else {
            res += val;
        }
        prf *= t - i;
    }
    return res;
}

template <typename mint>
FPS<mint> polynomial_interpolation(const std::vector<mint> &xs, const std::vector<mint> &ys) {
    assert(xs.size() == ys.size());
    int n = xs.size();
    int k = 1;
    while (k < n) k <<= 1;
    std::vector<FPS<mint>> seg(k << 1), g(k << 1);
    for (int i = 0; i < n; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};
    for (int i = n; i < k; ++i) seg[k + i] = FPS<mint> {1};
    for (int i = k - 1; i > 0; --i) {
        seg[i] = seg[i * 2] * seg[i * 2 + 1];
    }
    g[1] = std::move(seg[1].diff_inplace());
    for (int i = 1; i < k; ++i) {
        int l = 2 * i, r = l + 1;
        g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];
    }
    for (int i = 0; i < n; ++i) g[k + i] = FPS<mint> {ys[i] / g[k + i][0]};
    for (int i = n; i < k; ++i) g[k + i] = FPS<mint> {0};
    for (int i = k - 1; i > 0; --i) {
        int l = 2 * i, r = l + 1;
        g[i] = g[l] * seg[r] + g[r] * seg[l];
    }
    return g[1];
}
} // namespace suisen

#endif // SUISEN_INTERPOLATION

