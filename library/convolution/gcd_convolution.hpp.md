---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: library/convolution/convolution.hpp
  - icon: ':heavy_check_mark:'
    path: library/transform/multiple.hpp
    title: library/transform/multiple.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/gcd_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/multiple.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen\
    \ {\n\nnamespace multiple_transform {\n\n// Calculates `g` s.t. g(n) = Sum_{n\
    \ | m} f(m) inplace.\ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T>\
    \ &f, AddAssign add_assign) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto cum = [&](const int p) {\n        const int qmax\
    \ = (n - 1) / p, rmax = qmax * p;\n        for (int q = qmax, pq = rmax; q >=\
    \ 1; --q, pq -= p) {\n            add_assign(f[q], f[pq]);\n            is_prime[pq]\
    \ = false;\n        }\n    };\n    cum(2);\n    for (int p = 3; p < n; p += 2)\
    \ if (is_prime[p]) cum(p);\n}\n\n// Calculates `f` s.t. g(n) = Sum_{n | m} f(m)\
    \ inplace.\ntemplate <typename T, typename SubAssign>\nvoid mobius(std::vector<T>\
    \ &f, SubAssign sub_assign) {\n    const int n = f.size();\n    std::vector<char>\
    \ is_prime(n, true);\n    auto diff = [&](const int p) {\n        for (int q =\
    \ 1, pq = p; pq < n; ++q, pq += p) {\n            sub_assign(f[q], f[pq]);\n \
    \           is_prime[pq] = false;\n        }\n    };\n    diff(2);\n    for (int\
    \ p = 3; p < n; p += 2) if (is_prime[p]) diff(p);\n}\n\n// Calculates `g` s.t.\
    \ g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\n\n// Calculates `f`\
    \ s.t. g(n) = Sum_{n | m} f(m) inplace.\ntemplate <typename T>\nvoid mobius(std::vector<T>\
    \ &f) {\n    mobius(f, [](T &a, const T &b) { a -= b; });\n}\n\n} // namespace\
    \ multiple_transform\n\ntemplate <typename T, typename AddAssign, typename SubAssign,\
    \ AddAssign add_assign, SubAssign sub_assign>\nstruct MultipleTransformGeneral\
    \ {\n    static void transform(std::vector<T> &a) {\n        multiple_transform::zeta(a,\
    \ add_assign);\n    }\n    static void inverse_transform(std::vector<T> &a) {\n\
    \        multiple_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate <typename\
    \ T>\nstruct MultipleTransform {\n    static void transform(std::vector<T> &a)\
    \ {\n        multiple_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        multiple_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename T, template <typename> class Transform>\n\
    struct Convolution {\n    static std::vector<T> convolution(std::vector<T> a,\
    \ std::vector<T> b) {\n        const int n = a.size();\n        assert(n == int(b.size()));\n\
    \        Transform<T>::transform(a);\n        Transform<T>::transform(b);\n  \
    \      for (int i = 0; i < n; ++i) a[i] *= b[i];\n        Transform<T>::inverse_transform(a);\n\
    \        return a;\n    }\n    static std::vector<T> convolution(std::vector<std::vector<T>>\
    \ a) {\n        const int num = a.size();\n        if (num == 0) return {};\n\
    \        const int n = a[0].size();\n        for (auto &v : a) {\n           \
    \ assert(n == int(v.size()));\n            Transform<T>::transform(v);\n     \
    \   }\n        auto &res = a[0];\n        for (int i = 1; i < num; ++i) {\n  \
    \          for (int j = 0; j < n; ++j) res[j] *= a[i][j];\n        }\n       \
    \ Transform<T>::inverse_transform(res);\n        return res;\n    }\n};\n\n} //\
    \ namespace suisen\n\n\n\n#line 6 \"library/convolution/gcd_convolution.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nusing GCDConvolution = Convolution<T,\
    \ MultipleTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T>\
    \ gcd_convolution(Args &&...args) {\n    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_GCD_CONVOLUTION\n#define SUISEN_GCD_CONVOLUTION\n\n#include\
    \ \"library/transform/multiple.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing GCDConvolution = Convolution<T,\
    \ MultipleTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T>\
    \ gcd_convolution(Args &&...args) {\n    return GCDConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_GCD_CONVOLUTION\n"
  dependsOn:
  - library/transform/multiple.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/gcd_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/gcd_convolution/lcms.test.cpp
documentation_of: library/convolution/gcd_convolution.hpp
layout: document
redirect_from:
- /library/library/convolution/gcd_convolution.hpp
- /library/library/convolution/gcd_convolution.hpp.html
title: library/convolution/gcd_convolution.hpp
---
