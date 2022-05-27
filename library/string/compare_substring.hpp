#ifndef SUISEN_COMPARE_SUBSTRING
#define SUISEN_COMPARE_SUBSTRING

#include <atcoder/segtree>
#include <atcoder/string>

#include "library/datastructure/sparse_table.hpp"

namespace suisen {
    namespace internal::compare_substring {
        constexpr int op(int x, int y) { return std::min(x, y); }
        constexpr int e() { return std::numeric_limits<int>::max(); }
    }
    namespace compare_substring_rmq {
        using SegmentTreeRmQ = atcoder::segtree<int, internal::compare_substring::op, internal::compare_substring::e>;
        using SparseTableRmQ = SparseTable<int, internal::compare_substring::op, internal::compare_substring::e>;
    }
    template <typename RmQ = compare_substring_rmq::SparseTableRmQ>
    struct CompareSubstring {
        CompareSubstring() = default;
        CompareSubstring(const std::vector<int> &sa, const std::vector<int> &lcp) : _n(sa.size()), _sa_inv(_n), _lcp_min(lcp) {
            for (int i = 0; i < _n; ++i) _sa_inv[sa[i]] = i;
        }
        template <typename T>
        CompareSubstring(const std::vector<T> &s) : CompareSubstring(s, atcoder::suffix_array(s), DUMMY_PARAMETER) {}
        template <typename T>
        CompareSubstring(const std::vector<T> &s, const T& upper) : CompareSubstring(s, atcoder::suffix_array(s, upper), DUMMY_PARAMETER) {}
        CompareSubstring(const std::string &s) : CompareSubstring(s, atcoder::suffix_array(s), DUMMY_PARAMETER) {}

        int operator()(int l1, int r1, int l2, int r2) const {
            assert(0 <= l1 and l1 <= r1 and r1 <= _n);
            assert(0 <= l2 and l2 <= r2 and r2 <= _n);
            if (l1 == r1) return -(l2 != r2);
            if (l2 == r2) return l1 != r1;
            const int i1 = _sa_inv[l1], i2 = _sa_inv[l2];
            if (i1 > i2) return -(*this)(l2, r2, l1, r1);
            const int w1 = r1 - l1, w2 = r2 - l2;
            const int len = std::min(std::min(w1, w2), _lcp_min(i1, i2));
            return len >= w1 and len >= w2 ? 0 : len >= w1 ? -1 : len >= w2 ? 1 : _sa_inv[l1 + len] < _sa_inv[l2 + len] ? -1 : 1;
        }
        int compare(int l1, int r1, int l2, int r2) const {
            return (*this)(l1, r1, l2, r2);
        }

        struct Substring {
            int l, r;
            Substring() = default;
            Substring(int l, int r, CompareSubstring<RmQ> const * ptr) : l(l), r(r), _ptr(ptr) {}

            int size() const { return r - l; }

            int compare(const Substring &rhs) const {
                assert(rhs._ptr == _ptr);
                return _ptr->compare(l, r, rhs.l, rhs.r);
            }
            bool operator==(const Substring &rhs) const { return compare(rhs) == 0; }
            bool operator!=(const Substring &rhs) const { return compare(rhs) != 0; }
            bool operator< (const Substring &rhs) const { return compare(rhs) <  0; }
            bool operator<=(const Substring &rhs) const { return compare(rhs) <= 0; }
            bool operator> (const Substring &rhs) const { return compare(rhs) >  0; }
            bool operator>=(const Substring &rhs) const { return compare(rhs) >= 0; }
        private:
            CompareSubstring<RmQ> const * _ptr;
        };

        Substring substr(int l, int r) const {
            return Substring(l, r, this);
        }
    private:
        static constexpr bool DUMMY_PARAMETER{};
        int _n;
        std::vector<int> _sa_inv;
        RmQ _lcp_min;

        template <typename Container>
        CompareSubstring(const Container &s, const std::vector<int> &sa, bool) : CompareSubstring(sa, atcoder::lcp_array(s, sa)) {}
    };
} // namespace suisen

#endif // SUISEN_COMPARE_SUBSTRING
