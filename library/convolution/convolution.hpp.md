---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/gcd_convolution.hpp
    title: GCD Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/lcm_convolution.hpp
    title: LCM Convolution
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/gcd_convolution.test.cpp
    title: test/src/convolution/gcd_convolution/gcd_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
    title: test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace\
    \ suisen {\n    namespace default_operator {\n        template <typename T>\n\
    \        auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template\
    \ <typename T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n\
    \        template <typename T>\n        auto add(const T &x, const T &y) -> decltype(x\
    \ + y) { return x + y; }\n        template <typename T>\n        auto sub(const\
    \ T &x, const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n    namespace default_operator_noref\
    \ {\n        template <typename T>\n        auto zero() -> decltype(T { 0 }) {\
    \ return T { 0 }; }\n        template <typename T>\n        auto one()  -> decltype(T\
    \ { 1 }) { return T { 1 }; }\n        template <typename T>\n        auto add(T\
    \ x, T y) -> decltype(x + y) { return x + y; }\n        template <typename T>\n\
    \        auto sub(T x, T y) -> decltype(x - y) { return x - y; }\n        template\
    \ <typename T>\n        auto mul(T x, T y) -> decltype(x * y) { return x * y;\
    \ }\n        template <typename T>\n        auto div(T x, T y) -> decltype(x /\
    \ y) { return x / y; }\n        template <typename T>\n        auto mod(T x, T\
    \ y) -> decltype(x % y) { return x % y; }\n        template <typename T>\n   \
    \     auto neg(T x) -> decltype(-x) { return -x; }\n        template <typename\
    \ T>\n        auto inv(T x) -> decltype(one<T>() / x)  { return one<T>() / x;\
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 8 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n    namespace convolution {\n        template <typename\
    \ T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>\n\
    \        std::vector<T> transform_convolution(std::vector<T> a, std::vector<T>\
    \ b) {\n            const std::size_t n = a.size(), m = b.size();\n          \
    \  assert(n == m);\n            transform(a), transform(b);\n            for (std::size_t\
    \ i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);\n            inv_transform(a);\n\
    \            return a;\n        }\n        template <typename T, auto transform,\
    \ auto inv_transform, auto mul = default_operator::mul<T>>\n        std::vector<T>\
    \ transform_convolution(std::vector<std::vector<T>> a) {\n            const std::size_t\
    \ num = a.size();\n            assert(num);\n            const std::size_t n =\
    \ a[0].size();\n            for (auto &v : a) {\n                assert(n == int(v.size()));\n\
    \                transform(v);\n            }\n            auto &res = a[0];\n\
    \            for (int i = 1; i < num; ++i) {\n                for (int j = 0;\
    \ j < n; ++j) res[j] = mul(res[j], a[i][j]);\n            }\n            inv_transform(res);\n\
    \            return res;\n        }\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION\n#define SUISEN_CONVOLUTION\n\n#include <cassert>\n\
    #include <vector>\n\n#include \"library/util/default_operator.hpp\"\n\nnamespace\
    \ suisen {\n    namespace convolution {\n        template <typename T, auto transform,\
    \ auto inv_transform, auto mul = default_operator::mul<T>>\n        std::vector<T>\
    \ transform_convolution(std::vector<T> a, std::vector<T> b) {\n            const\
    \ std::size_t n = a.size(), m = b.size();\n            assert(n == m);\n     \
    \       transform(a), transform(b);\n            for (std::size_t i = 0; i < n;\
    \ ++i) a[i] = mul(a[i], b[i]);\n            inv_transform(a);\n            return\
    \ a;\n        }\n        template <typename T, auto transform, auto inv_transform,\
    \ auto mul = default_operator::mul<T>>\n        std::vector<T> transform_convolution(std::vector<std::vector<T>>\
    \ a) {\n            const std::size_t num = a.size();\n            assert(num);\n\
    \            const std::size_t n = a[0].size();\n            for (auto &v : a)\
    \ {\n                assert(n == int(v.size()));\n                transform(v);\n\
    \            }\n            auto &res = a[0];\n            for (int i = 1; i <\
    \ num; ++i) {\n                for (int j = 0; j < n; ++j) res[j] = mul(res[j],\
    \ a[i][j]);\n            }\n            inv_transform(res);\n            return\
    \ res;\n        }\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/convolution/convolution.hpp
  requiredBy:
  - library/convolution/xor_convolution.hpp
  - library/convolution/lcm_convolution.hpp
  - library/convolution/and_convolution.hpp
  - library/convolution/or_convolution.hpp
  - library/convolution/gcd_convolution.hpp
  timestamp: '2022-01-31 13:34:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/gcd_convolution/lcms.test.cpp
  - test/src/convolution/gcd_convolution/gcd_convolution.test.cpp
  - test/src/convolution/and_convolution/and_convolution.test.cpp
  - test/src/convolution/lcm_convolution/lcm_convolution.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
documentation_of: library/convolution/convolution.hpp
layout: document
title: Convolution
---

### transform_convolution

- シグネチャ

  ```cpp
  template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
  std::vector<T> transform_convolution(std::vector<T> a, std::vector<T> b) // (1)
  template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
  std::vector<T> transform_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \oplus j = k } A _ i \cdot B _ j $$

  ここで，$\oplus$ は $\mathbb{Z}$ 上の二項演算です．
  
  この関数は $\odot$ を列の各点積を取る演算として，$\mathcal{F}[A]\odot \mathcal{F}[B]=\mathcal{F}[C]$ を満たす変換行列 $\mathcal{F}$ とその逆行列 $\mathcal{F}^{-1}$ が存在することが必要であり，この条件の下で $C=\mathcal{F}^{-1}\left[\mathcal{F}[A]\odot \mathcal{F}[B]\right]$ として畳み込みを計算します．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を作用させる関数
  - `transform_inv`: 列に対して inplace に線形変換 $\mathcal{F}^{-1}$ を作用させる関数
  - `mul`: 各点積 $\odot$ を計算するための `T` 上の乗算．デフォルトでは `operator*` が呼ばれるようになっています．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 時間計算量

  `transform` の計算量を $\Theta(f(N))$, `transform_inv` の計算量を $\Theta(g(N))$ として

  1. $\Theta(f(N)+g(N))$
  2. 列の数を $K$ として，$\Theta(K\cdot(f(N)+g(N)))$
