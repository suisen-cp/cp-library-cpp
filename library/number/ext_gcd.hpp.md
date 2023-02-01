---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':heavy_check_mark:'
    path: library/number/garner.hpp
    title: Garner's Algorithm
  - icon: ':warning:'
    path: library/number/index_calculus.hpp
    title: Index Calculus
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cmath>\n#include <limits>\n#include <optional>\n#include <tuple>\n#include\
    \ <utility>\n\nnamespace suisen {\n    constexpr long long safe_mod(long long\
    \ x, long long m) {\n        x %= m;\n        return x < 0 ? x + m : x;\n    }\n\
    \n    // returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long,\
    \ long long, long long> ext_gcd(long long a, long long b) {\n        long long\
    \ x = 1, y = 0;\n        long long z = 0, w = 1;\n        while (b) {\n      \
    \      long long p = a / b, q = a % b;\n            x -= y * p, std::swap(x, y);\n\
    \            z -= w * p, std::swap(z, w);\n            a = b, b = q;\n       \
    \ }\n        if (a < 0) {\n            x = -x, z = -z, a = -a;\n        }\n  \
    \      return { x, z, a };\n    }\n\n    // returns {x,g} s.t. a*x=g (mod m)\n\
    \    std::pair<long long, long long> gcd_inv(long long a, long long m) {\n   \
    \     auto [x, y, g] = ext_gcd(a, m);\n        return { safe_mod(x, m), g };\n\
    \    }\n\n    // returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime\
    \ error.\n    long long inv_mod(long long a, long long mod) {\n        auto [inv,\
    \ y, g] = ext_gcd(a, mod);\n        assert(g == 1);\n        return safe_mod(inv,\
    \ mod);\n    }\n\n    class Solution {\n        enum class SolutionType {\n  \
    \          None, Arbitrary, Linear\n        };\n\n        friend struct Equation;\n\
    \n        static constexpr long long neginf = std::numeric_limits<long long>::min()\
    \ / 2;\n        static constexpr long long posinf = std::numeric_limits<long long>::max()\
    \ / 2;\n\n        SolutionType t;\n        // if t == Linear:\n        //    \
    \  x = x0 + k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax\
    \ and kymin <= k <= kymax)\n        // if t == Arbitrary:\n        //      x =\
    \ x0 + k * cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy =\
    \ l     (kymin <= l <= kymax)\n        // if t == None:\n        //      No solution\n\
    \        long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax =\
    \ posinf;\n        long long kymin = neginf, kymax = posinf;\n\n        Solution(SolutionType\
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
    \  template <typename T>\n        static constexpr T fld(T x, T y) {\n       \
    \     return x / y - ((x ^ y) < 0 and x % y);\n        }\n        template <typename\
    \ T>\n        static constexpr T cld(T x, T y) {\n            return x / y + ((x\
    \ ^ y) >= 0 and x % y);\n        }\n    public:\n        static Solution make_none()\
    \ {\n            return Solution(SolutionType::None);\n        }\n        static\
    \ Solution make_arbitrary() {\n            return Solution(SolutionType::Arbitrary,\
    \ 0, 1, 0, 1);\n        }\n        static Solution make_linear(long long x0, long\
    \ long cx, long long y0, long long cy) {\n            return Solution(SolutionType::Linear,\
    \ x0, cx, y0, cy);\n        }\n\n        bool has_solution() const {\n       \
    \     if (t == SolutionType::None) {\n                return false;\n        \
    \    } else if (t == SolutionType::Arbitrary) {\n                return true;\n\
    \            } else {\n                return get_k_range().has_value();\n   \
    \         }\n        }\n        template <typename T = long long>\n        T count()\
    \ const {\n            if (t == SolutionType::None) {\n                return\
    \ 0;\n            } else if (t == SolutionType::Arbitrary) {\n               \
    \ return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);\n            } else {\n\
    \                auto k_range = get_k_range();\n                if (k_range) {\n\
    \                    return k_range->second - k_range->first + 1;\n          \
    \      } else {\n                    return 0;\n                }\n          \
    \  }\n        }\n\n        // restrict to x <= upper.\n        bool set_upper_x(long\
    \ long upper) {\n            if (t == SolutionType::None) return false;\n    \
    \        // x0 + k * cx <= upper\n            if (cx == 0) {\n               \
    \ if (x0 > upper) t = SolutionType::None;\n            } else {\n            \
    \    if (cx > 0) { // k <= (upper - x0) / cx\n                    kxmin = std::min(kxmin,\
    \ fld(upper - x0, cx));\n                } else { // k >= (upper - x0) / cx\n\
    \                    kxmax = std::max(kxmax, cld(upper - x0, cx));\n         \
    \       }\n                if (kxmin > kxmax) t = SolutionType::None;\n      \
    \      }\n            return t != SolutionType::None;\n        }\n        // restrict\
    \ to x >= lower.\n        bool set_lower_x(long long lower) {\n            if\
    \ (t == SolutionType::None) return false;\n            // x0 + k * cx >= lower\n\
    \            if (cx == 0) {\n                if (x0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cx > 0) { // k >= (lower - x0) / cx\n\
    \                    kxmin = std::max(kxmin, cld(lower - x0, cx));\n         \
    \       } else { // k <= (lower - x0) / cx\n                    kxmax = std::min(kxmax,\
    \ fld(lower - x0, cx));\n                }\n                if (kxmin > kxmax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_lower_y(long long lower) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy >= lower\n   \
    \         if (cy == 0) {\n                if (y0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k >= (lower - y0) / cy\n\
    \                    kymin = std::max(kymin, cld(lower - y0, cy));\n         \
    \       } else { // k <= (lower - y0) / cy\n                    kymax = std::min(kymax,\
    \ fld(lower - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_upper_y(long long upper) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy <= upper\n   \
    \         if (cy == 0) {\n                if (y0 > upper) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k <= (upper - y0) / cy\n\
    \                    kymin = std::min(kymin, fld(upper - y0, cy));\n         \
    \       } else { // k >= (upper - y0) / cy\n                    kymax = std::max(kymax,\
    \ cld(upper - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n\n        std::pair<long long, long long> xmin_solution() const {\n\
    \            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cx == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cx >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> xmax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cx == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cx <= 0 ? kl : kr);\n    \
    \        }\n        }\n        std::pair<long long, long long> ymin_solution()\
    \ const {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cy == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cy >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> ymax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cy == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cy <= 0 ? kl : kr);\n    \
    \        }\n        }\n    };\n\n    struct Equation {\n        long long a, b;\n\
    \        long long x, y, g;\n\n        Equation(long long a, long long b): a(a),\
    \ b(b) {\n            std::tie(x, y, g) = ext_gcd(a, b);\n        }\n\n      \
    \  // solve ax + by = z\n        Solution solve(long long z) {\n            if\
    \ (g == 0) {\n                if (z != 0) {\n                    return Solution::make_none();\n\
    \                } else {\n                    return Solution::make_arbitrary();\n\
    \                }\n            } else {\n                if (z % g) {\n     \
    \               return Solution::make_none();\n                } else {\n    \
    \                z /= g;\n                    return Solution::make_linear(x *\
    \ z, b / g, y * z, -a / g);\n                }\n            }\n        }\n   \
    \ };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_EXT_GCD\n#define SUISEN_EXT_GCD\n\n#include <cassert>\n#include\
    \ <cmath>\n#include <limits>\n#include <optional>\n#include <tuple>\n#include\
    \ <utility>\n\nnamespace suisen {\n    constexpr long long safe_mod(long long\
    \ x, long long m) {\n        x %= m;\n        return x < 0 ? x + m : x;\n    }\n\
    \n    // returns {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long,\
    \ long long, long long> ext_gcd(long long a, long long b) {\n        long long\
    \ x = 1, y = 0;\n        long long z = 0, w = 1;\n        while (b) {\n      \
    \      long long p = a / b, q = a % b;\n            x -= y * p, std::swap(x, y);\n\
    \            z -= w * p, std::swap(z, w);\n            a = b, b = q;\n       \
    \ }\n        if (a < 0) {\n            x = -x, z = -z, a = -a;\n        }\n  \
    \      return { x, z, a };\n    }\n\n    // returns {x,g} s.t. a*x=g (mod m)\n\
    \    std::pair<long long, long long> gcd_inv(long long a, long long m) {\n   \
    \     auto [x, y, g] = ext_gcd(a, m);\n        return { safe_mod(x, m), g };\n\
    \    }\n\n    // returns x s.t. a*x=1 (mod m) if exists, otherwise throws runtime\
    \ error.\n    long long inv_mod(long long a, long long mod) {\n        auto [inv,\
    \ y, g] = ext_gcd(a, mod);\n        assert(g == 1);\n        return safe_mod(inv,\
    \ mod);\n    }\n\n    class Solution {\n        enum class SolutionType {\n  \
    \          None, Arbitrary, Linear\n        };\n\n        friend struct Equation;\n\
    \n        static constexpr long long neginf = std::numeric_limits<long long>::min()\
    \ / 2;\n        static constexpr long long posinf = std::numeric_limits<long long>::max()\
    \ / 2;\n\n        SolutionType t;\n        // if t == Linear:\n        //    \
    \  x = x0 + k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax\
    \ and kymin <= k <= kymax)\n        // if t == Arbitrary:\n        //      x =\
    \ x0 + k * cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy =\
    \ l     (kymin <= l <= kymax)\n        // if t == None:\n        //      No solution\n\
    \        long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax =\
    \ posinf;\n        long long kymin = neginf, kymax = posinf;\n\n        Solution(SolutionType\
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
    \  template <typename T>\n        static constexpr T fld(T x, T y) {\n       \
    \     return x / y - ((x ^ y) < 0 and x % y);\n        }\n        template <typename\
    \ T>\n        static constexpr T cld(T x, T y) {\n            return x / y + ((x\
    \ ^ y) >= 0 and x % y);\n        }\n    public:\n        static Solution make_none()\
    \ {\n            return Solution(SolutionType::None);\n        }\n        static\
    \ Solution make_arbitrary() {\n            return Solution(SolutionType::Arbitrary,\
    \ 0, 1, 0, 1);\n        }\n        static Solution make_linear(long long x0, long\
    \ long cx, long long y0, long long cy) {\n            return Solution(SolutionType::Linear,\
    \ x0, cx, y0, cy);\n        }\n\n        bool has_solution() const {\n       \
    \     if (t == SolutionType::None) {\n                return false;\n        \
    \    } else if (t == SolutionType::Arbitrary) {\n                return true;\n\
    \            } else {\n                return get_k_range().has_value();\n   \
    \         }\n        }\n        template <typename T = long long>\n        T count()\
    \ const {\n            if (t == SolutionType::None) {\n                return\
    \ 0;\n            } else if (t == SolutionType::Arbitrary) {\n               \
    \ return T(kxmax - kxmin + 1) * T(kymax - kymin + 1);\n            } else {\n\
    \                auto k_range = get_k_range();\n                if (k_range) {\n\
    \                    return k_range->second - k_range->first + 1;\n          \
    \      } else {\n                    return 0;\n                }\n          \
    \  }\n        }\n\n        // restrict to x <= upper.\n        bool set_upper_x(long\
    \ long upper) {\n            if (t == SolutionType::None) return false;\n    \
    \        // x0 + k * cx <= upper\n            if (cx == 0) {\n               \
    \ if (x0 > upper) t = SolutionType::None;\n            } else {\n            \
    \    if (cx > 0) { // k <= (upper - x0) / cx\n                    kxmin = std::min(kxmin,\
    \ fld(upper - x0, cx));\n                } else { // k >= (upper - x0) / cx\n\
    \                    kxmax = std::max(kxmax, cld(upper - x0, cx));\n         \
    \       }\n                if (kxmin > kxmax) t = SolutionType::None;\n      \
    \      }\n            return t != SolutionType::None;\n        }\n        // restrict\
    \ to x >= lower.\n        bool set_lower_x(long long lower) {\n            if\
    \ (t == SolutionType::None) return false;\n            // x0 + k * cx >= lower\n\
    \            if (cx == 0) {\n                if (x0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cx > 0) { // k >= (lower - x0) / cx\n\
    \                    kxmin = std::max(kxmin, cld(lower - x0, cx));\n         \
    \       } else { // k <= (lower - x0) / cx\n                    kxmax = std::min(kxmax,\
    \ fld(lower - x0, cx));\n                }\n                if (kxmin > kxmax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_lower_y(long long lower) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy >= lower\n   \
    \         if (cy == 0) {\n                if (y0 < lower) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k >= (lower - y0) / cy\n\
    \                    kymin = std::max(kymin, cld(lower - y0, cy));\n         \
    \       } else { // k <= (lower - y0) / cy\n                    kymax = std::min(kymax,\
    \ fld(lower - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n        bool set_upper_y(long long upper) {\n            if (t ==\
    \ SolutionType::None) return false;\n            // y0 + k * cy <= upper\n   \
    \         if (cy == 0) {\n                if (y0 > upper) t = SolutionType::None;\n\
    \            } else {\n                if (cy > 0) { // k <= (upper - y0) / cy\n\
    \                    kymin = std::min(kymin, fld(upper - y0, cy));\n         \
    \       } else { // k >= (upper - y0) / cy\n                    kymax = std::max(kymax,\
    \ cld(upper - y0, cy));\n                }\n                if (kymin > kymax)\
    \ t = SolutionType::None;\n            }\n            return t != SolutionType::None;\n\
    \        }\n\n        std::pair<long long, long long> xmin_solution() const {\n\
    \            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cx == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cx >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> xmax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cx == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cx <= 0 ? kl : kr);\n    \
    \        }\n        }\n        std::pair<long long, long long> ymin_solution()\
    \ const {\n            assert(has_solution());\n            if (t == SolutionType::Arbitrary)\
    \ {\n                return { kxmin, kymin };\n            } else {\n        \
    \        auto [kl, kr] = *get_k_range();\n                if (cy == 0) {\n   \
    \                 // avoid overflow\n                    return get_pair(kl !=\
    \ neginf ? kl : kr != posinf ? kr : 0);\n                }\n                return\
    \ get_pair(cy >= 0 ? kl : kr);\n            }\n        }\n        std::pair<long\
    \ long, long long> ymax_solution() const {\n            assert(has_solution());\n\
    \            if (t == SolutionType::Arbitrary) {\n                return { kxmax,\
    \ kymax };\n            } else {\n                auto [kl, kr] = *get_k_range();\n\
    \                if (cy == 0) {\n                    // avoid overflow\n     \
    \               return get_pair(kl != neginf ? kl : kr != posinf ? kr : 0);\n\
    \                }\n                return get_pair(cy <= 0 ? kl : kr);\n    \
    \        }\n        }\n    };\n\n    struct Equation {\n        long long a, b;\n\
    \        long long x, y, g;\n\n        Equation(long long a, long long b): a(a),\
    \ b(b) {\n            std::tie(x, y, g) = ext_gcd(a, b);\n        }\n\n      \
    \  // solve ax + by = z\n        Solution solve(long long z) {\n            if\
    \ (g == 0) {\n                if (z != 0) {\n                    return Solution::make_none();\n\
    \                } else {\n                    return Solution::make_arbitrary();\n\
    \                }\n            } else {\n                if (z % g) {\n     \
    \               return Solution::make_none();\n                } else {\n    \
    \                z /= g;\n                    return Solution::make_linear(x *\
    \ z, b / g, y * z, -a / g);\n                }\n            }\n        }\n   \
    \ };\n} // namespace suisen\n\n#endif // SUISEN_EXT_GCD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/ext_gcd.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/number/garner.hpp
  - library/number/index_calculus.hpp
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
documentation_of: library/number/ext_gcd.hpp
layout: document
title: Ext Gcd
---
## Ext Gcd