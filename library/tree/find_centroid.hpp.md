---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/tree/tree_isomorphism_classification.hpp
    title: Tree Isomorphism Classification
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
    title: test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/find_centroid.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ GraphType>\n    std::vector<int> find_centroids(const GraphType& g) {\n    \
    \    const int n = g.size();\n        std::vector<int> res;\n        std::vector<int8_t>\
    \ is_centroid(n, true);\n        std::vector<int> eid(n), par(n, -1), sub(n, 1);\n\
    \        for (int cur = 0; cur >= 0;) {\n            if (eid[cur] == int(g[cur].size()))\
    \ {\n                if (par[cur] >= 0) {\n                    sub[par[cur]] +=\
    \ sub[cur];\n                    is_centroid[par[cur]] &= 2 * sub[cur] <= n;\n\
    \                }\n                if (is_centroid[cur] and 2 * sub[cur] >= n)\
    \ {\n                    res.push_back(cur);\n                }\n            \
    \    cur = par[cur];\n            } else {\n                int nxt = g[cur][eid[cur]++];\n\
    \                if (nxt == par[cur]) continue;\n                par[nxt] = cur;\n\
    \                cur = nxt;\n            }\n        }\n        assert(res.size()\
    \ == 1 or res.size() == 2);\n        return res;\n    }\n} // namespace suisen\n\
    \n\n\n"
  code: "#ifndef SUISEN_FIND_CENTROID\n#define SUISEN_FIND_CENTROID\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ GraphType>\n    std::vector<int> find_centroids(const GraphType& g) {\n    \
    \    const int n = g.size();\n        std::vector<int> res;\n        std::vector<int8_t>\
    \ is_centroid(n, true);\n        std::vector<int> eid(n), par(n, -1), sub(n, 1);\n\
    \        for (int cur = 0; cur >= 0;) {\n            if (eid[cur] == int(g[cur].size()))\
    \ {\n                if (par[cur] >= 0) {\n                    sub[par[cur]] +=\
    \ sub[cur];\n                    is_centroid[par[cur]] &= 2 * sub[cur] <= n;\n\
    \                }\n                if (is_centroid[cur] and 2 * sub[cur] >= n)\
    \ {\n                    res.push_back(cur);\n                }\n            \
    \    cur = par[cur];\n            } else {\n                int nxt = g[cur][eid[cur]++];\n\
    \                if (nxt == par[cur]) continue;\n                par[nxt] = cur;\n\
    \                cur = nxt;\n            }\n        }\n        assert(res.size()\
    \ == 1 or res.size() == 2);\n        return res;\n    }\n} // namespace suisen\n\
    \n\n#endif // SUISEN_FIND_CENTROID\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/find_centroid.hpp
  requiredBy:
  - library/tree/tree_isomorphism_classification.hpp
  timestamp: '2022-10-23 23:59:03+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/tree/tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
documentation_of: library/tree/find_centroid.hpp
layout: document
title: Find Centroid
---
## Find Centroid

木の重心を $O(n)$ 時間で列挙する。
