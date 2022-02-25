---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n\n#include <iostream>\n#include <atcoder/segtree>\n#include <atcoder/modint>\n\
    \nusing mint = atcoder::modint998244353;\n\n#line 1 \"library/tree/heavy_light_decomposition.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ 5 \"library/tree/heavy_light_decomposition.hpp\"\n#include <vector>\n\nnamespace\
    \ suisen {\nclass HeavyLightDecomposition {\n    public:\n        template <typename\
    \ Q>\n        using is_point_update_query = std::is_invocable<Q, int>;\n     \
    \   template <typename Q>\n        using is_range_update_query = std::is_invocable<Q,\
    \ int, int>;\n        template <typename Q, typename T>\n        using is_point_get_query\
    \  = std::is_same<std::invoke_result_t<Q, int>, T>;\n        template <typename\
    \ Q, typename T>\n        using is_range_fold_query = std::is_same<std::invoke_result_t<Q,\
    \ int, int>, T>;\n\n        using Graph = std::vector<std::vector<int>>;\n\n \
    \       HeavyLightDecomposition(Graph &g, int root = 0) : n(g.size()), root(root),\
    \ visit(n), leave(n), head(n), ord(n), siz(n), par(n) {\n            dfs(g, root,\
    \ -1);\n            int time = 0;\n            hld(g, root, -1, time);\n     \
    \   }\n        int lca(int u, int v) {\n            for (;; v = par[head[v]])\
    \ {\n                if (visit[u] > visit[v]) std::swap(u, v);\n             \
    \   if (head[u] == head[v]) return u;\n            }\n        }\n        int la(int\
    \ u, int k, int default_value = -1) {\n            for (int h = head[u]; u >=\
    \ 0; u = par[h], h = head[u]) {\n                if (visit[u] - k >= visit[h])\
    \ return ord[visit[u] - k];\n                k -= visit[u] - visit[h] + 1;\n \
    \           }\n            return default_value;\n        }\n        template\
    \ <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q, T>,\
    \ is_bin_op<F, T>> = nullptr>\n        T fold_path(int u, int v, T identity, F\
    \ bin_op, Q fold_query, bool is_edge_query = false) {\n            T res = identity;\n\
    \            for (;; v = par[head[v]]) {\n                if (visit[u] > visit[v])\
    \ std::swap(u, v);\n                if (head[u] == head[v]) break;\n         \
    \       res = bin_op(fold_query(visit[head[v]], visit[v] + 1), res);\n       \
    \     }\n            return bin_op(fold_query(visit[u] + is_edge_query, visit[v]\
    \ + 1), res);\n        }\n        template <\n            typename T, typename\
    \ Q1, typename Q2, typename F,\n            constraints_t<is_range_fold_query<Q1,\
    \ T>, is_range_fold_query<Q2, T>, is_bin_op<F, T>> = nullptr\n        >\n    \
    \    T fold_path_noncommutative(int u, int v, T identity, F bin_op, Q1 fold_query,\
    \ Q2 fold_query_rev, bool is_edge_query = false) {\n            T res_u = identity,\
    \ res_v = identity;\n            // a := lca(u, v)\n            // res = fold(u\
    \ -> a) + fold(a -> v)\n            while (head[u] != head[v]) {\n           \
    \     if (visit[u] < visit[v]) { // a -> v\n                    res_v = bin_op(fold_query(visit[head[v]],\
    \ visit[v] + 1), res_v);\n                    v = par[head[v]];\n            \
    \    } else { // u -> a\n                    res_u = bin_op(res_u, fold_query_rev(visit[head[u]],\
    \ visit[u] + 1));\n                    u = par[head[u]];\n                }\n\
    \            }\n            if (visit[u] < visit[v]) { // a = u\n            \
    \    res_v = bin_op(fold_query(visit[u] + is_edge_query, visit[v] + 1), res_v);\n\
    \            } else { // a = v\n                res_u = bin_op(res_u, fold_query_rev(visit[v]\
    \ + is_edge_query, visit[u] + 1));\n            }\n            return bin_op(res_u,\
    \ res_v);\n        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_path(int u, int v, Q update_query, bool is_edge_query\
    \ = false) {\n            for (;; v = par[head[v]]) {\n                if (visit[u]\
    \ > visit[v]) std::swap(u, v);\n                if (head[u] == head[v]) break;\n\
    \                update_query(visit[head[v]], visit[v] + 1);\n            }\n\
    \            update_query(visit[u] + is_edge_query, visit[v] + 1);\n        }\n\
    \        template <typename T, typename Q, constraints_t<is_range_fold_query<Q,\
    \ T>> = nullptr>\n        T fold_subtree(int u, Q fold_query, bool is_edge_query\
    \ = false) {\n            return fold_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_subtree(int u, Q update_query, bool is_edge_query\
    \ = false) {\n            update_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename T, typename Q, constraints_t<is_point_get_query<Q,\
    \ T>> = nullptr>\n        T get_point(int u, Q get_query) {\n            return\
    \ get_query(visit[u]);\n        }\n        template <typename Q, constraints_t<is_point_update_query<Q>>\
    \ = nullptr>\n        void update_point(int u, Q update_query) {\n           \
    \ update_query(visit[u]);\n        }\n        std::vector<int> inv_ids() const\
    \ {\n            std::vector<int> inv(n);\n            for (int i = 0; i < n;\
    \ ++i) inv[visit[i]] = i;\n            return inv;\n        }\n        int get_head(int\
    \ u) const {\n            return head[u];\n        }\n    private:\n        const\
    \ int n, root;\n        std::vector<int> visit, leave, head, ord, siz, par;\n\
    \        int dfs(Graph &g, int u, int p) {\n            par[u] = p;\n        \
    \    siz[u] = 1;\n            int max_size = 0;\n            for (int &v : g[u])\
    \ {\n                if (v == p) continue;\n                siz[u] += dfs(g, v,\
    \ u);\n                if (max_size < siz[v]) {\n                    max_size\
    \ = siz[v];\n                    std::swap(g[u].front(), v);\n               \
    \ }\n            }\n            return siz[u];\n        }\n        void hld(Graph\
    \ &g, int u, int p, int &time) {\n            visit[u] = time, ord[time] = u,\
    \ ++time;\n            head[u] = p >= 0 and g[p].front() == u ? head[p] : u;\n\
    \            for (int v : g[u]) {\n                if (v != p) hld(g, v, u, time);\n\
    \            }\n            leave[u] = time;\n        }\n};\n} // namespace suisen\n\
    \n\n#line 10 \"test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp\"\
    \nusing suisen::HeavyLightDecomposition;\n\nstruct F {\n    mint a, b;\n    F(mint\
    \ a, mint b) : a(a), b(b) {}\n    F() : F(1, 0) {}\n    mint apply(mint x) { return\
    \ a * x + b; }\n};\n\nF op(F f, F g) { return F(g.a * f.a, g.a * f.b + g.b); }\n\
    F op_rev(F f, F g) { return F(f.a * g.a, f.a * g.b + f.b); }\nF e() { return F{};\
    \ }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<F> fs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int a, b;\n        std::cin >> a >> b;\n     \
    \   fs[i] = F(a, b);\n    }\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n    HeavyLightDecomposition\
    \ hld(g);\n    atcoder::segtree<F, op, e> seg(n);\n    atcoder::segtree<F, op_rev,\
    \ e> seg_rev(n);\n    for (int i = 0; i < n; ++i) {\n        hld.update_point(i,\
    \ [&](int v) {\n            seg.set(v, fs[i]);\n            seg_rev.set(v, fs[i]);\n\
    \        });\n    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n     \
    \   std::cin >> t;\n        if (t == 0) {\n            int p, c, d;\n        \
    \    std::cin >> p >> c >> d;\n            hld.update_point(p, [&](int v) {\n\
    \                seg.set(v, F(c, d));\n                seg_rev.set(v, F(c, d));\n\
    \            });\n        } else {\n            int u, v, x;\n            std::cin\
    \ >> u >> v >> x;\n            std::cout << hld.fold_path_noncommutative(\n  \
    \              u, v,\n                F{}, op,\n                [&](int l, int\
    \ r) { return seg.prod(l, r); },\n                [&](int l, int r) { return seg_rev.prod(l,\
    \ r); }\n            ).apply(x).val() << '\\n';\n        }\n        std::cout.flush();\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n\n#include <iostream>\n#include <atcoder/segtree>\n#include <atcoder/modint>\n\
    \nusing mint = atcoder::modint998244353;\n\n#include \"library/tree/heavy_light_decomposition.hpp\"\
    \nusing suisen::HeavyLightDecomposition;\n\nstruct F {\n    mint a, b;\n    F(mint\
    \ a, mint b) : a(a), b(b) {}\n    F() : F(1, 0) {}\n    mint apply(mint x) { return\
    \ a * x + b; }\n};\n\nF op(F f, F g) { return F(g.a * f.a, g.a * f.b + g.b); }\n\
    F op_rev(F f, F g) { return F(f.a * g.a, f.a * g.b + f.b); }\nF e() { return F{};\
    \ }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<F> fs(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int a, b;\n        std::cin >> a >> b;\n     \
    \   fs[i] = F(a, b);\n    }\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n    HeavyLightDecomposition\
    \ hld(g);\n    atcoder::segtree<F, op, e> seg(n);\n    atcoder::segtree<F, op_rev,\
    \ e> seg_rev(n);\n    for (int i = 0; i < n; ++i) {\n        hld.update_point(i,\
    \ [&](int v) {\n            seg.set(v, fs[i]);\n            seg_rev.set(v, fs[i]);\n\
    \        });\n    }\n    for (int i = 0; i < q; ++i) {\n        int t;\n     \
    \   std::cin >> t;\n        if (t == 0) {\n            int p, c, d;\n        \
    \    std::cin >> p >> c >> d;\n            hld.update_point(p, [&](int v) {\n\
    \                seg.set(v, F(c, d));\n                seg_rev.set(v, F(c, d));\n\
    \            });\n        } else {\n            int u, v, x;\n            std::cin\
    \ >> u >> v >> x;\n            std::cout << hld.fold_path_noncommutative(\n  \
    \              u, v,\n                F{}, op,\n                [&](int l, int\
    \ r) { return seg.prod(l, r); },\n                [&](int l, int r) { return seg_rev.prod(l,\
    \ r); }\n            ).apply(x).val() << '\\n';\n        }\n        std::cout.flush();\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - library/tree/heavy_light_decomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
- /verify/test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp.html
title: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
---
