#ifndef SUISEN_SUFFIX_AUTOMATON
#define SUISEN_SUFFIX_AUTOMATON

#include <cassert>
#include <deque>
#include <map>
#include <string>
#include <vector>

namespace suisen {

/**
 * reference : https://w.atwiki.jp/uwicoder/pages/2842.html
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

    bool accept(const SequenceType &t) const {
        int cur = 0;
        for (const auto &c : t) {
            auto it = nodes[cur].nxt.find(c);
            if (it == nodes[cur].nxt.end()) return false;
            cur = it->second;
        }
        return true;
    }

    class SubstringCounter {
        public:
            SubstringCounter(const SuffixAutomatonBase *sa, std::vector<long long> &&dp) : sa(sa), dp(std::move(dp)) {}

            long long count(const SequenceType &t) const {
                int cur = 0;
                for (const auto &c : t) {
                    auto it = sa->nodes[cur].nxt.find(c);
                    if (it == sa->nodes[cur].nxt.end()) return 0;
                    cur = it->second;
                }
                return dp[cur];
            }

        private:
            const SuffixAutomatonBase *sa;
            const std::vector<long long> dp;
    };

    SubstringCounter substring_counter() const & {
        const int n = nodes.size();
        const std::vector<int> ord = topological_order();
        std::vector<long long> dp(n, 0);
        for (int i = n - 1; i > 0; --i) {
            const int u = ord[i];
            if (not nodes[u].cloned) ++dp[u];
            dp[nodes[u].link] += dp[u];
        }
        return SubstringCounter { this, std::move(dp) };
    }
    SubstringCounter substring_counter() const && = delete;

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

    std::vector<int> topological_order() const {
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
