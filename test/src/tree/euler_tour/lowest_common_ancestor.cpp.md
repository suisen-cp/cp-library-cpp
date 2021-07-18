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
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/src/tree/euler_tour/lowest_common_ancestor.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
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
    \   std::cout << et.lca(u, v) << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/tree/euler_tour.hpp
  isVerificationFile: false
  path: test/src/tree/euler_tour/lowest_common_ancestor.cpp
  requiredBy: []
  timestamp: '2021-07-18 15:28:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/src/tree/euler_tour/lowest_common_ancestor.cpp
layout: document
redirect_from:
- /library/test/src/tree/euler_tour/lowest_common_ancestor.cpp
- /library/test/src/tree/euler_tour/lowest_common_ancestor.cpp.html
title: test/src/tree/euler_tour/lowest_common_ancestor.cpp
---
