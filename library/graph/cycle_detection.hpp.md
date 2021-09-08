---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/cycle_detection/cycle_detection.test.cpp
    title: test/src/graph/cycle_detection/cycle_detection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/cycle_detection.hpp\"\n\n\n\n#include <optional>\n\
    #include <vector>\n\nnamespace suisen {\n\nstd::optional<std::vector<int>> get_cycle_digraph(const\
    \ std::vector<std::vector<int>> &g) {\n    const int n = g.size();\n    std::vector<int>\
    \ index(n, -1);\n    std::vector<char> vis(n, false);\n    std::vector<int> st,\
    \ it;\n    st.reserve(n), it.reserve(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        if (vis[i]) continue;\n        index[i] = 0;\n        vis[i] = true;\n\
    \        st.push_back(i);\n        it.push_back(0);\n        while (st.size())\
    \ {\n            const int u = st.back();\n            if (it.back() == int(g[u].size()))\
    \ {\n                index[u] = -1;\n                st.pop_back();\n        \
    \        it.pop_back();\n                continue;\n            }\n          \
    \  const int v = g[u][it.back()++];\n            if (index[v] >= 0) {\n      \
    \          st.erase(st.begin(), st.begin() + index[v]);\n                return\
    \ st;\n            }\n            if (vis[v]) continue;\n            index[v]\
    \ = st.size();\n            vis[v] = true;\n            st.push_back(v);\n   \
    \         it.push_back(0);\n        }\n    }\n    return std::nullopt;\n}\n\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CYCLE_DETECTION\n#define SUISEN_CYCLE_DETECTION\n\n#include\
    \ <optional>\n#include <vector>\n\nnamespace suisen {\n\nstd::optional<std::vector<int>>\
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
    \    return std::nullopt;\n}\n\n} // namespace suisen\n\n\n#endif // SUISEN_CYCLE_DETECTION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/cycle_detection.hpp
  requiredBy: []
  timestamp: '2021-09-09 05:49:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/cycle_detection/cycle_detection.test.cpp
documentation_of: library/graph/cycle_detection.hpp
layout: document
redirect_from:
- /library/library/graph/cycle_detection.hpp
- /library/library/graph/cycle_detection.hpp.html
title: library/graph/cycle_detection.hpp
---
