---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/biconnected_components.hpp
    title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':question:'
    path: library/graph/low_link.hpp
    title: Low Link
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/biconnected_components
    links:
    - https://judge.yosupo.jp/problem/biconnected_components
  bundledCode: "#line 1 \"test/src/graph/biconnected_components/biconnected_components.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\n\
    \n#include <iostream>\n\n#line 1 \"library/graph/biconnected_components.hpp\"\n\
    \n\n\n#include <cstdint>\n#include <utility>\n#line 1 \"library/graph/low_link.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#line 8 \"library/graph/low_link.hpp\"\
    \n#include <vector>\n\nnamespace suisen {\n    struct LowLink {\n        LowLink()\
    \ : LowLink(0) {}\n        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n,\
    \ -1), _low_link(n), _built(false), _conn_comp_num(0), _par(n, -1) {}\n      \
    \  LowLink(const int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n)\
    \ {\n            for (const auto &[u, v] : edges) add_edge(u, v);\n          \
    \  build();\n        }\n        \n        // Add an edge and return its ID. IDs\
    \ are assigned in the order (0,1,2, ...).\n        int add_edge(int u, int v)\
    \ {\n            _built = false;\n            _edges.emplace_back(u, v);\n   \
    \         _g[u].emplace_back(v, _m);\n            _g[v].emplace_back(u, _m);\n\
    \            return _m++;\n        }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
    \            _built = true;\n        }\n\n        int vertex_num() const { return\
    \ _n; }\n        int edge_num()   const { return _m; }\n\n        const std::pair<int,\
    \ int>& edge(int edge_id) const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
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
    \ suisen\n\n\n\n#line 6 \"test/src/graph/biconnected_components/biconnected_components.test.cpp\"\
    \n\nusing suisen::BiconnectedComponents;\n\nauto solve1(int n, std::vector<std::pair<int,\
    \ int>> edges) {\n    BiconnectedComponents bcc(n, edges);\n    return std::make_pair(bcc.component_num(),\
    \ bcc.components());\n}\n\nauto solve2(int n, std::vector<std::pair<int, int>>\
    \ edges) {\n    BiconnectedComponents bcc(n);\n    for (const auto &[u, v] : edges)\
    \ bcc.add_edge(u, v);\n    bcc.build();\n    return std::make_pair(bcc.component_num(),\
    \ bcc.components());\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n    }\n    \n    auto ans1 = solve1(n, edges);\n    auto ans2 = solve2(n,\
    \ edges);\n    assert(ans1 == ans2);\n\n    const auto &[comp_num, components]\
    \ = ans1;\n\n    std::cout << comp_num << '\\n';\n    for (const auto &component\
    \ : components) {\n        std::cout << component.vids.size();\n        for (const\
    \ int v : component.vids) std::cout << ' ' << v;\n        std::cout << '\\n';\n\
    \    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\
    \n\n#include <iostream>\n\n#include \"library/graph/biconnected_components.hpp\"\
    \n\nusing suisen::BiconnectedComponents;\n\nauto solve1(int n, std::vector<std::pair<int,\
    \ int>> edges) {\n    BiconnectedComponents bcc(n, edges);\n    return std::make_pair(bcc.component_num(),\
    \ bcc.components());\n}\n\nauto solve2(int n, std::vector<std::pair<int, int>>\
    \ edges) {\n    BiconnectedComponents bcc(n);\n    for (const auto &[u, v] : edges)\
    \ bcc.add_edge(u, v);\n    bcc.build();\n    return std::make_pair(bcc.component_num(),\
    \ bcc.components());\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n    }\n    \n    auto ans1 = solve1(n, edges);\n    auto ans2 = solve2(n,\
    \ edges);\n    assert(ans1 == ans2);\n\n    const auto &[comp_num, components]\
    \ = ans1;\n\n    std::cout << comp_num << '\\n';\n    for (const auto &component\
    \ : components) {\n        std::cout << component.vids.size();\n        for (const\
    \ int v : component.vids) std::cout << ' ' << v;\n        std::cout << '\\n';\n\
    \    }\n\n    return 0;\n}"
  dependsOn:
  - library/graph/biconnected_components.hpp
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/biconnected_components/biconnected_components.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 20:12:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/biconnected_components/biconnected_components.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/biconnected_components/biconnected_components.test.cpp
- /verify/test/src/graph/biconnected_components/biconnected_components.test.cpp.html
title: test/src/graph/biconnected_components/biconnected_components.test.cpp
---
