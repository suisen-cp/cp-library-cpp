#ifndef SUISEN_BERNOULLI_NUMBER
#define SUISEN_BERNOULLI_NUMBER

#include "library/math/factorial.hpp"

namespace suisen {
    template <typename FPSType>
    std::vector<typename FPSType::value_type> bernoulli_number(int n) {
        using mint = typename FPSType::value_type;
        factorial<mint> fac(n);
        FPSType a(n + 1);
        for (int i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);
        a.inv_inplace(n + 1), a.resize(n + 1);
        for (int i = 2; i <= n; ++i) a[i] *= fac(i);
        return a;
    }
} // namespace suisen

#endif // SUISEN_BERNOULLI_NUMBER
