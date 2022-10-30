---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/number/kth_root_round/kth_root_integer.test.cpp
    title: test/src/number/kth_root_round/kth_root_integer.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/kth_root_round.hpp\"\n\n\n\n#include <cmath>\n\
    #include <type_traits>\n\nnamespace suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T floor_kth_root(T x, int k) {\n        if (k\
    \ == 1 or x == 0 or x == 1) return x;\n        if (k == 2) return ::sqrtl(x);\n\
    \        if (k >= 64) return 1;\n        T res = ::powl(x, ::nextafterl(1 / (long\
    \ double) k, 0));\n        while (::powl(res + 1, k) <= x) ++res;\n        return\
    \ res;\n    }\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T ceil_kth_root(T x, int k) {\n        T res\
    \ = floor_kth_root(x, k);\n        res += ::powl(res, k) < x;\n        return\
    \ res;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_KTH_ROOT_ROUND\n#define SUISEN_KTH_ROOT_ROUND\n\n#include\
    \ <cmath>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ floor_kth_root(T x, int k) {\n        if (k == 1 or x == 0 or x == 1) return\
    \ x;\n        if (k == 2) return ::sqrtl(x);\n        if (k >= 64) return 1;\n\
    \        T res = ::powl(x, ::nextafterl(1 / (long double) k, 0));\n        while\
    \ (::powl(res + 1, k) <= x) ++res;\n        return res;\n    }\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    T\
    \ ceil_kth_root(T x, int k) {\n        T res = floor_kth_root(x, k);\n       \
    \ res += ::powl(res, k) < x;\n        return res;\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_KTH_ROOT_ROUND\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/kth_root_round.hpp
  requiredBy: []
  timestamp: '2022-10-20 19:29:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/kth_root_round/kth_root_integer.test.cpp
documentation_of: library/number/kth_root_round.hpp
layout: document
title: $\lfloor a ^ {\frac{1}{k}}\rfloor, \lceil a ^ {\frac{1}{k}}\rceil$
---
## $\lfloor a ^ {\frac{1}{k}}\rfloor, \lceil a ^ {\frac{1}{k}}\rceil$
