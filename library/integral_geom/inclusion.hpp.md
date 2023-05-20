---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/closest_pair.hpp
    title: "\u6700\u8FD1\u70B9\u5BFE (\u6574\u6570\u5EA7\u6A19)"
  - icon: ':warning:'
    path: library/integral_geom/convex_hull_inclusion.hpp
    title: Convex Hull Inclusion
  - icon: ':warning:'
    path: library/integral_geom/farthest_pair.hpp
    title: Farthest Pair
  - icon: ':question:'
    path: library/integral_geom/geometry.hpp
    title: "\u5E7E\u4F55\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19\
      )"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
    title: test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_1_C.test.cpp
    title: test/src/integral_geom/geometry/CGL_1_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_2_A.test.cpp
    title: test/src/integral_geom/geometry/CGL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_2_B.test.cpp
    title: test/src/integral_geom/geometry/CGL_2_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_3_A.test.cpp
    title: test/src/integral_geom/geometry/CGL_3_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_3_B.test.cpp
    title: test/src/integral_geom/geometry/CGL_3_B.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_3_C.test.cpp
    title: test/src/integral_geom/geometry/CGL_3_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/CGL_7_A.test.cpp
    title: test/src/integral_geom/geometry/CGL_7_A.test.cpp
  - icon: ':x:'
    path: test/src/integral_geom/geometry/abc259_d.test.cpp
    title: test/src/integral_geom/geometry/abc259_d.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/integral_geom/inclusion.hpp\"\n\n\n\nnamespace suisen::integral_geometry\
    \ {\n    enum class Inclusion { OUT, ON, IN };\n}\n\n\n"
  code: "#ifndef SUISEN_INT_GEOM_INCLUSION\n#define SUISEN_INT_GEOM_INCLUSION\n\n\
    namespace suisen::integral_geometry {\n    enum class Inclusion { OUT, ON, IN\
    \ };\n}\n\n#endif // SUISEN_INT_GEOM_INCLUSION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/inclusion.hpp
  requiredBy:
  - library/integral_geom/closest_pair.hpp
  - library/integral_geom/convex_hull_inclusion.hpp
  - library/integral_geom/farthest_pair.hpp
  - library/integral_geom/geometry.hpp
  timestamp: '2023-05-11 13:21:20+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
  - test/src/integral_geom/geometry/CGL_1_C.test.cpp
  - test/src/integral_geom/geometry/abc259_d.test.cpp
  - test/src/integral_geom/geometry/CGL_3_A.test.cpp
  - test/src/integral_geom/geometry/CGL_3_B.test.cpp
  - test/src/integral_geom/geometry/CGL_3_C.test.cpp
  - test/src/integral_geom/geometry/CGL_2_B.test.cpp
  - test/src/integral_geom/geometry/CGL_2_A.test.cpp
  - test/src/integral_geom/geometry/CGL_7_A.test.cpp
documentation_of: library/integral_geom/inclusion.hpp
layout: document
title: Inclusion
---
## Inclusion
