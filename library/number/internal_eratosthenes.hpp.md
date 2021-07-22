---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: library/number/sieve_of_eratosthenes.hpp
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes_constexpr.hpp
    title: library/number/sieve_of_eratosthenes_constexpr.hpp
  _extendedVerifiedWith:
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
    \ 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 180, 120,  60, 120,  60, 120,\
    \ 180,  60 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {   0,   0,   0,   0,\
    \   0,   0,   0,  30 }, {  30,  30,  30,   0,  30,  30,  30,  30 },\n    {  60,\
    \  60,   0,  60,   0,  60,  60,  30 }, {  90,  30,  30,  60,  30,  30,  90,  30\
    \ },\n    {  90,  90,  30,  60,  30,  90,  90,  30 }, { 120,  60,  60,  60,  60,\
    \  60, 120,  30 },\n    { 150,  90,  30, 120,  30,  90, 150,  30 }, { 180, 120,\
    \  60, 120,  60, 120, 180,  30 },\n};\n\nconstexpr std::uint8_t MASK[K][K] = {\n\
    \    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01,\
    \ 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20\
    \ }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80, 0x02,\
    \ 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10,\
    \ 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40,\
    \ 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K]\
    \ = {\n    {  1,  7, 11, 13, 17, 19, 23, 29 }, {  7, 19, 17,  1, 29, 13, 11, 23\
    \ },\n    { 11, 17,  1, 23,  7, 29, 13, 19 }, { 13,  1, 23, 19, 11,  7, 29, 17\
    \ },\n    { 17, 29,  7, 11, 19, 23,  1, 13 }, { 19, 13, 29,  7, 23,  1, 17, 11\
    \ },\n    { 23, 11, 13, 29,  1, 17, 19,  7 }, { 29, 23, 19, 17, 13, 11,  7,  1\
    \ },\n};\n\nconstexpr std::uint8_t mask_to_index(const std::uint8_t bits) {\n\
    \    switch (bits) {\n        case 1 << 0: return 0;\n        case 1 << 1: return\
    \ 1;\n        case 1 << 2: return 2;\n        case 1 << 3: return 3;\n       \
    \ case 1 << 4: return 4;\n        case 1 << 5: return 5;\n        case 1 << 6:\
    \ return 6;\n        case 1 << 7: return 7;\n        default: assert(false);\n\
    \    }\n}\n} // namespace suisen::internal::sieve\n\n\n"
  code: "#ifndef SUISEN_INTERNAL_ERATOSTHENES\n#define SUISEN_INTERNAL_ERATOSTHENES\n\
    \n#include <cstdint>\n#include <cassert>\n\nnamespace suisen::internal::sieve\
    \ {\n\nconstexpr std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\n\
    constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t\
    \ DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K]\
    \ = {\n    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2,\
    \ 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3,\
    \ 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2,\
    \ 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 180, 120,  60, 120,\
    \  60, 120, 180,  60 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {   0,   0,\
    \   0,   0,   0,   0,   0,  30 }, {  30,  30,  30,   0,  30,  30,  30,  30 },\n\
    \    {  60,  60,   0,  60,   0,  60,  60,  30 }, {  90,  30,  30,  60,  30,  30,\
    \  90,  30 },\n    {  90,  90,  30,  60,  30,  90,  90,  30 }, { 120,  60,  60,\
    \  60,  60,  60, 120,  30 },\n    { 150,  90,  30, 120,  30,  90, 150,  30 },\
    \ { 180, 120,  60, 120,  60, 120, 180,  30 },\n};\n\nconstexpr std::uint8_t MASK[K][K]\
    \ = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10,\
    \ 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08,\
    \ 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80,\
    \ 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01,\
    \ 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80,\
    \ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K]\
    \ = {\n    {  1,  7, 11, 13, 17, 19, 23, 29 }, {  7, 19, 17,  1, 29, 13, 11, 23\
    \ },\n    { 11, 17,  1, 23,  7, 29, 13, 19 }, { 13,  1, 23, 19, 11,  7, 29, 17\
    \ },\n    { 17, 29,  7, 11, 19, 23,  1, 13 }, { 19, 13, 29,  7, 23,  1, 17, 11\
    \ },\n    { 23, 11, 13, 29,  1, 17, 19,  7 }, { 29, 23, 19, 17, 13, 11,  7,  1\
    \ },\n};\n\nconstexpr std::uint8_t mask_to_index(const std::uint8_t bits) {\n\
    \    switch (bits) {\n        case 1 << 0: return 0;\n        case 1 << 1: return\
    \ 1;\n        case 1 << 2: return 2;\n        case 1 << 3: return 3;\n       \
    \ case 1 << 4: return 4;\n        case 1 << 5: return 5;\n        case 1 << 6:\
    \ return 6;\n        case 1 << 7: return 7;\n        default: assert(false);\n\
    \    }\n}\n} // namespace suisen::internal::sieve\n\n#endif // SUISEN_INTERNAL_ERATOSTHENES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/internal_eratosthenes.hpp
  requiredBy:
  - library/number/sieve_of_eratosthenes_constexpr.hpp
  - library/number/sieve_of_eratosthenes.hpp
  timestamp: '2021-07-22 12:50:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/sieve_of_eratosthenes_constexpr/next_prime.test.cpp
  - test/src/number/sieve_of_eratosthenes_constexpr/flatten.test.cpp
  - test/src/number/sieve_of_eratosthenes/next_prime.test.cpp
  - test/src/number/sieve_of_eratosthenes/flatten.test.cpp
documentation_of: library/number/internal_eratosthenes.hpp
layout: document
redirect_from:
- /library/library/number/internal_eratosthenes.hpp
- /library/library/number/internal_eratosthenes.hpp.html
title: library/number/internal_eratosthenes.hpp
---
