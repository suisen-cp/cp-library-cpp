---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/geom/geometry.hpp
    title: "\u5E7E\u4F55\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '0.000001'
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
  bundledCode: "#line 1 \"test/src/geom/geometry/CGL_4_B.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\"\n#define\
    \ ERROR 0.000001\n\n#include <cassert>\n#include <iostream>\n#include <iomanip>\n\
    \n#line 1 \"library/geom/geometry.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"\
    library/geom/geometry.hpp\"\n#include <complex>\n#line 8 \"library/geom/geometry.hpp\"\
    \n#include <optional>\n#include <tuple>\n#include <variant>\n#include <vector>\n\
    \nnamespace suisen {\nnamespace geometry {\n    using coordinate_t = long double;\n\
    \    using Point = std::complex<coordinate_t>;\n\n    coordinate_t getx(const\
    \ Point& p) { return p.real(); }\n    coordinate_t gety(const Point& p) { return\
    \ p.imag(); }\n\n    // operator\n\n    Point operator+(const Point &p, coordinate_t\
    \ real) { return Point(p) + Point(real, 0); }\n    Point operator-(const Point\
    \ &p, coordinate_t real) { return Point(p) - Point(real, 0); }\n    Point operator*(const\
    \ Point &p, coordinate_t real) { return Point(p) * Point(real, 0); }\n    Point\
    \ operator/(const Point &p, coordinate_t real) { return Point(p) / Point(real,\
    \ 0); }\n    Point operator+(coordinate_t real, const Point &p) { return Point(real,\
    \ 0) + Point(p); }\n    Point operator-(coordinate_t real, const Point &p) { return\
    \ Point(real, 0) - Point(p); }\n    Point operator*(coordinate_t real, const Point\
    \ &p) { return Point(real, 0) * Point(p); }\n    Point operator/(coordinate_t\
    \ real, const Point &p) { return Point(real, 0) / Point(p); }\n\n    std::istream&\
    \ operator>>(std::istream &in, Point &p) {\n        coordinate_t x, y;\n     \
    \   in >> x >> y;\n        p = Point(x, y);\n        return in;\n    }\n    std::ostream&\
    \ operator<<(std::ostream &out, const Point &p) {\n        return out << getx(p)\
    \ << ' ' << gety(p);\n    }\n}\n\nnamespace geometry {\n    // relations between\
    \ three points X, Y, Z.\n\n    struct ISP {\n        static constexpr int L_CURVE\
    \ = +1; // +---------------+ Z is in 'a' => ISP = +1\n        static constexpr\
    \ int R_CURVE = -1; // |aaaaaaaaaaaaaaa| Z is in 'b' => ISP = -1\n        static\
    \ constexpr int FRONT   = +2; // |ddd X eee Y ccc| Z is in 'c' => ISP = +2\n \
    \       static constexpr int BACK    = -2; // |bbbbbbbbbbbbbbb| Z is in 'd' =>\
    \ ISP = -2\n        static constexpr int MIDDLE  =  0; // +---------------+ Z\
    \ is in 'e' => ISP =  0\n    };\n\n    struct Sign {\n        static constexpr\
    \ int NEGATIVE = -1;\n        static constexpr int ZERO = 0;\n        static constexpr\
    \ int POSITIVE = +1;\n    };\n\n    enum class Containment {\n        OUT, ON,\
    \ IN\n    };\n\n    constexpr Point ZERO = Point(0, 0);\n    constexpr Point ONE\
    \  = Point(1, 0);\n    constexpr Point I    = Point(0, 1);\n    constexpr coordinate_t\
    \ EPS = 1e-9;\n    constexpr coordinate_t PI  = 3.14159265358979323846264338327950288419716939937510L;\n\
    \    constexpr coordinate_t E   = 2.71828182845904523536028747135266249775724709369995L;\n\
    \n    constexpr auto XY_COMPARATOR = [](const Point &p, const Point &q) {\n  \
    \      return getx(p) == getx(q) ? gety(p) < gety(q) : getx(p) < getx(q);\n  \
    \  };\n    constexpr auto XY_COMPARATOR_GREATER = [](const Point &p, const Point\
    \ &q) {\n        return getx(p) == getx(q) ? gety(p) > gety(q) : getx(p) > getx(q);\n\
    \    };\n    constexpr auto YX_COMPARATOR = [](const Point &p, const Point &q)\
    \ {\n        return gety(p) == gety(q) ? getx(p) < getx(q) : gety(p) < gety(q);\n\
    \    };\n    constexpr auto YX_COMPARATOR_GREATER = [](const Point &p, const Point\
    \ &q) {\n        return gety(p) == gety(q) ? getx(p) > getx(q) : gety(p) > gety(q);\n\
    \    };\n\n    int sgn(coordinate_t x) {\n        return x > EPS ? Sign::POSITIVE\
    \ : x < -EPS ? Sign::NEGATIVE : Sign::ZERO;\n    }\n    int compare(coordinate_t\
    \ x, coordinate_t y) {\n        return sgn(x - y);\n    }\n\n    auto cartesian(const\
    \ coordinate_t real, const coordinate_t imag) {\n        return Point(real, imag);\n\
    \    }\n    auto polar(const coordinate_t rho, const coordinate_t theta) {\n \
    \       return Point(rho * std::cos(theta), rho * std::sin(theta));\n    }\n \
    \   auto cis(const coordinate_t theta) {\n        return Point(std::cos(theta),\
    \ std::sin(theta));\n    }\n    auto conj(const Point &z) {\n        return Point(getx(z),\
    \ -gety(z));\n    }\n    auto arg(const Point &z) {\n        return std::atan2(gety(z),\
    \ getx(z));\n    }\n    auto square_abs(const Point &z) {\n        return getx(z)\
    \ * getx(z) + gety(z) * gety(z);\n    }\n    auto abs(const Point &z) {\n    \
    \    return std::sqrt(square_abs(z));\n    }\n    auto rot(const Point &z, const\
    \ coordinate_t theta) {\n        return cis(theta) * z;\n    }\n    auto dot(const\
    \ Point &a, const Point &b) {\n        return getx(a) * getx(b) + gety(a) * gety(b);\n\
    \    }\n    auto det(const Point &a, const Point &b) {\n        return getx(a)\
    \ * gety(b) - gety(a) * getx(b);\n    }\n    bool equals(const Point &a, const\
    \ Point &b) {\n        return sgn(getx(a) - getx(b)) == Sign::ZERO and sgn(gety(a)\
    \ - gety(b)) == Sign::ZERO;\n    }\n    bool equals(coordinate_t a, coordinate_t\
    \ b) {\n        return compare(a, b) == 0;\n    }\n    \n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C\n\
    \    int isp(const Point &a, const Point &b, const Point &c) {\n        Point\
    \ ab = b - a, ac = c - a;\n        int s = sgn(det(ab, ac));\n        if (s ==\
    \ Sign::POSITIVE) return ISP::L_CURVE;\n        if (s == Sign::NEGATIVE) return\
    \ ISP::R_CURVE;\n        if (sgn(dot(ab, ac)) == Sign::NEGATIVE) return ISP::BACK;\n\
    \        Point ba = a - b, bc = c - b;\n        if (sgn(dot(ba, bc)) == Sign::NEGATIVE)\
    \ return ISP::FRONT;\n        return ISP::MIDDLE;\n    }\n\n    struct Line {\n\
    \        Point a, b;\n        Line() : Line(ZERO, ZERO) {}\n        Line(const\
    \ Point &from, const Point &to) : a(from), b(to) {}\n        // coef_x * x + coef_y\
    \ * y + cnst = 0\n        Line(coordinate_t coef_x, coordinate_t coef_y, coordinate_t\
    \ cnst) {\n            if (not equals(coef_x, 0.)) {\n                a = { (coef_y\
    \ - cnst) / coef_x, -1. };\n                b = { (-coef_y - cnst) / coef_x, +1.\
    \ };\n            } else {\n                a = { -1., (coef_x - cnst) / coef_y\
    \ };\n                b = { +1., (-coef_x - cnst) / coef_y };\n            }\n\
    \        }\n\n        template <size_t I> const std::tuple_element_t<I, Line>&\
    \ get() const {\n            static_assert(I < std::tuple_size_v<Line>);\n   \
    \         if constexpr (I == 0) return a;\n            else if constexpr (I ==\
    \ 1) return b;\n        }\n        template <size_t I> std::tuple_element_t<I,\
    \ Line>& get() {\n            static_assert(I < std::tuple_size_v<Line>);\n  \
    \          if constexpr (I == 0) return a;\n            else if constexpr (I ==\
    \ 1) return b;\n        }\n    };\n    struct Ray {\n        Point a, b;\n   \
    \     Ray() : Ray(ZERO, ZERO) {}\n        Ray(const Point &from, const Point &to)\
    \ : a(from), b(to) {}\n\n        template <size_t I> const std::tuple_element_t<I,\
    \ Ray>& get() const {\n            static_assert(I < std::tuple_size_v<Ray>);\n\
    \            if constexpr (I == 0) return a;\n            else if constexpr (I\
    \ == 1) return b;\n        }\n        template <size_t I> std::tuple_element_t<I,\
    \ Ray>& get() {\n            static_assert(I < std::tuple_size_v<Ray>);\n    \
    \        if constexpr (I == 0) return a;\n            else if constexpr (I ==\
    \ 1) return b;\n        }\n    };\n    struct Segment {\n        Point a, b;\n\
    \        Segment() : Segment(ZERO, ZERO) {}\n        Segment(const Point &from,\
    \ const Point &to) : a(from), b(to) {}\n\n        template <size_t I> const std::tuple_element_t<I,\
    \ Segment>& get() const {\n            static_assert(I < std::tuple_size_v<Segment>);\n\
    \            if constexpr (I == 0) return a;\n            else if constexpr (I\
    \ == 1) return b;\n        }\n        template <size_t I> std::tuple_element_t<I,\
    \ Segment>& get() {\n            static_assert(I < std::tuple_size_v<Segment>);\n\
    \            if constexpr (I == 0) return a;\n            else if constexpr (I\
    \ == 1) return b;\n        }\n    };\n    struct Circle {\n        Point center;\n\
    \        coordinate_t radius;\n        Circle() : Circle(ZERO, 0) {}\n       \
    \ Circle(const Point &c, const coordinate_t &r) : center(c), radius(r) {}\n  \
    \  };\n\n    // Triangle\n    \n    coordinate_t signed_area(const Point &a, const\
    \ Point &b, const Point &c) {\n        return det(b - a, c - a) / 2;\n    }\n\
    \    coordinate_t area(const Point &a, const Point &b, const Point &c) {\n   \
    \     return std::abs(signed_area(a, b, c));\n    }\n    Point pG(const Point\
    \ &a, const Point &b, const Point &c) {\n        return (a + b + c) / 3;\n   \
    \ }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B\n\
    \    Circle pI(const Point &a, const Point &b, const Point &c) {\n        coordinate_t\
    \ la = abs(b - c), lb = abs(c - a), lc = abs(a - b);\n        coordinate_t l =\
    \ la + lb + lc;\n        la /= l, lb /= l, lc /= l;\n        Point center = la\
    \ * a + lb * b + lc * c;\n        coordinate_t radius = 2 * area(a, b, c) / l;\n\
    \        return Circle(center, radius);\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C\n\
    \    Circle pO(const Point &a, const Point &b, const Point &c) {\n        Point\
    \ ab = b - a, bc = c - b, ca = a - c;\n        coordinate_t la = square_abs(bc),\
    \ lb = square_abs(ca), lc = square_abs(ab);\n        coordinate_t s = la * (lb\
    \ + lc - la), t = lb * (lc + la - lb), u = lc * (la + lb - lc);\n        coordinate_t\
    \ l = s + t + u;\n        s /= l, t /= l, u /= l;\n        Point center = a *\
    \ s + b * t + c * u;\n        return Circle(center, abs(center - a));\n    }\n\
    \    Point pH(const Point &a, const Point &b, const Point &c) {\n        return\
    \ a + b + c - 2 * pO(a, b, c).center;\n    }\n    auto pIabc(const Point &a, const\
    \ Point &b, const Point &c) {\n        return std::make_tuple(pI(-a, b, c), pI(a,\
    \ -b, c), pI(a, b, -c));\n    }\n\n    // Line\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto is_parallel(const\
    \ line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \ {\n        return sgn(det(l1.b - l1.a, l2.b - l2.a)) == Sign::ZERO;\n    }\n\
    \    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A\n  \
    \  template <typename line_t_1, typename line_t_2>\n    auto is_orthogonal(const\
    \ line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \  {\n        return sgn(dot(l1.b - l1.a, l2.b - l2.a)) == Sign::ZERO;\n    }\n\
    \    template <typename line_t_1, typename line_t_2>\n    auto on_the_same_line(const\
    \ line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())\
    \  {\n        return is_parallel(l1, l2) and sgn(det(l1.b - l1.a, l2.a - l1.a))\
    \ == Sign::ZERO;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A\n\
    \    template <typename line_t>\n    Point projection(const Point &p, const line_t\
    \ &line) {\n        Point a = p - line.a;\n        Point b = line.b - line.a;\n\
    \        return line.a + dot(a, b) / square_abs(b) * b;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B\n\
    \    template <typename line_t>\n    Point reflection(const Point &p, const line_t\
    \ &line) {\n        Point h = projection(p, line);\n        return p + (h - p)\
    \ * 2;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D\n\
    \    coordinate_t square_distance(const Point &p, const Segment &l) {\n      \
    \  Point h = projection(p, l);\n        if (isp(l.a, l.b, h) == ISP::MIDDLE) {\n\
    \            return square_abs(h - p);\n        } else {\n            return std::min(square_abs(p\
    \ - l.a), square_abs(p - l.b));\n        }\n    }\n    coordinate_t square_distance(const\
    \ Segment &l, const Point &p) {\n        return square_distance(p, l);\n    }\n\
    \    coordinate_t square_distance(const Point &p, const Ray &l) {\n        Point\
    \ h = projection(p, l);\n        int dir = isp(l.a, l.b, h);\n        return dir\
    \ == ISP::MIDDLE or dir == ISP::FRONT ? square_abs(h - p) : std::min(square_abs(p\
    \ - l.a), square_abs(p - l.b));\n    }\n    coordinate_t square_distance(const\
    \ Ray &l, const Point &p) {\n        return square_distance(p, l);\n    }\n  \
    \  coordinate_t square_distance(const Point &p, const Line &l) {\n        return\
    \ square_abs(projection(p, l) - p);\n    }\n    coordinate_t square_distance(const\
    \ Line &l, const Point &p) {\n        return square_distance(p, l);\n    }\n \
    \   // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D\n   \
    \ coordinate_t distance(const Point &p, const Segment &l) {\n        return std::sqrt(square_distance(p,\
    \ l));\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D\n\
    \    coordinate_t distance(const Segment &l, const Point &p) {\n        return\
    \ distance(p, l);\n    }\n    coordinate_t distance(const Point &p, const Ray\
    \ &l) {\n        return std::sqrt(square_distance(p, l));\n    }\n    coordinate_t\
    \ distance(const Ray &l, const Point &p) {\n        return distance(p, l);\n \
    \   }\n    coordinate_t distance(const Point &p, const Line &l) {\n        return\
    \ std::sqrt(square_distance(p, l));\n    }\n    coordinate_t distance(const Line\
    \ &l, const Point &p) {\n        return distance(p, l);\n    }\n\n    Containment\
    \ contains(const Segment &l, const Point &p) {\n        return sgn(distance(l,\
    \ p)) == 0 ? Containment::ON : Containment::OUT;\n    }\n    Containment contains(const\
    \ Ray &l, const Point &p) {\n        return sgn(distance(l, p)) == 0 ? Containment::ON\
    \ : Containment::OUT;\n    }\n    Containment contains(const Line &l, const Point\
    \ &p) {\n        return sgn(distance(l, p)) == 0 ? Containment::ON : Containment::OUT;\n\
    \    }\n\n    bool equals(const Line &l, const Line &m) {\n        return on_the_same_line(l,\
    \ m);\n    }\n    bool equals(const Ray &l, const Ray &m) {\n        return on_the_same_line(l,\
    \ m) and equals(l.a, m.a);\n    }\n    bool equals(const Segment &l, const Segment\
    \ &m) {\n        return (equals(l.a, m.a) and equals(l.b, m.b)) or (equals(l.a,\
    \ m.b) and equals(l.b, m.a));\n    }\n\n    // \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B\"\
    \n    bool has_common_point(const Segment &l1, const Segment &l2) {\n        int\
    \ isp_1a = isp(l1.a, l1.b, l2.a), isp_1b = isp(l1.a, l1.b, l2.b);\n        if\
    \ (isp_1a * isp_1b > 0) return false;\n        int isp_2a = isp(l2.a, l2.b, l1.a),\
    \ isp_2b = isp(l2.a, l2.b, l1.b);\n        if (isp_2a * isp_2b > 0) return false;\n\
    \        return true;\n    }\n\n    namespace internal {\n        template <typename\
    \ line_t_1, typename line_t_2>\n        Point cross_point(const line_t_1 &l1,\
    \ const line_t_2 &l2) {\n            assert(not is_parallel(l1, l2));\n      \
    \      Point u = l1.b - l1.a, v = l2.a - l2.b, c = l2.a - l1.a;\n            return\
    \ l2.a - det(u, c) / det(u, v) * v;\n        }\n    }\n\n    // \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C\"\
    \n    std::variant<std::nullptr_t, Point, Segment> common_point(const Segment\
    \ &l1, const Segment &l2) {\n        if (not has_common_point(l1, l2)) return\
    \ nullptr;\n        if (not is_parallel(l1, l2)) return internal::cross_point(l1,\
    \ l2);\n        std::vector<Point> ps { l1.a, l1.b, l2.a, l2.b };\n        for\
    \ (int i = 0; i <= 2; ++i) for (int j = 2; j >= i; --j) {\n            if (XY_COMPARATOR(ps[j\
    \ + 1], ps[j])) std::swap(ps[j], ps[j + 1]);\n        }\n        if (equals(ps[1],\
    \ ps[2])) return ps[1];\n        return Segment(ps[1], ps[2]);\n    }\n\n    //\
    \ https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D\n    coordinate_t\
    \ square_distance(const Segment &l1, const Segment &l2) {\n        if (has_common_point(l1,\
    \ l2)) return 0;\n        return std::min({ square_distance(l1, l2.a), square_distance(l1,\
    \ l2.b), square_distance(l1.a, l2), square_distance(l1.b, l2) });\n    }\n   \
    \ // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D\n    coordinate_t\
    \ distance(const Segment &l1, const Segment &l2) {\n        return std::sqrt(square_distance(l1,\
    \ l2));\n    }\n\n    // Polygon\n\n    using Polygon = std::vector<Point>;\n\n\
    \    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n  \
    \  coordinate_t signed_area(const Polygon &poly) {\n        coordinate_t res =\
    \ 0;\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i) {\n\
    \            int j = i + 1;\n            if (j == sz) j = 0;\n            res\
    \ += signed_area(ZERO, poly[i], poly[j]);\n        }\n        return res;\n  \
    \  }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A\n\
    \    auto area(const Polygon &poly) {\n        return std::abs(signed_area(poly));\n\
    \    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B\n\
    \    template <bool accept_180_degree = true>\n    bool is_convex(const Polygon\
    \ &poly) {\n        int sz = poly.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1, k = i + 2;\n            if (j >= sz) j -= sz;\n\
    \            if (k >= sz) k -= sz;\n            int dir = isp(poly[i], poly[j],\
    \ poly[k]);\n            if constexpr (accept_180_degree) {\n                if\
    \ (dir == ISP::R_CURVE) return false;\n            } else {\n                if\
    \ (dir != ISP::L_CURVE) return false;\n            }\n        }\n        return\
    \ true;\n    }\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C\n\
    \    Containment contains(const Polygon &poly, const Point &p) {\n        bool\
    \ in = false;\n        int sz = poly.size();\n        for (int i = 0; i < sz;\
    \ ++i) {\n            int j = i + 1;\n            if (j == sz) j -= sz;\n    \
    \        Point a = poly[i] - p, b = poly[j] - p;\n            if (gety(a) > gety(b))\
    \ std::swap(a, b);\n            if (sgn(gety(a)) <= 0 and sgn(gety(b)) > 0 and\
    \ sgn(det(a, b)) < 0) in = not in;\n            if (sgn(det(a, b)) == 0 and sgn(dot(a,\
    \ b)) <= 0) return Containment::ON;\n        }\n        return in ? Containment::IN\
    \ : Containment::OUT;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\n\
    \    std::tuple<int, int, coordinate_t> convex_diameter(const Polygon& convex)\
    \ {\n        const int sz = convex.size();\n        if (sz <= 2) return { 0, sz\
    \ - 1, abs(convex.front() - convex.back()) };\n        auto [si, sj] = [&]{\n\
    \            auto [it_min, it_max] = std::minmax_element(convex.begin(), convex.end(),\
    \ XY_COMPARATOR);\n            return std::pair<int, int> { it_min - convex.begin(),\
    \ it_max - convex.begin() };\n        }();\n        coordinate_t max_dist = -1;\n\
    \        std::pair<int, int> argmax{ -1, -1 };\n        for (int i = si, j = sj;\
    \ i != sj or j != si;) {\n            if (coordinate_t dij = square_abs(convex[j]\
    \ - convex[i]); dij > max_dist) max_dist = dij, argmax = { i, j };\n         \
    \   int ni = (i + 1) % sz, nj = (j + 1) % sz;\n            if (det(convex[ni]\
    \ - convex[i], convex[nj] - convex[j]) < 0) i = ni;\n            else j = nj;\n\
    \        }\n        return { argmax.first, argmax.second, ::sqrtl(max_dist) };\n\
    \    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C\n\
    \    auto convex_cut(const Polygon &convex, const Line &l) {\n        Polygon\
    \ res;\n        int sz = convex.size();\n        for (int i = 0; i < sz; ++i)\
    \ {\n            int j = i + 1;\n            if (j == sz) j -= sz;\n         \
    \   const Point &a = convex[i], &b = convex[j];\n            int da = sgn(det(l.b\
    \ - l.a, a - l.a));\n            if (da >= 0) res.push_back(a);\n            int\
    \ db = sgn(det(l.b - l.a, b - l.a));\n            if (da * db < 0) res.push_back(internal::cross_point(l,\
    \ Segment(a, b)));\n        }\n        return res;\n    }\n\n    // Circle\n\n\
    \    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A\n  \
    \  int tangent_num(const Circle &c1, const Circle &c2) {\n        coordinate_t\
    \ r1 = c1.radius, r2 = c2.radius;\n        if (r1 > r2) return tangent_num(c2,\
    \ c1);\n        coordinate_t d = abs(c1.center - c2.center);\n        int cp =\
    \ compare(d, r1 + r2);\n        if (cp > 0) return 4;\n        if (cp == 0) return\
    \ 3;\n        int cn = compare(d, r2 - r1);\n        if (cn > 0) return 2;\n \
    \       if (cn == 0) return 1;\n        return 0;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D\n\
    \    std::vector<Point> common_point(const Circle &c, const Line &l) {\n     \
    \   Point h = projection(c.center, l);\n        coordinate_t d = abs(c.center\
    \ - h);\n        int cp = compare(d, c.radius);\n        if (cp > 0) return {};\n\
    \        if (cp == 0) return { h };\n        auto v = (l.a - l.b) * (std::sqrt(c.radius\
    \ * c.radius - d * d) / abs(l.a - l.b));\n        return { h - v, h + v };\n \
    \   }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H\n\
    \    std::vector<Point> common_point(const Circle &c, const Segment &l) {\n  \
    \      auto ps = common_point(c, Line(l.a, l.b));\n        ps.erase(std::remove_if(ps.begin(),\
    \ ps.end(), [&](const auto &p) { return contains(l, p) != Containment::ON; }),\
    \ ps.end());\n        return ps;\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E\n\
    \    std::vector<Point> common_point(const Circle &c1, const Circle &c2) {\n \
    \       coordinate_t r1 = c1.radius, r2 = c2.radius;\n        if (r1 > r2) return\
    \ common_point(c2, c1);\n        coordinate_t d = abs(c1.center - c2.center);\n\
    \        int cp = compare(d, r1 + r2), cn = compare(d, r2 - r1);\n        if (cp\
    \ > 0 or cn < 0) return {};\n        auto v = c1.center - c2.center;\n       \
    \ coordinate_t lv = abs(v);\n        if (cp == 0 or cn == 0) {\n            return\
    \ { c2.center + v * (r2 / lv) };\n        }\n        coordinate_t lp = d, ln =\
    \ (r2 * r2 - r1 * r1) / d;\n        coordinate_t p = (lp + ln) / 2, x = sqrt(r2\
    \ * r2 - p * p);\n        auto h = c2.center + v * (p / lv);\n        auto t =\
    \ v * I;\n        return { h + t * (x / lv), h - t * (x / lv) };\n    }\n\n  \
    \  // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F\n    Containment\
    \ contains(const Circle &c, const Point &p) {\n        coordinate_t d = abs(c.center\
    \ - p);\n        int cp = compare(d, c.radius);\n        if (cp > 0) return Containment::OUT;\n\
    \        if (cp < 0) return Containment::IN;\n        return Containment::ON;\n\
    \    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F\n\
    \    std::vector<Point> tangent_to_circle(const Circle &c, const Point &p) {\n\
    \        Containment cnt = contains(c, p);\n        if (cnt == Containment::IN)\
    \ return {};\n        if (cnt == Containment::ON) return { p };\n        Point\
    \ v = c.center - p;\n        coordinate_t r = c.radius, d = abs(v), l = sqrt(d\
    \ * d - r * r);\n        coordinate_t t = std::asin(r / d);\n        return {\
    \ p + rot(v, t) * (l / d), p + rot(v, -t) * (l / d) };\n    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G\n\
    \    // returns { Line(p, q) | p is on c1, q is on c2, Line(p, q) is common tangent\
    \ of c1 and c2 }\n    std::vector<Line> common_tangent(const Circle &c1, const\
    \ Circle &c2) {\n        int num = tangent_num(c1, c2);\n        std::vector<Line>\
    \ res;\n        if (num == 0) return res;\n        Point a = c1.center, b = c2.center,\
    \ v = b - a;\n        coordinate_t r1 = c1.radius, r2 = c2.radius;\n        coordinate_t\
    \ rp = r1 + r2, rm = r1 - r2, rd = r2 / r1;\n        coordinate_t sqxy = square_abs(v);\n\
    \        coordinate_t rtp = std::sqrt(std::max(sqxy - rp * rp, coordinate_t(0)));\n\
    \        coordinate_t rtm = std::sqrt(std::max(sqxy - rm * rm, coordinate_t(0)));\n\
    \        Point r = v * r1, u = r * Point(0, 1);\n        Point l12 = r * rp, r12\
    \ = u * rtp, l34 = r * rm, r34 = u * rtm;\n        Point p14 = (l34 + r34) / sqxy;\n\
    \        res.emplace_back(a + p14, b + p14 * rd);\n        if (num == 1) return\
    \ res;\n        Point p13 = (l34 - r34) / sqxy;\n        res.emplace_back(a +\
    \ p13, b + p13 * rd);\n        if (num == 2) return res;\n        Point p12 =\
    \ (l12 + r12) / sqxy;\n        res.emplace_back(a + p12, b - p12 * rd);\n    \
    \    if (num == 3) return res;\n        Point p11 = (l12 - r12) / sqxy;\n    \
    \    res.emplace_back(a + p11, b - p11 * rd);\n        return res;\n    }\n\n\
    \    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H\n  \
    \  coordinate_t intersection_area(const Polygon &poly, const Circle &circle) {\n\
    \        int sz = poly.size();\n        coordinate_t r2 = circle.radius * circle.radius;\n\
    \        const Point &c = circle.center;\n        coordinate_t area = 0;\n   \
    \     for (int i = 0; i < sz; i++) {\n            int j = i + 1;\n           \
    \ if (j >= sz) j -= sz;\n            Point a = poly[i], b = poly[j];\n       \
    \     bool in_a = contains(circle, a) == Containment::IN, in_b = contains(circle,\
    \ b) == Containment::IN;\n            Point ca = a - c, cb = b - c;\n        \
    \    if (in_a and in_b) {\n                area += det(ca, cb);\n            \
    \    continue;\n            }\n            std::vector<Point> ps = common_point(circle,\
    \ Segment(a, b));\n            if (ps.empty()) {\n                area += r2 *\
    \ arg(cb / ca);\n            } else {\n                Point s = ps[0];\n    \
    \            Point t = ps.size() == 1 ? s : ps[1];\n                if (compare(square_abs(t\
    \ - a), square_abs(s - a)) < 0) std::swap(s, t);\n                Point cs = s\
    \ - c, ct = t - c;\n                area += det(cs, ct);\n                area\
    \ += in_a ? det(ca, cs) : r2 * arg(cs / ca);\n                area += in_b ? det(ct,\
    \ cb) : r2 * arg(cb / ct);\n            }\n        }\n        return area / 2;\n\
    \    }\n\n    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I\n\
    \    coordinate_t intersection_area(const Circle &c1, const Circle &c2) {\n  \
    \      coordinate_t r = c1.radius, s = c2.radius;\n        if (r < s) return intersection_area(c2,\
    \ c1);\n        Point a = c1.center, b = c2.center;\n        coordinate_t d =\
    \ abs(a - b);\n        if (compare(d, r + s) >= 0) return 0;\n        if (compare(d,\
    \ r - s) <= 0) return PI * s * s;\n        coordinate_t x = (d * d + r * r - s\
    \ * s) / (2 * d);\n        coordinate_t h = std::sqrt(std::max(r * r - x * x,\
    \ coordinate_t(0)));\n        coordinate_t a1 = r * r * std::acos(x / r);\n  \
    \      coordinate_t a2 = s * s * std::acos((d - x) / s);\n        coordinate_t\
    \ a12 = d * h;\n        return a1 + a2 - a12;\n    }\n}\n} // namespace suisen\n\
    \nnamespace std {\n    template <> struct tuple_size<suisen::geometry::Segment>\
    \ { static constexpr size_t value = 2; };\n    template <> struct tuple_element<0,\
    \ suisen::geometry::Segment> { using type = suisen::geometry::Point; };\n    template\
    \ <> struct tuple_element<1, suisen::geometry::Segment> { using type = suisen::geometry::Point;\
    \ };\n    template <> struct tuple_size<suisen::geometry::Ray> { static constexpr\
    \ size_t value = 2; };\n    template <> struct tuple_element<0, suisen::geometry::Ray>\
    \ { using type = suisen::geometry::Point; };\n    template <> struct tuple_element<1,\
    \ suisen::geometry::Ray> { using type = suisen::geometry::Point; };\n    template\
    \ <> struct tuple_size<suisen::geometry::Line> { static constexpr size_t value\
    \ = 2; };\n    template <> struct tuple_element<0, suisen::geometry::Line> { using\
    \ type = suisen::geometry::Point; };\n    template <> struct tuple_element<1,\
    \ suisen::geometry::Line> { using type = suisen::geometry::Point; };\n}\n\n\n\
    #line 9 \"test/src/geom/geometry/CGL_4_B.test.cpp\"\n\nusing namespace suisen::geometry;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    std::cout << std::fixed << std::setprecision(20);\n\n    int n;\n    std::cin\
    \ >> n;\n\n    Polygon poly(n);\n\n    for (int i = 0; i < n; ++i) {\n       \
    \ std::cin >> poly[i];\n    }\n\n    auto [i, j, diam] = convex_diameter(poly);\n\
    \    std::cout << diam << '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B\"\
    \n#define ERROR 0.000001\n\n#include <cassert>\n#include <iostream>\n#include\
    \ <iomanip>\n\n#include \"library/geom/geometry.hpp\"\n\nusing namespace suisen::geometry;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    std::cout << std::fixed << std::setprecision(20);\n\n    int n;\n    std::cin\
    \ >> n;\n\n    Polygon poly(n);\n\n    for (int i = 0; i < n; ++i) {\n       \
    \ std::cin >> poly[i];\n    }\n\n    auto [i, j, diam] = convex_diameter(poly);\n\
    \    std::cout << diam << '\\n';\n    return 0;\n}"
  dependsOn:
  - library/geom/geometry.hpp
  isVerificationFile: true
  path: test/src/geom/geometry/CGL_4_B.test.cpp
  requiredBy: []
  timestamp: '2023-09-06 20:35:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/geom/geometry/CGL_4_B.test.cpp
layout: document
redirect_from:
- /verify/test/src/geom/geometry/CGL_4_B.test.cpp
- /verify/test/src/geom/geometry/CGL_4_B.test.cpp.html
title: test/src/geom/geometry/CGL_4_B.test.cpp
---
