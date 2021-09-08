---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/cycle_detection.hpp
    title: library/graph/cycle_detection.hpp
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
    \n\n\n\n#include <optional>\n#include <vector>\n\nnamespace suisen {\n\nstd::optional<std::vector<int>>\
    \ get_cycle_digraph(const std::vector<std::vector<int>> &g) {\n    const int n\
    \ = g.size();\n    std::vector<int> index(n, -1);\n    std::vector<char> vis(n,\
    \ false);\n    std::vector<int> st, it;\n    st.reserve(n), it.reserve(n);\n \
    \   for (int i = 0; i < n; ++i) {\n        if (vis[i]) continue;\n        index[i]\
    \ = 0;\n        vis[i] = true;\n        st.push_back(i);\n        it.push_back(0);\n\
    \        while (st.size()) {\n            const int u = st.back();\n         \
    \   if (it.back() == int(g[u].size())) {\n                index[u] = -1;\n   \
    \             st.pop_back();\n                it.pop_back();\n               \
    \ continue;\n            }\n            const int v = g[u][it.back()++];\n   \
    \         if (index[v] >= 0) {\n                st.erase(st.begin(), st.begin()\
    \ + index[v]);\n                return st;\n            }\n            if (vis[v])\
    \ continue;\n            index[v] = st.size();\n            vis[v] = true;\n \
    \           st.push_back(v);\n            it.push_back(0);\n        }\n    }\n\
    \    return std::nullopt;\n}\n\n} // namespace suisen\n\n\n\n#line 7 \"test/src/graph/cycle_detection/cycle_detection.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>> g(n);\n\
    \    std::vector<long long> edges(m);\n    for (int i = 0; i < m; ++i) {\n   \
    \     long long u, v;\n        std::cin >> u >> v;\n        edges[i] = u << 40\
    \ | v << 20 | i;\n        g[u].push_back(v);\n    }\n    std::sort(edges.begin(),\
    \ edges.end());\n    const auto optional_cycle = suisen::get_cycle_digraph(g);\n\
    \    if (optional_cycle.has_value()) {\n        const auto &cycle = *optional_cycle;\n\
    \        const int sz = cycle.size();\n        std::cout << sz << '\\n';\n   \
    \     for (int i = 0; i < sz; ++i) {\n            const long long u = cycle[i],\
    \ v = cycle[(i + 1) % sz];\n            std::cout << (*std::lower_bound(edges.begin(),\
    \ edges.end(), u << 40 | v << 20) & ((1 << 20) - 1)) << '\\n';\n        }\n  \
    \  } else {\n        std::cout << -1 << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cycle_detection\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n\n#include \"library/graph/cycle_detection.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>> g(n);\n\
    \    std::vector<long long> edges(m);\n    for (int i = 0; i < m; ++i) {\n   \
    \     long long u, v;\n        std::cin >> u >> v;\n        edges[i] = u << 40\
    \ | v << 20 | i;\n        g[u].push_back(v);\n    }\n    std::sort(edges.begin(),\
    \ edges.end());\n    const auto optional_cycle = suisen::get_cycle_digraph(g);\n\
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
  timestamp: '2021-09-09 05:49:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/cycle_detection/cycle_detection.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/cycle_detection/cycle_detection.test.cpp
- /verify/test/src/graph/cycle_detection/cycle_detection.test.cpp.html
title: test/src/graph/cycle_detection/cycle_detection.test.cpp
---
