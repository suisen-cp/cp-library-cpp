---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/arbitrary_mod_convolution.hpp
    title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_2_64.hpp
    title: Convolution $(\mathrm{mod}\ 2 ^ {64})$
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_large.hpp
    title: Convolution (Large)
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':heavy_check_mark:'
    path: library/math/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':heavy_check_mark:'
    path: library/math/factorial_large.hpp
    title: Factorial Large
  - icon: ':heavy_check_mark:'
    path: library/math/unsigned_bigint.hpp
    title: Unsigned Bigint
  - icon: ':warning:'
    path: test/src/math/factorial_large/yuki502.cpp
    title: test/src/math/factorial_large/yuki502.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
    title: test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
    title: test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
    title: test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_large/convolution_large.test.cpp
    title: test/src/convolution/convolution_large/convolution_large.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_A.test.cpp
    title: test/src/math/bigint/NTL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_B.test.cpp
    title: test/src/math/bigint/NTL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_D.test.cpp
    title: test/src/math/bigint/NTL_2_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_E.test.cpp
    title: test/src/math/bigint/NTL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/NTL_2_F.test.cpp
    title: test/src/math/bigint/NTL_2_F.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/addition_of_big_integers.test.cpp
    title: test/src/math/bigint/addition_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/many_aplusb_128bit.test.cpp
    title: test/src/math/bigint/many_aplusb_128bit.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/bigint/multiplication_of_big_integers.test.cpp
    title: test/src/math/bigint/multiplication_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/dummy.test.cpp
    title: test/src/math/factorial_large/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/factorial.test.cpp
    title: test/src/math/factorial_large/factorial.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/math/factorial_large/many_factorials.test.cpp
    title: test/src/math/factorial_large/many_factorials.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen::internal {\n    template <typename T, typename\
    \ R = T>\n    std::vector<R> convolution_naive(const std::vector<T>& a, const\
    \ std::vector<T>& b) {\n        const int n = a.size(), m = b.size();\n      \
    \  std::vector<R> c(n + m - 1);\n        if (n < m) {\n            for (int j\
    \ = 0; j < m; j++) for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n \
    \       } else {\n            for (int i = 0; i < n; i++) for (int j = 0; j <\
    \ m; j++) c[i + j] += R(a[i]) * b[j];\n        }\n        return c;\n    }\n}\
    \ // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION_NAIVE\n#define SUISEN_CONVOLUTION_NAIVE\n\n#include\
    \ <vector>\n\nnamespace suisen::internal {\n    template <typename T, typename\
    \ R = T>\n    std::vector<R> convolution_naive(const std::vector<T>& a, const\
    \ std::vector<T>& b) {\n        const int n = a.size(), m = b.size();\n      \
    \  std::vector<R> c(n + m - 1);\n        if (n < m) {\n            for (int j\
    \ = 0; j < m; j++) for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n \
    \       } else {\n            for (int i = 0; i < n; i++) for (int j = 0; j <\
    \ m; j++) c[i + j] += R(a[i]) * b[j];\n        }\n        return c;\n    }\n}\
    \ // namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION_NAIVE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/convolution_naive.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/convolution/convolution_2_64.hpp
  - library/convolution/convolution_large.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/math/bigint.hpp
  - library/math/unsigned_bigint.hpp
  - library/math/factorial_large.hpp
  - test/src/math/factorial_large/yuki502.cpp
  timestamp: '2023-05-11 13:19:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
  - test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  - test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
  - test/src/convolution/convolution_large/convolution_large.test.cpp
  - test/src/math/bigint/NTL_2_E.test.cpp
  - test/src/math/bigint/multiplication_of_big_integers.test.cpp
  - test/src/math/bigint/NTL_2_B.test.cpp
  - test/src/math/bigint/addition_of_big_integers.test.cpp
  - test/src/math/bigint/many_aplusb_128bit.test.cpp
  - test/src/math/bigint/NTL_2_D.test.cpp
  - test/src/math/bigint/NTL_2_F.test.cpp
  - test/src/math/bigint/NTL_2_A.test.cpp
  - test/src/math/factorial_large/factorial.test.cpp
  - test/src/math/factorial_large/dummy.test.cpp
  - test/src/math/factorial_large/many_factorials.test.cpp
documentation_of: library/convolution/convolution_naive.hpp
layout: document
title: Naive Convolution
---
## Naive Convolution

愚直な畳み込みの実装です。列の一方の次数が小さい場合は、こちらを用いる方が高速な場合があります。
