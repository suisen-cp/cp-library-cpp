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
        int saturation_pow(int a, int b, int max_value = std::numeric_limits<int>::max()) {
            long long res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) res = std::min(res * pow_a, (long long) max_value);
                pow_a = std::min(pow_a * pow_a, (long long) max_value);
            }
            return res;
        }
        int pow_int(int a, int b) {
            int res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) res *= pow_a;
                pow_a *= pow_a;
            }
            return res;
        }
        int pow_mod(int a, int b, int m) {
            long long res = 1, pow_a = a;
            for (; b; b >>= 1) {
                if (b & 1) res = (res * pow_a) % m;
                pow_a = (pow_a * pow_a) % m;
            }
            return res;
        }

        int tetration_mod_naive(int a, int b, int m) {
            int res = 1;
            for (int i = 0; i < b; ++i) res = pow_int(a, res);
            return res % m;
        }

        int tetration_mod_impl(int a, int b, int m, int x) {
            if (m == 1) return x;
            if (b == 0) return 1;
            int nx = 0, m2 = m;
            while (true) {
                int g = std::gcd(m2, a);
                if (g == 1) break;
                m2 /= g, ++nx;
            }
            int phi_m2 = m2;
            for (auto [p, q] : fast_factorize::factorize(m2)) {
                phi_m2 /= p, phi_m2 *= p - 1;
            }
            int res = saturation_pow(a, b - 1) >= nx ? pow_mod(a, tetration_mod_impl(a, b - 1, phi_m2, nx), m) : tetration_mod_naive(a, b, m);
            return res >= x ? res : res + m * ((x - res + m - 1) / m);
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
        return internal::tetration_mod::tetration_mod_impl(a, b, m, 0);
    }
}

#endif // SUISEN_TETRATION_MOD
