#ifndef SUISEN_SUBSTRING_SET
#define SUISEN_SUBSTRING_SET

#include "library/string/suffix_automaton.hpp"

namespace suisen {

/**
 * Constant set of all substrings
 */
template <typename T>
class SubstringSet {
    public:
        using value_type = typename SuffixAutomaton<T>::sequence_type;
        using size_type = long long;
        using difference_type = size_type;

        // create empty set
        SubstringSet() : SubstringSet(value_type{}) {}

        // create set of all substrings in `s`
        SubstringSet(const value_type &s) {
            build(s);
        }

        // build set of all substrings in `s`
        void build(const value_type &s) {
            sa = SuffixAutomaton(s);
            const int n = sa.nodes.size();
            dp.resize(n, size_type(1));
            const std::vector<int> ord = sa.topological_order();
            for (int i = n - 1; i >= 0; --i) {
                const int u = ord[i];
                for (const auto &p : sa.nodes[u].nxt) dp[u] += dp[p.second];
            }
        }

        size_type size() const {
            return dp[0];
        }

        bool contains(const value_type &t) const {
            return sa.accept(t);
        }

        // the k'th lexicographically smallest substring, O(|return value|).
        value_type operator[](size_type k) const {
            assert(0 <= k and k < dp[0]);
            int cur = 0;
            value_type res;
            while (k--) {
                for (const auto &[e, v] : sa.nodes[cur].nxt) {
                    if (k < dp[v]) {
                        res.push_back(e);
                        cur = v;
                        break;
                    } else {
                        k -= dp[v];
                    }
                }
            }
            return res;
        }
        // the k'th lexicographically smallest substring, O(|return value|).
        value_type kth_element(size_type k) const {
            return (*this)[k];
        }

        // #{ s | s < t, s is in this set }, O(|min(t, max_substr_len)|).
        size_type count_lt(const value_type &t) const {
            size_type res = 0;
            int cur = 0;
            for (const T& c : t) {
                ++res;
                auto it_r = sa.nodes[cur].nxt.lower_bound(c);
                for (auto it_l = sa.nodes[cur].nxt.begin(); it_l != it_r; ++it_l) {
                    res += dp[it_l->second];
                }
                if (it_r == sa.nodes[cur].nxt.end() or it_r->first != c) break;
                cur = it_r->second;
            }
            return res;
        }
        // #{ s | s <= t, s is in this set }, O(min(|t|, max_substr_len)).
        size_type count_leq(const value_type &t) const {
            return count_lt(t) + contains(t);
        }
        // #{ s | s > t, s is in this set }, O(min(|t|, max_substr_len)).
        size_type count_gt(const value_type &t) const {
            return size() - count_leq(t);
        }
        // #{ s | s >= t, s is in this set }, O(min(|t|, max_substr_len)).
        size_type count_geq(const value_type &t) const {
            return size() - count_lt(t);
        }
        // #{ s | l <= s <= r, s is in this set }, O(min(|t|, max_substr_len)).
        size_type count_range(const value_type &l, const value_type &r) const {
            return l >= r ? 0 : count_lt(r) - count_lt(l);
        }

        // min { s | s >= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
        value_type min_geq(const value_type &t) const {
            return (*this)[count_lt(t)];
        }
        // min { s | s > t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
        value_type min_gt(const value_type &t) const {
            return (*this)[count_leq(t)];
        }
        // max { s | s < t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
        value_type max_lt(const value_type &t) const {
            return (*this)[count_lt(t) - 1];
        }
        // max { s | s <= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
        value_type max_leq(const value_type &t) const {
            return (*this)[count_leq(t) - 1];
        }

        // iterator

        // operator*: O(|return value|), other operations: O(1).
        class SubstringSetIterator {
            public:
                SubstringSetIterator(const SubstringSet *st, size_type k) : st(st), k(k) {}

                value_type operator*() const { return st->kth_substring(k); }

                auto& operator=(const SubstringSetIterator& other) {
                    st = other.st;
                    k = other.k;
                    return *this;
                }

                auto& operator++() { ++k; return *this; }
                auto& operator--() { --k; return *this; }
                auto& operator+=(difference_type d) { k += d; return *this; }
                auto& operator-=(difference_type d) { k -= d; return *this; }

                auto operator+(difference_type d) { return SubstringSetIterator { st, k + d }; }
                auto operator-(difference_type d) { return SubstringSetIterator { st, k - d }; }

                difference_type operator-(const SubstringSetIterator &other) { return k - other.k; }

                bool operator==(const SubstringSetIterator& other) const { return k == other.k; }
                bool operator!=(const SubstringSetIterator& other) const { return k != other.k; }
                bool operator< (const SubstringSetIterator& other) const { return k <  other.k; }
                bool operator<=(const SubstringSetIterator& other) const { return k <= other.k; }
                bool operator> (const SubstringSetIterator& other) const { return k >  other.k; }
                bool operator>=(const SubstringSetIterator& other) const { return k >= other.k; }

            protected:
                const SubstringSet *st;
                size_type k;
        };

        // operator*: O(|return value|), other operations: O(1).
        struct ReversedSubstringSetIterator : public SubstringSetIterator {
            using SubstringSetIterator::SubstringSetIterator;
            value_type operator*() const { return this->st->kth_element(this->st->size() - this->k - 1); }
        };

        using iterator = SubstringSetIterator;
        using reverse_iterator = ReversedSubstringSetIterator;
        using const_iterator = iterator;
        using const_reverse_iterator = reverse_iterator;

        auto begin()   const { return iterator { this, 0LL }; }
        auto end()     const { return iterator { this, size() }; }
        auto cbegin()  const { return begin(); }
        auto cend()    const { return end(); }
        auto rbegin()  const { return reverse_iterator { this, 0LL }; }
        auto rend()    const { return reverse_iterator { this, size() }; }
        auto crbegin() const { return rbegin(); }
        auto crend()   const { return rend(); }

        // O(|min(t, max_substr_len)|).
        auto lower_bound(const value_type &t) const {
            return iterator { this, count_lt(t) };
        }
        // O(|min(t, max_substr_len)|).
        auto upper_bound(const value_type &t) const {
            return iterator { this, count_leq(t) };
        }

        // O(|min(t, max_substr_len)|).
        auto find(const value_type &t) const {
            auto it = lower_bound(t);
            if (it == end() or t != *it) return end();
            return it;
        }

    private:
        SuffixAutomaton<T> sa;
        std::vector<size_type> dp;
};

template <typename T>
SubstringSet(std::vector<T>) -> SubstringSet<T>;

SubstringSet(std::string) -> SubstringSet<char>;

} // namespace suisen


#endif // SUISEN_SUBSTRING_SET
