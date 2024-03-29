#ifndef SUISEN_BINOMIAL_COEFFICIENT_SMALL_P
#define SUISEN_BINOMIAL_COEFFICIENT_SMALL_P

#include "library/math/factorial.hpp"

namespace suisen {
    template <typename mint>
    struct BinomialCoefficientSmallPrimeMod {
        mint operator()(long long n, long long r) const {
            return binom(n, r);
        }
        static mint binom(long long n, long long r) {
            factorial<mint> fac(mint::mod() - 1);

            if (r < 0 or n < r) return 0;
            r = std::min(r, n - r);
            // Lucas's theorem
            mint res = 1;
            while (r) {
                int ni = n % mint::mod(), ri = r % mint::mod();
                if (ni < ri) return 0;
                res *= fac.binom(ni, ri);
                n = n / mint::mod(), r = r / mint::mod();
            }
            return res;
        }
    };
} // namespace suisen


#endif // SUISEN_BINOMIAL_COEFFICIENT_SMALL_P
