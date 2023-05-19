#ifndef SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD
#define SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD

#include <cassert>
#include <cstdint>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

namespace suisen::miller_rabin_simd {
    namespace internal {
        __attribute__((target("avx2")))
        bool is_prime_int(uint32_t n) {
            if (n == 2 or n == 3 or n == 5 or n == 7) return true;
            if (n <= 1 or n % 2 == 0 or n % 3 == 0 or n % 5 == 0 or n % 7 == 0) return false;
            if (n < 121) return true;

            const uint32_t s = __builtin_ctz(n - 1); // >= 1
            const uint32_t d = (n - 1) >> s;

            // Montgomery Reduction (mod n)
            const uint32_t n2 = [&] {
                uint64_t invN = n;
                for (uint32_t cur_bits = 2; cur_bits < 32; cur_bits *= 2) {
                    invN = uint32_t(invN * uint32_t(2 - n * invN));
                }
                return uint32_t(-invN);
            }();
            const uint32_t rr = [&] {
                return -uint64_t(n) % n;
            }();
            const auto make = [&](uint32_t v) {
                uint64_t T = uint64_t(v) * rr;
                // reduce(T)
                uint64_t m = uint32_t(uint64_t(uint32_t(T)) * n2);
                uint64_t t = (T + m * n) >> 32;
                return t >= n ? t - n : t;
            };

#define SET4(A, B, C, D) _mm256_set_epi64x(A, B, C, D)
#define SET1(A) _mm256_set1_epi64x(A)

            __m256i mask_lo = SET1((uint64_t(1) << 32) - 1);

#define MOD_R(As) _mm256_and_si256(As, mask_lo)
#define DIV_R(As) _mm256_srli_epi64(As, 32)

#define ADD(As, Bs) _mm256_add_epi64(As, Bs)
#define SUB(As, Bs) _mm256_sub_epi64(As, Bs)
#define MUL(As, Bs) _mm256_mul_epu32(As, Bs)

#define XOR(As, Bs) _mm256_xor_si256(As, Bs)
#define OR(As, Bs) _mm256_or_si256(As, Bs)

            __m256i n2s = SET1(n2);
            __m256i ns = SET1(n);

#define MUL_MONTGOMERY(As, Bs, Cs) \
    {\
        __m256i Ts = MUL(As, Bs);                                           \
        __m256i ms = MOD_R(MUL(MOD_R(Ts), n2s));                            \
        __m256i ts = DIV_R(ADD(Ts, MUL(ms, ns)));                           \
        __m256i sub = _mm256_andnot_si256(_mm256_cmpgt_epi64(ns, ts), ns);  \
        Cs = SUB(ts, sub);                                                  \
    }\

            const uint32_t one = make(1), minus_one = make(n - 1);

            __m256i ones = SET4(one, one, one, 0);
            __m256i minus_ones = SET4(minus_one, minus_one, minus_one, 0);

            __m256i Ps = SET4(make(2 % n), make(7 % n), make(61 % n), 0);
            __m256i Ys = ones;

            for (uint32_t d2 = d; d2; d2 >>= 1) {
                if (d2 & 1) {
                    MUL_MONTGOMERY(Ps, Ys, Ys);
                }
                MUL_MONTGOMERY(Ps, Ps, Ps);
            }

            __m256i all1 = _mm256_set1_epi32(-1);
#define ALL_ONE(As, f) \
    {\
        __m256i negAs = XOR(all1, As); \
        f = _mm256_testz_si256(negAs, negAs);       \
    }\

            __m256i is_one = _mm256_cmpeq_epi64(Ys, ones);
            __m256i is_zero = SET4(-(2 % n == 0), -(7 % n == 0), -(61 % n == 0), -1);

            __m256i is_prime = OR(is_one, is_zero);

            bool f;
            for (uint32_t r = 0; ; ++r) {
                is_prime = OR(is_prime, _mm256_cmpeq_epi64(Ys, minus_ones));
                ALL_ONE(is_prime, f);
                if (f or r == s - 1) return f;
                MUL_MONTGOMERY(Ys, Ys, Ys);
            }
#undef SET4
#undef SET1
#undef MOD_R
#undef DIV_R
#undef ADD
#undef SUB
#undef MUL
#undef XOR
#undef OR
#undef MUL_MONTGOMERY
#undef ALL_ONE
        }
    }

    bool is_prime(long long n) {
        assert(0 <= n and n < 1LL << 31);
        return internal::is_prime_int(n);
    }
} // namespace suisen::miller_rabin

#endif // SUISEN_DETERMINISTIC_MILLER_RABIN_SIMD
