---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/undirected_eulerian_graph.hpp
    title: Undirected Eulerian Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/eulerian_trail_undirected
    links:
    - https://judge.yosupo.jp/problem/eulerian_trail_undirected
  bundledCode: "#line 1 \"test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n\n#include <map>\n#include <iostream>\n#line 1 \"library/graph/undirected_eulerian_graph.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct UndirectedEulerianGraph {\n     \
    \   UndirectedEulerianGraph() = default;\n        UndirectedEulerianGraph(int\
    \ n) : n(n), g(n), inv(n) {}\n\n        void add_edge(int u, int v) {\n      \
    \      const int su = g[u].size();\n            g[u].push_back(v);\n         \
    \   const int sv = g[v].size();\n            g[v].push_back(u);\n            inv[u].push_back(sv);\n\
    \            inv[v].push_back(su);\n        }\n\n        std::optional<std::vector<int>>\
    \ eulerian_circuit(int start = -1) {\n            std::size_t edge_num = 0;\n\
    \            std::vector<std::vector<bool>> used(n);\n            for (int i =\
    \ 0; i < n; ++i) {\n                const std::size_t sz = g[i].size();\n    \
    \            edge_num += sz;\n                used[i].resize(sz, false);\n   \
    \             if (sz & 1) return std::nullopt;\n            }\n            if\
    \ (start < 0) {\n                start = 0;\n                for (int i = 0; i\
    \ < n; ++i) if (g[i].size()) start = i;\n            }\n            edge_num /=\
    \ 2;\n            std::vector<int> res;\n            std::vector<std::size_t>\
    \ iter(n);\n            auto dfs = [&](auto dfs, int u) -> void {\n          \
    \      for (std::size_t &i = iter[u]; i < g[u].size(); ++i) {\n              \
    \      if (used[u][i]) continue;\n                    const int v = g[u][i];\n\
    \                    used[u][i] = true;\n                    assert(not used[v][inv[u][i]]);\n\
    \                    used[v][inv[u][i]] = true;\n                    dfs(dfs,\
    \ v);\n                }\n                res.push_back(u);\n            };\n\
    \            dfs(dfs, start);\n            if (res.size() != edge_num + 1) return\
    \ std::nullopt;\n            return res;\n        }\n        std::optional<std::vector<int>>\
    \ eulerian_trail(bool different_endpoints = false) {\n            int s = -1,\
    \ t = -1, invalid = -1;\n            for (int i = 0; i < n; ++i) if (g[i].size()\
    \ & 1) (s < 0 ? s : t < 0 ? t : invalid) = i;\n            if (not different_endpoints\
    \ and s < 0 and t < 0 and invalid < 0) {\n                return eulerian_circuit();\n\
    \            }\n            if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;\n\
    \            add_edge(s, t);\n            auto opt_res = eulerian_circuit(s);\n\
    \            if (not opt_res) return std::nullopt;\n            auto &res = *opt_res;\n\
    \            res.pop_back();\n            // remove edge (s, t)\n            g[s].pop_back(),\
    \ inv[s].pop_back();\n            g[t].pop_back(), inv[t].pop_back();\n      \
    \      if (res.back() == t) return res;\n            auto is_st_edge = [&](int\
    \ u, int v) {\n                return (u == s and v == t) or (u == t and v ==\
    \ s);\n            };\n            std::rotate(res.begin(), std::adjacent_find(res.begin(),\
    \ res.end(), is_st_edge) + 1, res.end());\n            return std::move(res);\n\
    \        }\n        \n        const std::vector<int>& operator[](int u) const\
    \ {\n            return g[u];\n        }\n        std::pair<int, int> rev_edge(int\
    \ u, int i) const {\n            return { g[u][i], inv[u][i] };\n        }\n \
    \   private:\n        int n;\n        std::vector<std::vector<int>> g;\n     \
    \   std::vector<std::vector<int>> inv;\n    };\n}\n\n\n#line 6 \"test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n    for (int tc = 0; tc < t; ++tc) {\n     \
    \   int n, m;\n        std::cin >> n >> m;\n        std::vector<std::map<int,\
    \ std::vector<int>>> mps(n);\n        suisen::UndirectedEulerianGraph g(n);\n\
    \        for (int e = 0; e < m; ++e) {\n            int u, v;\n            std::cin\
    \ >> u >> v;\n            g.add_edge(u, v);\n            if (u > v) std::swap(u,\
    \ v);\n            mps[u][v].push_back(e);\n        }\n        auto p = g.eulerian_trail();\n\
    \        if (p) {\n            std::cout << \"Yes\\n\";\n            for (int\
    \ i = 0; i < m; ++i) {\n                std::cout << (*p)[i] << ' ';\n       \
    \     }\n            std::cout << p->back() << '\\n';\n            for (int i\
    \ = 0; i < m; ++i) {\n                int u = (*p)[i], v = (*p)[i + 1];\n    \
    \            if (u > v) std::swap(u, v);\n                auto &es = mps[u][v];\n\
    \                if (i) std::cout << ' ';\n                std::cout << es.back();\n\
    \                es.pop_back();\n            }\n            std::cout << '\\n';\n\
    \        } else {\n            std::cout << \"No\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n\n#include <map>\n#include <iostream>\n#include \"library/graph/undirected_eulerian_graph.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t;\n    std::cin >> t;\n    for (int tc = 0; tc < t; ++tc) {\n     \
    \   int n, m;\n        std::cin >> n >> m;\n        std::vector<std::map<int,\
    \ std::vector<int>>> mps(n);\n        suisen::UndirectedEulerianGraph g(n);\n\
    \        for (int e = 0; e < m; ++e) {\n            int u, v;\n            std::cin\
    \ >> u >> v;\n            g.add_edge(u, v);\n            if (u > v) std::swap(u,\
    \ v);\n            mps[u][v].push_back(e);\n        }\n        auto p = g.eulerian_trail();\n\
    \        if (p) {\n            std::cout << \"Yes\\n\";\n            for (int\
    \ i = 0; i < m; ++i) {\n                std::cout << (*p)[i] << ' ';\n       \
    \     }\n            std::cout << p->back() << '\\n';\n            for (int i\
    \ = 0; i < m; ++i) {\n                int u = (*p)[i], v = (*p)[i + 1];\n    \
    \            if (u > v) std::swap(u, v);\n                auto &es = mps[u][v];\n\
    \                if (i) std::cout << ' ';\n                std::cout << es.back();\n\
    \                es.pop_back();\n            }\n            std::cout << '\\n';\n\
    \        } else {\n            std::cout << \"No\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - library/graph/undirected_eulerian_graph.hpp
  isVerificationFile: true
  path: test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 19:31:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp
- /verify/test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp.html
title: test/src/graph/undirected_eulerian_graph/eulerian_trail_undirected.test.cpp
---
