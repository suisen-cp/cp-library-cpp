---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/tree/point_add_range_contour_sum.hpp
    title: library/tree/point_add_range_contour_sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
    links:
    - https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
  bundledCode: "#line 1 \"test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree\"\
    \n\n#include <iostream>\n\n#line 1 \"library/tree/point_add_range_contour_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <deque>\n\
    #line 9 \"library/tree/point_add_range_contour_sum.hpp\"\n#include <queue>\n#include\
    \ <random>\n#include <utility>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct PointAddRangeContourSum {\n\
    \        using value_type = T;\n    private:\n        struct InternalSegmentTree\
    \ {\n            InternalSegmentTree(int n = 0) : _n(n), _dat(n + 1, e()) {}\n\
    \            template <typename InputIterator>\n            InternalSegmentTree(InputIterator\
    \ first, InputIterator last) : _n(last - first), _dat(2 * _n, e()) {\n       \
    \         for (int i = 0; i < _n; ++i) _dat[_n + i] = *first++;\n            \
    \    for (int i = _n - 1; i > 0; --i) _dat[i] = op(_dat[2 * i], _dat[2 * i + 1]);\n\
    \            }\n            void add(int i, const value_type& val) {\n       \
    \         for (i += _n; i; i >>= 1) _dat[i] = op(_dat[i], val);\n            }\n\
    \            value_type sum(int l, int r) const {\n                l = std::max(0,\
    \ l), r = std::min(r, _n);\n                value_type res = e();\n          \
    \      for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {\n                   \
    \ if (l & 1) res = op(res, _dat[l++]);\n                    if (r & 1) res = op(res,\
    \ _dat[--r]);\n                }\n                return res;\n            }\n\
    \        private:\n            int _n;\n            std::vector<value_type> _dat;\n\
    \        };\n        using sequence_type = InternalSegmentTree;\n\n        struct\
    \ AuxInfo {\n            int8_t child_index;\n            int dep;\n        };\n\
    \n        struct TreeNode {\n            std::vector<int> adj;\n            typename\
    \ std::array<AuxInfo, 30>::iterator info_it;\n            value_type dat;\n  \
    \      };\n    public:\n        PointAddRangeContourSum(int n = 0, const value_type&\
    \ fill_value = e()) : PointAddRangeContourSum(std::vector<value_type>(n, fill_value))\
    \ {}\n        PointAddRangeContourSum(const std::vector<value_type>& a) : _n(a.size()),\
    \ _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n), _ord(_n) {\n   \
    \         for (int i = 0; i < _n; ++i) _nodes[i].dat = a[i];\n        }\n\n  \
    \      void add_edge(int u, int v) {\n            _nodes[u].adj.push_back(v);\n\
    \            _nodes[v].adj.push_back(u);\n        }\n\n        // O(NlogN)\n \
    \       void build() {\n            std::mt19937 rng{ std::random_device{}() };\n\
    \            reorder(std::uniform_int_distribution<int>{ 0, _n - 1 }(rng));\n\n\
    \            int new_node = _n;\n            std::vector<int> sub_size(2 * _n,\
    \ 0);\n            std::vector<int> ctr(2 * _n, -1);\n\n            std::vector<int>\
    \ head(2 * _n), tail(2 * _n), link(2 * _n);\n            for (int i = 0; i < _n;\
    \ ++i) head[i] = tail[i] = i;\n\n            std::vector<value_type> dat(_n);\n\
    \n            auto rec = [&](auto rec, int r, int siz) -> int {\n            \
    \    int c = -1;\n                auto get_centroid = [&](auto get_centroid, int\
    \ u, int p) -> void {\n                    sub_size[u] = 1;\n                \
    \    for (int v : _nodes[u].adj) if (v != p) {\n                        get_centroid(get_centroid,\
    \ v, u);\n                        if (v == c) {\n                            sub_size[u]\
    \ = siz - sub_size[c];\n                            break;\n                 \
    \       }\n                        sub_size[u] += sub_size[v];\n             \
    \       }\n                    if (c < 0 and sub_size[u] * 2 > siz) c = u;\n \
    \               };\n                get_centroid(get_centroid, r, -1);\n\n   \
    \             for (int v : _nodes[c].adj) {\n                    const int comp_size\
    \ = sub_size[v];\n                    _nodes[v].adj.erase(std::find(_nodes[v].adj.begin(),\
    \ _nodes[v].adj.end(), c));\n                    ctr[v] = rec(rec, v, comp_size);\n\
    \                    sub_size[v] = comp_size;\n                }\n\n         \
    \       auto comp = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n\
    \                std::priority_queue<int, std::vector<int>, decltype(comp)> pq{\
    \ comp };\n\n                for (int v : _nodes[c].adj) {\n                 \
    \   link[v] = -1;\n                    pq.push(v);\n                }\n\n    \
    \            auto build_sequence = [&, this](const int root_head, const bool child_index)\
    \ {\n                    std::deque<std::pair<int, int>> dq;\n               \
    \     for (int root = root_head; root >= 0; root = link[root]) dq.emplace_back(root,\
    \ -1);\n                    value_type sum = e();\n                    auto dat_it\
    \ = dat.begin();\n                    int nxt = -1;\n                    while\
    \ (dq.size()) {\n                        const auto [u, pu] = dq.front();\n  \
    \                      dq.pop_front();\n                        if (u == nxt)\
    \ *dat_it++ = std::exchange(sum, e()), nxt = -1;\n                        auto&\
    \ node = _nodes[u];\n                        *node.info_it++ = { child_index,\
    \ int(dat_it - dat.begin()) };\n                        sum = op(sum, node.dat);\n\
    \                        for (int v : node.adj) if (v != pu) {\n             \
    \               dq.emplace_back(v, u);\n                            if (nxt <\
    \ 0) nxt = v;\n                        }\n                    }\n            \
    \        *dat_it++ = sum;\n                    return sequence_type(dat.begin(),\
    \ dat_it);\n                };\n\n                while (pq.size() >= 2) {\n \
    \                   const int u = pq.top(); pq.pop();\n                    const\
    \ int v = pq.top(); pq.pop();\n                    if (pq.empty()) {\n       \
    \                 _par[ctr[u]] = _par[ctr[v]] = c;\n                        _subtrees[c][0]\
    \ = build_sequence(head[u], 0);\n                        _subtrees[c][1] = build_sequence(head[v],\
    \ 1);\n                        break;\n                    }\n               \
    \     sub_size[new_node] = sub_size[u] + sub_size[v];\n                    ctr[new_node]\
    \ = new_node;\n                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n \
    \                   _subtrees[new_node][0] = build_sequence(head[u], 0);\n   \
    \                 _subtrees[new_node][1] = build_sequence(head[v], 1);\n     \
    \               head[new_node] = head[u], tail[new_node] = tail[v], link[tail[u]]\
    \ = head[v];\n                    pq.push(new_node);\n                    ++new_node;\n\
    \                }\n                if (pq.size()) {\n                    int\
    \ u = pq.top(); pq.pop();\n                    _par[ctr[u]] = c;\n           \
    \         _subtrees[c][0] = build_sequence(head[u], 0);\n                }\n \
    \               for (int v : _nodes[c].adj) _nodes[v].adj.push_back(c);\n    \
    \            return c;\n            };\n            rec(rec, 0, _n);\n       \
    \     _par.resize(new_node), _par.shrink_to_fit();\n            _subtrees.resize(new_node),\
    \ _subtrees.shrink_to_fit();\n        }\n\n        // O(1)\n        value_type\
    \ get(int u) const {\n            u = _ord[u];\n            return _nodes[u].dat;\n\
    \        }\n        // O((logN)^2)\n        void add(int u, const value_type&\
    \ val) {\n            u = _ord[u];\n            _nodes[u].dat = op(_nodes[u].dat,\
    \ val);\n            int v = _par[u];\n            const auto it_end = _nodes[u].info_it;\n\
    \            for (auto it = _info[u].begin(); it != it_end; ++it) _subtrees[std::exchange(v,\
    \ _par[v])][it->child_index].add(it->dep, val);\n        }\n        // O((logN)^2)\n\
    \        value_type sum(int u, int dl, int dr) const {\n            u = _ord[u];\n\
    \            value_type res = dl <= 0 and 0 < dr ? _nodes[u].dat : e();\n    \
    \        res = op(res, _subtrees[u][0].sum(dl - 1, dr - 1));\n            res\
    \ = op(res, _subtrees[u][1].sum(dl - 1, dr - 1));\n            int v = _par[u];\n\
    \            const auto it_end = _nodes[u].info_it;\n            for (auto it\
    \ = _info[u].begin(); it != it_end; ++it) {\n                const int ql = dl\
    \ - it->dep - 1, qr = dr - it->dep - 1;\n                if (v < _n and ql <=\
    \ 0 and 0 < qr) res = op(res, _nodes[v].dat);\n                res = op(res, _subtrees[std::exchange(v,\
    \ _par[v])][it->child_index ^ 1].sum(ql - 1, qr - 1));\n            }\n      \
    \      return res;\n        }\n\n    private:\n        int _n;\n        std::vector<TreeNode>\
    \ _nodes;\n        std::vector<int> _par;\n        std::vector<std::array<AuxInfo,\
    \ 30>> _info;\n        std::vector<std::array<sequence_type, 2>> _subtrees;\n\n\
    \        std::vector<int> _ord;\n\n        void reorder(int s) {\n           \
    \ _ord.assign(_n, -1);\n            int t = 0;\n            std::deque<int> dq{\
    \ s };\n            while (dq.size()) {\n                int u = dq.front(); dq.pop_front();\n\
    \                _ord[u] = t++;\n                for (int v : _nodes[u].adj) if\
    \ (_ord[v] < 0) dq.push_back(v);\n            }\n            assert(t == _n);\n\
    \            std::vector<TreeNode> tmp(_n);\n            for (int i = 0; i < _n;\
    \ ++i) {\n                for (int& elm : _nodes[i].adj) elm = _ord[elm];\n  \
    \              _nodes[i].info_it = _info[_ord[i]].begin();\n                tmp[_ord[i]]\
    \ = std::move(_nodes[i]);\n            }\n            _nodes.swap(tmp);\n    \
    \    }\n    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp\"\
    \n\nlong long op(long long x, long long y) {\n    return x + y;\n}\nlong long\
    \ e() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    \n    int n, q;\n    std::cin >> n >> q;\n\n\
    \    std::vector<long long> a(n);\n    for (auto &e : a) std::cin >> e;\n\n  \
    \  suisen::PointAddRangeContourSum<long long, op, e> g(a);\n    for (int i = 0;\
    \ i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        g.add_edge(u,\
    \ v);\n    }\n    g.build();\n\n    while (q --> 0) {\n        int query_type;\n\
    \        std::cin >> query_type;\n        if (query_type == 0) {\n           \
    \ int p, x;\n            std::cin >> p >> x;\n            g.add(p, x);\n     \
    \   } else {\n            int p, l, r;\n            std::cin >> p >> l >> r;\n\
    \            std::cout << g.sum(p, l, r) << '\\n';\n        }\n    }\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree\"\
    \n\n#include <iostream>\n\n#include \"library/tree/point_add_range_contour_sum.hpp\"\
    \n\nlong long op(long long x, long long y) {\n    return x + y;\n}\nlong long\
    \ e() {\n    return 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    \n    int n, q;\n    std::cin >> n >> q;\n\n\
    \    std::vector<long long> a(n);\n    for (auto &e : a) std::cin >> e;\n\n  \
    \  suisen::PointAddRangeContourSum<long long, op, e> g(a);\n    for (int i = 0;\
    \ i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        g.add_edge(u,\
    \ v);\n    }\n    g.build();\n\n    while (q --> 0) {\n        int query_type;\n\
    \        std::cin >> query_type;\n        if (query_type == 0) {\n           \
    \ int p, x;\n            std::cin >> p >> x;\n            g.add(p, x);\n     \
    \   } else {\n            int p, l, r;\n            std::cin >> p >> l >> r;\n\
    \            std::cout << g.sum(p, l, r) << '\\n';\n        }\n    }\n\n    return\
    \ 0;\n}"
  dependsOn:
  - library/tree/point_add_range_contour_sum.hpp
  isVerificationFile: true
  path: test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
  requiredBy: []
  timestamp: '2022-09-05 23:57:42+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
- /verify/test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp.html
title: test/src/tree/point_add_range_contour_sum/vertex_add_range_contour_sum_on_tree.test.cpp
---
