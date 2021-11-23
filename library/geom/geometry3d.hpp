#ifndef SUISEN_GEOMETRY_3D
#define SUISEN_GEOMETRY_3D

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <optional>

namespace suisen::geometry3d {
    namespace math {
        template <typename T>
        T sqrt(const T &x) { return ::sqrtl(x); }
#ifdef __HAVE_FLOAT128
        template <>
        __float128 sqrt<__float128>(const __float128 &x) { return ::sqrtf128(x); }
#endif
        template <>
        long double sqrt<long double>(const long double &x) { return ::sqrtl(x); }
        template <>
        double sqrt<double>(const double &x) { return ::sqrt(x); }
        template <>
        float sqrt<float>(const float &x) { return ::sqrtf(x); }
    }

    using coordinate_t = long double;
    using Point = std::array<coordinate_t, 3>;
    
    constexpr coordinate_t EPS = 1e-9;

    std::istream& operator>>(std::istream &in, Point &p) {
        return in >> p[0] >> p[1] >> p[2];
    }
    std::ostream& operator<<(std::ostream &out, const Point &p) {
        return out << p[0] << ' ' << p[1] << ' ' << p[2];
    }

    int signum(const coordinate_t &x) { return x < -EPS ? -1 : x > EPS ? +1 : 0; }
    int compare(const coordinate_t &x, const coordinate_t &y) { return signum(x - y); }
    bool equals(const coordinate_t &x, const coordinate_t &y) { return compare(x, y) == 0; }

