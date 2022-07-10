---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
    title: test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
  - icon: ':x:'
    path: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
    title: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/integral_geom/convex_hull.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<int> convex_hull(const std::vector<std::pair<T,\
    \ T>> &points) {\n        const int n = points.size();\n        std::vector<int>\
    \ sorted(n);\n        std::iota(sorted.begin(), sorted.end(), 0);\n        std::sort(sorted.begin(),\
    \ sorted.end(), [&points](int i, int j) {\n            auto &a = points[i], &b\
    \ = points[j];\n            return a.first == b.first ? a.second < b.second :\
    \ a.first < b.first;\n        });\n        std::vector<char> used(n, false);\n\
    \        sorted.resize(2 * n - 1);\n        std::copy(sorted.rbegin() + n, sorted.rend(),\
    \ sorted.begin() + n);\n        std::vector<int> res;\n        res.reserve(n);\n\
    \        int first = sorted[0], last = sorted[n - 1];\n        auto isp_pos =\
    \ [](T x1, T y1, T x2, T y2) -> bool {\n            T det = x1 * y2 - y1 * x2;\n\
    \            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);\n       \
    \ };\n        for (int k : sorted) {\n            if (k != first and used[k])\
    \ continue;\n            for (int sz = res.size(); sz >= 2; --sz) {\n        \
    \        int i = res[sz - 2], j = res[sz - 1];\n                if (j == last)\
    \ break;\n                T ab_x = points[j].first - points[i].first, ab_y = points[j].second\
    \ - points[i].second;\n                T bc_x = points[k].first - points[j].first,\
    \ bc_y = points[k].second - points[j].second;\n                if (isp_pos(ab_x,\
    \ ab_y, bc_x, bc_y)) break;\n                res.pop_back(), used[j] = false;\n\
    \            }\n            if (not used[k]) res.push_back(k);\n            used[k]\
    \ = true;\n        }\n        return res;\n    }\n} // namespace suisen::integral_geometry\n\
    \n\n"
  code: "#ifndef SUISEN_CONVEX_HULL_INTEGRAL\n#define SUISEN_CONVEX_HULL_INTEGRAL\n\
    \n#include <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    std::vector<int> convex_hull(const std::vector<std::pair<T,\
    \ T>> &points) {\n        const int n = points.size();\n        std::vector<int>\
    \ sorted(n);\n        std::iota(sorted.begin(), sorted.end(), 0);\n        std::sort(sorted.begin(),\
    \ sorted.end(), [&points](int i, int j) {\n            auto &a = points[i], &b\
    \ = points[j];\n            return a.first == b.first ? a.second < b.second :\
    \ a.first < b.first;\n        });\n        std::vector<char> used(n, false);\n\
    \        sorted.resize(2 * n - 1);\n        std::copy(sorted.rbegin() + n, sorted.rend(),\
    \ sorted.begin() + n);\n        std::vector<int> res;\n        res.reserve(n);\n\
    \        int first = sorted[0], last = sorted[n - 1];\n        auto isp_pos =\
    \ [](T x1, T y1, T x2, T y2) -> bool {\n            T det = x1 * y2 - y1 * x2;\n\
    \            return det > 0 or (det == 0 and x1 * x2 + y1 * y2 > 0);\n       \
    \ };\n        for (int k : sorted) {\n            if (k != first and used[k])\
    \ continue;\n            for (int sz = res.size(); sz >= 2; --sz) {\n        \
    \        int i = res[sz - 2], j = res[sz - 1];\n                if (j == last)\
    \ break;\n                T ab_x = points[j].first - points[i].first, ab_y = points[j].second\
    \ - points[i].second;\n                T bc_x = points[k].first - points[j].first,\
    \ bc_y = points[k].second - points[j].second;\n                if (isp_pos(ab_x,\
    \ ab_y, bc_x, bc_y)) break;\n                res.pop_back(), used[j] = false;\n\
    \            }\n            if (not used[k]) res.push_back(k);\n            used[k]\
    \ = true;\n        }\n        return res;\n    }\n} // namespace suisen::integral_geometry\n\
    \n#endif // SUISEN_CONVEX_HULL_INTEGRAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/convex_hull.hpp
  requiredBy: []
  timestamp: '2022-07-10 16:40:31+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
  - test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
documentation_of: library/integral_geom/convex_hull.hpp
layout: document
title: "\u51F8\u5305 (\u6574\u6570\u5EA7\u6A19)"
---
## 凸包 (整数座標)
