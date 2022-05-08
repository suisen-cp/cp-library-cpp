---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/biconnected_components.hpp
    title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':heavy_check_mark:'
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
    \n\n\n\n#line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include <cassert>\n#line\
    \ 6 \"library/graph/low_link.hpp\"\n\nnamespace suisen {\n    struct LowLink {\n\
    \        LowLink() : LowLink(0) {}\n        LowLink(const int n) : _n(n), _m(0),\
    \ _g(n), _pre_order(n, -1), _low_link(n), _built(false) {}\n        LowLink(const\
    \ int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n) {\n     \
    \       for (const auto &[u, v] : edges) add_edge(u, v);\n            build();\n\
    \        }\n        \n        int add_edge(int u, int v) {\n            _built\
    \ = false;\n            _edges.emplace_back(u, v);\n            _g[u].emplace_back(v,\
    \ _m);\n            _g[v].emplace_back(u, _m);\n            return _m++;\n   \
    \     }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
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
    \n\n#line 6 \"library/graph/biconnected_components.hpp\"\n\nnamespace suisen {\n\
    \    struct BiconnectedComponents : public LowLink {\n        BiconnectedComponents()\
    \ \n            : BiconnectedComponents(0) {}\n        BiconnectedComponents(const\
    \ int n) \n            : LowLink(n), _used(_n, false), _comp_id(_m, -1), _comp_num(0)\
    \ {}\n        BiconnectedComponents(const int n, const std::vector<std::pair<int,\
    \ int>> &edges) \n            : LowLink(n, edges), _used(_n, false), _comp_id(_m,\
    \ -1), _comp_num(0) {\n            dfs_for_all_connected_components();\n     \
    \   }\n\n        void build() {\n            LowLink::build();\n            dfs_for_all_connected_components();\n\
    \        }\n\n        int component_num() const {\n            assert(_built);\n\
    \            return _comp_num;\n        }\n\n        int operator[](int edge_id)\
    \ const {\n            assert(_built);\n            return _comp_id[edge_id];\n\
    \        }\n        \n        std::vector<std::vector<int>> edge_groups() const\
    \ {\n            assert(_built);\n            std::vector<std::vector<int>> res(component_num());\n\
    \            for (int i = 0; i < _m; ++i) res[_comp_id[i]].push_back(i);\n   \
    \         return res;\n        }\n\n    private:\n        std::vector<int8_t>\
    \ _used;\n        std::vector<int> _comp_id;\n        int _comp_num;\n\n     \
    \   void dfs(int u, int par_edge_id) {\n            _used[u] = true;\n       \
    \     static std::vector<int> edges;\n            for (const auto &[v, edge_id]\
    \ : _g[u]) if (edge_id != par_edge_id) {\n                // edge_id is a new\
    \ edge\n                if (not _used[v] or _pre_order[v] < _pre_order[u]) edges.push_back(edge_id);\n\
    \                // v is not a new vertex\n                if (_used[v]) continue;\n\
    \                dfs(v, edge_id);\n                if (_low_link[v] < _pre_order[u])\
    \ continue;\n                int e;\n                do _comp_id[e = edges.back()]\
    \ = _comp_num, edges.pop_back(); while (e != edge_id);\n                _comp_num++;\n\
    \            }\n        }\n        void dfs_for_all_connected_components() {\n\
    \            _comp_num = 0;\n            _comp_id.assign(_m, -1);\n          \
    \  _used.assign(_n, false);\n            for (int i = 0; i < _n; ++i) {\n    \
    \            if (not _used[i]) dfs(i, -1);\n            }\n        }\n    };\n\
    } // namespace suisen\n\n\n\n#line 6 \"library/graph/block_cut_forest.hpp\"\n\n\
    namespace suisen {\n    struct BlockCutForest {\n        BlockCutForest() = default;\n\
    \        BlockCutForest(const BiconnectedComponents &bcc)\n            : _bcc_num(bcc.component_num()),\
    \ _art_num(bcc.articulation_points().size()), _g(_bcc_num + _art_num), _vertex_num(_bcc_num\
    \ + _art_num) {\n            std::vector<int> art_id(bcc.vertex_num(), -1);\n\
    \            int next_id = _bcc_num;\n            for (int v : bcc.articulation_points())\
    \ art_id[v] = next_id++;\n\n            std::vector<int> comp_id(bcc.vertex_num());\n\
    \            for (int edge_id = 0; edge_id < bcc.edge_num(); ++edge_id) {\n  \
    \              const int cid = bcc[edge_id];\n                const auto &[u,\
    \ v] = bcc.edge(edge_id);\n                comp_id[u] = comp_id[v] = cid;\n  \
    \              if (int vid = art_id[u]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \                if (int vid = art_id[v]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \            }\n            remove_multiedges(_g);\n\n            for (int v =\
    \ 0; v < bcc.vertex_num(); ++v) {\n                if (int vid = art_id[v]; vid\
    \ < 0) {\n                    ++_vertex_num[comp_id[v]];\n                } else\
    \ {\n                    _vertex_num[vid] = 1;\n                    for (int cid\
    \ : _g[vid]) ++_vertex_num[cid];\n                }\n            }\n        }\n\
    \n        int size() const { return _bcc_num + _art_num; }\n        \n       \
    \ bool is_articulation_point(int id)    const { return id >= _bcc_num; }\n   \
    \     bool is_biconnected_component(int id) const { return not is_articulation_point(id);\
    \ }\n\n        const std::vector<int>& operator[](int id) const { return _g[id];\
    \ }\n        std::vector<int>& operator[](int id) { return _g[id]; }\n\n     \
    \   int vertex_num(int id) const { return _vertex_num[id]; }\n\n    private:\n\
    \        int _bcc_num;\n        int _art_num;\n        std::vector<std::vector<int>>\
    \ _g;\n        std::vector<int> _vertex_num;\n    };\n} // namespace suisen\n\n\
    \n\n"
  code: "#ifndef SUISEN_BLOCK_CUT_FOREST\n#define SUISEN_BLOCK_CUT_FOREST\n\n#include\
    \ \"library/graph/remove_multiedges.hpp\"\n#include \"library/graph/biconnected_components.hpp\"\
    \n\nnamespace suisen {\n    struct BlockCutForest {\n        BlockCutForest()\
    \ = default;\n        BlockCutForest(const BiconnectedComponents &bcc)\n     \
    \       : _bcc_num(bcc.component_num()), _art_num(bcc.articulation_points().size()),\
    \ _g(_bcc_num + _art_num), _vertex_num(_bcc_num + _art_num) {\n            std::vector<int>\
    \ art_id(bcc.vertex_num(), -1);\n            int next_id = _bcc_num;\n       \
    \     for (int v : bcc.articulation_points()) art_id[v] = next_id++;\n\n     \
    \       std::vector<int> comp_id(bcc.vertex_num());\n            for (int edge_id\
    \ = 0; edge_id < bcc.edge_num(); ++edge_id) {\n                const int cid =\
    \ bcc[edge_id];\n                const auto &[u, v] = bcc.edge(edge_id);\n   \
    \             comp_id[u] = comp_id[v] = cid;\n                if (int vid = art_id[u];\
    \ vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n                if\
    \ (int vid = art_id[v]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);\n\
    \            }\n            remove_multiedges(_g);\n\n            for (int v =\
    \ 0; v < bcc.vertex_num(); ++v) {\n                if (int vid = art_id[v]; vid\
    \ < 0) {\n                    ++_vertex_num[comp_id[v]];\n                } else\
    \ {\n                    _vertex_num[vid] = 1;\n                    for (int cid\
    \ : _g[vid]) ++_vertex_num[cid];\n                }\n            }\n        }\n\
    \n        int size() const { return _bcc_num + _art_num; }\n        \n       \
    \ bool is_articulation_point(int id)    const { return id >= _bcc_num; }\n   \
    \     bool is_biconnected_component(int id) const { return not is_articulation_point(id);\
    \ }\n\n        const std::vector<int>& operator[](int id) const { return _g[id];\
    \ }\n        std::vector<int>& operator[](int id) { return _g[id]; }\n\n     \
    \   int vertex_num(int id) const { return _vertex_num[id]; }\n\n    private:\n\
    \        int _bcc_num;\n        int _art_num;\n        std::vector<std::vector<int>>\
    \ _g;\n        std::vector<int> _vertex_num;\n    };\n} // namespace suisen\n\n\
    \n#endif // SUISEN_BLOCK_CUT_FOREST\n"
  dependsOn:
  - library/graph/remove_multiedges.hpp
  - library/graph/biconnected_components.hpp
  - library/graph/low_link.hpp
  isVerificationFile: false
  path: library/graph/block_cut_forest.hpp
  requiredBy: []
  timestamp: '2022-05-05 17:38:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/block_cut_forest.hpp
layout: document
title: Block Cut Forest
---
## Block Cut Forest