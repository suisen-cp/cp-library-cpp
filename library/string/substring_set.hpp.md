---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/string/suffix_automaton.hpp
    title: library/string/suffix_automaton.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/substring_set/arc097_a.test.cpp
    title: test/src/string/substring_set/arc097_a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/substring_set/number_of_substrings.test.cpp
    title: test/src/string/substring_set/number_of_substrings.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/string/substring_set.hpp\"\n\n\n\n#line 1 \"library/string/suffix_automaton.hpp\"\
    \n\n\n\n#include <cassert>\n#include <deque>\n#include <map>\n#include <string>\n\
    #include <vector>\n\nnamespace suisen {\n\n/**\n * reference : https://w.atwiki.jp/uwicoder/pages/2842.html\n\
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
    \n\n#line 5 \"library/string/substring_set.hpp\"\n\nnamespace suisen {\n\n/**\n\
    \ * Constant set of all substrings\n */\ntemplate <typename T>\nclass SubstringSet\
    \ {\n    public:\n        using value_type = typename SuffixAutomaton<T>::sequence_type;\n\
    \        using size_type = long long;\n        using difference_type = size_type;\n\
    \n        // create empty set\n        SubstringSet() : SubstringSet(value_type{})\
    \ {}\n\n        // create set of all substrings in `s`\n        SubstringSet(const\
    \ value_type &s) {\n            build(s);\n        }\n\n        // build set of\
    \ all substrings in `s`\n        void build(const value_type &s) {\n         \
    \   sa = SuffixAutomaton(s);\n            const int n = sa.nodes.size();\n   \
    \         dp.resize(n, size_type(1));\n            const std::vector<int> ord\
    \ = sa.topological_order();\n            for (int i = n - 1; i >= 0; --i) {\n\
    \                const int u = ord[i];\n                for (const auto &p : sa.nodes[u].nxt)\
    \ dp[u] += dp[p.second];\n            }\n        }\n\n        size_type size()\
    \ const {\n            return dp[0];\n        }\n\n        bool contains(const\
    \ value_type &t) const {\n            return sa.accept(t);\n        }\n\n    \
    \    // the k'th lexicographically smallest substring, O(|return value|).\n  \
    \      value_type operator[](size_type k) const {\n            assert(0 <= k and\
    \ k < dp[0]);\n            int cur = 0;\n            value_type res;\n       \
    \     while (k--) {\n                for (const auto &[e, v] : sa.nodes[cur].nxt)\
    \ {\n                    if (k < dp[v]) {\n                        res.push_back(e);\n\
    \                        cur = v;\n                        break;\n          \
    \          } else {\n                        k -= dp[v];\n                   \
    \ }\n                }\n            }\n            return res;\n        }\n  \
    \      // the k'th lexicographically smallest substring, O(|return value|).\n\
    \        value_type kth_element(size_type k) const {\n            return (*this)[k];\n\
    \        }\n\n        // #{ s | s < t, s is in this set }, O(|min(t, max_substr_len)|).\n\
    \        size_type count_lt(const value_type &t) const {\n            size_type\
    \ res = 0;\n            int cur = 0;\n            for (const T& c : t) {\n   \
    \             ++res;\n                auto it_r = sa.nodes[cur].nxt.lower_bound(c);\n\
    \                for (auto it_l = sa.nodes[cur].nxt.begin(); it_l != it_r; ++it_l)\
    \ {\n                    res += dp[it_l->second];\n                }\n       \
    \         if (it_r == sa.nodes[cur].nxt.end() or it_r->first != c) break;\n  \
    \              cur = it_r->second;\n            }\n            return res;\n \
    \       }\n        // #{ s | s <= t, s is in this set }, O(min(|t|, max_substr_len)).\n\
    \        size_type count_leq(const value_type &t) const {\n            return\
    \ count_lt(t) + contains(t);\n        }\n        // #{ s | s > t, s is in this\
    \ set }, O(min(|t|, max_substr_len)).\n        size_type count_gt(const value_type\
    \ &t) const {\n            return size() - count_leq(t);\n        }\n        //\
    \ #{ s | s >= t, s is in this set }, O(min(|t|, max_substr_len)).\n        size_type\
    \ count_geq(const value_type &t) const {\n            return size() - count_lt(t);\n\
    \        }\n        // #{ s | l <= s <= r, s is in this set }, O(min(|t|, max_substr_len)).\n\
    \        size_type count_range(const value_type &l, const value_type &r) const\
    \ {\n            return l >= r ? 0 : count_lt(r) - count_lt(l);\n        }\n\n\
    \        // min { s | s >= t, s is in this set }, O(|return value| + min(|t|,\
    \ max_substr_len))\n        value_type min_geq(const value_type &t) const {\n\
    \            return (*this)[count_lt(t)];\n        }\n        // min { s | s >\
    \ t, s is in this set }, O(|return value| + min(|t|, max_substr_len))\n      \
    \  value_type min_gt(const value_type &t) const {\n            return (*this)[count_leq(t)];\n\
    \        }\n        // max { s | s < t, s is in this set }, O(|return value| +\
    \ min(|t|, max_substr_len))\n        value_type max_lt(const value_type &t) const\
    \ {\n            return (*this)[count_lt(t) - 1];\n        }\n        // max {\
    \ s | s <= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))\n\
    \        value_type max_leq(const value_type &t) const {\n            return (*this)[count_leq(t)\
    \ - 1];\n        }\n\n        // iterator\n\n        // operator*: O(|return value|),\
    \ other operations: O(1).\n        class SubstringSetIterator {\n            public:\n\
    \                SubstringSetIterator(const SubstringSet *st, size_type k) : st(st),\
    \ k(k) {}\n\n                value_type operator*() const { return st->kth_substring(k);\
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
    \n\n"
  code: "#ifndef SUISEN_SUBSTRING_SET\n#define SUISEN_SUBSTRING_SET\n\n#include \"\
    library/string/suffix_automaton.hpp\"\n\nnamespace suisen {\n\n/**\n * Constant\
    \ set of all substrings\n */\ntemplate <typename T>\nclass SubstringSet {\n  \
    \  public:\n        using value_type = typename SuffixAutomaton<T>::sequence_type;\n\
    \        using size_type = long long;\n        using difference_type = size_type;\n\
    \n        // create empty set\n        SubstringSet() : SubstringSet(value_type{})\
    \ {}\n\n        // create set of all substrings in `s`\n        SubstringSet(const\
    \ value_type &s) {\n            build(s);\n        }\n\n        // build set of\
    \ all substrings in `s`\n        void build(const value_type &s) {\n         \
    \   sa = SuffixAutomaton(s);\n            const int n = sa.nodes.size();\n   \
    \         dp.resize(n, size_type(1));\n            const std::vector<int> ord\
    \ = sa.topological_order();\n            for (int i = n - 1; i >= 0; --i) {\n\
    \                const int u = ord[i];\n                for (const auto &p : sa.nodes[u].nxt)\
    \ dp[u] += dp[p.second];\n            }\n        }\n\n        size_type size()\
    \ const {\n            return dp[0];\n        }\n\n        bool contains(const\
    \ value_type &t) const {\n            return sa.accept(t);\n        }\n\n    \
    \    // the k'th lexicographically smallest substring, O(|return value|).\n  \
    \      value_type operator[](size_type k) const {\n            assert(0 <= k and\
    \ k < dp[0]);\n            int cur = 0;\n            value_type res;\n       \
    \     while (k--) {\n                for (const auto &[e, v] : sa.nodes[cur].nxt)\
    \ {\n                    if (k < dp[v]) {\n                        res.push_back(e);\n\
    \                        cur = v;\n                        break;\n          \
    \          } else {\n                        k -= dp[v];\n                   \
    \ }\n                }\n            }\n            return res;\n        }\n  \
    \      // the k'th lexicographically smallest substring, O(|return value|).\n\
    \        value_type kth_element(size_type k) const {\n            return (*this)[k];\n\
    \        }\n\n        // #{ s | s < t, s is in this set }, O(|min(t, max_substr_len)|).\n\
    \        size_type count_lt(const value_type &t) const {\n            size_type\
    \ res = 0;\n            int cur = 0;\n            for (const T& c : t) {\n   \
    \             ++res;\n                auto it_r = sa.nodes[cur].nxt.lower_bound(c);\n\
    \                for (auto it_l = sa.nodes[cur].nxt.begin(); it_l != it_r; ++it_l)\
    \ {\n                    res += dp[it_l->second];\n                }\n       \
    \         if (it_r == sa.nodes[cur].nxt.end() or it_r->first != c) break;\n  \
    \              cur = it_r->second;\n            }\n            return res;\n \
    \       }\n        // #{ s | s <= t, s is in this set }, O(min(|t|, max_substr_len)).\n\
    \        size_type count_leq(const value_type &t) const {\n            return\
    \ count_lt(t) + contains(t);\n        }\n        // #{ s | s > t, s is in this\
    \ set }, O(min(|t|, max_substr_len)).\n        size_type count_gt(const value_type\
    \ &t) const {\n            return size() - count_leq(t);\n        }\n        //\
    \ #{ s | s >= t, s is in this set }, O(min(|t|, max_substr_len)).\n        size_type\
    \ count_geq(const value_type &t) const {\n            return size() - count_lt(t);\n\
    \        }\n        // #{ s | l <= s <= r, s is in this set }, O(min(|t|, max_substr_len)).\n\
    \        size_type count_range(const value_type &l, const value_type &r) const\
    \ {\n            return l >= r ? 0 : count_lt(r) - count_lt(l);\n        }\n\n\
    \        // min { s | s >= t, s is in this set }, O(|return value| + min(|t|,\
    \ max_substr_len))\n        value_type min_geq(const value_type &t) const {\n\
    \            return (*this)[count_lt(t)];\n        }\n        // min { s | s >\
    \ t, s is in this set }, O(|return value| + min(|t|, max_substr_len))\n      \
    \  value_type min_gt(const value_type &t) const {\n            return (*this)[count_leq(t)];\n\
    \        }\n        // max { s | s < t, s is in this set }, O(|return value| +\
    \ min(|t|, max_substr_len))\n        value_type max_lt(const value_type &t) const\
    \ {\n            return (*this)[count_lt(t) - 1];\n        }\n        // max {\
    \ s | s <= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))\n\
    \        value_type max_leq(const value_type &t) const {\n            return (*this)[count_leq(t)\
    \ - 1];\n        }\n\n        // iterator\n\n        // operator*: O(|return value|),\
    \ other operations: O(1).\n        class SubstringSetIterator {\n            public:\n\
    \                SubstringSetIterator(const SubstringSet *st, size_type k) : st(st),\
    \ k(k) {}\n\n                value_type operator*() const { return st->kth_substring(k);\
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
    \n#endif // SUISEN_SUBSTRING_SET\n"
  dependsOn:
  - library/string/suffix_automaton.hpp
  isVerificationFile: false
  path: library/string/substring_set.hpp
  requiredBy: []
  timestamp: '2021-09-08 17:15:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/substring_set/number_of_substrings.test.cpp
  - test/src/string/substring_set/arc097_a.test.cpp
documentation_of: library/string/substring_set.hpp
layout: document
redirect_from:
- /library/library/string/substring_set.hpp
- /library/library/string/substring_set.hpp.html
title: library/string/substring_set.hpp
---
