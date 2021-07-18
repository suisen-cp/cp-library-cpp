---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/euler_tour.hpp
    title: library/tree/euler_tour.hpp
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
  bundledCode: "#line 1 \"test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    #include <vector>\n#include <library/tree/euler_tour.hpp>\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n        g[i].push_back(p);\n\
    \        g[p].push_back(i);\n    }\n    suisen::EulerTour et(g);\n    for (int\
    \ i = 0; i < q; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n     \
    \   std::cout << et.lca(u, v) << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    #include <vector>\n#include <library/tree/euler_tour.hpp>\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n,\
    \ q;\n    std::cin >> n >> q;\n    std::vector<std::vector<int>> g(n);\n    for\
    \ (int i = 1; i < n; ++i) {\n        int p;\n        std::cin >> p;\n        g[i].push_back(p);\n\
    \        g[p].push_back(i);\n    }\n    suisen::EulerTour et(g);\n    for (int\
    \ i = 0; i < q; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n     \
    \   std::cout << et.lca(u, v) << '\\n';\n    }\n    return 0;\n}\n"
  dependsOn:
  - library/tree/euler_tour.hpp
  isVerificationFile: true
  path: test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2021-07-18 15:28:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
- /verify/test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp.html
title: test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
---
