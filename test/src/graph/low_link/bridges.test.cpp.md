---
data:
  _extendedDependsOn:
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
  bundledCode: "#line 1 \"test/src/graph/low_link/bridges.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n\n#line 1 \"library/graph/low_link.hpp\"\n\
    \n\n\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <utility>\n\
    #include <vector>\n\nnamespace suisen {\n    struct LowLink {\n        LowLink()\
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
    \ }\n    };\n} // namespace suisen\n\n\n\n#line 7 \"test/src/graph/low_link/bridges.test.cpp\"\
    \nusing suisen::LowLink;\n\nstd::vector<std::pair<int, int>> solve1(int n, int\
    \ m, std::vector<std::pair<int, int>> edges) {\n    std::vector<int> bridge_ids\
    \ = LowLink(n, edges).bridge_ids();\n    std::vector<std::pair<int, int>> bridges;\n\
    \    for (auto id : bridge_ids) {\n        bridges.push_back(edges[id]);\n   \
    \ }\n    std::sort(bridges.begin(), bridges.end());\n    return bridges;\n}\n\n\
    std::vector<std::pair<int, int>> solve2(int n, int m, std::vector<std::pair<int,\
    \ int>> edges) {\n    LowLink low_link(n);\n    for (auto &[u, v] : edges) low_link.add_edge(u,\
    \ v);\n    low_link.build();\n\n    std::vector<int> bridge_ids = low_link.bridge_ids();\n\
    \    std::vector<std::pair<int, int>> bridges;\n    for (auto id : bridge_ids)\
    \ {\n        bridges.push_back(edges[id]);\n    }\n    std::sort(bridges.begin(),\
    \ bridges.end());\n    return bridges;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n        if (u > v) std::swap(u, v);\n    }\n\n    auto ans1 = solve1(n,\
    \ m, edges);\n    auto ans2 = solve2(n, m, edges);\n\n    assert(ans1 == ans2);\n\
    \n    for (auto [u, v] : ans1) {\n        std::cout << u << ' ' << v << '\\n';\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"library/graph/low_link.hpp\"\
    \nusing suisen::LowLink;\n\nstd::vector<std::pair<int, int>> solve1(int n, int\
    \ m, std::vector<std::pair<int, int>> edges) {\n    std::vector<int> bridge_ids\
    \ = LowLink(n, edges).bridge_ids();\n    std::vector<std::pair<int, int>> bridges;\n\
    \    for (auto id : bridge_ids) {\n        bridges.push_back(edges[id]);\n   \
    \ }\n    std::sort(bridges.begin(), bridges.end());\n    return bridges;\n}\n\n\
    std::vector<std::pair<int, int>> solve2(int n, int m, std::vector<std::pair<int,\
    \ int>> edges) {\n    LowLink low_link(n);\n    for (auto &[u, v] : edges) low_link.add_edge(u,\
    \ v);\n    low_link.build();\n\n    std::vector<int> bridge_ids = low_link.bridge_ids();\n\
    \    std::vector<std::pair<int, int>> bridges;\n    for (auto id : bridge_ids)\
    \ {\n        bridges.push_back(edges[id]);\n    }\n    std::sort(bridges.begin(),\
    \ bridges.end());\n    return bridges;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n        if (u > v) std::swap(u, v);\n    }\n\n    auto ans1 = solve1(n,\
    \ m, edges);\n    auto ans2 = solve2(n, m, edges);\n\n    assert(ans1 == ans2);\n\
    \n    for (auto [u, v] : ans1) {\n        std::cout << u << ' ' << v << '\\n';\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/low_link/bridges.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 20:12:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/low_link/bridges.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/low_link/bridges.test.cpp
- /verify/test/src/graph/low_link/bridges.test.cpp.html
title: test/src/graph/low_link/bridges.test.cpp
---
