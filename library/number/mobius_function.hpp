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
            mpf.fill(0);
            dat.fill(1);
            for (long long p = 2; p <= N; ++p) {
                if (mpf[p]) continue;
                mpf[p] = p;
                dat[p] = -1;
                for (long long q = p * 2; q <= N; q += p) {
                    if (not mpf[q]) mpf[q] = p;
                    dat[q] = q % (p * p) ? -dat[q] : 0;
                }
            }
        }
        // Note: `n` must be in [1, N].
        int operator()(unsigned int n) const {
            assert(0 < n and n <= N);
            return dat[n];
        }
        // Note: `n` must be in [1, N].
        int operator[](unsigned int n) const {
            return (*this)(n);
        }
        // Note: `n` must be in [1, N].
        int mobius(unsigned int n) const {
            return (*this)(n);
        }
        // Note: `n` must be in [2, N].
        int min_prime_factor(unsigned int n) const {
            assert(2 <= n and n <= N);
            return mpf[n];
        }
        /**
         * Returns a vector of `{ prime, index }`.
         * It is guaranteed that the returned vector is sorted in ascending order.
         */
        std::vector<std::pair<int, int>> factorize(unsigned int n) const {
            assert(0 < n and n <= N);
            std::vector<std::pair<int, int>> prime_powers;
            while (n > 1) {
                int p = mpf[n], c = 0;
                do { n /= p, ++c; } while (n % p == 0);
                prime_powers.emplace_back(p, c);
            }
            return prime_powers;
        }
        bool is_prime(unsigned int n) const {
            assert(n <= N);
            return 2 <= n and mpf[n] == n;
        }
    private:
        std::array<int, N + 1> mpf;
        std::array<int, N + 1> dat;
};
} // namespace suisen


#endif // SUISEN_MOBIUS_FUNCTION
