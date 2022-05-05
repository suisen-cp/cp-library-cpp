---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/biconnected_components.hpp
    title: library/graph/biconnected_components.hpp
  - icon: ':heavy_check_mark:'
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
    \n\n\n#include <cstdint>\n#line 1 \"library/graph/low_link.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    struct LowLink {\n \
    \       LowLink() : LowLink(0) {}\n        LowLink(const int n) : _n(n), _m(0),\
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
    } // namespace suisen\n\n\n\n#line 6 \"test/src/graph/biconnected_components/biconnected_components.test.cpp\"\
    \n\nusing suisen::BiconnectedComponents;\n\nauto solve1(int n, std::vector<std::pair<int,\
    \ int>> edges) {\n    BiconnectedComponents bcc(n, edges);\n    return std::make_pair(bcc.component_num(),\
    \ bcc.edge_groups());\n}\n\nauto solve2(int n, std::vector<std::pair<int, int>>\
    \ edges) {\n    BiconnectedComponents bcc(n);\n    for (const auto &[u, v] : edges)\
    \ bcc.add_edge(u, v);\n    bcc.build();\n    return std::make_pair(bcc.component_num(),\
    \ bcc.edge_groups());\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n    }\n    \n    auto ans1 = solve1(n, edges);\n    // auto ans2 = solve2(n,\
    \ edges);\n    // assert(ans1 == ans2);\n\n    const auto &[comp_num, groups]\
    \ = ans1;\n\n    std::cout << comp_num << '\\n';\n    for (const auto &group :\
    \ groups) {\n        std::cout << group.size();\n        for (const int v : group)\
    \ std::cout << ' ' << v;\n        std::cout << '\\n';\n    }\n\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\
    \n\n#include <iostream>\n\n#include \"library/graph/biconnected_components.hpp\"\
    \n\nusing suisen::BiconnectedComponents;\n\nauto solve1(int n, std::vector<std::pair<int,\
    \ int>> edges) {\n    BiconnectedComponents bcc(n, edges);\n    return std::make_pair(bcc.component_num(),\
    \ bcc.edge_groups());\n}\n\nauto solve2(int n, std::vector<std::pair<int, int>>\
    \ edges) {\n    BiconnectedComponents bcc(n);\n    for (const auto &[u, v] : edges)\
    \ bcc.add_edge(u, v);\n    bcc.build();\n    return std::make_pair(bcc.component_num(),\
    \ bcc.edge_groups());\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) {\n        std::cin >> u >>\
    \ v;\n    }\n    \n    auto ans1 = solve1(n, edges);\n    // auto ans2 = solve2(n,\
    \ edges);\n    // assert(ans1 == ans2);\n\n    const auto &[comp_num, groups]\
    \ = ans1;\n\n    std::cout << comp_num << '\\n';\n    for (const auto &group :\
    \ groups) {\n        std::cout << group.size();\n        for (const int v : group)\
    \ std::cout << ' ' << v;\n        std::cout << '\\n';\n    }\n\n    return 0;\n\
    }"
  dependsOn:
  - library/graph/biconnected_components.hpp
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/biconnected_components/biconnected_components.test.cpp
  requiredBy: []
  timestamp: '2022-05-05 17:38:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/biconnected_components/biconnected_components.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/biconnected_components/biconnected_components.test.cpp
- /verify/test/src/graph/biconnected_components/biconnected_components.test.cpp.html
title: test/src/graph/biconnected_components/biconnected_components.test.cpp
---