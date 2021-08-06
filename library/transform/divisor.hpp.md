---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/transform/multiple/divide_both.test.cpp
    title: test/src/transform/multiple/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/divisor.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen{\n\nnamespace divisor_transform {\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto cum = [&](const int p) {\n\
    \        for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n            add_assign(f[pq],\
    \ f[q]);\n            is_prime[pq] = false;\n        }\n    };\n    cum(2);\n\
    \    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\n// Calculates\
    \ `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename SubAssign>\n\
    void mobius(std::vector<T> &f, SubAssign sub_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto diff = [&](const int p) {\n\
    \        const int qmax = (n - 1) / p, rmax = qmax * p;\n        for (int q =\
    \ qmax, pq = rmax; q >= 1; --q, pq -= p) {\n            sub_assign(f[pq], f[q]);\n\
    \            is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ divisor_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct DivisorTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        divisor_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        divisor_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct DivisorTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        divisor_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        divisor_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_DIVISOR_TRANSFORM\n#define SUISEN_DIVISOR_TRANSFORM\n\n#include\
    \ <vector>\n\nnamespace suisen{\n\nnamespace divisor_transform {\n\n// Calculates\
    \ `g` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto cum = [&](const int p) {\n\
    \        for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n            add_assign(f[pq],\
    \ f[q]);\n            is_prime[pq] = false;\n        }\n    };\n    cum(2);\n\
    \    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\n// Calculates\
    \ `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename SubAssign>\n\
    void mobius(std::vector<T> &f, SubAssign sub_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto diff = [&](const int p) {\n\
    \        const int qmax = (n - 1) / p, rmax = qmax * p;\n        for (int q =\
    \ qmax, pq = rmax; q >= 1; --q, pq -= p) {\n            sub_assign(f[pq], f[q]);\n\
    \            is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ divisor_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct DivisorTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        divisor_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        divisor_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct DivisorTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        divisor_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        divisor_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n#endif // SUISEN_DIVISOR_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/divisor.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/transform/multiple/divide_both.test.cpp
documentation_of: library/transform/divisor.hpp
layout: document
title: "\u7D04\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\u30B9\
  \u5909\u63DB"
---

### struct DivisorTransform

- シグネチャ

  ```cpp
  template <typename T>
  struct DivisorTransform {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に約数系ゼータ変換を施す関数 `DivisorTransform<T>::transform` およびその逆変換 (メビウス変換) を施す関数 `DivisorTransform<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  1. ゼータ変換 (`DivisorTransform<T>::transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{j \mid i} A_j $$
  
  2. メビウス変換 (`DivisorTransform<T>::inverse_transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{j \mid i} B_j $$
  
  ここで，$j\mid i$ は $j$ が $i$ を割り切ること，言い換えれば $j$ が $i$ の約数であることを表します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=` が定義されている必要があります．

- 制約

  - $1\leq N \leq 10^7$

- 時間計算量

  $\Theta(N\log\log N)$

### struct DivisorTransformGeneral

- シグネチャ

  ```cpp
  template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
  struct DivisorTransformGeneral {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  型 `T` に `operator+=`，`operator-=` が定義されていない場合にはこちらを使用します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `AddAssign`: 複合代入演算 `operator+=` に相当する関数の型です．
  - `SubAssign`: 複合代入演算 `operator-=` に相当する関数の型です．
  - `AddAssign add_assign`: `AddAssign` 型のインスタンスです．関数呼び出し `add_assign(T &a, T b)` が意味的に `a += b` と等価であることを期待します．ただし，返り値は捨てられます．
  - `SubAssign sub_assign`: `SubAssign` 型のインスタンスです．関数呼び出し `sub_assign(T &a, T b)` が意味的に `a -= b` と等価であることを期待します．ただし，返り値は捨てられます．
