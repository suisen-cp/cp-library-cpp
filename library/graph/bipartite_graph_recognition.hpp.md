---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
    title: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/bipartite_graph_recognition.hpp\"\n\n\n\n\
    #include <deque>\n#include <optional>\n#include <vector>\n\nnamespace suisen {\n\
    \    static std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>>&\
    \ g, int col0 = 0, int col1 = 1) {\n        const int n = g.size();\n        int\
    \ uncolored = 2;\n        while (uncolored == col0 or uncolored == col1) ++uncolored;\n\
    \        std::vector<int> color(n, uncolored);\n        for (int i = 0; i < n;\
    \ ++i) {\n            if (color[i] != uncolored) continue;\n            color[i]\
    \ = col0;\n            std::deque<int> dq { i };\n            while (dq.size())\
    \ {\n                int u = dq.front();\n                dq.pop_front();\n  \
    \              for (int v : g[u]) {\n                    if (color[v] == uncolored)\
    \ {\n                        dq.push_back(v);\n                        color[v]\
    \ = color[u] ^ col0 ^ col1;\n                    } else if (color[v] == color[u])\
    \ {\n                        return std::nullopt;\n                    }\n   \
    \             }\n            }\n        }\n        return color;\n    }\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BIPARTITE_GRAPH_RECOGNITION\n#define SUISEN_BIPARTITE_GRAPH_RECOGNITION\n\
    \n#include <deque>\n#include <optional>\n#include <vector>\n\nnamespace suisen\
    \ {\n    static std::optional<std::vector<int>> bipartite_coloring(const std::vector<std::vector<int>>&\
    \ g, int col0 = 0, int col1 = 1) {\n        const int n = g.size();\n        int\
    \ uncolored = 2;\n        while (uncolored == col0 or uncolored == col1) ++uncolored;\n\
    \        std::vector<int> color(n, uncolored);\n        for (int i = 0; i < n;\
    \ ++i) {\n            if (color[i] != uncolored) continue;\n            color[i]\
    \ = col0;\n            std::deque<int> dq { i };\n            while (dq.size())\
    \ {\n                int u = dq.front();\n                dq.pop_front();\n  \
    \              for (int v : g[u]) {\n                    if (color[v] == uncolored)\
    \ {\n                        dq.push_back(v);\n                        color[v]\
    \ = color[u] ^ col0 ^ col1;\n                    } else if (color[v] == color[u])\
    \ {\n                        return std::nullopt;\n                    }\n   \
    \             }\n            }\n        }\n        return color;\n    }\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_BIPARTITE_GRAPH_RECOGNITION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/bipartite_graph_recognition.hpp
  requiredBy: []
  timestamp: '2022-03-17 16:17:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
documentation_of: library/graph/bipartite_graph_recognition.hpp
layout: document
redirect_from:
- /library/library/graph/bipartite_graph_recognition.hpp
- /library/library/graph/bipartite_graph_recognition.hpp.html
title: library/graph/bipartite_graph_recognition.hpp
---
