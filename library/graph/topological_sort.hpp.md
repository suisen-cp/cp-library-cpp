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
  bundledCode: "#line 1 \"library/graph/topological_sort.hpp\"\n\n\n\n#include <queue>\n\
    #include <vector>\n\nnamespace suisen {\nclass topological_sort {\n    public:\n\
    \        topological_sort(std::vector<std::vector<int>> &g): _n(g.size()) {\n\
    \            build(g);\n        }\n        bool is_dag() const { return _ord.size()\
    \ == _n; }\n        const std::vector<int>& sorted() const { return _ord; }\n\
    \        int operator[](int i) const { return _ord[i]; }\n    private:\n     \
    \   const int _n;\n        std::vector<int> _ord;\n        void build(std::vector<std::vector<int>>\
    \ &g) {\n            std::vector<int> in(_n);\n            for (auto &adj : g)\
    \ for (int j : adj) ++in[j];\n            std::deque<int> dq;\n            for\
    \ (int i = 0; i < _n; ++i) {\n                if (in[i] == 0) dq.push_back(i);\n\
    \            }\n            _ord.reserve(_n);\n            while (dq.size()) {\n\
    \                int u = dq.front(); dq.pop_front();\n                _ord.push_back(u);\n\
    \                for (int v : g[u]) {\n                    if (--in[v] == 0) dq.push_back(v);\n\
    \                }\n            }\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_TOPOLOGICAL_SORT\n#define SUISEN_TOPOLOGICAL_SORT\n\n#include\
    \ <queue>\n#include <vector>\n\nnamespace suisen {\nclass topological_sort {\n\
    \    public:\n        topological_sort(std::vector<std::vector<int>> &g): _n(g.size())\
    \ {\n            build(g);\n        }\n        bool is_dag() const { return _ord.size()\
    \ == _n; }\n        const std::vector<int>& sorted() const { return _ord; }\n\
    \        int operator[](int i) const { return _ord[i]; }\n    private:\n     \
    \   const int _n;\n        std::vector<int> _ord;\n        void build(std::vector<std::vector<int>>\
    \ &g) {\n            std::vector<int> in(_n);\n            for (auto &adj : g)\
    \ for (int j : adj) ++in[j];\n            std::deque<int> dq;\n            for\
    \ (int i = 0; i < _n; ++i) {\n                if (in[i] == 0) dq.push_back(i);\n\
    \            }\n            _ord.reserve(_n);\n            while (dq.size()) {\n\
    \                int u = dq.front(); dq.pop_front();\n                _ord.push_back(u);\n\
    \                for (int v : g[u]) {\n                    if (--in[v] == 0) dq.push_back(v);\n\
    \                }\n            }\n        }\n};\n} // namespace suisen\n\n#endif\
    \ // SUISEN_TOPOLOGICAL_SORT"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/topological_sort.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/topological_sort.hpp
layout: document
redirect_from:
- /library/library/graph/topological_sort.hpp
- /library/library/graph/topological_sort.hpp.html
title: library/graph/topological_sort.hpp
---
