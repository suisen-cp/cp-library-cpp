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
template <typename T, typename Container>
class SuffixAutomatonBase {
    struct Node {
        std::map<T, int> nxt;
        int link, len;
        bool cloned;
    };

    public:
        SuffixAutomatonBase() {
            nodes.push_back({ {}, -1, 0, false });
            last = 0;
        }
        SuffixAutomatonBase(const Container &s) : SuffixAutomatonBase() {
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

        long long number_of_substrings() const {
            return substring_set().size();
        }

        bool accept(const Container &t) const {
            Node &cur = nodes[0];
            for (const auto &c : t) {
                auto it = cur.nxt.find(c);
                if (it == cur.nxt.end()) return false;
                cur = nodes[it->second];
            }
            return true;
        }

        class SubstringCounter {
            public:
                SubstringCounter(const SuffixAutomatonBase &sa, std::vector<long long> &&dp) : sa_(sa), dp_(std::move(dp)) {}

                long long count(const Container &t) const {
                    int cur = 0;
                    for (const auto &c : t) {
                        auto it = sa_.nodes[cur].nxt.find(c);
                        if (it == sa_.nodes[cur].nxt.end()) return 0;
                        cur = it->second;
                    }
                    return dp_[cur];
                }

            private:
                const SuffixAutomatonBase &sa_;
                const std::vector<long long> dp_;
        };

        SubstringCounter substring_counter() const {
            const int n = nodes.size();
            const std::vector<int> ord = topological_order();
            std::vector<long long> dp(n, 0);
            for (int i = n - 1; i > 0; --i) {
                const int u = ord[i];
                if (not nodes[u].cloned) ++dp[u];
                dp[nodes[u].link] += dp[u];
            }
            return SubstringCounter { *this, std::move(dp) };
        }

        class SubstringSet {
            public:
                SubstringSet(const SuffixAutomatonBase &sa, std::vector<long long> &&dp) : sa_(sa), dp_(std::move(dp)) {}

                long long size() const {
                    return dp_[0];
                }

                bool contains(const Container &t) const {
                    return sa_.accept(t);
                }

                Container operator[](unsigned long long k) const {
                    assert(k < dp_[0]);
                    int cur = 0;
                    Container res;
                    while (k--) {
                        for (const auto &[e, v] : sa_.nodes[cur].nxt) {
                            if (k < dp_[v]) {
                                res.push_back(e);
                                cur = v;
                                break;
                            } else {
                                k -= dp_[v];
                            }
                        }
                    }
                    return res;
                }

                Container kth_substring(unsigned long long k) const {
                    return (*this)[k];
                }

            private:
                const SuffixAutomatonBase &sa_;
                const std::vector<long long> dp_;
        };

        SubstringSet substring_set() const {
            const int n = nodes.size();
            const std::vector<int> ord = topological_order();
            std::vector<long long> dp(n, 1);
            for (int i = n - 1; i >= 0; --i) {
                const int u = ord[i];
                for (const auto &[_, v] : nodes[u].nxt) dp[u] += dp[v];
            }
            return SubstringSet { *this, std::move(dp) };
        }

        // returns { from, len } s.t. lcs = t[from:from+len]
        std::pair<int, int> longest_common_substring(const Container &t) const {
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

    private:
        std::vector<Node> nodes;
        int last;

        std::vector<int> topological_order() const {
            const int n = nodes.size();
            std::vector<int> in(n, 0);
            for (const auto &node : nodes) {
                for (const auto &[_, v] : node.nxt) ++in[v];
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
                for (const auto &[_, v] : nodes[u].nxt) {
                    if (--in[v] == 0) dq.push_back(v);
                }
            }
            assert(int(res.size()) == n);
            return res;
        }
};

template <typename T>
struct SuffixAutomaton : public SuffixAutomatonBase<T, std::vector<T>> {
    using SuffixAutomatonBase<T, std::vector<T>>::SuffixAutomatonBase;
};

template <>
struct SuffixAutomaton<char> : public SuffixAutomatonBase<char, std::string> {
    using SuffixAutomatonBase<char, std::string>::SuffixAutomatonBase;
};

template <typename T>
SuffixAutomaton(std::vector<T>) -> SuffixAutomaton<T>;
SuffixAutomaton(std::string) -> SuffixAutomaton<char>;

} // namespace suisen

#endif // SUISEN_SUFFIX_AUTOMATON
