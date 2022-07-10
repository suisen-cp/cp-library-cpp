#ifndef SUISEN_POINT
#define SUISEN_POINT

#include <cassert>
#include <iostream>
#include <utility>

namespace suisen::integral_geometry {
    using coordinate_t = long long;
    using multiplied_t = __int128_t;

    struct Point {
        coordinate_t x, y;
        constexpr Point(coordinate_t x = 0, coordinate_t y = 0) : x(x), y(y) {}

        operator std::pair<coordinate_t, coordinate_t>() const { return std::pair<coordinate_t, coordinate_t> { x, y }; }

        friend Point operator+(const Point& p) { return p; }
        friend Point operator-(const Point& p) { return { -p.x, -p.y }; }

        friend Point operator+(const Point& lhs, const Point& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
        friend Point operator-(const Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
        friend Point operator*(const Point& lhs, const Point& rhs) { return { lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x }; }

        friend Point& operator+=(Point& lhs, const Point& rhs) { lhs.x += rhs.x, lhs.y += rhs.y; return lhs; }
        friend Point& operator-=(Point& lhs, const Point& rhs) { lhs.x -= rhs.x, lhs.y -= rhs.y; return lhs; }
        friend Point& operator*=(Point& lhs, const Point& rhs) { return lhs = lhs * rhs; }

        friend Point operator+(const Point& p, coordinate_t real) { return { p.x + real, p.y }; }
        friend Point operator-(const Point& p, coordinate_t real) { return { p.x - real, p.y }; }
        friend Point operator*(const Point& p, coordinate_t real) { return { p.x * real, p.y * real }; }
        friend Point operator/(const Point& p, coordinate_t real) { return { p.x / real, p.y / real }; }

        friend Point operator+=(Point& p, coordinate_t real) { p.x += real; return p; }
        friend Point operator-=(Point& p, coordinate_t real) { p.x -= real; return p; }
        friend Point operator*=(Point& p, coordinate_t real) { p.x *= real, p.y *= real; return p; }
        friend Point operator/=(Point& p, coordinate_t real) { p.x /= real, p.y /= real; return p; }

        friend Point operator+(coordinate_t real, const Point& p) { return { real + p.x, p.y }; }
        friend Point operator-(coordinate_t real, const Point& p) { return { real - p.x, -p.y }; }
        friend Point operator*(coordinate_t real, const Point& p) { return { real * p.x, real * p.y }; }

        friend bool operator==(const Point& lhs, const Point& rhs) { return lhs.x == rhs.x and lhs.y == rhs.y; }
        friend bool operator!=(const Point& lhs, const Point& rhs) { return not (lhs == rhs); }

        friend std::istream& operator>>(std::istream& in, Point& p) { return in >> p.x >> p.y; }
        friend std::ostream& operator<<(std::ostream& out, const Point& p) { return out << p.x << ' ' << p.y; }

        template <std::size_t I>
        coordinate_t get() const {
            if constexpr (I == 0) return x;
            else if constexpr (I == 1) return y;
            else assert(false);
        }
        template <std::size_t I>
        coordinate_t& get() {
            if constexpr (I == 0) return x;
            else if constexpr (I == 1) return y;
            else assert(false);
        }
    };

    constexpr Point ZERO = { 0, 0 };
    constexpr Point ONE  = { 1, 0 };
    constexpr Point I    = { 0, 1 };

    constexpr auto XY_COMPARATOR         = [](const Point& p, const Point& q) { return p.x == q.x ? p.y < q.y : p.x < q.x; };
    constexpr auto XY_COMPARATOR_GREATER = [](const Point& p, const Point& q) { return p.x == q.x ? p.y > q.y : p.x > q.x; };
    constexpr auto YX_COMPARATOR         = [](const Point& p, const Point& q) { return p.y == q.y ? p.x < q.x : p.y < q.y; };
    constexpr auto YX_COMPARATOR_GREATER = [](const Point& p, const Point& q) { return p.y == q.y ? p.x > q.x : p.y > q.y; };
} // namespace suisen::integral_geometry

namespace std {
    template <>
    struct tuple_size<suisen::integral_geometry::Point> : integral_constant<size_t, 2> {};
    template <size_t I>
    struct tuple_element<I, suisen::integral_geometry::Point> { using type = suisen::integral_geometry::coordinate_t; };
}

#endif // SUISEN_POINT
