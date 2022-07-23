---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/binary_trie_patricia.hpp
    title: Binary Trie Patricia
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 1 \"test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\n\
    #include <iostream>\n\n#line 1 \"library/datastructure/binary_trie_patricia.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <cstring>\n\
    #include <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    \n#ifdef _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\
    \nnamespace suisen {\n    template <typename T, uint32_t bit_num, typename SizeType\
    \ = int32_t, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>\n\
    \    struct BinaryTriePatricia {\n        using size_type = SizeType;\n      \
    \  using internal_size_type = std::make_unsigned_t<size_type>;\n\n        using\
    \ value_type = T;\n        using unsigned_value_type = std::make_unsigned_t<value_type>;\n\
    \n        static constexpr uint32_t ary = 4;\n        static constexpr uint32_t\
    \ log_ary = 2;\n\n        static_assert(bit_num <= std::numeric_limits<unsigned_value_type>::digits);\n\
    \        static_assert(bit_num <= 64);\n\n        struct Node;\n        using\
    \ node_type = Node;\n        using node_pointer_type = node_type*;\n\n       \
    \ struct Node {\n            unsigned_value_type val;\n            uint32_t len;\n\
    \            internal_size_type siz;\n            node_pointer_type ch[ary]{};\n\
    \n            Node(const unsigned_value_type& val, uint32_t len, internal_size_type\
    \ siz) : val(val), len(len), siz(siz) {}\n            ~Node() {\n            \
    \    for (uint32_t i = 0; i < ary; ++i) delete ch[i];\n            }\n\n     \
    \       static node_pointer_type new_node(const unsigned_value_type& val, uint32_t\
    \ len, internal_size_type siz) {\n                return new node_type(val, len,\
    \ siz);\n            }\n        };\n\n        BinaryTriePatricia() = default;\n\
    \        ~BinaryTriePatricia() {\n            delete _root;\n        }\n\n   \
    \     // number of elements in the set\n        int size() const {\n         \
    \   return _root->siz;\n        }\n        // true iff size() == 0\n        bool\
    \ empty() const {\n            return _root->siz == 0;\n        }\n        void\
    \ clear() { delete _root; _root = node_type::new_node(0, 0, 0); }\n\n        //\
    \ returns true iff insertion is succeeded.\n        bool insert_if_absent(unsigned_value_type\
    \ val) {\n            bit_reverse(val);\n            return _insert_if_absent(_root,\
    \ 0, val);\n        }\n        void insert(unsigned_value_type val, internal_size_type\
    \ num = 1) {\n            bit_reverse(val);\n            _insert(_root, 0, val,\
    \ num);\n        }\n        // returns the number of erased elements\n       \
    \ size_type erase(unsigned_value_type val, internal_size_type num = 1) {\n   \
    \         if (num == 0) return 0;\n            bit_reverse(val);\n           \
    \ _erase(_root, num, 0, val);\n            return num;\n        }\n\n        size_type\
    \ count(unsigned_value_type val) const {\n            bit_reverse(val);\n    \
    \        node_pointer_type cur = _root;\n            for (uint32_t l = 0; l <\
    \ bit_num;) {\n                const uint32_t ch_idx = val & (ary - 1);\n    \
    \            node_pointer_type nxt = cur->ch[ch_idx];\n                if (not\
    \ nxt or cut_lower(val ^ nxt->val, nxt->len)) return 0;\n                val >>=\
    \ nxt->len;\n                l += nxt->len;\n                cur = nxt;\n    \
    \        }\n            return cur->siz;\n        }\n        bool contains(unsigned_value_type\
    \ val) const { return count(val) != 0; }\n\n        // min{ x ^ v | v in S }\n\
    \        value_type xor_min(unsigned_value_type x) const {\n            return\
    \ xor_kth_min(x, 0);\n        }\n        // max{ x ^ v | v in S }\n        value_type\
    \ xor_max(const unsigned_value_type& x) const {\n            return xor_min(~x);\n\
    \        }\n\n        // k-th smallest of { x ^ v | v in S } (0-indexed)\n   \
    \     value_type xor_kth_min(unsigned_value_type x, internal_size_type k) const\
    \ {\n            unsigned_value_type x_ = x;\n            bit_reverse(x);\n  \
    \          unsigned_value_type res = 0;\n            node_pointer_type cur = _root;\n\
    \            for (uint32_t l = 0; l < bit_num;) {\n                const uint32_t\
    \ ch_idx = x & (ary - 1);\n                node_pointer_type nxt = nullptr;\n\
    \                for (int x : _ord) {\n                    if (nxt = cur->ch[ch_idx\
    \ ^ x]; nxt) {\n                        if (nxt->siz > k) break;\n           \
    \             k -= nxt->siz;\n                    }\n                }\n     \
    \           res |= nxt->val << l;\n                x >>= nxt->len;\n         \
    \       l += nxt->len;\n                cur = nxt;\n            }\n          \
    \  bit_reverse(res);\n            return x_ ^ res;\n        }\n        // k-th\
    \ largest of { x ^ v | v in S } (0-indexed)\n        value_type xor_kth_max(unsigned_value_type\
    \ x, internal_size_type k) const {\n            return xor_kth_min(x, _root->siz\
    \ - k - 1);\n        }\n\n        // #{ v in S | x ^ v < upper }\n        __attribute__((target(\"\
    bmi\")))\n        size_type xor_count_lt (unsigned_value_type x, unsigned_value_type\
    \ upper) const {\n            if (upper >> bit_num) return _root->siz;\n     \
    \       bit_reverse(x);\n            bit_reverse(upper);\n            internal_size_type\
    \ res = 0;\n            node_pointer_type cur = _root;\n            for (uint32_t\
    \ l = 0; l < bit_num;) {\n                const uint32_t ch_idx = x & (ary - 1);\n\
    \                const uint32_t ch_idx_r = upper & (ary - 1);\n              \
    \  node_pointer_type nxt = nullptr;\n                for (uint32_t x : _ord) {\n\
    \                    nxt = cur->ch[ch_idx ^ x];\n                    if (x ==\
    \ ch_idx_r) break;\n                    if (nxt) res += nxt->siz;\n          \
    \      }\n                if (not nxt) break;\n                const uint32_t\
    \ len = nxt->len;\n                unsigned_value_type vlo = cut_lower(x, len)\
    \ ^ nxt->val, ulo = cut_lower(upper, len);\n                if (vlo != ulo) {\n\
    \                    uint32_t tz = len <= 32 ? _tzcnt_u32(vlo ^ ulo) : _tzcnt_u64(vlo\
    \ ^ ulo);\n                    return (ulo >> tz) & 1 ? res + nxt->siz : res;\n\
    \                }\n                x >>= len;\n                upper >>= len;\n\
    \                l += len;\n                cur = nxt;\n            }\n      \
    \      return res;\n        }\n        // #{ v in S | x ^ v <= upper }\n     \
    \   size_type xor_count_leq(unsigned_value_type x, unsigned_value_type upper)\
    \ const {\n            if (upper == std::numeric_limits<unsigned_value_type>::max())\
    \ return _root->siz;\n            return xor_count_lt(x, upper + 1);\n       \
    \ }\n        // #{ v in S | x ^ v >= lower }\n        size_type xor_count_geq(unsigned_value_type\
    \ x, unsigned_value_type lower) const {\n            return _root->siz - xor_count_lt(x,\
    \ lower);\n        }\n        // #{ v in S | x ^ v > lower }\n        size_type\
    \ xor_count_gt (unsigned_value_type x, unsigned_value_type lower) const {\n  \
    \          return _root->siz - xor_count_leq(x, lower);\n        }\n\n       \
    \ // max{ x ^ v | x ^ v < upper } or std::nullopt\n        std::optional<value_type>\
    \ safe_xor_max_lt (unsigned_value_type x, unsigned_value_type upper) const {\n\
    \            internal_size_type cnt = xor_count_lt(x, upper);\n            if\
    \ (cnt == 0) return std::nullopt;\n            return xor_kth_min(x, cnt - 1);\n\
    \        }\n        // max{ x ^ v | x ^ v <= upper } or std::nullopt\n       \
    \ std::optional<value_type> safe_xor_max_leq(unsigned_value_type x, unsigned_value_type\
    \ upper) const {\n            internal_size_type cnt = xor_count_leq(x, upper);\n\
    \            if (cnt == 0) return std::nullopt;\n            return xor_kth_min(x,\
    \ cnt - 1);\n        }\n        // min{ x ^ v | x ^ v >= lower } or std::nullopt\n\
    \        std::optional<value_type> safe_xor_min_geq(unsigned_value_type x, unsigned_value_type\
    \ lower) const {\n            internal_size_type cnt = xor_count_lt(x, lower);\n\
    \            if (cnt == _root->siz) return std::nullopt;\n            return xor_kth_min(x,\
    \ cnt);\n        }\n        // min{ x ^ v | x ^ v > lower } or std::nullopt\n\
    \        std::optional<value_type> safe_xor_min_gt (unsigned_value_type x, unsigned_value_type\
    \ lower) const {\n            internal_size_type cnt = xor_count_leq(x, lower);\n\
    \            if (cnt == _root->siz) return std::nullopt;\n            return xor_kth_min(x,\
    \ cnt);\n        }\n\n        // max{ x ^ v | x ^ v < upper } or Runtime Error\n\
    \        value_type xor_max_lt (unsigned_value_type x, unsigned_value_type upper)\
    \ const { return *safe_xor_max_lt (x, upper); }\n        // max{ x ^ v | x ^ v\
    \ <= upper } or Runtime Error\n        value_type xor_max_leq(unsigned_value_type\
    \ x, unsigned_value_type upper) const { return *safe_xor_max_leq(x, upper); }\n\
    \        // min{ x ^ v | x ^ v >= lower } or Runtime Error\n        value_type\
    \ xor_min_geq(unsigned_value_type x, unsigned_value_type lower) const { return\
    \ *safe_xor_min_geq(x, lower); }\n        // min{ x ^ v | x ^ v > lower } or Runtime\
    \ Error\n        value_type xor_min_gt (unsigned_value_type x, unsigned_value_type\
    \ lower) const { return *safe_xor_min_gt (x, lower); }\n\n        // 0-indexed\n\
    \        value_type kth_min(internal_size_type k) const { return xor_kth_min(0,\
    \ k); }\n        // 0-indexed\n        value_type kth_max(internal_size_type k)\
    \ const { return xor_kth_max(0, k); }\n        // #{ v in S | v < upper }\n  \
    \      size_type count_lt (unsigned_value_type upper) const { return xor_count_lt\
    \ (0, upper); }\n        // #{ v in S | v <= upper }\n        size_type count_leq(unsigned_value_type\
    \ upper) const { return xor_count_leq(0, upper); }\n        // #{ v in S | v >=\
    \ lower }\n        size_type count_geq(unsigned_value_type lower) const { return\
    \ xor_count_geq(0, lower); }\n        // #{ v in S | v > lower }\n        size_type\
    \ count_gt (unsigned_value_type lower) const { return xor_count_gt (0, lower);\
    \ }\n\n        // max{ v | v < upper } or std::nullopt\n        std::optional<value_type>\
    \ safe_max_lt (unsigned_value_type upper) const { return safe_xor_max_lt (0, upper);\
    \ }\n        // max{ v | v <= upper } or std::nullopt\n        std::optional<value_type>\
    \ safe_max_leq(unsigned_value_type upper) const { return safe_xor_max_leq(0, upper);\
    \ }\n        // min{ v | v >= lower } or std::nullopt\n        std::optional<value_type>\
    \ safe_min_geq(unsigned_value_type lower) const { return safe_xor_min_geq(0, lower);\
    \ }\n        // min{ v | v > lower } or std::nullopt\n        std::optional<value_type>\
    \ safe_min_gt (unsigned_value_type lower) const { return safe_xor_min_gt (0, lower);\
    \ }\n\n        // max{ v | v < upper } or Runtime Error\n        value_type max_lt\
    \ (unsigned_value_type upper) const { return *safe_max_lt (upper); }\n       \
    \ // max{ v | v <= upper } or Runtime Error\n        value_type max_leq(unsigned_value_type\
    \ upper) const { return *safe_max_leq(upper); }\n        // min{ v | v >= lower\
    \ } or Runtime Error\n        value_type min_geq(unsigned_value_type lower) const\
    \ { return *safe_min_geq(lower); }\n        // min{ v | v > lower } or Runtime\
    \ Error\n        value_type min_gt (unsigned_value_type lower) const { return\
    \ *safe_min_gt (lower); }\n\n    private:\n        static constexpr uint32_t _ord[4]{\
    \ 0, 2, 1, 3 };\n        static constexpr uint32_t _rev_ord[4]{ 3, 1, 2, 0 };\n\
    \        static constexpr uint32_t _inv_ord[4]{ 0, 2, 1, 3 };\n\n        node_pointer_type\
    \ _root = node_type::new_node(0, 0, 0);\n\n        static constexpr unsigned_value_type\
    \ cut_lower(const unsigned_value_type& val, uint32_t r) {\n            return\
    \ val & ((unsigned_value_type(1) << r) - 1);\n        }\n        static constexpr\
    \ uint32_t bit_reverse_u32(uint32_t x) {\n            x = (((x & 0xaaaaaaaa) >>\
    \ 1) | ((x & 0x55555555) << 1));\n            x = (((x & 0xcccccccc) >> 2) | ((x\
    \ & 0x33333333) << 2));\n            x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f)\
    \ << 4));\n            x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));\n\
    \            return ((x >> 16) | (x << 16));\n        }\n        static constexpr\
    \ uint64_t bit_reverse_u64(uint64_t x) {\n            x = (((x & 0xaaaaaaaaaaaaaaaa)\
    \ >> 1) | ((x & 0x5555555555555555) << 1));\n            x = (((x & 0xcccccccccccccccc)\
    \ >> 2) | ((x & 0x3333333333333333) << 2));\n            x = (((x & 0xf0f0f0f0f0f0f0f0)\
    \ >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4));\n            x = (((x & 0xff00ff00ff00ff00)\
    \ >> 8) | ((x & 0x00ff00ff00ff00ff) << 8));\n            x = (((x & 0xffff0000ffff0000)\
    \ >> 16) | ((x & 0x0000ffff0000ffff) << 16));\n            return ((x >> 32) |\
    \ (x << 32));\n        }\n        static constexpr void bit_reverse(unsigned_value_type&\
    \ x) {\n            if constexpr (bit_num <= 32) {\n                x = bit_reverse_u32(x)\
    \ >> (32 - bit_num);\n            } else {\n                x = bit_reverse_u64(x)\
    \ >> (64 - bit_num);\n            }\n        }\n\n        __attribute__((target(\"\
    bmi\")))\n        bool _insert_if_absent(node_pointer_type cur, uint32_t l, unsigned_value_type\
    \ val) {\n            if (l == bit_num) return false;\n            const uint32_t\
    \ idx = val & (ary - 1);\n            node_pointer_type nxt = cur->ch[idx];\n\
    \            if (not nxt) {\n                cur->ch[idx] = node_type::new_node(val,\
    \ bit_num - l, 1);\n                ++cur->siz;\n                return true;\n\
    \            }\n            unsigned_value_type x = val ^ nxt->val;\n        \
    \    uint32_t len = nxt->len, tz = len <= 32 ? _tzcnt_u32(x) : _tzcnt_u64(x);\n\
    \            tz -= tz & (log_ary - 1);\n            if (tz >= len) {\n       \
    \         bool inserted = _insert_if_absent(nxt, l + len, val >> len);\n     \
    \           cur->siz += inserted;\n                return inserted;\n        \
    \    }\n            node_pointer_type br = node_type::new_node(cut_lower(nxt->val,\
    \ tz), tz, nxt->siz + 1);\n            cur->ch[idx] = br;\n            nxt->val\
    \ >>= tz;\n            nxt->len -= tz;\n            val >>= tz;\n            br->ch[nxt->val\
    \ & (ary - 1)] = nxt;\n            br->ch[val & (ary - 1)] = node_type::new_node(val,\
    \ bit_num - l - tz, 1);\n            ++cur->siz;\n            return true;\n \
    \       }\n\n        __attribute__((target(\"bmi\")))\n        void _insert(node_pointer_type\
    \ cur, uint32_t l, unsigned_value_type val, internal_size_type num) {\n      \
    \      cur->siz += num;\n            if (l == bit_num) return;\n            const\
    \ uint32_t idx = val & (ary - 1);\n            node_pointer_type nxt = cur->ch[idx];\n\
    \            if (not nxt) {\n                cur->ch[idx] = node_type::new_node(val,\
    \ bit_num - l, num);\n                return;\n            }\n            unsigned_value_type\
    \ x = val ^ nxt->val;\n            uint32_t len = nxt->len, tz = len <= 32 ? _tzcnt_u32(x)\
    \ : _tzcnt_u64(x);\n            tz -= tz & (log_ary - 1);\n            if (tz\
    \ >= len) return _insert(nxt, l + len, val >> len, num);\n            node_pointer_type\
    \ br = node_type::new_node(cut_lower(nxt->val, tz), tz, nxt->siz + num);\n   \
    \         cur->ch[idx] = br;\n            nxt->val >>= tz;\n            nxt->len\
    \ -= tz;\n            val >>= tz;\n            br->ch[nxt->val & (ary - 1)] =\
    \ nxt;\n            br->ch[val & (ary - 1)] = node_type::new_node(val, bit_num\
    \ - l - tz, num);\n        }\n\n        bool _erase(node_pointer_type cur, internal_size_type\
    \ &num, uint32_t l, unsigned_value_type val) {\n            if (l == bit_num)\
    \ {\n                if (cur->siz -= num = std::min(num, cur->siz); cur->siz)\
    \ return false;\n                delete cur;\n                return true;\n \
    \           }\n            const uint32_t idx = val & (ary - 1);\n           \
    \ node_pointer_type nxt = cur->ch[idx];\n            if (not nxt or cut_lower(val\
    \ ^ nxt->val, nxt->len)) return num = 0, false;\n            bool deleted = _erase(nxt,\
    \ num, l + nxt->len, val >> nxt->len);\n            cur->siz -= num;\n       \
    \     if (not deleted) return false;\n            cur->ch[idx] = nullptr;\n  \
    \          if (cur == _root) return false;\n            if (cur->siz == 0) {\n\
    \                delete cur;\n                return true;\n            }\n  \
    \          uint32_t ch_cnt = 0;\n            node_pointer_type ch = nullptr;\n\
    \            for (uint32_t i = 0; i < ary; ++i) if (cur->ch[i]) {\n          \
    \      ++ch_cnt, ch = cur->ch[i];\n            }\n            if (ch_cnt == 1)\
    \ {\n                cur->val |= ch->val << cur->len;\n                cur->len\
    \ += ch->len;\n                for (uint32_t i = 0; i < ary; ++i) cur->ch[i] =\
    \ std::exchange(ch->ch[i], nullptr);\n                delete ch;\n           \
    \ }\n            return false;\n        }\n    };\n} // namespace suisen\n\n\n\
    #line 6 \"test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::string t;\n    std::cin >>\
    \ t;\n\n    suisen::BinaryTriePatricia<int, 24> bt;\n    for (int i = 0; i < n;\
    \ ++i) if (t[i] == '1') {\n        bt.insert(i);\n    }\n\n    while (q --> 0)\
    \ {\n        int query_type, k;\n        std::cin >> query_type >> k;\n      \
    \  if (query_type == 0) {\n            bt.insert_if_absent(k);\n        } else\
    \ if (query_type == 1) {\n            bt.erase(k);\n        } else if (query_type\
    \ == 2) {\n            std::cout << bt.contains(k) << '\\n';\n        } else if\
    \ (query_type == 3) {\n            auto opt_v = bt.safe_min_geq(k);\n        \
    \    std::cout << (opt_v.has_value() ? *opt_v : -1) << '\\n';\n        } else\
    \ {\n            auto opt_v = bt.safe_max_leq(k);\n            std::cout << (opt_v.has_value()\
    \ ? *opt_v : -1) << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\n\
    \n#include <iostream>\n\n#include \"library/datastructure/binary_trie_patricia.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::string t;\n    std::cin >>\
    \ t;\n\n    suisen::BinaryTriePatricia<int, 24> bt;\n    for (int i = 0; i < n;\
    \ ++i) if (t[i] == '1') {\n        bt.insert(i);\n    }\n\n    while (q --> 0)\
    \ {\n        int query_type, k;\n        std::cin >> query_type >> k;\n      \
    \  if (query_type == 0) {\n            bt.insert_if_absent(k);\n        } else\
    \ if (query_type == 1) {\n            bt.erase(k);\n        } else if (query_type\
    \ == 2) {\n            std::cout << bt.contains(k) << '\\n';\n        } else if\
    \ (query_type == 3) {\n            auto opt_v = bt.safe_min_geq(k);\n        \
    \    std::cout << (opt_v.has_value() ? *opt_v : -1) << '\\n';\n        } else\
    \ {\n            auto opt_v = bt.safe_max_leq(k);\n            std::cout << (opt_v.has_value()\
    \ ? *opt_v : -1) << '\\n';\n        }\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/datastructure/binary_trie_patricia.hpp
  isVerificationFile: true
  path: test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp
  requiredBy: []
  timestamp: '2022-07-16 18:47:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp
- /verify/test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp.html
title: test/src/datastructure/binary_trie_patricia/predecessor_problem.test.cpp
---
