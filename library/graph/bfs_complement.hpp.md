---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/bfs_complement/AOJ_2744.test.cpp
    title: test/src/graph/bfs_complement/AOJ_2744.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/bfs_complement.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cstdint>\n#include <deque>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\nnamespace suisen {\n    struct ComplementBFS {\n        static\
    \ constexpr int unreachable = -1;\n\n        ComplementBFS(int n = 0) : n(n),\
    \ g(n) {}\n        template <typename Edges>\n        ComplementBFS(int n, const\
    \ Edges &edges) : ComplementBFS(n) {\n            for (const auto &[u, v] : edges)\
    \ add_edge(u, v);\n        }\n        ComplementBFS(const std::vector<std::vector<int>>&\
    \ g) : n(g.size()), g(g) {}\n\n        void add_edge(int u, int v) {\n       \
    \     g[u].push_back(v);\n            g[v].push_back(u);\n        }\n\n      \
    \  std::vector<int> distance(const std::vector<int>& src) const {\n          \
    \  std::vector<int> s = [&] {\n                std::vector<int8_t> is_src(n);\n\
    \                for (int v : src) is_src[v] = true;\n                std::vector<int>\
    \ s;\n                for (int i = 0; i < n; ++i) if (not is_src[i]) s.push_back(i);\n\
    \                return s;\n            }();\n\n            std::vector<int> dist(n,\
    \ unreachable);\n            for (int v : dist) dist[v] = 0;\n\n            std::vector<int8_t>\
    \ adj(n);\n            std::deque<int> dq(src.begin(), src.end());\n         \
    \   while (dq.size()) {\n                int u = dq.front();\n               \
    \ dq.pop_front();\n                for (int v : g[u]) adj[v] = true;\n       \
    \         std::size_t nsiz = std::partition(s.begin(), s.end(), [&adj](int v)\
    \ { return adj[v]; }) - s.begin();\n                for (; s.size() > nsiz; s.pop_back())\
    \ {\n                    int v = s.back();\n                    dist[v] = dist[u]\
    \ + 1, dq.push_back(v);\n                }\n                for (int v : g[u])\
    \ adj[v] = false;\n            }\n            return dist;\n        }\n      \
    \  std::vector<int> distance(int s) const {\n            return distance(std::vector<int>{\
    \ s });\n        }\n\n        std::vector<std::vector<int>> connected_components()\
    \ const {\n            std::vector<std::vector<int>> res;\n\n            std::vector<int8_t>\
    \ vis(n, false);\n\n            std::vector<int> s(n);\n            std::iota(s.begin(),\
    \ s.end(), 0);\n\n            std::vector<int8_t> adj(n);\n            for (int\
    \ i = 0; i < n; ++i) if (not vis[i]) {\n                s.erase(std::find(s.begin(),\
    \ s.end(), i));\n                auto& cmp = res.emplace_back();\n           \
    \     std::deque<int> dq{ i };\n                while (dq.size()) {\n        \
    \            int u = dq.front();\n                    dq.pop_front();\n      \
    \              cmp.push_back(u);\n                    vis[u] = true;\n       \
    \             for (int v : g[u]) adj[v] = true;\n                    auto it =\
    \ std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; });\n    \
    \                std::move(it, s.end(), std::back_inserter(dq));\n           \
    \         s.erase(it, s.end());\n                    for (int v : g[u]) adj[v]\
    \ = false;\n                }\n            }\n            return res;\n      \
    \  }\n    private:\n        int n;\n        std::vector<std::vector<int>> g;\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BFS_COMPLEMENT\n#define SUISEN_BFS_COMPLEMENT\n\n#include\
    \ <algorithm>\n#include <cstdint>\n#include <deque>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace suisen {\n    struct ComplementBFS\
    \ {\n        static constexpr int unreachable = -1;\n\n        ComplementBFS(int\
    \ n = 0) : n(n), g(n) {}\n        template <typename Edges>\n        ComplementBFS(int\
    \ n, const Edges &edges) : ComplementBFS(n) {\n            for (const auto &[u,\
    \ v] : edges) add_edge(u, v);\n        }\n        ComplementBFS(const std::vector<std::vector<int>>&\
    \ g) : n(g.size()), g(g) {}\n\n        void add_edge(int u, int v) {\n       \
    \     g[u].push_back(v);\n            g[v].push_back(u);\n        }\n\n      \
    \  std::vector<int> distance(const std::vector<int>& src) const {\n          \
    \  std::vector<int> s = [&] {\n                std::vector<int8_t> is_src(n);\n\
    \                for (int v : src) is_src[v] = true;\n                std::vector<int>\
    \ s;\n                for (int i = 0; i < n; ++i) if (not is_src[i]) s.push_back(i);\n\
    \                return s;\n            }();\n\n            std::vector<int> dist(n,\
    \ unreachable);\n            for (int v : dist) dist[v] = 0;\n\n            std::vector<int8_t>\
    \ adj(n);\n            std::deque<int> dq(src.begin(), src.end());\n         \
    \   while (dq.size()) {\n                int u = dq.front();\n               \
    \ dq.pop_front();\n                for (int v : g[u]) adj[v] = true;\n       \
    \         std::size_t nsiz = std::partition(s.begin(), s.end(), [&adj](int v)\
    \ { return adj[v]; }) - s.begin();\n                for (; s.size() > nsiz; s.pop_back())\
    \ {\n                    int v = s.back();\n                    dist[v] = dist[u]\
    \ + 1, dq.push_back(v);\n                }\n                for (int v : g[u])\
    \ adj[v] = false;\n            }\n            return dist;\n        }\n      \
    \  std::vector<int> distance(int s) const {\n            return distance(std::vector<int>{\
    \ s });\n        }\n\n        std::vector<std::vector<int>> connected_components()\
    \ const {\n            std::vector<std::vector<int>> res;\n\n            std::vector<int8_t>\
    \ vis(n, false);\n\n            std::vector<int> s(n);\n            std::iota(s.begin(),\
    \ s.end(), 0);\n\n            std::vector<int8_t> adj(n);\n            for (int\
    \ i = 0; i < n; ++i) if (not vis[i]) {\n                s.erase(std::find(s.begin(),\
    \ s.end(), i));\n                auto& cmp = res.emplace_back();\n           \
    \     std::deque<int> dq{ i };\n                while (dq.size()) {\n        \
    \            int u = dq.front();\n                    dq.pop_front();\n      \
    \              cmp.push_back(u);\n                    vis[u] = true;\n       \
    \             for (int v : g[u]) adj[v] = true;\n                    auto it =\
    \ std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; });\n    \
    \                std::move(it, s.end(), std::back_inserter(dq));\n           \
    \         s.erase(it, s.end());\n                    for (int v : g[u]) adj[v]\
    \ = false;\n                }\n            }\n            return res;\n      \
    \  }\n    private:\n        int n;\n        std::vector<std::vector<int>> g;\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_BFS_COMPLEMENT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/bfs_complement.hpp
  requiredBy: []
  timestamp: '2022-11-16 20:35:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/bfs_complement/AOJ_2744.test.cpp
documentation_of: library/graph/bfs_complement.hpp
layout: document
redirect_from:
- /library/library/graph/bfs_complement.hpp
- /library/library/graph/bfs_complement.hpp.html
title: library/graph/bfs_complement.hpp
---
