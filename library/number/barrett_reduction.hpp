#ifndef SUISEN_BARRETT_REDUCTION
#define SUISEN_BARRETT_REDUCTION

#include <array>
#include <cstdint>
#include <utility>

namespace suisen {
    struct BarrettReduction {
        uint32_t m;
        uint64_t im;
        BarrettReduction() = default;
        BarrettReduction(uint32_t m) : m(m), im(uint64_t(0x7fff'ffff'ffff'ffff) / m + 1) {}

        // 0 <= n < 2**63
        std::pair<uint64_t, uint32_t> quorem(uint64_t n) const {
            uint64_t q = uint64_t((__uint128_t(n) * im) >> 63);
            int64_t r = n - q * m;
            if (r < 0) --q, r += m;
            return std::make_pair(q, r);
        }
        // 0 <= n < 2**63
        uint32_t quo(uint64_t n) const {
            return quorem(n).first;
        }
        // 0 <= n < 2**63
        uint32_t rem(uint64_t n) const {
            return quorem(n).second;
        }

        template <typename Head, typename ...Tails>
        uint32_t mul(Head &&head, Tails &&...tails) const {
            if constexpr (sizeof...(tails)) {
                return rem(uint64_t(head) * mul(std::forward<Tails>(tails)...));
            } else {
                return head;
            }
        }
    };
} // namespace suisen


#endif // SUISEN_BARRETT_REDUCTION
