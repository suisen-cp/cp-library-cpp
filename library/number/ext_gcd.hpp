#ifndef SUISEN_EXT_GCD
#define SUISEN_EXT_GCD

#include <cassert>
#include <cmath>
#include <limits>
#include <optional>
#include <tuple>
#include <utility>

namespace suisen {
    constexpr long long safe_mod(long long x, long long m) {
        x %= m;
        return x < 0 ? x + m : x;
    }

    // returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. 
    std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
        long long x = 1, y = 0;
        long long z = 0, w = 1;
        while (b) {
            long long p = a / b, q = a % b;
            x -= y * p, std::swap(x, y);
            z -= w * p, std::swap(z, w);
            a = b, b = q;
        }
        if (a < 0) {
            x = -x, z = -z, a = -a;
        }
        return { x, z, a };
    }

    // returns {x,g} s.t. a*x=g (mod m)
    std::pair<long long, long long> gcd_inv(long long a, long long m) {
        auto [x, y, g] = ext_gcd(a, m);
        return { safe_mod(x, m), g };
    }

    // returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.
    long long inv_mod(long long a, long long mod) {
        auto [inv, y, g] = ext_gcd(a, mod);
        assert(g == 1);
        return safe_mod(inv, mod);
    }

    class Solution {
        enum class SolutionType {
            None, Arbitrary, Linear
        };

        friend struct Equation;

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

        Solution(SolutionType t, long long x0 = 0, long long cx = 0, long long y0 = 0, long long cy = 0) : t(t), x0(x0), cx(cx), y0(y0), cy(cy) {}

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

        template <typename T>
        static constexpr T fld(T x, T y) {
            return x / y - ((x ^ y) < 0 and x % y);
        }
        template <typename T>
        static constexpr T cld(T x, T y) {
            return x / y + ((x ^ y) >= 0 and x % y);
        }
    public:
        static Solution make_none() {
            return Solution(SolutionType::None);
        }
        static Solution make_arbitrary() {
            return Solution(SolutionType::Arbitrary, 0, 1, 0, 1);
        }
        static Solution make_linear(long long x0, long long cx, long long y0, long long cy) {
            return Solution(SolutionType::Linear, x0, cx, y0, cy);
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
        T count() const {
            if (t == SolutionType::None) {
                return 0;
            } else if (t == SolutionType::Arbitrary) {
                return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);
            } else {
                auto k_range = get_k_range();
                if (k_range) {
                    return k_range->second - k_range->first + 1;
                } else {
                    return 0;
                }
            }
        }

        // restrict to x <= upper.
        bool set_upper_x(long long upper) {
            if (t == SolutionType::None) return false;
            // x0 + k * cx <= upper
            if (cx == 0) {
                if (x0 > upper) t = SolutionType::None;
            } else {
                if (cx > 0) { // k <= (upper - x0) / cx
                    kxmin = std::min(kxmin, fld(upper - x0, cx));
                } else { // k >= (upper - x0) / cx
                    kxmax = std::max(kxmax, cld(upper - x0, cx));
                }
                if (kxmin > kxmax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        // restrict to x >= lower.
        bool set_lower_x(long long lower) {
            if (t == SolutionType::None) return false;
            // x0 + k * cx >= lower
            if (cx == 0) {
                if (x0 < lower) t = SolutionType::None;
            } else {
                if (cx > 0) { // k >= (lower - x0) / cx
                    kxmin = std::max(kxmin, cld(lower - x0, cx));
                } else { // k <= (lower - x0) / cx
                    kxmax = std::min(kxmax, fld(lower - x0, cx));
                }
                if (kxmin > kxmax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        bool set_lower_y(long long lower) {
            if (t == SolutionType::None) return false;
            // y0 + k * cy >= lower
            if (cy == 0) {
                if (y0 < lower) t = SolutionType::None;
            } else {
                if (cy > 0) { // k >= (lower - y0) / cy
                    kymin = std::max(kymin, cld(lower - y0, cy));
                } else { // k <= (lower - y0) / cy
                    kymax = std::min(kymax, fld(lower - y0, cy));
                }
                if (kymin > kymax) t = SolutionType::None;
            }
            return t != SolutionType::None;
        }
        bool set_upper_y(long long upper) {
            if (t == SolutionType::None) return false;
            // y0 + k * cy <= upper
            if (cy == 0) {
                if (y0 > upper) t = SolutionType::None;
            } else {
                if (cy > 0) { // k <= (upper - y0) / cy
                    kymin = std::min(kymin, fld(upper - y0, cy));
                } else { // k >= (upper - y0) / cy
                    kymax = std::max(kymax, cld(upper - y0, cy));
                }
                if (kymin > kymax) t = SolutionType::None;
            }
            return t != SolutionType::None;
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

    struct Equation {
        long long a, b;
        long long x, y, g;

        Equation(long long a, long long b): a(a), b(b) {
            std::tie(x, y, g) = ext_gcd(a, b);
        }

        // solve ax + by = z
        Solution solve(long long z) {
            if (g == 0) {
                if (z != 0) {
                    return Solution::make_none();
                } else {
                    return Solution::make_arbitrary();
                }
            } else {
                if (z % g) {
                    return Solution::make_none();
                } else {
                    z /= g;
                    return Solution::make_linear(x * z, b / g, y * z, -a / g);
                }
            }
        }
    };
} // namespace suisen

#endif // SUISEN_EXT_GCD
