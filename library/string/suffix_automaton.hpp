#ifndef SUISEN_SUFFIX_AUTOMATON
#define SUISEN_SUFFIX_AUTOMATON

#include <algorithm>
#include <cassert>
#include <deque>
#include <map>
#include <string>
#include <vector>

namespace suisen {

/**
 * reference
 * - https://w.atwiki.jp/uwicoder/pages/2842.html
 * - https://cp-algorithms.com/string/suffix-automaton.html
 */
template <typename T, typename SequenceType>
struct SuffixAutomatonBase {
    struct Node {
        std::map<T, int> nxt;
        int link, len;
        bool cloned;
    };

    std::vector<Node> nodes;
    int last;

    SuffixAutomatonBase() {
        nodes.push_back({ {}, -1, 0, false });
        last = 0;
    }
    SuffixAutomatonBase(const SequenceType &s) : SuffixAutomatonBase() {
        for (const T &c : s) append(c);
    }

    void append(const T &c) {
        const int new_node = nodes.size();
        nodes.push_back({ {}, -1, nodes[last].len + 1, false });
        int p = last;
        for (; p != -1 and not nodes[p].nxt.count(c); p = nodes[p].link) nodes[p].nxt[c] = new_node;
        const int q = p == -1 ? 0 : nodes[p].nxt[c];
        if (p == -1 or nodes[p].len + 1 == nodes[q].len) {
            nodes[new_node].link = q;
        } else {
            const int clone_node = nodes.size();
            nodes.push_back({ nodes[q].nxt, nodes[q].link, nodes[p].len + 1, true });
            for (; p != -1 and nodes[p].nxt[c] == q; p = nodes[p].link) nodes[p].nxt[c] = clone_node;
            nodes[new_node].link = nodes[q].link = clone_node;
        }
        last = new_node;
    }
    SuffixAutomatonBase& operator+=(const T &c) {
        append(c);
        return *this;
    }

    int transition(const SequenceType &t, int invalid_state = -1) const {
        int cur = 0;
        for (const auto &c : t) {
            auto it = nodes[cur].nxt.find(c);
            if (it == nodes[cur].nxt.end()) return invalid_state;
            cur = it->second;
        }
        return cur;
    }

    bool accept(const SequenceType &t) const {
        return transition(t) != -1;
    }

    class SubstringCounter {
        public:
            SubstringCounter(const SuffixAutomatonBase *sa) : sa(sa), n(sa->nodes.size()), dp(n, 0) {
                const std::vector<Node> &nodes = sa->nodes;
                for (const int u : sa->topological_order(/* reversed = */ true)) {
                    dp[u] += not nodes[u].cloned;
                    const int p = nodes[u].link;
                    if (p >= 0) dp[p] += dp[u];
                }
            }
            long long count(const SequenceType &t) const {
                const int state = sa->transition(t);
                return state == -1 ? 0 : dp[state];
            }
        private:
            const SuffixAutomatonBase *sa;
            int n;
            std::vector<long long> dp;
    };

    SubstringCounter substring_counter() const & {
        return SubstringCounter { this };
    }
    SubstringCounter substring_counter() const && = delete;

    class SuffixLinkTree {
        public:
            SuffixLinkTree(const SuffixAutomatonBase *sa) : sa(sa), g(sa->nodes.size()) {
                const int n = g.size();
                for (int i = 1; i < n; ++i) g[sa->nodes[i].link].push_back(i);
            }
            const int size() const {
                return g.size();
            }
            const std::vector<int>& operator[](int i) const {
                return g[i];
            }
        private:
            const SuffixAutomatonBase *sa;
            std::vector<std::vector<int>> g;
    };

    SuffixLinkTree suffix_link_tree() const & {
        return SuffixLinkTree(this);
    }
    SuffixLinkTree suffix_link_tree() const && = delete;

    class OccurrenceEnumerator {
        public:
            OccurrenceEnumerator(const SuffixAutomatonBase *sa) : sa(sa), t(sa->suffix_link_tree()) {}

