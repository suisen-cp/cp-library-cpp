---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/level_ancestor/jump_on_tree.test.cpp
    title: test/src/tree/level_ancestor/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
    title: test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/level_ancestor.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\n    struct LevelAncestor {\n        LevelAncestor()\
    \ = default;\n        LevelAncestor(const std::vector<std::vector<int>>& g, const\
    \ int root = 0)\n            : _n(g.size()), _visit_time(_n), _visit_time_inv(_n),\
    \ _depth(_n), _count(_n + 1), _bucket(_n) {\n            build(g, root);\n   \
    \     }\n\n        int query(const int u, const int k) const {\n            if\
    \ (k < 0 or k > _depth[u]) return -1;\n            const int d = _depth[u] - k;\n\
    \            const auto it_l = _bucket.begin() + _count[d], it_r = _bucket.begin()\
    \ + _count[d + 1];\n            const int visit_time_u = _visit_time[u];\n   \
    \         const int visit_time_v = *std::prev(std::upper_bound(it_l, it_r, visit_time_u));\n\
    \            return _visit_time_inv[visit_time_v];\n        }\n\n        int operator()(const\
    \ int u, const int k) const {\n            return query(u, k);\n        }\n\n\
    \        int get_visit_time(const int u)     const { return _visit_time[u]; }\n\
    \        int get_visit_time_inv(const int t) const { return _visit_time_inv[t];\
    \ }\n        int get_kth_visited(const int k)    const { return _visit_time_inv[k];\
    \ }\n        int get_depth(const int u)          const { return _depth[u]; }\n\
    \n    private:\n        int _n;\n        std::vector<int> _visit_time;     //\
    \ vertex -> time\n        std::vector<int> _visit_time_inv; // time   -> vertex\n\
    \        std::vector<int> _depth;          // vertex -> depth\n        std::vector<int>\
    \ _count;          // the leftmost index of the i'th block in the `_bucket`\n\
    \        std::vector<int> _bucket;         // [|dep=0|dep=1|dep=2|...|dep=n-1|].\
    \ Each block contains the visited times in ascending order.\n\n        void build(const\
    \ std::vector<std::vector<int>>& g, const int root) {\n            int time =\
    \ 0;\n            auto dfs = [&](auto dfs, int u, int p) -> void {\n         \
    \       _visit_time[u] = time;\n                _visit_time_inv[time] = u;\n \
    \               ++time;\n                ++_count[_depth[u] + 1];\n          \
    \      for (int v : g[u]) if (v != p) {\n                    _depth[v] = _depth[u]\
    \ + 1;\n                    dfs(dfs, v, u);\n                }\n            };\n\
    \            dfs(dfs, root, -1);\n\n            for (int i = 0; i < _n; ++i) _count[i\
    \ + 1] += _count[i];\n            auto index = _count;\n            for (int v\
    \ : _visit_time_inv) _bucket[index[_depth[v]]++] = _visit_time[v];\n        }\n\
    \    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_LEVEL_ANCESTOR\n#define SUISEN_LEVEL_ANCESTOR\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    struct LevelAncestor\
    \ {\n        LevelAncestor() = default;\n        LevelAncestor(const std::vector<std::vector<int>>&\
    \ g, const int root = 0)\n            : _n(g.size()), _visit_time(_n), _visit_time_inv(_n),\
    \ _depth(_n), _count(_n + 1), _bucket(_n) {\n            build(g, root);\n   \
    \     }\n\n        int query(const int u, const int k) const {\n            if\
    \ (k < 0 or k > _depth[u]) return -1;\n            const int d = _depth[u] - k;\n\
    \            const auto it_l = _bucket.begin() + _count[d], it_r = _bucket.begin()\
    \ + _count[d + 1];\n            const int visit_time_u = _visit_time[u];\n   \
    \         const int visit_time_v = *std::prev(std::upper_bound(it_l, it_r, visit_time_u));\n\
    \            return _visit_time_inv[visit_time_v];\n        }\n\n        int operator()(const\
    \ int u, const int k) const {\n            return query(u, k);\n        }\n\n\
    \        int get_visit_time(const int u)     const { return _visit_time[u]; }\n\
    \        int get_visit_time_inv(const int t) const { return _visit_time_inv[t];\
    \ }\n        int get_kth_visited(const int k)    const { return _visit_time_inv[k];\
    \ }\n        int get_depth(const int u)          const { return _depth[u]; }\n\
    \n    private:\n        int _n;\n        std::vector<int> _visit_time;     //\
    \ vertex -> time\n        std::vector<int> _visit_time_inv; // time   -> vertex\n\
    \        std::vector<int> _depth;          // vertex -> depth\n        std::vector<int>\
    \ _count;          // the leftmost index of the i'th block in the `_bucket`\n\
    \        std::vector<int> _bucket;         // [|dep=0|dep=1|dep=2|...|dep=n-1|].\
    \ Each block contains the visited times in ascending order.\n\n        void build(const\
    \ std::vector<std::vector<int>>& g, const int root) {\n            int time =\
    \ 0;\n            auto dfs = [&](auto dfs, int u, int p) -> void {\n         \
    \       _visit_time[u] = time;\n                _visit_time_inv[time] = u;\n \
    \               ++time;\n                ++_count[_depth[u] + 1];\n          \
    \      for (int v : g[u]) if (v != p) {\n                    _depth[v] = _depth[u]\
    \ + 1;\n                    dfs(dfs, v, u);\n                }\n            };\n\
    \            dfs(dfs, root, -1);\n\n            for (int i = 0; i < _n; ++i) _count[i\
    \ + 1] += _count[i];\n            auto index = _count;\n            for (int v\
    \ : _visit_time_inv) _bucket[index[_depth[v]]++] = _visit_time[v];\n        }\n\
    \    };\n} // namespace suisen\n\n\n#endif // SUISEN_LEVEL_ANCESTOR\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/level_ancestor.hpp
  requiredBy: []
  timestamp: '2022-05-08 15:48:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
  - test/src/tree/level_ancestor/jump_on_tree.test.cpp
documentation_of: library/tree/level_ancestor.hpp
layout: document
title: Level Ancestor
---
## Level Ancestor

根付き木において頂点 $u$ から親方向の辺をちょうど $k$ 回辿って到達する頂点を $v$ (存在しない場合は $-1$) として、$\mathrm{LA}(u,k)=v$ と定義する。

オンラインで与えられる $u,k$ に対して $\mathrm{LA}(u,k)$ を求めるクエリに前計算 $\Theta(N)$、クエリ $\Theta(\log N)$ で答えるアルゴリズムの実装である。

同じ計算量オーダーを達成する方法として Heavy Light Decomposition (HLD) を用いたアルゴリズムが存在する。速度はやや本実装の方が速いか？(要検証)

提出比較

- HLD:
  https://judge.yosupo.jp/submission/88623
- 本実装:
  https://judge.yosupo.jp/submission/88629

## 参考文献

- [そらで書ける <Θ(N), Θ(log N)> Level Ancestor](https://suisen-kyopro.hatenablog.com/entry/2022/04/04/043452)