    coordinate_t inner_product(const Point &p, const Point &q) {
        return p[0] * q[0] + p[1] * q[1] + p[2] * q[2];
    }
    Point outer_product(const Point &p, const Point &q) {
        return Point { p[1] * q[2] - p[2] * q[1], p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0] };
    }

    Point& operator+=(Point &p, const Point &q) { return p[0] += q[0], p[1] += q[1], p[2] += q[2], p; }
    Point& operator-=(Point &p, const Point &q) { return p[0] -= q[0], p[1] -= q[1], p[2] -= q[2], p; }
    Point& operator*=(Point &p, const Point &q) { return p = outer_product(p, q); }
    Point& operator*=(Point &p, const coordinate_t &c) { return p[0] *= c, p[1] *= c, p[2] *= c, p; }
    Point& operator/=(Point &p, const coordinate_t &c) { return p *= coordinate_t(1) / c; }

    Point operator+(const Point &p, const Point &q) { auto r = p; return r += q; }
    Point operator-(const Point &p, const Point &q) { auto r = p; return r -= q; }
    Point operator*(const Point &p, const Point &q) { auto r = p; return r *= q; }
    Point operator*(const Point &p, const coordinate_t &c) { auto r = p; return r *= c; }
    Point operator*(const coordinate_t &c, const Point &p) { auto r = p; return r *= c; }
    Point operator/(const Point &p, const coordinate_t &c) { auto r = p; return r /= c; }

    Point operator+(const Point &p) { return Point { +p[0], +p[1], +p[2] }; }
    Point operator-(const Point &p) { return Point { -p[0], -p[1], -p[2] }; }

    coordinate_t square_abs(const Point &p) { return inner_product(p, p); }
    coordinate_t abs(const Point &p) { return math::sqrt(square_abs(p)); }
    coordinate_t dist(const Point &p, const Point &q) { return abs(p - q); }
    Point& normalize(Point &p) { return p /= abs(p); }
    Point normalized(const Point &p) { auto q = p; return normalize(q); }

    bool equals(const Point &p, const Point &q) {
        auto [x, y, z] = p - q;
        return signum(x) == 0 and signum(y) == 0 and signum(z) == 0;
    }

    bool is_parallel(const Point &a, const Point &b) {
        return equals(outer_product(a, b), { 0, 0, 0 });
    }
    bool is_orthogonal(const Point &a, const Point &b) {
        return equals(inner_product(a, b), 0);
    }

    struct Line    : public std::pair<Point, Point> { using std::pair<Point, Point>::pair; };
    struct Ray     : public Line { using Line::Line; };
    struct Segment : public Line { using Line::Line; };

    Point projection(const Line &l, const Point &p) {
        Point a = l.first - p, b = l.second - p;
        auto ab = b - a;
        Point h = p + (inner_product(b, ab) * a - inner_product(a, ab) * b) / square_abs(ab);
        // assert(is_parallel(h - l.first, l.second - l.first));
        // assert(is_orthogonal(h - p, l.second - l.first));
        return h;
    }
    coordinate_t dist(const Line &l, const Point &p) {
        return dist(projection(l, p), p);
    }
    coordinate_t dist(const Ray &l, const Point &p) {
        const auto &[a, b] = l;
        Point h = projection(l, p);
        return signum(inner_product(h - a, b - a)) < 0 ? abs(a - p) : abs(h - p);
    }
    coordinate_t dist(const Segment &l, const Point &p) {
        const auto &[a, b] = l;
        Point h = projection(l, p);
        if (signum(inner_product(h - a, b - a)) < 0) {
            return dist(a, p);
        } else if (signum(inner_product(h - b, a - b)) < 0) {
            return dist(b, p);
        } else {
            return dist(h, p);
        }
    }
    bool on(const Line    &l, const Point &p) { return dist(l, p) < EPS; }
    bool on(const Ray     &l, const Point &p) { return dist(l, p) < EPS; }
    bool on(const Segment &l, const Point &p) { return dist(l, p) < EPS; }

    namespace internal {
        std::pair<Point, Point> closest_pair(const Line &l, const Line &m) {
            auto [la, lb] = l;
            auto [ma, mb] = m;
            Point ld = normalized(lb - la), md = normalized(mb - ma);
            // P(x) = la + ld * x, Q(y) = ma + md * y. min |P(x) - Q(y)| is the distance of the lines l, m.
            auto d = ma - la;
            coordinate_t p = inner_product(d, ld), q = inner_product(d, md), c = inner_product(ld, md);
            // x - cy = p
            // cx - y = q
            coordinate_t x, y;
            if (equals(std::abs(c), 1)) { // parallel <=> ld // md
                x = p, y = 0;
            } else {
                coordinate_t den = 1 - c * c;
                x = (p - c * q) / den, y = (c * p - q) / den;
            }
            return { la + ld * x, ma + md * y };
        }
    }
    coordinate_t dist(const Line &l, const Line &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return dist(p, q);
    }
    coordinate_t dist(const Line &l, const Ray &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return on(m, q) ? dist(p, q) : dist(l, m.first);
    }
    coordinate_t dist(const Ray &l, const Line &m) {
        return dist(m, l);
    }
    coordinate_t dist(const Line &l, const Segment &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(l, m.second));
    }
    coordinate_t dist(const Segment &l, Line &m) {
        return dist(m, l);
    }
    coordinate_t dist(const Ray &l, const Ray &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return on(l, p) and on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(m, l.first));
    }
    coordinate_t dist(const Ray &l, const Segment &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return on(l, p) and on(m, q) ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second), dist(m, l.first) });
    }
    coordinate_t dist(const Segment &l, const Ray &m) {
        return dist(m, l);
    }
    coordinate_t dist(const Segment &l, const Segment &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return on(l, p) and on(m, q) ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second), dist(m, l.first), dist(m, l.second) });
    }

    bool is_parallel(const Line &l, const Line &m) {
        return is_parallel(l.second - l.first, m.second - m.first);
    }
    bool is_orthogonal(const Line &l, const Line &m) {
        return is_orthogonal(l.second - l.first, m.second - m.first);
    }

    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line, line_t>, std::nullptr_t> = nullptr>
    std::optional<Point> cross_point(const line_t &l, const line_t &m) {
        auto [p, q] = internal::closest_pair(l, m);
        return equals(p, q) and on(l, p) and on(m, q) ? std::make_optional(p) : std::nullopt;
    }

    // Plane: ax + by + cz + d = 0
    struct Plane {
        Point normal_vec; // = [a, b, c]
        coordinate_t d;
        Plane() {}
        Plane(const Point &p, const Point &q, const Point &r) : normal_vec(normalized((q - p) * (r - p))), d(-inner_product(normal_vec, p)) {}
        Plane(const coordinate_t &a, coordinate_t &b, coordinate_t &c, coordinate_t &d) : normal_vec(normalized({a, b, c})), d(d / abs({a, b, c})) {}
    };

    coordinate_t dist(const Plane &plane, const Point &p) {
        return std::abs(inner_product(plane.normal_vec, p) + plane.d);
    }
    bool on(const Plane &plane, const Point &p) {
        return dist(plane, p) < EPS;
    }
    Point projection(const Plane &plane, const Point &p) {
        coordinate_t d = dist(plane, p);
        Point q = p + d * plane.normal_vec;
        return on(plane, q) ? q : p - d * plane.normal_vec;
    }

    bool is_parallel(const Plane &plane, const Line &l) {
        return is_orthogonal(plane.normal_vec, l.second - l.first);
    }
    bool is_orthogonal(const Plane &plane, const Line &l) {
        return is_parallel(plane.normal_vec, l.second - l.first);
    }
    coordinate_t dist(const Plane &plane, const Line &l) {
        return is_parallel(plane, l) ? dist(plane, l.first) : 0;
    }
    coordinate_t dist(const Plane &plane, const Ray &l) {
        Point h = projection(plane, l.first);
        coordinate_t ip = inner_product(l.first - h, l.second - l.first);
        return signum(ip) < 0 ? 0 : dist(h, l.first);
    }
    coordinate_t dist(const Plane &plane, const Segment &l) {
        Point ha = projection(plane, l.first), hb = projection(plane, l.second);
        coordinate_t ipa = inner_product(l.first - ha, l.second - l.first), ipb = inner_product(l.second - hb, l.first - l.second);
        return signum(ipa) < 0 and signum(ipb) < 0 ? 0 : std::min(dist(plane, l.first), dist(plane, l.second));
    }

    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line, line_t>, std::nullptr_t> = nullptr>
    std::optional<Point> cross_point(const Plane &plane, const line_t &l) {
        if (on(plane, l.first)) return std::make_optional(l.first);
        if (is_parallel(plane, l)) return std::nullopt;
        Point ha = projection(plane, l.first);
        Point hb = projection(plane, l.second);
        coordinate_t la = dist(ha, l.first), lb = dist(hb, l.second);
        Point p = hb + (ha - hb) * (lb / (lb + la));
        Line m { l.first, l.second };
        Point res = on(m, p) ? p : hb + (ha - hb) * (lb / (lb - la));
        // assert(on(plane, res) and on(m, res));
        return on(l, res) ? std::make_optional(res) : std::nullopt;
    }

    bool on_triangle(const std::array<Point, 3> &t, const Point &p) {
        if (not on(Plane{ t[0], t[1], t[2] }, p)) return false;
        bool first = true;
        Point normal;
        for (int i = 0; i < 3; ++i) {
            Point w = (t[(i + 1) % 3] - t[i]) * (p - t[i]);
            if (equals(w, Point{0, 0, 0})) continue;
            normalize(w);
            if (first) {
                normal = w;
                first = false;
            } else if (not equals(normal, w)) {
                return false;
            }
        }
        return true;
    }
}

#endif // SUISEN_GEOMETRY_3D
