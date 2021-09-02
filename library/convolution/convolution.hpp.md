---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/gcd_convolution.hpp
    title: GCD Convolution
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':question:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  - icon: ':question:'
    path: library/math/sps.hpp
    title: library/math/sps.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - icon: ':x:'
    path: test/src/math/sps/connectivity2.test.cpp
    title: test/src/math/sps/connectivity2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
    title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\nnamespace internal::arithmetic_operator {}\ntemplate <typename\
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
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION\n#define SUISEN_CONVOLUTION\n\n#include <vector>\n\
    \nnamespace suisen {\nnamespace internal::arithmetic_operator {}\ntemplate <typename\
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
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/convolution.hpp
  requiredBy:
  - library/convolution/gcd_convolution.hpp
  - library/convolution/or_convolution.hpp
  - library/convolution/subset_convolution.hpp
  - library/convolution/xor_convolution.hpp
  - library/convolution/and_convolution.hpp
  - library/math/sps.hpp
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/and_convolution/and_convolution.test.cpp
  - test/src/convolution/gcd_convolution/lcms.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
documentation_of: library/convolution/convolution.hpp
layout: document
title: Convolution
---

### convolution

- シグネチャ

  ```cpp
  template <typename T, template <typename> class Transform>
  struct Convolution {
      std::vector<T> convolution(std::vector<T> a, std::vector<T> b) // (1)
      std::vector<T> convolution(std::vector<std::vector<T>> a) // (2)
  }
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \oplus j = k } A _ i \cdot B _ j $$

  ここで，$\oplus$ は $\mathbb{Z}$ 上の二項演算です．
  
  $\odot$ を列の各点積を取る演算として，$\mathcal{F}[A]\odot \mathcal{F}[B]=\mathcal{F}[C]$ を満たす変換行列 $\mathcal{F}$ とその逆変換 $\mathcal{F}^{-1}$ を計算する静的関数を持つ `Transform` クラスをテンプレート引数に取ります．

  ここでは，上記の $\mathcal{F}$ および $\mathcal{F}^{-1}$ を用いて $C$ を次のように計算します．

  $$\mathcal{F}^{-1}\left[\mathcal{F}[A]\odot \mathcal{F}[B]\right]=C$$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator*=` が定義されている必要があります．
  - `Transform`: 列に対して inplace に変換行列 $\mathcal{F}$ を施す `static` 関数 `Transform<T>::transform(std::vector<T>&)` およびその逆変換 $\mathcal{F}^{-1}$ を施す `static` 関数 `Transform<T>::inverse_transform(std::vector<T>&)` を持つクラスです．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 時間計算量

  ここでは，`Transform<T>::transform` の計算量を $\Theta(f(N))$, `Transform<T>::inverse_transform` の計算量を $\Theta(g(N))$ とします．

  1. $\Theta(f(N)+g(N))$
  2. 列の数を $K$ として，$\Theta(K\cdot(f(N)+g(N)))$
