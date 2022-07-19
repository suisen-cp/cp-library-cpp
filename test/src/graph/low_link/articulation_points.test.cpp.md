---
data:
  _extendedDependsOn:
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
  bundledCode: "#line 1 \"test/src/graph/low_link/articulation_points.test.cpp\"\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#line 1 \"library/graph/low_link.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    struct\
    \ LowLink {\n        LowLink() : LowLink(0) {}\n        LowLink(const int n) :\
    \ _n(n), _m(0), _g(n), _pre_order(n, -1), _low_link(n), _built(false) {}\n   \
    \     LowLink(const int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n)\
    \ {\n            for (const auto &[u, v] : edges) add_edge(u, v);\n          \
    \  build();\n        }\n        \n        int add_edge(int u, int v) {\n     \
    \       _built = false;\n            _edges.emplace_back(u, v);\n            _g[u].emplace_back(v,\
    \ _m);\n            _g[v].emplace_back(u, _m);\n            return _m++;\n   \
    \     }\n\n        void build() {\n            dfs_for_all_connected_components();\n\
    \            _built = true;\n        }\n\n        int vertex_num() const { return\
    \ _n; }\n        int edge_num()   const { return _m; }\n\n        const std::pair<int,\
    \ int>& edge(int edge_id) const { return _edges[edge_id]; }\n        const std::vector<std::pair<int,\
    \ int>>& edges() const { return _edges; }\n        // list of edges { u, edge_id\
    \ } adjacent to the vertex v.\n        const std::vector<std::pair<int, int>>&\
    \ operator[](int v) const { return _g[v]; }\n        \n        int pre_order(int\
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
    \n\n#line 7 \"test/src/graph/low_link/articulation_points.test.cpp\"\nusing suisen::LowLink;\n\
    \nstd::vector<int> solve1(int n, int m, std::vector<std::pair<int, int>> edges)\
    \ {\n    std::vector<int> articulation_points = LowLink(n, edges).articulation_points();\n\
    \    std::sort(articulation_points.begin(), articulation_points.end());\n    return\
    \ articulation_points;\n}\n\nstd::vector<int> solve2(int n, int m, std::vector<std::pair<int,\
    \ int>> edges) {\n    LowLink low_link(n);\n    for (auto &[u, v] : edges) low_link.add_edge(u,\
    \ v);\n    low_link.build();\n    std::vector<int> articulation_points = low_link.articulation_points();\n\
    \    std::sort(articulation_points.begin(), articulation_points.end());\n    return\
    \ articulation_points;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) std::cin >> u >> v;\n\n    auto\
    \ ans1 = solve1(n, m, edges);\n    auto ans2 = solve2(n, m, edges);\n\n    assert(ans1\
    \ == ans2);\n\n    for (int v : ans1) {\n        std::cout << v << '\\n';\n  \
    \  }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"library/graph/low_link.hpp\"\
    \nusing suisen::LowLink;\n\nstd::vector<int> solve1(int n, int m, std::vector<std::pair<int,\
    \ int>> edges) {\n    std::vector<int> articulation_points = LowLink(n, edges).articulation_points();\n\
    \    std::sort(articulation_points.begin(), articulation_points.end());\n    return\
    \ articulation_points;\n}\n\nstd::vector<int> solve2(int n, int m, std::vector<std::pair<int,\
    \ int>> edges) {\n    LowLink low_link(n);\n    for (auto &[u, v] : edges) low_link.add_edge(u,\
    \ v);\n    low_link.build();\n    std::vector<int> articulation_points = low_link.articulation_points();\n\
    \    std::sort(articulation_points.begin(), articulation_points.end());\n    return\
    \ articulation_points;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) std::cin >> u >> v;\n\n    auto\
    \ ans1 = solve1(n, m, edges);\n    auto ans2 = solve2(n, m, edges);\n\n    assert(ans1\
    \ == ans2);\n\n    for (int v : ans1) {\n        std::cout << v << '\\n';\n  \
    \  }\n    return 0;\n}"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/low_link/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2022-07-16 16:39:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/low_link/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/low_link/articulation_points.test.cpp
- /verify/test/src/graph/low_link/articulation_points.test.cpp.html
title: test/src/graph/low_link/articulation_points.test.cpp
---
