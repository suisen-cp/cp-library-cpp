---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/polynomial/rook_polynomial.hpp
    title: library/polynomial/rook_polynomial.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/convert_to_newton_basis/conversion_from_monomial_basis_to_newton_basis.test.cpp
    title: test/src/polynomial/convert_to_newton_basis/conversion_from_monomial_basis_to_newton_basis.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
    title: test/src/polynomial/rook_polynomial/abc272_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/rook_polynomial/dummy.test.cpp
    title: test/src/polynomial/rook_polynomial/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/convert_to_newton_basis.hpp\"\n\n\n\n\
    #include <tuple>\n#include <vector>\n\nnamespace suisen {\n    // Returns b=(b_0,...,b_{N-1})\
    \ s.t. f(x) = Sum[i=0,N-1] b_i Prod[j=0,i-1](x - p_j)\n    template <typename\
    \ FPSType>\n    std::vector<typename FPSType::value_type> convert_to_newton_basis(const\
    \ FPSType& f, const std::vector<typename FPSType::value_type>& p) {\n        const\
    \ int n = p.size();\n        assert(f.size() == n);\n\n        int m = 1;\n  \
    \      while (m < n) m <<= 1;\n\n        std::vector<FPSType> seg(2 * m);\n  \
    \      for (int i = 0; i < m; ++i) {\n            seg[m + i] = { i < n ? -p[i]\
    \ : 0, 1 };\n        }\n        for (int i = m - 1; i > 0; --i) {\n          \
    \  if (((i + 1) & -(i + 1)) == (i + 1)) continue; // i = 2^k - 1\n           \
    \ seg[i] = seg[2 * i] * seg[2 * i + 1];\n        }\n\n        seg[1] = f;\n  \
    \      for (int i = 1; i < m; ++i) {\n            std::tie(seg[2 * i + 1], seg[2\
    \ * i]) = seg[i].div_mod(seg[2 * i]);\n        }\n\n        std::vector<typename\
    \ FPSType::value_type> b(n);\n        for (int i = 0; i < n; ++i) {\n        \
    \    b[i] = seg[m + i].safe_get(0);\n        }\n        return b;\n    }\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVERT_TO_NEWTON_BASIS\n#define SUISEN_CONVERT_TO_NEWTON_BASIS\n\
    \n#include <tuple>\n#include <vector>\n\nnamespace suisen {\n    // Returns b=(b_0,...,b_{N-1})\
    \ s.t. f(x) = Sum[i=0,N-1] b_i Prod[j=0,i-1](x - p_j)\n    template <typename\
    \ FPSType>\n    std::vector<typename FPSType::value_type> convert_to_newton_basis(const\
    \ FPSType& f, const std::vector<typename FPSType::value_type>& p) {\n        const\
    \ int n = p.size();\n        assert(f.size() == n);\n\n        int m = 1;\n  \
    \      while (m < n) m <<= 1;\n\n        std::vector<FPSType> seg(2 * m);\n  \
    \      for (int i = 0; i < m; ++i) {\n            seg[m + i] = { i < n ? -p[i]\
    \ : 0, 1 };\n        }\n        for (int i = m - 1; i > 0; --i) {\n          \
    \  if (((i + 1) & -(i + 1)) == (i + 1)) continue; // i = 2^k - 1\n           \
    \ seg[i] = seg[2 * i] * seg[2 * i + 1];\n        }\n\n        seg[1] = f;\n  \
    \      for (int i = 1; i < m; ++i) {\n            std::tie(seg[2 * i + 1], seg[2\
    \ * i]) = seg[i].div_mod(seg[2 * i]);\n        }\n\n        std::vector<typename\
    \ FPSType::value_type> b(n);\n        for (int i = 0; i < n; ++i) {\n        \
    \    b[i] = seg[m + i].safe_get(0);\n        }\n        return b;\n    }\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_CONVERT_TO_NEWTON_BASIS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/convert_to_newton_basis.hpp
  requiredBy:
  - library/polynomial/rook_polynomial.hpp
  timestamp: '2023-05-21 01:49:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/rook_polynomial/abc272_h.test.cpp
  - test/src/polynomial/rook_polynomial/dummy.test.cpp
  - test/src/polynomial/convert_to_newton_basis/conversion_from_monomial_basis_to_newton_basis.test.cpp
documentation_of: library/polynomial/convert_to_newton_basis.hpp
layout: document
title: Convert To Newton Basis
---
## Convert To Newton Basis

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {n - 1} a _ i x ^ i$ および長さ $n$ の列 $\lbrace p _ i \rbrace _ {i = 0} ^ {n - 1}$ に対して、次を満たす列 $\lbrace b _ i \rbrace _ {i = 0} ^ {n - 1}$ を $O(n (\log n) ^ 2)$ 時間で計算するライブラリ。

$$f(x) = \sum _ {i = 0} ^ {n - 1} b _ i \prod _ {j = 0} ^ {i - 1} (x - p _ j).$$

## アルゴリズム

分割統治法による。$0\leq l \lt r\leq n$ なる整数組 $(l, r)$ に対して $\displaystyle f _ {l, r}(x) \coloneqq \sum _ {i = l} ^ {r - 1} b _ i \prod _ {j = l} ^ {i - 1} (x - p _ j)$ と定義すると、整数 $m\in\lbrack l, r)$ に対して次が成り立つ。

$$\begin{aligned}
f _ {l, r}(x)
&= \sum _ {i = l} ^ {m - 1} b _ i \prod _ {j = l} ^ {i - 1} (x - p _ j) + \left(\prod _ {i = l} ^ {m - 1} (x - p _ i)\right) \sum _ {i = m} ^ {r - 1} b _ i \prod _ {j = m} ^ {i - 1} (x - p _ j) \newline
&= f _ {l, m}(x) + g _ {l, m}(x) f _ {m, r}(x). \quad \left(g _ {l, m}(x) \coloneqq \prod _ {i = l} ^ {m - 1} (x - p _ i)\right)
\end{aligned}$$

ここで $\deg g _ {l, m} = m - l,\ \deg f _ {l, m} = m - l - 1$ に注目すると、$f _ {m, r}(x)$ と $f _ {l, m}(x)$ はそれぞれ $f _ {l, r}(x)$ を $g _ {l, m}(x)$ で割った商と余りに対応することが分かる。

従って、二分木状に $g _ {l, r}$ をボトムアップに計算し (subproduct tree)、トップダウンに $f _ {l, r}$ を計算することで $O(n (\log n) ^ 2)$ 時間で全ての $i = 0, 1, \ldots, n - 1$ に対する $f _ {i, i + 1}(x) \equiv b _ i$ を計算することができる。
