#include <complex>

namespace suisen {
namespace geometry {
    // relations between three points X, Y, Z.
    enum class ISP : int {
        L_CURVE = +1, // +---------------+ Z is in 'a' => ISP = +1
        R_CURVE = -1, // |aaaaaaaaaaaaaaa| Z is in 'b' => ISP = -1
        FRONT   = +2, // |ddd X eee Y ccc| Z is in 'c' => ISP = +2
        BACK    = -2, // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2
        MIDDLE  =  0, // +---------------+ Z is in 'e' => ISP =  0
    };

    enum class SIGN : int {
        NEGATIVE = -1,
        ZERO = 0,
        POSITIVE = +1
    };

    template <typename T>
    class Base {
        public:
            static constexpr std::complex<T> ZERO = std::complex<T>(0, 0);
            static constexpr std::complex<T> ONE  = std::complex<T>(1, 0);
            static constexpr std::complex<T> I    = std::complex<T>(0, 1);
            static constexpr T EPS = 1e-9;
            static constexpr T PI  = M_PI;
            static constexpr T E   = M_E;

            static constexpr SIGN sgn(T x) {
                return x > EPS ? SIGN::POSITIVE : x < -EPS ? SIGN::NEGATIVE : SIGN::ZERO;
            }

            static constexpr std::complex<T> point_from_cartesian(const T real, const T imag) {
                return std::complex<T>(real, imag);
            }
            static constexpr std::complex<T> point_from_polar(const T rho, const T theta) {
                return std::complex<T>(rho * std::cos(theta), rho * std::sin(theta));
            }
            static constexpr std::complex<T> point_from_cis(const T theta) {
                return std::complex<T>(std::cos(theta), std::sin(theta));
            }
            static constexpr std::complex<T> conj(const std::complex<T> &z) {
                return std::complex<T>(z.real(), -z.imag());
            }
            static constexpr T arg(const std::complex<T> &z) {
                return std::atan2(z.imag(), z.real());
            }
            static constexpr T square_abs(const std::complex<T> &z) {
                return z.real() * z.real() + z.imag() * z.imag();
            }
            static constexpr T abs(const std::complex<T> &z) {
                return std::sqrt(square_abs(z));
            }
            static constexpr std::complex<T> rot(const std::complex<T> &z, const T theta) {
                return point_from_cis(theta) * z;
            }
            static constexpr T dot(const std::complex<T> &a, const std::complex<T> &b) {
                return a.real() * b.real() + a.imag() * b.imag();
            }
            static constexpr T det(const std::complex<T> &a, const std::complex<T> &b) {
                return a.real() * b.imag() - a.imag() * b.real();
            }
            
            static constexpr ISP isp(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                std::complex<T> ab = b - a, ac = c - a;
                SIGN s = sgn(det(ab, ac));
                if (s == SIGN::POSITIVE) return ISP::L_CURVE;
                if (s == SIGN::NEGATIVE) return ISP::R_CURVE;
                if (sgn(dot(ab, ac)) == SIGN::NEGATIVE) return ISP::BACK;
                std::complex<T> ba = a - b, bc = c - b;
                if (sgn(dot(ba, bc)) == SIGN::NEGATIVE) return ISP::FRONT;
                return ISP::MIDDLE;
            }
    };

    template <typename coordinate_t, typename radius_t = coordinate_t>
    class Circle {
        public:
            const std::complex<coordinate_t> center;
            const radius_t radius;
            Circle(const std::complex<coordinate_t> &c, const radius_t &r) : center(c), radius(r) {}
            inline bool on(const std::complex<coordinate_t> &z) const { return Base<coordinate_t>::sgn(abs(z - center) - radius) == 0; }
            inline bool in(const std::complex<coordinate_t> &z) const { return Base<coordinate_t>::sgn(abs(z - center) - radius) <  0; }
            inline bool contains(const std::complex<coordinate_t> &z) const { return on(z) or in(z); }
    };

    template <typename coordinate_t>
    class Line {
        public:
            const std::complex<coordinate_t> a, b;
            Line(const std::complex<coordinate_t> &from, const std::complex<coordinate_t> &to) : a(from), b(to) {}
    };
    template <typename coordinate_t>
    class Ray {
        public:
            const std::complex<coordinate_t> a, b;
            Ray(const std::complex<coordinate_t> &from, const std::complex<coordinate_t> &to) : a(from), b(to) {}
    };
    template <typename coordinate_t>
    class Segment {
        public:
            const std::complex<coordinate_t> a, b;
            Segment(const std::complex<coordinate_t> &from, const std::complex<coordinate_t> &to) : a(from), b(to) {}
    };

