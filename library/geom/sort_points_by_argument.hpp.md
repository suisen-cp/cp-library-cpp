---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/geom/sort_points_by_argument/sort_points_by_argument.test.cpp
    title: test/src/geom/sort_points_by_argument/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/geom/sort_points_by_argument.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * 1. (x\
    \ < 0, y = 0) -> pi\n     * 2. (x = 0, y = 0) -> 0\n     * 3. points with same\
    \ argument -> arbitrary order\n     */\n    bool compare_by_atan2(const std::pair<int,\
    \ int> &p, const std::pair<int, int> &q) {\n        const auto &[x1, y1] = p;\n\
    \        const auto &[x2, y2] = q;\n        if ((y1 < 0) xor (y2 < 0)) return\
    \ y1 < y2;\n        if ((x1 < 0) xor (x2 < 0)) return (y1 >= 0) xor (x1 < x2);\n\
    \        if (x1 == 0 and y1 == 0) return true;\n        if (x2 == 0 and y2 ==\
    \ 0) return false;\n        return ((long long) y1 * x2 < (long long) y2 * x1);\n\
    \    }\n    void sort_points_by_argument(std::vector<std::pair<int, int>> &points)\
    \ {\n        std::sort(points.begin(), points.end(), compare_by_atan2);\n    }\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SORT_POINTS_BY_ARGUMENT\n#define SUISEN_SORT_POINTS_BY_ARGUMENT\n\
    \n#include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    /**\n   \
    \  * 1. (x < 0, y = 0) -> pi\n     * 2. (x = 0, y = 0) -> 0\n     * 3. points\
    \ with same argument -> arbitrary order\n     */\n    bool compare_by_atan2(const\
    \ std::pair<int, int> &p, const std::pair<int, int> &q) {\n        const auto\
    \ &[x1, y1] = p;\n        const auto &[x2, y2] = q;\n        if ((y1 < 0) xor\
    \ (y2 < 0)) return y1 < y2;\n        if ((x1 < 0) xor (x2 < 0)) return (y1 >=\
    \ 0) xor (x1 < x2);\n        if (x1 == 0 and y1 == 0) return true;\n        if\
    \ (x2 == 0 and y2 == 0) return false;\n        return ((long long) y1 * x2 < (long\
    \ long) y2 * x1);\n    }\n    void sort_points_by_argument(std::vector<std::pair<int,\
    \ int>> &points) {\n        std::sort(points.begin(), points.end(), compare_by_atan2);\n\
    \    }\n} // namespace suisen\n\n\n#endif // SUISEN_SORT_POINTS_BY_ARGUMENT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/geom/sort_points_by_argument.hpp
  requiredBy: []
  timestamp: '2022-06-28 04:44:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/geom/sort_points_by_argument/sort_points_by_argument.test.cpp
documentation_of: library/geom/sort_points_by_argument.hpp
layout: document
title: "\u6574\u6570\u6F14\u7B97\u306B\u3088\u308B\u504F\u89D2\u30BD\u30FC\u30C8"
---
## 整数演算による偏角ソート