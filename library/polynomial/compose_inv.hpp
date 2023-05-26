#ifndef SUISEN_COMPOSE_INV
#define SUISEN_COMPOSE_INV

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/formal_power_series.hpp"

namespace suisen {
    // @return g mod x^n s.t. f(g(x))=g(f(x))=x (mod x^n)
    template <typename mint>
    std::vector<mint> compositional_inv(std::vector<mint> f, const int n) {
        using fps = FormalPowerSeries<mint>;

        assert(f[0] == 0);
        assert(f[1] != 0);

        if (n == 0) return {};
        if (n == 1) return { 0 };

        f.erase(f.begin());
        f.resize(n);

        const int B = ::sqrt(n) + 1;

        const int z = [n]{
            int z = 1;
            while (z < 2 * n - 1) z <<= 1;
            return z;
        }();
        const mint iz = mint(z).inv();
        
        f.resize(z);
        atcoder::internal::butterfly(f);
        auto mul_f = [&](std::vector<mint> a) {
            a.resize(z);
            atcoder::internal::butterfly(a);
            for (int j = 0; j < z; ++j) a[j] *= f[j] * iz;
            atcoder::internal::butterfly_inv(a);
            a.resize(n);
            return a;
        };

        std::vector<fps> h(B + 1, fps(n));
        h[0][0] = 1;
        for (int i = 1; i <= B; ++i) {
            h[i] = mul_f(h[i - 1]);
        }

        std::vector<mint>& hB = h[B];
        hB.resize(z);
        atcoder::internal::butterfly(hB);
        auto mul_hB = [&](std::vector<mint> a) {
            a.resize(z);
            atcoder::internal::butterfly(a);
            for (int j = 0; j < z; ++j) a[j] *= hB[j] * iz;
            atcoder::internal::butterfly_inv(a);
            a.resize(n);
            return a;
        };

        fps H(n);
        H[0] = 1;

        fps g(B * B);

        fps I(B * B);
        I[1] = 1;
        for (int q = 0; q < B; ++q) {
            // loop invariant
            // - H = H_q, I = I_q
            // - g[0,qB) is calculated

            // I_q / x^{qB}
            fps J = fps(I.begin() + q * B, I.begin() + (q * B + B)) * H.cut_copy(B).inv(B);
            J.resize(B);

            for (int r = 0; r < B; ++r) {
                for (int i = 0; i < r; ++i) {
                    J[r] -= J[i] * h[i][r - i];
                }
                J[r] /= h[r][0];
            }
            std::move(J.begin(), J.end(), g.begin() + (B * q));

            if (q == B - 1) break;

            // update I_q
            const int siz_q = n - q * B;
            J.assign(siz_q, 0);
            for (int r = 0; r < B; ++r) {
                const mint gr = g[q * B + r];
                for (int k = 0; k < siz_q - r; ++k) {
                    J[r + k] += gr * h[r][k];
                }
            }
            J *= H.cut_copy(siz_q);
            for (int k = 0; k < siz_q; ++k) {
                I[q * B + k] -= J[k];
            }

            // update H_q
            H = mul_hB(H);
        }
        g.resize(n);
        return g;
    }
} // namespace suisen


#endif // SUISEN_COMPOSE_INV
