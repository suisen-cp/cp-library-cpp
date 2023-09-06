#ifndef SUISEN_BEZOUT_EQUATION
#define SUISEN_BEZOUT_EQUATION

#include "library/number/ext_gcd.hpp"

namespace suisen {
    class BezoutEquationSolution {
        enum class SolutionType {
            None, Arbitrary, Linear
        };

        friend struct BezoutEquation;

        static constexpr long long neginf = std::numeric_limits<long long>::min() / 2;
        static constexpr long long posinf = std::numeric_limits<long long>::max() / 2;

        SolutionType t;
        // if t == Linear:
        //      x = x0 + k * cx,
        //      y = y0 + k * cy         (kxmin <= k <= kxmax and kymin <= k <= kymax)
        // if t == Arbitrary:
        //      x = x0 + k * cx = k,    (kxmin <= k <= kxmax)
        //      y = y0 + l * cy = l     (kymin <= l <= kymax)
        // if t == None:
        //      No solution
        long long x0, cx, y0, cy;
        long long kxmin = neginf, kxmax = posinf;
        long long kymin = neginf, kymax = posinf;

        BezoutEquationSolution(SolutionType t, long long x0 = 0, long long cx = 0, long long y0 = 0, long long cy = 0) : t(t), x0(x0), cx(cx), y0(y0), cy(cy) {}

        long long get_x(long long k) const {
            return x0 + k * cx;
        }
        long long get_y(long long k) const {
            return y0 + k * cy;
        }
        std::pair<long long, long long> get_pair(long long k) const {
            return { get_x(k), get_y(k) };
        }

        std::optional<std::pair<long long, long long>> get_k_range() const {
            long long kmin = std::max(kxmin, kymin);
            long long kmax = std::min(kxmax, kymax);
            if (kmin <= kmax) {
                return std::pair{ kmin, kmax };
            } else {
                return std::nullopt;
            }
        }

