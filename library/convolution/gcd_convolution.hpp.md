---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/multiple.hpp
    title: "\u500D\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/gcd_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/multiple.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen::internal::arithmetic_operator\
    \ {}\n\nnamespace suisen {\nnamespace multiple_transform {\n\nusing namespace\
    \ suisen::internal::arithmetic_operator;\n\n// Calculates `g` s.t. g(n) = Sum_{n\
    \ | m} f(m) inplace.\ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T>\
    \ &f, AddAssign add_assign) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto cum = [&](const int p) {\n        const int qmax\
    \ = (n - 1) / p, rmax = qmax * p;\n        for (int q = qmax, pq = rmax; q >=\
    \ 1; --q, pq -= p) {\n            add_assign(f[q], f[pq]);\n            is_prime[pq]\
    \ = false;\n        }\n    };\n    cum(2);\n    for (int p = 3; p < n; p += 2)\
    \ if (is_prime[p]) cum(p);\n}\n\n// Calculates `f` s.t. g(n) = Sum_{n | m} f(m)\
    \ inplace.\ntemplate <typename T, typename SubAssign>\nvoid mobius(std::vector<T>\
    \ &f, SubAssign sub_assign) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto diff = [&](const int p) {\n        for (int q =\
    \ 1, pq = p; pq < n; ++q, pq += p) {\n            sub_assign(f[q], f[pq]);\n \
    \           is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ multiple_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct MultipleTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        multiple_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        multiple_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct MultipleTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        multiple_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        multiple_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::arithmetic_operator {}\ntemplate <typename\
    \ T, template <typename> class Transform>\nstruct Convolution {\n    static std::vector<T>\
    \ convolution(std::vector<T> a, std::vector<T> b) {\n        using namespace internal::arithmetic_operator;\n\
    \        const int n = a.size();\n        assert(n == int(b.size()));\n      \
    \  Transform<T>::transform(a);\n        Transform<T>::transform(b);\n        for\
    \ (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        using namespace internal::arithmetic_operator;\n        const\
    \ int num = a.size();\n        if (num == 0) return {};\n        const int n =\
    \ a[0].size();\n        for (auto &v : a) {\n            assert(n == int(v.size()));\n\
    \            Transform<T>::transform(v);\n        }\n        auto &res = a[0];\n\
    \        for (int i = 1; i < num; ++i) {\n            for (int j = 0; j < n; ++j)\
    \ res[j] *= a[i][j];\n        }\n        Transform<T>::inverse_transform(res);\n\
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n#line 6 \"library/convolution/gcd_convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing GCDConvolution = Convolution<T,\
    \ MultipleTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T>\
    \ gcd_convolution(Args &&...args) {\n    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_GCD_CONVOLUTION\n#define SUISEN_GCD_CONVOLUTION\n\n#include\
    \ \"library/transform/multiple.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing GCDConvolution = Convolution<T,\
    \ MultipleTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T>\
    \ gcd_convolution(Args &&...args) {\n    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_GCD_CONVOLUTION\n"
  dependsOn:
  - library/transform/multiple.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/gcd_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/gcd_convolution/lcms.test.cpp
documentation_of: library/convolution/gcd_convolution.hpp
layout: document
title: GCD Convolution
---

### gcd_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> gcd_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> gcd_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ および $(B_0=0,B_1,\ldots,B_{N-1})$ を添字 gcd で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=1,\ldots,2^N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { \gcd (i, j) = k } A _ i \cdot B _ j $$

  __ここで，$A_0=0$ かつ $B_0=0$ であることが要求されます__．
  
  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - $\vert A\vert =\vert B\vert$
     - $A_0=B_0=0$
  2. - $\vert \mathcal{A} ^ i\vert$ は全て等しい
     - $\forall i.\; \mathcal{A} ^ i _ 0 = 0$

- 時間計算量

  1. $\Theta(N\log\log N)$
  2. 列の数を $K$ として，$\Theta(K\cdot N\log\log N)$
