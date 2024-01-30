---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/biconnected_components.hpp
    title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':question:'
    path: library/graph/low_link.hpp
    title: Low Link
  - icon: ':warning:'
    path: library/graph/remove_multiedges.hpp
    title: "\u591A\u91CD\u8FBA\u9664\u53BB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/block_cut_forest.hpp\"\n\n\n\n#line 1 \"library/graph/remove_multiedges.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n#include <cstdint>\n\nnamespace\
    \ suisen {\n\nvoid remove_multiedges(std::vector<std::vector<int>> &g) {\n   \
    \ std::vector<uint8_t> exists(g.size(), 0);\n    for (auto &vs : g) {\n      \
    \  for (int v : vs) exists[v] = true;\n        vs.erase(std::remove_if(vs.begin(),\
    \ vs.end(), [&](int v) { return not std::exchange(exists[v], false); }), vs.end());\n\
    \    }\n}\n\n} // namespace suisen\n\n\n\n#line 1 \"library/graph/biconnected_components.hpp\"\
    \n\n\n\n#line 5 \"library/graph/biconnected_components.hpp\"\n#include <utility>\n\
    #line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #line 9 \"library/graph/low_link.hpp\"\n\nnamespace suisen {\n    struct LowLink\
    \ {\n        LowLink() : LowLink(0) {}\n        LowLink(const int n) : _n(n),\
    \ _m(0), _g(n), _pre_order(n, -1), _low_link(n), _built(false), _conn_comp_num(0),\
    \ _par(n, -1) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
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
    \ }\n    };\n} // namespace suisen\n\n\n\n#line 7 \"library/graph/biconnected_components.hpp\"\
    \n\nnamespace suisen {\n    struct BiconnectedComponents : public LowLink {\n\
    \        BiconnectedComponents() \n            : BiconnectedComponents(0) {}\n\
    \        BiconnectedComponents(const int n) \n            : LowLink(n), _used(_n,\
    \ false), _edge_comp_id(_m, -1), _edge_comp_num(0) {}\n        BiconnectedComponents(const\
    \ int n, const std::vector<std::pair<int, int>> &edges) \n            : LowLink(n,\
    \ edges), _used(_n, false), _edge_comp_id(_m, -1), _edge_comp_num(0) {\n     \
    \       dfs_for_all_connected_components();\n        }\n\n        void build()\
    \ {\n            LowLink::build();\n            dfs_for_all_connected_components();\n\
    \        }\n\n        // # of component (including isolated vertices)\n      \
    \  int component_num() const {\n            assert(_built);\n            return\
    \ _edge_comp_num + _isolated_vertices.size();\n        }\n        // component_num()\
    \ - # of isolated vertices\n        int edge_component_num() const {\n       \
    \     assert(_built);\n            return _edge_comp_num;\n        }\n       \
    \ int isolated_vertex_num() const {\n            assert(_built);\n           \
    \ return _isolated_vertices.size();\n        }\n        bool is_isolated_component(int\
    \ component_id) const {\n            return component_id >= _edge_comp_num;\n\
    \        } \n\n        int operator[](int edge_id) const {\n            assert(_built);\n\
    \            return _edge_comp_id[edge_id];\n        }\n\n        const std::vector<int>&\
    \ isolated_vertices() const {\n            assert(_built);\n            return\
    \ _isolated_vertices;\n        }\n\n        struct Subgraph {\n            std::vector<int>\
    \ vids, eids;\n            int vertex_num() const { return vids.size(); }\n  \
    \          int edge_num()   const { return eids.size(); }\n            const std::vector<int>&\
    \ vertex_set() const { return vids; }\n            const std::vector<int>& edge_set()\
    \   const { return eids; }\n            bool operator==(const Subgraph &rhs) const\
    \ { return vids == rhs.vids and eids == rhs.eids; }\n            bool operator!=(const\
    \ Subgraph &rhs) const { return not (*this == rhs); }\n        };\n        \n\
    \        // vector of biconnected components. [0:edge_component_num()) has edges,\
    \ [edge_component_num(),component_num()) are isolated vertices.\n        std::vector<Subgraph>\
    \ components() const {\n            assert(_built);\n            std::vector<Subgraph>\
    \ res(component_num());\n            for (int i = 0; i < _m; ++i) {\n        \
    \        res[_edge_comp_id[i]].eids.push_back(i);\n            }\n           \
    \ std::vector<int8_t> seen(vertex_num(), false);\n            for (int id = 0;\
    \ id < _edge_comp_num; ++id) {\n                for (int eid : res[id].eids) {\n\
    \                    const auto &[u, v] = edge(eid);\n                    if (not\
    \ std::exchange(seen[u], true)) res[id].vids.push_back(u);\n                 \
    \   if (not std::exchange(seen[v], true)) res[id].vids.push_back(v);\n       \
    \         }\n                for (int eid : res[id].eids) {\n                \
    \    const auto &[u, v] = edge(eid);\n                    seen[u] = seen[v] =\
    \ false;\n                }\n            }\n            int id = _edge_comp_num;\n\
    \            for (int v : _isolated_vertices) {\n                res[id++].vids\
    \ = { v };\n            }\n            return res;\n        }\n\n    private:\n\
    \        std::vector<int8_t> _used;\n        std::vector<int> _edge_comp_id;\n\
    \        int _edge_comp_num;\n        std::vector<int> _isolated_vertices;\n\n\
    \        void dfs(int u, int par_edge_id) {\n            _used[u] = true;\n  \
    \          static std::vector<int> edges;\n            for (const auto &[v, edge_id]\
    \ : _g[u]) if (edge_id != par_edge_id) {\n                // edge_id is a new\
    \ edge\n                if (not _used[v] or _pre_order[v] < _pre_order[u]) edges.push_back(edge_id);\n\
    \                // v is not a new vertex\n                if (_used[v]) continue;\n\
    \                dfs(v, edge_id);\n                if (_low_link[v] < _pre_order[u])\
    \ continue;\n                int e;\n                do _edge_comp_id[e = edges.back()]\
    \ = _edge_comp_num, edges.pop_back(); while (e != edge_id);\n                _edge_comp_num++;\n\
    \            }\n        }\n        void dfs_for_all_connected_components() {\n\
    \            _edge_comp_num = 0;\n            _edge_comp_id.assign(_m, -1);\n\
    \            _used.assign(_n, false);\n            for (int i = 0; i < _n; ++i)\
    \ if (not _used[i]) {\n                dfs(i, -1);\n                if (_g[i].empty())\
    \ _isolated_vertices.push_back(i);\n            }\n        }\n    };\n} // namespace\
    \ suisen\n\n\n\n#line 6 \"library/graph/block_cut_forest.hpp\"\n\nnamespace suisen\
    \ {\n    struct BlockCutForest {\n        BlockCutForest() = default;\n      \
    \  BlockCutForest(const BiconnectedComponents &bcc)\n            : _edge_comp_num(bcc.edge_component_num()),\
    \ _isolated_vertex_num(bcc.isolated_vertex_num()), _art_num(bcc.articulation_points().size()),\
    \ _node_num(_edge_comp_num + _isolated_vertex_num + _art_num), _g(_node_num),\
    \ _vertex_num(_node_num), _comp_id(bcc.vertex_num(), -1) {\n            std::vector<int>\
    \ art_id(bcc.vertex_num(), -1);\n            int next_id = _edge_comp_num + _isolated_vertex_num;\n\
    \            for (int v : bcc.articulation_points()) art_id[v] = next_id++;\n\n\
    \            for (int edge_id = 0; edge_id < bcc.edge_num(); ++edge_id) {\n  \
    \              const int cid = bcc[edge_id];\n                const auto &[u,\
    \ v] = bcc.edge(edge_id);\n                _comp_id[u] = _comp_id[v] = cid;\n\
    \                if (int vid = art_id[u]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \                if (int vid = art_id[v]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \            }\n            int isolated_vertex_id = _edge_comp_num;\n       \
    \     for (int v : bcc.isolated_vertices()) {\n                _comp_id[v] = isolated_vertex_id++;\n\
    \            }\n\n            remove_multiedges(_g);\n\n            for (int v\
    \ = 0; v < bcc.vertex_num(); ++v) {\n                if (int vid = art_id[v];\
    \ vid < 0) {\n                    ++_vertex_num[_comp_id[v]];\n              \
    \  } else {\n                    _vertex_num[vid] = 1;\n                    for\
    \ (int cid : _g[vid]) ++_vertex_num[cid];\n                }\n            }\n\
    \        }\n\n        int size() const { return _edge_comp_num + _isolated_vertex_num\
    \ + _art_num; }\n        \n        bool is_articulation_point(int id)    const\
    \ { return id >= _edge_comp_num + _isolated_vertex_num; }\n        bool is_biconnected_component(int\
    \ id) const { return not is_articulation_point(id); }\n        bool is_isolated_vertex(int\
    \ id)       const { return id >= _edge_comp_num and is_biconnected_component(id);\
    \ }\n\n        const std::vector<int>& operator[](int id) const { return _g[id];\
    \ }\n        std::vector<int>& operator[](int id) { return _g[id]; }\n\n     \
    \   int vertex_num(int id) const { return _vertex_num[id]; }\n\n        int component_id(int\
    \ vertex) const {\n            return _comp_id[vertex];\n        }\n\n    private:\n\
    \        int _edge_comp_num;\n        int _isolated_vertex_num;\n        int _art_num;\n\
    \        int _node_num;\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _vertex_num;\n        std::vector<int> _comp_id;\n    };\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_BLOCK_CUT_FOREST\n#define SUISEN_BLOCK_CUT_FOREST\n\n#include\
    \ \"library/graph/remove_multiedges.hpp\"\n#include \"library/graph/biconnected_components.hpp\"\
    \n\nnamespace suisen {\n    struct BlockCutForest {\n        BlockCutForest()\
    \ = default;\n        BlockCutForest(const BiconnectedComponents &bcc)\n     \
    \       : _edge_comp_num(bcc.edge_component_num()), _isolated_vertex_num(bcc.isolated_vertex_num()),\
    \ _art_num(bcc.articulation_points().size()), _node_num(_edge_comp_num + _isolated_vertex_num\
    \ + _art_num), _g(_node_num), _vertex_num(_node_num), _comp_id(bcc.vertex_num(),\
    \ -1) {\n            std::vector<int> art_id(bcc.vertex_num(), -1);\n        \
    \    int next_id = _edge_comp_num + _isolated_vertex_num;\n            for (int\
    \ v : bcc.articulation_points()) art_id[v] = next_id++;\n\n            for (int\
    \ edge_id = 0; edge_id < bcc.edge_num(); ++edge_id) {\n                const int\
    \ cid = bcc[edge_id];\n                const auto &[u, v] = bcc.edge(edge_id);\n\
    \                _comp_id[u] = _comp_id[v] = cid;\n                if (int vid\
    \ = art_id[u]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n   \
    \             if (int vid = art_id[v]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \            }\n            int isolated_vertex_id = _edge_comp_num;\n       \
    \     for (int v : bcc.isolated_vertices()) {\n                _comp_id[v] = isolated_vertex_id++;\n\
    \            }\n\n            remove_multiedges(_g);\n\n            for (int v\
    \ = 0; v < bcc.vertex_num(); ++v) {\n                if (int vid = art_id[v];\
    \ vid < 0) {\n                    ++_vertex_num[_comp_id[v]];\n              \
    \  } else {\n                    _vertex_num[vid] = 1;\n                    for\
    \ (int cid : _g[vid]) ++_vertex_num[cid];\n                }\n            }\n\
    \        }\n\n        int size() const { return _edge_comp_num + _isolated_vertex_num\
    \ + _art_num; }\n        \n        bool is_articulation_point(int id)    const\
    \ { return id >= _edge_comp_num + _isolated_vertex_num; }\n        bool is_biconnected_component(int\
    \ id) const { return not is_articulation_point(id); }\n        bool is_isolated_vertex(int\
    \ id)       const { return id >= _edge_comp_num and is_biconnected_component(id);\
    \ }\n\n        const std::vector<int>& operator[](int id) const { return _g[id];\
    \ }\n        std::vector<int>& operator[](int id) { return _g[id]; }\n\n     \
    \   int vertex_num(int id) const { return _vertex_num[id]; }\n\n        int component_id(int\
    \ vertex) const {\n            return _comp_id[vertex];\n        }\n\n    private:\n\
    \        int _edge_comp_num;\n        int _isolated_vertex_num;\n        int _art_num;\n\
    \        int _node_num;\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _vertex_num;\n        std::vector<int> _comp_id;\n    };\n} // namespace suisen\n\
    \n\n#endif // SUISEN_BLOCK_CUT_FOREST\n"
  dependsOn:
  - library/graph/remove_multiedges.hpp
  - library/graph/biconnected_components.hpp
  - library/graph/low_link.hpp
  isVerificationFile: false
  path: library/graph/block_cut_forest.hpp
  requiredBy: []
  timestamp: '2024-01-30 20:12:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/block_cut_forest.hpp
layout: document
title: Block Cut Forest
---
## Block Cut Forest