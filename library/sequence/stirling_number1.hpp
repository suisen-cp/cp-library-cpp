#ifndef SUISEN_STIRLING_NUMBER_1
#define SUISEN_STIRLING_NUMBER_1

#include "library/math/inv_mods.hpp"
#include "library/math/factorial.hpp"

namespace suisen {
    /**
     * return:
     *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k (unsigned)
     * constraints:
     *   0 <= n <= 10^6
     */
    template <typename FPSType>
    std::vector<typename FPSType::value_type> stirling_number1_reversed(int n) {
        using mint = typename FPSType::value_type;
        factorial<mint> fac(n);
        int l = 0;
        while ((n >> l) != 0) ++l;
        FPSType a{ 1 };
        int m = 0;
        while (l-- > 0) {
            FPSType f(m + 1), g(m + 1);
            mint powm = 1;
            for (int i = 0; i <= m; ++i, powm *= m) {
                f[i] = powm * fac.fac_inv(i);
                g[i] = a[i] * fac.fac(m - i);
            }
            f *= g, f.cut(m + 1);
            for (int i = 0; i <= m; ++i) f[i] *= fac.fac_inv(m - i);
            a *= f, m *= 2, a.cut(m + 1);
            if ((n >> l) & 1) {
                a.push_back(0);
                for (int i = m; i > 0; --i) a[i] += m * a[i - 1];
                ++m;
            }
        }
        return a;
    }
    template <typename FPSType>
    std::vector<typename FPSType::value_type> stirling_number1(int n) {
        std::vector<typename FPSType::value_type> a(stirling_number1_reversed<FPSType>(n));
        std::reverse(a.begin(), a.end());
        return a;
    }
    /**
     * return:
     *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling number of the first kind (unsigned).
     * constraints:
     * - 0 <= n <= 10^18
     * - 0 <= k <= 5000
     * - k < mod
     */
    template <typename mint>
    std::vector<mint> stirling_number1_reversed(const long long n, const int k) {
        inv_mods<mint> invs(k + 1);
        std::vector<mint> a(k + 1, 0);
        a[0] = 1;
        int l = 0;
        while (n >> l) ++l;
        mint m = 0;
        while (l-- > 0) {
            std::vector<mint> b(k + 1, 0);
            for (int j = 0; j <= k; ++j) {
                mint tmp = 1;
                for (int i = j; i <= k; ++i) {
                    b[i] += a[j] * tmp;
                    tmp *= (m - i) * invs[i - j + 1] * m;
                }
            }
            for (int i = k + 1; i-- > 0;) {
                mint sum = 0;
                for (int j = 0; j <= i; ++j) sum += a[j] * b[i - j];
                a[i] = sum;
            }
            m *= 2;
            if ((n >> l) & 1) {
                for (int i = k; i > 0; --i) a[i] += m * a[i - 1];
                ++m;
            }
        }
        return a;
    }
    template <typename mint>
    std::vector<std::vector<mint>> stirling_number1_table(uint32_t n) {
        std::vector dp(n + 1, std::vector<mint>{});
        for (uint32_t i = 0; i <= n; ++i) {
            dp[i].resize(i + 1);
            dp[i][0] = 0, dp[i][i] = 1;
            for (uint32_t j = 1; j < i; ++j) dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j];
        }
        return dp;
    }
} // namespace suisen

#endif // SUISEN_STIRLING_NUMBER_1
