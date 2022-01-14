---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/polynomial_eval.hpp\"\n\n\n\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 7 \"library/convolution/polynomial_eval.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, auto transform, auto transform_inv,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\n  \
    \  std::vector<T> polynomial_eval(std::vector<T> &&a, F f) {\n        transform(a);\n\
    \        for (auto &x : a) x = f(x);\n        transform_inv(a);\n        return\
    \ a;\n    }\n\n    template <typename T, auto transform, auto transform_inv, typename\
    \ F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\n    std::vector<T>\
    \ polynomial_eval(const std::vector<T> &a, F f) {\n        return polynomial_eval<T,\
    \ transform, transform_inv>(std::vector<T>(a), f);\n    }\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL\n#define SUISEN_APPLY_POLYNOMIAL\n\n#include\
    \ <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename T, auto transform, auto transform_inv, typename F,\
    \ constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\n    std::vector<T>\
    \ polynomial_eval(std::vector<T> &&a, F f) {\n        transform(a);\n        for\
    \ (auto &x : a) x = f(x);\n        transform_inv(a);\n        return a;\n    }\n\
    \n    template <typename T, auto transform, auto transform_inv, typename F, constraints_t<is_same_as_invoke_result<T,\
    \ F, T>> = nullptr>\n    std::vector<T> polynomial_eval(const std::vector<T> &a,\
    \ F f) {\n        return polynomial_eval<T, transform, transform_inv>(std::vector<T>(a),\
    \ f);\n    }\n} // namespace suisen\n\n#endif // SUISEN_APPLY_POLYNOMIAL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/convolution/polynomial_eval.hpp
  requiredBy: []
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/polynomial_eval/nim_counting.test.cpp
documentation_of: library/convolution/polynomial_eval.hpp
layout: document
title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\u306E\
  \u8A55\u4FA1"
---

### polynomial_eval

- シグネチャ

  ```cpp
  template <typename T, auto transform, auto transform_inv, typename F>
  std::vector<T> polynomial_eval(std::vector<T> &&a, F f) // (1)

  template <typename T, auto transform, auto transform_inv, typename F>
  std::vector<T> polynomial_eval(const std::vector<T> &a, F f) // (2)
  ```

- 概要

  列 $A$ を変数に持つ多項式 $\displaystyle f(A)=\sum_{i=0}^{M-1} C_i \cdot A^i$ を評価します．ここで，$A^i$ はある畳み込み演算 $\ast$ に対して以下で定義されるものとします．

  $$ A^i = \underbrace{A \ast A \ast \cdots \ast A}_{i} $$

  また，$\ast$ に対してある正則な変換行列 $\mathcal{F}$ が存在して，任意の列 $X,Y$ に対して

  $$ \mathcal{F}[X] \odot \mathcal{F}[Y]=\mathcal{F}[X\ast Y]$$

  を満たす必要があります．ここで，$\odot$ は各点積をとる演算です．このとき，$f(A)$ は次のように計算されます．

  $$\begin{aligned}
  f(A)
  &=\mathcal{F}^{-1}\left[\sum_{i=0}^{M-1}C_i\cdot \left(\underbrace{\mathcal{F}[A]\odot\cdots\odot\mathcal{F}[A]}_{i}\right)\right]\\
  &=\mathcal{F}^{-1}\left[\begin{pmatrix}
  f(\mathcal{F}[A]_0)\\
  f(\mathcal{F}[A]_1)\\
  \vdots\\
  f(\mathcal{F}[A]_{\vert A\vert-1})\\
  \end{pmatrix}\right]
  \end{aligned}$$

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `transform` および `transform_inv` であり，$f(\cdot)$ を評価するのが引数 `f` です．

- テンプレート引数

  - `T`: 列の要素の型．
  - `transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を施す関数
  - `transform_inv`: 逆変換 $\mathcal{F}^{-1}$ を施す関数
  - `F`: `T` 型の要素 $x$ に対して $\displaystyle f(x)=\sum_{i=0}^{N-1}C_i \cdot x^i$ を計算する関数の型です．`F` 型のインスタンス `f` は `x` を引数に取る関数呼び出し `f(x)` によって $f(x)$ を計算できなければなりません．

- 引数

  - `a`: 列 $A$
  - `f`: $f(x)$ を評価する関数

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`transform` の計算量を $\Theta(f(N))$, `transform_inv` の計算量を $\Theta(g(N))$，`f` の計算量を $O(h(M))$ として，$\Theta(f(N)+g(N)+N\cdot h(M))$ です．

<!--

- テンプレート引数 `Transform` について

  典型的な畳み込み演算に対応する `Transform` の例を挙げます．

  1. bitwise and convolution

      [上位集合に対する高速ゼータ変換・高速メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/supset.hpp)
  2. bitwise or convolution

      [下位集合に対する高速ゼータ変換・高速メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/subset.hpp)
  3. bitwise xor convolution

      [Walsh Hadamard 変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/walsh_hadamard.hpp)
  4. gcd convolution

      [倍数系ゼータ変換・メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/multiple.hpp)
  5. lcm convolution

      [約数系ゼータ変換・メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/divisor.hpp)

-->
