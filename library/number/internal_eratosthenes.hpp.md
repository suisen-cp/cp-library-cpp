---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':warning:'
    path: library/number/fast_discrete_logarithm.hpp
    title: library/number/fast_discrete_logarithm.hpp
  - icon: ':question:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':question:'
    path: library/number/order_Z_mZ.hpp
    title: Order of $x \in (\mathbb{Z}/m\mathbb{Z}) ^ \ast$
  - icon: ':question:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':question:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes_constexpr.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9 (\u30B3\u30F3\u30D1\
      \u30A4\u30EB\u6642\u8A08\u7B97)"
  - icon: ':x:'
    path: library/number/tetration_mod.hpp
    title: $a\uparrow\uparrow b \bmod m$
  - icon: ':warning:'
    path: library/string/dynamic_rolling_hash.hpp
    title: Dynamic Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/algorithm/mo/abc238_g.test.cpp
    title: test/src/algorithm/mo/abc238_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - icon: ':x:'
    path: test/src/number/fast_factorize/factorize.test.cpp
    title: test/src/number/fast_factorize/factorize.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/dummy.test.cpp
    title: test/src/number/primitive_root/dummy.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/primitive_root.test.cpp
    title: test/src/number/primitive_root/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes/enumerate_primes.test.cpp
    title: test/src/number/sieve_of_eratosthenes/enumerate_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes/flatten.test.cpp
    title: test/src/number/sieve_of_eratosthenes/flatten.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes/next_prime.test.cpp
    title: test/src/number/sieve_of_eratosthenes/next_prime.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
    title: test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
    title: test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
  - icon: ':x:'
    path: test/src/number/tetration_mod/tetration_mod.test.cpp
    title: test/src/number/tetration_mod/tetration_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/transform/multiple/divide_both.test.cpp
    title: test/src/transform/multiple/divide_both.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/internal_eratosthenes.hpp\"\n\n\n\n#include\
    \ <cstdint>\n#include <cassert>\n\nnamespace suisen::internal::sieve {\n\nconstexpr\
    \ std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\nconstexpr std::uint8_t\
    \ RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t DR[K] = {\
    \ 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K] = {\n    {\
    \ 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2, 0, 2, 0,\
    \ 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4,\
    \ 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4,\
    \ 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16\
    \ };\nconstexpr std::uint8_t DFP[K][K] = {\n    {  0,  0,  0,  0,  0,  0,  0,\
    \  8 }, {  8,  8,  8,  0,  8,  8,  8,  8 },\n    { 16, 16,  0, 16,  0, 16, 16,\
    \  8 }, { 24,  8,  8, 16,  8,  8, 24,  8 },\n    { 24, 24,  8, 16,  8, 24, 24,\
    \  8 }, { 32, 16, 16, 16, 16, 16, 32,  8 },\n    { 40, 24,  8, 32,  8, 24, 40,\
    \  8 }, { 48, 32, 16, 32, 16, 32, 48,  8 },\n};\n\nconstexpr std::uint8_t MASK[K][K]\
    \ = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10,\
    \ 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08,\
    \ 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80,\
    \ 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01,\
    \ 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80,\
    \ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K]\
    \ = {\n    { 0, 1, 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3, 2, 6, },\n  \
    \  { 2, 4, 0, 6, 1, 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n    { 4, 7,\
    \ 1, 2, 5, 6, 0, 3, },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6, 2, 3, 7, 0,\
    \ 4, 5, 1, },\n    { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t\
    \ mask_to_index(const std::uint8_t bits) {\n    switch (bits) {\n        case\
    \ 1 << 0: return 0;\n        case 1 << 1: return 1;\n        case 1 << 2: return\
    \ 2;\n        case 1 << 3: return 3;\n        case 1 << 4: return 4;\n       \
    \ case 1 << 5: return 5;\n        case 1 << 6: return 6;\n        case 1 << 7:\
    \ return 7;\n        default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\
    \n\n"
  code: "#ifndef SUISEN_INTERNAL_ERATOSTHENES\n#define SUISEN_INTERNAL_ERATOSTHENES\n\
    \n#include <cstdint>\n#include <cassert>\n\nnamespace suisen::internal::sieve\
    \ {\n\nconstexpr std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\n\
    constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t\
    \ DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K]\
    \ = {\n    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2,\
    \ 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3,\
    \ 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2,\
    \ 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 48, 32, 16, 32, 16,\
    \ 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {  0,  0,  0,  0, \
    \ 0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8,  8 },\n    { 16, 16,  0, 16,\
    \  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,  8 },\n    { 24, 24,  8, 16,\
    \  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,  8 },\n    { 40, 24,  8, 32,\
    \  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,  8 },\n};\n\nconstexpr std::uint8_t\
    \ MASK[K][K] = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02,\
    \ 0x20, 0x10, 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02,\
    \ 0x80, 0x08, 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n  \
    \  { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02,\
    \ 0x40, 0x01, 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02\
    \ }, { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t\
    \ OFFSET[K][K] = {\n    { 0, 1, 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3,\
    \ 2, 6, },\n    { 2, 4, 0, 6, 1, 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n\
    \    { 4, 7, 1, 2, 5, 6, 0, 3, },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6,\
    \ 2, 3, 7, 0, 4, 5, 1, },\n    { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t\
    \ mask_to_index(const std::uint8_t bits) {\n    switch (bits) {\n        case\
    \ 1 << 0: return 0;\n        case 1 << 1: return 1;\n        case 1 << 2: return\
    \ 2;\n        case 1 << 3: return 3;\n        case 1 << 4: return 4;\n       \
    \ case 1 << 5: return 5;\n        case 1 << 6: return 6;\n        case 1 << 7:\
    \ return 7;\n        default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\
    \n#endif // SUISEN_INTERNAL_ERATOSTHENES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/internal_eratosthenes.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/number/sieve_of_eratosthenes_constexpr.hpp
  - library/number/primitive_root.hpp
  - library/number/fast_factorize.hpp
  - library/number/fast_discrete_logarithm.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/order_Z_mZ.hpp
  - library/number/tetration_mod.hpp
  - library/string/dynamic_rolling_hash.hpp
  timestamp: '2021-07-22 14:46:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/transform/multiple/divide_both.test.cpp
  - test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
  - test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
  - test/src/number/sieve_of_eratosthenes/next_prime.test.cpp
  - test/src/number/sieve_of_eratosthenes/enumerate_primes.test.cpp
  - test/src/number/sieve_of_eratosthenes/flatten.test.cpp
  - test/src/number/primitive_root/primitive_root.test.cpp
  - test/src/number/primitive_root/dummy.test.cpp
  - test/src/number/fast_factorize/factorize.test.cpp
  - test/src/number/tetration_mod/tetration_mod.test.cpp
  - test/src/algorithm/mo/abc238_g.test.cpp
documentation_of: library/number/internal_eratosthenes.hpp
layout: document
title: Internal Eratosthenes
---
## Internal Eratosthenes