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
  bundledCode: "#line 1 \"library/util/vector_ops.hpp\"\n#include <vector>\n\nnamespace\
    \ suisen {\ntemplate <typename T>\nstd::vector<T>& operator+=(std::vector<T> &a,\
    \ const std::vector<T> &b) {\n    int n = a.size();\n    a.resize(n + b.size());\n\
    \    std::copy(b.begin(), b.end(), a.begin() + n);\n    return a;\n}\ntemplate\
    \ <typename T>\nstd::vector<T> operator+(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n    std::vector<T> c = a; return c += b;\n}\ntemplate <typename T>\n\
    std::vector<T>& operator+=(std::vector<T> &a, const T &b) {\n    a.push_back(b);\
    \ return a;\n}\ntemplate <typename T>\nstd::vector<T> operator+(const std::vector<T>\
    \ &a, const T &b) {\n    std::vector<T> c = a; return c += b;\n}\ntemplate <typename\
    \ T>\nstd::vector<T>& operator+=(std::vector<T> &a, const T &&b) {\n    a.push_back(b);\
    \ return a;\n}\ntemplate <typename T>\nstd::vector<T> operator+(const std::vector<T>\
    \ &a, const T &&b) {\n    std::vector<T> c = a; return c += b;\n}\ntemplate <typename\
    \ T>\nstd::vector<T>& operator*=(std::vector<T> &a, const int repeat) {\n    int\
    \ n = a.size();\n    a.resize(n * repeat);\n    for (int i = 1; i < repeat; ++i)\
    \ std::copy(a.begin(), a.end(), a.begin() + i * n);\n    return a;\n}\ntemplate\
    \ <typename T>\nstd::vector<T> operator*(std::vector<T> &a, const int repeat)\
    \ {\n    std::vector<T> c = a; return c *= repeat;\n}\n} // namespace suisen\n"
  code: "#include <vector>\n\nnamespace suisen {\ntemplate <typename T>\nstd::vector<T>&\
    \ operator+=(std::vector<T> &a, const std::vector<T> &b) {\n    int n = a.size();\n\
    \    a.resize(n + b.size());\n    std::copy(b.begin(), b.end(), a.begin() + n);\n\
    \    return a;\n}\ntemplate <typename T>\nstd::vector<T> operator+(const std::vector<T>\
    \ &a, const std::vector<T> &b) {\n    std::vector<T> c = a; return c += b;\n}\n\
    template <typename T>\nstd::vector<T>& operator+=(std::vector<T> &a, const T &b)\
    \ {\n    a.push_back(b); return a;\n}\ntemplate <typename T>\nstd::vector<T> operator+(const\
    \ std::vector<T> &a, const T &b) {\n    std::vector<T> c = a; return c += b;\n\
    }\ntemplate <typename T>\nstd::vector<T>& operator+=(std::vector<T> &a, const\
    \ T &&b) {\n    a.push_back(b); return a;\n}\ntemplate <typename T>\nstd::vector<T>\
    \ operator+(const std::vector<T> &a, const T &&b) {\n    std::vector<T> c = a;\
    \ return c += b;\n}\ntemplate <typename T>\nstd::vector<T>& operator*=(std::vector<T>\
    \ &a, const int repeat) {\n    int n = a.size();\n    a.resize(n * repeat);\n\
    \    for (int i = 1; i < repeat; ++i) std::copy(a.begin(), a.end(), a.begin()\
    \ + i * n);\n    return a;\n}\ntemplate <typename T>\nstd::vector<T> operator*(std::vector<T>\
    \ &a, const int repeat) {\n    std::vector<T> c = a; return c *= repeat;\n}\n\
    } // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/util/vector_ops.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/vector_ops.hpp
layout: document
redirect_from:
- /library/library/util/vector_ops.hpp
- /library/library/util/vector_ops.hpp.html
title: library/util/vector_ops.hpp
---
