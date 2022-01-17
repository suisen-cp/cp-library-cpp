---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/cycle_detection.hpp
    title: Cycle Detection
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cycle_detection
    links:
    - https://judge.yosupo.jp/problem/cycle_detection
  bundledCode: "#line 1 \"test/src/graph/cycle_detection/cycle_detection.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n\n#line 1 \"library/graph/cycle_detection.hpp\"\
    \n\n\n\n#include <optional>\n#include <vector>\n\nnamespace suisen {\n\nenum class\
    \ GraphType {\n    DIRECTED, UNDIRECTED\n};\n\ntemplate <GraphType t>\nstd::optional<std::vector<int>>\
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
    \ suisen\n\n\n#line 7 \"test/src/graph/cycle_detection/cycle_detection.test.cpp\"\
    \nusing namespace suisen;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>>\
    \ g(n);\n    std::vector<long long> edges(m);\n    for (int i = 0; i < m; ++i)\
    \ {\n        long long u, v;\n        std::cin >> u >> v;\n        edges[i] =\
    \ u << 40 | v << 20 | i;\n        g[u].push_back(v);\n    }\n    std::sort(edges.begin(),\
    \ edges.end());\n\n    const auto optional_cycle = get_cycle<GraphType::DIRECTED>(g);\n\
    \    if (optional_cycle.has_value()) {\n        const auto &cycle = *optional_cycle;\n\
    \        const int sz = cycle.size();\n        std::cout << sz << '\\n';\n   \
    \     for (int i = 0; i < sz; ++i) {\n            const long long u = cycle[i],\
    \ v = cycle[(i + 1) % sz];\n            std::cout << (*std::lower_bound(edges.begin(),\
    \ edges.end(), u << 40 | v << 20) & ((1 << 20) - 1)) << '\\n';\n        }\n  \
    \  } else {\n        std::cout << -1 << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n\n#include \"library/graph/cycle_detection.hpp\"\
    \nusing namespace suisen;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>>\
    \ g(n);\n    std::vector<long long> edges(m);\n    for (int i = 0; i < m; ++i)\
    \ {\n        long long u, v;\n        std::cin >> u >> v;\n        edges[i] =\
    \ u << 40 | v << 20 | i;\n        g[u].push_back(v);\n    }\n    std::sort(edges.begin(),\
    \ edges.end());\n\n    const auto optional_cycle = get_cycle<GraphType::DIRECTED>(g);\n\
    \    if (optional_cycle.has_value()) {\n        const auto &cycle = *optional_cycle;\n\
    \        const int sz = cycle.size();\n        std::cout << sz << '\\n';\n   \
    \     for (int i = 0; i < sz; ++i) {\n            const long long u = cycle[i],\
    \ v = cycle[(i + 1) % sz];\n            std::cout << (*std::lower_bound(edges.begin(),\
    \ edges.end(), u << 40 | v << 20) & ((1 << 20) - 1)) << '\\n';\n        }\n  \
    \  } else {\n        std::cout << -1 << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/graph/cycle_detection.hpp
  isVerificationFile: true
  path: test/src/graph/cycle_detection/cycle_detection.test.cpp
  requiredBy: []
  timestamp: '2021-09-09 21:18:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/cycle_detection/cycle_detection.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/cycle_detection/cycle_detection.test.cpp
- /verify/test/src/graph/cycle_detection/cycle_detection.test.cpp.html
title: test/src/graph/cycle_detection/cycle_detection.test.cpp
---
