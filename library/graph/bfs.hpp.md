---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/graph/bfs_complement/AOJ_2744.test.cpp
    title: test/src/graph/bfs_complement/AOJ_2744.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/bfs.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cstdint>\n#include <deque>\n#include <numeric>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct BFS {\n        static constexpr int\
    \ unreachable = -1;\n\n        BFS(int n = 0) : n(n), g(n) {}\n        template\
    \ <typename Edges>\n        BFS(int n, const Edges& edges) : BFS(n) {\n      \
    \      for (const auto& [u, v] : edges) add_edge(u, v);\n        }\n        BFS(const\
    \ std::vector<std::vector<int>>& g) : n(g.size()), g(g) {}\n\n        void add_edge(int\
    \ u, int v) {\n            g[u].push_back(v);\n            g[v].push_back(u);\n\
    \        }\n\n        std::vector<int> distance(const std::vector<int>& src) const\
    \ {\n            std::vector<int> dist(n, unreachable);\n            for (int\
    \ v : dist) dist[v] = 0;\n\n            std::deque<int> dq(src.begin(), src.end());\n\
    \            while (dq.size()) {\n                int u = dq.front();\n      \
    \          dq.pop_front();\n                for (int v : g[u]) if (dist[v] ==\
    \ unreachable) {\n                    dist[v] = dist[u] + 1;\n               \
    \     dq.push_back(v);\n                }\n            }\n            return dist;\n\
    \        }\n        std::vector<int> distance(int s) const {\n            return\
    \ distance(std::vector<int>{ s });\n        }\n\n        std::vector<std::vector<int>>\
    \ connected_components() const {\n            std::vector<std::vector<int>> res;\n\
    \n            std::vector<int8_t> vis(n, false);\n\n            for (int i = 0;\
    \ i < n; ++i) if (not std::exchange(vis[i], true)) {\n                auto& cmp\
    \ = res.emplace_back();\n                std::deque<int> dq{ i };\n          \
    \      while (dq.size()) {\n                    int u = dq.front();\n        \
    \            dq.pop_front();\n                    cmp.push_back(u);\n        \
    \            for (int v : g[u]) if (not std::exchange(vis[v], true)) {\n     \
    \                   dq.push_back(v);\n                    }\n                }\n\
    \            }\n            return res;\n        }\n    private:\n        int\
    \ n;\n        std::vector<std::vector<int>> g;\n    };\n} // namespace suisen\n\
    \n\n"
  code: "#ifndef SUISEN_BFS\n#define SUISEN_BFS\n\n#include <algorithm>\n#include\
    \ <cstdint>\n#include <deque>\n#include <numeric>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct BFS {\n        static constexpr int\
    \ unreachable = -1;\n\n        BFS(int n = 0) : n(n), g(n) {}\n        template\
    \ <typename Edges>\n        BFS(int n, const Edges& edges) : BFS(n) {\n      \
    \      for (const auto& [u, v] : edges) add_edge(u, v);\n        }\n        BFS(const\
    \ std::vector<std::vector<int>>& g) : n(g.size()), g(g) {}\n\n        void add_edge(int\
    \ u, int v) {\n            g[u].push_back(v);\n            g[v].push_back(u);\n\
    \        }\n\n        std::vector<int> distance(const std::vector<int>& src) const\
    \ {\n            std::vector<int> dist(n, unreachable);\n            for (int\
    \ v : dist) dist[v] = 0;\n\n            std::deque<int> dq(src.begin(), src.end());\n\
    \            while (dq.size()) {\n                int u = dq.front();\n      \
    \          dq.pop_front();\n                for (int v : g[u]) if (dist[v] ==\
    \ unreachable) {\n                    dist[v] = dist[u] + 1;\n               \
    \     dq.push_back(v);\n                }\n            }\n            return dist;\n\
    \        }\n        std::vector<int> distance(int s) const {\n            return\
    \ distance(std::vector<int>{ s });\n        }\n\n        std::vector<std::vector<int>>\
    \ connected_components() const {\n            std::vector<std::vector<int>> res;\n\
    \n            std::vector<int8_t> vis(n, false);\n\n            for (int i = 0;\
    \ i < n; ++i) if (not std::exchange(vis[i], true)) {\n                auto& cmp\
    \ = res.emplace_back();\n                std::deque<int> dq{ i };\n          \
    \      while (dq.size()) {\n                    int u = dq.front();\n        \
    \            dq.pop_front();\n                    cmp.push_back(u);\n        \
    \            for (int v : g[u]) if (not std::exchange(vis[v], true)) {\n     \
    \                   dq.push_back(v);\n                    }\n                }\n\
    \            }\n            return res;\n        }\n    private:\n        int\
    \ n;\n        std::vector<std::vector<int>> g;\n    };\n} // namespace suisen\n\
    \n#endif // SUISEN_BFS\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/bfs.hpp
  requiredBy: []
  timestamp: '2022-11-16 20:35:20+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/graph/bfs_complement/AOJ_2744.test.cpp
documentation_of: library/graph/bfs.hpp
layout: document
title: Bfs
---
## Bfs