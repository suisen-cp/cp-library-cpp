---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':question:'
    path: library/util/default_operator.hpp
    title: Default Operator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/polynomial_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - icon: ':x:'
    path: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
    title: test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/walsh_hadamard.hpp\"\n\n\n\n#line 1 \"\
    library/transform/kronecker_power.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n\
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
    \ }\n    } // default_operator\n} // namespace suisen\n\n\n#line 9 \"library/transform/kronecker_power.hpp\"\
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
    \        }\n    }\n} // namespace suisen\n\n\n\n#line 5 \"library/transform/walsh_hadamard.hpp\"\
    \n\nnamespace suisen::walsh_hadamard_transform {\n    namespace internal {\n \
    \       template <typename T, auto add = default_operator::add<T>, auto sub =\
    \ default_operator::sub<T>>\n        void unit_transform(T& x0, T& x1) {\n   \
    \         T y0 = x0, y1 = x1;\n            x0 = add(y0, y1);   // 1,  1\n    \
    \        x1 = sub(y0, y1);   // 1, -1\n        }\n    } // namespace internal\n\
    \n    using kronecker_power_transform::kronecker_power_transform;\n\n    template\
    \ <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    void walsh_hadamard(std::vector<T>& a) {\n        kronecker_power_transform<T,\
    \ 2, internal::unit_transform<T, add, sub>>(a);\n    }\n    template <typename\
    \ T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>,\
    \ auto div = default_operator::div<T>, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     for (auto& val : a) val = div(val, n);\n    }\n    template <typename T,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto\
    \ mul = default_operator::mul<T>, auto inv = default_operator::inv<T>, std::enable_if_t<std::negation_v<std::is_integral<T>>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     const T inv_n = inv(n);\n        for (auto& val : a) val = mul(val, inv_n);\n\
    \    }\n} // namespace suisen::walsh_hadamard_transform\n\n\n\n"
  code: "#ifndef SUISEN_WALSH_HADAMARD_TRANSFORM\n#define SUISEN_WALSH_HADAMARD_TRANSFORM\n\
    \n#include \"library/transform/kronecker_power.hpp\"\n\nnamespace suisen::walsh_hadamard_transform\
    \ {\n    namespace internal {\n        template <typename T, auto add = default_operator::add<T>,\
    \ auto sub = default_operator::sub<T>>\n        void unit_transform(T& x0, T&\
    \ x1) {\n            T y0 = x0, y1 = x1;\n            x0 = add(y0, y1);   // 1,\
    \  1\n            x1 = sub(y0, y1);   // 1, -1\n        }\n    } // namespace\
    \ internal\n\n    using kronecker_power_transform::kronecker_power_transform;\n\
    \n    template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>\n\
    \    void walsh_hadamard(std::vector<T>& a) {\n        kronecker_power_transform<T,\
    \ 2, internal::unit_transform<T, add, sub>>(a);\n    }\n    template <typename\
    \ T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>,\
    \ auto div = default_operator::div<T>, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     for (auto& val : a) val = div(val, n);\n    }\n    template <typename T,\
    \ auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto\
    \ mul = default_operator::mul<T>, auto inv = default_operator::inv<T>, std::enable_if_t<std::negation_v<std::is_integral<T>>,\
    \ std::nullptr_t> = nullptr>\n    void walsh_hadamard_inv(std::vector<T>& a) {\n\
    \        walsh_hadamard<T, add, sub>(a);\n        const T n{ a.size() };\n   \
    \     const T inv_n = inv(n);\n        for (auto& val : a) val = mul(val, inv_n);\n\
    \    }\n} // namespace suisen::walsh_hadamard_transform\n\n\n#endif // SUISEN_WALSH_HADAMARD_TRANSFORM\n"
  dependsOn:
  - library/transform/kronecker_power.hpp
  - library/util/default_operator.hpp
  isVerificationFile: false
  path: library/transform/walsh_hadamard.hpp
  requiredBy:
  - library/convolution/xor_convolution.hpp
  timestamp: '2022-03-21 02:24:20+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
documentation_of: library/transform/walsh_hadamard.hpp
layout: document
title: "Walsh Hadamard \u5909\u63DB"
---

- シグネチャ

  ```cpp
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
  void walsh_hadamard(std::vector<T>&)
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto div = default_operator::div<T>>
  void walsh_hadamard_inv(std::vector<T>&) // std::is_integral_v<T> が true となる型
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto mul = default_operator::mul<T>, auto inv = default_operator::inv<T>>
  void walsh_hadamard_inv(std::vector<T>&) // std::is_integral_v<T> が false となる型
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に [アダマール変換](https://ja.wikipedia.org/wiki/%E3%82%A2%E3%83%80%E3%83%9E%E3%83%BC%E3%83%AB%E5%A4%89%E6%8F%9B) を施す関数 `walsh_hadamard` およびその逆変換を施す関数 `walsh_hadamard_inv` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．
  - `mul`: 二項演算 (乗算)．デフォルトでは `operator*` が呼ばれるようになっています．
  - `div`: 二項演算 (除算)．デフォルトでは `operator/` が呼ばれるようになっています．
  - `inv`: 単項演算 (乗法逆元)．デフォルトでは `x` に対して `T{1}/x` と計算されます．

  `walsh_hadamard_inv` に関して，`T` が `int` や `long long` などの型に対しては除算 `div` が要求され，`double` や `atcoder::modint` などの型に対しては乗法逆元 `inv` および乗算 `mul` が要求されます (あとで設計を見直す可能性が高いです)．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$
