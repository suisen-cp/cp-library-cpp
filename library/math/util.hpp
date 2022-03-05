#ifndef SUISEN_MATH_UTIL
#define SUISEN_MATH_UTIL

#include "library/math/factorial.hpp"

namespace suisen {
    template <typename mint>
    mint random_walk_1d(int n, int x) {
        if (x < 0) x = -x;
        factorial<mint> fac(n);
        int m = n + x;
        return m & 1 ? 0 : fac.binom(n, m / 2);
    }
    template <typename mint>
    mint random_walk_2d(int n, int x, int y) {
        return random_walk_1d<mint>(n, x + y) * random_walk_1d<mint>(n, x - y);
    }

    template <typename mint, typename BinomialCoefficient>
    mint random_walk_1d(int n, int x, const BinomialCoefficient &binom_n) {
        if (x < 0) x = -x;
        int m = n + x;
        return m & 1 ? 0 : binom_n(m / 2);
    }
    template <typename mint, typename BinomialCoefficient>
    mint random_walk_2d(int n, int x, int y, const BinomialCoefficient &binom_n) {
        return random_walk_1d<mint>(n, x + y, binom_n) * random_walk_1d<mint>(n, x - y, binom_n);
    }
} // namespace suisen


#endif // SUISEN_MATH_UTIL
