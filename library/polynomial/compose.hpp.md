---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
    title: test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/compose.hpp\"\n\n\n\n#include <cmath>\n\
    #include <atcoder/convolution>\n\nnamespace suisen {\n    template <typename FPSType>\n\
    \    FPSType compose(const FPSType& f, FPSType g, const int n) {\n        if (f.empty())\
    \ return {};\n        if (g.empty()) return { f[0] };\n\n        if (int(g.size())\
    \ > n) {\n            g.resize(n);\n        }\n\n        const int sqn = ::sqrt(f.size())\
    \ + 1;\n\n        std::vector<FPSType> pow_g_small(sqn);\n        pow_g_small[0]\
    \ = { 1 };\n        for (int i = 1; i < sqn; ++i) {\n            pow_g_small[i]\
    \ = pow_g_small[i - 1] * g;\n            pow_g_small[i].resize(n);\n        }\n\
    \        const FPSType g_large = pow_g_small.back() * g;\n\n        FPSType pow_g_large{\
    \ 1 };\n\n        FPSType h(n);\n        for (int i = 0; i < sqn; ++i) {\n   \
    \         FPSType hi(n);\n            for (int j = 0; j < sqn; ++j) {\n      \
    \          const int ij = i * sqn + j;\n                if (ij >= int(f.size()))\
    \ break;\n\n                const auto c = f[ij];\n                const FPSType&\
    \ gj = pow_g_small[j];\n\n                for (int k = 0; k < int(gj.size());\
    \ ++k) {\n                    hi[k] += c * gj[k];\n                }\n       \
    \     }\n            hi = pow_g_large * hi;\n            for (int k = 0; k < n;\
    \ ++k) {\n                h[k] += hi[k];\n            }\n            pow_g_large\
    \ = pow_g_large * g_large;\n            pow_g_large.resize(n);\n        }\n  \
    \      return h;\n    }\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_POLY_COMPOSE\n#define SUISEN_POLY_COMPOSE\n\n#include <cmath>\n\
    #include <atcoder/convolution>\n\nnamespace suisen {\n    template <typename FPSType>\n\
    \    FPSType compose(const FPSType& f, FPSType g, const int n) {\n        if (f.empty())\
    \ return {};\n        if (g.empty()) return { f[0] };\n\n        if (int(g.size())\
    \ > n) {\n            g.resize(n);\n        }\n\n        const int sqn = ::sqrt(f.size())\
    \ + 1;\n\n        std::vector<FPSType> pow_g_small(sqn);\n        pow_g_small[0]\
    \ = { 1 };\n        for (int i = 1; i < sqn; ++i) {\n            pow_g_small[i]\
    \ = pow_g_small[i - 1] * g;\n            pow_g_small[i].resize(n);\n        }\n\
    \        const FPSType g_large = pow_g_small.back() * g;\n\n        FPSType pow_g_large{\
    \ 1 };\n\n        FPSType h(n);\n        for (int i = 0; i < sqn; ++i) {\n   \
    \         FPSType hi(n);\n            for (int j = 0; j < sqn; ++j) {\n      \
    \          const int ij = i * sqn + j;\n                if (ij >= int(f.size()))\
    \ break;\n\n                const auto c = f[ij];\n                const FPSType&\
    \ gj = pow_g_small[j];\n\n                for (int k = 0; k < int(gj.size());\
    \ ++k) {\n                    hi[k] += c * gj[k];\n                }\n       \
    \     }\n            hi = pow_g_large * hi;\n            for (int k = 0; k < n;\
    \ ++k) {\n                h[k] += hi[k];\n            }\n            pow_g_large\
    \ = pow_g_large * g_large;\n            pow_g_large.resize(n);\n        }\n  \
    \      return h;\n    }\n\n} // namespace suisen\n\n\n#endif // SUISEN_POLY_COMPOSE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/compose.hpp
  requiredBy: []
  timestamp: '2023-05-21 06:42:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
documentation_of: library/polynomial/compose.hpp
layout: document
title: "\u5408\u6210"
---
## 合成

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ i,\ g(x) = \sum _ {i = 0} ^ {M - 1} b _ i x ^ i$ に対して合成 $(f\circ g)(x) \pmod{x ^ K}$ を $O(NK + \sqrt{N}K\log K + M)$ 時間で計算するライブラリ。

## アルゴリズム

まず、$g\leftarrow g \bmod x ^ K$ とする。この部分の計算量は $O(M + K)$ である。

$\displaystyle f\circ g = \sum _ {i = 0} ^ {N - 1} a _ i g ^ i$ を計算したい。$B \coloneqq \lceil \sqrt{N} \rceil$ とすれば $\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} G ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} g ^ j$ と表せる。ただし $i \geq N$ に対して $a _ i = 0$ とする。

$g ^ 0, g ^ 1, \ldots, g ^ {B - 1}$ および $G\coloneqq g ^ B$ に対して $G ^ 0, G ^ 1, \ldots, G ^ {B - 1}$ を全て ($\mathrm{mod}\ x ^ K$ で) 前計算する。この前計算は $O(\sqrt N K \log K)$ 時間で可能である。

この前計算の結果を用いれば、各 $i=0,1,\ldots,B-1$ に対して、$\displaystyle \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j \bmod x ^ K$ を $O(\sqrt{N} K)$ 時間で計算できる。従って、$\displaystyle \left(G ^ i \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j\right) \bmod x ^ K$ の計算は $O(\sqrt{N} K + K \log K)$ 時間で可能である。

以上をまとめると、全体の計算量は $O(NK + \sqrt{N}K\log K + M)$ 時間となる。
