---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
    title: test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/range_contour_aggregation_query_on_tree.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <deque>\n#include <map>\n#include <queue>\n\
    #include <tuple>\n\n#include <atcoder/segtree>\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct RangeContourAggregationQueryOnTree\
    \ {\n        RangeContourAggregationQueryOnTree() {}\n        RangeContourAggregationQueryOnTree(int\
    \ n) : RangeContourAggregationQueryOnTree(std::vector<T>(n, e())) {}\n       \
    \ RangeContourAggregationQueryOnTree(const std::vector<T>& dat) : _n(dat.size()),\
    \ _g(_n), _par(_n, -1), _removed(_n, false), _pos(_n), _idx(_n), _dist(_n), _sub(_n),\
    \ _dat(dat) {}\n\n        using segtree_type = atcoder::segtree<T, op, e>;\n\n\
    \        struct SubTree {\n            std::vector<int> _sep;\n            segtree_type\
    \ _seq;\n\n            SubTree() {}\n            SubTree(\n                const\
    \ std::vector<std::vector<int>> &g,\n                const std::vector<int8_t>\
    \ &removed,\n                const int root,\n                const std::vector<T>\
    \ &dat,\n                const bool is_right_child,\n                std::vector<std::vector<int8_t>>\
    \ &idx,\n                std::vector<std::vector<int>> &pos,\n               \
    \ std::vector<std::vector<int>> &dist\n            ) {\n                auto is_dummy_vertex\
    \ = [&](int u) { return u >= int(dat.size()); };\n                _sep.push_back(0);\n\
    \                std::vector<T> reordered_dat;\n                std::deque<std::tuple<int,\
    \ int, int>> dq { { root, -1, 0 } };\n                int pre_dist = 0;\n    \
    \            while (dq.size()) {\n                    const auto [u, pu, du] =\
    \ dq.front();\n                    dq.pop_front();\n                    if (du\
    \ == pre_dist + 1) {\n                        _sep.push_back(reordered_dat.size());\n\
    \                        pre_dist = du;\n                    }\n             \
    \       bool b = is_dummy_vertex(u);\n                    if (not b) {\n     \
    \                   pos[u].push_back(reordered_dat.size());\n                \
    \        reordered_dat.push_back(dat[u]);\n                        idx[u].push_back(is_right_child);\n\
    \                        dist[u].push_back(du);\n                    }\n     \
    \               for (int v : g[u]) {\n                        if (v == pu or removed[v])\
    \ continue;\n                        if (b) {\n                            dq.emplace_front(v,\
    \ u, du);\n                        } else {\n                            dq.emplace_back(v,\
    \ u, du + 1);\n                        }\n                    }\n            \
    \    }\n                _sep.push_back(reordered_dat.size());\n              \
    \  _seq = segtree_type(reordered_dat);\n            }\n\n            void set(int\
    \ i, const T &val) {\n                _seq.set(i, val);\n            }\n     \
    \       T prod(int dl, int dr) {\n                if (dl < 0) dl = 0;\n      \
    \          if (dr >= int(_sep.size())) dr = int(_sep.size()) - 1;\n          \
    \      if (dl >= dr) return e();\n                int ql = _sep[dl], qr = _sep[dr];\n\
    \                return _seq.prod(ql, qr);\n            }\n        };\n\n    \
    \    void add_edge(int u, int v) {\n            _g[u].push_back(v);\n        \
    \    _g[v].push_back(u);\n        }\n\n        void build() {\n            std::vector<int>\
    \ sub(_n, 0);\n            std::vector<int> ctr(_n, -1);\n            auto rec\
    \ = [&](auto rec, int r, int siz) -> int {\n                int c = -1;\n    \
    \            auto get_centroid = [&](auto get_centroid, int u, int p) -> void\
    \ {\n                    sub[u] = 1;\n                    for (int v : _g[u])\
    \ {\n                        if (v == p or _removed[v]) continue;\n          \
    \              get_centroid(get_centroid, v, u);\n                        if (v\
    \ == c) {\n                            sub[u] = siz - sub[c];\n              \
    \              break;\n                        }\n                        sub[u]\
    \ += sub[v];\n                    }\n                    if (c < 0 and sub[u]\
    \ * 2 > siz) c = u;\n                };\n                get_centroid(get_centroid,\
    \ r, -1);\n\n                _removed[c] = true;\n                for (int v :\
    \ _g[c]) {\n                    if (_removed[v]) continue;\n                 \
    \   const int comp_size = sub[v];\n                    ctr[v] = rec(rec, v, comp_size);\n\
    \                    sub[v] = comp_size;\n                }\n\n              \
    \  auto comp = [&](int i, int j) { return sub[i] > sub[j]; };\n              \
    \  std::priority_queue<int, std::vector<int>, decltype(comp)> pq { comp };\n\n\
    \                for (int v : _g[c]) {\n                    if (_removed[v]) continue;\n\
    \                    pq.push(v);\n                }\n\n                while (pq.size()\
    \ >= 2) {\n                    int u = pq.top();\n                    pq.pop();\n\
    \                    int v = pq.top();\n                    pq.pop();\n      \
    \              if (pq.empty()) {\n                        _par[ctr[u]] = _par[ctr[v]]\
    \ = c;\n                        _sub[c][0] = SubTree{ _g, _removed, u, _dat, 0,\
    \ _idx, _pos, _dist };\n                        _sub[c][1] = SubTree{ _g, _removed,\
    \ v, _dat, 1, _idx, _pos, _dist };\n                    } else {\n           \
    \             int new_node = sub.size();\n                        sub.push_back(sub[u]\
    \ + sub[v]);\n                        ctr.push_back(new_node);\n             \
    \           _par.push_back(-1);\n                        _par[ctr[u]] = _par[ctr[v]]\
    \ = new_node;\n                        pq.push(new_node);\n                  \
    \      _removed.push_back(false);\n                        _g.emplace_back();\n\
    \                        _g[new_node].push_back(u);\n                        _g[new_node].push_back(v);\n\
    \                        _sub.emplace_back();\n                        _sub[new_node][0]\
    \ = SubTree{ _g, _removed, u, _dat, 0, _idx, _pos, _dist };\n                \
    \        _sub[new_node][1] = SubTree{ _g, _removed, v, _dat, 1, _idx, _pos, _dist\
    \ };\n                    }\n                }\n                if (pq.size())\
    \ {\n                    int u = pq.top();\n                    pq.pop();\n  \
    \                  _par[ctr[u]] = c;\n                    _sub[c][0] = SubTree{\
    \ _g, _removed, u, _dat, 0, _idx, _pos, _dist };\n                }\n        \
    \        _removed[c] = false;\n                return c;\n            };\n   \
    \         rec(rec, 0, _n);\n        }\n\n        T get(int u) {\n            return\
    \ _dat[u];\n        }\n        void set(int u, const T &val) {\n            _dat[u]\
    \ = val;\n            int h = _pos[u].size();\n            for (int i = 0, v =\
    \ _par[u]; i < h; ++i) {\n                _sub[std::exchange(v, _par[v])][_idx[u][i]].set(_pos[u][i],\
    \ val);\n            }\n        }\n        T prod(int u, int dl, int dr) {\n \
    \           T res = dl <= 0 and 0 < dr ? _dat[u] : e();\n            res = op(res,\
    \ _sub[u][0].prod(dl - 1, dr - 1));\n            res = op(res, _sub[u][1].prod(dl\
    \ - 1, dr - 1));\n            int h = _pos[u].size();\n            for (int i\
    \ = 0, v = _par[u]; i < h; ++i) {\n                int ql = dl - _dist[u][i] -\
    \ 2, qr = dr - _dist[u][i] - 2;\n                if (v < _n and ql <= -1 and -1\
    \ < qr) res = op(res, _dat[v]);\n                res = op(res, _sub[std::exchange(v,\
    \ _par[v])][_idx[u][i] ^ 1].prod(ql, qr));\n            }\n            return\
    \ res;\n        }\n\n    private:\n        int _n;\n        std::vector<std::vector<int>>\
    \ _g;\n        std::vector<int> _par;\n        std::vector<int8_t> _removed;\n\
    \        std::vector<std::vector<int>> _pos;\n        std::vector<std::vector<int8_t>>\
    \ _idx;\n        std::vector<std::vector<int>> _dist;\n        std::vector<std::array<SubTree,\
    \ 2>> _sub;\n        std::vector<T> _dat;\n    };\n} // namespace suisen\n\n\n\
    \n"
  code: "#ifndef SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE\n#define SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE\n\
    \n#include <cstdint>\n#include <deque>\n#include <map>\n#include <queue>\n#include\
    \ <tuple>\n\n#include <atcoder/segtree>\n\nnamespace suisen {\n    template <typename\
    \ T, T(*op)(T, T), T(*e)()>\n    struct RangeContourAggregationQueryOnTree {\n\
    \        RangeContourAggregationQueryOnTree() {}\n        RangeContourAggregationQueryOnTree(int\
    \ n) : RangeContourAggregationQueryOnTree(std::vector<T>(n, e())) {}\n       \
    \ RangeContourAggregationQueryOnTree(const std::vector<T>& dat) : _n(dat.size()),\
    \ _g(_n), _par(_n, -1), _removed(_n, false), _pos(_n), _idx(_n), _dist(_n), _sub(_n),\
    \ _dat(dat) {}\n\n        using segtree_type = atcoder::segtree<T, op, e>;\n\n\
    \        struct SubTree {\n            std::vector<int> _sep;\n            segtree_type\
    \ _seq;\n\n            SubTree() {}\n            SubTree(\n                const\
    \ std::vector<std::vector<int>> &g,\n                const std::vector<int8_t>\
    \ &removed,\n                const int root,\n                const std::vector<T>\
    \ &dat,\n                const bool is_right_child,\n                std::vector<std::vector<int8_t>>\
    \ &idx,\n                std::vector<std::vector<int>> &pos,\n               \
    \ std::vector<std::vector<int>> &dist\n            ) {\n                auto is_dummy_vertex\
    \ = [&](int u) { return u >= int(dat.size()); };\n                _sep.push_back(0);\n\
    \                std::vector<T> reordered_dat;\n                std::deque<std::tuple<int,\
    \ int, int>> dq { { root, -1, 0 } };\n                int pre_dist = 0;\n    \
    \            while (dq.size()) {\n                    const auto [u, pu, du] =\
    \ dq.front();\n                    dq.pop_front();\n                    if (du\
    \ == pre_dist + 1) {\n                        _sep.push_back(reordered_dat.size());\n\
    \                        pre_dist = du;\n                    }\n             \
    \       bool b = is_dummy_vertex(u);\n                    if (not b) {\n     \
    \                   pos[u].push_back(reordered_dat.size());\n                \
    \        reordered_dat.push_back(dat[u]);\n                        idx[u].push_back(is_right_child);\n\
    \                        dist[u].push_back(du);\n                    }\n     \
    \               for (int v : g[u]) {\n                        if (v == pu or removed[v])\
    \ continue;\n                        if (b) {\n                            dq.emplace_front(v,\
    \ u, du);\n                        } else {\n                            dq.emplace_back(v,\
    \ u, du + 1);\n                        }\n                    }\n            \
    \    }\n                _sep.push_back(reordered_dat.size());\n              \
    \  _seq = segtree_type(reordered_dat);\n            }\n\n            void set(int\
    \ i, const T &val) {\n                _seq.set(i, val);\n            }\n     \
    \       T prod(int dl, int dr) {\n                if (dl < 0) dl = 0;\n      \
    \          if (dr >= int(_sep.size())) dr = int(_sep.size()) - 1;\n          \
    \      if (dl >= dr) return e();\n                int ql = _sep[dl], qr = _sep[dr];\n\
    \                return _seq.prod(ql, qr);\n            }\n        };\n\n    \
    \    void add_edge(int u, int v) {\n            _g[u].push_back(v);\n        \
    \    _g[v].push_back(u);\n        }\n\n        void build() {\n            std::vector<int>\
    \ sub(_n, 0);\n            std::vector<int> ctr(_n, -1);\n            auto rec\
    \ = [&](auto rec, int r, int siz) -> int {\n                int c = -1;\n    \
    \            auto get_centroid = [&](auto get_centroid, int u, int p) -> void\
    \ {\n                    sub[u] = 1;\n                    for (int v : _g[u])\
    \ {\n                        if (v == p or _removed[v]) continue;\n          \
    \              get_centroid(get_centroid, v, u);\n                        if (v\
    \ == c) {\n                            sub[u] = siz - sub[c];\n              \
    \              break;\n                        }\n                        sub[u]\
    \ += sub[v];\n                    }\n                    if (c < 0 and sub[u]\
    \ * 2 > siz) c = u;\n                };\n                get_centroid(get_centroid,\
    \ r, -1);\n\n                _removed[c] = true;\n                for (int v :\
    \ _g[c]) {\n                    if (_removed[v]) continue;\n                 \
    \   const int comp_size = sub[v];\n                    ctr[v] = rec(rec, v, comp_size);\n\
    \                    sub[v] = comp_size;\n                }\n\n              \
    \  auto comp = [&](int i, int j) { return sub[i] > sub[j]; };\n              \
    \  std::priority_queue<int, std::vector<int>, decltype(comp)> pq { comp };\n\n\
    \                for (int v : _g[c]) {\n                    if (_removed[v]) continue;\n\
    \                    pq.push(v);\n                }\n\n                while (pq.size()\
    \ >= 2) {\n                    int u = pq.top();\n                    pq.pop();\n\
    \                    int v = pq.top();\n                    pq.pop();\n      \
    \              if (pq.empty()) {\n                        _par[ctr[u]] = _par[ctr[v]]\
    \ = c;\n                        _sub[c][0] = SubTree{ _g, _removed, u, _dat, 0,\
    \ _idx, _pos, _dist };\n                        _sub[c][1] = SubTree{ _g, _removed,\
    \ v, _dat, 1, _idx, _pos, _dist };\n                    } else {\n           \
    \             int new_node = sub.size();\n                        sub.push_back(sub[u]\
    \ + sub[v]);\n                        ctr.push_back(new_node);\n             \
    \           _par.push_back(-1);\n                        _par[ctr[u]] = _par[ctr[v]]\
    \ = new_node;\n                        pq.push(new_node);\n                  \
    \      _removed.push_back(false);\n                        _g.emplace_back();\n\
    \                        _g[new_node].push_back(u);\n                        _g[new_node].push_back(v);\n\
    \                        _sub.emplace_back();\n                        _sub[new_node][0]\
    \ = SubTree{ _g, _removed, u, _dat, 0, _idx, _pos, _dist };\n                \
    \        _sub[new_node][1] = SubTree{ _g, _removed, v, _dat, 1, _idx, _pos, _dist\
    \ };\n                    }\n                }\n                if (pq.size())\
    \ {\n                    int u = pq.top();\n                    pq.pop();\n  \
    \                  _par[ctr[u]] = c;\n                    _sub[c][0] = SubTree{\
    \ _g, _removed, u, _dat, 0, _idx, _pos, _dist };\n                }\n        \
    \        _removed[c] = false;\n                return c;\n            };\n   \
    \         rec(rec, 0, _n);\n        }\n\n        T get(int u) {\n            return\
    \ _dat[u];\n        }\n        void set(int u, const T &val) {\n            _dat[u]\
    \ = val;\n            int h = _pos[u].size();\n            for (int i = 0, v =\
    \ _par[u]; i < h; ++i) {\n                _sub[std::exchange(v, _par[v])][_idx[u][i]].set(_pos[u][i],\
    \ val);\n            }\n        }\n        T prod(int u, int dl, int dr) {\n \
    \           T res = dl <= 0 and 0 < dr ? _dat[u] : e();\n            res = op(res,\
    \ _sub[u][0].prod(dl - 1, dr - 1));\n            res = op(res, _sub[u][1].prod(dl\
    \ - 1, dr - 1));\n            int h = _pos[u].size();\n            for (int i\
    \ = 0, v = _par[u]; i < h; ++i) {\n                int ql = dl - _dist[u][i] -\
    \ 2, qr = dr - _dist[u][i] - 2;\n                if (v < _n and ql <= -1 and -1\
    \ < qr) res = op(res, _dat[v]);\n                res = op(res, _sub[std::exchange(v,\
    \ _par[v])][_idx[u][i] ^ 1].prod(ql, qr));\n            }\n            return\
    \ res;\n        }\n\n    private:\n        int _n;\n        std::vector<std::vector<int>>\
    \ _g;\n        std::vector<int> _par;\n        std::vector<int8_t> _removed;\n\
    \        std::vector<std::vector<int>> _pos;\n        std::vector<std::vector<int8_t>>\
    \ _idx;\n        std::vector<std::vector<int>> _dist;\n        std::vector<std::array<SubTree,\
    \ 2>> _sub;\n        std::vector<T> _dat;\n    };\n} // namespace suisen\n\n\n\
    #endif // SUISEN_RANGE_CONTOUR_QUERY_ON_TREE_BASE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/range_contour_aggregation_query_on_tree.hpp
  requiredBy: []
  timestamp: '2022-03-31 19:51:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
documentation_of: library/tree/range_contour_aggregation_query_on_tree.hpp
layout: document
redirect_from:
- /library/library/tree/range_contour_aggregation_query_on_tree.hpp
- /library/library/tree/range_contour_aggregation_query_on_tree.hpp.html
title: library/tree/range_contour_aggregation_query_on_tree.hpp
---
