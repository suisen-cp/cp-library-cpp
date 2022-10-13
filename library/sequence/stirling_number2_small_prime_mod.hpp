#ifndef SUISEN_STIRLING_NUMBER2_SMALL_P
#define SUISEN_STIRLING_NUMBER2_SMALL_P

#include "library/sequence/stirling_number2.hpp"
#include "library/sequence/binomial_coefficient_small_prime_mod.hpp"

namespace suisen {
    template <typename mint>
    struct StirlingNumber2SmallPrimeMod {
        mint operator()(long long n, long long k) const {
            return s2(n, k);
        }
        static mint s2(long long n, long long k) {
            static const std::vector<std::vector<mint>> table = stirling_number2_table<mint>(mint::mod() - 1);
            static const BinomialCoefficientSmallPrimeMod<mint> binom{};
            static const int p = mint::mod();
            if (k < 0 or n < k) return 0;
            if (n == 0) return 1;
            long long c = k / p, d = k % p;
            long long a = (n - c - 1) / (p - 1), b = (n - c - 1) % (p - 1) + 1;
            if (b != p - 1) return d <= b ? binom(a, c) * table[b][d] : 0;
            else return d ? binom(a, c) * table[p - 1][d] : binom(a, c - 1);
        }
    };
} // namespace suisen


#endif // SUISEN_STIRLING_NUMBER2_SMALL_P
