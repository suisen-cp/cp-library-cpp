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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen::internal {\n    template <typename T>\n    std::vector<T>\
    \ convolution_naive(const std::vector<T>& a, const std::vector<T>& b) {\n    \
    \    const int n = a.size(), m = b.size();\n        std::vector<T> c(n + m - 1);\n\
    \        if (n < m) {\n            for (int j = 0; j < m; j++) for (int i = 0;\
    \ i < n; i++) c[i + j] += a[i] * b[j];\n        } else {\n            for (int\
    \ i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];\n  \
    \      }\n        return c;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION_NAIVE\n#define SUISEN_CONVOLUTION_NAIVE\n\n#include\
    \ <vector>\n\nnamespace suisen::internal {\n    template <typename T>\n    std::vector<T>\
    \ convolution_naive(const std::vector<T>& a, const std::vector<T>& b) {\n    \
    \    const int n = a.size(), m = b.size();\n        std::vector<T> c(n + m - 1);\n\
    \        if (n < m) {\n            for (int j = 0; j < m; j++) for (int i = 0;\
    \ i < n; i++) c[i + j] += a[i] * b[j];\n        } else {\n            for (int\
    \ i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];\n  \
    \      }\n        return c;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION_NAIVE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/convolution_naive.hpp
  requiredBy:
  - library/convolution/convolution_2_64.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/convolution/convolution_large.hpp
  timestamp: '2022-05-05 17:36:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/convolution_large/convolution_large.test.cpp
  - test/src/convolution/arbitrary_mod_convolution/convolution_mod_1000000007.test.cpp
  - test/src/convolution/convolution_2_64/convolution_mod_2_64.test.cpp
  - test/src/convolution/convolution_2_64/convolution_mod_2_64_6mod.test.cpp
documentation_of: library/convolution/convolution_naive.hpp
layout: document
title: Naive Convolution
---
## Naive Convolution

愚直な畳み込みの実装です。列の一方の次数が小さい場合は、こちらを用いる方が高速な場合があります。
