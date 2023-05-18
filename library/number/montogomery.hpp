#ifndef SUISEN_MONTGOMERY
#define SUISEN_MONTGOMERY

#include <cassert>
#include <cstdint>
#include <limits>

namespace suisen {
    namespace internal::montgomery {
        template <typename Int, typename DInt>
        struct Montgomery {
        private:
            static constexpr uint32_t bits = std::numeric_limits<Int>::digits;
            static constexpr Int mask = ~Int(0);
            // R = 2**32 or 2**64

            // 1. N is an odd number
            // 2. N < R
            // 3. gcd(N, R) = 1
            // 4. R * R2 - N * N2 = 1
            // 5. 0 < R2 < N
            // 6. 0 < N2 < R
            Int N, N2, R2;

            // RR = R * R (mod N)
            Int RR;
        public:
            constexpr Montgomery() = default;
            explicit constexpr Montgomery(Int N) : N(N), N2(calcN2(N)), R2(calcR2(N, N2)), RR(calcRR(N)) {
                assert(N & 1);
            }

            // @returns t * R (mod N)
            constexpr Int make(Int t) const {
                return reduce(static_cast<DInt>(t) * RR);
            }
            // @returns T * R^(-1) (mod N)
            constexpr Int reduce(DInt T) const {
                // 0 <= T < RN

                // Note:
                //  1. m = T * N2 (mod R)
                //  2. 0 <= m < R
                DInt m = modR(static_cast<DInt>(modR(T)) * N2);

                // Note:
                //  T + m * N = T + T * N * N2 = T + T * (R * R2 - 1) = 0 (mod R)
                //  => (T + m * N) / R is an integer.
                //  => t * R = T + m * N = T (mod N)
                //  => t = T R^(-1) (mod N)
                DInt t = divR(T + m * N);

                // Note:
                //  1. 0 <= T < RN
                //  2. 0 <= mN < RN (because 0 <= m < R)
                //  => 0 <= T + mN < 2RN
                //  => 0 <= t < 2N
                return t >= N ? t - N : t;
            }

            constexpr Int add(Int A, Int B) const {
                return (A += B) >= N ? A - N : A;
            }
            constexpr Int sub(Int A, Int B) const {
                return (A -= B) < 0 ? A + N : A;
            }
            constexpr Int mul(Int A, Int B) const {
                return reduce(static_cast<DInt>(A) * B);
            }
            constexpr Int div(Int A, Int B) const {
                return reduce(static_cast<DInt>(A) * inv(B));
            }
            constexpr Int inv(Int A) const; // TODO: Implement

            constexpr Int pow(Int A, long long b) const {
                Int P = make(1);
                for (; b; b >>= 1) {
                    if (b & 1) P = mul(P, A);
                    A = mul(A, A);
                }
                return P;
            }

        private:
            static constexpr Int divR(DInt t) { return t >> bits; }
            static constexpr Int modR(DInt t) { return t & mask; }

            static constexpr Int calcN2(Int N) {
                // - N * N2 = 1 (mod R)
                // N2 = -N^{-1} (mod R)

                // calculates N^{-1} (mod R) by Newton's method
                DInt invN = N; // = N^{-1} (mod 2^2)
                for (uint32_t cur_bits = 2; cur_bits < bits; cur_bits *= 2) {
                    // loop invariant: invN = N^{-1} (mod 2^cur_bits)

                    // x = a^{-1} mod m => x(2-ax) = a^{-1} mod m^2 because:
                    //  ax = 1 (mod m)
                    //  => (ax-1)^2 = 0 (mod m^2)
                    //  => 2ax - a^2x^2 = 1 (mod m^2)
                    //  => a(x(2-ax)) = 1 (mod m^2)
                    invN = modR(invN * modR(2 - N * invN));
                }
                assert(modR(N * invN) == 1);

                return modR(-invN);
            }
            static constexpr Int calcR2(Int N, Int N2) {
                // R * R2 - N * N2 = 1
                // => R2 = (1 + N * N2) / R
                return divR(1 + static_cast<DInt>(N) * N2);
            }
            static constexpr Int calcRR(Int N) {
                return -DInt(N) % N;
            }
        };
    } // namespace internal::montgomery
    using Montgomery32 = internal::montgomery::Montgomery<uint32_t, uint64_t>;
    using Montgomery64 = internal::montgomery::Montgomery<uint64_t, __uint128_t>;
} // namespace suisen


#endif // SUISEN_MONTGOMERY
