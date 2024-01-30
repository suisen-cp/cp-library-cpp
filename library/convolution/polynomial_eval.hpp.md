---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
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
    \ <limits>\n#include <iostream>\n#include <type_traits>\n\nnamespace suisen {\n\
    \    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 7 \"library/convolution/polynomial_eval.hpp\"\n\
    \nnamespace suisen {\n    template <typename T, auto transform, auto transform_inv,\
    \ typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n    std::vector<T>\
    \ polynomial_eval(std::vector<T> &&a, F f) {\n        transform(a);\n        for\
    \ (auto &x : a) x = f(x);\n        transform_inv(a);\n        return a;\n    }\n\
    \n    template <typename T, auto transform, auto transform_inv, typename F, constraints_t<std::is_invocable_r<T,\
    \ F, T>> = nullptr>\n    std::vector<T> polynomial_eval(const std::vector<T> &a,\
    \ F f) {\n        return polynomial_eval<T, transform, transform_inv>(std::vector<T>(a),\
    \ f);\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_APPLY_POLYNOMIAL\n#define SUISEN_APPLY_POLYNOMIAL\n\n#include\
    \ <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename T, auto transform, auto transform_inv, typename F,\
    \ constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n    std::vector<T> polynomial_eval(std::vector<T>\
    \ &&a, F f) {\n        transform(a);\n        for (auto &x : a) x = f(x);\n  \
    \      transform_inv(a);\n        return a;\n    }\n\n    template <typename T,\
    \ auto transform, auto transform_inv, typename F, constraints_t<std::is_invocable_r<T,\
    \ F, T>> = nullptr>\n    std::vector<T> polynomial_eval(const std::vector<T> &a,\
    \ F f) {\n        return polynomial_eval<T, transform, transform_inv>(std::vector<T>(a),\
    \ f);\n    }\n} // namespace suisen\n\n#endif // SUISEN_APPLY_POLYNOMIAL\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/convolution/polynomial_eval.hpp
  requiredBy: []
  timestamp: '2023-09-15 20:02:25+09:00'
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
