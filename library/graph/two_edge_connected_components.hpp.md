---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/low_link.hpp
    title: Low Link
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
    #line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <utility>\n#include <vector>\n\nnamespace suisen\
    \ {\n    struct LowLink {\n        LowLink() : LowLink(0) {}\n        LowLink(const\
    \ int n) : _n(n), _m(0), _g(n), _pre_order(n, -1), _low_link(n), _built(false),\
    \ _conn_comp_num(0), _par(n, -1) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) : LowLink(n) {\n            for (const auto &[u, v] : edges) add_edge(u,\
    \ v);\n            build();\n        }\n        \n        // Add an edge and return\
    \ its ID. IDs are assigned in the order (0,1,2, ...).\n        int add_edge(int\
    \ u, int v) {\n            _built = false;\n            _edges.emplace_back(u,\
    \ v);\n            _g[u].emplace_back(v, _m);\n            _g[v].emplace_back(u,\
    \ _m);\n            return _m++;\n        }\n\n        void build() {\n      \
    \      dfs_for_all_connected_components();\n            _built = true;\n     \
    \   }\n\n        int vertex_num() const { return _n; }\n        int edge_num()\
    \   const { return _m; }\n\n        const std::pair<int, int>& edge(int edge_id)\
    \ const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
    \ int>>& edges() const { return _edges; }\n        // list of edges { u, edge_id\
    \ } adjacent to the vertex v.\n        const std::vector<std::pair<int, int>>&\
    \ operator[](int v) const { return _g[v]; }\n        \n        int pre_order(int\
    \ v) const {\n            assert(_built);\n            return _pre_order[v];\n\
    \        }\n        int low_link(int v) const {\n            assert(_built);\n\
    \            return _low_link[v];\n        }\n\n        // Returns IDs of bridges.\n\
    \        const std::vector<int>& bridge_ids() const {\n            assert(_built);\n\
    \            return _bridges;\n        }\n        const std::vector<int>& articulation_points()\
    \ const {\n            assert(_built);\n            return _articulation_points;\n\
    \        }\n\n        // O(1)\n        // Assuming that there exists the edge\
    \ {u,v}, return whether the edge is a bridge or not.\n        bool is_bridge(int\
    \ u, int v) const {\n            assert(_built);\n            if (_pre_order[u]\
    \ > _pre_order[v]) std::swap(u, v);\n            // u is an ancestor of v\n  \
    \          return _pre_order[u] < _low_link[v];\n        }\n\n        // O(# edges\
    \ incident with u)\n        // Return whether the vertex is a articulation point\
    \ or not.\n        bool is_articulation_point(int u) const {\n            assert(_built);\n\
    \            return connected_component_num_if_removed(u) > connected_component_num();\n\
    \        }\n\n        // Return the number of connected components\n        int\
    \ connected_component_num() const {\n            assert(_built);\n           \
    \ return _conn_comp_num;\n        }\n\n        // O(1)\n        // Assuming that\
    \ there exists the edge {u,v}, return the number of connected components of the\
    \ graph obtained by removing an edge {u,v}.\n        // If there are multiple\
    \ edges {u,v}, consider removing only one of them.\n        int connected_component_num_if_removed(int\
    \ u, int v) const {\n            assert(_built);\n            return _conn_comp_num\
    \ + is_bridge(u, v);\n        }\n\n        // O(# edges incident with u)\n   \
    \     // Return the number of connected components of the graph obtained by removing\
    \ an vertex u and edges incident with it.\n        int connected_component_num_if_removed(int\
    \ u) const {\n            assert(_built);\n            static std::vector<int8_t>\
    \ seen;\n            if (seen.size() < size_t(_n)) seen.resize(_n);\n        \
    \    bool is_root = true;\n            int res = 0;\n            for (const auto&\
    \ [v, _] : _g[u]) {\n                if (_pre_order[v] < _pre_order[u]) {\n  \
    \                  is_root = false;\n                    continue;\n         \
    \       }\n                if (_par[v] == u and not std::exchange(seen[v], true))\
    \ {\n                    res += (_pre_order[u] <= _low_link[v]);\n           \
    \     }\n            }\n            // rollback\n            for (const auto&\
    \ [v, _] : _g[u]) seen[v] = false;\n            return _conn_comp_num - 1 + res\
    \ + (not is_root);\n        }\n    protected:\n        int _n, _m;\n        //\
    \ list of edges\n        std::vector<std::pair<int, int>> _edges;\n        //\
    \ vertex -> list of (adjacent vertex, edge id)\n        std::vector<std::vector<std::pair<int,\
    \ int>>> _g;\n        // vertex -> pre order\n        std::vector<int> _pre_order;\n\
    \        std::vector<int> _low_link;\n        // list of ids of bridges\n    \
    \    std::vector<int> _bridges;\n        std::vector<int> _articulation_points;\n\
    \n        bool _built;\n\n    private:\n        // # connected components\n  \
    \      int _conn_comp_num;\n        std::vector<int> _par;\n\n        void dfs(const\
    \ int u, const int prev_id, int& ord) {\n            const bool is_root = prev_id\
    \ < 0;\n            bool is_articulation_point = false;\n            int ch_cnt\
    \ = 0;\n            _pre_order[u] = _low_link[u] = ord++;\n            for (const\
    \ auto& [v, id] : _g[u]) if (id != prev_id) {\n                if (_pre_order[v]\
    \ < 0) {\n                    _par[v] = u;\n                    ++ch_cnt;\n  \
    \                  dfs(v, id, ord);\n                    _low_link[u] = std::min(_low_link[u],\
    \ _low_link[v]);\n                    if (_pre_order[u] <= _low_link[v]) {\n \
    \                       is_articulation_point = not is_root;\n               \
    \         if (_pre_order[u] != _low_link[v]) _bridges.push_back(id);\n       \
    \             }\n                } else {\n                    _low_link[u] =\
    \ std::min(_low_link[u], _pre_order[v]);\n                }\n            }\n \
    \           if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);\n\
    \        }\n\n        void dfs_for_all_connected_components() {\n            for\
    \ (int i = 0, ord = 0; i < _n; ++i) if (_pre_order[i] < 0) {\n               \
    \ dfs(i, -1, ord);\n                ++_conn_comp_num;\n            }\n       \
    \ }\n    };\n} // namespace suisen\n\n\n\n#line 5 \"library/graph/two_edge_connected_components.hpp\"\
    \n\nnamespace suisen {\n    struct TwoEdgeConnectedComponents : public LowLink\
    \ {\n        TwoEdgeConnectedComponents()\n            : TwoEdgeConnectedComponents(0)\
    \ {}\n        TwoEdgeConnectedComponents(const int n)\n            : LowLink(n),\
    \ _comp_id(_n, -1), _comp_num(0) {}\n        TwoEdgeConnectedComponents(const\
    \ int n, const std::vector<std::pair<int, int>> &edges)\n            : LowLink(n,\
    \ edges), _comp_id(_n, -1), _comp_num(0) {\n            dfs_for_all_connected_components();\n\
    \        }\n\n        void build() {\n            LowLink::build();\n        \
    \    dfs_for_all_connected_components();\n        }\n\n        int component_num()\
    \ const {\n            assert(_built);\n            return _comp_num;\n      \
    \  }\n\n        int operator[](int v) const {\n            assert(_built);\n \
    \           return _comp_id[v];\n        }\n        \n        std::vector<std::vector<int>>\
    \ groups() const {\n            assert(_built);\n            std::vector<std::vector<int>>\
    \ res(component_num());\n            for (int i = 0; i < _n; ++i) res[_comp_id[i]].push_back(i);\n\
    \            return res;\n        }\n\n        // v -> list of (adjacent_vertex,\
    \ edge_id)\n        std::vector<std::vector<std::pair<int, int>>> reduced_forest()\
    \ const {\n            assert(_built);\n            std::vector<std::vector<std::pair<int,\
    \ int>>> reduced(_comp_num);\n            for (int u = 0; u < _n; ++u) {\n   \
    \             for (const auto &[v, edge_id] : _g[u]) {\n                    const\
    \ int comp_u = (*this)[u], comp_v = (*this)[v];\n                    if (comp_u\
    \ != comp_v) reduced[comp_u].emplace_back(comp_v, edge_id);\n                }\n\
    \            }\n            return reduced;\n        }\n\n    private:\n     \
    \   std::vector<int> _comp_id;\n        int _comp_num;\n\n        void dfs(int\
    \ u, int p) {\n            if (p >= 0 and _low_link[u] <= _pre_order[p]) {\n \
    \               _comp_id[u] = _comp_id[p];\n            } else {\n           \
    \     _comp_id[u] = _comp_num++;\n            }\n            for (const auto &e\
    \ : _g[u]) {\n                const int v = e.first;\n                if (_comp_id[v]\
    \ < 0) dfs(v, u);\n            }\n        }\n        void dfs_for_all_connected_components()\
    \ {\n            _comp_num = 0;\n            for (int i = 0; i < _n; ++i) {\n\
    \                if (_comp_id[i] < 0) dfs(i, -1);\n            }\n        }\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n#define SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n\
    \n#include \"library/graph/low_link.hpp\"\n\nnamespace suisen {\n    struct TwoEdgeConnectedComponents\
    \ : public LowLink {\n        TwoEdgeConnectedComponents()\n            : TwoEdgeConnectedComponents(0)\
    \ {}\n        TwoEdgeConnectedComponents(const int n)\n            : LowLink(n),\
    \ _comp_id(_n, -1), _comp_num(0) {}\n        TwoEdgeConnectedComponents(const\
    \ int n, const std::vector<std::pair<int, int>> &edges)\n            : LowLink(n,\
    \ edges), _comp_id(_n, -1), _comp_num(0) {\n            dfs_for_all_connected_components();\n\
    \        }\n\n        void build() {\n            LowLink::build();\n        \
    \    dfs_for_all_connected_components();\n        }\n\n        int component_num()\
    \ const {\n            assert(_built);\n            return _comp_num;\n      \
    \  }\n\n        int operator[](int v) const {\n            assert(_built);\n \
    \           return _comp_id[v];\n        }\n        \n        std::vector<std::vector<int>>\
    \ groups() const {\n            assert(_built);\n            std::vector<std::vector<int>>\
    \ res(component_num());\n            for (int i = 0; i < _n; ++i) res[_comp_id[i]].push_back(i);\n\
    \            return res;\n        }\n\n        // v -> list of (adjacent_vertex,\
    \ edge_id)\n        std::vector<std::vector<std::pair<int, int>>> reduced_forest()\
    \ const {\n            assert(_built);\n            std::vector<std::vector<std::pair<int,\
    \ int>>> reduced(_comp_num);\n            for (int u = 0; u < _n; ++u) {\n   \
    \             for (const auto &[v, edge_id] : _g[u]) {\n                    const\
    \ int comp_u = (*this)[u], comp_v = (*this)[v];\n                    if (comp_u\
    \ != comp_v) reduced[comp_u].emplace_back(comp_v, edge_id);\n                }\n\
    \            }\n            return reduced;\n        }\n\n    private:\n     \
    \   std::vector<int> _comp_id;\n        int _comp_num;\n\n        void dfs(int\
    \ u, int p) {\n            if (p >= 0 and _low_link[u] <= _pre_order[p]) {\n \
    \               _comp_id[u] = _comp_id[p];\n            } else {\n           \
    \     _comp_id[u] = _comp_num++;\n            }\n            for (const auto &e\
    \ : _g[u]) {\n                const int v = e.first;\n                if (_comp_id[v]\
    \ < 0) dfs(v, u);\n            }\n        }\n        void dfs_for_all_connected_components()\
    \ {\n            _comp_num = 0;\n            for (int i = 0; i < _n; ++i) {\n\
    \                if (_comp_id[i] < 0) dfs(i, -1);\n            }\n        }\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_TWO_EDGE_CONNECTED_COMPONENTS\n"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: false
  path: library/graph/two_edge_connected_components.hpp
  requiredBy: []
  timestamp: '2024-01-30 20:12:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/two_edge_connected_components/two_edge_connected_components.test.cpp
documentation_of: library/graph/two_edge_connected_components.hpp
layout: document
title: "\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3"
---
## 二重辺連結成分分解

多重辺があったり、非連結でも動きます。
