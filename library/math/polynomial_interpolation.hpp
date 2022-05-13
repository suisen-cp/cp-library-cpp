#ifndef SUISEN_POLYNOMIAL_INTERPOLATION
#define SUISEN_POLYNOMIAL_INTERPOLATION

#include "library/math/fps.hpp"

namespace suisen {
    template <typename mint>
    FPS<mint> polynomial_interpolation(const std::vector<mint>& xs, const std::vector<mint>& ys) {
        assert(xs.size() == ys.size());
        int n = xs.size();
        std::vector<FPS<mint>> seg(2 * n), g(2 * n);
        for (int i = 0; i < n; ++i) seg[n + i] = FPS<mint>{ -xs[i], 1 };
        for (int i = n - 1; i > 0; --i) {
            seg[i] = seg[i * 2] * seg[i * 2 + 1];
        }
        g[1] = std::move(seg[1].diff_inplace());
        for (int i = 1; i < n; ++i) {
            int l = 2 * i, r = l + 1;
            g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];
        }
        for (int i = 0; i < n; ++i) g[n + i] = FPS<mint>{ ys[i] / g[n + i][0] };
        for (int i = n - 1; i > 0; --i) {
            int l = 2 * i, r = l + 1;
            g[i] = g[l] * seg[r] + g[r] * seg[l];
        }
        return g[1];
    }

} // namespace suisen


#endif // SUISEN_POLYNOMIAL_INTERPOLATION
