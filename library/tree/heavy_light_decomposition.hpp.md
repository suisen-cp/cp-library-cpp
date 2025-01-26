---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/tree/auxiliary_tree.hpp
    title: "\u6307\u5B9A\u3055\u308C\u305F\u9802\u70B9\u305F\u3061\u306E\u6700\u5C0F\
      \u5171\u901A\u7956\u5148\u95A2\u4FC2\u3092\u4FDD\u3063\u3066\u6728\u3092\u5727\
      \u7E2E\u3057\u3066\u3067\u304D\u308B\u88DC\u52A9\u7684\u306A\u6728"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
    title: test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/jump_on_tree.test.cpp
    title: test/src/tree/heavy_light_decomposition/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/la_based_lowest_common_ancestor.test.cpp
    title: test/src/tree/heavy_light_decomposition/la_based_lowest_common_ancestor.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
    title: test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
    title: test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/heavy_light_decomposition.hpp\"\n\n\n\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <iostream>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename\
    \ ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 5 \"library/tree/heavy_light_decomposition.hpp\"\
    \n#include <vector>\n\nnamespace suisen {\nclass HeavyLightDecomposition {\n \
    \   public:\n        template <typename Q>\n        using is_point_update_query\
    \ = std::is_invocable<Q, int>;\n        template <typename Q>\n        using is_range_update_query\
    \ = std::is_invocable<Q, int, int>;\n        template <typename Q, typename T>\n\
    \        using is_point_get_query  = std::is_same<std::invoke_result_t<Q, int>,\
    \ T>;\n        template <typename Q, typename T>\n        using is_range_fold_query\
    \ = std::is_same<std::invoke_result_t<Q, int, int>, T>;\n\n        using Graph\
    \ = std::vector<std::vector<int>>;\n\n        HeavyLightDecomposition() = default;\n\
    \        HeavyLightDecomposition(Graph &g) : n(g.size()), visit(n), leave(n),\
    \ head(n), ord(n), siz(n), par(n, -1), dep(n, 0) {\n            for (int i = 0;\
    \ i < n; ++i) if (par[i] < 0) dfs(g, i, -1);\n            int time = 0;\n    \
    \        for (int i = 0; i < n; ++i) if (par[i] < 0) hld(g, i, -1, time);\n  \
    \      }\n        HeavyLightDecomposition(Graph &g, const std::vector<int> &roots)\
    \ : n(g.size()), visit(n), leave(n), head(n), ord(n), siz(n), par(n, -1), dep(n,\
    \ 0) {\n            for (int i : roots) dfs(g, i, -1);\n            int time =\
    \ 0;\n            for (int i : roots) hld(g, i, -1, time);\n        }\n      \
    \  int size() const {\n            return n;\n        }\n        int lca(int u,\
    \ int v) const {\n            for (;; v = par[head[v]]) {\n                if\
    \ (visit[u] > visit[v]) std::swap(u, v);\n                if (head[u] == head[v])\
    \ return u;\n            }\n        }\n        int la(int u, int k, int default_value\
    \ = -1) const {\n            if (k < 0) return default_value;\n            while\
    \ (u >= 0) {\n                int h = head[u];\n                if (visit[u] -\
    \ k >= visit[h]) return ord[visit[u] - k];\n                k -= visit[u] - visit[h]\
    \ + 1;\n                u = par[h];\n            }\n            return default_value;\n\
    \        }\n        int jump(int u, int v, int d, int default_value = -1) const\
    \ {\n            if (d < 0) return default_value;\n            const int w = lca(u,\
    \ v);\n            int uw = dep[u] - dep[w];\n            if (d <= uw) return\
    \ la(u, d);\n            int vw = dep[v] - dep[w];\n            return d <= uw\
    \ + vw ? la(v, (uw + vw) - d) : default_value;\n        }\n        int dist(int\
    \ u, int v) const {\n            return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n\
    \        }\n        template <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q,\
    \ T>, std::is_invocable_r<T, F, T, T>> = nullptr>\n        T fold_path(int u,\
    \ int v, T identity, F bin_op, Q fold_query, bool is_edge_query = false) const\
    \ {\n            T res = identity;\n            for (;; v = par[head[v]]) {\n\
    \                if (visit[u] > visit[v]) std::swap(u, v);\n                if\
    \ (head[u] == head[v]) break;\n                res = bin_op(fold_query(visit[head[v]],\
    \ visit[v] + 1), res);\n            }\n            return bin_op(fold_query(visit[u]\
    \ + is_edge_query, visit[v] + 1), res);\n        }\n        template <\n     \
    \       typename T, typename Q1, typename Q2, typename F,\n            constraints_t<is_range_fold_query<Q1,\
    \ T>, is_range_fold_query<Q2, T>, std::is_invocable_r<T, F, T, T>> = nullptr\n\
    \        >\n        T fold_path_noncommutative(int u, int v, T identity, F bin_op,\
    \ Q1 fold_query, Q2 fold_query_rev, bool is_edge_query = false) const {\n    \
    \        T res_u = identity, res_v = identity;\n            // a := lca(u, v)\n\
    \            // res = fold(u -> a) + fold(a -> v)\n            while (head[u]\
    \ != head[v]) {\n                if (visit[u] < visit[v]) { // a -> v\n      \
    \              res_v = bin_op(fold_query(visit[head[v]], visit[v] + 1), res_v);\n\
    \                    v = par[head[v]];\n                } else { // u -> a\n \
    \                   res_u = bin_op(res_u, fold_query_rev(visit[head[u]], visit[u]\
    \ + 1));\n                    u = par[head[u]];\n                }\n         \
    \   }\n            if (visit[u] < visit[v]) { // a = u\n                res_v\
    \ = bin_op(fold_query(visit[u] + is_edge_query, visit[v] + 1), res_v);\n     \
    \       } else { // a = v\n                res_u = bin_op(res_u, fold_query_rev(visit[v]\
    \ + is_edge_query, visit[u] + 1));\n            }\n            return bin_op(res_u,\
    \ res_v);\n        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_path(int u, int v, Q update_query, bool is_edge_query\
    \ = false) const {\n            for (;; v = par[head[v]]) {\n                if\
    \ (visit[u] > visit[v]) std::swap(u, v);\n                if (head[u] == head[v])\
    \ break;\n                update_query(visit[head[v]], visit[v] + 1);\n      \
    \      }\n            update_query(visit[u] + is_edge_query, visit[v] + 1);\n\
    \        }\n        template <typename T, typename Q, constraints_t<is_range_fold_query<Q,\
    \ T>> = nullptr>\n        T fold_subtree(int u, Q fold_query, bool is_edge_query\
    \ = false) const {\n            return fold_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_subtree(int u, Q update_query, bool is_edge_query\
    \ = false) const {\n            update_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename T, typename Q, constraints_t<is_point_get_query<Q,\
    \ T>> = nullptr>\n        T get_point(int u, Q get_query) const {\n          \
    \  return get_query(visit[u]);\n        }\n        template <typename Q, constraints_t<is_point_update_query<Q>>\
    \ = nullptr>\n        void update_point(int u, Q update_query) const {\n     \
    \       update_query(visit[u]);\n        }\n        std::vector<int> inv_ids()\
    \ const {\n            std::vector<int> inv(n);\n            for (int i = 0; i\
    \ < n; ++i) inv[visit[i]] = i;\n            return inv;\n        }\n        int\
    \ get_visit_time(int u) const {\n            return visit[u];\n        }\n   \
    \     int get_leave_time(int u) const {\n            return leave[u];\n      \
    \  }\n        int get_head(int u) const {\n            return head[u];\n     \
    \   }\n        int get_kth_visited(int k) const {\n            return ord[k];\n\
    \        }\n        int get_subtree_size(int u) const {\n            return siz[u];\n\
    \        }\n        int get_parent(int u) const {\n            return par[u];\n\
    \        }\n        int get_depth(int u) const {\n            return dep[u];\n\
    \        }\n        std::vector<int> get_roots() const {\n            std::vector<int>\
    \ res;\n            for (int i = 0; i < n; ++i) if (par[i] < 0) res.push_back(i);\n\
    \            return res;\n        }\n    private:\n        int n;\n        std::vector<int>\
    \ visit, leave, head, ord, siz, par, dep;\n        int dfs(Graph &g, int u, int\
    \ p) {\n            par[u] = p;\n            siz[u] = 1;\n            int max_size\
    \ = 0;\n            for (int &v : g[u]) {\n                if (v == p) continue;\n\
    \                dep[v] = dep[u] + 1;\n                siz[u] += dfs(g, v, u);\n\
    \                if (max_size < siz[v]) {\n                    max_size = siz[v];\n\
    \                    std::swap(g[u].front(), v);\n                }\n        \
    \    }\n            return siz[u];\n        }\n        void hld(Graph &g, int\
    \ u, int p, int &time) {\n            visit[u] = time, ord[time] = u, ++time;\n\
    \            head[u] = p >= 0 and g[p].front() == u ? head[p] : u;\n         \
    \   for (int v : g[u]) {\n                if (v != p) hld(g, v, u, time);\n  \
    \          }\n            leave[u] = time;\n        }\n};\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_HLD\n#define SUISEN_HLD\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n#include <vector>\n\nnamespace suisen {\nclass HeavyLightDecomposition {\n \
    \   public:\n        template <typename Q>\n        using is_point_update_query\
    \ = std::is_invocable<Q, int>;\n        template <typename Q>\n        using is_range_update_query\
    \ = std::is_invocable<Q, int, int>;\n        template <typename Q, typename T>\n\
    \        using is_point_get_query  = std::is_same<std::invoke_result_t<Q, int>,\
    \ T>;\n        template <typename Q, typename T>\n        using is_range_fold_query\
    \ = std::is_same<std::invoke_result_t<Q, int, int>, T>;\n\n        using Graph\
    \ = std::vector<std::vector<int>>;\n\n        HeavyLightDecomposition() = default;\n\
    \        HeavyLightDecomposition(Graph &g) : n(g.size()), visit(n), leave(n),\
    \ head(n), ord(n), siz(n), par(n, -1), dep(n, 0) {\n            for (int i = 0;\
    \ i < n; ++i) if (par[i] < 0) dfs(g, i, -1);\n            int time = 0;\n    \
    \        for (int i = 0; i < n; ++i) if (par[i] < 0) hld(g, i, -1, time);\n  \
    \      }\n        HeavyLightDecomposition(Graph &g, const std::vector<int> &roots)\
    \ : n(g.size()), visit(n), leave(n), head(n), ord(n), siz(n), par(n, -1), dep(n,\
    \ 0) {\n            for (int i : roots) dfs(g, i, -1);\n            int time =\
    \ 0;\n            for (int i : roots) hld(g, i, -1, time);\n        }\n      \
    \  int size() const {\n            return n;\n        }\n        int lca(int u,\
    \ int v) const {\n            for (;; v = par[head[v]]) {\n                if\
    \ (visit[u] > visit[v]) std::swap(u, v);\n                if (head[u] == head[v])\
    \ return u;\n            }\n        }\n        int la(int u, int k, int default_value\
    \ = -1) const {\n            if (k < 0) return default_value;\n            while\
    \ (u >= 0) {\n                int h = head[u];\n                if (visit[u] -\
    \ k >= visit[h]) return ord[visit[u] - k];\n                k -= visit[u] - visit[h]\
    \ + 1;\n                u = par[h];\n            }\n            return default_value;\n\
    \        }\n        int jump(int u, int v, int d, int default_value = -1) const\
    \ {\n            if (d < 0) return default_value;\n            const int w = lca(u,\
    \ v);\n            int uw = dep[u] - dep[w];\n            if (d <= uw) return\
    \ la(u, d);\n            int vw = dep[v] - dep[w];\n            return d <= uw\
    \ + vw ? la(v, (uw + vw) - d) : default_value;\n        }\n        int dist(int\
    \ u, int v) const {\n            return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n\
    \        }\n        template <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q,\
    \ T>, std::is_invocable_r<T, F, T, T>> = nullptr>\n        T fold_path(int u,\
    \ int v, T identity, F bin_op, Q fold_query, bool is_edge_query = false) const\
    \ {\n            T res = identity;\n            for (;; v = par[head[v]]) {\n\
    \                if (visit[u] > visit[v]) std::swap(u, v);\n                if\
    \ (head[u] == head[v]) break;\n                res = bin_op(fold_query(visit[head[v]],\
    \ visit[v] + 1), res);\n            }\n            return bin_op(fold_query(visit[u]\
    \ + is_edge_query, visit[v] + 1), res);\n        }\n        template <\n     \
    \       typename T, typename Q1, typename Q2, typename F,\n            constraints_t<is_range_fold_query<Q1,\
    \ T>, is_range_fold_query<Q2, T>, std::is_invocable_r<T, F, T, T>> = nullptr\n\
    \        >\n        T fold_path_noncommutative(int u, int v, T identity, F bin_op,\
    \ Q1 fold_query, Q2 fold_query_rev, bool is_edge_query = false) const {\n    \
    \        T res_u = identity, res_v = identity;\n            // a := lca(u, v)\n\
    \            // res = fold(u -> a) + fold(a -> v)\n            while (head[u]\
    \ != head[v]) {\n                if (visit[u] < visit[v]) { // a -> v\n      \
    \              res_v = bin_op(fold_query(visit[head[v]], visit[v] + 1), res_v);\n\
    \                    v = par[head[v]];\n                } else { // u -> a\n \
    \                   res_u = bin_op(res_u, fold_query_rev(visit[head[u]], visit[u]\
    \ + 1));\n                    u = par[head[u]];\n                }\n         \
    \   }\n            if (visit[u] < visit[v]) { // a = u\n                res_v\
    \ = bin_op(fold_query(visit[u] + is_edge_query, visit[v] + 1), res_v);\n     \
    \       } else { // a = v\n                res_u = bin_op(res_u, fold_query_rev(visit[v]\
    \ + is_edge_query, visit[u] + 1));\n            }\n            return bin_op(res_u,\
    \ res_v);\n        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_path(int u, int v, Q update_query, bool is_edge_query\
    \ = false) const {\n            for (;; v = par[head[v]]) {\n                if\
    \ (visit[u] > visit[v]) std::swap(u, v);\n                if (head[u] == head[v])\
    \ break;\n                update_query(visit[head[v]], visit[v] + 1);\n      \
    \      }\n            update_query(visit[u] + is_edge_query, visit[v] + 1);\n\
    \        }\n        template <typename T, typename Q, constraints_t<is_range_fold_query<Q,\
    \ T>> = nullptr>\n        T fold_subtree(int u, Q fold_query, bool is_edge_query\
    \ = false) const {\n            return fold_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename Q, constraints_t<is_range_update_query<Q>>\
    \ = nullptr>\n        void update_subtree(int u, Q update_query, bool is_edge_query\
    \ = false) const {\n            update_query(visit[u] + is_edge_query, leave[u]);\n\
    \        }\n        template <typename T, typename Q, constraints_t<is_point_get_query<Q,\
    \ T>> = nullptr>\n        T get_point(int u, Q get_query) const {\n          \
    \  return get_query(visit[u]);\n        }\n        template <typename Q, constraints_t<is_point_update_query<Q>>\
    \ = nullptr>\n        void update_point(int u, Q update_query) const {\n     \
    \       update_query(visit[u]);\n        }\n        std::vector<int> inv_ids()\
    \ const {\n            std::vector<int> inv(n);\n            for (int i = 0; i\
    \ < n; ++i) inv[visit[i]] = i;\n            return inv;\n        }\n        int\
    \ get_visit_time(int u) const {\n            return visit[u];\n        }\n   \
    \     int get_leave_time(int u) const {\n            return leave[u];\n      \
    \  }\n        int get_head(int u) const {\n            return head[u];\n     \
    \   }\n        int get_kth_visited(int k) const {\n            return ord[k];\n\
    \        }\n        int get_subtree_size(int u) const {\n            return siz[u];\n\
    \        }\n        int get_parent(int u) const {\n            return par[u];\n\
    \        }\n        int get_depth(int u) const {\n            return dep[u];\n\
    \        }\n        std::vector<int> get_roots() const {\n            std::vector<int>\
    \ res;\n            for (int i = 0; i < n; ++i) if (par[i] < 0) res.push_back(i);\n\
    \            return res;\n        }\n    private:\n        int n;\n        std::vector<int>\
    \ visit, leave, head, ord, siz, par, dep;\n        int dfs(Graph &g, int u, int\
    \ p) {\n            par[u] = p;\n            siz[u] = 1;\n            int max_size\
    \ = 0;\n            for (int &v : g[u]) {\n                if (v == p) continue;\n\
    \                dep[v] = dep[u] + 1;\n                siz[u] += dfs(g, v, u);\n\
    \                if (max_size < siz[v]) {\n                    max_size = siz[v];\n\
    \                    std::swap(g[u].front(), v);\n                }\n        \
    \    }\n            return siz[u];\n        }\n        void hld(Graph &g, int\
    \ u, int p, int &time) {\n            visit[u] = time, ord[time] = u, ++time;\n\
    \            head[u] = p >= 0 and g[p].front() == u ? head[p] : u;\n         \
    \   for (int v : g[u]) {\n                if (v != p) hld(g, v, u, time);\n  \
    \          }\n            leave[u] = time;\n        }\n};\n} // namespace suisen\n\
    \n#endif // SUISEN_HLD\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/tree/heavy_light_decomposition.hpp
  requiredBy:
  - library/tree/auxiliary_tree.hpp
  timestamp: '2024-01-31 02:46:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/heavy_light_decomposition/vertex_add_path_composite.test.cpp
  - test/src/tree/heavy_light_decomposition/lowest_common_ancestor.test.cpp
  - test/src/tree/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
  - test/src/tree/heavy_light_decomposition/jump_on_tree.test.cpp
  - test/src/tree/heavy_light_decomposition/vertex_add_path_sum.test.cpp
  - test/src/tree/heavy_light_decomposition/do_use_segment_tree.test.cpp
  - test/src/tree/heavy_light_decomposition/la_based_lowest_common_ancestor.test.cpp
