#ifndef SUISEN_MOBIUS_FUNCTION
#define SUISEN_MOBIUS_FUNCTION

#include <array>
#include <cassert>
#include <vector>

namespace suisen {

template <unsigned int N>
class MobiusFunction {
    public:
        MobiusFunction() {
            min_prime_factor.fill(0);
            mobius.fill(1);
            for (int p = 2; p <= N; ++p) {
                if (min_prime_factor[p]) continue;
                min_prime_factor[p] = p;
                mobius[p] = -1;
                for (int q = p * 2; q <= N; q += p) {
                    if (not min_prime_factor[q]) min_prime_factor[q] = p;
                    mobius[q] = q % (p * p) ? -mobius[q] : 0;
                }
            }
        }
        // Note: `n` must be in [1, N].
        int operator[](int n) const {
            assert(0 < n and n <= N);
            return mobius[n];
        }
        // Note: `n` must be in [1, N].
        int mobius(int n) const {
            return (*this)[n];
        }
        // Note: `n` must be in [2, N].
        int min_prime_factor(int n) const {
            assert(2 <= n and n <= N);
            return min_prime_factor[n];
        }
        /**
         * Returns a vector of `{ prime, index }`.
         * It is guaranteed that the returned vector is sorted in ascending order.
         */
        std::vector<std::pair<int, int>> factorize(int n) const {
            assert(0 < n and n <= N);
            std::vector<std::pair<int, int>> prime_powers;
            while (n > 1) {
                int p = min_prime_factor[n], c = 0;
                do { n /= p, ++c; } while (n % p == 0);
                prime_powers.emplace_back(p, c);
            }
            return prime_powers;
        }
        bool is_prime(int n) const {
            assert(n <= N);
            return 2 <= n and min_prime_factor[n] == n;
        }
    private:
        std::array<int, N + 1> min_prime_factor;
        std::array<int, N + 1> mobius;
};
} // namespace suisen


#endif // SUISEN_MOBIUS_FUNCTION
