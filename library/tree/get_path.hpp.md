---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/get_path.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    std::vector<int> get_tree_path(const std::vector<std::vector<int>>&\
    \ g, int u, int v) {\n        std::vector<int> res;\n        auto dfs = [&](auto\
    \ dfs, int cur, int par) -> bool {\n            res.push_back(cur);\n        \
    \    if (cur == v) return true;\n            for (int nxt : g[cur]) if (nxt !=\
    \ par and dfs(dfs, nxt, cur)) return true;\n            res.pop_back();\n    \
    \        return false;\n        };\n        dfs(dfs, u, -1);\n        return res;\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_GET_TREE_PATH\n#define SUISEN_GET_TREE_PATH\n\n#include <vector>\n\
    \nnamespace suisen {\n    std::vector<int> get_tree_path(const std::vector<std::vector<int>>&\
    \ g, int u, int v) {\n        std::vector<int> res;\n        auto dfs = [&](auto\
    \ dfs, int cur, int par) -> bool {\n            res.push_back(cur);\n        \
    \    if (cur == v) return true;\n            for (int nxt : g[cur]) if (nxt !=\
    \ par and dfs(dfs, nxt, cur)) return true;\n            res.pop_back();\n    \
    \        return false;\n        };\n        dfs(dfs, u, -1);\n        return res;\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_GET_TREE_PATH\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/get_path.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:36:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/tree/get_path.hpp
layout: document
redirect_from:
- /library/library/tree/get_path.hpp
- /library/library/tree/get_path.hpp.html
title: library/tree/get_path.hpp
---
