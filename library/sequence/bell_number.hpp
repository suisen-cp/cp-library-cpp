#ifndef SUISEN_BELL_NUMBER
#define SUISEN_BELL_NUMBER

#include "library/math/factorial.hpp"

namespace suisen {
    /**
     * return:
     *   vector<mint> v s.t. v[i] = B_i = Σ_j S2[i,j] for i=0,...,n
     * constraints:
     *   0 <= n <= 10^6
     * note:
     *   EGF of B is e^(e^x-1)
     */
    template <typename FPSType>
    std::vector<typename FPSType::value_type> bell_number(int n) {
        using mint = typename FPSType::value_type;
        factorial<mint> fac(n);
        FPSType f(n + 1);
        for (int i = 1; i <= n; ++i) f[i] = fac.fac_inv(i);
        f.exp_inplace(n);
        for (int i = 0; i <= n; ++i) f[i] *= fac.fac(i);
        return f;
    }
} // namespace suisen

#endif // SUISEN_BELL_NUMBER
