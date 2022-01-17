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
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    struct LowLink {\n      \
    \  using Graph = std::vector<std::vector<std::pair<int, int>>>;\n\n        int\
    \ n, m;\n        // vertex -> list of (adjacent vertex, edge id)\n        Graph\
    \ g;\n        // vertex -> pre order\n        std::vector<int> pre_order;\n  \
    \      std::vector<int> low_link;\n        // list of ids of bridges\n       \
    \ std::vector<int> bridges;\n        std::vector<int> articulation_points;\n\n\
    \        LowLink() : LowLink(0, {}) {}\n        LowLink(const int n, const std::vector<std::pair<int,\
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
    \            }\n        }\n    };\n} // namespace suisen\n\n\n\n#line 7 \"test/src/graph/low_link/articulation_points.test.cpp\"\
    \nusing suisen::LowLink;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) std::cin >> u >> v;\n\n    std::vector<int>\
    \ articulation_points = LowLink(n, edges).articulation_points;\n    std::sort(articulation_points.begin(),\
    \ articulation_points.end());\n    for (int v : articulation_points) {\n     \
    \   std::cout << v << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"library/graph/low_link.hpp\"\
    \nusing suisen::LowLink;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::pair<int,\
    \ int>> edges(m);\n    for (auto &[u, v] : edges) std::cin >> u >> v;\n\n    std::vector<int>\
    \ articulation_points = LowLink(n, edges).articulation_points;\n    std::sort(articulation_points.begin(),\
    \ articulation_points.end());\n    for (int v : articulation_points) {\n     \
    \   std::cout << v << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/graph/low_link.hpp
  isVerificationFile: true
  path: test/src/graph/low_link/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2021-10-22 11:27:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/low_link/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/low_link/articulation_points.test.cpp
- /verify/test/src/graph/low_link/articulation_points.test.cpp.html
title: test/src/graph/low_link/articulation_points.test.cpp
---
