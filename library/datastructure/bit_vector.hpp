#ifndef SUISEN_BIT_VECTOR
#define SUISEN_BIT_VECTOR

#include <cstdint>
#include <vector>

#include "library/type_traits/type_traits.hpp"

namespace suisen {
class BitVector {
    using u8 = std::uint8_t;
    public:
        explicit BitVector(int n) : n(n), nl((n >> LOG_BLOCK_L) + 1), ns((n >> LOG_BLOCK_S) + 1), cum_l(nl, 0), cum_s(ns, 0), bits(ns, 0) {}
        BitVector() : BitVector(0) {}
        template <typename Gen, constraints_t<is_same_as_invoke_result<bool, Gen, int>> = nullptr>
        BitVector(int n, Gen gen) : BitVector(n) {
            build(gen);
        }
        BitVector& operator=(const BitVector &bv) {
            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = bv.cum_l, cum_s = bv.cum_s, bits = bv.bits;
            return *this;
        }
        BitVector& operator=(BitVector &&bv) {
            n = bv.n, nl = bv.nl, ns = bv.ns, cum_l = std::move(bv.cum_l), cum_s = std::move(bv.cum_s), bits = std::move(bv.bits);
            return *this;
        }
        template <typename Gen, constraints_t<is_same_as_invoke_result<bool, Gen, int>> = nullptr>
        void build(Gen gen) {
            int i = 0;
            for (int index_s = 1; index_s < ns; ++index_s) {
                int count = cum_s[index_s - 1];
                for (; i < index_s << LOG_BLOCK_S; ++i) {
                    bool b = gen(i);
                    bits[index_s - 1] |= b << (i & MASK_S);
                    count += b;
                }
                if (index_s & ((1 << (LOG_BLOCK_L - LOG_BLOCK_S)) - 1)) {
                    cum_s[index_s] = count;
                } else {
                    int index_l = i >> LOG_BLOCK_L;
                    cum_l[index_l] = cum_l[index_l - 1] + count;
                }
            }
            for (; i < n; ++i) bits[ns - 1] |= gen(i) << (i & MASK_S);
        }
        inline bool operator[](int i) const {
            return (bits[i >> LOG_BLOCK_S] >> (i & MASK_S)) & 1;
        }
        // returns the i'th val (i: 0-indexed)
        inline bool access(int i) const {
            return (*this)[i];
        }
        // returns the number of val in [0, i)
        inline int rank(bool val, int i) const {
            int res_1 = cum_l[i >> LOG_BLOCK_L] + cum_s[i >> LOG_BLOCK_S] + popcount8(bits[i >> LOG_BLOCK_S] & ((1 << (i & MASK_S)) - 1));
            return val ? res_1 : i - res_1;
        }
        // returns the number of val in [l, r)
        inline int rank(bool val, int l, int r) const {
            return rank(val, r) - rank(val, l);
        }
        // find the index of num'th val. (num: 1-indexed). if not exists, returns default_value.
        int select(bool val, int num, int default_value = -1) const {
            int l = -1, r = n + 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                (rank(val, m) >= num ? r : l) = m;
            }
            return r == n + 1 ? default_value : r;
        }
    private:
        static constexpr int LOG_BLOCK_L = 8;
        static constexpr int LOG_BLOCK_S = 3;
        static constexpr int MASK_S = (1 << LOG_BLOCK_S) - 1;

        int n, nl, ns;
        std::vector<int> cum_l;
        std::vector<u8> cum_s, bits;

        static constexpr u8 popcount8(u8 x) {
            x = (x & 0b01010101) + ((x >> 1) & 0b01010101);
            x = (x & 0b00110011) + ((x >> 2) & 0b00110011);
            return (x & 0b00001111) + (x >> 4);
        }
};
} // namespace suisen

#endif // SUISEN_BIT_VECTOR
