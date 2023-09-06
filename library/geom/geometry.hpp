#ifndef SUISEN_GEOMETRY
#define SUISEN_GEOMETRY

#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <optional>
#include <tuple>
#include <variant>
#include <vector>

namespace suisen {
namespace geometry {
    using coordinate_t = long double;
    using Point = std::complex<coordinate_t>;

    coordinate_t getx(const Point& p) { return p.real(); }
    coordinate_t gety(const Point& p) { return p.imag(); }

    // operator

    Point operator+(const Point &p, coordinate_t real) { return Point(p) + Point(real, 0); }
    Point operator-(const Point &p, coordinate_t real) { return Point(p) - Point(real, 0); }
    Point operator*(const Point &p, coordinate_t real) { return Point(p) * Point(real, 0); }
    Point operator/(const Point &p, coordinate_t real) { return Point(p) / Point(real, 0); }
    Point operator+(coordinate_t real, const Point &p) { return Point(real, 0) + Point(p); }
    Point operator-(coordinate_t real, const Point &p) { return Point(real, 0) - Point(p); }
    Point operator*(coordinate_t real, const Point &p) { return Point(real, 0) * Point(p); }
    Point operator/(coordinate_t real, const Point &p) { return Point(real, 0) / Point(p); }

    std::istream& operator>>(std::istream &in, Point &p) {
        coordinate_t x, y;
        in >> x >> y;
        p = Point(x, y);
        return in;
    }
    std::ostream& operator<<(std::ostream &out, const Point &p) {
        return out << getx(p) << ' ' << gety(p);
    }
}

namespace geometry {
    // relations between three points X, Y, Z.

    struct ISP {
        static constexpr int L_CURVE = +1; // +---------------+ Z is in 'a' => ISP = +1
        static constexpr int R_CURVE = -1; // |aaaaaaaaaaaaaaa| Z is in 'b' => ISP = -1
        static constexpr int FRONT   = +2; // |ddd X eee Y ccc| Z is in 'c' => ISP = +2
        static constexpr int BACK    = -2; // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2
        static constexpr int MIDDLE  =  0; // +---------------+ Z is in 'e' => ISP =  0
    };

    struct Sign {
        static constexpr int NEGATIVE = -1;
        static constexpr int ZERO = 0;
        static constexpr int POSITIVE = +1;
    };

    enum class Containment {
        OUT, ON, IN
    };

    constexpr Point ZERO = Point(0, 0);
    constexpr Point ONE  = Point(1, 0);
    constexpr Point I    = Point(0, 1);
    constexpr coordinate_t EPS = 1e-9;
    constexpr coordinate_t PI  = 3.14159265358979323846264338327950288419716939937510L;
    constexpr coordinate_t E   = 2.71828182845904523536028747135266249775724709369995L;

    constexpr auto XY_COMPARATOR = [](const Point &p, const Point &q) {
        return getx(p) == getx(q) ? gety(p) < gety(q) : getx(p) < getx(q);
    };
    constexpr auto XY_COMPARATOR_GREATER = [](const Point &p, const Point &q) {
        return getx(p) == getx(q) ? gety(p) > gety(q) : getx(p) > getx(q);
    };
    constexpr auto YX_COMPARATOR = [](const Point &p, const Point &q) {
        return gety(p) == gety(q) ? getx(p) < getx(q) : gety(p) < gety(q);
    };
    constexpr auto YX_COMPARATOR_GREATER = [](const Point &p, const Point &q) {
        return gety(p) == gety(q) ? getx(p) > getx(q) : gety(p) > gety(q);
    };

    int sgn(coordinate_t x) {
        return x > EPS ? Sign::POSITIVE : x < -EPS ? Sign::NEGATIVE : Sign::ZERO;
    }
    int compare(coordinate_t x, coordinate_t y) {
        return sgn(x - y);
    }

