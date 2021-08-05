---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution.hpp
    title: library/convolution/convolution.hpp
  - icon: ':heavy_check_mark:'
    path: library/transform/subset.hpp
    title: library/transform/subset.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/or_convolution.hpp\"\n\n\n\n#line 1\
    \ \"library/transform/subset.hpp\"\n\n\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace suisen {\n\nnamespace subset_transform {\n\nnamespace internal {\n\
    \ntemplate <typename T, typename AssignOp>\nvoid transform(std::vector<T> &f,\
    \ AssignOp assign_op) {\n    const int n = f.size();\n    assert((-n & n) == n);\n\
    \    for (int k = 1; k < n; k <<= 1) {\n        for (int l = 0; l < n; l += 2\
    \ * k) {\n            int m = l + k;\n            for (int p = 0; p < k; ++p)\
    \ assign_op(f[m + p], f[l + p]);\n        }\n    }\n}\n\n} // namespace internal\n\
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
    \ namespace suisen\n\n\n\n#line 6 \"library/convolution/or_convolution.hpp\"\n\
    \nnamespace suisen {\ntemplate <typename T>\nusing OrConvolution = Convolution<T,\
    \ SubsetTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> or_convolution(Args\
    \ &&...args) {\n    return OrConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_OR_CONVOLUTION\n#define SUISEN_OR_CONVOLUTION\n\n#include\
    \ \"library/transform/subset.hpp\"\n#include \"library/convolution/convolution.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T>\nusing OrConvolution = Convolution<T,\
    \ SubsetTransform>;\ntemplate <typename T, typename ...Args>\nstd::vector<T> or_convolution(Args\
    \ &&...args) {\n    return OrConvolution<T>::convolution(std::forward<Args>(args)...);\n\
    }\n} // namespace suisen\n\n#endif // SUISEN_OR_CONVOLUTION\n"
  dependsOn:
  - library/transform/subset.hpp
  - library/convolution/convolution.hpp
  isVerificationFile: false
  path: library/convolution/or_convolution.hpp
  requiredBy: []
  timestamp: '2021-08-05 18:57:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/convolution/or_convolution.hpp
layout: document
redirect_from:
- /library/library/convolution/or_convolution.hpp
- /library/library/convolution/or_convolution.hpp.html
title: library/convolution/or_convolution.hpp
---
