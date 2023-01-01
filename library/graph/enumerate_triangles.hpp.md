---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/enumerate_triangles/abc258_g.test.cpp
    title: test/src/graph/enumerate_triangles/abc258_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/graph/enumerate_triangles/enumerate_triangles.test.cpp
    title: test/src/graph/enumerate_triangles/enumerate_triangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/graph/enumerate_triangles.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\nnamespace suisen {\n    /**\n     * Type Parameters\n\
    \     * - TriangleConsumer : type of consumer function (int, int, int) -> void\n\
    \     * \n     * Parameters\n     * - std::vector<std::vector<int>> g : simple\
    \ undirected graph\n     * - TriangleConsumer fun\n     * \n     * Requirements\n\
    \     * - v in g[u] <=> u in g[v]\n     * \n     * Complexity\n     * - time :\
    \ O(N + M^{3/2})\n     * - space : O(N + M)\n     */\n    template <typename TriangleConsumer>\n\
    \    void enumerate_triangles(std::vector<std::vector<int>> g, TriangleConsumer\
    \ &&fun) {\n        const int n = g.size();\n        std::vector<int> cnt(n +\
    \ 1);\n        for (int i = 0; i < n; ++i) ++cnt[g[i].size() + 1];\n        for\
    \ (int i = 0; i < n; ++i) cnt[i + 1] += cnt[i];\n        std::vector<int> ord(n),\
    \ idx(n);\n        for (int i = 0; i < n; ++i) ord[idx[i] = cnt[g[i].size()]++]\
    \ = i;\n        for (int i = 0; i < n; ++i) g[i].erase(std::remove_if(g[i].begin(),\
    \ g[i].end(), [&](int j) { return idx[j] < idx[i]; }), g[i].end());\n        std::vector<int8_t>\
    \ exists(n, false);\n        for (int i : ord) {\n            for (int j : g[i])\
    \ exists[j] = true;\n            for (int j : g[i]) for (int k : g[j]) if (exists[k])\
    \ fun(i, j, k);\n            for (int j : g[i]) exists[j] = false;\n        }\n\
    \    }\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_ENUMERATE_TRIANGLES\n#define SUISEN_ENUMERATE_TRIANGLES\n\n\
    #include <algorithm>\n#include <vector>\n\nnamespace suisen {\n    /**\n     *\
    \ Type Parameters\n     * - TriangleConsumer : type of consumer function (int,\
    \ int, int) -> void\n     * \n     * Parameters\n     * - std::vector<std::vector<int>>\
    \ g : simple undirected graph\n     * - TriangleConsumer fun\n     * \n     *\
    \ Requirements\n     * - v in g[u] <=> u in g[v]\n     * \n     * Complexity\n\
    \     * - time : O(N + M^{3/2})\n     * - space : O(N + M)\n     */\n    template\
    \ <typename TriangleConsumer>\n    void enumerate_triangles(std::vector<std::vector<int>>\
    \ g, TriangleConsumer &&fun) {\n        const int n = g.size();\n        std::vector<int>\
    \ cnt(n + 1);\n        for (int i = 0; i < n; ++i) ++cnt[g[i].size() + 1];\n \
    \       for (int i = 0; i < n; ++i) cnt[i + 1] += cnt[i];\n        std::vector<int>\
    \ ord(n), idx(n);\n        for (int i = 0; i < n; ++i) ord[idx[i] = cnt[g[i].size()]++]\
    \ = i;\n        for (int i = 0; i < n; ++i) g[i].erase(std::remove_if(g[i].begin(),\
    \ g[i].end(), [&](int j) { return idx[j] < idx[i]; }), g[i].end());\n        std::vector<int8_t>\
    \ exists(n, false);\n        for (int i : ord) {\n            for (int j : g[i])\
    \ exists[j] = true;\n            for (int j : g[i]) for (int k : g[j]) if (exists[k])\
    \ fun(i, j, k);\n            for (int j : g[i]) exists[j] = false;\n        }\n\
    \    }\n} // namespace suisen\n\n#endif // SUISEN_ENUMERATE_TRIANGLES\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/enumerate_triangles.hpp
  requiredBy: []
  timestamp: '2022-07-05 15:09:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/enumerate_triangles/enumerate_triangles.test.cpp
  - test/src/graph/enumerate_triangles/abc258_g.test.cpp
documentation_of: library/graph/enumerate_triangles.hpp
layout: document
title: "\u4E09\u89D2\u5F62\u5217\u6319"
---
## 三角形列挙