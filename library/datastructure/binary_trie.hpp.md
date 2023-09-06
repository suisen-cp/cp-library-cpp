---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/binary_trie/set_xor_min.test.cpp
    title: test/src/datastructure/binary_trie/set_xor_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/binary_trie/xor_game.test.cpp
    title: test/src/datastructure/binary_trie/xor_game.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/binary_trie.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <limits>\n#include <optional>\n#include <string>\n#include\
    \ <vector>\n\nnamespace suisen {\ntemplate <typename T, int bit_length = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    class BinaryTrie {\n    using U = std::make_unsigned_t<T>;\n    struct Node {\n\
    \        int siz;\n        Node *ch[2] {nullptr, nullptr};\n        Node() : siz(0)\
    \ {}\n        ~Node() {\n            delete ch[0];\n            delete ch[1];\n\
    \        }\n        inline Node* get_or_create(bool b) noexcept {\n          \
    \  if (is_absent(b)) ch[b] = new Node();\n            return ch[b];\n        }\n\
    \        inline Node* operator[](bool b) const noexcept { return ch[b]; }\n  \
    \      inline bool is_absent (bool b) const noexcept { return ch[b] == nullptr;\
    \ }\n        inline bool is_present(bool b) const noexcept { return ch[b] != nullptr;\
    \ }\n        static inline int size(const Node *const node) noexcept { return\
    \ node == nullptr ? 0 : node->siz; }\n        inline void update_size() noexcept\
    \ { siz = size(ch[0]) + size(ch[1]); }\n\n        std::string to_string(const\
    \ int k = bit_length - 1, const U val = 0, const std::string &prefix = \"\") const\
    \ {\n            static const std::string zo[2] {\"+-[0]- \", \"+-[1]- \"};\n\
    \            static const std::string branch = '|' + std::string(zo[0].size()\
    \ - 1, ' ');\n            auto res = std::to_string(siz) + ' ';\n            if\
    \ (is_absent(0) and is_absent(1)) {\n                return res + \"(\" + std::to_string(val)\
    \ + \")\\n\";\n            }\n            auto pref0 = prefix + std::string(res.size(),\
    \ ' ');\n            auto prefb = pref0 + branch;\n            auto pref1 = pref0\
    \ + std::string(zo[0].size(), ' ');\n            if (is_absent(0) or is_absent(1))\
    \ {\n                bool b = is_absent(0);\n                return res + zo[b]\
    \ + ch[b]->to_string(k - 1, val | (b << k), pref1);\n            }\n         \
    \   res += zo[0] + ch[0]->to_string(k - 1, val, prefb);\n            res += pref0\
    \ + \"|\\n\";\n            res += pref0 + zo[1] + ch[1]->to_string(k - 1, val\
    \ | (1 << k), pref1);\n            return res;\n        }\n    };\n    public:\n\
    \        BinaryTrie() : root(new Node) {}\n        ~BinaryTrie() { delete root;\
    \ }\n\n        inline int size() const noexcept { return Node::size(root); }\n\
    \        inline bool empty() const noexcept { return size() == 0; }\n\n      \
    \  int insert(const U val, const int num = 1) noexcept {\n            if (num\
    \ == 0) return 0;\n            Node *cur = root;\n            cur->siz += num;\n\
    \            for (int i = bit_length; i --> 0;) {\n                cur = cur->get_or_create(bit(val,\
    \ i));\n                cur->siz += num;\n            }\n            return cur->siz;\n\
    \        }\n        int erase(const U val, const int num = 1) noexcept {\n   \
    \         if (num == 0) return 0;\n            return erase(root, bit_length -\
    \ 1, val, num);\n        }\n        int erase_all(const U val) noexcept {\n  \
    \          return erase(val, std::numeric_limits<int>::max());\n        }\n  \
    \      int prefix_count(const U val, const unsigned int l) const noexcept {\n\
    \            Node *cur = root;\n            for (int i = bit_length; i --> l;)\
    \ {\n                if (cur == nullptr) return 0;\n                cur = (*cur)[bit(val,\
    \ i)];\n            }\n            return Node::size(cur);\n        }\n      \
    \  inline int count(const U val) const noexcept { return prefix_count(val, 0);\
    \ }\n        inline bool contains(const U val) const noexcept { return count(val)\
    \ > 0; }\n\n        inline U xor_kth_min(const U x, const int k) const {\n   \
    \         assert(0 <= k and k < size());\n            return unchecked_xor_kth_element</*\
    \ is_max_query = */false>(x, k);\n        }\n        inline U xor_kth_max(const\
    \ U x, const int k) const {\n            assert(0 <= k and k < size());\n    \
    \        return unchecked_xor_kth_element</* is_max_query = */true>(x, k);\n \
    \       }\n        inline U xor_min(const U x) const { return xor_kth_min(x, 0);\
    \  }\n        inline U xor_max(const U x) const { return xor_kth_max(x, 0); }\n\
    \        int xor_count_lt(const U x, const U val) const noexcept {\n         \
    \   int res = 0;\n            Node *cur = root;\n            for (int i = bit_length\
    \ - 1; i >= 0; --i) {\n                if (cur == nullptr) break;\n          \
    \      bool bx = bit(x, i);\n                bool bv = bit(x ^ val, i);\n    \
    \            if (bx != bv) {\n                    res += Node::size((*cur)[bx]);\n\
    \                }\n                cur = (*cur)[bv];\n            }\n       \
    \     return res;\n        }\n        inline int xor_count_leq(const U x, const\
    \ U val) const noexcept { return xor_count_lt(x, val) + count(val); }\n      \
    \  inline int xor_count_gt (const U x, const U val) const noexcept { return size()\
    \ - xor_count_leq(x, val);    }\n        inline int xor_count_geq(const U x, const\
    \ U val) const noexcept { return size() - xor_count_lt(x, val);     }\n      \
    \  inline U xor_lower(const U x, const U val, const U default_value = ~U(0)) const\
    \ noexcept {\n            int k = size() - xor_count_geq(x, val) - 1;\n      \
    \      return k < 0 ? default_value : unchecked_xor_kth_element(x, k);\n     \
    \   }\n        inline U xor_floor(const U x, const U val, const U default_value\
    \ = ~U(0)) const noexcept {\n            int k = size() - xor_count_gt(x, val)\
    \ - 1;\n            return k < 0 ? default_value : unchecked_xor_kth_element(x,\
    \ k);\n        }\n        inline U xor_higher(const U x, const U val, const U\
    \ default_value = ~U(0)) const noexcept {\n            int k = xor_count_leq(x,\
    \ val);\n            return k == size() ? default_value : unchecked_xor_kth_element(x,\
    \ k);\n        }\n        inline U xor_ceil(const U x, const U val, const U default_value\
    \ = ~U(0)) const noexcept {\n            int k = xor_count_lt(x, val);\n     \
    \       return k == size() ? default_value : unchecked_xor_kth_element(x, k);\n\
    \        }\n\n        inline U kth_min(const int k) const { return xor_kth_min(0,\
    \ k); }\n        inline U min() const { return xor_kth_min(0, 0); }\n        inline\
    \ U max() const { return xor_kth_min(~U(0), 0); }\n        inline int count_lt\
    \ (const U val) const noexcept { return xor_count_lt(0, val);  }\n        inline\
    \ int count_leq(const U val) const noexcept { return xor_count_leq(0, val); }\n\
    \        inline int count_gt (const U val) const noexcept { return xor_count_gt(0,\
    \ val);  }\n        inline int count_geq(const U val) const noexcept { return\
    \ xor_count_geq(0, val); }\n        inline U lower (const U val, const U default_value\
    \ = ~U(0)) const noexcept { return xor_lower (0, val, default_value); }\n    \
    \    inline U floor (const U val, const U default_value = ~U(0)) const noexcept\
    \ { return xor_floor (0, val, default_value); }\n        inline U higher(const\
    \ U val, const U default_value = ~U(0)) const noexcept { return xor_higher(0,\
    \ val, default_value); }\n        inline U ceil  (const U val, const U default_value\
    \ = ~U(0)) const noexcept { return xor_ceil  (0, val, default_value); }\n\n  \
    \      inline std::string to_string() const noexcept { return root->to_string();\
    \ }\n        friend std::ostream& operator<<(std::ostream& out, const BinaryTrie\
    \ &bt) { return out << bt.to_string(); }\n    private:\n        Node *const root;\n\
    \        static constexpr bool bit(const U val, const int i) noexcept {\n    \
    \        return (val >> i) & 1;\n        }\n        int erase(Node *cur, const\
    \ int k, const U val, const int num) {\n            if (k == -1) {\n         \
    \       int removed = std::min(cur->siz, num);\n                cur->siz -= removed;\n\
    \                return removed;\n            }\n            bool b = bit(val,\
    \ k);\n            if (cur->is_absent(b)) return 0;\n            int removed =\
    \ erase((*cur)[b], k - 1, val, num);\n            cur->update_size();\n      \
    \      return removed;\n        }\n        template <bool is_max_query = false>\n\
    \        U unchecked_xor_kth_element(const U x, const int k) const noexcept {\n\
    \            U res = 0;\n            int rest = k;\n            Node *cur = root;\n\
    \            for (int i = bit_length - 1; i >= 0; --i) {\n                bool\
    \ b = is_max_query ^ bit(x, i);\n                int sz = Node::size((*cur)[b]);\n\
    \                if (sz <= rest) rest -= sz, b = not b;\n                res |=\
    \ U(b) << i;\n                cur = (*cur)[b];\n            }\n            return\
    \ x ^ res;\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_BINARY_TRIE\n#define SUISEN_BINARY_TRIE\n\n#include <cassert>\n\
    #include <limits>\n#include <optional>\n#include <string>\n#include <vector>\n\
    \nnamespace suisen {\ntemplate <typename T, int bit_length = std::numeric_limits<std::make_unsigned_t<T>>::digits>\n\
    class BinaryTrie {\n    using U = std::make_unsigned_t<T>;\n    struct Node {\n\
    \        int siz;\n        Node *ch[2] {nullptr, nullptr};\n        Node() : siz(0)\
    \ {}\n        ~Node() {\n            delete ch[0];\n            delete ch[1];\n\
    \        }\n        inline Node* get_or_create(bool b) noexcept {\n          \
    \  if (is_absent(b)) ch[b] = new Node();\n            return ch[b];\n        }\n\
    \        inline Node* operator[](bool b) const noexcept { return ch[b]; }\n  \
    \      inline bool is_absent (bool b) const noexcept { return ch[b] == nullptr;\
    \ }\n        inline bool is_present(bool b) const noexcept { return ch[b] != nullptr;\
    \ }\n        static inline int size(const Node *const node) noexcept { return\
    \ node == nullptr ? 0 : node->siz; }\n        inline void update_size() noexcept\
    \ { siz = size(ch[0]) + size(ch[1]); }\n\n        std::string to_string(const\
    \ int k = bit_length - 1, const U val = 0, const std::string &prefix = \"\") const\
    \ {\n            static const std::string zo[2] {\"+-[0]- \", \"+-[1]- \"};\n\
    \            static const std::string branch = '|' + std::string(zo[0].size()\
    \ - 1, ' ');\n            auto res = std::to_string(siz) + ' ';\n            if\
    \ (is_absent(0) and is_absent(1)) {\n                return res + \"(\" + std::to_string(val)\
    \ + \")\\n\";\n            }\n            auto pref0 = prefix + std::string(res.size(),\
    \ ' ');\n            auto prefb = pref0 + branch;\n            auto pref1 = pref0\
    \ + std::string(zo[0].size(), ' ');\n            if (is_absent(0) or is_absent(1))\
    \ {\n                bool b = is_absent(0);\n                return res + zo[b]\
    \ + ch[b]->to_string(k - 1, val | (b << k), pref1);\n            }\n         \
    \   res += zo[0] + ch[0]->to_string(k - 1, val, prefb);\n            res += pref0\
    \ + \"|\\n\";\n            res += pref0 + zo[1] + ch[1]->to_string(k - 1, val\
    \ | (1 << k), pref1);\n            return res;\n        }\n    };\n    public:\n\
    \        BinaryTrie() : root(new Node) {}\n        ~BinaryTrie() { delete root;\
    \ }\n\n        inline int size() const noexcept { return Node::size(root); }\n\
    \        inline bool empty() const noexcept { return size() == 0; }\n\n      \
    \  int insert(const U val, const int num = 1) noexcept {\n            if (num\
    \ == 0) return 0;\n            Node *cur = root;\n            cur->siz += num;\n\
    \            for (int i = bit_length; i --> 0;) {\n                cur = cur->get_or_create(bit(val,\
    \ i));\n                cur->siz += num;\n            }\n            return cur->siz;\n\
    \        }\n        int erase(const U val, const int num = 1) noexcept {\n   \
    \         if (num == 0) return 0;\n            return erase(root, bit_length -\
    \ 1, val, num);\n        }\n        int erase_all(const U val) noexcept {\n  \
    \          return erase(val, std::numeric_limits<int>::max());\n        }\n  \
    \      int prefix_count(const U val, const unsigned int l) const noexcept {\n\
    \            Node *cur = root;\n            for (int i = bit_length; i --> l;)\
    \ {\n                if (cur == nullptr) return 0;\n                cur = (*cur)[bit(val,\
    \ i)];\n            }\n            return Node::size(cur);\n        }\n      \
    \  inline int count(const U val) const noexcept { return prefix_count(val, 0);\
    \ }\n        inline bool contains(const U val) const noexcept { return count(val)\
    \ > 0; }\n\n        inline U xor_kth_min(const U x, const int k) const {\n   \
    \         assert(0 <= k and k < size());\n            return unchecked_xor_kth_element</*\
    \ is_max_query = */false>(x, k);\n        }\n        inline U xor_kth_max(const\
    \ U x, const int k) const {\n            assert(0 <= k and k < size());\n    \
    \        return unchecked_xor_kth_element</* is_max_query = */true>(x, k);\n \
    \       }\n        inline U xor_min(const U x) const { return xor_kth_min(x, 0);\
    \  }\n        inline U xor_max(const U x) const { return xor_kth_max(x, 0); }\n\
    \        int xor_count_lt(const U x, const U val) const noexcept {\n         \
    \   int res = 0;\n            Node *cur = root;\n            for (int i = bit_length\
    \ - 1; i >= 0; --i) {\n                if (cur == nullptr) break;\n          \
    \      bool bx = bit(x, i);\n                bool bv = bit(x ^ val, i);\n    \
    \            if (bx != bv) {\n                    res += Node::size((*cur)[bx]);\n\
    \                }\n                cur = (*cur)[bv];\n            }\n       \
    \     return res;\n        }\n        inline int xor_count_leq(const U x, const\
    \ U val) const noexcept { return xor_count_lt(x, val) + count(val); }\n      \
    \  inline int xor_count_gt (const U x, const U val) const noexcept { return size()\
    \ - xor_count_leq(x, val);    }\n        inline int xor_count_geq(const U x, const\
    \ U val) const noexcept { return size() - xor_count_lt(x, val);     }\n      \
    \  inline U xor_lower(const U x, const U val, const U default_value = ~U(0)) const\
    \ noexcept {\n            int k = size() - xor_count_geq(x, val) - 1;\n      \
    \      return k < 0 ? default_value : unchecked_xor_kth_element(x, k);\n     \
    \   }\n        inline U xor_floor(const U x, const U val, const U default_value\
    \ = ~U(0)) const noexcept {\n            int k = size() - xor_count_gt(x, val)\
    \ - 1;\n            return k < 0 ? default_value : unchecked_xor_kth_element(x,\
    \ k);\n        }\n        inline U xor_higher(const U x, const U val, const U\
    \ default_value = ~U(0)) const noexcept {\n            int k = xor_count_leq(x,\
    \ val);\n            return k == size() ? default_value : unchecked_xor_kth_element(x,\
    \ k);\n        }\n        inline U xor_ceil(const U x, const U val, const U default_value\
    \ = ~U(0)) const noexcept {\n            int k = xor_count_lt(x, val);\n     \
    \       return k == size() ? default_value : unchecked_xor_kth_element(x, k);\n\
    \        }\n\n        inline U kth_min(const int k) const { return xor_kth_min(0,\
    \ k); }\n        inline U min() const { return xor_kth_min(0, 0); }\n        inline\
    \ U max() const { return xor_kth_min(~U(0), 0); }\n        inline int count_lt\
    \ (const U val) const noexcept { return xor_count_lt(0, val);  }\n        inline\
    \ int count_leq(const U val) const noexcept { return xor_count_leq(0, val); }\n\
    \        inline int count_gt (const U val) const noexcept { return xor_count_gt(0,\
    \ val);  }\n        inline int count_geq(const U val) const noexcept { return\
    \ xor_count_geq(0, val); }\n        inline U lower (const U val, const U default_value\
    \ = ~U(0)) const noexcept { return xor_lower (0, val, default_value); }\n    \
    \    inline U floor (const U val, const U default_value = ~U(0)) const noexcept\
    \ { return xor_floor (0, val, default_value); }\n        inline U higher(const\
    \ U val, const U default_value = ~U(0)) const noexcept { return xor_higher(0,\
    \ val, default_value); }\n        inline U ceil  (const U val, const U default_value\
    \ = ~U(0)) const noexcept { return xor_ceil  (0, val, default_value); }\n\n  \
    \      inline std::string to_string() const noexcept { return root->to_string();\
    \ }\n        friend std::ostream& operator<<(std::ostream& out, const BinaryTrie\
    \ &bt) { return out << bt.to_string(); }\n    private:\n        Node *const root;\n\
    \        static constexpr bool bit(const U val, const int i) noexcept {\n    \
    \        return (val >> i) & 1;\n        }\n        int erase(Node *cur, const\
    \ int k, const U val, const int num) {\n            if (k == -1) {\n         \
    \       int removed = std::min(cur->siz, num);\n                cur->siz -= removed;\n\
    \                return removed;\n            }\n            bool b = bit(val,\
    \ k);\n            if (cur->is_absent(b)) return 0;\n            int removed =\
    \ erase((*cur)[b], k - 1, val, num);\n            cur->update_size();\n      \
    \      return removed;\n        }\n        template <bool is_max_query = false>\n\
    \        U unchecked_xor_kth_element(const U x, const int k) const noexcept {\n\
    \            U res = 0;\n            int rest = k;\n            Node *cur = root;\n\
    \            for (int i = bit_length - 1; i >= 0; --i) {\n                bool\
    \ b = is_max_query ^ bit(x, i);\n                int sz = Node::size((*cur)[b]);\n\
    \                if (sz <= rest) rest -= sz, b = not b;\n                res |=\
    \ U(b) << i;\n                cur = (*cur)[b];\n            }\n            return\
    \ x ^ res;\n        }\n};\n} // namespace suisen\n\n#endif // SUISEN_BINARY_TRIE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/binary_trie.hpp
  requiredBy: []
  timestamp: '2022-03-28 17:49:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/binary_trie/set_xor_min.test.cpp
  - test/src/datastructure/binary_trie/xor_game.test.cpp
documentation_of: library/datastructure/binary_trie.hpp
layout: document
title: Binary Trie
---
## Binary Trie