documentation_of: library/tree/heavy_light_decomposition.hpp
layout: document
title: Heavy Light Decomposition (HLD)
---

### コンストラクタ

- シグネチャ

  ```cpp
  using Graph = std::vector<std::vector<int>>;

  HeavyLightDecomposition(Graph &g, int root = 0)
  ```

- 概要

  与えられたグラフに対して HL 分解を行います．

  __Note. 隣接リストの順序を変更します．具体的には，隣接リストの先頭に Heavy Edge で繋がる子を配置します__

  - このようなことを行う理由として，DFS の探索順序と HLD により振られる添字の昇順に頂点を並べた列が一致するという嬉しい性質があります．パスクエリと部分木クエリで添字の置換を共有できるので，両方のタイプのクエリが同時に来るような場合にも対応できるようになります．

- 制約

  - $0\leq \mathrm{root}\lt n$

- 時間計算量

  木の頂点数を $n$ として，$O(n)$

### Lowest Common Ancestor (LCA)

- シグネチャ

  ```cpp
  int lca(int u, int v)
  ```

- 概要

  与えられた頂点対の LCA を計算します．

- 制約

  - $0\leq u,v\lt n$

- 時間計算量

  $O(\log n)$

### Level Ancestor (LA)

- シグネチャ

  ```cpp
  int la(int u, int k, int default_value = -1)
  ```

