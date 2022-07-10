#ifndef SUISEN_GEOMETRY
#define SUISEN_GEOMETRY

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "library/integral_geom/point.hpp"

namespace suisen::integral_geometry {
    // relations between three points X, Y, Z.
    struct ISP {
        static constexpr int L_CURVE = +1; // +---------------+ Z is in 'a' => ISP = +1
        static constexpr int R_CURVE = -1; // |aaaaaaaaaaaaaaa| Z is in 'b' => ISP = -1
        static constexpr int FRONT = +2;   // |ddd X eee Y ccc| Z is in 'c' => ISP = +2
        static constexpr int BACK = -2;    // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2
        static constexpr int MIDDLE = 0;   // +---------------+ Z is in 'e' => ISP =  0
    };

    enum class Containment { OUT, ON, IN };

    int sgn(coordinate_t x) { return x < 0 ? -1 : x > 0 ? +1 : 0; }
    int compare(coordinate_t x, coordinate_t y) { return sgn(x - y); }

    Point cartesian(const coordinate_t real, const coordinate_t imag) { return Point(real, imag); }
    Point conj(const Point& z) { return Point(z.x, -z.y); }
    double arg(const Point& z) { return std::atan2(z.y, z.x); }
    multiplied_t square_abs(const Point& z) { return multiplied_t(z.x) * z.x + multiplied_t(z.y) * z.y; }
    double abs(const Point& z) { return std::sqrt(square_abs(z)); }

    multiplied_t dot(const Point& a, const Point& b) { return multiplied_t(a.x) * b.x + multiplied_t(a.y) * b.y; }
    multiplied_t det(const Point& a, const Point& b) { return multiplied_t(a.x) * b.y - multiplied_t(a.y) * b.x; }

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
    int isp(const Point& a, const Point& b, const Point& c) {
        Point ab = b - a, ac = c - a;
        coordinate_t det_ab_ac = det(ab, ac);
        if (det_ab_ac > 0) return ISP::L_CURVE;
        if (det_ab_ac < 0) return ISP::R_CURVE;
        if (dot(ab, ac) < 0) return ISP::BACK;
        if (dot(a - b, c - b) < 0) return ISP::FRONT;
        return ISP::MIDDLE;
    }

    struct Line {
        Point a, b;
        Line() = default;
        Line(const Point& from, const Point& to) : a(from), b(to) {}
    };
    struct Ray {
        Point a, b;
        Ray() = default;
        Ray(const Point& from, const Point& to) : a(from), b(to) {}
    };
    struct Segment {
        Point a, b;
        Segment() = default;
        Segment(const Point& from, const Point& to) : a(from), b(to) {}
    };
    struct Circle {
        Point center;
        coordinate_t radius;
        Circle() = default;
        Circle(const Point& c, const coordinate_t& r) : center(c), radius(r) {}
    };

    // Triangle

    coordinate_t signed_area_doubled(const Point& a, const Point& b, const Point& c) {
        return det(b - a, c - a);
    }
    coordinate_t area_doubled(const Point& a, const Point& b, const Point& c) {
        return std::abs(signed_area_doubled(a, b, c));
    }

