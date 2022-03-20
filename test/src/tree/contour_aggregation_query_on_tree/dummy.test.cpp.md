---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: library/tree/contour_aggregation_query_on_tree.hpp
    title: Contour Aggregation Query On Tree
  - icon: ':heavy_check_mark:'
    path: library/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition (HLD)
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <numeric>\n\n#line 1 \"library/tree/contour_aggregation_query_on_tree.hpp\"\
    \n\n\n\n#include <deque>\n#include <map>\n#include <tuple>\n\n#include <atcoder/segtree>\n\
    \n#line 1 \"library/tree/centroid_decomposition.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n\n    struct CentroidDecomposition : public std::vector<std::vector<int>>\
    \ {\n        using BaseType = std::vector<std::vector<int>>;\n    public:\n  \
    \      using BaseType::BaseType;\n\n        void add_edge(int u, int v) {\n  \
    \          BaseType::operator[](u).push_back(v);\n            BaseType::operator[](v).push_back(u);\n\
    \        }\n\n    private:\n        std::vector<bool> removed;\n        std::vector<int>\
    \ sub;\n\n        struct AdjacentListIterator {\n            using it_t = std::vector<int>::const_iterator;\n\
    \            const CentroidDecomposition* const ptr;\n            const int u;\n\
    \            it_t it;\n            AdjacentListIterator(const CentroidDecomposition*\
    \ const ptr, int u, it_t it) : ptr(ptr), u(u), it(it) { suc(); }\n           \
    \ AdjacentListIterator& operator++() { return ++it, suc(), * this; }\n       \
    \     int operator*() { return *it; }\n            bool operator!=(const AdjacentListIterator&\
    \ other) { return it != other.it; }\n            void suc() { while (it != (*ptr).BaseType::operator[](u).end()\
    \ and ptr->removed[*it]) ++it; }\n        };\n        struct AdjacentList {\n\
    \            CentroidDecomposition* const ptr;\n            const int u;\n   \
    \         std::vector<int>& base_vector()& { return ptr->BaseType::operator[](u);\
    \ }\n            auto begin() const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin());\
    \ }\n            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end());\
    \ }\n        };\n        struct ConstAdjacentList {\n            const CentroidDecomposition*\
    \ const ptr;\n            const int u;\n            const std::vector<int>& base_vector()\
    \ const& { return ptr->BaseType::operator[](u); }\n            auto begin() const\
    \ { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).begin());\
    \ }\n            auto end()   const { return AdjacentListIterator(ptr, u, (*ptr).BaseType::operator[](u).end());\
    \ }\n        };\n\n    public:\n        static constexpr void dummy(int, int)\
    \ {}\n\n        // Returns the list of vertices adjacent to `u`. If called during\
    \ decomposition, it skips removed vertices.\n        auto operator[](int u) {\n\
    \            return AdjacentList{ this, u };\n        }\n        // Returns the\
    \ (constant) list of vertices adjacent to `u`. If called during decomposition,\
    \ it skips removed vertices.\n        auto operator[](int u) const {\n       \
    \     return ConstAdjacentList{ this, u };\n        }\n\n        // This method\
    \ is expected to be called in functions passed to the `decomp`.\n        // The\
    \ argument `root` must be directly connected to the current centroid. If not,\
    \ the returned value will be undefined.\n        int component_size(int root)\
    \ const {\n            return sub[root];\n        }\n\n        struct DecompositionTree\
    \ {\n            DecompositionTree() {}\n            DecompositionTree(int root,\
    \ const std::vector<int> &par) : n(par.size()), root(root), par(par) {}\n\n  \
    \          int size() const { return n; }\n            int get_root() const {\
    \ return root; }\n            int get_parent(int u) const { return par[u]; }\n\
    \            const std::vector<int>& parents() const { return par; }\n       \
    \ private:\n            int n;\n            int root;\n            std::vector<int>\
    \ par;\n        };\n\n        // returns the centroid decomposition tree\n   \
    \     template <typename DownF = decltype(dummy), typename UpF = decltype(dummy)>\n\
    \        DecompositionTree decomp(DownF down = dummy, UpF up = dummy) {\n    \
    \        removed.assign(size(), false);\n            sub.assign(size(), 0);\n\
    \            std::vector<int> par(size(), -1);\n            auto rec = [&](auto\
    \ rec, int r, int siz) -> int {\n                int c = -1;\n               \
    \ auto get_centroid = [&](auto get_centroid, int u, int p) -> void {\n       \
    \             sub[u] = 1;\n                    for (int v : (*this)[u]) {\n  \
    \                      if (v == p) continue;\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub[u]\
    \ = siz - sub[c];\n                            break;\n                      \
    \  }\n                        sub[u] += sub[v];\n                    }\n     \
    \               if (c < 0 and sub[u] * 2 > siz) c = u;\n                };\n \
    \               get_centroid(get_centroid, r, -1);\n                down(c, siz);\n\
    \                removed[c] = true;\n                for (int v : (*this)[c])\
    \ {\n                    const int comp_size = sub[v];\n                    par[rec(rec,\
    \ v, comp_size)] = c;\n                    sub[v] = comp_size;\n             \
    \   }\n                removed[c] = false;\n                up(c, siz);\n    \
    \            return c;\n            };\n            int root = rec(rec, 0, size());\n\
    \            return DecompositionTree(root, par);\n        }\n    };\n\n} // namespace\
    \ suisen\n\n\n#line 1 \"library/tree/heavy_light_decomposition.hpp\"\n\n\n\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
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
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 6 \"library/tree/heavy_light_decomposition.hpp\"\n\nnamespace suisen {\nclass\
    \ HeavyLightDecomposition {\n    public:\n        template <typename Q>\n    \
    \    using is_point_update_query = std::is_invocable<Q, int>;\n        template\
    \ <typename Q>\n        using is_range_update_query = std::is_invocable<Q, int,\
    \ int>;\n        template <typename Q, typename T>\n        using is_point_get_query\
    \  = std::is_same<std::invoke_result_t<Q, int>, T>;\n        template <typename\
    \ Q, typename T>\n        using is_range_fold_query = std::is_same<std::invoke_result_t<Q,\
    \ int, int>, T>;\n\n        using Graph = std::vector<std::vector<int>>;\n\n \
    \       HeavyLightDecomposition() = default;\n        HeavyLightDecomposition(Graph\
    \ &g) : n(g.size()), visit(n), leave(n), head(n), ord(n), siz(n), par(n, -1),\
    \ dep(n, 0) {\n            for (int i = 0; i < n; ++i) if (par[i] < 0) dfs(g,\
    \ i, -1);\n            int time = 0;\n            for (int i = 0; i < n; ++i)\
    \ if (par[i] < 0) hld(g, i, -1, time);\n        }\n        int lca(int u, int\
    \ v) {\n            for (;; v = par[head[v]]) {\n                if (visit[u]\
    \ > visit[v]) std::swap(u, v);\n                if (head[u] == head[v]) return\
    \ u;\n            }\n        }\n        int la(int u, int k, int default_value\
    \ = -1) {\n            if (k < 0) return default_value;\n            while (u\
    \ >= 0) {\n                int h = head[u];\n                if (visit[u] - k\
    \ >= visit[h]) return ord[visit[u] - k];\n                k -= visit[u] - visit[h]\
    \ + 1;\n                u = par[h];\n            }\n            return default_value;\n\
    \        }\n        int move_to(int u, int v, int d, int default_value = -1) {\n\
    \            if (d < 0) return default_value;\n            const int w = lca(u,\
    \ v);\n            int uw = dep[u] - dep[w];\n            if (d <= uw) return\
    \ la(u, d);\n            int vw = dep[v] - dep[w];\n            return d <= uw\
    \ + vw ? la(v, (uw + vw) - d) : default_value;\n        }\n        int dist(int\
    \ u, int v) {\n            return dep[u] + dep[v] - 2 * dep[lca(u, v)];\n    \
    \    }\n        template <typename T, typename Q, typename F, constraints_t<is_range_fold_query<Q,\
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
    \ update_query(visit[u]);\n        }\n        std::vector<int> inv_ids() const\
    \ {\n            std::vector<int> inv(n);\n            for (int i = 0; i < n;\
    \ ++i) inv[visit[i]] = i;\n            return inv;\n        }\n        int get_head(int\
    \ u) const {\n            return head[u];\n        }\n        int get_parent(int\
    \ u) const {\n            return par[u];\n        }\n        int get_subtree_size(int\
    \ u) const {\n            return siz[u];\n        }\n        std::vector<int>\
    \ get_roots() const {\n            std::vector<int> res;\n            for (int\
    \ i = 0; i < n; ++i) if (par[i] < 0) res.push_back(i);\n            return res;\n\
    \        }\n    private:\n        int n;\n        std::vector<int> visit, leave,\
    \ head, ord, siz, par, dep;\n        int dfs(Graph &g, int u, int p) {\n     \
    \       par[u] = p;\n            siz[u] = 1;\n            int max_size = 0;\n\
    \            for (int &v : g[u]) {\n                if (v == p) continue;\n  \
    \              dep[v] = dep[u] + 1;\n                siz[u] += dfs(g, v, u);\n\
    \                if (max_size < siz[v]) {\n                    max_size = siz[v];\n\
    \                    std::swap(g[u].front(), v);\n                }\n        \
    \    }\n            return siz[u];\n        }\n        void hld(Graph &g, int\
    \ u, int p, int &time) {\n            visit[u] = time, ord[time] = u, ++time;\n\
    \            head[u] = p >= 0 and g[p].front() == u ? head[p] : u;\n         \
    \   for (int v : g[u]) {\n                if (v != p) hld(g, v, u, time);\n  \
    \          }\n            leave[u] = time;\n        }\n};\n} // namespace suisen\n\
    \n\n#line 12 \"library/tree/contour_aggregation_query_on_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct ContourAggregationQueryOnTree\
    \ : private CentroidDecomposition {\n        using base_type = CentroidDecomposition;\n\
    \        using base_type::base_type;\n        using base_type::add_edge;\n\n \
    \       using segtree_type = atcoder::segtree<T, op, e>;\n\n        void build(const\
    \ std::vector<T> &dat) {\n            _hld = HeavyLightDecomposition(*this);\n\
    \            _siz.resize(size());\n            _sub_root.resize(size());\n   \
    \         _sep.resize(size());\n            _range.resize(size());\n         \
    \   _seg.resize(size());\n            _tree = base_type::decomp(\n           \
    \     [&](int centroid, int siz) {\n                    _siz[centroid] = siz;\n\
    \                    std::vector<T> vs { dat[centroid] };\n                  \
    \  auto &sep = _sep[centroid];\n                    auto &ran = _range[centroid];\n\
    \                    auto &sub = _sub_root[centroid];\n                    //\
    \ (current vertex, parent vertex, component id, depth)\n                    std::deque<std::tuple<int,\
    \ int, int, int>> dq;\n                    for (int sub_root : (*this)[centroid])\
    \ sub.push_back(sub_root);\n                    std::sort(sub.begin(), sub.end());\n\
    \                    for (std::size_t i = 0; i < sub.size(); ++i) {\n        \
    \                dq.emplace_back(sub[i], centroid, i, 1);\n                  \
    \  }\n                    sep.push_back(0);\n                    ran.resize(sub.size(),\
    \ { { -1, -1 } });\n                    int pre_dep = 0, pre_id = -1;\n      \
    \              while (dq.size()) {\n                        const auto [u, p,\
    \ id, dep] = dq.front();\n                        dq.pop_front();\n          \
    \              if (pre_dep != dep or pre_id != id) {\n                       \
    \     if (pre_dep != dep) sep.push_back(vs.size());\n                        \
    \    if (pre_id >= 0) {\n                                ran[pre_id][pre_dep].second\
    \ = vs.size();\n                            }\n                            ran[id].emplace_back(vs.size(),\
    \ -1);\n                            pre_dep = dep, pre_id = id;\n            \
    \            }\n                        vs.push_back(dat[u]);\n              \
    \          for (int v : (*this)[u]) {\n                            if (v == p)\
    \ continue;\n                            dq.emplace_back(v, u, id, dep + 1);\n\
    \                        }\n                    }\n                    if (pre_id\
    \ >= 0) {\n                        ran[pre_id][pre_dep].second = vs.size();\n\
    \                        sep.push_back(vs.size());\n                    }\n  \
    \                  _seg[centroid] = segtree_type(std::move(vs));\n           \
    \     }\n            );\n        }\n\n        T prod(int u, int d) {\n       \
    \     T res = e();\n            int skip = -1;\n            for (int v = u;;)\
    \ {\n                res = op(res, prod(v, d - _hld.dist(u, v), skip));\n    \
    \            int p = _tree.get_parent(v);\n                if (p < 0) break;\n\
    \                skip = _hld.move_to(p, v, 1);\n                v = p;\n     \
    \       }\n            return res;\n        }\n\n    private:\n        HeavyLightDecomposition\
    \ _hld;\n\n        CentroidDecomposition::DecompositionTree _tree;\n\n       \
    \ std::vector<int> _siz;\n        std::vector<std::vector<int>> _sub_root;\n \
    \       std::vector<std::vector<int>> _sep;\n        std::vector<std::vector<std::vector<std::pair<int,\
    \ int>>>> _range;\n        std::vector<segtree_type> _seg;\n\n        T prod(int\
    \ u, int d, int skip) {\n            if (d == 0) return _seg[u].get(0);\n    \
    \        if (d < 0 or int(_sep[u].size()) <= d + 1) return e();\n            int\
    \ l = _sep[u][d], r = _sep[u][d + 1];\n            if (skip < 0) return _seg[u].prod(l,\
    \ r);\n            int skip_index = std::lower_bound(_sub_root[u].begin(), _sub_root[u].end(),\
    \ skip) - _sub_root[u].begin();\n            if (int(_range[u][skip_index].size())\
    \ <= d) {\n                return _seg[u].prod(l, r);\n            } else {\n\
    \                auto [ml, mr] = _range[u][skip_index][d];\n                return\
    \ op(_seg[u].prod(l, ml), _seg[u].prod(mr, r));\n            }\n        }\n  \
    \  };\n} // namespace suisen\n\n\n\n#line 7 \"test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp\"\
    \n\nint op(int x, int y) {\n    return x + y;\n}\nint e() {\n    return 0;\n}\n\
    \nvoid test() {\n    std::vector<std::vector<int>> g {\n        { 1, 8, 16 },\
    \       // 0\n        { 0, 2, 3 },        // 1\n        { 1 },              //\
    \ 2\n        { 1, 4, 7 },        // 3\n        { 3, 5, 6 },        // 4\n    \
    \    { 4 },              // 5\n        { 4 },              // 6\n        { 3 },\
    \              // 7\n        { 0, 9, 10 },       // 8\n        { 8 },        \
    \      // 9\n        { 8, 11, 15 },      // 10\n        { 10, 12, 13, 14 }, //\
    \ 11\n        { 11 },             // 12\n        { 11 },             // 13\n \
    \       { 11 },             // 14\n        { 10 },             // 15\n       \
    \ { 0, 17, 18, 20 },  // 16\n        { 16 },             // 17\n        { 16,\
    \ 19 },         // 18\n        { 18 },             // 19\n        { 16, 21, 24\
    \ },     // 20\n        { 20, 22, 23 },     // 21\n        { 21 },           \
    \  // 22\n        { 21 },             // 23\n        { 20 }              // 24\n\
    \    };\n\n    const int n = g.size();\n    suisen::ContourAggregationQueryOnTree<int,\
    \ op, e> contour_aggregator(n);\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j : g[i]) if (i < j) {\n            contour_aggregator.add_edge(i, j);\n\
    \        }\n    }\n    std::vector<int> dat(n);\n    std::iota(dat.begin(), dat.end(),\
    \ 0);\n    contour_aggregator.build(dat);\n\n    auto naive = [&](int k, int d)\
    \ {\n        int res = 0;\n        auto dfs = [&](auto dfs, int u, int p, int\
    \ dep) -> void {\n            if (dep == d) res += dat[u];\n            for (int\
    \ v : g[u]) {\n                if (v == p) continue;\n                dfs(dfs,\
    \ v, u, dep + 1);\n            }\n        };\n        dfs(dfs, k, -1, 0);\n  \
    \      return res;\n    };\n\n    for (int i = 0; i < n; ++i) {\n        for (int\
    \ d = 0; d <= n; ++d) {\n            int sum1 = contour_aggregator.prod(i, d);\n\
    \            int sum2 = naive(i, d);\n            if (sum1 != sum2) {\n      \
    \          std::cout << \"failed in the cese (\" << i << \", \" << d << \"):\"\
    \ << std::endl;\n                std::cout << \"  expected : \" << sum2 << std::endl;\n\
    \                std::cout << \"  actual   : \" << sum1 << std::endl;\n      \
    \      }\n        }\n    }\n}\n\nint main() {\n    test();\n    std::cout << \"\
    Hello World\" << std::endl;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <numeric>\n\n#include \"library/tree/contour_aggregation_query_on_tree.hpp\"\
    \n\nint op(int x, int y) {\n    return x + y;\n}\nint e() {\n    return 0;\n}\n\
    \nvoid test() {\n    std::vector<std::vector<int>> g {\n        { 1, 8, 16 },\
    \       // 0\n        { 0, 2, 3 },        // 1\n        { 1 },              //\
    \ 2\n        { 1, 4, 7 },        // 3\n        { 3, 5, 6 },        // 4\n    \
    \    { 4 },              // 5\n        { 4 },              // 6\n        { 3 },\
    \              // 7\n        { 0, 9, 10 },       // 8\n        { 8 },        \
    \      // 9\n        { 8, 11, 15 },      // 10\n        { 10, 12, 13, 14 }, //\
    \ 11\n        { 11 },             // 12\n        { 11 },             // 13\n \
    \       { 11 },             // 14\n        { 10 },             // 15\n       \
    \ { 0, 17, 18, 20 },  // 16\n        { 16 },             // 17\n        { 16,\
    \ 19 },         // 18\n        { 18 },             // 19\n        { 16, 21, 24\
    \ },     // 20\n        { 20, 22, 23 },     // 21\n        { 21 },           \
    \  // 22\n        { 21 },             // 23\n        { 20 }              // 24\n\
    \    };\n\n    const int n = g.size();\n    suisen::ContourAggregationQueryOnTree<int,\
    \ op, e> contour_aggregator(n);\n    for (int i = 0; i < n; ++i) {\n        for\
    \ (int j : g[i]) if (i < j) {\n            contour_aggregator.add_edge(i, j);\n\
    \        }\n    }\n    std::vector<int> dat(n);\n    std::iota(dat.begin(), dat.end(),\
    \ 0);\n    contour_aggregator.build(dat);\n\n    auto naive = [&](int k, int d)\
    \ {\n        int res = 0;\n        auto dfs = [&](auto dfs, int u, int p, int\
    \ dep) -> void {\n            if (dep == d) res += dat[u];\n            for (int\
    \ v : g[u]) {\n                if (v == p) continue;\n                dfs(dfs,\
    \ v, u, dep + 1);\n            }\n        };\n        dfs(dfs, k, -1, 0);\n  \
    \      return res;\n    };\n\n    for (int i = 0; i < n; ++i) {\n        for (int\
    \ d = 0; d <= n; ++d) {\n            int sum1 = contour_aggregator.prod(i, d);\n\
    \            int sum2 = naive(i, d);\n            if (sum1 != sum2) {\n      \
    \          std::cout << \"failed in the cese (\" << i << \", \" << d << \"):\"\
    \ << std::endl;\n                std::cout << \"  expected : \" << sum2 << std::endl;\n\
    \                std::cout << \"  actual   : \" << sum1 << std::endl;\n      \
    \      }\n        }\n    }\n}\n\nint main() {\n    test();\n    std::cout << \"\
    Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/tree/contour_aggregation_query_on_tree.hpp
  - library/tree/centroid_decomposition.hpp
  - library/tree/heavy_light_decomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-03-21 02:24:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
- /verify/test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp.html
title: test/src/tree/contour_aggregation_query_on_tree/dummy.test.cpp
---
