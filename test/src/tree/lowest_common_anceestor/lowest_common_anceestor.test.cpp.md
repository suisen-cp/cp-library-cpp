---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/rmq_pm1_with_index.hpp
    title: library/algorithm/rmq_pm1_with_index.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_table.hpp
    title: library/datastructure/sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: library/tree/lowest_common_ancestor.hpp
    title: library/tree/lowest_common_ancestor.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#line 1 \"library/tree/lowest_common_ancestor.hpp\"\n\n\n\n#line 1 \"library/algorithm/rmq_pm1_with_index.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <cmath>\n#include <algorithm>\n\
    \n#line 1 \"library/datastructure/sparse_table.hpp\"\n\n\n\n#include <vector>\n\
    \n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\n\
    using constraints_t = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\n\
    template <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto)\
    \ constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n\
    \        return std::forward<Then>(then);\n    } else {\n        return std::forward<OrElse>(or_else);\n\
    \    }\n}\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 7 \"library/datastructure/sparse_table.hpp\"\
    \n\nnamespace suisen {\ntemplate <typename T, typename Op, constraints_t<is_bin_op<Op,\
    \ T>> = nullptr>\nclass SparseTable {\n    public:\n        SparseTable() {}\n\
    \        SparseTable(std::vector<T> &&a, T e, Op op) : n(a.size()), log(floor_log2(n)),\
    \ e(e), op(op), table(log + 1), flog(n + 1, 0) {\n            build_table(std::move(a));\n\
    \            build_flog_table();\n        }\n        SparseTable(const std::vector<T>\
    \ &a, T e, Op op) : SparseTable(std::vector<T>(a), e, op) {}\n        T operator()(int\
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
    \ suisen\n\n\n#line 10 \"library/algorithm/rmq_pm1_with_index.hpp\"\n\nnamespace\
    \ suisen {\n\ntemplate <bool is_min_query = true>\nclass RMQpm1WithIndex {\n \
    \   static constexpr typename std::conditional_t<is_min_query, std::less<std::pair<int,\
    \ int>>, std::greater<std::pair<int, int>>> comp {};\n    static constexpr typename\
    \ std::conditional_t<is_min_query, std::less<int>, std::greater<int>> comp_val\
    \ {};\n    static constexpr std::pair<int, int> e = { is_min_query ? std::numeric_limits<int>::max()\
    \ : std::numeric_limits<int>::min(), -1 };\n    static constexpr auto op = [](const\
    \ std::pair<int, int> &x, const std::pair<int, int> &y) { return comp(x, y) ?\
    \ x : y ; };\n    \n    static constexpr int LOG = 4;\n    static constexpr int\
    \ SIZE = 1 << LOG;\n\n    static constexpr class S {\n        public:\n      \
    \      int prd[1 << RMQpm1WithIndex<is_min_query>::SIZE];\n            int arg[1\
    \ << RMQpm1WithIndex<is_min_query>::SIZE];\n            constexpr S() : prd(),\
    \ arg(), sum() {\n                prd[is_min_query] = sum[is_min_query] = -1,\
    \ prd[not is_min_query] = sum[not is_min_query] = 1;\n                arg[is_min_query]\
    \ = arg[not is_min_query] = 0;\n                for (int n = 2; n <= RMQpm1WithIndex<is_min_query>::SIZE;\
    \ n <<= 1) {\n                    for (int s = (1 << n) - 1; s >= 0; --s) merge(s,\
    \ n >> 1);\n                }\n            }\n        private:\n            int\
    \ sum[1 << RMQpm1WithIndex<is_min_query>::SIZE];\n            constexpr void merge(int\
    \ s, int half) {\n                int upper = s >> half, lower = s ^ (upper <<\
    \ half);\n                if (RMQpm1WithIndex<is_min_query>::comp_val(prd[lower],\
    \ sum[lower] + prd[upper])) {\n                    prd[s] = prd[lower];\n    \
    \                arg[s] = arg[lower];\n                } else {\n            \
    \        prd[s] = sum[lower] + prd[upper];\n                    arg[s] = half\
    \ + arg[upper];\n                }\n                sum[s] = sum[lower] + sum[upper];\n\
    \            }\n    } tabs {};\n\n    public:\n        RMQpm1WithIndex(std::vector<int>\
    \ &&x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build(),\
    \ e, op) {}\n        RMQpm1WithIndex(const std::vector<int> &x) : RMQpm1WithIndex(std::vector<int>(x))\
    \ {}\n\n        std::pair<int, int> operator()(int l, int r) const {\n       \
    \     if (l >= r) return e;\n            static constexpr int MASK = SIZE - 1;\n\
    \            auto f = [this](int l, int r) -> std::pair<int, int> {\n        \
    \        if (l >= r) return e;\n                int idx = cut(b[l >> LOG], l &\
    \ MASK, ((r - 1) & MASK) + 1);\n                return { a[l] + tabs.prd[idx],\
    \ l + tabs.arg[idx] };\n            };\n            if (l >> LOG == (r - 1) >>\
    \ LOG) return f(l, r);\n            int spl = (l + SIZE - 1) >> LOG, spr = r >>\
    \ LOG;\n            return op(op(f(l, spl << LOG), f(spr << LOG, r)), tabl(spl,\
    \ spr));\n        }\n        \n    private:\n        int n, m;\n        std::vector<int>\
    \ a;\n        std::vector<std::uint16_t> b;\n        SparseTable<std::pair<int,\
    \ int>, decltype(op)> tabl;\n\n        std::vector<std::pair<int, int>> build()\
    \ {\n            std::vector<std::pair<int, int>> c(m, e);\n            if (n\
    \ == 0) return c;\n            std::pair<int, int> p { a[0] - 1, -1 };\n     \
    \       for (int i = 0; i < n; p = { a[i], i }, ++i) {\n                std::pair<int,\
    \ int> q { a[i], i };\n                int outer = i >> LOG;\n               \
    \ c[outer] = op(c[outer], q);\n                b[outer] |= comp(q, p) << (i &\
    \ (SIZE - 1));\n            }\n            a.insert(a.begin(), a[0] - 1);\n  \
    \          assert(std::adjacent_find(a.begin(), a.end(), [](int x, int y) { return\
    \ std::abs(x - y) != 1; }) == a.end());\n            return c;\n        }\n\n\
    \        static std::uint16_t cut(const std::uint16_t bits, const int l, const\
    \ int r) {\n            return std::uint16_t(bits << (SIZE - r)) >> (SIZE - r\
    \ + l);\n        }\n};\n} // namespace suisen\n\n\n#line 5 \"library/tree/lowest_common_ancestor.hpp\"\
    \n\nnamespace suisen {\nclass LowestCommonAncestor {\n    public:\n        LowestCommonAncestor(const\
    \ std::vector<std::vector<int>> &g, int root = 0) : idx(g.size()), dep(2 * g.size()\
    \ - 1), tour(2 * g.size() - 1), rmq(dfs(g, root)) {}\n\n        int lca(int u,\
    \ int v) const { return idx[u] <= idx[v] ? tour[rmq(idx[u], idx[v] + 1).second]\
    \ : lca(v, u); }\n        int dist(int u, int v) const { return dep[idx[u]] +\
    \ dep[idx[v]] - 2 * dep[idx[operator()(u, v)]]; }\n        int operator()(int\
    \ u, int v) const { return lca(u, v); }\n    private:\n        std::vector<int>\
    \ idx, dep, tour;\n        RMQpm1WithIndex<true> rmq;\n\n        std::vector<int>&\
    \ dfs(const std::vector<std::vector<int>> &g, int root) {\n            int k =\
    \ 0;\n            auto rec = [&](auto self, int u, int p, int d) -> void {\n \
    \               dep[k] = d, tour[idx[u] = k++] = u;\n                for (int\
    \ v : g[u]) if (v != p) self(self, v, u, d + 1);\n                if (p >= 0)\
    \ {\n                    dep[k] = d - 1, tour[idx[p] = k++] = p;\n           \
    \     }\n            };\n            rec(rec, root, -1, 0);\n            return\
    \ dep;\n        }\n};\n} // namespace suisen\n\n\n\n#line 6 \"test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp\"\
    \nusing suisen::LowestCommonAncestor;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >>\
    \ p;\n        g[i].push_back(p);\n        g[p].push_back(i);\n    }\n    LowestCommonAncestor\
    \ lca(g);\n    for (int i = 0; i < q; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        std::cout << lca(u, v) << '\\n';\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#include \"library/tree/lowest_common_ancestor.hpp\"\nusing suisen::LowestCommonAncestor;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>> g(n);\n\
    \    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n \
    \       g[i].push_back(p);\n        g[p].push_back(i);\n    }\n    LowestCommonAncestor\
    \ lca(g);\n    for (int i = 0; i < q; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        std::cout << lca(u, v) << '\\n';\n    }\n    return 0;\n\
    }"
  dependsOn:
  - library/tree/lowest_common_ancestor.hpp
  - library/algorithm/rmq_pm1_with_index.hpp
  - library/datastructure/sparse_table.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
  requiredBy: []
  timestamp: '2021-11-23 23:32:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
- /verify/test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp.html
title: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
---