    // Line

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
    template <typename line_t_1, typename line_t_2>
    auto is_parallel(const line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {
        return det(l1.b - l1.a, l2.b - l2.a) == 0;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
    template <typename line_t_1, typename line_t_2>
    auto is_orthogonal(const line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {
        return dot(l1.b - l1.a, l2.b - l2.a) == 0;
    }
    template <typename line_t_1, typename line_t_2>
    auto on_the_same_line(const line_t_1& l1, const line_t_2& l2) -> decltype(l1.a, l1.b, l2.a, l2.b, bool()) {
        return is_parallel(l1, l2) and det(l1.b - l1.a, l2.a - l1.a) == 0;
    }

    Containment contains(const Line& l, const Point& p) {
        if (l.a.x == l.b.x) return p.x == l.a.x ? Containment::ON : Containment::OUT;
        coordinate_t a = p.x - l.a.x, b = p.y - l.a.y, c = l.b.x - p.x, d = l.b.y - p.y;
        return b * c == a * d ? Containment::ON : Containment::OUT;
    }
    Containment contains(const Ray& l, const Point& p) {
        if (contains(Line { l.a, l.b }, p) == Containment::OUT) return Containment::OUT;
        if (l.a.x == l.b.x) {
            if (l.a.y < l.b.y) return p.y >= l.a.y ? Containment::ON : Containment::OUT;
            else return p.y <= l.a.y ? Containment::ON : Containment::OUT;
        } else if (l.a.x < l.b.x) {
            return p.x >= l.a.x ? Containment::ON : Containment::OUT;
        } else {
            return p.x <= l.a.x ? Containment::ON : Containment::OUT;
        }
    }
    Containment contains(const Segment& l, const Point& p) {
        if (contains(Line { l.a, l.b }, p) == Containment::OUT) return Containment::OUT;
        if (l.a.x == l.b.x) {
            if (l.a.y < l.b.y) return p.y >= l.a.y and p.y <= l.b.y ? Containment::ON : Containment::OUT;
            else return p.y >= l.b.y and p.y <= l.a.y ? Containment::ON : Containment::OUT;
        } else if (l.a.x < l.b.x) {
            return p.x >= l.a.x and p.x <= l.b.x ? Containment::ON : Containment::OUT;
        } else {
            return p.x >= l.b.x and p.x <= l.a.x ? Containment::ON : Containment::OUT;
        }
    }

    bool operator==(const Line& l, const Line& m) {
        return on_the_same_line(l, m);
    }
    bool operator==(const Ray& l, const Ray& m) {
        return on_the_same_line(l, m) and l.a == m.a;
    }
    bool operator==(const Segment& l, const Segment& m) {
        return (l.a == m.a and l.b == m.b) or (l.a == m.b and l.b == m.a);
    }

    // "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"
    bool has_common_point(const Segment& l1, const Segment& l2) {
        int isp_1a = isp(l1.a, l1.b, l2.a), isp_1b = isp(l1.a, l1.b, l2.b);
        if (isp_1a * isp_1b > 0) return false;
        int isp_2a = isp(l2.a, l2.b, l1.a), isp_2b = isp(l2.a, l2.b, l1.b);
        if (isp_2a * isp_2b > 0) return false;
        return true;
    }

    // Polygon

    using Polygon = std::vector<Point>;

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    coordinate_t signed_area_doubled(const Polygon& poly) {
        coordinate_t res = 0;
        int sz = poly.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1;
            if (j == sz) j = 0;
            res += signed_area_doubled(ZERO, poly[i], poly[j]);
        }
        return res;
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
    coordinate_t area_doubled(const Polygon& poly) {
        return std::abs(signed_area_doubled(poly));
    }
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
    template <bool accept_180_degree = true>
    bool is_convex(const Polygon& poly) {
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
    Containment contains(const Polygon& poly, const Point& p) {
        bool in = false;
        int sz = poly.size();
        for (int i = 0; i < sz; ++i) {
            int j = i + 1;
            if (j == sz) j -= sz;
            Point a = poly[i] - p, b = poly[j] - p;
            if (a.y > b.y) std::swap(a, b);
            if (a.y <= 0 and b.y > 0 and det(a, b) < 0) in = not in;
            if (det(a, b) == 0 and dot(a, b) <= 0) return Containment::ON;
        }
        return in ? Containment::IN : Containment::OUT;
    }

    std::pair<int, int> convex_diameter(const Polygon& convex) {
        const int sz = convex.size();
        if (sz <= 2) return { 0, sz - 1 };
        auto [si, sj] = [&]{
            auto [it_min, it_max] = std::minmax_element(convex.begin(), convex.end(), XY_COMPARATOR);
            return std::pair<int, int> { it_min - convex.begin(), it_max - convex.begin() };
        }();
        coordinate_t max_dist = -1;
        std::pair<int, int> argmax{ -1, -1 };
        for (int i = si, j = sj; i != sj or j != si;) {
            if (multiplied_t dij = square_abs(convex[j] - convex[i]); dij > max_dist) max_dist = dij, argmax = { i, j };
            int ni = (i + 1) % sz, nj = (j + 1) % sz;
            if (det(convex[ni] - convex[i], convex[nj] - convex[j]) < 0) i = ni;
            else j = nj;
        }
        return argmax;
    }

    // Circle

    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A
    int tangent_num(const Circle& c1, const Circle& c2) {
        coordinate_t r1 = c1.radius, r2 = c2.radius;
        if (r1 > r2) return tangent_num(c2, c1);
        coordinate_t d2 = square_abs(c1.center - c2.center);
        coordinate_t dp = d2 - (r1 + r2) * (r1 + r2);
        if (dp > 0) return 4;
        if (dp == 0) return 3;
        coordinate_t dn = d2 - (r2 - r1) * (r2 - r1);
        if (dn > 0) return 2;
        if (dn == 0) return 1;
        return 0;
    }
    bool has_common_point(const Circle& c1, const Circle& c2) {
        int tnum = tangent_num(c1, c2);
        return 1 <= tnum and tnum <= 3;
    }
    bool has_cross_point(const Circle& c1, const Circle& c2) {
        return tangent_num(c1, c2) == 2;
    }

    Containment contains(const Circle& c, const Point& p) {
        coordinate_t df = square_abs(c.center - p) - c.radius * c.radius;
        if (df > 0) return Containment::OUT;
        if (df < 0) return Containment::IN;
        return Containment::ON;
    }
} // namespace suisen::integral_geometry

#endif // SUISEN_GEOMETRY
