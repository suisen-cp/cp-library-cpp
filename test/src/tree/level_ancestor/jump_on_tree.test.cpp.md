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
    path: library/tree/level_ancestor.hpp
    title: Level Ancestor
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
    PROBLEM: https://judge.yosupo.jp/problem/jump_on_tree
    links:
    - https://judge.yosupo.jp/problem/jump_on_tree
  bundledCode: "#line 1 \"test/src/tree/level_ancestor/jump_on_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include <iostream>\n\
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
    \ dep;\n        }\n};\n} // namespace suisen\n\n\n\n#line 1 \"library/tree/level_ancestor.hpp\"\
    \n\n\n\n#line 6 \"library/tree/level_ancestor.hpp\"\n\nnamespace suisen {\n  \
    \  struct LevelAncestor {\n        LevelAncestor() = default;\n        LevelAncestor(const\
    \ std::vector<std::vector<int>>& g, const int root = 0)\n            : _n(g.size()),\
    \ _visit_time(_n), _visit_time_inv(_n), _depth(_n), _count(_n + 1), _bucket(_n)\
    \ {\n            build(g, root);\n        }\n\n        int query(const int u,\
    \ const int k) const {\n            if (k < 0 or k > _depth[u]) return -1;\n \
    \           const int d = _depth[u] - k;\n            const auto it_l = _bucket.begin()\
    \ + _count[d], it_r = _bucket.begin() + _count[d + 1];\n            const int\
    \ visit_time_u = _visit_time[u];\n            const int visit_time_v = *std::prev(std::upper_bound(it_l,\
    \ it_r, visit_time_u));\n            return _visit_time_inv[visit_time_v];\n \
    \       }\n\n        int operator()(const int u, const int k) const {\n      \
    \      return query(u, k);\n        }\n\n        int get_visit_time(const int\
    \ u)     const { return _visit_time[u]; }\n        int get_visit_time_inv(const\
    \ int t) const { return _visit_time_inv[t]; }\n        int get_kth_visited(const\
    \ int k)    const { return _visit_time_inv[k]; }\n        int get_depth(const\
    \ int u)          const { return _depth[u]; }\n\n    private:\n        int _n;\n\
    \        std::vector<int> _visit_time;     // vertex -> time\n        std::vector<int>\
    \ _visit_time_inv; // time   -> vertex\n        std::vector<int> _depth;     \
    \     // vertex -> depth\n        std::vector<int> _count;          // the leftmost\
    \ index of the i'th block in the `_bucket`\n        std::vector<int> _bucket;\
    \         // [|dep=0|dep=1|dep=2|...|dep=n-1|]. Each block contains the visited\
    \ times in ascending order.\n\n        void build(const std::vector<std::vector<int>>&\
    \ g, const int root) {\n            int time = 0;\n            auto dfs = [&](auto\
    \ dfs, int u, int p) -> void {\n                _visit_time[u] = time;\n     \
    \           _visit_time_inv[time] = u;\n                ++time;\n            \
    \    ++_count[_depth[u] + 1];\n                for (int v : g[u]) if (v != p)\
    \ {\n                    _depth[v] = _depth[u] + 1;\n                    dfs(dfs,\
    \ v, u);\n                }\n            };\n            dfs(dfs, root, -1);\n\
    \n            for (int i = 0; i < _n; ++i) _count[i + 1] += _count[i];\n     \
    \       auto index = _count;\n            for (int v : _visit_time_inv) _bucket[index[_depth[v]]++]\
    \ = _visit_time[v];\n        }\n    };\n} // namespace suisen\n\n\n\n#line 7 \"\
    test/src/tree/level_ancestor/jump_on_tree.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\n\
    \    suisen::LowestCommonAncestor lca(g);\n    suisen::LevelAncestor la(g);\n\n\
    \    while (q --> 0) {\n        int u, v, d;\n        std::cin >> u >> v >> d;\n\
    \n        const int a = lca(u, v);\n        const int du = la.get_depth(u) - la.get_depth(a);\n\
    \        const int dv = la.get_depth(v) - la.get_depth(a);\n        if (d <= du)\
    \ {\n            std::cout << la(u, d) << '\\n';\n        } else if (d <= du +\
    \ dv) {\n            std::cout << la(v, du + dv - d) << '\\n';\n        } else\
    \ {\n            std::cout << -1 << '\\n';\n        }\n    }\n    \n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include\
    \ <iostream>\n\n#include \"library/tree/lowest_common_ancestor.hpp\"\n#include\
    \ \"library/tree/level_ancestor.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\n\
    \    suisen::LowestCommonAncestor lca(g);\n    suisen::LevelAncestor la(g);\n\n\
    \    while (q --> 0) {\n        int u, v, d;\n        std::cin >> u >> v >> d;\n\
    \n        const int a = lca(u, v);\n        const int du = la.get_depth(u) - la.get_depth(a);\n\
    \        const int dv = la.get_depth(v) - la.get_depth(a);\n        if (d <= du)\
    \ {\n            std::cout << la(u, d) << '\\n';\n        } else if (d <= du +\
    \ dv) {\n            std::cout << la(v, du + dv - d) << '\\n';\n        } else\
    \ {\n            std::cout << -1 << '\\n';\n        }\n    }\n    \n    return\
    \ 0;\n}"
  dependsOn:
  - library/tree/lowest_common_ancestor.hpp
  - library/algorithm/rmq_pm1_with_index.hpp
  - library/datastructure/sparse_table.hpp
  - library/tree/level_ancestor.hpp
  isVerificationFile: true
  path: test/src/tree/level_ancestor/jump_on_tree.test.cpp
  requiredBy: []
  timestamp: '2022-07-26 15:09:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/level_ancestor/jump_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/level_ancestor/jump_on_tree.test.cpp
- /verify/test/src/tree/level_ancestor/jump_on_tree.test.cpp.html
title: test/src/tree/level_ancestor/jump_on_tree.test.cpp
---
