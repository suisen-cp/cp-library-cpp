---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  - icon: ':question:'
    path: library/number/deterministic_miller_rabin.hpp
    title: Deterministic Miller Rabin
  - icon: ':warning:'
    path: library/number/fast_discrete_logarithm.hpp
    title: Fast Discrete Logarithm
  - icon: ':question:'
    path: library/number/fast_factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3"
  - icon: ':question:'
    path: library/number/order_Z_mZ.hpp
    title: Order of $x \in (\mathbb{Z}/m\mathbb{Z}) ^ \ast$
  - icon: ':question:'
    path: library/number/primitive_root.hpp
    title: Primitive Root
  - icon: ':x:'
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
    path: test/src/number/deterministic_miller_rabin/primarity_test.test.cpp
    title: test/src/number/deterministic_miller_rabin/primarity_test.test.cpp
  - icon: ':x:'
    path: test/src/number/fast_factorize/factorize.test.cpp
    title: test/src/number/fast_factorize/factorize.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/dummy.test.cpp
    title: test/src/number/primitive_root/dummy.test.cpp
  - icon: ':x:'
    path: test/src/number/primitive_root/primitive_root.test.cpp
    title: test/src/number/primitive_root/primitive_root.test.cpp
  - icon: ':x:'
    path: test/src/number/tetration_mod/tetration_mod.test.cpp
    title: test/src/number/tetration_mod/tetration_mod.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/montogomery.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n\nnamespace suisen {\n    namespace internal::montgomery\
    \ {\n        template <typename Int, typename DInt>\n        struct Montgomery\
    \ {\n        private:\n            static constexpr uint32_t bits = std::numeric_limits<Int>::digits;\n\
    \            static constexpr Int mask = ~Int(0);\n            // R = 2**32 or\
    \ 2**64\n\n            // 1. N is an odd number\n            // 2. N < R\n   \
    \         // 3. gcd(N, R) = 1\n            // 4. R * R2 - N * N2 = 1\n       \
    \     // 5. 0 < R2 < N\n            // 6. 0 < N2 < R\n            Int N, N2, R2;\n\
    \n            // RR = R * R (mod N)\n            Int RR;\n        public:\n  \
    \          constexpr Montgomery() = default;\n            explicit constexpr Montgomery(Int\
    \ N) : N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {\n             \
    \   assert(N & 1);\n            }\n\n            // @returns t * R (mod N)\n \
    \           constexpr Int make(Int t) const {\n                return reduce(static_cast<DInt>(t)\
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
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MONTGOMERY\n#define SUISEN_MONTGOMERY\n\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n\nnamespace suisen {\n    namespace internal::montgomery\
    \ {\n        template <typename Int, typename DInt>\n        struct Montgomery\
    \ {\n        private:\n            static constexpr uint32_t bits = std::numeric_limits<Int>::digits;\n\
    \            static constexpr Int mask = ~Int(0);\n            // R = 2**32 or\
    \ 2**64\n\n            // 1. N is an odd number\n            // 2. N < R\n   \
    \         // 3. gcd(N, R) = 1\n            // 4. R * R2 - N * N2 = 1\n       \
    \     // 5. 0 < R2 < N\n            // 6. 0 < N2 < R\n            Int N, N2, R2;\n\
    \n            // RR = R * R (mod N)\n            Int RR;\n        public:\n  \
    \          constexpr Montgomery() = default;\n            explicit constexpr Montgomery(Int\
    \ N) : N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {\n             \
    \   assert(N & 1);\n            }\n\n            // @returns t * R (mod N)\n \
    \           constexpr Int make(Int t) const {\n                return reduce(static_cast<DInt>(t)\
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
    } // namespace suisen\n\n\n#endif // SUISEN_MONTGOMERY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/montogomery.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  - library/number/primitive_root.hpp
  - library/number/deterministic_miller_rabin.hpp
  - library/number/fast_factorize.hpp
  - library/number/fast_discrete_logarithm.hpp
  - library/number/order_Z_mZ.hpp
  - library/number/tetration_mod.hpp
  timestamp: '2023-05-18 22:35:58+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/number/deterministic_miller_rabin/primarity_test.test.cpp
  - test/src/number/primitive_root/primitive_root.test.cpp
  - test/src/number/primitive_root/dummy.test.cpp
  - test/src/number/fast_factorize/factorize.test.cpp
  - test/src/number/tetration_mod/tetration_mod.test.cpp
documentation_of: library/number/montogomery.hpp
layout: document
title: Montogomery
---
## Montogomery
