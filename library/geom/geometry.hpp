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

    // operator

    Point& operator+=(Point &p, coordinate_t real) { return p += Point(real, 0); }
    Point& operator-=(Point &p, coordinate_t real) { return p -= Point(real, 0); }
    Point& operator*=(Point &p, coordinate_t real) { return p *= Point(real, 0); }
    Point& operator/=(Point &p, coordinate_t real) { return p /= Point(real, 0); }
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
        return out << p.real() << ' ' << p.imag();
    }

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
    constexpr coordinate_t PI  = M_PI;
    constexpr coordinate_t E   = M_E;

    constexpr auto XY_COMPARATOR = [](const Point &p, const Point &q) {
        return p.real() == q.real() ? p.imag() < q.imag() : p.real() < q.real();
    };
    constexpr auto XY_COMPARATOR_GREATER = [](const Point &p, const Point &q) {
        return p.real() == q.real() ? p.imag() > q.imag() : p.real() > q.real();
    };
    constexpr auto YX_COMPARATOR = [](const Point &p, const Point &q) {
        return p.imag() == q.imag() ? p.real() < q.real() : p.imag() < q.imag();
    };
    constexpr auto YX_COMPARATOR_GREATER = [](const Point &p, const Point &q) {
        return p.imag() == q.imag() ? p.real() > q.real() : p.imag() > q.imag();
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
        return Point(z.real(), -z.imag());
    }
    auto arg(const Point &z) {
        return std::atan2(z.imag(), z.real());
    }
    auto square_abs(const Point &z) {
        return z.real() * z.real() + z.imag() * z.imag();
    }
    auto abs(const Point &z) {
        return std::sqrt(square_abs(z));
    }
    auto rot(const Point &z, const coordinate_t theta) {
        return cis(theta) * z;
    }
    auto dot(const Point &a, const Point &b) {
        return a.real() * b.real() + a.imag() * b.imag();
    }
    auto det(const Point &a, const Point &b) {
        return a.real() * b.imag() - a.imag() * b.real();
    }
    bool equals(const Point &a, const Point &b) {
        return sgn(a.real() - b.real()) == Sign::ZERO and sgn(a.imag() - b.imag()) == Sign::ZERO;
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
    };
    struct Ray {
        Point a, b;
        Ray() : Ray(ZERO, ZERO) {}
        Ray(const Point &from, const Point &to) : a(from), b(to) {}
    };
    struct Segment {
        Point a, b;
        Segment() : Segment(ZERO, ZERO) {}
        Segment(const Point &from, const Point &to) : a(from), b(to) {}
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
        auto la = std::abs(b - c), lb = std::abs(c - a), lc = std::abs(a - b);
        auto l = la + lb + lc;
        la /= l, lb /= l, lc /= l;
        Point center = la * a + lb * b + lc * c;
        auto radius = 2. * area(a, b, c) / l;
        return Circle(center, radius);
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
    Circle pO(const Point &a, const Point &b, const Point &c) {
        Point ab = b - a, bc = c - b, ca = a - c;
        auto la = square_abs(bc), lb = square_abs(ca), lc = square_abs(ab);
        auto s = la * (lb + lc - la), t = lb * (lc + la - lb), u = lc * (la + lb - lc);
        auto l = s + t + u;
        s /= l, t /= l, u /= l;
        Point center = a * s + b * t + c * u;
        return Circle(center, std::abs(center - a));
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
    coordinate_t dist(const Point &p, const Segment &l) {
        Point h = projection(p, l);
        if (isp(l.a, l.b, h) == ISP::MIDDLE) {
            return abs(h - p);
        } else {
            return std::sqrt(std::min(square_abs(p - l.a), square_abs(p - l.b)));
        }
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t dist(const Segment &l, const Point &p) {
        return dist(p, l);
    }
    coordinate_t dist(const Point &p, const Ray &l) {
        Point h = projection(p, l);
        int dir = isp(l.a, l.b, h);
        return dir == ISP::MIDDLE or dir == ISP::FRONT ? abs(h - p) : std::sqrt(std::min(square_abs(p - l.a), square_abs(p - l.b)));
    }
    coordinate_t dist(const Ray &l, const Point &p) {
        return dist(p, l);
    }
    coordinate_t dist(const Point &p, const Line &l) {
        return abs(projection(p, l) - p);
    }
    coordinate_t dist(const Line &l, const Point &p) {
        return dist(p, l);
    }

    Containment contains(const Segment &l, const Point &p) {
        return sgn(dist(l, p)) == 0 ? Containment::ON : Containment::OUT;
    }
    Containment contains(const Ray &l, const Point &p) {
        return sgn(dist(l, p)) == 0 ? Containment::ON : Containment::OUT;
    }
    Containment contains(const Line &l, const Point &p) {
        return sgn(dist(l, p)) == 0 ? Containment::ON : Containment::OUT;
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
            Point ha = projection(l2.a, l1), hb = projection(l2.b, l1);
            auto la = abs(l2.a - ha);
            if (sgn(la) == 0) return ha;
            auto lb = abs(l2.b - hb);
            if (sgn(lb) == 0) return hb;
            return l2.a + (l2.b - l2.a) * (la / (la + lb));
        }
    }

    // "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
    std::variant<std::nullptr_t, Point, Segment> common_point(const Segment &l1, const Segment &l2) {
        if (not has_common_point(l1, l2)) return nullptr;
        if (not is_parallel(l1, l2)) return internal::cross_point(l1, l2);
        std::vector<Point> ps { l1.a, l1.b, l2.a, l2.b };
        auto comp = [](const Point &p, const Point &q) { return p.real() == q.real() ? p.imag() < q.imag() : p.real() < q.real(); };
        for (int i = 0; i <= 2; ++i) for (int j = 2; j >= i; --j) {
            if (comp(ps[j], ps[j + 1])) std::swap(ps[j], ps[j + 1]);
        }
        if (ps[1] == ps[2]) return ps[1];
        return Segment(ps[1], ps[2]);
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
    coordinate_t dist(const Segment &l1, const Segment &l2) {
        if (has_common_point(l1, l2)) return 0;
        return std::min({ dist(l1, l2.a), dist(l1, l2.b), dist(l1.a, l2), dist(l1.b, l2) });
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
            if (a.imag() > b.imag()) std::swap(a, b);
            if (sgn(a.imag()) <= 0 and sgn(b.imag()) > 0 and sgn(det(a, b)) < 0) in = not in;
            if (sgn(det(a, b)) == 0 and sgn(dot(a, b)) <= 0) return Containment::ON;
        }
        return in ? Containment::IN : Containment::OUT;
    }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
    auto convex_diameter(const Polygon &convex) {
        const int sz = convex.size();
        auto d2 = [&](int i, int j) { return square_abs(convex[j % sz] - convex[i]); };
        coordinate_t max_dist = -1;
        std::pair<int, int> argmax { -1, -1 };
        for (int i = 0, j = 0; i < sz; ++i) {
            while (d2(i, j + 1) >= d2(i, j)) ++j;
            coordinate_t cur_dist = d2(i, j);
            if (cur_dist > max_dist) {
                max_dist = cur_dist;
                argmax = { i, j };
            }
        }
        auto [i, j] = argmax;
        return std::make_tuple(i, j % sz, std::sqrt(max_dist));
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
        auto v = c.center - p;
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
        Point p11 = (l12 - r12) / sqxy, p12 = (l12 + r12) / sqxy, p13 = (l34 - r34) / sqxy, p14 = (l34 + r34) / sqxy;
        Point p21 = p11 * rd, p22 = p12 * rd, p23 = p13 * rd, p24 = p14 * rd;
        res.emplace_back(a + p14, b + p24);
        if (num == 1) return res;
        res.emplace_back(a + p13, b + p23);
        if (num == 2) return res;
        res.emplace_back(a + p12, b - p22);
        if (num == 3) return res;
        res.emplace_back(a + p11, b - p21);
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

#endif // SUISEN_GEOMETRY
