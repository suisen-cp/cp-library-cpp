---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
    title: test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 2 \"\
    library/tree/HeavyLightDecomposition.hpp\"\n#include <vector>\n\nnamespace suisen\
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
    \ T>> = nullptr>\n        T fold_subtree(int u, Q fold_query) {\n            return\
    \ fold_query(visit[u], leave[u]);\n        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_subtree(int u, Q update_query) {\n         \
    \   update_query(visit[u], leave[u]);\n        }\n        template <typename T,\
    \ typename Q, constraints_t<is_point_get_query<Q, T>> = nullptr>\n        T get_point(int\
    \ u, Q get_query) {\n            return get_query(visit[u]);\n        }\n    \
    \    template <typename Q, constraints_t<is_point_update_query<Q>> = nullptr>\n\
    \        void update_point(int u, Q update_query) {\n            update_query(visit[u]);\n\
    \        }\n    private:\n        const int n, root;\n        std::vector<int>\
    \ visit, leave, head, ord, siz, par;\n        int dfs(Graph &g, int u, int p)\
    \ {\n            par[u] = p;\n            siz[u] = 1;\n            int max_size\
    \ = 0;\n            for (int &v : g[u]) {\n                if (v == p) continue;\n\
    \                siz[u] += dfs(g, v, u);\n                if (max_size < siz[v])\
    \ {\n                    max_size = siz[v];\n                    std::swap(g[u].front(),\
    \ v);\n                }\n            }\n            return siz[u];\n        }\n\
    \        void hld(Graph &g, int u, int p, int &time) {\n            visit[u] =\
    \ time, ord[time] = u, ++time;\n            head[u] = p >= 0 and g[p].front()\
    \ == u ? head[p] : u;\n            for (int v : g[u]) {\n                if (v\
    \ != p) hld(g, v, u, time);\n            }\n            leave[u] = time;\n   \
    \     }\n};\n} // namespace suisen\n"
  code: "#include \"library/type_traits/type_traits.hpp\"\n#include <vector>\n\nnamespace\
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
    \ T>> = nullptr>\n        T fold_subtree(int u, Q fold_query) {\n            return\
    \ fold_query(visit[u], leave[u]);\n        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_subtree(int u, Q update_query) {\n         \
    \   update_query(visit[u], leave[u]);\n        }\n        template <typename T,\
    \ typename Q, constraints_t<is_point_get_query<Q, T>> = nullptr>\n        T get_point(int\
    \ u, Q get_query) {\n            return get_query(visit[u]);\n        }\n    \
    \    template <typename Q, constraints_t<is_point_update_query<Q>> = nullptr>\n\
    \        void update_point(int u, Q update_query) {\n            update_query(visit[u]);\n\
    \        }\n    private:\n        const int n, root;\n        std::vector<int>\
    \ visit, leave, head, ord, siz, par;\n        int dfs(Graph &g, int u, int p)\
    \ {\n            par[u] = p;\n            siz[u] = 1;\n            int max_size\
    \ = 0;\n            for (int &v : g[u]) {\n                if (v == p) continue;\n\
    \                siz[u] += dfs(g, v, u);\n                if (max_size < siz[v])\
    \ {\n                    max_size = siz[v];\n                    std::swap(g[u].front(),\
    \ v);\n                }\n            }\n            return siz[u];\n        }\n\
    \        void hld(Graph &g, int u, int p, int &time) {\n            visit[u] =\
    \ time, ord[time] = u, ++time;\n            head[u] = p >= 0 and g[p].front()\
    \ == u ? head[p] : u;\n            for (int v : g[u]) {\n                if (v\
    \ != p) hld(g, v, u, time);\n            }\n            leave[u] = time;\n   \
    \     }\n};\n} // namespace suisen"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/tree/HeavyLightDecomposition.hpp
  requiredBy:
  - test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
  timestamp: '2021-07-16 04:04:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/HeavyLightDecomposition.hpp
layout: document
redirect_from:
- /library/library/tree/HeavyLightDecomposition.hpp
- /library/library/tree/HeavyLightDecomposition.hpp.html
title: library/tree/HeavyLightDecomposition.hpp
---