    template <typename T>
    class triangle_utils {
        public:
            static constexpr std::complex<T> signed_area(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                return det(b - a, c - a) / 2;
            }
            static constexpr std::complex<T> area(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                return std::abs(det(b - a, c - a)) / 2;
            }
            static constexpr std::complex<T> pG(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                return (a + b + c) / 3;
            }
            static constexpr Circle<T> pO(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                std::complex<T> ab = b - a, bc = c - b, ca = a - c;
                T la = square_abs(bc), lb = square_abs(ca), lc = square_abs(ab);
                T s = la * (lb + lc - la), t = lb * (lc + la - lb), u = lc * (la + lb - lc);
                T l = s + t + u;
                s /= l, t /= l, u /= l;
                std::complex<T> center = a * s + b * t + c * u;
                return Circle<T>(center, std::abs(center - a));
            }
            static constexpr std::complex<T> pH(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                return a + b + c - 2 * pO(a, b, c).center;
            }
            static constexpr Circle<T> pI(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                T la = std::abs(b - c), lb = std::abs(c - a), lc = std::abs(a - b);
                T l = la + lb + lc;
                la /= l, lb /= l, lc /= l;
                std::complex<T> center = la * a + lb * b + lc * c;
                T radius = 2. * area(a, b, c) / l;
                return Circle<T>(center, radius);
            }
            static constexpr std::tuple<Circle<T>, Circle<T>, Circle<T>> pIabc(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {
                return {pI(-a, b, c), pI(a, -b, c), pI(a, b, -c)};
            }
    };

    template <typename T>
    class line_utils {
        public:
            template <typename L1, typename L2>
            static constexpr bool is_parallel(const L1 &l1, const L2 &l2) {
                return Base<T>::sgn(Base<T>::det(l1.b - l1.a, l2.b - l2.a)) == SIGN::ZERO;
            }
            template <typename L1, typename L2>
            static constexpr bool is_orthogonal(const L1 &l1, const L2 &l2) {
                return Base<T>::sgn(Base<T>::dot(l1.b - l1.a, l2.b - l2.a)) == SIGN::ZERO;
            }
            template <typename L1, typename L2>
            static constexpr bool on_a_line(const L1 &l1, const L2 &l2) {
                return is_parallel(l1, l2) and Base<T>::sgn(Base<T>::det(l1.b - l1.a, l2.a - l1.a)) == SIGN::ZERO;
            }
            template <typename L>
            static constexpr bool in_domain_rect(const L &l, const std::complex<T> &z) {
                return domain_x(l, z) and domain_y(l, z);
            }
            template <typename L>
            static constexpr bool on(const L &l, const std::complex<T> &z) {
                return in_domain_rect(l, z) and Base<T>::sgn(Base<T>::det(l.a - z, l.b - z)) == SIGN::ZERO;
            }
        private:
            static constexpr bool domain_x(const Line<T> &l, const std::complex<T> &z) {
                return l.a.real() != l.b.real() or Base<T>::sgn(l.a.real() - z.real()) == SIGN::ZERO;
            }
            static constexpr bool domain_y(const Line<T> &l, const std::complex<T> &z) {
                return l.a.imag() != l.b.imag() or Base<T>::sgn(l.a.imag() - z.imag()) == SIGN::ZERO;
            }
            static constexpr bool domain_x(const Ray<T> &l, const std::complex<T> &z) {
                SIGN sgn_ab = Base<T>::sgn(l.b.real() - l.a.real()), sgn_az = Base<T>::sgn(z.real() - l.a.real());
                if (sgn_ab == SIGN::POSITIVE) return sgn_az != SIGN::NEGATIVE;
                if (sgn_ab == SIGN::NEGATIVE) return sgn_az != SIGN::POSITIVE;
                return sgn_az == SIGN::ZERO;
            }
            static constexpr bool domain_y(const Ray<T> &l, const std::complex<T> &z) {
                SIGN sgn_ab = Base<T>::sgn(l.b.imag() - l.a.imag()), sgn_az = Base<T>::sgn(z.imag() - l.a.imag());
                if (sgn_ab == SIGN::POSITIVE) return sgn_az != SIGN::NEGATIVE;
                if (sgn_ab == SIGN::NEGATIVE) return sgn_az != SIGN::POSITIVE;
                return sgn_az == SIGN::ZERO;
            }
            static constexpr bool domain_x(const Segment<T> &l, const std::complex<T> &z) {
                return domain_x(Ray<T>(l.a, l.b), z) and domain_x(Ray<T>(l.b, l.a), z);
            }
            static constexpr bool domain_y(const Segment<T> &l, const std::complex<T> &z) {
                return domain_y(Ray<T>(l.a, l.b), z) and domain_y(Ray<T>(l.b, l.a), z);
            }
    };
}
} // namespace suisen