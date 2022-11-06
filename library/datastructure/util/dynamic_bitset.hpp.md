---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/linear_algebra/gaussian_elimination_f2.hpp
    title: library/linear_algebra/gaussian_elimination_f2.hpp
  - icon: ':warning:'
    path: library/linear_algebra/matrix_f2.hpp
    title: library/linear_algebra/matrix_f2.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
    title: test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/util/dynamic_bitset.hpp\"\n\n\n\n\
    #include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace suisen {\n    struct DynamicBitSet {\n    private:\n        using\
    \ block = unsigned long long;\n        static constexpr std::size_t block_size\
    \ = std::numeric_limits<block>::digits;\n        static constexpr std::size_t\
    \ log_block_size = __builtin_ctz(block_size);\n\n        struct bitref {\n   \
    \         block& b;\n            std::size_t i;\n            operator bool() const\
    \ { return (b >> i) & 1; }\n            bool test() const { return (b >> i) &\
    \ 1; }\n            void set() { b |= block(1) << i; }\n            void reset()\
    \ { b &= ~(block(1) << i); }\n            void flip() { b ^= block(1) << i; }\n\
    \            bitref& operator&=(bool val) { b &= block(val) << i; return *this;\
    \ }\n            bitref& operator|=(bool val) { b |= block(val) << i; return *this;\
    \ }\n            bitref& operator^=(bool val) { b ^= block(val) << i; return *this;\
    \ }\n            bitref& operator =(bool val) { val ? set() : reset(); return\
    \ *this; }\n            bitref& operator =(const bitref& v) { return (*this) =\
    \ bool(v); }\n        };\n\n        std::size_t n;\n        std::vector<block>\
    \ blocks;\n    public:\n        DynamicBitSet(std::size_t n = 0, bool fill_value\
    \ = false) : n(n), blocks((n + block_size - 1) >> log_block_size, fill_value ?\
    \ ~block(0) : 0) {}\n\n        bool empty() const { return n == 0; }\n       \
    \ int size() const { return n; }\n\n        void resize(std::size_t new_size,\
    \ bool fill_value = false) {\n            std::size_t new_block_num = (new_size\
    \ + block_size - 1) >> log_block_size;\n            if (new_block_num < block_num())\
    \ {\n                n = new_size;\n                return blocks.resize(new_block_num);\n\
    \            }\n            blocks.resize(new_block_num);\n            std::size_t\
    \ old_size = std::exchange(n, new_size);\n            if (old_size <= new_size)\
    \ range_update(old_size, new_size, fill_value);\n        }\n        void push_back(bool\
    \ val) {\n            if (n & (block_size - 1)) {\n                (*this)[n]\
    \ = val;\n            } else {\n                blocks.push_back(val);\n     \
    \       }\n            ++n;\n        }\n        void pop_back() {\n          \
    \  if ((n & (block_size - 1)) == 1) blocks.pop_back();\n            --n;\n   \
    \     }\n\n        friend bool operator==(const DynamicBitSet& x, const DynamicBitSet&\
    \ y) {\n            if (x.n != y.n) return false;\n            if (x.empty())\
    \ return true;\n            for (std::size_t i = 0; i < x.block_num() - 1; ++i)\
    \ {\n                if (x.blocks[i] != y.blocks[i]) return false;\n         \
    \   }\n            const std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);\n\
    \            return get_lower_bits(x.blocks.back(), num) == get_lower_bits(y.blocks.back(),\
    \ num);\n        }\n        friend bool operator!=(const DynamicBitSet& x, const\
    \ DynamicBitSet& y) {\n            return not (x == y);\n        }\n        friend\
    \ bool operator<(const DynamicBitSet& x, const DynamicBitSet& y) {\n         \
    \   assert(x.n == y.n);\n            if (x.empty()) return false;\n          \
    \  std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);\n        \
    \    block tx = get_lower_bits(x.blocks.back(), num);\n            block ty =\
    \ get_lower_bits(y.blocks.back(), num);\n            if (tx != ty) return tx <\
    \ ty;\n            for (std::size_t i = x.block_num() - 1; i-- > 0;) {\n     \
    \           if (x.blocks[i] != y.blocks[i]) return x.blocks[i] < y.blocks[i];\n\
    \            }\n            return false;\n        }\n        friend bool operator<=(const\
    \ DynamicBitSet& x, const DynamicBitSet& y) {\n            assert(x.n == y.n);\n\
    \            if (x.empty()) return true;\n            std::size_t num = x.n -\
    \ ((x.block_num() - 1) << log_block_size);\n            block tx = get_lower_bits(x.blocks.back(),\
    \ num);\n            block ty = get_lower_bits(y.blocks.back(), num);\n      \
    \      if (tx != ty) return tx < ty;\n            for (std::size_t i = x.block_num()\
    \ - 1; i-- > 0;) {\n                if (x.blocks[i] != y.blocks[i]) return x.blocks[i]\
    \ < y.blocks[i];\n            }\n            return true;\n        }\n       \
    \ friend bool operator>(const DynamicBitSet& x, const DynamicBitSet& y) {\n  \
    \          return not (x <= y);\n        }\n        friend bool operator>=(const\
    \ DynamicBitSet& x, const DynamicBitSet& y) {\n            return not (x < y);\n\
    \        }\n\n        operator bool() const { return any(); }\n\n        friend\
    \ DynamicBitSet& operator&=(DynamicBitSet& x, const DynamicBitSet& y) {\n    \
    \        assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] &= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet& operator|=(DynamicBitSet& x, const DynamicBitSet& y) {\n\
    \            assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] |= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet& operator^=(DynamicBitSet& x, const DynamicBitSet& y) {\n\
    \            assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] ^= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet operator&(DynamicBitSet x, const DynamicBitSet& y) { x\
    \ &= y; return x; }\n        friend DynamicBitSet operator|(DynamicBitSet x, const\
    \ DynamicBitSet& y) { x |= y; return x; }\n        friend DynamicBitSet operator^(DynamicBitSet\
    \ x, const DynamicBitSet& y) { x ^= y; return x; }\n\n        friend DynamicBitSet&\
    \ operator<<=(DynamicBitSet &x, std::size_t shamt) {\n            return x = x\
    \ << shamt;\n        }\n        friend DynamicBitSet& operator>>=(DynamicBitSet\
    \ &x, std::size_t shamt) {\n            return x = x >> shamt;\n        }\n  \
    \      friend DynamicBitSet operator<<(const DynamicBitSet &x, std::size_t shamt)\
    \ {\n            if (shamt >= x.n) return DynamicBitSet(x.size());\n         \
    \   DynamicBitSet res(x.size());\n            std::size_t block_shamt = shamt\
    \ >> log_block_size;\n            std::size_t bit_shamt = shamt & (block_size\
    \ - 1);\n            for (std::size_t i = 0; i + block_shamt < res.block_num();\
    \ ++i) {\n                if (bit_shamt == 0) {\n                    res.blocks[i\
    \ + block_shamt] = x.blocks[i];\n                } else {\n                  \
    \  res.blocks[i + block_shamt] |= x.blocks[i] << bit_shamt;\n                \
    \    if (i + block_shamt + 1 != res.block_num()) {\n                        res.blocks[i\
    \ + block_shamt + 1] |= x.blocks[i] >> (block_size - bit_shamt);\n           \
    \         }\n                }\n            }\n            return res;\n     \
    \   }\n        friend DynamicBitSet operator>>(const DynamicBitSet& x, std::size_t\
    \ shamt) {\n            if (shamt >= x.n) return DynamicBitSet(x.size());\n  \
    \          DynamicBitSet res(x.size());\n            std::size_t block_shamt =\
    \ shamt >> log_block_size;\n            std::size_t bit_shamt = shamt & (block_size\
    \ - 1);\n            for (std::size_t i = 0; i + block_shamt < x.block_num();\
    \ ++i) {\n                if (bit_shamt == 0) {\n                    res.blocks[i]\
    \ = x.blocks[i + block_shamt];\n                } else {\n                   \
    \ res.blocks[i] |= x.blocks[i + block_shamt] >> bit_shamt;\n                 \
    \   if (i + block_shamt + 1 != x.block_num()) {\n                        res.blocks[i]\
    \ |= x.blocks[i + block_shamt + 1] << (block_size - bit_shamt);\n            \
    \        }\n                }\n            }\n            return res;\n      \
    \  }\n\n        DynamicBitSet operator~() const {\n            DynamicBitSet neg(n);\n\
    \            for (std::size_t i = 0; i < block_num(); ++i) neg.blocks[i] = ~blocks[i];\n\
    \            return neg;\n        }\n\n        bool operator[](std::size_t i)\
    \ const {\n            return (blocks[block_index(i)] >> bit_index(i)) & 1;\n\
    \        }\n        bitref operator[](std::size_t i) {\n            return { blocks[block_index(i)],\
    \ bit_index(i) };\n        }\n\n        void range_set(std::size_t l, std::size_t\
    \ r) {\n            assert(l <= r and r <= n);\n            if (l == r) return;\n\
    \            std::size_t lb = block_index(l), rb = block_index(r - 1);\n     \
    \       std::size_t li = bit_index(l), ri = bit_index(r);\n            if (ri\
    \ == 0) ri = block_size;\n            if (lb == rb) {\n                blocks[lb]\
    \ |= mask_range_bits(~block(0), li, ri);\n                return;\n          \
    \  }\n            blocks[lb] |= mask_upper_bits(~block(0), block_size - li);\n\
    \            blocks[rb] |= mask_lower_bits(~block(0), ri);\n            for (std::size_t\
    \ i = lb + 1; i < rb; ++i) blocks[i] = ~block(0);\n        }\n        void range_reset(std::size_t\
    \ l, std::size_t r) {\n            assert(l <= r and r <= n);\n            if\
    \ (l == r) return;\n            std::size_t lb = block_index(l), rb = block_index(r\
    \ - 1);\n            std::size_t li = bit_index(l), ri = bit_index(r);\n     \
    \       if (ri == 0) ri = block_size;\n            if (lb == rb) {\n         \
    \       blocks[lb] &= ~mask_range_bits(~block(0), li, ri);\n                return;\n\
    \            }\n            blocks[lb] &= ~mask_upper_bits(~block(0), block_size\
    \ - li);\n            blocks[rb] &= ~mask_lower_bits(~block(0), ri);\n       \
    \     for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] = block(0);\n      \
    \  }\n        void range_flip(std::size_t l, std::size_t r) {\n            assert(l\
    \ <= r and r <= n);\n            if (l == r) return;\n            std::size_t\
    \ lb = block_index(l), rb = block_index(r - 1);\n            std::size_t li =\
    \ bit_index(l), ri = bit_index(r);\n            if (ri == 0) ri = block_size;\n\
    \            if (lb == rb) {\n                blocks[lb] ^= mask_range_bits(~block(0),\
    \ li, ri);\n                return;\n            }\n            blocks[lb] ^=\
    \ mask_upper_bits(~block(0), block_size - li);\n            blocks[rb] ^= mask_lower_bits(~block(0),\
    \ ri);\n            for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] ^= ~block(0);\n\
    \        }\n        void range_update(std::size_t l, std::size_t r, bool val)\
    \ {\n            val ? range_set(l, r) : range_reset(l, r);\n        }\n     \
    \   int range_count(std::size_t l, std::size_t r) const {\n            assert(l\
    \ <= r and r <= n);\n            if (l == r) return 0;\n            std::size_t\
    \ lb = block_index(l), rb = block_index(r - 1);\n            std::size_t li =\
    \ bit_index(l), ri = bit_index(r);\n            if (ri == 0) ri = block_size;\n\
    \            \n            if (lb == rb) {\n                return __builtin_popcountll(blocks[lb]\
    \ & mask_range_bits(~block(0), li, ri));\n            }\n            int res =\
    \ 0;\n            res += __builtin_popcountll(blocks[lb] & mask_upper_bits(~block(0),\
    \ block_size - li));\n            res += __builtin_popcountll(blocks[rb] & mask_lower_bits(~block(0),\
    \ ri));\n            for (std::size_t i = lb + 1; i < rb; ++i) res += __builtin_popcountll(blocks[i]);\n\
    \            return res;\n        }\n\n        void set() {\n            for (block&\
    \ b : blocks) b = ~block(0);\n        }\n        void reset() {\n            for\
    \ (block& b : blocks) b = 0;\n        }\n        bool all() const {\n        \
    \    if (empty()) return true;\n            for (std::size_t i = 0; i < block_num()\
    \ - 1; ++i) {\n                if (blocks[i] != ~block(0)) return false;\n   \
    \         }\n            const std::size_t num = n - ((block_num() - 1) << log_block_size);\n\
    \            assert(num);\n            const block upper = ((block(1) << (block_size\
    \ - num)) - 1) << num;\n            return (upper | blocks.back()) == ~block(0);\n\
    \        }\n        bool none() const {\n            if (empty()) return true;\n\
    \            for (std::size_t i = 0; i < block_num() - 1; ++i) {\n           \
    \     if (blocks[i] != 0) return false;\n            }\n            const std::size_t\
    \ num = n - ((block_num() - 1) << log_block_size);\n            return get_lower_bits(blocks.back(),\
    \ num) == 0;\n        }\n        bool any() const {\n            return not none();\n\
    \        }\n        int count() const {\n            if (empty()) return 0;\n\
    \            int res = 0;\n            for (std::size_t i = 0; i < block_num()\
    \ - 1; ++i) {\n                res += __builtin_popcountll(blocks[i]);\n     \
    \       }\n            const std::size_t num = n - ((block_num() - 1) << log_block_size);\n\
    \            return res + __builtin_popcountll(get_lower_bits(blocks.back(), num));\n\
    \        }\n\n        // Returns the position of first set bit. If there is no\
    \ such positions, then returns size().\n        int find_first() const {\n   \
    \         if (empty()) return size();\n            for (std::size_t i = 0; i <\
    \ block_num(); ++i) {\n                if (blocks[i] != 0) return std::min(n,\
    \ __builtin_ctzll(blocks[i]) | (i << log_block_size));\n            }\n      \
    \      return n;\n        }\n        // Returns the position of first set bit\
    \ after the given position (exclusive). If there is no such positions, then returns\
    \ size().\n        int find_next(std::size_t pos) const {\n            std::size_t\
    \ i = block_index(++pos);\n            if (i >= blocks.size()) return n;\n   \
    \         block upper = mask_upper_bits(blocks[i], block_size - bit_index(pos));\n\
    \            if (upper != 0) return std::min(n, __builtin_ctzll(upper) | (i <<\
    \ log_block_size));\n            while (++i < block_num()) {\n               \
    \ if (blocks[i] != 0) return std::min(n, __builtin_ctzll(blocks[i]) | (i << log_block_size));\n\
    \            }\n            return n;\n        }\n\n        bool has_intersection(const\
    \ DynamicBitSet& y) const {\n            if (n > y.n) return y.has_intersection(*this);\n\
    \            if (empty()) return false;\n            for (std::size_t i = 0; i\
    \ < block_num() - 1; ++i) {\n                if (blocks[i] & y.blocks[i]) return\
    \ true;\n            }\n            const std::size_t num = n - ((block_num()\
    \ - 1) << log_block_size);\n            return get_lower_bits(blocks.back(), num)\
    \ & y.blocks[block_num() - 1];\n        }\n        bool is_disjoint(const DynamicBitSet&\
    \ y) const {\n            return not has_intersection(y);\n        }\n\n    private:\n\
    \        static constexpr std::size_t block_index(std::size_t i) {\n         \
    \   return i >> log_block_size;\n        }\n        static constexpr std::size_t\
    \ bit_index(std::size_t i) {\n            return i & (block_size - 1);\n     \
    \   }\n        static constexpr block get_lower_bits(block b, std::size_t num)\
    \ {\n            return num ? (b << (block_size - num) >> (block_size - num))\
    \ : block(0);\n        }\n        static constexpr block get_upper_bits(block\
    \ b, std::size_t num) {\n            return num ? (b >> (block_size - num)) :\
    \ block(0);\n        }\n        static constexpr block get_range_bits(block b,\
    \ std::size_t l, std::size_t r) {\n            return l < r ? b << (block_size\
    \ - r) >> (block_size - r + l) : block(0);\n        }\n        static constexpr\
    \ block mask_lower_bits(block b, std::size_t num) {\n            return get_lower_bits(b,\
    \ num);\n        }\n        static constexpr block mask_upper_bits(block b, std::size_t\
    \ num) {\n            return num ? (b >> (block_size - num) << (block_size - num))\
    \ : block(0);\n        }\n        static constexpr block mask_range_bits(block\
    \ b, std::size_t l, std::size_t r) {\n            return l < r ? b << (block_size\
    \ - r) >> (block_size - r + l) << l : block(0);\n        }\n\n        std::size_t\
    \ block_num() const {\n            return blocks.size();\n        }\n    };\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DYNAMIC_BITSET\n#define SUISEN_DYNAMIC_BITSET\n\n#include\
    \ <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ suisen {\n    struct DynamicBitSet {\n    private:\n        using block = unsigned\
    \ long long;\n        static constexpr std::size_t block_size = std::numeric_limits<block>::digits;\n\
    \        static constexpr std::size_t log_block_size = __builtin_ctz(block_size);\n\
    \n        struct bitref {\n            block& b;\n            std::size_t i;\n\
    \            operator bool() const { return (b >> i) & 1; }\n            bool\
    \ test() const { return (b >> i) & 1; }\n            void set() { b |= block(1)\
    \ << i; }\n            void reset() { b &= ~(block(1) << i); }\n            void\
    \ flip() { b ^= block(1) << i; }\n            bitref& operator&=(bool val) { b\
    \ &= block(val) << i; return *this; }\n            bitref& operator|=(bool val)\
    \ { b |= block(val) << i; return *this; }\n            bitref& operator^=(bool\
    \ val) { b ^= block(val) << i; return *this; }\n            bitref& operator =(bool\
    \ val) { val ? set() : reset(); return *this; }\n            bitref& operator\
    \ =(const bitref& v) { return (*this) = bool(v); }\n        };\n\n        std::size_t\
    \ n;\n        std::vector<block> blocks;\n    public:\n        DynamicBitSet(std::size_t\
    \ n = 0, bool fill_value = false) : n(n), blocks((n + block_size - 1) >> log_block_size,\
    \ fill_value ? ~block(0) : 0) {}\n\n        bool empty() const { return n == 0;\
    \ }\n        int size() const { return n; }\n\n        void resize(std::size_t\
    \ new_size, bool fill_value = false) {\n            std::size_t new_block_num\
    \ = (new_size + block_size - 1) >> log_block_size;\n            if (new_block_num\
    \ < block_num()) {\n                n = new_size;\n                return blocks.resize(new_block_num);\n\
    \            }\n            blocks.resize(new_block_num);\n            std::size_t\
    \ old_size = std::exchange(n, new_size);\n            if (old_size <= new_size)\
    \ range_update(old_size, new_size, fill_value);\n        }\n        void push_back(bool\
    \ val) {\n            if (n & (block_size - 1)) {\n                (*this)[n]\
    \ = val;\n            } else {\n                blocks.push_back(val);\n     \
    \       }\n            ++n;\n        }\n        void pop_back() {\n          \
    \  if ((n & (block_size - 1)) == 1) blocks.pop_back();\n            --n;\n   \
    \     }\n\n        friend bool operator==(const DynamicBitSet& x, const DynamicBitSet&\
    \ y) {\n            if (x.n != y.n) return false;\n            if (x.empty())\
    \ return true;\n            for (std::size_t i = 0; i < x.block_num() - 1; ++i)\
    \ {\n                if (x.blocks[i] != y.blocks[i]) return false;\n         \
    \   }\n            const std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);\n\
    \            return get_lower_bits(x.blocks.back(), num) == get_lower_bits(y.blocks.back(),\
    \ num);\n        }\n        friend bool operator!=(const DynamicBitSet& x, const\
    \ DynamicBitSet& y) {\n            return not (x == y);\n        }\n        friend\
    \ bool operator<(const DynamicBitSet& x, const DynamicBitSet& y) {\n         \
    \   assert(x.n == y.n);\n            if (x.empty()) return false;\n          \
    \  std::size_t num = x.n - ((x.block_num() - 1) << log_block_size);\n        \
    \    block tx = get_lower_bits(x.blocks.back(), num);\n            block ty =\
    \ get_lower_bits(y.blocks.back(), num);\n            if (tx != ty) return tx <\
    \ ty;\n            for (std::size_t i = x.block_num() - 1; i-- > 0;) {\n     \
    \           if (x.blocks[i] != y.blocks[i]) return x.blocks[i] < y.blocks[i];\n\
    \            }\n            return false;\n        }\n        friend bool operator<=(const\
    \ DynamicBitSet& x, const DynamicBitSet& y) {\n            assert(x.n == y.n);\n\
    \            if (x.empty()) return true;\n            std::size_t num = x.n -\
    \ ((x.block_num() - 1) << log_block_size);\n            block tx = get_lower_bits(x.blocks.back(),\
    \ num);\n            block ty = get_lower_bits(y.blocks.back(), num);\n      \
    \      if (tx != ty) return tx < ty;\n            for (std::size_t i = x.block_num()\
    \ - 1; i-- > 0;) {\n                if (x.blocks[i] != y.blocks[i]) return x.blocks[i]\
    \ < y.blocks[i];\n            }\n            return true;\n        }\n       \
    \ friend bool operator>(const DynamicBitSet& x, const DynamicBitSet& y) {\n  \
    \          return not (x <= y);\n        }\n        friend bool operator>=(const\
    \ DynamicBitSet& x, const DynamicBitSet& y) {\n            return not (x < y);\n\
    \        }\n\n        operator bool() const { return any(); }\n\n        friend\
    \ DynamicBitSet& operator&=(DynamicBitSet& x, const DynamicBitSet& y) {\n    \
    \        assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] &= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet& operator|=(DynamicBitSet& x, const DynamicBitSet& y) {\n\
    \            assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] |= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet& operator^=(DynamicBitSet& x, const DynamicBitSet& y) {\n\
    \            assert(x.n == y.n);\n            for (std::size_t i = 0; i < y.block_num();\
    \ ++i) x.blocks[i] ^= y.blocks[i];\n            return x;\n        }\n       \
    \ friend DynamicBitSet operator&(DynamicBitSet x, const DynamicBitSet& y) { x\
    \ &= y; return x; }\n        friend DynamicBitSet operator|(DynamicBitSet x, const\
    \ DynamicBitSet& y) { x |= y; return x; }\n        friend DynamicBitSet operator^(DynamicBitSet\
    \ x, const DynamicBitSet& y) { x ^= y; return x; }\n\n        friend DynamicBitSet&\
    \ operator<<=(DynamicBitSet &x, std::size_t shamt) {\n            return x = x\
    \ << shamt;\n        }\n        friend DynamicBitSet& operator>>=(DynamicBitSet\
    \ &x, std::size_t shamt) {\n            return x = x >> shamt;\n        }\n  \
    \      friend DynamicBitSet operator<<(const DynamicBitSet &x, std::size_t shamt)\
    \ {\n            if (shamt >= x.n) return DynamicBitSet(x.size());\n         \
    \   DynamicBitSet res(x.size());\n            std::size_t block_shamt = shamt\
    \ >> log_block_size;\n            std::size_t bit_shamt = shamt & (block_size\
    \ - 1);\n            for (std::size_t i = 0; i + block_shamt < res.block_num();\
    \ ++i) {\n                if (bit_shamt == 0) {\n                    res.blocks[i\
    \ + block_shamt] = x.blocks[i];\n                } else {\n                  \
    \  res.blocks[i + block_shamt] |= x.blocks[i] << bit_shamt;\n                \
    \    if (i + block_shamt + 1 != res.block_num()) {\n                        res.blocks[i\
    \ + block_shamt + 1] |= x.blocks[i] >> (block_size - bit_shamt);\n           \
    \         }\n                }\n            }\n            return res;\n     \
    \   }\n        friend DynamicBitSet operator>>(const DynamicBitSet& x, std::size_t\
    \ shamt) {\n            if (shamt >= x.n) return DynamicBitSet(x.size());\n  \
    \          DynamicBitSet res(x.size());\n            std::size_t block_shamt =\
    \ shamt >> log_block_size;\n            std::size_t bit_shamt = shamt & (block_size\
    \ - 1);\n            for (std::size_t i = 0; i + block_shamt < x.block_num();\
    \ ++i) {\n                if (bit_shamt == 0) {\n                    res.blocks[i]\
    \ = x.blocks[i + block_shamt];\n                } else {\n                   \
    \ res.blocks[i] |= x.blocks[i + block_shamt] >> bit_shamt;\n                 \
    \   if (i + block_shamt + 1 != x.block_num()) {\n                        res.blocks[i]\
    \ |= x.blocks[i + block_shamt + 1] << (block_size - bit_shamt);\n            \
    \        }\n                }\n            }\n            return res;\n      \
    \  }\n\n        DynamicBitSet operator~() const {\n            DynamicBitSet neg(n);\n\
    \            for (std::size_t i = 0; i < block_num(); ++i) neg.blocks[i] = ~blocks[i];\n\
    \            return neg;\n        }\n\n        bool operator[](std::size_t i)\
    \ const {\n            return (blocks[block_index(i)] >> bit_index(i)) & 1;\n\
    \        }\n        bitref operator[](std::size_t i) {\n            return { blocks[block_index(i)],\
    \ bit_index(i) };\n        }\n\n        void range_set(std::size_t l, std::size_t\
    \ r) {\n            assert(l <= r and r <= n);\n            if (l == r) return;\n\
    \            std::size_t lb = block_index(l), rb = block_index(r - 1);\n     \
    \       std::size_t li = bit_index(l), ri = bit_index(r);\n            if (ri\
    \ == 0) ri = block_size;\n            if (lb == rb) {\n                blocks[lb]\
    \ |= mask_range_bits(~block(0), li, ri);\n                return;\n          \
    \  }\n            blocks[lb] |= mask_upper_bits(~block(0), block_size - li);\n\
    \            blocks[rb] |= mask_lower_bits(~block(0), ri);\n            for (std::size_t\
    \ i = lb + 1; i < rb; ++i) blocks[i] = ~block(0);\n        }\n        void range_reset(std::size_t\
    \ l, std::size_t r) {\n            assert(l <= r and r <= n);\n            if\
    \ (l == r) return;\n            std::size_t lb = block_index(l), rb = block_index(r\
    \ - 1);\n            std::size_t li = bit_index(l), ri = bit_index(r);\n     \
    \       if (ri == 0) ri = block_size;\n            if (lb == rb) {\n         \
    \       blocks[lb] &= ~mask_range_bits(~block(0), li, ri);\n                return;\n\
    \            }\n            blocks[lb] &= ~mask_upper_bits(~block(0), block_size\
    \ - li);\n            blocks[rb] &= ~mask_lower_bits(~block(0), ri);\n       \
    \     for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] = block(0);\n      \
    \  }\n        void range_flip(std::size_t l, std::size_t r) {\n            assert(l\
    \ <= r and r <= n);\n            if (l == r) return;\n            std::size_t\
    \ lb = block_index(l), rb = block_index(r - 1);\n            std::size_t li =\
    \ bit_index(l), ri = bit_index(r);\n            if (ri == 0) ri = block_size;\n\
    \            if (lb == rb) {\n                blocks[lb] ^= mask_range_bits(~block(0),\
    \ li, ri);\n                return;\n            }\n            blocks[lb] ^=\
    \ mask_upper_bits(~block(0), block_size - li);\n            blocks[rb] ^= mask_lower_bits(~block(0),\
    \ ri);\n            for (std::size_t i = lb + 1; i < rb; ++i) blocks[i] ^= ~block(0);\n\
    \        }\n        void range_update(std::size_t l, std::size_t r, bool val)\
    \ {\n            val ? range_set(l, r) : range_reset(l, r);\n        }\n     \
    \   int range_count(std::size_t l, std::size_t r) const {\n            assert(l\
    \ <= r and r <= n);\n            if (l == r) return 0;\n            std::size_t\
    \ lb = block_index(l), rb = block_index(r - 1);\n            std::size_t li =\
    \ bit_index(l), ri = bit_index(r);\n            if (ri == 0) ri = block_size;\n\
    \            \n            if (lb == rb) {\n                return __builtin_popcountll(blocks[lb]\
    \ & mask_range_bits(~block(0), li, ri));\n            }\n            int res =\
    \ 0;\n            res += __builtin_popcountll(blocks[lb] & mask_upper_bits(~block(0),\
    \ block_size - li));\n            res += __builtin_popcountll(blocks[rb] & mask_lower_bits(~block(0),\
    \ ri));\n            for (std::size_t i = lb + 1; i < rb; ++i) res += __builtin_popcountll(blocks[i]);\n\
    \            return res;\n        }\n\n        void set() {\n            for (block&\
    \ b : blocks) b = ~block(0);\n        }\n        void reset() {\n            for\
    \ (block& b : blocks) b = 0;\n        }\n        bool all() const {\n        \
    \    if (empty()) return true;\n            for (std::size_t i = 0; i < block_num()\
    \ - 1; ++i) {\n                if (blocks[i] != ~block(0)) return false;\n   \
    \         }\n            const std::size_t num = n - ((block_num() - 1) << log_block_size);\n\
    \            assert(num);\n            const block upper = ((block(1) << (block_size\
    \ - num)) - 1) << num;\n            return (upper | blocks.back()) == ~block(0);\n\
    \        }\n        bool none() const {\n            if (empty()) return true;\n\
    \            for (std::size_t i = 0; i < block_num() - 1; ++i) {\n           \
    \     if (blocks[i] != 0) return false;\n            }\n            const std::size_t\
    \ num = n - ((block_num() - 1) << log_block_size);\n            return get_lower_bits(blocks.back(),\
    \ num) == 0;\n        }\n        bool any() const {\n            return not none();\n\
    \        }\n        int count() const {\n            if (empty()) return 0;\n\
    \            int res = 0;\n            for (std::size_t i = 0; i < block_num()\
    \ - 1; ++i) {\n                res += __builtin_popcountll(blocks[i]);\n     \
    \       }\n            const std::size_t num = n - ((block_num() - 1) << log_block_size);\n\
    \            return res + __builtin_popcountll(get_lower_bits(blocks.back(), num));\n\
    \        }\n\n        // Returns the position of first set bit. If there is no\
    \ such positions, then returns size().\n        int find_first() const {\n   \
    \         if (empty()) return size();\n            for (std::size_t i = 0; i <\
    \ block_num(); ++i) {\n                if (blocks[i] != 0) return std::min(n,\
    \ __builtin_ctzll(blocks[i]) | (i << log_block_size));\n            }\n      \
    \      return n;\n        }\n        // Returns the position of first set bit\
    \ after the given position (exclusive). If there is no such positions, then returns\
    \ size().\n        int find_next(std::size_t pos) const {\n            std::size_t\
    \ i = block_index(++pos);\n            if (i >= blocks.size()) return n;\n   \
    \         block upper = mask_upper_bits(blocks[i], block_size - bit_index(pos));\n\
    \            if (upper != 0) return std::min(n, __builtin_ctzll(upper) | (i <<\
    \ log_block_size));\n            while (++i < block_num()) {\n               \
    \ if (blocks[i] != 0) return std::min(n, __builtin_ctzll(blocks[i]) | (i << log_block_size));\n\
    \            }\n            return n;\n        }\n\n        bool has_intersection(const\
    \ DynamicBitSet& y) const {\n            if (n > y.n) return y.has_intersection(*this);\n\
    \            if (empty()) return false;\n            for (std::size_t i = 0; i\
    \ < block_num() - 1; ++i) {\n                if (blocks[i] & y.blocks[i]) return\
    \ true;\n            }\n            const std::size_t num = n - ((block_num()\
    \ - 1) << log_block_size);\n            return get_lower_bits(blocks.back(), num)\
    \ & y.blocks[block_num() - 1];\n        }\n        bool is_disjoint(const DynamicBitSet&\
    \ y) const {\n            return not has_intersection(y);\n        }\n\n    private:\n\
    \        static constexpr std::size_t block_index(std::size_t i) {\n         \
    \   return i >> log_block_size;\n        }\n        static constexpr std::size_t\
    \ bit_index(std::size_t i) {\n            return i & (block_size - 1);\n     \
    \   }\n        static constexpr block get_lower_bits(block b, std::size_t num)\
    \ {\n            return num ? (b << (block_size - num) >> (block_size - num))\
    \ : block(0);\n        }\n        static constexpr block get_upper_bits(block\
    \ b, std::size_t num) {\n            return num ? (b >> (block_size - num)) :\
    \ block(0);\n        }\n        static constexpr block get_range_bits(block b,\
    \ std::size_t l, std::size_t r) {\n            return l < r ? b << (block_size\
    \ - r) >> (block_size - r + l) : block(0);\n        }\n        static constexpr\
    \ block mask_lower_bits(block b, std::size_t num) {\n            return get_lower_bits(b,\
    \ num);\n        }\n        static constexpr block mask_upper_bits(block b, std::size_t\
    \ num) {\n            return num ? (b >> (block_size - num) << (block_size - num))\
    \ : block(0);\n        }\n        static constexpr block mask_range_bits(block\
    \ b, std::size_t l, std::size_t r) {\n            return l < r ? b << (block_size\
    \ - r) >> (block_size - r + l) << l : block(0);\n        }\n\n        std::size_t\
    \ block_num() const {\n            return blocks.size();\n        }\n    };\n\
    } // namespace suisen\n\n\n#endif // SUISEN_DYNAMIC_BITSET\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/util/dynamic_bitset.hpp
  requiredBy:
  - library/linear_algebra/gaussian_elimination_f2.hpp
  - library/linear_algebra/matrix_f2.hpp
  timestamp: '2022-11-06 23:07:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
documentation_of: library/datastructure/util/dynamic_bitset.hpp
layout: document
title: Dynamic Bitset
---
## Dynamic Bitset

bit 長を動的に管理する bitset。あんまりテストできてなかったはず。
