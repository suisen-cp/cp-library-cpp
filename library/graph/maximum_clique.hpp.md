---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/maximum_independent_set.hpp
    title: library/graph/maximum_independent_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/maximum_clique.hpp\"\n\n\n\n#line 1 \"library/graph/maximum_independent_set.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <deque>\n\
    #include <iostream>\n#include <vector>\n\nnamespace suisen {\n    std::vector<int>\
    \ maximum_independent_set(const std::vector<std::vector<int>>& g) {\n        const\
    \ int n = g.size();\n        if (n == 0) return {};\n\n        const int argmax_deg\
    \ = std::max_element(g.begin(), g.end(), [](const auto& adj1, const auto& adj2)\
    \ { return adj1.size() < adj2.size(); }) - g.begin();\n\n        if (g[argmax_deg].size()\
    \ <= 2) {\n            std::vector<int> mis;\n            std::vector<int> color(n,\
    \ -1);\n            for (int i = 0; i < n; ++i) if (color[i] < 0) {\n        \
    \        std::vector<int> updated;\n                std::array<int, 2> cnt{};\n\
    \                color[i] = 0;\n                std::deque<int> dq{ i };\n   \
    \             int p = -1;\n                while (dq.size()) {\n             \
    \       int u = dq.front();\n                    dq.pop_front();\n           \
    \         updated.push_back(u);\n                    ++cnt[color[u]];\n      \
    \              for (int v : g[u]) {\n                        if (color[v] < 0)\
    \ {\n                            color[v] = 1 ^ color[u];\n                  \
    \          dq.push_back(v);\n                        } else if (color[u] == color[v])\
    \ {\n                            p = u;\n                        }\n         \
    \           }\n                }\n                int majority = cnt[1] >= cnt[0];\n\
    \                for (int u : updated) if (color[u] == majority and u != p) {\n\
    \                    mis.push_back(u);\n                }\n            }\n   \
    \         return mis;\n        }\n\n        std::vector<int> mis;\n        for\
    \ (const auto& remove_vertices : { std::vector<int>{}, g[argmax_deg] }) {\n  \
    \          std::vector<int8_t> rem_flg(n, false);\n            rem_flg[argmax_deg]\
    \ = true;\n            for (const auto& e : remove_vertices) {\n             \
    \   rem_flg[e] = true;\n            }\n            std::vector<int> bias(n + 1);\n\
    \            for (int i = 0; i < n; ++i) {\n                bias[i + 1] = bias[i]\
    \ + rem_flg[i];\n            }\n            std::vector<int> decomp(n, -1);\n\
    \            for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n             \
    \   decomp[i - bias[i]] = i;\n            }\n\n            std::vector<std::vector<int>>\
    \ h;\n            h.reserve(g.size() - remove_vertices.size() - 1);\n        \
    \    for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n                std::vector<int>\
    \ adj;\n                for (int j : g[i]) if (not rem_flg[j]) {\n           \
    \         adj.push_back(j - bias[j]);\n                }\n                h.push_back(std::move(adj));\n\
    \            }\n\n            std::vector<int> vs = maximum_independent_set(h);\n\
    \            for (auto& e : vs) {\n                e = decomp[e];\n          \
    \  }\n            if (remove_vertices.size()) {\n                vs.push_back(argmax_deg);\n\
    \            }\n            if (vs.size() > mis.size()) {\n                mis\
    \ = std::move(vs);\n            }\n        }\n        return mis;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 5 \"library/graph/maximum_clique.hpp\"\n\nnamespace\
    \ suisen {\n    std::vector<int> maximum_clique(const std::vector<std::vector<int>>&\
    \ g) {\n        const int n = g.size();\n        std::vector<std::vector<int>>\
    \ h(n);\n        for (int i = 0; i < n; ++i) {\n            std::vector<int8_t>\
    \ adj(n, false);\n            for (int j : g[i]) adj[j] = true;\n            for\
    \ (int j = 0; j < n; ++j) if (not adj[j]) h[i].push_back(j);\n        }\n    \
    \    return maximum_independent_set(h);\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MAXIMUM_CLIQUE\n#define SUISEN_MAXIMUM_CLIQUE\n\n#include\
    \ \"library/graph/maximum_independent_set.hpp\"\n\nnamespace suisen {\n    std::vector<int>\
    \ maximum_clique(const std::vector<std::vector<int>>& g) {\n        const int\
    \ n = g.size();\n        std::vector<std::vector<int>> h(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            std::vector<int8_t> adj(n, false);\n     \
    \       for (int j : g[i]) adj[j] = true;\n            for (int j = 0; j < n;\
    \ ++j) if (not adj[j]) h[i].push_back(j);\n        }\n        return maximum_independent_set(h);\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_MAXIMUM_CLIQUE\n"
  dependsOn:
  - library/graph/maximum_independent_set.hpp
  isVerificationFile: false
  path: library/graph/maximum_clique.hpp
  requiredBy: []
  timestamp: '2022-06-11 19:33:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/maximum_clique.hpp
layout: document
redirect_from:
- /library/library/graph/maximum_clique.hpp
- /library/library/graph/maximum_clique.hpp.html
title: library/graph/maximum_clique.hpp
---
