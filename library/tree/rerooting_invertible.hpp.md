---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/rerooting_invertible/abc160_f.test.cpp
    title: test/src/tree/rerooting_invertible/abc160_f.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/rerooting_invertible.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <tuple>\n#include <vector>\n#include <variant>\n\nnamespace\
    \ suisen {\n    namespace internal::rerooting {\n        using void_weight = std::monostate;\n\
    \n        template <typename VertexWeight, typename EdgeWeight>\n        struct\
    \ RerootingInvertible {\n            using vertex_weight = VertexWeight;\n   \
    \         using edge_weight = EdgeWeight;\n    private:\n            using is_vertex_weight_void\
    \ = std::is_same<vertex_weight, void_weight>;\n            using is_edge_weight_void\
    \ = std::is_same<edge_weight, void_weight>;\n            static constexpr bool\
    \ is_vertex_weight_void_v = is_vertex_weight_void::value;\n            static\
    \ constexpr bool is_edge_weight_void_v = is_edge_weight_void::value;\n\n     \
    \       template <typename DP, typename AddSubtreeRoot>\n            using is_add_subtree_root\
    \ = std::conditional_t<\n                std::negation_v<is_vertex_weight_void>,\n\
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
    \            RerootingInvertible() : _w{} {}\n            explicit RerootingInvertible(int\
    \ n) : _w(n) {}\n            explicit RerootingInvertible(const std::vector<vertex_weight>&\
    \ w) : _w(w) {}\n\n            void reserve(int n) {\n                _w.reserve(n);\n\
    \            }\n\n            void add_vertex(const vertex_weight& w) {\n    \
    \            _w.emplace_back(w);\n            }\n            void add_edge(int\
    \ u, int v, const edge_weight& w = {}) {\n                const int n = _w.size();\n\
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
    \ typename Inv, typename AddSubtreeRoot, typename AddRoot,\n                typename\
    \ DP = std::decay_t<std::invoke_result_t<E>>,\n                std::enable_if_t<std::conjunction_v<\n\
    \                    std::is_invocable_r<DP, Op, DP, DP>,\n                  \
    \  std::is_invocable_r<DP, E>,\n                    std::is_invocable_r<DP, Inv,\
    \ DP>,\n                    is_add_subtree_root<DP, AddSubtreeRoot>,\n       \
    \             is_add_root<DP, AddRoot>\n                >, std::nullptr_t> = nullptr\n\
    \            >\n            std::vector<DP> run_dp(const Op& op, const E& e, const\
    \ Inv &inv, const AddSubtreeRoot& add_subtree_root, const AddRoot& add_root) const\
    \ {\n                auto add_subtree_root_ = [&add_subtree_root](const DP &val,\
    \ const vertex_weight& vw, const edge_weight& ew) {\n                    if constexpr\
    \ (std::negation_v<is_vertex_weight_void>) {\n                        if constexpr\
    \ (std::negation_v<is_edge_weight_void>) {\n                            return\
    \ add_subtree_root(val, vw, ew);\n                        } else {\n         \
    \                   return add_subtree_root(val, vw);\n                      \
    \  }\n                    } else {\n                        if constexpr (std::negation_v<is_edge_weight_void>)\
    \ {\n                            return add_subtree_root(val, ew);\n         \
    \               } else {\n                            return add_subtree_root(val);\n\
    \                        }\n                    }\n                };\n      \
    \          auto add_root_ = [&add_root](const DP &val, const vertex_weight& vw)\
    \ {\n                    if constexpr (std::negation_v<is_vertex_weight_void>)\
    \ {\n                        return add_root(val, vw);\n                    }\
    \ else {\n                        return add_root(val);\n                    }\n\
    \                };\n\n                const int n = _w.size();\n\n          \
    \      GraphCSR g(n, _e);\n\n                std::vector<DP> dp(n, e());\n\n \
    \               [dfs = [&, this](auto dfs, int u, int p) -> void {\n         \
    \           for (const auto& [v, w] : g[u]) if (v != p) {\n                  \
    \      dfs(dfs, v, u);\n                        dp[u] = op(dp[u], add_subtree_root_(dp[v],\
    \ _w[v], w));\n                    }\n                }] { dfs(dfs, 0, -1); }();\n\
    \                [dfs = [&, this](auto dfs, int u, int p) -> void {\n        \
    \            for (const auto& [v, w] : g[u]) if (v != p) {\n                 \
    \       DP sum_u = op(dp[u], inv(add_subtree_root_(dp[v], _w[v], w)));\n     \
    \                   dp[v] = op(dp[v], add_subtree_root_(sum_u, _w[u], w));\n \
    \                       dfs(dfs, v, u);\n                    }\n             \
    \       dp[u] = add_root_(dp[u], _w[u]);\n                }] { dfs(dfs, 0, -1);\
    \ }();\n                return dp;\n            }\n\n        private:\n      \
    \      std::vector<vertex_weight> _w;\n            std::vector<std::tuple<int,\
    \ int, edge_weight>> _e;\n\n            struct GraphCSR {\n                GraphCSR(int\
    \ n, const std::vector<std::tuple<int, int, edge_weight>>& edges) : _n(n), _m(edges.size()),\
    \ _edges(2 * _m), _start(_n + 1) {\n                    for (const auto& [u, v,\
    \ w] : edges) {\n                        ++_start[u];\n                      \
    \  ++_start[v];\n                    }\n                    for (int i = 1; i\
    \ <= _n; ++i) {\n                        _start[i] += _start[i - 1];\n       \
    \             }\n                    for (const auto& [u, v, w] : edges) {\n \
    \                       _edges[--_start[u]] = { v, w };\n                    \
    \    _edges[--_start[v]] = { u, w };\n                    }\n                }\n\
    \            private:\n                using edge_type = std::pair<int, edge_weight>;\n\
    \                using iterator = typename std::vector<edge_type>::const_iterator;\n\
    \n                struct AdjacentListView {\n                    AdjacentListView(const\
    \ iterator& l, const iterator& r) : _l(l), _r(r) {}\n\n                    int\
    \ size() const { return _r - _l; }\n\n                    const edge_type& operator[](int\
    \ i) const { return *(_l + i); }\n\n                    iterator begin() const\
    \ { return _l; }\n                    iterator end() const { return _r; }\n  \
    \              private:\n                    iterator _l, _r;\n              \
    \  };\n            public:\n                AdjacentListView operator[](int u)\
    \ const {\n                    return AdjacentListView(_edges.begin() + _start[u],\
    \ _edges.begin() + _start[u + 1]);\n                }\n            private:\n\
    \                int _n, _m;\n                std::vector<std::pair<int, edge_weight>>\
    \ _edges;\n                std::vector<int> _start;\n            };\n        };\n\
    \    }\n    using RerootingInvertible = internal::rerooting::RerootingInvertible<internal::rerooting::void_weight,\
    \ internal::rerooting::void_weight>;\n    template <typename VertexWeight>\n \
    \   using RerootingInvertibleVertexWeighted = internal::rerooting::RerootingInvertible<VertexWeight,\
    \ internal::rerooting::void_weight>;\n    template <typename EdgeWeight>\n   \
    \ using RerootingInvertibleEdgeWeighted = internal::rerooting::RerootingInvertible<internal::rerooting::void_weight,\
    \ EdgeWeight>;\n    template <typename VertexWeight, typename EdgeWeighted>\n\
    \    using RerootingInvertibleWeighted = internal::rerooting::RerootingInvertible<VertexWeight,\
    \ EdgeWeighted>;\n} // namsepace suisen\n\n\n"
  code: "#ifndef SUISEN_REROOTING\n#define SUISEN_REROOTING\n\n#include <cassert>\n\
    #include <tuple>\n#include <vector>\n#include <variant>\n\nnamespace suisen {\n\
    \    namespace internal::rerooting {\n        using void_weight = std::monostate;\n\
    \n        template <typename VertexWeight, typename EdgeWeight>\n        struct\
    \ RerootingInvertible {\n            using vertex_weight = VertexWeight;\n   \
    \         using edge_weight = EdgeWeight;\n    private:\n            using is_vertex_weight_void\
    \ = std::is_same<vertex_weight, void_weight>;\n            using is_edge_weight_void\
    \ = std::is_same<edge_weight, void_weight>;\n            static constexpr bool\
    \ is_vertex_weight_void_v = is_vertex_weight_void::value;\n            static\
    \ constexpr bool is_edge_weight_void_v = is_edge_weight_void::value;\n\n     \
    \       template <typename DP, typename AddSubtreeRoot>\n            using is_add_subtree_root\
    \ = std::conditional_t<\n                std::negation_v<is_vertex_weight_void>,\n\
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
    \            RerootingInvertible() : _w{} {}\n            explicit RerootingInvertible(int\
    \ n) : _w(n) {}\n            explicit RerootingInvertible(const std::vector<vertex_weight>&\
    \ w) : _w(w) {}\n\n            void reserve(int n) {\n                _w.reserve(n);\n\
    \            }\n\n            void add_vertex(const vertex_weight& w) {\n    \
    \            _w.emplace_back(w);\n            }\n            void add_edge(int\
    \ u, int v, const edge_weight& w = {}) {\n                const int n = _w.size();\n\
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
    \ typename Inv, typename AddSubtreeRoot, typename AddRoot,\n                typename\
    \ DP = std::decay_t<std::invoke_result_t<E>>,\n                std::enable_if_t<std::conjunction_v<\n\
    \                    std::is_invocable_r<DP, Op, DP, DP>,\n                  \
    \  std::is_invocable_r<DP, E>,\n                    std::is_invocable_r<DP, Inv,\
    \ DP>,\n                    is_add_subtree_root<DP, AddSubtreeRoot>,\n       \
    \             is_add_root<DP, AddRoot>\n                >, std::nullptr_t> = nullptr\n\
    \            >\n            std::vector<DP> run_dp(const Op& op, const E& e, const\
    \ Inv &inv, const AddSubtreeRoot& add_subtree_root, const AddRoot& add_root) const\
    \ {\n                auto add_subtree_root_ = [&add_subtree_root](const DP &val,\
    \ const vertex_weight& vw, const edge_weight& ew) {\n                    if constexpr\
    \ (std::negation_v<is_vertex_weight_void>) {\n                        if constexpr\
    \ (std::negation_v<is_edge_weight_void>) {\n                            return\
    \ add_subtree_root(val, vw, ew);\n                        } else {\n         \
    \                   return add_subtree_root(val, vw);\n                      \
    \  }\n                    } else {\n                        if constexpr (std::negation_v<is_edge_weight_void>)\
    \ {\n                            return add_subtree_root(val, ew);\n         \
    \               } else {\n                            return add_subtree_root(val);\n\
    \                        }\n                    }\n                };\n      \
    \          auto add_root_ = [&add_root](const DP &val, const vertex_weight& vw)\
    \ {\n                    if constexpr (std::negation_v<is_vertex_weight_void>)\
    \ {\n                        return add_root(val, vw);\n                    }\
    \ else {\n                        return add_root(val);\n                    }\n\
    \                };\n\n                const int n = _w.size();\n\n          \
    \      GraphCSR g(n, _e);\n\n                std::vector<DP> dp(n, e());\n\n \
    \               [dfs = [&, this](auto dfs, int u, int p) -> void {\n         \
    \           for (const auto& [v, w] : g[u]) if (v != p) {\n                  \
    \      dfs(dfs, v, u);\n                        dp[u] = op(dp[u], add_subtree_root_(dp[v],\
    \ _w[v], w));\n                    }\n                }] { dfs(dfs, 0, -1); }();\n\
    \                [dfs = [&, this](auto dfs, int u, int p) -> void {\n        \
    \            for (const auto& [v, w] : g[u]) if (v != p) {\n                 \
    \       DP sum_u = op(dp[u], inv(add_subtree_root_(dp[v], _w[v], w)));\n     \
    \                   dp[v] = op(dp[v], add_subtree_root_(sum_u, _w[u], w));\n \
    \                       dfs(dfs, v, u);\n                    }\n             \
    \       dp[u] = add_root_(dp[u], _w[u]);\n                }] { dfs(dfs, 0, -1);\
    \ }();\n                return dp;\n            }\n\n        private:\n      \
    \      std::vector<vertex_weight> _w;\n            std::vector<std::tuple<int,\
    \ int, edge_weight>> _e;\n\n            struct GraphCSR {\n                GraphCSR(int\
    \ n, const std::vector<std::tuple<int, int, edge_weight>>& edges) : _n(n), _m(edges.size()),\
    \ _edges(2 * _m), _start(_n + 1) {\n                    for (const auto& [u, v,\
    \ w] : edges) {\n                        ++_start[u];\n                      \
    \  ++_start[v];\n                    }\n                    for (int i = 1; i\
    \ <= _n; ++i) {\n                        _start[i] += _start[i - 1];\n       \
    \             }\n                    for (const auto& [u, v, w] : edges) {\n \
    \                       _edges[--_start[u]] = { v, w };\n                    \
    \    _edges[--_start[v]] = { u, w };\n                    }\n                }\n\
    \            private:\n                using edge_type = std::pair<int, edge_weight>;\n\
    \                using iterator = typename std::vector<edge_type>::const_iterator;\n\
    \n                struct AdjacentListView {\n                    AdjacentListView(const\
    \ iterator& l, const iterator& r) : _l(l), _r(r) {}\n\n                    int\
    \ size() const { return _r - _l; }\n\n                    const edge_type& operator[](int\
    \ i) const { return *(_l + i); }\n\n                    iterator begin() const\
    \ { return _l; }\n                    iterator end() const { return _r; }\n  \
    \              private:\n                    iterator _l, _r;\n              \
    \  };\n            public:\n                AdjacentListView operator[](int u)\
    \ const {\n                    return AdjacentListView(_edges.begin() + _start[u],\
    \ _edges.begin() + _start[u + 1]);\n                }\n            private:\n\
    \                int _n, _m;\n                std::vector<std::pair<int, edge_weight>>\
    \ _edges;\n                std::vector<int> _start;\n            };\n        };\n\
    \    }\n    using RerootingInvertible = internal::rerooting::RerootingInvertible<internal::rerooting::void_weight,\
    \ internal::rerooting::void_weight>;\n    template <typename VertexWeight>\n \
    \   using RerootingInvertibleVertexWeighted = internal::rerooting::RerootingInvertible<VertexWeight,\
    \ internal::rerooting::void_weight>;\n    template <typename EdgeWeight>\n   \
    \ using RerootingInvertibleEdgeWeighted = internal::rerooting::RerootingInvertible<internal::rerooting::void_weight,\
    \ EdgeWeight>;\n    template <typename VertexWeight, typename EdgeWeighted>\n\
    \    using RerootingInvertibleWeighted = internal::rerooting::RerootingInvertible<VertexWeight,\
    \ EdgeWeighted>;\n} // namsepace suisen\n\n#endif // SUISEN_REROOTING\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/rerooting_invertible.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:24:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/rerooting_invertible/abc160_f.test.cpp
documentation_of: library/tree/rerooting_invertible.hpp
layout: document
title: Rerooting Invertible
---
## Rerooting Invertible