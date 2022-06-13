---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/maximum_independent_set.hpp
    title: "Maximum Independent Set (\u6700\u5927\u72EC\u7ACB\u96C6\u5408)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/minimum_vertex_cover.hpp\"\n\n\n\n#line 1\
    \ \"library/graph/maximum_independent_set.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <deque>\n#include <iostream>\n\
    #include <vector>\n\nnamespace suisen {\n    std::vector<int> maximum_independent_set(const\
    \ std::vector<std::vector<int>>& g) {\n        const int n = g.size();\n     \
    \   if (n == 0) return {};\n\n        const int argmax_deg = std::max_element(g.begin(),\
    \ g.end(), [](const auto& adj1, const auto& adj2) { return adj1.size() < adj2.size();\
    \ }) - g.begin();\n\n        if (g[argmax_deg].size() <= 2) {\n            std::vector<int>\
    \ mis;\n            std::vector<int> color(n, -1);\n            for (int i = 0;\
    \ i < n; ++i) if (color[i] < 0) {\n                std::vector<int> updated;\n\
    \                std::array<int, 2> cnt{};\n                color[i] = 0;\n  \
    \              std::deque<int> dq{ i };\n                int p = -1;\n       \
    \         while (dq.size()) {\n                    int u = dq.front();\n     \
    \               dq.pop_front();\n                    updated.push_back(u);\n \
    \                   ++cnt[color[u]];\n                    for (int v : g[u]) {\n\
    \                        if (color[v] < 0) {\n                            color[v]\
    \ = 1 ^ color[u];\n                            dq.push_back(v);\n            \
    \            } else if (color[u] == color[v]) {\n                            p\
    \ = u;\n                        }\n                    }\n                }\n\
    \                int majority = cnt[1] >= cnt[0];\n                for (int u\
    \ : updated) if (color[u] == majority and u != p) {\n                    mis.push_back(u);\n\
    \                }\n            }\n            return mis;\n        }\n\n    \
    \    std::vector<int> mis;\n        for (const auto& remove_vertices : { std::vector<int>{},\
    \ g[argmax_deg] }) {\n            std::vector<int8_t> rem_flg(n, false);\n   \
    \         rem_flg[argmax_deg] = true;\n            for (const auto& e : remove_vertices)\
    \ {\n                rem_flg[e] = true;\n            }\n            std::vector<int>\
    \ bias(n + 1);\n            for (int i = 0; i < n; ++i) {\n                bias[i\
    \ + 1] = bias[i] + rem_flg[i];\n            }\n            std::vector<int> decomp(n,\
    \ -1);\n            for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n      \
    \          decomp[i - bias[i]] = i;\n            }\n\n            std::vector<std::vector<int>>\
    \ h;\n            h.reserve(g.size() - remove_vertices.size() - 1);\n        \
    \    for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n                std::vector<int>\
    \ adj;\n                for (int j : g[i]) if (not rem_flg[j]) {\n           \
    \         adj.push_back(j - bias[j]);\n                }\n                h.push_back(std::move(adj));\n\
    \            }\n\n            std::vector<int> vs = maximum_independent_set(h);\n\
    \            for (auto& e : vs) {\n                e = decomp[e];\n          \
    \  }\n            if (remove_vertices.size()) {\n                vs.push_back(argmax_deg);\n\
    \            }\n            if (vs.size() > mis.size()) {\n                mis\
    \ = std::move(vs);\n            }\n        }\n        return mis;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 5 \"library/graph/minimum_vertex_cover.hpp\"\n\
    \nnamespace suisen {\n    std::vector<int> minimum_vertex_cover(const std::vector<std::vector<int>>&\
    \ g) {\n        const int n = g.size();\n        std::vector<int8_t> in_msi(n,\
    \ false);\n        for (int v : maximum_independent_set(g)) in_msi[v] = true;\n\
    \        std::vector<int> res;\n        for (int i = 0; i < n; ++i) if (not in_msi[i])\
    \ res.push_back(i);\n        return res;\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_MINIMUM_VERTEX_COVER\n#define SUISEN_MINIMUM_VERTEX_COVER\n\
    \n#include \"library/graph/maximum_independent_set.hpp\"\n\nnamespace suisen {\n\
    \    std::vector<int> minimum_vertex_cover(const std::vector<std::vector<int>>&\
    \ g) {\n        const int n = g.size();\n        std::vector<int8_t> in_msi(n,\
    \ false);\n        for (int v : maximum_independent_set(g)) in_msi[v] = true;\n\
    \        std::vector<int> res;\n        for (int i = 0; i < n; ++i) if (not in_msi[i])\
    \ res.push_back(i);\n        return res;\n    }\n} // namespace suisen\n\n#endif\
    \ // SUISEN_MINIMUM_VERTEX_COVER\n"
  dependsOn:
  - library/graph/maximum_independent_set.hpp
  isVerificationFile: false
  path: library/graph/minimum_vertex_cover.hpp
  requiredBy: []
  timestamp: '2022-06-11 19:33:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/minimum_vertex_cover.hpp
layout: document
title: "Minimum Vertex Cover (\u6700\u5C0F\u9802\u70B9\u88AB\u8986)"
---
## Minimum Vertex Cover (最小頂点被覆)

グラフ $G(V,E)$ の最小頂点被覆は，$G$ の最大独立集合の補集合であることを用いて計算する．
