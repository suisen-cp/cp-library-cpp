---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/arbitrary_mod_convolution.hpp
    title: "\u4EFB\u610F $\\mathrm{mod}$ \u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':heavy_check_mark:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':heavy_check_mark:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
  - icon: ':heavy_check_mark:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: library/number/garner.hpp
    title: Garner's Algorithm
  - icon: ':heavy_check_mark:'
    path: library/number/internal_eratosthenes.hpp
    title: Internal Eratosthenes
  - icon: ':heavy_check_mark:'
    path: library/number/montogomery.hpp
    title: Montogomery
  - icon: ':heavy_check_mark:'
    path: library/number/order_Z_mZ.hpp
    title: Order of $x \in (\mathbb{Z}/m\mathbb{Z}) ^ \ast$
  - icon: ':heavy_check_mark:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: library/number/sieve_of_eratosthenes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9"
  - icon: ':heavy_check_mark:'
    path: library/transform/chirp_z_transform.hpp
    title: "chirp z-transform (\u8A55\u4FA1\u70B9\u304C\u7B49\u5DEE\u6570\u5217\u3092\
      \u6210\u3059\u5834\u5408\u306E Multipoint Evaluation)"
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n\
    \n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/convolution/multi_variate_convolution_circular.hpp\"\n\n\n\
    \n#line 5 \"library/convolution/multi_variate_convolution_circular.hpp\"\n\n#line\
    \ 1 \"library/transform/chirp_z_transform.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\n#include <atcoder/convolution>\n\n/**\n * @brief chirp z-transform\
    \ ($g _ k = f(a r^k)$)\n*/\n\nnamespace suisen {\n    namespace internal {\n \
    \       const auto default_convolution = [](const auto& a, const auto& b) { return\
    \ atcoder::convolution(a, b); };\n\n        template <typename T>\n        std::vector<T>\
    \ chirp_z_transform_naive(const std::vector<T> &f, T a, T r, int m) {\n      \
    \      const int n = f.size();\n            std::vector<T> g(m);\n           \
    \ T pow_r = 1;\n            for (int k = 0; k < m; ++k) {\n                T ark\
    \ = a * pow_r, pow_ark = 1;\n                for (int i = 0; i < n; ++i) {\n \
    \                   g[k] += f[i] * pow_ark;\n                    pow_ark *= ark;\n\
    \                }\n                pow_r *= r;\n            }\n            return\
    \ g;\n        }\n    } // namespace internal\n    /**\n     * @brief Calculates\
    \ f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m) time\n     */\n    template <typename\
    \ T, typename Convolution>\n    std::vector<T> chirp_z_transform(std::vector<T>\
    \ f, T a, T r, int m, Convolution&& convolution = internal::default_convolution)\
    \ {\n        const int n = f.size();\n        std::vector<T> g(m);\n        if\
    \ (n == 0 or m == 0) return g;\n        T pow_a = 1;\n        for (int i = 0;\
    \ i < n; ++i, pow_a *= a) f[i] *= pow_a;\n        if (r == 0) {\n            for\
    \ (int i = 0; i < n; ++i) g[0] += f[i];\n            for (int k = 1; k < m; ++k)\
    \ g[k] += f[0];\n            return g;\n        }\n        if (n < 60) return\
    \ internal::chirp_z_transform_naive(f, a, r, m);\n        const T r_inv = r.inv();\n\
    \n        const int l = n + m - 1;\n\n        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);\n\
    \        pow_r_tri[0] = pow_r_tri_inv[0] = 1;\n\n        T pow_r = 1, pow_r_inv\
    \ = 1;\n        for (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= r_inv) {\n\
    \            pow_r_tri[i] = pow_r_tri[i - 1] * pow_r;\n            pow_r_tri_inv[i]\
    \ = pow_r_tri_inv[i - 1] * pow_r_inv;\n        }\n\n        std::vector<T> p(n),\
    \ q(l);\n        for (int i = 0; i < n; ++i) p[i] = f[i] * pow_r_tri_inv[i];\n\
    \        for (int i = 0; i < l; ++i) q[i] = pow_r_tri[i];\n        std::reverse(p.begin(),\
    \ p.end());\n        std::vector<T> pq = convolution(p, q);\n        for (int\
    \ k = 0; k < m; ++k) {\n            g[k] = pow_r_tri_inv[k] * pq[n - 1 + k];\n\
    \        }\n\n        return g;\n    }\n} // namespace suisen\n\n\n\n#line 1 \"\
    library/convolution/arbitrary_mod_convolution.hpp\"\n\n\n\n#line 6 \"library/convolution/arbitrary_mod_convolution.hpp\"\
    \n\n#line 1 \"library/convolution/convolution_naive.hpp\"\n\n\n\n#line 5 \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen::internal {\n    template <typename T, typename R = T>\n\
    \    std::vector<R> convolution_naive(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\n        const int n = a.size(), m = b.size();\n        std::vector<R>\
    \ c(n + m - 1);\n        if (n < m) {\n            for (int j = 0; j < m; j++)\
    \ for (int i = 0; i < n; i++) c[i + j] += R(a[i]) * b[j];\n        } else {\n\
    \            for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j]\
    \ += R(a[i]) * b[j];\n        }\n        return c;\n    }\n} // namespace suisen\n\
    \n\n\n#line 8 \"library/convolution/arbitrary_mod_convolution.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename mint, atcoder::internal::is_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> arbitrary_mod_convolution(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        int n = int(a.size()), m = int(b.size());\n\
    \n        if constexpr (atcoder::internal::is_static_modint<mint>::value) {\n\
    \            if constexpr (not (mint::mod() & 63)) {\n                int maxz\
    \ = 1;\n                while (not ((mint::mod() - 1) & maxz)) maxz <<= 1;\n \
    \               int z = 1;\n                while (z < n + m - 1) z <<= 1;\n \
    \               if (z <= maxz) return atcoder::convolution<mint>(a, b);\n    \
    \        }\n        }\n\n        if (n == 0 or m == 0) return {};\n        if\
    \ (std::min(n, m) <= 120) return internal::convolution_naive(a, b);\n\n      \
    \  static constexpr long long MOD1 = 754974721;  // 2^24\n        static constexpr\
    \ long long MOD2 = 167772161;  // 2^25\n        static constexpr long long MOD3\
    \ = 469762049;  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n\
    \        static constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1,\
    \ MOD2).second;\n        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        std::vector<int> a2(n), b2(m);\n        for (int i\
    \ = 0; i < n; ++i) a2[i] = a[i].val();\n        for (int i = 0; i < m; ++i) b2[i]\
    \ = b[i].val();\n\n        auto c1 = atcoder::convolution<MOD1>(a2, b2);\n   \
    \     auto c2 = atcoder::convolution<MOD2>(a2, b2);\n        auto c3 = atcoder::convolution<MOD3>(a2,\
    \ b2);\n\n        const long long m1m2 = mint(M1M2).val();\n        std::vector<mint>\
    \ c(n + m - 1);\n        for (int i = 0; i < n + m - 1; ++i) {\n            //\
    \ Garner's Algorithm\n            // X = x1 + x2 * m1 + x3 * m1 * m2\n       \
    \     // x1 = c1[i], x2 = (c2[i] - x1) / m1 (mod m2), x3 = (c3[i] - x1 - x2 *\
    \ m1) / m2 (mod m3)\n            long long x1 = c1[i];\n            long long\
    \ x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n     \
    \       long long x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + x3 * m1m2;\n    \
    \    }\n        return c;\n    }\n\n    std::vector<__uint128_t> convolution_int(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n        int n = int(a.size()),\
    \ m = int(b.size());\n\n        auto check_nonnegative = [](int e) { return e\
    \ >= 0; };\n        assert(std::all_of(a.begin(), a.end(), check_nonnegative));\n\
    \        assert(std::all_of(b.begin(), b.end(), check_nonnegative));\n\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 120) return\
    \ internal::convolution_naive<int, __uint128_t>(a, b);\n\n        static constexpr\
    \ long long MOD1 = 754974721;  // 2^24\n        static constexpr long long MOD2\
    \ = 167772161;  // 2^25\n        static constexpr long long MOD3 = 469762049;\
    \  // 2^26\n        static constexpr long long M1M2 = MOD1 * MOD2;\n        static\
    \ constexpr long long INV_M1_MOD2 = atcoder::internal::inv_gcd(MOD1, MOD2).second;\n\
    \        static constexpr long long INV_M1M2_MOD3 = atcoder::internal::inv_gcd(M1M2,\
    \ MOD3).second;\n\n        auto c1 = atcoder::convolution<MOD1>(a, b);\n     \
    \   auto c2 = atcoder::convolution<MOD2>(a, b);\n        auto c3 = atcoder::convolution<MOD3>(a,\
    \ b);\n        std::vector<__uint128_t> c(n + m - 1);\n        for (int i = 0;\
    \ i < n + m - 1; ++i) {\n            // Garner's Algorithm\n            // X =\
    \ x1 + x2 * m1 + x3 * m1 * m2\n            // x1 = c1[i], x2 = (c2[i] - x1) /\
    \ m1 (mod m2), x3 = (c3[i] - x1 - x2 * m1) / m2 (mod m3)\n            int x1 =\
    \ c1[i];\n            int x2 = (atcoder::static_modint<MOD2>(c2[i] - x1) * INV_M1_MOD2).val();\n\
    \            int x3 = (atcoder::static_modint<MOD3>(c3[i] - x1 - x2 * MOD1) *\
    \ INV_M1M2_MOD3).val();\n            c[i] = x1 + x2 * MOD1 + __uint128_t(x3) *\
    \ M1M2;\n        }\n        return c;\n    }\n} // namespace suisen\n\n\n\n#line\
    \ 8 \"library/convolution/multi_variate_convolution_circular.hpp\"\n\n#line 1\
    \ \"library/number/deterministic_miller_rabin.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <cstdint>\n#include <iterator>\n#include <tuple>\n\
    #include <type_traits>\n\n#line 1 \"library/number/montogomery.hpp\"\n\n\n\n#line\
    \ 6 \"library/number/montogomery.hpp\"\n#include <limits>\n\nnamespace suisen\
    \ {\n    namespace internal::montgomery {\n        template <typename Int, typename\
    \ DInt>\n        struct Montgomery {\n        private:\n            static constexpr\
    \ uint32_t bits = std::numeric_limits<Int>::digits;\n            static constexpr\
    \ Int mask = ~Int(0);\n            // R = 2**32 or 2**64\n\n            // 1.\
    \ N is an odd number\n            // 2. N < R\n            // 3. gcd(N, R) = 1\n\
    \            // 4. R * R2 - N * N2 = 1\n            // 5. 0 < R2 < N\n       \
    \     // 6. 0 < N2 < R\n            Int N, N2, R2;\n\n            // RR = R *\
    \ R (mod N)\n            Int RR;\n        public:\n            constexpr Montgomery()\
    \ = default;\n            explicit constexpr Montgomery(Int N) : N(N), N2(calcN2(N)),\
    \ R2(calcR2(N, N2)), RR(calcRR(N)) {\n                assert(N & 1);\n       \
    \     }\n\n            // @returns t * R (mod N)\n            constexpr Int make(Int\
    \ t) const {\n                return reduce(static_cast<DInt>(t) * RR);\n    \
    \        }\n            // @returns T * R^(-1) (mod N)\n            constexpr\
    \ Int reduce(DInt T) const {\n                // 0 <= T < RN\n\n             \
    \   // Note:\n                //  1. m = T * N2 (mod R)\n                //  2.\
    \ 0 <= m < R\n                DInt m = modR(static_cast<DInt>(modR(T)) * N2);\n\
    \n                // Note:\n                //  T + m * N = T + T * N * N2 = T\
    \ + T * (R * R2 - 1) = 0 (mod R)\n                //  => (T + m * N) / R is an\
    \ integer.\n                //  => t * R = T + m * N = T (mod N)\n           \
    \     //  => t = T R^(-1) (mod N)\n                DInt t = divR(T + m * N);\n\
    \n                // Note:\n                //  1. 0 <= T < RN\n             \
    \   //  2. 0 <= mN < RN (because 0 <= m < R)\n                //  => 0 <= T +\
    \ mN < 2RN\n                //  => 0 <= t < 2N\n                return t >= N\
    \ ? t - N : t;\n            }\n\n            constexpr Int add(Int A, Int B) const\
    \ {\n                return (A += B) >= N ? A - N : A;\n            }\n      \
    \      constexpr Int sub(Int A, Int B) const {\n                return (A -= B)\
    \ < 0 ? A + N : A;\n            }\n            constexpr Int mul(Int A, Int B)\
    \ const {\n                return reduce(static_cast<DInt>(A) * B);\n        \
    \    }\n            constexpr Int div(Int A, Int B) const {\n                return\
    \ reduce(static_cast<DInt>(A) * inv(B));\n            }\n            constexpr\
    \ Int inv(Int A) const; // TODO: Implement\n\n            constexpr Int pow(Int\
    \ A, long long b) const {\n                Int P = make(1);\n                for\
    \ (; b; b >>= 1) {\n                    if (b & 1) P = mul(P, A);\n          \
    \          A = mul(A, A);\n                }\n                return P;\n    \
    \        }\n\n        private:\n            static constexpr Int divR(DInt t)\
    \ { return t >> bits; }\n            static constexpr Int modR(DInt t) { return\
    \ t & mask; }\n\n            static constexpr Int calcN2(Int N) {\n          \
    \      // - N * N2 = 1 (mod R)\n                // N2 = -N^{-1} (mod R)\n\n  \
    \              // calculates N^{-1} (mod R) by Newton's method\n             \
    \   DInt invN = N; // = N^{-1} (mod 2^2)\n                for (uint32_t cur_bits\
    \ = 2; cur_bits < bits; cur_bits *= 2) {\n                    // loop invariant:\
    \ invN = N^{-1} (mod 2^cur_bits)\n\n                    // x = a^{-1} mod m =>\
    \ x(2-ax) = a^{-1} mod m^2 because:\n                    //  ax = 1 (mod m)\n\
    \                    //  => (ax-1)^2 = 0 (mod m^2)\n                    //  =>\
    \ 2ax - a^2x^2 = 1 (mod m^2)\n                    //  => a(x(2-ax)) = 1 (mod m^2)\n\
    \                    invN = modR(invN * modR(2 - N * invN));\n               \
    \ }\n                assert(modR(N * invN) == 1);\n\n                return modR(-invN);\n\
    \            }\n            static constexpr Int calcR2(Int N, Int N2) {\n   \
    \             // R * R2 - N * N2 = 1\n                // => R2 = (1 + N * N2)\
    \ / R\n                return divR(1 + static_cast<DInt>(N) * N2);\n         \
    \   }\n            static constexpr Int calcRR(Int N) {\n                return\
    \ -DInt(N) % N;\n            }\n        };\n    } // namespace internal::montgomery\n\
    \    using Montgomery32 = internal::montgomery::Montgomery<uint32_t, uint64_t>;\n\
    \    using Montgomery64 = internal::montgomery::Montgomery<uint64_t, __uint128_t>;\n\
    } // namespace suisen\n\n\n\n#line 12 \"library/number/deterministic_miller_rabin.hpp\"\
    \n\nnamespace suisen::miller_rabin {\n    namespace internal {\n        constexpr\
    \ uint64_t THRESHOLD_1 = 341531ULL;\n        constexpr uint64_t BASE_1[]{ 9345883071009581737ULL\
    \ };\n\n        constexpr uint64_t THRESHOLD_2 = 1050535501ULL;\n        constexpr\
    \ uint64_t BASE_2[]{ 336781006125ULL, 9639812373923155ULL };\n\n        constexpr\
    \ uint64_t THRESHOLD_3 = 350269456337ULL;\n        constexpr uint64_t BASE_3[]{\
    \ 4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL };\n\
    \n        constexpr uint64_t THRESHOLD_4 = 55245642489451ULL;\n        constexpr\
    \ uint64_t BASE_4[]{ 2ULL, 141889084524735ULL, 1199124725622454117ULL, 11096072698276303650ULL\
    \ };\n\n        constexpr uint64_t THRESHOLD_5 = 7999252175582851ULL;\n      \
    \  constexpr uint64_t BASE_5[]{ 2ULL, 4130806001517ULL, 149795463772692060ULL,\
    \ 186635894390467037ULL, 3967304179347715805ULL };\n\n        constexpr uint64_t\
    \ THRESHOLD_6 = 585226005592931977ULL;\n        constexpr uint64_t BASE_6[]{ 2ULL,\
    \ 123635709730000ULL, 9233062284813009ULL, 43835965440333360ULL, 761179012939631437ULL,\
    \ 1263739024124850375ULL };\n\n        constexpr uint64_t BASE_7[]{ 2U, 325U,\
    \ 9375U, 28178U, 450775U, 9780504U, 1795265022U };\n\n        template <auto BASE,\
    \ std::size_t SIZE>\n        constexpr bool miller_rabin(uint64_t n) {\n     \
    \       if (n == 2 or n == 3 or n == 5 or n == 7) return true;\n            if\
    \ (n <= 1 or n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;\n\
    \            if (n < 121) return true;\n\n            const uint32_t s = __builtin_ctzll(n\
    \ - 1); // >= 1\n            const uint64_t d = (n - 1) >> s;\n\n            const\
    \ Montgomery64 mg{ n };\n\n            const uint64_t one = mg.make(1), minus_one\
    \ = mg.make(n - 1);\n\n            for (std::size_t i = 0; i < SIZE; ++i) {\n\
    \                uint64_t a = BASE[i] % n;\n                if (a == 0) continue;\n\
    \                uint64_t Y = mg.pow(mg.make(a), d);\n                if (Y ==\
    \ one) continue;\n                for (uint32_t r = 0;; ++r, Y = mg.mul(Y, Y))\
    \ {\n                    // Y = a^(d 2^r)\n                    if (Y == minus_one)\
    \ break;\n                    if (r == s - 1) return false;\n                }\n\
    \            }\n            return true;\n        }\n    }\n\n    template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n    constexpr\
    \ bool is_prime(T n) {\n        if constexpr (std::is_signed_v<T>) {\n       \
    \     assert(n >= 0);\n        }\n        const std::make_unsigned_t<T> n_unsigned\
    \ = n;\n        assert(n_unsigned <= std::numeric_limits<uint64_t>::max()); //\
    \ n < 2^64\n        using namespace internal;\n        if (n_unsigned < THRESHOLD_1)\
    \ return miller_rabin<BASE_1, 1>(n_unsigned);\n        if (n_unsigned < THRESHOLD_2)\
    \ return miller_rabin<BASE_2, 2>(n_unsigned);\n        if (n_unsigned < THRESHOLD_3)\
    \ return miller_rabin<BASE_3, 3>(n_unsigned);\n        if (n_unsigned < THRESHOLD_4)\
    \ return miller_rabin<BASE_4, 4>(n_unsigned);\n        if (n_unsigned < THRESHOLD_5)\
    \ return miller_rabin<BASE_5, 5>(n_unsigned);\n        if (n_unsigned < THRESHOLD_6)\
    \ return miller_rabin<BASE_6, 6>(n_unsigned);\n        return miller_rabin<BASE_7,\
    \ 7>(n_unsigned);\n    }\n} // namespace suisen::miller_rabin\n\n\n#line 1 \"\
    library/number/primitive_root.hpp\"\n\n\n\n#line 1 \"library/number/order_Z_mZ.hpp\"\
    \n\n\n\n#include <map>\n#line 6 \"library/number/order_Z_mZ.hpp\"\n\n#line 1 \"\
    library/number/fast_factorize.hpp\"\n\n\n\n#include <cmath>\n#line 6 \"library/number/fast_factorize.hpp\"\
    \n#include <random>\n#include <numeric>\n#include <utility>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#line 7 \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\
    \    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 11 \"library/number/fast_factorize.hpp\"\n\n#line\
    \ 1 \"library/number/sieve_of_eratosthenes.hpp\"\n\n\n\n#line 7 \"library/number/sieve_of_eratosthenes.hpp\"\
    \n\n#line 1 \"library/number/internal_eratosthenes.hpp\"\n\n\n\n#line 6 \"library/number/internal_eratosthenes.hpp\"\
    \n\nnamespace suisen::internal::sieve {\n\nconstexpr std::uint8_t K = 8;\nconstexpr\
    \ std::uint8_t PROD = 2 * 3 * 5;\nconstexpr std::uint8_t RM[K] = { 1,  7, 11,\
    \ 13, 17, 19, 23, 29 };\nconstexpr std::uint8_t DR[K] = { 6,  4,  2,  4,  2, \
    \ 4,  6,  2 };\nconstexpr std::uint8_t DF[K][K] = {\n    { 0, 0, 0, 0, 0, 0, 0,\
    \ 1 }, { 1, 1, 1, 0, 1, 1, 1, 1 },\n    { 2, 2, 0, 2, 0, 2, 2, 1 }, { 3, 1, 1,\
    \ 2, 1, 1, 3, 1 },\n    { 3, 3, 1, 2, 1, 3, 3, 1 }, { 4, 2, 2, 2, 2, 2, 4, 1 },\n\
    \    { 5, 3, 1, 4, 1, 3, 5, 1 }, { 6, 4, 2, 4, 2, 4, 6, 1 },\n};\nconstexpr std::uint8_t\
    \ DRP[K] = { 48, 32, 16, 32, 16, 32, 48, 16 };\nconstexpr std::uint8_t DFP[K][K]\
    \ = {\n    {  0,  0,  0,  0,  0,  0,  0,  8 }, {  8,  8,  8,  0,  8,  8,  8, \
    \ 8 },\n    { 16, 16,  0, 16,  0, 16, 16,  8 }, { 24,  8,  8, 16,  8,  8, 24,\
    \  8 },\n    { 24, 24,  8, 16,  8, 24, 24,  8 }, { 32, 16, 16, 16, 16, 16, 32,\
    \  8 },\n    { 40, 24,  8, 32,  8, 24, 40,  8 }, { 48, 32, 16, 32, 16, 32, 48,\
    \  8 },\n};\n\nconstexpr std::uint8_t MASK[K][K] = {\n    { 0x01, 0x02, 0x04,\
    \ 0x08, 0x10, 0x20, 0x40, 0x80 }, { 0x02, 0x20, 0x10, 0x01, 0x80, 0x08, 0x04,\
    \ 0x40 },\n    { 0x04, 0x10, 0x01, 0x40, 0x02, 0x80, 0x08, 0x20 }, { 0x08, 0x01,\
    \ 0x40, 0x20, 0x04, 0x02, 0x80, 0x10 },\n    { 0x10, 0x80, 0x02, 0x04, 0x20, 0x40,\
    \ 0x01, 0x08 }, { 0x20, 0x08, 0x80, 0x02, 0x40, 0x01, 0x10, 0x04 },\n    { 0x40,\
    \ 0x04, 0x08, 0x80, 0x01, 0x10, 0x20, 0x02 }, { 0x80, 0x40, 0x20, 0x10, 0x08,\
    \ 0x04, 0x02, 0x01 },\n};\nconstexpr std::uint8_t OFFSET[K][K] = {\n    { 0, 1,\
    \ 2, 3, 4, 5, 6, 7, },\n    { 1, 5, 4, 0, 7, 3, 2, 6, },\n    { 2, 4, 0, 6, 1,\
    \ 7, 3, 5, },\n    { 3, 0, 6, 5, 2, 1, 7, 4, },\n    { 4, 7, 1, 2, 5, 6, 0, 3,\
    \ },\n    { 5, 3, 7, 1, 6, 0, 4, 2, },\n    { 6, 2, 3, 7, 0, 4, 5, 1, },\n   \
    \ { 7, 6, 5, 4, 3, 2, 1, 0, },\n};\n\nconstexpr std::uint8_t mask_to_index(const\
    \ std::uint8_t bits) {\n    switch (bits) {\n        case 1 << 0: return 0;\n\
    \        case 1 << 1: return 1;\n        case 1 << 2: return 2;\n        case\
    \ 1 << 3: return 3;\n        case 1 << 4: return 4;\n        case 1 << 5: return\
    \ 5;\n        case 1 << 6: return 6;\n        case 1 << 7: return 7;\n       \
    \ default: assert(false);\n    }\n}\n} // namespace suisen::internal::sieve\n\n\
    \n#line 9 \"library/number/sieve_of_eratosthenes.hpp\"\n\nnamespace suisen {\n\
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
    \ + internal::sieve::K];\n} // namespace suisen\n\n\n#line 14 \"library/number/fast_factorize.hpp\"\
    \n\nnamespace suisen::fast_factorize {\n    namespace internal {\n        template\
    \ <typename T>\n        constexpr int floor_log2(T n) {\n            int i = 0;\n\
    \            while (n) n >>= 1, ++i;\n            return i - 1;\n        }\n \
    \       template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t>\
    \ = nullptr>\n        T pollard_rho(const T n) {\n            using M = safely_multipliable_t<T>;\n\
    \            const T m = T(1) << (floor_log2(n) / 5);\n\n            static std::mt19937_64\
    \ rng{std::random_device{}()};\n            std::uniform_int_distribution<T> dist(0,\
    \ n - 1);\n\n            // const Montgomery64 mg{n};\n\n            while (true)\
    \ {\n                T c = dist(rng);\n                auto f = [&](T x) -> T\
    \ { return (M(x) * x + c) % n; };\n                T x, y = 2, ys, q = 1, g =\
    \ 1;\n                for (T r = 1; g == 1; r <<= 1) {\n                    x\
    \ = y;\n                    for (T i = 0; i < r; ++i) y = f(y);\n            \
    \        for (T k = 0; k < r and g == 1; k += m) {\n                        ys\
    \ = y;\n                        for (T i = 0; i < std::min(m, r - k); ++i) y =\
    \ f(y), q = M(q) * (x > y ? x - y : y - x) % n;\n                        g = std::gcd(q,\
    \ n);\n                    }\n                }\n                if (g == n) {\n\
    \                    g = 1;\n                    while (g == 1) ys = f(ys), g\
    \ = std::gcd(x > ys ? x - ys : ys - x, n);\n                }\n              \
    \  if (g < n) {\n                    if (miller_rabin::is_prime(g)) return g;\n\
    \                    if (T d = n / g; miller_rabin::is_prime(d)) return d;\n \
    \                   return pollard_rho(g);\n                }\n            }\n\
    \        }\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    std::vector<std::pair<T, int>> factorize(T n)\
    \ {\n        static constexpr int threshold = 1000000;\n        static Sieve<threshold>\
    \ sieve;\n\n        std::vector<std::pair<T, int>> res;\n        if (n <= threshold)\
    \ {\n            for (auto [p, q] : sieve.factorize(n)) res.emplace_back(p, q);\n\
    \            return res;\n        }\n\n        if ((n & 1) == 0) {\n         \
    \   int q = 0;\n            do ++q, n >>= 1; while ((n & 1) == 0);\n         \
    \   res.emplace_back(2, q);\n        }\n        for (T p = 3; p * p <= n; p +=\
    \ 2) {\n            if (p >= 101 and n >= 1 << 20) {\n                while (n\
    \ > 1) {\n                    if (miller_rabin::is_prime(n)) {\n             \
    \           res.emplace_back(std::exchange(n, 1), 1);\n                    } else\
    \ {\n                        p = internal::pollard_rho(n);\n                 \
    \       int q = 0;\n                        do ++q, n /= p; while (n % p == 0);\n\
    \                        res.emplace_back(p, q);\n                    }\n    \
    \            }\n                break;\n            }\n            if (n % p ==\
    \ 0) {\n                int q = 0;\n                do ++q, n /= p; while (n %\
    \ p == 0);\n                res.emplace_back(p, q);\n            }\n        }\n\
    \        if (n > 1) res.emplace_back(n, 1);\n        return res;\n    }\n} //\
    \ namespace suisen::fast_factorize\n\n\n#line 9 \"library/number/order_Z_mZ.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::order_prime_mod {\n        template\
    \ <int id>\n        struct mint64 {\n            static uint64_t mod() { return\
    \ _mod; }\n            static void set_mod(uint64_t new_mod) { mint64<id>::_mod\
    \ = new_mod; }\n\n            mint64() : _val(0) {}\n            mint64(long long\
    \ val) : _val(safe_mod(val)) {}\n\n            uint64_t val() { return _val; }\n\
    \n            friend mint64& operator*=(mint64& x, const mint64& y) {\n      \
    \          x._val = __uint128_t(x._val) * y._val % _mod;\n                return\
    \ x;\n            }\n            friend mint64 operator*(mint64 x, const mint64&\
    \ y) {\n                x *= y;\n                return x;\n            }\n  \
    \          mint64 pow(long long b) const {\n                assert(b >= 0);\n\
    \                mint64 p = *this, res = 1;\n                for (; b; b >>= 1)\
    \ {\n                    if (b & 1) res *= p;\n                    p *= p;\n \
    \               }\n                return res;\n            }\n        private:\n\
    \            static inline uint64_t _mod;\n            uint64_t _val;\n\n    \
    \        static uint64_t safe_mod(long long val) { return (val %= _mod) < 0 ?\
    \ val + _mod : val; }\n        };\n    }\n\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct OrderMod {\n        using U = std::make_unsigned_t<T>;\n\
    \        OrderMod() = default;\n        OrderMod(T m) : _mod(m) {\n          \
    \  auto factorized = fast_factorize::factorize<T>(_mod);\n            _is_prime\
    \ = factorized.size() == 1;\n            _lambda = _carmichael(factorized);\n\
    \            _phi = _totient(factorized);\n            for (auto [p, q] : fast_factorize::factorize<T>(_lambda))\
    \ {\n                U r = 1;\n                for (int i = 0; i < q; ++i) r *=\
    \ p;\n                _fac_lambda.emplace_back(p, q, r);\n            }\n    \
    \    }\n\n        bool is_primitive_root(U a) const {\n            if (_mod <\
    \ 1ULL << 32) {\n                using mint = atcoder::dynamic_modint<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                bool res = _is_primitive_root_impl<mint>(a);\n              \
    \  mint::set_mod(old_mod);\n                return res;\n            } else {\n\
    \                using mint = internal::order_prime_mod::mint64<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                bool res = _is_primitive_root_impl<mint>(a);\n              \
    \  mint::set_mod(old_mod);\n                return res;\n            }\n     \
    \   }\n\n        T primitive_root() const {\n            assert(_lambda == _phi);\n\
    \            if (_mod < 1ULL << 32) {\n                return _primitive_root_impl<std::mt19937>();\n\
    \            } else {\n                return _primitive_root_impl<std::mt19937_64>();\n\
    \            }\n        }\n\n        T operator()(U a) const {\n            if\
    \ (_mod < 1ULL << 31) {\n                using mint = atcoder::dynamic_modint<1000000000>;\n\
    \                U old_mod = mint::mod();\n                mint::set_mod(_mod);\n\
    \                T res = _order_impl<mint>(a);\n                mint::set_mod(old_mod);\n\
    \                return res;\n            } else {\n                using mint\
    \ = internal::order_prime_mod::mint64<1000000000>;\n                U old_mod\
    \ = mint::mod();\n                mint::set_mod(_mod);\n                T res\
    \ = _order_impl<mint>(a);\n                mint::set_mod(old_mod);\n         \
    \       return res;\n            }\n        }\n\n        T mod() const {\n   \
    \         return _mod;\n        }\n        T totient() const {\n            return\
    \ _phi;\n        }\n        T carmichael() const {\n            return _lambda;\n\
    \        }\n        bool is_prime() const {\n            return _is_prime;\n \
    \       }\n        std::vector<T> carmichael_prime_factors() const {\n       \
    \     std::vector<T> res;\n            for (const auto &e : _fac_lambda) res.push_back(std::get<0>(e));\n\
    \            return res;\n        }\n\n    private:\n        U _mod;\n       \
    \ U _phi;\n        U _lambda;\n        bool _is_prime;\n\n        std::vector<std::tuple<U,\
    \ int, U>> _fac_lambda;\n\n        static T _carmichael(const std::vector<std::pair<T,\
    \ int>>& factorized) {\n            T lambda = 1;\n            for (auto [p, ep]\
    \ : factorized) {\n                T phi = p - 1;\n                int exponent\
    \ = ep - (1 + (p == 2 and ep >= 3));\n                for (int i = 0; i < exponent;\
    \ ++i) phi *= p;\n                lambda = std::lcm(lambda, phi);\n          \
    \  }\n            return lambda;\n        }\n        static T _totient(const std::vector<std::pair<T,\
    \ int>>& factorized) {\n            T t = 1;\n            for (const auto& [p,\
    \ ep] : factorized) {\n                t *= p - 1;\n                for (int i\
    \ = 0; i < ep - 1; ++i) t *= p;\n            }\n            return t;\n      \
    \  }\n\n        template <typename mint>\n        bool _is_primitive_root_impl(U\
    \ a) const {\n            if (_lambda != _phi) return false;\n            if (_mod\
    \ == 2) return a % 2 == 1;\n\n            const int k = _fac_lambda.size();\n\
    \            U x = _lambda;\n            for (const auto& [p, q, pq] : _fac_lambda)\
    \ x /= p;\n\n            mint b = mint(a).pow(x);\n            if (k == 1) return\
    \ b.val() != 1;\n\n            auto dfs = [&](auto dfs, const int l, const int\
    \ r, const mint val) -> bool {\n                const int m = (l + r) >> 1;\n\n\
    \                U lp = 1;\n                for (int i = m; i < r; ++i) lp *=\
    \ std::get<0>(_fac_lambda[i]);\n                mint lval = val.pow(lp);\n   \
    \             if (m - l == 1) {\n                    if (lval.val() == 1) return\
    \ false;\n                } else {\n                    if (not dfs(dfs, l, m,\
    \ lval)) return false;\n                }\n\n                U rp = 1;\n     \
    \           for (int i = l; i < m; ++i) rp *= std::get<0>(_fac_lambda[i]);\n \
    \               mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    if (rval.val() == 1) return false;\n                } else\
    \ {\n                    if (not dfs(dfs, m, r, rval)) return false;\n       \
    \         }\n\n                return true;\n            };\n            return\
    \ dfs(dfs, 0, k, b);\n        }\n\n        template <typename Rng>\n        T\
    \ _primitive_root_impl() const {\n            if (_mod == 2) return 1;\n\n   \
    \         Rng rng{ std::random_device{}() };\n            while (true) {\n   \
    \             U a = rng() % (_mod - 2) + 2;\n                while (not _is_prime\
    \ and std::gcd(a, _mod) != 1) {\n                    a = rng() % (_mod - 2) +\
    \ 2;\n                }\n                if (is_primitive_root(a)) return a;\n\
    \            }\n        }\n\n        template <typename mint>\n        U _order_impl(U\
    \ a) const {\n            if (_mod == 2) return a % 2 == 1;\n\n            const\
    \ int k = _fac_lambda.size();\n\n            U res = 1;\n\n            auto update\
    \ = [&](U p, mint val) {\n                while (val.val() != 1) {\n         \
    \           val = val.pow(p);\n                    res *= p;\n               \
    \ }\n            };\n\n            if (k == 1) {\n                update(std::get<0>(_fac_lambda.front()),\
    \ a);\n                return res;\n            }\n\n            auto dfs = [&](auto\
    \ dfs, const int l, const int r, const mint val) -> void {\n                const\
    \ int m = (l + r) >> 1;\n\n                U lp = 1;\n                for (int\
    \ i = m; i < r; ++i) lp *= std::get<2>(_fac_lambda[i]);\n                mint\
    \ lval = val.pow(lp);\n                if (m - l == 1) {\n                   \
    \ update(std::get<0>(_fac_lambda[l]), lval);\n                } else {\n     \
    \               dfs(dfs, l, m, lval);\n                }\n\n                U\
    \ rp = 1;\n                for (int i = l; i < m; ++i) rp *= std::get<2>(_fac_lambda[i]);\n\
    \                mint rval = val.pow(rp);\n                if (r - m == 1) {\n\
    \                    update(std::get<0>(_fac_lambda[m]), rval);\n            \
    \    } else {\n                    dfs(dfs, m, r, rval);\n                }\n\
    \            };\n            dfs(dfs, 0, k, a);\n\n            return res;\n \
    \       }\n    };\n} // namespace suisen\n\n\n#line 5 \"library/number/primitive_root.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    T primitive_root(T p) {\n        return OrderMod<T>{p}.primitive_root();\n\
    \    }\n} // namespace suisen\n\n\n#line 1 \"library/number/garner.hpp\"\n\n\n\
    \n#line 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#line 7 \"library/number/ext_gcd.hpp\"\
    \n#include <optional>\n#line 10 \"library/number/ext_gcd.hpp\"\n\nnamespace suisen\
    \ {\n    constexpr long long safe_mod(long long x, long long m) {\n        x %=\
    \ m;\n        return x < 0 ? x + m : x;\n    }\n\n    // returns {x,y,g} s.t.\
    \ ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long, long long, long long> ext_gcd(long\
    \ long a, long long b) {\n        long long x = 1, y = 0;\n        long long z\
    \ = 0, w = 1;\n        while (b) {\n            long long p = a / b, q = a % b;\n\
    \            x -= y * p, std::swap(x, y);\n            z -= w * p, std::swap(z,\
    \ w);\n            a = b, b = q;\n        }\n        if (a < 0) {\n          \
    \  x = -x, z = -z, a = -a;\n        }\n        return { x, z, a };\n    }\n\n\
    \    // returns {x,g} s.t. a*x=g (mod m)\n    std::pair<long long, long long>\
    \ gcd_inv(long long a, long long m) {\n        auto [x, y, g] = ext_gcd(a, m);\n\
    \        return { safe_mod(x, m), g };\n    }\n\n    // returns x s.t. a*x=1 (mod\
    \ m) if exists, otherwise throws runtime error.\n    long long inv_mod(long long\
    \ a, long long mod) {\n        auto [inv, y, g] = ext_gcd(a, mod);\n        assert(g\
    \ == 1);\n        return safe_mod(inv, mod);\n    }\n} // namespace suisen\n\n\
    \n#line 6 \"library/number/garner.hpp\"\n\nnamespace suisen {\n    /**\n     *\
    \ @brief Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime each\
    \ other.\n     * @param eq vector of { x_i, m_i }\n     * @return x mod m s.t.\
    \ x = x_i (mod m_i)\n     */\n    int garner(std::vector<std::pair<int, int>>\
    \ eq, int m) {\n        const int n = eq.size();\n        std::vector<long long>\
    \ a(n);\n\n        auto calc_prefix = [&](int i, long long mod) {\n          \
    \  long long res = 0;\n            long long prd = 1;\n            for (int j\
    \ = 0; j < i; ++j) {\n                (res += a[j] * prd) %= mod;\n          \
    \      (prd *= eq[j].second) %= mod;\n            }\n            return res;\n\
    \        };\n    \n        for (int i = 0; i < n; ++i) {\n            auto [xi,\
    \ mi] = eq[i];\n            a[i] = (xi - calc_prefix(i, mi)) % mi;\n         \
    \   if (a[i] < 0) a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n   \
    \             long long mj = eq[j].second;\n                a[i] *= inv_mod(mj,\
    \ mi);\n                a[i] %= mi;\n            }\n        }\n        return\
    \ calc_prefix(n, m);\n    }\n} // namespace suisen\n\n\n\n#line 12 \"library/convolution/multi_variate_convolution_circular.hpp\"\
    \n\nnamespace suisen {\n    namespace internal {\n        template <typename mint,\
    \ std::enable_if_t<atcoder::internal::is_modint<mint>::value, std::nullptr_t>\
    \ = nullptr>\n        struct multi_variate_convolution_circular {\n          \
    \  multi_variate_convolution_circular() = default;\n            multi_variate_convolution_circular(std::vector<int>\
    \ n) : _d(n.size()), _l(std::reduce(n.begin(), n.end(), 1, std::multiplies<int>())),\
    \ _n(n), _g(_d), _ig(_d) {\n                assert(miller_rabin::is_prime(mint::mod()));\n\
    \                mint g = primitive_root(mint::mod());\n                for (int\
    \ i = 0; i < _d; ++i) {\n                    assert((mint::mod() - 1) % n[i] ==\
    \ 0);\n                    _g[i] = g.pow((mint::mod() - 1) / n[i]);\n        \
    \            _ig[i] = _g[i].inv();\n                }\n            }\n\n     \
    \       std::vector<mint> convolution(std::vector<mint> f, std::vector<mint> g)\
    \ {\n                fft(f, false), fft(g, false);\n                for (int i\
    \ = 0; i < _l; ++i) f[i] *= g[i];\n                fft(f, true);\n           \
    \     return f;\n            }\n            std::vector<mint> operator()(const\
    \ std::vector<mint>& f, const std::vector<mint>& g) {\n                return\
    \ convolution(f, g);\n            }\n        private:\n            int _d, _l;\n\
    \            std::vector<int> _n;\n            std::vector<mint> _g, _ig;\n\n\
    \            void fft(std::vector<mint>& f, bool inverse) {\n                const\
    \ auto& g = inverse ? _g : _ig;\n                for (int i = 0, block = 1; i\
    \ < _d; ++i) {\n                    std::vector<mint> x(_n[i]);\n            \
    \        const int nblock = block * _n[i];\n                    for (int l = 0;\
    \ l + nblock <= _l; l += nblock) {\n                        for (int start = l;\
    \ start < l + block; ++start) {\n                            if (_n[i] == 2) {\n\
    \                                mint u = f[start], v = f[start + block];\n  \
    \                              f[start] = u + v;\n                           \
    \     f[start + block] = u - v;\n                            } else if (_n[i]\
    \ == 3) {\n                                mint u = f[start], v = f[start + block],\
    \ w = f[start + block + block];\n                                f[start] = u\
    \ + v + w;\n                                f[start + block] = u + (v + w * g[i])\
    \ * g[i];\n                                f[start + block + block] = u + (w +\
    \ v * g[i]) * g[i];\n                            } else {\n                  \
    \              for (int p = 0; p < _n[i]; ++p) x[p] = f[start + p * block];\n\
    \                                if (_n[i] <= 100) {\n                       \
    \             x = internal::chirp_z_transform_naive<mint>(x, 1, g[i], _n[i]);\n\
    \                                } else {\n                                  \
    \  x = chirp_z_transform<mint>(x, 1, g[i], _n[i], arbitrary_mod_convolution<mint>);\n\
    \                                }\n                                for (int p\
    \ = 0; p < _n[i]; ++p) f[start + p * block] = x[p];\n                        \
    \    }\n                        }\n                    }\n                   \
    \ block = nblock;\n                }\n                if (inverse) {\n       \
    \             mint iz = mint(f.size()).inv();\n                    for (auto&\
    \ e : f) e *= iz;\n                }\n            }\n        };\n    }\n\n   \
    \ template <typename mint, std::enable_if_t<atcoder::internal::is_modint<mint>::value,\
    \ std::nullptr_t> = nullptr>\n    struct multi_variate_convolution_circular {\n\
    \    private:\n        using mint2 = atcoder::dynamic_modint<102938478>;\n   \
    \ public:\n        multi_variate_convolution_circular() = default;\n        multi_variate_convolution_circular(std::vector<int>\
    \ n) : _d(n.size()), _l(std::reduce(n.begin(), n.end(), 1, std::multiplies<int>())),\
    \ _n(n) {\n            const __int128_t max_val = __int128_t(mint::mod() - 1)\
    \ * (mint::mod() - 1) * _l;\n\n            const int t = std::reduce(n.begin(),\
    \ n.end(), 1, [](int x, int y) { return std::lcm(x, y); });\n\n            if\
    \ ((mint::mod() - 1) % t == 0) {\n                _mods = { mint::mod() };\n \
    \           } else {\n                __int128_t prod = 1;\n                for\
    \ (int k = 1000000000 / t; k >= 0; --k) if (const int p = k * t + 1; miller_rabin::is_prime(p))\
    \ {\n                    _mods.push_back(p);\n                    prod *= p;\n\
    \                    if (prod >= max_val) break;\n                }\n        \
    \        assert(prod >= max_val);\n            }\n            const int m = _mods.size();\n\
    \            _cnvs.resize(m);\n            for (int i = 0; i < m; ++i) with_kth_mod(i,\
    \ [&, this] {\n                _cnvs[i] = internal::multi_variate_convolution_circular<mint2>(_n);\n\
    \            });\n        }\n\n        std::vector<mint> convolution(std::vector<mint>\
    \ f, const std::vector<mint>& g) {\n            assert(int(f.size()) == _l and\
    \ int(g.size()) == _l);\n            if (_d == 0) return { f[0] * g[0] };\n  \
    \          // if (_d == 1) return arbitrary_mod_convolution<mint>(f, g);\n   \
    \         if (_l <= 60) return convolution_naive(f, g);\n            const int\
    \ m = _mods.size();\n            std::vector res(m, std::vector<int>(_l));\n \
    \           for (int i = 0; i < m; ++i) with_kth_mod(i, [&, this] {\n        \
    \        std::vector<mint2> f2(_l), g2(_l);\n                for (int j = 0; j\
    \ < _l; ++j) f2[j] = f[j].val(), g2[j] = g[j].val();\n                std::vector<mint2>\
    \ h = _cnvs[i](f2, g2);\n                for (int j = 0; j < _l; ++j) res[i][j]\
    \ = h[j].val();\n            });\n            std::vector<mint> h(_l);\n     \
    \       for (int j = 0; j < _l; ++j) {\n                std::vector<std::pair<int,\
    \ int>> eq(m);\n                for (int i = 0; i < m; ++i) {\n              \
    \      eq[i] = { res[i][j], _mods[i] };\n                }\n                h[j]\
    \ = garner(eq, mint::mod());\n            }\n            return h;\n        }\n\
    \        std::vector<mint> operator()(const std::vector<mint>& f, const std::vector<mint>&\
    \ g) {\n            return convolution(f, g);\n        }\n\n        std::vector<mint>\
    \ convolution_naive(const std::vector<mint>& f, const std::vector<mint>& g) {\n\
    \            std::vector<mint> h(_l);\n            for (int i = 0; i < _l; ++i)\
    \ for (int j = 0; j < _l; ++j) {\n                int k = 0;\n               \
    \ for (int d = 0, i2 = i, j2 = j, prd = 1; d < _d; ++d) {\n                  \
    \  k += prd * ((i2 + j2) % _n[d]);\n                    i2 /= _n[d], j2 /= _n[d],\
    \ prd *= _n[d];\n                }\n                h[k] += f[i] * g[j];\n   \
    \         }\n            return h;\n        }\n    private:\n        int _d, _l;\n\
    \        std::vector<int> _n;\n        std::vector<int> _mods;\n        std::vector<internal::multi_variate_convolution_circular<mint2>>\
    \ _cnvs;\n\n        template <typename F>\n        void with_kth_mod(int k, F&&\
    \ f) {\n            int old_mod = mint2::mod();\n            mint2::set_mod(_mods[k]);\n\
    \            f();\n            if (old_mod >= 1) mint2::set_mod(old_mod);\n  \
    \      }\n    };\n} // namespace suisen\n\n\n\n#line 10 \"test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp\"\
    \n\nint main() {\n    using suisen::multi_variate_convolution_circular;\n\n  \
    \  std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n;\n\
    \    std::cin >> n;\n\n    std::vector<mint> a(1 << n), b(1 << n);\n\n    for\
    \ (int i = 0, v; i < 1 << n; ++i) std::cin >> v, a[i] = v;\n    for (int i = 0,\
    \ v; i < 1 << n; ++i) std::cin >> v, b[i] = v;\n\n    multi_variate_convolution_circular<mint>\
    \ conv(std::vector<int>(n, 2));\n\n    std::vector<mint> c = conv(a, b);\n   \
    \ for (int i = 0; i < 1 << n; ++i) std::cout << c[i].val() << \" \\n\"[i == (1\
    \ << n) - 1];\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/convolution/multi_variate_convolution_circular.hpp\"\n\n\
    int main() {\n    using suisen::multi_variate_convolution_circular;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >>\
    \ v, a[i] = v;\n    for (int i = 0, v; i < 1 << n; ++i) std::cin >> v, b[i] =\
    \ v;\n\n    multi_variate_convolution_circular<mint> conv(std::vector<int>(n,\
    \ 2));\n\n    std::vector<mint> c = conv(a, b);\n    for (int i = 0; i < 1 <<\
    \ n; ++i) std::cout << c[i].val() << \" \\n\"[i == (1 << n) - 1];\n\n    return\
    \ 0;\n}"
  dependsOn:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/transform/chirp_z_transform.hpp
  - library/convolution/arbitrary_mod_convolution.hpp
  - library/convolution/convolution_naive.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/number/montogomery.hpp
  - library/number/primitive_root.hpp
  - library/number/order_Z_mZ.hpp
  - library/number/fast_factorize.hpp
  - library/type_traits/type_traits.hpp
  - library/number/sieve_of_eratosthenes.hpp
  - library/number/internal_eratosthenes.hpp
  - library/number/garner.hpp
  - library/number/ext_gcd.hpp
  isVerificationFile: true
  path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 21:04:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
- /verify/test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp.html
title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
---
