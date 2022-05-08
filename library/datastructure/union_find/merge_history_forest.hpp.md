---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
    title: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/union_find/merge_history_forest.hpp\"\
    \n\n\n\n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include\
    \ <numeric>\n#include <limits>\n\nnamespace suisen {\n    struct MergeHistoryForest\
    \ : public atcoder::dsu {\n        using base_type = atcoder::dsu;\n\n       \
    \ MergeHistoryForest() : MergeHistoryForest(0) {}\n        explicit MergeHistoryForest(int\
    \ n) : base_type(n), _g(n), _parent(n, -1), _root(n), _time(0), _created_time(n,\
    \ _time) {\n            std::iota(_root.begin(), _root.end(), 0);\n        }\n\
    \n        int node_num() const { return _g.size(); }\n        int leaf_num() const\
    \ { return _root.size(); }\n\n        const auto& get_forest() const { return\
    \ _g; }\n    \n        int forest_root(int i) { return _root[leader(i)]; }\n \
    \       int forest_parent(int vid) const { return _parent[vid]; }\n        const\
    \ auto& forest_children(int vid) { return _g[vid]; }\n        bool is_forest_root(int\
    \ vid) const { return _parent[vid] < 0; }\n        bool is_forest_leaf(int vid)\
    \ const { return vid < leaf_num(); }\n\n        std::vector<int> forest_roots()\
    \ {\n            const int n = leaf_num();\n            std::vector<int> roots;\n\
    \            for (int i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);\n\
    \            return roots;\n        }\n \n        void merge(int u, int v) {\n\
    \            ++_time;\n            const int ru = leader(u), rv = leader(v);\n\
    \            if (ru == rv) return;\n            const int new_root = create_node();\n\
    \            create_edge(new_root, _root[ru]), create_edge(new_root, _root[rv]);\n\
    \            _root[base_type::merge(ru, rv)] = new_root;\n        }\n        void\
    \ merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }\n\
    \n        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges)\
    \ {\n            ++_time;\n            std::vector<int> vs;\n            for (const\
    \ auto &[u, v] : edges) {\n                const int ru = leader(u), rv = leader(v);\n\
    \                if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ {\n                const int new_root = create_node();\n                merge_dfs(s,\
    \ new_root);\n                _root[s] = new_root;\n            }\n        }\n\
    \n        int current_time() const { return _time; }\n        int created_time(int\
    \ vid) const { return _created_time[vid]; }\n\n        std::vector<int> group(int\
    \ i, int time) {\n            int root = i;\n            while (_parent[root]\
    \ >= 0 and _created_time[_parent[root]] <= time) root = _parent[root];\n     \
    \       std::vector<int> res;\n            auto dfs = [&, this](auto dfs, int\
    \ u) -> void {\n                if (is_forest_leaf(u)) {\n                   \
    \ res.push_back(u);\n                } else {\n                    for (int v\
    \ : _g[u]) dfs(dfs, v);\n                }\n            };\n            dfs(dfs,\
    \ root);\n            return res;\n        }\n        std::vector<std::vector<int>>\
    \ groups(int time) {\n            std::vector<std::vector<int>> res;\n       \
    \     const int n = leaf_num();\n            std::vector<bool> seen(n, false);\n\
    \            for (int i = 0; i < n; ++i) if (not seen[i]) for (int v : res.emplace_back(group(i,\
    \ time))) seen[v] = true;\n            return res;\n        }\n\n        template\
    \ <typename GetLCA>\n        bool same(int u, int v, int time, GetLCA&& get_lca)\
    \ {\n            if (not base_type::same(u, v)) return false;\n            int\
    \ a = get_lca(u, v);\n            return _created_time[a] <= time;\n        }\n\
    \n    private:\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _parent;\n        std::vector<int> _root;\n\n        // sum of the number of\
    \ calls of function `merge` and those of `merge_simultaneously`\n        int _time;\n\
    \        std::vector<int> _created_time;\n\n        void merge_dfs(int u, int\
    \ new_root) {\n            for (int v : _g[u]) merge_dfs(v, new_root), _g[v].shrink_to_fit();\n\
    \            create_edge(new_root, _root[u]);\n            _g[u].clear();\n  \
    \      }\n\n        int create_node() {\n            _g.emplace_back();\n    \
    \        _created_time.push_back(_time);\n            _parent.push_back(-1);\n\
    \            return _g.size() - 1;\n        }\n        void create_edge(int new_root,\
    \ int old_root) {\n            _g[new_root].push_back(old_root);\n           \
    \ _parent[old_root] = new_root;\n        }\n        static int floor_log2(int\
    \ n) {\n            int res = 0;\n            while (1 << (res + 1) <= n) ++res;\n\
    \            return res;\n        }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MERGE_HISTORY_FOREST\n#define SUISEN_MERGE_HISTORY_FOREST\n\
    \n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include <numeric>\n\
    #include <limits>\n\nnamespace suisen {\n    struct MergeHistoryForest : public\
    \ atcoder::dsu {\n        using base_type = atcoder::dsu;\n\n        MergeHistoryForest()\
    \ : MergeHistoryForest(0) {}\n        explicit MergeHistoryForest(int n) : base_type(n),\
    \ _g(n), _parent(n, -1), _root(n), _time(0), _created_time(n, _time) {\n     \
    \       std::iota(_root.begin(), _root.end(), 0);\n        }\n\n        int node_num()\
    \ const { return _g.size(); }\n        int leaf_num() const { return _root.size();\
    \ }\n\n        const auto& get_forest() const { return _g; }\n    \n        int\
    \ forest_root(int i) { return _root[leader(i)]; }\n        int forest_parent(int\
    \ vid) const { return _parent[vid]; }\n        const auto& forest_children(int\
    \ vid) { return _g[vid]; }\n        bool is_forest_root(int vid) const { return\
    \ _parent[vid] < 0; }\n        bool is_forest_leaf(int vid) const { return vid\
    \ < leaf_num(); }\n\n        std::vector<int> forest_roots() {\n            const\
    \ int n = leaf_num();\n            std::vector<int> roots;\n            for (int\
    \ i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);\n        \
    \    return roots;\n        }\n \n        void merge(int u, int v) {\n       \
    \     ++_time;\n            const int ru = leader(u), rv = leader(v);\n      \
    \      if (ru == rv) return;\n            const int new_root = create_node();\n\
    \            create_edge(new_root, _root[ru]), create_edge(new_root, _root[rv]);\n\
    \            _root[base_type::merge(ru, rv)] = new_root;\n        }\n        void\
    \ merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }\n\
    \n        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges)\
    \ {\n            ++_time;\n            std::vector<int> vs;\n            for (const\
    \ auto &[u, v] : edges) {\n                const int ru = leader(u), rv = leader(v);\n\
    \                if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ {\n                const int new_root = create_node();\n                merge_dfs(s,\
    \ new_root);\n                _root[s] = new_root;\n            }\n        }\n\
    \n        int current_time() const { return _time; }\n        int created_time(int\
    \ vid) const { return _created_time[vid]; }\n\n        std::vector<int> group(int\
    \ i, int time) {\n            int root = i;\n            while (_parent[root]\
    \ >= 0 and _created_time[_parent[root]] <= time) root = _parent[root];\n     \
    \       std::vector<int> res;\n            auto dfs = [&, this](auto dfs, int\
    \ u) -> void {\n                if (is_forest_leaf(u)) {\n                   \
    \ res.push_back(u);\n                } else {\n                    for (int v\
    \ : _g[u]) dfs(dfs, v);\n                }\n            };\n            dfs(dfs,\
    \ root);\n            return res;\n        }\n        std::vector<std::vector<int>>\
    \ groups(int time) {\n            std::vector<std::vector<int>> res;\n       \
    \     const int n = leaf_num();\n            std::vector<bool> seen(n, false);\n\
    \            for (int i = 0; i < n; ++i) if (not seen[i]) for (int v : res.emplace_back(group(i,\
    \ time))) seen[v] = true;\n            return res;\n        }\n\n        template\
    \ <typename GetLCA>\n        bool same(int u, int v, int time, GetLCA&& get_lca)\
    \ {\n            if (not base_type::same(u, v)) return false;\n            int\
    \ a = get_lca(u, v);\n            return _created_time[a] <= time;\n        }\n\
    \n    private:\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _parent;\n        std::vector<int> _root;\n\n        // sum of the number of\
    \ calls of function `merge` and those of `merge_simultaneously`\n        int _time;\n\
    \        std::vector<int> _created_time;\n\n        void merge_dfs(int u, int\
    \ new_root) {\n            for (int v : _g[u]) merge_dfs(v, new_root), _g[v].shrink_to_fit();\n\
    \            create_edge(new_root, _root[u]);\n            _g[u].clear();\n  \
    \      }\n\n        int create_node() {\n            _g.emplace_back();\n    \
    \        _created_time.push_back(_time);\n            _parent.push_back(-1);\n\
    \            return _g.size() - 1;\n        }\n        void create_edge(int new_root,\
    \ int old_root) {\n            _g[new_root].push_back(old_root);\n           \
    \ _parent[old_root] = new_root;\n        }\n        static int floor_log2(int\
    \ n) {\n            int res = 0;\n            while (1 << (res + 1) <= n) ++res;\n\
    \            return res;\n        }\n    };\n} // namespace suisen\n\n\n#endif\
    \ // SUISEN_MERGE_HISTORY_FOREST\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/union_find/merge_history_forest.hpp
  requiredBy: []
  timestamp: '2022-03-15 15:38:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
documentation_of: library/datastructure/union_find/merge_history_forest.hpp
layout: document
title: Merge History Forest
---
## Merge History Forest

いわゆる「マージ過程を表す木」。
