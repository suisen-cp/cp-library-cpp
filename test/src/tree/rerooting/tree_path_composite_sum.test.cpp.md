---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/tree/rerooting.hpp
    title: "Rerooting (\u5168\u65B9\u4F4D\u6728 DP)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_path_composite_sum
    links:
    - https://judge.yosupo.jp/problem/tree_path_composite_sum
  bundledCode: "#line 1 \"test/src/tree/rerooting/tree_path_composite_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\n\
    \n#include <iostream>\n\n#include <atcoder/modint>\n\n#line 1 \"library/tree/rerooting.hpp\"\
    \n\n\n\n#include <cassert>\n#include <tuple>\n#include <vector>\n#include <variant>\n\
    \nnamespace suisen {\n    namespace internal::rerooting {\n        using void_weight\
    \ = std::monostate;\n\n        template <typename VertexWeight, typename EdgeWeight>\n\
    \        struct Rerooting {\n            using vertex_weight = VertexWeight;\n\
    \            using edge_weight = EdgeWeight;\n    private:\n            using\
    \ is_vertex_weight_void = std::is_same<vertex_weight, void_weight>;\n        \
    \    using is_edge_weight_void = std::is_same<edge_weight, void_weight>;\n   \
    \         static constexpr bool is_vertex_weight_void_v = is_vertex_weight_void::value;\n\
    \            static constexpr bool is_edge_weight_void_v = is_edge_weight_void::value;\n\
    \n            template <typename DP, typename AddSubtreeRoot>\n            using\
    \ is_add_subtree_root = std::conditional_t<\n                std::negation_v<is_vertex_weight_void>,\n\
    \                std::conditional_t<\n                    std::negation_v<is_edge_weight_void>,\n\
    \                    std::is_invocable_r<DP, AddSubtreeRoot, DP, vertex_weight,\
    \ edge_weight>,\n                    std::is_invocable_r<DP, AddSubtreeRoot, DP,\
    \ vertex_weight>\n                >,\n                std::conditional_t<\n  \
    \                  std::negation_v<is_edge_weight_void>,\n                   \
    \ std::is_invocable_r<DP, AddSubtreeRoot, DP, edge_weight>,\n                \
    \    std::is_invocable_r<DP, AddSubtreeRoot, DP>\n                >\n        \
    \    >;\n            template <typename DP, typename AddRoot>\n            using\
    \ is_add_root = std::conditional_t<\n                std::negation_v<is_vertex_weight_void>,\n\
    \                std::is_invocable_r<DP, AddRoot, DP, vertex_weight>,\n      \
    \          std::is_invocable_r<DP, AddRoot, DP>\n            >;\n    public:\n\
    \            Rerooting() : _w{} {}\n            explicit Rerooting(int n) : _w(n)\
    \ {}\n            explicit Rerooting(const std::vector<vertex_weight>& w) : _w(w)\
    \ {}\n\n            void reserve(int n) {\n                _w.reserve(n);\n  \
    \          }\n\n            void add_vertex(const vertex_weight& w) {\n      \
    \          _w.emplace_back(w);\n            }\n            void add_edge(int u,\
    \ int v, const edge_weight& w = {}) {\n                const int n = _w.size();\n\
    \                assert(0 <= u and u < n);\n                assert(0 <= v and\
    \ v < n);\n                _e.emplace_back(u, v, w);\n            }\n        \
    \    void set_vertex_weights(const std::vector<vertex_weight>& w) {\n        \
    \        assert(w.size() == _w.size());\n                _w = w;\n           \
    \ }\n\n            /**\n             * op               : (T, T) -> T        \
    \                       // commutative monoid\n             * e              \
    \  : () -> T                                   // identity\n             * add_subtree_root\
    \ : (T, vertex_weight, edge_weight) -> T        // add subroot, edge to parent\n\
    \             * add_root         : (T, vertex_weight) -> T                   \
    \ // add root\n            */\n            template <typename Op, typename E,\
    \ typename AddSubtreeRoot, typename AddRoot,\n                typename DP = std::decay_t<std::invoke_result_t<E>>,\n\
    \                std::enable_if_t<std::conjunction_v<\n                    std::is_invocable_r<DP,\
    \ Op, DP, DP>,\n                    std::is_invocable_r<DP, E>,\n            \
    \        is_add_subtree_root<DP, AddSubtreeRoot>,\n                    is_add_root<DP,\
    \ AddRoot>\n                >, std::nullptr_t> = nullptr\n            >\n    \
    \        std::vector<DP> run_dp(const Op& op, const E& e, const AddSubtreeRoot&\
    \ add_subtree_root, const AddRoot& add_root) const {\n                auto add_subtree_root_\
    \ = [&add_subtree_root](const DP &val, const vertex_weight& vw, const edge_weight&\
    \ ew) {\n                    if constexpr (std::negation_v<is_vertex_weight_void>)\
    \ {\n                        if constexpr (std::negation_v<is_edge_weight_void>)\
    \ {\n                            return add_subtree_root(val, vw, ew);\n     \
    \                   } else {\n                            return add_subtree_root(val,\
    \ vw);\n                        }\n                    } else {\n            \
    \            if constexpr (std::negation_v<is_edge_weight_void>) {\n         \
    \                   return add_subtree_root(val, ew);\n                      \
    \  } else {\n                            return add_subtree_root(val);\n     \
    \                   }\n                    }\n                };\n           \
    \     auto add_root_ = [&add_root](const DP &val, const vertex_weight& vw) {\n\
    \                    if constexpr (std::negation_v<is_vertex_weight_void>) {\n\
    \                        return add_root(val, vw);\n                    } else\
    \ {\n                        return add_root(val);\n                    }\n  \
    \              };\n\n                const int n = _w.size();\n\n            \
    \    GraphCSR g(n, _e);\n\n                std::vector<DP> dp(n, e());\n\n   \
    \             [dfs = [&, this](auto dfs, int u, int p) -> void {\n           \
    \         for (const auto& [v, w] : g[u]) if (v != p) {\n                    \
    \    dfs(dfs, v, u);\n                        dp[u] = op(dp[u], add_subtree_root_(dp[v],\
    \ _w[v], w));\n                    }\n                }] { dfs(dfs, 0, -1); }();\n\
    \                dp[0] = add_root_(dp[0], _w[0]);\n\n                [dfs = [&,\
    \ this](auto dfs, int u, int p, const DP& sum_p) -> void {\n                 \
    \   auto get_sum = [&](int v) {\n                        return v == p ? sum_p\
    \ : dp[v];\n                    };\n\n                    const int siz = g[u].size();\n\
    \                    std::vector<DP> sum_r(siz + 1, e());\n                  \
    \  for (int i = siz - 1; i >= 0; --i) {\n                        const auto& [v,\
    \ w] = g[u][i];\n                        sum_r[i] = op(sum_r[i + 1], add_subtree_root_(get_sum(v),\
    \ _w[v], w));\n                    }\n\n                    DP sum_l = e();\n\
    \                    for (int i = 0; i < siz; ++i) {\n                       \
    \ const auto& [v, w] = g[u][i];\n                        DP nxt_sum_l = op(sum_l,\
    \ add_subtree_root_(get_sum(v), _w[v], w));\n                        if (v !=\
    \ p) {\n                            DP sum_lr = op(sum_l, sum_r[i + 1]);\n   \
    \                         DP sum_v = op(dp[v], add_subtree_root_(sum_lr, _w[u],\
    \ w));\n                            dp[v] = add_root_(sum_v, _w[v]);\n       \
    \                     dfs(dfs, v, u, sum_lr);\n                        }\n   \
    \                     sum_l = std::move(nxt_sum_l);\n                    }\n \
    \               }, &e] { dfs(dfs, 0, -1, e()); }();\n\n                return\
    \ dp;\n            }\n\n        private:\n            std::vector<vertex_weight>\
    \ _w;\n            std::vector<std::tuple<int, int, edge_weight>> _e;\n\n    \
    \        struct GraphCSR {\n                GraphCSR(int n, const std::vector<std::tuple<int,\
    \ int, edge_weight>>& edges) : _n(n), _m(edges.size()), _edges(2 * _m), _start(_n\
    \ + 1) {\n                    for (const auto& [u, v, w] : edges) {\n        \
    \                ++_start[u];\n                        ++_start[v];\n        \
    \            }\n                    for (int i = 1; i <= _n; ++i) {\n        \
    \                _start[i] += _start[i - 1];\n                    }\n        \
    \            for (const auto& [u, v, w] : edges) {\n                        _edges[--_start[u]]\
    \ = { v, w };\n                        _edges[--_start[v]] = { u, w };\n     \
    \               }\n                }\n            private:\n                using\
    \ edge_type = std::pair<int, edge_weight>;\n                using iterator = typename\
    \ std::vector<edge_type>::const_iterator;\n\n                struct AdjacentListView\
    \ {\n                    AdjacentListView(const iterator& l, const iterator& r)\
    \ : _l(l), _r(r) {}\n\n                    int size() const { return _r - _l;\
    \ }\n\n                    const edge_type& operator[](int i) const { return *(_l\
    \ + i); }\n\n                    iterator begin() const { return _l; }\n     \
    \               iterator end() const { return _r; }\n                private:\n\
    \                    iterator _l, _r;\n                };\n            public:\n\
    \                AdjacentListView operator[](int u) const {\n                \
    \    return AdjacentListView(_edges.begin() + _start[u], _edges.begin() + _start[u\
    \ + 1]);\n                }\n            private:\n                int _n, _m;\n\
    \                std::vector<std::pair<int, edge_weight>> _edges;\n          \
    \      std::vector<int> _start;\n            };\n        };\n    }\n    using\
    \ Rerooting = internal::rerooting::Rerooting<internal::rerooting::void_weight,\
    \ internal::rerooting::void_weight>;\n    template <typename VertexWeight>\n \
    \   using RerootingVertexWeighted = internal::rerooting::Rerooting<VertexWeight,\
    \ internal::rerooting::void_weight>;\n    template <typename EdgeWeight>\n   \
    \ using RerootingEdgeWeighted = internal::rerooting::Rerooting<internal::rerooting::void_weight,\
    \ EdgeWeight>;\n    template <typename VertexWeight, typename EdgeWeighted>\n\
    \    using RerootingWeighted = internal::rerooting::Rerooting<VertexWeight, EdgeWeighted>;\n\
    } // namsepace suisen\n\n\n#line 8 \"test/src/tree/rerooting/tree_path_composite_sum.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nnamespace atcoder {\n    std::istream&\
    \ operator>>(std::istream& in, mint& a) {\n        long long e; in >> e; a = e;\n\
    \        return in;\n    }\n\n    std::ostream& operator<<(std::ostream& out,\
    \ const mint& a) {\n        out << a.val();\n        return out;\n    }\n} //\
    \ namespace atcoder\n\nusing DP = std::pair<mint, int>;\nusing VWeight = mint;\n\
    using EWeight = std::pair<mint, mint>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<VWeight>\
    \ a(n);\n    for (auto& e : a) std::cin >> e;\n\n    suisen::RerootingWeighted<VWeight,\
    \ EWeight> g(a);\n\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n\
    \        std::cin >> u >> v;\n\n        mint b, c;\n        std::cin >> b >> c;\n\
    \n        g.add_edge(u, v, EWeight{ b, c });\n    }\n\n    std::vector ans = g.run_dp(\n\
    \        [](const DP& x, const DP& y) {\n            return DP{ x.first + y.first,\
    \ x.second + y.second };\n        },\n        []() {\n            return DP{ 0,\
    \ 0 };\n        },\n        [](const DP& x, const VWeight& a, const EWeight& f)\
    \ {\n            return DP{ f.first * (x.first + a) + f.second * (x.second + 1),\
    \ (x.second + 1) };\n        },\n        [](const DP& x, const VWeight& a) {\n\
    \            return DP{ x.first + a, x.second + 1 };\n        }\n    );\n\n  \
    \  for (const DP& v : ans) {\n        std::cout << v.first << ' ';\n    }\n  \
    \  std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\n\n#include \"library/tree/rerooting.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\n\nnamespace atcoder {\n    std::istream&\
    \ operator>>(std::istream& in, mint& a) {\n        long long e; in >> e; a = e;\n\
    \        return in;\n    }\n\n    std::ostream& operator<<(std::ostream& out,\
    \ const mint& a) {\n        out << a.val();\n        return out;\n    }\n} //\
    \ namespace atcoder\n\nusing DP = std::pair<mint, int>;\nusing VWeight = mint;\n\
    using EWeight = std::pair<mint, mint>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<VWeight>\
    \ a(n);\n    for (auto& e : a) std::cin >> e;\n\n    suisen::RerootingWeighted<VWeight,\
    \ EWeight> g(a);\n\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n\
    \        std::cin >> u >> v;\n\n        mint b, c;\n        std::cin >> b >> c;\n\
    \n        g.add_edge(u, v, EWeight{ b, c });\n    }\n\n    std::vector ans = g.run_dp(\n\
    \        [](const DP& x, const DP& y) {\n            return DP{ x.first + y.first,\
    \ x.second + y.second };\n        },\n        []() {\n            return DP{ 0,\
    \ 0 };\n        },\n        [](const DP& x, const VWeight& a, const EWeight& f)\
    \ {\n            return DP{ f.first * (x.first + a) + f.second * (x.second + 1),\
    \ (x.second + 1) };\n        },\n        [](const DP& x, const VWeight& a) {\n\
    \            return DP{ x.first + a, x.second + 1 };\n        }\n    );\n\n  \
    \  for (const DP& v : ans) {\n        std::cout << v.first << ' ';\n    }\n  \
    \  std::cout << '\\n';\n}"
  dependsOn:
  - library/tree/rerooting.hpp
  isVerificationFile: true
  path: test/src/tree/rerooting/tree_path_composite_sum.test.cpp
  requiredBy: []
  timestamp: '2023-05-11 13:28:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/rerooting/tree_path_composite_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/rerooting/tree_path_composite_sum.test.cpp
- /verify/test/src/tree/rerooting/tree_path_composite_sum.test.cpp.html
title: test/src/tree/rerooting/tree_path_composite_sum.test.cpp
---
