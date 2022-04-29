---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/algorithm/rmq_pm1.hpp
    title: Rmq Pm1
  - icon: ':heavy_check_mark:'
    path: library/algorithm/rmq_pm1_with_index.hpp
    title: Rmq Pm1 With Index
  - icon: ':heavy_check_mark:'
    path: library/tree/lowest_common_ancestor.hpp
    title: Lowest Common Ancestor
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
    title: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/sparse_table.hpp\"\n\n\n\n#include\
    \ <vector>\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate\
    \ <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 7 \"library/datastructure/sparse_table.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <typename T, typename Op, constraints_t<is_bin_op<Op, T>> = nullptr>\nclass\
    \ SparseTable {\n    public:\n        SparseTable() {}\n        SparseTable(std::vector<T>\
    \ &&a, T e, Op op) : n(a.size()), log(floor_log2(n)), e(e), op(op), table(log\
    \ + 1), flog(n + 1, 0) {\n            build_table(std::move(a));\n           \
    \ build_flog_table();\n        }\n        SparseTable(const std::vector<T> &a,\
    \ T e, Op op) : SparseTable(std::vector<T>(a), e, op) {}\n        T operator()(int\
    \ l, int r) const {\n            if (l >= r) return e;\n            int i = flog[r\
    \ - l];\n            return op(table[i][l], table[i][r - (1 << i)]);\n       \
    \ }\n        T prod(int l, int r) const {\n            return (*this)(l, r);\n\
    \        }\n    private:\n        int n;\n        int log;\n        T e;\n   \
    \     Op op;\n        std::vector<std::vector<T>> table;\n        std::vector<int>\
    \ flog;\n\n        void build_table(std::vector<T> &&a) {\n            table[0]\
    \ = std::move(a);\n            for (int i = 0; i < log; ++i) {\n             \
    \   int lmax = n - (1 << (i + 1));\n                table[i + 1].resize(lmax +\
    \ 1);\n                for (int l = 0; l <= lmax; ++l) table[i + 1][l] = op(table[i][l],\
    \ table[i][l + (1 << i)]);\n            }\n        }\n        void build_flog_table()\
    \ {\n            for (int l = 0; l < log; ++l) {\n                std::fill(flog.begin()\
    \ + (1 << l), flog.begin() + (1 << (l + 1)), l);\n            }\n            std::fill(flog.begin()\
    \ + (1 << log), flog.end(), log);\n        }\n        static int floor_log2(int\
    \ i) {\n            return 31 - __builtin_clz(i);\n        }\n};\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_SPARSE_TABLE\n#define SUISEN_SPARSE_TABLE\n\n#include <vector>\n\
    \n#include \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <typename T, typename Op, constraints_t<is_bin_op<Op, T>> = nullptr>\nclass\
    \ SparseTable {\n    public:\n        SparseTable() {}\n        SparseTable(std::vector<T>\
    \ &&a, T e, Op op) : n(a.size()), log(floor_log2(n)), e(e), op(op), table(log\
    \ + 1), flog(n + 1, 0) {\n            build_table(std::move(a));\n           \
    \ build_flog_table();\n        }\n        SparseTable(const std::vector<T> &a,\
    \ T e, Op op) : SparseTable(std::vector<T>(a), e, op) {}\n        T operator()(int\
    \ l, int r) const {\n            if (l >= r) return e;\n            int i = flog[r\
    \ - l];\n            return op(table[i][l], table[i][r - (1 << i)]);\n       \
    \ }\n        T prod(int l, int r) const {\n            return (*this)(l, r);\n\
    \        }\n    private:\n        int n;\n        int log;\n        T e;\n   \
    \     Op op;\n        std::vector<std::vector<T>> table;\n        std::vector<int>\
    \ flog;\n\n        void build_table(std::vector<T> &&a) {\n            table[0]\
    \ = std::move(a);\n            for (int i = 0; i < log; ++i) {\n             \
    \   int lmax = n - (1 << (i + 1));\n                table[i + 1].resize(lmax +\
    \ 1);\n                for (int l = 0; l <= lmax; ++l) table[i + 1][l] = op(table[i][l],\
    \ table[i][l + (1 << i)]);\n            }\n        }\n        void build_flog_table()\
    \ {\n            for (int l = 0; l < log; ++l) {\n                std::fill(flog.begin()\
    \ + (1 << l), flog.begin() + (1 << (l + 1)), l);\n            }\n            std::fill(flog.begin()\
    \ + (1 << log), flog.end(), log);\n        }\n        static int floor_log2(int\
    \ i) {\n            return 31 - __builtin_clz(i);\n        }\n};\n} // namespace\
    \ suisen\n\n#endif // SUISEN_SPARSE_TABLE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/sparse_table.hpp
  requiredBy:
  - library/tree/lowest_common_ancestor.hpp
  - library/algorithm/rmq_pm1.hpp
  - library/algorithm/rmq_pm1_with_index.hpp
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
documentation_of: library/datastructure/sparse_table.hpp
layout: document
title: Sparse Table
---
## Sparse Table