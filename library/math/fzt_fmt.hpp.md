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
  bundledCode: "#line 1 \"library/math/fzt_fmt.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T>\nvoid fmt_subset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {\n        for (int l = 0; l\
    \ < (1 << n); l += 2 * k) {\n            int m = l + k;\n            for (int\
    \ p = 0; p < k; ++p) f[m + p] -= f[l + p];\n        }\n    }\n}\ntemplate <typename\
    \ T>\nvoid fmt_supset(const int n, std::vector<T> &f) {\n    int sz = f.size();\n\
    \    assert(sz == 1 << n);\n    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {\n\
    \        for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l +\
    \ k;\n            for (int p = 0; p < k; ++p) f[l + p] -= f[m + p];\n        }\n\
    \    }\n}\n\ntemplate <typename T>\nvoid fzt_subset(const int n, std::vector<T>\
    \ &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1;\
    \ k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k)\
    \ {\n            int m = l + k;\n            for (int p = 0; p < k; ++p) f[m +\
    \ p] += f[l + p];\n        }\n    }\n}\ntemplate <typename T>\nvoid fzt_supset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1; k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1\
    \ << n); l += 2 * k) {\n            int m = l + k;\n            for (int p = 0;\
    \ p < k; ++p) f[l + p] += f[m + p];\n        }\n    }\n}\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_FZT_FMT\n#define SUISEN_FZT_FMT\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T>\nvoid fmt_subset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {\n        for (int l = 0; l\
    \ < (1 << n); l += 2 * k) {\n            int m = l + k;\n            for (int\
    \ p = 0; p < k; ++p) f[m + p] -= f[l + p];\n        }\n    }\n}\ntemplate <typename\
    \ T>\nvoid fmt_supset(const int n, std::vector<T> &f) {\n    int sz = f.size();\n\
    \    assert(sz == 1 << n);\n    for (int k = 1 << (n - 1); k >= 1; k >>= 1) {\n\
    \        for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l +\
    \ k;\n            for (int p = 0; p < k; ++p) f[l + p] -= f[m + p];\n        }\n\
    \    }\n}\n\ntemplate <typename T>\nvoid fzt_subset(const int n, std::vector<T>\
    \ &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1;\
    \ k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k)\
    \ {\n            int m = l + k;\n            for (int p = 0; p < k; ++p) f[m +\
    \ p] += f[l + p];\n        }\n    }\n}\ntemplate <typename T>\nvoid fzt_supset(const\
    \ int n, std::vector<T> &f) {\n    int sz = f.size();\n    assert(sz == 1 << n);\n\
    \    for (int k = 1; k < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1\
    \ << n); l += 2 * k) {\n            int m = l + k;\n            for (int p = 0;\
    \ p < k; ++p) f[l + p] += f[m + p];\n        }\n    }\n}\n} // namespace suisen\n\
    \n#endif // SUISEN_FZT_FMT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/math/fzt_fmt.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/fzt_fmt.hpp
layout: document
redirect_from:
- /library/library/math/fzt_fmt.hpp
- /library/library/math/fzt_fmt.hpp.html
title: library/math/fzt_fmt.hpp
---
