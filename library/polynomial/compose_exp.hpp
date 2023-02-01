#ifndef SUISEN_COMPOSE_EXP
#define SUISEN_COMPOSE_EXP

#include "library/math/factorial.hpp"
#include "library/polynomial/formal_power_series.hpp"
#include "library/polynomial/rational_fps.hpp"

namespace suisen {
    // Calculates f(e^x) mod x^n in O(d (log d)^2 + n log n), where d := deg f.
    template <typename FPSType>
    FPSType compose_exp(const FPSType& f, int n) {
        // f(x) = Sum_i A_i x^i
        // f(e^x) := Sum_i B_i x^i, F(x) := Sum_i B_i i! x^i
        // F(x) = Sum_i A_i Sum_j (ix)^j
        //      = Sum_i A_i/(1-ix)
        using mint = typename FPSType::value_type;
        using RFPS = RationalFPS<FPSType>;
        std::vector<RFPS> fs;
        for (int i = 0; i < f.size(); ++i) {
            fs.emplace_back(FPSType{ f[i] }, FPSType{ 1, -i });
        }
        FPSType g = RFPS::sum(fs).to_fps(n);
        factorial<mint> fac(n);
        for (int i = 2; i < n; ++i) {
            g[i] *= fac.fac_inv(i);
        }
        return g;
    }
} // namespace suisen


#endif // SUISEN_COMPOSE_EXP
