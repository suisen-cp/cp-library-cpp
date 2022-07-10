---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/integral_geom/count_lattice_point/typical90_ao.test.cpp
    title: test/src/integral_geom/count_lattice_point/typical90_ao.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Pick%27s_theorem).
  bundledCode: "#line 1 \"library/integral_geom/count_lattice_point.hpp\"\n\n\n\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    // return: calculate the number of lattice points in the polygon or on\
    \ at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    long long count_lattice_points(const std::vector<std::pair<T,\
    \ T>> &polygon) {\n        const int n = polygon.size();\n        long long s\
    \ = 0, b = 0;\n        for (int i = 0; i < n; ++i) {\n            auto [x1, y1]\
    \ = polygon[i];\n            auto [x2, y2] = polygon[(i + 1) % n];\n         \
    \   s += (long long) x1 * y2 - (long long) y1 * x2;\n            b += std::abs(std::gcd(x2\
    \ - x1, y2 - y1));\n        }\n        return (s + 2 + b) / 2;\n    }\n} // namespace\
    \ suisen::integral_geometry\n\n\n"
  code: "#ifndef SUISEN_COUNT_LATTICE_POINT\n#define SUISEN_COUNT_LATTICE_POINT\n\n\
    #include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen::integral_geometry\
    \ {\n    // return: calculate the number of lattice points in the polygon or on\
    \ at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n    long long count_lattice_points(const std::vector<std::pair<T,\
    \ T>> &polygon) {\n        const int n = polygon.size();\n        long long s\
    \ = 0, b = 0;\n        for (int i = 0; i < n; ++i) {\n            auto [x1, y1]\
    \ = polygon[i];\n            auto [x2, y2] = polygon[(i + 1) % n];\n         \
    \   s += (long long) x1 * y2 - (long long) y1 * x2;\n            b += std::abs(std::gcd(x2\
    \ - x1, y2 - y1));\n        }\n        return (s + 2 + b) / 2;\n    }\n} // namespace\
    \ suisen::integral_geometry\n\n#endif // SUISEN_COUNT_LATTICE_POINT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/count_lattice_point.hpp
  requiredBy: []
  timestamp: '2022-07-10 16:40:31+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/integral_geom/count_lattice_point/typical90_ao.test.cpp
documentation_of: library/integral_geom/count_lattice_point.hpp
layout: document
redirect_from:
- /library/library/integral_geom/count_lattice_point.hpp
- /library/library/integral_geom/count_lattice_point.hpp.html
title: library/integral_geom/count_lattice_point.hpp
---
