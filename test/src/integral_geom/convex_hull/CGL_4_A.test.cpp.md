---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/convex_hull.hpp
    title: "Convex Hull (\u6574\u6570\u5EA7\u6A19)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
  bundledCode: "#line 1 \"test/src/integral_geom/convex_hull/CGL_4_A.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <iomanip>\n\n#line 1 \"\
    library/integral_geom/convex_hull.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry {\n    template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    std::vector<int> convex_hull(const std::vector<std::pair<T, T>> &points)\
    \ {\n        const int n = points.size();\n        std::vector<int> sorted(n);\n\
    \        std::iota(sorted.begin(), sorted.end(), 0);\n        std::sort(sorted.begin(),\
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
    \n\n#line 8 \"test/src/integral_geom/convex_hull/CGL_4_A.test.cpp\"\n\nusing namespace\
    \ suisen::integral_geometry;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    std::cout << std::fixed << std::setprecision(0);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::pair<long long, long\
    \ long>> points(n);\n\n    for (auto &[x, y] : points) std::cin >> x >> y;\n\n\
    \    std::vector<int> ids = convex_hull(points);\n\n    int amin = 0;\n    for\
    \ (int i = 1; i < int(ids.size()); ++i) {\n        long long x0 = points[ids[amin]].first,\
    \ y0 = points[ids[amin]].second;\n        long long x1 = points[ids[i]].first,\
    \ y1 = points[ids[i]].second;\n        if (y1 < y0 or (y1 == y0 and x1 < x0))\
    \ {\n            amin = i;\n        }\n    }\n\n    std::cout << ids.size() <<\
    \ '\\n';\n    for (int i = 0; i < int(ids.size()); ++i) {\n        auto [x, y]\
    \ = points[ids[(amin + i) % ids.size()]];\n        std::cout << x << ' ' << y\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <iomanip>\n\n#include \"\
    library/integral_geom/convex_hull.hpp\"\n\nusing namespace suisen::integral_geometry;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    std::cout << std::fixed << std::setprecision(0);\n\n    int n;\n    std::cin\
    \ >> n;\n\n    std::vector<std::pair<long long, long long>> points(n);\n\n   \
    \ for (auto &[x, y] : points) std::cin >> x >> y;\n\n    std::vector<int> ids\
    \ = convex_hull(points);\n\n    int amin = 0;\n    for (int i = 1; i < int(ids.size());\
    \ ++i) {\n        long long x0 = points[ids[amin]].first, y0 = points[ids[amin]].second;\n\
    \        long long x1 = points[ids[i]].first, y1 = points[ids[i]].second;\n  \
    \      if (y1 < y0 or (y1 == y0 and x1 < x0)) {\n            amin = i;\n     \
    \   }\n    }\n\n    std::cout << ids.size() << '\\n';\n    for (int i = 0; i <\
    \ int(ids.size()); ++i) {\n        auto [x, y] = points[ids[(amin + i) % ids.size()]];\n\
    \        std::cout << x << ' ' << y << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/integral_geom/convex_hull.hpp
  isVerificationFile: true
  path: test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 16:40:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
layout: document
redirect_from:
- /verify/test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
- /verify/test/src/integral_geom/convex_hull/CGL_4_A.test.cpp.html
title: test/src/integral_geom/convex_hull/CGL_4_A.test.cpp
---
