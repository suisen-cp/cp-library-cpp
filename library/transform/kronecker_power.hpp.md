---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/default_operator.hpp
    title: library/util/default_operator.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: "\u4E0B\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/transform/supset.hpp
    title: "\u4E0A\u4F4D\u96C6\u5408\u306B\u5BFE\u3059\u308B\u9AD8\u901F\u30BC\u30FC\
      \u30BF\u5909\u63DB\u30FB\u9AD8\u901F\u30E1\u30D3\u30A6\u30B9\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/transform/walsh_hadamard.hpp
    title: "Walsh Hadamard \u5909\u63DB"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
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
  bundledCode: "#line 1 \"library/transform/kronecker_power.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\n#line 1 \"library/util/default_operator.hpp\"\
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
    } // namespace suisen\n\n\n#line 8 \"library/transform/kronecker_power.hpp\"\n\
    \nnamespace suisen {\n    namespace kronecker_power_transform {\n        namespace\
    \ internal {\n            template <typename UnitTransform, typename ReferenceGetter,\
    \ std::size_t... Seq>\n            void unit_transform(UnitTransform transform,\
    \ ReferenceGetter ref_getter, std::index_sequence<Seq...>) {\n               \
    \ transform(ref_getter(Seq)...);\n            }\n        }\n\n        template\
    \ <typename T, std::size_t D, auto unit_transform>\n        void kronecker_power_transform(std::vector<T>\
    \ &x) {\n            const std::size_t n = x.size();\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_KRONECKER_POWER\n#define SUISEN_KRONECKER_POWER\n\n#include\
    \ <cassert>\n#include <vector>\n\n#include \"library/util/default_operator.hpp\"\
    \n\nnamespace suisen {\n    namespace kronecker_power_transform {\n        namespace\
    \ internal {\n            template <typename UnitTransform, typename ReferenceGetter,\
    \ std::size_t... Seq>\n            void unit_transform(UnitTransform transform,\
    \ ReferenceGetter ref_getter, std::index_sequence<Seq...>) {\n               \
    \ transform(ref_getter(Seq)...);\n            }\n        }\n\n        template\
    \ <typename T, std::size_t D, auto unit_transform>\n        void kronecker_power_transform(std::vector<T>\
    \ &x) {\n            const std::size_t n = x.size();\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        const auto ref_getter = [&](std::size_t\
    \ i) -> T& { return x[offset + i * block]; };\n                        internal::unit_transform(unit_transform,\
    \ ref_getter, std::make_index_sequence<D>());\n                    }\n       \
    \         }\n            }\n        }\n\n        template <typename T, typename\
    \ UnitTransform>\n        void kronecker_power_transform(std::vector<T> &x, const\
    \ std::size_t D, UnitTransform unit_transform) {\n            const std::size_t\
    \ n = x.size();\n            std::vector<T> work(D);\n            for (std::size_t\
    \ block = 1; block < n; block *= D) {\n                for (std::size_t l = 0;\
    \ l < n; l += D * block) {\n                    for (std::size_t offset = l; offset\
    \ < l + block; ++offset) {\n                        for (std::size_t i = 0; i\
    \ < D; ++i) work[i] = x[offset + i * block];\n                        unit_transform(work);\n\
    \                        for (std::size_t i = 0; i < D; ++i) x[offset + i * block]\
    \ = work[i];\n                    }\n                }\n            }\n      \
    \  }\n\n        template <typename T, auto e = default_operator::zero<T>, auto\
    \ add = default_operator::add<T>, auto mul = default_operator::mul<T>>\n     \
    \   auto kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>>\
    \ &A) -> decltype(e(), add(std::declval<T>(), std::declval<T>()), mul(std::declval<T>(),\
    \ std::declval<T>()), void()) {\n            const std::size_t D = A.size();\n\
    \            assert(D == A[0].size());\n            auto unit_transform = [&](std::vector<T>\
    \ &x) {\n                std::vector<T> y(D, e());\n                for (std::size_t\
    \ i = 0; i < D; ++i) for (std::size_t j = 0; j < D; ++j) {\n                 \
    \   y[i] = add(y[i], mul(A[i][j], x[j]));\n                }\n               \
    \ x.swap(y);\n            };\n            kronecker_power_transform<T>(x, D, unit_transform);\n\
    \        }\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_KRONECKER_POWER\n"
  dependsOn:
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/transform/kronecker_power.hpp
  requiredBy:
  - library/transform/subset.hpp
  - library/transform/walsh_hadamard.hpp
  - library/transform/supset.hpp
  - library/convolution/xor_convolution.hpp
  - library/convolution/and_convolution.hpp
  - library/convolution/or_convolution.hpp
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/convolution/and_convolution/and_convolution.test.cpp
documentation_of: library/transform/kronecker_power.hpp
layout: document
title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\u5909\
  \u63DB (\u4EEE\u79F0)"
---

### kronecker_power_transform

- シグネチャ

  ```cpp
  template <typename T, std::size_t D, auto unit_transform>
  void kronecker_power_transform(std::vector<T> &x) // (1)

  template <typename T, typename UnitTransform>
  void kronecker_power_transform(std::vector<T> &x, const std::size_t D, UnitTransform unit_transform) // (2)

  template <typename T, auto e = default_operator::zero<T>, auto add = default_operator::add<T>, auto mul = default_operator::mul<T>>
  void kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>> &A) // (3)
  ```

- 概要

  $D \times D$ 行列 $A$ のクロネッカー積における $N$ 乗 $A ^ {\otimes N}$ と $D ^ N$ 次元ベクトル $x$ の積を inplace に $\Theta ( N \cdot D ^ N )$ 時間で計算する。

  ゼータ変換・メビウス変換・アダマール変換らはこの具体例であり、以下のように対応付けられる。

  - 上位集合版のゼータ変換
  
    $D=2,A=\begin{pmatrix} 1 & 1 \\\\ 0 & 1 \end{pmatrix}$
  
  - 上位集合版のメビウス変換

    $D=2,A=\begin{pmatrix} 1 & -1 \\\\ 0 & 1 \end{pmatrix}$

  - 下位集合版のゼータ変換
  
    $D=2,A=\begin{pmatrix} 1 & 0 \\\\ 1 & 1 \end{pmatrix}$

  - 下位集合版のメビウス変換

    $D=2,A=\begin{pmatrix} 1 & 0 \\\\ -1 & 1 \end{pmatrix}$

  - アダマール変換

    $D=2,A=\begin{pmatrix} 1 & 1 \\\\ 1 & -1 \end{pmatrix}$

  これらは全て $D=2$ の例であるが、例えば $3$ 進ゼータ変換は $D=3,A=\begin{pmatrix} 1 & 0 & 0 \\\\ 1 & 1 & 0 \\\\ 1 & 1 & 1 \end{pmatrix}$、メビウス変換は $D=3,A=\begin{pmatrix} 1 & 0 & 0 \\\\ -1 & 1 & 0 \\\\ 0 & -1 & 1 \end{pmatrix}$ となる (はず)。

- 使い方

  1. $D$ の値がコンパイル時に分かっている場合はこれを用いるのがパフォーマンス的に最適 (なはず)。テンプレート引数 `unit_transform` は引数に $x _ 1,\ldots, x _ D$ を $A x$ に置き換える関数である。具体的には、$D$ 個の参照 `T &x1, ..., T &xD` を引数に取る関数で、各 $i = 1, \ldots, D$ に対して $x_i \leftarrow (Ax)_i$ という代入が行われなければならない。返り値は捨てられる。
  2. $D$ の値がコンパイル時に分からない場合であって、行列積をそのまま計算すると無駄が多い場合はこれを用いる。`unit_transform` はサイズ `D` の `vector<T> &` を受け取り、1 と同様に中身を $Ax$ で置き換える必要がある。
  3. $D$ の値がコンパイル時に分からない場合であって、行列をそのまま与えてしまいたい場合はこれを用いる。加算や乗算、加法単位元をテンプレート引数に渡すことができる。デフォルトでは加算は `operator+`、乗算は `operator*`、加法単位元は `T{0}` として扱われる。

- 返り値

  1, 2, 3 ともに無し。変換は inplace に行われる。

- 制約

  - 引数 `x` のサイズ $L$ に対してある非負整数 $N$ が存在して $L=D^N$ を満たす。

- 時間計算量

  $\Theta(N\cdot D ^ N)$
