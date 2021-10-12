---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/rerooting/abc160_f.test.cpp
    title: test/src/tree/rerooting/abc160_f.test.cpp
  - icon: ':x:'
    path: test/src/tree/rerooting/abc222_f.test.cpp
    title: test/src/tree/rerooting/abc222_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/rerooting/edpc_v.test.cpp
    title: test/src/tree/rerooting/edpc_v.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/rerooting.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    template <\n        // type of DP array elements\n   \
    \     typename dp_value_type,\n        // merge children\n        dp_value_type(*op)(dp_value_type,\
    \ dp_value_type),\n        // identity element of op\n        dp_value_type(*e)(),\n\
    \        // add info as a root of subtree\n        dp_value_type(*add_subtree_root)(dp_value_type,\
    \ int, int),\n        // type of weights on the edges\n        typename edge_data_type,\n\
    \        // transition from child to parent using edge weight; trans_to_par(dp[child],\
    \ parent, child, weight(parent, child))\n        dp_value_type(*trans_to_par)(dp_value_type,\
    \ int, int, edge_data_type)\n    >\n    struct ReRooting : public std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>> {\n        using base_type = std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>>;\n        public:\n            using base_type::base_type;\n\
    \n            void add_edge(int u, int v, const edge_data_type& w) {\n       \
    \         (*this)[u].emplace_back(v, w);\n                (*this)[v].emplace_back(u,\
    \ w);\n            }\n\n            const std::vector<dp_value_type>& rerooting()\
    \ {\n                const int n = this->size();\n                dp.resize(n),\
    \ to_par.resize(n);\n                dfs_subtree(0, -1);\n                dp[0]\
    \ = add_subtree_root(dp[0], 0, -1);\n                dfs(0, -1, e());\n      \
    \          return dp;\n            }\n\n        private:\n            std::vector<dp_value_type>\
    \ dp, to_par;\n\n            void dfs_subtree(int u, int p) {\n              \
    \  dp[u] = e();\n                for (auto [v, w] : (*this)[u]) {\n          \
    \          if (v == p) continue;\n                    dfs_subtree(v, u);\n   \
    \                 dp[u] = op(dp[u], to_par[v] = trans_to_par(add_subtree_root(dp[v],\
    \ v, u), u, v, w));\n                }\n            }\n            void dfs(int\
    \ u, int p, dp_value_type from_p) {\n                const int sz = (*this)[u].size();\n\
    \                // cumulative sum from left to right\n                std::vector<dp_value_type>\
    \ cum_l;\n                cum_l.reserve(sz + 1);\n                cum_l.push_back(e());\n\
    \                for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(),\
    \ v == p ? from_p : to_par[v]));\n                // cumulative sum from right\
    \ to left\n                dp_value_type cum_r = e();\n                for (int\
    \ i = sz - 1; i >= 0; --i) {\n                    const auto& [v, w] = (*this)[u][i];\n\
    \                    if (v == p) {\n                        cum_r = op(from_p,\
    \ cum_r);\n                    } else {\n                        dp_value_type\
    \ from_u = trans_to_par(add_subtree_root(op(cum_l[i], cum_r), u, v), v, u, w);\n\
    \                        dp[v] = add_subtree_root(op(dp[v], from_u), v, -1);\n\
    \                        dfs(v, u, from_u);\n                        cum_r = op(to_par[v],\
    \ cum_r);\n                    }\n                }\n            }\n    };\n}\
    \ // namsepace suisen\n\n\n"
  code: "#ifndef SUISEN_REROOTING\n#define SUISEN_REROOTING\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <\n        // type of DP array elements\n \
    \       typename dp_value_type,\n        // merge children\n        dp_value_type(*op)(dp_value_type,\
    \ dp_value_type),\n        // identity element of op\n        dp_value_type(*e)(),\n\
    \        // add info as a root of subtree\n        dp_value_type(*add_subtree_root)(dp_value_type,\
    \ int, int),\n        // type of weights on the edges\n        typename edge_data_type,\n\
    \        // transition from child to parent using edge weight; trans_to_par(dp[child],\
    \ parent, child, weight(parent, child))\n        dp_value_type(*trans_to_par)(dp_value_type,\
    \ int, int, edge_data_type)\n    >\n    struct ReRooting : public std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>> {\n        using base_type = std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>>;\n        public:\n            using base_type::base_type;\n\
    \n            void add_edge(int u, int v, const edge_data_type& w) {\n       \
    \         (*this)[u].emplace_back(v, w);\n                (*this)[v].emplace_back(u,\
    \ w);\n            }\n\n            const std::vector<dp_value_type>& rerooting()\
    \ {\n                const int n = this->size();\n                dp.resize(n),\
    \ to_par.resize(n);\n                dfs_subtree(0, -1);\n                dp[0]\
    \ = add_subtree_root(dp[0], 0, -1);\n                dfs(0, -1, e());\n      \
    \          return dp;\n            }\n\n        private:\n            std::vector<dp_value_type>\
    \ dp, to_par;\n\n            void dfs_subtree(int u, int p) {\n              \
    \  dp[u] = e();\n                for (auto [v, w] : (*this)[u]) {\n          \
    \          if (v == p) continue;\n                    dfs_subtree(v, u);\n   \
    \                 dp[u] = op(dp[u], to_par[v] = trans_to_par(add_subtree_root(dp[v],\
    \ v, u), u, v, w));\n                }\n            }\n            void dfs(int\
    \ u, int p, dp_value_type from_p) {\n                const int sz = (*this)[u].size();\n\
    \                // cumulative sum from left to right\n                std::vector<dp_value_type>\
    \ cum_l;\n                cum_l.reserve(sz + 1);\n                cum_l.push_back(e());\n\
    \                for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(),\
    \ v == p ? from_p : to_par[v]));\n                // cumulative sum from right\
    \ to left\n                dp_value_type cum_r = e();\n                for (int\
    \ i = sz - 1; i >= 0; --i) {\n                    const auto& [v, w] = (*this)[u][i];\n\
    \                    if (v == p) {\n                        cum_r = op(from_p,\
    \ cum_r);\n                    } else {\n                        dp_value_type\
    \ from_u = trans_to_par(add_subtree_root(op(cum_l[i], cum_r), u, v), v, u, w);\n\
    \                        dp[v] = add_subtree_root(op(dp[v], from_u), v, -1);\n\
    \                        dfs(v, u, from_u);\n                        cum_r = op(to_par[v],\
    \ cum_r);\n                    }\n                }\n            }\n    };\n}\
    \ // namsepace suisen\n\n#endif // SUISEN_REROOTING\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/rerooting.hpp
  requiredBy: []
  timestamp: '2021-10-12 21:18:57+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/tree/rerooting/abc222_f.test.cpp
  - test/src/tree/rerooting/abc160_f.test.cpp
  - test/src/tree/rerooting/edpc_v.test.cpp
documentation_of: library/tree/rerooting.hpp
layout: document
redirect_from:
- /library/library/tree/rerooting.hpp
- /library/library/tree/rerooting.hpp.html
title: library/tree/rerooting.hpp
---