- 概要

  頂点 $u$ の祖先であって，深さが頂点 $u$ よりも丁度 $k$ だけ小さい頂点を返します．つまり，親への辺を丁度 $k$ 回だけ辿って到達する頂点を求めます．ただし，そのような頂点が存在しない場合は，第二引数として渡された `default_value` を返します．

- 制約

  - $0\leq u\lt n$

- 時間計算量

  $O(\log n)$

### fold_path

- シグネチャ

  ```cpp
  template <typename T, typename Q, typename F>
  T fold_path(int u, int v, T identity, F bin_op, Q fold_query, bool is_edge_query = false)
  ```

- 概要

  $u-v$ パス上の頂点または辺に載せられた要素を二項演算 `bin_op` で累積した結果を計算します．

  内部的には，$u-v$ パスを添字が連続したいくつかのパスに分割して `fold_query` により区間和を計算した後，__順不同__ で結果をマージします．ここでいう添字は元の頂点番号ではなく HLD による置換を作用させた番号であり，`fold_query` には置換後の添字区間 `[l, r)` が引数として与えられます．従って，区間和を高速に求める Segment Tree などのデータ構造を外部で用意しておくことが想定されます．

  なお，頂点に要素が乗っている場合は `is_edge_query=false` を，辺に要素が乗っている場合は `is_edge_query=true` を指定します．辺に要素を載せる場合は，木の根以外の頂点に対して，その親への辺に要素が乗っているものとして考えます．

  具体的な使用方法についてはテストファイルのコードを見るのが速いと思います．

