---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/lcm_convolution.hpp
    title: LCM Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
    title: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/transform/multiple/divide_both.test.cpp
    title: test/src/transform/multiple/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/divisor.hpp\"\n\n\n\n#include <vector>\n\
    #line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace suisen {\n    namespace\
    \ default_operator {\n        template <typename T>\n        auto zero() -> decltype(T\
    \ { 0 }) { return T { 0 }; }\n        template <typename T>\n        auto one()\
    \  -> decltype(T { 1 }) { return T { 1 }; }\n        template <typename T>\n \
    \       auto add(const T &x, const T &y) -> decltype(x + y) { return x + y; }\n\
    \        template <typename T>\n        auto sub(const T &x, const T &y) -> decltype(x\
    \ - y) { return x - y; }\n        template <typename T>\n        auto mul(const\
    \ T &x, const T &y) -> decltype(x * y) { return x * y; }\n        template <typename\
    \ T>\n        auto div(const T &x, const T &y) -> decltype(x / y) { return x /\
    \ y; }\n        template <typename T>\n        auto mod(const T &x, const T &y)\
    \ -> decltype(x % y) { return x % y; }\n        template <typename T>\n      \
    \  auto neg(const T &x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(const T &x) -> decltype(one<T>() / x)  { return one<T>()\
    \ / x; }\n    } // default_operator\n    namespace default_operator_noref {\n\
    \        template <typename T>\n        auto zero() -> decltype(T { 0 }) { return\
    \ T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 6 \"library/transform/divisor.hpp\"\
    \n\nnamespace suisen::divisor_transform {\n    // Calculates `g` s.t. g(n) = Sum_{d\
    \ | n} f(d) inplace.\n    template <typename T, auto add = default_operator::add<T>>\n\
    \    void zeta(std::vector<T> &f) {\n        const int n = f.size();\n       \
    \ std::vector<char> is_prime(n, true);\n        auto cum = [&](const int p) {\n\
    \            for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n               \
    \ f[pq] = add(f[pq], f[q]);\n                is_prime[pq] = false;\n         \
    \   }\n        };\n        for (int p = 2; p < n; ++p) if (is_prime[p]) cum(p);\n\
    \    }\n    // Calculates `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\n    template\
    \ <typename T, auto sub = default_operator::sub<T>>\n    void mobius(std::vector<T>\
    \ &f) {\n        const int n = f.size();\n        std::vector<char> is_prime(n,\
    \ true);\n        auto diff = [&](const int p) {\n            const int qmax =\
    \ (n - 1) / p, rmax = qmax * p;\n            for (int q = qmax, pq = rmax; q >=\
    \ 1; --q, pq -= p) {\n                f[pq] = sub(f[pq], f[q]);\n            \
    \    is_prime[pq] = false;\n            }\n        };\n        for (int p = 2;\
    \ p < n; ++p) if (is_prime[p]) diff(p);\n    }\n} // namespace suisen::divisor_transform\n\
    \n\n"
  code: "#ifndef SUISEN_DIVISOR_TRANSFORM\n#define SUISEN_DIVISOR_TRANSFORM\n\n#include\
    \ <vector>\n#include \"library/util/default_operator.hpp\"\n\nnamespace suisen::divisor_transform\
    \ {\n    // Calculates `g` s.t. g(n) = Sum_{d | n} f(d) inplace.\n    template\
    \ <typename T, auto add = default_operator::add<T>>\n    void zeta(std::vector<T>\
    \ &f) {\n        const int n = f.size();\n        std::vector<char> is_prime(n,\
    \ true);\n        auto cum = [&](const int p) {\n            for (int q = 1, pq\
    \ = p; pq < n; ++q, pq += p) {\n                f[pq] = add(f[pq], f[q]);\n  \
    \              is_prime[pq] = false;\n            }\n        };\n        for (int\
    \ p = 2; p < n; ++p) if (is_prime[p]) cum(p);\n    }\n    // Calculates `f` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\n    template <typename T, auto sub = default_operator::sub<T>>\n\
    \    void mobius(std::vector<T> &f) {\n        const int n = f.size();\n     \
    \   std::vector<char> is_prime(n, true);\n        auto diff = [&](const int p)\
    \ {\n            const int qmax = (n - 1) / p, rmax = qmax * p;\n            for\
    \ (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n                f[pq] = sub(f[pq],\
    \ f[q]);\n                is_prime[pq] = false;\n            }\n        };\n \
    \       for (int p = 2; p < n; ++p) if (is_prime[p]) diff(p);\n    }\n} // namespace\
    \ suisen::divisor_transform\n\n#endif // SUISEN_DIVISOR_TRANSFORM\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/transform/divisor.hpp
  requiredBy:
  - library/convolution/lcm_convolution.hpp
  timestamp: '2022-01-31 13:34:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
  - test/src/transform/multiple/divide_both.test.cpp
documentation_of: library/transform/divisor.hpp
layout: document
title: "\u7D04\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\u30B9\
  \u5909\u63DB"
---

- シグネチャ

  ```cpp
  template <typename T, auto add = default_operator::add<T>>
  void zeta(std::vector<T> &f)
  template <typename T, auto sub = default_operator::sub<T>>
  void mobius(std::vector<T> &f)
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に約数系ゼータ変換を施す関数 `zeta` およびその逆変換 (メビウス変換) を施す関数 `mobius` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  ゼータ変換では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{j \mid i} A_j $$

  メビウス変換では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{j \mid i} B_j $$
  
  ここで，$j\mid i$ は $j$ が $i$ を割り切ること，言い換えれば $j$ が $i$ の約数であることを表します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．

- 制約

  - $1\leq N \leq 10^7$

- 時間計算量

  $\Theta(N\log\log N)$
