#ifndef SUISEN_CONVOLUTION_2_64
#define SUISEN_CONVOLUTION_2_64

#include <atcoder/convolution>
#include <iostream>

#include "library/convolution/convolution_naive.hpp"

namespace suisen {
    namespace internal::convolution_2_64 {
        std::vector<unsigned long long> convolution_6mod(const std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b) {
            int n = int(a.size()), m = int(b.size());

            static constexpr long long MOD1 = 754974721;  // 2^24
            static constexpr long long MOD2 = 167772161;  // 2^25
            static constexpr long long MOD3 = 469762049;  // 2^26
            static constexpr long long MOD4 = 377487361;  // 2^23
            static constexpr long long MOD5 = 595591169;  // 2^23
            static constexpr long long MOD6 = 645922817;  // 2^23

            static constexpr long long M1_MOD2 = MOD1 % MOD2;
            static constexpr long long M1_MOD3 = MOD1 % MOD3;
            static constexpr long long M1_MOD4 = MOD1 % MOD4;
            static constexpr long long M1_MOD5 = MOD1 % MOD5;
            static constexpr long long M1_MOD6 = MOD1 % MOD6;
            static constexpr long long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;
            static constexpr long long M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;
            static constexpr long long M1M2_MOD5 = M1_MOD5 * MOD2 % MOD5;
            static constexpr long long M1M2_MOD6 = M1_MOD6 * MOD2 % MOD6;
            static constexpr long long M1M2M3_MOD4 = M1M2_MOD4 * MOD3 % MOD4;
            static constexpr long long M1M2M3_MOD5 = M1M2_MOD5 * MOD3 % MOD5;
            static constexpr long long M1M2M3_MOD6 = M1M2_MOD6 * MOD3 % MOD6;
            static constexpr long long M1M2M3M4_MOD5 = M1M2M3_MOD5 * MOD4 % MOD5;
            static constexpr long long M1M2M3M4_MOD6 = M1M2M3_MOD6 * MOD4 % MOD6;
            static constexpr long long M1M2M3M4M5_MOD6 = M1M2M3M4_MOD6 * MOD5 % MOD6;

            static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(M1_MOD2, MOD2).second;
            static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3, MOD3).second;
            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4, MOD4).second;
            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5, MOD5).second;
            static constexpr long long INV_M1M2M3M4M5_MOD6 = atcoder::internal::inv_gcd(M1M2M3M4M5_MOD6, MOD6).second;

            static constexpr unsigned long long M1 = MOD1;
            static constexpr unsigned long long M1M2 = M1 * MOD2;
            static constexpr unsigned long long M1M2M3 = M1M2 * MOD3;
            static constexpr unsigned long long M1M2M3M4 = M1M2M3 * MOD4;
            static constexpr unsigned long long M1M2M3M4M5 = M1M2M3M4 * MOD5;

            std::vector<unsigned long long> a2(n), b2(m);
            for (int i = 0; i < n; ++i) a2[i] = a[i];
            for (int i = 0; i < m; ++i) b2[i] = b[i];

            auto c1 = atcoder::convolution<MOD1>(a2, b2);
            auto c2 = atcoder::convolution<MOD2>(a2, b2);
            auto c3 = atcoder::convolution<MOD3>(a2, b2);
            auto c4 = atcoder::convolution<MOD4>(a2, b2);
            auto c5 = atcoder::convolution<MOD5>(a2, b2);
            auto c6 = atcoder::convolution<MOD6>(a2, b2);

            std::vector<unsigned long long> c(n + m - 1);
            for (int i = 0; i < n + m - 1; ++i) {
                // Garner's Algorithm
                long long x1 = c1[i];
                long long x2 = (atcoder::static_modint<MOD2>((long long) c2[i] - x1) * INV_M1_MOD2).val();
                long long x3 = (atcoder::static_modint<MOD3>((long long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();
                long long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4 - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();
                long long x5 = (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5 - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();
                long long x6 = (atcoder::static_modint<MOD6>((long long) c6[i] - x1 - x2 * M1_MOD6 - x3 * M1M2_MOD6 - x4 * M1M2M3_MOD6 - x5 * M1M2M3M4_MOD6) * INV_M1M2M3M4M5_MOD6).val();
                c[i] = x1 + x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4 + x6 * M1M2M3M4M5;
            }
            return c;
        }

        std::vector<unsigned long long> convolution_5mod(const std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b) {
            int n = int(a.size()), m = int(b.size());

            static constexpr long long MOD1 = 998244353;  // 2^23
            static constexpr long long MOD2 = 985661441;  // 2^22
            static constexpr long long MOD3 = 943718401;  // 2^22
            static constexpr long long MOD4 = 935329793;  // 2^22
            static constexpr long long MOD5 = 918552577;  // 2^22

            static constexpr long long M1_MOD2 = MOD1 % MOD2;
            static constexpr long long M1_MOD3 = MOD1 % MOD3;
            static constexpr long long M1_MOD4 = MOD1 % MOD4;
            static constexpr long long M1_MOD5 = MOD1 % MOD5;
            static constexpr long long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;
            static constexpr long long M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;
            static constexpr long long M1M2_MOD5 = M1_MOD5 * MOD2 % MOD5;
            static constexpr long long M1M2M3_MOD4 = M1M2_MOD4 * MOD3 % MOD4;
            static constexpr long long M1M2M3_MOD5 = M1M2_MOD5 * MOD3 % MOD5;
            static constexpr long long M1M2M3M4_MOD5 = M1M2M3_MOD5 * MOD4 % MOD5;

            static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(M1_MOD2, MOD2).second;
            static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3, MOD3).second;
            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4, MOD4).second;
            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5, MOD5).second;

            static constexpr unsigned long long M1 = MOD1;
            static constexpr unsigned long long M1M2 = M1 * MOD2;
            static constexpr unsigned long long M1M2M3 = M1M2 * MOD3;
            static constexpr unsigned long long M1M2M3M4 = M1M2M3 * MOD4;

            std::vector<unsigned long long> a2(n), b2(m);
            for (int i = 0; i < n; ++i) a2[i] = a[i];
            for (int i = 0; i < m; ++i) b2[i] = b[i];

            auto c1 = atcoder::convolution<MOD1>(a2, b2);
            auto c2 = atcoder::convolution<MOD2>(a2, b2);
            auto c3 = atcoder::convolution<MOD3>(a2, b2);
            auto c4 = atcoder::convolution<MOD4>(a2, b2);
            auto c5 = atcoder::convolution<MOD5>(a2, b2);

            std::vector<unsigned long long> c(n + m - 1);
            for (int i = 0; i < n + m - 1; ++i) {
                // Garner's Algorithm
                long long x1 = c1[i];
                long long x2 = (atcoder::static_modint<MOD2>((long long) c2[i] - x1) * INV_M1_MOD2).val();
                long long x3 = (atcoder::static_modint<MOD3>((long long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();
                long long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4 - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();
                long long x5 = (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5 - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();
                c[i] = x1 + x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4;
            }
            return c;
        }
    }
    std::vector<unsigned long long> convolution_mod_2_64(const std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b) {
        int n = int(a.size()), m = int(b.size());
        if (n == 0 or m == 0) return {};
        if (std::min(n, m) <= 60) return internal::convolution_naive(a, b);

        if (n + m - 1 <= 1 << 22) {
            return internal::convolution_2_64::convolution_5mod(a, b);
        } else {
            assert(n + m - 1 <= 1 << 23);
            return internal::convolution_2_64::convolution_6mod(a, b);
        }
    }
} // namespace suisen


#endif // SUISEN_CONVOLUTION_2_64
