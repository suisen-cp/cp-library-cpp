---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/auxiliary_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 1 \"library/tree/heavy_light_decomposition.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <iostream>\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
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
    \n\n#line 6 \"library/tree/auxiliary_tree.hpp\"\n\nnamespace suisen {\n    struct\
    \ AuxiliaryTree {\n        AuxiliaryTree() = default;\n        AuxiliaryTree(const\
    \ HeavyLightDecomposition& hld) : _n(hld.size()), _aux(_n), _hld(hld) {}\n\n \
    \       const std::vector<int>& operator[](int u) const {\n            return\
    \ _aux[u];\n        }\n\n        void build(std::vector<int> vs) {\n         \
    \   const int k = vs.size();\n            for (int v : _upd) _aux[v].clear();\n\
    \            _upd.clear();\n\n            std::sort(vs.begin(), vs.end(), [this](int\
    \ i, int j) { return _hld.get_visit_time(i) < _hld.get_visit_time(j); });\n\n\
    \            std::copy(vs.begin(), vs.end(), std::back_inserter(_upd));\n\n  \
    \          std::vector<int> st{ vs[0] };\n            for (int i = 0; i < k -\
    \ 1; ++i) {\n                const int w = _hld.lca(vs[i], vs[i + 1]);\n\n   \
    \             if (w != vs[i]) {\n                    _upd.push_back(w);\n    \
    \                int last = st.back();\n                    st.pop_back();\n \
    \                   while (st.size() and _hld.get_depth(w) < _hld.get_depth(st.back()))\
    \ {\n                        int u = st.back();\n                        _aux[u].push_back(last);\n\
    \                        _aux[last].push_back(u);\n                        last\
    \ = st.back();\n                        st.pop_back();\n                    }\n\
    \n                    if (st.empty() or st.back() != w) {\n                  \
    \      st.push_back(w);\n                        vs.push_back(w);\n          \
    \              _aux[w].push_back(last);\n                        _aux[last].push_back(w);\n\
    \                    } else {\n                        _aux[w].push_back(last);\n\
    \                        _aux[last].push_back(w);\n                    }\n   \
    \             }\n\n                st.push_back(vs[i + 1]);\n            }\n \
    \           const int siz = st.size();\n            for (int i = 0; i < siz -\
    \ 1; ++i) {\n                _aux[st[i]].push_back(st[i + 1]);\n             \
    \   _aux[st[i + 1]].push_back(st[i]);\n            }\n        }\n\n        const\
    \ HeavyLightDecomposition& get_hld() const {\n            return _hld;\n     \
    \   }\n    private:\n        int _n;\n        std::vector<std::vector<int>> _aux;\n\
    \        HeavyLightDecomposition _hld;\n        std::vector<int> _upd;\n    };\n\
    } // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_AUXILIARY_TREE\n#define SUISEN_AUXILIARY_TREE\n\n#include\
    \ <algorithm>\n#include \"library/tree/heavy_light_decomposition.hpp\"\n\nnamespace\
    \ suisen {\n    struct AuxiliaryTree {\n        AuxiliaryTree() = default;\n \
    \       AuxiliaryTree(const HeavyLightDecomposition& hld) : _n(hld.size()), _aux(_n),\
    \ _hld(hld) {}\n\n        const std::vector<int>& operator[](int u) const {\n\
    \            return _aux[u];\n        }\n\n        void build(std::vector<int>\
    \ vs) {\n            const int k = vs.size();\n            for (int v : _upd)\
    \ _aux[v].clear();\n            _upd.clear();\n\n            std::sort(vs.begin(),\
    \ vs.end(), [this](int i, int j) { return _hld.get_visit_time(i) < _hld.get_visit_time(j);\
    \ });\n\n            std::copy(vs.begin(), vs.end(), std::back_inserter(_upd));\n\
    \n            std::vector<int> st{ vs[0] };\n            for (int i = 0; i < k\
    \ - 1; ++i) {\n                const int w = _hld.lca(vs[i], vs[i + 1]);\n\n \
    \               if (w != vs[i]) {\n                    _upd.push_back(w);\n  \
    \                  int last = st.back();\n                    st.pop_back();\n\
    \                    while (st.size() and _hld.get_depth(w) < _hld.get_depth(st.back()))\
    \ {\n                        int u = st.back();\n                        _aux[u].push_back(last);\n\
    \                        _aux[last].push_back(u);\n                        last\
    \ = st.back();\n                        st.pop_back();\n                    }\n\
    \n                    if (st.empty() or st.back() != w) {\n                  \
    \      st.push_back(w);\n                        vs.push_back(w);\n          \
    \              _aux[w].push_back(last);\n                        _aux[last].push_back(w);\n\
    \                    } else {\n                        _aux[w].push_back(last);\n\
    \                        _aux[last].push_back(w);\n                    }\n   \
    \             }\n\n                st.push_back(vs[i + 1]);\n            }\n \
    \           const int siz = st.size();\n            for (int i = 0; i < siz -\
    \ 1; ++i) {\n                _aux[st[i]].push_back(st[i + 1]);\n             \
    \   _aux[st[i + 1]].push_back(st[i]);\n            }\n        }\n\n        const\
    \ HeavyLightDecomposition& get_hld() const {\n            return _hld;\n     \
    \   }\n    private:\n        int _n;\n        std::vector<std::vector<int>> _aux;\n\
    \        HeavyLightDecomposition _hld;\n        std::vector<int> _upd;\n    };\n\
    } // namespace suisen\n\n#endif // SUISEN_AUXILIARY_TREE\n"
  dependsOn:
  - library/tree/heavy_light_decomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/tree/auxiliary_tree.hpp
  requiredBy: []
  timestamp: '2024-01-31 02:46:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/auxiliary_tree.hpp
layout: document
title: "\u6307\u5B9A\u3055\u308C\u305F\u9802\u70B9\u305F\u3061\u306E\u6700\u5C0F\u5171\
  \u901A\u7956\u5148\u95A2\u4FC2\u3092\u4FDD\u3063\u3066\u6728\u3092\u5727\u7E2E\u3057\
  \u3066\u3067\u304D\u308B\u88DC\u52A9\u7684\u306A\u6728"
---
## 指定された頂点たちの最小共通祖先関係を保って木を圧縮してできる補助的な木

名称は [ア辞典](https://web.archive.org/web/20211022091628/https://dic.kimiyuki.net/auxiliary-tree) から拝借しました。