- テンプレート引数

  - `T`: 頂点または辺に載せる要素の型
  - `Q`: 区間和を求める `(int, int) -> T` の関数型
  - `F`: 二項演算 `(T, T) -> T` の関数型

  ただ，これらを明示的に与える必要があることは少ないと思います．

- 制約

  - $0\leq u,v\lt n$
  - $(T,F)$ は可換モノイド
  - $\mathrm{identity}$ は可換モノイド $(T, F)$ の単位元
  - 任意の $0\leq l\leq r\leq n$ に対して，$\displaystyle \mathrm{fold\\\_ query}(l,r)=\bigoplus_{i=l}^{r-1}t_i$．ここで $\oplus$ は二項演算であり，$t_i$ は置換後の添字 $i$ に対応する要素．

- 時間計算量

  `fold_query(l, r)` の計算量を $O(f(n))$ として，$O(f(n)\cdot \log n)$．例えば Segment Tree を用いて区間和を取得する場合は $O((\log n) ^ 2)$ となる．

### fold_path_noncommutative

- シグネチャ

  ```cpp
  template <typename T, typename Q1, typename Q2, typename F>
  T fold_path_noncommutative(int u, int v, T identity, F bin_op, Q1 fold_query, Q2 fold_query_rev, bool is_edge_query = false)
  ```

