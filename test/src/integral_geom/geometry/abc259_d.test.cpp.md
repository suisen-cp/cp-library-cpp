---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/integral_geom/geometry.hpp
    title: library/integral_geom/geometry.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc259/tasks/abc259_d
    links:
    - https://atcoder.jp/contests/abc259/tasks/abc259_d
  bundledCode: "#line 1 \"test/src/integral_geom/geometry/abc259_d.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc259/tasks/abc259_d\"\n\n#include <iostream>\n\
    #include <atcoder/dsu>\n\n#line 1 \"library/integral_geom/geometry.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <cmath>\n#line 7 \"library/integral_geom/geometry.hpp\"\
    \n#include <vector>\n\nnamespace suisen::integral_geometry {\n\n    using coordinate_t\
    \ = long long;\n\n    struct Point {\n        long long x, y;\n        constexpr\
    \ Point(long long x = 0, long long y = 0) : x(x), y(y) {}\n\n        operator\
    \ std::pair<coordinate_t, coordinate_t>() { return std::pair<coordinate_t, coordinate_t>\
    \ { x, y }; }\n\n        friend Point operator+(const Point& p) { return p; }\n\
    \        friend Point operator-(const Point& p) { return { -p.x, -p.y }; }\n\n\
    \        friend Point operator+(const Point& lhs, const Point& rhs) { return {\
    \ lhs.x + rhs.x, lhs.y + rhs.y }; }\n        friend Point operator-(const Point&\
    \ lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }\n      \
    \  friend Point operator*(const Point& lhs, const Point& rhs) { return { lhs.x\
    \ * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x }; }\n\n        friend\
    \ Point& operator+=(Point& lhs, const Point& rhs) { lhs.x += rhs.x, lhs.y += rhs.y;\
    \ return lhs; }\n        friend Point& operator-=(Point& lhs, const Point& rhs)\
    \ { lhs.x -= rhs.x, lhs.y -= rhs.y; return lhs; }\n        friend Point& operator*=(Point&\
    \ lhs, const Point& rhs) { return lhs = lhs * rhs; }\n        \n        friend\
    \ Point operator+(const Point& p, coordinate_t real) { return { p.x + real, p.y\
    \ }; }\n        friend Point operator-(const Point& p, coordinate_t real) { return\
    \ { p.x - real, p.y }; }\n        friend Point operator*(const Point& p, coordinate_t\
    \ real) { return { p.x * real, p.y * real }; }\n        friend Point operator/(const\
    \ Point& p, coordinate_t real) { return { p.x / real, p.y / real }; }\n\n    \
    \    friend Point operator+=(Point& p, coordinate_t real) { p.x += real; return\
    \ p; }\n        friend Point operator-=(Point& p, coordinate_t real) { p.x -=\
    \ real; return p; }\n        friend Point operator*=(Point& p, coordinate_t real)\
    \ { p.x *= real, p.y *= real; return p; }\n        friend Point operator/=(Point&\
    \ p, coordinate_t real) { p.x /= real, p.y /= real; return p; }\n\n        friend\
    \ Point operator+(coordinate_t real, const Point& p) { return { real + p.x, p.y\
    \ }; }\n        friend Point operator-(coordinate_t real, const Point& p) { return\
    \ { real - p.x, -p.y }; }\n        friend Point operator*(coordinate_t real, const\
    \ Point& p) { return { real * p.x, real * p.y }; }\n\n        friend bool operator==(const\
    \ Point& lhs, const Point& rhs) { return lhs.x == rhs.x and lhs.y == rhs.y; }\n\
    \        friend bool operator!=(const Point& lhs, const Point& rhs) { return not\
    \ (lhs == rhs); }\n\n        friend std::istream& operator>>(std::istream& in,\
    \ Point& p) { return in >> p.x >> p.y; }\n        friend std::ostream& operator<<(std::ostream&\
    \ out, const Point& p) { return out << p.x << ' ' << p.y; }\n    };\n\n    //\
    \ relations between three points X, Y, Z.\n\n    struct ISP {\n        static\
    \ constexpr int L_CURVE = +1; // +---------------+ Z is in 'a' => ISP = +1\n \
    \       static constexpr int R_CURVE = -1; // |aaaaaaaaaaaaaaa| Z is in 'b' =>\
    \ ISP = -1\n        static constexpr int FRONT = +2;   // |ddd X eee Y ccc| Z\
    \ is in 'c' => ISP = +2\n        static constexpr int BACK = -2;    // |bbbbbbbbbbbbbbb|\
    \ Z is in 'd' => ISP = -2\n        static constexpr int MIDDLE = 0;   // +---------------+\
    \ Z is in 'e' => ISP =  0\n    };\n\n    enum class Containment { OUT, ON, IN\
    \ };\n\n    constexpr Point ZERO = { 0, 0 };\n    constexpr Point ONE  = { 1,\
    \ 0 };\n    constexpr Point I    = { 0, 1 };\n\n    constexpr auto XY_COMPARATOR\
    \         = [](const Point& p, const Point& q) { return p.x == q.x ? p.y < q.y\
    \ : p.x < q.x; };\n    constexpr auto XY_COMPARATOR_GREATER = [](const Point&\
    \ p, const Point& q) { return p.x == q.x ? p.y > q.y : p.x > q.x; };\n    constexpr\
    \ auto YX_COMPARATOR         = [](const Point& p, const Point& q) { return p.y\
    \ == q.y ? p.x < q.x : p.y < q.y; };\n    constexpr auto YX_COMPARATOR_GREATER\
    \ = [](const Point& p, const Point& q) { return p.y == q.y ? p.x > q.x : p.y >\
    \ q.y; };\n\n    int sgn(coordinate_t x) { return x < 0 ? -1 : x > 0 ? +1 : 0;\
    \ }\n    int compare(coordinate_t x, coordinate_t y) { return sgn(x - y); }\n\n\
    \    auto cartesian(const coordinate_t real, const coordinate_t imag) { return\
    \ Point(real, imag); }\n    auto conj(const Point& z) { return Point(z.x, -z.y);\
    \ }\n    auto arg(const Point& z) { return std::atan2(z.y, z.x); }\n    auto square_abs(const\
    \ Point& z) { return z.x * z.x + z.y * z.y; }\n    auto abs(const Point& z) {\
    \ return std::sqrt(square_abs(z)); }\n\n    auto dot(const Point& a, const Point&\
    \ b) { return a.x * b.x + a.y * b.y; }\n    auto det(const Point& a, const Point&\
    \ b) { return a.x * b.y - a.y * b.x; }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C\n\
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
    \ int sz = convex.size();\n        auto d2 = [&](int i, int j) { return square_abs(convex[j\
    \ % sz] - convex[i]); };\n        coordinate_t max_dist = -1;\n        std::pair<int,\
    \ int> argmax{ -1, -1 };\n        for (int i = 0, j = 0; i < sz; ++i) {\n    \
    \        while (d2(i, j + 1) >= d2(i, j)) ++j;\n            coordinate_t cur_dist\
    \ = d2(i, j);\n            if (cur_dist > max_dist) max_dist = cur_dist, argmax\
    \ = { i, j };\n        }\n        argmax.second %= sz;\n        return argmax;\n\
    \    }\n\n    // Circle\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A\n\
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
    \    }\n} // namespace suisen::integral_geometry\n\n\n#line 7 \"test/src/integral_geom/geometry/abc259_d.test.cpp\"\
    \nusing namespace suisen::integral_geometry;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    Point s,\
    \ t;\n    std::cin >> s >> t;\n\n    std::vector<Circle> cs(n + 2);\n    cs[0]\
    \ = { s, 0 }, cs[n + 1] = { t, 0 };\n    for (int i = 1; i <= n; ++i) {\n    \
    \    Point c;\n        long long r;\n        std::cin >> c >> r;\n        cs[i]\
    \ = { c, r };\n    }\n    \n    atcoder::dsu uf(n + 2);\n    for (int i = 0; i\
    \ < n + 2; ++i) for (int j = 0; j < i; ++j) {\n        if (has_common_point(cs[i],\
    \ cs[j])) uf.merge(i, j);\n    }\n    std::cout << (uf.same(0, n + 1) ? \"Yes\"\
    \ : \"No\") << std::endl;\n    \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc259/tasks/abc259_d\"\n\n\
    #include <iostream>\n#include <atcoder/dsu>\n\n#include \"library/integral_geom/geometry.hpp\"\
    \nusing namespace suisen::integral_geometry;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    Point s,\
    \ t;\n    std::cin >> s >> t;\n\n    std::vector<Circle> cs(n + 2);\n    cs[0]\
    \ = { s, 0 }, cs[n + 1] = { t, 0 };\n    for (int i = 1; i <= n; ++i) {\n    \
    \    Point c;\n        long long r;\n        std::cin >> c >> r;\n        cs[i]\
    \ = { c, r };\n    }\n    \n    atcoder::dsu uf(n + 2);\n    for (int i = 0; i\
    \ < n + 2; ++i) for (int j = 0; j < i; ++j) {\n        if (has_common_point(cs[i],\
    \ cs[j])) uf.merge(i, j);\n    }\n    std::cout << (uf.same(0, n + 1) ? \"Yes\"\
    \ : \"No\") << std::endl;\n    \n    return 0;\n}"
  dependsOn:
  - library/integral_geom/geometry.hpp
  isVerificationFile: true
  path: test/src/integral_geom/geometry/abc259_d.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 16:59:40+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/integral_geom/geometry/abc259_d.test.cpp
layout: document
redirect_from:
- /verify/test/src/integral_geom/geometry/abc259_d.test.cpp
- /verify/test/src/integral_geom/geometry/abc259_d.test.cpp.html
title: test/src/integral_geom/geometry/abc259_d.test.cpp
---