            // returns vector of i s.t. S[i:i+|t|] = t
            std::vector<int> enumerate_all_occurrence(const SequenceType &pattern) const {
                const int state = sa->transition(pattern);
                if (state == -1) return {};
                const std::vector<Node> &nodes = sa->nodes;
                const int l = pattern.size();
                std::vector<int> res;
                auto dfs = [&](auto self, int u) -> void {
                    if (not nodes[u].cloned) res.push_back(nodes[u].len - l);
                    for (const int v : t[u]) self(self, v);
                };
                dfs(dfs, state);
                return res;
            }

        private:
            const SuffixAutomatonBase *sa;
            SuffixLinkTree t;
    };

    OccurrenceEnumerator occurrence_enumerator() const & {
        return OccurrenceEnumerator(this);
    }
    OccurrenceEnumerator occurrence_enumerator() const && = delete;

    class FirstOccurenceSearcher {
        public:
            FirstOccurenceSearcher(const SuffixAutomatonBase *sa) : sa(sa) {
                const std::vector<Node> &nodes = sa->nodes;
                dp.resize(nodes.size(), std::numeric_limits<int>::max());
                for (const int u : sa->topological_order(/* reversed = */ true)) {
                    if (not nodes[u].cloned) dp[u] = nodes[u].len;
                    const int p = nodes[u].link;
                    if (p >= 0 and nodes[p].cloned) dp[p] = std::min(dp[p], dp[u]);
                }
            }

            // returns min { i | S[i:i+|t|] = t }. if such i does not exist, returns -1.
            int first_occurrence(const SequenceType &t) const {
                const int state = sa->transition(t);
                if (state == -1) return -1;
                return dp[state] - t.size();
            }

        private:
            const SuffixAutomatonBase *sa;
            std::vector<int> dp;
    };

    FirstOccurenceSearcher first_occurence_searcher() const & {
        return FirstOccurenceSearcher(this);
    }
    FirstOccurenceSearcher first_occurence_searcher() const && = delete;

    // returns { from, len } s.t. lcs = t[from:from+len]
    std::pair<int, int> longest_common_substring(const SequenceType &t) const {
        if (t.size() == 0) return { 0, 0 };
        const Node *v = &nodes[0];
        int l = 0, best = 0, best_pos = 0;
        for (int i = 0; i < int(t.size()); ++i){
            while (v->link != -1 and not v->nxt.count(t[i])) {
                v = &nodes[v->link];
                l = v->len;
            }
            auto it = v->nxt.find(t[i]);
            if (it != v->nxt.end()){
                v = &nodes[it->second];
                l++;
            }
            if (l > best){
                best = l;
                best_pos = i;
            }
        }
        return { best_pos - best + 1, best };
    }

    std::vector<int> topological_order(bool reversed = false) const {
        const int n = nodes.size();
        std::vector<int> in(n, 0);
        for (const auto &node : nodes) {
            for (const auto &p : node.nxt) ++in[p.second];
        }
        std::deque<int> dq;
        for (int i = 0; i < n; ++i) {
            if (in[i] == 0) dq.push_back(i);
        }
        std::vector<int> res;
        while (dq.size()) {
            int u = dq.front();
            dq.pop_front();
            res.push_back(u);
            for (const auto &p : nodes[u].nxt) {
                if (--in[p.second] == 0) dq.push_back(p.second);
            }
        }
        if (reversed) std::reverse(res.begin(), res.end());
        assert(int(res.size()) == n);
        return res;
    }
};

template <typename T>
struct SuffixAutomaton : public SuffixAutomatonBase<T, std::vector<T>> {
    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;
    using value_type = T;
    using sequence_type = std::vector<T>;
};

template <typename T>
SuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;

template <>
struct SuffixAutomaton<char> : public SuffixAutomatonBase<char, std::string> {
    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;
    using value_type = char;
    using sequence_type = std::string;
};

SuffixAutomaton(std::string) -> SuffixAutomaton<char>;

} // namespace suisen

#endif // SUISEN_SUFFIX_AUTOMATON
