---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/low_link.hpp
    title: library/graph/low_link.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
    title: test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/two_edge_connected_components.hpp\"\n\n\n\n\
    #line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <vector>\n\nnamespace suisen\
    \ {\n    struct LowLink {\n        using Graph = std::vector<std::vector<std::pair<int,\
    \ int>>>;\n\n        int n, m;\n        // vertex -> list of (adjacent vertex,\
    \ edge id)\n        Graph g;\n        // vertex -> pre order\n        std::vector<int>\
    \ pre_order;\n        std::vector<int> low_link;\n        // list of ids of bridges\n\
    \        std::vector<int> bridges;\n        std::vector<int> articulation_points;\n\
    \n        LowLink() : LowLink(0, {}) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) : LowLink(n, edges.size(), [&edges](int i) { return edges[i];\
    \ }) {}\n        template <typename EdgeGenerator>\n        LowLink(const int\
    \ n, const int m, EdgeGenerator edge_gen) : n(n), m(m), g(n), pre_order(n, -1),\
    \ low_link(n) {\n            build_graph(edge_gen);\n            dfs_for_all_connected_components();\n\
    \        }\n    private:\n        template <typename EdgeGenerator>\n        void\
    \ build_graph(EdgeGenerator edge_gen) {\n            for (int i = 0; i < m; ++i)\
    \ {\n                auto&& [u, v] = edge_gen(i);\n                g[u].emplace_back(v,\
    \ i);\n                g[v].emplace_back(u, i);\n            }\n        }\n\n\
    \        void dfs(int u, int id, int& ord) {\n            bool is_root = id <\
    \ 0;\n            bool is_articulation_point = false;\n            int ch_cnt\
    \ = 0;\n            pre_order[u] = low_link[u] = ord++;\n            for (const\
    \ auto& [v, id2] : g[u]) {\n                if (id == id2) continue;\n       \
    \         if (pre_order[v] < 0) {\n                    ++ch_cnt;\n           \
    \         dfs(v, id2, ord);\n                    low_link[u] = std::min(low_link[u],\
    \ low_link[v]);\n                    if (pre_order[u] <= low_link[v]) {\n    \
    \                    is_articulation_point = not is_root;\n                  \
    \      if (pre_order[u] != low_link[v]) bridges.push_back(id2);\n            \
    \        }\n                } else {\n                    low_link[u] = std::min(low_link[u],\
    \ pre_order[v]);\n                }\n            }\n            if (is_articulation_point\
    \ or (is_root and ch_cnt > 1)) articulation_points.push_back(u);\n        }\n\n\
    \        void dfs_for_all_connected_components() {\n            for (int i = 0,\
    \ ord = 0; i < n; ++i) {\n                if (pre_order[i] < 0) dfs(i, -1, ord);\n\
    \            }\n        }\n    };\n} // namespace suisen\n\n\n\n#line 5 \"library/graph/two_edge_connected_components.hpp\"\
    \n\nnamespace suisen {\n    struct TwoEdgeConnectedComponents : LowLink {\n  \
    \      std::vector<int> comp_id;\n        int comp_num;\n\n        TwoEdgeConnectedComponents()\
    \ : \n            TwoEdgeConnectedComponents(0, {}) {}\n\n        TwoEdgeConnectedComponents(const\
    \ int n, const std::vector<std::pair<int, int>> &edges) : \n            TwoEdgeConnectedComponents(n,\
    \ edges.size(), [&edges](int i) { return edges[i]; }) {}\n\n        template <typename\
    \ EdgeGenerator>\n        TwoEdgeConnectedComponents(const int n, const int m,\
    \ EdgeGenerator edge_gen) : \n            LowLink(n, m, edge_gen), comp_id(n,\
    \ -1), comp_num(0) { dfs_for_all_connected_components(); }\n        \n       \
    \ int operator[](int v) const {\n            return comp_id[v];\n        }\n\n\
    \        Graph reduced_forest() const {\n            Graph reduced(comp_num);\n\
    \            for (int u = 0; u < n; ++u) {\n                for (const auto &[v,\
    \ edge_id] : g[u]) {\n                    const int comp_u = (*this)[u], comp_v\
    \ = (*this)[v];\n                    if (comp_u != comp_v) reduced[comp_u].emplace_back(comp_v,\
    \ edge_id);\n                }\n            }\n            return reduced;\n \
    \       }\n\n    private:\n        void dfs(int u, int p) {\n            if (p\
    \ >= 0 and low_link[u] <= pre_order[p]) {\n                comp_id[u] = comp_id[p];\n\
    \            } else {\n                comp_id[u] = comp_num++;\n            }\n\
    \            for (const auto &e : g[u]) {\n                const int v = e.first;\n\
    \                if (comp_id[v] < 0) dfs(v, u);\n            }\n        }\n  \
    \      void dfs_for_all_connected_components() {\n            for (int i = 0;\
    \ i < n; ++i) {\n                if (comp_id[i] < 0) dfs(i, -1);\n           \
    \ }\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n#define SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n\
    \n#include \"library/graph/low_link.hpp\"\n\nnamespace suisen {\n    struct TwoEdgeConnectedComponents\
    \ : LowLink {\n        std::vector<int> comp_id;\n        int comp_num;\n\n  \
    \      TwoEdgeConnectedComponents() : \n            TwoEdgeConnectedComponents(0,\
    \ {}) {}\n\n        TwoEdgeConnectedComponents(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) : \n            TwoEdgeConnectedComponents(n, edges.size(), [&edges](int\
    \ i) { return edges[i]; }) {}\n\n        template <typename EdgeGenerator>\n \
    \       TwoEdgeConnectedComponents(const int n, const int m, EdgeGenerator edge_gen)\
    \ : \n            LowLink(n, m, edge_gen), comp_id(n, -1), comp_num(0) { dfs_for_all_connected_components();\
    \ }\n        \n        int operator[](int v) const {\n            return comp_id[v];\n\
    \        }\n\n        Graph reduced_forest() const {\n            Graph reduced(comp_num);\n\
    \            for (int u = 0; u < n; ++u) {\n                for (const auto &[v,\
    \ edge_id] : g[u]) {\n                    const int comp_u = (*this)[u], comp_v\
    \ = (*this)[v];\n                    if (comp_u != comp_v) reduced[comp_u].emplace_back(comp_v,\
    \ edge_id);\n                }\n            }\n            return reduced;\n \
    \       }\n\n    private:\n        void dfs(int u, int p) {\n            if (p\
    \ >= 0 and low_link[u] <= pre_order[p]) {\n                comp_id[u] = comp_id[p];\n\
    \            } else {\n                comp_id[u] = comp_num++;\n            }\n\
    \            for (const auto &e : g[u]) {\n                const int v = e.first;\n\
    \                if (comp_id[v] < 0) dfs(v, u);\n            }\n        }\n  \
    \      void dfs_for_all_connected_components() {\n            for (int i = 0;\
    \ i < n; ++i) {\n                if (comp_id[i] < 0) dfs(i, -1);\n           \
    \ }\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: false
  path: library/graph/two_edge_connected_components.hpp
  requiredBy: []
  timestamp: '2021-10-22 11:27:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
documentation_of: library/graph/two_edge_connected_components.hpp
layout: document
redirect_from:
- /library/library/graph/two_edge_connected_components.hpp
- /library/library/graph/two_edge_connected_components.hpp.html
title: library/graph/two_edge_connected_components.hpp
---