- 概要

  `fold_path` における可換性の要求を緩和した関数です．可換性を要求しない代わりに，区間和を逆順に求める関数 `fold_query_rev` を与える必要があります．

- テンプレート引数

  - `T`: 頂点または辺に載せる要素の型
  - `Q1`: 区間和を求める `(int, int) -> T` の関数型
  - `Q2`: 逆順の区間和を求める `(int, int) -> T` の関数型
  - `F`: 二項演算 `(T, T) -> T` の関数型

- 制約

  - $0\leq u,v\lt n$
  - $(T,F)$ はモノイド (非可換でもよい)
  - $\mathrm{identity}$ はモノイド $(T, F)$ の単位元
  - 任意の $0\leq l\leq r\leq n$ に対して，$\displaystyle \mathrm{fold\\\_ query}(l,r)=t_l\oplus t_{l+1}\oplus\cdots\oplus t_{r-1}$．
  - 任意の $0\leq l\leq r\leq n$ に対して，$\displaystyle \mathrm{fold\\\_ query\\\_ rev}(l,r)=t_{r-1}\oplus\cdots\oplus t_{l+1}\oplus t_l$．

- 時間計算量

  `fold_query(l, r)` および `fold_query_rev(l, r)` の計算量を $O(f(n))$ として，$O(f(n)\cdot \log n)$．

