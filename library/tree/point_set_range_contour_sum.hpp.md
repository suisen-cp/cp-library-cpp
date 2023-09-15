---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/tree/point_set_range_contour_sum/dummy.test.cpp
    title: test/src/tree/point_set_range_contour_sum/dummy.test.cpp
  - icon: ':x:'
    path: test/src/tree/point_set_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/src/tree/point_set_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/point_set_range_contour_sum.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cstdint>\n#include <deque>\n#include <map>\n#include <queue>\n\
    #include <tuple>\n#include <utility>\n\n#include <atcoder/segtree>\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct PointSetRangeContourSum\
    \ {\n        PointSetRangeContourSum() = default;\n        PointSetRangeContourSum(int\
    \ n, const T &fill_value) : PointSetRangeContourSum(std::vector<T>(n, fill_value))\
    \ {}\n        PointSetRangeContourSum(const std::vector<T> &dat) : _n(dat.size()),\
    \ _g(_n), _par(_n, -1), _removed(_n, false), _info(_n), _nodes(_n), _dat(dat)\
    \ {\n            _par.reserve(2 * _n);\n            for (int i = 0; i < _n; ++i)\
    \ _info[i].reserve(30);\n        }\n\n        using segtree_type = atcoder::segtree<T,\
    \ op, e>;\n\n        struct AuxData {\n            int segtree_index;\n      \
    \      int8_t child_index;\n            int dep;\n        };\n\n        struct\
    \ Node {\n            std::vector<int> _sep;\n            segtree_type _seq;\n\
    \n            Node() = default;\n            Node(const std::vector<std::vector<int>>&\
    \ g, const std::vector<int8_t>& removed, const std::vector<int> &roots, const\
    \ bool child_index, std::vector<std::vector<AuxData>>& info, const std::vector<T>\
    \ &dat, int siz) {\n                std::vector<T> reordered_dat(siz);\n     \
    \           _sep.push_back(0);\n                std::deque<std::tuple<int, int,\
    \ int>> dq;\n                for (int r : roots) dq.emplace_back(r, -1, 0);\n\
    \                int pre_dist = 0, cnt = 0;\n                while (dq.size())\
    \ {\n                    const auto [u, pu, du] = dq.front();\n              \
    \      dq.pop_front();\n                    if (du == pre_dist + 1) _sep.push_back(cnt),\
    \ pre_dist = du;\n                    info[u].push_back({ cnt, child_index, du\
    \ });\n                    reordered_dat[cnt++] = dat[u];\n                  \
    \  for (int v : g[u]) if (v != pu and not removed[v]) dq.emplace_back(v, u, du\
    \ + 1);\n                }\n                _sep.push_back(cnt);\n           \
    \     _seq = segtree_type(reordered_dat);\n            }\n\n            void set(int\
    \ i, const T& val) {\n                _seq.set(i, val);\n            }\n     \
    \       T sum(int dl, int dr) const {\n                dl = std::max(dl, 0);\n\
    \                dr = std::min(dr, int(_sep.size()) - 1);\n                return\
    \ dl < dr ? _seq.prod(_sep[dl], _sep[dr]) : e();\n            }\n        };\n\n\
    \        void add_edge(int u, int v) {\n            _g[u].push_back(v);\n    \
    \        _g[v].push_back(u);\n        }\n\n        void build() {\n          \
    \  std::vector<int> sub_size(_n, 0);\n            std::vector<int> ctr(_n, -1);\n\
    \            sub_size.reserve(2 * _n);\n            ctr.reserve(2 * _n);\n   \
    \         std::vector<std::vector<int>> ch(_n);\n            ch.reserve(2 * _n);\n\
    \n            auto merge = [&](std::vector<int> &&l, std::vector<int> &&r) ->\
    \ std::vector<int>&& {\n                if (l.size() > r.size()) std::swap(l,\
    \ r);\n                for (int v : l) r.push_back(v);\n                return\
    \ std::move(r);\n            };\n\n            auto rec = [&](auto rec, int r,\
    \ int siz) -> int {\n                int c = -1;\n                auto get_centroid\
    \ = [&](auto get_centroid, int u, int p) -> void {\n                    sub_size[u]\
    \ = 1;\n                    for (int v : _g[u]) {\n                        if\
    \ (v == p or _removed[v]) continue;\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub_size[u]\
    \ = siz - sub_size[c];\n                            break;\n                 \
    \       }\n                        sub_size[u] += sub_size[v];\n             \
    \       }\n                    if (c < 0 and sub_size[u] * 2 > siz) c = u;\n \
    \               };\n                get_centroid(get_centroid, r, -1);\n\n   \
    \             _removed[c] = true;\n                for (int v : _g[c]) {\n   \
    \                 if (_removed[v]) continue;\n                    const int comp_size\
    \ = sub_size[v];\n                    ctr[v] = rec(rec, v, comp_size);\n     \
    \               sub_size[v] = comp_size;\n                }\n\n              \
    \  auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n    \
    \            std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp\
    \ };\n\n                for (int v : _g[c]) {\n                    if (_removed[v])\
    \ continue;\n                    ch[v] = { v };\n                    pq.push(v);\n\
    \                }\n\n                while (pq.size() >= 2) {\n             \
    \       const int u = pq.top(); pq.pop();\n                    const int v = pq.top();\
    \ pq.pop();\n                    if (pq.empty()) {\n                        _par[ctr[u]]\
    \ = _par[ctr[v]] = c;\n                        _nodes[c][0] = Node{ _g, _removed,\
    \ ch[u], 0, _info, _dat, sub_size[u] };\n                        _nodes[c][1]\
    \ = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };\n              \
    \          break;\n                    }\n                    const int new_node\
    \ = sub_size.size();\n                    sub_size.push_back(sub_size[u] + sub_size[v]);\n\
    \                    ctr.push_back(new_node);\n                    _par.push_back(-1);\n\
    \                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n               \
    \     _nodes.emplace_back();\n                    _nodes[new_node][0] = Node{\
    \ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };\n                    _nodes[new_node][1]\
    \ = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };\n              \
    \      ch.push_back(merge(std::move(ch[u]), std::move(ch[v])));\n            \
    \        ch[u].clear(), ch[u].shrink_to_fit();\n                    ch[v].clear(),\
    \ ch[v].shrink_to_fit();\n                    pq.push(new_node);\n           \
    \     }\n                if (pq.size()) {\n                    int u = pq.top();\
    \ pq.pop();\n                    _par[ctr[u]] = c;\n                    _nodes[c][0]\
    \ = Node{ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };\n              \
    \  }\n                _removed[c] = false;\n                return c;\n      \
    \      };\n            rec(rec, 0, _n);\n        }\n\n        T get(int u) const\
    \ {\n            return _dat[u];\n        }\n        void set(int u, const T&\
    \ val) {\n            _dat[u] = val;\n            int v = _par[u];\n         \
    \   for (const auto &info : _info[u]) {\n                _nodes[std::exchange(v,\
    \ _par[v])][info.child_index].set(info.segtree_index, val);\n            }\n \
    \       }\n        T sum(int u, int dl, int dr) const {\n            T res = dl\
    \ <= 0 and 0 < dr ? _dat[u] : e();\n            res = op(res, _nodes[u][0].sum(dl\
    \ - 1, dr - 1));\n            res = op(res, _nodes[u][1].sum(dl - 1, dr - 1));\n\
    \            int v = _par[u];\n            for (const auto &info : _info[u]) {\n\
    \                int ql = dl - info.dep - 2, qr = dr - info.dep - 2;\n       \
    \         if (v < _n and ql <= -1 and -1 < qr) res = op(res, _dat[v]);\n     \
    \           res = op(res, _nodes[std::exchange(v, _par[v])][info.child_index ^\
    \ 1].sum(ql, qr));\n            }\n            return res;\n        }\n\n    private:\n\
    \        int _n;\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _par;\n        std::vector<int8_t> _removed;\n        std::vector<std::vector<AuxData>>\
    \ _info;\n        std::vector<std::array<Node, 2>> _nodes;\n        std::vector<T>\
    \ _dat;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_POINT_SET_RANGE_CONTOUR_SUM\n#define SUISEN_POINT_SET_RANGE_CONTOUR_SUM\n\
    \n#include <array>\n#include <cstdint>\n#include <deque>\n#include <map>\n#include\
    \ <queue>\n#include <tuple>\n#include <utility>\n\n#include <atcoder/segtree>\n\
    \nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)()>\n    struct\
    \ PointSetRangeContourSum {\n        PointSetRangeContourSum() = default;\n  \
    \      PointSetRangeContourSum(int n, const T &fill_value) : PointSetRangeContourSum(std::vector<T>(n,\
    \ fill_value)) {}\n        PointSetRangeContourSum(const std::vector<T> &dat)\
    \ : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _info(_n), _nodes(_n),\
    \ _dat(dat) {\n            _par.reserve(2 * _n);\n            for (int i = 0;\
    \ i < _n; ++i) _info[i].reserve(30);\n        }\n\n        using segtree_type\
    \ = atcoder::segtree<T, op, e>;\n\n        struct AuxData {\n            int segtree_index;\n\
    \            int8_t child_index;\n            int dep;\n        };\n\n       \
    \ struct Node {\n            std::vector<int> _sep;\n            segtree_type\
    \ _seq;\n\n            Node() = default;\n            Node(const std::vector<std::vector<int>>&\
    \ g, const std::vector<int8_t>& removed, const std::vector<int> &roots, const\
    \ bool child_index, std::vector<std::vector<AuxData>>& info, const std::vector<T>\
    \ &dat, int siz) {\n                std::vector<T> reordered_dat(siz);\n     \
    \           _sep.push_back(0);\n                std::deque<std::tuple<int, int,\
    \ int>> dq;\n                for (int r : roots) dq.emplace_back(r, -1, 0);\n\
    \                int pre_dist = 0, cnt = 0;\n                while (dq.size())\
    \ {\n                    const auto [u, pu, du] = dq.front();\n              \
    \      dq.pop_front();\n                    if (du == pre_dist + 1) _sep.push_back(cnt),\
    \ pre_dist = du;\n                    info[u].push_back({ cnt, child_index, du\
    \ });\n                    reordered_dat[cnt++] = dat[u];\n                  \
    \  for (int v : g[u]) if (v != pu and not removed[v]) dq.emplace_back(v, u, du\
    \ + 1);\n                }\n                _sep.push_back(cnt);\n           \
    \     _seq = segtree_type(reordered_dat);\n            }\n\n            void set(int\
    \ i, const T& val) {\n                _seq.set(i, val);\n            }\n     \
    \       T sum(int dl, int dr) const {\n                dl = std::max(dl, 0);\n\
    \                dr = std::min(dr, int(_sep.size()) - 1);\n                return\
    \ dl < dr ? _seq.prod(_sep[dl], _sep[dr]) : e();\n            }\n        };\n\n\
    \        void add_edge(int u, int v) {\n            _g[u].push_back(v);\n    \
    \        _g[v].push_back(u);\n        }\n\n        void build() {\n          \
    \  std::vector<int> sub_size(_n, 0);\n            std::vector<int> ctr(_n, -1);\n\
    \            sub_size.reserve(2 * _n);\n            ctr.reserve(2 * _n);\n   \
    \         std::vector<std::vector<int>> ch(_n);\n            ch.reserve(2 * _n);\n\
    \n            auto merge = [&](std::vector<int> &&l, std::vector<int> &&r) ->\
    \ std::vector<int>&& {\n                if (l.size() > r.size()) std::swap(l,\
    \ r);\n                for (int v : l) r.push_back(v);\n                return\
    \ std::move(r);\n            };\n\n            auto rec = [&](auto rec, int r,\
    \ int siz) -> int {\n                int c = -1;\n                auto get_centroid\
    \ = [&](auto get_centroid, int u, int p) -> void {\n                    sub_size[u]\
    \ = 1;\n                    for (int v : _g[u]) {\n                        if\
    \ (v == p or _removed[v]) continue;\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub_size[u]\
    \ = siz - sub_size[c];\n                            break;\n                 \
    \       }\n                        sub_size[u] += sub_size[v];\n             \
    \       }\n                    if (c < 0 and sub_size[u] * 2 > siz) c = u;\n \
    \               };\n                get_centroid(get_centroid, r, -1);\n\n   \
    \             _removed[c] = true;\n                for (int v : _g[c]) {\n   \
    \                 if (_removed[v]) continue;\n                    const int comp_size\
    \ = sub_size[v];\n                    ctr[v] = rec(rec, v, comp_size);\n     \
    \               sub_size[v] = comp_size;\n                }\n\n              \
    \  auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n    \
    \            std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp\
    \ };\n\n                for (int v : _g[c]) {\n                    if (_removed[v])\
    \ continue;\n                    ch[v] = { v };\n                    pq.push(v);\n\
    \                }\n\n                while (pq.size() >= 2) {\n             \
    \       const int u = pq.top(); pq.pop();\n                    const int v = pq.top();\
    \ pq.pop();\n                    if (pq.empty()) {\n                        _par[ctr[u]]\
    \ = _par[ctr[v]] = c;\n                        _nodes[c][0] = Node{ _g, _removed,\
    \ ch[u], 0, _info, _dat, sub_size[u] };\n                        _nodes[c][1]\
    \ = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };\n              \
    \          break;\n                    }\n                    const int new_node\
    \ = sub_size.size();\n                    sub_size.push_back(sub_size[u] + sub_size[v]);\n\
    \                    ctr.push_back(new_node);\n                    _par.push_back(-1);\n\
    \                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n               \
    \     _nodes.emplace_back();\n                    _nodes[new_node][0] = Node{\
    \ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };\n                    _nodes[new_node][1]\
    \ = Node{ _g, _removed, ch[v], 1, _info, _dat, sub_size[v] };\n              \
    \      ch.push_back(merge(std::move(ch[u]), std::move(ch[v])));\n            \
    \        ch[u].clear(), ch[u].shrink_to_fit();\n                    ch[v].clear(),\
    \ ch[v].shrink_to_fit();\n                    pq.push(new_node);\n           \
    \     }\n                if (pq.size()) {\n                    int u = pq.top();\
    \ pq.pop();\n                    _par[ctr[u]] = c;\n                    _nodes[c][0]\
    \ = Node{ _g, _removed, ch[u], 0, _info, _dat, sub_size[u] };\n              \
    \  }\n                _removed[c] = false;\n                return c;\n      \
    \      };\n            rec(rec, 0, _n);\n        }\n\n        T get(int u) const\
    \ {\n            return _dat[u];\n        }\n        void set(int u, const T&\
    \ val) {\n            _dat[u] = val;\n            int v = _par[u];\n         \
    \   for (const auto &info : _info[u]) {\n                _nodes[std::exchange(v,\
    \ _par[v])][info.child_index].set(info.segtree_index, val);\n            }\n \
    \       }\n        T sum(int u, int dl, int dr) const {\n            T res = dl\
    \ <= 0 and 0 < dr ? _dat[u] : e();\n            res = op(res, _nodes[u][0].sum(dl\
    \ - 1, dr - 1));\n            res = op(res, _nodes[u][1].sum(dl - 1, dr - 1));\n\
    \            int v = _par[u];\n            for (const auto &info : _info[u]) {\n\
    \                int ql = dl - info.dep - 2, qr = dr - info.dep - 2;\n       \
    \         if (v < _n and ql <= -1 and -1 < qr) res = op(res, _dat[v]);\n     \
    \           res = op(res, _nodes[std::exchange(v, _par[v])][info.child_index ^\
    \ 1].sum(ql, qr));\n            }\n            return res;\n        }\n\n    private:\n\
    \        int _n;\n        std::vector<std::vector<int>> _g;\n        std::vector<int>\
    \ _par;\n        std::vector<int8_t> _removed;\n        std::vector<std::vector<AuxData>>\
    \ _info;\n        std::vector<std::array<Node, 2>> _nodes;\n        std::vector<T>\
    \ _dat;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_POINT_SET_RANGE_CONTOUR_SUM"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/point_set_range_contour_sum.hpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/tree/point_set_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
  - test/src/tree/point_set_range_contour_sum/dummy.test.cpp
documentation_of: library/tree/point_set_range_contour_sum.hpp
layout: document
title: Point Set Range Contour Sum
---
## Point Set Range Contour Sum

以下のような問題を考えます。

### 問題

$N$ 頂点の木 $T$ の各頂点 $v$ に可換モノイド $(G,\oplus)$ の元 $A _ v$ が書かれている。以下の形式で表されるクエリが $Q$ 個与えられるので、順番に処理せよ。

- `1 v x` : 頂点 $v\in V(T)$ に書かれた値を $x$ に変更する。即ち、$A _ v \leftarrow x$ とする。
- `2 v l r` : 頂点 $v\in V(T)$ からの最短距離が $l$ 以上 $r$ 未満であるような頂点の集合を $S(v,l,r)$ として、$\displaystyle \bigoplus _ { u \in S (v,l, r) } A _ u$ を計算する。

ここで、$T$ の辺の重みは全て $1$ であるとします。

本ライブラリは、$\oplus$ の計算にかかる時間を $O(1)$ と仮定して、上記の問題を前計算 $\Theta(N \log N)$、クエリ $\Theta( (\log N) ^ 2 )$ で解くアルゴリズムの実装です。

## 参考

- [重心分解で 1 点更新区間取得 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2022/03/27/042143)