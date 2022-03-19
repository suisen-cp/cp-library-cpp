---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/undirected_eulerian_graph.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\n\
    namespace suisen {\n    struct UndirectedEulerianGraph {\n        UndirectedEulerianGraph()\
    \ {}\n        UndirectedEulerianGraph(int n) : n(n), g(n), inv(n) {}\n\n     \
    \   void add_edge(int u, int v) {\n            const int su = g[u].size();\n \
    \           g[u].push_back(v);\n            const int sv = g[v].size();\n    \
    \        g[v].push_back(u);\n            inv[u].push_back(sv);\n            inv[v].push_back(su);\n\
    \        }\n\n        std::optional<std::vector<int>> eulerian_circuit(int start\
    \ = 0) {\n            std::size_t edge_num = 0;\n            std::vector<std::vector<bool>>\
    \ used(n);\n            for (int i = 0; i < n; ++i) {\n                const std::size_t\
    \ sz = g[i].size();\n                edge_num += sz;\n                used[i].resize(sz,\
    \ false);\n                if (sz & 1) return std::nullopt;\n            }\n \
    \           edge_num /= 2;\n            std::vector<int> res;\n            auto\
    \ dfs = [&](auto dfs, int u) -> void {\n                for (std::size_t i = 0;\
    \ i < g[u].size(); ++i) {\n                    if (used[u][i]) continue;\n   \
    \                 const int v = g[u][i];\n                    used[u][i] = true;\n\
    \                    assert(not used[v][inv[u][i]]);\n                    used[v][inv[u][i]]\
    \ = true;\n                    dfs(dfs, v);\n                }\n             \
    \   res.push_back(u);\n            };\n            dfs(dfs, start);\n        \
    \    if (res.size() != edge_num + 1) return std::nullopt;\n            return\
    \ res;\n        }\n        std::optional<std::vector<int>> eulerian_trail() {\n\
    \            int s = -1, t = -1, invalid = -1;\n            for (int i = 0; i\
    \ < n; ++i) if (g[i].size() & 1) (s < 0 ? s : t < 0 ? t : invalid) = i;\n    \
    \        if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;\n          \
    \  add_edge(s, t);\n            auto opt_res = eulerian_circuit(s);\n        \
    \    if (not opt_res.has_value()) return std::nullopt;\n            auto res =\
    \ *opt_res;\n            res.pop_back();\n            // remove edge (s, t)\n\
    \            g[s].pop_back(), inv[s].pop_back();\n            g[t].pop_back(),\
    \ inv[t].pop_back();\n            if (res.back() == t) return res;\n         \
    \   auto is_st_edge = [&](int u, int v) {\n                return (u == s and\
    \ v == t) or (u == t and v == s);\n            };\n            std::rotate(res.begin(),\
    \ std::adjacent_find(res.begin(), res.end(), is_st_edge) + 1, res.end());\n  \
    \          return res;\n        }\n        \n        const std::vector<int>& operator[](int\
    \ u) const {\n            return g[u];\n        }\n        std::pair<int, int>\
    \ rev_edge(int u, int i) const {\n            return { g[u][i], inv[u][i] };\n\
    \        }\n    private:\n        int n;\n        std::vector<std::vector<int>>\
    \ g;\n        std::vector<std::vector<int>> inv;\n\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_UNDIRECTED_EULERIAN_GRAPH\n#define SUISEN_UNDIRECTED_EULERIAN_GRAPH\n\
    \n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\
    \nnamespace suisen {\n    struct UndirectedEulerianGraph {\n        UndirectedEulerianGraph()\
    \ {}\n        UndirectedEulerianGraph(int n) : n(n), g(n), inv(n) {}\n\n     \
    \   void add_edge(int u, int v) {\n            const int su = g[u].size();\n \
    \           g[u].push_back(v);\n            const int sv = g[v].size();\n    \
    \        g[v].push_back(u);\n            inv[u].push_back(sv);\n            inv[v].push_back(su);\n\
    \        }\n\n        std::optional<std::vector<int>> eulerian_circuit(int start\
    \ = 0) {\n            std::size_t edge_num = 0;\n            std::vector<std::vector<bool>>\
    \ used(n);\n            for (int i = 0; i < n; ++i) {\n                const std::size_t\
    \ sz = g[i].size();\n                edge_num += sz;\n                used[i].resize(sz,\
    \ false);\n                if (sz & 1) return std::nullopt;\n            }\n \
    \           edge_num /= 2;\n            std::vector<int> res;\n            auto\
    \ dfs = [&](auto dfs, int u) -> void {\n                for (std::size_t i = 0;\
    \ i < g[u].size(); ++i) {\n                    if (used[u][i]) continue;\n   \
    \                 const int v = g[u][i];\n                    used[u][i] = true;\n\
    \                    assert(not used[v][inv[u][i]]);\n                    used[v][inv[u][i]]\
    \ = true;\n                    dfs(dfs, v);\n                }\n             \
    \   res.push_back(u);\n            };\n            dfs(dfs, start);\n        \
    \    if (res.size() != edge_num + 1) return std::nullopt;\n            return\
    \ res;\n        }\n        std::optional<std::vector<int>> eulerian_trail() {\n\
    \            int s = -1, t = -1, invalid = -1;\n            for (int i = 0; i\
    \ < n; ++i) if (g[i].size() & 1) (s < 0 ? s : t < 0 ? t : invalid) = i;\n    \
    \        if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;\n          \
    \  add_edge(s, t);\n            auto opt_res = eulerian_circuit(s);\n        \
    \    if (not opt_res.has_value()) return std::nullopt;\n            auto res =\
    \ *opt_res;\n            res.pop_back();\n            // remove edge (s, t)\n\
    \            g[s].pop_back(), inv[s].pop_back();\n            g[t].pop_back(),\
    \ inv[t].pop_back();\n            if (res.back() == t) return res;\n         \
    \   auto is_st_edge = [&](int u, int v) {\n                return (u == s and\
    \ v == t) or (u == t and v == s);\n            };\n            std::rotate(res.begin(),\
    \ std::adjacent_find(res.begin(), res.end(), is_st_edge) + 1, res.end());\n  \
    \          return res;\n        }\n        \n        const std::vector<int>& operator[](int\
    \ u) const {\n            return g[u];\n        }\n        std::pair<int, int>\
    \ rev_edge(int u, int i) const {\n            return { g[u][i], inv[u][i] };\n\
    \        }\n    private:\n        int n;\n        std::vector<std::vector<int>>\
    \ g;\n        std::vector<std::vector<int>> inv;\n\n    };\n}\n\n#endif // SUISEN_UNDIRECTED_EULERIAN_GRAPH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/undirected_eulerian_graph.hpp
  requiredBy: []
  timestamp: '2022-03-19 20:37:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/undirected_eulerian_graph.hpp
layout: document
title: Undirected Eulerian Graph
---
## Undirected Eulerian Graph