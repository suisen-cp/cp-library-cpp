---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/graph/two_edge_connected_components.hpp
    title: Two Edge Connected Components
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/low_link/articulation_points.test.cpp
    title: test/src/graph/low_link/articulation_points.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/low_link/bridges.test.cpp
    title: test/src/graph/low_link/bridges.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
    title: test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    struct LowLink {\n        using Graph = std::vector<std::vector<std::pair<int,\
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
    \            }\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_LOW_LINK\n#define SUISEN_LOW_LINK\n\n#include <vector>\n\n\
    namespace suisen {\n    struct LowLink {\n        using Graph = std::vector<std::vector<std::pair<int,\
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
    \            }\n        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_LOW_LINK\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/low_link.hpp
  requiredBy:
  - library/graph/two_edge_connected_components.hpp
  timestamp: '2021-10-22 11:27:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
  - test/src/graph/low_link/articulation_points.test.cpp
  - test/src/graph/low_link/bridges.test.cpp
documentation_of: library/graph/low_link.hpp
layout: document
title: Low Link
---
## Low Link