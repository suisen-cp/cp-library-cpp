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
  bundledCode: "#line 1 \"library/convolution/dirichlet_convolution.hpp\"\n\n\n\n\
    #include <vector>\n#include <limits>\n\nnamespace suisen {\n\ntemplate <typename\
    \ T>\nstatic std::vector<T> dirichlet_convolution(const std::vector<T> &a, const\
    \ std::vector<T> &b, const int n) {\n    std::vector<T> c(n, T(0));\n    const\
    \ int m = std::min(int(a.size()), n), k = std::min(int(b.size()), n);\n    for\
    \ (int i = 1; i < m; ++i) {\n        int jmax = std::min((n + i - 1) / i, k);\n\
    \        for (int j = 1; j < jmax; ++j) {\n            c[i * j] += a[i] * b[j];\n\
    \        }\n    }\n    return c;\n}\n\ntemplate <typename T>\nstatic std::vector<T>\
    \ dirichlet_convolution_coprime(const std::vector<T> &a, const std::vector<T>\
    \ &b, const int n) {\n    std::vector<T> c(n, T(0));\n    const int m = std::min(int(a.size()),\
    \ n), k = std::min(int(b.size()), n);\n    std::vector<std::vector<int>> dp(m);\n\
    \    for (int i = 1; i < m; ++i) {\n        const int jmax = std::min((n + i -\
    \ 1) / i, k);\n        dp[i].reserve(jmax);\n        dp[i].push_back(i);\n   \
    \     for (int j = 1; j < jmax; ++j) {\n            int g = i > j ? dp[i - j][j]\
    \ : dp[i][j - i];\n            dp[i].push_back(g);\n            if (g == 1) c[i\
    \ * j] += a[i] * b[j];\n        }\n    }\n    return c;\n}\n\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_DIRICHLET_CONVOLUTION\n#define SUISEN_DIRICHLET_CONVOLUTION\n\
    \n#include <vector>\n#include <limits>\n\nnamespace suisen {\n\ntemplate <typename\
    \ T>\nstatic std::vector<T> dirichlet_convolution(const std::vector<T> &a, const\
    \ std::vector<T> &b, const int n) {\n    std::vector<T> c(n, T(0));\n    const\
    \ int m = std::min(int(a.size()), n), k = std::min(int(b.size()), n);\n    for\
    \ (int i = 1; i < m; ++i) {\n        int jmax = std::min((n + i - 1) / i, k);\n\
    \        for (int j = 1; j < jmax; ++j) {\n            c[i * j] += a[i] * b[j];\n\
    \        }\n    }\n    return c;\n}\n\ntemplate <typename T>\nstatic std::vector<T>\
    \ dirichlet_convolution_coprime(const std::vector<T> &a, const std::vector<T>\
    \ &b, const int n) {\n    std::vector<T> c(n, T(0));\n    const int m = std::min(int(a.size()),\
    \ n), k = std::min(int(b.size()), n);\n    std::vector<std::vector<int>> dp(m);\n\
    \    for (int i = 1; i < m; ++i) {\n        const int jmax = std::min((n + i -\
    \ 1) / i, k);\n        dp[i].reserve(jmax);\n        dp[i].push_back(i);\n   \
    \     for (int j = 1; j < jmax; ++j) {\n            int g = i > j ? dp[i - j][j]\
    \ : dp[i][j - i];\n            dp[i].push_back(g);\n            if (g == 1) c[i\
    \ * j] += a[i] * b[j];\n        }\n    }\n    return c;\n}\n\n} // namespace suisen\n\
    \n\n#endif // SUISEN_DIRICHLET_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/dirichlet_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-05 19:28:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/convolution/dirichlet_convolution.hpp
layout: document
redirect_from:
- /library/library/convolution/dirichlet_convolution.hpp
- /library/library/convolution/dirichlet_convolution.hpp.html
title: library/convolution/dirichlet_convolution.hpp
---
