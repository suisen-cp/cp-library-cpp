---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/bezout_equation.hpp\"\n\n\n\n#line 1 \"library/number/ext_gcd.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cmath>\n#include <limits>\n#include <optional>\n\
    #include <tuple>\n#include <utility>\n\nnamespace suisen {\n    constexpr long\
    \ long safe_mod(long long x, long long m) {\n        x %= m;\n        return x\
    \ < 0 ? x + m : x;\n    }\n\n    // returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0.\
    \ \n    std::tuple<long long, long long, long long> ext_gcd(long long a, long\
    \ long b) {\n        long long x = 1, y = 0;\n        long long z = 0, w = 1;\n\
    \        while (b) {\n            long long p = a / b, q = a % b;\n          \
    \  x -= y * p, std::swap(x, y);\n            z -= w * p, std::swap(z, w);\n  \
    \          a = b, b = q;\n        }\n        if (a < 0) {\n            x = -x,\
    \ z = -z, a = -a;\n        }\n        return { x, z, a };\n    }\n\n    // returns\
    \ {x,g} s.t. a*x=g (mod m)\n    std::pair<long long, long long> gcd_inv(long long\
    \ a, long long m) {\n        auto [x, y, g] = ext_gcd(a, m);\n        return {\
    \ safe_mod(x, m), g };\n    }\n\n    // returns x s.t. a*x=1 (mod m) if exists,\
    \ otherwise throws runtime error.\n    long long inv_mod(long long a, long long\
    \ mod) {\n        auto [inv, y, g] = ext_gcd(a, mod);\n        assert(g == 1);\n\
    \        return safe_mod(inv, mod);\n    }\n} // namespace suisen\n\n\n#line 5\
    \ \"library/number/bezout_equation.hpp\"\n\nnamespace suisen {\n    class BezoutEquationSolution\
    \ {\n        enum class SolutionType {\n            None, Arbitrary, Linear\n\
    \        };\n\n        friend struct BezoutEquation;\n\n        static constexpr\
    \ long long neginf = std::numeric_limits<long long>::min() / 2;\n        static\
    \ constexpr long long posinf = std::numeric_limits<long long>::max() / 2;\n\n\
    \        SolutionType t;\n        // if t == Linear:\n        //      x = x0 +\
    \ k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax and kymin\
    \ <= k <= kymax)\n        // if t == Arbitrary:\n        //      x = x0 + k *\
    \ cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy = l     (kymin\
    \ <= l <= kymax)\n        // if t == None:\n        //      No solution\n    \
    \    long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax = posinf;\n\
    \        long long kymin = neginf, kymax = posinf;\n\n        BezoutEquationSolution(SolutionType\
    \ t, long long x0 = 0, long long cx = 0, long long y0 = 0, long long cy = 0) :\
    \ t(t), x0(x0), cx(cx), y0(y0), cy(cy) {}\n\n        long long get_x(long long\
    \ k) const {\n            return x0 + k * cx;\n        }\n        long long get_y(long\
    \ long k) const {\n            return y0 + k * cy;\n        }\n        std::pair<long\
    \ long, long long> get_pair(long long k) const {\n            return { get_x(k),\
    \ get_y(k) };\n        }\n\n        std::optional<std::pair<long long, long long>>\
    \ get_k_range() const {\n            long long kmin = std::max(kxmin, kymin);\n\
    \            long long kmax = std::min(kxmax, kymax);\n            if (kmin <=\
    \ kmax) {\n                return std::pair{ kmin, kmax };\n            } else\
    \ {\n                return std::nullopt;\n            }\n        }\n\n      \
    \  template <class T>\n        static constexpr T fld(const T x, const T y) {\
    \ T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }\n        template\
    \ <class T>\n        static constexpr T cld(const T x, const T y) { T q = x /\
    \ y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }\n    public:\n      \
    \  static BezoutEquationSolution make_none() {\n            return BezoutEquationSolution(SolutionType::None);\n\
    \        }\n        static BezoutEquationSolution make_arbitrary() {\n       \
    \     return BezoutEquationSolution(SolutionType::Arbitrary, 0, 1, 0, 1);\n  \
    \      }\n        static BezoutEquationSolution make_linear(long long x0, long\
    \ long cx, long long y0, long long cy) {\n            return BezoutEquationSolution(SolutionType::Linear,\
    \ x0, cx, y0, cy);\n        }\n\n        bool has_solution() const {\n       \
    \     if (t == SolutionType::None) {\n                return false;\n        \
    \    } else if (t == SolutionType::Arbitrary) {\n                return true;\n\
    \            } else {\n                return get_k_range().has_value();\n   \
    \         }\n        }\n        template <typename T = long long>\n        std::optional<T>\
    \ count() const {\n            if (t == SolutionType::None) {\n              \
    \  return 0;\n            } else if (t == SolutionType::Arbitrary) {\n       \
    \         return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);\n            } else\
    \ {\n                auto k_range = get_k_range();\n                if (k_range)\
    \ {\n                    if (k_range->first == neginf or k_range->second == posinf)\
    \ return std::nullopt;\n                    return k_range->second - k_range->first\
    \ + 1;\n                } else {\n                    return 0;\n            \
    \    }\n            }\n        }\n\n        // restrict to x >= min_x.\n     \
    \   bool set_min_x(long long min_x) {\n            if (t == SolutionType::None)\
    \ return false;\n            // x0 + k * cx >= min_x\n            if (cx == 0)\
    \ {\n                if (x0 < min_x) t = SolutionType::None;\n            } else\
    \ {\n                if (cx > 0) { // k >= (min_x - x0) / cx\n               \
    \     kxmin = std::max(kxmin, cld(min_x - x0, cx));\n                } else {\
    \ // k <= (min_x - x0) / cx\n                    kxmax = std::min(kxmax, fld(min_x\
    \ - x0, cx));\n                }\n                if (kxmin > kxmax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   // restrict to x <= max_x.\n        bool set_max_x(long long max_x) {\n  \
    \          if (t == SolutionType::None) return false;\n            // x0 + k *\
    \ cx <= max_x\n            if (cx == 0) {\n                if (x0 > max_x) t =\
    \ SolutionType::None;\n            } else {\n                if (cx > 0) { //\
    \ k <= (max_x - x0) / cx\n                    kxmax = std::min(kxmax, fld(max_x\
    \ - x0, cx));\n                } else { // k >= (max_x - x0) / cx\n          \
    \          kxmin = std::max(kxmin, cld(max_x - x0, cx));\n                }\n\
    \                if (kxmin > kxmax) t = SolutionType::None;\n            }\n \
    \           return t != SolutionType::None;\n        }\n        bool set_x_range(long\
    \ long min_x, long long max_x) {\n            return set_min_x(min_x) and set_max_x(max_x);\n\
    \        }\n        bool set_min_y(long long min_y) {\n            if (t == SolutionType::None)\
    \ return false;\n            // y0 + k * cy >= min_y\n            if (cy == 0)\
    \ {\n                if (y0 < min_y) t = SolutionType::None;\n            } else\
    \ {\n                if (cy > 0) { // k >= (min_y - y0) / cy\n               \
    \     kymin = std::max(kymin, cld(min_y - y0, cy));\n                } else {\
    \ // k <= (min_y - y0) / cy\n                    kymax = std::min(kymax, fld(min_y\
    \ - y0, cy));\n                }\n                if (kymin > kymax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   bool set_max_y(long long max_y) {\n            if (t == SolutionType::None)\
    \ return false;\n            // y0 + k * cy <= max_y\n            if (cy == 0)\
    \ {\n                if (y0 > max_y) t = SolutionType::None;\n            } else\
    \ {\n                if (cy > 0) { // k <= (max_y - y0) / cy\n               \
    \     kymax = std::min(kymax, fld(max_y - y0, cy));\n                } else {\
    \ // k >= (max_y - y0) / cy\n                    kymin = std::max(kymin, cld(max_y\
    \ - y0, cy));\n                }\n                if (kymin > kymax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   bool set_y_range(long long min_y, long long max_y) {\n            return set_min_y(min_y)\
    \ and set_max_y(max_y);\n        }\n\n        std::pair<long long, long long>\
    \ xmin_solution() const {\n            assert(has_solution());\n            if\
    \ (t == SolutionType::Arbitrary) {\n                return { kxmin, kymin };\n\
    \            } else {\n                auto [kl, kr] = *get_k_range();\n     \
    \           if (cx == 0) {\n                    // avoid overflow\n          \
    \          return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n     \
    \           }\n                return get_pair(cx >= 0 ? kl : kr);\n         \
    \   }\n        }\n        std::pair<long long, long long> xmax_solution() const\
    \ {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmax, kymax };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cx == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cx <= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> ymin_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmin,\
    \ kymin };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cy == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cy >= 0 ? kl : kr);\n    \
    \        }\n        }\n        std::pair<long long, long long> ymax_solution()\
    \ const {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmax, kymax };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cy == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cy <= 0 ? kl : kr);\n            }\n        }\n    };\n\n    // ax+by=c\n\
    \    struct BezoutEquation {\n        long long a, b;\n        long long x, y,\
    \ g;\n\n        BezoutEquation(long long a, long long b): a(a), b(b) {\n     \
    \       std::tie(x, y, g) = ext_gcd(a, b);\n        }\n\n        // solve ax +\
    \ by = z\n        BezoutEquationSolution solve(long long z) {\n            if\
    \ (g == 0) {\n                if (z != 0) {\n                    return BezoutEquationSolution::make_none();\n\
    \                } else {\n                    return BezoutEquationSolution::make_arbitrary();\n\
    \                }\n            } else {\n                if (z % g) {\n     \
    \               return BezoutEquationSolution::make_none();\n                }\
    \ else {\n                    const long long cx = b / g, cy = -a / g;\n     \
    \               z /= g;\n                    __int128_t x0 = __int128_t(x) * z,\
    \ y0 = __int128_t(y) * z;\n                    __int128_t k0 = -x0 / cx;\n   \
    \                 return BezoutEquationSolution::make_linear(x0 + k0 * cx, cx,\
    \ y0 + k0 * cy, cy);\n                }\n            }\n        }\n    };\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BEZOUT_EQUATION\n#define SUISEN_BEZOUT_EQUATION\n\n#include\
    \ \"library/number/ext_gcd.hpp\"\n\nnamespace suisen {\n    class BezoutEquationSolution\
    \ {\n        enum class SolutionType {\n            None, Arbitrary, Linear\n\
    \        };\n\n        friend struct BezoutEquation;\n\n        static constexpr\
    \ long long neginf = std::numeric_limits<long long>::min() / 2;\n        static\
    \ constexpr long long posinf = std::numeric_limits<long long>::max() / 2;\n\n\
    \        SolutionType t;\n        // if t == Linear:\n        //      x = x0 +\
    \ k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax and kymin\
    \ <= k <= kymax)\n        // if t == Arbitrary:\n        //      x = x0 + k *\
    \ cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy = l     (kymin\
    \ <= l <= kymax)\n        // if t == None:\n        //      No solution\n    \
    \    long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax = posinf;\n\
    \        long long kymin = neginf, kymax = posinf;\n\n        BezoutEquationSolution(SolutionType\
    \ t, long long x0 = 0, long long cx = 0, long long y0 = 0, long long cy = 0) :\
    \ t(t), x0(x0), cx(cx), y0(y0), cy(cy) {}\n\n        long long get_x(long long\
    \ k) const {\n            return x0 + k * cx;\n        }\n        long long get_y(long\
    \ long k) const {\n            return y0 + k * cy;\n        }\n        std::pair<long\
    \ long, long long> get_pair(long long k) const {\n            return { get_x(k),\
    \ get_y(k) };\n        }\n\n        std::optional<std::pair<long long, long long>>\
    \ get_k_range() const {\n            long long kmin = std::max(kxmin, kymin);\n\
    \            long long kmax = std::min(kxmax, kymax);\n            if (kmin <=\
    \ kmax) {\n                return std::pair{ kmin, kmax };\n            } else\
    \ {\n                return std::nullopt;\n            }\n        }\n\n      \
    \  template <class T>\n        static constexpr T fld(const T x, const T y) {\
    \ T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }\n        template\
    \ <class T>\n        static constexpr T cld(const T x, const T y) { T q = x /\
    \ y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }\n    public:\n      \
    \  static BezoutEquationSolution make_none() {\n            return BezoutEquationSolution(SolutionType::None);\n\
    \        }\n        static BezoutEquationSolution make_arbitrary() {\n       \
    \     return BezoutEquationSolution(SolutionType::Arbitrary, 0, 1, 0, 1);\n  \
    \      }\n        static BezoutEquationSolution make_linear(long long x0, long\
    \ long cx, long long y0, long long cy) {\n            return BezoutEquationSolution(SolutionType::Linear,\
    \ x0, cx, y0, cy);\n        }\n\n        bool has_solution() const {\n       \
    \     if (t == SolutionType::None) {\n                return false;\n        \
    \    } else if (t == SolutionType::Arbitrary) {\n                return true;\n\
    \            } else {\n                return get_k_range().has_value();\n   \
    \         }\n        }\n        template <typename T = long long>\n        std::optional<T>\
    \ count() const {\n            if (t == SolutionType::None) {\n              \
    \  return 0;\n            } else if (t == SolutionType::Arbitrary) {\n       \
    \         return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);\n            } else\
    \ {\n                auto k_range = get_k_range();\n                if (k_range)\
    \ {\n                    if (k_range->first == neginf or k_range->second == posinf)\
    \ return std::nullopt;\n                    return k_range->second - k_range->first\
    \ + 1;\n                } else {\n                    return 0;\n            \
    \    }\n            }\n        }\n\n        // restrict to x >= min_x.\n     \
    \   bool set_min_x(long long min_x) {\n            if (t == SolutionType::None)\
    \ return false;\n            // x0 + k * cx >= min_x\n            if (cx == 0)\
    \ {\n                if (x0 < min_x) t = SolutionType::None;\n            } else\
    \ {\n                if (cx > 0) { // k >= (min_x - x0) / cx\n               \
    \     kxmin = std::max(kxmin, cld(min_x - x0, cx));\n                } else {\
    \ // k <= (min_x - x0) / cx\n                    kxmax = std::min(kxmax, fld(min_x\
    \ - x0, cx));\n                }\n                if (kxmin > kxmax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   // restrict to x <= max_x.\n        bool set_max_x(long long max_x) {\n  \
    \          if (t == SolutionType::None) return false;\n            // x0 + k *\
    \ cx <= max_x\n            if (cx == 0) {\n                if (x0 > max_x) t =\
    \ SolutionType::None;\n            } else {\n                if (cx > 0) { //\
    \ k <= (max_x - x0) / cx\n                    kxmax = std::min(kxmax, fld(max_x\
    \ - x0, cx));\n                } else { // k >= (max_x - x0) / cx\n          \
    \          kxmin = std::max(kxmin, cld(max_x - x0, cx));\n                }\n\
    \                if (kxmin > kxmax) t = SolutionType::None;\n            }\n \
    \           return t != SolutionType::None;\n        }\n        bool set_x_range(long\
    \ long min_x, long long max_x) {\n            return set_min_x(min_x) and set_max_x(max_x);\n\
    \        }\n        bool set_min_y(long long min_y) {\n            if (t == SolutionType::None)\
    \ return false;\n            // y0 + k * cy >= min_y\n            if (cy == 0)\
    \ {\n                if (y0 < min_y) t = SolutionType::None;\n            } else\
    \ {\n                if (cy > 0) { // k >= (min_y - y0) / cy\n               \
    \     kymin = std::max(kymin, cld(min_y - y0, cy));\n                } else {\
    \ // k <= (min_y - y0) / cy\n                    kymax = std::min(kymax, fld(min_y\
    \ - y0, cy));\n                }\n                if (kymin > kymax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   bool set_max_y(long long max_y) {\n            if (t == SolutionType::None)\
    \ return false;\n            // y0 + k * cy <= max_y\n            if (cy == 0)\
    \ {\n                if (y0 > max_y) t = SolutionType::None;\n            } else\
    \ {\n                if (cy > 0) { // k <= (max_y - y0) / cy\n               \
    \     kymax = std::min(kymax, fld(max_y - y0, cy));\n                } else {\
    \ // k >= (max_y - y0) / cy\n                    kymin = std::max(kymin, cld(max_y\
    \ - y0, cy));\n                }\n                if (kymin > kymax) t = SolutionType::None;\n\
    \            }\n            return t != SolutionType::None;\n        }\n     \
    \   bool set_y_range(long long min_y, long long max_y) {\n            return set_min_y(min_y)\
    \ and set_max_y(max_y);\n        }\n\n        std::pair<long long, long long>\
    \ xmin_solution() const {\n            assert(has_solution());\n            if\
    \ (t == SolutionType::Arbitrary) {\n                return { kxmin, kymin };\n\
    \            } else {\n                auto [kl, kr] = *get_k_range();\n     \
    \           if (cx == 0) {\n                    // avoid overflow\n          \
    \          return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n     \
    \           }\n                return get_pair(cx >= 0 ? kl : kr);\n         \
    \   }\n        }\n        std::pair<long long, long long> xmax_solution() const\
    \ {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmax, kymax };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cx == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cx <= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> ymin_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmin,\
    \ kymin };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cy == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cy >= 0 ? kl : kr);\n    \
    \        }\n        }\n        std::pair<long long, long long> ymax_solution()\
    \ const {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmax, kymax };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cy == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cy <= 0 ? kl : kr);\n            }\n        }\n    };\n\n    // ax+by=c\n\
    \    struct BezoutEquation {\n        long long a, b;\n        long long x, y,\
    \ g;\n\n        BezoutEquation(long long a, long long b): a(a), b(b) {\n     \
    \       std::tie(x, y, g) = ext_gcd(a, b);\n        }\n\n        // solve ax +\
    \ by = z\n        BezoutEquationSolution solve(long long z) {\n            if\
    \ (g == 0) {\n                if (z != 0) {\n                    return BezoutEquationSolution::make_none();\n\
    \                } else {\n                    return BezoutEquationSolution::make_arbitrary();\n\
    \                }\n            } else {\n                if (z % g) {\n     \
    \               return BezoutEquationSolution::make_none();\n                }\
    \ else {\n                    const long long cx = b / g, cy = -a / g;\n     \
    \               z /= g;\n                    __int128_t x0 = __int128_t(x) * z,\
    \ y0 = __int128_t(y) * z;\n                    __int128_t k0 = -x0 / cx;\n   \
    \                 return BezoutEquationSolution::make_linear(x0 + k0 * cx, cx,\
    \ y0 + k0 * cy, cy);\n                }\n            }\n        }\n    };\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_BEZOUT_EQUATION\n"
  dependsOn:
  - library/number/ext_gcd.hpp
  isVerificationFile: false
  path: library/number/bezout_equation.hpp
  requiredBy: []
  timestamp: '2023-09-06 20:35:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/bezout_equation.hpp
layout: document
title: Bezout Equation
---
## Bezout Equation
