#ifndef SUISEN_FENWICK_TREE_SET
#define SUISEN_FENWICK_TREE_SET

#include <array>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

namespace suisen {
    struct fenwick_tree_set {
    private:
        template <typename T>
        struct is_container {
            template <typename T2>
            static auto test(T2 t) -> decltype(++t.begin() != t.end(), *t.begin(), std::true_type{});
            static std::false_type test(...);
        public:
            static constexpr bool value = decltype(test(std::declval<T>()))::value;
        };
        static constexpr int WORD = 64, MASK_WORD = 63, LOG_WORD = 6;
        static constexpr int SEARCH_WIDTH = 1;
    public:
        fenwick_tree_set() : fenwick_tree_set(0) {}
        // Construct (an empty / a full) set and set the universe as {0,1,...,n-1}
        explicit fenwick_tree_set(int n, bool fullset = false): _n(n), _wn(std::max((_n + (WORD - 1)) >> LOG_WORD, 1)), _lg(top_setbit(_wn)), _siz(0), _d(_wn + 1), _bs(_wn) {
            if (fullset) {
                std::vector<int> values(n);
                std::iota(values.begin(), values.end(), 0);
                construct_from_values(values);
            }
        }
        // Construct a set containing the values in `values`.
        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        fenwick_tree_set(int n, const Container &values): fenwick_tree_set(n) {
            construct_from_values(values);
        }
        // Construct a set containing the values `i` such that `seq01[i] == 1` (or `one` you give).
        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        fenwick_tree_set(const Container &seq01, typename Container::value_type one = 1): fenwick_tree_set(seq01.size()) {
            std::vector<int> values;
            for (int i = 0; i < _n; ++i) if (seq01[i] == one) values.push_back(i);
            construct_from_values(values);
        }

        // O(1).
        // Number of elements.
        int size() const { return _siz; }

        // O(1).
        // Check if `v` is contained. `v` may be out of range.
        bool contains(int v) const {
            if (not (0 <= v and v < _n)) return false;
            const auto [t, u] = index(v);
            return (_bs[t] >> u) & 1;
        }
        // O(log n) if `v` is not a member, O(1) otherwise.
        // Insert `v` if not contained. Raise an assertion error if `v` is out of range.
        // Return `true` if `v` is inserted, `false` otherwise.
        bool insert(int v) {
            if (contains(v)) return false;
            add<+1>(v);
            const auto [t, u] = index(v);
            _bs[t] |= uint64_t(1) << u;
            return true;
        }
        // O(log n) if `v` is a member, O(1) otherwise.
        // Erase `v` if contained. Raise an assertion error if `v` is out of range.
        // Return `true` if `v` is erased, `false` otherwise.
        bool erase(int v) {
            if (not contains(v)) return false;
            add<-1>(v);
            const auto [t, u] = index(v);
            _bs[t] &= ~(uint64_t(1) << u);
            return true;
        }

        // O(log n).
        // Count elements < `v`. `v` may be out of range.
        int count_lt(int v) const {
            if (v <= 0) return 0;
            if (v >= _n) return _siz;
            auto [t, u] = index(v);
            int res = __builtin_popcountll(_bs[t] & ((uint64_t(1) << u) - 1));
            for (; t; t &= t - 1) res += _d[t];
            return res;
        }
        // O(log n).
        // Count elements <= `v`. `v` may be out of range.
        int count_leq(int v) const { return count_lt(v + 1); }
        // O(log n).
        // Count elements > `v`. `v` may be out of range.
        int count_gt(int v) const { return _siz - count_leq(v); }
        // O(log n).
        // Count elements >= `v`. `v` may be out of range.
        int count_geq(int v) const { return _siz - count_lt(v); }

        // O(log n).
        // `k`-th smallest element or `-1` if `k` is out of range.
        int kth_element(int k) const {
            // Out of range
            if (not (0 <= k and k < _siz)) return -1;
            // Binary search
            int t = 1 << _lg;
            // (I) non-leaf node
            //      [   t   ]
            //      [t-p]    [t+p]
            for (int p = 1 << _lg >> 1; p; p >>= 1) {
                if (int nk = t <= _wn ? k - _d[t] : -1; nk >= 0) k = nk, t += p;
                else t -= p;
            }
            // (II) leaf node
            if (int nk = t <= _wn ? k - _d[t] : -1; nk >= 0) k = nk, ++t;
            --t;
            return (t << LOG_WORD) | kth_setbit(_bs[t], k);
        }
        // O(log n).
        // `k`-th smallest element or `-1` if `k` is out of range.
        int operator[](int k) const { return kth_element(k); }

        // O(log n).
        // Max element <= `v` or `-1` if not exists
        int max_leq(int v) const {
            if (v < 0) return -1;
            v = std::min(v, _n - 1);
            const auto [t, u] = index(v);
            const int lz = (WORD - 1) - u;
            if (const uint64_t bits = _bs[t] << lz >> lz) {
                return (t << LOG_WORD) | top_setbit(bits);
            }
            for (int i = 1; i <= SEARCH_WIDTH; ++i) {
                if (t - i < 0) return -1;
                if (_bs[t - i]) return ((t - i) << LOG_WORD) | top_setbit(_bs[t - i]);
            }
            return *--upper_bound(v);
        }
        // O(log n).
        // Max element < `v` or `-1` if not exists
        int max_lt(int v) const { return max_leq(v - 1); }
        // O(log n).
        // Min element >= `v` or `-1` if not exists
        int min_geq(int v) const {
            if (v >= _n) return -1;
            v = std::max(v, 0);
            const auto [t, u] = index(v);
            if (const uint64_t bits = _bs[t] >> u << u) {
                return (t << LOG_WORD) | __builtin_ctzll(bits);
            }
            for (int i = 1; i <= SEARCH_WIDTH; ++i) {
                if (t + i >= _wn) return -1;
                if (_bs[t + i]) return ((t + i) << LOG_WORD) | __builtin_ctzll(_bs[t + i]);
            }
            return *lower_bound(v);
        }
        // O(log n).
        // Min element > `v` or `-1` if not exists
        int min_gt(int v) const { return min_geq(v + 1); }
    private:
        struct IndexHolder {
            friend fenwick_tree_set;

