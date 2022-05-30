---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/divisor.hpp
    title: "\u7D04\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
    title: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/lcm_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/divisor.hpp\"\n\n\n\n#include <vector>\n#line 1 \"library/util/default_operator.hpp\"\
    \n\n\n\nnamespace suisen {\n    namespace default_operator {\n        template\
    \ <typename T>\n        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n\
    \        template <typename T>\n        auto one()  -> decltype(T { 1 }) { return\
    \ T { 1 }; }\n        template <typename T>\n        auto add(const T &x, const\
    \ T &y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(const T &x, const T &y) -> decltype(x - y) { return x - y; }\n\
    \        template <typename T>\n        auto mul(const T &x, const T &y) -> decltype(x\
    \ * y) { return x * y; }\n        template <typename T>\n        auto div(const\
    \ T &x, const T &y) -> decltype(x / y) { return x / y; }\n        template <typename\
    \ T>\n        auto mod(const T &x, const T &y) -> decltype(x % y) { return x %\
    \ y; }\n        template <typename T>\n        auto neg(const T &x) -> decltype(-x)\
    \ { return -x; }\n        template <typename T>\n        auto inv(const T &x)\
    \ -> decltype(one<T>() / x)  { return one<T>() / x; }\n    } // default_operator\n\
    \    namespace default_operator_noref {\n        template <typename T>\n     \
    \   auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(T x, T y) -> decltype(x + y) { return x + y;\
    \ }\n        template <typename T>\n        auto sub(T x, T y) -> decltype(x -\
    \ y) { return x - y; }\n        template <typename T>\n        auto mul(T x, T\
    \ y) -> decltype(x * y) { return x * y; }\n        template <typename T>\n   \
    \     auto div(T x, T y) -> decltype(x / y) { return x / y; }\n        template\
    \ <typename T>\n        auto mod(T x, T y) -> decltype(x % y) { return x % y;\
    \ }\n        template <typename T>\n        auto neg(T x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(T x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n#line 6 \"library/transform/divisor.hpp\"\n\nnamespace suisen::divisor_transform\
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
    \ suisen::divisor_transform\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/convolution/convolution.hpp\"\n\n\
    #line 8 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n    namespace\
    \ convolution {\n        template <typename T, auto transform, auto inv_transform,\
    \ auto mul = default_operator::mul<T>>\n        std::vector<T> transform_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n            const std::size_t n = a.size(), m = b.size();\n\
    \            assert(n == m);\n            transform(a), transform(b);\n      \
    \      for (std::size_t i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);\n         \
    \   inv_transform(a);\n            return a;\n        }\n        template <typename\
    \ T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>\n\
    \        std::vector<T> transform_convolution(std::vector<std::vector<T>> a) {\n\
    \            const std::size_t num = a.size();\n            assert(num);\n   \
    \         const std::size_t n = a[0].size();\n            for (auto &v : a) {\n\
    \                assert(n == int(v.size()));\n                transform(v);\n\
    \            }\n            auto &res = a[0];\n            for (int i = 1; i <\
    \ num; ++i) {\n                for (int j = 0; j < n; ++j) res[j] = mul(res[j],\
    \ a[i][j]);\n            }\n            inv_transform(res);\n            return\
    \ res;\n        }\n    }\n} // namespace suisen\n\n\n\n#line 6 \"library/convolution/lcm_convolution.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T,\n        auto add\
    \ = default_operator::add<T>,\n        auto sub = default_operator::sub<T>,\n\
    \        auto mul = default_operator::mul<T>\n    >\n    auto lcm_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        return convolution::transform_convolution<\n\
    \            T,\n            divisor_transform::zeta<T, add>,\n            divisor_transform::mobius<T,\
    \ sub>,\n            mul\n        >(std::move(a), std::move(b));\n    }\n} //\
    \ namespace suisen\n\n\n"
  code: "#ifndef SUISEN_LCM_CONVOLUTION\n#define SUISEN_LCM_CONVOLUTION\n\n#include\
    \ \"library/transform/divisor.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename T,\n        auto add\
    \ = default_operator::add<T>,\n        auto sub = default_operator::sub<T>,\n\
    \        auto mul = default_operator::mul<T>\n    >\n    auto lcm_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        return convolution::transform_convolution<\n\
    \            T,\n            divisor_transform::zeta<T, add>,\n            divisor_transform::mobius<T,\
    \ sub>,\n            mul\n        >(std::move(a), std::move(b));\n    }\n} //\
    \ namespace suisen\n\n#endif // SUISEN_LCM_CONVOLUTION\n"
  dependsOn:
  - library/transform/divisor.hpp
  - library/util/default_operator.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/lcm_convolution.hpp
  requiredBy: []
  timestamp: '2022-02-16 15:42:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
documentation_of: library/convolution/lcm_convolution.hpp
layout: document
title: LCM Convolution
---

### lcm_convolution

- シグネチャ

  ```cpp
  template <
      typename T,
      auto add = default_operator::add<T>,
      auto sub = default_operator::sub<T>,
      auto mul = default_operator::mul<T>
  >
  std::vector<T> lcm_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ および $(B_0=0,B_1,\ldots,B_{N-1})$ を添字 lcm で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { \mathrm{lcm} (i, j) = k } A _ i \cdot B _ j $$

  __ここで，$A_0=0$ かつ $B_0=0$ であることが要求されます__．
  
  $\gcd$ とは異なり，$N$ 以上の部分に非零の項が存在しますが，これらを全て計算すると計算量が大きくなりすぎるため，$N$ 以上の部分は切り捨てる実装となっています．以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．
  - `mul`: 二項演算 (乗算)．デフォルトでは `operator*` が呼ばれるようになっています．

- 返り値
  
  $A\ast B$

- 制約

  - $\vert A\vert =\vert B\vert$
  - $A_0=B_0=0$

- 時間計算量

  $\Theta(N\log\log N)$