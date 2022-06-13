---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/maximum_independent_set.hpp
    title: "Maximum Independent Set (\u6700\u5927\u72EC\u7ACB\u96C6\u5408)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n\
    \n#include <iostream>\n\n#line 1 \"library/graph/maximum_independent_set.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <deque>\n\
    #line 9 \"library/graph/maximum_independent_set.hpp\"\n#include <vector>\n\nnamespace\
    \ suisen {\n    std::vector<int> maximum_independent_set(const std::vector<std::vector<int>>&\
    \ g) {\n        const int n = g.size();\n        if (n == 0) return {};\n\n  \
    \      const int argmax_deg = std::max_element(g.begin(), g.end(), [](const auto&\
    \ adj1, const auto& adj2) { return adj1.size() < adj2.size(); }) - g.begin();\n\
    \n        if (g[argmax_deg].size() <= 2) {\n            std::vector<int> mis;\n\
    \            std::vector<int> color(n, -1);\n            for (int i = 0; i < n;\
    \ ++i) if (color[i] < 0) {\n                std::vector<int> updated;\n      \
    \          std::array<int, 2> cnt{};\n                color[i] = 0;\n        \
    \        std::deque<int> dq{ i };\n                int p = -1;\n             \
    \   while (dq.size()) {\n                    int u = dq.front();\n           \
    \         dq.pop_front();\n                    updated.push_back(u);\n       \
    \             ++cnt[color[u]];\n                    for (int v : g[u]) {\n   \
    \                     if (color[v] < 0) {\n                            color[v]\
    \ = 1 ^ color[u];\n                            dq.push_back(v);\n            \
    \            } else if (color[u] == color[v]) {\n                            p\
    \ = u;\n                        }\n                    }\n                }\n\
    \                int majority = cnt[1] >= cnt[0];\n                for (int u\
    \ : updated) if (color[u] == majority and u != p) {\n                    mis.push_back(u);\n\
    \                }\n            }\n            return mis;\n        }\n\n    \
    \    std::vector<int> mis;\n        for (const auto& remove_vertices : { std::vector<int>{},\
    \ g[argmax_deg] }) {\n            std::vector<int8_t> rem_flg(n, false);\n   \
    \         rem_flg[argmax_deg] = true;\n            for (const auto& e : remove_vertices)\
    \ {\n                rem_flg[e] = true;\n            }\n            std::vector<int>\
    \ bias(n + 1);\n            for (int i = 0; i < n; ++i) {\n                bias[i\
    \ + 1] = bias[i] + rem_flg[i];\n            }\n            std::vector<int> decomp(n,\
    \ -1);\n            for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n      \
    \          decomp[i - bias[i]] = i;\n            }\n\n            std::vector<std::vector<int>>\
    \ h;\n            h.reserve(g.size() - remove_vertices.size() - 1);\n        \
    \    for (int i = 0; i < n; ++i) if (not rem_flg[i]) {\n                std::vector<int>\
    \ adj;\n                for (int j : g[i]) if (not rem_flg[j]) {\n           \
    \         adj.push_back(j - bias[j]);\n                }\n                h.push_back(std::move(adj));\n\
    \            }\n\n            std::vector<int> vs = maximum_independent_set(h);\n\
    \            for (auto& e : vs) {\n                e = decomp[e];\n          \
    \  }\n            if (remove_vertices.size()) {\n                vs.push_back(argmax_deg);\n\
    \            }\n            if (vs.size() > mis.size()) {\n                mis\
    \ = std::move(vs);\n            }\n        }\n        return mis;\n    }\n} //\
    \ namespace suisen\n\n\n\n#line 6 \"test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp\"\
    \n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\
    \    const auto I = suisen::maximum_independent_set(g);\n    const int k = I.size();\n\
    \    std::cout << k << '\\n';\n    for (int i = 0; i < k; ++i) {\n        std::cout\
    \ << I[i];\n        if (i + 1 != k) std::cout << ' ';\n    }\n    std::cout <<\
    \ '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n\n#include <iostream>\n\n#include \"library/graph/maximum_independent_set.hpp\"\
    \n\nint main() {\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\
    \    const auto I = suisen::maximum_independent_set(g);\n    const int k = I.size();\n\
    \    std::cout << k << '\\n';\n    for (int i = 0; i < k; ++i) {\n        std::cout\
    \ << I[i];\n        if (i + 1 != k) std::cout << ' ';\n    }\n    std::cout <<\
    \ '\\n';\n    return 0;\n}"
  dependsOn:
  - library/graph/maximum_independent_set.hpp
  isVerificationFile: true
  path: test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp
  requiredBy: []
  timestamp: '2022-06-11 19:21:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp
- /verify/test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp.html
title: test/src/graph/maximum_independent_set/maximum_independent_set.test.cpp
---
