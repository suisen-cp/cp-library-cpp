---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
  requiredBy: []
  timestamp: '2022-10-13 23:32:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/sequence/binomial_coefficient.hpp
layout: document
title: Binomial Coefficient
---
## Binomial Coefficient
