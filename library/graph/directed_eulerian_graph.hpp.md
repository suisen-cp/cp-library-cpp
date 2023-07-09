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
  bundledCode: "#line 1 \"library/graph/directed_eulerian_graph.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\n\
    namespace suisen {\n    struct DirectedEulerianGraph {\n        DirectedEulerianGraph()\
    \ = default;\n        DirectedEulerianGraph(int n) : n(n), g(n), in_deg(n, 0)\
    \ {}\n\n        void add_edge(int u, int v) {\n            g[u].push_back(v);\n\
    \            ++in_deg[v];\n        }\n\n        std::optional<std::vector<int>>\
    \ eulerian_circuit(int start = 0) {\n            std::size_t edge_num = 0;\n \
    \           std::vector<std::vector<bool>> used(n);\n            for (int i =\
    \ 0; i < n; ++i) {\n                const int sz = g[i].size();\n            \
    \    edge_num += sz;\n                used[i].resize(sz, false);\n           \
    \     if (in_deg[i] != sz) return std::nullopt;\n            }\n            std::vector<int>\
    \ res;\n            std::vector<std::size_t> iter(n);\n            auto dfs =\
    \ [&](auto dfs, int u) -> void {\n                for (std::size_t &i = iter[u];\
    \ i < g[u].size(); ++i) {\n                    if (used[u][i]) continue;\n   \
    \                 const int v = g[u][i];\n                    used[u][i] = true;\n\
    \                    dfs(dfs, v);\n                }\n                res.push_back(u);\n\
    \            };\n            dfs(dfs, start);\n            std::reverse(res.begin(),\
    \ res.end());\n            if (res.size() != edge_num + 1) return std::nullopt;\n\
    \            return res;\n        }\n        std::optional<std::vector<int>> eulerian_trail()\
    \ {\n            int s = -1, t = -1, invalid = -1;\n            for (int i = 0;\
    \ i < n; ++i) {\n                int out_deg = g[i].size();\n                if\
    \ (out_deg == in_deg[i] + 1) {\n                    (s < 0 ? s : invalid) = i;\n\
    \                } else if (out_deg == in_deg[i] - 1) {\n                    (t\
    \ < 0 ? t : invalid) = i;\n                } else if (out_deg != in_deg[i]) {\n\
    \                    invalid = i;\n                }\n            }\n        \
    \    if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;\n            add_edge(t,\
    \ s);\n            auto res = *eulerian_circuit(s);\n            res.pop_back();\n\
    \            // remove edge (t, s)\n            g[t].pop_back();\n           \
    \ if (res.back() == t) return res;\n            auto is_ts_edge = [&](int u, int\
    \ v) {\n                return u == t and v == s;\n            };\n          \
    \  std::rotate(res.begin(), std::adjacent_find(res.begin(), res.end(), is_ts_edge)\
    \ + 1, res.end());\n            return res;\n        }\n        \n        const\
    \ std::vector<int>& operator[](int u) const {\n            return g[u];\n    \
    \    }\n    private:\n        int n;\n        std::vector<std::vector<int>> g;\n\
    \        std::vector<int> in_deg;\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_DIRECTED_EULERIAN_GRAPH\n#define SUISEN_DIRECTED_EULERIAN_GRAPH\n\
    \n#include <algorithm>\n#include <cassert>\n#include <optional>\n#include <vector>\n\
    \nnamespace suisen {\n    struct DirectedEulerianGraph {\n        DirectedEulerianGraph()\
    \ = default;\n        DirectedEulerianGraph(int n) : n(n), g(n), in_deg(n, 0)\
    \ {}\n\n        void add_edge(int u, int v) {\n            g[u].push_back(v);\n\
    \            ++in_deg[v];\n        }\n\n        std::optional<std::vector<int>>\
    \ eulerian_circuit(int start = 0) {\n            std::size_t edge_num = 0;\n \
    \           std::vector<std::vector<bool>> used(n);\n            for (int i =\
    \ 0; i < n; ++i) {\n                const int sz = g[i].size();\n            \
    \    edge_num += sz;\n                used[i].resize(sz, false);\n           \
    \     if (in_deg[i] != sz) return std::nullopt;\n            }\n            std::vector<int>\
    \ res;\n            std::vector<std::size_t> iter(n);\n            auto dfs =\
    \ [&](auto dfs, int u) -> void {\n                for (std::size_t &i = iter[u];\
    \ i < g[u].size(); ++i) {\n                    if (used[u][i]) continue;\n   \
    \                 const int v = g[u][i];\n                    used[u][i] = true;\n\
    \                    dfs(dfs, v);\n                }\n                res.push_back(u);\n\
    \            };\n            dfs(dfs, start);\n            std::reverse(res.begin(),\
    \ res.end());\n            if (res.size() != edge_num + 1) return std::nullopt;\n\
    \            return res;\n        }\n        std::optional<std::vector<int>> eulerian_trail()\
    \ {\n            int s = -1, t = -1, invalid = -1;\n            for (int i = 0;\
    \ i < n; ++i) {\n                int out_deg = g[i].size();\n                if\
    \ (out_deg == in_deg[i] + 1) {\n                    (s < 0 ? s : invalid) = i;\n\
    \                } else if (out_deg == in_deg[i] - 1) {\n                    (t\
    \ < 0 ? t : invalid) = i;\n                } else if (out_deg != in_deg[i]) {\n\
    \                    invalid = i;\n                }\n            }\n        \
    \    if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;\n            add_edge(t,\
    \ s);\n            auto res = *eulerian_circuit(s);\n            res.pop_back();\n\
    \            // remove edge (t, s)\n            g[t].pop_back();\n           \
    \ if (res.back() == t) return res;\n            auto is_ts_edge = [&](int u, int\
    \ v) {\n                return u == t and v == s;\n            };\n          \
    \  std::rotate(res.begin(), std::adjacent_find(res.begin(), res.end(), is_ts_edge)\
    \ + 1, res.end());\n            return res;\n        }\n        \n        const\
    \ std::vector<int>& operator[](int u) const {\n            return g[u];\n    \
    \    }\n    private:\n        int n;\n        std::vector<std::vector<int>> g;\n\
    \        std::vector<int> in_deg;\n    };\n}\n\n#endif // SUISEN_DIRECTED_EULERIAN_GRAPH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/directed_eulerian_graph.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/directed_eulerian_graph.hpp
layout: document
title: Directed Eulerian Graph
---
## Directed Eulerian Graph