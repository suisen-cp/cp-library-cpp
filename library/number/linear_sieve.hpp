#ifndef SUISEN_LINEAR_SIEVE
#define SUISEN_LINEAR_SIEVE

#include <cassert>
#include <numeric>
#include <vector>

namespace suisen {
// referece: https://37zigen.com/linear-sieve/
class LinearSieve {
    public:
        LinearSieve(const int n) : _n(n), min_prime_factor(std::vector<int>(n + 1)) {
            std::iota(min_prime_factor.begin(), min_prime_factor.end(), 0);
            prime_list.reserve(_n / 20);
            for (int d = 2; d <= _n; ++d) {
                if (min_prime_factor[d] == d) prime_list.push_back(d);
                const int prime_max = std::min(min_prime_factor[d], _n / d);
                for (int prime : prime_list) {
                    if (prime > prime_max) break;
                    min_prime_factor[prime * d] = prime;
                }
            }
        }
        int prime_num() const noexcept { return prime_list.size(); }
        /**
         * Returns a vector of primes in [0, n].
         * It is guaranteed that the returned vector is sorted in ascending order.
         */
        const std::vector<int>& get_prime_list() const noexcept  {
            return prime_list;
        }
        const std::vector<int>& get_min_prime_factor() const noexcept { return min_prime_factor; }
        /**
         * Returns a vector of `{ prime, index }`.
         * It is guaranteed that the returned vector is sorted in ascending order.
         */
        std::vector<std::pair<int, int>> factorize(int n) const noexcept {
            assert(0 < n and n <= _n);
            std::vector<std::pair<int, int>> prime_powers;
            while (n > 1) {
                int p = min_prime_factor[n], c = 0;
                do { n /= p, ++c; } while (n % p == 0);
                prime_powers.emplace_back(p, c);
            }
            return prime_powers;
        }
    private:
        const int _n;
        std::vector<int> min_prime_factor;
        std::vector<int> prime_list;
};
} // namespace suisen

#endif // SUISEN_LINEAR_SIEVE