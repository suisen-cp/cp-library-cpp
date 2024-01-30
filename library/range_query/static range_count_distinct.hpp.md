---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/range_query/static range_count_distinct/static_range_count_distinct.test.cpp
    title: test/src/range_query/static range_count_distinct/static_range_count_distinct.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/range_query/static range_count_distinct.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstdint>\n#include <cstddef>\n#include <unordered_map>\n\
    #include <utility>\n#include <vector>\n\n#include <atcoder/fenwicktree>\n\nnamespace\
    \ suisen {\n    struct StaticRangeCountDistinctOffline {\n        StaticRangeCountDistinctOffline()\
    \ : StaticRangeCountDistinctOffline(std::vector<int>{}) {}\n        explicit StaticRangeCountDistinctOffline(const\
    \ std::vector<int>& a) : _n(a.size()), _q(0), _a(a) {}\n\n        void reserve(int\
    \ q) { _qs.reserve(q); }\n\n        // Return the ID of the given query (NOT the\
    \ answer)\n        int add_query(int l, int r) {\n            assert(0 <= l and\
    \ l <= r and r <= _n);\n            _qs.emplace_back(l, r);\n            return\
    \ _q++;\n        }\n\n        std::vector<int> solve() const {\n            //\
    \ last[v] = 1 + max{ i | a[i]=v or i=-1 }\n            std::unordered_map<int,\
    \ int> last;\n            // prv[i] = 1 + max{ j | a[i]=a[j] or j=-1 }\n     \
    \       std::vector<int> prv(_n);\n            for (int i = 0; i < _n; ++i) {\n\
    \                prv[i] = std::exchange(last[_a[i]], i + 1);\n            }\n\
    \            // sort ranges by bucket sort\n            std::vector<int> index(_n\
    \ + 2);\n            for (auto& [l, r] : _qs) {\n                ++index[r];\n\
    \            }\n            for (int i = 1; i <= _n; ++i) {\n                index[i]\
    \ += index[i - 1];\n            }\n            index[_n + 1] = _q;\n         \
    \   std::vector<int> qs_ord(_q);\n            for (int qid = 0; qid < _q; ++qid)\
    \ {\n                qs_ord[--index[_qs[qid].second]] = qid;\n            }\n\n\
    \            atcoder::fenwick_tree<int> ft(_n + 1);\n            std::vector<int>\
    \ ans(_q);\n            for (int r = 0; r <= _n; ++r) {\n                for (int\
    \ i = index[r]; i < index[r + 1]; ++i) {\n                    const int qid =\
    \ qs_ord[i], l = _qs[qid].first;\n                    assert(_qs[qid].second ==\
    \ r);\n                    ans[qid] = ft.sum(0, l + 1) - l;\n                }\n\
    \                if (r < _n) ft.add(prv[r], 1);\n            }\n            return\
    \ ans;\n        }\n\n    private:\n        int _n, _q;\n        std::vector<int>\
    \ _a;\n        std::vector<std::pair<int, int>> _qs;\n    };\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_STATIC_RANGE_COUNT_DISTINCT\n#define SUISEN_STATIC_RANGE_COUNT_DISTINCT\n\
    \n#include <cassert>\n#include <cstdint>\n#include <cstddef>\n#include <unordered_map>\n\
    #include <utility>\n#include <vector>\n\n#include <atcoder/fenwicktree>\n\nnamespace\
    \ suisen {\n    struct StaticRangeCountDistinctOffline {\n        StaticRangeCountDistinctOffline()\
    \ : StaticRangeCountDistinctOffline(std::vector<int>{}) {}\n        explicit StaticRangeCountDistinctOffline(const\
    \ std::vector<int>& a) : _n(a.size()), _q(0), _a(a) {}\n\n        void reserve(int\
    \ q) { _qs.reserve(q); }\n\n        // Return the ID of the given query (NOT the\
    \ answer)\n        int add_query(int l, int r) {\n            assert(0 <= l and\
    \ l <= r and r <= _n);\n            _qs.emplace_back(l, r);\n            return\
    \ _q++;\n        }\n\n        std::vector<int> solve() const {\n            //\
    \ last[v] = 1 + max{ i | a[i]=v or i=-1 }\n            std::unordered_map<int,\
    \ int> last;\n            // prv[i] = 1 + max{ j | a[i]=a[j] or j=-1 }\n     \
    \       std::vector<int> prv(_n);\n            for (int i = 0; i < _n; ++i) {\n\
    \                prv[i] = std::exchange(last[_a[i]], i + 1);\n            }\n\
    \            // sort ranges by bucket sort\n            std::vector<int> index(_n\
    \ + 2);\n            for (auto& [l, r] : _qs) {\n                ++index[r];\n\
    \            }\n            for (int i = 1; i <= _n; ++i) {\n                index[i]\
    \ += index[i - 1];\n            }\n            index[_n + 1] = _q;\n         \
    \   std::vector<int> qs_ord(_q);\n            for (int qid = 0; qid < _q; ++qid)\
    \ {\n                qs_ord[--index[_qs[qid].second]] = qid;\n            }\n\n\
    \            atcoder::fenwick_tree<int> ft(_n + 1);\n            std::vector<int>\
    \ ans(_q);\n            for (int r = 0; r <= _n; ++r) {\n                for (int\
    \ i = index[r]; i < index[r + 1]; ++i) {\n                    const int qid =\
    \ qs_ord[i], l = _qs[qid].first;\n                    assert(_qs[qid].second ==\
    \ r);\n                    ans[qid] = ft.sum(0, l + 1) - l;\n                }\n\
    \                if (r < _n) ft.add(prv[r], 1);\n            }\n            return\
    \ ans;\n        }\n\n    private:\n        int _n, _q;\n        std::vector<int>\
    \ _a;\n        std::vector<std::pair<int, int>> _qs;\n    };\n} // namespace suisen\n\
    \n#endif // SUISEN_STATIC_RANGE_COUNT_DISTINCT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/range_query/static range_count_distinct.hpp
  requiredBy: []
  timestamp: '2024-01-30 19:29:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/range_query/static range_count_distinct/static_range_count_distinct.test.cpp
documentation_of: library/range_query/static range_count_distinct.hpp
layout: document
title: Static range Count Distinct
---
## Static range Count Distinct
