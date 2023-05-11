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
  bundledCode: "#line 1 \"library/dp/grid_connectivity.hpp\"\n\n\n\n#include <atcoder/dsu>\n\
    \nnamespace suisen::grid_connectivity {\n    struct Result {\n        std::vector<int>\
    \ next_state;\n        int frontier_comp_num;\n        int forget_comp_num;\n\
    \    };\n    // -1: None\n    // 0, 1, ...: component ID\n    Result transition(const\
    \ std::vector<int> &state, int next_row) {\n        const int m = state.size();\n\
    \        std::vector<int> state2(m, -1);\n        for (int i = 0, nid = -1; i\
    \ < m; ++i) {\n            if ((next_row >> i) & 1) {\n                state2[i]\
    \ = i > 0 and state2[i - 1] >= 0 ? state2[i - 1] : ++nid;\n            }\n   \
    \     }\n        const int V1 = *std::max_element(state.begin(), state.end())\
    \ + 1;\n        const int V2 = *std::max_element(state2.begin(), state2.end())\
    \ + 1;\n        const int V = V1 + V2;\n        atcoder::dsu uf(V);\n        for\
    \ (int i = 0; i < m; ++i) if (state[i] >= 0 and state2[i] >= 0) {\n          \
    \  uf.merge(state[i], V1 + state2[i]);\n        }\n        std::vector<int> comp_ids(V);\n\
    \        std::vector<std::vector<int>> groups = uf.groups();\n        const int\
    \ k = groups.size();\n        for (int comp_id = 0; comp_id < k; ++comp_id) {\n\
    \            for (int v : groups[comp_id]) comp_ids[v] = comp_id;\n        }\n\
    \        std::vector<int> normalize(k, -1);\n        for (int i = 0, nid = 0;\
    \ i < m; ++i) if (state2[i] >= 0) {\n            int comp_id = comp_ids[V1 + state2[i]];\n\
    \            if (normalize[comp_id] == -1) {\n                normalize[comp_id]\
    \ = nid++;\n            }\n            state2[i] = normalize[comp_id];\n     \
    \   }\n        const int frontier_comp_num = *std::max_element(state2.begin(),\
    \ state2.end()) + 1;\n        const int forget_comp_num = k - frontier_comp_num;\n\
    \        return Result{ state2, frontier_comp_num, forget_comp_num };\n    }\n\
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_GRID_CONNECTIVITY\n#define SUISEN_GRID_CONNECTIVITY\n\n#include\
    \ <atcoder/dsu>\n\nnamespace suisen::grid_connectivity {\n    struct Result {\n\
    \        std::vector<int> next_state;\n        int frontier_comp_num;\n      \
    \  int forget_comp_num;\n    };\n    // -1: None\n    // 0, 1, ...: component\
    \ ID\n    Result transition(const std::vector<int> &state, int next_row) {\n \
    \       const int m = state.size();\n        std::vector<int> state2(m, -1);\n\
    \        for (int i = 0, nid = -1; i < m; ++i) {\n            if ((next_row >>\
    \ i) & 1) {\n                state2[i] = i > 0 and state2[i - 1] >= 0 ? state2[i\
    \ - 1] : ++nid;\n            }\n        }\n        const int V1 = *std::max_element(state.begin(),\
    \ state.end()) + 1;\n        const int V2 = *std::max_element(state2.begin(),\
    \ state2.end()) + 1;\n        const int V = V1 + V2;\n        atcoder::dsu uf(V);\n\
    \        for (int i = 0; i < m; ++i) if (state[i] >= 0 and state2[i] >= 0) {\n\
    \            uf.merge(state[i], V1 + state2[i]);\n        }\n        std::vector<int>\
    \ comp_ids(V);\n        std::vector<std::vector<int>> groups = uf.groups();\n\
    \        const int k = groups.size();\n        for (int comp_id = 0; comp_id <\
    \ k; ++comp_id) {\n            for (int v : groups[comp_id]) comp_ids[v] = comp_id;\n\
    \        }\n        std::vector<int> normalize(k, -1);\n        for (int i = 0,\
    \ nid = 0; i < m; ++i) if (state2[i] >= 0) {\n            int comp_id = comp_ids[V1\
    \ + state2[i]];\n            if (normalize[comp_id] == -1) {\n               \
    \ normalize[comp_id] = nid++;\n            }\n            state2[i] = normalize[comp_id];\n\
    \        }\n        const int frontier_comp_num = *std::max_element(state2.begin(),\
    \ state2.end()) + 1;\n        const int forget_comp_num = k - frontier_comp_num;\n\
    \        return Result{ state2, frontier_comp_num, forget_comp_num };\n    }\n\
    } // namespace suisen\n\n\n#endif // SUISEN_GRID_CONNECTIVITY\n"
  dependsOn: []
  isVerificationFile: false
  path: library/dp/grid_connectivity.hpp
  requiredBy: []
  timestamp: '2023-05-11 13:19:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/dp/grid_connectivity.hpp
layout: document
redirect_from:
- /library/library/dp/grid_connectivity.hpp
- /library/library/dp/grid_connectivity.hpp.html
title: library/dp/grid_connectivity.hpp
---
