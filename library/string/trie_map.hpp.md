---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/tree/tree_isomorphism_classification.hpp
    title: Tree Isomorphism Classification
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
    title: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/trie_map.hpp\"\n\n\n\n#include <map>\n#include\
    \ <unordered_map>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T, bool use_ordered_map = true>\n    struct MapTrieNode : std::conditional_t<use_ordered_map,\
    \ std::map<T, int>, std::unordered_map<T, int>> {\n        static constexpr int\
    \ none = -1;\n        static constexpr bool ordered = use_ordered_map;\n\n   \
    \     using key_type = T;\n\n        int operator[](const key_type& c) const {\n\
    \            auto it = this->find(c);\n            return it == this->end() ?\
    \ none : it->second;\n        }\n        int& operator[](const key_type& c) {\n\
    \            return this->try_emplace(c, none).first->second;\n        }\n   \
    \ };\n    template <\n        typename NodeType,\n        std::enable_if_t<std::is_base_of_v<MapTrieNode<typename\
    \ NodeType::key_type, NodeType::ordered>, NodeType>, std::nullptr_t> = nullptr\n\
    \    >\n    struct MapTrie {\n        using node_type = NodeType;\n        using\
    \ key_type = typename node_type::key_type;\n        using base_node_type = MapTrieNode<key_type>;\n\
    \n        static constexpr int none = node_type::none;\n\n        std::vector<node_type>\
    \ nodes;\n\n        MapTrie() { nodes.emplace_back(); }\n\n        void reserve(int\
    \ capacity) {\n            nodes.reserve(capacity);\n        }\n\n        template\
    \ <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n        node_type& add(const\
    \ Container& s, int start = 0) {\n            int cur = start;\n            for\
    \ (key_type c : s) {\n                auto [it, inserted] = nodes[cur].try_emplace(c,\
    \ nodes.size());\n                if (inserted) nodes.emplace_back();\n      \
    \          cur = it->second;\n            }\n            return nodes[cur];\n\
    \        }\n        const node_type& operator[](int i) const {\n            return\
    \ nodes[i];\n        }\n        node_type& operator[](int i) {\n            return\
    \ nodes[i];\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TRIE_MAP\n#define SUISEN_TRIE_MAP\n\n#include <map>\n#include\
    \ <unordered_map>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T, bool use_ordered_map = true>\n    struct MapTrieNode : std::conditional_t<use_ordered_map,\
    \ std::map<T, int>, std::unordered_map<T, int>> {\n        static constexpr int\
    \ none = -1;\n        static constexpr bool ordered = use_ordered_map;\n\n   \
    \     using key_type = T;\n\n        int operator[](const key_type& c) const {\n\
    \            auto it = this->find(c);\n            return it == this->end() ?\
    \ none : it->second;\n        }\n        int& operator[](const key_type& c) {\n\
    \            return this->try_emplace(c, none).first->second;\n        }\n   \
    \ };\n    template <\n        typename NodeType,\n        std::enable_if_t<std::is_base_of_v<MapTrieNode<typename\
    \ NodeType::key_type, NodeType::ordered>, NodeType>, std::nullptr_t> = nullptr\n\
    \    >\n    struct MapTrie {\n        using node_type = NodeType;\n        using\
    \ key_type = typename node_type::key_type;\n        using base_node_type = MapTrieNode<key_type>;\n\
    \n        static constexpr int none = node_type::none;\n\n        std::vector<node_type>\
    \ nodes;\n\n        MapTrie() { nodes.emplace_back(); }\n\n        void reserve(int\
    \ capacity) {\n            nodes.reserve(capacity);\n        }\n\n        template\
    \ <typename Container, std::enable_if_t<std::is_constructible_v<key_type, typename\
    \ Container::value_type>, std::nullptr_t> = nullptr>\n        node_type& add(const\
    \ Container& s, int start = 0) {\n            int cur = start;\n            for\
    \ (key_type c : s) {\n                auto [it, inserted] = nodes[cur].try_emplace(c,\
    \ nodes.size());\n                if (inserted) nodes.emplace_back();\n      \
    \          cur = it->second;\n            }\n            return nodes[cur];\n\
    \        }\n        const node_type& operator[](int i) const {\n            return\
    \ nodes[i];\n        }\n        node_type& operator[](int i) {\n            return\
    \ nodes[i];\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_TRIE_MAP\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/trie_map.hpp
  requiredBy:
  - library/tree/tree_isomorphism_classification.hpp
  timestamp: '2022-10-23 23:58:47+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
documentation_of: library/string/trie_map.hpp
layout: document
title: Trie Map
---
## Trie Map