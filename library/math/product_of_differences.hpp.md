---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/polynomial/multi_point_eval.hpp
    title: Multi Point Evaluation
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/polynomial/lagrange_interpolation.hpp
    title: "\u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u88DC\u9593"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/math/product_of_differences/yuki1938.test.cpp
    title: test/src/math/product_of_differences/yuki1938.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
    title: test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - icon: ':x:'
    path: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
    title: test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/product_of_differences.hpp\"\n\n\n\n#include\
    \ <deque>\n#line 1 \"library/polynomial/multi_point_eval.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename FPSType, typename T>\n\
    \    std::vector<typename FPSType::value_type> multi_point_eval(const FPSType&\
    \ f, const std::vector<T>& xs) {\n        int n = xs.size();\n        std::vector<FPSType>\
    \ seg(2 * n);\n        for (int i = 0; i < n; ++i) seg[n + i] = FPSType{ -xs[i],\
    \ 1 };\n        for (int i = n - 1; i > 0; --i) seg[i] = seg[i * 2] * seg[i *\
    \ 2 + 1];\n        seg[1] = f % seg[1];\n        for (int i = 2; i < 2 * n; ++i)\
    \ seg[i] = seg[i / 2] % seg[i];\n        std::vector<typename FPSType::value_type>\
    \ ys(n);\n        for (int i = 0; i < n; ++i) ys[i] = seg[n + i][0];\n       \
    \ return ys;\n    }\n} // namespace suisen\n\n\n#line 6 \"library/math/product_of_differences.hpp\"\
    \n\nnamespace suisen {\n    /**\n     * O(N(logN)^2)\n     * return the vector\
    \ p of length xs.size() s.t. p[i]=\u03A0[j!=i](x[i]-x[j])\n     */\n    template\
    \ <typename FPSType, typename T>\n    std::vector<typename FPSType::value_type>\
    \ product_of_differences(const std::vector<T>& xs) {\n        // f(x):=\u03A0\
    _i(x-x[i])\n        // => f'(x)=\u03A3_i \u03A0[j!=i](x-x[j])\n        // => f'(x[i])=\u03A0\
    [j!=i](x[i]-x[j])\n        const int n = xs.size();\n        std::deque<FPSType>\
    \ dq;\n        for (int i = 0; i < n; ++i) dq.push_back(FPSType{ -xs[i], 1 });\n\
    \        while (dq.size() >= 2) {\n            auto f = std::move(dq.front());\n\
    \            dq.pop_front();\n            auto g = std::move(dq.front());\n  \
    \          dq.pop_front();\n            dq.push_back(f * g);\n        }\n    \
    \    auto f = std::move(dq.front());\n        f.diff_inplace();\n        return\
    \ multi_point_eval<FPSType, T>(f, xs);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_PRODUCT_OF_DIFFERNCES\n#define SUISEN_PRODUCT_OF_DIFFERNCES\n\
    \n#include <deque>\n#include \"library/polynomial/multi_point_eval.hpp\"\n\nnamespace\
    \ suisen {\n    /**\n     * O(N(logN)^2)\n     * return the vector p of length\
    \ xs.size() s.t. p[i]=\u03A0[j!=i](x[i]-x[j])\n     */\n    template <typename\
    \ FPSType, typename T>\n    std::vector<typename FPSType::value_type> product_of_differences(const\
    \ std::vector<T>& xs) {\n        // f(x):=\u03A0_i(x-x[i])\n        // => f'(x)=\u03A3\
    _i \u03A0[j!=i](x-x[j])\n        // => f'(x[i])=\u03A0[j!=i](x[i]-x[j])\n    \
    \    const int n = xs.size();\n        std::deque<FPSType> dq;\n        for (int\
    \ i = 0; i < n; ++i) dq.push_back(FPSType{ -xs[i], 1 });\n        while (dq.size()\
    \ >= 2) {\n            auto f = std::move(dq.front());\n            dq.pop_front();\n\
    \            auto g = std::move(dq.front());\n            dq.pop_front();\n  \
    \          dq.push_back(f * g);\n        }\n        auto f = std::move(dq.front());\n\
    \        f.diff_inplace();\n        return multi_point_eval<FPSType, T>(f, xs);\n\
    \    }\n} // namespace suisen\n\n\n#endif // SUISEN_PRODUCT_OF_DIFFERNCES\n"
  dependsOn:
  - library/polynomial/multi_point_eval.hpp
  isVerificationFile: false
  path: library/math/product_of_differences.hpp
  requiredBy:
  - library/polynomial/lagrange_interpolation.hpp
  timestamp: '2022-07-23 23:55:26+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/polynomial/lagrange_interpolation/dummy.test.cpp
  - test/src/polynomial/lagrange_interpolation/dummy_2.test.cpp
  - test/src/polynomial/lagrange_interpolation/cumulative_sum.test.cpp
  - test/src/math/product_of_differences/yuki1938.test.cpp
documentation_of: library/math/product_of_differences.hpp
layout: document
title: Product Of Differences
---
## Product Of Differences