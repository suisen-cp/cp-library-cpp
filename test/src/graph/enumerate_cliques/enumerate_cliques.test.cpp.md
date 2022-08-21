---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/graph/enumerate_cliques.hpp
    title: library/graph/enumerate_cliques.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_cliques
    links:
    - https://judge.yosupo.jp/problem/enumerate_cliques
  bundledCode: "#line 1 \"test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_cliques\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/graph/enumerate_cliques.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace suisen {\n    /**\n     * Type Parameters\n   \
    \  * - CliqueComsumer : type of consumer function std::vector<int> -> void\n \
    \    * \n     * Parameters\n     * - std::vector<std::vector<int>> g : simple\
    \ undirected graph\n     * - CliqueComsumer fun\n     * \n     * Requirements\n\
    \     * - v in g[u] <=> u in g[v]\n     * \n     * Complexity\n     * - time :\
    \ O(2^sqrt(2M) * N + (sum of size of cliques)) = O(2^sqrt(2M) * N * sqrt(2M))\
    \ ?\n     * - space : O(N + M)\n     */\n    template <typename CliqueComsumer>\n\
    \    void enumerate_cliques(std::vector<std::vector<int>> g, CliqueComsumer &&fun)\
    \ {\n        const int n = g.size();\n        // sort by degree\n        std::vector<int>\
    \ ord(n), idx(n);\n        std::iota(ord.begin(), ord.end(), 0);\n        std::sort(ord.begin(),\
    \ ord.end(), [&](int i, int j) { return g[i].size() < g[j].size(); });\n     \
    \   for (int i = 0; i < n; ++i) idx[ord[i]] = i;\n        for (int i = 0; i <\
    \ n; ++i) {\n            g[i].erase(std::remove_if(g[i].begin(), g[i].end(), [&](int\
    \ j) { return idx[j] < idx[i]; }), g[i].end());\n            std::sort(g[i].begin(),\
    \ g[i].end(), [&](int x, int y) { return idx[x] < idx[y]; });\n        }\n\n \
    \       std::vector<int> id(n, -1), inv_id(n);\n        std::vector<int> clique(n);\n\
    \        for (int i : ord) {\n            const int l = g[i].size();\n       \
    \     for (int p = 0; p < l; ++p) {\n                int j = g[i][p];\n      \
    \          inv_id[id[j] = p] = j;\n            }\n            std::vector<int>\
    \ st(l);\n            for (int p = 0; p < l; ++p) {\n                st[p] = (1\
    \ << (p + 1)) - 1;\n                for (int j : g[g[i][p]]) if (int k = id[j];\
    \ k >= 0) st[p] |= 1 << k;\n            }\n            std::vector<int>::iterator\
    \ it = clique.begin();\n            *it++ = i;\n            fun(std::vector<int>(clique.begin(),\
    \ it));\n            std::vector<int> intersec(l, (1 << l) - 1);\n           \
    \ for (int c = 1; c < 1 << l; ++c) {\n                const int k = __builtin_ctz(c);\n\
    \                std::fill(intersec.begin(), intersec.begin() + k, intersec[k]\
    \ &= st[k]);\n                *(it -= k)++ = inv_id[k];\n                if ((intersec[0]\
    \ & c) == c) fun(std::vector<int>(clique.begin(), it));\n            }\n     \
    \       for (int j : g[i]) id[j] = -1;\n        }\n    }\n} // namespace suisen\n\
    \n\n#line 9 \"test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<int> x(n);\n    for\
    \ (int &e : x) std::cin >> e;\n\n    std::vector<std::vector<int>> g(n);\n   \
    \ for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\n    mint ans\
    \ = 0;\n    suisen::enumerate_cliques(\n        g,\n        [&ans, &x](const std::vector<int>\
    \ &clique) {\n            mint prod = 1;\n            for (int i : clique) prod\
    \ *= mint::raw(x[i]);\n            ans += prod;\n        }\n    );\n    std::cout\
    \ << ans.val() << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_cliques\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/graph/enumerate_cliques.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<int>\
    \ x(n);\n    for (int &e : x) std::cin >> e;\n\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\n\
    \    mint ans = 0;\n    suisen::enumerate_cliques(\n        g,\n        [&ans,\
    \ &x](const std::vector<int> &clique) {\n            mint prod = 1;\n        \
    \    for (int i : clique) prod *= mint::raw(x[i]);\n            ans += prod;\n\
    \        }\n    );\n    std::cout << ans.val() << '\\n';\n\n    return 0;\n}"
  dependsOn:
  - library/graph/enumerate_cliques.hpp
  isVerificationFile: true
  path: test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp
  requiredBy: []
  timestamp: '2022-08-21 18:24:56+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp
- /verify/test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp.html
title: test/src/graph/enumerate_cliques/enumerate_cliques.test.cpp
---
