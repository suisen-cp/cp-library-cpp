---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Pick%27s_theorem).
  bundledCode: "#line 1 \"library/geom/count_lattice_point.hpp\"\n#include <cmath>\n\
    #include <numeric>\n#include <vector>\n\nnamespace suisen {\nnamespace geometry\
    \ {\n    // return: calculate the number of lattice points in the polygon or on\
    \ at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    long long count_lattice_points(const std::vector<std::pair<long long, long\
    \ long>> &polygon) {\n        const int n = polygon.size();\n        long long\
    \ s = 0, b = 0;\n        for (int i = 0; i < n; ++i) {\n            auto [x1,\
    \ y1] = polygon[i];\n            auto [x2, y2] = polygon[(i + 1) % n];\n     \
    \       s += x1 * y2 - y1 * x2;\n            b += std::abs(std::gcd(x2 - x1, y2\
    \ - y1));\n        }\n        return (s + 2 + b) / 2;\n    }\n}\n} // namespace\
    \ suisen\n"
  code: "#include <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace suisen\
    \ {\nnamespace geometry {\n    // return: calculate the number of lattice points\
    \ in the polygon or on at least one of the edges of it, using Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem).\n\
    \    long long count_lattice_points(const std::vector<std::pair<long long, long\
    \ long>> &polygon) {\n        const int n = polygon.size();\n        long long\
    \ s = 0, b = 0;\n        for (int i = 0; i < n; ++i) {\n            auto [x1,\
    \ y1] = polygon[i];\n            auto [x2, y2] = polygon[(i + 1) % n];\n     \
    \       s += x1 * y2 - y1 * x2;\n            b += std::abs(std::gcd(x2 - x1, y2\
    \ - y1));\n        }\n        return (s + 2 + b) / 2;\n    }\n}\n} // namespace\
    \ suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/geom/count_lattice_point.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/geom/count_lattice_point.hpp
layout: document
redirect_from:
- /library/library/geom/count_lattice_point.hpp
- /library/library/geom/count_lattice_point.hpp.html
title: library/geom/count_lattice_point.hpp
---
