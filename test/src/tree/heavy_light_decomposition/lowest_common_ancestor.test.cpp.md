---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
  - icon: ':question:'
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
  bundledCode: "#line 1 \"test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#line 1 \"library/tree/heavy_light_decomposition.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 5 \"\
    library/tree/heavy_light_decomposition.hpp\"\n#include <vector>\n\nnamespace suisen\
    \ {\nclass HeavyLightDecomposition {\n    public:\n        template <typename\
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
    \ update_query(visit[u]);\n        }\n    private:\n        const int n, root;\n\
    \        std::vector<int> visit, leave, head, ord, siz, par;\n        int dfs(Graph\
    \ &g, int u, int p) {\n            par[u] = p;\n            siz[u] = 1;\n    \
    \        int max_size = 0;\n            for (int &v : g[u]) {\n              \
    \  if (v == p) continue;\n                siz[u] += dfs(g, v, u);\n          \
    \      if (max_size < siz[v]) {\n                    max_size = siz[v];\n    \
    \                std::swap(g[u].front(), v);\n                }\n            }\n\
    \            return siz[u];\n        }\n        void hld(Graph &g, int u, int\
    \ p, int &time) {\n            visit[u] = time, ord[time] = u, ++time;\n     \
    \       head[u] = p >= 0 and g[p].front() == u ? head[p] : u;\n            for\
    \ (int v : g[u]) {\n                if (v != p) hld(g, v, u, time);\n        \
    \    }\n            leave[u] = time;\n        }\n};\n} // namespace suisen\n\n\
    \n#line 6 \"test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp\"\
    \nusing suisen::HeavyLightDecomposition;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >>\
    \ p;\n        g[i].push_back(p);\n        g[p].push_back(i);\n    }\n    HeavyLightDecomposition\
    \ hld(g);\n    for (int i = 0; i < q; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        std::cout << hld.lca(u, v) << '\\n';\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#include \"library/tree/heavy_light_decomposition.hpp\"\nusing suisen::HeavyLightDecomposition;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>> g(n);\n\
    \    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n \
    \       g[i].push_back(p);\n        g[p].push_back(i);\n    }\n    HeavyLightDecomposition\
    \ hld(g);\n    for (int i = 0; i < q; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        std::cout << hld.lca(u, v) << '\\n';\n    }\n    return\
    \ 0;\n}"
  dependsOn:
  - library/tree/heavy_light_decomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2021-08-02 17:38:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
- /verify/test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp.html
title: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
---