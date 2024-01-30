---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/string/aho_corasick_array.hpp
    title: Aho Corasick Array
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/aho_corasick_array/abc268_h.test.cpp
    title: test/src/string/aho_corasick_array/abc268_h.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/trie_array.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template <int\
    \ _alphabet_size, int _offset>\n    struct ArrayTrieNode : std::array<int, _alphabet_size>\
    \ {\n        using key_type = int;\n\n        static constexpr int none = -1;\n\
    \        static constexpr int alphabet_size = _alphabet_size;\n        static\
    \ constexpr int offset = _offset;\n\n        ArrayTrieNode() { this->fill(none);\
    \ }\n    };\n    template <int _alphabet_size, int _offset>\n    struct ArrayTrieNodeWithParentLink\
    \ : ArrayTrieNode<_alphabet_size, _offset> {\n        using base_node_type = ArrayTrieNode<_alphabet_size,\
    \ _offset>;\n        using key_type = typename base_node_type::key_type;\n   \
    \     int par;\n        key_type key;\n\n        ArrayTrieNodeWithParentLink()\
    \ : base_node_type() {}\n        ArrayTrieNodeWithParentLink(int par, const key_type&\
    \ key) : base_node_type(), par(par), key(key) {}\n    };\n\n    template <typename\
    \ NodeType, std::enable_if_t<std::is_base_of_v<ArrayTrieNode<NodeType::alphabet_size,\
    \ NodeType::offset>, NodeType>, std::nullptr_t> = nullptr>\n    struct ArrayTrie\
    \ {\n        using node_type = NodeType;\n        using key_type = typename node_type::key_type;\n\
    \n        static constexpr int none = node_type::none;\n        static constexpr\
    \ int alphabet_size = node_type::alphabet_size;\n        static constexpr int\
    \ offset = node_type::offset;\n\n        static constexpr int root = 0;\n\n  \
    \      using base_node_type = ArrayTrieNode<alphabet_size, offset>;\n\n      \
    \  std::vector<node_type> nodes;\n\n        ArrayTrie() {\n            nodes.emplace_back();\n\
    \        }\n\n        void reserve(int capacity) {\n            nodes.reserve(capacity);\n\
    \        }\n\n        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        node_type&\
    \ add(const Container& s, int start = 0) {\n            int cur = start;\n   \
    \         for (key_type c : s) {\n                c -= offset;\n             \
    \   if (nodes[cur][c] == none) {\n                    nodes[cur][c] = nodes.size();\n\
    \                    if constexpr (std::is_base_of_v<ArrayTrieNodeWithParentLink<alphabet_size,\
    \ offset>, node_type>) {\n                        nodes.emplace_back(cur, c);\n\
    \                    } else {\n                        nodes.emplace_back();\n\
    \                    }\n                }\n                cur = nodes[cur][c];\n\
    \            }\n            return nodes[cur];\n        }\n\n        const node_type&\
    \ operator[](int i) const {\n            return nodes[i];\n        }\n       \
    \ node_type& operator[](int i) {\n            return nodes[i];\n        }\n  \
    \  };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_TRIE_ARRAY\n#define SUISEN_TRIE_ARRAY\n\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template <int\
    \ _alphabet_size, int _offset>\n    struct ArrayTrieNode : std::array<int, _alphabet_size>\
    \ {\n        using key_type = int;\n\n        static constexpr int none = -1;\n\
    \        static constexpr int alphabet_size = _alphabet_size;\n        static\
    \ constexpr int offset = _offset;\n\n        ArrayTrieNode() { this->fill(none);\
    \ }\n    };\n    template <int _alphabet_size, int _offset>\n    struct ArrayTrieNodeWithParentLink\
    \ : ArrayTrieNode<_alphabet_size, _offset> {\n        using base_node_type = ArrayTrieNode<_alphabet_size,\
    \ _offset>;\n        using key_type = typename base_node_type::key_type;\n   \
    \     int par;\n        key_type key;\n\n        ArrayTrieNodeWithParentLink()\
    \ : base_node_type() {}\n        ArrayTrieNodeWithParentLink(int par, const key_type&\
    \ key) : base_node_type(), par(par), key(key) {}\n    };\n\n    template <typename\
    \ NodeType, std::enable_if_t<std::is_base_of_v<ArrayTrieNode<NodeType::alphabet_size,\
    \ NodeType::offset>, NodeType>, std::nullptr_t> = nullptr>\n    struct ArrayTrie\
    \ {\n        using node_type = NodeType;\n        using key_type = typename node_type::key_type;\n\
    \n        static constexpr int none = node_type::none;\n        static constexpr\
    \ int alphabet_size = node_type::alphabet_size;\n        static constexpr int\
    \ offset = node_type::offset;\n\n        static constexpr int root = 0;\n\n  \
    \      using base_node_type = ArrayTrieNode<alphabet_size, offset>;\n\n      \
    \  std::vector<node_type> nodes;\n\n        ArrayTrie() {\n            nodes.emplace_back();\n\
    \        }\n\n        void reserve(int capacity) {\n            nodes.reserve(capacity);\n\
    \        }\n\n        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        node_type&\
    \ add(const Container& s, int start = 0) {\n            int cur = start;\n   \
    \         for (key_type c : s) {\n                c -= offset;\n             \
    \   if (nodes[cur][c] == none) {\n                    nodes[cur][c] = nodes.size();\n\
    \                    if constexpr (std::is_base_of_v<ArrayTrieNodeWithParentLink<alphabet_size,\
    \ offset>, node_type>) {\n                        nodes.emplace_back(cur, c);\n\
    \                    } else {\n                        nodes.emplace_back();\n\
    \                    }\n                }\n                cur = nodes[cur][c];\n\
    \            }\n            return nodes[cur];\n        }\n\n        const node_type&\
    \ operator[](int i) const {\n            return nodes[i];\n        }\n       \
    \ node_type& operator[](int i) {\n            return nodes[i];\n        }\n  \
    \  };\n} // namespace suisen\n\n#endif // SUISEN_TRIE_ARRAY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/trie_array.hpp
  requiredBy:
  - library/string/aho_corasick_array.hpp
  timestamp: '2022-11-06 23:07:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/aho_corasick_array/abc268_h.test.cpp
documentation_of: library/string/trie_array.hpp
layout: document
title: Trie Array
---
## Trie Array