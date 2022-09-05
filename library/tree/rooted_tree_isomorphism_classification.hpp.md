---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/tree/rooted_tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
    title: test/src/tree/rooted_tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/rooted_tree_isomorphism_classification.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <map>\n#include <utility>\n\
    #include <vector>\n\nnamespace suisen {\n    // @returns (number of distinct (rooted)\
    \ subtrees, id of subtrees)\n    std::pair<int, std::vector<int>> tree_isomorphism_classification(const\
    \ std::vector<std::vector<int>>& g, int root) {\n        static constexpr int\
    \ None = -1;\n        const int n = g.size();\n\n        std::vector<int> ids(n);\n\
    \n        std::vector<int> mp1(n, None);\n        std::vector<std::map<std::vector<int>,\
    \ int>> mps(n);\n        int next_id = 0;\n\n        std::vector<int> stk(n),\
    \ par(n, None);\n        auto stk_it = stk.begin();\n        *stk_it++ = root;\n\
    \        while (stk_it != stk.begin()) {\n            int u = *--stk_it;\n   \
    \         for (int v : g[u]) if (v != par[u]) par[v] = u, *stk_it++ = v;\n   \
    \         for (const int par_of_nxt = stk_it != stk.begin() ? par[*std::prev(stk_it)]\
    \ : None; u != par_of_nxt; u = par[u]) {\n                // dfs post order\n\
    \                std::vector<int> ch_ids;\n                ch_ids.reserve(g[u].size());\n\
    \                for (int v : g[u]) if (v != par[u]) ch_ids.push_back(ids[v]);\n\
    \                if (const int siz = ch_ids.size(); siz == 1) {\n            \
    \        int ch = ch_ids[0];\n                    ids[u] = mp1[ch] != None ? mp1[ch]\
    \ : mp1[ch] = next_id++;\n                } else {\n                    std::sort(ch_ids.begin(),\
    \ ch_ids.end());\n                    auto [it, inserted] = mps[siz].try_emplace(std::move(ch_ids),\
    \ next_id);\n                    next_id += inserted;\n                    ids[u]\
    \ = it->second;\n                }\n            }\n        }\n        return {\
    \ next_id, ids };\n    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n#define SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n\
    \n#include <algorithm>\n#include <cassert>\n#include <map>\n#include <utility>\n\
    #include <vector>\n\nnamespace suisen {\n    // @returns (number of distinct (rooted)\
    \ subtrees, id of subtrees)\n    std::pair<int, std::vector<int>> tree_isomorphism_classification(const\
    \ std::vector<std::vector<int>>& g, int root) {\n        static constexpr int\
    \ None = -1;\n        const int n = g.size();\n\n        std::vector<int> ids(n);\n\
    \n        std::vector<int> mp1(n, None);\n        std::vector<std::map<std::vector<int>,\
    \ int>> mps(n);\n        int next_id = 0;\n\n        std::vector<int> stk(n),\
    \ par(n, None);\n        auto stk_it = stk.begin();\n        *stk_it++ = root;\n\
    \        while (stk_it != stk.begin()) {\n            int u = *--stk_it;\n   \
    \         for (int v : g[u]) if (v != par[u]) par[v] = u, *stk_it++ = v;\n   \
    \         for (const int par_of_nxt = stk_it != stk.begin() ? par[*std::prev(stk_it)]\
    \ : None; u != par_of_nxt; u = par[u]) {\n                // dfs post order\n\
    \                std::vector<int> ch_ids;\n                ch_ids.reserve(g[u].size());\n\
    \                for (int v : g[u]) if (v != par[u]) ch_ids.push_back(ids[v]);\n\
    \                if (const int siz = ch_ids.size(); siz == 1) {\n            \
    \        int ch = ch_ids[0];\n                    ids[u] = mp1[ch] != None ? mp1[ch]\
    \ : mp1[ch] = next_id++;\n                } else {\n                    std::sort(ch_ids.begin(),\
    \ ch_ids.end());\n                    auto [it, inserted] = mps[siz].try_emplace(std::move(ch_ids),\
    \ next_id);\n                    next_id += inserted;\n                    ids[u]\
    \ = it->second;\n                }\n            }\n        }\n        return {\
    \ next_id, ids };\n    }\n} // namespace suisen\n\n#endif // SUISEN_ROOTED_TREE_ISOMORPHISM_CLASSIFICATION\n"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/rooted_tree_isomorphism_classification.hpp
  requiredBy: []
  timestamp: '2022-09-05 23:58:08+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/tree/rooted_tree_isomorphism_classification/rooted_tree_isomorphism_classification.test.cpp
documentation_of: library/tree/rooted_tree_isomorphism_classification.hpp
layout: document
redirect_from:
- /library/library/tree/rooted_tree_isomorphism_classification.hpp
- /library/library/tree/rooted_tree_isomorphism_classification.hpp.html
title: library/tree/rooted_tree_isomorphism_classification.hpp
---
