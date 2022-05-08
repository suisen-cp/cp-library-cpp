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
  bundledCode: "#line 1 \"library/integral_geom/convex_hull.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace suisen {\nnamespace\
    \ integral_geometry {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<int> convex_hull(const std::vector<std::pair<T,\
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
    \ = true;\n        }\n        return res;\n    }\n}\n} // namespace suisen\n\n\
    \n"
  code: "#ifndef SUISEN_CONVEX_HULL_INTEGRAL\n#define SUISEN_CONVEX_HULL_INTEGRAL\n\
    \n#include <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace suisen\
    \ {\nnamespace integral_geometry {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<int> convex_hull(const std::vector<std::pair<T,\
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
    \ = true;\n        }\n        return res;\n    }\n}\n} // namespace suisen\n\n\
    #endif // SUISEN_CONVEX_HULL_INTEGRAL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/convex_hull.hpp
  requiredBy: []
  timestamp: '2021-08-25 03:07:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/integral_geom/convex_hull.hpp
layout: document
title: "Convex Hull (\u6574\u6570\u5EA7\u6A19)"
---
## Convex Hull (整数座標)