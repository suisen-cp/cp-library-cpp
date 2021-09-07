---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/string/suffix_automaton.hpp
    title: library/string/suffix_automaton.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"test/src/string/suffix_automaton/number_of_substrings.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\n\
    #include <iostream>\n\n#line 1 \"library/string/suffix_automaton.hpp\"\n\n\n\n\
    #include <cassert>\n#include <deque>\n#include <map>\n#include <string>\n#include\
    \ <vector>\n\nnamespace suisen {\n\n/**\n * reference : https://w.atwiki.jp/uwicoder/pages/2842.html\n\
    \ */\ntemplate <typename T, typename Container>\nclass SuffixAutomatonBase {\n\
    \    struct Node {\n        std::map<T, int> nxt;\n        int link, len;\n  \
    \      bool cloned;\n    };\n\n    public:\n        SuffixAutomatonBase() {\n\
    \            nodes.push_back({ {}, -1, 0, false });\n            last = 0;\n \
    \       }\n        SuffixAutomatonBase(const Container &s) : SuffixAutomatonBase()\
    \ {\n            for (const T &c : s) append(c);\n        }\n\n        void append(const\
    \ T &c) {\n            const int new_node = nodes.size();\n            nodes.push_back({\
    \ {}, -1, nodes[last].len + 1, false });\n            int p = last;\n        \
    \    for (; p != -1 and not nodes[p].nxt.count(c); p = nodes[p].link) nodes[p].nxt[c]\
    \ = new_node;\n            const int q = p == -1 ? 0 : nodes[p].nxt[c];\n    \
    \        if (p == -1 or nodes[p].len + 1 == nodes[q].len) {\n                nodes[new_node].link\
    \ = q;\n            } else {\n                const int clone_node = nodes.size();\n\
    \                nodes.push_back({ nodes[q].nxt, nodes[q].link, nodes[p].len +\
    \ 1, true });\n                for (; p != -1 and nodes[p].nxt[c] == q; p = nodes[p].link)\
    \ nodes[p].nxt[c] = clone_node;\n                nodes[new_node].link = nodes[q].link\
    \ = clone_node;\n            }\n            last = new_node;\n        }\n\n  \
    \      SuffixAutomatonBase& operator+=(const T &c) {\n            append(c);\n\
    \            return *this;\n        }\n\n        long long number_of_substrings()\
    \ const {\n            return substring_set().size();\n        }\n\n        bool\
    \ accept(const Container &t) const {\n            int cur = 0;\n            for\
    \ (const auto &c : t) {\n                auto it = nodes[cur].nxt.find(c);\n \
    \               if (it == nodes[cur].nxt.end()) return false;\n              \
    \  cur = it->second;\n            }\n            return true;\n        }\n\n \
    \       class SubstringCounter {\n            public:\n                SubstringCounter(const\
    \ SuffixAutomatonBase &sa, std::vector<long long> &&dp) : sa_(sa), dp_(std::move(dp))\
    \ {}\n\n                long long count(const Container &t) const {\n        \
    \            int cur = 0;\n                    for (const auto &c : t) {\n   \
    \                     auto it = sa_.nodes[cur].nxt.find(c);\n                \
    \        if (it == sa_.nodes[cur].nxt.end()) return 0;\n                     \
    \   cur = it->second;\n                    }\n                    return dp_[cur];\n\
    \                }\n\n            private:\n                const SuffixAutomatonBase\
    \ &sa_;\n                const std::vector<long long> dp_;\n        };\n\n   \
    \     SubstringCounter substring_counter() const {\n            const int n =\
    \ nodes.size();\n            const std::vector<int> ord = topological_order();\n\
    \            std::vector<long long> dp(n, 0);\n            for (int i = n - 1;\
    \ i > 0; --i) {\n                const int u = ord[i];\n                if (not\
    \ nodes[u].cloned) ++dp[u];\n                dp[nodes[u].link] += dp[u];\n   \
    \         }\n            return SubstringCounter { *this, std::move(dp) };\n \
    \       }\n\n        class SubstringSet {\n            public:\n             \
    \   SubstringSet(const SuffixAutomatonBase *sa, std::vector<long long> &&dp) :\
    \ sa(sa), dp(std::move(dp)) {}\n\n                long long size() const {\n \
    \                   return dp[0];\n                }\n\n                bool contains(const\
    \ Container &t) const {\n                    return sa->accept(t);\n         \
    \       }\n\n                Container operator[](long long k) const {\n     \
    \               assert((unsigned long long) k < dp[0]);\n                    int\
    \ cur = 0;\n                    Container res;\n                    while (k--)\
    \ {\n                        for (const auto &[e, v] : sa->nodes[cur].nxt) {\n\
    \                            if (k < dp[v]) {\n                              \
    \  res.push_back(e);\n                                cur = v;\n             \
    \                   break;\n                            } else {\n           \
    \                     k -= dp[v];\n                            }\n           \
    \             }\n                    }\n                    return res;\n    \
    \            }\n\n                Container kth_substring(unsigned long long k)\
    \ const {\n                    return (*this)[k];\n                }\n\n     \
    \           long long count_lt(const Container &t) const {\n                 \
    \   long long res = 0;\n                    int cur = 0;\n                   \
    \ for (const T& c : t) {\n                        ++res;\n                   \
    \     auto it_r = sa->nodes[cur].nxt.lower_bound(c);\n                       \
    \ for (auto it_l = sa->nodes[cur].nxt.begin(); it_l != it_r; ++it_l) {\n     \
    \                       res += dp[it_l->second];\n                        }\n\
    \                        if (it_r == sa->nodes[cur].nxt.end() or it_r->first !=\
    \ c) break;\n                        cur = it_r->second;\n                   \
    \ }\n                    return res;\n                }\n                long\
    \ long count_leq(const Container &t) const {\n                    return count_lt(t)\
    \ + contains(t);\n                }\n                long long count_gt(const\
    \ Container &t) const {\n                    return size() - count_leq(t);\n \
    \               }\n                long long count_geq(const Container &t) const\
    \ {\n                    return size() - count_lt(t);\n                }\n\n \
    \               Container min_geq(const Container &t) const {\n              \
    \      return (*this)[count_lt(t)];\n                }\n                Container\
    \ min_gt(const Container &t) const {\n                    return (*this)[count_leq(t)];\n\
    \                }\n                Container max_lt(const Container &t) const\
    \ {\n                    return (*this)[count_lt(t) - 1];\n                }\n\
    \                Container max_leq(const Container &t) const {\n             \
    \       return (*this)[count_leq(t) - 1];\n                }\n\n             \
    \   class SubstringSetIterator {\n                    public:\n              \
    \          SubstringSetIterator(const SubstringSet *s, long long init) : st(s),\
    \ k(init) {}\n\n                        SubstringSetIterator& operator=(const\
    \ SubstringSetIterator& other) {\n                            st = other.st;\n\
    \                            k = other.k;\n                            return\
    \ *this;\n                        }\n\n                        Container operator*()\
    \ const { return st->kth_substring(k); }\n\n                        SubstringSetIterator&\
    \ operator--() { --k; return *this; }\n                        SubstringSetIterator&\
    \ operator++() { ++k; return *this; }\n\n                        bool operator==(const\
    \ SubstringSetIterator& other) const { return k == other.k; }\n              \
    \          bool operator!=(const SubstringSetIterator& other) const { return k\
    \ != other.k; }\n                        bool operator< (const SubstringSetIterator&\
    \ other) const { return k <  other.k; }\n                        bool operator<=(const\
    \ SubstringSetIterator& other) const { return k <= other.k; }\n              \
    \          bool operator> (const SubstringSetIterator& other) const { return k\
    \ >  other.k; }\n                        bool operator>=(const SubstringSetIterator&\
    \ other) const { return k >= other.k; }\n\n                    private:\n    \
    \                    const SubstringSet *st;\n                        long long\
    \ k;\n                };\n\n                SubstringSetIterator begin() const\
    \ {\n                    return SubstringSetIterator { this, 0LL };\n        \
    \        }\n                SubstringSetIterator end() const {\n             \
    \       return SubstringSetIterator { this, size() };\n                }\n\n \
    \               SubstringSetIterator lower_bound(const Container &t) const {\n\
    \                    return SubstringSetIterator { this, count_lt(t) };\n    \
    \            }\n                SubstringSetIterator upper_bound(const Container\
    \ &t) const {\n                    return SubstringSetIterator { this, count_leq(t)\
    \ };\n                }\n\n                SubstringSetIterator find(const Container\
    \ &t) const {\n                    auto it = lower_bound(t);\n               \
    \     if (it == end() or t != *it) return end();\n                    return it;\n\
    \                }\n\n            private:\n                const SuffixAutomatonBase\
    \ *sa;\n                std::vector<long long> dp;\n        };\n\n        SubstringSet\
    \ substring_set() const {\n            const int n = nodes.size();\n         \
    \   const std::vector<int> ord = topological_order();\n            std::vector<long\
    \ long> dp(n, 1);\n            for (int i = n - 1; i >= 0; --i) {\n          \
    \      const int u = ord[i];\n                for (const auto &[_, v] : nodes[u].nxt)\
    \ dp[u] += dp[v];\n            }\n            return SubstringSet { this, std::move(dp)\
    \ };\n        }\n\n        // returns { from, len } s.t. lcs = t[from:from+len]\n\
    \        std::pair<int, int> longest_common_substring(const Container &t) const\
    \ {\n            if (t.size() == 0) return { 0, 0 };\n            const Node *v\
    \ = &nodes[0];\n            int l = 0, best = 0, best_pos = 0;\n            for\
    \ (int i = 0; i < int(t.size()); ++i){\n                while (v->link != -1 and\
    \ not v->nxt.count(t[i])) {\n                    v = &nodes[v->link];\n      \
    \              l = v->len;\n                }\n                auto it = v->nxt.find(t[i]);\n\
    \                if (it != v->nxt.end()){\n                    v = &nodes[it->second];\n\
    \                    l++;\n                }\n                if (l > best){\n\
    \                    best = l;\n                    best_pos = i;\n          \
    \      }\n            }\n            return { best_pos - best + 1, best };\n \
    \       }\n\n    private:\n        std::vector<Node> nodes;\n        int last;\n\
    \n        std::vector<int> topological_order() const {\n            const int\
    \ n = nodes.size();\n            std::vector<int> in(n, 0);\n            for (const\
    \ auto &node : nodes) {\n                for (const auto &[_, v] : node.nxt) ++in[v];\n\
    \            }\n            std::deque<int> dq;\n            for (int i = 0; i\
    \ < n; ++i) {\n                if (in[i] == 0) dq.push_back(i);\n            }\n\
    \            std::vector<int> res;\n            while (dq.size()) {\n        \
    \        int u = dq.front();\n                dq.pop_front();\n              \
    \  res.push_back(u);\n                for (const auto &[_, v] : nodes[u].nxt)\
    \ {\n                    if (--in[v] == 0) dq.push_back(v);\n                }\n\
    \            }\n            assert(int(res.size()) == n);\n            return\
    \ res;\n        }\n};\n\ntemplate <typename T>\nstruct SuffixAutomaton : public\
    \ SuffixAutomatonBase<T, std::vector<T>> {\n    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;\n\
    };\n\ntemplate <>\nstruct SuffixAutomaton<char> : public SuffixAutomatonBase<char,\
    \ std::string> {\n    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;\n\
    };\n\ntemplate <typename T>\nSuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;\n\
    SuffixAutomaton(std::string) -> SuffixAutomaton<char>;\n\n} // namespace suisen\n\
    \n\n#line 6 \"test/src/string/suffix_automaton/number_of_substrings.test.cpp\"\
    \nusing suisen::SuffixAutomaton;\n\nint main() {\n    std::string s;\n    std::cin\
    \ >> s;\n    std::cout << SuffixAutomaton(s).number_of_substrings() - 1 << std::endl;\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    \n#include <iostream>\n\n#include \"library/string/suffix_automaton.hpp\"\nusing\
    \ suisen::SuffixAutomaton;\n\nint main() {\n    std::string s;\n    std::cin >>\
    \ s;\n    std::cout << SuffixAutomaton(s).number_of_substrings() - 1 << std::endl;\n\
    \    return 0;\n}"
  dependsOn:
  - library/string/suffix_automaton.hpp
  isVerificationFile: true
  path: test/src/string/suffix_automaton/number_of_substrings.test.cpp
  requiredBy: []
  timestamp: '2021-09-08 04:34:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/string/suffix_automaton/number_of_substrings.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/suffix_automaton/number_of_substrings.test.cpp
- /verify/test/src/string/suffix_automaton/number_of_substrings.test.cpp.html
title: test/src/string/suffix_automaton/number_of_substrings.test.cpp
---
