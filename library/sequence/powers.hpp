#ifndef SUISEN_POWERS
#define SUISEN_POWERS

#include <cstdint>
#include "library/number/linear_sieve.hpp"

namespace suisen {
    // returns { 0^k, 1^k, ..., n^k }
    template <typename mint>
    std::vector<mint> powers(uint32_t n, uint64_t k) {
        const auto mpf = LinearSieve(n).get_min_prime_factor();
        std::vector<mint> res(n + 1);
        res[0] = k == 0;
        for (uint32_t i = 1; i <= n; ++i) res[i] = i == 1 ? 1 : uint32_t(mpf[i]) == i ? mint(i).pow(k) : res[mpf[i]] * res[i / mpf[i]];
        return res;
    }
} // namespace suisen

#endif // SUISEN_POWERS