        template <class T>
        static constexpr T fld(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
        template <class T>
        static constexpr T cld(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
    public:
        static BezoutEquationSolution make_none() {
            return BezoutEquationSolution(SolutionType::None);
        }
        static BezoutEquationSolution make_arbitrary() {
            return BezoutEquationSolution(SolutionType::Arbitrary, 0, 1, 0, 1);
        }
        static BezoutEquationSolution make_linear(long long x0, long long cx, long long y0, long long cy) {
            return BezoutEquationSolution(SolutionType::Linear, x0, cx, y0, cy);
        }

        bool has_solution() const {
            if (t == SolutionType::None) {
                return false;
            } else if (t == SolutionType::Arbitrary) {
                return true;
            } else {
                return get_k_range().has_value();
            }
        }
        template <typename T = long long>
        std::optional<T> count() const {
            if (t == SolutionType::None) {
                return 0;
            } else if (t == SolutionType::Arbitrary) {
                return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);
            } else {
                auto k_range = get_k_range();
                if (k_range) {
                    if (k_range->first == neginf or k_range->second == posinf) return std::nullopt;
                    return k_range->second - k_range->first + 1;
                } else {
                    return 0;
                }
            }
        }

        // restrict to x >= min_x.
        bool set_min_x(long long min_x) {
            if (t == SolutionType::None) return false;
            // x0 + k * cx >= min_x
            if (cx == 0) {
                if (x0 < min_x) t = SolutionType::None;
            } else {
                if (cx > 0) { // k >= (min_x - x0) / cx
                    kxmin = std::max(kxmin, cld(min_x - x0, cx));
                } else { // k <= (min_x - x0) / cx
                    kxmax = std::min(kxmax, fld(min_x - x0, cx));
                }
                if (kxmin > kxmax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        // restrict to x <= max_x.
        bool set_max_x(long long max_x) {
            if (t == SolutionType::None) return false;
            // x0 + k * cx <= max_x
            if (cx == 0) {
                if (x0 > max_x) t = SolutionType::None;
            } else {
                if (cx > 0) { // k <= (max_x - x0) / cx
                    kxmax = std::min(kxmax, fld(max_x - x0, cx));
                } else { // k >= (max_x - x0) / cx
                    kxmin = std::max(kxmin, cld(max_x - x0, cx));
                }
                if (kxmin > kxmax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        bool set_x_range(long long min_x, long long max_x) {
            return set_min_x(min_x) and set_max_x(max_x);
        }
        bool set_min_y(long long min_y) {
            if (t == SolutionType::None) return false;
            // y0 + k * cy >= min_y
            if (cy == 0) {
                if (y0 < min_y) t = SolutionType::None;
            } else {
                if (cy > 0) { // k >= (min_y - y0) / cy
                    kymin = std::max(kymin, cld(min_y - y0, cy));
                } else { // k <= (min_y - y0) / cy
                    kymax = std::min(kymax, fld(min_y - y0, cy));
                }
                if (kymin > kymax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        bool set_max_y(long long max_y) {
            if (t == SolutionType::None) return false;
            // y0 + k * cy <= max_y
            if (cy == 0) {
                if (y0 > max_y) t = SolutionType::None;
            } else {
                if (cy > 0) { // k <= (max_y - y0) / cy
                    kymax = std::min(kymax, fld(max_y - y0, cy));
                } else { // k >= (max_y - y0) / cy
                    kymin = std::max(kymin, cld(max_y - y0, cy));
                }
                if (kymin > kymax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        bool set_y_range(long long min_y, long long max_y) {
            return set_min_y(min_y) and set_max_y(max_y);
        }

        std::pair<long long, long long> xmin_solution() const {
            assert(has_solution());
            if (t == SolutionType::Arbitrary) {
                return { kxmin, kymin };
            } else {
                auto [kl, kr] = *get_k_range();
                if (cx == 0) {
                    // avoid overflow
                    return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);
                }
                return get_pair(cx >= 0 ? kl : kr);
            }
        }
        std::pair<long long, long long> xmax_solution() const {
            assert(has_solution());
            if (t == SolutionType::Arbitrary) {
                return { kxmax, kymax };
            } else {
                auto [kl, kr] = *get_k_range();
                if (cx == 0) {
                    // avoid overflow
                    return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);
                }
                return get_pair(cx <= 0 ? kl : kr);
            }
        }
        std::pair<long long, long long> ymin_solution() const {
            assert(has_solution());
            if (t == SolutionType::Arbitrary) {
                return { kxmin, kymin };
            } else {
                auto [kl, kr] = *get_k_range();
                if (cy == 0) {
                    // avoid overflow
                    return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);
                }
                return get_pair(cy >= 0 ? kl : kr);
            }
        }
        std::pair<long long, long long> ymax_solution() const {
            assert(has_solution());
            if (t == SolutionType::Arbitrary) {
                return { kxmax, kymax };
            } else {
                auto [kl, kr] = *get_k_range();
                if (cy == 0) {
                    // avoid overflow
                    return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);
                }
                return get_pair(cy <= 0 ? kl : kr);
            }
        }
    };

    // ax+by=c
    struct BezoutEquation {
        long long a, b;
        long long x, y, g;

        BezoutEquation(long long a, long long b): a(a), b(b) {
            std::tie(x, y, g) = ext_gcd(a, b);
        }

        // solve ax + by = z
        BezoutEquationSolution solve(long long z) {
            if (g == 0) {
                if (z != 0) {
                    return BezoutEquationSolution::make_none();
                } else {
                    return BezoutEquationSolution::make_arbitrary();
                }
            } else {
                if (z % g) {
                    return BezoutEquationSolution::make_none();
                } else {
                    const long long cx = b / g, cy = -a / g;
                    z /= g;
                    __int128_t x0 = __int128_t(x) * z, y0 = __int128_t(y) * z;
                    __int128_t k0 = -x0 / cx;
                    return BezoutEquationSolution::make_linear(x0 + k0 * cx, cx, y0 + k0 * cy, cy);
                }
            }
        }
    };
} // namespace suisen


#endif // SUISEN_BEZOUT_EQUATION
