---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/union_find/merge_history_forest.hpp
    title: Merge History Forest
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc235/tasks/abc235_h
    links:
    - https://atcoder.jp/contests/abc235/tasks/abc235_h
  bundledCode: "#line 1 \"test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc235/tasks/abc235_h\"\n\n#include\
    \ <iostream>\n#include <map>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include <numeric>\n\
    #include <optional>\n#include <queue>\n\n#line 1 \"library/datastructure/union_find/merge_history_forest.hpp\"\
    \n\n\n\n#line 8 \"library/datastructure/union_find/merge_history_forest.hpp\"\n\
    \nnamespace suisen {\n    struct MergeHistoryForest : public atcoder::dsu {\n\
    \        using base_type = atcoder::dsu;\n\n        MergeHistoryForest() : MergeHistoryForest(0)\
    \ {}\n        explicit MergeHistoryForest(int n) : base_type(n), _g(n), _root(n)\
    \ {\n            std::iota(_root.begin(), _root.end(), 0);\n        }\n\n    \
    \    int node_num() const { return _g.size(); }\n\n        const auto& get_forest()\
    \ const { return _g; }\n\n        int tree_root(int i) { return _root[leader(i)];\
    \ }\n\n        std::vector<int> tree_roots() {\n            const int n = _root.size();\n\
    \            std::vector<int> roots;\n            for (int i = 0; i < n; ++i)\
    \ if (leader(i) == i) roots.push_back(_root[i]);\n            return roots;\n\
    \        }\n \n        void merge(int u, int v) {\n            const int ru =\
    \ leader(u), rv = leader(v);\n            if (ru == rv) return;\n            _g.push_back({\
    \ _root[ru], _root[rv] });\n            _root[base_type::merge(ru, rv)] = _g.size()\
    \ - 1;\n        }\n        void merge(const std::pair<int, int> &edge) { merge(edge.first,\
    \ edge.second); }\n\n        void merge_simultaneously(const std::vector<std::pair<int,\
    \ int>> &edges) {\n            std::vector<int> vs;\n            for (const auto\
    \ &[u, v] : edges) {\n                const int ru = leader(u), rv = leader(v);\n\
    \                if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ dfs(s, _g.emplace_back()), _root[s] = _g.size() - 1;\n        }\n\n    private:\n\
    \        std::vector<std::vector<int>> _g;\n        std::vector<int> _root;\n\n\
    \        void dfs(int u, std::vector<int> &con) {\n            for (int v : _g[u])\
    \ dfs(v, con), _g[v].shrink_to_fit();\n            con.push_back(_root[u]), _g[u].clear();\n\
    \        }\n    };\n} // namespace suisen\n\n\n\n#line 17 \"test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp\"\
    \nusing suisen::MergeHistoryForest;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n \n    int n, m, k;\n    std::cin >> n >> m >> k;\n\
    \ \n    std::map<int, std::vector<std::pair<int, int>>> edges;\n    while (m -->\
    \ 0) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n        edges[w].emplace_back(u\
    \ - 1, v - 1);\n    }\n \n    MergeHistoryForest uf(n);\n    for (const auto &e\
    \ : edges) {\n        const auto &es = e.second;\n        if (es.size() == 1)\
    \ {\n            uf.merge(es.front());\n        } else {\n            uf.merge_simultaneously(e.second);\n\
    \        }\n    }\n \n    const auto &g = uf.get_forest();\n \n    auto merge\
    \ = [&](auto &f, auto &g) {\n        int szf = f.size(), szg = g.size();\n   \
    \     std::vector<mint> nf(std::min(szf + szg - 1, k + 1), 0);\n        for (int\
    \ i = 0; i < szf; ++i) for (int j = 0; j < szg; ++j) {\n            if (i + j\
    \ > k) break;\n            nf[i + j] += f[i] * g[j];\n        }\n        return\
    \ nf;\n    };\n \n    std::vector dp(g.size(), std::vector<mint>{});\n    auto\
    \ dfs = [&](auto dfs, int u) -> void {\n        if (g[u].empty()) {\n        \
    \    dp[u] = { 1, 1 };\n            return;\n        }\n        dp[u] = { 1 };\n\
    \        for (int v : g[u]) {\n            dfs(dfs, v);\n            dp[u] = merge(dp[u],\
    \ dp[v]);\n        }\n        dp[u][1] += 1;\n        if (int c = g[u].size();\
    \ c <= k) dp[u][c] -= 1;\n    };\n \n    std::vector<mint> f { 1 };\n    for (int\
    \ root : uf.tree_roots()) {\n        dfs(dfs, root);\n        f = merge(f, dp[root]);\n\
    \    }\n \n    std::cout << std::accumulate(f.begin(), f.end(), mint(0)).val()\
    \ << std::endl;\n \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc235/tasks/abc235_h\"\n\n\
    #include <iostream>\n#include <map>\n\n#include <atcoder/modint>\nusing mint =\
    \ atcoder::modint998244353;\n\n#include <atcoder/dsu>\n#include <algorithm>\n\
    #include <deque>\n#include <numeric>\n#include <optional>\n#include <queue>\n\n\
    #include \"library/datastructure/union_find/merge_history_forest.hpp\"\nusing\
    \ suisen::MergeHistoryForest;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n \n    int n, m, k;\n    std::cin >> n >> m >> k;\n\
    \ \n    std::map<int, std::vector<std::pair<int, int>>> edges;\n    while (m -->\
    \ 0) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n        edges[w].emplace_back(u\
    \ - 1, v - 1);\n    }\n \n    MergeHistoryForest uf(n);\n    for (const auto &e\
    \ : edges) {\n        const auto &es = e.second;\n        if (es.size() == 1)\
    \ {\n            uf.merge(es.front());\n        } else {\n            uf.merge_simultaneously(e.second);\n\
    \        }\n    }\n \n    const auto &g = uf.get_forest();\n \n    auto merge\
    \ = [&](auto &f, auto &g) {\n        int szf = f.size(), szg = g.size();\n   \
    \     std::vector<mint> nf(std::min(szf + szg - 1, k + 1), 0);\n        for (int\
    \ i = 0; i < szf; ++i) for (int j = 0; j < szg; ++j) {\n            if (i + j\
    \ > k) break;\n            nf[i + j] += f[i] * g[j];\n        }\n        return\
    \ nf;\n    };\n \n    std::vector dp(g.size(), std::vector<mint>{});\n    auto\
    \ dfs = [&](auto dfs, int u) -> void {\n        if (g[u].empty()) {\n        \
    \    dp[u] = { 1, 1 };\n            return;\n        }\n        dp[u] = { 1 };\n\
    \        for (int v : g[u]) {\n            dfs(dfs, v);\n            dp[u] = merge(dp[u],\
    \ dp[v]);\n        }\n        dp[u][1] += 1;\n        if (int c = g[u].size();\
    \ c <= k) dp[u][c] -= 1;\n    };\n \n    std::vector<mint> f { 1 };\n    for (int\
    \ root : uf.tree_roots()) {\n        dfs(dfs, root);\n        f = merge(f, dp[root]);\n\
    \    }\n \n    std::cout << std::accumulate(f.begin(), f.end(), mint(0)).val()\
    \ << std::endl;\n \n    return 0;\n}"
  dependsOn:
  - library/datastructure/union_find/merge_history_forest.hpp
  isVerificationFile: true
  path: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
  requiredBy: []
  timestamp: '2022-02-26 00:55:04+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
- /verify/test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp.html
title: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
---
