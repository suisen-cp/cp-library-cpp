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
  bundledCode: "#line 1 \"library/geom/base.hpp\"\n#include <complex>\n\nnamespace\
    \ suisen {\nnamespace geometry {\n    // relations between three points X, Y,\
    \ Z.\n    enum class ISP : int {\n        L_CURVE = +1, // +---------------+ Z\
    \ is in 'a' => ISP = +1\n        R_CURVE = -1, // |aaaaaaaaaaaaaaa| Z is in 'b'\
    \ => ISP = -1\n        FRONT   = +2, // |ddd X eee Y ccc| Z is in 'c' => ISP =\
    \ +2\n        BACK    = -2, // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP = -2\n   \
    \     MIDDLE  =  0, // +---------------+ Z is in 'e' => ISP =  0\n    };\n\n \
    \   enum class SIGN : int {\n        NEGATIVE = -1,\n        ZERO = 0,\n     \
    \   POSITIVE = +1\n    };\n\n    template <typename T>\n    class Base {\n   \
    \     public:\n            static constexpr std::complex<T> ZERO = std::complex<T>(0,\
    \ 0);\n            static constexpr std::complex<T> ONE  = std::complex<T>(1,\
    \ 0);\n            static constexpr std::complex<T> I    = std::complex<T>(0,\
    \ 1);\n            static constexpr T EPS = 1e-9;\n            static constexpr\
    \ T PI  = M_PI;\n            static constexpr T E   = M_E;\n\n            static\
    \ constexpr SIGN sgn(T x) {\n                return x > EPS ? SIGN::POSITIVE :\
    \ x < -EPS ? SIGN::NEGATIVE : SIGN::ZERO;\n            }\n\n            static\
    \ constexpr std::complex<T> point_from_cartesian(const T real, const T imag) {\n\
    \                return std::complex<T>(real, imag);\n            }\n        \
    \    static constexpr std::complex<T> point_from_polar(const T rho, const T theta)\
    \ {\n                return std::complex<T>(rho * std::cos(theta), rho * std::sin(theta));\n\
    \            }\n            static constexpr std::complex<T> point_from_cis(const\
    \ T theta) {\n                return std::complex<T>(std::cos(theta), std::sin(theta));\n\
    \            }\n            static constexpr std::complex<T> conj(const std::complex<T>\
    \ &z) {\n                return std::complex<T>(z.real(), -z.imag());\n      \
    \      }\n            static constexpr T arg(const std::complex<T> &z) {\n   \
    \             return std::atan2(z.imag(), z.real());\n            }\n        \
    \    static constexpr T square_abs(const std::complex<T> &z) {\n             \
    \   return z.real() * z.real() + z.imag() * z.imag();\n            }\n       \
    \     static constexpr T abs(const std::complex<T> &z) {\n                return\
    \ std::sqrt(square_abs(z));\n            }\n            static constexpr std::complex<T>\
    \ rot(const std::complex<T> &z, const T theta) {\n                return point_from_cis(theta)\
    \ * z;\n            }\n            static constexpr T dot(const std::complex<T>\
    \ &a, const std::complex<T> &b) {\n                return a.real() * b.real()\
    \ + a.imag() * b.imag();\n            }\n            static constexpr T det(const\
    \ std::complex<T> &a, const std::complex<T> &b) {\n                return a.real()\
    \ * b.imag() - a.imag() * b.real();\n            }\n            \n           \
    \ static constexpr ISP isp(const std::complex<T> &a, const std::complex<T> &b,\
    \ const std::complex<T> &c) {\n                std::complex<T> ab = b - a, ac\
    \ = c - a;\n                SIGN s = sgn(det(ab, ac));\n                if (s\
    \ == SIGN::POSITIVE) return ISP::L_CURVE;\n                if (s == SIGN::NEGATIVE)\
    \ return ISP::R_CURVE;\n                if (sgn(dot(ab, ac)) == SIGN::NEGATIVE)\
    \ return ISP::BACK;\n                std::complex<T> ba = a - b, bc = c - b;\n\
    \                if (sgn(dot(ba, bc)) == SIGN::NEGATIVE) return ISP::FRONT;\n\
    \                return ISP::MIDDLE;\n            }\n    };\n\n    template <typename\
    \ coordinate_t, typename radius_t = coordinate_t>\n    class Circle {\n      \
    \  public:\n            const std::complex<coordinate_t> center;\n           \
    \ const radius_t radius;\n            Circle(const std::complex<coordinate_t>\
    \ &c, const radius_t &r) : center(c), radius(r) {}\n            inline bool on(const\
    \ std::complex<coordinate_t> &z) const { return Base<coordinate_t>::sgn(abs(z\
    \ - center) - radius) == 0; }\n            inline bool in(const std::complex<coordinate_t>\
    \ &z) const { return Base<coordinate_t>::sgn(abs(z - center) - radius) <  0; }\n\
    \            inline bool contains(const std::complex<coordinate_t> &z) const {\
    \ return on(z) or in(z); }\n    };\n\n    template <typename coordinate_t>\n \
    \   class Line {\n        public:\n            const std::complex<coordinate_t>\
    \ a, b;\n            Line(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n    template <typename coordinate_t>\n   \
    \ class Ray {\n        public:\n            const std::complex<coordinate_t> a,\
    \ b;\n            Ray(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n    template <typename coordinate_t>\n   \
    \ class Segment {\n        public:\n            const std::complex<coordinate_t>\
    \ a, b;\n            Segment(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n\n    template <typename T>\n    class triangle_utils\
    \ {\n        public:\n            static constexpr std::complex<T> signed_area(const\
    \ std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {\n\
    \                return det(b - a, c - a) / 2;\n            }\n            static\
    \ constexpr std::complex<T> area(const std::complex<T> &a, const std::complex<T>\
    \ &b, const std::complex<T> &c) {\n                return std::abs(det(b - a,\
    \ c - a)) / 2;\n            }\n            static constexpr std::complex<T> pG(const\
    \ std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {\n\
    \                return (a + b + c) / 3;\n            }\n            static constexpr\
    \ Circle<T> pO(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T>\
    \ &c) {\n                std::complex<T> ab = b - a, bc = c - b, ca = a - c;\n\
    \                T la = square_abs(bc), lb = square_abs(ca), lc = square_abs(ab);\n\
    \                T s = la * (lb + lc - la), t = lb * (lc + la - lb), u = lc *\
    \ (la + lb - lc);\n                T l = s + t + u;\n                s /= l, t\
    \ /= l, u /= l;\n                std::complex<T> center = a * s + b * t + c *\
    \ u;\n                return Circle<T>(center, std::abs(center - a));\n      \
    \      }\n            static constexpr std::complex<T> pH(const std::complex<T>\
    \ &a, const std::complex<T> &b, const std::complex<T> &c) {\n                return\
    \ a + b + c - 2 * pO(a, b, c).center;\n            }\n            static constexpr\
    \ Circle<T> pI(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T>\
    \ &c) {\n                T la = std::abs(b - c), lb = std::abs(c - a), lc = std::abs(a\
    \ - b);\n                T l = la + lb + lc;\n                la /= l, lb /= l,\
    \ lc /= l;\n                std::complex<T> center = la * a + lb * b + lc * c;\n\
    \                T radius = 2. * area(a, b, c) / l;\n                return Circle<T>(center,\
    \ radius);\n            }\n            static constexpr std::tuple<Circle<T>,\
    \ Circle<T>, Circle<T>> pIabc(const std::complex<T> &a, const std::complex<T>\
    \ &b, const std::complex<T> &c) {\n                return {pI(-a, b, c), pI(a,\
    \ -b, c), pI(a, b, -c)};\n            }\n    };\n\n    template <typename T>\n\
    \    class line_utils {\n        public:\n            template <typename L1, typename\
    \ L2>\n            static constexpr bool is_parallel(const L1 &l1, const L2 &l2)\
    \ {\n                return Base<T>::sgn(Base<T>::det(l1.b - l1.a, l2.b - l2.a))\
    \ == SIGN::ZERO;\n            }\n            template <typename L1, typename L2>\n\
    \            static constexpr bool is_orthogonal(const L1 &l1, const L2 &l2) {\n\
    \                return Base<T>::sgn(Base<T>::dot(l1.b - l1.a, l2.b - l2.a)) ==\
    \ SIGN::ZERO;\n            }\n            template <typename L1, typename L2>\n\
    \            static constexpr bool on_a_line(const L1 &l1, const L2 &l2) {\n \
    \               return is_parallel(l1, l2) and Base<T>::sgn(Base<T>::det(l1.b\
    \ - l1.a, l2.a - l1.a)) == SIGN::ZERO;\n            }\n            template <typename\
    \ L>\n            static constexpr bool in_domain_rect(const L &l, const std::complex<T>\
    \ &z) {\n                return domain_x(l, z) and domain_y(l, z);\n         \
    \   }\n            template <typename L>\n            static constexpr bool on(const\
    \ L &l, const std::complex<T> &z) {\n                return in_domain_rect(l,\
    \ z) and Base<T>::sgn(Base<T>::det(l.a - z, l.b - z)) == SIGN::ZERO;\n       \
    \     }\n        private:\n            static constexpr bool domain_x(const Line<T>\
    \ &l, const std::complex<T> &z) {\n                return l.a.real() != l.b.real()\
    \ or Base<T>::sgn(l.a.real() - z.real()) == SIGN::ZERO;\n            }\n     \
    \       static constexpr bool domain_y(const Line<T> &l, const std::complex<T>\
    \ &z) {\n                return l.a.imag() != l.b.imag() or Base<T>::sgn(l.a.imag()\
    \ - z.imag()) == SIGN::ZERO;\n            }\n            static constexpr bool\
    \ domain_x(const Ray<T> &l, const std::complex<T> &z) {\n                SIGN\
    \ sgn_ab = Base<T>::sgn(l.b.real() - l.a.real()), sgn_az = Base<T>::sgn(z.real()\
    \ - l.a.real());\n                if (sgn_ab == SIGN::POSITIVE) return sgn_az\
    \ != SIGN::NEGATIVE;\n                if (sgn_ab == SIGN::NEGATIVE) return sgn_az\
    \ != SIGN::POSITIVE;\n                return sgn_az == SIGN::ZERO;\n         \
    \   }\n            static constexpr bool domain_y(const Ray<T> &l, const std::complex<T>\
    \ &z) {\n                SIGN sgn_ab = Base<T>::sgn(l.b.imag() - l.a.imag()),\
    \ sgn_az = Base<T>::sgn(z.imag() - l.a.imag());\n                if (sgn_ab ==\
    \ SIGN::POSITIVE) return sgn_az != SIGN::NEGATIVE;\n                if (sgn_ab\
    \ == SIGN::NEGATIVE) return sgn_az != SIGN::POSITIVE;\n                return\
    \ sgn_az == SIGN::ZERO;\n            }\n            static constexpr bool domain_x(const\
    \ Segment<T> &l, const std::complex<T> &z) {\n                return domain_x(Ray<T>(l.a,\
    \ l.b), z) and domain_x(Ray<T>(l.b, l.a), z);\n            }\n            static\
    \ constexpr bool domain_y(const Segment<T> &l, const std::complex<T> &z) {\n \
    \               return domain_y(Ray<T>(l.a, l.b), z) and domain_y(Ray<T>(l.b,\
    \ l.a), z);\n            }\n    };\n}\n} // namespace suisen\n"
  code: "#include <complex>\n\nnamespace suisen {\nnamespace geometry {\n    // relations\
    \ between three points X, Y, Z.\n    enum class ISP : int {\n        L_CURVE =\
    \ +1, // +---------------+ Z is in 'a' => ISP = +1\n        R_CURVE = -1, // |aaaaaaaaaaaaaaa|\
    \ Z is in 'b' => ISP = -1\n        FRONT   = +2, // |ddd X eee Y ccc| Z is in\
    \ 'c' => ISP = +2\n        BACK    = -2, // |bbbbbbbbbbbbbbb| Z is in 'd' => ISP\
    \ = -2\n        MIDDLE  =  0, // +---------------+ Z is in 'e' => ISP =  0\n \
    \   };\n\n    enum class SIGN : int {\n        NEGATIVE = -1,\n        ZERO =\
    \ 0,\n        POSITIVE = +1\n    };\n\n    template <typename T>\n    class Base\
    \ {\n        public:\n            static constexpr std::complex<T> ZERO = std::complex<T>(0,\
    \ 0);\n            static constexpr std::complex<T> ONE  = std::complex<T>(1,\
    \ 0);\n            static constexpr std::complex<T> I    = std::complex<T>(0,\
    \ 1);\n            static constexpr T EPS = 1e-9;\n            static constexpr\
    \ T PI  = M_PI;\n            static constexpr T E   = M_E;\n\n            static\
    \ constexpr SIGN sgn(T x) {\n                return x > EPS ? SIGN::POSITIVE :\
    \ x < -EPS ? SIGN::NEGATIVE : SIGN::ZERO;\n            }\n\n            static\
    \ constexpr std::complex<T> point_from_cartesian(const T real, const T imag) {\n\
    \                return std::complex<T>(real, imag);\n            }\n        \
    \    static constexpr std::complex<T> point_from_polar(const T rho, const T theta)\
    \ {\n                return std::complex<T>(rho * std::cos(theta), rho * std::sin(theta));\n\
    \            }\n            static constexpr std::complex<T> point_from_cis(const\
    \ T theta) {\n                return std::complex<T>(std::cos(theta), std::sin(theta));\n\
    \            }\n            static constexpr std::complex<T> conj(const std::complex<T>\
    \ &z) {\n                return std::complex<T>(z.real(), -z.imag());\n      \
    \      }\n            static constexpr T arg(const std::complex<T> &z) {\n   \
    \             return std::atan2(z.imag(), z.real());\n            }\n        \
    \    static constexpr T square_abs(const std::complex<T> &z) {\n             \
    \   return z.real() * z.real() + z.imag() * z.imag();\n            }\n       \
    \     static constexpr T abs(const std::complex<T> &z) {\n                return\
    \ std::sqrt(square_abs(z));\n            }\n            static constexpr std::complex<T>\
    \ rot(const std::complex<T> &z, const T theta) {\n                return point_from_cis(theta)\
    \ * z;\n            }\n            static constexpr T dot(const std::complex<T>\
    \ &a, const std::complex<T> &b) {\n                return a.real() * b.real()\
    \ + a.imag() * b.imag();\n            }\n            static constexpr T det(const\
    \ std::complex<T> &a, const std::complex<T> &b) {\n                return a.real()\
    \ * b.imag() - a.imag() * b.real();\n            }\n            \n           \
    \ static constexpr ISP isp(const std::complex<T> &a, const std::complex<T> &b,\
    \ const std::complex<T> &c) {\n                std::complex<T> ab = b - a, ac\
    \ = c - a;\n                SIGN s = sgn(det(ab, ac));\n                if (s\
    \ == SIGN::POSITIVE) return ISP::L_CURVE;\n                if (s == SIGN::NEGATIVE)\
    \ return ISP::R_CURVE;\n                if (sgn(dot(ab, ac)) == SIGN::NEGATIVE)\
    \ return ISP::BACK;\n                std::complex<T> ba = a - b, bc = c - b;\n\
    \                if (sgn(dot(ba, bc)) == SIGN::NEGATIVE) return ISP::FRONT;\n\
    \                return ISP::MIDDLE;\n            }\n    };\n\n    template <typename\
    \ coordinate_t, typename radius_t = coordinate_t>\n    class Circle {\n      \
    \  public:\n            const std::complex<coordinate_t> center;\n           \
    \ const radius_t radius;\n            Circle(const std::complex<coordinate_t>\
    \ &c, const radius_t &r) : center(c), radius(r) {}\n            inline bool on(const\
    \ std::complex<coordinate_t> &z) const { return Base<coordinate_t>::sgn(abs(z\
    \ - center) - radius) == 0; }\n            inline bool in(const std::complex<coordinate_t>\
    \ &z) const { return Base<coordinate_t>::sgn(abs(z - center) - radius) <  0; }\n\
    \            inline bool contains(const std::complex<coordinate_t> &z) const {\
    \ return on(z) or in(z); }\n    };\n\n    template <typename coordinate_t>\n \
    \   class Line {\n        public:\n            const std::complex<coordinate_t>\
    \ a, b;\n            Line(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n    template <typename coordinate_t>\n   \
    \ class Ray {\n        public:\n            const std::complex<coordinate_t> a,\
    \ b;\n            Ray(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n    template <typename coordinate_t>\n   \
    \ class Segment {\n        public:\n            const std::complex<coordinate_t>\
    \ a, b;\n            Segment(const std::complex<coordinate_t> &from, const std::complex<coordinate_t>\
    \ &to) : a(from), b(to) {}\n    };\n\n    template <typename T>\n    class triangle_utils\
    \ {\n        public:\n            static constexpr std::complex<T> signed_area(const\
    \ std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {\n\
    \                return det(b - a, c - a) / 2;\n            }\n            static\
    \ constexpr std::complex<T> area(const std::complex<T> &a, const std::complex<T>\
    \ &b, const std::complex<T> &c) {\n                return std::abs(det(b - a,\
    \ c - a)) / 2;\n            }\n            static constexpr std::complex<T> pG(const\
    \ std::complex<T> &a, const std::complex<T> &b, const std::complex<T> &c) {\n\
    \                return (a + b + c) / 3;\n            }\n            static constexpr\
    \ Circle<T> pO(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T>\
    \ &c) {\n                std::complex<T> ab = b - a, bc = c - b, ca = a - c;\n\
    \                T la = square_abs(bc), lb = square_abs(ca), lc = square_abs(ab);\n\
    \                T s = la * (lb + lc - la), t = lb * (lc + la - lb), u = lc *\
    \ (la + lb - lc);\n                T l = s + t + u;\n                s /= l, t\
    \ /= l, u /= l;\n                std::complex<T> center = a * s + b * t + c *\
    \ u;\n                return Circle<T>(center, std::abs(center - a));\n      \
    \      }\n            static constexpr std::complex<T> pH(const std::complex<T>\
    \ &a, const std::complex<T> &b, const std::complex<T> &c) {\n                return\
    \ a + b + c - 2 * pO(a, b, c).center;\n            }\n            static constexpr\
    \ Circle<T> pI(const std::complex<T> &a, const std::complex<T> &b, const std::complex<T>\
    \ &c) {\n                T la = std::abs(b - c), lb = std::abs(c - a), lc = std::abs(a\
    \ - b);\n                T l = la + lb + lc;\n                la /= l, lb /= l,\
    \ lc /= l;\n                std::complex<T> center = la * a + lb * b + lc * c;\n\
    \                T radius = 2. * area(a, b, c) / l;\n                return Circle<T>(center,\
    \ radius);\n            }\n            static constexpr std::tuple<Circle<T>,\
    \ Circle<T>, Circle<T>> pIabc(const std::complex<T> &a, const std::complex<T>\
    \ &b, const std::complex<T> &c) {\n                return {pI(-a, b, c), pI(a,\
    \ -b, c), pI(a, b, -c)};\n            }\n    };\n\n    template <typename T>\n\
    \    class line_utils {\n        public:\n            template <typename L1, typename\
    \ L2>\n            static constexpr bool is_parallel(const L1 &l1, const L2 &l2)\
    \ {\n                return Base<T>::sgn(Base<T>::det(l1.b - l1.a, l2.b - l2.a))\
    \ == SIGN::ZERO;\n            }\n            template <typename L1, typename L2>\n\
    \            static constexpr bool is_orthogonal(const L1 &l1, const L2 &l2) {\n\
    \                return Base<T>::sgn(Base<T>::dot(l1.b - l1.a, l2.b - l2.a)) ==\
    \ SIGN::ZERO;\n            }\n            template <typename L1, typename L2>\n\
    \            static constexpr bool on_a_line(const L1 &l1, const L2 &l2) {\n \
    \               return is_parallel(l1, l2) and Base<T>::sgn(Base<T>::det(l1.b\
    \ - l1.a, l2.a - l1.a)) == SIGN::ZERO;\n            }\n            template <typename\
    \ L>\n            static constexpr bool in_domain_rect(const L &l, const std::complex<T>\
    \ &z) {\n                return domain_x(l, z) and domain_y(l, z);\n         \
    \   }\n            template <typename L>\n            static constexpr bool on(const\
    \ L &l, const std::complex<T> &z) {\n                return in_domain_rect(l,\
    \ z) and Base<T>::sgn(Base<T>::det(l.a - z, l.b - z)) == SIGN::ZERO;\n       \
    \     }\n        private:\n            static constexpr bool domain_x(const Line<T>\
    \ &l, const std::complex<T> &z) {\n                return l.a.real() != l.b.real()\
    \ or Base<T>::sgn(l.a.real() - z.real()) == SIGN::ZERO;\n            }\n     \
    \       static constexpr bool domain_y(const Line<T> &l, const std::complex<T>\
    \ &z) {\n                return l.a.imag() != l.b.imag() or Base<T>::sgn(l.a.imag()\
    \ - z.imag()) == SIGN::ZERO;\n            }\n            static constexpr bool\
    \ domain_x(const Ray<T> &l, const std::complex<T> &z) {\n                SIGN\
    \ sgn_ab = Base<T>::sgn(l.b.real() - l.a.real()), sgn_az = Base<T>::sgn(z.real()\
    \ - l.a.real());\n                if (sgn_ab == SIGN::POSITIVE) return sgn_az\
    \ != SIGN::NEGATIVE;\n                if (sgn_ab == SIGN::NEGATIVE) return sgn_az\
    \ != SIGN::POSITIVE;\n                return sgn_az == SIGN::ZERO;\n         \
    \   }\n            static constexpr bool domain_y(const Ray<T> &l, const std::complex<T>\
    \ &z) {\n                SIGN sgn_ab = Base<T>::sgn(l.b.imag() - l.a.imag()),\
    \ sgn_az = Base<T>::sgn(z.imag() - l.a.imag());\n                if (sgn_ab ==\
    \ SIGN::POSITIVE) return sgn_az != SIGN::NEGATIVE;\n                if (sgn_ab\
    \ == SIGN::NEGATIVE) return sgn_az != SIGN::POSITIVE;\n                return\
    \ sgn_az == SIGN::ZERO;\n            }\n            static constexpr bool domain_x(const\
    \ Segment<T> &l, const std::complex<T> &z) {\n                return domain_x(Ray<T>(l.a,\
    \ l.b), z) and domain_x(Ray<T>(l.b, l.a), z);\n            }\n            static\
    \ constexpr bool domain_y(const Segment<T> &l, const std::complex<T> &z) {\n \
    \               return domain_y(Ray<T>(l.a, l.b), z) and domain_y(Ray<T>(l.b,\
    \ l.a), z);\n            }\n    };\n}\n} // namespace suisen"
  dependsOn: []
  isVerificationFile: false
  path: library/geom/base.hpp
  requiredBy: []
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/geom/base.hpp
layout: document
redirect_from:
- /library/library/geom/base.hpp
- /library/library/geom/base.hpp.html
title: library/geom/base.hpp
---
