---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
    title: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
    title: test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution_2_64.hpp\"\n\n\n\n#include\
    \ <atcoder/convolution>\n#include <iostream>\n\n#line 1 \"library/convolution/convolution_naive.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen::internal {\n    template <typename\
    \ T, typename R = T>\n    std::vector<R> convolution_naive(const std::vector<T>&\
    \ a, const std::vector<T>& b) {\n        const int n = a.size(), m = b.size();\n\
    \        std::vector<R> c(n + m - 1);\n        if (n < m) {\n            for (int\
    \ j = 0; j < m; j++) for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n\
    \        } else {\n            for (int i = 0; i < n; i++) for (int j = 0; j <\
    \ m; j++) c[i + j] += R(a[i]) * b[j];\n        }\n        return c;\n    }\n}\
    \ // namespace suisen\n\n\n\n#line 8 \"library/convolution/convolution_2_64.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::convolution_2_64 {\n        std::vector<unsigned\
    \ long long> convolution_6mod(const std::vector<unsigned long long>& a, const\
    \ std::vector<unsigned long long>& b) {\n            int n = int(a.size()), m\
    \ = int(b.size());\n\n            static constexpr long long MOD1 = 754974721;\
    \  // 2^24\n            static constexpr long long MOD2 = 167772161;  // 2^25\n\
    \            static constexpr long long MOD3 = 469762049;  // 2^26\n         \
    \   static constexpr long long MOD4 = 377487361;  // 2^23\n            static\
    \ constexpr long long MOD5 = 595591169;  // 2^23\n            static constexpr\
    \ long long MOD6 = 645922817;  // 2^23\n\n            static constexpr long long\
    \ M1_MOD2 = MOD1 % MOD2;\n            static constexpr long long M1_MOD3 = MOD1\
    \ % MOD3;\n            static constexpr long long M1_MOD4 = MOD1 % MOD4;\n   \
    \         static constexpr long long M1_MOD5 = MOD1 % MOD5;\n            static\
    \ constexpr long long M1_MOD6 = MOD1 % MOD6;\n            static constexpr long\
    \ long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;\n            static constexpr long long\
    \ M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;\n            static constexpr long long M1M2_MOD5\
    \ = M1_MOD5 * MOD2 % MOD5;\n            static constexpr long long M1M2_MOD6 =\
    \ M1_MOD6 * MOD2 % MOD6;\n            static constexpr long long M1M2M3_MOD4 =\
    \ M1M2_MOD4 * MOD3 % MOD4;\n            static constexpr long long M1M2M3_MOD5\
    \ = M1M2_MOD5 * MOD3 % MOD5;\n            static constexpr long long M1M2M3_MOD6\
    \ = M1M2_MOD6 * MOD3 % MOD6;\n            static constexpr long long M1M2M3M4_MOD5\
    \ = M1M2M3_MOD5 * MOD4 % MOD5;\n            static constexpr long long M1M2M3M4_MOD6\
    \ = M1M2M3_MOD6 * MOD4 % MOD6;\n            static constexpr long long M1M2M3M4M5_MOD6\
    \ = M1M2M3M4_MOD6 * MOD5 % MOD6;\n\n            static constexpr long long INV_M1_MOD2\
    \ = atcoder::internal::inv_gcd(M1_MOD2, MOD2).second;\n            static constexpr\
    \ long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3, MOD3).second;\n\
    \            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4,\
    \ MOD4).second;\n            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5,\
    \ MOD5).second;\n            static constexpr long long INV_M1M2M3M4M5_MOD6 =\
    \ atcoder::internal::inv_gcd(M1M2M3M4M5_MOD6, MOD6).second;\n\n            static\
    \ constexpr unsigned long long M1 = MOD1;\n            static constexpr unsigned\
    \ long long M1M2 = M1 * MOD2;\n            static constexpr unsigned long long\
    \ M1M2M3 = M1M2 * MOD3;\n            static constexpr unsigned long long M1M2M3M4\
    \ = M1M2M3 * MOD4;\n            static constexpr unsigned long long M1M2M3M4M5\
    \ = M1M2M3M4 * MOD5;\n\n            std::vector<unsigned long long> a2(n), b2(m);\n\
    \            for (int i = 0; i < n; ++i) a2[i] = a[i];\n            for (int i\
    \ = 0; i < m; ++i) b2[i] = b[i];\n\n            auto c1 = atcoder::convolution<MOD1>(a2,\
    \ b2);\n            auto c2 = atcoder::convolution<MOD2>(a2, b2);\n          \
    \  auto c3 = atcoder::convolution<MOD3>(a2, b2);\n            auto c4 = atcoder::convolution<MOD4>(a2,\
    \ b2);\n            auto c5 = atcoder::convolution<MOD5>(a2, b2);\n          \
    \  auto c6 = atcoder::convolution<MOD6>(a2, b2);\n\n            std::vector<unsigned\
    \ long long> c(n + m - 1);\n            for (int i = 0; i < n + m - 1; ++i) {\n\
    \                // Garner's Algorithm\n                long long x1 = c1[i];\n\
    \                long long x2 = (atcoder::static_modint<MOD2>((long long) c2[i]\
    \ - x1) * INV_M1_MOD2).val();\n                long long x3 = (atcoder::static_modint<MOD3>((long\
    \ long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();\n                long\
    \ long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4\
    \ - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();\n                long long x5 =\
    \ (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5\
    \ - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();\n                long long x6\
    \ = (atcoder::static_modint<MOD6>((long long) c6[i] - x1 - x2 * M1_MOD6 - x3 *\
    \ M1M2_MOD6 - x4 * M1M2M3_MOD6 - x5 * M1M2M3M4_MOD6) * INV_M1M2M3M4M5_MOD6).val();\n\
    \                c[i] = x1 + x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4\
    \ + x6 * M1M2M3M4M5;\n            }\n            return c;\n        }\n\n    \
    \    std::vector<unsigned long long> convolution_5mod(const std::vector<unsigned\
    \ long long>& a, const std::vector<unsigned long long>& b) {\n            int\
    \ n = int(a.size()), m = int(b.size());\n\n            static constexpr long long\
    \ MOD1 = 998244353;  // 2^23\n            static constexpr long long MOD2 = 985661441;\
    \  // 2^22\n            static constexpr long long MOD3 = 943718401;  // 2^22\n\
    \            static constexpr long long MOD4 = 935329793;  // 2^22\n         \
    \   static constexpr long long MOD5 = 918552577;  // 2^22\n\n            static\
    \ constexpr long long M1_MOD2 = MOD1 % MOD2;\n            static constexpr long\
    \ long M1_MOD3 = MOD1 % MOD3;\n            static constexpr long long M1_MOD4\
    \ = MOD1 % MOD4;\n            static constexpr long long M1_MOD5 = MOD1 % MOD5;\n\
    \            static constexpr long long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;\n \
    \           static constexpr long long M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;\n  \
    \          static constexpr long long M1M2_MOD5 = M1_MOD5 * MOD2 % MOD5;\n   \
    \         static constexpr long long M1M2M3_MOD4 = M1M2_MOD4 * MOD3 % MOD4;\n\
    \            static constexpr long long M1M2M3_MOD5 = M1M2_MOD5 * MOD3 % MOD5;\n\
    \            static constexpr long long M1M2M3M4_MOD5 = M1M2M3_MOD5 * MOD4 % MOD5;\n\
    \n            static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(M1_MOD2,\
    \ MOD2).second;\n            static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3,\
    \ MOD3).second;\n            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4,\
    \ MOD4).second;\n            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5,\
    \ MOD5).second;\n\n            static constexpr unsigned long long M1 = MOD1;\n\
    \            static constexpr unsigned long long M1M2 = M1 * MOD2;\n         \
    \   static constexpr unsigned long long M1M2M3 = M1M2 * MOD3;\n            static\
    \ constexpr unsigned long long M1M2M3M4 = M1M2M3 * MOD4;\n\n            std::vector<unsigned\
    \ long long> a2(n), b2(m);\n            for (int i = 0; i < n; ++i) a2[i] = a[i];\n\
    \            for (int i = 0; i < m; ++i) b2[i] = b[i];\n\n            auto c1\
    \ = atcoder::convolution<MOD1>(a2, b2);\n            auto c2 = atcoder::convolution<MOD2>(a2,\
    \ b2);\n            auto c3 = atcoder::convolution<MOD3>(a2, b2);\n          \
    \  auto c4 = atcoder::convolution<MOD4>(a2, b2);\n            auto c5 = atcoder::convolution<MOD5>(a2,\
    \ b2);\n\n            std::vector<unsigned long long> c(n + m - 1);\n        \
    \    for (int i = 0; i < n + m - 1; ++i) {\n                // Garner's Algorithm\n\
    \                long long x1 = c1[i];\n                long long x2 = (atcoder::static_modint<MOD2>((long\
    \ long) c2[i] - x1) * INV_M1_MOD2).val();\n                long long x3 = (atcoder::static_modint<MOD3>((long\
    \ long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();\n                long\
    \ long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4\
    \ - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();\n                long long x5 =\
    \ (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5\
    \ - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();\n                c[i] = x1 +\
    \ x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4;\n            }\n        \
    \    return c;\n        }\n    }\n    std::vector<unsigned long long> convolution_mod_2_64(const\
    \ std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b)\
    \ {\n        int n = int(a.size()), m = int(b.size());\n        if (n == 0 or\
    \ m == 0) return {};\n        if (std::min(n, m) <= 60) return internal::convolution_naive(a,\
    \ b);\n\n        if (n + m - 1 <= 1 << 22) {\n            return internal::convolution_2_64::convolution_5mod(a,\
    \ b);\n        } else {\n            assert(n + m - 1 <= 1 << 23);\n         \
    \   return internal::convolution_2_64::convolution_6mod(a, b);\n        }\n  \
    \  }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION_2_64\n#define SUISEN_CONVOLUTION_2_64\n\n#include\
    \ <atcoder/convolution>\n#include <iostream>\n\n#include \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::convolution_2_64 {\n        std::vector<unsigned\
    \ long long> convolution_6mod(const std::vector<unsigned long long>& a, const\
    \ std::vector<unsigned long long>& b) {\n            int n = int(a.size()), m\
    \ = int(b.size());\n\n            static constexpr long long MOD1 = 754974721;\
    \  // 2^24\n            static constexpr long long MOD2 = 167772161;  // 2^25\n\
    \            static constexpr long long MOD3 = 469762049;  // 2^26\n         \
    \   static constexpr long long MOD4 = 377487361;  // 2^23\n            static\
    \ constexpr long long MOD5 = 595591169;  // 2^23\n            static constexpr\
    \ long long MOD6 = 645922817;  // 2^23\n\n            static constexpr long long\
    \ M1_MOD2 = MOD1 % MOD2;\n            static constexpr long long M1_MOD3 = MOD1\
    \ % MOD3;\n            static constexpr long long M1_MOD4 = MOD1 % MOD4;\n   \
    \         static constexpr long long M1_MOD5 = MOD1 % MOD5;\n            static\
    \ constexpr long long M1_MOD6 = MOD1 % MOD6;\n            static constexpr long\
    \ long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;\n            static constexpr long long\
    \ M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;\n            static constexpr long long M1M2_MOD5\
    \ = M1_MOD5 * MOD2 % MOD5;\n            static constexpr long long M1M2_MOD6 =\
    \ M1_MOD6 * MOD2 % MOD6;\n            static constexpr long long M1M2M3_MOD4 =\
    \ M1M2_MOD4 * MOD3 % MOD4;\n            static constexpr long long M1M2M3_MOD5\
    \ = M1M2_MOD5 * MOD3 % MOD5;\n            static constexpr long long M1M2M3_MOD6\
    \ = M1M2_MOD6 * MOD3 % MOD6;\n            static constexpr long long M1M2M3M4_MOD5\
    \ = M1M2M3_MOD5 * MOD4 % MOD5;\n            static constexpr long long M1M2M3M4_MOD6\
    \ = M1M2M3_MOD6 * MOD4 % MOD6;\n            static constexpr long long M1M2M3M4M5_MOD6\
    \ = M1M2M3M4_MOD6 * MOD5 % MOD6;\n\n            static constexpr long long INV_M1_MOD2\
    \ = atcoder::internal::inv_gcd(M1_MOD2, MOD2).second;\n            static constexpr\
    \ long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3, MOD3).second;\n\
    \            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4,\
    \ MOD4).second;\n            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5,\
    \ MOD5).second;\n            static constexpr long long INV_M1M2M3M4M5_MOD6 =\
    \ atcoder::internal::inv_gcd(M1M2M3M4M5_MOD6, MOD6).second;\n\n            static\
    \ constexpr unsigned long long M1 = MOD1;\n            static constexpr unsigned\
    \ long long M1M2 = M1 * MOD2;\n            static constexpr unsigned long long\
    \ M1M2M3 = M1M2 * MOD3;\n            static constexpr unsigned long long M1M2M3M4\
    \ = M1M2M3 * MOD4;\n            static constexpr unsigned long long M1M2M3M4M5\
    \ = M1M2M3M4 * MOD5;\n\n            std::vector<unsigned long long> a2(n), b2(m);\n\
    \            for (int i = 0; i < n; ++i) a2[i] = a[i];\n            for (int i\
    \ = 0; i < m; ++i) b2[i] = b[i];\n\n            auto c1 = atcoder::convolution<MOD1>(a2,\
    \ b2);\n            auto c2 = atcoder::convolution<MOD2>(a2, b2);\n          \
    \  auto c3 = atcoder::convolution<MOD3>(a2, b2);\n            auto c4 = atcoder::convolution<MOD4>(a2,\
    \ b2);\n            auto c5 = atcoder::convolution<MOD5>(a2, b2);\n          \
    \  auto c6 = atcoder::convolution<MOD6>(a2, b2);\n\n            std::vector<unsigned\
    \ long long> c(n + m - 1);\n            for (int i = 0; i < n + m - 1; ++i) {\n\
    \                // Garner's Algorithm\n                long long x1 = c1[i];\n\
    \                long long x2 = (atcoder::static_modint<MOD2>((long long) c2[i]\
    \ - x1) * INV_M1_MOD2).val();\n                long long x3 = (atcoder::static_modint<MOD3>((long\
    \ long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();\n                long\
    \ long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4\
    \ - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();\n                long long x5 =\
    \ (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5\
    \ - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();\n                long long x6\
    \ = (atcoder::static_modint<MOD6>((long long) c6[i] - x1 - x2 * M1_MOD6 - x3 *\
    \ M1M2_MOD6 - x4 * M1M2M3_MOD6 - x5 * M1M2M3M4_MOD6) * INV_M1M2M3M4M5_MOD6).val();\n\
    \                c[i] = x1 + x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4\
    \ + x6 * M1M2M3M4M5;\n            }\n            return c;\n        }\n\n    \
    \    std::vector<unsigned long long> convolution_5mod(const std::vector<unsigned\
    \ long long>& a, const std::vector<unsigned long long>& b) {\n            int\
    \ n = int(a.size()), m = int(b.size());\n\n            static constexpr long long\
    \ MOD1 = 998244353;  // 2^23\n            static constexpr long long MOD2 = 985661441;\
    \  // 2^22\n            static constexpr long long MOD3 = 943718401;  // 2^22\n\
    \            static constexpr long long MOD4 = 935329793;  // 2^22\n         \
    \   static constexpr long long MOD5 = 918552577;  // 2^22\n\n            static\
    \ constexpr long long M1_MOD2 = MOD1 % MOD2;\n            static constexpr long\
    \ long M1_MOD3 = MOD1 % MOD3;\n            static constexpr long long M1_MOD4\
    \ = MOD1 % MOD4;\n            static constexpr long long M1_MOD5 = MOD1 % MOD5;\n\
    \            static constexpr long long M1M2_MOD3 = M1_MOD3 * MOD2 % MOD3;\n \
    \           static constexpr long long M1M2_MOD4 = M1_MOD4 * MOD2 % MOD4;\n  \
    \          static constexpr long long M1M2_MOD5 = M1_MOD5 * MOD2 % MOD5;\n   \
    \         static constexpr long long M1M2M3_MOD4 = M1M2_MOD4 * MOD3 % MOD4;\n\
    \            static constexpr long long M1M2M3_MOD5 = M1M2_MOD5 * MOD3 % MOD5;\n\
    \            static constexpr long long M1M2M3M4_MOD5 = M1M2M3_MOD5 * MOD4 % MOD5;\n\
    \n            static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(M1_MOD2,\
    \ MOD2).second;\n            static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2_MOD3,\
    \ MOD3).second;\n            static constexpr long long INV_M1M2M3_MOD4 = atcoder::internal::inv_gcd(M1M2M3_MOD4,\
    \ MOD4).second;\n            static constexpr long long INV_M1M2M3M4_MOD5 = atcoder::internal::inv_gcd(M1M2M3M4_MOD5,\
    \ MOD5).second;\n\n            static constexpr unsigned long long M1 = MOD1;\n\
    \            static constexpr unsigned long long M1M2 = M1 * MOD2;\n         \
    \   static constexpr unsigned long long M1M2M3 = M1M2 * MOD3;\n            static\
    \ constexpr unsigned long long M1M2M3M4 = M1M2M3 * MOD4;\n\n            std::vector<unsigned\
    \ long long> a2(n), b2(m);\n            for (int i = 0; i < n; ++i) a2[i] = a[i];\n\
    \            for (int i = 0; i < m; ++i) b2[i] = b[i];\n\n            auto c1\
    \ = atcoder::convolution<MOD1>(a2, b2);\n            auto c2 = atcoder::convolution<MOD2>(a2,\
    \ b2);\n            auto c3 = atcoder::convolution<MOD3>(a2, b2);\n          \
    \  auto c4 = atcoder::convolution<MOD4>(a2, b2);\n            auto c5 = atcoder::convolution<MOD5>(a2,\
    \ b2);\n\n            std::vector<unsigned long long> c(n + m - 1);\n        \
    \    for (int i = 0; i < n + m - 1; ++i) {\n                // Garner's Algorithm\n\
    \                long long x1 = c1[i];\n                long long x2 = (atcoder::static_modint<MOD2>((long\
    \ long) c2[i] - x1) * INV_M1_MOD2).val();\n                long long x3 = (atcoder::static_modint<MOD3>((long\
    \ long) c3[i] - x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();\n                long\
    \ long x4 = (atcoder::static_modint<MOD4>((long long) c4[i] - x1 - x2 * M1_MOD4\
    \ - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();\n                long long x5 =\
    \ (atcoder::static_modint<MOD5>((long long) c5[i] - x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5\
    \ - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();\n                c[i] = x1 +\
    \ x2 * M1 + x3 * M1M2 + x4 * M1M2M3 + x5 * M1M2M3M4;\n            }\n        \
    \    return c;\n        }\n    }\n    std::vector<unsigned long long> convolution_mod_2_64(const\
    \ std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b)\
    \ {\n        int n = int(a.size()), m = int(b.size());\n        if (n == 0 or\
    \ m == 0) return {};\n        if (std::min(n, m) <= 60) return internal::convolution_naive(a,\
    \ b);\n\n        if (n + m - 1 <= 1 << 22) {\n            return internal::convolution_2_64::convolution_5mod(a,\
    \ b);\n        } else {\n            assert(n + m - 1 <= 1 << 23);\n         \
    \   return internal::convolution_2_64::convolution_6mod(a, b);\n        }\n  \
    \  }\n} // namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION_2_64\n"
  dependsOn:
  - library/convolution/convolution_naive.hpp
  isVerificationFile: false
  path: library/convolution/convolution_2_64.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:19:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  - test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
