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
  bundledCode: "#line 1 \"library/tree/level_ancestor.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\n    struct LevelAncestor {\n        LevelAncestor()\
    \ = default;\n        LevelAncestor(const std::vector<std::vector<int>>& g, const\
    \ int root = 0) : _n(g.size()), _visit_time(_n), _depth(_n), _bucket(_n) {\n \
    \           build(g, root);\n        }\n\n        int query(const int u, const\
    \ int k) const {\n            const int d = _depth[u] - k;\n            if (d\
    \ < 0 or d > _depth[u]) return -1;\n            auto comp = [this](int i, int\
    \ j) {\n                return _visit_time[i] < _visit_time[j];\n            };\n\
    \            return *std::prev(std::upper_bound(_bucket[d].begin(), _bucket[d].end(),\
    \ u, comp));\n        }\n        int operator()(const int u, const int k) const\
    \ {\n            return query(u, k);\n        }\n\n        int get_depth(const\
    \ int u) const {\n            return _depth[u];\n        }\n    private:\n   \
    \     int _n;\n        std::vector<int> _visit_time;\n        std::vector<int>\
    \ _depth;\n        std::vector<std::vector<int>> _bucket;\n\n        void build(const\
    \ std::vector<std::vector<int>>& g, const int root) {\n            int time =\
    \ 0;\n            auto dfs = [&](auto dfs, int u, int p) -> void {\n         \
    \       _visit_time[u] = time++;\n                _bucket[_depth[u]].push_back(u);\n\
    \                for (int v : g[u]) {\n                    if (v == p) continue;\n\
    \                    _depth[v] = _depth[u] + 1;\n                    dfs(dfs,\
    \ v, u);\n                }\n            };\n            dfs(dfs, root, -1);\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_LEVEL_ANCESTOR\n#define SUISEN_LEVEL_ANCESTOR\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct LevelAncestor\
    \ {\n        LevelAncestor() = default;\n        LevelAncestor(const std::vector<std::vector<int>>&\
    \ g, const int root = 0) : _n(g.size()), _visit_time(_n), _depth(_n), _bucket(_n)\
    \ {\n            build(g, root);\n        }\n\n        int query(const int u,\
    \ const int k) const {\n            const int d = _depth[u] - k;\n           \
    \ if (d < 0 or d > _depth[u]) return -1;\n            auto comp = [this](int i,\
    \ int j) {\n                return _visit_time[i] < _visit_time[j];\n        \
    \    };\n            return *std::prev(std::upper_bound(_bucket[d].begin(), _bucket[d].end(),\
    \ u, comp));\n        }\n        int operator()(const int u, const int k) const\
    \ {\n            return query(u, k);\n        }\n\n        int get_depth(const\
    \ int u) const {\n            return _depth[u];\n        }\n    private:\n   \
    \     int _n;\n        std::vector<int> _visit_time;\n        std::vector<int>\
    \ _depth;\n        std::vector<std::vector<int>> _bucket;\n\n        void build(const\
    \ std::vector<std::vector<int>>& g, const int root) {\n            int time =\
    \ 0;\n            auto dfs = [&](auto dfs, int u, int p) -> void {\n         \
    \       _visit_time[u] = time++;\n                _bucket[_depth[u]].push_back(u);\n\
    \                for (int v : g[u]) {\n                    if (v == p) continue;\n\
    \                    _depth[v] = _depth[u] + 1;\n                    dfs(dfs,\
    \ v, u);\n                }\n            };\n            dfs(dfs, root, -1);\n\
    \        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_LEVEL_ANCESTOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/level_ancestor.hpp
  requiredBy: []
  timestamp: '2022-04-16 16:20:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/level_ancestor.hpp
layout: document
title: Level Ancestor
---
## Level Ancestor