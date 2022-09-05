---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/enumerate_triangles.hpp
    title: "\u4E09\u89D2\u5F62\u5217\u6319"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc258/tasks/abc258_g
    links:
    - https://atcoder.jp/contests/abc258/tasks/abc258_g
  bundledCode: "#line 1 \"test/src/graph/enumerate_triangles/abc258_g.test.cpp\"\n\
    #define PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_g\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/enumerate_triangles.hpp\"\n\n\n\n#include\
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
    \    }\n} // namespace suisen\n\n\n#line 6 \"test/src/graph/enumerate_triangles/abc258_g.test.cpp\"\
    \n\nint main() {\n    int n;\n    std::cin >> n;\n    \n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int u = 0; u < n; ++u) {\n        std::string s;\n        std::cin\
    \ >> s;\n        for (int v = 0; v < n; ++v) if (s[v] == '1') {\n            g[u].push_back(v);\n\
    \        }\n    }\n\n    long long ans = 0;\n    suisen::enumerate_triangles(g,\
    \ [&ans](int, int, int) { ++ans; });\n    std::cout << ans << std::endl;\n\n \
    \   return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_g\"\n\n\
    #include <iostream>\n\n#include \"library/graph/enumerate_triangles.hpp\"\n\n\
    int main() {\n    int n;\n    std::cin >> n;\n    \n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int u = 0; u < n; ++u) {\n        std::string s;\n        std::cin\
    \ >> s;\n        for (int v = 0; v < n; ++v) if (s[v] == '1') {\n            g[u].push_back(v);\n\
    \        }\n    }\n\n    long long ans = 0;\n    suisen::enumerate_triangles(g,\
    \ [&ans](int, int, int) { ++ans; });\n    std::cout << ans << std::endl;\n\n \
    \   return 0;\n}"
  dependsOn:
  - library/graph/enumerate_triangles.hpp
  isVerificationFile: true
  path: test/src/graph/enumerate_triangles/abc258_g.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 15:07:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/enumerate_triangles/abc258_g.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/enumerate_triangles/abc258_g.test.cpp
- /verify/test/src/graph/enumerate_triangles/abc258_g.test.cpp.html
title: test/src/graph/enumerate_triangles/abc258_g.test.cpp
---
