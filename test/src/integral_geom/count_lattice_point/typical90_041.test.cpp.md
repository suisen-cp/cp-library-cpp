---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/convex_hull.hpp
    title: "\u51F8\u5305 (\u6574\u6570\u5EA7\u6A19)"
  - icon: ':x:'
    path: library/integral_geom/count_lattice_point.hpp
    title: "\u683C\u5B50\u70B9\u3092\u9802\u70B9\u3068\u3059\u308B\u591A\u89D2\u5F62\
      \u306E\u5185\u90E8\u307E\u305F\u306F\u8FBA\u4E0A\u306B\u5B58\u5728\u3059\u308B\
      \u683C\u5B50\u70B9\u306E\u500B\u6570\u306E\u30AB\u30A6\u30F3\u30C8"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/typical90/tasks/typical90_041
    links:
    - https://atcoder.jp/contests/typical90/tasks/typical90_041
  bundledCode: "#line 1 \"test/src/integral_geom/count_lattice_point/typical90_041.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/typical90/tasks/typical90_041\"\
    \n\n#include <iostream>\n\n#line 1 \"library/integral_geom/convex_hull.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <numeric>\n#include <vector>\n\nnamespace\
    \ suisen::integral_geometry {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
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
    \ = true;\n        }\n        return res;\n    }\n} // namespace suisen::integral_geometry\n\
    \n\n#line 1 \"library/integral_geom/count_lattice_point.hpp\"\n\n\n\n#include\
    \ <cmath>\n#line 7 \"library/integral_geom/count_lattice_point.hpp\"\n\nnamespace\
    \ suisen::integral_geometry {\n    // return: calculate the number of lattice\
    \ points in the polygon or on at least one of the edges of it, using Pick's theorem\
    \ (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n    template <typename T,\
    \ std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    long\
    \ long count_lattice_points(const std::vector<std::pair<T, T>> &polygon) {\n \
    \       const int n = polygon.size();\n        long long s = 0, b = 0;\n     \
    \   for (int i = 0; i < n; ++i) {\n            auto [x1, y1] = polygon[i];\n \
    \           auto [x2, y2] = polygon[(i + 1) % n];\n            s += (long long)\
    \ x1 * y2 - (long long) y1 * x2;\n            b += std::abs(std::gcd(x2 - x1,\
    \ y2 - y1));\n        }\n        return (s + 2 + b) / 2;\n    }\n} // namespace\
    \ suisen::integral_geometry\n\n\n#line 7 \"test/src/integral_geom/count_lattice_point/typical90_041.test.cpp\"\
    \nusing namespace suisen::integral_geometry;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<std::pair<long\
    \ long, long long>> points(n);\n    for (auto &[x, y] : points) std::cin >> x\
    \ >> y;\n\n    std::vector<std::pair<long long, long long>> ch;\n    for (int\
    \ id : convex_hull(points)) {\n        ch.push_back(points[id]);\n    }\n    std::cout\
    \ << count_lattice_points(ch) - n << std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/typical90/tasks/typical90_041\"\
    \n\n#include <iostream>\n\n#include \"library/integral_geom/convex_hull.hpp\"\n\
    #include \"library/integral_geom/count_lattice_point.hpp\"\nusing namespace suisen::integral_geometry;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::pair<long long, long\
    \ long>> points(n);\n    for (auto &[x, y] : points) std::cin >> x >> y;\n\n \
    \   std::vector<std::pair<long long, long long>> ch;\n    for (int id : convex_hull(points))\
    \ {\n        ch.push_back(points[id]);\n    }\n    std::cout << count_lattice_points(ch)\
    \ - n << std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/integral_geom/convex_hull.hpp
  - library/integral_geom/count_lattice_point.hpp
  isVerificationFile: true
  path: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 16:59:40+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
layout: document
redirect_from:
- /verify/test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
- /verify/test/src/integral_geom/count_lattice_point/typical90_041.test.cpp.html
title: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
---
