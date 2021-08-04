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
  bundledCode: "#line 1 \"library/transform/supset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen::supset_transform {\n\ntemplate <typename\
    \ T>\nvoid zeta(const int n, std::vector<T> &f) {\n    int sz = f.size();\n  \
    \  assert(sz == 1 << n);\n    for (int k = 1; k < (1 << n); k <<= 1) {\n     \
    \   for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l + k;\n\
    \            for (int p = 0; p < k; ++p) f[l + p] += f[m + p];\n        }\n  \
    \  }\n}\n\ntemplate <typename T>\nvoid mobius(const int n, std::vector<T> &f)\
    \ {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1; k\
    \ < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) f[l + p]\
    \ -= f[m + p];\n        }\n    }\n}\n\n} // namespace suisen::supset_transform\n\
    \n\n\n"
  code: "#ifndef SUISEN_SUPSET_TRANSFORM\n#define SUISEN_SUPSET_TRANSFORM\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen::supset_transform {\n\ntemplate\
    \ <typename T>\nvoid zeta(const int n, std::vector<T> &f) {\n    int sz = f.size();\n\
    \    assert(sz == 1 << n);\n    for (int k = 1; k < (1 << n); k <<= 1) {\n   \
    \     for (int l = 0; l < (1 << n); l += 2 * k) {\n            int m = l + k;\n\
    \            for (int p = 0; p < k; ++p) f[l + p] += f[m + p];\n        }\n  \
    \  }\n}\n\ntemplate <typename T>\nvoid mobius(const int n, std::vector<T> &f)\
    \ {\n    int sz = f.size();\n    assert(sz == 1 << n);\n    for (int k = 1; k\
    \ < (1 << n); k <<= 1) {\n        for (int l = 0; l < (1 << n); l += 2 * k) {\n\
    \            int m = l + k;\n            for (int p = 0; p < k; ++p) f[l + p]\
    \ -= f[m + p];\n        }\n    }\n}\n\n} // namespace suisen::supset_transform\n\
    \n\n#endif // SUISEN_SUPSET_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/supset.hpp
  requiredBy: []
  timestamp: '2021-08-04 13:32:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/transform/supset.hpp
layout: document
redirect_from:
- /library/library/transform/supset.hpp
- /library/library/transform/supset.hpp.html
title: library/transform/supset.hpp
---
