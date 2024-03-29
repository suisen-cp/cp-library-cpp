#ifndef SUISEN_STIRLING_NUMBER_2
#define SUISEN_STIRLING_NUMBER_2

#include "library/math/factorial.hpp"
#include "library/sequence/powers.hpp"

namespace suisen {
    /**
     * return:
     *   vector<mint> v s.t. v[i] = S2[n,i] for i=0,...,k
     * constraints:
     *   0 <= n <= 10^6
     */
    template <typename FPSType>
    std::vector<typename FPSType::value_type> stirling_number2(int n) {
        using mint = typename FPSType::value_type;
        std::vector<mint> pows = powers<mint>(n, n);
        factorial<mint> fac(n);
        FPSType a(n + 1), b(n + 1);
        for (int i = 0; i <= n; ++i) {
            a[i] = pows[i] * fac.fac_inv(i);
            b[i] = i & 1 ? -fac.fac_inv(i) : fac.fac_inv(i);
        }
        a *= b, a.cut(n + 1);
        return a;
    }
    template <typename mint>
    std::vector<std::vector<mint>> stirling_number2_table(int n) {
        std::vector dp(n + 1, std::vector<mint>{});
        for (int i = 0; i <= n; ++i) {
            dp[i].resize(i + 1);
            dp[i][0] = 0, dp[i][i] = 1;
            for (int j = 1; j < i; ++j) dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];
        }
        return dp;
    }
} // namespace suisen

#endif // SUISEN_STIRLING_NUMBER_2
