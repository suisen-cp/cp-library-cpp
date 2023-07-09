---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/string/aho_corasick_array.hpp
    title: Aho Corasick Array
  - icon: ':x:'
    path: library/string/trie_array.hpp
    title: Trie Array
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc268/tasks/abc268_Ex
    links:
    - https://atcoder.jp/contests/abc268/tasks/abc268_Ex
  bundledCode: "#line 1 \"test/src/string/aho_corasick_array/abc268_h.test.cpp\"\n\
    #define PROBLEM \"https://atcoder.jp/contests/abc268/tasks/abc268_Ex\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/string/aho_corasick_array.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cassert>\n#include <deque>\n#include <vector>\n\n#line 1\
    \ \"library/string/trie_array.hpp\"\n\n\n\n#line 7 \"library/string/trie_array.hpp\"\
    \n\nnamespace suisen {\n    template <int _alphabet_size, int _offset>\n    struct\
    \ ArrayTrieNode : std::array<int, _alphabet_size> {\n        using key_type =\
    \ int;\n\n        static constexpr int none = -1;\n        static constexpr int\
    \ alphabet_size = _alphabet_size;\n        static constexpr int offset = _offset;\n\
    \n        ArrayTrieNode() { this->fill(none); }\n    };\n    template <int _alphabet_size,\
    \ int _offset>\n    struct ArrayTrieNodeWithParentLink : ArrayTrieNode<_alphabet_size,\
    \ _offset> {\n        using base_node_type = ArrayTrieNode<_alphabet_size, _offset>;\n\
    \        using key_type = typename base_node_type::key_type;\n        int par;\n\
    \        key_type key;\n\n        ArrayTrieNodeWithParentLink() : base_node_type()\
    \ {}\n        ArrayTrieNodeWithParentLink(int par, const key_type& key) : base_node_type(),\
    \ par(par), key(key) {}\n    };\n\n    template <typename NodeType, std::enable_if_t<std::is_base_of_v<ArrayTrieNode<NodeType::alphabet_size,\
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
    \  };\n} // namespace suisen\n\n\n#line 10 \"library/string/aho_corasick_array.hpp\"\
    \n\nnamespace suisen {\n    template <int alphabet_size, int offset>\n    struct\
    \ AhoCorasickArrayNode : ArrayTrieNode<alphabet_size, offset> {\n        int count;\n\
    \        int failure;\n    };\n\n    template <int alphabet_size, int offset>\n\
    \    struct AhoCorasickArray : private ArrayTrie<AhoCorasickArrayNode<alphabet_size,\
    \ offset>> {\n        using base_type = ArrayTrie<AhoCorasickArrayNode<alphabet_size,\
    \ offset>>;\n        using node_type = typename base_type::node_type;\n      \
    \  using key_type = typename base_type::key_type;\n\n        using base_type::base_type;\n\
    \n        template <typename Container, std::enable_if_t<std::is_constructible_v<key_type,\
    \ typename Container::value_type>, std::nullptr_t> = nullptr>\n        void add(const\
    \ Container& s) {\n            ++base_type::add(s).count;\n        }\n\n     \
    \   void build() {\n            this->nodes[0].failure = init_state();\n     \
    \       std::deque<int> dq{ init_state() };\n            while (dq.size()) {\n\
    \                const int cur = dq.front();\n                dq.pop_front();\n\
    \                const auto& links = this->nodes[this->nodes[cur].failure];\n\
    \                for (int i = 0; i < alphabet_size; ++i) {\n                 \
    \   const int link = cur ? links[i] : init_state();\n                    if (int&\
    \ nxt = this->nodes[cur][i]; nxt != node_type::none) {\n                     \
    \   this->nodes[nxt].failure = link;\n                        this->nodes[nxt].count\
    \ += this->nodes[link].count;\n                        dq.push_back(nxt);\n  \
    \                  } else {\n                        nxt = link;\n           \
    \         }\n                }\n            }\n            _built = true;\n  \
    \      }\n\n\n        int state_num() const {\n            return this->nodes.size();\n\
    \        }\n\n        int init_state() const {\n            return 0;\n      \
    \  }\n        int next_state(int state, key_type c) const {\n            assert(_built);\n\
    \            return this->nodes[state][c - offset];\n        }\n        int count_suffix_matching(int\
    \ state) const {\n            assert(_built);\n            return this->nodes[state].count;\n\
    \        }\n    private:\n        bool _built = false;\n    };\n\n} // namespace\
    \ suisen\n\n\n\n#line 6 \"test/src/string/aho_corasick_array/abc268_h.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \ \n    std::string s;\n    std::cin >> s;\n    int n;\n    std::cin >> n;\n \n\
    \    suisen::AhoCorasickArray<26, 'a'> ac;\n    for (int i = 0; i < n; ++i) {\n\
    \        std::string t;\n        std::cin >> t;\n        ac.add(t);\n    }\n \
    \   ac.build();\n\n    int ans = 0;\n    int state = ac.init_state();\n    for\
    \ (char c : s) {\n        if (int next_state = ac.next_state(state, c); ac.count_suffix_matching(next_state))\
    \ {\n            ++ans;\n            state = ac.init_state();\n        } else\
    \ {\n            state = next_state;\n        }\n    }\n    std::cout << ans <<\
    \ std::endl;\n \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc268/tasks/abc268_Ex\"\n\n\
    #include <iostream>\n\n#include \"library/string/aho_corasick_array.hpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \ \n    std::string s;\n    std::cin >> s;\n    int n;\n    std::cin >> n;\n \n\
    \    suisen::AhoCorasickArray<26, 'a'> ac;\n    for (int i = 0; i < n; ++i) {\n\
    \        std::string t;\n        std::cin >> t;\n        ac.add(t);\n    }\n \
    \   ac.build();\n\n    int ans = 0;\n    int state = ac.init_state();\n    for\
    \ (char c : s) {\n        if (int next_state = ac.next_state(state, c); ac.count_suffix_matching(next_state))\
    \ {\n            ++ans;\n            state = ac.init_state();\n        } else\
    \ {\n            state = next_state;\n        }\n    }\n    std::cout << ans <<\
    \ std::endl;\n \n    return 0;\n}"
  dependsOn:
  - library/string/aho_corasick_array.hpp
  - library/string/trie_array.hpp
  isVerificationFile: true
  path: test/src/string/aho_corasick_array/abc268_h.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/string/aho_corasick_array/abc268_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/aho_corasick_array/abc268_h.test.cpp
- /verify/test/src/string/aho_corasick_array/abc268_h.test.cpp.html
title: test/src/string/aho_corasick_array/abc268_h.test.cpp
---
