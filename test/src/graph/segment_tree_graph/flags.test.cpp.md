---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/segment_tree_graph.hpp
    title: library/graph/segment_tree_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc069/tasks/arc069_f
    links:
    - https://atcoder.jp/contests/arc069/tasks/arc069_f
  bundledCode: "#line 1 \"test/src/graph/segment_tree_graph/flags.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/arc069/tasks/arc069_f\"\n\n#include <algorithm>\n\
    #include <iostream>\n#include <numeric>\n#include <atcoder/twosat>\n\n#line 1\
    \ \"library/graph/segment_tree_graph.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <type_traits>\n#include <vector>\n\nnamespace suisen {\n\nclass SegmentTreeGraph\
    \ {\n    public:\n        struct SegmentNode { const int order_id, l, r; };\n\n\
    \        SegmentTreeGraph() : SegmentTreeGraph(0) {}\n        SegmentTreeGraph(int\
    \ n) : n(n), next_id(n), ceil_log2(n + 2, 0), is_invalid_node(n, false) {\n  \
    \          for (int i = 1, l = 0; i <= n + 1; ++i) {\n                ceil_log2[i]\
    \ = l;\n                l += (i & -i) == i;\n            }\n            if (n)\
    \ {\n                for (int m = n / (-n & n) >> 1;; m >>= 1) {\n           \
    \         is_invalid_node[m] = true;\n                    if (m == 0) break;\n\
    \                }\n            }\n        }\n\n        int size() const {\n \
    \           return next_id;\n        }\n\n        int add_order(const std::vector<int>\
    \ &p) {\n            assert(int(p.size()) == n);\n            std::vector<int>\
    \ seg(2 * n, -1);\n            for (int i = 0; i < n; ++i) seg[n + i] = p[i];\n\
    \            for (int i = 1; i < n; ++i) seg[i] = next_id++;\n            segs.push_back(std::move(seg));\n\
    \            return segs.size() - 1;\n        }\n        int add_order_identity()\
    \ {\n            std::vector<int> p(n);\n            for (int i = 0; i < n; ++i)\
    \ p[i] = i;\n            return add_order(p);\n        }\n\n        bool is_segment_node(int\
    \ node_id) const {\n            return node_id >= n;\n        }\n\n        SegmentNode\
    \ get_segment_node(int node_id) const {\n            assert(node_id >= n);\n \
    \           node_id -= n;\n            int order_id = node_id / (n - 1);\n   \
    \         int k = node_id - order_id * (n - 1) + 1;\n            int l = k <<\
    \ ceil_log2[(n + k - 1) / k], r = (k + 1) << ceil_log2[n / (k + 1) + 1];\n   \
    \         return SegmentNode { order_id, l - n, r - n };\n        }\n        SegmentNode\
    \ operator[](int node_id) const {\n            return get_segment_node(node_id);\n\
    \        }\n\n        // add_edge(parent, child_l, child_r)\n        template\
    \ <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge, int, int, int>,\
    \ std::nullptr_t> = nullptr>\n        void add_edges_to_children(AddEdge add_edge)\
    \ {\n            for (const auto &seg : segs) {\n                for (int i =\
    \ 1; i < n; ++i) {\n                    if (is_invalid_node[i]) continue;\n  \
    \                  add_edge(seg[i], seg[i * 2 + 0], seg[i * 2 + 1]);\n       \
    \         }\n            }\n        }\n        // add_edge(parent, child)\n  \
    \      template <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge,\
    \ int, int>, std::nullptr_t> = nullptr>\n        void add_edges_to_children(AddEdge\
    \ add_edge) {\n            for (const auto &seg : segs) {\n                for\
    \ (int i = 1; i < n; ++i) {\n                    if (is_invalid_node[i]) continue;\n\
    \                    add_edge(seg[i], seg[i * 2 + 0]);\n                    add_edge(seg[i],\
    \ seg[i * 2 + 1]);\n                }\n            }\n        }\n\n        //\
    \ add_edge(from, to)\n        template <typename AddEdge, std::enable_if_t<std::is_invocable_v<AddEdge,\
    \ int, int>, std::nullptr_t> = nullptr>\n        void add_edge(int from, SegmentNode\
    \ to, AddEdge add_edge_func) {\n            const auto &seg = segs[to.order_id];\n\
    \            for (int lk = to.l + n, rk = to.r + n; lk < rk; lk >>= 1, rk >>=\
    \ 1) {\n                if (lk & 1) add_edge_func(from, seg[lk++]);\n        \
    \        if (rk & 1) add_edge_func(from, seg[--rk]);\n            }\n        }\n\
    \n    private:\n        int n;\n        int next_id;\n        std::vector<int>\
    \ ceil_log2;\n        std::vector<char> is_invalid_node;\n        std::vector<std::vector<int>>\
    \ segs;\n};\n\n} // namespace suisen\n\n\n\n#line 9 \"test/src/graph/segment_tree_graph/flags.test.cpp\"\
    \nusing namespace suisen;\n\nint main() {\n    int n;\n    std::cin >> n;\n\n\
    \    std::vector xys(2, std::vector<long long>(n));\n    for (int i = 0; i < n;\
    \ ++i) {\n        std::cin >> xys[0][i] >> xys[1][i];\n    }\n\n    SegmentTreeGraph\
    \ g(n);\n\n    std::vector ps(2, std::vector<int>(n));\n    for (int t = 0; t\
    \ < 2; ++t) {\n        std::iota(ps[t].begin(), ps[t].end(), 0);\n        std::sort(ps[t].begin(),\
    \ ps[t].end(), [&](int i, int j) { return xys[t][i] < xys[t][j]; });\n       \
    \ g.add_order(ps[t]);\n    }\n\n    auto get_range = [&](int order_id, long long\
    \ c, long long d) -> std::pair<int, int> {\n        const auto &p = ps[order_id];\n\
    \        const auto &a = xys[order_id];\n        auto bs = [&](long long x) {\n\
    \            int l = -1, r = n;\n            while (r - l > 1) {\n           \
    \     int m = (l + r) >> 1;\n                (a[p[m]] < x ? l : r) = m;\n    \
    \        }\n            return r;\n        };\n        return { bs(c - d + 1),\
    \ bs(c + d) };\n    };\n\n    auto check = [&](const long long d) -> bool {\n\
    \        atcoder::two_sat sat(g.size());\n\n        g.add_edges_to_children(\n\
    \            [&](int p, int c) {\n                assert(g.is_segment_node(p));\n\
    \                bool b = g.get_segment_node(p).order_id == 0;\n             \
    \   sat.add_clause(c, b, p, not b);\n            }\n        );\n\n        for\
    \ (int i = 0; i < n; ++i) {\n            for (auto jk : std::vector<std::pair<int,\
    \ int>> { { 0, 0 }, { 0, 1 }, { 1, 1 } }) {\n                const int j = jk.first,\
    \ k = jk.second, p = ps[j][i];\n                auto [l, r] = get_range(k, xys[j][p],\
    \ d);\n                if (j == k) r = i;\n                g.add_edge(p, { k,\
    \ l, r }, [&](int fr, int to) { sat.add_clause(fr, j ^ 1, to, k ^ 1); });\n  \
    \          }\n        }\n\n        return sat.satisfiable();\n    };\n\n    long\
    \ long l = 0, r = 1000000001;\n    while (r - l > 1) {\n        long long d =\
    \ (l + r) >> 1;\n        (check(d) ? l : r) = d;\n    }\n    std::cout << l <<\
    \ std::endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc069/tasks/arc069_f\"\n\n\
    #include <algorithm>\n#include <iostream>\n#include <numeric>\n#include <atcoder/twosat>\n\
    \n#include \"library/graph/segment_tree_graph.hpp\"\nusing namespace suisen;\n\
    \nint main() {\n    int n;\n    std::cin >> n;\n\n    std::vector xys(2, std::vector<long\
    \ long>(n));\n    for (int i = 0; i < n; ++i) {\n        std::cin >> xys[0][i]\
    \ >> xys[1][i];\n    }\n\n    SegmentTreeGraph g(n);\n\n    std::vector ps(2,\
    \ std::vector<int>(n));\n    for (int t = 0; t < 2; ++t) {\n        std::iota(ps[t].begin(),\
    \ ps[t].end(), 0);\n        std::sort(ps[t].begin(), ps[t].end(), [&](int i, int\
    \ j) { return xys[t][i] < xys[t][j]; });\n        g.add_order(ps[t]);\n    }\n\
    \n    auto get_range = [&](int order_id, long long c, long long d) -> std::pair<int,\
    \ int> {\n        const auto &p = ps[order_id];\n        const auto &a = xys[order_id];\n\
    \        auto bs = [&](long long x) {\n            int l = -1, r = n;\n      \
    \      while (r - l > 1) {\n                int m = (l + r) >> 1;\n          \
    \      (a[p[m]] < x ? l : r) = m;\n            }\n            return r;\n    \
    \    };\n        return { bs(c - d + 1), bs(c + d) };\n    };\n\n    auto check\
    \ = [&](const long long d) -> bool {\n        atcoder::two_sat sat(g.size());\n\
    \n        g.add_edges_to_children(\n            [&](int p, int c) {\n        \
    \        assert(g.is_segment_node(p));\n                bool b = g.get_segment_node(p).order_id\
    \ == 0;\n                sat.add_clause(c, b, p, not b);\n            }\n    \
    \    );\n\n        for (int i = 0; i < n; ++i) {\n            for (auto jk : std::vector<std::pair<int,\
    \ int>> { { 0, 0 }, { 0, 1 }, { 1, 1 } }) {\n                const int j = jk.first,\
    \ k = jk.second, p = ps[j][i];\n                auto [l, r] = get_range(k, xys[j][p],\
    \ d);\n                if (j == k) r = i;\n                g.add_edge(p, { k,\
    \ l, r }, [&](int fr, int to) { sat.add_clause(fr, j ^ 1, to, k ^ 1); });\n  \
    \          }\n        }\n\n        return sat.satisfiable();\n    };\n\n    long\
    \ long l = 0, r = 1000000001;\n    while (r - l > 1) {\n        long long d =\
    \ (l + r) >> 1;\n        (check(d) ? l : r) = d;\n    }\n    std::cout << l <<\
    \ std::endl;\n\n    return 0;\n}"
  dependsOn:
  - library/graph/segment_tree_graph.hpp
  isVerificationFile: true
  path: test/src/graph/segment_tree_graph/flags.test.cpp
  requiredBy: []
  timestamp: '2021-09-21 22:18:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/segment_tree_graph/flags.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/segment_tree_graph/flags.test.cpp
- /verify/test/src/graph/segment_tree_graph/flags.test.cpp.html
title: test/src/graph/segment_tree_graph/flags.test.cpp
---
