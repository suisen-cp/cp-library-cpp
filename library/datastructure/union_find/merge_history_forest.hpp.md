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
  bundledCode: "#line 1 \"library/datastructure/union_find/merge_history_forest.hpp\"\
    \n\n\n\n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include\
    \ <numeric>\n\nnamespace suisen {\n    struct MergeHistoryForest : public atcoder::dsu\
    \ {\n        using base_type = atcoder::dsu;\n\n        MergeHistoryForest() :\
    \ MergeHistoryForest(0) {}\n        explicit MergeHistoryForest(int n) : base_type(n),\
    \ _g(n), _root(n) {\n            std::iota(_root.begin(), _root.end(), 0);\n \
    \       }\n\n        int node_num() const { return _g.size(); }\n\n        const\
    \ auto& get_forest() const { return _g; }\n\n        int tree_root(int i) { return\
    \ _root[leader(i)]; }\n\n        std::vector<int> tree_roots() {\n           \
    \ const int n = _root.size();\n            std::vector<int> roots;\n         \
    \   for (int i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);\n\
    \            return roots;\n        }\n \n        void merge(int u, int v) {\n\
    \            const int ru = leader(u), rv = leader(v);\n            if (ru ==\
    \ rv) return;\n            _g.push_back({ _root[ru], _root[rv] });\n         \
    \   _root[base_type::merge(ru, rv)] = _g.size() - 1;\n        }\n        void\
    \ merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }\n\
    \n        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges)\
    \ {\n            std::vector<int> vs;\n            for (const auto &[u, v] : edges)\
    \ {\n                const int ru = leader(u), rv = leader(v);\n             \
    \   if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ dfs(s, _g.emplace_back()), _root[s] = _g.size() - 1;\n        }\n\n    private:\n\
    \        std::vector<std::vector<int>> _g;\n        std::vector<int> _root;\n\n\
    \        void dfs(int u, std::vector<int> &con) {\n            for (int v : _g[u])\
    \ dfs(v, con), _g[v].shrink_to_fit();\n            con.push_back(_root[u]), _g[u].clear();\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MERGE_HISTORY_FOREST\n#define SUISEN_MERGE_HISTORY_FOREST\n\
    \n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include <numeric>\n\
    \nnamespace suisen {\n    struct MergeHistoryForest : public atcoder::dsu {\n\
    \        using base_type = atcoder::dsu;\n\n        MergeHistoryForest() : MergeHistoryForest(0)\
    \ {}\n        explicit MergeHistoryForest(int n) : base_type(n), _g(n), _root(n)\
    \ {\n            std::iota(_root.begin(), _root.end(), 0);\n        }\n\n    \
    \    int node_num() const { return _g.size(); }\n\n        const auto& get_forest()\
    \ const { return _g; }\n\n        int tree_root(int i) { return _root[leader(i)];\
    \ }\n\n        std::vector<int> tree_roots() {\n            const int n = _root.size();\n\
    \            std::vector<int> roots;\n            for (int i = 0; i < n; ++i)\
    \ if (leader(i) == i) roots.push_back(_root[i]);\n            return roots;\n\
    \        }\n \n        void merge(int u, int v) {\n            const int ru =\
    \ leader(u), rv = leader(v);\n            if (ru == rv) return;\n            _g.push_back({\
    \ _root[ru], _root[rv] });\n            _root[base_type::merge(ru, rv)] = _g.size()\
    \ - 1;\n        }\n        void merge(const std::pair<int, int> &edge) { merge(edge.first,\
    \ edge.second); }\n\n        void merge_simultaneously(const std::vector<std::pair<int,\
    \ int>> &edges) {\n            std::vector<int> vs;\n            for (const auto\
    \ &[u, v] : edges) {\n                const int ru = leader(u), rv = leader(v);\n\
    \                if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ dfs(s, _g.emplace_back()), _root[s] = _g.size() - 1;\n        }\n\n    private:\n\
    \        std::vector<std::vector<int>> _g;\n        std::vector<int> _root;\n\n\
    \        void dfs(int u, std::vector<int> &con) {\n            for (int v : _g[u])\
    \ dfs(v, con), _g[v].shrink_to_fit();\n            con.push_back(_root[u]), _g[u].clear();\n\
    \        }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_MERGE_HISTORY_FOREST\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/union_find/merge_history_forest.hpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/union_find/merge_history_forest.hpp
layout: document
title: Merge History Forest
---
## Merge History Forest