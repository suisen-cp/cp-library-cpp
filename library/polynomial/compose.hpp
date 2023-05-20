#ifndef SUISEN_POLY_COMPOSE
#define SUISEN_POLY_COMPOSE

#include <cmath>
#include <atcoder/convolution>

namespace suisen {
    template <typename FPSType>
    FPSType compose(const FPSType& f, FPSType g, const int n) {
        if (f.empty()) return {};
        if (g.empty()) return { f[0] };

        if (int(g.size()) > n) {
            g.resize(n);
        }

        const int sqn = ::sqrt(f.size()) + 1;

        std::vector<FPSType> pow_g_small(sqn);
        pow_g_small[0] = { 1 };
        for (int i = 1; i < sqn; ++i) {
            pow_g_small[i] = pow_g_small[i - 1] * g;
            pow_g_small[i].resize(n);
        }
        const FPSType g_large = pow_g_small.back() * g;

        FPSType pow_g_large{ 1 };

        FPSType h(n);
        for (int i = 0; i < sqn; ++i) {
            FPSType hi(n);
            for (int j = 0; j < sqn; ++j) {
                const int ij = i * sqn + j;
                if (ij >= int(f.size())) break;

                const auto c = f[ij];
                const FPSType& gj = pow_g_small[j];

                for (int k = 0; k < int(gj.size()); ++k) {
                    hi[k] += c * gj[k];
                }
            }
            hi = pow_g_large * hi;
            for (int k = 0; k < n; ++k) {
                h[k] += hi[k];
            }
            pow_g_large = pow_g_large * g_large;
            pow_g_large.resize(n);
        }
        return h;
    }

} // namespace suisen


#endif // SUISEN_POLY_COMPOSE
