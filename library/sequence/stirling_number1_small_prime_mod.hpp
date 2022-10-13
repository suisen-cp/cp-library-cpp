#ifndef SUISEN_STIRLING_NUMBER1_SMALL_P
#define SUISEN_STIRLING_NUMBER1_SMALL_P

#include "library/sequence/stirling_number1.hpp"
#include "library/sequence/binomial_coefficient_small_prime_mod.hpp"

namespace suisen {
    template <typename mint>
    struct StirlingNumber1SmallPrimeMod {
        mint operator()(long long n, long long k) const {
            return s1(n, k);
        }
        static mint s1(long long n, long long k) {
            static const std::vector<std::vector<mint>> table = stirling_number1_table<mint>(mint::mod() - 1);
            static const BinomialCoefficientSmallPrimeMod<mint> binom{};
            static const int p = mint::mod();
            if (k < 0 or n < k) return 0;
            long long a = n / p, b = n % p;
            if (k < a) return 0;
            long long c = (k - a) / (p - 1), d = (k - a) % (p - 1);
            return ((a - c) & 1 ? -1 : 1) * (b == p - 1 and d == 0 ? -binom(a, c - 1) : d <= b ? table[b][d] * binom(a, c): 0);
        }
    };
} // namespace suisen


#endif // SUISEN_STIRLING_NUMBER1_SMALL_P
