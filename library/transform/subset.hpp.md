---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':x:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  - icon: ':x:'
    path: library/math/sps.hpp
    title: library/math/sps.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':x:'
    path: test/src/math/sps/connectivity2.test.cpp
    title: test/src/math/sps/connectivity2.test.cpp
  - icon: ':x:'
    path: test/src/math/sps/lights_out_on_connected_graph.test.cpp
    title: test/src/math/sps/lights_out_on_connected_graph.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/subset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen::internal::arithmetic_operator {}\n\nnamespace\
    \ suisen {\nnamespace subset_transform {\nnamespace internal {\ntemplate <typename\
    \ T, typename AssignOp>\nvoid transform(std::vector<T> &f, AssignOp assign_op)\
    \ {\n    const int n = f.size();\n    assert((-n & n) == n);\n    for (int k =\
    \ 1; k < n; k <<= 1) {\n        for (int l = 0; l < n; l += 2 * k) {\n       \
    \     int m = l + k;\n            for (int p = 0; p < k; ++p) assign_op(f[m +\
    \ p], f[l + p]);\n        }\n    }\n}\n} // namespace internal\n\nusing namespace\
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
    \    }\n};\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SUBSET_TRANSFORM\n#define SUISEN_SUBSET_TRANSFORM\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen::internal::arithmetic_operator\
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
    \    }\n};\n\n} // namespace suisen\n\n\n#endif // SUISEN_SUBSET_TRANSFORM"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/subset.hpp
  requiredBy:
  - library/math/sps.hpp
  - library/convolution/or_convolution.hpp
  - library/convolution/subset_convolution.hpp
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/transform/subset.hpp
layout: document
title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\u30BF\
  \u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
---

### struct SubsetTransform

- シグネチャ

  ```cpp
  template <typename T>
  struct SubsetTransform {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に下位集合版のゼータ変換を施す関数 `SubsetTransform<T>::transform` およびその逆変換 (メビウス変換) を施す関数 `SubsetTransform<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  ゼータ変換 (`SubsetTransform<T>::transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{j\subseteq i} A_j $$
  
  メビウス変換 (`SubsetTransform<T>::inverse_transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{j\subseteq i} B_j $$

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=` が定義されている必要があります．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$

### struct SubsetTransformGeneral

- シグネチャ

  ```cpp
  template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
  struct SubsetTransformGeneral {
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
