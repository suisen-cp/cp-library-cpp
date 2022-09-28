---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/graph/dulmage_mendelsohn_decomposition.hpp
    title: "Dulmage Mendelsohn Decomposition (DM \u5206\u89E3)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/bipartite_matching/bipartite_matching.test.cpp
    title: test/src/graph/bipartite_matching/bipartite_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
    title: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/dulmage_mendelsohn_decomposition/yuki1744.test.cpp
    title: test/src/graph/dulmage_mendelsohn_decomposition/yuki1744.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/dulmage_mendelsohn_decomposition/yuki1745.test.cpp
    title: test/src/graph/dulmage_mendelsohn_decomposition/yuki1745.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/string/palindromic_tree/abc237_h.test.cpp
    title: test/src/string/palindromic_tree/abc237_h.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/bipartite_matching.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <deque>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\nnamespace suisen {\n    struct BipartiteMatching {\n    \
    \    static constexpr int ABSENT = -1;\n\n        BipartiteMatching() {}\n   \
    \     BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, ABSENT), _to_l(_m,\
    \ ABSENT), _g(n + m) {}\n\n        void add_edge(int fr, int to) {\n         \
    \   _g[fr].push_back(to), _f = -1;\n        }\n\n        // template <bool shuffle\
    \ = true>\n        // int solve_heuristics() {\n        //     if (_f >= 0) return\
    \ _f;\n\n        //     static std::mt19937 rng(std::random_device{}());\n   \
    \     //     if constexpr (shuffle) for (auto& adj : _g) std::shuffle(adj.begin(),\
    \ adj.end(), rng);\n\n        //     std::vector<int8_t> vis(_n, false);\n\n \
    \       //     auto dfs = [&, this](auto dfs, int u) -> bool {\n        //   \
    \      if (std::exchange(vis[u], true)) return false;\n        //         for\
    \ (int v : _g[u]) if (_to_l[v] == ABSENT) return _to_r[u] = v, _to_l[v] = u, true;\n\
    \        //         for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u]\
    \ = v, _to_l[v] = u, true;\n        //         return false;\n        //     };\n\
    \n        //     for (bool upd = true; std::exchange(upd, false);) {\n       \
    \ //         vis.assign(_n, false);\n        //         for (int i = 0; i < _n;\
    \ ++i) if (_to_r[i] == ABSENT) upd |= dfs(dfs, i);\n        //     }\n\n     \
    \   //     return _f = _n - std::count(_to_r.begin(), _to_r.end(), ABSENT);\n\
    \        // }\n    \n        int solve() {\n            if (_f >= 0) return _f;\n\
    \            const auto h = reversed_graph();\n\n            std::vector<int>\
    \ level(_n + _m), iter(_n + _m);\n            std::deque<int> que;\n         \
    \   auto bfs = [&] {\n                for (int i = 0; i < _n; ++i) {\n       \
    \             if (_to_r[i] == ABSENT) level[i] = 0, que.push_back(i);\n      \
    \              else level[i] = -1;\n                }\n                std::fill(level.begin()\
    \ + _n, level.end(), -1);\n                bool ok = false;\n                while\
    \ (not que.empty()) {\n                    const int l = que.front();\n      \
    \              que.pop_front();\n                    for (int r : _g[l]) if (_to_r[l]\
    \ != r and level[_n + r] < 0) {\n                        const int nl = _to_l[r];\n\
    \                        level[_n + r] = level[l] + 1;\n                     \
    \   if (nl == ABSENT) ok = true;\n                        else if (level[nl] <\
    \ 0) level[nl] = level[l] + 2, que.push_back(nl);\n                    }\n   \
    \             }\n                return ok;\n            };\n            auto\
    \ dfs = [&](auto dfs, const int r) -> bool {\n                const int level_v\
    \ = level[_n + r];\n                if (level_v < 0) return false;\n         \
    \       const int dr = h[r].size();\n                for (int &i = iter[_n + r];\
    \ i < dr; ++i) {\n                    const int l = h[r][i];\n               \
    \     if (level_v <= level[l] or _to_l[r] == l or iter[l] > _m) continue;\n  \
    \                  if (int nr = _to_r[l]; nr == ABSENT) {\n                  \
    \      iter[l] = _m + 1, level[l] = _n + _m;\n                        _to_r[l]\
    \ = r, _to_l[r] = l;\n                        return true;\n                 \
    \   } else if (iter[l] <= nr) {\n                        iter[l] = nr + 1;\n \
    \                       if (level[l] > level[_n + nr] and dfs(dfs, nr)) {\n  \
    \                          _to_r[l] = r, _to_l[r] = l;\n                     \
    \       return true;\n                        }\n                        iter[l]\
    \ = _m + 1, level[l] = _n + _m;\n                    }\n                }\n  \
    \              return level[_n + r] = _n + _m, false;\n            };\n      \
    \      for (_f = 0; bfs();) {\n                std::fill(iter.begin(), iter.end(),\
    \ 0);\n                for (int j = 0; j < _m; ++j) if (_to_l[j] == ABSENT) _f\
    \ += dfs(dfs, j);\n            }\n            return _f;\n        }\n\n      \
    \  std::vector<std::pair<int, int>> max_matching() {\n            if (_f < 0)\
    \ solve();\n            std::vector<std::pair<int, int>> res;\n            res.reserve(_f);\n\
    \            for (int i = 0; i < _n; ++i) if (_to_r[i] != ABSENT) res.emplace_back(i,\
    \ _to_r[i]);\n            return res;\n        }\n\n        std::vector<std::pair<int,\
    \ int>> min_edge_cover() {\n            auto res = max_matching();\n         \
    \   std::vector<bool> vl(_n, false), vr(_n, false);\n            for (const auto&\
    \ [u, v] : res) vl[u] = vr[v] = true;\n            for (int u = 0; u < _n; ++u)\
    \ for (int v : _g[u]) if (not (vl[u] and vr[v])) {\n                vl[u] = vr[v]\
    \ = true;\n                res.emplace_back(u, v);\n            }\n          \
    \  return res;\n        }\n\n        std::vector<int> min_vertex_cover() {\n \
    \           if (_f < 0) solve();\n            std::vector<std::vector<int>> g(_n\
    \ + _m);\n            std::vector<bool> cl(_n, true), cr(_m, false);\n       \
    \     for (int u = 0; u < _n; ++u) for (int v : _g[u]) {\n                if (_to_r[u]\
    \ == v) {\n                    g[v + _n].push_back(u);\n                    cl[u]\
    \ = false;\n                } else {\n                    g[u].push_back(v + _n);\n\
    \                }\n            }\n            std::vector<bool> vis(_n + _m,\
    \ false);\n            std::deque<int> dq;\n            for (int i = 0; i < _n;\
    \ ++i) if (cl[i]) {\n                dq.push_back(i);\n                vis[i]\
    \ = true;\n            }\n            while (dq.size()) {\n                int\
    \ u = dq.front();\n                dq.pop_front();\n                for (int v\
    \ : g[u]) {\n                    if (vis[v]) continue;\n                    vis[v]\
    \ = true;\n                    (v < _n ? cl[v] : cr[v - _n]) = true;\n       \
    \             dq.push_back(v);\n                }\n            }\n           \
    \ std::vector<int> res;\n            for (int i = 0; i < _n; ++i) if (not cl[i])\
    \ res.push_back(i);\n            for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n\
    \ + i);\n            return res;\n        }\n\n        std::vector<int> max_independent_set()\
    \ {\n            std::vector<bool> use(_n + _m, true);\n            for (int v\
    \ : min_vertex_cover()) use[v] = false;\n            std::vector<int> res;\n \
    \           for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);\n\
    \            return res;\n        }\n\n        int left_size() const { return\
    \ _n; }\n        int right_size() const { return _m; }\n        std::pair<int,\
    \ int> size() const { return { _n, _m }; }\n\n        int right(int l) const {\
    \ assert(_f >= 0); return _to_r[l]; }\n        int left(int r) const { assert(_f\
    \ >= 0); return _to_l[r]; }\n\n        const auto graph() const { return _g; }\n\
    \n        std::vector<std::vector<int>> reversed_graph() const {\n           \
    \ std::vector<std::vector<int>> h(_m);\n            for (int i = 0; i < _n; ++i)\
    \ for (int j : _g[i]) h[j].push_back(i);\n            return h;\n        }\n\n\
    \    private:\n        int _n, _m;\n        std::vector<int> _to_r, _to_l;\n \
    \       std::vector<std::vector<int>> _g;\n        int _f = 0;\n    };\n\n} //\
    \ namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_BIPARTITE_MATCHING\n#define SUISEN_BIPARTITE_MATCHING\n\n\
    #include <algorithm>\n#include <cassert>\n#include <deque>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\nnamespace suisen {\n    struct BipartiteMatching\
    \ {\n        static constexpr int ABSENT = -1;\n\n        BipartiteMatching()\
    \ {}\n        BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, ABSENT),\
    \ _to_l(_m, ABSENT), _g(n + m) {}\n\n        void add_edge(int fr, int to) {\n\
    \            _g[fr].push_back(to), _f = -1;\n        }\n\n        // template\
    \ <bool shuffle = true>\n        // int solve_heuristics() {\n        //     if\
    \ (_f >= 0) return _f;\n\n        //     static std::mt19937 rng(std::random_device{}());\n\
    \        //     if constexpr (shuffle) for (auto& adj : _g) std::shuffle(adj.begin(),\
    \ adj.end(), rng);\n\n        //     std::vector<int8_t> vis(_n, false);\n\n \
    \       //     auto dfs = [&, this](auto dfs, int u) -> bool {\n        //   \
    \      if (std::exchange(vis[u], true)) return false;\n        //         for\
    \ (int v : _g[u]) if (_to_l[v] == ABSENT) return _to_r[u] = v, _to_l[v] = u, true;\n\
    \        //         for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u]\
    \ = v, _to_l[v] = u, true;\n        //         return false;\n        //     };\n\
    \n        //     for (bool upd = true; std::exchange(upd, false);) {\n       \
    \ //         vis.assign(_n, false);\n        //         for (int i = 0; i < _n;\
    \ ++i) if (_to_r[i] == ABSENT) upd |= dfs(dfs, i);\n        //     }\n\n     \
    \   //     return _f = _n - std::count(_to_r.begin(), _to_r.end(), ABSENT);\n\
    \        // }\n    \n        int solve() {\n            if (_f >= 0) return _f;\n\
    \            const auto h = reversed_graph();\n\n            std::vector<int>\
    \ level(_n + _m), iter(_n + _m);\n            std::deque<int> que;\n         \
    \   auto bfs = [&] {\n                for (int i = 0; i < _n; ++i) {\n       \
    \             if (_to_r[i] == ABSENT) level[i] = 0, que.push_back(i);\n      \
    \              else level[i] = -1;\n                }\n                std::fill(level.begin()\
    \ + _n, level.end(), -1);\n                bool ok = false;\n                while\
    \ (not que.empty()) {\n                    const int l = que.front();\n      \
    \              que.pop_front();\n                    for (int r : _g[l]) if (_to_r[l]\
    \ != r and level[_n + r] < 0) {\n                        const int nl = _to_l[r];\n\
    \                        level[_n + r] = level[l] + 1;\n                     \
    \   if (nl == ABSENT) ok = true;\n                        else if (level[nl] <\
    \ 0) level[nl] = level[l] + 2, que.push_back(nl);\n                    }\n   \
    \             }\n                return ok;\n            };\n            auto\
    \ dfs = [&](auto dfs, const int r) -> bool {\n                const int level_v\
    \ = level[_n + r];\n                if (level_v < 0) return false;\n         \
    \       const int dr = h[r].size();\n                for (int &i = iter[_n + r];\
    \ i < dr; ++i) {\n                    const int l = h[r][i];\n               \
    \     if (level_v <= level[l] or _to_l[r] == l or iter[l] > _m) continue;\n  \
    \                  if (int nr = _to_r[l]; nr == ABSENT) {\n                  \
    \      iter[l] = _m + 1, level[l] = _n + _m;\n                        _to_r[l]\
    \ = r, _to_l[r] = l;\n                        return true;\n                 \
    \   } else if (iter[l] <= nr) {\n                        iter[l] = nr + 1;\n \
    \                       if (level[l] > level[_n + nr] and dfs(dfs, nr)) {\n  \
    \                          _to_r[l] = r, _to_l[r] = l;\n                     \
    \       return true;\n                        }\n                        iter[l]\
    \ = _m + 1, level[l] = _n + _m;\n                    }\n                }\n  \
    \              return level[_n + r] = _n + _m, false;\n            };\n      \
    \      for (_f = 0; bfs();) {\n                std::fill(iter.begin(), iter.end(),\
    \ 0);\n                for (int j = 0; j < _m; ++j) if (_to_l[j] == ABSENT) _f\
    \ += dfs(dfs, j);\n            }\n            return _f;\n        }\n\n      \
    \  std::vector<std::pair<int, int>> max_matching() {\n            if (_f < 0)\
    \ solve();\n            std::vector<std::pair<int, int>> res;\n            res.reserve(_f);\n\
    \            for (int i = 0; i < _n; ++i) if (_to_r[i] != ABSENT) res.emplace_back(i,\
    \ _to_r[i]);\n            return res;\n        }\n\n        std::vector<std::pair<int,\
    \ int>> min_edge_cover() {\n            auto res = max_matching();\n         \
    \   std::vector<bool> vl(_n, false), vr(_n, false);\n            for (const auto&\
    \ [u, v] : res) vl[u] = vr[v] = true;\n            for (int u = 0; u < _n; ++u)\
    \ for (int v : _g[u]) if (not (vl[u] and vr[v])) {\n                vl[u] = vr[v]\
    \ = true;\n                res.emplace_back(u, v);\n            }\n          \
    \  return res;\n        }\n\n        std::vector<int> min_vertex_cover() {\n \
    \           if (_f < 0) solve();\n            std::vector<std::vector<int>> g(_n\
    \ + _m);\n            std::vector<bool> cl(_n, true), cr(_m, false);\n       \
    \     for (int u = 0; u < _n; ++u) for (int v : _g[u]) {\n                if (_to_r[u]\
    \ == v) {\n                    g[v + _n].push_back(u);\n                    cl[u]\
    \ = false;\n                } else {\n                    g[u].push_back(v + _n);\n\
    \                }\n            }\n            std::vector<bool> vis(_n + _m,\
    \ false);\n            std::deque<int> dq;\n            for (int i = 0; i < _n;\
    \ ++i) if (cl[i]) {\n                dq.push_back(i);\n                vis[i]\
    \ = true;\n            }\n            while (dq.size()) {\n                int\
    \ u = dq.front();\n                dq.pop_front();\n                for (int v\
    \ : g[u]) {\n                    if (vis[v]) continue;\n                    vis[v]\
    \ = true;\n                    (v < _n ? cl[v] : cr[v - _n]) = true;\n       \
    \             dq.push_back(v);\n                }\n            }\n           \
    \ std::vector<int> res;\n            for (int i = 0; i < _n; ++i) if (not cl[i])\
    \ res.push_back(i);\n            for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n\
    \ + i);\n            return res;\n        }\n\n        std::vector<int> max_independent_set()\
    \ {\n            std::vector<bool> use(_n + _m, true);\n            for (int v\
    \ : min_vertex_cover()) use[v] = false;\n            std::vector<int> res;\n \
    \           for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);\n\
    \            return res;\n        }\n\n        int left_size() const { return\
    \ _n; }\n        int right_size() const { return _m; }\n        std::pair<int,\
    \ int> size() const { return { _n, _m }; }\n\n        int right(int l) const {\
    \ assert(_f >= 0); return _to_r[l]; }\n        int left(int r) const { assert(_f\
    \ >= 0); return _to_l[r]; }\n\n        const auto graph() const { return _g; }\n\
    \n        std::vector<std::vector<int>> reversed_graph() const {\n           \
    \ std::vector<std::vector<int>> h(_m);\n            for (int i = 0; i < _n; ++i)\
    \ for (int j : _g[i]) h[j].push_back(i);\n            return h;\n        }\n\n\
    \    private:\n        int _n, _m;\n        std::vector<int> _to_r, _to_l;\n \
    \       std::vector<std::vector<int>> _g;\n        int _f = 0;\n    };\n\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_BIPARTITE_MATCHING\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/bipartite_matching.hpp
  requiredBy:
  - library/graph/dulmage_mendelsohn_decomposition.hpp
  timestamp: '2022-06-28 04:44:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/string/palindromic_tree/abc237_h.test.cpp
  - test/src/graph/bipartite_matching/bipartite_matching.test.cpp
  - test/src/graph/dulmage_mendelsohn_decomposition/yuki1745.test.cpp
  - test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
  - test/src/graph/dulmage_mendelsohn_decomposition/yuki1744.test.cpp
documentation_of: library/graph/bipartite_matching.hpp
layout: document
title: "\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0"
---
## 二部マッチング

最小辺被覆、最小頂点被覆、最大独立集合を求めることもできる。
