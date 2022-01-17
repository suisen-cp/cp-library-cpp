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
  bundledCode: "#line 1 \"library/graph/remove_multiedges.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n#include <cstdint>\n\nnamespace suisen {\n\nvoid remove_multiedges(std::vector<std::vector<int>>\
    \ &g) {\n    std::vector<uint8_t> exists(g.size(), 0);\n    auto rem_pred = [&](int\
    \ v) {\n        bool cond = not exists[v];\n        exists[v] = false;\n     \
    \   return cond;\n    };\n    for (auto &vs : g) {\n        for (int v : vs) exists[v]\
    \ = true;\n        vs.erase(std::remove_if(vs.begin(), vs.end(), rem_pred), vs.end());\n\
    \    }\n}\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_REMOVE_MULTIPLE_EDGES\n#define SUISEN_REMOVE_MULTIPLE_EDGES\n\
    \n#include <algorithm>\n#include <vector>\n#include <cstdint>\n\nnamespace suisen\
    \ {\n\nvoid remove_multiedges(std::vector<std::vector<int>> &g) {\n    std::vector<uint8_t>\
    \ exists(g.size(), 0);\n    auto rem_pred = [&](int v) {\n        bool cond =\
    \ not exists[v];\n        exists[v] = false;\n        return cond;\n    };\n \
    \   for (auto &vs : g) {\n        for (int v : vs) exists[v] = true;\n       \
    \ vs.erase(std::remove_if(vs.begin(), vs.end(), rem_pred), vs.end());\n    }\n\
    }\n\n} // namespace suisen\n\n\n#endif // SUISEN_REMOVE_MULTIPLE_EDGES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/remove_multiedges.hpp
  requiredBy: []
  timestamp: '2021-09-09 21:18:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/remove_multiedges.hpp
layout: document
title: Remove Multiedges
---
## Remove Multiedges