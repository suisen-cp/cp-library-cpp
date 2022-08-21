#ifndef SUISEN_AFFINE_CLAMP
#define SUISEN_AFFINE_CLAMP

#include <algorithm>
#include <limits>
#include <type_traits>

#include "library/algebra/monoid/affine.hpp"

namespace suisen {
    template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
    struct AffineClamp : public Affine<T> {
        static constexpr T neg_inf = std::numeric_limits<T>::min();
        static constexpr T pos_inf = std::numeric_limits<T>::max();

        T l, r;
        AffineClamp(const T &a = 1, const T &b = 0, const T &l = neg_inf, T r = pos_inf) : Affine<T>(a, b), l(l), r(r) {}
        AffineClamp(const Affine<T> &f, const T &l = neg_inf, const T &r = pos_inf) : Affine<T>(f), l(l), r(r) {}

        static AffineClamp<T> id() { return AffineClamp<T>{}; }
        static AffineClamp<T> compose(const AffineClamp<T>& f, const AffineClamp<T>& g) {
            AffineClamp<T> h{ Affine<T>::compose(f, g), f.affine_clamp(g.l), f.affine_clamp(g.r) };
            if (h.l > h.r) std::swap(h.l, h.r);
            return h;
        }

        AffineClamp<T> compose(const AffineClamp<T>& g) const { return AffineClamp<T>::compose(*this, g); }

        T affine_clamp(const T &x) const { return std::clamp<__int128_t>(this->template affine<__int128_t>(x), l, r); }
        T operator()(const T &x) const { return affine_clamp(x); }

        template <typename U = T, typename V = T, typename W = T, typename X = T>
        operator std::tuple<U, V, W, X>() { return { this->a, this->b, l, r }; }

        friend std::istream& operator<<(std::istream& in, AffineClamp<T>& f) { return in >> f.a >> f.b >> f.l >> f.r; }
        friend std::ostream& operator>>(std::ostream& out, const AffineClamp<T>& f) { return out << f.a << ' ' << f.b << ' ' << f.l << ' ' << f.r; }
    };
} // namespace suisen

#endif // SUISEN_AFFINE_CLAMP
