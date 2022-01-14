---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/bipartite_matching.hpp
    title: library/graph/bipartite_matching.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"test/src/graph/bipartite_matching/bipartite_matching.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/bipartite_matching.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <deque>\n#include <random>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct BipartiteMatching {\n        BipartiteMatching()\
    \ {}\n        BipartiteMatching(int n, int m) : _n(n), _m(m), _to_r(_n, None),\
    \ _to_l(_m, None), _g(n + m) {}\n\n        void add_edge(int fr, int to) {\n \
    \           _g[fr].push_back(to);\n            _f = -1;\n        }\n\n       \
    \ template <bool shuffle = true>\n        int solve() {\n            static std::mt19937\
    \ rng(std::random_device{}());\n            if constexpr (shuffle) for (auto &adj\
    \ : _g) std::shuffle(adj.begin(), adj.end(), rng);\n\n            std::vector<int8_t>\
    \ vis(_n, false);\n        \n            auto dfs = [&, this](auto dfs, int u)\
    \ -> bool {\n                if (std::exchange(vis[u], true)) return false;\n\
    \                for (int v : _g[u]) if (_to_l[v] == None) {\n               \
    \     _to_r[u] = v, _to_l[v] = u;\n                    return true;\n        \
    \        }\n                for (int v : _g[u]) if (dfs(dfs, _to_l[v])) {\n  \
    \                  _to_r[u] = v, _to_l[v] = u;\n                    return true;\n\
    \                }\n                return false;\n            };\n    \n    \
    \        for (bool upd = true; std::exchange(upd, false);) {\n               \
    \ vis.assign(_n + _m, false);\n                for (int i = 0; i < _n; ++i) if\
    \ (_to_r[i] == None) upd |= dfs(dfs, i);\n            }\n\n            return\
    \ _f = _n - std::count(_to_r.begin(), _to_r.end(), None);\n        }\n\n     \
    \   std::vector<std::pair<int, int>> max_matching() {\n            if (_f < 0)\
    \ _f = solve();\n            std::vector<std::pair<int, int>> res;\n         \
    \   res.reserve(_f);\n            for (int i = 0; i < _n; ++i) if (_to_r[i] !=\
    \ None) res.emplace_back(i, _to_r[i]);\n            return res;\n        }\n\n\
    \        std::vector<std::pair<int, int>> min_edge_cover() {\n            auto\
    \ res = max_matching();\n            std::vector<bool> vl(_n, false), vr(_n, false);\n\
    \            for (const auto &[u, v] : res) vl[u] = vr[v] = true;\n          \
    \  for (int u = 0; u < _n; ++u) {\n                for (int v : _g[u]) if (not\
    \ (vl[u] and vr[v])) {\n                    vl[u] = vr[v] = true;\n          \
    \          res.emplace_back(u, v);\n                }\n            }\n       \
    \     return res;\n        }\n\n        std::vector<int> min_vertex_cover() {\n\
    \            if (_f < 0) _f = solve();\n            std::vector<std::vector<int>>\
    \ g(_n + _m);\n            std::vector<bool> cl(_n, true), cr(_m, false);\n  \
    \          for (int u = 0; u < _n; ++u) {\n                for (int v : _g[u]){\n\
    \                    if (_to_r[u] == v) {\n                        g[v + _n].push_back(u);\n\
    \                        cl[u] = false;\n                    } else {\n      \
    \                  g[u].push_back(v + _n);\n                    }\n          \
    \      }\n            }\n            std::vector<bool> vis(_n + _m, false);\n\
    \            std::deque<int> dq;\n            for (int i = 0; i < _n; ++i) if\
    \ (cl[i]) {\n                dq.push_back(i);\n                vis[i] = true;\n\
    \            }\n            while (dq.size()) {\n                int u = dq.front();\n\
    \                dq.pop_front();\n                for (int v : g[u]) {\n     \
    \               if (vis[v]) continue;\n                    (v < _n ? cl[v] : cr[v\
    \ - _n]) = true;\n                    vis[v] = true;\n                    dq.push_back(v);\n\
    \                }\n            }\n            std::vector<int> res;\n       \
    \     for (int i = 0; i < _n; ++i) if (not cl[i]) res.push_back(i);\n        \
    \    for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n + i);\n        \
    \    return res;\n        }\n        \n        std::vector<int> max_independent_set()\
    \ {\n            std::vector<bool> use(_n + _m, true);\n            for (int v\
    \ : min_vertex_cover()) use[v] = false;\n            std::vector<int> res;\n \
    \           for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);\n\
    \            return res;\n        }\n\n    private:\n        static constexpr\
    \ int None = -1;\n\n        int _n, _m;\n        std::vector<int> _to_r, _to_l;\n\
    \        std::vector<std::vector<int>> _g;\n        int _f = 0;\n    };\n    \n\
    } // namespace suisen\n\n\n\n#line 6 \"test/src/graph/bipartite_matching/bipartite_matching.test.cpp\"\
    \nusing suisen::BipartiteMatching;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, k;\n    std::cin >> n >> m >> k;\n\
    \    BipartiteMatching matching(n, m);\n    while (k --> 0) {\n        int u,\
    \ v;\n        std::cin >> u >> v;\n        matching.add_edge(u, v);\n    }\n \
    \   auto ans = matching.max_matching();\n    std::cout << ans.size() << '\\n';\n\
    \    for (const auto &[u, v] : ans) {\n        std::cout << u << ' ' << v << '\\\
    n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n\
    #include <iostream>\n\n#include \"library/graph/bipartite_matching.hpp\"\nusing\
    \ suisen::BipartiteMatching;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m, k;\n    std::cin >> n >> m >> k;\n\
    \    BipartiteMatching matching(n, m);\n    while (k --> 0) {\n        int u,\
    \ v;\n        std::cin >> u >> v;\n        matching.add_edge(u, v);\n    }\n \
    \   auto ans = matching.max_matching();\n    std::cout << ans.size() << '\\n';\n\
    \    for (const auto &[u, v] : ans) {\n        std::cout << u << ' ' << v << '\\\
    n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/graph/bipartite_matching.hpp
  isVerificationFile: true
  path: test/src/graph/bipartite_matching/bipartite_matching.test.cpp
  requiredBy: []
  timestamp: '2022-01-15 05:46:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/bipartite_matching/bipartite_matching.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/bipartite_matching/bipartite_matching.test.cpp
- /verify/test/src/graph/bipartite_matching/bipartite_matching.test.cpp.html
title: test/src/graph/bipartite_matching/bipartite_matching.test.cpp
---
