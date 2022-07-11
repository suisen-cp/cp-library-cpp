---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/point.hpp
    title: Point
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/integral_geom/closest_pair.hpp
    title: "\u6700\u8FD1\u70B9\u5BFE (\u6574\u6570\u5EA7\u6A19)"
  - icon: ':warning:'
    path: library/integral_geom/farthest_pair.hpp
    title: Farthest Pair
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
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A
  bundledCode: "#line 1 \"library/integral_geom/geometry.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cmath>\n#include <iostream>\n#include <vector>\n\n#line 1 \"library/integral_geom/point.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/integral_geom/point.hpp\"\n#include\
    \ <utility>\n\n#ifndef COORDINATE_TYPE\n#define COORDINATE_TYPE long long\n#endif\
    \ // COORDINATE_TYPE\n#ifndef MULTIPLIED_TYPE\n#define MULTIPLIED_TYPE long long\n\
    #endif // MULTIPLIED_TYPE\n\nnamespace suisen::integral_geometry {\n    using\
    \ coordinate_t = COORDINATE_TYPE;\n    using multiplied_t = MULTIPLIED_TYPE;\n\
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
    \ { using type = suisen::integral_geometry::coordinate_t; };\n}\n\n\n#line 10\
    \ \"library/integral_geom/geometry.hpp\"\n\nnamespace suisen::integral_geometry\
    \ {\n    // relations between three points X, Y, Z.\n    struct ISP {\n      \
    \  static constexpr int L_CURVE = +1; // +---------------+ Z is in 'a' => ISP\
    \ = +1\n        static constexpr int R_CURVE = -1; // |aaaaaaaaaaaaaaa| Z is in\
    \ 'b' => ISP = -1\n        static constexpr int FRONT = +2;   // |ddd X eee Y\
    \ ccc| Z is in 'c' => ISP = +2\n        static constexpr int BACK = -2;    //\
    \ |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2\n        static constexpr int MIDDLE\
    \ = 0;   // +---------------+ Z is in 'e' => ISP =  0\n    };\n\n    enum class\
    \ Containment { OUT, ON, IN };\n\n    int sgn(coordinate_t x) { return x < 0 ?\
    \ -1 : x > 0 ? +1 : 0; }\n    int compare(coordinate_t x, coordinate_t y) { return\
    \ sgn(x - y); }\n\n    Point cartesian(const coordinate_t real, const coordinate_t\
    \ imag) { return Point(real, imag); }\n    Point conj(const Point& z) { return\
    \ Point(z.x, -z.y); }\n    double arg(const Point& z) { return std::atan2(z.y,\
    \ z.x); }\n    multiplied_t square_abs(const Point& z) { return multiplied_t(z.x)\
    \ * z.x + multiplied_t(z.y) * z.y; }\n    double abs(const Point& z) { return\
    \ std::sqrt(square_abs(z)); }\n\n    multiplied_t dot(const Point& a, const Point&\
    \ b) { return multiplied_t(a.x) * b.x + multiplied_t(a.y) * b.y; }\n    multiplied_t\
    \ det(const Point& a, const Point& b) { return multiplied_t(a.x) * b.y - multiplied_t(a.y)\
    \ * b.x; }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C\n\
    \    int isp(const Point& a, const Point& b, const Point& c) {\n        Point\
    \ ab = b - a, ac = c - a;\n        coordinate_t det_ab_ac = det(ab, ac);\n   \
    \     if (det_ab_ac > 0) return ISP::L_CURVE;\n        if (det_ab_ac < 0) return\
    \ ISP::R_CURVE;\n        if (dot(ab, ac) < 0) return ISP::BACK;\n        if (dot(a\
    \ - b, c - b) < 0) return ISP::FRONT;\n        return ISP::MIDDLE;\n    }\n\n\
    \    struct Line {\n        Point a, b;\n        Line() = default;\n        Line(const\
    \ Point& from, const Point& to) : a(from), b(to) {}\n    };\n    struct Ray {\n\
    \        Point a, b;\n        Ray() = default;\n        Ray(const Point& from,\
    \ const Point& to) : a(from), b(to) {}\n    };\n    struct Segment {\n       \
    \ Point a, b;\n        Segment() = default;\n        Segment(const Point& from,\
    \ const Point& to) : a(from), b(to) {}\n    };\n    struct Circle {\n        Point\
    \ center;\n        coordinate_t radius;\n        Circle() = default;\n       \
    \ Circle(const Point& c, const coordinate_t& r) : center(c), radius(r) {}\n  \
    \  };\n\n    // Triangle\n\n    coordinate_t signed_area_doubled(const Point&\
    \ a, const Point& b, const Point& c) {\n        return det(b - a, c - a);\n  \
    \  }\n    coordinate_t area_doubled(const Point& a, const Point& b, const Point&\
    \ c) {\n        return std::abs(signed_area_doubled(a, b, c));\n    }\n\n    //\
    \ Line\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto is_parallel(const\
    \ line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \ {\n        return det(l1.b - l1.a, l2.b - l2.a) == 0;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto is_orthogonal(const\
    \ line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \ {\n        return dot(l1.b - l1.a, l2.b - l2.a) == 0;\n    }\n    template <typename\
    \ line_t_1, typename line_t_2>\n    auto on_the_same_line(const line_t_1& l1,\
    \ const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {\n        return\
    \ is_parallel(l1, l2) and det(l1.b - l1.a, l2.a - l1.a) == 0;\n    }\n\n    Containment\
    \ contains(const Line& l, const Point& p) {\n        if (l.a.x == l.b.x) return\
    \ p.x == l.a.x ? Containment::ON : Containment::OUT;\n        coordinate_t a =\
    \ p.x - l.a.x, b = p.y - l.a.y, c = l.b.x - p.x, d = l.b.y - p.y;\n        return\
    \ b * c == a * d ? Containment::ON : Containment::OUT;\n    }\n    Containment\
    \ contains(const Ray& l, const Point& p) {\n        if (contains(Line { l.a, l.b\
    \ }, p) == Containment::OUT) return Containment::OUT;\n        if (l.a.x == l.b.x)\
    \ {\n            if (l.a.y < l.b.y) return p.y >= l.a.y ? Containment::ON : Containment::OUT;\n\
    \            else return p.y <= l.a.y ? Containment::ON : Containment::OUT;\n\
    \        } else if (l.a.x < l.b.x) {\n            return p.x >= l.a.x ? Containment::ON\
    \ : Containment::OUT;\n        } else {\n            return p.x <= l.a.x ? Containment::ON\
    \ : Containment::OUT;\n        }\n    }\n    Containment contains(const Segment&\
    \ l, const Point& p) {\n        if (contains(Line { l.a, l.b }, p) == Containment::OUT)\
    \ return Containment::OUT;\n        if (l.a.x == l.b.x) {\n            if (l.a.y\
    \ < l.b.y) return p.y >= l.a.y and p.y <= l.b.y ? Containment::ON : Containment::OUT;\n\
    \            else return p.y >= l.b.y and p.y <= l.a.y ? Containment::ON : Containment::OUT;\n\
    \        } else if (l.a.x < l.b.x) {\n            return p.x >= l.a.x and p.x\
    \ <= l.b.x ? Containment::ON : Containment::OUT;\n        } else {\n         \
    \   return p.x >= l.b.x and p.x <= l.a.x ? Containment::ON : Containment::OUT;\n\
    \        }\n    }\n\n    bool operator==(const Line& l, const Line& m) {\n   \
    \     return on_the_same_line(l, m);\n    }\n    bool operator==(const Ray& l,\
    \ const Ray& m) {\n        return on_the_same_line(l, m) and l.a == m.a;\n   \
    \ }\n    bool operator==(const Segment& l, const Segment& m) {\n        return\
    \ (l.a == m.a and l.b == m.b) or (l.a == m.b and l.b == m.a);\n    }\n\n    //\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B\"\n    bool\
    \ has_common_point(const Segment& l1, const Segment& l2) {\n        int isp_1a\
    \ = isp(l1.a, l1.b, l2.a), isp_1b = isp(l1.a, l1.b, l2.b);\n        if (isp_1a\
    \ * isp_1b > 0) return false;\n        int isp_2a = isp(l2.a, l2.b, l1.a), isp_2b\
    \ = isp(l2.a, l2.b, l1.b);\n        if (isp_2a * isp_2b > 0) return false;\n \
    \       return true;\n    }\n\n    // Polygon\n\n    using Polygon = std::vector<Point>;\n\
    \n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n \
    \   coordinate_t signed_area_doubled(const Polygon& poly) {\n        coordinate_t\
    \ res = 0;\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1;\n            if (j == sz) j = 0;\n           \
    \ res += signed_area_doubled(ZERO, poly[i], poly[j]);\n        }\n        return\
    \ res;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n\
    \    coordinate_t area_doubled(const Polygon& poly) {\n        return std::abs(signed_area_doubled(poly));\n\
    \    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\n\
    \    template <bool accept_180_degree = true>\n    bool is_convex(const Polygon&\
    \ poly) {\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1, k = i + 2;\n            if (j >= sz) j -= sz;\n\
    \            if (k >= sz) k -= sz;\n            int dir = isp(poly[i], poly[j],\
    \ poly[k]);\n            if constexpr (accept_180_degree) {\n                if\
    \ (dir == ISP::R_CURVE) return false;\n            } else {\n                if\
    \ (dir != ISP::L_CURVE) return false;\n            }\n        }\n        return\
    \ true;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C\n\
    \    Containment contains(const Polygon& poly, const Point& p) {\n        bool\
    \ in = false;\n        int sz = poly.size();\n        for (int i = 0; i < sz;\
    \ ++i) {\n            int j = i + 1;\n            if (j == sz) j -= sz;\n    \
    \        Point a = poly[i] - p, b = poly[j] - p;\n            if (a.y > b.y) std::swap(a,\
    \ b);\n            if (a.y <= 0 and b.y > 0 and det(a, b) < 0) in = not in;\n\
    \            if (det(a, b) == 0 and dot(a, b) <= 0) return Containment::ON;\n\
    \        }\n        return in ? Containment::IN : Containment::OUT;\n    }\n\n\
    \    std::pair<int, int> convex_diameter(const Polygon& convex) {\n        const\
    \ int sz = convex.size();\n        if (sz <= 2) return { 0, sz - 1 };\n      \
    \  auto [si, sj] = [&]{\n            auto [it_min, it_max] = std::minmax_element(convex.begin(),\
    \ convex.end(), XY_COMPARATOR);\n            return std::pair<int, int> { it_min\
    \ - convex.begin(), it_max - convex.begin() };\n        }();\n        coordinate_t\
    \ max_dist = -1;\n        std::pair<int, int> argmax{ -1, -1 };\n        for (int\
    \ i = si, j = sj; i != sj or j != si;) {\n            if (multiplied_t dij = square_abs(convex[j]\
    \ - convex[i]); dij > max_dist) max_dist = dij, argmax = { i, j };\n         \
    \   int ni = (i + 1) % sz, nj = (j + 1) % sz;\n            if (det(convex[ni]\
    \ - convex[i], convex[nj] - convex[j]) < 0) i = ni;\n            else j = nj;\n\
    \        }\n        return argmax;\n    }\n\n    // Circle\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A\n\
    \    int tangent_num(const Circle& c1, const Circle& c2) {\n        coordinate_t\
    \ r1 = c1.radius, r2 = c2.radius;\n        if (r1 > r2) return tangent_num(c2,\
    \ c1);\n        coordinate_t d2 = square_abs(c1.center - c2.center);\n       \
    \ coordinate_t dp = d2 - (r1 + r2) * (r1 + r2);\n        if (dp > 0) return 4;\n\
    \        if (dp == 0) return 3;\n        coordinate_t dn = d2 - (r2 - r1) * (r2\
    \ - r1);\n        if (dn > 0) return 2;\n        if (dn == 0) return 1;\n    \
    \    return 0;\n    }\n    bool has_common_point(const Circle& c1, const Circle&\
    \ c2) {\n        int tnum = tangent_num(c1, c2);\n        return 1 <= tnum and\
    \ tnum <= 3;\n    }\n    bool has_cross_point(const Circle& c1, const Circle&\
    \ c2) {\n        return tangent_num(c1, c2) == 2;\n    }\n\n    Containment contains(const\
    \ Circle& c, const Point& p) {\n        coordinate_t df = square_abs(c.center\
    \ - p) - c.radius * c.radius;\n        if (df > 0) return Containment::OUT;\n\
    \        if (df < 0) return Containment::IN;\n        return Containment::ON;\n\
    \    }\n} // namespace suisen::integral_geometry\n\n\n"
  code: "#ifndef SUISEN_GEOMETRY\n#define SUISEN_GEOMETRY\n\n#include <algorithm>\n\
    #include <cmath>\n#include <iostream>\n#include <vector>\n\n#include \"library/integral_geom/point.hpp\"\
    \n\nnamespace suisen::integral_geometry {\n    // relations between three points\
    \ X, Y, Z.\n    struct ISP {\n        static constexpr int L_CURVE = +1; // +---------------+\
    \ Z is in 'a' => ISP = +1\n        static constexpr int R_CURVE = -1; // |aaaaaaaaaaaaaaa|\
    \ Z is in 'b' => ISP = -1\n        static constexpr int FRONT = +2;   // |ddd\
    \ X eee Y ccc| Z is in 'c' => ISP = +2\n        static constexpr int BACK = -2;\
    \    // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2\n        static constexpr int\
    \ MIDDLE = 0;   // +---------------+ Z is in 'e' => ISP =  0\n    };\n\n    enum\
    \ class Containment { OUT, ON, IN };\n\n    int sgn(coordinate_t x) { return x\
    \ < 0 ? -1 : x > 0 ? +1 : 0; }\n    int compare(coordinate_t x, coordinate_t y)\
    \ { return sgn(x - y); }\n\n    Point cartesian(const coordinate_t real, const\
    \ coordinate_t imag) { return Point(real, imag); }\n    Point conj(const Point&\
    \ z) { return Point(z.x, -z.y); }\n    double arg(const Point& z) { return std::atan2(z.y,\
    \ z.x); }\n    multiplied_t square_abs(const Point& z) { return multiplied_t(z.x)\
    \ * z.x + multiplied_t(z.y) * z.y; }\n    double abs(const Point& z) { return\
    \ std::sqrt(square_abs(z)); }\n\n    multiplied_t dot(const Point& a, const Point&\
    \ b) { return multiplied_t(a.x) * b.x + multiplied_t(a.y) * b.y; }\n    multiplied_t\
    \ det(const Point& a, const Point& b) { return multiplied_t(a.x) * b.y - multiplied_t(a.y)\
    \ * b.x; }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C\n\
    \    int isp(const Point& a, const Point& b, const Point& c) {\n        Point\
    \ ab = b - a, ac = c - a;\n        coordinate_t det_ab_ac = det(ab, ac);\n   \
    \     if (det_ab_ac > 0) return ISP::L_CURVE;\n        if (det_ab_ac < 0) return\
    \ ISP::R_CURVE;\n        if (dot(ab, ac) < 0) return ISP::BACK;\n        if (dot(a\
    \ - b, c - b) < 0) return ISP::FRONT;\n        return ISP::MIDDLE;\n    }\n\n\
    \    struct Line {\n        Point a, b;\n        Line() = default;\n        Line(const\
    \ Point& from, const Point& to) : a(from), b(to) {}\n    };\n    struct Ray {\n\
    \        Point a, b;\n        Ray() = default;\n        Ray(const Point& from,\
    \ const Point& to) : a(from), b(to) {}\n    };\n    struct Segment {\n       \
    \ Point a, b;\n        Segment() = default;\n        Segment(const Point& from,\
    \ const Point& to) : a(from), b(to) {}\n    };\n    struct Circle {\n        Point\
    \ center;\n        coordinate_t radius;\n        Circle() = default;\n       \
    \ Circle(const Point& c, const coordinate_t& r) : center(c), radius(r) {}\n  \
    \  };\n\n    // Triangle\n\n    coordinate_t signed_area_doubled(const Point&\
    \ a, const Point& b, const Point& c) {\n        return det(b - a, c - a);\n  \
    \  }\n    coordinate_t area_doubled(const Point& a, const Point& b, const Point&\
    \ c) {\n        return std::abs(signed_area_doubled(a, b, c));\n    }\n\n    //\
    \ Line\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto is_parallel(const\
    \ line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \ {\n        return det(l1.b - l1.a, l2.b - l2.a) == 0;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto is_orthogonal(const\
    \ line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \ {\n        return dot(l1.b - l1.a, l2.b - l2.a) == 0;\n    }\n    template <typename\
    \ line_t_1, typename line_t_2>\n    auto on_the_same_line(const line_t_1& l1,\
    \ const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {\n        return\
    \ is_parallel(l1, l2) and det(l1.b - l1.a, l2.a - l1.a) == 0;\n    }\n\n    Containment\
    \ contains(const Line& l, const Point& p) {\n        if (l.a.x == l.b.x) return\
    \ p.x == l.a.x ? Containment::ON : Containment::OUT;\n        coordinate_t a =\
    \ p.x - l.a.x, b = p.y - l.a.y, c = l.b.x - p.x, d = l.b.y - p.y;\n        return\
    \ b * c == a * d ? Containment::ON : Containment::OUT;\n    }\n    Containment\
    \ contains(const Ray& l, const Point& p) {\n        if (contains(Line { l.a, l.b\
    \ }, p) == Containment::OUT) return Containment::OUT;\n        if (l.a.x == l.b.x)\
    \ {\n            if (l.a.y < l.b.y) return p.y >= l.a.y ? Containment::ON : Containment::OUT;\n\
    \            else return p.y <= l.a.y ? Containment::ON : Containment::OUT;\n\
    \        } else if (l.a.x < l.b.x) {\n            return p.x >= l.a.x ? Containment::ON\
    \ : Containment::OUT;\n        } else {\n            return p.x <= l.a.x ? Containment::ON\
    \ : Containment::OUT;\n        }\n    }\n    Containment contains(const Segment&\
    \ l, const Point& p) {\n        if (contains(Line { l.a, l.b }, p) == Containment::OUT)\
    \ return Containment::OUT;\n        if (l.a.x == l.b.x) {\n            if (l.a.y\
    \ < l.b.y) return p.y >= l.a.y and p.y <= l.b.y ? Containment::ON : Containment::OUT;\n\
    \            else return p.y >= l.b.y and p.y <= l.a.y ? Containment::ON : Containment::OUT;\n\
    \        } else if (l.a.x < l.b.x) {\n            return p.x >= l.a.x and p.x\
    \ <= l.b.x ? Containment::ON : Containment::OUT;\n        } else {\n         \
    \   return p.x >= l.b.x and p.x <= l.a.x ? Containment::ON : Containment::OUT;\n\
    \        }\n    }\n\n    bool operator==(const Line& l, const Line& m) {\n   \
    \     return on_the_same_line(l, m);\n    }\n    bool operator==(const Ray& l,\
    \ const Ray& m) {\n        return on_the_same_line(l, m) and l.a == m.a;\n   \
    \ }\n    bool operator==(const Segment& l, const Segment& m) {\n        return\
    \ (l.a == m.a and l.b == m.b) or (l.a == m.b and l.b == m.a);\n    }\n\n    //\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B\"\n    bool\
    \ has_common_point(const Segment& l1, const Segment& l2) {\n        int isp_1a\
    \ = isp(l1.a, l1.b, l2.a), isp_1b = isp(l1.a, l1.b, l2.b);\n        if (isp_1a\
    \ * isp_1b > 0) return false;\n        int isp_2a = isp(l2.a, l2.b, l1.a), isp_2b\
    \ = isp(l2.a, l2.b, l1.b);\n        if (isp_2a * isp_2b > 0) return false;\n \
    \       return true;\n    }\n\n    // Polygon\n\n    using Polygon = std::vector<Point>;\n\
    \n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n \
    \   coordinate_t signed_area_doubled(const Polygon& poly) {\n        coordinate_t\
    \ res = 0;\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1;\n            if (j == sz) j = 0;\n           \
    \ res += signed_area_doubled(ZERO, poly[i], poly[j]);\n        }\n        return\
    \ res;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n\
    \    coordinate_t area_doubled(const Polygon& poly) {\n        return std::abs(signed_area_doubled(poly));\n\
    \    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\n\
    \    template <bool accept_180_degree = true>\n    bool is_convex(const Polygon&\
    \ poly) {\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1, k = i + 2;\n            if (j >= sz) j -= sz;\n\
    \            if (k >= sz) k -= sz;\n            int dir = isp(poly[i], poly[j],\
    \ poly[k]);\n            if constexpr (accept_180_degree) {\n                if\
    \ (dir == ISP::R_CURVE) return false;\n            } else {\n                if\
    \ (dir != ISP::L_CURVE) return false;\n            }\n        }\n        return\
    \ true;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C\n\
    \    Containment contains(const Polygon& poly, const Point& p) {\n        bool\
    \ in = false;\n        int sz = poly.size();\n        for (int i = 0; i < sz;\
    \ ++i) {\n            int j = i + 1;\n            if (j == sz) j -= sz;\n    \
    \        Point a = poly[i] - p, b = poly[j] - p;\n            if (a.y > b.y) std::swap(a,\
    \ b);\n            if (a.y <= 0 and b.y > 0 and det(a, b) < 0) in = not in;\n\
    \            if (det(a, b) == 0 and dot(a, b) <= 0) return Containment::ON;\n\
    \        }\n        return in ? Containment::IN : Containment::OUT;\n    }\n\n\
    \    std::pair<int, int> convex_diameter(const Polygon& convex) {\n        const\
    \ int sz = convex.size();\n        if (sz <= 2) return { 0, sz - 1 };\n      \
    \  auto [si, sj] = [&]{\n            auto [it_min, it_max] = std::minmax_element(convex.begin(),\
    \ convex.end(), XY_COMPARATOR);\n            return std::pair<int, int> { it_min\
    \ - convex.begin(), it_max - convex.begin() };\n        }();\n        coordinate_t\
    \ max_dist = -1;\n        std::pair<int, int> argmax{ -1, -1 };\n        for (int\
    \ i = si, j = sj; i != sj or j != si;) {\n            if (multiplied_t dij = square_abs(convex[j]\
    \ - convex[i]); dij > max_dist) max_dist = dij, argmax = { i, j };\n         \
    \   int ni = (i + 1) % sz, nj = (j + 1) % sz;\n            if (det(convex[ni]\
    \ - convex[i], convex[nj] - convex[j]) < 0) i = ni;\n            else j = nj;\n\
    \        }\n        return argmax;\n    }\n\n    // Circle\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A\n\
    \    int tangent_num(const Circle& c1, const Circle& c2) {\n        coordinate_t\
    \ r1 = c1.radius, r2 = c2.radius;\n        if (r1 > r2) return tangent_num(c2,\
    \ c1);\n        coordinate_t d2 = square_abs(c1.center - c2.center);\n       \
    \ coordinate_t dp = d2 - (r1 + r2) * (r1 + r2);\n        if (dp > 0) return 4;\n\
    \        if (dp == 0) return 3;\n        coordinate_t dn = d2 - (r2 - r1) * (r2\
    \ - r1);\n        if (dn > 0) return 2;\n        if (dn == 0) return 1;\n    \
    \    return 0;\n    }\n    bool has_common_point(const Circle& c1, const Circle&\
    \ c2) {\n        int tnum = tangent_num(c1, c2);\n        return 1 <= tnum and\
    \ tnum <= 3;\n    }\n    bool has_cross_point(const Circle& c1, const Circle&\
    \ c2) {\n        return tangent_num(c1, c2) == 2;\n    }\n\n    Containment contains(const\
    \ Circle& c, const Point& p) {\n        coordinate_t df = square_abs(c.center\
    \ - p) - c.radius * c.radius;\n        if (df > 0) return Containment::OUT;\n\
    \        if (df < 0) return Containment::IN;\n        return Containment::ON;\n\
    \    }\n} // namespace suisen::integral_geometry\n\n#endif // SUISEN_GEOMETRY\n"
  dependsOn:
  - library/integral_geom/point.hpp
  isVerificationFile: false
  path: library/integral_geom/geometry.hpp
  requiredBy:
  - library/integral_geom/closest_pair.hpp
  - library/integral_geom/farthest_pair.hpp
  timestamp: '2022-07-10 19:58:11+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/integral_geom/closest_pair/AOJ_0585.test.cpp
  - test/src/integral_geom/geometry/CGL_1_C.test.cpp
  - test/src/integral_geom/geometry/CGL_3_A.test.cpp
  - test/src/integral_geom/geometry/CGL_7_A.test.cpp
  - test/src/integral_geom/geometry/CGL_2_B.test.cpp
  - test/src/integral_geom/geometry/CGL_3_B.test.cpp
  - test/src/integral_geom/geometry/CGL_2_A.test.cpp
  - test/src/integral_geom/geometry/CGL_3_C.test.cpp
  - test/src/integral_geom/geometry/abc259_d.test.cpp
documentation_of: library/integral_geom/geometry.hpp
layout: document
title: "\u5E7E\u4F55\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8 (\u6574\u6570\u5EA7\u6A19\
  )"
---
## 幾何テンプレート (整数座標)
