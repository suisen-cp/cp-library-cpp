---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
    title: test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
    title: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Pick%27s_theorem).
  bundledCode: "#line 1 \"library/integral_geom/count_lattice_point.hpp\"\n\n\n\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    // return: calculate the number of lattice points in the polygon or on\
    \ at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    template <typename PointType, typename MultipliedType = long long>\n    MultipliedType\
    \ count_lattice_points(const std::vector<PointType> &polygon) {\n        const\
    \ int n = polygon.size();\n        MultipliedType s = 0, b = 0;\n        for (int\
    \ i = 0; i < n; ++i) {\n            auto [x1, y1] = polygon[i];\n            auto\
    \ [x2, y2] = polygon[(i + 1) % n];\n            s += MultipliedType(x1) * y2 -\
    \ MultipliedType(y1) * x2;\n            b += std::abs(std::gcd(x2 - x1, y2 - y1));\n\
    \        }\n        return (s + 2 + b) / 2;\n    }\n} // namespace suisen::integral_geometry\n\
    \n\n"
  code: "#ifndef SUISEN_COUNT_LATTICE_POINT\n#define SUISEN_COUNT_LATTICE_POINT\n\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    // return: calculate the number of lattice points in the polygon or on\
    \ at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    template <typename PointType, typename MultipliedType = long long>\n    MultipliedType\
    \ count_lattice_points(const std::vector<PointType> &polygon) {\n        const\
    \ int n = polygon.size();\n        MultipliedType s = 0, b = 0;\n        for (int\
    \ i = 0; i < n; ++i) {\n            auto [x1, y1] = polygon[i];\n            auto\
    \ [x2, y2] = polygon[(i + 1) % n];\n            s += MultipliedType(x1) * y2 -\
    \ MultipliedType(y1) * x2;\n            b += std::abs(std::gcd(x2 - x1, y2 - y1));\n\
    \        }\n        return (s + 2 + b) / 2;\n    }\n} // namespace suisen::integral_geometry\n\
    \n#endif // SUISEN_COUNT_LATTICE_POINT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/count_lattice_point.hpp
  requiredBy: []
  timestamp: '2022-07-10 18:49:22+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/integral_geom/count_lattice_point/typical90_041.test.cpp
  - test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
documentation_of: library/integral_geom/count_lattice_point.hpp
layout: document
title: "\u683C\u5B50\u70B9\u3092\u9802\u70B9\u3068\u3059\u308B\u591A\u89D2\u5F62\u306E\
  \u5185\u90E8\u307E\u305F\u306F\u8FBA\u4E0A\u306B\u5B58\u5728\u3059\u308B\u683C\u5B50\
  \u70B9\u306E\u500B\u6570\u306E\u30AB\u30A6\u30F3\u30C8"
---
## 格子点を頂点とする多角形の内部または辺上に存在する格子点の個数のカウント

[ピックの定理](https://ja.wikipedia.org/wiki/%E3%83%94%E3%83%83%E3%82%AF%E3%81%AE%E5%AE%9A%E7%90%86) を使うとできる。