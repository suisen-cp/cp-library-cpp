---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/rerooting.hpp
    title: Rerooting
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/dp/tasks/dp_v
    links:
    - https://atcoder.jp/contests/dp/tasks/dp_v
  bundledCode: "#line 1 \"test/src/tree/rerooting/edpc_v.test.cpp\"\n#define PROBLEM\
    \ \"https://atcoder.jp/contests/dp/tasks/dp_v\"\n\n#include <iostream>\n#include\
    \ <atcoder/modint>\n\nusing mint = atcoder::modint;\n\n#line 1 \"library/tree/rerooting.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen {\n    template <\n        // type\
    \ of DP array elements\n        typename dp_value_type,\n        // merge children\
    \ ((op, dp_value_type) is required to be commutative monoid)\n        dp_value_type(*op)(dp_value_type,\
    \ dp_value_type),\n        // identity element of op\n        dp_value_type(*e)(),\n\
    \        // add info as a root of subtree; add_subtree_root(dp[child], child,\
    \ parent)\n        dp_value_type(*add_subtree_root)(dp_value_type, int, int),\n\
    \        // type of weights on the edges\n        typename edge_data_type,\n \
    \       // transition from child to parent using edge weight; trans_to_par(dp[child],\
    \ child, parent, weight(child, parent))\n        dp_value_type(*trans_to_par)(dp_value_type,\
    \ int, int, edge_data_type)\n    >\n    struct ReRooting : public std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>> {\n        using base_type = std::vector<std::vector<std::pair<int,\
    \ edge_data_type>>>;\n        public:\n            static constexpr int NIL =\
    \ -1;\n\n            using base_type::base_type;\n\n            void add_edge(int\
    \ u, int v, const edge_data_type& w) {\n                (*this)[u].emplace_back(v,\
    \ w);\n                (*this)[v].emplace_back(u, w);\n            }\n\n     \
    \       const std::vector<dp_value_type>& rerooting(int initial_root = 0) {\n\
    \                const int n = this->size();\n                dp.resize(n), to_par.resize(n);\n\
    \                dfs_subtree(initial_root, NIL);\n                dfs(initial_root,\
    \ NIL, e());\n                return dp;\n            }\n\n        private:\n\
    \            std::vector<dp_value_type> dp, to_par;\n\n            void dfs_subtree(int\
    \ u, int p) {\n                dp[u] = e();\n                for (auto [v, w]\
    \ : (*this)[u]) {\n                    if (v == p) continue;\n               \
    \     dfs_subtree(v, u);\n                    dp[u] = op(dp[u], to_par[v] = trans_to_par(add_subtree_root(dp[v],\
    \ v, u), v, u, w));\n                }\n            }\n            void dfs(int\
    \ u, int p, dp_value_type from_p) {\n                dp[u] = add_subtree_root(dp[u],\
    \ u, NIL);\n                const int sz = (*this)[u].size();\n              \
    \  std::vector<dp_value_type> cum_l { e() };\n                cum_l.reserve(sz\
    \ + 1);\n                for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(),\
    \ v == p ? from_p : to_par[v]));\n                dp_value_type cum_r = e();\n\
    \                for (int i = sz - 1; i >= 0; --i) {\n                    const\
    \ auto& [v, w] = (*this)[u][i];\n                    if (v == p) {\n         \
    \               cum_r = op(from_p, cum_r);\n                    } else {\n   \
    \                     dp_value_type from_u = trans_to_par(add_subtree_root(op(cum_l[i],\
    \ cum_r), u, v), u, v, w);\n                        dp[v] = op(dp[v], from_u);\n\
    \                        dfs(v, u, from_u);\n                        cum_r = op(to_par[v],\
    \ cum_r);\n                    }\n                }\n            }\n    };\n}\
    \ // namsepace suisen\n\n\n#line 9 \"test/src/tree/rerooting/edpc_v.test.cpp\"\
    \nusing suisen::ReRooting;\n\nmint op(mint x, mint y) {\n    return x * y;\n}\n\
    mint e() {\n    return 1;\n}\nmint add_subtree_root(mint val, int, int) {\n  \
    \  return val;\n}\nmint trans_to_par(mint val, int, int, std::nullptr_t) {\n \
    \   return val + 1;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    mint::set_mod(m);\n\
    \n    ReRooting<mint, op, e, add_subtree_root, std::nullptr_t, trans_to_par> g(n);\n\
    \    for (int i = 0; i < n - 1; ++i) {\n        int x, y;\n        std::cin >>\
    \ x >> y;\n        --x, --y;\n        g.add_edge(x, y, nullptr);\n    }\n\n  \
    \  for (mint e : g.rerooting()) {\n        std::cout << e.val() << '\\n';\n  \
    \  }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/dp/tasks/dp_v\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint;\n\n#include\
    \ \"library/tree/rerooting.hpp\"\nusing suisen::ReRooting;\n\nmint op(mint x,\
    \ mint y) {\n    return x * y;\n}\nmint e() {\n    return 1;\n}\nmint add_subtree_root(mint\
    \ val, int, int) {\n    return val;\n}\nmint trans_to_par(mint val, int, int,\
    \ std::nullptr_t) {\n    return val + 1;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    mint::set_mod(m);\n\
    \n    ReRooting<mint, op, e, add_subtree_root, std::nullptr_t, trans_to_par> g(n);\n\
    \    for (int i = 0; i < n - 1; ++i) {\n        int x, y;\n        std::cin >>\
    \ x >> y;\n        --x, --y;\n        g.add_edge(x, y, nullptr);\n    }\n\n  \
    \  for (mint e : g.rerooting()) {\n        std::cout << e.val() << '\\n';\n  \
    \  }\n    return 0;\n}"
  dependsOn:
  - library/tree/rerooting.hpp
  isVerificationFile: true
  path: test/src/tree/rerooting/edpc_v.test.cpp
  requiredBy: []
  timestamp: '2021-10-12 21:48:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/tree/rerooting/edpc_v.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/rerooting/edpc_v.test.cpp
- /verify/test/src/tree/rerooting/edpc_v.test.cpp.html
title: test/src/tree/rerooting/edpc_v.test.cpp
---