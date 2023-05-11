---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/number/factorial_number.hpp
    title: library/number/factorial_number.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_set.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ fenwick_tree_set {\n        fenwick_tree_set(): fenwick_tree_set(0) {}\n   \
    \     explicit fenwick_tree_set(int n, bool fullset = false): _n(n), _lg(floor_log2(_n)),\
    \ _siz(fullset ? _n : 0), _d(_n + 1) {\n            if (fullset) {\n         \
    \       for (int i = 1; i <= _n; ++i) {\n                    ++_d[i];\n      \
    \              if (int p = i + (-i & i); p <= _n) _d[p] += _d[i];\n          \
    \      }\n            }\n        }\n\n        int size() const { return _siz;\
    \ }\n\n        void insert(int v) { add(v, +1); }\n        void erase(int v) {\
    \ add(v, -1); }\n\n        int count_lt(int v) const {\n            if (v <= 0)\
    \ return 0;\n            if (v >= _n) return _siz;\n            int k = 0;\n \
    \           for (; v; v -= -v & v) k += _d[v];\n            return k;\n      \
    \  }\n        int count_leq(int v) const { return count_lt(v + 1); }\n       \
    \ int count_gt(int v) const { return _siz - count_leq(v); }\n        int count_geq(int\
    \ v) const { return _siz - count_lt(v); }\n        int count(int v) const { return\
    \ count_leq(v) - count_lt(v); }\n\n        int index_of(int v) const {\n     \
    \       return count_lt(v);\n        }\n        int kth_element(int k) const {\n\
    \            int i = 1 << _lg, s = 0;\n            auto check = [&] { return i\
    \ <= _n and s + _d[i] <= k; };\n            for (int bit = _lg - 1; bit >= 0;\
    \ --bit) {\n                if (check()) {\n                    s += _d[i];\n\
    \                    i += 1 << bit;\n                } else {\n              \
    \      i -= 1 << bit;\n                }\n            }\n            return (i\
    \ + check()) - 1;\n        }\n    private:\n        int _n, _lg, _siz;\n     \
    \   std::vector<int> _d;\n\n        static int floor_log2(int x) {\n         \
    \   int l = 0;\n            while (1 << (l + 1) <= x) ++l;\n            return\
    \ l;\n        }\n\n        void add(int v, int k) {\n            assert(0 <= v\
    \ and v < _n);\n            _siz += k;\n            for (++v; v <= _n; v += -v\
    \ & v) _d[v] += k;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_FENWICK_TREE_SET\n#define SUISEN_FENWICK_TREE_SET\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    struct fenwick_tree_set\
    \ {\n        fenwick_tree_set(): fenwick_tree_set(0) {}\n        explicit fenwick_tree_set(int\
    \ n, bool fullset = false): _n(n), _lg(floor_log2(_n)), _siz(fullset ? _n : 0),\
    \ _d(_n + 1) {\n            if (fullset) {\n                for (int i = 1; i\
    \ <= _n; ++i) {\n                    ++_d[i];\n                    if (int p =\
    \ i + (-i & i); p <= _n) _d[p] += _d[i];\n                }\n            }\n \
    \       }\n\n        int size() const { return _siz; }\n\n        void insert(int\
    \ v) { add(v, +1); }\n        void erase(int v) { add(v, -1); }\n\n        int\
    \ count_lt(int v) const {\n            if (v <= 0) return 0;\n            if (v\
    \ >= _n) return _siz;\n            int k = 0;\n            for (; v; v -= -v &\
    \ v) k += _d[v];\n            return k;\n        }\n        int count_leq(int\
    \ v) const { return count_lt(v + 1); }\n        int count_gt(int v) const { return\
    \ _siz - count_leq(v); }\n        int count_geq(int v) const { return _siz - count_lt(v);\
    \ }\n        int count(int v) const { return count_leq(v) - count_lt(v); }\n\n\
    \        int index_of(int v) const {\n            return count_lt(v);\n      \
    \  }\n        int kth_element(int k) const {\n            int i = 1 << _lg, s\
    \ = 0;\n            auto check = [&] { return i <= _n and s + _d[i] <= k; };\n\
    \            for (int bit = _lg - 1; bit >= 0; --bit) {\n                if (check())\
    \ {\n                    s += _d[i];\n                    i += 1 << bit;\n   \
    \             } else {\n                    i -= 1 << bit;\n                }\n\
    \            }\n            return (i + check()) - 1;\n        }\n    private:\n\
    \        int _n, _lg, _siz;\n        std::vector<int> _d;\n\n        static int\
    \ floor_log2(int x) {\n            int l = 0;\n            while (1 << (l + 1)\
    \ <= x) ++l;\n            return l;\n        }\n\n        void add(int v, int\
    \ k) {\n            assert(0 <= v and v < _n);\n            _siz += k;\n     \
    \       for (++v; v <= _n; v += -v & v) _d[v] += k;\n        }\n    };\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_FENWICK_TREE_SET\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree/fenwick_tree_set.hpp
  requiredBy:
  - library/number/factorial_number.hpp
  timestamp: '2023-05-11 13:19:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/fenwick_tree/fenwick_tree_set.hpp
layout: document
redirect_from:
- /library/library/datastructure/fenwick_tree/fenwick_tree_set.hpp
- /library/library/datastructure/fenwick_tree/fenwick_tree_set.hpp.html
title: library/datastructure/fenwick_tree/fenwick_tree_set.hpp
---
