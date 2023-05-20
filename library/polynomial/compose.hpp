#ifndef SUISEN_POLY_COMPOSE
#define SUISEN_POLY_COMPOSE

#include <cmath>
#include <atcoder/convolution>

#include "library/linear_algebra/matrix.hpp"

namespace suisen {
    template <typename mint>
    std::vector<mint> compose(const std::vector<mint>& f, std::vector<mint> g, const int n) {
        if (f.empty()) return {};
        if (g.empty()) return { f[0] };

        const int sqn = ::sqrt(f.size()) + 1;

        const int z = [n]{
            int z = 1;
            while (z < 2 * n - 1) z <<= 1;
            return z;
        }();
        const mint iz = mint(z).inv();

        g.resize(n), g.resize(z);
        atcoder::internal::butterfly(g);

        auto mult_g = [&](std::vector<mint> a) {
            a.resize(z);
            atcoder::internal::butterfly(a);
            for (int j = 0; j < z; ++j) a[j] *= g[j] * iz;
            atcoder::internal::butterfly_inv(a);
            a.resize(n);
            return a;
        };

        Matrix<mint> pow_g(sqn, n);
        pow_g[0][0] = 1;
        for (int i = 1; i < sqn; ++i) {
            pow_g[i] = mult_g(pow_g[i - 1]);
        }

        std::vector<mint> gl = mult_g(pow_g[sqn - 1]);
        gl.resize(z);
        atcoder::internal::butterfly(gl);

        std::vector<mint> pow_gl(z);
        pow_gl[0] = 1;

        Matrix<mint> F(sqn, sqn);
        for (int i = 0; i < sqn; ++i) for (int j = 0; j < sqn; ++j) {
            if (int ij = i * sqn + j; ij < int(f.size())) {
                F[i][j] = f[ij];
            }
        }
        Matrix<mint> H = F * pow_g;

        std::vector<mint> h(n);
        for (int i = 0; i < sqn; ++i) {
            auto &hi = H[i];
            hi.resize(z);
            atcoder::internal::butterfly(pow_gl);
            atcoder::internal::butterfly(hi);
            for (int k = 0; k < z; ++k) {
                hi[k] *= pow_gl[k] * iz;
                pow_gl[k] *= gl[k] * iz;
            }
            atcoder::internal::butterfly_inv(pow_gl);
            atcoder::internal::butterfly_inv(hi);
            for (int k = 0; k < n; ++k) {
                h[k] += hi[k];
            }
            for (int k = n; k < z; ++k) {
                pow_gl[k] = 0;
            }
            hi.clear(), hi.shrink_to_fit();
        }
        return h;
    }

} // namespace suisen


#endif // SUISEN_POLY_COMPOSE
