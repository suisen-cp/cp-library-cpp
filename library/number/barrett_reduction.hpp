#ifndef SUISEN_BARRETT_REDUCTION
#define SUISEN_BARRETT_REDUCTION

#include <array>
#include <cassert>
#include <cstdint>
#include <utility>

namespace suisen {
    struct barrett {
        constexpr barrett() : M(1), L(0) {}
        constexpr explicit barrett(uint32_t M) : M(M), L(uint64_t(-1) / M + 1) { assert(M); }
        constexpr int32_t mod() { return M; }
        constexpr uint32_t umod() const { return M; }
        // floor(x/M) (correctly works for all 0<=x<2^64)
        template <bool care_M1 = true> constexpr uint64_t quo(uint64_t x) const { return quorem<care_M1>(x).first; }
        // x%M (correctly works for all 0<=x<2^64)
        template <bool care_M1 = true> constexpr uint32_t rem(uint64_t x) const { return quorem<care_M1>(x).second; }
        // { floor(x/M), x%M } (correctly works for all 0<=x<2^64)
        template <bool care_M1 = true> constexpr std::pair<uint64_t, uint32_t> quorem(uint64_t x) const {
            if constexpr (care_M1) if (M == 1) return { x, 0 };
            uint64_t q = (__uint128_t(x) * L) >> 64;
            int32_t r = x - q * M;
            if (r < 0) --q, r += M;
            return { q, uint32_t(r) };
        }
        // a*b mod M
        template <bool care_M1 = true> constexpr uint32_t mul(uint32_t a, uint32_t b) const { return rem<care_M1>(uint64_t(a) * b); }
    private:
        uint32_t M; // mod
        uint64_t L; // ceil(2^K / M), where K = 64 (if M != 1)
    };
} // namespace suisen


#endif // SUISEN_BARRETT_REDUCTION
