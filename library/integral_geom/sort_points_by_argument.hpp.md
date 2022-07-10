---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/point.hpp
    title: library/integral_geom/point.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
    title: test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
    title: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/integral_geom/sort_points_by_argument.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <vector>\n\n#line 1 \"library/integral_geom/point.hpp\"\
    \n\n\n\n#include <cassert>\n#include <iostream>\n#include <utility>\n\n#ifndef\
    \ COORDINATE_TYPE\n#define COORDINATE_TYPE long long\n#endif // COORDINATE_TYPE\n\
    #ifndef MULTIPLIED_TYPE\n#define MULTIPLIED_TYPE long long\n#endif // MULTIPLIED_TYPE\n\
    \nnamespace suisen::integral_geometry {\n    using coordinate_t = COORDINATE_TYPE;\n\
    \    using multiplied_t = MULTIPLIED_TYPE;\n\n    struct Point {\n        coordinate_t\
    \ x, y;\n        constexpr Point(coordinate_t x = 0, coordinate_t y = 0) : x(x),\
    \ y(y) {}\n\n        template <typename T = coordinate_t, typename U = coordinate_t>\n\
    \        operator std::pair<T, U>() const { return std::pair<T, U> { T{ x }, U{\
    \ y } }; }\n        template <typename T, typename U>\n        Point& operator=(const\
    \ std::pair<T, U> &p) { x = p.first, y = p.second; return *this; }\n\n       \
    \ friend Point operator+(const Point& p) { return p; }\n        friend Point operator-(const\
    \ Point& p) { return { -p.x, -p.y }; }\n\n        friend Point operator+(const\
    \ Point& lhs, const Point& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }\n\
    \        friend Point operator-(const Point& lhs, const Point& rhs) { return {\
    \ lhs.x - rhs.x, lhs.y - rhs.y }; }\n        friend Point operator*(const Point&\
    \ lhs, const Point& rhs) { return { lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y\
    \ + lhs.y * rhs.x }; }\n\n        friend Point& operator+=(Point& lhs, const Point&\
    \ rhs) { lhs.x += rhs.x, lhs.y += rhs.y; return lhs; }\n        friend Point&\
    \ operator-=(Point& lhs, const Point& rhs) { lhs.x -= rhs.x, lhs.y -= rhs.y; return\
    \ lhs; }\n        friend Point& operator*=(Point& lhs, const Point& rhs) { return\
    \ lhs = lhs * rhs; }\n\n        friend Point operator+(const Point& p, coordinate_t\
    \ real) { return { p.x + real, p.y }; }\n        friend Point operator-(const\
    \ Point& p, coordinate_t real) { return { p.x - real, p.y }; }\n        friend\
    \ Point operator*(const Point& p, coordinate_t real) { return { p.x * real, p.y\
    \ * real }; }\n        friend Point operator/(const Point& p, coordinate_t real)\
    \ { return { p.x / real, p.y / real }; }\n\n        friend Point operator+=(Point&\
    \ p, coordinate_t real) { p.x += real; return p; }\n        friend Point operator-=(Point&\
    \ p, coordinate_t real) { p.x -= real; return p; }\n        friend Point operator*=(Point&\
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
    \ { using type = suisen::integral_geometry::coordinate_t; };\n}\n\n\n#line 8 \"\
    library/integral_geom/sort_points_by_argument.hpp\"\n\nnamespace suisen::integral_geometry\
    \ {\n    /**\n     * 1. (x < 0, y = 0) -> pi\n     * 2. (x = 0, y = 0) -> 0\n\
    \     * 3. points with same argument -> arbitrary order\n     */\n    template\
    \ <typename PointType, typename MultipliedType = long long>\n    bool compare_by_atan2(const\
    \ PointType &p, const PointType &q) {\n        const auto &[x1, y1] = p;\n   \
    \     const auto &[x2, y2] = q;\n        if ((y1 < 0) xor (y2 < 0)) return y1\
    \ < y2;\n        if ((x1 < 0) xor (x2 < 0)) return (y1 >= 0) xor (x1 < x2);\n\
    \        if (x1 == 0 and y1 == 0) return true;\n        if (x2 == 0 and y2 ==\
    \ 0) return false;\n        return (MultipliedType(y1) * x2 < MultipliedType(y2)\
    \ * x1);\n    }\n    template <typename PointType, typename MultipliedType = long\
    \ long>\n    void sort_points_by_argument(std::vector<PointType> &points) {\n\
    \        std::sort(points.begin(), points.end(), compare_by_atan2<PointType, MultipliedType>);\n\
    \    }\n} // namespace suisen::integral_geometry\n\n\n\n"
  code: "#ifndef SUISEN_SORT_POINTS_BY_ARGUMENT\n#define SUISEN_SORT_POINTS_BY_ARGUMENT\n\
    \n#include <algorithm>\n#include <vector>\n\n#include \"library/integral_geom/point.hpp\"\
    \n\nnamespace suisen::integral_geometry {\n    /**\n     * 1. (x < 0, y = 0) ->\
    \ pi\n     * 2. (x = 0, y = 0) -> 0\n     * 3. points with same argument -> arbitrary\
    \ order\n     */\n    template <typename PointType, typename MultipliedType =\
    \ long long>\n    bool compare_by_atan2(const PointType &p, const PointType &q)\
    \ {\n        const auto &[x1, y1] = p;\n        const auto &[x2, y2] = q;\n  \
    \      if ((y1 < 0) xor (y2 < 0)) return y1 < y2;\n        if ((x1 < 0) xor (x2\
    \ < 0)) return (y1 >= 0) xor (x1 < x2);\n        if (x1 == 0 and y1 == 0) return\
    \ true;\n        if (x2 == 0 and y2 == 0) return false;\n        return (MultipliedType(y1)\
    \ * x2 < MultipliedType(y2) * x1);\n    }\n    template <typename PointType, typename\
    \ MultipliedType = long long>\n    void sort_points_by_argument(std::vector<PointType>\
    \ &points) {\n        std::sort(points.begin(), points.end(), compare_by_atan2<PointType,\
    \ MultipliedType>);\n    }\n} // namespace suisen::integral_geometry\n\n\n#endif\
    \ // SUISEN_SORT_POINTS_BY_ARGUMENT\n"
  dependsOn:
  - library/integral_geom/point.hpp
  isVerificationFile: false
  path: library/integral_geom/sort_points_by_argument.hpp
  requiredBy: []
  timestamp: '2022-07-10 19:58:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/integral_geom/count_lattice_point/yuki1999.test.cpp
  - test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
documentation_of: library/integral_geom/sort_points_by_argument.hpp
layout: document
title: "\u504F\u89D2\u30BD\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19)"
---
## 偏角ソート (整数座標)
