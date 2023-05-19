---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/point_get_range_contour_operate.hpp
    title: Point Get Range Contour Operate
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
    links:
    - https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
  bundledCode: "#line 1 \"test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree\"\
    \n\n#include <iostream>\n\n#line 1 \"library/tree/point_get_range_contour_operate.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstdint>\n\
    #include <deque>\n#include <queue>\n#include <random>\n#include <tuple>\n#include\
    \ <utility>\n\nnamespace suisen {\n    template <typename T, typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n    struct PointGetRangeContourOperate\
    \ {\n        using value_type = T;\n        using operator_type = F;\n    private:\n\
    \        struct InternalCommutativeDualSegmentTree {\n            InternalCommutativeDualSegmentTree(int\
    \ n = 0) : _n(n), _laz(2 * _n, id()) {}\n            void apply(int l, int r,\
    \ const operator_type& f) {\n                l = std::max(l, 0), r = std::min(r,\
    \ _n);\n                for (l += _n, r += _n; l < r; l >>= 1, r >>= 1) {\n  \
    \                  if (l & 1) _laz[l] = composition(f, _laz[l]), ++l;\n      \
    \              if (r & 1) --r, _laz[r] = composition(f, _laz[r]);\n          \
    \      }\n            }\n            operator_type get(int i) const {\n      \
    \          operator_type res = id();\n                for (i += _n; i; i >>= 1)\
    \ res = composition(res, _laz[i]);\n                return res;\n            }\n\
    \        private:\n            int _n;\n            std::vector<operator_type>\
    \ _laz;\n        };\n\n        using sequence_type = InternalCommutativeDualSegmentTree;\n\
    \n        struct AuxInfo {\n            int8_t child_index;\n            int dep;\n\
    \        };\n\n        struct TreeNode {\n            std::vector<int> adj;\n\
    \            typename std::array<AuxInfo, 30>::iterator info_it;\n        };\n\
    \    public:\n        PointGetRangeContourOperate(int n = 0) : _n(n), _dat(_n),\
    \ _nodes(_n), _par(2 * _n, -1), _info(_n), _subtrees(2 * _n) {}\n\n        void\
    \ add_edge(int u, int v) {\n            _nodes[u].adj.push_back(v);\n        \
    \    _nodes[v].adj.push_back(u);\n        }\n        // O(NlogN)\n        void\
    \ build(const std::vector<value_type>& a) {\n            for (int i = 0; i < _n;\
    \ ++i) _dat[i] = a[i], _nodes[i].info_it = _info[i].begin();\n\n            int\
    \ new_node = _n;\n            std::vector<int> sub_size(2 * _n, 0);\n        \
    \    std::vector<int> ctr(2 * _n, -1);\n\n            std::vector<int> head(2\
    \ * _n), tail(2 * _n), link(2 * _n);\n            for (int i = 0; i < _n; ++i)\
    \ head[i] = tail[i] = i;\n\n            auto rec = [&](auto rec, int r, int siz)\
    \ -> int {\n                int c = -1;\n                auto get_centroid = [&](auto\
    \ get_centroid, int u, int p) -> void {\n                    sub_size[u] = 1;\n\
    \                    for (int v : _nodes[u].adj) if (v != p) {\n             \
    \           get_centroid(get_centroid, v, u);\n                        if (v ==\
    \ c) {\n                            sub_size[u] = siz - sub_size[c];\n       \
    \                     break;\n                        }\n                    \
    \    sub_size[u] += sub_size[v];\n                    }\n                    if\
    \ (c < 0 and sub_size[u] * 2 > siz) c = u;\n                };\n             \
    \   get_centroid(get_centroid, r, -1);\n\n                for (int v : _nodes[c].adj)\
    \ {\n                    const int comp_size = sub_size[v];\n                \
    \    _nodes[v].adj.erase(std::find(_nodes[v].adj.begin(), _nodes[v].adj.end(),\
    \ c));\n                    ctr[v] = rec(rec, v, comp_size);\n               \
    \     sub_size[v] = comp_size;\n                }\n\n                auto comp\
    \ = [&](int i, int j) { return sub_size[i] > sub_size[j]; };\n               \
    \ std::priority_queue<int, std::vector<int>, decltype(comp)> pq{ comp };\n\n \
    \               for (int v : _nodes[c].adj) {\n                    link[v] = -1;\n\
    \                    pq.push(v);\n                }\n\n                auto build_sequence\
    \ = [&, this](const int root_head, const bool child_index) {\n               \
    \     std::deque<std::pair<int, int>> dq;\n                    for (int root =\
    \ root_head; root >= 0; root = link[root]) dq.emplace_back(root, -1);\n      \
    \              int dep = 0, nxt = -1;\n                    while (dq.size()) {\n\
    \                        const auto [u, pu] = dq.front();\n                  \
    \      dq.pop_front();\n                        if (u == nxt) ++dep, nxt = -1;\n\
    \                        auto& node = _nodes[u];\n                        *node.info_it++\
    \ = { child_index, dep };\n                        for (int v : node.adj) if (v\
    \ != pu) {\n                            dq.emplace_back(v, u);\n             \
    \               if (nxt < 0) nxt = v;\n                        }\n           \
    \         }\n                    return sequence_type(++dep);\n              \
    \  };\n\n                while (pq.size() >= 2) {\n                    const int\
    \ u = pq.top(); pq.pop();\n                    const int v = pq.top(); pq.pop();\n\
    \                    if (pq.empty()) {\n                        _par[ctr[u]] =\
    \ _par[ctr[v]] = c;\n                        _subtrees[c][0] = build_sequence(head[u],\
    \ 0);\n                        _subtrees[c][1] = build_sequence(head[v], 1);\n\
    \                        break;\n                    }\n                    sub_size[new_node]\
    \ = sub_size[u] + sub_size[v];\n                    ctr[new_node] = new_node;\n\
    \                    _par[ctr[u]] = _par[ctr[v]] = new_node;\n               \
    \     _subtrees[new_node][0] = build_sequence(head[u], 0);\n                 \
    \   _subtrees[new_node][1] = build_sequence(head[v], 1);\n                   \
    \ head[new_node] = head[u], tail[new_node] = tail[v], link[tail[u]] = head[v];\n\
    \                    pq.push(new_node);\n                    ++new_node;\n   \
    \             }\n                if (pq.size()) {\n                    int u =\
    \ pq.top(); pq.pop();\n                    _par[ctr[u]] = c;\n               \
    \     _subtrees[c][0] = build_sequence(head[u], 0);\n                }\n     \
    \           for (int v : _nodes[c].adj) _nodes[v].adj.push_back(c);\n        \
    \        return c;\n            };\n            rec(rec, 0, _n);\n           \
    \ _par.resize(new_node), _par.shrink_to_fit();\n            _subtrees.resize(new_node),\
    \ _subtrees.shrink_to_fit();\n        }\n\n        // O((logN)^2)\n        value_type\
    \ get(int u) const {\n            value_type res = _dat[u];\n            int v\
    \ = _par[u];\n            const auto it_end = _nodes[u].info_it;\n           \
    \ for (auto it = _info[u].begin(); it != it_end; ++it) res = mapping(_subtrees[std::exchange(v,\
    \ _par[v])][it->child_index].get(it->dep), res);\n            return res;\n  \
    \      }\n        // O(1)\n        void apply(int u, const operator_type& f) {\n\
    \            _dat[u] = mapping(f, _dat[u]);\n        }\n        // O((logN)^2)\n\
    \        void apply(int u, int dl, int dr, const operator_type& f) {\n       \
    \     if (dl <= 0 and 0 < dr) _dat[u] = mapping(f, _dat[u]);\n            _subtrees[u][0].apply(dl\
    \ - 1, dr - 1, f);\n            _subtrees[u][1].apply(dl - 1, dr - 1, f);\n  \
    \          int v = _par[u];\n            const auto it_end = _nodes[u].info_it;\n\
    \            for (auto it = _info[u].begin(); it != it_end; ++it) {\n        \
    \        int ql = dl - it->dep - 1, qr = dr - it->dep - 1;\n                if\
    \ (v < _n and ql <= 0 and 0 < qr) _dat[v] = mapping(f, _dat[v]);\n           \
    \     _subtrees[std::exchange(v, _par[v])][it->child_index ^ 1].apply(ql - 1,\
    \ qr - 1, f);\n            }\n        }\n\n    private:\n        int _n;\n   \
    \     std::vector<value_type> _dat;\n        std::vector<TreeNode> _nodes;\n \
    \       std::vector<int> _par;\n        std::vector<std::array<AuxInfo, 30>> _info;\n\
    \        std::vector<std::array<sequence_type, 2>> _subtrees;\n    };\n} // namespace\
    \ suisen\n\n\n#line 6 \"test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp\"\
    \n\nusing T = long long;\nusing F = long long;\nT mapping(F f, T x) {\n    return\
    \ f + x;\n}\nF composition(F f, F g) {\n    return f + g;\n}\nF id() {\n    return\
    \ 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    using suisen::PointGetRangeContourOperate;\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n\n    std::vector<T> a(n);\n    for (auto &e : a) std::cin >> e;\n\
    \n    PointGetRangeContourOperate<T, F, mapping, composition, id> g(n);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        g.add_edge(u, v);\n    }\n    g.build(a);\n\n    while (q --> 0) {\n\
    \        int query_type;\n        std::cin >> query_type;\n        if (query_type\
    \ == 0) {\n            int p, l, r, x;\n            std::cin >> p >> l >> r >>\
    \ x;\n            g.apply(p, l, r, x);\n        } else {\n            int p;\n\
    \            std::cin >> p;\n            std::cout << g.get(p) << '\\n';\n   \
    \     }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree\"\
    \n\n#include <iostream>\n\n#include \"library/tree/point_get_range_contour_operate.hpp\"\
    \n\nusing T = long long;\nusing F = long long;\nT mapping(F f, T x) {\n    return\
    \ f + x;\n}\nF composition(F f, F g) {\n    return f + g;\n}\nF id() {\n    return\
    \ 0;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    using suisen::PointGetRangeContourOperate;\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n\n    std::vector<T> a(n);\n    for (auto &e : a) std::cin >> e;\n\
    \n    PointGetRangeContourOperate<T, F, mapping, composition, id> g(n);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        g.add_edge(u, v);\n    }\n    g.build(a);\n\n    while (q --> 0) {\n\
    \        int query_type;\n        std::cin >> query_type;\n        if (query_type\
    \ == 0) {\n            int p, l, r, x;\n            std::cin >> p >> l >> r >>\
    \ x;\n            g.apply(p, l, r, x);\n        } else {\n            int p;\n\
    \            std::cin >> p;\n            std::cout << g.get(p) << '\\n';\n   \
    \     }\n    }\n}"
  dependsOn:
  - library/tree/point_get_range_contour_operate.hpp
  isVerificationFile: true
  path: test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp
  requiredBy: []
  timestamp: '2023-05-18 22:36:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp
- /verify/test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp.html
title: test/src/tree/point_get_range_contour_operate/vertex_get_range_contour_add_on_tree.test.cpp
---
