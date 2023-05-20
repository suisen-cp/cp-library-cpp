---
data:
  _extendedDependsOn:
  - icon: ':warning:'
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
    \n\n\n\n#line 6 \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\n\n\
    namespace suisen {\n    struct fenwick_tree_set {\n        fenwick_tree_set():\
    \ fenwick_tree_set(0) {}\n        explicit fenwick_tree_set(int n, bool fullset\
    \ = false): _n(n), _lg(floor_log2(_n)), _siz(fullset ? _n : 0), _d(_n + 1) {\n\
    \            if (fullset) {\n                for (int i = 1; i <= _n; ++i) {\n\
    \                    ++_d[i];\n                    if (int p = i + (-i & i); p\
    \ <= _n) _d[p] += _d[i];\n                }\n            }\n        }\n\n    \
    \    int size() const { return _siz; }\n\n        void insert(int v) { add(v,\
    \ +1); }\n        void erase(int v) { add(v, -1); }\n\n        int count_lt(int\
    \ v) const {\n            if (v <= 0) return 0;\n            if (v >= _n) return\
    \ _siz;\n            int k = 0;\n            for (; v; v -= -v & v) k += _d[v];\n\
    \            return k;\n        }\n        int count_leq(int v) const { return\
    \ count_lt(v + 1); }\n        int count_gt(int v) const { return _siz - count_leq(v);\
    \ }\n        int count_geq(int v) const { return _siz - count_lt(v); }\n     \
    \   int count(int v) const { return count_leq(v) - count_lt(v); }\n\n        int\
    \ index_of(int v) const {\n            return count_lt(v);\n        }\n      \
    \  int kth_element(int k) const {\n            int i = 1 << _lg, s = 0;\n    \
    \        auto check = [&] { return i <= _n and s + _d[i] <= k; };\n          \
    \  for (int bit = _lg - 1; bit >= 0; --bit) {\n                if (check()) {\n\
    \                    s += _d[i];\n                    i += 1 << bit;\n       \
    \         } else {\n                    i -= 1 << bit;\n                }\n  \
    \          }\n            return (i + check()) - 1;\n        }\n    private:\n\
    \        int _n, _lg, _siz;\n        std::vector<int> _d;\n\n        static int\
    \ floor_log2(int x) {\n            int l = 0;\n            while (1 << (l + 1)\
    \ <= x) ++l;\n            return l;\n        }\n\n        void add(int v, int\
    \ k) {\n            assert(0 <= v and v < _n);\n            _siz += k;\n     \
    \       for (++v; v <= _n; v += -v & v) _d[v] += k;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 9 \"library/number/factorial_number.hpp\"\n\nnamespace suisen\
    \ {\n    struct factorial_number {\n        factorial_number(): factorial_number(1)\
    \ {}\n        explicit factorial_number(int n, long long val = 0): _n(n), _d(_n\
    \ - 1) {\n            bool neg = val < 0;\n            val = std::abs(val);\n\
    \            for (int i = 0; val and i < _n - 1; ++i) {\n                _d[i]\
    \ = val % (i + 2);\n                val /= i + 2;\n            }\n           \
    \ if (neg) *this = -*this;\n        }\n        explicit factorial_number(const\
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
  timestamp: '2023-05-11 13:33:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/number/factorial_number.hpp
layout: document
title: Factorial Number
---
## Factorial Number
