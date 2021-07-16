---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/math/fzt_fmt_test.cpp
    title: test/math/fzt_fmt_test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/fzt.hpp\"\n#include <cassert>\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename T>\nvoid fzt_subset(const int n, std::vector<T>\
    \ &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1;\
    \ k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k)\
    \ {\n            int m = l + k;\n            for (int p = 0; p < k; ++p) f[m +\
    \ p] += f[l + p];\n        }\n    }\n}\ntemplate <typename T>\nvoid fzt_supset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1; k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1\
    \ << n); l += 2 * k) {\n            int m = l + k;\n            for (int p = 0;\
    \ p < k; ++p) f[l + p] += f[m + p];\n        }\n    }\n}\n} // namespace suisen\n"
  code: "#include <cassert>\n#include <vector>\n\nnamespace suisen {\ntemplate <typename\
    \ T>\nvoid fzt_subset(const int n, std::vector<T> &f) {\n    int sz = f.size();\n\
    \    assert(sz == 1 << n);\n    for (int k = 1; k < (1 << n); k <<= 1) {\n   \
    \     for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l + k;\n\
    \            for (int p = 0; p < k; ++p) f[m + p] += f[l + p];\n        }\n  \
    \  }\n}\ntemplate <typename T>\nvoid fzt_supset(const int n, std::vector<T> &f)\
    \ {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1; k\
    \ < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) f[l + p]\
    \ += f[m + p];\n        }\n    }\n}\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/math/fzt.hpp
  requiredBy:
  - test/math/fzt_fmt_test.cpp
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/fzt.hpp
layout: document
redirect_from:
- /library/library/math/fzt.hpp
- /library/library/math/fzt.hpp.html
title: library/math/fzt.hpp
---
