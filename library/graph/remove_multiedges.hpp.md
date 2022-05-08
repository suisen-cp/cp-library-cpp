---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/graph/block_cut_forest.hpp
    title: Block Cut Forest
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/remove_multiedges.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n#include <cstdint>\n\nnamespace suisen {\n\nvoid remove_multiedges(std::vector<std::vector<int>>\
    \ &g) {\n    std::vector<uint8_t> exists(g.size(), 0);\n    for (auto &vs : g)\
    \ {\n        for (int v : vs) exists[v] = true;\n        vs.erase(std::remove_if(vs.begin(),\
    \ vs.end(), [&](int v) { return not std::exchange(exists[v], false); }), vs.end());\n\
    \    }\n}\n\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_REMOVE_MULTIPLE_EDGES\n#define SUISEN_REMOVE_MULTIPLE_EDGES\n\
    \n#include <algorithm>\n#include <vector>\n#include <cstdint>\n\nnamespace suisen\
    \ {\n\nvoid remove_multiedges(std::vector<std::vector<int>> &g) {\n    std::vector<uint8_t>\
    \ exists(g.size(), 0);\n    for (auto &vs : g) {\n        for (int v : vs) exists[v]\
    \ = true;\n        vs.erase(std::remove_if(vs.begin(), vs.end(), [&](int v) {\
    \ return not std::exchange(exists[v], false); }), vs.end());\n    }\n}\n\n} //\
    \ namespace suisen\n\n\n#endif // SUISEN_REMOVE_MULTIPLE_EDGES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/remove_multiedges.hpp
  requiredBy:
  - library/graph/block_cut_forest.hpp
  timestamp: '2022-05-05 17:37:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/graph/remove_multiedges.hpp
layout: document
title: "\u591A\u91CD\u8FBA\u9664\u53BB"
---
## 多重辺除去

$\Theta(V+E)$ で多重辺を除去する。
