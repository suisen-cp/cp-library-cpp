---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/gcd_convolution.hpp
    title: GCD Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution.hpp
    title: library/convolution/multi_variate_convolution.hpp
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: Bitwise Xor Convolution
  - icon: ':heavy_check_mark:'
    path: library/transform/divisor.hpp
    title: "\u7D04\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: library/transform/kronecker_power.hpp
    title: "\u30AF\u30ED\u30CD\u30C3\u30AB\u30FC\u51AA\u306B\u3088\u308B\u7DDA\u5F62\
      \u5909\u63DB (\u4EEE\u79F0)"
  - icon: ':heavy_check_mark:'
    path: library/transform/multiple.hpp
    title: "\u500D\u6570\u7CFB\u30BC\u30FC\u30BF\u5909\u63DB\u30FB\u30E1\u30D3\u30A6\
      \u30B9\u5909\u63DB"
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
  - icon: ':warning:'
    path: library/util/cumulative_sum.hpp
    title: library/util/cumulative_sum.hpp
  - icon: ':warning:'
    path: library/util/cumulative_sum_2d.hpp
    title: library/util/cumulative_sum_2d.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
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
  - icon: ':heavy_check_mark:'
    path: test/src/transform/kronecker_power/agc044_c.test.cpp
    title: test/src/transform/kronecker_power/agc044_c.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/transform/multiple/divide_both.test.cpp
    title: test/src/transform/multiple/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/default_operator.hpp\"\n\n\n\nnamespace suisen\
    \ {\n    namespace default_operator {\n        template <typename T>\n       \
    \ auto zero() -> decltype(T { 0 }) { return T { 0 }; }\n        template <typename\
    \ T>\n        auto one()  -> decltype(T { 1 }) { return T { 1 }; }\n        template\
    \ <typename T>\n        auto add(const T &x, const T &y) -> decltype(x + y) {\
    \ return x + y; }\n        template <typename T>\n        auto sub(const T &x,\
    \ const T &y) -> decltype(x - y) { return x - y; }\n        template <typename\
    \ T>\n        auto mul(const T &x, const T &y) -> decltype(x * y) { return x *\
    \ y; }\n        template <typename T>\n        auto div(const T &x, const T &y)\
    \ -> decltype(x / y) { return x / y; }\n        template <typename T>\n      \
    \  auto mod(const T &x, const T &y) -> decltype(x % y) { return x % y; }\n   \
    \     template <typename T>\n        auto neg(const T &x) -> decltype(-x) { return\
    \ -x; }\n        template <typename T>\n        auto inv(const T &x) -> decltype(one<T>()\
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_DEFAULT_OPERATOR\n#define SUISEN_DEFAULT_OPERATOR\n\nnamespace\
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
    \ / x)  { return one<T>() / x; }\n    } // default_operator\n} // namespace suisen\n\
    \n#endif // SUISEN_DEFAULT_OPERATOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/default_operator.hpp
  requiredBy:
  - library/util/cumulative_sum_2d.hpp
  - library/util/cumulative_sum.hpp
  - library/transform/subset.hpp
  - library/transform/multiple.hpp
  - library/transform/walsh_hadamard.hpp
  - library/transform/divisor.hpp
  - library/transform/kronecker_power.hpp
  - library/transform/supset.hpp
  - library/convolution/xor_convolution.hpp
  - library/convolution/gcd_convolution.hpp
  - library/convolution/multi_variate_convolution.hpp
  - library/convolution/and_convolution.hpp
  - library/convolution/convolution.hpp
  - library/convolution/or_convolution.hpp
  timestamp: '2021-09-29 01:36:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/transform/multiple/divide_both.test.cpp
  - test/src/transform/kronecker_power/agc044_c.test.cpp
  - test/src/math/sps/connectivity2.test.cpp
  - test/src/math/sps/lights_out_on_connected_graph.test.cpp
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - test/src/convolution/polynomial_eval/nim_counting.test.cpp
  - test/src/convolution/gcd_convolution/lcms.test.cpp
  - test/src/convolution/multi_variate_convolution/multivariate_convolution.test.cpp
  - test/src/convolution/polynomial_eval_multipoint_eval/nim_counting.test.cpp
  - test/src/convolution/and_convolution/and_convolution.test.cpp
documentation_of: library/util/default_operator.hpp
layout: document
redirect_from:
- /library/library/util/default_operator.hpp
- /library/library/util/default_operator.hpp.html
title: library/util/default_operator.hpp
---