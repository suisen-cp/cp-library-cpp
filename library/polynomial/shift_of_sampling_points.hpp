#ifndef SUISEN_SHIFT_OF_SAMPLING_POINTS
#define SUISEN_SHIFT_OF_SAMPLING_POINTS

#include <vector>
#include <atcoder/convolution>

#include "library/math/factorial.hpp"

namespace suisen {
    template <typename mint, typename Convolve,
        std::enable_if_t<std::is_invocable_r_v<std::vector<mint>, Convolve, std::vector<mint>, std::vector<mint>>, std::nullptr_t> = nullptr>
    std::vector<mint> shift_of_sampling_points(const std::vector<mint>& ys, mint t, int m, const Convolve &convolve) {
        const int n = ys.size();
        factorial<mint> fac(std::max(n, m));

        std::vector<mint> b = [&] {
            std::vector<mint> f(n), g(n);
            for (int i = 0; i < n; ++i) {
                f[i] = ys[i] * fac.fac_inv(i);
                g[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);
            }
            std::vector<mint> b = convolve(f, g);
            b.resize(n);
            return b;
        }();
        std::vector<mint> e = [&] {
            std::vector<mint> c(n);
            mint prd = 1;
            std::reverse(b.begin(), b.end());
            for (int i = 0; i < n; ++i) {
                b[i] *= fac.fac(n - i - 1);
                c[i] = prd * fac.fac_inv(i);
                prd *= t - i;
            }
            std::vector<mint> e = convolve(b, c);
            e.resize(n);
            return e;
        }();
        std::reverse(e.begin(), e.end());
        for (int i = 0; i < n; ++i) {
            e[i] *= fac.fac_inv(i);
        }

        std::vector<mint> f(m);
        for (int i = 0; i < m; ++i) f[i] = fac.fac_inv(i);
        std::vector<mint> res = convolve(e, f);
        res.resize(m);
        for (int i = 0; i < m; ++i) res[i] *= fac.fac(i);
        return res;
    }

    template <typename mint>
    std::vector<mint> shift_of_sampling_points(const std::vector<mint>& ys, mint t, int m) {
        auto convolve = [&](const std::vector<mint> &f, const std::vector<mint> &g) { return atcoder::convolution(f, g); };
        return shift_of_sampling_points(ys, t, m, convolve);
    }
} // namespace suisen


#endif // SUISEN_SHIFT_OF_SAMPLING_POINTS
