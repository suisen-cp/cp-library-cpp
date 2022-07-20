#ifndef SUISEN_POLYNOMIAL_TAYLOR_SHIFT
#define SUISEN_POLYNOMIAL_TAYLOR_SHIFT

#include <algorithm>

#include "library/math/factorial.hpp"

namespace suisen {
    // return f(x + c) 
    template <typename FPSType, typename T>
    FPSType translate(const FPSType& f, const T c) {
        int d = f.deg();
        if (d < 0) return FPSType{ 0 };
        using mint = typename FPSType::value_type;
        factorial<mint> fac(d);
        FPSType expc(d + 1), g(d + 1);
        mint p = 1;
        for (int i = 0; i <= d; ++i, p *= c) {
            expc[i] = p * fac.fac_inv(i);
            g[d - i] = f[i] * fac(i);
        }
        g *= expc, g.resize(d + 1);
        for (int i = 0; i <= d; ++i) g[i] *= fac.fac_inv(d - i);
        std::reverse(g.begin(), g.end());
        return g;
    }
} // namespace suisen

#endif // SUISEN_POLYNOMIAL_TAYLOR_SHIFT
