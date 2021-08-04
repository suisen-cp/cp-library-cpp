---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/transform/multiple/divide_both.test.cpp
    title: test/src/transform/multiple/divide_both.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/multiple.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen::multiple_transform {\n\n// Calculates `g` s.t. g(n) = Sum_{n\
    \ | m} f(m) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T> &f) {\n\
    \    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n    auto\
    \ cum = [&](const int p) {\n        const int qmax = (n - 1) / p, rmax = qmax\
    \ * p;\n        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n      \
    \      f[q] += f[pq];\n            is_prime[pq] = false;\n        }\n    };\n\
    \    cum(2);\n    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\
    \n// Calculates `f` s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename\
    \ T>\nvoid mobius(std::vector<T> &f) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto diff = [&](const int p) {\n        for (int q =\
    \ 1, pq = p; pq < n; ++q, pq += p) {\n            f[q] -= f[pq];\n           \
    \ is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int p = 3;\
    \ p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n} // namespace suisen:: multiple_transform\n\
    \n\n\n"
  code: "#ifndef SUISEN_MULTIPLE_TRANSFORM\n#define SUISEN_MULTIPLE_TRANSFORM\n\n\
    #include <vector>\n\nnamespace suisen::multiple_transform {\n\n// Calculates `g`\
    \ s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    const int n = f.size();\n    std::vector<char> is_prime(n, true);\n\
    \    auto cum = [&](const int p) {\n        const int qmax = (n - 1) / p, rmax\
    \ = qmax * p;\n        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {\n\
    \            f[q] += f[pq];\n            is_prime[pq] = false;\n        }\n  \
    \  };\n    cum(2);\n    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n\
    }\n\n// Calculates `f` s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename\
    \ T>\nvoid mobius(std::vector<T> &f) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto diff = [&](const int p) {\n        for (int q =\
    \ 1, pq = p; pq < n; ++q, pq += p) {\n            f[q] -= f[pq];\n           \
    \ is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int p = 3;\
    \ p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n} // namespace suisen:: multiple_transform\n\
    \n\n#endif // SUISEN_MULTIPLE_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/multiple.hpp
  requiredBy: []
  timestamp: '2021-08-04 13:32:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/transform/multiple/divide_both.test.cpp
documentation_of: library/transform/multiple.hpp
layout: document
redirect_from:
- /library/library/transform/multiple.hpp
- /library/library/transform/multiple.hpp.html
title: library/transform/multiple.hpp
---
