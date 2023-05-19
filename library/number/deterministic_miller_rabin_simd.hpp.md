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
  bundledCode: "#line 1 \"library/number/deterministic_miller_rabin_simd.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstdint>\n\n#ifdef _MSC_VER\n#  include <intrin.h>\n\
    #else\n#  include <x86intrin.h>\n#endif\n\nnamespace suisen::miller_rabin_simd\
    \ {\n    namespace internal {\n        __attribute__((target(\"avx2\")))\n   \
    \     bool is_prime_int(uint32_t n) {\n            if (n == 2 or n == 3 or n ==\
    \ 5 or n == 7) return true;\n            if (n <= 1 or n % 2 == 0 or n % 3 ==\
    \ 0 or n % 5 == 0 or n % 7 == 0) return false;\n            if (n < 121) return\
    \ true;\n\n            const uint32_t s = __builtin_ctz(n - 1); // >= 1\n    \
    \        const uint32_t d = (n - 1) >> s;\n\n            // Montgomery Reduction\
    \ (mod n)\n            const uint32_t n2 = [&] {\n                uint64_t invN\
    \ = n;\n                for (uint32_t cur_bits = 2; cur_bits < 32; cur_bits *=\
    \ 2) {\n                    invN = uint32_t(invN * uint32_t(2 - n * invN));\n\
    \                }\n                return uint32_t(-invN);\n            }();\n\
    \            const uint32_t rr = [&] {\n                return -uint64_t(n) %\
    \ n;\n            }();\n            const auto make = [&](uint32_t v) {\n    \
    \            uint64_t T = uint64_t(v) * rr;\n                // reduce(T)\n  \
    \              uint64_t m = uint32_t(uint64_t(uint32_t(T)) * n2);\n          \
    \      uint64_t t = (T + m * n) >> 32;\n                return t >= n ? t - n\
    \ : t;\n            };\n\n#define SET4(A, B, C, D) _mm256_set_epi64x(A, B, C,\
    \ D)\n#define SET1(A) _mm256_set1_epi64x(A)\n\n            __m256i mask_lo = SET1((uint64_t(1)\
    \ << 32) - 1);\n\n#define MOD_R(As) _mm256_and_si256(As, mask_lo)\n#define DIV_R(As)\
    \ _mm256_srli_epi64(As, 32)\n\n#define ADD(As, Bs) _mm256_add_epi64(As, Bs)\n\
    #define SUB(As, Bs) _mm256_sub_epi64(As, Bs)\n#define MUL(As, Bs) _mm256_mul_epu32(As,\
    \ Bs)\n\n#define XOR(As, Bs) _mm256_xor_si256(As, Bs)\n#define OR(As, Bs) _mm256_or_si256(As,\
    \ Bs)\n\n            __m256i n2s = SET1(n2);\n            __m256i ns = SET1(n);\n\
    \n#define MUL_MONTGOMERY(As, Bs, Cs) \\\n    {\\\n        __m256i Ts = MUL(As,\
    \ Bs);                                           \\\n        __m256i ms = MOD_R(MUL(MOD_R(Ts),\
    \ n2s));                            \\\n        __m256i ts = DIV_R(ADD(Ts, MUL(ms,\
    \ ns)));                           \\\n        __m256i sub = _mm256_andnot_si256(_mm256_cmpgt_epi64(ns,\
    \ ts), ns);  \\\n        Cs = SUB(ts, sub);                                  \
    \                \\\n    }\\\n\n            const uint32_t one = make(1), minus_one\
    \ = make(n - 1);\n\n            __m256i ones = SET4(one, one, one, 0);\n     \
    \       __m256i minus_ones = SET4(minus_one, minus_one, minus_one, 0);\n\n   \
    \         __m256i Ps = SET4(make(2 % n), make(7 % n), make(61 % n), 0);\n    \
    \        __m256i Ys = ones;\n\n            for (uint32_t d2 = d; d2; d2 >>= 1)\
    \ {\n                if (d2 & 1) {\n                    MUL_MONTGOMERY(Ps, Ys,\
    \ Ys);\n                }\n                MUL_MONTGOMERY(Ps, Ps, Ps);\n     \
    \       }\n\n            __m256i all1 = _mm256_set1_epi32(-1);\n#define ALL_ONE(As,\
    \ f) \\\n    {\\\n        __m256i negAs = XOR(all1, As); \\\n        f = _mm256_testz_si256(negAs,\
    \ negAs);       \\\n    }\\\n\n            __m256i is_one = _mm256_cmpeq_epi64(Ys,\
    \ ones);\n            __m256i is_zero = SET4(-(2 % n == 0), -(7 % n == 0), -(61\
    \ % n == 0), -1);\n\n            __m256i is_prime = OR(is_one, is_zero);\n\n \
    \           bool f;\n            for (uint32_t r = 0; ; ++r) {\n             \
    \   is_prime = OR(is_prime, _mm256_cmpeq_epi64(Ys, minus_ones));\n           \
    \     ALL_ONE(is_prime, f);\n                if (f or r == s - 1) return f;\n\
    \                MUL_MONTGOMERY(Ys, Ys, Ys);\n            }\n#undef SET4\n#undef\
    \ SET1\n#undef MOD_R\n#undef DIV_R\n#undef ADD\n#undef SUB\n#undef MUL\n#undef\
    \ XOR\n#undef OR\n#undef MUL_MONTGOMERY\n#undef ALL_ONE\n        }\n    }\n\n\
    \    bool is_prime(long long n) {\n        assert(0 <= n and n < 1LL << 31);\n\
    \        return internal::is_prime_int(n);\n    }\n} // namespace suisen::miller_rabin\n\
    \n\n"
  code: "#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD\n#define SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD\n\
    \n#include <cassert>\n#include <cstdint>\n\n#ifdef _MSC_VER\n#  include <intrin.h>\n\
    #else\n#  include <x86intrin.h>\n#endif\n\nnamespace suisen::miller_rabin_simd\
    \ {\n    namespace internal {\n        __attribute__((target(\"avx2\")))\n   \
    \     bool is_prime_int(uint32_t n) {\n            if (n == 2 or n == 3 or n ==\
    \ 5 or n == 7) return true;\n            if (n <= 1 or n % 2 == 0 or n % 3 ==\
    \ 0 or n % 5 == 0 or n % 7 == 0) return false;\n            if (n < 121) return\
    \ true;\n\n            const uint32_t s = __builtin_ctz(n - 1); // >= 1\n    \
    \        const uint32_t d = (n - 1) >> s;\n\n            // Montgomery Reduction\
    \ (mod n)\n            const uint32_t n2 = [&] {\n                uint64_t invN\
    \ = n;\n                for (uint32_t cur_bits = 2; cur_bits < 32; cur_bits *=\
    \ 2) {\n                    invN = uint32_t(invN * uint32_t(2 - n * invN));\n\
    \                }\n                return uint32_t(-invN);\n            }();\n\
    \            const uint32_t rr = [&] {\n                return -uint64_t(n) %\
    \ n;\n            }();\n            const auto make = [&](uint32_t v) {\n    \
    \            uint64_t T = uint64_t(v) * rr;\n                // reduce(T)\n  \
    \              uint64_t m = uint32_t(uint64_t(uint32_t(T)) * n2);\n          \
    \      uint64_t t = (T + m * n) >> 32;\n                return t >= n ? t - n\
    \ : t;\n            };\n\n#define SET4(A, B, C, D) _mm256_set_epi64x(A, B, C,\
    \ D)\n#define SET1(A) _mm256_set1_epi64x(A)\n\n            __m256i mask_lo = SET1((uint64_t(1)\
    \ << 32) - 1);\n\n#define MOD_R(As) _mm256_and_si256(As, mask_lo)\n#define DIV_R(As)\
    \ _mm256_srli_epi64(As, 32)\n\n#define ADD(As, Bs) _mm256_add_epi64(As, Bs)\n\
    #define SUB(As, Bs) _mm256_sub_epi64(As, Bs)\n#define MUL(As, Bs) _mm256_mul_epu32(As,\
    \ Bs)\n\n#define XOR(As, Bs) _mm256_xor_si256(As, Bs)\n#define OR(As, Bs) _mm256_or_si256(As,\
    \ Bs)\n\n            __m256i n2s = SET1(n2);\n            __m256i ns = SET1(n);\n\
    \n#define MUL_MONTGOMERY(As, Bs, Cs) \\\n    {\\\n        __m256i Ts = MUL(As,\
    \ Bs);                                           \\\n        __m256i ms = MOD_R(MUL(MOD_R(Ts),\
    \ n2s));                            \\\n        __m256i ts = DIV_R(ADD(Ts, MUL(ms,\
    \ ns)));                           \\\n        __m256i sub = _mm256_andnot_si256(_mm256_cmpgt_epi64(ns,\
    \ ts), ns);  \\\n        Cs = SUB(ts, sub);                                  \
    \                \\\n    }\\\n\n            const uint32_t one = make(1), minus_one\
    \ = make(n - 1);\n\n            __m256i ones = SET4(one, one, one, 0);\n     \
    \       __m256i minus_ones = SET4(minus_one, minus_one, minus_one, 0);\n\n   \
    \         __m256i Ps = SET4(make(2 % n), make(7 % n), make(61 % n), 0);\n    \
    \        __m256i Ys = ones;\n\n            for (uint32_t d2 = d; d2; d2 >>= 1)\
    \ {\n                if (d2 & 1) {\n                    MUL_MONTGOMERY(Ps, Ys,\
    \ Ys);\n                }\n                MUL_MONTGOMERY(Ps, Ps, Ps);\n     \
    \       }\n\n            __m256i all1 = _mm256_set1_epi32(-1);\n#define ALL_ONE(As,\
    \ f) \\\n    {\\\n        __m256i negAs = XOR(all1, As); \\\n        f = _mm256_testz_si256(negAs,\
    \ negAs);       \\\n    }\\\n\n            __m256i is_one = _mm256_cmpeq_epi64(Ys,\
    \ ones);\n            __m256i is_zero = SET4(-(2 % n == 0), -(7 % n == 0), -(61\
    \ % n == 0), -1);\n\n            __m256i is_prime = OR(is_one, is_zero);\n\n \
    \           bool f;\n            for (uint32_t r = 0; ; ++r) {\n             \
    \   is_prime = OR(is_prime, _mm256_cmpeq_epi64(Ys, minus_ones));\n           \
    \     ALL_ONE(is_prime, f);\n                if (f or r == s - 1) return f;\n\
    \                MUL_MONTGOMERY(Ys, Ys, Ys);\n            }\n#undef SET4\n#undef\
    \ SET1\n#undef MOD_R\n#undef DIV_R\n#undef ADD\n#undef SUB\n#undef MUL\n#undef\
    \ XOR\n#undef OR\n#undef MUL_MONTGOMERY\n#undef ALL_ONE\n        }\n    }\n\n\
    \    bool is_prime(long long n) {\n        assert(0 <= n and n < 1LL << 31);\n\
    \        return internal::is_prime_int(n);\n    }\n} // namespace suisen::miller_rabin\n\
    \n#endif // SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD\n"
  dependsOn: []
  isVerificationFile: false
  path: library/number/deterministic_miller_rabin_simd.hpp
  requiredBy: []
  timestamp: '2023-05-19 09:20:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/deterministic_miller_rabin_simd.hpp
layout: document
redirect_from:
- /library/library/number/deterministic_miller_rabin_simd.hpp
- /library/library/number/deterministic_miller_rabin_simd.hpp.html
title: library/number/deterministic_miller_rabin_simd.hpp
---
