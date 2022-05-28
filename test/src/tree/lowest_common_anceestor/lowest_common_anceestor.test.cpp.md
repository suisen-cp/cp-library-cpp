---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/rmq_pm1_with_index.hpp
    title: "\u96A3\u63A5\u8981\u7D20\u306E\u5DEE\u304C $\\pm 1$ \u306E\u5834\u5408\
      \u306E RMQ (\u6DFB\u5B57\u306E\u5FA9\u5143\u4ED8\u304D)"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: library/tree/lowest_common_ancestor.hpp
    title: Lowest Common Ancestor
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
    \ suisen\n\n\n#line 10 \"library/algorithm/rmq_pm1_with_index.hpp\"\n\nnamespace\
    \ suisen {\n\n    template <bool is_min_query = true>\n    class RMQpm1WithIndex\
    \ {\n        static constexpr typename std::conditional_t<is_min_query, std::less<std::pair<int,\
    \ int>>, std::greater<std::pair<int, int>>> comp{};\n        static constexpr\
    \ typename std::conditional_t<is_min_query, std::less<int>, std::greater<int>>\
    \ comp_val{};\n\n        static constexpr std::pair<int, int> op(std::pair<int,\
    \ int> x, std::pair<int, int> y) {\n            return comp(x, y) ? x : y;\n \
    \       }\n        static constexpr std::pair<int, int> e() {\n            if\
    \ constexpr (is_min_query) {\n                return { std::numeric_limits<int>::max(),\
    \ -1 };\n            } else {\n                return { std::numeric_limits<int>::min(),\
    \ -1 };\n            }\n        }\n\n        static constexpr int LOG = 4;\n \
    \       static constexpr int SIZE = 1 << LOG;\n\n        static constexpr class\
    \ S {\n        public:\n            int prd[1 << RMQpm1WithIndex<is_min_query>::SIZE];\n\
    \            int arg[1 << RMQpm1WithIndex<is_min_query>::SIZE];\n            constexpr\
    \ S() : prd(), arg(), sum() {\n                prd[is_min_query] = sum[is_min_query]\
    \ = -1, prd[not is_min_query] = sum[not is_min_query] = 1;\n                arg[is_min_query]\
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
    \            }\n        } tabs{};\n\n    public:\n        RMQpm1WithIndex(std::vector<int>&&\
    \ x) : n(x.size()), m((n + SIZE - 1) >> LOG), a(std::move(x)), b(m, 0), tabl(build())\
    \ {}\n        RMQpm1WithIndex(const std::vector<int>& x) : RMQpm1WithIndex(std::vector<int>(x))\
    \ {}\n\n        std::pair<int, int> operator()(int l, int r) const {\n       \
    \     if (l >= r) return e();\n            static constexpr int MASK = SIZE -\
    \ 1;\n            auto f = [this](int l, int r) -> std::pair<int, int> {\n   \
    \             if (l >= r) return e();\n                int idx = cut(b[l >> LOG],\
    \ l & MASK, ((r - 1) & MASK) + 1);\n                return { a[l] + tabs.prd[idx],\
    \ l + tabs.arg[idx] };\n            };\n            if (l >> LOG == (r - 1) >>\
    \ LOG) return f(l, r);\n            int spl = (l + SIZE - 1) >> LOG, spr = r >>\
    \ LOG;\n            return op(op(f(l, spl << LOG), f(spr << LOG, r)), tabl(spl,\
    \ spr));\n        }\n\n    private:\n        int n, m;\n        std::vector<int>\
    \ a;\n        std::vector<std::uint16_t> b;\n        SparseTable<std::pair<int,\
    \ int>, op, e> tabl;\n\n        std::vector<std::pair<int, int>> build() {\n \
    \           std::vector<std::pair<int, int>> c(m, e());\n            if (n ==\
    \ 0) return c;\n            std::pair<int, int> p{ a[0] - 1, -1 };\n         \
    \   for (int i = 0; i < n; p = { a[i], i }, ++i) {\n                std::pair<int,\
    \ int> q{ a[i], i };\n                int outer = i >> LOG;\n                c[outer]\
    \ = op(c[outer], q);\n                b[outer] |= comp(q, p) << (i & (SIZE - 1));\n\
    \            }\n            a.insert(a.begin(), a[0] - 1);\n            assert(std::adjacent_find(a.begin(),\
    \ a.end(), [](int x, int y) { return std::abs(x - y) != 1; }) == a.end());\n \
    \           return c;\n        }\n\n        static constexpr std::uint16_t cut(const\
    \ std::uint16_t bits, const int l, const int r) {\n            return std::uint16_t(bits\
    \ << (SIZE - r)) >> (SIZE - r + l);\n        }\n    };\n} // namespace suisen\n\
    \n\n#line 5 \"library/tree/lowest_common_ancestor.hpp\"\n\nnamespace suisen {\n\
    class LowestCommonAncestor {\n    public:\n        LowestCommonAncestor(const\
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
  isVerificationFile: true
  path: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
  requiredBy: []
  timestamp: '2022-05-29 02:48:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
- /verify/test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp.html
title: test/src/tree/lowest_common_anceestor/lowest_common_anceestor.test.cpp
---
