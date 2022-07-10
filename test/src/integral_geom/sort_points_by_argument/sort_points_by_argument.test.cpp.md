---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/point.hpp
    title: library/integral_geom/point.hpp
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/sort_points_by_argument.hpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19)"
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
    \n\n\n\n#include <algorithm>\n#include <vector>\n\n#line 1 \"library/integral_geom/point.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/integral_geom/point.hpp\"\n#include\
    \ <utility>\n\nnamespace suisen::integral_geometry {\n    using coordinate_t =\
    \ long long;\n    using multiplied_t = __int128_t;\n\n    struct Point {\n   \
    \     coordinate_t x, y;\n        constexpr Point(coordinate_t x = 0, coordinate_t\
    \ y = 0) : x(x), y(y) {}\n\n        operator std::pair<coordinate_t, coordinate_t>()\
    \ const { return std::pair<coordinate_t, coordinate_t> { x, y }; }\n\n       \
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
    \    }\n} // namespace suisen::integral_geometry\n\n\n\n#line 6 \"test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp\"\
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
  - library/integral_geom/point.hpp
  isVerificationFile: true
  path: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 18:49:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
- /verify/test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp.html
title: test/src/integral_geom/sort_points_by_argument/sort_points_by_argument.test.cpp
---
