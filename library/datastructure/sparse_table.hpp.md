---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/algorithm/rmq_pm1.hpp
    title: "\u96A3\u63A5\u8981\u7D20\u306E\u5DEE\u304C $\\pm 1$ \u306E\u5834\u5408\
      \u306E RMQ"
  - icon: ':heavy_check_mark:'
    path: library/algorithm/rmq_pm1_with_index.hpp
    title: "\u96A3\u63A5\u8981\u7D20\u306E\u5DEE\u304C $\\pm 1$ \u306E\u5834\u5408\
      \u306E RMQ (\u6DFB\u5B57\u306E\u5FA9\u5143\u4ED8\u304D)"
  - icon: ':heavy_check_mark:'
    path: library/string/compare_substring.hpp
    title: Compare Substring
  - icon: ':heavy_check_mark:'
    path: library/tree/lowest_common_ancestor.hpp
    title: Lowest Common Ancestor
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/abc141_e.test.cpp
    title: test/src/string/compare_substring/abc141_e.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/dummy.test.cpp
    title: test/src/string/compare_substring/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/string_search.test.cpp
    title: test/src/string/compare_substring/string_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/compare_substring/substring.test.cpp
    title: test/src/string/compare_substring/substring.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/level_ancestor/jump_on_tree.test.cpp
    title: test/src/tree/level_ancestor/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
    title: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/sparse_table.hpp\"\n\n\n\n#include\
    \ <vector>\n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n\
    \    struct SparseTable {\n        SparseTable() = default;\n        SparseTable(std::vector<T>&&\
    \ a) : n(a.size()), log(floor_log2(n)), table(log + 1), flog(n + 1, 0) {\n   \
    \         build_table(std::move(a));\n            build_flog_table();\n      \
    \  }\n        SparseTable(const std::vector<T>& a) : SparseTable(std::vector<T>(a))\
    \ {}\n        T operator()(int l, int r) const {\n            if (l >= r) return\
    \ e();\n            int i = flog[r - l];\n            return op(table[i][l], table[i][r\
    \ - (1 << i)]);\n        }\n        T prod(int l, int r) const {\n           \
    \ return (*this)(l, r);\n        }\n    private:\n        int n;\n        int\
    \ log;\n        std::vector<std::vector<T>> table;\n        std::vector<int> flog;\n\
    \n        void build_table(std::vector<T>&& a) {\n            table[0] = std::move(a);\n\
    \            for (int i = 0; i < log; ++i) {\n                int lmax = n - (1\
    \ << (i + 1));\n                table[i + 1].resize(lmax + 1);\n             \
    \   for (int l = 0; l <= lmax; ++l) table[i + 1][l] = op(table[i][l], table[i][l\
    \ + (1 << i)]);\n            }\n        }\n        void build_flog_table() {\n\
    \            for (int l = 0; l < log; ++l) {\n                std::fill(flog.begin()\
    \ + (1 << l), flog.begin() + (1 << (l + 1)), l);\n            }\n            std::fill(flog.begin()\
    \ + (1 << log), flog.end(), log);\n        }\n        static int floor_log2(int\
    \ i) {\n            return 31 - __builtin_clz(i);\n        }\n    };\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_SPARSE_TABLE\n#define SUISEN_SPARSE_TABLE\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct\
    \ SparseTable {\n        SparseTable() = default;\n        SparseTable(std::vector<T>&&\
    \ a) : n(a.size()), log(floor_log2(n)), table(log + 1), flog(n + 1, 0) {\n   \
    \         build_table(std::move(a));\n            build_flog_table();\n      \
    \  }\n        SparseTable(const std::vector<T>& a) : SparseTable(std::vector<T>(a))\
    \ {}\n        T operator()(int l, int r) const {\n            if (l >= r) return\
    \ e();\n            int i = flog[r - l];\n            return op(table[i][l], table[i][r\
    \ - (1 << i)]);\n        }\n        T prod(int l, int r) const {\n           \
    \ return (*this)(l, r);\n        }\n    private:\n        int n;\n        int\
    \ log;\n        std::vector<std::vector<T>> table;\n        std::vector<int> flog;\n\
    \n        void build_table(std::vector<T>&& a) {\n            table[0] = std::move(a);\n\
    \            for (int i = 0; i < log; ++i) {\n                int lmax = n - (1\
    \ << (i + 1));\n                table[i + 1].resize(lmax + 1);\n             \
    \   for (int l = 0; l <= lmax; ++l) table[i + 1][l] = op(table[i][l], table[i][l\
    \ + (1 << i)]);\n            }\n        }\n        void build_flog_table() {\n\
    \            for (int l = 0; l < log; ++l) {\n                std::fill(flog.begin()\
    \ + (1 << l), flog.begin() + (1 << (l + 1)), l);\n            }\n            std::fill(flog.begin()\
    \ + (1 << log), flog.end(), log);\n        }\n        static int floor_log2(int\
    \ i) {\n            return 31 - __builtin_clz(i);\n        }\n    };\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SPARSE_TABLE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/sparse_table.hpp
  requiredBy:
  - library/algorithm/rmq_pm1_with_index.hpp
  - library/algorithm/rmq_pm1.hpp
  - library/tree/lowest_common_ancestor.hpp
  - library/string/compare_substring.hpp
  timestamp: '2022-05-29 02:48:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
  - test/src/tree/level_ancestor/jump_on_tree.test.cpp
  - test/src/string/compare_substring/substring.test.cpp
  - test/src/string/compare_substring/dummy.test.cpp
  - test/src/string/compare_substring/string_search.test.cpp
  - test/src/string/compare_substring/abc141_e.test.cpp
documentation_of: library/datastructure/sparse_table.hpp
layout: document
title: Sparse Table
---
## Sparse Table