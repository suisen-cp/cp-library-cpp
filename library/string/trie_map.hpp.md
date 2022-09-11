---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/trie_map.hpp\"\n\n\n\n#include <map>\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T>\n    struct MapTrieNode\
    \ : std::map<T, int> {\n        static constexpr int none = -1;\n\n        using\
    \ key_type = T;\n\n        int operator[](const key_type& c) const {\n       \
    \     auto it = this->find(c);\n            return it == this->end() ? none :\
    \ it->second;\n        }\n        int& operator[](const key_type& c) {\n     \
    \       return this->try_emplace(c, none).first->second;\n        }\n    };\n\
    \    template <typename NodeType, std::enable_if_t<std::is_base_of_v<MapTrieNode<typename\
    \ NodeType::key_type>, NodeType>, std::nullptr_t> = nullptr>\n    struct MapTrie\
    \ {\n        using node_type = NodeType;\n        using key_type = typename node_type::key_type;\n\
    \        using base_node_type = MapTrieNode<key_type>;\n\n        static constexpr\
    \ int none = node_type::none;\n\n        std::vector<node_type> nodes;\n\n   \
    \     MapTrie() { nodes.emplace_back(); }\n\n        void reserve(int capacity)\
    \ {\n            nodes.reserve(capacity);\n        }\n\n        template <typename\
    \ Container, std::enable_if_t<std::is_constructible_v<key_type, typename Container::value_type>,\
    \ std::nullptr_t> = nullptr>\n        node_type& add(const Container& s, int start\
    \ = 0) {\n            int cur = start;\n            for (key_type c : s) {\n \
    \               auto [it, inserted] = nodes[cur].try_emplace(c, nodes.size());\n\
    \                if (inserted) nodes.emplace_back();\n                cur = it->second;\n\
    \            }\n            return nodes[cur];\n        }\n        const node_type&\
    \ operator[](int i) const {\n            return nodes[i];\n        }\n       \
    \ node_type& operator[](int i) {\n            return nodes[i];\n        }\n  \
    \  };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TRIE_MAP\n#define SUISEN_TRIE_MAP\n\n#include <map>\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T>\n    struct MapTrieNode\
    \ : std::map<T, int> {\n        static constexpr int none = -1;\n\n        using\
    \ key_type = T;\n\n        int operator[](const key_type& c) const {\n       \
    \     auto it = this->find(c);\n            return it == this->end() ? none :\
    \ it->second;\n        }\n        int& operator[](const key_type& c) {\n     \
    \       return this->try_emplace(c, none).first->second;\n        }\n    };\n\
    \    template <typename NodeType, std::enable_if_t<std::is_base_of_v<MapTrieNode<typename\
    \ NodeType::key_type>, NodeType>, std::nullptr_t> = nullptr>\n    struct MapTrie\
    \ {\n        using node_type = NodeType;\n        using key_type = typename node_type::key_type;\n\
    \        using base_node_type = MapTrieNode<key_type>;\n\n        static constexpr\
    \ int none = node_type::none;\n\n        std::vector<node_type> nodes;\n\n   \
    \     MapTrie() { nodes.emplace_back(); }\n\n        void reserve(int capacity)\
    \ {\n            nodes.reserve(capacity);\n        }\n\n        template <typename\
    \ Container, std::enable_if_t<std::is_constructible_v<key_type, typename Container::value_type>,\
    \ std::nullptr_t> = nullptr>\n        node_type& add(const Container& s, int start\
    \ = 0) {\n            int cur = start;\n            for (key_type c : s) {\n \
    \               auto [it, inserted] = nodes[cur].try_emplace(c, nodes.size());\n\
    \                if (inserted) nodes.emplace_back();\n                cur = it->second;\n\
    \            }\n            return nodes[cur];\n        }\n        const node_type&\
    \ operator[](int i) const {\n            return nodes[i];\n        }\n       \
    \ node_type& operator[](int i) {\n            return nodes[i];\n        }\n  \
    \  };\n} // namespace suisen\n\n\n#endif // SUISEN_TRIE_MAP\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/trie_map.hpp
  requiredBy: []
  timestamp: '2022-09-11 20:50:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/string/trie_map.hpp
layout: document
redirect_from:
- /library/library/string/trie_map.hpp
- /library/library/string/trie_map.hpp.html
title: library/string/trie_map.hpp
---
