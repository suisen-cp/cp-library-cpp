---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/graph/biconnected_components.hpp
    title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':warning:'
    path: library/graph/block_cut_forest.hpp
    title: Block Cut Forest
  - icon: ':heavy_check_mark:'
    path: library/graph/two_edge_connected_components.hpp
    title: "\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/biconnected_components/biconnected_components.test.cpp
    title: test/src/graph/biconnected_components/biconnected_components.test.cpp
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
  bundledCode: "#line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    struct LowLink {\n        LowLink()\
    \ : LowLink(0) {}\n        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n,\
    \ -1), _low_link(n), _built(false) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) : LowLink(n) {\n            for (const auto &[u, v] : edges) add_edge(u,\
    \ v);\n            build();\n        }\n        \n        int add_edge(int u,\
    \ int v) {\n            _built = false;\n            _edges.emplace_back(u, v);\n\
    \            _g[u].emplace_back(v, _m);\n            _g[v].emplace_back(u, _m);\n\
    \            return _m++;\n        }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
    \            _built = true;\n        }\n\n        int vertex_num() const { return\
    \ _n; }\n        int edge_num()   const { return _m; }\n\n        const std::pair<int,\
    \ int>& edge(int edge_id) const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
    \ int>>& edges() const { return _edges; }\n        \n        int pre_order(int\
    \ v) const {\n            assert(_built);\n            return _pre_order[v];\n\
    \        }\n        int low_link(int v) const {\n            assert(_built);\n\
    \            return _low_link[v];\n        }\n\n        const std::vector<int>&\
    \ bridge_ids() const {\n            assert(_built);\n            return _bridges;\n\
    \        }\n        const std::vector<int>& articulation_points() const {\n  \
    \          assert(_built);\n            return _articulation_points;\n       \
    \ }\n\n    protected:\n        int _n, _m;\n        // list of edges\n       \
    \ std::vector<std::pair<int, int>> _edges;\n        // vertex -> list of (adjacent\
    \ vertex, edge id)\n        std::vector<std::vector<std::pair<int, int>>> _g;\n\
    \        // vertex -> pre order\n        std::vector<int> _pre_order;\n      \
    \  std::vector<int> _low_link;\n        // list of ids of bridges\n        std::vector<int>\
    \ _bridges;\n        std::vector<int> _articulation_points;\n\n        bool _built;\n\
    \n    private:\n        void dfs(int u, int id, int& ord) {\n            bool\
    \ is_root = id < 0;\n            bool is_articulation_point = false;\n       \
    \     int ch_cnt = 0;\n            _pre_order[u] = _low_link[u] = ord++;\n   \
    \         for (const auto& [v, id2] : _g[u]) {\n                if (id == id2)\
    \ continue;\n                if (_pre_order[v] < 0) {\n                    ++ch_cnt;\n\
    \                    dfs(v, id2, ord);\n                    _low_link[u] = std::min(_low_link[u],\
    \ _low_link[v]);\n                    if (_pre_order[u] <= _low_link[v]) {\n \
    \                       is_articulation_point = not is_root;\n               \
    \         if (_pre_order[u] != _low_link[v]) _bridges.push_back(id2);\n      \
    \              }\n                } else {\n                    _low_link[u] =\
    \ std::min(_low_link[u], _pre_order[v]);\n                }\n            }\n \
    \           if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);\n\
    \        }\n\n        void dfs_for_all_connected_components() {\n            for\
    \ (int i = 0, ord = 0; i < _n; ++i) {\n                if (_pre_order[i] < 0)\
    \ dfs(i, -1, ord);\n            }\n        }\n    };\n} // namespace suisen\n\n\
    \n\n"
  code: "#ifndef SUISEN_LOW_LINK\n#define SUISEN_LOW_LINK\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace suisen {\n    struct LowLink {\n        LowLink()\
    \ : LowLink(0) {}\n        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n,\
    \ -1), _low_link(n), _built(false) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) : LowLink(n) {\n            for (const auto &[u, v] : edges) add_edge(u,\
    \ v);\n            build();\n        }\n        \n        int add_edge(int u,\
    \ int v) {\n            _built = false;\n            _edges.emplace_back(u, v);\n\
    \            _g[u].emplace_back(v, _m);\n            _g[v].emplace_back(u, _m);\n\
    \            return _m++;\n        }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
    \            _built = true;\n        }\n\n        int vertex_num() const { return\
    \ _n; }\n        int edge_num()   const { return _m; }\n\n        const std::pair<int,\
    \ int>& edge(int edge_id) const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
    \ int>>& edges() const { return _edges; }\n        \n        int pre_order(int\
    \ v) const {\n            assert(_built);\n            return _pre_order[v];\n\
    \        }\n        int low_link(int v) const {\n            assert(_built);\n\
    \            return _low_link[v];\n        }\n\n        const std::vector<int>&\
    \ bridge_ids() const {\n            assert(_built);\n            return _bridges;\n\
    \        }\n        const std::vector<int>& articulation_points() const {\n  \
    \          assert(_built);\n            return _articulation_points;\n       \
    \ }\n\n    protected:\n        int _n, _m;\n        // list of edges\n       \
    \ std::vector<std::pair<int, int>> _edges;\n        // vertex -> list of (adjacent\
    \ vertex, edge id)\n        std::vector<std::vector<std::pair<int, int>>> _g;\n\
    \        // vertex -> pre order\n        std::vector<int> _pre_order;\n      \
    \  std::vector<int> _low_link;\n        // list of ids of bridges\n        std::vector<int>\
    \ _bridges;\n        std::vector<int> _articulation_points;\n\n        bool _built;\n\
    \n    private:\n        void dfs(int u, int id, int& ord) {\n            bool\
    \ is_root = id < 0;\n            bool is_articulation_point = false;\n       \
    \     int ch_cnt = 0;\n            _pre_order[u] = _low_link[u] = ord++;\n   \
    \         for (const auto& [v, id2] : _g[u]) {\n                if (id == id2)\
    \ continue;\n                if (_pre_order[v] < 0) {\n                    ++ch_cnt;\n\
    \                    dfs(v, id2, ord);\n                    _low_link[u] = std::min(_low_link[u],\
    \ _low_link[v]);\n                    if (_pre_order[u] <= _low_link[v]) {\n \
    \                       is_articulation_point = not is_root;\n               \
    \         if (_pre_order[u] != _low_link[v]) _bridges.push_back(id2);\n      \
    \              }\n                } else {\n                    _low_link[u] =\
    \ std::min(_low_link[u], _pre_order[v]);\n                }\n            }\n \
    \           if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);\n\
    \        }\n\n        void dfs_for_all_connected_components() {\n            for\
    \ (int i = 0, ord = 0; i < _n; ++i) {\n                if (_pre_order[i] < 0)\
    \ dfs(i, -1, ord);\n            }\n        }\n    };\n} // namespace suisen\n\n\
    \n#endif // SUISEN_LOW_LINK\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/low_link.hpp
  requiredBy:
  - library/graph/two_edge_connected_components.hpp
  - library/graph/block_cut_forest.hpp
  - library/graph/biconnected_components.hpp
  timestamp: '2022-05-05 17:37:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
  - test/src/graph/low_link/bridges.test.cpp
  - test/src/graph/low_link/articulation_points.test.cpp
  - test/src/graph/biconnected_components/biconnected_components.test.cpp
documentation_of: library/graph/low_link.hpp
layout: document
title: Low Link
---
## Low Link

橋や関節点を求めるのに用いる。
