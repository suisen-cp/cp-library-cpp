---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/convolution/apply_polynomial/nim_counting.test.cpp
    title: test/src/convolution/apply_polynomial/nim_counting.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/apply_polynomial.hpp\"\n\n\n\n#include\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 7 \"\
    library/convolution/apply_polynomial.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, template <typename> class Transform, typename F, constraints_t<is_same_as_invoke_result<T,\
    \ F, T>> = nullptr>\nstd::vector<T> apply_polynomial(std::vector<T> &&a, F f)\
    \ {\n    Transform<T>::transform(a);\n    for (auto &x : a) x = f(x);\n    Transform<T>::inverse_transform(a);\n\
    \    return a;\n}\n\ntemplate <typename T, template <typename> class Transform,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(const std::vector<T> &a, F f) {\n    return apply_polynomial<T,\
    \ Transform>(std::vector<T>(a), f);\n}\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL\n#define SUISEN_APPLY_POLYNOMIAL\n\n#include\
    \ <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen\
    \ {\n\ntemplate <typename T, template <typename> class Transform, typename F,\
    \ constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(std::vector<T> &&a, F f) {\n    Transform<T>::transform(a);\n\
    \    for (auto &x : a) x = f(x);\n    Transform<T>::inverse_transform(a);\n  \
    \  return a;\n}\n\ntemplate <typename T, template <typename> class Transform,\
    \ typename F, constraints_t<is_same_as_invoke_result<T, F, T>> = nullptr>\nstd::vector<T>\
    \ apply_polynomial(const std::vector<T> &a, F f) {\n    return apply_polynomial<T,\
    \ Transform>(std::vector<T>(a), f);\n}\n\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_APPLY_POLYNOMIAL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/convolution/apply_polynomial.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/convolution/apply_polynomial/nim_counting.test.cpp
documentation_of: library/convolution/apply_polynomial.hpp
layout: document
title: "\u5217\u3092\u5909\u6570\u3068\u3057\u3066\u6301\u3064\u591A\u9805\u5F0F\u306E\
  \u8A55\u4FA1"
---

### apply_polynomial

- シグネチャ

  ```cpp
  template <typename T, template <typename> class Transform, typename F>
  std::vector<T> apply_polynomial(std::vector<T> &&a, F f) // (1)

  template <typename T, template <typename> class Transform, typename F>
  std::vector<T> apply_polynomial(const std::vector<T> &a, F f) // (2)
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

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `Transform` の静的メンバ関数 `Transform<T>::transform` と `Transform<T>::inverse_transform` で，$f(\cdot)$ を評価するのが引数 `f` です．

- テンプレート引数

  - `T`: 列の要素の型．
  - `Transform`: 列に対して inplace に線形写像 $\mathcal{F}$ を施す `static` 関数 `Transform<T>::transform(std::vector<T>&)` およびその逆変換 $\mathcal{F}^{-1}$ を施す `static` 関数 `Transform<T>::inverse_transform(std::vector<T>&)` を持つクラス．
  - `F`: `T` 型の要素 $x$ に対して $\displaystyle f(x)=\sum_{i=0}^{N-1}C_i \cdot x^i$ を計算する関数の型です．`F` 型のインスタンス `f` は `x` を引数に取る関数呼び出し `f(x)` によって $f(x)$ を計算できなければなりません．

- 引数

  - `a`: 列 $A$
  - `f`: $f(x)$ を評価する関数

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`Transform<T>::transform` の計算量を $\Theta(f(N))$, `Transform<T>::inverse_transform` の計算量を $\Theta(g(N))$，`f` の計算量を $O(h(M))$ として，$\Theta(f(N)+g(N)+N\cdot h(M))$ です．

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
