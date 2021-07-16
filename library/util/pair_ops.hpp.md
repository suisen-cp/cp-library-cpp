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
  bundledCode: "#line 1 \"library/util/pair_ops.hpp\"\n#include <utility>\n\nnamespace\
    \ suisen {\ntemplate <typename T, typename U>\nstd::pair<T, U>& operator+=(std::pair<T,\
    \ U> &p1, const std::pair<T, U> &p2) {\n    p1.first += p2.first, p1.second +=\
    \ p2.second;\n    return p1;\n}\ntemplate <typename T, typename U>\nstd::pair<T,\
    \ U> operator+(const std::pair<T, U> &p1, const std::pair<T, U> &p2) {\n    return\
    \ {p1.first + p2.first, p1.second + p2.second};\n}\ntemplate <typename T, typename\
    \ U>\nstd::pair<T, U>& operator-=(std::pair<T, U> &p1, const std::pair<T, U> &p2)\
    \ {\n    p1.first -= p2.first, p1.second -= p2.second;\n    return p1;\n}\ntemplate\
    \ <typename T, typename U>\nstd::pair<T, U> operator-(const std::pair<T, U> &p1,\
    \ const std::pair<T, U> &p2) {\n    return {p1.first - p2.first, p1.second - p2.second};\n\
    }\ntemplate <typename T, typename U, typename V>\nstd::pair<T, U>& operator*=(std::pair<T,\
    \ U> &p, const V m) {\n    p.first *= m, p.second *= m;\n    return p;\n}\ntemplate\
    \ <typename T, typename U, typename V>\nstd::pair<T, U> operator*(std::pair<T,\
    \ U> &p, const V m) {\n    return {p.first * m, p.second * m};\n}\n} // namespace\
    \ suisen\n"
  code: "#include <utility>\n\nnamespace suisen {\ntemplate <typename T, typename\
    \ U>\nstd::pair<T, U>& operator+=(std::pair<T, U> &p1, const std::pair<T, U> &p2)\
    \ {\n    p1.first += p2.first, p1.second += p2.second;\n    return p1;\n}\ntemplate\
    \ <typename T, typename U>\nstd::pair<T, U> operator+(const std::pair<T, U> &p1,\
    \ const std::pair<T, U> &p2) {\n    return {p1.first + p2.first, p1.second + p2.second};\n\
    }\ntemplate <typename T, typename U>\nstd::pair<T, U>& operator-=(std::pair<T,\
    \ U> &p1, const std::pair<T, U> &p2) {\n    p1.first -= p2.first, p1.second -=\
    \ p2.second;\n    return p1;\n}\ntemplate <typename T, typename U>\nstd::pair<T,\
    \ U> operator-(const std::pair<T, U> &p1, const std::pair<T, U> &p2) {\n    return\
    \ {p1.first - p2.first, p1.second - p2.second};\n}\ntemplate <typename T, typename\
    \ U, typename V>\nstd::pair<T, U>& operator*=(std::pair<T, U> &p, const V m) {\n\
    \    p.first *= m, p.second *= m;\n    return p;\n}\ntemplate <typename T, typename\
    \ U, typename V>\nstd::pair<T, U> operator*(std::pair<T, U> &p, const V m) {\n\
    \    return {p.first * m, p.second * m};\n}\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/util/pair_ops.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/pair_ops.hpp
layout: document
redirect_from:
- /library/library/util/pair_ops.hpp
- /library/library/util/pair_ops.hpp.html
title: library/util/pair_ops.hpp
---
