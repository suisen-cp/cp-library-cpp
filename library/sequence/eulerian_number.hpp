#ifndef SUISEN_EULERIAN_NUMBER
#define SUISEN_EULERIAN_NUMBER

#include "library/polynomial/fps.hpp"
#include "library/math/factorial.hpp"
#include "library/sequence/powers.hpp"

// reference: https://en.wikipedia.org/wiki/Eulerian_number
namespace suisen {
    template <typename mint>
    std::vector<mint> eulerian_number(uint32_t n) {
        if (n == 0) return {};
        factorial<mint> fac(n + 1);
        const uint32_t h = (n + 1) >> 1;
        FPS<mint> f = powers<mint>(h, n);
        f.erase(f.begin());
        FPS<mint> g(h);
        for (uint32_t i = 0; i < h; ++i) {
            mint v = fac.fac_inv(i) * fac.fac_inv(n + 1 - i);
            g[i] = i & 1 ? -v : v;
        }
        FPS<mint> res = f * g;
        for (uint32_t i = h; i < n; ++i) res[i] = res[n - 1 - i];
        res.resize(n);
        return res;
    }
    template <typename mint>
    std::vector<std::vector<mint>> eulerian_number_table(uint32_t n) {
        if (n == 0) return {};
        std::vector dp(n + 1, std::vector<mint>{});
        for (uint32_t i = 1; i <= n; ++i) {
            dp[i].resize(i);
            dp[i][0] = dp[i][i - 1] = 1;
            for (uint32_t j = 1; j < i - 1; ++j) dp[i][j] = (i - j) * dp[i - 1][j - 1] + (j + 1) * dp[i - 1][j];
        }
        return dp;
    }
} // namespace suisen


#endif // SUISEN_EULERIAN_NUMBER
