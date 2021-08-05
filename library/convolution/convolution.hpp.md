---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/and_convolution.hpp
    title: library/convolution/and_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: library/convolution/gcd_convolution.hpp
    title: library/convolution/gcd_convolution.hpp
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: library/convolution/or_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: library/convolution/subset_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: library/convolution/xor_convolution.hpp
    title: library/convolution/xor_convolution.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/and_convolution/and_convolution.test.cpp
    title: test/src/convolution/and_convolution/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/gcd_convolution/lcms.test.cpp
    title: test/src/convolution/gcd_convolution/lcms.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/xor_convolution/xor_convolution.test.cpp
    title: test/src/convolution/xor_convolution/xor_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n\ntemplate <typename T, template <typename> class Transform>\n\
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
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLUTION\n#define SUISEN_CONVOLUTION\n\n#include <vector>\n\
    \nnamespace suisen {\n\ntemplate <typename T, template <typename> class Transform>\n\
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
    \ namespace suisen\n\n\n#endif // SUISEN_CONVOLUTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/convolution/convolution.hpp
  requiredBy:
  - library/convolution/and_convolution.hpp
  - library/convolution/gcd_convolution.hpp
  - library/convolution/or_convolution.hpp
  - library/convolution/subset_convolution.hpp
  - library/convolution/xor_convolution.hpp
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/xor_convolution/xor_convolution.test.cpp
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
  - test/src/convolution/and_convolution/and_convolution.test.cpp
  - test/src/convolution/gcd_convolution/lcms.test.cpp
documentation_of: library/convolution/convolution.hpp
layout: document
redirect_from:
- /library/library/convolution/convolution.hpp
- /library/library/convolution/convolution.hpp.html
title: library/convolution/convolution.hpp
---
