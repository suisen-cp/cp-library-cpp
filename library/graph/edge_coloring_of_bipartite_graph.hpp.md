---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/graph/bipartite_matching.hpp
    title: "\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/edge_coloring_of_bipartite_graph/bipartite_edge_coloring.test.cpp
    title: test/src/graph/edge_coloring_of_bipartite_graph/bipartite_edge_coloring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/edge_coloring_of_bipartite_graph.hpp\"\n\n\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <queue>\n\
    #include <utility>\n\n#include <atcoder/dsu>\n\n#line 1 \"library/graph/bipartite_matching.hpp\"\
    \n\n\n\n#line 6 \"library/graph/bipartite_matching.hpp\"\n#include <deque>\n#include\
    \ <random>\n#line 9 \"library/graph/bipartite_matching.hpp\"\n#include <vector>\n\
    \nnamespace suisen {\n    struct BipartiteMatching {\n        static constexpr\
    \ int ABSENT = -1;\n\n        BipartiteMatching() = default;\n        BipartiteMatching(int\
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
    \ namespace suisen\n\n\n\n#line 13 \"library/graph/edge_coloring_of_bipartite_graph.hpp\"\
    \n\nnamespace suisen {\n    struct EdgeColoringOfBipartiteGraph {\n        EdgeColoringOfBipartiteGraph(int\
    \ l = 0, int r = 0) : l(l), r(r) {}\n        void add_edge(int u, int v) {\n \
    \           assert(0 <= u and u < l);\n            assert(0 <= v and v < r);\n\
    \            edges.emplace_back(u, v);\n        }\n\n        std::pair<int, std::vector<int>>\
    \ solve() {\n            if (edges.empty()) return {};\n            std::vector<int>\
    \ degl(l), degr(r);\n            for (const auto& [u, v] : edges) {\n        \
    \        ++degl[u], ++degr[v];\n            }\n            const int k = std::max(\n\
    \                *std::max_element(degl.begin(), degl.end()),\n              \
    \  *std::max_element(degr.begin(), degr.end())\n            );\n            auto\
    \ [numl, idl] = contract(degl, k);\n            auto [numr, idr] = contract(degr,\
    \ k);\n            const int n = std::max(numl, numr);\n            degl.assign(n,\
    \ 0);\n            degr.assign(n, 0);\n            std::vector<std::pair<int,\
    \ int>> new_edges;\n\n            new_edges.reserve(n * k);\n            for (auto\
    \ [u, v] : edges) {\n                u = idl[u], v = idr[v];\n               \
    \ new_edges.emplace_back(u, v);\n                ++degl[u], ++degr[v];\n     \
    \       }\n            for (int i = 0, j = 0; i < n; ++i) {\n                while\
    \ (degl[i] < k) {\n                    while (degr[j] == k) ++j;\n           \
    \         new_edges.emplace_back(i, j);\n                    ++degl[i], ++degr[j];\n\
    \                }\n            }\n            std::vector<int> color = solve_regular(n,\
    \ k, new_edges);\n            color.resize(edges.size());\n            return\
    \ { k, color };\n        }\n\n    private:\n        int l, r;\n        std::vector<std::pair<int,\
    \ int>> edges;\n\n        template <typename T>\n        using priority_queue_greater\
    \ = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n\n        static\
    \ std::vector<int> solve_regular(const int n, const int k, const std::vector<std::pair<int,\
    \ int>>& edges, const int color_offset = 0) {\n            assert(n * k == int(edges.size()));\n\
    \            if (k == 0) {\n                return {};\n            } else if\
    \ (k == 1) {\n                return std::vector<int>(edges.size(), color_offset);\n\
    \            } else if ((k & 1) == 0) {\n                const int m = edges.size();\n\
    \                const int hm = m / 2;\n                std::vector<std::vector<std::pair<int,\
    \ int>>> g(n + n);\n                for (int i = 0; i < m; ++i) {\n          \
    \          const auto [u, v] = edges[i];\n                    g[u].emplace_back(n\
    \ + v, i);\n                    g[n + v].emplace_back(u, i);\n               \
    \ }\n                std::vector<int> circuit;\n                std::vector<int8_t>\
    \ used(m, false), vis(n + n, false);\n                std::vector<std::size_t>\
    \ iter(n + n);\n                for (int i = 0; i < n + n; ++i) if (not vis[i])\
    \ {\n                    auto dfs = [&](auto dfs, int u, int id) -> void {\n \
    \                       vis[u] = true;\n                        for (std::size_t\
    \ &i = iter[u]; i < g[u].size(); ++i) {\n                            auto [v,\
    \ nid] = g[u][i];\n                            if (std::exchange(used[nid], true))\
    \ continue;\n                            dfs(dfs, v, nid);\n                 \
    \       }\n                        if (id >= 0) circuit.push_back(id);\n     \
    \               };\n                    dfs(dfs, i, -1);\n                }\n\
    \                std::array<std::vector<int>, 2> id;\n                id[0].reserve(hm),\
    \ id[1].reserve(hm);\n                std::array<std::vector<std::pair<int, int>>,\
    \ 2> nxt_edges;\n                assert(int(circuit.size()) == m);\n         \
    \       for (int i = 0; i < m; ++i) {\n                    nxt_edges[i & 1].push_back(edges[circuit[i]]);\n\
    \                    id[i & 1].push_back(circuit[i]);\n                }\n   \
    \             std::array<std::vector<int>, 2> rec_res;\n                rec_res[0]\
    \ = solve_regular(n, k / 2, nxt_edges[0], color_offset);\n                rec_res[1]\
    \ = solve_regular(n, k / 2, nxt_edges[1], color_offset + k / 2);\n           \
    \     std::vector<int> res(m);\n                for (int p = 0; p < 2; ++p) {\n\
    \                    for (int i = 0; i < hm; ++i) {\n                        res[id[p][i]]\
    \ = rec_res[p][i];\n                    }\n                }\n               \
    \ return res;\n            } else {\n                BipartiteMatching bimatch(n,\
    \ n);\n                for (const auto& [u, v] : edges) bimatch.add_edge(u, v);\n\
    \                const int matching_size = bimatch.solve();\n                assert(matching_size\
    \ == n);\n                std::vector<std::pair<int, int>> nxt_edges;\n      \
    \          const int m = edges.size();\n                std::vector<int> res(m);\n\
    \                std::vector<int> id(m - n);\n                std::vector<int8_t>\
    \ used(n, false);\n                for (int i = 0; i < m; ++i) {\n           \
    \         auto [u, v] = edges[i];\n                    if (bimatch.right(u) ==\
    \ v and not std::exchange(used[u], true)) {\n                        res[i] =\
    \ color_offset;\n                    } else {\n                        id[nxt_edges.size()]\
    \ = i;\n                        nxt_edges.emplace_back(u, v);\n              \
    \      }\n                }\n                std::vector<int> rec_res = solve_regular(n,\
    \ k - 1, nxt_edges, color_offset + 1);\n                assert(rec_res.size()\
    \ == nxt_edges.size());\n                for (int i = 0; i < m - n; ++i) res[id[i]]\
    \ = rec_res[i];\n                return res;\n            }\n        }\n\n   \
    \     static std::pair<int, std::vector<int>> contract(const std::vector<int>&\
    \ deg, const int k) {\n            const int n = deg.size();\n            atcoder::dsu\
    \ uf(n);\n            priority_queue_greater<std::pair<int, int>> pq{};\n    \
    \        for (int i = 0; i < n; ++i) pq.emplace(deg[i], i);\n            while\
    \ (pq.size() >= 2) {\n                auto [di, i] = pq.top();\n             \
    \   pq.pop();\n                auto [dj, j] = pq.top();\n                pq.pop();\n\
    \                if (di + dj <= k) {\n                    uf.merge(i, j);\n  \
    \                  pq.emplace(di + dj, uf.leader(i));\n                } else\
    \ break;\n            }\n            auto groups = uf.groups();\n            const\
    \ int m = groups.size();\n            std::vector<int> cmp_id(n);\n          \
    \  for (int i = 0; i < m; ++i) for (int v : groups[i]) {\n                cmp_id[v]\
    \ = i;\n            }\n            return { m, cmp_id };\n        }\n    };\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH\n#define SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <queue>\n\
    #include <utility>\n\n#include <atcoder/dsu>\n\n#include \"library/graph/bipartite_matching.hpp\"\
    \n\nnamespace suisen {\n    struct EdgeColoringOfBipartiteGraph {\n        EdgeColoringOfBipartiteGraph(int\
    \ l = 0, int r = 0) : l(l), r(r) {}\n        void add_edge(int u, int v) {\n \
    \           assert(0 <= u and u < l);\n            assert(0 <= v and v < r);\n\
    \            edges.emplace_back(u, v);\n        }\n\n        std::pair<int, std::vector<int>>\
    \ solve() {\n            if (edges.empty()) return {};\n            std::vector<int>\
    \ degl(l), degr(r);\n            for (const auto& [u, v] : edges) {\n        \
    \        ++degl[u], ++degr[v];\n            }\n            const int k = std::max(\n\
    \                *std::max_element(degl.begin(), degl.end()),\n              \
    \  *std::max_element(degr.begin(), degr.end())\n            );\n            auto\
    \ [numl, idl] = contract(degl, k);\n            auto [numr, idr] = contract(degr,\
    \ k);\n            const int n = std::max(numl, numr);\n            degl.assign(n,\
    \ 0);\n            degr.assign(n, 0);\n            std::vector<std::pair<int,\
    \ int>> new_edges;\n\n            new_edges.reserve(n * k);\n            for (auto\
    \ [u, v] : edges) {\n                u = idl[u], v = idr[v];\n               \
    \ new_edges.emplace_back(u, v);\n                ++degl[u], ++degr[v];\n     \
    \       }\n            for (int i = 0, j = 0; i < n; ++i) {\n                while\
    \ (degl[i] < k) {\n                    while (degr[j] == k) ++j;\n           \
    \         new_edges.emplace_back(i, j);\n                    ++degl[i], ++degr[j];\n\
    \                }\n            }\n            std::vector<int> color = solve_regular(n,\
    \ k, new_edges);\n            color.resize(edges.size());\n            return\
    \ { k, color };\n        }\n\n    private:\n        int l, r;\n        std::vector<std::pair<int,\
    \ int>> edges;\n\n        template <typename T>\n        using priority_queue_greater\
    \ = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n\n        static\
    \ std::vector<int> solve_regular(const int n, const int k, const std::vector<std::pair<int,\
    \ int>>& edges, const int color_offset = 0) {\n            assert(n * k == int(edges.size()));\n\
    \            if (k == 0) {\n                return {};\n            } else if\
    \ (k == 1) {\n                return std::vector<int>(edges.size(), color_offset);\n\
    \            } else if ((k & 1) == 0) {\n                const int m = edges.size();\n\
    \                const int hm = m / 2;\n                std::vector<std::vector<std::pair<int,\
    \ int>>> g(n + n);\n                for (int i = 0; i < m; ++i) {\n          \
    \          const auto [u, v] = edges[i];\n                    g[u].emplace_back(n\
    \ + v, i);\n                    g[n + v].emplace_back(u, i);\n               \
    \ }\n                std::vector<int> circuit;\n                std::vector<int8_t>\
    \ used(m, false), vis(n + n, false);\n                std::vector<std::size_t>\
    \ iter(n + n);\n                for (int i = 0; i < n + n; ++i) if (not vis[i])\
    \ {\n                    auto dfs = [&](auto dfs, int u, int id) -> void {\n \
    \                       vis[u] = true;\n                        for (std::size_t\
    \ &i = iter[u]; i < g[u].size(); ++i) {\n                            auto [v,\
    \ nid] = g[u][i];\n                            if (std::exchange(used[nid], true))\
    \ continue;\n                            dfs(dfs, v, nid);\n                 \
    \       }\n                        if (id >= 0) circuit.push_back(id);\n     \
    \               };\n                    dfs(dfs, i, -1);\n                }\n\
    \                std::array<std::vector<int>, 2> id;\n                id[0].reserve(hm),\
    \ id[1].reserve(hm);\n                std::array<std::vector<std::pair<int, int>>,\
    \ 2> nxt_edges;\n                assert(int(circuit.size()) == m);\n         \
    \       for (int i = 0; i < m; ++i) {\n                    nxt_edges[i & 1].push_back(edges[circuit[i]]);\n\
    \                    id[i & 1].push_back(circuit[i]);\n                }\n   \
    \             std::array<std::vector<int>, 2> rec_res;\n                rec_res[0]\
    \ = solve_regular(n, k / 2, nxt_edges[0], color_offset);\n                rec_res[1]\
    \ = solve_regular(n, k / 2, nxt_edges[1], color_offset + k / 2);\n           \
    \     std::vector<int> res(m);\n                for (int p = 0; p < 2; ++p) {\n\
    \                    for (int i = 0; i < hm; ++i) {\n                        res[id[p][i]]\
    \ = rec_res[p][i];\n                    }\n                }\n               \
    \ return res;\n            } else {\n                BipartiteMatching bimatch(n,\
    \ n);\n                for (const auto& [u, v] : edges) bimatch.add_edge(u, v);\n\
    \                const int matching_size = bimatch.solve();\n                assert(matching_size\
    \ == n);\n                std::vector<std::pair<int, int>> nxt_edges;\n      \
    \          const int m = edges.size();\n                std::vector<int> res(m);\n\
    \                std::vector<int> id(m - n);\n                std::vector<int8_t>\
    \ used(n, false);\n                for (int i = 0; i < m; ++i) {\n           \
    \         auto [u, v] = edges[i];\n                    if (bimatch.right(u) ==\
    \ v and not std::exchange(used[u], true)) {\n                        res[i] =\
    \ color_offset;\n                    } else {\n                        id[nxt_edges.size()]\
    \ = i;\n                        nxt_edges.emplace_back(u, v);\n              \
    \      }\n                }\n                std::vector<int> rec_res = solve_regular(n,\
    \ k - 1, nxt_edges, color_offset + 1);\n                assert(rec_res.size()\
    \ == nxt_edges.size());\n                for (int i = 0; i < m - n; ++i) res[id[i]]\
    \ = rec_res[i];\n                return res;\n            }\n        }\n\n   \
    \     static std::pair<int, std::vector<int>> contract(const std::vector<int>&\
    \ deg, const int k) {\n            const int n = deg.size();\n            atcoder::dsu\
    \ uf(n);\n            priority_queue_greater<std::pair<int, int>> pq{};\n    \
    \        for (int i = 0; i < n; ++i) pq.emplace(deg[i], i);\n            while\
    \ (pq.size() >= 2) {\n                auto [di, i] = pq.top();\n             \
    \   pq.pop();\n                auto [dj, j] = pq.top();\n                pq.pop();\n\
    \                if (di + dj <= k) {\n                    uf.merge(i, j);\n  \
    \                  pq.emplace(di + dj, uf.leader(i));\n                } else\
    \ break;\n            }\n            auto groups = uf.groups();\n            const\
    \ int m = groups.size();\n            std::vector<int> cmp_id(n);\n          \
    \  for (int i = 0; i < m; ++i) for (int v : groups[i]) {\n                cmp_id[v]\
    \ = i;\n            }\n            return { m, cmp_id };\n        }\n    };\n\
    } // namespace suisen\n\n\n#endif // SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH\n"
  dependsOn:
  - library/graph/bipartite_matching.hpp
  isVerificationFile: false
  path: library/graph/edge_coloring_of_bipartite_graph.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/edge_coloring_of_bipartite_graph/bipartite_edge_coloring.test.cpp
documentation_of: library/graph/edge_coloring_of_bipartite_graph.hpp
layout: document
title: Edge Coloring Of Bipartite Graph
---
## Edge Coloring Of Bipartite Graph
