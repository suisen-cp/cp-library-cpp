---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/string/substring_set.hpp
    title: Substring Set
  - icon: ':x:'
    path: library/string/suffix_automaton.hpp
    title: Suffix Automaton
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc097/tasks/arc097_c
    links:
    - https://atcoder.jp/contests/arc097/tasks/arc097_c
  bundledCode: "#line 1 \"test/src/string/substring_set/arc097_a.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/arc097/tasks/arc097_c\"\n\n#include <iostream>\n\
    \n#line 1 \"library/string/substring_set.hpp\"\n\n\n\n#line 1 \"library/string/suffix_automaton.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <deque>\n#include <limits>\n\
    #include <map>\n#include <string>\n#include <tuple>\n#include <vector>\n\nnamespace\
    \ suisen {\n\n/**\n * reference\n * - https://w.atwiki.jp/uwicoder/pages/2842.html\n\
    \ * - https://cp-algorithms.com/string/suffix-automaton.html\n */\ntemplate <typename\
    \ T, typename SequenceType>\nstruct SuffixAutomatonBase {\n    struct Node {\n\
    \        std::map<T, int> nxt;\n        int link, len;\n        bool cloned;\n\
    \        int index;\n    };\n\n    std::vector<Node> nodes;\n    int last;\n\n\
    \    SuffixAutomatonBase() {\n        nodes.push_back({ {}, -1, 0, false, -1 });\n\
    \        last = 0;\n    }\n    SuffixAutomatonBase(const SequenceType &s) : SuffixAutomatonBase()\
    \ {\n        for (const T &c : s) append(c);\n    }\n\n    void append(const T\
    \ &c) {\n        const int new_node = nodes.size();\n        const int new_node_index\
    \ = nodes[last].index + 1;\n        nodes.push_back({ {}, -1, nodes[last].len\
    \ + 1, false, new_node_index });\n        int p = last;\n        for (; p != -1\
    \ and not nodes[p].nxt.count(c); p = nodes[p].link) nodes[p].nxt[c] = new_node;\n\
    \        const int q = p == -1 ? 0 : nodes[p].nxt[c];\n        if (p == -1 or\
    \ nodes[p].len + 1 == nodes[q].len) {\n            nodes[new_node].link = q;\n\
    \        } else {\n            const int clone_node = nodes.size();\n        \
    \    nodes.push_back({ nodes[q].nxt, nodes[q].link, nodes[p].len + 1, true, new_node_index\
    \ });\n            for (; p != -1 and nodes[p].nxt[c] == q; p = nodes[p].link)\
    \ nodes[p].nxt[c] = clone_node;\n            nodes[new_node].link = nodes[q].link\
    \ = clone_node;\n        }\n        last = new_node;\n    }\n    SuffixAutomatonBase&\
    \ operator+=(const T &c) {\n        append(c);\n        return *this;\n    }\n\
    \n    int transition(const SequenceType &t, int invalid_state = -1) const {\n\
    \        int cur = 0;\n        for (const auto &c : t) {\n            auto it\
    \ = nodes[cur].nxt.find(c);\n            if (it == nodes[cur].nxt.end()) return\
    \ invalid_state;\n            cur = it->second;\n        }\n        return cur;\n\
    \    }\n\n    bool accept(const SequenceType &t) const {\n        return transition(t)\
    \ != -1;\n    }\n\n    class SubstringCounter {\n        public:\n           \
    \ SubstringCounter(const SuffixAutomatonBase *sa) : sa(sa), n(sa->nodes.size()),\
    \ dp(n, 0) {\n                const std::vector<Node> &nodes = sa->nodes;\n  \
    \              for (const int u : sa->topological_order(/* reversed = */ true))\
    \ {\n                    dp[u] += not nodes[u].cloned;\n                    const\
    \ int p = nodes[u].link;\n                    if (p >= 0) dp[p] += dp[u];\n  \
    \              }\n            }\n            long long count(const SequenceType\
    \ &t) const {\n                const int state = sa->transition(t);\n        \
    \        return state == -1 ? 0 : dp[state];\n            }\n        private:\n\
    \            const SuffixAutomatonBase *sa;\n            int n;\n            std::vector<long\
    \ long> dp;\n    };\n\n    SubstringCounter substring_counter() const & {\n  \
    \      return SubstringCounter { this };\n    }\n    SubstringCounter substring_counter()\
    \ const && = delete;\n\n    class SuffixLinkTree {\n        public:\n        \
    \    SuffixLinkTree(const SuffixAutomatonBase *sa) : sa(sa), g(sa->nodes.size())\
    \ {\n                const int n = g.size();\n                for (int i = 1;\
    \ i < n; ++i) g[sa->nodes[i].link].push_back(i);\n            }\n            int\
    \ size() const {\n                return g.size();\n            }\n          \
    \  const std::vector<int>& operator[](int i) const {\n                return g[i];\n\
    \            }\n        private:\n            const SuffixAutomatonBase *sa;\n\
    \            std::vector<std::vector<int>> g;\n    };\n\n    SuffixLinkTree suffix_link_tree()\
    \ const & {\n        return SuffixLinkTree(this);\n    }\n    SuffixLinkTree suffix_link_tree()\
    \ const && = delete;\n\n    class OccurrenceEnumerator {\n        public:\n  \
    \          OccurrenceEnumerator(const SuffixAutomatonBase *sa) : sa(sa), t(sa->suffix_link_tree())\
    \ {}\n\n            // returns vector of i s.t. S[i:i+|t|] = t\n            std::vector<int>\
    \ enumerate_all_occurrence(const SequenceType &pattern) const {\n            \
    \    const int state = sa->transition(pattern);\n                if (state ==\
    \ -1) return {};\n                const std::vector<Node> &nodes = sa->nodes;\n\
    \                const int l = pattern.size();\n                std::vector<int>\
    \ res;\n                auto dfs = [&](auto self, int u) -> void {\n         \
    \           if (not nodes[u].cloned) res.push_back(nodes[u].len - l);\n      \
    \              for (const int v : t[u]) self(self, v);\n                };\n \
    \               dfs(dfs, state);\n                return res;\n            }\n\
    \n        private:\n            const SuffixAutomatonBase *sa;\n            SuffixLinkTree\
    \ t;\n    };\n\n    OccurrenceEnumerator occurrence_enumerator() const & {\n \
    \       return OccurrenceEnumerator(this);\n    }\n    OccurrenceEnumerator occurrence_enumerator()\
    \ const && = delete;\n\n    class FirstOccurenceSearcher {\n        public:\n\
    \            FirstOccurenceSearcher(const SuffixAutomatonBase *sa) : sa(sa) {\n\
    \                const std::vector<Node> &nodes = sa->nodes;\n               \
    \ dp.resize(nodes.size(), std::numeric_limits<int>::max());\n                for\
    \ (const int u : sa->topological_order(/* reversed = */ true)) {\n           \
    \         if (not nodes[u].cloned) dp[u] = nodes[u].len;\n                   \
    \ const int p = nodes[u].link;\n                    if (p >= 0 and nodes[p].cloned)\
    \ dp[p] = std::min(dp[p], dp[u]);\n                }\n            }\n\n      \
    \      // returns min { i | S[i:i+|t|] = t }. if such i does not exist, returns\
    \ -1.\n            int first_occurrence(const SequenceType &t) const {\n     \
    \           const int state = sa->transition(t);\n                if (state ==\
    \ -1) return -1;\n                return dp[state] - t.size();\n            }\n\
    \n        private:\n            const SuffixAutomatonBase *sa;\n            std::vector<int>\
    \ dp;\n    };\n\n    FirstOccurenceSearcher first_occurence_searcher() const &\
    \ {\n        return FirstOccurenceSearcher(this);\n    }\n    FirstOccurenceSearcher\
    \ first_occurence_searcher() const && = delete;\n\n    // returns { start_s, start_t,\
    \ len } s.t. lcs = s[start_s: start_s+len] t[start_t: start_t+len]\n    std::tuple<int,\
    \ int, int> longest_common_substring(const SequenceType &t) const {\n        if\
    \ (t.size() == 0) return { 0, 0, 0 };\n        const Node *v = &nodes[0];\n  \
    \      int l = 0, max_len = 0, s_end_pos = 0, t_end_pos = 0;\n        for (int\
    \ i = 0; i < int(t.size()); ++i){\n            while (v->link != -1 and not v->nxt.count(t[i]))\
    \ {\n                v = &nodes[v->link];\n                l = v->len;\n     \
    \       }\n            auto it = v->nxt.find(t[i]);\n            if (it != v->nxt.end()){\n\
    \                v = &nodes[it->second];\n                l++;\n            }\n\
    \            if (l > max_len){\n                max_len = l;\n               \
    \ t_end_pos = i;\n                s_end_pos = v->index;\n            }\n     \
    \   }\n        if (max_len == 0) return { 0, 0, 0 };\n        return { s_end_pos\
    \ - max_len + 1, t_end_pos - max_len + 1, max_len };\n    }\n\n    std::vector<int>\
    \ topological_order(bool reversed = false) const {\n        const int n = nodes.size();\n\
    \        std::vector<int> in(n, 0);\n        for (const auto &node : nodes) {\n\
    \            for (const auto &p : node.nxt) ++in[p.second];\n        }\n     \
    \   std::deque<int> dq;\n        for (int i = 0; i < n; ++i) {\n            if\
    \ (in[i] == 0) dq.push_back(i);\n        }\n        std::vector<int> res;\n  \
    \      while (dq.size()) {\n            int u = dq.front();\n            dq.pop_front();\n\
    \            res.push_back(u);\n            for (const auto &p : nodes[u].nxt)\
    \ {\n                if (--in[p.second] == 0) dq.push_back(p.second);\n      \
    \      }\n        }\n        if (reversed) std::reverse(res.begin(), res.end());\n\
    \        assert(int(res.size()) == n);\n        return res;\n    }\n};\n\ntemplate\
    \ <typename T>\nstruct SuffixAutomaton : public SuffixAutomatonBase<T, std::vector<T>>\
    \ {\n    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;\n\
    \    using value_type = T;\n    using sequence_type = std::vector<T>;\n};\n\n\
    template <typename T>\nSuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;\n\
    \ntemplate <>\nstruct SuffixAutomaton<char> : public SuffixAutomatonBase<char,\
    \ std::string> {\n    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;\n\
    \    using value_type = char;\n    using sequence_type = std::string;\n};\n\n\
    SuffixAutomaton(std::string) -> SuffixAutomaton<char>;\n\n} // namespace suisen\n\
    \n\n#line 5 \"library/string/substring_set.hpp\"\n\nnamespace suisen {\n\n/**\n\
    \ * Constant set of all substrings\n */\ntemplate <typename T>\nclass SubstringSet\
    \ {\n    public:\n        using value_type = typename SuffixAutomaton<T>::sequence_type;\n\
    \        using size_type = long long;\n        using difference_type = size_type;\n\
    \n        // create empty set\n        SubstringSet() : SubstringSet(value_type{})\
    \ {}\n\n        // create set of all substrings in `s`\n        SubstringSet(const\
    \ value_type &s) {\n            build(s);\n        }\n\n        // build set of\
    \ all substrings in `s`\n        void build(const value_type &s) {\n         \
    \   sa = SuffixAutomaton(s);\n            dp.resize(sa.nodes.size(), size_type(1));\n\
    \            for (const int u : sa.topological_order(/* reversed = */true)) {\n\
    \                for (const auto &p : sa.nodes[u].nxt) dp[u] += dp[p.second];\n\
    \            }\n        }\n\n        size_type size() const {\n            return\
    \ dp[0];\n        }\n\n        bool contains(const value_type &t) const {\n  \
    \          return sa.accept(t);\n        }\n\n        // the k'th lexicographically\
    \ smallest substring, O(|return value|).\n        value_type operator[](size_type\
    \ k) const {\n            assert(0 <= k and k < dp[0]);\n            int cur =\
    \ 0;\n            value_type res;\n            while (k--) {\n               \
    \ for (const auto &[e, v] : sa.nodes[cur].nxt) {\n                    if (k <\
    \ dp[v]) {\n                        res.push_back(e);\n                      \
    \  cur = v;\n                        break;\n                    } else {\n  \
    \                      k -= dp[v];\n                    }\n                }\n\
    \            }\n            return res;\n        }\n        // the k'th lexicographically\
    \ smallest substring, O(|return value|).\n        value_type kth_element(size_type\
    \ k) const {\n            return (*this)[k];\n        }\n\n        // #{ s | s\
    \ < t, s is in this set }, O(|min(t, max_substr_len)|).\n        size_type count_lt(const\
    \ value_type &t) const {\n            size_type res = 0;\n            int cur\
    \ = 0;\n            for (const T& c : t) {\n                ++res;\n         \
    \       auto it_r = sa.nodes[cur].nxt.lower_bound(c);\n                for (auto\
    \ it_l = sa.nodes[cur].nxt.begin(); it_l != it_r; ++it_l) {\n                \
    \    res += dp[it_l->second];\n                }\n                if (it_r ==\
    \ sa.nodes[cur].nxt.end() or it_r->first != c) break;\n                cur = it_r->second;\n\
    \            }\n            return res;\n        }\n        // #{ s | s <= t,\
    \ s is in this set }, O(min(|t|, max_substr_len)).\n        size_type count_leq(const\
    \ value_type &t) const {\n            return count_lt(t) + contains(t);\n    \
    \    }\n        // #{ s | s > t, s is in this set }, O(min(|t|, max_substr_len)).\n\
    \        size_type count_gt(const value_type &t) const {\n            return size()\
    \ - count_leq(t);\n        }\n        // #{ s | s >= t, s is in this set }, O(min(|t|,\
    \ max_substr_len)).\n        size_type count_geq(const value_type &t) const {\n\
    \            return size() - count_lt(t);\n        }\n        // #{ s | l <= s\
    \ <= r, s is in this set }, O(min(|t|, max_substr_len)).\n        size_type count_range(const\
    \ value_type &l, const value_type &r) const {\n            return l >= r ? 0 :\
    \ count_lt(r) - count_lt(l);\n        }\n\n        // min { s | s >= t, s is in\
    \ this set }, O(|return value| + min(|t|, max_substr_len))\n        value_type\
    \ min_geq(const value_type &t) const {\n            return (*this)[count_lt(t)];\n\
    \        }\n        // min { s | s > t, s is in this set }, O(|return value| +\
    \ min(|t|, max_substr_len))\n        value_type min_gt(const value_type &t) const\
    \ {\n            return (*this)[count_leq(t)];\n        }\n        // max { s\
    \ | s < t, s is in this set }, O(|return value| + min(|t|, max_substr_len))\n\
    \        value_type max_lt(const value_type &t) const {\n            return (*this)[count_lt(t)\
    \ - 1];\n        }\n        // max { s | s <= t, s is in this set }, O(|return\
    \ value| + min(|t|, max_substr_len))\n        value_type max_leq(const value_type\
    \ &t) const {\n            return (*this)[count_leq(t) - 1];\n        }\n\n  \
    \      // iterator\n\n        // operator*: O(|return value|), other operations:\
    \ O(1).\n        class SubstringSetIterator {\n            public:\n         \
    \       SubstringSetIterator(const SubstringSet *st, size_type k) : st(st), k(k)\
    \ {}\n\n                value_type operator*() const { return st->kth_substring(k);\
    \ }\n\n                auto& operator=(const SubstringSetIterator& other) {\n\
    \                    st = other.st;\n                    k = other.k;\n      \
    \              return *this;\n                }\n\n                auto& operator++()\
    \ { ++k; return *this; }\n                auto& operator--() { --k; return *this;\
    \ }\n                auto& operator+=(difference_type d) { k += d; return *this;\
    \ }\n                auto& operator-=(difference_type d) { k -= d; return *this;\
    \ }\n\n                auto operator+(difference_type d) { return SubstringSetIterator\
    \ { st, k + d }; }\n                auto operator-(difference_type d) { return\
    \ SubstringSetIterator { st, k - d }; }\n\n                difference_type operator-(const\
    \ SubstringSetIterator &other) { return k - other.k; }\n\n                bool\
    \ operator==(const SubstringSetIterator& other) const { return k == other.k; }\n\
    \                bool operator!=(const SubstringSetIterator& other) const { return\
    \ k != other.k; }\n                bool operator< (const SubstringSetIterator&\
    \ other) const { return k <  other.k; }\n                bool operator<=(const\
    \ SubstringSetIterator& other) const { return k <= other.k; }\n              \
    \  bool operator> (const SubstringSetIterator& other) const { return k >  other.k;\
    \ }\n                bool operator>=(const SubstringSetIterator& other) const\
    \ { return k >= other.k; }\n\n            protected:\n                const SubstringSet\
    \ *st;\n                size_type k;\n        };\n\n        // operator*: O(|return\
    \ value|), other operations: O(1).\n        struct ReversedSubstringSetIterator\
    \ : public SubstringSetIterator {\n            using SubstringSetIterator::SubstringSetIterator;\n\
    \            value_type operator*() const { return this->st->kth_element(this->st->size()\
    \ - this->k - 1); }\n        };\n\n        using iterator = SubstringSetIterator;\n\
    \        using reverse_iterator = ReversedSubstringSetIterator;\n        using\
    \ const_iterator = iterator;\n        using const_reverse_iterator = reverse_iterator;\n\
    \n        auto begin()   const { return iterator { this, 0LL }; }\n        auto\
    \ end()     const { return iterator { this, size() }; }\n        auto cbegin()\
    \  const { return begin(); }\n        auto cend()    const { return end(); }\n\
    \        auto rbegin()  const { return reverse_iterator { this, 0LL }; }\n   \
    \     auto rend()    const { return reverse_iterator { this, size() }; }\n   \
    \     auto crbegin() const { return rbegin(); }\n        auto crend()   const\
    \ { return rend(); }\n\n        // O(|min(t, max_substr_len)|).\n        auto\
    \ lower_bound(const value_type &t) const {\n            return iterator { this,\
    \ count_lt(t) };\n        }\n        // O(|min(t, max_substr_len)|).\n       \
    \ auto upper_bound(const value_type &t) const {\n            return iterator {\
    \ this, count_leq(t) };\n        }\n\n        // O(|min(t, max_substr_len)|).\n\
    \        auto find(const value_type &t) const {\n            auto it = lower_bound(t);\n\
    \            if (it == end() or t != *it) return end();\n            return it;\n\
    \        }\n\n    private:\n        SuffixAutomaton<T> sa;\n        std::vector<size_type>\
    \ dp;\n};\n\ntemplate <typename T>\nSubstringSet(std::vector<T>) -> SubstringSet<T>;\n\
    \nSubstringSet(std::string) -> SubstringSet<char>;\n\n} // namespace suisen\n\n\
    \n\n#line 6 \"test/src/string/substring_set/arc097_a.test.cpp\"\nusing suisen::SubstringSet;\n\
    \nint main() {\n    std::string s;\n    int k;\n    std::cin >> s >> k;\n    std::cout\
    \ << SubstringSet(s)[k] << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc097/tasks/arc097_c\"\n\n\
    #include <iostream>\n\n#include \"library/string/substring_set.hpp\"\nusing suisen::SubstringSet;\n\
    \nint main() {\n    std::string s;\n    int k;\n    std::cin >> s >> k;\n    std::cout\
    \ << SubstringSet(s)[k] << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/string/substring_set.hpp
  - library/string/suffix_automaton.hpp
  isVerificationFile: true
  path: test/src/string/substring_set/arc097_a.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 21:46:01+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/string/substring_set/arc097_a.test.cpp
layout: document
redirect_from:
- /verify/test/src/string/substring_set/arc097_a.test.cpp
- /verify/test/src/string/substring_set/arc097_a.test.cpp.html
title: test/src/string/substring_set/arc097_a.test.cpp
---
