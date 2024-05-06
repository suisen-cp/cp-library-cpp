---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/closest_pair.hpp
    title: "\u6700\u8FD1\u70B9\u5BFE (\u6574\u6570\u5EA7\u6A19)"
  - icon: ':warning:'
    path: library/integral_geom/farthest_pair.hpp
    title: Farthest Pair
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/geometry.hpp
    title: "\u5E7E\u4F55\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19\
      )"
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/sort_points_by_argument.hpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
    title: test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
    title: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
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
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/geometry/abc259_d.test.cpp
    title: test/src/integral_geom/geometry/abc259_d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
    title: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/integral_geom/point.hpp\"\n\n\n\n#include <cassert>\n\
    #include <iostream>\n#include <utility>\n\n#ifndef COORDINATE_TYPE\n#define COORDINATE_TYPE\
    \ long long\n#endif // COORDINATE_TYPE\n#ifndef MULTIPLIED_TYPE\n#define MULTIPLIED_TYPE\
    \ long long\n#endif // MULTIPLIED_TYPE\n\nnamespace suisen::integral_geometry\
    \ {\n    using coordinate_t = COORDINATE_TYPE;\n    using multiplied_t = MULTIPLIED_TYPE;\n\
    \n    struct Point {\n        coordinate_t x, y;\n        constexpr Point(coordinate_t\
    \ x = 0, coordinate_t y = 0) : x(x), y(y) {}\n\n        template <typename T =\
    \ coordinate_t, typename U = coordinate_t>\n        operator std::pair<T, U>()\
    \ const { return std::pair<T, U> { T{ x }, U{ y } }; }\n        template <typename\
    \ T, typename U>\n        Point& operator=(const std::pair<T, U> &p) { x = p.first,\
    \ y = p.second; return *this; }\n\n        friend Point operator+(const Point&\
    \ p) { return p; }\n        friend Point operator-(const Point& p) { return {\
    \ -p.x, -p.y }; }\n\n        friend Point operator+(const Point& lhs, const Point&\
    \ rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }\n        friend Point operator-(const\
    \ Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }\n\
    \        friend Point operator*(const Point& lhs, const Point& rhs) { return {\
    \ lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x }; }\n\n      \
    \  friend Point& operator+=(Point& lhs, const Point& rhs) { lhs.x += rhs.x, lhs.y\
    \ += rhs.y; return lhs; }\n        friend Point& operator-=(Point& lhs, const\
    \ Point& rhs) { lhs.x -= rhs.x, lhs.y -= rhs.y; return lhs; }\n        friend\
    \ Point& operator*=(Point& lhs, const Point& rhs) { return lhs = lhs * rhs; }\n\
    \n        friend Point operator+(const Point& p, coordinate_t real) { return {\
    \ p.x + real, p.y }; }\n        friend Point operator-(const Point& p, coordinate_t\
    \ real) { return { p.x - real, p.y }; }\n        friend Point operator*(const\
    \ Point& p, coordinate_t real) { return { p.x * real, p.y * real }; }\n      \
    \  friend Point operator/(const Point& p, coordinate_t real) { return { p.x /\
    \ real, p.y / real }; }\n\n        friend Point operator+=(Point& p, coordinate_t\
    \ real) { p.x += real; return p; }\n        friend Point operator-=(Point& p,\
    \ coordinate_t real) { p.x -= real; return p; }\n        friend Point operator*=(Point&\
    \ p, coordinate_t real) { p.x *= real, p.y *= real; return p; }\n        friend\
    \ Point operator/=(Point& p, coordinate_t real) { p.x /= real, p.y /= real; return\
    \ p; }\n\n        friend Point operator+(coordinate_t real, const Point& p) {\
    \ return { real + p.x, p.y }; }\n        friend Point operator-(coordinate_t real,\
    \ const Point& p) { return { real - p.x, -p.y }; }\n        friend Point operator*(coordinate_t\
    \ real, const Point& p) { return { real * p.x, real * p.y }; }\n\n        friend\
    \ bool operator==(const Point& lhs, const Point& rhs) { return lhs.x == rhs.x\
    \ and lhs.y == rhs.y; }\n        friend bool operator!=(const Point& lhs, const\
    \ Point& rhs) { return not (lhs == rhs); }\n\n        friend std::istream& operator>>(std::istream&\
    \ in, Point& p) { return in >> p.x >> p.y; }\n        friend std::ostream& operator<<(std::ostream&\
    \ out, const Point& p) { return out << p.x << ' ' << p.y; }\n\n        template\
    \ <std::size_t I>\n        coordinate_t get() const {\n            if constexpr\
    \ (I == 0) return x;\n            else if constexpr (I == 1) return y;\n     \
    \       else assert(false);\n        }\n        template <std::size_t I>\n   \
    \     coordinate_t& get() {\n            if constexpr (I == 0) return x;\n   \
    \         else if constexpr (I == 1) return y;\n            else assert(false);\n\
    \        }\n    };\n\n    constexpr Point ZERO = { 0, 0 };\n    constexpr Point\
    \ ONE  = { 1, 0 };\n    constexpr Point I    = { 0, 1 };\n\n    constexpr auto\
    \ XY_COMPARATOR         = [](const Point& p, const Point& q) { return p.x == q.x\
    \ ? p.y < q.y : p.x < q.x; };\n    constexpr auto XY_COMPARATOR_GREATER = [](const\
    \ Point& p, const Point& q) { return p.x == q.x ? p.y > q.y : p.x > q.x; };\n\
    \    constexpr auto YX_COMPARATOR         = [](const Point& p, const Point& q)\
    \ { return p.y == q.y ? p.x < q.x : p.y < q.y; };\n    constexpr auto YX_COMPARATOR_GREATER\
    \ = [](const Point& p, const Point& q) { return p.y == q.y ? p.x > q.x : p.y >\
    \ q.y; };\n} // namespace suisen::integral_geometry\n\nnamespace std {\n    template\
    \ <>\n    struct tuple_size<suisen::integral_geometry::Point> : integral_constant<size_t,\
    \ 2> {};\n    template <size_t I>\n    struct tuple_element<I, suisen::integral_geometry::Point>\
    \ { using type = suisen::integral_geometry::coordinate_t; };\n}\n\n\n"
  code: "#ifndef SUISEN_POINT\n#define SUISEN_POINT\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <utility>\n\n#ifndef COORDINATE_TYPE\n#define COORDINATE_TYPE\
    \ long long\n#endif // COORDINATE_TYPE\n#ifndef MULTIPLIED_TYPE\n#define MULTIPLIED_TYPE\
    \ long long\n#endif // MULTIPLIED_TYPE\n\nnamespace suisen::integral_geometry\
    \ {\n    using coordinate_t = COORDINATE_TYPE;\n    using multiplied_t = MULTIPLIED_TYPE;\n\
    \n    struct Point {\n        coordinate_t x, y;\n        constexpr Point(coordinate_t\
    \ x = 0, coordinate_t y = 0) : x(x), y(y) {}\n\n        template <typename T =\
    \ coordinate_t, typename U = coordinate_t>\n        operator std::pair<T, U>()\
    \ const { return std::pair<T, U> { T{ x }, U{ y } }; }\n        template <typename\
    \ T, typename U>\n        Point& operator=(const std::pair<T, U> &p) { x = p.first,\
    \ y = p.second; return *this; }\n\n        friend Point operator+(const Point&\
    \ p) { return p; }\n        friend Point operator-(const Point& p) { return {\
    \ -p.x, -p.y }; }\n\n        friend Point operator+(const Point& lhs, const Point&\
    \ rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }\n        friend Point operator-(const\
    \ Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }\n\
    \        friend Point operator*(const Point& lhs, const Point& rhs) { return {\
    \ lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x }; }\n\n      \
    \  friend Point& operator+=(Point& lhs, const Point& rhs) { lhs.x += rhs.x, lhs.y\
    \ += rhs.y; return lhs; }\n        friend Point& operator-=(Point& lhs, const\
    \ Point& rhs) { lhs.x -= rhs.x, lhs.y -= rhs.y; return lhs; }\n        friend\
    \ Point& operator*=(Point& lhs, const Point& rhs) { return lhs = lhs * rhs; }\n\
    \n        friend Point operator+(const Point& p, coordinate_t real) { return {\
    \ p.x + real, p.y }; }\n        friend Point operator-(const Point& p, coordinate_t\
    \ real) { return { p.x - real, p.y }; }\n        friend Point operator*(const\
    \ Point& p, coordinate_t real) { return { p.x * real, p.y * real }; }\n      \
    \  friend Point operator/(const Point& p, coordinate_t real) { return { p.x /\
    \ real, p.y / real }; }\n\n        friend Point operator+=(Point& p, coordinate_t\
    \ real) { p.x += real; return p; }\n        friend Point operator-=(Point& p,\
    \ coordinate_t real) { p.x -= real; return p; }\n        friend Point operator*=(Point&\
    \ p, coordinate_t real) { p.x *= real, p.y *= real; return p; }\n        friend\
    \ Point operator/=(Point& p, coordinate_t real) { p.x /= real, p.y /= real; return\
    \ p; }\n\n        friend Point operator+(coordinate_t real, const Point& p) {\
    \ return { real + p.x, p.y }; }\n        friend Point operator-(coordinate_t real,\
    \ const Point& p) { return { real - p.x, -p.y }; }\n        friend Point operator*(coordinate_t\
    \ real, const Point& p) { return { real * p.x, real * p.y }; }\n\n        friend\
    \ bool operator==(const Point& lhs, const Point& rhs) { return lhs.x == rhs.x\
    \ and lhs.y == rhs.y; }\n        friend bool operator!=(const Point& lhs, const\
    \ Point& rhs) { return not (lhs == rhs); }\n\n        friend std::istream& operator>>(std::istream&\
    \ in, Point& p) { return in >> p.x >> p.y; }\n        friend std::ostream& operator<<(std::ostream&\
    \ out, const Point& p) { return out << p.x << ' ' << p.y; }\n\n        template\
    \ <std::size_t I>\n        coordinate_t get() const {\n            if constexpr\
    \ (I == 0) return x;\n            else if constexpr (I == 1) return y;\n     \
    \       else assert(false);\n        }\n        template <std::size_t I>\n   \
    \     coordinate_t& get() {\n            if constexpr (I == 0) return x;\n   \
    \         else if constexpr (I == 1) return y;\n            else assert(false);\n\
    \        }\n    };\n\n    constexpr Point ZERO = { 0, 0 };\n    constexpr Point\
    \ ONE  = { 1, 0 };\n    constexpr Point I    = { 0, 1 };\n\n    constexpr auto\
    \ XY_COMPARATOR         = [](const Point& p, const Point& q) { return p.x == q.x\
    \ ? p.y < q.y : p.x < q.x; };\n    constexpr auto XY_COMPARATOR_GREATER = [](const\
    \ Point& p, const Point& q) { return p.x == q.x ? p.y > q.y : p.x > q.x; };\n\
    \    constexpr auto YX_COMPARATOR         = [](const Point& p, const Point& q)\
    \ { return p.y == q.y ? p.x < q.x : p.y < q.y; };\n    constexpr auto YX_COMPARATOR_GREATER\
    \ = [](const Point& p, const Point& q) { return p.y == q.y ? p.x > q.x : p.y >\
    \ q.y; };\n} // namespace suisen::integral_geometry\n\nnamespace std {\n    template\
    \ <>\n    struct tuple_size<suisen::integral_geometry::Point> : integral_constant<size_t,\
    \ 2> {};\n    template <size_t I>\n    struct tuple_element<I, suisen::integral_geometry::Point>\
    \ { using type = suisen::integral_geometry::coordinate_t; };\n}\n\n#endif // SUISEN_POINT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/integral_geom/point.hpp
  requiredBy:
  - library/integral_geom/farthest_pair.hpp
  - library/integral_geom/closest_pair.hpp
  - library/integral_geom/sort_points_by_argument.hpp
  - library/integral_geom/geometry.hpp
  timestamp: '2022-07-10 19:58:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
  - test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
  - test/src/integral_geom/geometry/CGL_2_A.test.cpp
  - test/src/integral_geom/geometry/CGL_3_A.test.cpp
  - test/src/integral_geom/geometry/CGL_3_C.test.cpp
  - test/src/integral_geom/geometry/CGL_1_C.test.cpp
  - test/src/integral_geom/geometry/abc259_d.test.cpp
  - test/src/integral_geom/geometry/CGL_3_B.test.cpp
  - test/src/integral_geom/geometry/CGL_2_B.test.cpp
  - test/src/integral_geom/geometry/CGL_7_A.test.cpp
  - test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
documentation_of: library/integral_geom/point.hpp
layout: document
title: Point
---
## Point