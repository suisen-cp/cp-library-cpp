---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/sequence/montmort_number/montmort_number_mod.test.cpp
    title: test/src/sequence/montmort_number/montmort_number_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/sequence/montmort_number.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename mint>\n    std::vector<mint> montmort_number(int\
    \ n) {\n        std::vector<mint> res{ 1, 0 };\n        for (int i = 2; i <= n;\
    \ ++i) res.push_back((i - 1) * (res[i - 1] + res[i - 2]));\n        res.resize(n\
    \ + 1);\n        return res;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MONTMORT_NUMBER\n#define SUISEN_MONTMORT_NUMBER\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename mint>\n    std::vector<mint>\
    \ montmort_number(int n) {\n        std::vector<mint> res{ 1, 0 };\n        for\
    \ (int i = 2; i <= n; ++i) res.push_back((i - 1) * (res[i - 1] + res[i - 2]));\n\
    \        res.resize(n + 1);\n        return res;\n    }\n} // namespace suisen\n\
    \n#endif // SUISEN_MONTMORT_NUMBER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/sequence/montmort_number.hpp
  requiredBy: []
  timestamp: '2022-07-10 22:02:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/sequence/montmort_number/montmort_number_mod.test.cpp
documentation_of: library/sequence/montmort_number.hpp
layout: document
title: Montmort Number
---
## Montmort Number