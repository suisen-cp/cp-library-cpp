#ifndef SUISEN_TETRATION_MOD
#define SUISEN_TETRATION_MOD

#include <numeric>
#include <optional>

#include "library/number/fast_factorize.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"

/**
 * @brief $a \uparrow \uparrow b \pmod{m}$
*/

namespace suisen {
    namespace internal::tetration_mod {
        constexpr int max_value = std::numeric_limits<int>::max();
        int saturation_pow(int a, int b) {
            if (b >= 32) return max_value;
            long long res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) res = std::min(res * pow_a, (long long) max_value);
                pow_a = std::min(pow_a * pow_a, (long long) max_value);
            }
            return res;
        }
        int saturation_tetration(int a, int b) {
            assert(a >= 2);
            if (b == 0) return 1;
            int exponent = 1;
            for (int i = 0; i < b and exponent != max_value; ++i) exponent = saturation_pow(a, exponent);
            return exponent;
        }
        int pow_mod(int a, int b, int m) {
            long long res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) res = (res * pow_a) % m;
                pow_a = (pow_a * pow_a) % m;
            }
            return res;
        }
    }

    /**
     * @brief Calculates a↑↑b mod m (= a^(a^(a^...(b times)...)) mod m)
     * @param a base
     * @param b number of power operations
     * @param m mod
     * @return a↑↑b mod m
     */
    int tetration_mod(int a, int b, int m) {
        using namespace internal::tetration_mod;
        if (m == 1) return 0;
        if (a == 0) return 1 ^ (b & 1);
        if (a == 1 or b == 0) return 1;
        int i0 = 0, m0 = m;
        for (int g = std::gcd(m0, a); g != 1; g = std::gcd(m0, g)) {
            m0 /= g, ++i0;
        }
        int phi = m0;
        for (auto [p, q] : fast_factorize::factorize(m0)) {
            phi /= p, phi *= p - 1;
        }
        int exponent = saturation_tetration(a, b - 1);
        if (exponent == max_value) {
            exponent = tetration_mod(a, b - 1, phi);
            if (i0 > exponent) {
                exponent += (((i0 - exponent) + phi - 1) / phi) * phi;
            }
        } else if (i0 <= exponent) {
            exponent -= ((exponent - i0) / phi) * phi;
        }
        return pow_mod(a, exponent, m);
    }
}

#endif // SUISEN_TETRATION_MOD