            using difference_type = int;
            using value_type = int;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = std::random_access_iterator_tag;

            // O(1). Index of the element pointed to by the iterator. Negative values or values greater than or equal to `n` (= size of the set) means that the iterator doesn't point to any element.
            int index() const { return i; }
            // O(1). Check if the iterator points to some element.
            bool has_value() const { return 0 <= i and i < ptr->size(); }

            // O(1)
            IndexHolder& operator++() { return ++i, *this; }
            // O(1)
            IndexHolder operator++(int) { IndexHolder ret = *this; ++(*this); return ret; }
            // O(1)
            IndexHolder& operator--() { return --i, *this; }
            // O(1)
            IndexHolder operator--(int) { IndexHolder ret = *this; --(*this); return ret; }
            // O(1)
            IndexHolder& operator+=(difference_type dif) { return i += dif, *this; }
            // O(1)
            friend IndexHolder operator+(IndexHolder it, difference_type dif) { it += dif; return it; }
            // O(1)
            friend IndexHolder operator+(difference_type dif, IndexHolder it) { it += dif; return it; }
            // O(1)
            IndexHolder& operator-=(difference_type dif) { return i -= dif, *this; }
            // O(1)
            friend IndexHolder operator-(IndexHolder it, difference_type dif) { it -= dif; return it; }
            // O(1)
            difference_type operator-(const IndexHolder &rhs) const { return i - rhs.i; }
            // O(log n)
            value_type operator[](difference_type i) const { return *((*this) + i); }
            // O(log n)
            value_type operator*() const { return ptr->kth_element(i); }
            // O(1)
            bool operator!=(const IndexHolder &rhs) const { return i != rhs.i; }
            // O(1)
            bool operator==(const IndexHolder &rhs) const { return i == rhs.i; }
            // O(1)
            bool operator<(const IndexHolder &rhs) const { return i < rhs.i; }
            // O(1)
            bool operator<=(const IndexHolder &rhs) const { return i <= rhs.i; }
            // O(1)
            bool operator>(const IndexHolder &rhs) const { return i > rhs.i; }
            // O(1)
            bool operator>=(const IndexHolder &rhs) const { return i >= rhs.i; }
        private:
            IndexHolder(const fenwick_tree_set* ptr, int i) : ptr(ptr), i(i) {}

            const fenwick_tree_set* ptr;
            int i;
        };
    public:
        using iterator = IndexHolder;
        using difference_type = iterator::difference_type;
        using value_type = iterator::value_type;
        using pointer = iterator::pointer;
        using reference = iterator::reference;

        // O(1).
        iterator begin() const { return iterator(this, 0); }
        // O(1).
        iterator end() const { return iterator(this, _siz); }
        // O(log n).
        iterator lower_bound(int v) const { return iterator(this, count_lt(v)); }
        // O(log n).
        iterator upper_bound(int v) const { return iterator(this, count_leq(v)); }
        // O(log n) if `v` is a member, O(1) otherwise.
        iterator find(int v) const { return contains(v) ? lower_bound(v) : end(); }
        // O(log n).
        iterator erase(iterator it) { return erase(*it), it; }
    private:
        int _n, _wn, _lg, _siz;
        std::vector<int> _d;       // Fenwick Tree
        std::vector<uint64_t> _bs; // Bitset

        template <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t> = nullptr>
        void construct_from_values(const Container &values) {
            for (int v : values) {
                assert(0 <= v and v < _n);
                const auto [t, u] = index(v);
                if ((_bs[t] >> u) & 1) continue;
                ++_siz;
                ++_d[t + 1];
                _bs[t] |= uint64_t(1) << u;
            }
            for (int i = 1; i <= _wn; ++i) {
                const int p = i + (-i & i);
                if (p <= _wn) _d[p] += _d[i];
            }
        }

        static constexpr int _large(int i) { return i >> LOG_WORD; }
        static constexpr int _small(int i) { return i & MASK_WORD; }
        static constexpr std::array<int, 2> index(int i) { return { _large(i), _small(i) }; }

        // Position of highest set bit
        static constexpr int top_setbit(uint64_t x) { return (WORD - 1) - __builtin_clzll(x); }
        // Position of k-th set bit
        __attribute__((target("bmi2")))
        static int kth_setbit(uint64_t x, int k) { return __builtin_ctzll(_pdep_u64(uint64_t(1) << k, x)); }

        template <int k>
        void add(int v) {
            assert(0 <= v and v < _n);
            _siz += k;
            for (int t = _large(v) + 1; t <= _wn; t += -t & t) _d[t] += k;
        }
    };
} // namespace suisen

#endif // SUISEN_FENWICK_TREE_SET
