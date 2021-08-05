---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/convolution/or_convolution.hpp
    title: Bitwise Or Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/subset_convolution.hpp
    title: Subset Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/subset_convolution/subset_convolution.test.cpp
    title: test/src/convolution/subset_convolution/subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/transform/subset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n\nnamespace subset_transform {\n\nnamespace\
    \ internal {\n\ntemplate <typename T, typename AssignOp>\nvoid transform(std::vector<T>\
    \ &f, AssignOp assign_op) {\n    const int n = f.size();\n    assert((-n & n)\
    \ == n);\n    for (int k = 1; k < n; k <<= 1) {\n        for (int l = 0; l < n;\
    \ l += 2 * k) {\n            int m = l + k;\n            for (int p = 0; p < k;\
    \ ++p) assign_op(f[m + p], f[l + p]);\n        }\n    }\n}\n\n} // namespace internal\n\
    \ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T> &f, AddAssign\
    \ add_assign) {\n    internal::transform(f, add_assign);\n}\ntemplate <typename\
    \ T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    internal::transform(f, sub_assign);\n}\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\ntemplate <typename\
    \ T>\nvoid mobius(std::vector<T> &f) {\n    mobius(f, [](T &a, const T &b) { a\
    \ -= b; });\n}\n\n} // namespace subset_transform\n\ntemplate <typename T, typename\
    \ AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>\n\
    struct SubsetTransformGeneral {\n    static void transform(std::vector<T> &a)\
    \ {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate\
    \ <typename T>\nstruct SubsetTransform {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_SUBSET_TRANSFORM\n#define SUISEN_SUBSET_TRANSFORM\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n\nnamespace subset_transform\
    \ {\n\nnamespace internal {\n\ntemplate <typename T, typename AssignOp>\nvoid\
    \ transform(std::vector<T> &f, AssignOp assign_op) {\n    const int n = f.size();\n\
    \    assert((-n & n) == n);\n    for (int k = 1; k < n; k <<= 1) {\n        for\
    \ (int l = 0; l < n; l += 2 * k) {\n            int m = l + k;\n            for\
    \ (int p = 0; p < k; ++p) assign_op(f[m + p], f[l + p]);\n        }\n    }\n}\n\
    \n} // namespace internal\n\ntemplate <typename T, typename AddAssign>\nvoid zeta(std::vector<T>\
    \ &f, AddAssign add_assign) {\n    internal::transform(f, add_assign);\n}\ntemplate\
    \ <typename T, typename SubAssign>\nvoid mobius(std::vector<T> &f, SubAssign sub_assign)\
    \ {\n    internal::transform(f, sub_assign);\n}\ntemplate <typename T>\nvoid zeta(std::vector<T>\
    \ &f) {\n    zeta(f, [](T &a, const T &b) { a += b; });\n}\ntemplate <typename\
    \ T>\nvoid mobius(std::vector<T> &f) {\n    mobius(f, [](T &a, const T &b) { a\
    \ -= b; });\n}\n\n} // namespace subset_transform\n\ntemplate <typename T, typename\
    \ AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>\n\
    struct SubsetTransformGeneral {\n    static void transform(std::vector<T> &a)\
    \ {\n        subset_transform::zeta(a, add_assign);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a, sub_assign);\n    }\n};\n\ntemplate\
    \ <typename T>\nstruct SubsetTransform {\n    static void transform(std::vector<T>\
    \ &a) {\n        subset_transform::zeta(a);\n    }\n    static void inverse_transform(std::vector<T>\
    \ &a) {\n        subset_transform::mobius(a);\n    }\n};\n\n} // namespace suisen\n\
    \n\n#endif // SUISEN_SUBSET_TRANSFORM"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/subset.hpp
  requiredBy:
  - library/convolution/or_convolution.hpp
  - library/convolution/subset_convolution.hpp
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/subset_convolution/subset_convolution.test.cpp
documentation_of: library/transform/subset.hpp
layout: document
redirect_from:
- /library/library/transform/subset.hpp
- /library/library/transform/subset.hpp.html
title: library/transform/subset.hpp
---
