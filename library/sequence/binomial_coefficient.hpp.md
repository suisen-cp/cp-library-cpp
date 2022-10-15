---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/sequence/binomial_coefficient_small_prime_mod.hpp
    title: Binomial Coefficient Small Prime Mod
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number1_small_prime_mod.hpp
    title: Stirling Number of the First Kind (Small Prime Mod)
  - icon: ':heavy_check_mark:'
    path: library/sequence/stirling_number2_small_prime_mod.hpp
    title: Stirling Number2 Small Prime Mod
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
    title: test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/binomial_coefficient.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T>\n    std::vector<std::vector<T>>\
    \ binom_table(int n) {\n        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n\
    \ + 1));\n        for (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i]\
    \ = 1;\n            for (int j = 1; j < i; ++j) {\n                binom[i][j]\
    \ = binom[i - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n       \
    \ return binom;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BINOMIAL_COEFFICIENT\n#define SUISEN_BINOMIAL_COEFFICIENT\n\
    \n#include <vector>\n\nnamespace suisen {\n    template <typename T>\n    std::vector<std::vector<T>>\
    \ binom_table(int n) {\n        std::vector<std::vector<T>> binom(n + 1, std::vector<T>(n\
    \ + 1));\n        for (int i = 0; i <= n; ++i) {\n            binom[i][0] = binom[i][i]\
    \ = 1;\n            for (int j = 1; j < i; ++j) {\n                binom[i][j]\
    \ = binom[i - 1][j - 1] + binom[i - 1][j];\n            }\n        }\n       \
    \ return binom;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_BINOMIAL_COEFFICIENT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/sequence/binomial_coefficient.hpp
  requiredBy:
  - library/sequence/stirling_number2_small_prime_mod.hpp
  - library/sequence/binomial_coefficient_small_prime_mod.hpp
  - library/sequence/stirling_number1_small_prime_mod.hpp
  timestamp: '2022-10-13 23:32:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/stirling_number2_small_prime_mod/stirling_number_of_the_second_kind_small_p_large_n.test.cpp
  - test/src/sequence/stirling_number1_small_prime_mod/stirling_number_of_the_first_kind_small_p_large_n.test.cpp
documentation_of: library/sequence/binomial_coefficient.hpp
layout: document
title: Binomial Coefficient
---
## Binomial Coefficient
