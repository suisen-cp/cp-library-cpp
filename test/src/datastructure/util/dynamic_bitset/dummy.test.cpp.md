---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/util/dynamic_bitset.hpp
    title: Dynamic Bitset
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/datastructure/util/dynamic_bitset/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <bitset>\n#include <iostream>\n\n#line 1 \"library/datastructure/util/dynamic_bitset.hpp\"\
    \n\n\n\n#include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
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
    } // namespace suisen\n\n\n\n#line 7 \"test/src/datastructure/util/dynamic_bitset/dummy.test.cpp\"\
    \n\nusing suisen::DynamicBitSet;\n\ntemplate <std::size_t n>\nbool operator==(const\
    \ DynamicBitSet& dbs, const std::bitset<n>& bs) {\n    if (dbs.size() != int(n))\
    \ return false;\n    for (std::size_t i = 0; i < n; ++i) if (dbs[i] != bs[i])\
    \ return false;\n    return true;\n}\ntemplate <std::size_t n>\nbool operator==(const\
    \ std::bitset<n>& bs, const DynamicBitSet& dbs) {\n    return dbs == bs;\n}\n\
    template <std::size_t n>\nbool operator!=(const DynamicBitSet& dbs, const std::bitset<n>&\
    \ bs) {\n    return not (dbs == bs);\n}\ntemplate <std::size_t n>\nbool operator!=(const\
    \ std::bitset<n>& bs, const DynamicBitSet& dbs) {\n    return dbs != bs;\n}\n\n\
    void test_empty() {\n    assert(DynamicBitSet(0).empty());\n    assert(not DynamicBitSet(1).empty());\n\
    }\n\nvoid test_size() {\n    assert(DynamicBitSet(0).size() == 0);\n    assert(DynamicBitSet(1).size()\
    \ == 1);\n    assert(DynamicBitSet(64).size() == 64);\n}\n\nvoid test_resize()\
    \ {\n    DynamicBitSet bs;\n    bs.resize(35, true);\n    assert(bs.size() ==\
    \ 35);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n    bs.resize(1026, false);\n\
    \    assert(bs.size() == 1026);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 1026; ++i) assert(not bs[i]);\n    bs.resize(78);\n\
    \    assert(bs.size() == 78);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 78; ++i) assert(not bs[i]);\n    bs.resize(512, true);\n\
    \    assert(bs.size() == 512);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 78; ++i) assert(not bs[i]);\n    for (int i = 78; i\
    \ < 512; ++i) assert(bs[i]);\n    bs.resize(128, false);\n    assert(bs.size()\
    \ == 128);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n    for (int i =\
    \ 35; i < 78; ++i) assert(not bs[i]);\n    for (int i = 78; i < 128; ++i) assert(bs[i]);\n\
    }\n\nvoid test_push_back() {\n    DynamicBitSet bs;\n    for (int i = 0; i < 1000;\
    \ ++i) {\n        bs.push_back(i & 1);\n        assert(bs.size() == i + 1);\n\
    \        for (int j = 0; j <= i; ++j) assert(bs[j] == (j & 1));\n    }\n}\n\n\
    void test_pop_back() {\n    DynamicBitSet bs;\n    for (int i = 0; i < 1000; ++i)\
    \ {\n        bs.push_back(i & 1);\n    }\n    for (int i = 0; i < 1000; ++i) {\n\
    \        bs.pop_back();\n        assert(bs.size() == 999 - i);\n        for (int\
    \ j = 0; j < 999 - i; ++j) assert(bs[j] == (j & 1));\n    }\n}\n\nvoid test_eq()\
    \ {\n    DynamicBitSet x(10, true);\n    DynamicBitSet y(10);\n    for (int i\
    \ = 0; i < 10; ++i) y[i] = true;\n    assert(x == y);\n    x.resize(516, false);\n\
    \    y.resize(516, false);\n    assert(x == y);\n    x.resize(100);\n    y.resize(200);\n\
    \    x.resize(300, true);\n    y.resize(300, true);\n    for (int i = 100; i <\
    \ 200; ++i) y[i] = true;\n    assert(x == y);\n}\n\nvoid test_neq() {\n    DynamicBitSet\
    \ x(10);\n    DynamicBitSet y;\n    assert(x != y);\n    y.resize(5);\n    assert(x\
    \ != y);\n    y.resize(64, true);\n    assert(x != y);\n    y.resize(10);\n  \
    \  assert(x != y);\n    x.resize(500);\n    y.resize(500);\n    for (int i = 5;\
    \ i < 10; ++i) x[i] = true;\n    assert(x == y);\n    y[499] = true;\n    assert(x\
    \ != y);\n    y[499] = false;\n    assert(x == y);\n    y[256] = true;\n    assert(x\
    \ != y);\n    y[256] = false;\n    assert(x == y);\n    y[255] = true;\n    assert(x\
    \ != y);\n}\n\nvoid test_lt() {\n    DynamicBitSet x(100), y(100);\n    assert(not\
    \ (x < y));\n    x[56] = true;\n    assert(not (x < y));\n    y[56] = true;\n\
    \    assert(not (x < y));\n    y[99] = true;\n    assert(x < y);\n    x.resize(200),\
    \ y.resize(200);\n    x[100] = true;\n    assert(not (x < y));\n    y[100] = true;\n\
    \    assert(x < y);\n    x[99] = true;\n    assert(not (x < y));\n    y[199] =\
    \ true;\n    assert(x < y);\n    y[199] = false;\n    y[128] = true;\n    assert(x\
    \ < y);\n    y[128] = false;\n    y[127] = true;\n    assert(x < y);\n}\n\nvoid\
    \ test_leq() {\n    DynamicBitSet x(100), y(100);\n    assert(x <= y);\n    x[56]\
    \ = true;\n    assert(not (x <= y));\n    y[56] = true;\n    assert(x <= y);\n\
    \    y[99] = true;\n    assert(x <= y);\n    x.resize(200), y.resize(200);\n \
    \   x[100] = true;\n    assert(not (x <= y));\n    y[100] = true;\n    assert(x\
    \ <= y);\n    x[99] = true;\n    assert(x <= y);\n    y[199] = true;\n    assert(x\
    \ <= y);\n    y[199] = false;\n    y[128] = true;\n    assert(x <= y);\n    y[128]\
    \ = false;\n    y[127] = true;\n    assert(x <= y);\n}\nvoid test_gt() {\n   \
    \ DynamicBitSet x(100), y(100);\n    assert(not (x > y));\n    x[56] = true;\n\
    \    assert(x > y);\n    y[56] = true;\n    assert(not (x > y));\n    y[99] =\
    \ true;\n    assert(not (x > y));\n    x.resize(200), y.resize(200);\n    x[100]\
    \ = true;\n    assert(x > y);\n    y[100] = true;\n    assert(not (x > y));\n\
    \    x[99] = true;\n    assert(not (x > y));\n    y[199] = true;\n    assert(not\
    \ (x > y));\n    y[199] = false;\n    y[128] = true;\n    assert(not (x > y));\n\
    \    y[128] = false;\n    y[127] = true;\n    assert(not (x > y));\n}\nvoid test_geq()\
    \ {\n    DynamicBitSet x(100), y(100);\n    assert(x >= y);\n    x[56] = true;\n\
    \    assert(x >= y);\n    y[56] = true;\n    assert(x >= y);\n    y[99] = true;\n\
    \    assert(not (x >= y));\n    x.resize(200), y.resize(200);\n    x[100] = true;\n\
    \    assert(x >= y);\n    y[100] = true;\n    assert(not (x >= y));\n    x[99]\
    \ = true;\n    assert(x >= y);\n    y[199] = true;\n    assert(not (x >= y));\n\
    \    y[199] = false;\n    y[128] = true;\n    assert(not (x >= y));\n    y[128]\
    \ = false;\n    y[127] = true;\n    assert(not (x >= y));\n}\n\nvoid test_cast_bool()\
    \ {\n    DynamicBitSet x;\n    assert(not x);\n    x.resize(100);\n    assert(not\
    \ x);\n    x[99] = true;\n    assert(x);\n}\n\nvoid test_and() {\n    constexpr\
    \ int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet dbs1(n), dbs2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3 == 0;\n        dbs1[i]\
    \ = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i) {\n        bs2[i] = i\
    \ % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto bs = bs1 & bs2;\n\
    \    auto dbs = dbs1 & dbs2;\n    assert(bs == dbs);\n}\nvoid test_or() {\n  \
    \  constexpr int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet dbs1(n),\
    \ dbs2(n);\n    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3 == 0;\n\
    \        dbs1[i] = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i) {\n   \
    \     bs2[i] = i % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto bs\
    \ = bs1 | bs2;\n    auto dbs = dbs1 | dbs2;\n    assert(bs == dbs);\n}\nvoid test_xor()\
    \ {\n    constexpr int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet\
    \ dbs1(n), dbs2(n);\n    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3\
    \ == 0;\n        dbs1[i] = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i)\
    \ {\n        bs2[i] = i % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto\
    \ bs = bs1 ^ bs2;\n    auto dbs = dbs1 ^ dbs2;\n    assert(bs == dbs);\n}\nvoid\
    \ test_shift_r() {\n    constexpr int n = 353;\n    std::bitset<n> bs;\n    DynamicBitSet\
    \ dbs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n  \
    \      dbs[i] = i % 3 == 0;\n    }\n\n    for (std::size_t i = 0; i < n; ++i)\
    \ {\n        assert((bs >> i) == (dbs >> i));\n    }\n}\nvoid test_shift_l() {\n\
    \    constexpr int n = 353;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i]\
    \ = i % 3 == 0;\n    }\n\n    for (std::size_t i = 0; i < n; ++i) {\n        assert((bs\
    \ << i) == (dbs << i));\n    }\n}\nvoid test_neg() {\n    constexpr int n = 353;\n\
    \    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i = 0; i < n;\
    \ ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n    }\n\n\
    \    assert(~bs == ~dbs);\n}\n\nvoid test_get_set() {\n    constexpr int n = 2349;\n\
    \    DynamicBitSet bs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] =\
    \ i % 3 != 0;\n    }\n    for (int i = 0; i < n; ++i) {\n        assert(bs[i]\
    \ == (i % 3 != 0));\n    }\n}\n\nvoid test_range_set() {\n    constexpr int n\
    \ = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i =\
    \ 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n\
    \    }\n\n    auto range_set_dbs = [&](int l, int r) {\n        auto dbs2 = dbs;\n\
    \        dbs2.range_set(l, r);\n        return dbs2;\n    };\n    auto range_set_bs\
    \ = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int i = l; i < r;\
    \ ++i) bs2[i] = true;\n        return bs2;\n    };\n\n    for (int l = 0; l <=\
    \ n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_set_bs(l, r) ==\
    \ range_set_dbs(l, r));\n    }\n}\nvoid test_range_reset() {\n    constexpr int\
    \ n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i\
    \ = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n\
    \    }\n\n    auto range_reset_dbs = [&](int l, int r) {\n        auto dbs2 =\
    \ dbs;\n        dbs2.range_reset(l, r);\n        return dbs2;\n    };\n    auto\
    \ range_reset_bs = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int\
    \ i = l; i < r; ++i) bs2[i] = false;\n        return bs2;\n    };\n\n    for (int\
    \ l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_reset_bs(l,\
    \ r) == range_reset_dbs(l, r));\n    }\n}\nvoid test_range_flip() {\n    constexpr\
    \ int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 ==\
    \ 0;\n    }\n\n    auto range_flip_dbs = [&](int l, int r) {\n        auto dbs2\
    \ = dbs;\n        dbs2.range_flip(l, r);\n        return dbs2;\n    };\n    auto\
    \ range_flip_bs = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int\
    \ i = l; i < r; ++i) bs2[i].flip();\n        return bs2;\n    };\n\n    for (int\
    \ l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_flip_bs(l,\
    \ r) == range_flip_dbs(l, r));\n    }\n}\n\nvoid test_range_update() {\n    constexpr\
    \ int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 ==\
    \ 0;\n    }\n\n    auto range_update_dbs = [&](int l, int r, bool val) {\n   \
    \     auto dbs2 = dbs;\n        dbs2.range_update(l, r, val);\n        return\
    \ dbs2;\n    };\n    auto range_update_bs = [&](int l, int r, bool val) {\n  \
    \      auto bs2 = bs;\n        for (int i = l; i < r; ++i) bs2[i] = val;\n   \
    \     return bs2;\n    };\n\n    for (bool b : { false, true }) {\n        for\
    \ (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n            assert(range_update_bs(l,\
    \ r, b) == range_update_dbs(l, r, b));\n        }\n    }\n}\nvoid test_range_count()\
    \ {\n    constexpr int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i]\
    \ = i % 3 == 0;\n    }\n\n    auto range_count_dbs = [&](int l, int r) {\n   \
    \     return dbs.range_count(l, r);\n    };\n    auto range_count_bs = [&](int\
    \ l, int r) {\n        int res = 0;\n        for (int i = l; i < r; ++i) res +=\
    \ bs[i];\n        return res;\n    };\n\n    for (int l = 0; l <= n; ++l) for\
    \ (int r = l; r <= n; ++r) {\n        assert(range_count_bs(l, r) == range_count_dbs(l,\
    \ r));\n    }\n}\n\nvoid test_all() {\n    DynamicBitSet x;\n    assert(x.all());\n\
    \    x.push_back(true);\n    assert(x.all());\n    x[0] = false;\n    assert(not\
    \ x.all());\n    x.resize(129, true);\n    assert(not x.all());\n    x[0] = true;\n\
    \    assert(x.all());\n    x[128] = false;\n    assert(not x.all());\n}\nvoid\
    \ test_none() {\n    DynamicBitSet x;\n    assert(x.none());\n    x.push_back(true);\n\
    \    assert(not x.none());\n    x[0] = false;\n    assert(x.none());\n    x.resize(129,\
    \ false);\n    assert(x.none());\n    x[0] = true;\n    assert(not x.none());\n\
    \    x[0] = false;\n    assert(x.none());\n    x[128] = true;\n    assert(not\
    \ x.none());\n}\nvoid test_any() {\n    DynamicBitSet x;\n    assert(not x.any());\n\
    \    x.push_back(true);\n    assert(x.any());\n    x[0] = false;\n    assert(not\
    \ x.any());\n    x.resize(129, false);\n    assert(not x.any());\n    x[0] = true;\n\
    \    assert(x.any());\n    x[0] = false;\n    assert(not x.any());\n    x[128]\
    \ = true;\n    assert(x.any());\n}\n\nvoid test_count() {\n    DynamicBitSet x;\n\
    \    assert(x.count() == 0);\n    x.resize(10);\n    assert(x.count() == 0);\n\
    \    x[3] = true;\n    assert(x.count() == 1);\n    x.resize(176, true);\n   \
    \ assert(x.count() == 167);\n}\n\nvoid test_set() {\n    DynamicBitSet x;\n  \
    \  x.set();\n    assert(x.count() == 0);\n    x.resize(20, false);\n    x.set();\n\
    \    assert(x.count() == 20);\n    x.resize(1238);\n    x.set();\n    assert(x.count()\
    \ == 1238);\n}\nvoid test_reset() {\n    DynamicBitSet x;\n    x.reset();\n  \
    \  assert(x.count() == 0);\n    x.resize(20, true);\n    x.reset();\n    assert(x.count()\
    \ == 0);\n    x.resize(1238);\n    x.reset();\n    assert(x.count() == 0);\n}\n\
    \nvoid test_find() {\n    constexpr int n = 513;\n    std::bitset<n> bs;\n   \
    \ DynamicBitSet dbs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] = i\
    \ % 3 == 0;\n        dbs[i] = i % 3 == 0;\n    }\n\n    int i = bs._Find_first(),\
    \ j = dbs.find_first();\n    for (; i < n and j < n; i = bs._Find_next(i), j =\
    \ dbs.find_next(j)) {\n        assert(i == j);\n    }\n    assert(i == n and j\
    \ == n);\n}\n\nvoid test_has_intersectoin() {\n    DynamicBitSet x(10, true),\
    \ y;\n    assert(not x.has_intersection(y));\n    y.resize(10);\n    y[9] = true;\n\
    \    assert(x.has_intersection(y));\n    y[9] = false;\n    y.resize(123);\n \
    \   y[122] = true;\n    assert(not x.has_intersection(y));\n    x.resize(1230);\n\
    \    x[122] = true;\n    assert(x.has_intersection(y));\n}\nvoid test_is_disjoint()\
    \ {\n    DynamicBitSet x(10, true), y;\n    assert(x.is_disjoint(y));\n    y.resize(10);\n\
    \    y[9] = true;\n    assert(not x.is_disjoint(y));\n    y[9] = false;\n    y.resize(123);\n\
    \    y[122] = true;\n    assert(x.is_disjoint(y));\n    x.resize(1230);\n    x[122]\
    \ = true;\n    assert(not x.is_disjoint(y));\n}\n\nvoid test() {\n    test_empty();\n\
    \    test_size();\n    test_resize();\n    test_push_back();\n    test_pop_back();\n\
    \    test_eq();\n    test_neq();\n    test_lt();\n    test_leq();\n    test_gt();\n\
    \    test_geq();\n    test_cast_bool();\n    test_and();\n    test_or();\n   \
    \ test_xor();\n    test_shift_r();\n    test_shift_l();\n    test_neg();\n   \
    \ test_get_set();\n    test_range_set();\n    test_range_reset();\n    test_range_flip();\n\
    \    test_range_update();\n    test_range_count();\n    test_all();\n    test_none();\n\
    \    test_any();\n    test_count();\n    test_set();\n    test_reset();\n    test_find();\n\
    \    test_has_intersectoin();\n    test_is_disjoint();\n}\n\nint main() {\n  \
    \  test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <bitset>\n#include <iostream>\n\n#include \"library/datastructure/util/dynamic_bitset.hpp\"\
    \n\nusing suisen::DynamicBitSet;\n\ntemplate <std::size_t n>\nbool operator==(const\
    \ DynamicBitSet& dbs, const std::bitset<n>& bs) {\n    if (dbs.size() != int(n))\
    \ return false;\n    for (std::size_t i = 0; i < n; ++i) if (dbs[i] != bs[i])\
    \ return false;\n    return true;\n}\ntemplate <std::size_t n>\nbool operator==(const\
    \ std::bitset<n>& bs, const DynamicBitSet& dbs) {\n    return dbs == bs;\n}\n\
    template <std::size_t n>\nbool operator!=(const DynamicBitSet& dbs, const std::bitset<n>&\
    \ bs) {\n    return not (dbs == bs);\n}\ntemplate <std::size_t n>\nbool operator!=(const\
    \ std::bitset<n>& bs, const DynamicBitSet& dbs) {\n    return dbs != bs;\n}\n\n\
    void test_empty() {\n    assert(DynamicBitSet(0).empty());\n    assert(not DynamicBitSet(1).empty());\n\
    }\n\nvoid test_size() {\n    assert(DynamicBitSet(0).size() == 0);\n    assert(DynamicBitSet(1).size()\
    \ == 1);\n    assert(DynamicBitSet(64).size() == 64);\n}\n\nvoid test_resize()\
    \ {\n    DynamicBitSet bs;\n    bs.resize(35, true);\n    assert(bs.size() ==\
    \ 35);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n    bs.resize(1026, false);\n\
    \    assert(bs.size() == 1026);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 1026; ++i) assert(not bs[i]);\n    bs.resize(78);\n\
    \    assert(bs.size() == 78);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 78; ++i) assert(not bs[i]);\n    bs.resize(512, true);\n\
    \    assert(bs.size() == 512);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n\
    \    for (int i = 35; i < 78; ++i) assert(not bs[i]);\n    for (int i = 78; i\
    \ < 512; ++i) assert(bs[i]);\n    bs.resize(128, false);\n    assert(bs.size()\
    \ == 128);\n    for (int i = 0; i < 35; ++i) assert(bs[i]);\n    for (int i =\
    \ 35; i < 78; ++i) assert(not bs[i]);\n    for (int i = 78; i < 128; ++i) assert(bs[i]);\n\
    }\n\nvoid test_push_back() {\n    DynamicBitSet bs;\n    for (int i = 0; i < 1000;\
    \ ++i) {\n        bs.push_back(i & 1);\n        assert(bs.size() == i + 1);\n\
    \        for (int j = 0; j <= i; ++j) assert(bs[j] == (j & 1));\n    }\n}\n\n\
    void test_pop_back() {\n    DynamicBitSet bs;\n    for (int i = 0; i < 1000; ++i)\
    \ {\n        bs.push_back(i & 1);\n    }\n    for (int i = 0; i < 1000; ++i) {\n\
    \        bs.pop_back();\n        assert(bs.size() == 999 - i);\n        for (int\
    \ j = 0; j < 999 - i; ++j) assert(bs[j] == (j & 1));\n    }\n}\n\nvoid test_eq()\
    \ {\n    DynamicBitSet x(10, true);\n    DynamicBitSet y(10);\n    for (int i\
    \ = 0; i < 10; ++i) y[i] = true;\n    assert(x == y);\n    x.resize(516, false);\n\
    \    y.resize(516, false);\n    assert(x == y);\n    x.resize(100);\n    y.resize(200);\n\
    \    x.resize(300, true);\n    y.resize(300, true);\n    for (int i = 100; i <\
    \ 200; ++i) y[i] = true;\n    assert(x == y);\n}\n\nvoid test_neq() {\n    DynamicBitSet\
    \ x(10);\n    DynamicBitSet y;\n    assert(x != y);\n    y.resize(5);\n    assert(x\
    \ != y);\n    y.resize(64, true);\n    assert(x != y);\n    y.resize(10);\n  \
    \  assert(x != y);\n    x.resize(500);\n    y.resize(500);\n    for (int i = 5;\
    \ i < 10; ++i) x[i] = true;\n    assert(x == y);\n    y[499] = true;\n    assert(x\
    \ != y);\n    y[499] = false;\n    assert(x == y);\n    y[256] = true;\n    assert(x\
    \ != y);\n    y[256] = false;\n    assert(x == y);\n    y[255] = true;\n    assert(x\
    \ != y);\n}\n\nvoid test_lt() {\n    DynamicBitSet x(100), y(100);\n    assert(not\
    \ (x < y));\n    x[56] = true;\n    assert(not (x < y));\n    y[56] = true;\n\
    \    assert(not (x < y));\n    y[99] = true;\n    assert(x < y);\n    x.resize(200),\
    \ y.resize(200);\n    x[100] = true;\n    assert(not (x < y));\n    y[100] = true;\n\
    \    assert(x < y);\n    x[99] = true;\n    assert(not (x < y));\n    y[199] =\
    \ true;\n    assert(x < y);\n    y[199] = false;\n    y[128] = true;\n    assert(x\
    \ < y);\n    y[128] = false;\n    y[127] = true;\n    assert(x < y);\n}\n\nvoid\
    \ test_leq() {\n    DynamicBitSet x(100), y(100);\n    assert(x <= y);\n    x[56]\
    \ = true;\n    assert(not (x <= y));\n    y[56] = true;\n    assert(x <= y);\n\
    \    y[99] = true;\n    assert(x <= y);\n    x.resize(200), y.resize(200);\n \
    \   x[100] = true;\n    assert(not (x <= y));\n    y[100] = true;\n    assert(x\
    \ <= y);\n    x[99] = true;\n    assert(x <= y);\n    y[199] = true;\n    assert(x\
    \ <= y);\n    y[199] = false;\n    y[128] = true;\n    assert(x <= y);\n    y[128]\
    \ = false;\n    y[127] = true;\n    assert(x <= y);\n}\nvoid test_gt() {\n   \
    \ DynamicBitSet x(100), y(100);\n    assert(not (x > y));\n    x[56] = true;\n\
    \    assert(x > y);\n    y[56] = true;\n    assert(not (x > y));\n    y[99] =\
    \ true;\n    assert(not (x > y));\n    x.resize(200), y.resize(200);\n    x[100]\
    \ = true;\n    assert(x > y);\n    y[100] = true;\n    assert(not (x > y));\n\
    \    x[99] = true;\n    assert(not (x > y));\n    y[199] = true;\n    assert(not\
    \ (x > y));\n    y[199] = false;\n    y[128] = true;\n    assert(not (x > y));\n\
    \    y[128] = false;\n    y[127] = true;\n    assert(not (x > y));\n}\nvoid test_geq()\
    \ {\n    DynamicBitSet x(100), y(100);\n    assert(x >= y);\n    x[56] = true;\n\
    \    assert(x >= y);\n    y[56] = true;\n    assert(x >= y);\n    y[99] = true;\n\
    \    assert(not (x >= y));\n    x.resize(200), y.resize(200);\n    x[100] = true;\n\
    \    assert(x >= y);\n    y[100] = true;\n    assert(not (x >= y));\n    x[99]\
    \ = true;\n    assert(x >= y);\n    y[199] = true;\n    assert(not (x >= y));\n\
    \    y[199] = false;\n    y[128] = true;\n    assert(not (x >= y));\n    y[128]\
    \ = false;\n    y[127] = true;\n    assert(not (x >= y));\n}\n\nvoid test_cast_bool()\
    \ {\n    DynamicBitSet x;\n    assert(not x);\n    x.resize(100);\n    assert(not\
    \ x);\n    x[99] = true;\n    assert(x);\n}\n\nvoid test_and() {\n    constexpr\
    \ int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet dbs1(n), dbs2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3 == 0;\n        dbs1[i]\
    \ = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i) {\n        bs2[i] = i\
    \ % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto bs = bs1 & bs2;\n\
    \    auto dbs = dbs1 & dbs2;\n    assert(bs == dbs);\n}\nvoid test_or() {\n  \
    \  constexpr int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet dbs1(n),\
    \ dbs2(n);\n    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3 == 0;\n\
    \        dbs1[i] = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i) {\n   \
    \     bs2[i] = i % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto bs\
    \ = bs1 | bs2;\n    auto dbs = dbs1 | dbs2;\n    assert(bs == dbs);\n}\nvoid test_xor()\
    \ {\n    constexpr int n = 353;\n    std::bitset<n> bs1, bs2;\n    DynamicBitSet\
    \ dbs1(n), dbs2(n);\n    for (int i = 0; i < n; ++i) {\n        bs1[i] = i % 3\
    \ == 0;\n        dbs1[i] = i % 3 == 0;\n    }\n    for (int i = 0; i < n; ++i)\
    \ {\n        bs2[i] = i % 5 == 0;\n        dbs2[i] = i % 5 == 0;\n    }\n    auto\
    \ bs = bs1 ^ bs2;\n    auto dbs = dbs1 ^ dbs2;\n    assert(bs == dbs);\n}\nvoid\
    \ test_shift_r() {\n    constexpr int n = 353;\n    std::bitset<n> bs;\n    DynamicBitSet\
    \ dbs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n  \
    \      dbs[i] = i % 3 == 0;\n    }\n\n    for (std::size_t i = 0; i < n; ++i)\
    \ {\n        assert((bs >> i) == (dbs >> i));\n    }\n}\nvoid test_shift_l() {\n\
    \    constexpr int n = 353;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i]\
    \ = i % 3 == 0;\n    }\n\n    for (std::size_t i = 0; i < n; ++i) {\n        assert((bs\
    \ << i) == (dbs << i));\n    }\n}\nvoid test_neg() {\n    constexpr int n = 353;\n\
    \    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i = 0; i < n;\
    \ ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n    }\n\n\
    \    assert(~bs == ~dbs);\n}\n\nvoid test_get_set() {\n    constexpr int n = 2349;\n\
    \    DynamicBitSet bs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] =\
    \ i % 3 != 0;\n    }\n    for (int i = 0; i < n; ++i) {\n        assert(bs[i]\
    \ == (i % 3 != 0));\n    }\n}\n\nvoid test_range_set() {\n    constexpr int n\
    \ = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i =\
    \ 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n\
    \    }\n\n    auto range_set_dbs = [&](int l, int r) {\n        auto dbs2 = dbs;\n\
    \        dbs2.range_set(l, r);\n        return dbs2;\n    };\n    auto range_set_bs\
    \ = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int i = l; i < r;\
    \ ++i) bs2[i] = true;\n        return bs2;\n    };\n\n    for (int l = 0; l <=\
    \ n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_set_bs(l, r) ==\
    \ range_set_dbs(l, r));\n    }\n}\nvoid test_range_reset() {\n    constexpr int\
    \ n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int i\
    \ = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 == 0;\n\
    \    }\n\n    auto range_reset_dbs = [&](int l, int r) {\n        auto dbs2 =\
    \ dbs;\n        dbs2.range_reset(l, r);\n        return dbs2;\n    };\n    auto\
    \ range_reset_bs = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int\
    \ i = l; i < r; ++i) bs2[i] = false;\n        return bs2;\n    };\n\n    for (int\
    \ l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_reset_bs(l,\
    \ r) == range_reset_dbs(l, r));\n    }\n}\nvoid test_range_flip() {\n    constexpr\
    \ int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 ==\
    \ 0;\n    }\n\n    auto range_flip_dbs = [&](int l, int r) {\n        auto dbs2\
    \ = dbs;\n        dbs2.range_flip(l, r);\n        return dbs2;\n    };\n    auto\
    \ range_flip_bs = [&](int l, int r) {\n        auto bs2 = bs;\n        for (int\
    \ i = l; i < r; ++i) bs2[i].flip();\n        return bs2;\n    };\n\n    for (int\
    \ l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n        assert(range_flip_bs(l,\
    \ r) == range_flip_dbs(l, r));\n    }\n}\n\nvoid test_range_update() {\n    constexpr\
    \ int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i] = i % 3 ==\
    \ 0;\n    }\n\n    auto range_update_dbs = [&](int l, int r, bool val) {\n   \
    \     auto dbs2 = dbs;\n        dbs2.range_update(l, r, val);\n        return\
    \ dbs2;\n    };\n    auto range_update_bs = [&](int l, int r, bool val) {\n  \
    \      auto bs2 = bs;\n        for (int i = l; i < r; ++i) bs2[i] = val;\n   \
    \     return bs2;\n    };\n\n    for (bool b : { false, true }) {\n        for\
    \ (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {\n            assert(range_update_bs(l,\
    \ r, b) == range_update_dbs(l, r, b));\n        }\n    }\n}\nvoid test_range_count()\
    \ {\n    constexpr int n = 513;\n    std::bitset<n> bs;\n    DynamicBitSet dbs(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        bs[i] = i % 3 == 0;\n        dbs[i]\
    \ = i % 3 == 0;\n    }\n\n    auto range_count_dbs = [&](int l, int r) {\n   \
    \     return dbs.range_count(l, r);\n    };\n    auto range_count_bs = [&](int\
    \ l, int r) {\n        int res = 0;\n        for (int i = l; i < r; ++i) res +=\
    \ bs[i];\n        return res;\n    };\n\n    for (int l = 0; l <= n; ++l) for\
    \ (int r = l; r <= n; ++r) {\n        assert(range_count_bs(l, r) == range_count_dbs(l,\
    \ r));\n    }\n}\n\nvoid test_all() {\n    DynamicBitSet x;\n    assert(x.all());\n\
    \    x.push_back(true);\n    assert(x.all());\n    x[0] = false;\n    assert(not\
    \ x.all());\n    x.resize(129, true);\n    assert(not x.all());\n    x[0] = true;\n\
    \    assert(x.all());\n    x[128] = false;\n    assert(not x.all());\n}\nvoid\
    \ test_none() {\n    DynamicBitSet x;\n    assert(x.none());\n    x.push_back(true);\n\
    \    assert(not x.none());\n    x[0] = false;\n    assert(x.none());\n    x.resize(129,\
    \ false);\n    assert(x.none());\n    x[0] = true;\n    assert(not x.none());\n\
    \    x[0] = false;\n    assert(x.none());\n    x[128] = true;\n    assert(not\
    \ x.none());\n}\nvoid test_any() {\n    DynamicBitSet x;\n    assert(not x.any());\n\
    \    x.push_back(true);\n    assert(x.any());\n    x[0] = false;\n    assert(not\
    \ x.any());\n    x.resize(129, false);\n    assert(not x.any());\n    x[0] = true;\n\
    \    assert(x.any());\n    x[0] = false;\n    assert(not x.any());\n    x[128]\
    \ = true;\n    assert(x.any());\n}\n\nvoid test_count() {\n    DynamicBitSet x;\n\
    \    assert(x.count() == 0);\n    x.resize(10);\n    assert(x.count() == 0);\n\
    \    x[3] = true;\n    assert(x.count() == 1);\n    x.resize(176, true);\n   \
    \ assert(x.count() == 167);\n}\n\nvoid test_set() {\n    DynamicBitSet x;\n  \
    \  x.set();\n    assert(x.count() == 0);\n    x.resize(20, false);\n    x.set();\n\
    \    assert(x.count() == 20);\n    x.resize(1238);\n    x.set();\n    assert(x.count()\
    \ == 1238);\n}\nvoid test_reset() {\n    DynamicBitSet x;\n    x.reset();\n  \
    \  assert(x.count() == 0);\n    x.resize(20, true);\n    x.reset();\n    assert(x.count()\
    \ == 0);\n    x.resize(1238);\n    x.reset();\n    assert(x.count() == 0);\n}\n\
    \nvoid test_find() {\n    constexpr int n = 513;\n    std::bitset<n> bs;\n   \
    \ DynamicBitSet dbs(n);\n    for (int i = 0; i < n; ++i) {\n        bs[i] = i\
    \ % 3 == 0;\n        dbs[i] = i % 3 == 0;\n    }\n\n    int i = bs._Find_first(),\
    \ j = dbs.find_first();\n    for (; i < n and j < n; i = bs._Find_next(i), j =\
    \ dbs.find_next(j)) {\n        assert(i == j);\n    }\n    assert(i == n and j\
    \ == n);\n}\n\nvoid test_has_intersectoin() {\n    DynamicBitSet x(10, true),\
    \ y;\n    assert(not x.has_intersection(y));\n    y.resize(10);\n    y[9] = true;\n\
    \    assert(x.has_intersection(y));\n    y[9] = false;\n    y.resize(123);\n \
    \   y[122] = true;\n    assert(not x.has_intersection(y));\n    x.resize(1230);\n\
    \    x[122] = true;\n    assert(x.has_intersection(y));\n}\nvoid test_is_disjoint()\
    \ {\n    DynamicBitSet x(10, true), y;\n    assert(x.is_disjoint(y));\n    y.resize(10);\n\
    \    y[9] = true;\n    assert(not x.is_disjoint(y));\n    y[9] = false;\n    y.resize(123);\n\
    \    y[122] = true;\n    assert(x.is_disjoint(y));\n    x.resize(1230);\n    x[122]\
    \ = true;\n    assert(not x.is_disjoint(y));\n}\n\nvoid test() {\n    test_empty();\n\
    \    test_size();\n    test_resize();\n    test_push_back();\n    test_pop_back();\n\
    \    test_eq();\n    test_neq();\n    test_lt();\n    test_leq();\n    test_gt();\n\
    \    test_geq();\n    test_cast_bool();\n    test_and();\n    test_or();\n   \
    \ test_xor();\n    test_shift_r();\n    test_shift_l();\n    test_neg();\n   \
    \ test_get_set();\n    test_range_set();\n    test_range_reset();\n    test_range_flip();\n\
    \    test_range_update();\n    test_range_count();\n    test_all();\n    test_none();\n\
    \    test_any();\n    test_count();\n    test_set();\n    test_reset();\n    test_find();\n\
    \    test_has_intersectoin();\n    test_is_disjoint();\n}\n\nint main() {\n  \
    \  test();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n}\n"
  dependsOn:
  - library/datastructure/util/dynamic_bitset.hpp
  isVerificationFile: true
  path: test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-11-06 23:07:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
- /verify/test/src/datastructure/util/dynamic_bitset/dummy.test.cpp.html
title: test/src/datastructure/util/dynamic_bitset/dummy.test.cpp
---