    auto cartesian(const coordinate_t real, const coordinate_t imag) {
        return Point(real, imag);
    }
    auto polar(const coordinate_t rho, const coordinate_t theta) {
        return Point(rho * std::cos(theta), rho * std::sin(theta));
    }
    auto cis(const coordinate_t theta) {
        return Point(std::cos(theta), std::sin(theta));
    }
    auto conj(const Point &z) {
        return Point(getx(z), -gety(z));
    }
    auto arg(const Point &z) {
        return std::atan2(gety(z), getx(z));
    }
    auto square_abs(const Point &z) {
        return getx(z) * getx(z) + gety(z) * gety(z);
    }
    auto abs(const Point &z) {
        return std::sqrt(square_abs(z));
    }
    auto rot(const Point &z, const coordinate_t theta) {
        return cis(theta) * z;
    }
    auto dot(const Point &a, const Point &b) {
        return getx(a) * getx(b) + gety(a) * gety(b);
    }
    auto det(const Point &a, const Point &b) {
        return getx(a) * gety(b) - gety(a) * getx(b);
    }
    bool equals(const Point &a, const Point &b) {
        return sgn(getx(a) - getx(b)) == Sign::ZERO and sgn(gety(a) - gety(b)) == Sign::ZERO;
    }
    bool equals(coordinate_t a, coordinate_t b) {
        return compare(a, b) == 0;
    }
    
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
    int isp(const Point &a, const Point &b, const Point &c) {
        Point ab = b - a, ac = c - a;
        int s = sgn(det(ab, ac));
        if (s == Sign::POSITIVE) return ISP::L_CURVE;
        if (s == Sign::NEGATIVE) return ISP::R_CURVE;
        if (sgn(dot(ab, ac)) == Sign::NEGATIVE) return ISP::BACK;
        Point ba = a - b, bc = c - b;
        if (sgn(dot(ba, bc)) == Sign::NEGATIVE) return ISP::FRONT;
        return ISP::MIDDLE;
    }

    struct Line {
        Point a, b;
        Line() : Line(ZERO, ZERO) {}
        Line(const Point &from, const Point &to) : a(from), b(to) {}
        // coef_x * x + coef_y * y + cnst = 0
        Line(coordinate_t coef_x, coordinate_t coef_y, coordinate_t cnst) {
            if (not equals(coef_x, 0.)) {
                a = { (coef_y - cnst) / coef_x, -1. };
                b = { (-coef_y - cnst) / coef_x, +1. };
            } else {
                a = { -1., (coef_x - cnst) / coef_y };
                b = { +1., (-coef_x - cnst) / coef_y };
            }
        }

