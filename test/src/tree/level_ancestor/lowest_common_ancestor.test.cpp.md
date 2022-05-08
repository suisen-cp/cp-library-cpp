---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/level_ancestor.hpp
    title: Level Ancestor
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#line 1 \"library/tree/level_ancestor.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct LevelAncestor {\n        LevelAncestor()\
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
    \    };\n} // namespace suisen\n\n\n\n#line 6 \"test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp\"\
    \nusing suisen::LevelAncestor;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >>\
    \ p;\n        g[p].push_back(i);\n        g[i].push_back(p);\n    }\n\n    LevelAncestor\
    \ la(g);\n\n    auto lca = [&](int u, int v) -> int {\n        int du = la.get_depth(u);\n\
    \        int dv = la.get_depth(v);\n        if (du < dv) {\n            std::swap(u,\
    \ v);\n            std::swap(du, dv);\n        }\n\n        int l = -1, r = dv;\n\
    \        while (r - l > 1) {\n            int k = (l + r) >> 1;\n            (la(u,\
    \ k + (du - dv)) == la(v, k) ? r : l) = k;\n        }\n        return la(v, r);\n\
    \    };\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n        int\
    \ u, v;\n        std::cin >> u >> v;\n        \n        std::cout << lca(u, v)\
    \ << '\\n';\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#include \"library/tree/level_ancestor.hpp\"\nusing suisen::LevelAncestor;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >>\
    \ p;\n        g[p].push_back(i);\n        g[i].push_back(p);\n    }\n\n    LevelAncestor\
    \ la(g);\n\n    auto lca = [&](int u, int v) -> int {\n        int du = la.get_depth(u);\n\
    \        int dv = la.get_depth(v);\n        if (du < dv) {\n            std::swap(u,\
    \ v);\n            std::swap(du, dv);\n        }\n\n        int l = -1, r = dv;\n\
    \        while (r - l > 1) {\n            int k = (l + r) >> 1;\n            (la(u,\
    \ k + (du - dv)) == la(v, k) ? r : l) = k;\n        }\n        return la(v, r);\n\
    \    };\n\n    for (int query_id = 0; query_id < q; ++query_id) {\n        int\
    \ u, v;\n        std::cin >> u >> v;\n        \n        std::cout << lca(u, v)\
    \ << '\\n';\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/tree/level_ancestor.hpp
  isVerificationFile: true
  path: test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2022-05-08 15:48:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
- /verify/test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp.html
title: test/src/tree/level_ancestor/lowest_common_ancestor.test.cpp
---
