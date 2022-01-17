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
  bundledCode: "#line 1 \"library/graph/dijkstra.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n#include <queue>\n#include <vector>\n\nnamespace suisen {\n\
    template<typename Cost>\nclass dijkstra {\n    public:\n        template <typename\
    \ Transition>\n        dijkstra(unsigned int n, Transition transition, unsigned\
    \ int src) : _src(src) {\n            _par.resize(n);\n            _dist.assign(n,\
    \ UNREACHABLE);\n            _dist[src] = 0;\n            using state = std::pair<Cost,\
    \ unsigned int>;\n            std::priority_queue<state, std::vector<state>, std::greater<state>>\
    \ pq;\n            pq.emplace(0, src);\n            auto g = [&](unsigned int\
    \ u) {\n                return [&, u](unsigned int v, Cost new_cost) {\n     \
    \               if (new_cost < _dist[v]) pq.emplace(_dist[v] = new_cost, v), _par[v]\
    \ = u;\n                };\n            };\n            while (pq.size()) {\n\
    \                auto [du, u] = pq.top(); pq.pop();\n                if (du ==\
    \ _dist[u]) transition(u, du, g(u));\n            }\n        }\n        dijkstra(const\
    \ std::vector<std::vector<std::pair<int, Cost>>> &g, unsigned int src) :\n   \
    \         dijkstra(g.size(), [&](int u, Cost du, auto f) { for (auto [v, c] :\
    \ g[u]) f(v, du + c); }, src) {}\n        std::vector<unsigned int> path_to(unsigned\
    \ int t) const {\n            assert(is_reachale(t));\n            std::vector<unsigned\
    \ int> path = {t};\n            while (t != _src) path.push_back(t = _par[t]);\n\
    \            std::reverse(path.begin(), path.end());\n            return path;\n\
    \        }\n        Cost operator[](unsigned int t) const { return _dist[t]; }\n\
    \        bool is_reachale   (unsigned int t) const { return _dist[t] != UNREACHABLE;\
    \ }\n        bool is_unreachable(unsigned int t) const { return _dist[t] == UNREACHABLE;\
    \ }\n    private:\n        const Cost UNREACHABLE = std::numeric_limits<Cost>::max();\n\
    \        const unsigned int _src;\n        std::vector<Cost> _dist;\n        std::vector<unsigned\
    \ int> _par;\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_DIJKSTRA\n#define SUISEN_DIJKSTRA\n\n#include <algorithm>\n\
    #include <limits>\n#include <queue>\n#include <vector>\n\nnamespace suisen {\n\
    template<typename Cost>\nclass dijkstra {\n    public:\n        template <typename\
    \ Transition>\n        dijkstra(unsigned int n, Transition transition, unsigned\
    \ int src) : _src(src) {\n            _par.resize(n);\n            _dist.assign(n,\
    \ UNREACHABLE);\n            _dist[src] = 0;\n            using state = std::pair<Cost,\
    \ unsigned int>;\n            std::priority_queue<state, std::vector<state>, std::greater<state>>\
    \ pq;\n            pq.emplace(0, src);\n            auto g = [&](unsigned int\
    \ u) {\n                return [&, u](unsigned int v, Cost new_cost) {\n     \
    \               if (new_cost < _dist[v]) pq.emplace(_dist[v] = new_cost, v), _par[v]\
    \ = u;\n                };\n            };\n            while (pq.size()) {\n\
    \                auto [du, u] = pq.top(); pq.pop();\n                if (du ==\
    \ _dist[u]) transition(u, du, g(u));\n            }\n        }\n        dijkstra(const\
    \ std::vector<std::vector<std::pair<int, Cost>>> &g, unsigned int src) :\n   \
    \         dijkstra(g.size(), [&](int u, Cost du, auto f) { for (auto [v, c] :\
    \ g[u]) f(v, du + c); }, src) {}\n        std::vector<unsigned int> path_to(unsigned\
    \ int t) const {\n            assert(is_reachale(t));\n            std::vector<unsigned\
    \ int> path = {t};\n            while (t != _src) path.push_back(t = _par[t]);\n\
    \            std::reverse(path.begin(), path.end());\n            return path;\n\
    \        }\n        Cost operator[](unsigned int t) const { return _dist[t]; }\n\
    \        bool is_reachale   (unsigned int t) const { return _dist[t] != UNREACHABLE;\
    \ }\n        bool is_unreachable(unsigned int t) const { return _dist[t] == UNREACHABLE;\
    \ }\n    private:\n        const Cost UNREACHABLE = std::numeric_limits<Cost>::max();\n\
    \        const unsigned int _src;\n        std::vector<Cost> _dist;\n        std::vector<unsigned\
    \ int> _par;\n};\n} // namespace suisen\n\n#endif // SUISEN_DIJKSTRA\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2021-08-03 16:07:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/dijkstra.hpp
layout: document
title: Dijkstra
---
## Dijkstra