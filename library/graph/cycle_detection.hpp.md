---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/cycle_detection/cycle_detection.test.cpp
    title: test/src/graph/cycle_detection/cycle_detection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/cycle_detection/cycle_detection_2.test.cpp
    title: test/src/graph/cycle_detection/cycle_detection_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/cycle_detection.hpp\"\n\n\n\n#include <optional>\n\
    #include <vector>\n\nnamespace suisen {\n\nenum class GraphType {\n    DIRECTED,\
    \ UNDIRECTED\n};\n\ntemplate <GraphType t>\nstd::optional<std::vector<int>> get_cycle(const\
    \ std::vector<std::vector<int>> &g) {\n    const int n = g.size();\n    // detect\
    \ multiedge\n    if constexpr (t == GraphType::UNDIRECTED) {\n        std::vector<uint8_t>\
    \ exists(n, 0);\n        for (int u = 0; u < n; ++u) {\n            for (int v\
    \ : g[u]) if (exists[v]++) return std::vector<int> { u, v };\n            for\
    \ (int v : g[u]) exists[v] = 0;\n        }\n    }\n    // simulate dfs\n    std::vector<int>\
    \ itr(n, 0), stk, par(0);\n    if constexpr (t == GraphType::UNDIRECTED) par.resize(n,\
    \ -1);\n    stk.reserve(n);\n    std::vector<uint8_t> in(n, false);\n    for (int\
    \ i = 0; i < n; ++i) {\n        if (itr[i] == 0) stk.push_back(i), in[i] = true;\n\
    \        while (stk.size()) {\n            const int u = stk.back();\n       \
    \     if (itr[u] < int(g[u].size())) {\n                const int v = g[u][itr[u]++];\n\
    \                if constexpr (t == GraphType::UNDIRECTED) if (v == par[u]) continue;\n\
    \                if (in[v]) return stk.erase(stk.begin(), std::find(stk.begin(),\
    \ stk.end(), v)), stk;\n                if (itr[v] == 0) {\n                 \
    \   stk.push_back(v), in[v] = true;\n                    if constexpr (t == GraphType::UNDIRECTED)\
    \ par[v] = u;\n                }\n            } else stk.pop_back(), in[u] = false;\n\
    \        }\n    }\n    return std::nullopt;\n}\n\ntemplate <GraphType t, typename\
    \ T>\nstd::optional<std::vector<T>> get_cycle_values(const std::vector<std::vector<std::pair<int,\
    \ T>>> &g) {\n    const int n = g.size();\n    // detect multiedge\n    if constexpr\
    \ (t == GraphType::UNDIRECTED) {\n        std::vector<uint8_t> exists(n, 0);\n\
    \        std::vector<T> vals(n);\n        for (int u = 0; u < n; ++u) {\n    \
    \        for (const auto &[v, val] : g[u]) if (exists[v]++) return std::vector<T>\
    \ { vals[v], val };\n            for (const auto &[v, val] : g[u]) exists[v] =\
    \ 0;\n        }\n    }\n    // simulate dfs\n    std::vector<int> itr(n, 0), stk,\
    \ par(0);\n    std::vector<T> vals;\n    if constexpr (t == GraphType::UNDIRECTED)\
    \ par.resize(n, -1);\n    stk.reserve(n), vals.reserve(n);\n    std::vector<uint8_t>\
    \ in(n, false);\n    for (int i = 0; i < n; ++i) {\n        if (itr[i] == 0) stk.push_back(i),\
    \ in[i] = true, vals.push_back(T{});\n        while (stk.size()) {\n         \
    \   const int u = stk.back();\n            if (itr[u] < int(g[u].size())) {\n\
    \                const auto &[v, val] = g[u][itr[u]++];\n                if constexpr\
    \ (t == GraphType::UNDIRECTED) if (v == par[u]) continue;\n                if\
    \ (in[v]) {\n                    const int idx = std::find(stk.begin(), stk.end(),\
    \ v) - stk.begin();\n                    vals[idx] = val;\n                  \
    \  vals.erase(vals.begin(), vals.begin() + idx);\n                    return vals;\n\
    \                }\n                if (itr[v] == 0) {\n                    stk.push_back(v),\
    \ in[v] = true, vals.push_back(val);\n                    if constexpr (t == GraphType::UNDIRECTED)\
    \ par[v] = u;\n                }\n            } else stk.pop_back(), in[u] = false,\
    \ vals.pop_back();\n        }\n    }\n    return std::nullopt;\n}\n\n} // namespace\
    \ suisen\n\n\n"
  code: "#ifndef SUISEN_CYCLE_DETECTION\n#define SUISEN_CYCLE_DETECTION\n\n#include\
    \ <optional>\n#include <vector>\n\nnamespace suisen {\n\nenum class GraphType\
    \ {\n    DIRECTED, UNDIRECTED\n};\n\ntemplate <GraphType t>\nstd::optional<std::vector<int>>\
    \ get_cycle(const std::vector<std::vector<int>> &g) {\n    const int n = g.size();\n\
    \    // detect multiedge\n    if constexpr (t == GraphType::UNDIRECTED) {\n  \
    \      std::vector<uint8_t> exists(n, 0);\n        for (int u = 0; u < n; ++u)\
    \ {\n            for (int v : g[u]) if (exists[v]++) return std::vector<int> {\
    \ u, v };\n            for (int v : g[u]) exists[v] = 0;\n        }\n    }\n \
    \   // simulate dfs\n    std::vector<int> itr(n, 0), stk, par(0);\n    if constexpr\
    \ (t == GraphType::UNDIRECTED) par.resize(n, -1);\n    stk.reserve(n);\n    std::vector<uint8_t>\
    \ in(n, false);\n    for (int i = 0; i < n; ++i) {\n        if (itr[i] == 0) stk.push_back(i),\
    \ in[i] = true;\n        while (stk.size()) {\n            const int u = stk.back();\n\
    \            if (itr[u] < int(g[u].size())) {\n                const int v = g[u][itr[u]++];\n\
    \                if constexpr (t == GraphType::UNDIRECTED) if (v == par[u]) continue;\n\
    \                if (in[v]) return stk.erase(stk.begin(), std::find(stk.begin(),\
    \ stk.end(), v)), stk;\n                if (itr[v] == 0) {\n                 \
    \   stk.push_back(v), in[v] = true;\n                    if constexpr (t == GraphType::UNDIRECTED)\
    \ par[v] = u;\n                }\n            } else stk.pop_back(), in[u] = false;\n\
    \        }\n    }\n    return std::nullopt;\n}\n\ntemplate <GraphType t, typename\
    \ T>\nstd::optional<std::vector<T>> get_cycle_values(const std::vector<std::vector<std::pair<int,\
    \ T>>> &g) {\n    const int n = g.size();\n    // detect multiedge\n    if constexpr\
    \ (t == GraphType::UNDIRECTED) {\n        std::vector<uint8_t> exists(n, 0);\n\
    \        std::vector<T> vals(n);\n        for (int u = 0; u < n; ++u) {\n    \
    \        for (const auto &[v, val] : g[u]) if (exists[v]++) return std::vector<T>\
    \ { vals[v], val };\n            for (const auto &[v, val] : g[u]) exists[v] =\
    \ 0;\n        }\n    }\n    // simulate dfs\n    std::vector<int> itr(n, 0), stk,\
    \ par(0);\n    std::vector<T> vals;\n    if constexpr (t == GraphType::UNDIRECTED)\
    \ par.resize(n, -1);\n    stk.reserve(n), vals.reserve(n);\n    std::vector<uint8_t>\
    \ in(n, false);\n    for (int i = 0; i < n; ++i) {\n        if (itr[i] == 0) stk.push_back(i),\
    \ in[i] = true, vals.push_back(T{});\n        while (stk.size()) {\n         \
    \   const int u = stk.back();\n            if (itr[u] < int(g[u].size())) {\n\
    \                const auto &[v, val] = g[u][itr[u]++];\n                if constexpr\
    \ (t == GraphType::UNDIRECTED) if (v == par[u]) continue;\n                if\
    \ (in[v]) {\n                    const int idx = std::find(stk.begin(), stk.end(),\
    \ v) - stk.begin();\n                    vals[idx] = val;\n                  \
    \  vals.erase(vals.begin(), vals.begin() + idx);\n                    return vals;\n\
    \                }\n                if (itr[v] == 0) {\n                    stk.push_back(v),\
    \ in[v] = true, vals.push_back(val);\n                    if constexpr (t == GraphType::UNDIRECTED)\
    \ par[v] = u;\n                }\n            } else stk.pop_back(), in[u] = false,\
    \ vals.pop_back();\n        }\n    }\n    return std::nullopt;\n}\n\n} // namespace\
    \ suisen\n\n#endif // SUISEN_CYCLE_DETECTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/cycle_detection.hpp
  requiredBy: []
  timestamp: '2021-09-09 21:18:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/cycle_detection/cycle_detection.test.cpp
  - test/src/graph/cycle_detection/cycle_detection_2.test.cpp
documentation_of: library/graph/cycle_detection.hpp
layout: document
title: Cycle Detection
---
## Cycle Detection