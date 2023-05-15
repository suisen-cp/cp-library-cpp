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
  bundledCode: "#line 1 \"library/util/sum_count.hpp\"\n\n\n\nnamespace suisen {\n\
    \    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b=sum)\n \
    \   template <typename T, typename R = T>\n    constexpr R sum_count(T min_a,\
    \ T max_a, T min_b, T max_b, T sum) {\n        // max(min_a, sum - max_b) <= a\
    \ <= min(max_a, x - min_b)\n        return std::max<R>(0, std::min<R>(max_a, sum\
    \ - min_b) - std::max<R>(min_a, sum - max_b) + 1);\n    }\n\n    // # of (a, b)\
    \ s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<=max_sum)\n    template <typename\
    \ T, typename R = T>\n    constexpr R sum_count_leq(T min_a, T max_a, T min_b,\
    \ T max_b, T max_sum) {\n        // count # of (a,b) s.t. 0<=a<=ra and 0<=b<=rb\
    \ and a+b<=rs\n        const R ra = R(max_a) - R(min_a), rb = R(max_b) - R(min_b),\
    \ rs = R(max_sum) - R(min_a + min_b);\n        if (ra < 0 or rb < 0 or rs < 0)\
    \ {\n            return 0;\n        }\n        const R t = std::max<R>(0, std::min<R>(ra,\
    \ rs - rb) + 1);\n        // Case 1. 0<=a<t  : 0<=b<=rb   <===> a+b<=rs\n    \
    \    // Case 2. t<=a<=ra: 0<=b<=rs-a <===> a+b<=rs\n        // fr + ... + (to-1)\n\
    \        const R fr = rs - std::min<R>(ra, rs) + 1, to = rs - t + 2 /* >= 1 */;\n\
    \        return t * (rb + 1) + (to - fr) * (fr + to - 1) / 2;\n    }\n\n    //\
    \ # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<x)\n    template\
    \ <typename T, typename R = T>\n    constexpr R sum_count_lt(T min_a, T max_a,\
    \ T min_b, T max_b, T x) {\n        return sum_count_leq(min_a, max_a, min_b,\
    \ max_b, x - 1);\n    }\n\n    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b\
    \ and a+b>=min_sum)\n    template <typename T, typename R = T>\n    constexpr\
    \ R sum_count_geq(T min_a, T max_a, T min_b, T max_b, T min_sum) {\n        return\
    \ std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b + 1) - sum_count_lt(min_a,\
    \ max_a, min_b, max_b, min_sum);\n    }\n\n    // # of (a, b) s.t. (min_a<=a<=max_a\
    \ and min_b<=b<=max_b and a+b>x)\n    template <typename T, typename R = T>\n\
    \    constexpr R sum_count_gt(T min_a, T max_a, T min_b, T max_b, T x) {\n   \
    \     return std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b\
    \ + 1) - sum_count_leq(min_a, max_a, min_b, max_b, x);\n    }\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_SUM_COUNT\n#define SUISEN_SUM_COUNT\n\nnamespace suisen {\n\
    \    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b=sum)\n \
    \   template <typename T, typename R = T>\n    constexpr R sum_count(T min_a,\
    \ T max_a, T min_b, T max_b, T sum) {\n        // max(min_a, sum - max_b) <= a\
    \ <= min(max_a, x - min_b)\n        return std::max<R>(0, std::min<R>(max_a, sum\
    \ - min_b) - std::max<R>(min_a, sum - max_b) + 1);\n    }\n\n    // # of (a, b)\
    \ s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<=max_sum)\n    template <typename\
    \ T, typename R = T>\n    constexpr R sum_count_leq(T min_a, T max_a, T min_b,\
    \ T max_b, T max_sum) {\n        // count # of (a,b) s.t. 0<=a<=ra and 0<=b<=rb\
    \ and a+b<=rs\n        const R ra = R(max_a) - R(min_a), rb = R(max_b) - R(min_b),\
    \ rs = R(max_sum) - R(min_a + min_b);\n        if (ra < 0 or rb < 0 or rs < 0)\
    \ {\n            return 0;\n        }\n        const R t = std::max<R>(0, std::min<R>(ra,\
    \ rs - rb) + 1);\n        // Case 1. 0<=a<t  : 0<=b<=rb   <===> a+b<=rs\n    \
    \    // Case 2. t<=a<=ra: 0<=b<=rs-a <===> a+b<=rs\n        // fr + ... + (to-1)\n\
    \        const R fr = rs - std::min<R>(ra, rs) + 1, to = rs - t + 2 /* >= 1 */;\n\
    \        return t * (rb + 1) + (to - fr) * (fr + to - 1) / 2;\n    }\n\n    //\
    \ # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b and a+b<x)\n    template\
    \ <typename T, typename R = T>\n    constexpr R sum_count_lt(T min_a, T max_a,\
    \ T min_b, T max_b, T x) {\n        return sum_count_leq(min_a, max_a, min_b,\
    \ max_b, x - 1);\n    }\n\n    // # of (a, b) s.t. (min_a<=a<=max_a and min_b<=b<=max_b\
    \ and a+b>=min_sum)\n    template <typename T, typename R = T>\n    constexpr\
    \ R sum_count_geq(T min_a, T max_a, T min_b, T max_b, T min_sum) {\n        return\
    \ std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b + 1) - sum_count_lt(min_a,\
    \ max_a, min_b, max_b, min_sum);\n    }\n\n    // # of (a, b) s.t. (min_a<=a<=max_a\
    \ and min_b<=b<=max_b and a+b>x)\n    template <typename T, typename R = T>\n\
    \    constexpr R sum_count_gt(T min_a, T max_a, T min_b, T max_b, T x) {\n   \
    \     return std::max<R>(0, max_a - min_a + 1) * std::max<R>(0, max_b - min_b\
    \ + 1) - sum_count_leq(min_a, max_a, min_b, max_b, x);\n    }\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_SUM_COUNT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/sum_count.hpp
  requiredBy: []
  timestamp: '2023-05-13 02:46:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/util/sum_count.hpp
layout: document
redirect_from:
- /library/library/util/sum_count.hpp
- /library/library/util/sum_count.hpp.html
title: library/util/sum_count.hpp
---
