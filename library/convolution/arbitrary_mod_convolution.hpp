#ifndef SUISEN_ARBITRARY_MOD_CONVOLUTION
#define SUISEN_ARBITRARY_MOD_CONVOLUTION

#include <atcoder/convolution>
#include <iostream>

namespace suisen {
    template <typename mint, atcoder::internal::is_modint_t<mint>* = nullptr>
    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>& a, const std::vector<mint>& b) {
        int n = int(a.size()), m = int(b.size());
        if (n == 0 or m == 0) return {};

        static constexpr long long MOD1 = 754974721;  // 2^24
        static constexpr long long MOD2 = 167772161;  // 2^25
        static constexpr long long MOD3 = 469762049;  // 2^26
        static constexpr long long M1M2 = MOD1 * MOD2;
        static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;
        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2, MOD3).second;

        std::vector<int> a2(n), b2(m);
        for (int i = 0; i < n; ++i) a2[i] = a[i].val();
        for (int i = 0; i < m; ++i) b2[i] = b[i].val();

        auto c1 = atcoder::convolution<MOD1>(a2, b2);
        auto c2 = atcoder::convolution<MOD2>(a2, b2);
        auto c3 = atcoder::convolution<MOD3>(a2, b2);

        const long long m1m2 = mint(M1M2).val();
        std::vector<mint> c(n + m - 1);
        for (int i = 0; i < n + m - 1; ++i) {
            // Garner's Algorithm
            // X = x1 + x2 * m1 + x3 * m1 * m2
            // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 * m1) / m2 (mod m3)
            long long x1 = c1[i];
            long long x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();
            long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) * INV_M1M2_MOD3).val();
            c[i] = x1 + x2 * MOD1 + x3 * m1m2;
        }
        return c;
    }
} // namespace suisen


#endif // SUISEN_ARBITRARY_MOD_CONVOLUTION
