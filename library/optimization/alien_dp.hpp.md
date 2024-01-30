---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/optimization/alien_dp/abc218_h_1.test.cpp
    title: test/src/optimization/alien_dp/abc218_h_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/optimization/alien_dp/abc218_h_2.test.cpp
    title: test/src/optimization/alien_dp/abc218_h_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/optimization/alien_dp/arc168_e_1.test.cpp
    title: test/src/optimization/alien_dp/arc168_e_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/optimization/alien_dp/arc168_e_2.test.cpp
    title: test/src/optimization/alien_dp/arc168_e_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 'evaluates f(x) (f: convex)'
    links: []
  bundledCode: "#line 1 \"library/optimization/alien_dp.hpp\"\n\n\n\n#include <type_traits>\n\
    #include <utility>\n\nnamespace suisen {\n    /**\n     * @brief evaluates f(x)\
    \ (f: convex)\n     * @param g p -> inf(f(x)-px)\n     */\n    template <typename\
    \ Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<Cost, DP, Cost>, std::nullptr_t>\
    \ = nullptr>\n    Cost alien_convex(int x, Cost min_slope, Cost max_slope, DP\
    \ g) {\n        // x <= max (argmin (f(x)-rx))\n        Cost lp = min_slope -\
    \ 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n            Cost p =\
    \ (lp + rp) / 2;\n            // xp: max (argmin f(x)-px) (= min (argmin f(x)-(p+1)x))\n\
    \            int xp = g(p) - g(p + 1);\n            (x <= xp ? rp : lp) = p;\n\
    \        }\n        return g(rp) + Cost(rp) * x;\n    }\n    /**\n     * @brief\
    \ evaluates f(x) (f: convex)\n     * @param g p -> { inf(f(x)-px), min argmin(f(x)-px)\
    \ }\n     */\n    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost,\
    \ int>, DP, Cost>, std::nullptr_t> = nullptr>\n    Cost alien_convex(int x, Cost\
    \ min_slope, Cost max_slope, DP g) {\n        Cost lp = min_slope - 1, rp = max_slope\
    \ + 1;\n        while (rp - lp > 1) {\n            Cost p = (lp + rp) / 2;\n \
    \           // g(p).second: min (argmin f(x)-px)\n            (g(p).second <=\
    \ x ? lp : rp) = p;\n        }\n        return g(lp).first + Cost(lp) * x;\n \
    \   }\n\n    /**\n     * @brief evaluates f(x) (f: concave)\n     * @param g p\
    \ -> sup(f(x)-px)\n     */\n    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<Cost,\
    \ DP, Cost>, std::nullptr_t> = nullptr>\n    Cost alien_concave(int x, Cost min_slope,\
    \ Cost max_slope, DP g) {\n        // min (argmax f(x)-rx) <= x\n        Cost\
    \ lp = min_slope - 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n   \
    \         Cost p = (lp + rp) / 2;\n            // xp: min (argmax f(x)-px) (=\
    \ max (argmax f(x)-(p+1)x))\n            int xp = g(p) - g(p + 1);\n         \
    \   (xp <= x ? rp : lp) = p;\n        }\n        return g(rp) + Cost(rp) * x;\n\
    \    }\n    /**\n     * @brief evaluates f(x) (f: concave)\n     * @param g p\
    \ -> { sup(f(x)-px), max argmax(f(x)-px) }\n     */\n    template <typename Cost,\
    \ typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost, int>, DP,\
    \ Cost>, std::nullptr_t> = nullptr>\n    Cost alien_concave(int x, Cost min_slope,\
    \ Cost max_slope, DP g) {\n        // x <= max (argmax f(x)-lx)\n        Cost\
    \ lp = min_slope - 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n   \
    \         Cost p = (lp + rp) / 2;\n            // g(p).second: max (argmax f(x)-px)\n\
    \            (x <= g(p).second ? lp : rp) = p;\n        }\n        return g(lp).first\
    \ + Cost(lp) * x;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_ALIEN\n#define SUISEN_ALIEN\n\n#include <type_traits>\n#include\
    \ <utility>\n\nnamespace suisen {\n    /**\n     * @brief evaluates f(x) (f: convex)\n\
    \     * @param g p -> inf(f(x)-px)\n     */\n    template <typename Cost, typename\
    \ DP, std::enable_if_t<std::is_invocable_r_v<Cost, DP, Cost>, std::nullptr_t>\
    \ = nullptr>\n    Cost alien_convex(int x, Cost min_slope, Cost max_slope, DP\
    \ g) {\n        // x <= max (argmin (f(x)-rx))\n        Cost lp = min_slope -\
    \ 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n            Cost p =\
    \ (lp + rp) / 2;\n            // xp: max (argmin f(x)-px) (= min (argmin f(x)-(p+1)x))\n\
    \            int xp = g(p) - g(p + 1);\n            (x <= xp ? rp : lp) = p;\n\
    \        }\n        return g(rp) + Cost(rp) * x;\n    }\n    /**\n     * @brief\
    \ evaluates f(x) (f: convex)\n     * @param g p -> { inf(f(x)-px), min argmin(f(x)-px)\
    \ }\n     */\n    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost,\
    \ int>, DP, Cost>, std::nullptr_t> = nullptr>\n    Cost alien_convex(int x, Cost\
    \ min_slope, Cost max_slope, DP g) {\n        Cost lp = min_slope - 1, rp = max_slope\
    \ + 1;\n        while (rp - lp > 1) {\n            Cost p = (lp + rp) / 2;\n \
    \           // g(p).second: min (argmin f(x)-px)\n            (g(p).second <=\
    \ x ? lp : rp) = p;\n        }\n        return g(lp).first + Cost(lp) * x;\n \
    \   }\n\n    /**\n     * @brief evaluates f(x) (f: concave)\n     * @param g p\
    \ -> sup(f(x)-px)\n     */\n    template <typename Cost, typename DP, std::enable_if_t<std::is_invocable_r_v<Cost,\
    \ DP, Cost>, std::nullptr_t> = nullptr>\n    Cost alien_concave(int x, Cost min_slope,\
    \ Cost max_slope, DP g) {\n        // min (argmax f(x)-rx) <= x\n        Cost\
    \ lp = min_slope - 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n   \
    \         Cost p = (lp + rp) / 2;\n            // xp: min (argmax f(x)-px) (=\
    \ max (argmax f(x)-(p+1)x))\n            int xp = g(p) - g(p + 1);\n         \
    \   (xp <= x ? rp : lp) = p;\n        }\n        return g(rp) + Cost(rp) * x;\n\
    \    }\n    /**\n     * @brief evaluates f(x) (f: concave)\n     * @param g p\
    \ -> { sup(f(x)-px), max argmax(f(x)-px) }\n     */\n    template <typename Cost,\
    \ typename DP, std::enable_if_t<std::is_invocable_r_v<std::pair<Cost, int>, DP,\
    \ Cost>, std::nullptr_t> = nullptr>\n    Cost alien_concave(int x, Cost min_slope,\
    \ Cost max_slope, DP g) {\n        // x <= max (argmax f(x)-lx)\n        Cost\
    \ lp = min_slope - 1, rp = max_slope + 1;\n        while (rp - lp > 1) {\n   \
    \         Cost p = (lp + rp) / 2;\n            // g(p).second: max (argmax f(x)-px)\n\
    \            (x <= g(p).second ? lp : rp) = p;\n        }\n        return g(lp).first\
    \ + Cost(lp) * x;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_ALIEN\n"
  dependsOn: []
  isVerificationFile: false
  path: library/optimization/alien_dp.hpp
  requiredBy: []
  timestamp: '2024-01-30 21:41:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/optimization/alien_dp/abc218_h_2.test.cpp
  - test/src/optimization/alien_dp/arc168_e_2.test.cpp
  - test/src/optimization/alien_dp/abc218_h_1.test.cpp
  - test/src/optimization/alien_dp/arc168_e_1.test.cpp
documentation_of: library/optimization/alien_dp.hpp
layout: document
title: Alien Dp
---
## Alien Dp
