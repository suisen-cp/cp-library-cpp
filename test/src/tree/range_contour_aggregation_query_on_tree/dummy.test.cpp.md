---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/range_contour_aggregation_query_on_tree.hpp
    title: "Range Contour Aggregation Query On Tree (\u6728\u4E0A\u306E\u7B49\u9AD8\
      \u7DDA\u96C6\u7D04\u30AF\u30A8\u30EA)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <numeric>\n#include <random>\n\n#line 1 \"library/tree/range_contour_aggregation_query_on_tree.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <deque>\n#include <map>\n#include <queue>\n\
    #include <tuple>\n\n#include <atcoder/segtree>\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct RangeContourAggregationQueryOnTree\
    \ {\n        RangeContourAggregationQueryOnTree() {}\n        RangeContourAggregationQueryOnTree(int\
    \ n, const T &fill_value) : RangeContourAggregationQueryOnTree(std::vector<T>(n,\
    \ fill_value)) {}\n        RangeContourAggregationQueryOnTree(const std::vector<T>\
    \ &dat) : _n(dat.size()), _g(_n), _par(_n, -1), _removed(_n, false), _info(_n),\
    \ _nodes(_n), _dat(dat) {\n            _par.reserve(2 * _n);\n            for\
    \ (int i = 0; i < _n; ++i) _info[i].reserve(30);\n        }\n\n        using segtree_type\
    \ = atcoder::segtree<T, op, e>;\n\n        struct AuxData {\n            int segtree_index;\n\
    \            int8_t child_index;\n            int dist;\n        };\n\n      \
    \  struct Node {\n            std::vector<int> _sep;\n            segtree_type\
    \ _seq;\n\n            Node() {}\n            Node(const std::vector<std::vector<int>>&\
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
    \       T prod(int dl, int dr) const {\n                dl = std::max(dl, 0);\n\
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
    \       }\n        T prod(int u, int dl, int dr) const {\n            T res =\
    \ dl <= 0 and 0 < dr ? _dat[u] : e();\n            res = op(res, _nodes[u][0].prod(dl\
    \ - 1, dr - 1));\n            res = op(res, _nodes[u][1].prod(dl - 1, dr - 1));\n\
    \            int v = _par[u];\n            for (const auto &info : _info[u]) {\n\
    \                int ql = dl - info.dist - 2, qr = dr - info.dist - 2;\n     \
    \           if (v < _n and ql <= -1 and -1 < qr) res = op(res, _dat[v]);\n   \
    \             res = op(res, _nodes[std::exchange(v, _par[v])][info.child_index\
    \ ^ 1].prod(ql, qr));\n            }\n            return res;\n        }\n\n \
    \   private:\n        int _n;\n        std::vector<std::vector<int>> _g;\n   \
    \     std::vector<int> _par;\n        std::vector<int8_t> _removed;\n        std::vector<std::vector<AuxData>>\
    \ _info;\n        std::vector<std::array<Node, 2>> _nodes;\n        std::vector<T>\
    \ _dat;\n    };\n} // namespace suisen\n\n\n\n#line 8 \"test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp\"\
    \n\nint op(int x, int y) {\n    return std::max(x, y);\n}\nint e() {\n    return\
    \ 0;\n}\n\nusing Solution = suisen::RangeContourAggregationQueryOnTree<int, op,\
    \ e>;\n\nstruct NaiveSolution {\n    NaiveSolution(std::vector<std::vector<int>>\
    \ g, std::vector<int> dat) : g(g), dat(dat) {}\n\n    void set(int u, int val)\
    \ {\n        dat[u] = val;\n    }\n    int prod(int k, int dl, int dr) {\n   \
    \     int res = e();\n        auto dfs = [&](auto dfs, int u, int p, int dep)\
    \ -> void {\n            if (dl <= dep and dep < dr) res = op(res, dat[u]);\n\
    \            for (int v : g[u]) {\n                if (v == p) continue;\n   \
    \             dfs(dfs, v, u, dep + 1);\n            }\n        };\n        dfs(dfs,\
    \ k, -1, 0);\n        return res;\n    }\nprivate:\n    std::vector<std::vector<int>>\
    \ g;\n    std::vector<int> dat;\n};\n\nvoid random_queries(int n, int q, Solution\
    \ &t1, NaiveSolution &t2) {\n    auto check = [&](int k, int dl, int dr) {\n \
    \       int sum1 = t1.prod(k, dl, dr);\n        int sum2 = t2.prod(k, dl, dr);\n\
    \        assert(sum1 == sum2);\n    };\n\n    std::mt19937 rng{ std::random_device{}()\
    \ };\n    while (q --> 0) {\n        int qt = rng();\n        if (qt == 1) {\n\
    \            int i = rng() % n;\n            int v = rng() % 10000;\n        \
    \    t1.set(i, v);\n            t2.set(i, v);\n        } else {\n            int\
    \ i = rng() % n;\n            int l = rng() % n;\n            int r = l + rng()\
    \ % (n - l);\n            check(i, l, r);\n        }\n    }\n}\n\n#include <atcoder/dsu>\n\
    \nstd::vector<std::vector<int>> random_tree(int n) {\n    std::mt19937 rng{std::random_device{}()};\n\
    \n    std::vector<std::pair<int, int>> edges;\n    for (int i = 0; i < n; ++i)\
    \ for (int j = 0; j < i; ++j) {\n        edges.emplace_back(i, j);\n    }\n  \
    \  std::shuffle(edges.begin(), edges.end(), rng);\n    \n    std::vector<std::vector<int>>\
    \ g(n);\n\n    atcoder::dsu uf(n);\n    int con = n;\n    while (con > 1) {\n\
    \        auto [u, v] = edges.back();\n        edges.pop_back();\n        if (uf.same(u,\
    \ v)) continue;\n        uf.merge(u, v);\n        --con;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    return g;\n}\n\nvoid test1(int q = 100000)\
    \ {\n    std::vector<std::vector<int>> g{\n        { 1, 8, 16 },       // 0\n\
    \        { 0, 2, 3 },        // 1\n        { 1 },              // 2\n        {\
    \ 1, 4, 7 },        // 3\n        { 3, 5, 6 },        // 4\n        { 4 },   \
    \           // 5\n        { 4 },              // 6\n        { 3 },           \
    \   // 7\n        { 0, 9, 10 },       // 8\n        { 8 },              // 9\n\
    \        { 8, 11, 15 },      // 10\n        { 10, 12, 13, 14 }, // 11\n      \
    \  { 11 },             // 12\n        { 11 },             // 13\n        { 11\
    \ },             // 14\n        { 10 },             // 15\n        { 0, 17, 18,\
    \ 20 },  // 16\n        { 16 },             // 17\n        { 16, 19 },       \
    \  // 18\n        { 18 },             // 19\n        { 16, 21, 24 },     // 20\n\
    \        { 20, 22, 23 },     // 21\n        { 21 },             // 22\n      \
    \  { 21 },             // 23\n        { 20 }              // 24\n    };\n\n  \
    \  const int n = g.size();\n    std::vector<int> dat(n);\n    std::iota(dat.begin(),\
    \ dat.end(), 1);\n\n    suisen::RangeContourAggregationQueryOnTree<int, op, e>\
    \ contour_aggregator(dat);\n    for (int i = 0; i < n; ++i) for (int j : g[i])\
    \ if (i < j) {\n        contour_aggregator.add_edge(i, j);\n    }\n\n    contour_aggregator.build();\n\
    \    NaiveSolution naive(g, dat);\n\n    random_queries(n, q, contour_aggregator,\
    \ naive);\n}\n\nvoid test2(int n = 1000, int q = 10000) {\n    auto g = random_tree(n);\n\
    \    std::vector<int> dat(n);\n    std::iota(dat.begin(), dat.end(), 1);\n\n \
    \   suisen::RangeContourAggregationQueryOnTree<int, op, e> contour_aggregator(dat);\n\
    \    for (int i = 0; i < n; ++i) for (int j : g[i]) if (i < j) {\n        contour_aggregator.add_edge(i,\
    \ j);\n    }\n\n    contour_aggregator.build();\n    NaiveSolution naive(g, dat);\n\
    \n    random_queries(n, q, contour_aggregator, naive);\n}\n\nint main() {\n  \
    \  test1();\n    test2();\n    std::cout << \"Hello World\" << std::endl;\n  \
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <numeric>\n#include <random>\n\n#include \"\
    library/tree/range_contour_aggregation_query_on_tree.hpp\"\n\nint op(int x, int\
    \ y) {\n    return std::max(x, y);\n}\nint e() {\n    return 0;\n}\n\nusing Solution\
    \ = suisen::RangeContourAggregationQueryOnTree<int, op, e>;\n\nstruct NaiveSolution\
    \ {\n    NaiveSolution(std::vector<std::vector<int>> g, std::vector<int> dat)\
    \ : g(g), dat(dat) {}\n\n    void set(int u, int val) {\n        dat[u] = val;\n\
    \    }\n    int prod(int k, int dl, int dr) {\n        int res = e();\n      \
    \  auto dfs = [&](auto dfs, int u, int p, int dep) -> void {\n            if (dl\
    \ <= dep and dep < dr) res = op(res, dat[u]);\n            for (int v : g[u])\
    \ {\n                if (v == p) continue;\n                dfs(dfs, v, u, dep\
    \ + 1);\n            }\n        };\n        dfs(dfs, k, -1, 0);\n        return\
    \ res;\n    }\nprivate:\n    std::vector<std::vector<int>> g;\n    std::vector<int>\
    \ dat;\n};\n\nvoid random_queries(int n, int q, Solution &t1, NaiveSolution &t2)\
    \ {\n    auto check = [&](int k, int dl, int dr) {\n        int sum1 = t1.prod(k,\
    \ dl, dr);\n        int sum2 = t2.prod(k, dl, dr);\n        assert(sum1 == sum2);\n\
    \    };\n\n    std::mt19937 rng{ std::random_device{}() };\n    while (q --> 0)\
    \ {\n        int qt = rng();\n        if (qt == 1) {\n            int i = rng()\
    \ % n;\n            int v = rng() % 10000;\n            t1.set(i, v);\n      \
    \      t2.set(i, v);\n        } else {\n            int i = rng() % n;\n     \
    \       int l = rng() % n;\n            int r = l + rng() % (n - l);\n       \
    \     check(i, l, r);\n        }\n    }\n}\n\n#include <atcoder/dsu>\n\nstd::vector<std::vector<int>>\
    \ random_tree(int n) {\n    std::mt19937 rng{std::random_device{}()};\n\n    std::vector<std::pair<int,\
    \ int>> edges;\n    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) {\n\
    \        edges.emplace_back(i, j);\n    }\n    std::shuffle(edges.begin(), edges.end(),\
    \ rng);\n    \n    std::vector<std::vector<int>> g(n);\n\n    atcoder::dsu uf(n);\n\
    \    int con = n;\n    while (con > 1) {\n        auto [u, v] = edges.back();\n\
    \        edges.pop_back();\n        if (uf.same(u, v)) continue;\n        uf.merge(u,\
    \ v);\n        --con;\n        g[u].push_back(v);\n        g[v].push_back(u);\n\
    \    }\n    return g;\n}\n\nvoid test1(int q = 100000) {\n    std::vector<std::vector<int>>\
    \ g{\n        { 1, 8, 16 },       // 0\n        { 0, 2, 3 },        // 1\n   \
    \     { 1 },              // 2\n        { 1, 4, 7 },        // 3\n        { 3,\
    \ 5, 6 },        // 4\n        { 4 },              // 5\n        { 4 },      \
    \        // 6\n        { 3 },              // 7\n        { 0, 9, 10 },       //\
    \ 8\n        { 8 },              // 9\n        { 8, 11, 15 },      // 10\n   \
    \     { 10, 12, 13, 14 }, // 11\n        { 11 },             // 12\n        {\
    \ 11 },             // 13\n        { 11 },             // 14\n        { 10 },\
    \             // 15\n        { 0, 17, 18, 20 },  // 16\n        { 16 },      \
    \       // 17\n        { 16, 19 },         // 18\n        { 18 },            \
    \ // 19\n        { 16, 21, 24 },     // 20\n        { 20, 22, 23 },     // 21\n\
    \        { 21 },             // 22\n        { 21 },             // 23\n      \
    \  { 20 }              // 24\n    };\n\n    const int n = g.size();\n    std::vector<int>\
    \ dat(n);\n    std::iota(dat.begin(), dat.end(), 1);\n\n    suisen::RangeContourAggregationQueryOnTree<int,\
    \ op, e> contour_aggregator(dat);\n    for (int i = 0; i < n; ++i) for (int j\
    \ : g[i]) if (i < j) {\n        contour_aggregator.add_edge(i, j);\n    }\n\n\
    \    contour_aggregator.build();\n    NaiveSolution naive(g, dat);\n\n    random_queries(n,\
    \ q, contour_aggregator, naive);\n}\n\nvoid test2(int n = 1000, int q = 10000)\
    \ {\n    auto g = random_tree(n);\n    std::vector<int> dat(n);\n    std::iota(dat.begin(),\
    \ dat.end(), 1);\n\n    suisen::RangeContourAggregationQueryOnTree<int, op, e>\
    \ contour_aggregator(dat);\n    for (int i = 0; i < n; ++i) for (int j : g[i])\
    \ if (i < j) {\n        contour_aggregator.add_edge(i, j);\n    }\n\n    contour_aggregator.build();\n\
    \    NaiveSolution naive(g, dat);\n\n    random_queries(n, q, contour_aggregator,\
    \ naive);\n}\n\nint main() {\n    test1();\n    test2();\n    std::cout << \"\
    Hello World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/tree/range_contour_aggregation_query_on_tree.hpp
  isVerificationFile: true
  path: test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
  requiredBy: []
  timestamp: '2022-04-01 18:30:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
- /verify/test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp.html
title: test/src/tree/range_contour_aggregation_query_on_tree/dummy.test.cpp
---
