---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/graph/manhattan_minimum_distances.hpp
    title: "\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u3067\u6700\u3082\u8FD1\
      \u3044\u70B9\u3078\u306E\u8DDD\u96E2\u306E\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: library/graph/manhattan_mst.hpp
    title: Manhattan Mst
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/manhattan_mst/manhattanmst.test.cpp
    title: test/src/graph/manhattan_mst/manhattanmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T,\
    \ T), T(*e)()>\n    struct FenwickTreePrefix {\n        FenwickTreePrefix() :\
    \ FenwickTreePrefix(0) {}\n        explicit FenwickTreePrefix(int n) : _n(n),\
    \ _dat(_n + 1, e()) {}\n        FenwickTreePrefix(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(_n + 1, e()) {\n            for (int i = _n; i > 0; --i)\
    \ {\n                _dat[i] = op(_dat[i], dat[i - 1]);\n                if (int\
    \ p = i + (-i & i); p <= _n) _dat[p] = op(_dat[p], _dat[i]);\n            }\n\
    \        }\n        void apply(int i, const T& val) {\n            for (++i; i\
    \ <= _n; i += -i & i) _dat[i] = op(_dat[i], val);\n        }\n        T prefix_query(int\
    \ r) const {\n            T res = e();\n            for (; r; r -= -r & r) res\
    \ = op(res, _dat[r]);\n            return res;\n        }\n    private:\n    \
    \    int _n;\n        std::vector<T> _dat;\n    };\n} // namespace suisen\n\n\n\
    \n"
  code: "#ifndef SUISEN_FENWICK_TREE_PREFIX\n#define SUISEN_FENWICK_TREE_PREFIX\n\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T, T),\
    \ T(*e)()>\n    struct FenwickTreePrefix {\n        FenwickTreePrefix() : FenwickTreePrefix(0)\
    \ {}\n        explicit FenwickTreePrefix(int n) : _n(n), _dat(_n + 1, e()) {}\n\
    \        FenwickTreePrefix(const std::vector<T> &dat) : _n(dat.size()), _dat(_n\
    \ + 1, e()) {\n            for (int i = _n; i > 0; --i) {\n                _dat[i]\
    \ = op(_dat[i], dat[i - 1]);\n                if (int p = i + (-i & i); p <= _n)\
    \ _dat[p] = op(_dat[p], _dat[i]);\n            }\n        }\n        void apply(int\
    \ i, const T& val) {\n            for (++i; i <= _n; i += -i & i) _dat[i] = op(_dat[i],\
    \ val);\n        }\n        T prefix_query(int r) const {\n            T res =\
    \ e();\n            for (; r; r -= -r & r) res = op(res, _dat[r]);\n         \
    \   return res;\n        }\n    private:\n        int _n;\n        std::vector<T>\
    \ _dat;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_FENWICK_TREE_PREFIX\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
  requiredBy:
  - library/graph/manhattan_minimum_distances.hpp
  - library/graph/manhattan_mst.hpp
  timestamp: '2022-06-14 00:04:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/manhattan_mst/manhattanmst.test.cpp
documentation_of: library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
layout: document
title: Fenwick Tree Prefix
---
## Fenwick Tree Prefix

一般のモノイド $(\oplus,M)$ が乗る代わりに，処理できるクエリは以下の 2 つに制限される．

- $\mathrm{apply}(i,v)$: $A _ i \leftarrow A _ i \oplus v$ と更新する
- $\mathrm{prefix\\_query}(r)$: $\displaystyle \bigoplus _ {i = 0} ^ {r - 1} A _ i$ を計算する
