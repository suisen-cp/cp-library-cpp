---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/euler_tour.hpp
    title: Euler Tour
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    \n#include <iostream>\n#include <atcoder/segtree>\n\n#line 1 \"library/tree/euler_tour.hpp\"\
    \n\n\n\n#include <limits>\n#include <vector>\n\nnamespace suisen {\n/**\n * ImplicitGraph\
    \ g : (int u, auto f) -> { for (int v : adjacent(u)) f(v); }\n */\nclass EulerTour\
    \ {\n    public:\n        template <typename ImplicitGraph>\n        EulerTour(const\
    \ ImplicitGraph g, int n, int root = 0) : n(n), m(ceil_pow2(2 * n)) {\n      \
    \      dep.resize(n + 1), visit.resize(n), leave.resize(n);\n            seg.assign(2\
    \ * m, n);\n            dfs(g, root);\n            for (int k = m - 1; k > 0;\
    \ --k) seg[k] = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);\n        }\n   \
    \     template <typename Edge, typename EdgeToNode>\n        EulerTour(const std::vector<std::vector<Edge>>\
    \ &g, const EdgeToNode eton, int root = 0) :\n            EulerTour([&](int u,\
    \ auto f) { for (const Edge &e : g[u]) f(eton(e)); }, g.size(), root) {}\n   \
    \     EulerTour(const std::vector<std::vector<int>> &g, int root = 0) :\n    \
    \        EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(),\
    \ root) {}\n        int lca(int u, int v) const {\n            if (visit[u] >\
    \ visit[v]) return lca(v, u);\n            int res = n;\n            for (int\
    \ l = m + visit[u], r = m + visit[v] + 1; l < r; l >>= 1, r >>= 1) {\n       \
    \         if (l & 1) res = argmin(res, seg[l++]);\n                if (r & 1)\
    \ res = argmin(res, seg[--r]);\n            }\n            return res;\n     \
    \   }\n        inline int dist(int u, int v) const { return dep[u] + dep[v] -\
    \ 2 * dep[lca(u, v)]; }\n        inline int depth(int u) const { return dep[u];\
    \ }\n        inline int visit_time(int u) const { return visit[u]; }\n       \
    \ inline int leave_time(int u) const { return leave[u]; }\n        inline int\
    \ parent(int u) const {\n            int p = seg[m + leave[u]];\n            return\
    \ p == n ? -1 : p;\n        }\n    private:\n        const int n, m;\n       \
    \ std::vector<int> visit, leave, dep, seg;\n        template <typename ImplicitGraph>\n\
    \        void dfs(ImplicitGraph g, int root) {\n            dep[root] = 0, dep[n]\
    \ = std::numeric_limits<int>::max();\n            int k = 0;\n            auto\
    \ f = [&](auto self, int u, int p) -> void {\n                visit[u] = k, seg[m\
    \ + k++] = u;\n                g(u, [&](int v){ if (v != p) dep[v] = dep[u] +\
    \ 1, self(self, v, u); });\n                leave[u] = k, seg[m + k++] = p;\n\
    \            };\n            f(f, root, n);\n        }\n        inline int argmin(int\
    \ u, int v) const { return dep[u] < dep[v] ? u : v; }\n        static int ceil_pow2(const\
    \ int n) {\n            int k = 1;\n            while (k < n) k <<= 1;\n     \
    \       return k;\n        }\n};\n} // namespace suisen\n\n\n#line 7 \"test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp\"\
    \n\nusing suisen::EulerTour;\n\nconstexpr long long op(long long x, long long\
    \ y) { return x + y; }\nconstexpr long long e() { return  0LL; }\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<long long> a(n);\n    for (long\
    \ long &e : a) std::cin >> e;\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n        g[i].push_back(p);\n\
    \        g[p].push_back(i);\n    }\n    EulerTour et(g);\n    atcoder::segtree<long\
    \ long, op, e> seg(2 * n);\n    for (int i = 0; i < n; ++i) {\n        seg.set(et.visit_time(i),\
    \ a[i]);\n    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int u, x;\n            std::cin >>\
    \ u >> x;\n            int vis = et.visit_time(u);\n            seg.set(vis, seg.get(vis)\
    \ + x);\n        } else {\n            int u;\n            std::cin >> u;\n  \
    \          std::cout << seg.prod(et.visit_time(u), et.leave_time(u)) << '\\n';\n\
    \        }\n        std::cout.flush();\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n\n#include <iostream>\n#include <atcoder/segtree>\n\n#include \"library/tree/euler_tour.hpp\"\
    \n\nusing suisen::EulerTour;\n\nconstexpr long long op(long long x, long long\
    \ y) { return x + y; }\nconstexpr long long e() { return  0LL; }\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<long long> a(n);\n    for (long\
    \ long &e : a) std::cin >> e;\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n        g[i].push_back(p);\n\
    \        g[p].push_back(i);\n    }\n    EulerTour et(g);\n    atcoder::segtree<long\
    \ long, op, e> seg(2 * n);\n    for (int i = 0; i < n; ++i) {\n        seg.set(et.visit_time(i),\
    \ a[i]);\n    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            int u, x;\n            std::cin >>\
    \ u >> x;\n            int vis = et.visit_time(u);\n            seg.set(vis, seg.get(vis)\
    \ + x);\n        } else {\n            int u;\n            std::cin >> u;\n  \
    \          std::cout << seg.prod(et.visit_time(u), et.leave_time(u)) << '\\n';\n\
    \        }\n        std::cout.flush();\n    }\n    return 0;\n}"
  dependsOn:
  - library/tree/euler_tour.hpp
  isVerificationFile: true
  path: test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2021-07-20 21:04:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp
- /verify/test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp.html
title: test/src/tree/euler_tour/vertex_add_subtree_sum.test.cpp
---
