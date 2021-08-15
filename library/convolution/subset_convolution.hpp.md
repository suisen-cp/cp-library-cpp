---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/math/sps.hpp
    title: library/math/sps.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
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
  bundledCode: "#line 1 \"library/convolution/subset_convolution.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen::internal::arithmetic_operator {\ntemplate <typename\
    \ T>\nvoid operator+=(std::vector<T> &a, const std::vector<T> &b) {\n    int n\
    \ = b.size();\n    for (int i = 0; i < n; ++i) a[i] += b[i];\n}\ntemplate <typename\
    \ T>\nvoid operator-=(std::vector<T> &a, const std::vector<T> &b) {\n    int n\
    \ = b.size();\n    for (int i = 0; i < n; ++i) a[i] -= b[i];\n}\ntemplate <typename\
    \ T>\nvoid operator*=(std::vector<T> &a, const std::vector<T> &b) {\n    int n\
    \ = b.size();\n    for (int i = n - 1; i >= 0; --i) {\n        for (int j = n\
    \ - i - 1; j > 0; --j) a[i + j] += a[i] * b[j];\n        a[i] *= b[0];\n    }\n\
    }\n}\n\n#line 1 \"library/transform/subset.hpp\"\n\n\n\n#include <cassert>\n#line\
    \ 6 \"library/transform/subset.hpp\"\n\nnamespace suisen::internal::arithmetic_operator\
    \ {}\n\nnamespace suisen {\nnamespace subset_transform {\nnamespace internal {\n\
    template <typename T, typename AssignOp>\nvoid transform(std::vector<T> &f, AssignOp\
    \ assign_op) {\n    const int n = f.size();\n    assert((-n & n) == n);\n    for\
    \ (int k = 1; k < n; k <<= 1) {\n        for (int l = 0; l < n; l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) assign_op(f[m\
    \ + p], f[l + p]);\n        }\n    }\n}\n} // namespace internal\n\nusing namespace\
    \ suisen::internal::arithmetic_operator;\n\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    internal::transform(f,\
    \ add_assign);\n}\ntemplate <typename T, typename SubAssign>\nvoid mobius(std::vector<T>\
    \ &f, SubAssign sub_assign) {\n    internal::transform(f, sub_assign);\n}\ntemplate\
    \ <typename T>\nvoid zeta(std::vector<T> &f) {\n    zeta(f, [](T &a, const T &b)\
    \ { a += b; });\n}\ntemplate <typename T>\nvoid mobius(std::vector<T> &f) {\n\
    \    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace subset_transform\n\
    \ntemplate <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign,\
    \ SubAssign sub_assign>\nstruct SubsetTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct SubsetTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        subset_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        subset_transform::mobius(a);\n\
    \    }\n};\n\n} // namespace suisen\n\n\n\n#line 1 \"library/convolution/convolution.hpp\"\
    \n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\n\nnamespace suisen {\n\
    namespace internal::arithmetic_operator {}\ntemplate <typename T, template <typename>\
    \ class Transform>\nstruct Convolution {\n    static std::vector<T> convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        using namespace internal::arithmetic_operator;\n\
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
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n#line 29 \"library/convolution/subset_convolution.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal::subset_convolution {\ntemplate <typename\
    \ T, typename Container>\nauto add_rank(const Container &a) {\n    int n = a.size();\n\
    \    assert((-n & n) == n);\n    std::vector<std::vector<T>> fs(n, std::vector<T>(__builtin_ctz(n)\
    \ + 1, T(0)));\n    for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] =\
    \ a[i];\n    return fs;\n}\ntemplate <typename T>\nauto remove_rank(const std::vector<std::vector<T>>\
    \ &polys) {\n    int n = polys.size();\n    assert((-n & n) == n);\n    std::vector<T>\
    \ a(n);\n    for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \    return a;\n}\n} // namespace internal\n\ntemplate <typename T>\nusing SubsetConvolution\
    \ = Convolution<std::vector<T>, SubsetTransform>;\n\ntemplate <typename T, typename\
    \ ...Args>\nstd::vector<T> subset_convolution(Args &&...args) {\n    using namespace\
    \ internal::subset_convolution;\n    return remove_rank<T>(SubsetConvolution<T>::convolution(add_rank<T>(args)...));\n\
    }\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SUBSET_CONVOLUTION\n#define SUISEN_SUBSET_CONVOLUTION\n\n\
    #include <vector>\n\nnamespace suisen::internal::arithmetic_operator {\ntemplate\
    \ <typename T>\nvoid operator+=(std::vector<T> &a, const std::vector<T> &b) {\n\
    \    int n = b.size();\n    for (int i = 0; i < n; ++i) a[i] += b[i];\n}\ntemplate\
    \ <typename T>\nvoid operator-=(std::vector<T> &a, const std::vector<T> &b) {\n\
    \    int n = b.size();\n    for (int i = 0; i < n; ++i) a[i] -= b[i];\n}\ntemplate\
    \ <typename T>\nvoid operator*=(std::vector<T> &a, const std::vector<T> &b) {\n\
    \    int n = b.size();\n    for (int i = n - 1; i >= 0; --i) {\n        for (int\
    \ j = n - i - 1; j > 0; --j) a[i + j] += a[i] * b[j];\n        a[i] *= b[0];\n\
    \    }\n}\n}\n\n#include \"library/transform/subset.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal::subset_convolution {\ntemplate <typename\
    \ T, typename Container>\nauto add_rank(const Container &a) {\n    int n = a.size();\n\
    \    assert((-n & n) == n);\n    std::vector<std::vector<T>> fs(n, std::vector<T>(__builtin_ctz(n)\
    \ + 1, T(0)));\n    for (int i = 0; i < n; ++i) fs[i][__builtin_popcount(i)] =\
    \ a[i];\n    return fs;\n}\ntemplate <typename T>\nauto remove_rank(const std::vector<std::vector<T>>\
    \ &polys) {\n    int n = polys.size();\n    assert((-n & n) == n);\n    std::vector<T>\
    \ a(n);\n    for (int i = 0; i < n; ++i) a[i] = polys[i][__builtin_popcount(i)];\n\
    \    return a;\n}\n} // namespace internal\n\ntemplate <typename T>\nusing SubsetConvolution\
    \ = Convolution<std::vector<T>, SubsetTransform>;\n\ntemplate <typename T, typename\
    \ ...Args>\nstd::vector<T> subset_convolution(Args &&...args) {\n    using namespace\
    \ internal::subset_convolution;\n    return remove_rank<T>(SubsetConvolution<T>::convolution(add_rank<T>(args)...));\n\
    }\n\n} // namespace suisen\n\n#endif // SUISEN_SUBSET_CONVOLUTION\n"
  dependsOn:
  - library/transform/subset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/subset_convolution.hpp
  requiredBy:
  - library/math/sps.hpp
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/convolution/subset_convolution.hpp
layout: document
title: Subset Convolution
---

### subset_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> subset_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の直和演算で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \sqcup j = k } A _ i \cdot B _ j $$

  ここで，$i\sqcup j=k$ は $i\And j=0$ かつ $i\mid j=k$ と等価です．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
     - $0\leq L\leq 20$
  2. - ある非負整数 $L$ が存在して $\vert\mathcal{A}^0\vert=\vert\mathcal{A}^1\vert=\cdots=2^L$ を満たす
     - $0\leq L\leq 20$

- 時間計算量

  1. $\Theta(N(\log N)^2)$，あるいは $\Theta(L^2\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N(\log N)^2)$，あるいは $\Theta(K\cdot L^2\cdot 2^L)$
