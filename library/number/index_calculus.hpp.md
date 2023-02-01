---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/index_calculus.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cmath>\n#include <optional>\n\n#line 1 \"library/number/ext_gcd.hpp\"\
    \n\n\n\n#include <cassert>\n#line 6 \"library/number/ext_gcd.hpp\"\n#include <limits>\n\
    #line 8 \"library/number/ext_gcd.hpp\"\n#include <tuple>\n#include <utility>\n\
    \nnamespace suisen {\n    constexpr long long safe_mod(long long x, long long\
    \ m) {\n        x %= m;\n        return x < 0 ? x + m : x;\n    }\n\n    // returns\
    \ {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long, long long, long\
    \ long> ext_gcd(long long a, long long b) {\n        long long x = 1, y = 0;\n\
    \        long long z = 0, w = 1;\n        while (b) {\n            long long p\
    \ = a / b, q = a % b;\n            x -= y * p, std::swap(x, y);\n            z\
    \ -= w * p, std::swap(z, w);\n            a = b, b = q;\n        }\n        if\
    \ (a < 0) {\n            x = -x, z = -z, a = -a;\n        }\n        return {\
    \ x, z, a };\n    }\n\n    // returns {x,g} s.t. a*x=g (mod m)\n    std::pair<long\
    \ long, long long> gcd_inv(long long a, long long m) {\n        auto [x, y, g]\
    \ = ext_gcd(a, m);\n        return { safe_mod(x, m), g };\n    }\n\n    // returns\
    \ x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.\n    long long\
    \ inv_mod(long long a, long long mod) {\n        auto [inv, y, g] = ext_gcd(a,\
    \ mod);\n        assert(g == 1);\n        return safe_mod(inv, mod);\n    }\n\n\
    \    class Solution {\n        enum class SolutionType {\n            None, Arbitrary,\
    \ Linear\n        };\n\n        friend struct Equation;\n\n        static constexpr\
    \ long long neginf = std::numeric_limits<long long>::min() / 2;\n        static\
    \ constexpr long long posinf = std::numeric_limits<long long>::max() / 2;\n\n\
    \        SolutionType t;\n        // if t == Linear:\n        //      x = x0 +\
    \ k * cx,\n        //      y = y0 + k * cy         (kxmin <= k <= kxmax and kymin\
    \ <= k <= kymax)\n        // if t == Arbitrary:\n        //      x = x0 + k *\
    \ cx = k,    (kxmin <= k <= kxmax)\n        //      y = y0 + l * cy = l     (kymin\
    \ <= l <= kymax)\n        // if t == None:\n        //      No solution\n    \
    \    long long x0, cx, y0, cy;\n        long long kxmin = neginf, kxmax = posinf;\n\
    \        long long kymin = neginf, kymax = posinf;\n\n        Solution(SolutionType\
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
    \ };\n} // namespace suisen\n\n\n#line 1 \"library/number/sieve_of_eratosthenes.hpp\"\
    \n\n\n\n#line 6 \"library/number/sieve_of_eratosthenes.hpp\"\n#include <vector>\n\
    \n#line 1 \"library/number/internal_eratosthenes.hpp\"\n\n\n\n#include <cstdint>\n\
    #line 6 \"library/number/internal_eratosthenes.hpp\"\n\nnamespace suisen::internal::sieve\
    \ {\n\nconstexpr std::uint8_t K = 8;\nconstexpr std::uint8_t PROD = 2 * 3 * 5;\n\
    constexpr std::uint8_t RM[K] = { 1,  7, 11, 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t\
    \ DR[K] = { 6,  4,  2,  4,  2,  4,  6,  2 };\nconstexpr std::uint8_t DF[K][K]\
    \ = {\n    { 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2,\
    \ 0, 2, 0, 2, 2, 1 }, { 3, 1, 1, 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3,\
    \ 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2,\
    \ 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t DRP[K] = { 48, 32, 16, 32, 16,\
    \ 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K] = {\n    {  0,  0,  0,  0, \
    \ 0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8,  8 },\n    { 16, 16,  0, 16,\
    \  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,  8 },\n    { 24, 24,  8, 16,\
    \  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,  8 },\n    { 40, 24,  8, 32,\
    \  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,  8 },\n};\n\nconstexpr std::uint8_t\
    \ MASK[K][K] = {\n    { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02,\
    \ 0x20, 0x10, 0x01, 0x80, 0x08, 0x04, 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02,\
    \ 0x80, 0x08, 0x20 }, { 0x08, 0x01, 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n  \
    \  { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40, 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02,\
    \ 0x40, 0x01, 0x10, 0x04 },\n    { 0x40, 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02\
    \ }, { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t\
    \ OFFSET[K][K] = {\n    { 0, 1, 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3,\
    \ 2, 6, },\n    { 2, 4, 0, 6, 1, 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n\
    \    { 4, 7, 1, 2, 5, 6, 0, 3, },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6,\
    \ 2, 3, 7, 0, 4, 5, 1, },\n    { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t\
    \ mask_to_index(const std::uint8_t bits) {\n    switch (bits) {\n        case\
    \ 1 << 0: return 0;\n        case 1 << 1: return 1;\n        case 1 << 2: return\
    \ 2;\n        case 1 << 3: return 3;\n        case 1 << 4: return 4;\n       \
    \ case 1 << 5: return 5;\n        case 1 << 6: return 6;\n        case 1 << 7:\
    \ return 7;\n        default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\
    \n\n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
    \ntemplate <unsigned int N>\nclass SimpleSieve {\n    private:\n        static\
    \ constexpr unsigned int siz = N / internal::sieve::PROD + 1;\n        static\
    \ std::uint8_t flag[siz];\n    public:\n        SimpleSieve() {\n            using\
    \ namespace internal::sieve;\n            flag[0] |= 1;\n            unsigned\
    \ int k_max = (unsigned int) std::sqrt(N + 2) / PROD;\n            for (unsigned\
    \ int kp = 0; kp <= k_max; ++kp) {\n                for (std::uint8_t bits = ~flag[kp];\
    \ bits; bits &= bits - 1) {\n                    const std::uint8_t mp = mask_to_index(bits\
    \ & -bits), m = RM[mp];\n                    unsigned int kr = kp * (PROD * kp\
    \ + 2 * m) + m * m / PROD;\n                    for (std::uint8_t mq = mp; kr\
    \ < siz; kr += kp * DR[mq] + DF[mp][mq], ++mq &= 7) {\n                      \
    \  flag[kr] |= MASK[mp][mq];\n                    }\n                }\n     \
    \       }\n        }\n        std::vector<int> prime_list(unsigned int max_val\
    \ = N) const {\n            using namespace internal::sieve;\n            std::vector<int>\
    \ res { 2, 3, 5 };\n            res.reserve(max_val / 25);\n            for (unsigned\
    \ int i = 0, offset = 0; i < siz and offset < max_val; ++i, offset += PROD) {\n\
    \                for (uint8_t f = ~flag[i]; f;) {\n                    uint8_t\
    \ g = f & -f;\n                    res.push_back(offset + RM[mask_to_index(g)]);\n\
    \                    f ^= g;\n                }\n            }\n            while\
    \ (res.size() and (unsigned int) res.back() > max_val) res.pop_back();\n     \
    \       return res;\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return ((flag[p / PROD] >> 0) & 1) == 0;\n                        case RM[1]:\
    \ return ((flag[p / PROD] >> 1) & 1) == 0;\n                        case RM[2]:\
    \ return ((flag[p / PROD] >> 2) & 1) == 0;\n                        case RM[3]:\
    \ return ((flag[p / PROD] >> 3) & 1) == 0;\n                        case RM[4]:\
    \ return ((flag[p / PROD] >> 4) & 1) == 0;\n                        case RM[5]:\
    \ return ((flag[p / PROD] >> 5) & 1) == 0;\n                        case RM[6]:\
    \ return ((flag[p / PROD] >> 6) & 1) == 0;\n                        case RM[7]:\
    \ return ((flag[p / PROD] >> 7) & 1) == 0;\n                        default: return\
    \ false;\n                    }\n            }\n        }\n};\ntemplate <unsigned\
    \ int N>\nstd::uint8_t SimpleSieve<N>::flag[SimpleSieve<N>::siz];\n\ntemplate\
    \ <unsigned int N>\nclass Sieve {\n    private:\n        static constexpr unsigned\
    \ int base_max = (N + 1) * internal::sieve::K / internal::sieve::PROD;\n     \
    \   static unsigned int pf[base_max + internal::sieve::K];\n\n    public:\n  \
    \      Sieve() {\n            using namespace internal::sieve;\n            pf[0]\
    \ = 1;\n            unsigned int k_max = ((unsigned int) std::sqrt(N + 1) - 1)\
    \ / PROD;\n            for (unsigned int kp = 0; kp <= k_max; ++kp) {\n      \
    \          const int base_i = kp * K, base_act_i = kp * PROD;\n              \
    \  for (int mp = 0; mp < K; ++mp) {\n                    const int m = RM[mp],\
    \ i = base_i + mp;\n                    if (pf[i] == 0) {\n                  \
    \      unsigned int act_i = base_act_i + m;\n                        unsigned\
    \ int base_k = (kp * (PROD * kp + 2 * m) + m * m / PROD) * K;\n              \
    \          for (std::uint8_t mq = mp; base_k <= base_max; base_k += kp * DRP[mq]\
    \ + DFP[mp][mq], ++mq &= 7) {\n                            pf[base_k + OFFSET[mp][mq]]\
    \ = act_i;\n                        }\n                    }\n               \
    \ }\n            }\n        }\n        bool is_prime(const unsigned int p) const\
    \ {\n            using namespace internal::sieve;\n            switch (p) {\n\
    \                case 2: case 3: case 5: return true;\n                default:\n\
    \                    switch (p % PROD) {\n                        case RM[0]:\
    \ return pf[p / PROD * K + 0] == 0;\n                        case RM[1]: return\
    \ pf[p / PROD * K + 1] == 0;\n                        case RM[2]: return pf[p\
    \ / PROD * K + 2] == 0;\n                        case RM[3]: return pf[p / PROD\
    \ * K + 3] == 0;\n                        case RM[4]: return pf[p / PROD * K +\
    \ 4] == 0;\n                        case RM[5]: return pf[p / PROD * K + 5] ==\
    \ 0;\n                        case RM[6]: return pf[p / PROD * K + 6] == 0;\n\
    \                        case RM[7]: return pf[p / PROD * K + 7] == 0;\n     \
    \                   default: return false;\n                    }\n          \
    \  }\n        }\n        int prime_factor(const unsigned int p) const {\n    \
    \        using namespace internal::sieve;\n            switch (p % PROD) {\n \
    \               case  0: case  2: case  4: case  6: case  8:\n               \
    \ case 10: case 12: case 14: case 16: case 18:\n                case 20: case\
    \ 22: case 24: case 26: case 28: return 2;\n                case  3: case  9:\
    \ case 15: case 21: case 27: return 3;\n                case  5: case 25: return\
    \ 5;\n                case RM[0]: return pf[p / PROD * K + 0] ? pf[p / PROD *\
    \ K + 0] : p;\n                case RM[1]: return pf[p / PROD * K + 1] ? pf[p\
    \ / PROD * K + 1] : p;\n                case RM[2]: return pf[p / PROD * K + 2]\
    \ ? pf[p / PROD * K + 2] : p;\n                case RM[3]: return pf[p / PROD\
    \ * K + 3] ? pf[p / PROD * K + 3] : p;\n                case RM[4]: return pf[p\
    \ / PROD * K + 4] ? pf[p / PROD * K + 4] : p;\n                case RM[5]: return\
    \ pf[p / PROD * K + 5] ? pf[p / PROD * K + 5] : p;\n                case RM[6]:\
    \ return pf[p / PROD * K + 6] ? pf[p / PROD * K + 6] : p;\n                case\
    \ RM[7]: return pf[p / PROD * K + 7] ? pf[p / PROD * K + 7] : p;\n           \
    \     default: assert(false);\n            }\n        }\n        /**\n       \
    \  * Returns a vector of `{ prime, index }`.\n         */\n        std::vector<std::pair<int,\
    \ int>> factorize(unsigned int n) const {\n            assert(0 < n and n <= N);\n\
    \            std::vector<std::pair<int, int>> prime_powers;\n            while\
    \ (n > 1) {\n                int p = prime_factor(n), c = 0;\n               \
    \ do { n /= p, ++c; } while (n % p == 0);\n                prime_powers.emplace_back(p,\
    \ c);\n            }\n            return prime_powers;\n        }\n        /**\n\
    \         * Returns the divisors of `n`.\n         * It is NOT guaranteed that\
    \ the returned vector is sorted.\n         */\n        std::vector<int> divisors(unsigned\
    \ int n) const {\n            assert(0 < n and n <= N);\n            std::vector<int>\
    \ divs { 1 };\n            for (auto [prime, index] : factorize(n)) {\n      \
    \          int sz = divs.size();\n                for (int i = 0; i < sz; ++i)\
    \ {\n                    int d = divs[i];\n                    for (int j = 0;\
    \ j < index; ++j) {\n                        divs.push_back(d *= prime);\n   \
    \                 }\n                }\n            }\n            return divs;\n\
    \        }\n};\ntemplate <unsigned int N>\nunsigned int Sieve<N>::pf[Sieve<N>::base_max\
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 10 \"library/number/index_calculus.hpp\"\
    \n\nnamespace suisen {\n    struct IndexCalculus {\n    private:\n        using\
    \ mint_p = atcoder::dynamic_modint<1000000001>;\n        using mint_pm1 = atcoder::dynamic_modint<1000000002>;\n\
    \n        using row = std::pair<std::vector<std::pair<int, mint_pm1>>, mint_pm1>;\n\
    \n        static constexpr int L = 1000000;\n        static inline Sieve<L> sieve{};\n\
    \    public:\n        IndexCalculus(int p, int g) : _p(p), _alpha(g), _b(bound(p)),\
    \ _ps(primes(_b)), _l(_ps.size()), _es(_l, 0), _ps_inv(_b + 1) {\n           \
    \ for (int i = 0; i < int(_ps.size()); ++i) {\n                _ps_inv[_ps[i]]\
    \ = i;\n            }\n        }\n\n        int operator()(int beta) {\n     \
    \       beta %= _p;\n            if (_p == 2) {\n                if (beta == 0)\
    \ return -1;\n                return 0;\n            }\n            return with_modint_context(\n\
    \                [&, this]() -> int {\n                    if (beta == 0) return\
    \ -1;\n                    const int inv_beta = mint_p(beta).inv().val();\n\n\
    \                    auto find_index = [](const row& r, int col) {\n         \
    \               auto find_col_cmp = [](const std::pair<int, mint_pm1>& cell, int\
    \ v) { return cell.first < v; };\n                        const int idx = std::lower_bound(r.first.begin(),\
    \ r.first.end(), col, find_col_cmp) - r.first.begin();\n                     \
    \   return idx == int(r.first.size()) or r.first[idx].first != col ? -1 : idx;\n\
    \                    };\n\n                    auto up = [&, this](std::vector<row>\
    \ &mat) {\n                        std::vector<row> nmat;\n                  \
    \      int ans = -1;\n                        for (int i = mat.size() - 1; i >=\
    \ 0; --i) {\n                            row eq;\n                           \
    \ eq.second = mat[i].second;\n                            for (auto [j, val] :\
    \ mat[i].first) {\n                                if (j < _l and _es[j] != 0)\
    \ {\n                                    eq.second -= _es[j] * val;\n        \
    \                        } else {\n                                    eq.first.emplace_back(j,\
    \ val);\n                                }\n                            }\n  \
    \                          if (eq.first.size() == 1) {\n                     \
    \           auto [j, val] = eq.first.front();\n                              \
    \  auto rhs = eq.second;\n                                const int d = std::gcd(_p\
    \ - 1, val.val());\n                                if (d != 1) continue;\n  \
    \                              assert(rhs.val() % d == 0);\n                 \
    \               const int q = (_p - 1) / d;\n                                auto\
    \ log_pj = gcd_inv(val.val() / d, q).first * (rhs.val() / d) % q;\n          \
    \                      if (j == _l) {\n                                    ans\
    \ = log_pj;\n                                } else {\n                      \
    \              _es[j] = log_pj;\n                                }\n         \
    \                   } else {\n                                nmat.emplace_back(std::move(eq));\n\
    \                            }\n                        }\n                  \
    \      nmat.swap(mat);\n                        return ans;\n                \
    \    };\n\n                    std::vector<row> mat(_l + 1);\n\n             \
    \       for (int i = 0; i < _l + 1; ++i) {\n                        mat[i] = gen_equation(inv_beta);\n\
    \                    }\n                    for (int i = 0; i < int(mat.size());\
    \ ++i) {\n                        int j = _l + 1;\n                        int\
    \ pivot = -1;\n\n                        for (int i2 = i; i2 < int(mat.size());\
    \ ++i2) {\n                            int j2 = mat[i2].first.front().first;\n\
    \                            if (j2 < j) j = j2, pivot = i2;\n               \
    \         }\n                        std::swap(mat[pivot], mat[i]);\n        \
    \                for (int i2 = i + 1; i2 < int(mat.size()); ++i2) {\n        \
    \                    int idx = find_index(mat[i2], j);\n                     \
    \       if (idx < 0) continue;\n                            assert(mat[i].first[0].first\
    \ == j);\n                            mint_pm1 val = mat[i].first[0].second;\n\
    \                            eliminate(val, mat[i], mat[i2].first[idx].second,\
    \ mat[i2]);\n                            if (mat[i2].first.empty()) {\n      \
    \                          assert(mat[i2].second == 0);\n                    \
    \            std::swap(mat[i2], mat.back());\n                               \
    \ mat.pop_back();\n                                --i2;\n                   \
    \         } else {\n                                assert(mat[i2].first[0].first\
    \ > j);\n                            }\n                        }\n          \
    \          }\n                    if (const int ans = up(mat); ans >= 0) return\
    \ ans;\n\n                    while (true) {\n                        const int\
    \ row_num = mat.size();\n\n                        row r = gen_equation(inv_beta);\n\
    \n                        bool inserted = false;\n                        for\
    \ (int i = 0; i < row_num; ++i) {\n                            if (r.first.empty())\
    \ break;\n                            auto [j, val] = mat[i].first.front();\n\
    \                            if (r.first[0].first < j) {\n                   \
    \             mat.insert(mat.begin() + i, r);\n                              \
    \  inserted = true;\n                                break;\n                \
    \            }\n                            const int idx = find_index(r, j);\n\
    \                            if (idx < 0) continue;\n                        \
    \    eliminate(val, mat[i], r.first[idx].second, r);\n                       \
    \ }\n                        if (not inserted) {\n                           \
    \ if (r.first.size()) {\n                                mat.emplace_back(r);\n\
    \                            } else {\n                                continue;\n\
    \                            }\n                        }\n                  \
    \      if (const int ans = up(mat); ans >= 0) return ans;\n                  \
    \  }\n                }\n            );\n        }\n\n    private:\n        int\
    \ _p, _alpha, _b;\n\n        std::vector<int> _ps;\n        int _l;\n        std::vector<int>\
    \ _es;\n\n        std::vector<int> _ps_inv;\n\n        template <typename F>\n\
    \        std::invoke_result_t<F> with_modint_context(F&& f) {\n            const\
    \ int old_mod_p = mint_p::mod();\n            const int old_mod_pm1 = mint_pm1::mod();\n\
    \            mint_p::set_mod(_p);\n            mint_pm1::set_mod(_p - 1);\n  \
    \          std::invoke_result_t<F> res = f();\n            mint_p::set_mod(old_mod_p);\n\
    \            mint_pm1::set_mod(old_mod_pm1);\n            return res;\n      \
    \  }\n\n        row gen_equation(int inv_beta) const {\n            static std::mt19937_64\
    \ rng{ std::random_device{}() };\n            while (true) {\n               \
    \ int k = rng() % (_p - 1) + 1;\n                auto opt_fac = try_factorize((mint_p(_alpha).pow(k)\
    \ * inv_beta).val());\n                if (not opt_fac.has_value()) continue;\n\
    \                mint_pm1 rhs = k;\n                std::vector<std::pair<int,\
    \ mint_pm1>> lhs;\n                for (auto [i, c] : *opt_fac) {\n          \
    \          if (_es[i] != 0) {\n                        rhs -= c * _es[i];\n  \
    \                  } else {\n                        lhs.emplace_back(i, c);\n\
    \                    }\n                }\n                lhs.emplace_back(_l,\
    \ 1);\n                return { lhs, rhs };\n            }\n        }\n\n    \
    \    std::optional<std::vector<std::pair<int, int>>> try_factorize(int v) const\
    \ {\n            std::vector<std::pair<int, int>> res;\n            const int\
    \ num_p = _ps.size();\n            for (int i = 0; i < num_p; ++i) {\n       \
    \         // if ((i == 10 and v > L)) return std::nullopt;\n                if\
    \ (v < L) {\n                    const int max_p = _ps.back();\n             \
    \       for (auto [p, c] : sieve.factorize(v)) {\n                        if (p\
    \ > max_p) return std::nullopt;\n                        res.emplace_back(_ps_inv[p],\
    \ c);\n                    }\n                    std::sort(res.begin(), res.end());\n\
    \                    return res;\n                }\n                if (v % _ps[i]\
    \ == 0) {\n                    int q = 0;\n                    do {\n        \
    \                v /= _ps[i];\n                        ++q;\n                \
    \    } while (v % _ps[i] == 0);\n                    res.emplace_back(i, q);\n\
    \                }\n            }\n            if (v != 1) return std::nullopt;\n\
    \            return res;\n        }\n\n        static int bound(int p) {\n   \
    \         // return ::exp(::sqrt(std::max(0., ::log(p) * ::log(::log(p)))) / 2)\
    \ + 1;\n            return 200;\n        }\n        static std::vector<int> primes(int\
    \ b) {\n            std::vector<int> ps;\n            std::vector<int8_t> sieve(b\
    \ + 1, true);\n            for (int p = 2; p <= b; ++p) {\n                if\
    \ (not sieve[p]) continue;\n                ps.push_back(p);\n               \
    \ for (int q = p * p; q <= b; q += p) sieve[q] = false;\n            }\n     \
    \       return ps;\n        }\n\n        static row add(const mint_pm1 c1, const\
    \ row& r1, const mint_pm1 c2, const row& r2) {\n            row res;\n       \
    \     const int s1 = r1.first.size(), s2 = r2.first.size();\n            for (int\
    \ i = 0, j = 0; i < s1 or j < s2;) {\n                const int idx1 = i == s1\
    \ ? std::numeric_limits<int>::max() : r1.first[i].first;\n                const\
    \ int idx2 = j == s2 ? std::numeric_limits<int>::max() : r2.first[j].first;\n\
    \                int idx;\n                mint_pm1 val;\n                if (idx1\
    \ < idx2) {\n                    idx = idx1;\n                    val = c1 * r1.first[i++].second;\n\
    \                } else if (idx2 < idx1) {\n                    idx = idx2;\n\
    \                    val = c2 * r2.first[j++].second;\n                } else\
    \ {\n                    idx = idx1;\n                    val = c1 * r1.first[i++].second\
    \ + c2 * r2.first[j++].second;\n                }\n                if (val !=\
    \ 0) {\n                    res.first.emplace_back(idx, val);\n              \
    \  }\n            }\n            res.second = c1 * r1.second + c2 * r2.second;\n\
    \            return res;\n        }\n\n        static void eliminate(mint_pm1\
    \ &t1, row& r1, mint_pm1 t2, row& r2) {\n            for (; t2 != 0;) {\n    \
    \            if (t1.val() > t2.val()) {\n                    std::swap(r1, r2);\n\
    \                    std::swap(t1, t2);\n                }\n                const\
    \ int q = t2.val() / t1.val();\n                r2 = add(1, r2, -q, r1);\n   \
    \             t2 -= t1 * q;\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n"
  code: "#ifndef SUISEN_INDEX_CALCULUS\n#define SUISEN_INDEX_CALCULUS\n\n#include\
    \ <algorithm>\n#include <cmath>\n#include <optional>\n\n#include \"library/number/ext_gcd.hpp\"\
    \n#include \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
    \    struct IndexCalculus {\n    private:\n        using mint_p = atcoder::dynamic_modint<1000000001>;\n\
    \        using mint_pm1 = atcoder::dynamic_modint<1000000002>;\n\n        using\
    \ row = std::pair<std::vector<std::pair<int, mint_pm1>>, mint_pm1>;\n\n      \
    \  static constexpr int L = 1000000;\n        static inline Sieve<L> sieve{};\n\
    \    public:\n        IndexCalculus(int p, int g) : _p(p), _alpha(g), _b(bound(p)),\
    \ _ps(primes(_b)), _l(_ps.size()), _es(_l, 0), _ps_inv(_b + 1) {\n           \
    \ for (int i = 0; i < int(_ps.size()); ++i) {\n                _ps_inv[_ps[i]]\
    \ = i;\n            }\n        }\n\n        int operator()(int beta) {\n     \
    \       beta %= _p;\n            if (_p == 2) {\n                if (beta == 0)\
    \ return -1;\n                return 0;\n            }\n            return with_modint_context(\n\
    \                [&, this]() -> int {\n                    if (beta == 0) return\
    \ -1;\n                    const int inv_beta = mint_p(beta).inv().val();\n\n\
    \                    auto find_index = [](const row& r, int col) {\n         \
    \               auto find_col_cmp = [](const std::pair<int, mint_pm1>& cell, int\
    \ v) { return cell.first < v; };\n                        const int idx = std::lower_bound(r.first.begin(),\
    \ r.first.end(), col, find_col_cmp) - r.first.begin();\n                     \
    \   return idx == int(r.first.size()) or r.first[idx].first != col ? -1 : idx;\n\
    \                    };\n\n                    auto up = [&, this](std::vector<row>\
    \ &mat) {\n                        std::vector<row> nmat;\n                  \
    \      int ans = -1;\n                        for (int i = mat.size() - 1; i >=\
    \ 0; --i) {\n                            row eq;\n                           \
    \ eq.second = mat[i].second;\n                            for (auto [j, val] :\
    \ mat[i].first) {\n                                if (j < _l and _es[j] != 0)\
    \ {\n                                    eq.second -= _es[j] * val;\n        \
    \                        } else {\n                                    eq.first.emplace_back(j,\
    \ val);\n                                }\n                            }\n  \
    \                          if (eq.first.size() == 1) {\n                     \
    \           auto [j, val] = eq.first.front();\n                              \
    \  auto rhs = eq.second;\n                                const int d = std::gcd(_p\
    \ - 1, val.val());\n                                if (d != 1) continue;\n  \
    \                              assert(rhs.val() % d == 0);\n                 \
    \               const int q = (_p - 1) / d;\n                                auto\
    \ log_pj = gcd_inv(val.val() / d, q).first * (rhs.val() / d) % q;\n          \
    \                      if (j == _l) {\n                                    ans\
    \ = log_pj;\n                                } else {\n                      \
    \              _es[j] = log_pj;\n                                }\n         \
    \                   } else {\n                                nmat.emplace_back(std::move(eq));\n\
    \                            }\n                        }\n                  \
    \      nmat.swap(mat);\n                        return ans;\n                \
    \    };\n\n                    std::vector<row> mat(_l + 1);\n\n             \
    \       for (int i = 0; i < _l + 1; ++i) {\n                        mat[i] = gen_equation(inv_beta);\n\
    \                    }\n                    for (int i = 0; i < int(mat.size());\
    \ ++i) {\n                        int j = _l + 1;\n                        int\
    \ pivot = -1;\n\n                        for (int i2 = i; i2 < int(mat.size());\
    \ ++i2) {\n                            int j2 = mat[i2].first.front().first;\n\
    \                            if (j2 < j) j = j2, pivot = i2;\n               \
    \         }\n                        std::swap(mat[pivot], mat[i]);\n        \
    \                for (int i2 = i + 1; i2 < int(mat.size()); ++i2) {\n        \
    \                    int idx = find_index(mat[i2], j);\n                     \
    \       if (idx < 0) continue;\n                            assert(mat[i].first[0].first\
    \ == j);\n                            mint_pm1 val = mat[i].first[0].second;\n\
    \                            eliminate(val, mat[i], mat[i2].first[idx].second,\
    \ mat[i2]);\n                            if (mat[i2].first.empty()) {\n      \
    \                          assert(mat[i2].second == 0);\n                    \
    \            std::swap(mat[i2], mat.back());\n                               \
    \ mat.pop_back();\n                                --i2;\n                   \
    \         } else {\n                                assert(mat[i2].first[0].first\
    \ > j);\n                            }\n                        }\n          \
    \          }\n                    if (const int ans = up(mat); ans >= 0) return\
    \ ans;\n\n                    while (true) {\n                        const int\
    \ row_num = mat.size();\n\n                        row r = gen_equation(inv_beta);\n\
    \n                        bool inserted = false;\n                        for\
    \ (int i = 0; i < row_num; ++i) {\n                            if (r.first.empty())\
    \ break;\n                            auto [j, val] = mat[i].first.front();\n\
    \                            if (r.first[0].first < j) {\n                   \
    \             mat.insert(mat.begin() + i, r);\n                              \
    \  inserted = true;\n                                break;\n                \
    \            }\n                            const int idx = find_index(r, j);\n\
    \                            if (idx < 0) continue;\n                        \
    \    eliminate(val, mat[i], r.first[idx].second, r);\n                       \
    \ }\n                        if (not inserted) {\n                           \
    \ if (r.first.size()) {\n                                mat.emplace_back(r);\n\
    \                            } else {\n                                continue;\n\
    \                            }\n                        }\n                  \
    \      if (const int ans = up(mat); ans >= 0) return ans;\n                  \
    \  }\n                }\n            );\n        }\n\n    private:\n        int\
    \ _p, _alpha, _b;\n\n        std::vector<int> _ps;\n        int _l;\n        std::vector<int>\
    \ _es;\n\n        std::vector<int> _ps_inv;\n\n        template <typename F>\n\
    \        std::invoke_result_t<F> with_modint_context(F&& f) {\n            const\
    \ int old_mod_p = mint_p::mod();\n            const int old_mod_pm1 = mint_pm1::mod();\n\
    \            mint_p::set_mod(_p);\n            mint_pm1::set_mod(_p - 1);\n  \
    \          std::invoke_result_t<F> res = f();\n            mint_p::set_mod(old_mod_p);\n\
    \            mint_pm1::set_mod(old_mod_pm1);\n            return res;\n      \
    \  }\n\n        row gen_equation(int inv_beta) const {\n            static std::mt19937_64\
    \ rng{ std::random_device{}() };\n            while (true) {\n               \
    \ int k = rng() % (_p - 1) + 1;\n                auto opt_fac = try_factorize((mint_p(_alpha).pow(k)\
    \ * inv_beta).val());\n                if (not opt_fac.has_value()) continue;\n\
    \                mint_pm1 rhs = k;\n                std::vector<std::pair<int,\
    \ mint_pm1>> lhs;\n                for (auto [i, c] : *opt_fac) {\n          \
    \          if (_es[i] != 0) {\n                        rhs -= c * _es[i];\n  \
    \                  } else {\n                        lhs.emplace_back(i, c);\n\
    \                    }\n                }\n                lhs.emplace_back(_l,\
    \ 1);\n                return { lhs, rhs };\n            }\n        }\n\n    \
    \    std::optional<std::vector<std::pair<int, int>>> try_factorize(int v) const\
    \ {\n            std::vector<std::pair<int, int>> res;\n            const int\
    \ num_p = _ps.size();\n            for (int i = 0; i < num_p; ++i) {\n       \
    \         // if ((i == 10 and v > L)) return std::nullopt;\n                if\
    \ (v < L) {\n                    const int max_p = _ps.back();\n             \
    \       for (auto [p, c] : sieve.factorize(v)) {\n                        if (p\
    \ > max_p) return std::nullopt;\n                        res.emplace_back(_ps_inv[p],\
    \ c);\n                    }\n                    std::sort(res.begin(), res.end());\n\
    \                    return res;\n                }\n                if (v % _ps[i]\
    \ == 0) {\n                    int q = 0;\n                    do {\n        \
    \                v /= _ps[i];\n                        ++q;\n                \
    \    } while (v % _ps[i] == 0);\n                    res.emplace_back(i, q);\n\
    \                }\n            }\n            if (v != 1) return std::nullopt;\n\
    \            return res;\n        }\n\n        static int bound(int p) {\n   \
    \         // return ::exp(::sqrt(std::max(0., ::log(p) * ::log(::log(p)))) / 2)\
    \ + 1;\n            return 200;\n        }\n        static std::vector<int> primes(int\
    \ b) {\n            std::vector<int> ps;\n            std::vector<int8_t> sieve(b\
    \ + 1, true);\n            for (int p = 2; p <= b; ++p) {\n                if\
    \ (not sieve[p]) continue;\n                ps.push_back(p);\n               \
    \ for (int q = p * p; q <= b; q += p) sieve[q] = false;\n            }\n     \
    \       return ps;\n        }\n\n        static row add(const mint_pm1 c1, const\
    \ row& r1, const mint_pm1 c2, const row& r2) {\n            row res;\n       \
    \     const int s1 = r1.first.size(), s2 = r2.first.size();\n            for (int\
    \ i = 0, j = 0; i < s1 or j < s2;) {\n                const int idx1 = i == s1\
    \ ? std::numeric_limits<int>::max() : r1.first[i].first;\n                const\
    \ int idx2 = j == s2 ? std::numeric_limits<int>::max() : r2.first[j].first;\n\
    \                int idx;\n                mint_pm1 val;\n                if (idx1\
    \ < idx2) {\n                    idx = idx1;\n                    val = c1 * r1.first[i++].second;\n\
    \                } else if (idx2 < idx1) {\n                    idx = idx2;\n\
    \                    val = c2 * r2.first[j++].second;\n                } else\
    \ {\n                    idx = idx1;\n                    val = c1 * r1.first[i++].second\
    \ + c2 * r2.first[j++].second;\n                }\n                if (val !=\
    \ 0) {\n                    res.first.emplace_back(idx, val);\n              \
    \  }\n            }\n            res.second = c1 * r1.second + c2 * r2.second;\n\
    \            return res;\n        }\n\n        static void eliminate(mint_pm1\
    \ &t1, row& r1, mint_pm1 t2, row& r2) {\n            for (; t2 != 0;) {\n    \
    \            if (t1.val() > t2.val()) {\n                    std::swap(r1, r2);\n\
    \                    std::swap(t1, t2);\n                }\n                const\
    \ int q = t2.val() / t1.val();\n                r2 = add(1, r2, -q, r1);\n   \
    \             t2 -= t1 * q;\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_INDEX_CALCULUS\n"
  dependsOn:
  - library/number/ext_gcd.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  isVerificationFile: false
  path: library/number/index_calculus.hpp
  requiredBy: []
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/index_calculus.hpp
layout: document
title: Index Calculus
---
## Index Calculus