        template <size_t I> const std::tuple_element_t<I, Line>& get() const {
            static_assert(I < std::tuple_size_v<Line>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
        template <size_t I> std::tuple_element_t<I, Line>& get() {
            static_assert(I < std::tuple_size_v<Line>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
    };
    struct Ray {
        Point a, b;
        Ray() : Ray(ZERO, ZERO) {}
        Ray(const Point &from, const Point &to) : a(from), b(to) {}

        template <size_t I> const std::tuple_element_t<I, Ray>& get() const {
            static_assert(I < std::tuple_size_v<Ray>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
        template <size_t I> std::tuple_element_t<I, Ray>& get() {
            static_assert(I < std::tuple_size_v<Ray>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
    };
    struct Segment {
        Point a, b;
        Segment() : Segment(ZERO, ZERO) {}
        Segment(const Point &from, const Point &to) : a(from), b(to) {}

        template <size_t I> const std::tuple_element_t<I, Segment>& get() const {
            static_assert(I < std::tuple_size_v<Segment>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
        template <size_t I> std::tuple_element_t<I, Segment>& get() {
            static_assert(I < std::tuple_size_v<Segment>);
            if constexpr (I == 0) return a;
            else if constexpr (I == 1) return b;
        }
    };
    struct Circle {
        Point center;
        coordinate_t radius;
        Circle() : Circle(ZERO, 0) {}
        Circle(const Point &c, const coordinate_t &r) : center(c), radius(r) {}
    };

    // Triangle
    
    coordinate_t signed_area(const Point &a, const Point &b, const Point &c) {
        return det(b - a, c - a) / 2;
    }
    coordinate_t area(const Point &a, const Point &b, const Point &c) {
        return std::abs(signed_area(a, b, c));
    }
    Point pG(const Point &a, const Point &b, const Point &c) {
        return (a + b + c) / 3;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B
    Circle pI(const Point &a, const Point &b, const Point &c) {
        coordinate_t la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
        coordinate_t l = la + lb + lc;
        la /= l, lb /= l, lc /= l;
        Point center = la * a + lb * b + lc * c;
        coordinate_t radius = 2 * area(a, b, c) / l;
        return Circle(center, radius);
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
    Circle pO(const Point &a, const Point &b, const Point &c) {
        Point ab = b - a, bc = c - b, ca = a - c;
        coordinate_t la = square_abs(bc), lb = square_abs(ca), lc = square_abs(ab);
        coordinate_t s = la * (lb + lc - la), t = lb * (lc + la - lb), u = lc * (la + lb - lc);
        coordinate_t l = s + t + u;
        s /= l, t /= l, u /= l;
        Point center = a * s + b * t + c * u;
        return Circle(center, abs(center - a));
    }
    Point pH(const Point &a, const Point &b, const Point &c) {
        return a + b + c - 2 * pO(a, b, c).center;
    }
    auto pIabc(const Point &a, const Point &b, const Point &c) {
        return std::make_tuple(pI(-a, b, c), pI(a, -b, c), pI(a, b, -c));
    }

    // Line

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
    template <typename line_t_1, typename line_t_2>
    auto is_parallel(const line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {
        return sgn(det(l1.b - l1.a, l2.b - l2.a)) == Sign::ZERO;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
    template <typename line_t_1, typename line_t_2>
    auto is_orthogonal(const line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())  {
        return sgn(dot(l1.b - l1.a, l2.b - l2.a)) == Sign::ZERO;
    }
    template <typename line_t_1, typename line_t_2>
    auto on_the_same_line(const line_t_1 &l1, const line_t_2 &l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool())  {
        return is_parallel(l1, l2) and sgn(det(l1.b - l1.a, l2.a - l1.a)) == Sign::ZERO;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
    template <typename line_t>
    Point projection(const Point &p, const line_t &line) {
        Point a = p - line.a;
        Point b = line.b - line.a;
        return line.a + dot(a, b) / square_abs(b) * b;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
    template <typename line_t>
    Point reflection(const Point &p, const line_t &line) {
        Point h = projection(p, line);
        return p + (h - p) * 2;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t square_distance(const Point &p, const Segment &l) {
        Point h = projection(p, l);
        if (isp(l.a, l.b, h) == ISP::MIDDLE) {
            return square_abs(h - p);
        } else {
            return std::min(square_abs(p - l.a), square_abs(p - l.b));
        }
    }
    coordinate_t square_distance(const Segment &l, const Point &p) {
        return square_distance(p, l);
    }
    coordinate_t square_distance(const Point &p, const Ray &l) {
        Point h = projection(p, l);
        int dir = isp(l.a, l.b, h);
        return dir == ISP::MIDDLE or dir == ISP::FRONT ? square_abs(h - p) : std::min(square_abs(p - l.a), square_abs(p - l.b));
    }
    coordinate_t square_distance(const Ray &l, const Point &p) {
        return square_distance(p, l);
    }
    coordinate_t square_distance(const Point &p, const Line &l) {
        return square_abs(projection(p, l) - p);
    }
    coordinate_t square_distance(const Line &l, const Point &p) {
        return square_distance(p, l);
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t distance(const Point &p, const Segment &l) {
        return std::sqrt(square_distance(p, l));
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t distance(const Segment &l, const Point &p) {
        return distance(p, l);
    }
    coordinate_t distance(const Point &p, const Ray &l) {
        return std::sqrt(square_distance(p, l));
    }
    coordinate_t distance(const Ray &l, const Point &p) {
        return distance(p, l);
    }
    coordinate_t distance(const Point &p, const Line &l) {
        return std::sqrt(square_distance(p, l));
    }
    coordinate_t distance(const Line &l, const Point &p) {
        return distance(p, l);
    }

    Containment contains(const Segment &l, const Point &p) {
        return sgn(distance(l, p)) == 0 ? Containment::ON : Containment::OUT;
    }
    Containment contains(const Ray &l, const Point &p) {
        return sgn(distance(l, p)) == 0 ? Containment::ON : Containment::OUT;
    }
    Containment contains(const Line &l, const Point &p) {
        return sgn(distance(l, p)) == 0 ? Containment::ON : Containment::OUT;
    }

    bool equals(const Line &l, const Line &m) {
        return on_the_same_line(l, m);
    }
    bool equals(const Ray &l, const Ray &m) {
        return on_the_same_line(l, m) and equals(l.a, m.a);
    }
    bool equals(const Segment &l, const Segment &m) {
        return (equals(l.a, m.a) and equals(l.b, m.b)) or (equals(l.a, m.b) and equals(l.b, m.a));
    }

    // "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"
    bool has_common_point(const Segment &l1, const Segment &l2) {
        int isp_1a = isp(l1.a, l1.b, l2.a), isp_1b = isp(l1.a, l1.b, l2.b);
        if (isp_1a * isp_1b > 0) return false;
        int isp_2a = isp(l2.a, l2.b, l1.a), isp_2b = isp(l2.a, l2.b, l1.b);
        if (isp_2a * isp_2b > 0) return false;
        return true;
    }

    namespace internal {
        template <typename line_t_1, typename line_t_2>
        Point cross_point(const line_t_1 &l1, const line_t_2 &l2) {
            assert(not is_parallel(l1, l2));
            Point u = l1.b - l1.a, v = l2.a - l2.b, c = l2.a - l1.a;
            return l2.a - det(u, c) / det(u, v) * v;
        }
    }

    // "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
    std::variant<std::nullptr_t, Point, Segment> common_point(const Segment &l1, const Segment &l2) {
        if (not has_common_point(l1, l2)) return nullptr;
        if (not is_parallel(l1, l2)) return internal::cross_point(l1, l2);
        std::vector<Point> ps { l1.a, l1.b, l2.a, l2.b };
        for (int i = 0; i <= 2; ++i) for (int j = 2; j >= i; --j) {
            if (XY_COMPARATOR(ps[j + 1], ps[j])) std::swap(ps[j], ps[j + 1]);
        }
        if (equals(ps[1], ps[2])) return ps[1];
        return Segment(ps[1], ps[2]);
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t square_distance(const Segment &l1, const Segment &l2) {
        if (has_common_point(l1, l2)) return 0;
        return std::min({ square_distance(l1, l2.a), square_distance(l1, l2.b), square_distance(l1.a, l2), square_distance(l1.b, l2) });
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t distance(const Segment &l1, const Segment &l2) {
        return std::sqrt(square_distance(l1, l2));
    }

    // Polygon

    using Polygon = std::vector<Point>;

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    coordinate_t signed_area(const Polygon &poly) {
        coordinate_t res = 0;
        int sz = poly.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1;
            if (j == sz) j = 0;
            res += signed_area(ZERO, poly[i], poly[j]);
        }
        return res;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    auto area(const Polygon &poly) {
        return std::abs(signed_area(poly));
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
    template <bool accept_180_degree = true>
    bool is_convex(const Polygon &poly) {
        int sz = poly.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1, k = i + 2;
            if (j >= sz) j -= sz;
            if (k >= sz) k -= sz;
            int dir = isp(poly[i], poly[j], poly[k]);
            if constexpr (accept_180_degree) {
                if (dir == ISP::R_CURVE) return false;
            } else {
                if (dir != ISP::L_CURVE) return false;
            }
        }
        return true;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
    Containment contains(const Polygon &poly, const Point &p) {
        bool in = false;
        int sz = poly.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1;
            if (j == sz) j -= sz;
            Point a = poly[i] - p, b = poly[j] - p;
            if (gety(a) > gety(b)) std::swap(a, b);
            if (sgn(gety(a)) <= 0 and sgn(gety(b)) > 0 and sgn(det(a, b)) < 0) in = not in;
            if (sgn(det(a, b)) == 0 and sgn(dot(a, b)) <= 0) return Containment::ON;
        }
        return in ? Containment::IN : Containment::OUT;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
    std::tuple<int, int, coordinate_t> convex_diameter(const Polygon& convex) {
        const int sz = convex.size();
        if (sz <= 2) return { 0, sz - 1, abs(convex.front() - convex.back()) };
        auto [si, sj] = [&]{
            auto [it_min, it_max] = std::minmax_element(convex.begin(), convex.end(), XY_COMPARATOR);
            return std::pair<int, int> { it_min - convex.begin(), it_max - convex.begin() };
        }();
        coordinate_t max_dist = -1;
        std::pair<int, int> argmax{ -1, -1 };
        for (int i = si, j = sj; i != sj or j != si;) {
            if (coordinate_t dij = square_abs(convex[j] - convex[i]); dij > max_dist) max_dist = dij, argmax = { i, j };
            int ni = (i + 1) % sz, nj = (j + 1) % sz;
            if (det(convex[ni] - convex[i], convex[nj] - convex[j]) < 0) i = ni;
            else j = nj;
        }
        return { argmax.first, argmax.second, ::sqrtl(max_dist) };
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
    auto convex_cut(const Polygon &convex, const Line &l) {
        Polygon res;
        int sz = convex.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1;
            if (j == sz) j -= sz;
            const Point &a = convex[i], &b = convex[j];
            int da = sgn(det(l.b - l.a, a - l.a));
            if (da >= 0) res.push_back(a);
            int db = sgn(det(l.b - l.a, b - l.a));
            if (da * db < 0) res.push_back(internal::cross_point(l, Segment(a, b)));
        }
        return res;
    }

    // Circle

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A
    int tangent_num(const Circle &c1, const Circle &c2) {
        coordinate_t r1 = c1.radius, r2 = c2.radius;
        if (r1 > r2) return tangent_num(c2, c1);
        coordinate_t d = abs(c1.center - c2.center);
        int cp = compare(d, r1 + r2);
        if (cp > 0) return 4;
        if (cp == 0) return 3;
        int cn = compare(d, r2 - r1);
        if (cn > 0) return 2;
        if (cn == 0) return 1;
        return 0;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
    std::vector<Point> common_point(const Circle &c, const Line &l) {
        Point h = projection(c.center, l);
        coordinate_t d = abs(c.center - h);
        int cp = compare(d, c.radius);
        if (cp > 0) return {};
        if (cp == 0) return { h };
        auto v = (l.a - l.b) * (std::sqrt(c.radius * c.radius - d * d) / abs(l.a - l.b));
        return { h - v, h + v };
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
    std::vector<Point> common_point(const Circle &c, const Segment &l) {
        auto ps = common_point(c, Line(l.a, l.b));
        ps.erase(std::remove_if(ps.begin(), ps.end(), [&](const auto &p) { return contains(l, p) != Containment::ON; }), ps.end());
        return ps;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
    std::vector<Point> common_point(const Circle &c1, const Circle &c2) {
        coordinate_t r1 = c1.radius, r2 = c2.radius;
        if (r1 > r2) return common_point(c2, c1);
        coordinate_t d = abs(c1.center - c2.center);
        int cp = compare(d, r1 + r2), cn = compare(d, r2 - r1);
        if (cp > 0 or cn < 0) return {};
        auto v = c1.center - c2.center;
        coordinate_t lv = abs(v);
        if (cp == 0 or cn == 0) {
            return { c2.center + v * (r2 / lv) };
        }
        coordinate_t lp = d, ln = (r2 * r2 - r1 * r1) / d;
        coordinate_t p = (lp + ln) / 2, x = sqrt(r2 * r2 - p * p);
        auto h = c2.center + v * (p / lv);
        auto t = v * I;
        return { h + t * (x / lv), h - t * (x / lv) };
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F
    Containment contains(const Circle &c, const Point &p) {
        coordinate_t d = abs(c.center - p);
        int cp = compare(d, c.radius);
        if (cp > 0) return Containment::OUT;
        if (cp < 0) return Containment::IN;
        return Containment::ON;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F
    std::vector<Point> tangent_to_circle(const Circle &c, const Point &p) {
        Containment cnt = contains(c, p);
        if (cnt == Containment::IN) return {};
        if (cnt == Containment::ON) return { p };
        Point v = c.center - p;
        coordinate_t r = c.radius, d = abs(v), l = sqrt(d * d - r * r);
        coordinate_t t = std::asin(r / d);
        return { p + rot(v, t) * (l / d), p + rot(v, -t) * (l / d) };
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G
    // returns { Line(p, q) | p is on c1, q is on c2, Line(p, q) is common tangent of c1 and c2 }
    std::vector<Line> common_tangent(const Circle &c1, const Circle &c2) {
        int num = tangent_num(c1, c2);
        std::vector<Line> res;
        if (num == 0) return res;
        Point a = c1.center, b = c2.center, v = b - a;
        coordinate_t r1 = c1.radius, r2 = c2.radius;
        coordinate_t rp = r1 + r2, rm = r1 - r2, rd = r2 / r1;
        coordinate_t sqxy = square_abs(v);
        coordinate_t rtp = std::sqrt(std::max(sqxy - rp * rp, coordinate_t(0)));
        coordinate_t rtm = std::sqrt(std::max(sqxy - rm * rm, coordinate_t(0)));
        Point r = v * r1, u = r * Point(0, 1);
        Point l12 = r * rp, r12 = u * rtp, l34 = r * rm, r34 = u * rtm;
        Point p14 = (l34 + r34) / sqxy;
        res.emplace_back(a + p14, b + p14 * rd);
        if (num == 1) return res;
        Point p13 = (l34 - r34) / sqxy;
        res.emplace_back(a + p13, b + p13 * rd);
        if (num == 2) return res;
        Point p12 = (l12 + r12) / sqxy;
        res.emplace_back(a + p12, b - p12 * rd);
        if (num == 3) return res;
        Point p11 = (l12 - r12) / sqxy;
        res.emplace_back(a + p11, b - p11 * rd);
        return res;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
    coordinate_t intersection_area(const Polygon &poly, const Circle &circle) {
        int sz = poly.size();
        coordinate_t r2 = circle.radius * circle.radius;
        const Point &c = circle.center;
        coordinate_t area = 0;
        for (int i = 0; i < sz; i++) {
            int j = i + 1;
            if (j >= sz) j -= sz;
            Point a = poly[i], b = poly[j];
            bool in_a = contains(circle, a) == Containment::IN, in_b = contains(circle, b) == Containment::IN;
            Point ca = a - c, cb = b - c;
            if (in_a and in_b) {
                area += det(ca, cb);
                continue;
            }
            std::vector<Point> ps = common_point(circle, Segment(a, b));
            if (ps.empty()) {
                area += r2 * arg(cb / ca);
            } else {
                Point s = ps[0];
                Point t = ps.size() == 1 ? s : ps[1];
                if (compare(square_abs(t - a), square_abs(s - a)) < 0) std::swap(s, t);
                Point cs = s - c, ct = t - c;
                area += det(cs, ct);
                area += in_a ? det(ca, cs) : r2 * arg(cs / ca);
                area += in_b ? det(ct, cb) : r2 * arg(cb / ct);
            }
        }
        return area / 2;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I
    coordinate_t intersection_area(const Circle &c1, const Circle &c2) {
        coordinate_t r = c1.radius, s = c2.radius;
        if (r < s) return intersection_area(c2, c1);
        Point a = c1.center, b = c2.center;
        coordinate_t d = abs(a - b);
        if (compare(d, r + s) >= 0) return 0;
        if (compare(d, r - s) <= 0) return PI * s * s;
        coordinate_t x = (d * d + r * r - s * s) / (2 * d);
        coordinate_t h = std::sqrt(std::max(r * r - x * x, coordinate_t(0)));
        coordinate_t a1 = r * r * std::acos(x / r);
        coordinate_t a2 = s * s * std::acos((d - x) / s);
        coordinate_t a12 = d * h;
        return a1 + a2 - a12;
    }
}
} // namespace suisen

namespace std {
    template <> struct tuple_size<suisen::geometry::Segment> { static constexpr size_t value = 2; };
    template <> struct tuple_element<0, suisen::geometry::Segment> { using type = suisen::geometry::Point; };
    template <> struct tuple_element<1, suisen::geometry::Segment> { using type = suisen::geometry::Point; };
    template <> struct tuple_size<suisen::geometry::Ray> { static constexpr size_t value = 2; };
    template <> struct tuple_element<0, suisen::geometry::Ray> { using type = suisen::geometry::Point; };
    template <> struct tuple_element<1, suisen::geometry::Ray> { using type = suisen::geometry::Point; };
    template <> struct tuple_size<suisen::geometry::Line> { static constexpr size_t value = 2; };
    template <> struct tuple_element<0, suisen::geometry::Line> { using type = suisen::geometry::Point; };
    template <> struct tuple_element<1, suisen::geometry::Line> { using type = suisen::geometry::Point; };
}

#endif // SUISEN_GEOMETRY
