---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
    title: test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\n\n\
    \n#include <atcoder/convolution>\n#include <iostream>\n\n#line 1 \"library/convolution/convolution_naive.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen::internal {\n    template <typename\
    \ T>\n    std::vector<T> convolution_naive(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\n        const int n = a.size(), m = b.size();\n        std::vector<T>\
    \ c(n + m - 1);\n        if (n < m) {\n            for (int j = 0; j < m; j++)\
    \ for (int i = 0; i < n; i++) c[i + j] += a[i] * b[j];\n        } else {\n   \
    \         for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] +=\
    \ a[i] * b[j];\n        }\n        return c;\n    }\n} // namespace suisen\n\n\
    \n\n#line 8 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \        if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 60) return\
    \ internal::convolution_naive(a, b);\n\n        static constexpr long long MOD1\
    \ = 754974721;  // 2^24\n        static constexpr long long MOD2 = 167772161;\
    \  // 2^25\n        static constexpr long long MOD3 = 469762049;  // 2^26\n  \
    \      static constexpr long long M1M2 = MOD1 * MOD2;\n        static constexpr\
    \ long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n   \
    \     static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ARBITRARY_MOD_CONVOLUTION\n#define SUISEN_ARBITRARY_MOD_CONVOLUTION\n\
    \n#include <atcoder/convolution>\n#include <iostream>\n\n#include \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \        if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 60) return\
    \ internal::convolution_naive(a, b);\n\n        static constexpr long long MOD1\
    \ = 754974721;  // 2^24\n        static constexpr long long MOD2 = 167772161;\
    \  // 2^25\n        static constexpr long long MOD3 = 469762049;  // 2^26\n  \
    \      static constexpr long long M1M2 = MOD1 * MOD2;\n        static constexpr\
    \ long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n   \
    \     static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_ARBITRARY_MOD_CONVOLUTION\n"
  dependsOn:
  - library/convolution/convolution_naive.hpp
  isVerificationFile: false
  path: library/convolution/arbitrary_mod_convolution.hpp
  requiredBy: []
  timestamp: '2022-05-05 17:36:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
documentation_of: library/convolution/arbitrary_mod_convolution.hpp
layout: document
title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
---
## 任意 $\mathrm{mod}$ 畳み込み

以下の $3$ つの NTT-friendly な素数を法として畳み込んだ後、Garner のアルゴリズムにより復元する。

1. $p _ 1 = 754974721=45\times 2 ^ {24}+1$
2. $p _ 2 = 167772161=5\times 2 ^ {25}+1$
3. $p _ 3 = 469762049=7\times 2 ^ {26}+1$

即ち、列 $A,B$ を畳み込む場合、$|A|+|B|-1\leq 2 ^ {24}=16777216\simeq 1.68\times 10 ^ 7$ を満たす必要がある。

また、正しい値を復元するためには畳み込んだ後の各係数が $p _ 1 \times p _ 2 \times p _ 3$ 未満でなければならないが、$\mathrm{mod}$ が $2 ^ {31}$ 以下と仮定すれば、$(2 ^ {31} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {24} + 1}{2}\right\rceil \leq p _ 1 \times p _ 2 \times p _ 3$ が成り立つため、$|A|+|B|-1\leq 2^{24}$ の下では必ず正しい値を復元することが出来る。
