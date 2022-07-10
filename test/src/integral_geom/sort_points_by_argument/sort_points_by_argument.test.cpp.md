---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/sort_points_by_argument.hpp
    title: library/integral_geom/sort_points_by_argument.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\
    \n#include <iostream>\n\n#line 1 \"library/integral_geom/sort_points_by_argument.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    /**\n     * 1. (x < 0, y = 0) -> pi\n     * 2. (x = 0, y = 0) -> 0\n\
    \     * 3. points with same argument -> arbitrary order\n     */\n    template\
    \ <typename T>\n    bool compare_by_atan2(const std::pair<T, T> &p, const std::pair<T,\
    \ T> &q) {\n        const auto &[x1, y1] = p;\n        const auto &[x2, y2] =\
    \ q;\n        if ((y1 < 0) xor (y2 < 0)) return y1 < y2;\n        if ((x1 < 0)\
    \ xor (x2 < 0)) return (y1 >= 0) xor (x1 < x2);\n        if (x1 == 0 and y1 ==\
    \ 0) return true;\n        if (x2 == 0 and y2 == 0) return false;\n        return\
    \ ((long long) y1 * x2 < (long long) y2 * x1);\n    }\n    template <typename\
    \ T>\n    void sort_points_by_argument(std::vector<std::pair<T, T>> &points) {\n\
    \        std::sort(points.begin(), points.end(), compare_by_atan2<T>);\n    }\n\
    } // namespace suisen::integral_geometry\n\n\n\n#line 6 \"test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::pair<int, int>> points(n);\n\
    \    for (auto &[x, y] : points) std::cin >> x >> y;\n    \n    suisen::integral_geometry::sort_points_by_argument(points);\n\
    \n    for (auto &[x, y] : points) {\n        std::cout << x << ' ' << y << '\\\
    n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n\n#include <iostream>\n\n#include \"library/integral_geom/sort_points_by_argument.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::pair<int, int>> points(n);\n\
    \    for (auto &[x, y] : points) std::cin >> x >> y;\n    \n    suisen::integral_geometry::sort_points_by_argument(points);\n\
    \n    for (auto &[x, y] : points) {\n        std::cout << x << ' ' << y << '\\\
    n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/integral_geom/sort_points_by_argument.hpp
  isVerificationFile: true
  path: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 16:40:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
- /verify/test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp.html
title: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
---
