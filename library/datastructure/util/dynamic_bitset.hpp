#ifndef SUISEN_DYNAMIC_BITSET
#define SUISEN_DYNAMIC_BITSET

#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace suisen {
    struct DynamicBitSet {
    private:
        using block = unsigned long long;
        static constexpr std::size_t block_size = std::numeric_limits<block>::digits;
        static constexpr std::size_t log_block_size = __builtin_ctz(block_size);

        struct bitref {
            block& b;
            std::size_t i;
            operator bool() const { return (b >> i) & 1; }
            bool test() const { return (b >> i) & 1; }
            void set() { b |= block(1) << i; }
            void reset() { b &= ~(block(1) << i); }
            void flip() { b ^= block(1) << i; }
            bitref& operator&=(bool val) { b &= block(val) << i; return *this; }
            bitref& operator|=(bool val) { b |= block(val) << i; return *this; }
            bitref& operator^=(bool val) { b ^= block(val) << i; return *this; }
            bitref& operator =(bool val) { val ? set() : reset(); return *this; }
            bitref& operator =(const bitref& v) { return (*this) = bool(v); }
        };

        std::size_t n;
        std::vector<block> blocks;
    public:
        DynamicBitSet(std::size_t n = 0, bool fill_value = false) : n(n), blocks((n + block_size - 1) >> log_block_size, fill_value ? ~block(0) : 0) {}

        bool empty() const { return n == 0; }
        int size() const { return n; }

        void resize(std::size_t new_size, bool fill_value = false) {
            std::size_t new_block_num = (new_size + block_size - 1) >> log_block_size;
            if (new_block_num < block_num()) {
                n = new_size;
                return blocks.resize(new_block_num);
            }
            blocks.resize(new_block_num);
            std::size_t old_size = std::exchange(n, new_size);
            if (old_size <= new_size) range_update(old_size, new_size, fill_value);
        }
        void push_back(bool val) {
            if (n & (block_size - 1)) {
                (*this)[n] = val;
            } else {
                blocks.push_back(val);
            }
            ++n;
        }
        void pop_back() {
            if ((n & (block_size - 1)) == 1) blocks.pop_back();
            --n;
        }

        friend bool operator==(const DynamicBitSet& x, const DynamicBitSet& y) {
            if (x.n != y.n) return false;
            if (x.empty()) return true;
            for (std::size_t i = 0; i < x.block_num() - 1; ++i) {
                if (x.blocks[i] != y.blocks[i]) return false;
            }
            const std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);
            return get_lower_bits(x.blocks.back(), num) == get_lower_bits(y.blocks.back(), num);
        }
        friend bool operator!=(const DynamicBitSet& x, const DynamicBitSet& y) {
            return not (x == y);
        }
        friend bool operator<(const DynamicBitSet& x, const DynamicBitSet& y) {
            assert(x.n == y.n);
            if (x.empty()) return false;
            std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);
            block tx = get_lower_bits(x.blocks.back(), num);
            block ty = get_lower_bits(y.blocks.back(), num);
            if (tx != ty) return tx < ty;
            for (std::size_t i = x.block_num() - 1; i-- > 0;) {
                if (x.blocks[i] != y.blocks[i]) return x.blocks[i] < y.blocks[i];
            }
            return false;
        }
        friend bool operator<=(const DynamicBitSet& x, const DynamicBitSet& y) {
            assert(x.n == y.n);
            if (x.empty()) return true;
            std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);
            block tx = get_lower_bits(x.blocks.back(), num);
            block ty = get_lower_bits(y.blocks.back(), num);
            if (tx != ty) return tx < ty;
            for (std::size_t i = x.block_num() - 1; i-- > 0;) {
                if (x.blocks[i] != y.blocks[i]) return x.blocks[i] < y.blocks[i];
            }
            return true;
        }
        friend bool operator>(const DynamicBitSet& x, const DynamicBitSet& y) {
            return not (x <= y);
        }
        friend bool operator>=(const DynamicBitSet& x, const DynamicBitSet& y) {
            return not (x < y);
        }

        operator bool() const { return any(); }

        friend DynamicBitSet& operator&=(DynamicBitSet& x, const DynamicBitSet& y) {
            assert(x.n == y.n);
            for (std::size_t i = 0; i < y.block_num(); ++i) x.blocks[i] &= y.blocks[i];
            return x;
        }
        friend DynamicBitSet& operator|=(DynamicBitSet& x, const DynamicBitSet& y) {
            assert(x.n == y.n);
            for (std::size_t i = 0; i < y.block_num(); ++i) x.blocks[i] |= y.blocks[i];
            return x;
        }
        friend DynamicBitSet& operator^=(DynamicBitSet& x, const DynamicBitSet& y) {
            assert(x.n == y.n);
            for (std::size_t i = 0; i < y.block_num(); ++i) x.blocks[i] ^= y.blocks[i];
            return x;
        }
        friend DynamicBitSet operator&(DynamicBitSet x, const DynamicBitSet& y) { x &= y; return x; }
        friend DynamicBitSet operator|(DynamicBitSet x, const DynamicBitSet& y) { x |= y; return x; }
        friend DynamicBitSet operator^(DynamicBitSet x, const DynamicBitSet& y) { x ^= y; return x; }

        friend DynamicBitSet& operator<<=(DynamicBitSet &x, std::size_t shamt) {
            return x = x << shamt;
        }
        friend DynamicBitSet& operator>>=(DynamicBitSet &x, std::size_t shamt) {
            return x = x >> shamt;
        }
        friend DynamicBitSet operator<<(const DynamicBitSet &x, std::size_t shamt) {
            if (shamt >= x.n) return DynamicBitSet(x.size());
            DynamicBitSet res(x.size());
            std::size_t block_shamt = shamt >> log_block_size;
            std::size_t bit_shamt = shamt & (block_size - 1);
            for (std::size_t i = 0; i + block_shamt < res.block_num(); ++i) {
                if (bit_shamt == 0) {
                    res.blocks[i + block_shamt] = x.blocks[i];
                } else {
                    res.blocks[i + block_shamt] |= x.blocks[i] << bit_shamt;
                    if (i + block_shamt + 1 != res.block_num()) {
                        res.blocks[i + block_shamt + 1] |= x.blocks[i] >> (block_size - bit_shamt);
                    }
                }
            }
            return res;
        }
        friend DynamicBitSet operator>>(const DynamicBitSet& x, std::size_t shamt) {
            if (shamt >= x.n) return DynamicBitSet(x.size());
            DynamicBitSet res(x.size());
            std::size_t block_shamt = shamt >> log_block_size;
            std::size_t bit_shamt = shamt & (block_size - 1);
            for (std::size_t i = 0; i + block_shamt < x.block_num(); ++i) {
                if (bit_shamt == 0) {
                    res.blocks[i] = x.blocks[i + block_shamt];
                } else {
                    res.blocks[i] |= x.blocks[i + block_shamt] >> bit_shamt;
                    if (i + block_shamt + 1 != x.block_num()) {
                        res.blocks[i] |= x.blocks[i + block_shamt + 1] << (block_size - bit_shamt);
                    }
                }
            }
            res.range_reset(x.n - shamt, x.n);
            return res;
        }

        DynamicBitSet operator~() const {
            DynamicBitSet neg(n);
            for (std::size_t i = 0; i < block_num(); ++i) neg.blocks[i] = ~blocks[i];
            return neg;
        }

        bool operator[](std::size_t i) const {
            return (blocks[block_index(i)] >> bit_index(i)) & 1;
        }
        bitref operator[](std::size_t i) {
            return { blocks[block_index(i)], bit_index(i) };
        }

        void range_set(std::size_t l, std::size_t r) {
            assert(l <= r and r <= n);
            if (l == r) return;
            std::size_t lb = block_index(l), rb = block_index(r - 1);
            std::size_t li = bit_index(l), ri = bit_index(r);
            if (ri == 0) ri = block_size;
            if (lb == rb) {
                blocks[lb] |= mask_range_bits(~block(0), li, ri);
                return;
            }
            blocks[lb] |= mask_upper_bits(~block(0), block_size - li);
            blocks[rb] |= mask_lower_bits(~block(0), ri);
            for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] = ~block(0);
        }
        void range_reset(std::size_t l, std::size_t r) {
            assert(l <= r and r <= n);
            if (l == r) return;
            std::size_t lb = block_index(l), rb = block_index(r - 1);
            std::size_t li = bit_index(l), ri = bit_index(r);
            if (ri == 0) ri = block_size;
            if (lb == rb) {
                blocks[lb] &= ~mask_range_bits(~block(0), li, ri);
                return;
            }
            blocks[lb] &= ~mask_upper_bits(~block(0), block_size - li);
            blocks[rb] &= ~mask_lower_bits(~block(0), ri);
            for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] = block(0);
        }
        void range_flip(std::size_t l, std::size_t r) {
            assert(l <= r and r <= n);
            if (l == r) return;
            std::size_t lb = block_index(l), rb = block_index(r - 1);
            std::size_t li = bit_index(l), ri = bit_index(r);
            if (ri == 0) ri = block_size;
            if (lb == rb) {
                blocks[lb] ^= mask_range_bits(~block(0), li, ri);
                return;
            }
            blocks[lb] ^= mask_upper_bits(~block(0), block_size - li);
            blocks[rb] ^= mask_lower_bits(~block(0), ri);
            for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] ^= ~block(0);
        }
        void range_update(std::size_t l, std::size_t r, bool val) {
            val ? range_set(l, r) : range_reset(l, r);
        }
        int range_count(std::size_t l, std::size_t r) const {
            assert(l <= r and r <= n);
            if (l == r) return 0;
            std::size_t lb = block_index(l), rb = block_index(r - 1);
            std::size_t li = bit_index(l), ri = bit_index(r);
            if (ri == 0) ri = block_size;
            
            if (lb == rb) {
                return __builtin_popcountll(blocks[lb] & mask_range_bits(~block(0), li, ri));
            }
            int res = 0;
            res += __builtin_popcountll(blocks[lb] & mask_upper_bits(~block(0), block_size - li));
            res += __builtin_popcountll(blocks[rb] & mask_lower_bits(~block(0), ri));
            for (std::size_t i = lb + 1; i < rb; ++i) res += __builtin_popcountll(blocks[i]);
            return res;
        }

        void set() {
            for (block& b : blocks) b = ~block(0);
        }
        void reset() {
            for (block& b : blocks) b = 0;
        }
        bool all() const {
            if (empty()) return true;
            for (std::size_t i = 0; i < block_num() - 1; ++i) {
                if (blocks[i] != ~block(0)) return false;
            }
            const std::size_t num = n - ((block_num() - 1) << log_block_size);
            assert(num);
            const block upper = ((block(1) << (block_size - num)) - 1) << num;
            return (upper | blocks.back()) == ~block(0);
        }
        bool none() const {
            if (empty()) return true;
            for (std::size_t i = 0; i < block_num() - 1; ++i) {
                if (blocks[i] != 0) return false;
            }
            const std::size_t num = n - ((block_num() - 1) << log_block_size);
            return get_lower_bits(blocks.back(), num) == 0;
        }
        bool any() const {
            return not none();
        }
        int count() const {
            if (empty()) return 0;
            int res = 0;
            for (std::size_t i = 0; i < block_num() - 1; ++i) {
                res += __builtin_popcountll(blocks[i]);
            }
            const std::size_t num = n - ((block_num() - 1) << log_block_size);
            return res + __builtin_popcountll(get_lower_bits(blocks.back(), num));
        }

        // Returns the position of first set bit. If there is no such positions, then returns size().
        int find_first() const {
            if (empty()) return size();
            for (std::size_t i = 0; i < block_num(); ++i) {
                if (blocks[i] != 0) return std::min(n, __builtin_ctzll(blocks[i]) | (i << log_block_size));
            }
            return n;
        }
        // Returns the position of first set bit after the given position (exclusive). If there is no such positions, then returns size().
        int find_next(std::size_t pos) const {
            std::size_t i = block_index(++pos);
            if (i >= blocks.size()) return n;
            block upper = mask_upper_bits(blocks[i], block_size - bit_index(pos));
            if (upper != 0) return std::min(n, __builtin_ctzll(upper) | (i << log_block_size));
            while (++i < block_num()) {
                if (blocks[i] != 0) return std::min(n, __builtin_ctzll(blocks[i]) | (i << log_block_size));
            }
            return n;
        }

        bool has_intersection(const DynamicBitSet& y) const {
            if (n > y.n) return y.has_intersection(*this);
            if (empty()) return false;
            for (std::size_t i = 0; i < block_num() - 1; ++i) {
                if (blocks[i] & y.blocks[i]) return true;
            }
            const std::size_t num = n - ((block_num() - 1) << log_block_size);
            return get_lower_bits(blocks.back(), num) & y.blocks[block_num() - 1];
        }
        bool is_disjoint(const DynamicBitSet& y) const {
            return not has_intersection(y);
        }

    private:
        static constexpr std::size_t block_index(std::size_t i) {
            return i >> log_block_size;
        }
        static constexpr std::size_t bit_index(std::size_t i) {
            return i & (block_size - 1);
        }
        static constexpr block get_lower_bits(block b, std::size_t num) {
            return num ? (b << (block_size - num) >> (block_size - num)) : block(0);
        }
        static constexpr block get_upper_bits(block b, std::size_t num) {
            return num ? (b >> (block_size - num)) : block(0);
        }
        static constexpr block get_range_bits(block b, std::size_t l, std::size_t r) {
            return l < r ? b << (block_size - r) >> (block_size - r + l) : block(0);
        }
        static constexpr block mask_lower_bits(block b, std::size_t num) {
            return get_lower_bits(b, num);
        }
        static constexpr block mask_upper_bits(block b, std::size_t num) {
            return num ? (b >> (block_size - num) << (block_size - num)) : block(0);
        }
        static constexpr block mask_range_bits(block b, std::size_t l, std::size_t r) {
            return l < r ? b << (block_size - r) >> (block_size - r + l) << l : block(0);
        }

        std::size_t block_num() const {
            return blocks.size();
        }
    };
} // namespace suisen


#endif // SUISEN_DYNAMIC_BITSET
