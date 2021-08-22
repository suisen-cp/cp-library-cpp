---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/supset.hpp
    title: "\u4E0A\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/and_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/supset.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace suisen::internal::arithmetic_operator {}\n\nnamespace suisen {\nnamespace\
    \ supset_transform {\nnamespace internal {\ntemplate <typename T, typename AssignOp>\n\
    void transform(std::vector<T> &f, AssignOp assign_op) {\n    const int n = f.size();\n\
    \    assert((-n & n) == n);\n    for (int k = 1; k < n; k <<= 1) {\n        for\
    \ (int l = 0; l < n; l += 2 * k) {\n            int m = l + k;\n            for\
    \ (int p = 0; p < k; ++p) assign_op(f[l + p], f[m + p]);\n        }\n    }\n}\n\
    } // namespace internal\n\nusing namespace suisen::internal::arithmetic_operator;\n\
    \ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign\
    \ add_assign) {\n    internal::transform(f, add_assign);\n}\ntemplate <typename\
    \ T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    internal::transform(f, sub_assign);\n}\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    internal::transform(f, [](T &a, const T &b) { a += b; });\n}\ntemplate\
    \ <typename T>\nvoid mobius(std::vector<T> &f) {\n    internal::transform(f, [](T\
    \ &a, const T &b) { a -= b; });\n}\n\n} // namespace supset_transform\n\ntemplate\
    \ <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign\
    \ sub_assign>\nstruct SupsetTransformGeneral {\n    static void transform(std::vector<T>\
    \ &a) {\n        supset_transform::zeta(a, add_assign);\n    }\n    static void\
    \ inverse_transform(std::vector<T> &a) {\n        supset_transform::mobius(a,\
    \ sub_assign);\n    }\n};\n\ntemplate <typename T>\nstruct SupsetTransform {\n\
    \    static void transform(std::vector<T> &a) {\n        supset_transform::zeta(a);\n\
    \    }\n    static void inverse_transform(std::vector<T> &a) {\n        supset_transform::mobius(a);\n\
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
    \        return res;\n    }\n};\n\n} // namespace suisen\n\n\n\n#line 6 \"library/convolution/and_convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing AndConvolution = Convolution<T,\
    \ SupsetTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> and_convolution(Args\
    \ &&...args) {\n    return AndConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_AND_CONVOLUTION\n#define SUISEN_AND_CONVOLUTION\n\n#include\
    \ \"library/transform/supset.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing AndConvolution = Convolution<T,\
    \ SupsetTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> and_convolution(Args\
    \ &&...args) {\n    return AndConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_AND_CONVOLUTION\n"
  dependsOn:
  - library/transform/supset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/and_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-13 19:00:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/and_convolution/and_convolution.test.cpp
documentation_of: library/convolution/and_convolution.hpp
layout: document
title: Bitwise And Convolution
---

### and_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> and_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> and_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字 bitwise and で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \And j = k } A _ i \cdot B _ j $$

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

  1. $\Theta(N\log N)$，あるいは $\Theta(L\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N\log N)$，あるいは $\Theta(K\cdot L\cdot 2^L)$