documentation_of: library/convolution/convolution_2_64.hpp
layout: document
title: Convolution $(\mathrm{mod}\ 2 ^ {64})$
---
## Convolution $(\mathrm{mod}\ 2 ^ {64})$

以下の $6$ つの NTT-friendly な素数を法として畳み込んだ後、Garner のアルゴリズムにより復元する。

1. $p _ 1 = 754974721=45\times 2 ^ {24}+1$
2. $p _ 2 = 167772161=5\times 2 ^ {25}+1$
3. $p _ 3 = 469762049=7\times 2 ^ {26}+1$
4. $p _ 4 = 377487361=45\times 2 ^ {23}+1$
5. $p _ 5 = 595591169=71\times 2 ^ {23}+1$
6. $p _ 6 = 645922817=77\times 2 ^ {23}+1$

即ち、列 $A,B$ を畳み込む場合、$\vert A\vert +\vert B\vert -1\leq 2 ^ {23}=8388608\simeq 8.39\times 10 ^ 6$ を満たす必要がある。

また、正しい値を復元するためには畳み込んだ後の各係数が $p _ 1 \times p _ 2 \times p _ 3\times p _ 4\times p _ 5\times p _ 6$ 未満でなければならないが、$(2 ^ {64} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {23} + 1}{2}\right\rceil \leq p _ 1 \times p _ 2 \times p _ 3\times p _ 4\times p _ 5\times p _ 6$ が成り立つため、$\vert A\vert +\vert B\vert -1\leq 2 ^ {23}$ の下では必ず正しい値を復元することが出来る。

一方で、$\vert A\vert +\vert B\vert -1\leq 2 ^ {22} = 4194304 \simeq 4.2\times 10 ^ 6$ を仮定すれば、$5$ つの NTT-friendly な素数を以下のように選ぶことで、

1. $p _ 1 ' = 998244353=119\times 2 ^ {23}+1$
2. $p _ 2 ' = 985661441=235\times 2 ^ {22}+1$
3. $p _ 3 ' = 943718401=225\times 2 ^ {22}+1$
4. $p _ 4 ' = 935329793=223\times 2 ^ {22}+1$
5. $p _ 5 ' = 918552577=219\times 2 ^ {22}+1$

$(2 ^ {64} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {22} + 1}{2}\right\rceil \leq p _ 1 ' \times p _ 2 ' \times p _ 3 ' \times p _ 4 ' \times p _ 5 ' $ を満たす。

本実装では、$\vert A\vert +\vert B\vert -1\leq 2 ^ {22} = 4194304$ を満たすならば $\mathrm{mod}$ を $5$ つ取る解法を、$2 ^ {22} \lt \vert A\vert +\vert B\vert -1 \leq 2 ^ {23}$ を満たすならば $\mathrm{mod}$ を $6$ つ取る解法を選択する。
