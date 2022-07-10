#ifndef SUISEN_BERNOULLI_NUMBER
#define SUISEN_BERNOULLI_NUMBER

#include "library/polynomial/fps.hpp"
#include "library/math/factorial.hpp"

namespace suisen {
    template <typename mint>
    std::vector<mint> bernoulli_number(int n) {
        factorial<mint> fac(n);
        FPS<mint> a(n + 1);
        for (int i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);
        a.inv_inplace(n), a.resize(n + 1);
        for (int i = 2; i <= n; ++i) a[i] *= fac(i);
        return a;
    }
} // namespace suisen

#endif // SUISEN_BERNOULLI_NUMBER
