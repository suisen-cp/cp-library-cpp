---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/bipartite_graph_recognition.hpp
    title: Bipartite Graph Recognition
  - icon: ':heavy_check_mark:'
    path: library/graph/bipartite_matching.hpp
    title: "\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0"
  - icon: ':heavy_check_mark:'
    path: library/graph/dulmage_mendelsohn_decomposition.hpp
    title: "Dulmage Mendelsohn Decomposition (DM \u5206\u89E3)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc223/tasks/abc223_g
    links:
    - https://atcoder.jp/contests/abc223/tasks/abc223_g
  bundledCode: "#line 1 \"test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc223/tasks/abc223_g\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/bipartite_graph_recognition.hpp\"\n\n\n\
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
    \ namespace suisen\n\n\n\n#line 1 \"library/graph/dulmage_mendelsohn_decomposition.hpp\"\
    \n\n\n\n#include <atcoder/scc>\n#line 1 \"library/graph/bipartite_matching.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#line 7 \"library/graph/bipartite_matching.hpp\"\
    \n#include <random>\n#include <utility>\n#line 10 \"library/graph/bipartite_matching.hpp\"\
    \n\nnamespace suisen {\n    struct BipartiteMatching {\n        static constexpr\
    \ int ABSENT = -1;\n\n        BipartiteMatching() {}\n        BipartiteMatching(int\
    \ n, int m) : _n(n), _m(m), _to_r(_n, ABSENT), _to_l(_m, ABSENT), _g(n + m) {}\n\
    \n        void add_edge(int fr, int to) {\n            _g[fr].push_back(to), _f\
    \ = -1;\n        }\n\n        // template <bool shuffle = true>\n        // int\
    \ solve_heuristics() {\n        //     if (_f >= 0) return _f;\n\n        // \
    \    static std::mt19937 rng(std::random_device{}());\n        //     if constexpr\
    \ (shuffle) for (auto& adj : _g) std::shuffle(adj.begin(), adj.end(), rng);\n\n\
    \        //     std::vector<int8_t> vis(_n, false);\n\n        //     auto dfs\
    \ = [&, this](auto dfs, int u) -> bool {\n        //         if (std::exchange(vis[u],\
    \ true)) return false;\n        //         for (int v : _g[u]) if (_to_l[v] ==\
    \ ABSENT) return _to_r[u] = v, _to_l[v] = u, true;\n        //         for (int\
    \ v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u] = v, _to_l[v] = u, true;\n\
    \        //         return false;\n        //     };\n\n        //     for (bool\
    \ upd = true; std::exchange(upd, false);) {\n        //         vis.assign(_n,\
    \ false);\n        //         for (int i = 0; i < _n; ++i) if (_to_r[i] == ABSENT)\
    \ upd |= dfs(dfs, i);\n        //     }\n\n        //     return _f = _n - std::count(_to_r.begin(),\
    \ _to_r.end(), ABSENT);\n        // }\n    \n        int solve() {\n         \
    \   if (_f >= 0) return _f;\n            const auto h = reversed_graph();\n\n\
    \            std::vector<int> level(_n + _m), iter(_n + _m);\n            std::deque<int>\
    \ que;\n            auto bfs = [&] {\n                for (int i = 0; i < _n;\
    \ ++i) {\n                    if (_to_r[i] == ABSENT) level[i] = 0, que.push_back(i);\n\
    \                    else level[i] = -1;\n                }\n                std::fill(level.begin()\
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
    \ namespace suisen\n\n\n\n#line 6 \"library/graph/dulmage_mendelsohn_decomposition.hpp\"\
    \n\nnamespace suisen {\n    std::vector<std::pair<std::vector<int>, std::vector<int>>>\
    \ dulmage_mendelsohn_decomposition(BipartiteMatching& bm) {\n        bm.solve();\n\
    \        const int n = bm.left_size(), m = bm.right_size();\n\n        std::vector<int8_t>\
    \ wk_l(n, false), wk_r(m, false);\n        const auto& g = bm.graph();\n     \
    \   auto dfs_l = [&](auto dfs_l, int i) -> void {\n            if (i == BipartiteMatching::ABSENT\
    \ or std::exchange(wk_l[i], true)) return;\n            for (int j : g[i]) wk_r[j]\
    \ = true, dfs_l(dfs_l, bm.left(j));\n        };\n        for (int i = 0; i < n;\
    \ ++i) if (bm.right(i) == BipartiteMatching::ABSENT) dfs_l(dfs_l, i);\n\n    \
    \    std::vector<int8_t> w0_l(n, false), w0_r(m, false);\n        const auto h\
    \ = bm.reversed_graph();\n        auto dfs_r = [&](auto dfs_r, int j) -> void\
    \ {\n            if (j == BipartiteMatching::ABSENT or std::exchange(w0_r[j],\
    \ true)) return;\n            for (int i : h[j]) w0_l[i] = true, dfs_r(dfs_r,\
    \ bm.right(i));\n        };\n        for (int j = 0; j < m; ++j) if (bm.left(j)\
    \ == BipartiteMatching::ABSENT) dfs_r(dfs_r, j);\n\n        std::vector<std::pair<std::vector<int>,\
    \ std::vector<int>>> dm;\n        auto add_pair = [&](int i, int j) {\n      \
    \      auto& [l, r] = dm.back();\n            l.push_back(i), r.push_back(j);\n\
    \        };\n        // W_0\n        dm.emplace_back();\n        for (int i =\
    \ 0; i < n; ++i) if (w0_l[i]) {\n            add_pair(i, bm.right(i));\n     \
    \   }\n        for (int j = 0; j < m; ++j) if (w0_r[j] and bm.left(j) == BipartiteMatching::ABSENT)\
    \ {\n            dm.back().second.push_back(j);\n        }\n        // W_1, ...,\
    \ W_{k-1}\n        atcoder::scc_graph scc_g(n + m);\n        for (int i = 0; i\
    \ < n; ++i) {\n            for (int j : g[i]) scc_g.add_edge(i, n + j);\n    \
    \        int j = bm.right(i); \n            if (j != BipartiteMatching::ABSENT)\
    \ scc_g.add_edge(n + j, i);\n        }\n        for (const auto& group : scc_g.scc())\
    \ {\n            if (int v0 = group.front(); (v0 < n and (w0_l[v0] or wk_l[v0]))\
    \ or (v0 >= n and (w0_r[v0 - n] or wk_r[v0 - n]))) continue;\n            dm.emplace_back();\n\
    \            for (int i : group) if (i < n) add_pair(i, bm.right(i));\n      \
    \  }\n        // W_k\n        dm.emplace_back();\n        for (int j = 0; j <\
    \ m; ++j) if (wk_r[j]) {\n            add_pair(bm.left(j), j);\n        }\n  \
    \      for (int i = 0; i < n; ++i) if (wk_l[i] and bm.right(i) == BipartiteMatching::ABSENT)\
    \ {\n            dm.back().first.push_back(i);\n        }\n        return dm;\n\
    \    }\n} // namespace suisen\n\n\n\n#line 7 \"test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp\"\
    \n\nusing suisen::bipartite_coloring;\nusing suisen::BipartiteMatching;\nusing\
    \ suisen::dulmage_mendelsohn_decomposition;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n\
    \    }\n\n    std::vector<int> col = *bipartite_coloring(g);\n    std::vector<int>\
    \ id(n);\n    int l = 0, r = 0;\n    for (int i = 0; i < n; ++i) {\n        id[i]\
    \ = (col[i] == 0 ? l : r)++;\n    }\n\n    BipartiteMatching bm(l, r);\n    for\
    \ (int i = 0; i < n; ++i) {\n        if (col[i] == 1) continue;\n        for (int\
    \ j : g[i]) bm.add_edge(id[i], id[j]);\n    }\n    auto dm = dulmage_mendelsohn_decomposition(bm);\n\
    \n    std::cout << dm.front().second.size() + dm.back().first.size() << std::endl;\n\
    \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc223/tasks/abc223_g\"\n\n\
    #include <iostream>\n\n#include \"library/graph/bipartite_graph_recognition.hpp\"\
    \n#include \"library/graph/dulmage_mendelsohn_decomposition.hpp\"\n\nusing suisen::bipartite_coloring;\n\
    using suisen::BipartiteMatching;\nusing suisen::dulmage_mendelsohn_decomposition;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    std::vector<std::vector<int>> g(n);\n\
    \    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >>\
    \ u >> v;\n        --u, --v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n\
    \    }\n\n    std::vector<int> col = *bipartite_coloring(g);\n    std::vector<int>\
    \ id(n);\n    int l = 0, r = 0;\n    for (int i = 0; i < n; ++i) {\n        id[i]\
    \ = (col[i] == 0 ? l : r)++;\n    }\n\n    BipartiteMatching bm(l, r);\n    for\
    \ (int i = 0; i < n; ++i) {\n        if (col[i] == 1) continue;\n        for (int\
    \ j : g[i]) bm.add_edge(id[i], id[j]);\n    }\n    auto dm = dulmage_mendelsohn_decomposition(bm);\n\
    \n    std::cout << dm.front().second.size() + dm.back().first.size() << std::endl;\n\
    \n    return 0;\n}"
  dependsOn:
  - library/graph/bipartite_graph_recognition.hpp
  - library/graph/dulmage_mendelsohn_decomposition.hpp
  - library/graph/bipartite_matching.hpp
  isVerificationFile: true
  path: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
  requiredBy: []
  timestamp: '2022-03-17 16:17:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
- /verify/test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp.html
title: test/src/graph/dulmage_mendelsohn_decomposition/abc223_g.test.cpp
---
