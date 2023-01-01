---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/union_find/merge_history_forest.hpp
    title: "\u30DE\u30FC\u30B8\u904E\u7A0B\u3092\u8868\u3059\u68EE"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc235/tasks/abc235_Ex
    links:
    - https://atcoder.jp/contests/abc235/tasks/abc235_Ex
  bundledCode: "#line 1 \"test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc235/tasks/abc235_Ex\"\n\n#include\
    \ <iostream>\n#include <map>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include <atcoder/dsu>\n#include <algorithm>\n#include <deque>\n#include <numeric>\n\
    #include <optional>\n#include <queue>\n\n#line 1 \"library/datastructure/union_find/merge_history_forest.hpp\"\
    \n\n\n\n#line 8 \"library/datastructure/union_find/merge_history_forest.hpp\"\n\
    #include <limits>\n\nnamespace suisen {\n    struct MergeHistoryForest : public\
    \ atcoder::dsu {\n        using base_type = atcoder::dsu;\n\n        MergeHistoryForest()\
    \ : MergeHistoryForest(0) {}\n        explicit MergeHistoryForest(int n) : base_type(n),\
    \ _g(n), _parent(n, -1), _root(n), _time(0), _created_time(n, _time) {\n     \
    \       std::iota(_root.begin(), _root.end(), 0);\n        }\n\n        int node_num()\
    \ const { return _g.size(); }\n        int leaf_num() const { return _root.size();\
    \ }\n\n        const auto& get_forest() const { return _g; }\n    \n        int\
    \ forest_root(int i) { return _root[leader(i)]; }\n        int forest_parent(int\
    \ vid) const { return _parent[vid]; }\n        const auto& forest_children(int\
    \ vid) { return _g[vid]; }\n        bool is_forest_root(int vid) const { return\
    \ _parent[vid] < 0; }\n        bool is_forest_leaf(int vid) const { return vid\
    \ < leaf_num(); }\n\n        std::vector<int> forest_roots() {\n            const\
    \ int n = leaf_num();\n            std::vector<int> roots;\n            for (int\
    \ i = 0; i < n; ++i) if (leader(i) == i) roots.push_back(_root[i]);\n        \
    \    return roots;\n        }\n \n        void merge(int u, int v) {\n       \
    \     ++_time;\n            const int ru = leader(u), rv = leader(v);\n      \
    \      if (ru == rv) return;\n            const int new_root = create_node();\n\
    \            create_edge(new_root, _root[ru]), create_edge(new_root, _root[rv]);\n\
    \            _root[base_type::merge(ru, rv)] = new_root;\n        }\n        void\
    \ merge(const std::pair<int, int> &edge) { merge(edge.first, edge.second); }\n\
    \n        void merge_simultaneously(const std::vector<std::pair<int, int>> &edges)\
    \ {\n            ++_time;\n            std::vector<int> vs;\n            for (const\
    \ auto &[u, v] : edges) {\n                const int ru = leader(u), rv = leader(v);\n\
    \                if (ru == rv) continue;\n                const int r = base_type::merge(ru,\
    \ rv), c = ru ^ rv ^ r;\n                _g[r].push_back(c);\n               \
    \ vs.push_back(r);\n            }\n            for (int s : vs) if (s == leader(s))\
    \ {\n                const int new_root = create_node();\n                merge_dfs(s,\
    \ new_root);\n                _root[s] = new_root;\n            }\n        }\n\
    \n        int current_time() const { return _time; }\n        int created_time(int\
    \ vid) const { return _created_time[vid]; }\n\n        std::vector<int> group(int\
    \ i, int time = std::numeric_limits<int>::max()) {\n            int root = i;\n\
    \            while (_parent[root] >= 0 and _created_time[_parent[root]] <= time)\
    \ root = _parent[root];\n            std::vector<int> res;\n            auto dfs\
    \ = [&, this](auto dfs, int u) -> void {\n                if (is_forest_leaf(u))\
    \ {\n                    res.push_back(u);\n                } else {\n       \
    \             for (int v : _g[u]) dfs(dfs, v);\n                }\n          \
    \  };\n            dfs(dfs, root);\n            return res;\n        }\n     \
    \   std::vector<std::vector<int>> groups(int time = std::numeric_limits<int>::max())\
    \ {\n            std::vector<std::vector<int>> res;\n            const int n =\
    \ leaf_num();\n            std::vector<bool> seen(n, false);\n            for\
    \ (int i = 0; i < n; ++i) if (not seen[i]) for (int v : res.emplace_back(group(i,\
    \ time))) seen[v] = true;\n            return res;\n        }\n\n        template\
    \ <typename GetLCA>\n        bool same(int u, int v, int time, GetLCA&& get_lca)\
    \ {\n            if (not base_type::same(u, v)) return false;\n            int\
    \ a = get_lca(u, v);\n            return _created_time[a] <= time;\n        }\n\
    \n        using base_type::same;\n\n    private:\n        std::vector<std::vector<int>>\
    \ _g;\n        std::vector<int> _parent;\n        std::vector<int> _root;\n\n\
    \        // sum of the number of calls of function `merge` and those of `merge_simultaneously`\n\
    \        int _time;\n        std::vector<int> _created_time;\n\n        void merge_dfs(int\
    \ u, int new_root) {\n            for (int v : _g[u]) merge_dfs(v, new_root),\
    \ _g[v].shrink_to_fit();\n            create_edge(new_root, _root[u]);\n     \
    \       _g[u].clear();\n        }\n\n        int create_node() {\n           \
    \ _g.emplace_back();\n            _created_time.push_back(_time);\n          \
    \  _parent.push_back(-1);\n            return _g.size() - 1;\n        }\n    \
    \    void create_edge(int new_root, int old_root) {\n            _g[new_root].push_back(old_root);\n\
    \            _parent[old_root] = new_root;\n        }\n        static int floor_log2(int\
    \ n) {\n            int res = 0;\n            while (1 << (res + 1) <= n) ++res;\n\
    \            return res;\n        }\n    };\n} // namespace suisen\n\n\n\n#line\
    \ 17 \"test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp\"\
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
    \ root : uf.forest_roots()) {\n        dfs(dfs, root);\n        f = merge(f, dp[root]);\n\
    \    }\n \n    std::cout << std::accumulate(f.begin(), f.end(), mint(0)).val()\
    \ << std::endl;\n \n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc235/tasks/abc235_Ex\"\n\n\
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
    \ root : uf.forest_roots()) {\n        dfs(dfs, root);\n        f = merge(f, dp[root]);\n\
    \    }\n \n    std::cout << std::accumulate(f.begin(), f.end(), mint(0)).val()\
    \ << std::endl;\n \n    return 0;\n}"
  dependsOn:
  - library/datastructure/union_find/merge_history_forest.hpp
  isVerificationFile: true
  path: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
  requiredBy: []
  timestamp: '2023-01-01 18:21:45+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
- /verify/test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp.html
title: test/src/datastructure/union_find/merge_history_forest/abc235_h.test.cpp
---