### update_path

- シグネチャ

  ```cpp
  template <typename Q>
  void update_path(int u, int v, Q update_query, bool is_edge_query = false)
  ```

- 概要

  $u-v$ パス上の頂点または辺に載せられた要素を更新します．`update_query` として渡す関数は [fold_path](#fold_path) における `fold_query` とほぼ同様であり，置換後の添字の区間 `[l, r)` が与えられます．

- テンプレート引数

  - `Q`: 区間更新を行う `(int, int) -> void` の関数型

  [fold_path](#fold_path) と同様，明示的に渡す必要があることは少ないと思います．

- 制約

  - $0\leq u,v\lt n$

- 時間計算量

  `update_query(l, r)` の計算量を $O(f(n))$ として，$O(f(n)\cdot \log n)$．

### fold_subtree

- シグネチャ

  ```cpp
  template <typename T, typename Q>
  T fold_subtree(int u, Q fold_query, bool is_edge_query = false)
  ```

- 概要

  頂点 $u$ を根とする部分木に含まれる頂点または辺に載せられた要素を __順不同__ で畳み込みます．[fold_path](#fold_path) と同様に，`fold_query` の引数には置換後の添字の区間 `[l, r)` が与えられます．

  区間和を高速に求める Segment Tree などのデータ構造を外部で用意しておくことが想定されます．

- テンプレート引数

  - `T`: 頂点に載せる要素の型
  - `Q`: 区間和を求める `(int, int) -> T` の関数型

- 制約

  - $0\leq u\lt n$

- 時間計算量

  `fold_query(l, r)` の計算量を $O(f(n))$ として，$O(f(n))$

### update_subtree

- シグネチャ

  ```cpp
  template <typename Q>
  void update_subtree(int u, Q update_query, bool is_edge_query = false)
  ```

- 概要

  頂点 $u$ を根とする部分木に含まれる頂点または辺に載せられた要素を更新します．`update_query` として渡す関数には，引数として置換後の添字の区間 `[l, r)` が与えられます．

- テンプレート引数

  - `Q`: 区間更新を行う `(int, int) -> void` の関数型

- 制約

  - $0\leq u\lt n$

- 時間計算量

  `update_query(l, r)` の計算量を $O(f(n))$ として，$O(f(n))$．

### get_point

- シグネチャ

  ```cpp
  template <typename T, typename Q>
  T get_point(int u, Q get_query)
  ```

- 概要

  頂点 $u$ に載せられた情報を取得します．`get_query` として渡す関数には，引数として置換後の添字 $i$ が与えられます．

- テンプレート引数

  - `T`: 要素型
  - `Q`: 点取得を行う `(int) -> T` の関数型

- 制約

  - $0\leq u\lt n$

- 時間計算量
  
  `get_query(i)` の計算量を $O(f(n))$ として，$O(f(n))$．

### update_point

- シグネチャ

  ```cpp
  template <typename Q>
  void update_point(int u, Q update_query)
  ```

- 概要

  頂点 $u$ の情報を更新します．`update_query` として渡す関数には，引数として置換後の添字 $i$ が与えられます．

- テンプレート引数

  - `Q`: 点更新を行う `(int) -> void` の関数型

- 制約

  - $0\leq u\lt n$

- 時間計算量
  
  `update_query(i)` の計算量を $O(f(n))$ として，$O(f(n))$．
