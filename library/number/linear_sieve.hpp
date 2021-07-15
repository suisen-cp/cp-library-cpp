#include <numeric>
#include <vector>

namespace suisen {
// referece: https://37zigen.com/linear-sieve/
class LinearSieve {
    public:
        LinearSieve(const unsigned int n) : _n(n), min_prime_factor(std::vector<unsigned int>(n + 1)) {
            std::iota(min_prime_factor.begin(), min_prime_factor.end(), 0);
            prime_list.reserve(_n / 3);
            for (unsigned int d = 2; d <= _n; ++d) {
                if (min_prime_factor[d] == d) prime_list.push_back(d);
                const unsigned int prime_max = std::min(min_prime_factor[d], _n / d);
                for (unsigned int prime : prime_list) {
                    if (prime > prime_max) break;
                    min_prime_factor[prime * d] = prime;
                }
            }
        }
        unsigned int prime_num() const { return prime_list.size(); }
        const std::vector<unsigned int>& get_prime_list() const { return prime_list; }
        const std::vector<unsigned int>& get_min_prime_factor() const { return min_prime_factor; }
    private:
        const unsigned int _n;
        std::vector<unsigned int> min_prime_factor;
        std::vector<unsigned int> prime_list;
};
} // namespace suisen