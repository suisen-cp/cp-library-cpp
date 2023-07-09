---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/geom/geometry3d.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cmath>\n#include <iostream>\n#include <optional>\n\
    \nnamespace suisen::geometry3d {\n    namespace math {\n        template <typename\
    \ T>\n        T sqrt(const T &x) { return ::sqrtl(x); }\n#ifdef __HAVE_FLOAT128\n\
    \        template <>\n        __float128 sqrt<__float128>(const __float128 &x)\
    \ { return ::sqrtf128(x); }\n#endif\n        template <>\n        long double\
    \ sqrt<long double>(const long double &x) { return ::sqrtl(x); }\n        template\
    \ <>\n        double sqrt<double>(const double &x) { return ::sqrt(x); }\n   \
    \     template <>\n        float sqrt<float>(const float &x) { return ::sqrtf(x);\
    \ }\n    }\n\n    using coordinate_t = long double;\n    using Point = std::array<coordinate_t,\
    \ 3>;\n    \n    constexpr coordinate_t EPS = 1e-9;\n\n    std::istream& operator>>(std::istream\
    \ &in, Point &p) {\n        return in >> p[0] >> p[1] >> p[2];\n    }\n    std::ostream&\
    \ operator<<(std::ostream &out, const Point &p) {\n        return out << p[0]\
    \ << ' ' << p[1] << ' ' << p[2];\n    }\n\n    int signum(const coordinate_t &x)\
    \ { return x < -EPS ? -1 : x > EPS ? +1 : 0; }\n    int compare(const coordinate_t\
    \ &x, const coordinate_t &y) { return signum(x - y); }\n    bool equals(const\
    \ coordinate_t &x, const coordinate_t &y) { return compare(x, y) == 0; }\n\n \
    \   coordinate_t inner_product(const Point &p, const Point &q) {\n        return\
    \ p[0] * q[0] + p[1] * q[1] + p[2] * q[2];\n    }\n    Point outer_product(const\
    \ Point &p, const Point &q) {\n        return Point { p[1] * q[2] - p[2] * q[1],\
    \ p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0] };\n    }\n\n    Point&\
    \ operator+=(Point &p, const Point &q) { return p[0] += q[0], p[1] += q[1], p[2]\
    \ += q[2], p; }\n    Point& operator-=(Point &p, const Point &q) { return p[0]\
    \ -= q[0], p[1] -= q[1], p[2] -= q[2], p; }\n    Point& operator*=(Point &p, const\
    \ Point &q) { return p = outer_product(p, q); }\n    Point& operator*=(Point &p,\
    \ const coordinate_t &c) { return p[0] *= c, p[1] *= c, p[2] *= c, p; }\n    Point&\
    \ operator/=(Point &p, const coordinate_t &c) { return p *= coordinate_t(1) /\
    \ c; }\n\n    Point operator+(const Point &p, const Point &q) { auto r = p; return\
    \ r += q; }\n    Point operator-(const Point &p, const Point &q) { auto r = p;\
    \ return r -= q; }\n    Point operator*(const Point &p, const Point &q) { auto\
    \ r = p; return r *= q; }\n    Point operator*(const Point &p, const coordinate_t\
    \ &c) { auto r = p; return r *= c; }\n    Point operator*(const coordinate_t &c,\
    \ const Point &p) { auto r = p; return r *= c; }\n    Point operator/(const Point\
    \ &p, const coordinate_t &c) { auto r = p; return r /= c; }\n\n    Point operator+(const\
    \ Point &p) { return Point { +p[0], +p[1], +p[2] }; }\n    Point operator-(const\
    \ Point &p) { return Point { -p[0], -p[1], -p[2] }; }\n\n    coordinate_t square_abs(const\
    \ Point &p) { return inner_product(p, p); }\n    coordinate_t abs(const Point\
    \ &p) { return math::sqrt(square_abs(p)); }\n    coordinate_t dist(const Point\
    \ &p, const Point &q) { return abs(p - q); }\n    Point& normalize(Point &p) {\
    \ return p /= abs(p); }\n    Point normalized(const Point &p) { auto q = p; return\
    \ normalize(q); }\n\n    bool equals(const Point &p, const Point &q) {\n     \
    \   auto [x, y, z] = p - q;\n        return signum(x) == 0 and signum(y) == 0\
    \ and signum(z) == 0;\n    }\n\n    bool is_parallel(const Point &a, const Point\
    \ &b) {\n        return equals(outer_product(a, b), { 0, 0, 0 });\n    }\n   \
    \ bool is_orthogonal(const Point &a, const Point &b) {\n        return equals(inner_product(a,\
    \ b), 0);\n    }\n\n    struct Line    : public std::pair<Point, Point> { using\
    \ std::pair<Point, Point>::pair; };\n    struct Ray     : public Line { using\
    \ Line::Line; };\n    struct Segment : public Line { using Line::Line; };\n\n\
    \    Point projection(const Line &l, const Point &p) {\n        Point a = l.first\
    \ - p, b = l.second - p;\n        auto ab = b - a;\n        Point h = p + (inner_product(b,\
    \ ab) * a - inner_product(a, ab) * b) / square_abs(ab);\n        // assert(is_parallel(h\
    \ - l.first, l.second - l.first));\n        // assert(is_orthogonal(h - p, l.second\
    \ - l.first));\n        return h;\n    }\n    coordinate_t dist(const Line &l,\
    \ const Point &p) {\n        return dist(projection(l, p), p);\n    }\n    coordinate_t\
    \ dist(const Ray &l, const Point &p) {\n        const auto &[a, b] = l;\n    \
    \    Point h = projection(l, p);\n        return signum(inner_product(h - a, b\
    \ - a)) < 0 ? abs(a - p) : abs(h - p);\n    }\n    coordinate_t dist(const Segment\
    \ &l, const Point &p) {\n        const auto &[a, b] = l;\n        Point h = projection(l,\
    \ p);\n        if (signum(inner_product(h - a, b - a)) < 0) {\n            return\
    \ dist(a, p);\n        } else if (signum(inner_product(h - b, a - b)) < 0) {\n\
    \            return dist(b, p);\n        } else {\n            return dist(h,\
    \ p);\n        }\n    }\n    bool on(const Line    &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n    bool on(const Ray     &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n    bool on(const Segment &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n\n    namespace internal {\n        std::pair<Point, Point>\
    \ closest_pair(const Line &l, const Line &m) {\n            auto [la, lb] = l;\n\
    \            auto [ma, mb] = m;\n            Point ld = normalized(lb - la), md\
    \ = normalized(mb - ma);\n            // P(x) = la + ld * x, Q(y) = ma + md *\
    \ y. min |P(x) - Q(y)| is the distance of the lines l, m.\n            auto d\
    \ = ma - la;\n            coordinate_t p = inner_product(d, ld), q = inner_product(d,\
    \ md), c = inner_product(ld, md);\n            // x - cy = p\n            // cx\
    \ - y = q\n            coordinate_t x, y;\n            if (equals(std::abs(c),\
    \ 1)) { // parallel <=> ld // md\n                x = p, y = 0;\n            }\
    \ else {\n                coordinate_t den = 1 - c * c;\n                x = (p\
    \ - c * q) / den, y = (c * p - q) / den;\n            }\n            return {\
    \ la + ld * x, ma + md * y };\n        }\n    }\n    coordinate_t dist(const Line\
    \ &l, const Line &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n\
    \        return dist(p, q);\n    }\n    coordinate_t dist(const Line &l, const\
    \ Ray &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return\
    \ on(m, q) ? dist(p, q) : dist(l, m.first);\n    }\n    coordinate_t dist(const\
    \ Ray &l, const Line &m) {\n        return dist(m, l);\n    }\n    coordinate_t\
    \ dist(const Line &l, const Segment &m) {\n        auto [p, q] = internal::closest_pair(l,\
    \ m);\n        return on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(l,\
    \ m.second));\n    }\n    coordinate_t dist(const Segment &l, Line &m) {\n   \
    \     return dist(m, l);\n    }\n    coordinate_t dist(const Ray &l, const Ray\
    \ &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return on(l,\
    \ p) and on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(m, l.first));\n\
    \    }\n    coordinate_t dist(const Ray &l, const Segment &m) {\n        auto\
    \ [p, q] = internal::closest_pair(l, m);\n        return on(l, p) and on(m, q)\
    \ ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second), dist(m, l.first)\
    \ });\n    }\n    coordinate_t dist(const Segment &l, const Ray &m) {\n      \
    \  return dist(m, l);\n    }\n    coordinate_t dist(const Segment &l, const Segment\
    \ &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return on(l,\
    \ p) and on(m, q) ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second),\
    \ dist(m, l.first), dist(m, l.second) });\n    }\n\n    bool is_parallel(const\
    \ Line &l, const Line &m) {\n        return is_parallel(l.second - l.first, m.second\
    \ - m.first);\n    }\n    bool is_orthogonal(const Line &l, const Line &m) {\n\
    \        return is_orthogonal(l.second - l.first, m.second - m.first);\n    }\n\
    \n    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line, line_t>,\
    \ std::nullptr_t> = nullptr>\n    std::optional<Point> cross_point(const line_t\
    \ &l, const line_t &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n\
    \        return equals(p, q) and on(l, p) and on(m, q) ? std::make_optional(p)\
    \ : std::nullopt;\n    }\n\n    // Plane: ax + by + cz + d = 0\n    struct Plane\
    \ {\n        Point normal_vec; // = [a, b, c]\n        coordinate_t d;\n     \
    \   Plane() = default;\n        Plane(const Point &p, const Point &q, const Point\
    \ &r) : normal_vec(normalized((q - p) * (r - p))), d(-inner_product(normal_vec,\
    \ p)) {}\n        Plane(const coordinate_t &a, coordinate_t &b, coordinate_t &c,\
    \ coordinate_t &d) : normal_vec(normalized({a, b, c})), d(d / abs({a, b, c}))\
    \ {}\n    };\n\n    coordinate_t dist(const Plane &plane, const Point &p) {\n\
    \        return std::abs(inner_product(plane.normal_vec, p) + plane.d);\n    }\n\
    \    bool on(const Plane &plane, const Point &p) {\n        return dist(plane,\
    \ p) < EPS;\n    }\n    Point projection(const Plane &plane, const Point &p) {\n\
    \        coordinate_t d = dist(plane, p);\n        Point q = p + d * plane.normal_vec;\n\
    \        return on(plane, q) ? q : p - d * plane.normal_vec;\n    }\n\n    bool\
    \ is_parallel(const Plane &plane, const Line &l) {\n        return is_orthogonal(plane.normal_vec,\
    \ l.second - l.first);\n    }\n    bool is_orthogonal(const Plane &plane, const\
    \ Line &l) {\n        return is_parallel(plane.normal_vec, l.second - l.first);\n\
    \    }\n    coordinate_t dist(const Plane &plane, const Line &l) {\n        return\
    \ is_parallel(plane, l) ? dist(plane, l.first) : 0;\n    }\n    coordinate_t dist(const\
    \ Plane &plane, const Ray &l) {\n        Point h = projection(plane, l.first);\n\
    \        coordinate_t ip = inner_product(l.first - h, l.second - l.first);\n \
    \       return signum(ip) < 0 ? 0 : dist(h, l.first);\n    }\n    coordinate_t\
    \ dist(const Plane &plane, const Segment &l) {\n        Point ha = projection(plane,\
    \ l.first), hb = projection(plane, l.second);\n        coordinate_t ipa = inner_product(l.first\
    \ - ha, l.second - l.first), ipb = inner_product(l.second - hb, l.first - l.second);\n\
    \        return signum(ipa) < 0 and signum(ipb) < 0 ? 0 : std::min(dist(plane,\
    \ l.first), dist(plane, l.second));\n    }\n\n    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line,\
    \ line_t>, std::nullptr_t> = nullptr>\n    std::optional<Point> cross_point(const\
    \ Plane &plane, const line_t &l) {\n        if (on(plane, l.first)) return std::make_optional(l.first);\n\
    \        if (is_parallel(plane, l)) return std::nullopt;\n        Point ha = projection(plane,\
    \ l.first);\n        Point hb = projection(plane, l.second);\n        coordinate_t\
    \ la = dist(ha, l.first), lb = dist(hb, l.second);\n        Point p = hb + (ha\
    \ - hb) * (lb / (lb + la));\n        Line m { l.first, l.second };\n        Point\
    \ res = on(m, p) ? p : hb + (ha - hb) * (lb / (lb - la));\n        // assert(on(plane,\
    \ res) and on(m, res));\n        return on(l, res) ? std::make_optional(res) :\
    \ std::nullopt;\n    }\n\n    bool on_triangle(const std::array<Point, 3> &t,\
    \ const Point &p) {\n        if (not on(Plane{ t[0], t[1], t[2] }, p)) return\
    \ false;\n        bool first = true;\n        Point normal;\n        for (int\
    \ i = 0; i < 3; ++i) {\n            Point w = (t[(i + 1) % 3] - t[i]) * (p - t[i]);\n\
    \            if (equals(w, Point{0, 0, 0})) continue;\n            normalize(w);\n\
    \            if (first) {\n                normal = w;\n                first\
    \ = false;\n            } else if (not equals(normal, w)) {\n                return\
    \ false;\n            }\n        }\n        return true;\n    }\n}\n\n\n"
  code: "#ifndef SUISEN_GEOMETRY_3D\n#define SUISEN_GEOMETRY_3D\n\n#include <algorithm>\n\
    #include <array>\n#include <cmath>\n#include <iostream>\n#include <optional>\n\
    \nnamespace suisen::geometry3d {\n    namespace math {\n        template <typename\
    \ T>\n        T sqrt(const T &x) { return ::sqrtl(x); }\n#ifdef __HAVE_FLOAT128\n\
    \        template <>\n        __float128 sqrt<__float128>(const __float128 &x)\
    \ { return ::sqrtf128(x); }\n#endif\n        template <>\n        long double\
    \ sqrt<long double>(const long double &x) { return ::sqrtl(x); }\n        template\
    \ <>\n        double sqrt<double>(const double &x) { return ::sqrt(x); }\n   \
    \     template <>\n        float sqrt<float>(const float &x) { return ::sqrtf(x);\
    \ }\n    }\n\n    using coordinate_t = long double;\n    using Point = std::array<coordinate_t,\
    \ 3>;\n    \n    constexpr coordinate_t EPS = 1e-9;\n\n    std::istream& operator>>(std::istream\
    \ &in, Point &p) {\n        return in >> p[0] >> p[1] >> p[2];\n    }\n    std::ostream&\
    \ operator<<(std::ostream &out, const Point &p) {\n        return out << p[0]\
    \ << ' ' << p[1] << ' ' << p[2];\n    }\n\n    int signum(const coordinate_t &x)\
    \ { return x < -EPS ? -1 : x > EPS ? +1 : 0; }\n    int compare(const coordinate_t\
    \ &x, const coordinate_t &y) { return signum(x - y); }\n    bool equals(const\
    \ coordinate_t &x, const coordinate_t &y) { return compare(x, y) == 0; }\n\n \
    \   coordinate_t inner_product(const Point &p, const Point &q) {\n        return\
    \ p[0] * q[0] + p[1] * q[1] + p[2] * q[2];\n    }\n    Point outer_product(const\
    \ Point &p, const Point &q) {\n        return Point { p[1] * q[2] - p[2] * q[1],\
    \ p[2] * q[0] - p[0] * q[2], p[0] * q[1] - p[1] * q[0] };\n    }\n\n    Point&\
    \ operator+=(Point &p, const Point &q) { return p[0] += q[0], p[1] += q[1], p[2]\
    \ += q[2], p; }\n    Point& operator-=(Point &p, const Point &q) { return p[0]\
    \ -= q[0], p[1] -= q[1], p[2] -= q[2], p; }\n    Point& operator*=(Point &p, const\
    \ Point &q) { return p = outer_product(p, q); }\n    Point& operator*=(Point &p,\
    \ const coordinate_t &c) { return p[0] *= c, p[1] *= c, p[2] *= c, p; }\n    Point&\
    \ operator/=(Point &p, const coordinate_t &c) { return p *= coordinate_t(1) /\
    \ c; }\n\n    Point operator+(const Point &p, const Point &q) { auto r = p; return\
    \ r += q; }\n    Point operator-(const Point &p, const Point &q) { auto r = p;\
    \ return r -= q; }\n    Point operator*(const Point &p, const Point &q) { auto\
    \ r = p; return r *= q; }\n    Point operator*(const Point &p, const coordinate_t\
    \ &c) { auto r = p; return r *= c; }\n    Point operator*(const coordinate_t &c,\
    \ const Point &p) { auto r = p; return r *= c; }\n    Point operator/(const Point\
    \ &p, const coordinate_t &c) { auto r = p; return r /= c; }\n\n    Point operator+(const\
    \ Point &p) { return Point { +p[0], +p[1], +p[2] }; }\n    Point operator-(const\
    \ Point &p) { return Point { -p[0], -p[1], -p[2] }; }\n\n    coordinate_t square_abs(const\
    \ Point &p) { return inner_product(p, p); }\n    coordinate_t abs(const Point\
    \ &p) { return math::sqrt(square_abs(p)); }\n    coordinate_t dist(const Point\
    \ &p, const Point &q) { return abs(p - q); }\n    Point& normalize(Point &p) {\
    \ return p /= abs(p); }\n    Point normalized(const Point &p) { auto q = p; return\
    \ normalize(q); }\n\n    bool equals(const Point &p, const Point &q) {\n     \
    \   auto [x, y, z] = p - q;\n        return signum(x) == 0 and signum(y) == 0\
    \ and signum(z) == 0;\n    }\n\n    bool is_parallel(const Point &a, const Point\
    \ &b) {\n        return equals(outer_product(a, b), { 0, 0, 0 });\n    }\n   \
    \ bool is_orthogonal(const Point &a, const Point &b) {\n        return equals(inner_product(a,\
    \ b), 0);\n    }\n\n    struct Line    : public std::pair<Point, Point> { using\
    \ std::pair<Point, Point>::pair; };\n    struct Ray     : public Line { using\
    \ Line::Line; };\n    struct Segment : public Line { using Line::Line; };\n\n\
    \    Point projection(const Line &l, const Point &p) {\n        Point a = l.first\
    \ - p, b = l.second - p;\n        auto ab = b - a;\n        Point h = p + (inner_product(b,\
    \ ab) * a - inner_product(a, ab) * b) / square_abs(ab);\n        // assert(is_parallel(h\
    \ - l.first, l.second - l.first));\n        // assert(is_orthogonal(h - p, l.second\
    \ - l.first));\n        return h;\n    }\n    coordinate_t dist(const Line &l,\
    \ const Point &p) {\n        return dist(projection(l, p), p);\n    }\n    coordinate_t\
    \ dist(const Ray &l, const Point &p) {\n        const auto &[a, b] = l;\n    \
    \    Point h = projection(l, p);\n        return signum(inner_product(h - a, b\
    \ - a)) < 0 ? abs(a - p) : abs(h - p);\n    }\n    coordinate_t dist(const Segment\
    \ &l, const Point &p) {\n        const auto &[a, b] = l;\n        Point h = projection(l,\
    \ p);\n        if (signum(inner_product(h - a, b - a)) < 0) {\n            return\
    \ dist(a, p);\n        } else if (signum(inner_product(h - b, a - b)) < 0) {\n\
    \            return dist(b, p);\n        } else {\n            return dist(h,\
    \ p);\n        }\n    }\n    bool on(const Line    &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n    bool on(const Ray     &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n    bool on(const Segment &l, const Point &p) { return\
    \ dist(l, p) < EPS; }\n\n    namespace internal {\n        std::pair<Point, Point>\
    \ closest_pair(const Line &l, const Line &m) {\n            auto [la, lb] = l;\n\
    \            auto [ma, mb] = m;\n            Point ld = normalized(lb - la), md\
    \ = normalized(mb - ma);\n            // P(x) = la + ld * x, Q(y) = ma + md *\
    \ y. min |P(x) - Q(y)| is the distance of the lines l, m.\n            auto d\
    \ = ma - la;\n            coordinate_t p = inner_product(d, ld), q = inner_product(d,\
    \ md), c = inner_product(ld, md);\n            // x - cy = p\n            // cx\
    \ - y = q\n            coordinate_t x, y;\n            if (equals(std::abs(c),\
    \ 1)) { // parallel <=> ld // md\n                x = p, y = 0;\n            }\
    \ else {\n                coordinate_t den = 1 - c * c;\n                x = (p\
    \ - c * q) / den, y = (c * p - q) / den;\n            }\n            return {\
    \ la + ld * x, ma + md * y };\n        }\n    }\n    coordinate_t dist(const Line\
    \ &l, const Line &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n\
    \        return dist(p, q);\n    }\n    coordinate_t dist(const Line &l, const\
    \ Ray &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return\
    \ on(m, q) ? dist(p, q) : dist(l, m.first);\n    }\n    coordinate_t dist(const\
    \ Ray &l, const Line &m) {\n        return dist(m, l);\n    }\n    coordinate_t\
    \ dist(const Line &l, const Segment &m) {\n        auto [p, q] = internal::closest_pair(l,\
    \ m);\n        return on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(l,\
    \ m.second));\n    }\n    coordinate_t dist(const Segment &l, Line &m) {\n   \
    \     return dist(m, l);\n    }\n    coordinate_t dist(const Ray &l, const Ray\
    \ &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return on(l,\
    \ p) and on(m, q) ? dist(p, q) : std::min(dist(l, m.first), dist(m, l.first));\n\
    \    }\n    coordinate_t dist(const Ray &l, const Segment &m) {\n        auto\
    \ [p, q] = internal::closest_pair(l, m);\n        return on(l, p) and on(m, q)\
    \ ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second), dist(m, l.first)\
    \ });\n    }\n    coordinate_t dist(const Segment &l, const Ray &m) {\n      \
    \  return dist(m, l);\n    }\n    coordinate_t dist(const Segment &l, const Segment\
    \ &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n        return on(l,\
    \ p) and on(m, q) ? dist(p, q) : std::min({ dist(l, m.first), dist(l, m.second),\
    \ dist(m, l.first), dist(m, l.second) });\n    }\n\n    bool is_parallel(const\
    \ Line &l, const Line &m) {\n        return is_parallel(l.second - l.first, m.second\
    \ - m.first);\n    }\n    bool is_orthogonal(const Line &l, const Line &m) {\n\
    \        return is_orthogonal(l.second - l.first, m.second - m.first);\n    }\n\
    \n    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line, line_t>,\
    \ std::nullptr_t> = nullptr>\n    std::optional<Point> cross_point(const line_t\
    \ &l, const line_t &m) {\n        auto [p, q] = internal::closest_pair(l, m);\n\
    \        return equals(p, q) and on(l, p) and on(m, q) ? std::make_optional(p)\
    \ : std::nullopt;\n    }\n\n    // Plane: ax + by + cz + d = 0\n    struct Plane\
    \ {\n        Point normal_vec; // = [a, b, c]\n        coordinate_t d;\n     \
    \   Plane() = default;\n        Plane(const Point &p, const Point &q, const Point\
    \ &r) : normal_vec(normalized((q - p) * (r - p))), d(-inner_product(normal_vec,\
    \ p)) {}\n        Plane(const coordinate_t &a, coordinate_t &b, coordinate_t &c,\
    \ coordinate_t &d) : normal_vec(normalized({a, b, c})), d(d / abs({a, b, c}))\
    \ {}\n    };\n\n    coordinate_t dist(const Plane &plane, const Point &p) {\n\
    \        return std::abs(inner_product(plane.normal_vec, p) + plane.d);\n    }\n\
    \    bool on(const Plane &plane, const Point &p) {\n        return dist(plane,\
    \ p) < EPS;\n    }\n    Point projection(const Plane &plane, const Point &p) {\n\
    \        coordinate_t d = dist(plane, p);\n        Point q = p + d * plane.normal_vec;\n\
    \        return on(plane, q) ? q : p - d * plane.normal_vec;\n    }\n\n    bool\
    \ is_parallel(const Plane &plane, const Line &l) {\n        return is_orthogonal(plane.normal_vec,\
    \ l.second - l.first);\n    }\n    bool is_orthogonal(const Plane &plane, const\
    \ Line &l) {\n        return is_parallel(plane.normal_vec, l.second - l.first);\n\
    \    }\n    coordinate_t dist(const Plane &plane, const Line &l) {\n        return\
    \ is_parallel(plane, l) ? dist(plane, l.first) : 0;\n    }\n    coordinate_t dist(const\
    \ Plane &plane, const Ray &l) {\n        Point h = projection(plane, l.first);\n\
    \        coordinate_t ip = inner_product(l.first - h, l.second - l.first);\n \
    \       return signum(ip) < 0 ? 0 : dist(h, l.first);\n    }\n    coordinate_t\
    \ dist(const Plane &plane, const Segment &l) {\n        Point ha = projection(plane,\
    \ l.first), hb = projection(plane, l.second);\n        coordinate_t ipa = inner_product(l.first\
    \ - ha, l.second - l.first), ipb = inner_product(l.second - hb, l.first - l.second);\n\
    \        return signum(ipa) < 0 and signum(ipb) < 0 ? 0 : std::min(dist(plane,\
    \ l.first), dist(plane, l.second));\n    }\n\n    template <typename line_t, std::enable_if_t<std::is_base_of_v<Line,\
    \ line_t>, std::nullptr_t> = nullptr>\n    std::optional<Point> cross_point(const\
    \ Plane &plane, const line_t &l) {\n        if (on(plane, l.first)) return std::make_optional(l.first);\n\
    \        if (is_parallel(plane, l)) return std::nullopt;\n        Point ha = projection(plane,\
    \ l.first);\n        Point hb = projection(plane, l.second);\n        coordinate_t\
    \ la = dist(ha, l.first), lb = dist(hb, l.second);\n        Point p = hb + (ha\
    \ - hb) * (lb / (lb + la));\n        Line m { l.first, l.second };\n        Point\
    \ res = on(m, p) ? p : hb + (ha - hb) * (lb / (lb - la));\n        // assert(on(plane,\
    \ res) and on(m, res));\n        return on(l, res) ? std::make_optional(res) :\
    \ std::nullopt;\n    }\n\n    bool on_triangle(const std::array<Point, 3> &t,\
    \ const Point &p) {\n        if (not on(Plane{ t[0], t[1], t[2] }, p)) return\
    \ false;\n        bool first = true;\n        Point normal;\n        for (int\
    \ i = 0; i < 3; ++i) {\n            Point w = (t[(i + 1) % 3] - t[i]) * (p - t[i]);\n\
    \            if (equals(w, Point{0, 0, 0})) continue;\n            normalize(w);\n\
    \            if (first) {\n                normal = w;\n                first\
    \ = false;\n            } else if (not equals(normal, w)) {\n                return\
    \ false;\n            }\n        }\n        return true;\n    }\n}\n\n#endif //\
    \ SUISEN_GEOMETRY_3D\n"
  dependsOn: []
  isVerificationFile: false
  path: library/geom/geometry3d.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/geom/geometry3d.hpp
layout: document
title: "3\u6B21\u5143\u5E7E\u4F55\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
---
## 3次元幾何テンプレート

verify は出来てません。
