---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/math/sps.hpp
    title: Sps
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/abc236_h.test.cpp
    title: test/src/math/sps/abc236_h.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/connectivity2.test.cpp
    title: test/src/math/sps/connectivity2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
    title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/subset_convolution.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    namespace internal::subset_convolution {\n\
    \        template <typename T>\n        std::vector<T>& addeq(std::vector<T> &a,\
    \ const std::vector<T> &b) {\n            const int n = a.size();\n          \
    \  for (int i = 0; i < n; ++i) a[i] += b[i];\n            return a;\n        }\n\
    \        template <typename T>\n        std::vector<T>& subeq(std::vector<T> &a,\
    \ const std::vector<T> &b) {\n            const int n = a.size();\n          \
    \  for (int i = 0; i < n; ++i) a[i] -= b[i];\n            return a;\n        }\n\
    \        template <typename T>\n        std::vector<T>& muleq(std::vector<T> &a,\
    \ const std::vector<T> &b) {\n            const int n = a.size();\n          \
    \  for (int i = n - 1; i >= 0; --i) {\n                for (int j = n - 1 - i;\
    \ j > 0; --j) a[i + j] += a[i] * b[j];\n                a[i] *= b[0];\n      \
    \      }\n            return a;\n        }\n        template <typename T>\n  \
    \      std::vector<T> add(const std::vector<T> &a, const std::vector<T> &b) {\n\
    \            std::vector<T> c = a;\n            return addeq(c, b);\n        }\n\
    \        template <typename T>\n        std::vector<T> sub(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            std::vector<T> c = a;\n        \
    \    return subeq(c, b);\n        }\n        template <typename T>\n        std::vector<T>\
    \ mul(const std::vector<T> &a, const std::vector<T> &b) {\n            std::vector<T>\
    \ c = a;\n            return muleq(c, b);\n        }\n\n        template <typename\
    \ T>\n        std::vector<std::vector<T>> ranked(const std::vector<T> &a) {\n\
    \            const int n = a.size();\n            assert((-n & n) == n);\n   \
    \         std::vector fs(n, std::vector(__builtin_ctz(n) + 1, T(0)));\n      \
    \      for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];\n    \
    \        return fs;\n        }\n        template <typename T>\n        std::vector<T>\
    \ deranked(const std::vector<std::vector<T>> &polys) {\n            const int\
    \ n = polys.size();\n            assert((-n & n) == n);\n            std::vector<T>\
    \ a(n);\n            for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \            return a;\n        }\n\n        template <typename T>\n        std::vector<std::vector<T>>\
    \ ranked_zeta(const std::vector<T> &a) {\n            std::vector<std::vector<T>>\
    \ ranked_a = ranked<T>(a);\n            const int n = ranked_a.size();\n     \
    \       for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for\
    \ (int i = l; i < l + k; ++i) {\n                addeq(ranked_a[i + k], ranked_a[i]);\n\
    \            }\n            return ranked_a;\n        }\n        template <typename\
    \ T>\n        std::vector<T> deranked_mobius(std::vector<std::vector<T>> &ranked_a)\
    \ {\n            const int n = ranked_a.size();\n            for (int k = 1; k\
    \ < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i)\
    \ {\n                subeq(ranked_a[i + k], ranked_a[i]);\n            }\n   \
    \         return deranked<T>(ranked_a);\n        }\n    } // internal::subset_convolution\n\
    \n    template <typename T>\n    std::vector<T> subset_convolution(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n        using namespace internal::subset_convolution;\n\
    \        const int n = a.size();\n        auto ranked_a = ranked_zeta(a), ranked_b\
    \ = ranked_zeta(b);\n        for (int i = 0; i < n; ++i) muleq(ranked_a[i], ranked_b[i]);\n\
    \        return deranked_mobius(ranked_a);\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_CONVOLUTION\n#define SUISEN_SUBSET_CONVOLUTION\n\n\
    #include <vector>\n\nnamespace suisen {\n    namespace internal::subset_convolution\
    \ {\n        template <typename T>\n        std::vector<T>& addeq(std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            const int n = a.size();\n      \
    \      for (int i = 0; i < n; ++i) a[i] += b[i];\n            return a;\n    \
    \    }\n        template <typename T>\n        std::vector<T>& subeq(std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            const int n = a.size();\n      \
    \      for (int i = 0; i < n; ++i) a[i] -= b[i];\n            return a;\n    \
    \    }\n        template <typename T>\n        std::vector<T>& muleq(std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            const int n = a.size();\n      \
    \      for (int i = n - 1; i >= 0; --i) {\n                for (int j = n - 1\
    \ - i; j > 0; --j) a[i + j] += a[i] * b[j];\n                a[i] *= b[0];\n \
    \           }\n            return a;\n        }\n        template <typename T>\n\
    \        std::vector<T> add(const std::vector<T> &a, const std::vector<T> &b)\
    \ {\n            std::vector<T> c = a;\n            return addeq(c, b);\n    \
    \    }\n        template <typename T>\n        std::vector<T> sub(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n            std::vector<T> c = a;\n        \
    \    return subeq(c, b);\n        }\n        template <typename T>\n        std::vector<T>\
    \ mul(const std::vector<T> &a, const std::vector<T> &b) {\n            std::vector<T>\
    \ c = a;\n            return muleq(c, b);\n        }\n\n        template <typename\
    \ T>\n        std::vector<std::vector<T>> ranked(const std::vector<T> &a) {\n\
    \            const int n = a.size();\n            assert((-n & n) == n);\n   \
    \         std::vector fs(n, std::vector(__builtin_ctz(n) + 1, T(0)));\n      \
    \      for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] = a[i];\n    \
    \        return fs;\n        }\n        template <typename T>\n        std::vector<T>\
    \ deranked(const std::vector<std::vector<T>> &polys) {\n            const int\
    \ n = polys.size();\n            assert((-n & n) == n);\n            std::vector<T>\
    \ a(n);\n            for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \            return a;\n        }\n\n        template <typename T>\n        std::vector<std::vector<T>>\
    \ ranked_zeta(const std::vector<T> &a) {\n            std::vector<std::vector<T>>\
    \ ranked_a = ranked<T>(a);\n            const int n = ranked_a.size();\n     \
    \       for (int k = 1; k < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for\
    \ (int i = l; i < l + k; ++i) {\n                addeq(ranked_a[i + k], ranked_a[i]);\n\
    \            }\n            return ranked_a;\n        }\n        template <typename\
    \ T>\n        std::vector<T> deranked_mobius(std::vector<std::vector<T>> &ranked_a)\
    \ {\n            const int n = ranked_a.size();\n            for (int k = 1; k\
    \ < n; k *= 2) for (int l = 0; l < n; l += 2 * k) for (int i = l; i < l + k; ++i)\
    \ {\n                subeq(ranked_a[i + k], ranked_a[i]);\n            }\n   \
    \         return deranked<T>(ranked_a);\n        }\n    } // internal::subset_convolution\n\
    \n    template <typename T>\n    std::vector<T> subset_convolution(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n        using namespace internal::subset_convolution;\n\
    \        const int n = a.size();\n        auto ranked_a = ranked_zeta(a), ranked_b\
    \ = ranked_zeta(b);\n        for (int i = 0; i < n; ++i) muleq(ranked_a[i], ranked_b[i]);\n\
    \        return deranked_mobius(ranked_a);\n    }\n} // namespace suisen\n\n#endif\
    \ // SUISEN_SUBSET_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/subset_convolution.hpp
  requiredBy:
  - library/math/sps.hpp
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sps/abc236_h.test.cpp
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/convolution/subset_convolution.hpp
layout: document
title: Subset Convolution
---

### subset_convolution

__TODO__: 抽象化

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の直和演算で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \sqcup j = k } A _ i \cdot B _ j $$

  ここで，$i\sqcup j=k$ は $i\And j=0$ かつ $i\mid j=k$ と等価です．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=`，`operator*` が定義されている必要があります．

- 返り値
  
  $A\ast B$

- 制約

  - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N(\log N)^2)$，あるいは $\Theta(L^2\cdot 2^L)$
