---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
  bundledCode: "#line 1 \"test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n#include <atcoder/lazysegtree>\n#line 1 \"library/tree/heavy_light_decomposition.hpp\"\
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
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 5 \"library/tree/heavy_light_decomposition.hpp\"\
    \n#include <vector>\n\nnamespace suisen {\nclass HeavyLightDecomposition {\n \
    \   public:\n        template <typename Q>\n        using is_point_update_query\
    \ = std::is_invocable<Q, int>;\n        template <typename Q>\n        using is_range_update_query\
    \ = std::is_invocable<Q, int, int>;\n        template <typename Q, typename T>\n\
    \        using is_point_get_query  = std::is_same<std::invoke_result_t<Q, int>,\
    \ T>;\n        template <typename Q, typename T>\n        using is_range_fold_query\
    \ = std::is_same<std::invoke_result_t<Q, int, int>, T>;\n\n        using Graph\
    \ = std::vector<std::vector<int>>;\n\n        HeavyLightDecomposition(Graph &g,\
    \ int root = 0) : n(g.size()), root(root), visit(n), leave(n), head(n), ord(n),\
    \ siz(n), par(n) {\n            dfs(g, root, -1);\n            int time = 0;\n\
    \            hld(g, root, -1, time);\n        }\n        int lca(int u, int v)\
    \ {\n            for (;; v = par[head[v]]) {\n                if (visit[u] > visit[v])\
    \ std::swap(u, v);\n                if (head[u] == head[v]) return u;\n      \
    \      }\n        }\n        int la(int u, int k, int default_value = -1) {\n\
    \            for (int h = head[u]; u >= 0; u = par[h], h = head[u]) {\n      \
    \          if (visit[u] - k >= visit[h]) return ord[visit[u] - k];\n         \
    \       k -= visit[u] - visit[h] + 1;\n            }\n            return default_value;\n\
    \        }\n        template <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q,\
    \ T>, is_bin_op<F, T>> = nullptr>\n        T fold_path(int u, int v, T identity,\
    \ F bin_op, Q fold_query, bool is_edge_query = false) {\n            T res = identity;\n\
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
    \n#line 6 \"test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp\"\
    \n\nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n#include <atcoder/lazysegtree>\n#include \"library/tree/heavy_light_decomposition.hpp\"\
    \n\nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/tree/heavy_light_decomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
- /verify/test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp.html
title: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
---
