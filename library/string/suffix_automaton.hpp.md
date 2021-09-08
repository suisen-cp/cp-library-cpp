---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/string/substring_set.hpp
    title: library/string/substring_set.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/substring_set/arc097_a.test.cpp
    title: test/src/string/substring_set/arc097_a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/substring_set/number_of_substrings.test.cpp
    title: test/src/string/substring_set/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/suffix_automaton/yuki430.test.cpp
    title: test/src/string/suffix_automaton/yuki430.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://w.atwiki.jp/uwicoder/pages/2842.html
  bundledCode: "#line 1 \"library/string/suffix_automaton.hpp\"\n\n\n\n#include <cassert>\n\
    #include <deque>\n#include <map>\n#include <string>\n#include <vector>\n\nnamespace\
    \ suisen {\n\n/**\n * reference : https://w.atwiki.jp/uwicoder/pages/2842.html\n\
    \ */\ntemplate <typename T, typename SequenceType>\nstruct SuffixAutomatonBase\
    \ {\n    struct Node {\n        std::map<T, int> nxt;\n        int link, len;\n\
    \        bool cloned;\n    };\n\n    std::vector<Node> nodes;\n    int last;\n\
    \n    SuffixAutomatonBase() {\n        nodes.push_back({ {}, -1, 0, false });\n\
    \        last = 0;\n    }\n    SuffixAutomatonBase(const SequenceType &s) : SuffixAutomatonBase()\
    \ {\n        for (const T &c : s) append(c);\n    }\n\n    void append(const T\
    \ &c) {\n        const int new_node = nodes.size();\n        nodes.push_back({\
    \ {}, -1, nodes[last].len + 1, false });\n        int p = last;\n        for (;\
    \ p != -1 and not nodes[p].nxt.count(c); p = nodes[p].link) nodes[p].nxt[c] =\
    \ new_node;\n        const int q = p == -1 ? 0 : nodes[p].nxt[c];\n        if\
    \ (p == -1 or nodes[p].len + 1 == nodes[q].len) {\n            nodes[new_node].link\
    \ = q;\n        } else {\n            const int clone_node = nodes.size();\n \
    \           nodes.push_back({ nodes[q].nxt, nodes[q].link, nodes[p].len + 1, true\
    \ });\n            for (; p != -1 and nodes[p].nxt[c] == q; p = nodes[p].link)\
    \ nodes[p].nxt[c] = clone_node;\n            nodes[new_node].link = nodes[q].link\
    \ = clone_node;\n        }\n        last = new_node;\n    }\n    SuffixAutomatonBase&\
    \ operator+=(const T &c) {\n        append(c);\n        return *this;\n    }\n\
    \n    bool accept(const SequenceType &t) const {\n        int cur = 0;\n     \
    \   for (const auto &c : t) {\n            auto it = nodes[cur].nxt.find(c);\n\
    \            if (it == nodes[cur].nxt.end()) return false;\n            cur =\
    \ it->second;\n        }\n        return true;\n    }\n\n    class SubstringCounter\
    \ {\n        public:\n            SubstringCounter(const SuffixAutomatonBase *sa,\
    \ std::vector<long long> &&dp) : sa(sa), dp(std::move(dp)) {}\n\n            long\
    \ long count(const SequenceType &t) const {\n                int cur = 0;\n  \
    \              for (const auto &c : t) {\n                    auto it = sa->nodes[cur].nxt.find(c);\n\
    \                    if (it == sa->nodes[cur].nxt.end()) return 0;\n         \
    \           cur = it->second;\n                }\n                return dp[cur];\n\
    \            }\n\n        private:\n            const SuffixAutomatonBase *sa;\n\
    \            const std::vector<long long> dp;\n    };\n\n    SubstringCounter\
    \ substring_counter() const & {\n        const int n = nodes.size();\n       \
    \ const std::vector<int> ord = topological_order();\n        std::vector<long\
    \ long> dp(n, 0);\n        for (int i = n - 1; i > 0; --i) {\n            const\
    \ int u = ord[i];\n            if (not nodes[u].cloned) ++dp[u];\n           \
    \ dp[nodes[u].link] += dp[u];\n        }\n        return SubstringCounter { this,\
    \ std::move(dp) };\n    }\n    SubstringCounter substring_counter() const && =\
    \ delete;\n\n    // returns { from, len } s.t. lcs = t[from:from+len]\n    std::pair<int,\
    \ int> longest_common_substring(const SequenceType &t) const {\n        if (t.size()\
    \ == 0) return { 0, 0 };\n        const Node *v = &nodes[0];\n        int l =\
    \ 0, best = 0, best_pos = 0;\n        for (int i = 0; i < int(t.size()); ++i){\n\
    \            while (v->link != -1 and not v->nxt.count(t[i])) {\n            \
    \    v = &nodes[v->link];\n                l = v->len;\n            }\n      \
    \      auto it = v->nxt.find(t[i]);\n            if (it != v->nxt.end()){\n  \
    \              v = &nodes[it->second];\n                l++;\n            }\n\
    \            if (l > best){\n                best = l;\n                best_pos\
    \ = i;\n            }\n        }\n        return { best_pos - best + 1, best };\n\
    \    }\n\n    std::vector<int> topological_order() const {\n        const int\
    \ n = nodes.size();\n        std::vector<int> in(n, 0);\n        for (const auto\
    \ &node : nodes) {\n            for (const auto &p : node.nxt) ++in[p.second];\n\
    \        }\n        std::deque<int> dq;\n        for (int i = 0; i < n; ++i) {\n\
    \            if (in[i] == 0) dq.push_back(i);\n        }\n        std::vector<int>\
    \ res;\n        while (dq.size()) {\n            int u = dq.front();\n       \
    \     dq.pop_front();\n            res.push_back(u);\n            for (const auto\
    \ &p : nodes[u].nxt) {\n                if (--in[p.second] == 0) dq.push_back(p.second);\n\
    \            }\n        }\n        assert(int(res.size()) == n);\n        return\
    \ res;\n    }\n};\n\ntemplate <typename T>\nstruct SuffixAutomaton : public SuffixAutomatonBase<T,\
    \ std::vector<T>> {\n    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;\n\
    \    using value_type = T;\n    using sequence_type = std::vector<T>;\n};\n\n\
    template <typename T>\nSuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;\n\
    \ntemplate <>\nstruct SuffixAutomaton<char> : public SuffixAutomatonBase<char,\
    \ std::string> {\n    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;\n\
    \    using value_type = char;\n    using sequence_type = std::string;\n};\n\n\
    SuffixAutomaton(std::string) -> SuffixAutomaton<char>;\n\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_SUFFIX_AUTOMATON\n#define SUISEN_SUFFIX_AUTOMATON\n\n#include\
    \ <cassert>\n#include <deque>\n#include <map>\n#include <string>\n#include <vector>\n\
    \nnamespace suisen {\n\n/**\n * reference : https://w.atwiki.jp/uwicoder/pages/2842.html\n\
    \ */\ntemplate <typename T, typename SequenceType>\nstruct SuffixAutomatonBase\
    \ {\n    struct Node {\n        std::map<T, int> nxt;\n        int link, len;\n\
    \        bool cloned;\n    };\n\n    std::vector<Node> nodes;\n    int last;\n\
    \n    SuffixAutomatonBase() {\n        nodes.push_back({ {}, -1, 0, false });\n\
    \        last = 0;\n    }\n    SuffixAutomatonBase(const SequenceType &s) : SuffixAutomatonBase()\
    \ {\n        for (const T &c : s) append(c);\n    }\n\n    void append(const T\
    \ &c) {\n        const int new_node = nodes.size();\n        nodes.push_back({\
    \ {}, -1, nodes[last].len + 1, false });\n        int p = last;\n        for (;\
    \ p != -1 and not nodes[p].nxt.count(c); p = nodes[p].link) nodes[p].nxt[c] =\
    \ new_node;\n        const int q = p == -1 ? 0 : nodes[p].nxt[c];\n        if\
    \ (p == -1 or nodes[p].len + 1 == nodes[q].len) {\n            nodes[new_node].link\
    \ = q;\n        } else {\n            const int clone_node = nodes.size();\n \
    \           nodes.push_back({ nodes[q].nxt, nodes[q].link, nodes[p].len + 1, true\
    \ });\n            for (; p != -1 and nodes[p].nxt[c] == q; p = nodes[p].link)\
    \ nodes[p].nxt[c] = clone_node;\n            nodes[new_node].link = nodes[q].link\
    \ = clone_node;\n        }\n        last = new_node;\n    }\n    SuffixAutomatonBase&\
    \ operator+=(const T &c) {\n        append(c);\n        return *this;\n    }\n\
    \n    bool accept(const SequenceType &t) const {\n        int cur = 0;\n     \
    \   for (const auto &c : t) {\n            auto it = nodes[cur].nxt.find(c);\n\
    \            if (it == nodes[cur].nxt.end()) return false;\n            cur =\
    \ it->second;\n        }\n        return true;\n    }\n\n    class SubstringCounter\
    \ {\n        public:\n            SubstringCounter(const SuffixAutomatonBase *sa,\
    \ std::vector<long long> &&dp) : sa(sa), dp(std::move(dp)) {}\n\n            long\
    \ long count(const SequenceType &t) const {\n                int cur = 0;\n  \
    \              for (const auto &c : t) {\n                    auto it = sa->nodes[cur].nxt.find(c);\n\
    \                    if (it == sa->nodes[cur].nxt.end()) return 0;\n         \
    \           cur = it->second;\n                }\n                return dp[cur];\n\
    \            }\n\n        private:\n            const SuffixAutomatonBase *sa;\n\
    \            const std::vector<long long> dp;\n    };\n\n    SubstringCounter\
    \ substring_counter() const & {\n        const int n = nodes.size();\n       \
    \ const std::vector<int> ord = topological_order();\n        std::vector<long\
    \ long> dp(n, 0);\n        for (int i = n - 1; i > 0; --i) {\n            const\
    \ int u = ord[i];\n            if (not nodes[u].cloned) ++dp[u];\n           \
    \ dp[nodes[u].link] += dp[u];\n        }\n        return SubstringCounter { this,\
    \ std::move(dp) };\n    }\n    SubstringCounter substring_counter() const && =\
    \ delete;\n\n    // returns { from, len } s.t. lcs = t[from:from+len]\n    std::pair<int,\
    \ int> longest_common_substring(const SequenceType &t) const {\n        if (t.size()\
    \ == 0) return { 0, 0 };\n        const Node *v = &nodes[0];\n        int l =\
    \ 0, best = 0, best_pos = 0;\n        for (int i = 0; i < int(t.size()); ++i){\n\
    \            while (v->link != -1 and not v->nxt.count(t[i])) {\n            \
    \    v = &nodes[v->link];\n                l = v->len;\n            }\n      \
    \      auto it = v->nxt.find(t[i]);\n            if (it != v->nxt.end()){\n  \
    \              v = &nodes[it->second];\n                l++;\n            }\n\
    \            if (l > best){\n                best = l;\n                best_pos\
    \ = i;\n            }\n        }\n        return { best_pos - best + 1, best };\n\
    \    }\n\n    std::vector<int> topological_order() const {\n        const int\
    \ n = nodes.size();\n        std::vector<int> in(n, 0);\n        for (const auto\
    \ &node : nodes) {\n            for (const auto &p : node.nxt) ++in[p.second];\n\
    \        }\n        std::deque<int> dq;\n        for (int i = 0; i < n; ++i) {\n\
    \            if (in[i] == 0) dq.push_back(i);\n        }\n        std::vector<int>\
    \ res;\n        while (dq.size()) {\n            int u = dq.front();\n       \
    \     dq.pop_front();\n            res.push_back(u);\n            for (const auto\
    \ &p : nodes[u].nxt) {\n                if (--in[p.second] == 0) dq.push_back(p.second);\n\
    \            }\n        }\n        assert(int(res.size()) == n);\n        return\
    \ res;\n    }\n};\n\ntemplate <typename T>\nstruct SuffixAutomaton : public SuffixAutomatonBase<T,\
    \ std::vector<T>> {\n    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;\n\
    \    using value_type = T;\n    using sequence_type = std::vector<T>;\n};\n\n\
    template <typename T>\nSuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;\n\
    \ntemplate <>\nstruct SuffixAutomaton<char> : public SuffixAutomatonBase<char,\
    \ std::string> {\n    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;\n\
    \    using value_type = char;\n    using sequence_type = std::string;\n};\n\n\
    SuffixAutomaton(std::string) -> SuffixAutomaton<char>;\n\n} // namespace suisen\n\
    \n#endif // SUISEN_SUFFIX_AUTOMATON\n"
  dependsOn: []
  isVerificationFile: false
  path: library/string/suffix_automaton.hpp
  requiredBy:
  - library/string/substring_set.hpp
  timestamp: '2021-09-08 17:15:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/substring_set/number_of_substrings.test.cpp
  - test/src/string/substring_set/arc097_a.test.cpp
  - test/src/string/suffix_automaton/yuki430.test.cpp
documentation_of: library/string/suffix_automaton.hpp
layout: document
redirect_from:
- /library/library/string/suffix_automaton.hpp
- /library/library/string/suffix_automaton.hpp.html
title: library/string/suffix_automaton.hpp
---
