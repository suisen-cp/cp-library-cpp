---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_2_64.hpp
    title: Convolution 2 64
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: library/convolution/convolution_naive.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_2_64
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_2_64
  bundledCode: "#line 1 \"test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_2_64\"\n\n\
    #include <iostream>\n#line 1 \"library/convolution/convolution_2_64.hpp\"\n\n\n\
    \n#include <atcoder/convolution>\n#line 6 \"library/convolution/convolution_2_64.hpp\"\
    \n\n#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen::internal {\n    template <typename T>\n    std::vector<T>\
    \ convolution_naive(const std::vector<T>& a, const std::vector<T>& b) {\n    \
    \    const int n = a.size(), m = b.size();\n        std::vector<T> c(n + m - 1);\n\
    \        if (n < m) {\n            for (int j = 0; j < m; j++) for (int i = 0;\
    \ i < n; i++) c[i + j] += a[i] * b[j];\n        } else {\n            for (int\
    \ i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];\n  \
    \      }\n        return c;\n    }\n} // namespace suisen\n\n\n\n#line 8 \"library/convolution/convolution_2_64.hpp\"\
    \n\nnamespace suisen {\n    std::vector<unsigned long long> convolution_mod_2_64(const\
    \ std::vector<unsigned long long>& a, const std::vector<unsigned long long>& b)\
    \ {\n        int n = int(a.size()), m = int(b.size());\n        if (n == 0 or\
    \ m == 0) return {};\n        if (std::min(n, m) <= 60) return internal::convolution_naive(a,\
    \ b);\n\n        static constexpr long long MOD1 = 754974721;  // 2^24\n     \
    \   static constexpr long long MOD2 = 167772161;  // 2^25\n        static constexpr\
    \ long long MOD3 = 469762049;  // 2^26\n        static constexpr long long MOD4\
    \ = 377487361;  // 2^23\n        static constexpr long long MOD5 = 595591169;\
    \  // 2^23\n        static constexpr long long MOD6 = 645922817;  // 2^23\n  \
    \      \n        static constexpr long long M1_MOD2         = MOD1 % MOD2;\n \
    \       static constexpr long long M1_MOD3         = MOD1 % MOD3;\n        static\
    \ constexpr long long M1_MOD4         = MOD1 % MOD4;\n        static constexpr\
    \ long long M1_MOD5         = MOD1 % MOD5;\n        static constexpr long long\
    \ M1_MOD6         = MOD1 % MOD6;\n        static constexpr long long M1M2_MOD3\
    \       = M1_MOD3 * MOD2 % MOD3;\n        static constexpr long long M1M2_MOD4\
    \       = M1_MOD4 * MOD2 % MOD4;\n        static constexpr long long M1M2_MOD5\
    \       = M1_MOD5 * MOD2 % MOD5;\n        static constexpr long long M1M2_MOD6\
    \       = M1_MOD6 * MOD2 % MOD6;\n        static constexpr long long M1M2M3_MOD4\
    \     = M1M2_MOD4 * MOD3 % MOD4;\n        static constexpr long long M1M2M3_MOD5\
    \     = M1M2_MOD5 * MOD3 % MOD5;\n        static constexpr long long M1M2M3_MOD6\
    \     = M1M2_MOD6 * MOD3 % MOD6;\n        static constexpr long long M1M2M3M4_MOD5\
    \   = M1M2M3_MOD5 * MOD4 % MOD5;\n        static constexpr long long M1M2M3M4_MOD6\
    \   = M1M2M3_MOD6 * MOD4 % MOD6;\n        static constexpr long long M1M2M3M4M5_MOD6\
    \ = M1M2M3M4_MOD6 * MOD5 % MOD6;\n\n        static constexpr long long INV_M1_MOD2\
    \         = atcoder::internal::inv_gcd(M1_MOD2, MOD2).second;\n        static\
    \ constexpr long long INV_M1M2_MOD3       = atcoder::internal::inv_gcd(M1M2_MOD3,\
    \ MOD3).second;\n        static constexpr long long INV_M1M2M3_MOD4     = atcoder::internal::inv_gcd(M1M2M3_MOD4,\
    \ MOD4).second;\n        static constexpr long long INV_M1M2M3M4_MOD5   = atcoder::internal::inv_gcd(M1M2M3M4_MOD5,\
    \ MOD5).second;\n        static constexpr long long INV_M1M2M3M4M5_MOD6 = atcoder::internal::inv_gcd(M1M2M3M4M5_MOD6,\
    \ MOD6).second;\n\n        std::vector<unsigned long long> a2(n), b2(m);\n   \
    \     for (int i = 0; i < n; ++i) a2[i] = a[i];\n        for (int i = 0; i < m;\
    \ ++i) b2[i] = b[i];\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n\
    \        auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n        auto c4 = atcoder::convolution<MOD4>(a2, b2);\n        auto c5\
    \ = atcoder::convolution<MOD5>(a2, b2);\n        auto c6 = atcoder::convolution<MOD6>(a2,\
    \ b2);\n\n        const unsigned long long m1         = MOD1;\n        const unsigned\
    \ long long m1m2       = m1 * MOD2;\n        const unsigned long long m1m2m3 \
    \    = m1m2 * MOD3;\n        const unsigned long long m1m2m3m4   = m1m2m3 * MOD4;\n\
    \        const unsigned long long m1m2m3m4m5 = m1m2m3m4 * MOD5;\n\n        std::vector<unsigned\
    \ long long> c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n  \
    \          // Garner's Algorithm\n            long long x1 = c1[i];\n        \
    \    long long x2 = (atcoder::static_modint<MOD2>((long long) c2[i] - x1) * INV_M1_MOD2).val();\n\
    \            long long x3 = (atcoder::static_modint<MOD3>((long long) c3[i] -\
    \ x1 - x2 * M1_MOD3) * INV_M1M2_MOD3).val();\n            long long x4 = (atcoder::static_modint<MOD4>((long\
    \ long) c4[i] - x1 - x2 * M1_MOD4 - x3 * M1M2_MOD4) * INV_M1M2M3_MOD4).val();\n\
    \            long long x5 = (atcoder::static_modint<MOD5>((long long) c5[i] -\
    \ x1 - x2 * M1_MOD5 - x3 * M1M2_MOD5 - x4 * M1M2M3_MOD5) * INV_M1M2M3M4_MOD5).val();\n\
    \            long long x6 = (atcoder::static_modint<MOD6>((long long) c6[i] -\
    \ x1 - x2 * M1_MOD6 - x3 * M1M2_MOD6 - x4 * M1M2M3_MOD6 - x5 * M1M2M3M4_MOD6)\
    \ * INV_M1M2M3M4M5_MOD6).val();\n            c[i] = x1 + x2 * m1 + x3 * m1m2 +\
    \ x4 * m1m2m3 + x5 * m1m2m3m4 + x6 * m1m2m3m4m5;\n        }\n        return c;\n\
    \    }\n} // namespace suisen\n\n\n\n#line 5 \"test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<unsigned long\
    \ long> a(n), b(m);\n    for (auto &e : a) std::cin >> e;\n    for (auto &e :\
    \ b) std::cin >> e;\n\n    std::vector<unsigned long long> c = suisen::convolution_mod_2_64(a,\
    \ b);\n    for (std::size_t i = 0; i < n + m - 1; ++i) {\n        std::cout <<\
    \ c[i] << \" \\n\"[i == n + m - 2];\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_2_64\"\n\
    \n#include <iostream>\n#include \"library/convolution/convolution_2_64.hpp\"\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::size_t n, m;\n    std::cin >> n >> m;\n\n    std::vector<unsigned long\
    \ long> a(n), b(m);\n    for (auto &e : a) std::cin >> e;\n    for (auto &e :\
    \ b) std::cin >> e;\n\n    std::vector<unsigned long long> c = suisen::convolution_mod_2_64(a,\
    \ b);\n    for (std::size_t i = 0; i < n + m - 1; ++i) {\n        std::cout <<\
    \ c[i] << \" \\n\"[i == n + m - 2];\n    }\n    return 0;\n}"
  dependsOn:
  - library/convolution/convolution_2_64.hpp
  - library/convolution/convolution_naive.hpp
  isVerificationFile: true
  path: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  requiredBy: []
  timestamp: '2022-05-05 17:36:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
- /verify/test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp.html
title: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
---
