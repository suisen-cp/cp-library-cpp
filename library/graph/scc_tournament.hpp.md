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
  bundledCode: "#line 1 \"library/graph/scc_tournament.hpp\"\n\n\n\n#include <numeric>\n\
    #include <vector>\n\nnamespace suisen {\n    std::vector<std::vector<int>> scc_tournament(const\
    \ std::vector<int> &in_deg) {\n        const int n = in_deg.size();\n        std::vector<std::vector<int>>\
    \ bucket(n);\n        for (int i = 0; i < n; ++i) {\n            int d = in_deg[i];\n\
    \            bucket[d].push_back(i);\n        }\n        std::vector<std::vector<int>>\
    \ scc{{}};\n        int removed_num = 0;\n        long long num = 0;\n       \
    \ long long sum = 0;\n        for (int d = 0; d < n; ++d) for (int v : bucket[d])\
    \ {\n            scc.back().push_back(v);\n            num += 1;\n           \
    \ sum += d - removed_num;\n            if (num * (num - 1) == 2 * sum) {\n   \
    \             removed_num += num;\n                num = 0, sum = 0;\n       \
    \         scc.emplace_back();\n            }\n        }\n        scc.pop_back();\n\
    \        return scc;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_SCC_TOURNAMENT\n#define SUISEN_SCC_TOURNAMENT\n\n#include\
    \ <numeric>\n#include <vector>\n\nnamespace suisen {\n    std::vector<std::vector<int>>\
    \ scc_tournament(const std::vector<int> &in_deg) {\n        const int n = in_deg.size();\n\
    \        std::vector<std::vector<int>> bucket(n);\n        for (int i = 0; i <\
    \ n; ++i) {\n            int d = in_deg[i];\n            bucket[d].push_back(i);\n\
    \        }\n        std::vector<std::vector<int>> scc{{}};\n        int removed_num\
    \ = 0;\n        long long num = 0;\n        long long sum = 0;\n        for (int\
    \ d = 0; d < n; ++d) for (int v : bucket[d]) {\n            scc.back().push_back(v);\n\
    \            num += 1;\n            sum += d - removed_num;\n            if (num\
    \ * (num - 1) == 2 * sum) {\n                removed_num += num;\n           \
    \     num = 0, sum = 0;\n                scc.emplace_back();\n            }\n\
    \        }\n        scc.pop_back();\n        return scc;\n    }\n} // namespace\
    \ suisen\n\n\n#endif // SUISEN_SCC_TOURNAMENT\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/scc_tournament.hpp
  requiredBy: []
  timestamp: '2023-01-02 12:13:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/scc_tournament.hpp
layout: document
title: Scc Tournament
---
## Scc Tournament
