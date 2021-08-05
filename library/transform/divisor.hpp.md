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
  bundledCode: "#line 1 \"library/transform/divisor.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen{\n\nnamespace divisor_transform {\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto cum = [&](const int p) {\n\
    \        for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n            add_assign(f[pq],\
    \ f[q]);\n            is_prime[pq] = false;\n        }\n    };\n    cum(2);\n\
    \    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\n// Calculates\
    \ `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename SubAssign>\n\
    void mobius(std::vector<T> &f, SubAssign sub_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto diff = [&](const int p) {\n\
    \        const int qmax = (n - 1) / p, rmax = qmax * p;\n        for (int q =\
    \ qmax, pq = rmax; q >= 1; --q, pq -= p) {\n            sub_assign(f[pq], f[q]);\n\
    \            is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ divisor_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct DivisorTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        divisor_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        divisor_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct DivisorTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        divisor_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        divisor_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_DIVISOR_TRANSFORM\n#define SUISEN_DIVISOR_TRANSFORM\n\n#include\
    \ <vector>\n\nnamespace suisen{\n\nnamespace divisor_transform {\n\n// Calculates\
    \ `g` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename AddAssign>\n\
    void zeta(std::vector<T> &f, AddAssign add_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto cum = [&](const int p) {\n\
    \        for (int q = 1, pq = p; pq < n; ++q, pq += p) {\n            add_assign(f[pq],\
    \ f[q]);\n            is_prime[pq] = false;\n        }\n    };\n    cum(2);\n\
    \    for (int p = 3; p < n; p += 2) if (is_prime[p]) cum(p);\n}\n\n// Calculates\
    \ `f` s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T, typename SubAssign>\n\
    void mobius(std::vector<T> &f, SubAssign sub_assign) {\n    const int n = f.size();\n\
    \    std::vector<char> is_prime(n, true);\n    auto diff = [&](const int p) {\n\
    \        const int qmax = (n - 1) / p, rmax = qmax * p;\n        for (int q =\
    \ qmax, pq = rmax; q >= 1; --q, pq -= p) {\n            sub_assign(f[pq], f[q]);\n\
    \            is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{d | n} f(d) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ divisor_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct DivisorTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        divisor_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        divisor_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct DivisorTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        divisor_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        divisor_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n#endif // SUISEN_DIVISOR_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/divisor.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/transform/multiple/divide_both.test.cpp
documentation_of: library/transform/divisor.hpp
layout: document
redirect_from:
- /library/library/transform/divisor.hpp
- /library/library/transform/divisor.hpp.html
title: library/transform/divisor.hpp
---
