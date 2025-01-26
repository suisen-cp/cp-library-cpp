---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/montogomery.hpp
    title: Montogomery
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':warning:'
    path: library/number/fast_discrete_logarithm.hpp
    title: Fast Discrete Logarithm
  - icon: ':heavy_check_mark:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: library/number/order_Z_mZ.hpp
    title: Order of $x \in (\mathbb{Z}/m\mathbb{Z}) ^ \ast$
  - icon: ':heavy_check_mark:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: library/number/tetration_mod.hpp
    title: $a\uparrow\uparrow b \bmod m$
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
  - icon: ':heavy_check_mark:'
    path: test/src/number/deterministic_miller_rabin/primality_test.test.cpp
    title: test/src/number/deterministic_miller_rabin/primality_test.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/fast_factorize/factorize.test.cpp
    title: test/src/number/fast_factorize/factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/primitive_root/dummy.test.cpp
    title: test/src/number/primitive_root/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/primitive_root/primitive_root.test.cpp
    title: test/src/number/primitive_root/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/number/tetration_mod/tetration_mod.test.cpp
    title: test/src/number/tetration_mod/tetration_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/deterministic_miller_rabin.hpp\"\n\n\n\n\
    #include <array>\n#include <cassert>\n#include <cstdint>\n#include <iterator>\n\
    #include <tuple>\n#include <type_traits>\n\n#line 1 \"library/number/montogomery.hpp\"\
    \n\n\n\n#line 6 \"library/number/montogomery.hpp\"\n#include <limits>\n\nnamespace\
    \ suisen {\n    namespace internal::montgomery {\n        template <typename Int,\
    \ typename DInt>\n        struct Montgomery {\n        private:\n            static\
    \ constexpr uint32_t bits = std::numeric_limits<Int>::digits;\n            static\
    \ constexpr Int mask = ~Int(0);\n            // R = 2**32 or 2**64\n\n       \
    \     // 1. N is an odd number\n            // 2. N < R\n            // 3. gcd(N,\
    \ R) = 1\n            // 4. R * R2 - N * N2 = 1\n            // 5. 0 < R2 < N\n\
    \            // 6. 0 < N2 < R\n            Int N, N2, R2;\n\n            // RR\
    \ = R * R (mod N)\n            Int RR;\n        public:\n            constexpr\
    \ Montgomery() = default;\n            explicit constexpr Montgomery(Int N) :\
    \ N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {\n                assert(N\
    \ & 1);\n            }\n\n            // @returns t * R (mod N)\n            constexpr\
    \ Int make(Int t) const {\n                return reduce(static_cast<DInt>(t)\
    \ * RR);\n            }\n            // @returns T * R^(-1) (mod N)\n        \
    \    constexpr Int reduce(DInt T) const {\n                // 0 <= T < RN\n\n\
    \                // Note:\n                //  1. m = T * N2 (mod R)\n       \
    \         //  2. 0 <= m < R\n                DInt m = modR(static_cast<DInt>(modR(T))\
    \ * N2);\n\n                // Note:\n                //  T + m * N = T + T *\
    \ N * N2 = T + T * (R * R2 - 1) = 0 (mod R)\n                //  => (T + m * N)\
    \ / R is an integer.\n                //  => t * R = T + m * N = T (mod N)\n \
    \               //  => t = T R^(-1) (mod N)\n                DInt t = divR(T +\
    \ m * N);\n\n                // Note:\n                //  1. 0 <= T < RN\n  \
    \              //  2. 0 <= mN < RN (because 0 <= m < R)\n                //  =>\
    \ 0 <= T + mN < 2RN\n                //  => 0 <= t < 2N\n                return\
    \ t >= N ? t - N : t;\n            }\n\n            constexpr Int add(Int A, Int\
    \ B) const {\n                return (A += B) >= N ? A - N : A;\n            }\n\
    \            constexpr Int sub(Int A, Int B) const {\n                return (A\
    \ -= B) < 0 ? A + N : A;\n            }\n            constexpr Int mul(Int A,\
    \ Int B) const {\n                return reduce(static_cast<DInt>(A) * B);\n \
    \           }\n            constexpr Int div(Int A, Int B) const {\n         \
    \       return reduce(static_cast<DInt>(A) * inv(B));\n            }\n       \
    \     constexpr Int inv(Int A) const; // TODO: Implement\n\n            constexpr\
    \ Int pow(Int A, long long b) const {\n                Int P = make(1);\n    \
    \            for (; b; b >>= 1) {\n                    if (b & 1) P = mul(P, A);\n\
    \                    A = mul(A, A);\n                }\n                return\
    \ P;\n            }\n\n        private:\n            static constexpr Int divR(DInt\
    \ t) { return t >> bits; }\n            static constexpr Int modR(DInt t) { return\
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
    \ 7>(n_unsigned);\n    }\n} // namespace suisen::miller_rabin\n\n\n"
  code: "#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN\n#define SUISEN_DETERMINISTIC_MILLER_RABIN\n\
    \n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <iterator>\n\
    #include <tuple>\n#include <type_traits>\n\n#include \"library/number/montogomery.hpp\"\
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
    \ 7>(n_unsigned);\n    }\n} // namespace suisen::miller_rabin\n\n#endif // SUISEN_DETERMINISTIC_MILLER_RABIN\n"
  dependsOn:
  - library/number/montogomery.hpp
  isVerificationFile: false
  path: library/number/deterministic_miller_rabin.hpp
  requiredBy:
  - library/number/primitive_root.hpp
  - library/number/fast_factorize.hpp
  - library/number/order_Z_mZ.hpp
  - library/number/tetration_mod.hpp
  - library/number/fast_discrete_logarithm.hpp
  - library/convolution/multi_variate_convolution_circular.hpp
  timestamp: '2023-05-19 09:20:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/number/fast_factorize/factorize.test.cpp
  - test/src/number/deterministic_miller_rabin/primality_test.test.cpp
  - test/src/number/tetration_mod/tetration_mod.test.cpp
  - test/src/number/primitive_root/primitive_root.test.cpp
  - test/src/number/primitive_root/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
documentation_of: library/number/deterministic_miller_rabin.hpp
layout: document
title: Deterministic Miller Rabin
---
## Deterministic Miller Rabin