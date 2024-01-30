---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/fenwick_tree/fenwick_tree_set.hpp
    title: Fenwick Tree Set
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/number/factorial_number.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\
    \n\n\n\n#include <array>\n#line 6 \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\
    \n#include <cstdint>\n#include <numeric>\n#line 9 \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\
    \n\n#ifdef _MSC_VER\n#  include <intrin.h>\n#else\n#  include <x86intrin.h>\n\
    #endif\n\nnamespace suisen {\n    struct fenwick_tree_set {\n    private:\n  \
    \      template <typename T>\n        struct is_container {\n            template\
    \ <typename T2>\n            static auto test(T2 t) -> decltype(++t.begin() !=\
    \ t.end(), *t.begin(), std::true_type{});\n            static std::false_type\
    \ test(...);\n        public:\n            static constexpr bool value = decltype(test(std::declval<T>()))::value;\n\
    \        };\n        static constexpr int WORD = 64, MASK_WORD = 63, LOG_WORD\
    \ = 6;\n        static constexpr int SEARCH_WIDTH = 1;\n    public:\n        fenwick_tree_set()\
    \ : fenwick_tree_set(0) {}\n        // Construct (an empty / a full) set and set\
    \ the universe as {0,1,...,n-1}\n        explicit fenwick_tree_set(int n, bool\
    \ fullset = false): _n(n), _wn(std::max((_n + (WORD - 1)) >> LOG_WORD, 1)), _lg(top_setbit(_wn)),\
    \ _siz(0), _d(_wn + 1), _bs(_wn) {\n            if (fullset) {\n             \
    \   std::vector<int> values(n);\n                std::iota(values.begin(), values.end(),\
    \ 0);\n                construct_from_values(values);\n            }\n       \
    \ }\n        // Construct a set containing the values in `values`.\n        template\
    \ <typename Container, std::enable_if_t<is_container<Container>::value, std::nullptr_t>\
    \ = nullptr>\n        fenwick_tree_set(int n, const Container &values): fenwick_tree_set(n)\
    \ {\n            construct_from_values(values);\n        }\n        // Construct\
    \ a set containing the values `i` such that `seq01[i] == 1` (or `one` you give).\n\
    \        template <typename Container, std::enable_if_t<is_container<Container>::value,\
    \ std::nullptr_t> = nullptr>\n        fenwick_tree_set(const Container &seq01,\
    \ typename Container::value_type one = 1): fenwick_tree_set(seq01.size()) {\n\
    \            std::vector<int> values;\n            for (int i = 0; i < _n; ++i)\
    \ if (seq01[i] == one) values.push_back(i);\n            construct_from_values(values);\n\
    \        }\n\n        // O(1).\n        // Number of elements.\n        int size()\
    \ const { return _siz; }\n\n        // O(1).\n        // Check if `v` is contained.\
    \ `v` may be out of range.\n        bool contains(int v) const {\n           \
    \ if (not (0 <= v and v < _n)) return false;\n            const auto [t, u] =\
    \ index(v);\n            return (_bs[t] >> u) & 1;\n        }\n        // O(log\
    \ n) if `v` is not a member, O(1) otherwise.\n        // Insert `v` if not contained.\
    \ Raise an assertion error if `v` is out of range.\n        // Return `true` if\
    \ `v` is inserted, `false` otherwise.\n        bool insert(int v) {\n        \
    \    if (contains(v)) return false;\n            add<+1>(v);\n            const\
    \ auto [t, u] = index(v);\n            _bs[t] |= uint64_t(1) << u;\n         \
    \   return true;\n        }\n        // O(log n) if `v` is a member, O(1) otherwise.\n\
    \        // Erase `v` if contained. Raise an assertion error if `v` is out of\
    \ range.\n        // Return `true` if `v` is erased, `false` otherwise.\n    \
    \    bool erase(int v) {\n            if (not contains(v)) return false;\n   \
    \         add<-1>(v);\n            const auto [t, u] = index(v);\n           \
    \ _bs[t] &= ~(uint64_t(1) << u);\n            return true;\n        }\n\n    \
    \    // O(log n).\n        // Count elements < `v`. `v` may be out of range.\n\
    \        int count_lt(int v) const {\n            if (v <= 0) return 0;\n    \
    \        if (v >= _n) return _siz;\n            auto [t, u] = index(v);\n    \
    \        int res = __builtin_popcountll(_bs[t] & ((uint64_t(1) << u) - 1));\n\
    \            for (; t; t &= t - 1) res += _d[t];\n            return res;\n  \
    \      }\n        // O(log n).\n        // Count elements <= `v`. `v` may be out\
    \ of range.\n        int count_leq(int v) const { return count_lt(v + 1); }\n\
    \        // O(log n).\n        // Count elements > `v`. `v` may be out of range.\n\
    \        int count_gt(int v) const { return _siz - count_leq(v); }\n        //\
    \ O(log n).\n        // Count elements >= `v`. `v` may be out of range.\n    \
    \    int count_geq(int v) const { return _siz - count_lt(v); }\n\n        // O(log\
    \ n).\n        // `k`-th smallest element or `-1` if `k` is out of range.\n  \
    \      int kth_element(int k) const {\n            // Out of range\n         \
    \   if (not (0 <= k and k < _siz)) return -1;\n            // Binary search\n\
    \            int t = 1 << _lg;\n            // (I) non-leaf node\n           \
    \ //      [   t   ]\n            //      [t-p]    [t+p]\n            for (int\
    \ p = 1 << _lg >> 1; p; p >>= 1) {\n                if (int nk = t <= _wn ? k\
    \ - _d[t] : -1; nk >= 0) k = nk, t += p;\n                else t -= p;\n     \
    \       }\n            // (II) leaf node\n            if (int nk = t <= _wn ?\
    \ k - _d[t] : -1; nk >= 0) k = nk, ++t;\n            --t;\n            return\
    \ (t << LOG_WORD) | kth_setbit(_bs[t], k);\n        }\n        // O(log n).\n\
    \        // `k`-th smallest element or `-1` if `k` is out of range.\n        int\
    \ operator[](int k) const { return kth_element(k); }\n\n        // O(log n).\n\
    \        // Max element <= `v` or `-1` if not exists\n        int max_leq(int\
    \ v) const {\n            if (v < 0) return -1;\n            v = std::min(v, _n\
    \ - 1);\n            const auto [t, u] = index(v);\n            const int lz =\
    \ (WORD - 1) - u;\n            if (const uint64_t bits = _bs[t] << lz >> lz) {\n\
    \                return (t << LOG_WORD) | top_setbit(bits);\n            }\n \
    \           for (int i = 1; i <= SEARCH_WIDTH; ++i) {\n                if (t -\
    \ i < 0) return -1;\n                if (_bs[t - i]) return ((t - i) << LOG_WORD)\
    \ | top_setbit(_bs[t - i]);\n            }\n            return *--upper_bound(v);\n\
    \        }\n        // O(log n).\n        // Max element < `v` or `-1` if not\
    \ exists\n        int max_lt(int v) const { return max_leq(v - 1); }\n       \
    \ // O(log n).\n        // Min element >= `v` or `-1` if not exists\n        int\
    \ min_geq(int v) const {\n            if (v >= _n) return -1;\n            v =\
    \ std::max(v, 0);\n            const auto [t, u] = index(v);\n            if (const\
    \ uint64_t bits = _bs[t] >> u << u) {\n                return (t << LOG_WORD)\
    \ | __builtin_ctzll(bits);\n            }\n            for (int i = 1; i <= SEARCH_WIDTH;\
    \ ++i) {\n                if (t + i >= _wn) return -1;\n                if (_bs[t\
    \ + i]) return ((t + i) << LOG_WORD) | __builtin_ctzll(_bs[t + i]);\n        \
    \    }\n            return *lower_bound(v);\n        }\n        // O(log n).\n\
    \        // Min element > `v` or `-1` if not exists\n        int min_gt(int v)\
    \ const { return min_geq(v + 1); }\n    private:\n        struct IndexHolder {\n\
    \            friend fenwick_tree_set;\n\n            using difference_type = int;\n\
    \            using value_type = int;\n            using pointer = value_type*;\n\
    \            using reference = value_type&;\n            using iterator_category\
    \ = std::random_access_iterator_tag;\n\n            // O(1). Index of the element\
    \ pointed to by the iterator. Negative values or values greater than or equal\
    \ to `n` (= size of the set) means that the iterator doesn't point to any element.\n\
    \            int index() const { return i; }\n            // O(1). Check if the\
    \ iterator points to some element.\n            bool has_value() const { return\
    \ 0 <= i and i < ptr->size(); }\n\n            // O(1)\n            IndexHolder&\
    \ operator++() { return ++i, *this; }\n            // O(1)\n            IndexHolder\
    \ operator++(int) { IndexHolder ret = *this; ++(*this); return ret; }\n      \
    \      // O(1)\n            IndexHolder& operator--() { return --i, *this; }\n\
    \            // O(1)\n            IndexHolder operator--(int) { IndexHolder ret\
    \ = *this; --(*this); return ret; }\n            // O(1)\n            IndexHolder&\
    \ operator+=(difference_type dif) { return i += dif, *this; }\n            //\
    \ O(1)\n            friend IndexHolder operator+(IndexHolder it, difference_type\
    \ dif) { it += dif; return it; }\n            // O(1)\n            friend IndexHolder\
    \ operator+(difference_type dif, IndexHolder it) { it += dif; return it; }\n \
    \           // O(1)\n            IndexHolder& operator-=(difference_type dif)\
    \ { return i -= dif, *this; }\n            // O(1)\n            friend IndexHolder\
    \ operator-(IndexHolder it, difference_type dif) { it -= dif; return it; }\n \
    \           // O(1)\n            difference_type operator-(const IndexHolder &rhs)\
    \ const { return i - rhs.i; }\n            // O(log n)\n            value_type\
    \ operator[](difference_type i) const { return *((*this) + i); }\n           \
    \ // O(log n)\n            value_type operator*() const { return ptr->kth_element(i);\
    \ }\n            // O(1)\n            bool operator!=(const IndexHolder &rhs)\
    \ const { return i != rhs.i; }\n            // O(1)\n            bool operator==(const\
    \ IndexHolder &rhs) const { return i == rhs.i; }\n            // O(1)\n      \
    \      bool operator<(const IndexHolder &rhs) const { return i < rhs.i; }\n  \
    \          // O(1)\n            bool operator<=(const IndexHolder &rhs) const\
    \ { return i <= rhs.i; }\n            // O(1)\n            bool operator>(const\
    \ IndexHolder &rhs) const { return i > rhs.i; }\n            // O(1)\n       \
    \     bool operator>=(const IndexHolder &rhs) const { return i >= rhs.i; }\n \
    \       private:\n            IndexHolder(const fenwick_tree_set* ptr, int i)\
    \ : ptr(ptr), i(i) {}\n\n            const fenwick_tree_set* ptr;\n          \
    \  int i;\n        };\n    public:\n        using iterator = IndexHolder;\n  \
    \      using difference_type = iterator::difference_type;\n        using value_type\
    \ = iterator::value_type;\n        using pointer = iterator::pointer;\n      \
    \  using reference = iterator::reference;\n\n        // O(1).\n        iterator\
    \ begin() const { return iterator(this, 0); }\n        // O(1).\n        iterator\
    \ end() const { return iterator(this, _siz); }\n        // O(log n).\n       \
    \ iterator lower_bound(int v) const { return iterator(this, count_lt(v)); }\n\
    \        // O(log n).\n        iterator upper_bound(int v) const { return iterator(this,\
    \ count_leq(v)); }\n        // O(log n) if `v` is a member, O(1) otherwise.\n\
    \        iterator find(int v) const { return contains(v) ? lower_bound(v) : end();\
    \ }\n        // O(log n).\n        iterator erase(iterator it) { return erase(*it),\
    \ it; }\n    private:\n        int _n, _wn, _lg, _siz;\n        std::vector<int>\
    \ _d;       // Fenwick Tree\n        std::vector<uint64_t> _bs; // Bitset\n\n\
    \        template <typename Container, std::enable_if_t<is_container<Container>::value,\
    \ std::nullptr_t> = nullptr>\n        void construct_from_values(const Container\
    \ &values) {\n            for (int v : values) {\n                assert(0 <=\
    \ v and v < _n);\n                const auto [t, u] = index(v);\n            \
    \    if ((_bs[t] >> u) & 1) continue;\n                ++_siz;\n             \
    \   ++_d[t + 1];\n                _bs[t] |= uint64_t(1) << u;\n            }\n\
    \            for (int i = 1; i <= _wn; ++i) {\n                const int p = i\
    \ + (-i & i);\n                if (p <= _wn) _d[p] += _d[i];\n            }\n\
    \        }\n\n        static constexpr int _large(int i) { return i >> LOG_WORD;\
    \ }\n        static constexpr int _small(int i) { return i & MASK_WORD; }\n  \
    \      static constexpr std::array<int, 2> index(int i) { return { _large(i),\
    \ _small(i) }; }\n\n        // Position of highest set bit\n        static constexpr\
    \ int top_setbit(uint64_t x) { return (WORD - 1) - __builtin_clzll(x); }\n   \
    \     // Position of k-th set bit\n        __attribute__((target(\"bmi2\")))\n\
    \        static int kth_setbit(uint64_t x, int k) { return __builtin_ctzll(_pdep_u64(uint64_t(1)\
    \ << k, x)); }\n\n        template <int k>\n        void add(int v) {\n      \
    \      assert(0 <= v and v < _n);\n            _siz += k;\n            for (int\
    \ t = _large(v) + 1; t <= _wn; t += -t & t) _d[t] += k;\n        }\n    };\n}\
    \ // namespace suisen\n\n\n#line 9 \"library/number/factorial_number.hpp\"\n\n\
    namespace suisen {\n    struct factorial_number {\n        factorial_number():\
    \ factorial_number(1) {}\n        explicit factorial_number(int n, long long val\
    \ = 0): _n(n), _d(_n - 1) {\n            bool neg = val < 0;\n            val\
    \ = std::abs(val);\n            for (int i = 0; val and i < _n - 1; ++i) {\n \
    \               _d[i] = val % (i + 2);\n                val /= i + 2;\n      \
    \      }\n            if (neg) *this = -*this;\n        }\n        explicit factorial_number(const\
    \ std::vector<int>& perm): factorial_number(perm.size()) {\n            fenwick_tree_set\
    \ st(_n, true);\n            for (int i = 0; i < _n - 1; ++i) {\n            \
    \    int v = perm[i];\n                _d[_n - 2 - i] = st.index_of(v);\n    \
    \            st.erase(v);\n            }\n        }\n\n        int size() const\
    \ {\n            return _n;\n        }\n        void resize(int n) {\n       \
    \     _n = n;\n            _d.resize(_n - 1);\n        }\n\n        factorial_number\
    \ operator-() const {\n            factorial_number res(_n);\n            res\
    \ -= *this;\n            return res;\n        }\n\n        factorial_number& operator++()\
    \ {\n            for (int i = 0; i < _n - 1; ++i) {\n                if (++_d[i]\
    \ > i + 1) {\n                    _d[i] = 0;\n                } else {\n     \
    \               break;\n                }\n            }\n            return *this;\n\
    \        }\n        factorial_number& operator--() {\n            for (int i =\
    \ 0; i < _n - 1; ++i) {\n                if (--_d[i] < 0) {\n                \
    \    _d[i] = i + 1;\n                } else {\n                    break;\n  \
    \              }\n            }\n            return *this;\n        }\n\n    \
    \    factorial_number operator++(int) {\n            factorial_number res = *this;\n\
    \            ++* this;\n            return res;\n        }\n        factorial_number\
    \ operator--(int) {\n            factorial_number res = *this;\n            --*\
    \ this;\n            return res;\n        }\n\n        factorial_number& operator+=(const\
    \ factorial_number& x) {\n            assert(size() == x.size());\n          \
    \  add(x, 0);\n            return *this;\n        }\n        factorial_number&\
    \ operator-=(factorial_number x) {\n            assert(size() == x.size());\n\
    \            for (int i = 0; i < _n - 1; ++i) {\n                x._d[i] = (i\
    \ + 1) - x._d[i];\n            }\n            add(x, 1);\n            return *this;\n\
    \        }\n\n        friend factorial_number operator+(const factorial_number&\
    \ x, const factorial_number& y) {\n            factorial_number z = x;\n     \
    \       z += y;\n            return z;\n        }\n        friend factorial_number\
    \ operator-(const factorial_number& x, const factorial_number& y) {\n        \
    \    factorial_number z = x;\n            z -= y;\n            return z;\n   \
    \     }\n\n        factorial_number& operator+=(long long val) {\n           \
    \ return *this += factorial_number(_n, val);\n        }\n        factorial_number&\
    \ operator-=(long long val) {\n            return *this -= factorial_number(_n,\
    \ val);\n        }\n\n        friend factorial_number operator+(const factorial_number&\
    \ x, long long val) {\n            return x + factorial_number(x._n, val);\n \
    \       }\n        friend factorial_number operator-(const factorial_number& x,\
    \ long long val) {\n            return x - factorial_number(x._n, val);\n    \
    \    }\n        friend factorial_number operator+(long long val, const factorial_number&\
    \ x) {\n            return factorial_number(x._n, val) + x;\n        }\n     \
    \   friend factorial_number operator-(long long val, const factorial_number& x)\
    \ {\n            return factorial_number(x._n, val) - x;\n        }\n\n      \
    \  factorial_number& operator*=(long long val) {\n            bool neg = val <\
    \ 0;\n            val = std::abs(val);\n            __int128_t carry = 0;\n  \
    \          for (int i = 0; i < _n - 1; ++i) {\n                __int128_t x =\
    \ __int128_t(_d[i]) * val + carry;\n                _d[i] = x % (i + 2);\n   \
    \             carry = x / (i + 2);\n            }\n            if (neg) *this\
    \ = -*this;\n            return *this;\n        }\n        friend factorial_number\
    \ operator*(const factorial_number& x, long long val) {\n            factorial_number\
    \ z = x;\n            z *= val;\n            return z;\n        }\n        friend\
    \ factorial_number operator*(long long val, const factorial_number& x) {\n   \
    \         return x * val;\n        }\n\n        std::vector<int> to_permutation()\
    \ const {\n            fenwick_tree_set st(_n, true);\n            std::vector<int>\
    \ p(_n);\n            for (int i = 0; i < _n; ++i) {\n                int v =\
    \ st.kth_element(i < _n - 1 ? _d[_n - 2 - i] : 0);\n                p[i] = v;\n\
    \                st.erase(v);\n            }\n            return p;\n        }\n\
    \        unsigned long long to_ull() const {\n            unsigned long long res\
    \ = 0;\n            for (int i = _n - 2; i >= 0; --i) {\n                res =\
    \ res * (i + 2) + _d[i];\n            }\n            return res;\n        }\n\n\
    \        friend bool operator==(const factorial_number &x, const factorial_number\
    \ &y) {\n            return x._d == y._d;\n        }\n        friend bool operator!=(const\
    \ factorial_number &x, const factorial_number &y) {\n            return x._d !=\
    \ y._d;\n        }\n        friend bool operator<(const factorial_number &x, const\
    \ factorial_number &y) {\n            assert(x._n == y._n);\n            for (int\
    \ i = x._n - 2; i >= 0; --i) if (x._d[i] != y._d[i]) {\n                return\
    \ x._d[i] < y._d[i];\n            }\n            return false;\n        }\n  \
    \      friend bool operator<=(const factorial_number &x, const factorial_number\
    \ &y) {\n            return not (y < x);\n        }\n        friend bool operator>(const\
    \ factorial_number &x, const factorial_number &y) {\n            return y < x;\n\
    \        }\n        friend bool operator>=(const factorial_number &x, const factorial_number\
    \ &y) {\n            return not (x < y);\n        }\n    private:\n        //\
    \ Sum[i=0,_n-2] _d[i] * (i+1)!\n        int _n;\n        std::vector<int> _d;\n\
    \n        void add(const factorial_number& x, int carry) {\n            for (int\
    \ i = 0; i < _n - 1; ++i) {\n                _d[i] += x._d[i] + carry;\n     \
    \           if (_d[i] > i + 1) {\n                    _d[i] -= i + 2;\n      \
    \              carry = 1;\n                } else {\n                    carry\
    \ = 0;\n                }\n            }\n        }\n        static int floor_log2(int\
    \ x) {\n            int l = 0;\n            while (1 << (l + 1) <= x) ++l;\n \
    \           return l;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_FACTORIAL_NUMBER\n#define SUISEN_FACTORIAL_NUMBER\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\n#include \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\
    \n\nnamespace suisen {\n    struct factorial_number {\n        factorial_number():\
    \ factorial_number(1) {}\n        explicit factorial_number(int n, long long val\
    \ = 0): _n(n), _d(_n - 1) {\n            bool neg = val < 0;\n            val\
    \ = std::abs(val);\n            for (int i = 0; val and i < _n - 1; ++i) {\n \
    \               _d[i] = val % (i + 2);\n                val /= i + 2;\n      \
    \      }\n            if (neg) *this = -*this;\n        }\n        explicit factorial_number(const\
    \ std::vector<int>& perm): factorial_number(perm.size()) {\n            fenwick_tree_set\
    \ st(_n, true);\n            for (int i = 0; i < _n - 1; ++i) {\n            \
    \    int v = perm[i];\n                _d[_n - 2 - i] = st.index_of(v);\n    \
    \            st.erase(v);\n            }\n        }\n\n        int size() const\
    \ {\n            return _n;\n        }\n        void resize(int n) {\n       \
    \     _n = n;\n            _d.resize(_n - 1);\n        }\n\n        factorial_number\
    \ operator-() const {\n            factorial_number res(_n);\n            res\
    \ -= *this;\n            return res;\n        }\n\n        factorial_number& operator++()\
    \ {\n            for (int i = 0; i < _n - 1; ++i) {\n                if (++_d[i]\
    \ > i + 1) {\n                    _d[i] = 0;\n                } else {\n     \
    \               break;\n                }\n            }\n            return *this;\n\
    \        }\n        factorial_number& operator--() {\n            for (int i =\
    \ 0; i < _n - 1; ++i) {\n                if (--_d[i] < 0) {\n                \
    \    _d[i] = i + 1;\n                } else {\n                    break;\n  \
    \              }\n            }\n            return *this;\n        }\n\n    \
    \    factorial_number operator++(int) {\n            factorial_number res = *this;\n\
    \            ++* this;\n            return res;\n        }\n        factorial_number\
    \ operator--(int) {\n            factorial_number res = *this;\n            --*\
    \ this;\n            return res;\n        }\n\n        factorial_number& operator+=(const\
    \ factorial_number& x) {\n            assert(size() == x.size());\n          \
    \  add(x, 0);\n            return *this;\n        }\n        factorial_number&\
    \ operator-=(factorial_number x) {\n            assert(size() == x.size());\n\
    \            for (int i = 0; i < _n - 1; ++i) {\n                x._d[i] = (i\
    \ + 1) - x._d[i];\n            }\n            add(x, 1);\n            return *this;\n\
    \        }\n\n        friend factorial_number operator+(const factorial_number&\
    \ x, const factorial_number& y) {\n            factorial_number z = x;\n     \
    \       z += y;\n            return z;\n        }\n        friend factorial_number\
    \ operator-(const factorial_number& x, const factorial_number& y) {\n        \
    \    factorial_number z = x;\n            z -= y;\n            return z;\n   \
    \     }\n\n        factorial_number& operator+=(long long val) {\n           \
    \ return *this += factorial_number(_n, val);\n        }\n        factorial_number&\
    \ operator-=(long long val) {\n            return *this -= factorial_number(_n,\
    \ val);\n        }\n\n        friend factorial_number operator+(const factorial_number&\
    \ x, long long val) {\n            return x + factorial_number(x._n, val);\n \
    \       }\n        friend factorial_number operator-(const factorial_number& x,\
    \ long long val) {\n            return x - factorial_number(x._n, val);\n    \
    \    }\n        friend factorial_number operator+(long long val, const factorial_number&\
    \ x) {\n            return factorial_number(x._n, val) + x;\n        }\n     \
    \   friend factorial_number operator-(long long val, const factorial_number& x)\
    \ {\n            return factorial_number(x._n, val) - x;\n        }\n\n      \
    \  factorial_number& operator*=(long long val) {\n            bool neg = val <\
    \ 0;\n            val = std::abs(val);\n            __int128_t carry = 0;\n  \
    \          for (int i = 0; i < _n - 1; ++i) {\n                __int128_t x =\
    \ __int128_t(_d[i]) * val + carry;\n                _d[i] = x % (i + 2);\n   \
    \             carry = x / (i + 2);\n            }\n            if (neg) *this\
    \ = -*this;\n            return *this;\n        }\n        friend factorial_number\
    \ operator*(const factorial_number& x, long long val) {\n            factorial_number\
    \ z = x;\n            z *= val;\n            return z;\n        }\n        friend\
    \ factorial_number operator*(long long val, const factorial_number& x) {\n   \
    \         return x * val;\n        }\n\n        std::vector<int> to_permutation()\
    \ const {\n            fenwick_tree_set st(_n, true);\n            std::vector<int>\
    \ p(_n);\n            for (int i = 0; i < _n; ++i) {\n                int v =\
    \ st.kth_element(i < _n - 1 ? _d[_n - 2 - i] : 0);\n                p[i] = v;\n\
    \                st.erase(v);\n            }\n            return p;\n        }\n\
    \        unsigned long long to_ull() const {\n            unsigned long long res\
    \ = 0;\n            for (int i = _n - 2; i >= 0; --i) {\n                res =\
    \ res * (i + 2) + _d[i];\n            }\n            return res;\n        }\n\n\
    \        friend bool operator==(const factorial_number &x, const factorial_number\
    \ &y) {\n            return x._d == y._d;\n        }\n        friend bool operator!=(const\
    \ factorial_number &x, const factorial_number &y) {\n            return x._d !=\
    \ y._d;\n        }\n        friend bool operator<(const factorial_number &x, const\
    \ factorial_number &y) {\n            assert(x._n == y._n);\n            for (int\
    \ i = x._n - 2; i >= 0; --i) if (x._d[i] != y._d[i]) {\n                return\
    \ x._d[i] < y._d[i];\n            }\n            return false;\n        }\n  \
    \      friend bool operator<=(const factorial_number &x, const factorial_number\
    \ &y) {\n            return not (y < x);\n        }\n        friend bool operator>(const\
    \ factorial_number &x, const factorial_number &y) {\n            return y < x;\n\
    \        }\n        friend bool operator>=(const factorial_number &x, const factorial_number\
    \ &y) {\n            return not (x < y);\n        }\n    private:\n        //\
    \ Sum[i=0,_n-2] _d[i] * (i+1)!\n        int _n;\n        std::vector<int> _d;\n\
    \n        void add(const factorial_number& x, int carry) {\n            for (int\
    \ i = 0; i < _n - 1; ++i) {\n                _d[i] += x._d[i] + carry;\n     \
    \           if (_d[i] > i + 1) {\n                    _d[i] -= i + 2;\n      \
    \              carry = 1;\n                } else {\n                    carry\
    \ = 0;\n                }\n            }\n        }\n        static int floor_log2(int\
    \ x) {\n            int l = 0;\n            while (1 << (l + 1) <= x) ++l;\n \
    \           return l;\n        }\n    };\n} // namespace suisen\n\n\n#endif //\
    \ SUISEN_FACTORIAL_NUMBER\n"
  dependsOn:
  - library/datastructure/fenwick_tree/fenwick_tree_set.hpp
  isVerificationFile: false
  path: library/number/factorial_number.hpp
  requiredBy: []
  timestamp: '2024-01-30 19:29:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/factorial_number.hpp
layout: document
title: Factorial Number
---
## Factorial Number
