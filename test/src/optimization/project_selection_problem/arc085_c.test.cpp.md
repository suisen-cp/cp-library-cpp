---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/optimization/project_selection_problem.hpp
    title: library/optimization/project_selection_problem.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/arc085/tasks/arc085_c
    links:
    - https://atcoder.jp/contests/arc085/tasks/arc085_c
  bundledCode: "#line 1 \"test/src/optimization/project_selection_problem/arc085_c.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/arc085/tasks/arc085_c\"\n\n#line\
    \ 1 \"library/optimization/project_selection_problem.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <utility>\n#include <tuple>\n#include <vector>\n\n\
    #include <atcoder/maxflow>\n\nnamespace suisen {\n    template <typename Cost>\n\
    \    struct ProjectSelection {\n        using Item = std::size_t;\n\nprivate:\n\
    \        template <typename T>\n        using CostFunc = std::array<T, 2>;\npublic:\n\
    \n        using CostFunc0 = Cost;\n        using CostFunc1 = CostFunc<CostFunc0>;\n\
    \        using CostFunc2 = CostFunc<CostFunc1>;\n        using CostFunc3 = CostFunc<CostFunc2>;\n\
    \n        ProjectSelection() = default;\n\n        explicit ProjectSelection(std::size_t\
    \ n) : _num(n), _cost1(n) {}\n\n        void add_cost(CostFunc0 cost) { _cost0\
    \ += cost; }\n        void add_profit(CostFunc0 profit) { add_cost(-profit); }\n\
    \n        void add_cost_0(Item i, Cost cost) { add_cost(i, CostFunc1{ cost, 0\
    \ }); }\n        void add_cost_1(Item i, Cost cost) { add_cost(i, CostFunc1{ 0,\
    \ cost }); }\n        void add_profit_0(Item i, Cost profit) { add_cost(i, CostFunc1{\
    \ -profit, 0 }); }\n        void add_profit_1(Item i, Cost profit) { add_cost(i,\
    \ CostFunc1{ 0, -profit }); }\n\n        void add_cost(Item i, CostFunc1 cost)\
    \ {\n            assert(i < _num);\n            _cost1[i][0] += cost[0];\n   \
    \         _cost1[i][1] += cost[1];\n        }\n        void add_profit(Item i,\
    \ CostFunc1 profit) { add_cost(i, neg(profit)); }\n\n        void add_cost_01(Item\
    \ i, Item j, Cost cost) {\n            assert(i < _num);\n            assert(j\
    \ < _num);\n            assert(i != j);\n            add_edge(i, j, cost);\n \
    \       }\n\n        void add_cost_10(Item i, Item j, Cost cost) { add_cost_01(j,\
    \ i, cost); }\n        void add_cost_not_same(Item i, Item j, Cost cost) { add_cost(i,\
    \ j, CostFunc2{ 0, cost, cost, 0 }); }\n        void add_profit_00(Item i, Item\
    \ j, Cost profit) { add_cost(i, j, CostFunc2{ -profit, 0, 0, 0 }); }\n       \
    \ void add_profit_11(Item i, Item j, Cost profit) { add_cost(i, j, CostFunc2{\
    \ 0, 0, 0, -profit }); }\n        void add_profit_same(Item i, Item j, Cost profit)\
    \ { add_cost(i, j, CostFunc2{ -profit, 0, 0, -profit }); }\n\n        // cost:\
    \ submodular (i.e., cost[0][1] + cost[1][0] >= cost[0][0] + cost[1][1])\n    \
    \    void add_cost(Item i, Item j, CostFunc2 cost) {\n            assert(i < _num);\n\
    \            assert(j < _num);\n            assert(i != j);\n            add_cost(cost[0][0]);\n\
    \            add_cost(i, CostFunc1{ 0, cost[1][0] - cost[0][0] });\n         \
    \   add_cost(j, CostFunc1{ 0, cost[1][1] - cost[1][0] });\n            add_cost_01(i,\
    \ j, (cost[0][1] + cost[1][0]) - (cost[0][0] + cost[1][1]));\n        }\n    \
    \    void add_profit(Item i, Item j, const CostFunc2 &profit) { add_cost(i, j,\
    \ neg(profit)); }\n\n        // cost: submodular (i.e., cost(X) + cost(Y) >= cost(X\
    \ | Y) + cost(X & Y))\n        void add_cost(Item i, Item j, Item k, CostFunc3\
    \ cost) {\n            assert(i < _num);\n            assert(j < _num);\n    \
    \        assert(k < _num);\n            assert(i != j);\n            assert(j\
    \ != k);\n            assert(k != i);\n            const Cost A = cost[0][0][0],\
    \ B = cost[0][0][1];\n            const Cost C = cost[0][1][0], D = cost[0][1][1];\n\
    \            const Cost E = cost[1][0][0], F = cost[1][0][1];\n            const\
    \ Cost G = cost[1][1][0], H = cost[1][1][1];\n            const Cost P = (A +\
    \ D + F + G) - (B + C + E + H);\n            if (P >= 0) {\n                const\
    \ Cost P1 = F - B, P2 = G - E, P3 = D - C;\n                const Cost P12 = (C\
    \ + E) - (A + G), P23 = (B + C) - (A + D), P31 = (B + E) - (A + F);\n        \
    \        add_cost(A);\n                add_cost(i, CostFunc1{ 0, P1 });\n    \
    \            add_cost(j, CostFunc1{ 0, P2 });\n                add_cost(k, CostFunc1{\
    \ 0, P3 });\n                add_cost_01(i, j, P12);\n                add_cost_01(j,\
    \ k, P23);\n                add_cost_01(k, i, P31);\n                add_profit_all_1(std::array<Item,\
    \ 3>{ i, j, k }, P);\n            } else {\n                const Cost P1 = C\
    \ - G, P2 = B - D, P3 = E - F;\n                const Cost P21 = (D + F) - (B\
    \ + H), P32 = (F + G) - (E + H), P13 = (D + G) - (C + H);\n                add_cost(H);\n\
    \                add_cost(i, CostFunc1{ P1, 0 });\n                add_cost(j,\
    \ CostFunc1{ P2, 0 });\n                add_cost(k, CostFunc1{ P3, 0 });\n   \
    \             add_cost_01(j, i, P21);\n                add_cost_01(k, j, P32);\n\
    \                add_cost_01(i, k, P13);\n                add_profit_all_0(std::array<Item,\
    \ 3>{ i, j, k }, -P);\n            }\n        }\n\n        template <typename\
    \ Container>\n        auto add_profit_all_0(const Container& is, Cost profit)\
    \ -> decltype(static_cast<Item>(*is.begin()), is.end(), void()) {\n          \
    \  assert(profit >= 0);\n            if (is.size() == 0) {\n                return\
    \ add_profit(profit);\n            } else if (is.size() == 1) {\n            \
    \    return add_profit(is[0], CostFunc1{ profit, 0 });\n            } else if\
    \ (is.size() == 2) {\n                return add_profit_00(is[0], is[1], profit);\n\
    \            }\n            add_profit(profit);\n            const Item aux =\
    \ _num + _num_aux++;\n            add_edge(S, aux, profit);\n            for (Item\
    \ i : is) {\n                add_edge(aux, i, profit);\n            }\n      \
    \  }\n        template <typename Container>\n        auto add_profit_all_1(const\
    \ Container& is, Cost profit) -> decltype(static_cast<Item>(*is.begin()), is.end(),\
    \ void()) {\n            assert(profit >= 0);\n            if (is.size() == 0)\
    \ {\n                return add_profit(profit);\n            } else if (is.size()\
    \ == 1) {\n                return add_profit(is[0], CostFunc1{ 0, profit });\n\
    \            } else if (is.size() == 2) {\n                return add_profit_11(is[0],\
    \ is[1], profit);\n            }\n            add_profit(profit);\n          \
    \  const Item aux = _num + _num_aux++;\n            for (Item i : is) {\n    \
    \            add_edge(i, aux, profit);\n            }\n            add_edge(aux,\
    \ T, profit);\n        }\n\n        auto min_cost() {\n            atcoder::mf_graph<Cost>\
    \ g(_num + _num_aux + 2);\n            const std::size_t s = _num + _num_aux,\
    \ t = s + 1;\n            make_edges_for_cost1();\n            for (const auto\
    \ &[i, j, cost] : _edges) {\n                std::size_t u = (i == S) ? s : (i\
    \ == T) ? t : i;\n                std::size_t v = (j == S) ? s : (j == T) ? t\
    \ : j;\n                g.add_edge(u, v, cost);\n            }\n            Cost\
    \ ans = _cost0 + g.flow(s, t);\n            auto x = g.min_cut(s);\n         \
    \   x.resize(_num);\n            for (std::size_t i = 0; i < _num; ++i) {\n  \
    \              x[i] = not x[i];\n            }\n            return std::make_pair(ans,\
    \ x);\n        }\n        auto max_profit() {\n            auto res = min_cost();\n\
    \            res.first = -res.first;\n            return res;\n        }\n   \
    \ private:\n        static constexpr std::size_t S = ~0;\n        static constexpr\
    \ std::size_t T = ~1;\n\n        std::size_t _num;\n        std::size_t _num_aux\
    \ = 0;\n        Cost _cost0 = 0;\n        std::vector<CostFunc1> _cost1;\n   \
    \     std::vector<std::tuple<Item, Item, Cost>> _edges{};\n\n        void make_edges_for_cost1()\
    \ {\n            for (std::size_t i = 0; i < _num; ++i) {\n                CostFunc1&\
    \ cost = _cost1[i];\n                if (cost[0] <= cost[1]) {\n             \
    \       add_cost(cost[0]);\n                    add_edge(S, i, cost[1] - cost[0]);\n\
    \                } else {\n                    add_cost(cost[1]);\n          \
    \          add_edge(i, T, cost[0] - cost[1]);\n                }\n           \
    \     cost = { 0, 0 };\n            }\n        }\n        void add_edge(std::size_t\
    \ i, std::size_t j, Cost cost) {\n            assert(cost >= 0);\n           \
    \ assert(i == S or i == T or i < _num + _num_aux);\n            assert(j == S\
    \ or j == T or j < _num + _num_aux);\n            assert(i != j);\n          \
    \  if (cost == 0) return;\n            _edges.emplace_back(i, j, cost);\n    \
    \    }\n\n        static constexpr Cost neg(Cost cost) { return -cost; }\n   \
    \     template <typename T>\n        static constexpr CostFunc<T> neg(const CostFunc<T>\
    \ &cost) { return { neg(cost[0]), neg(cost[1]) }; }\n    };\n} // namespace suisen\n\
    \n\n\n#line 4 \"test/src/optimization/project_selection_problem/arc085_c.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n    int n;\n    std::cin >> n;\n\n  \
    \  using Cost = long long;\n\n    Cost inf = std::numeric_limits<Cost>::max()\
    \ / 2;\n\n    std::vector<Cost> a(n + 1);\n    for (int i = 1; i <= n; ++i) {\n\
    \        std::cin >> a[i];\n    }\n\n    suisen::ProjectSelection<Cost> psp(n\
    \ + 1);\n\n    for (int x = 1; x <= n; ++x) {\n        psp.add_profit_0(x, a[x]);\n\
    \        for (int y = 2 * x; y <= n; y += x) {\n            psp.add_cost_01(y,\
    \ x, inf);\n        }\n    }\n\n    std::cout << psp.max_profit().first << std::endl;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/arc085/tasks/arc085_c\"\n\n\
    #include \"library/optimization/project_selection_problem.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n    int n;\n    std::cin >> n;\n\n    using Cost = long long;\n\
    \n    Cost inf = std::numeric_limits<Cost>::max() / 2;\n\n    std::vector<Cost>\
    \ a(n + 1);\n    for (int i = 1; i <= n; ++i) {\n        std::cin >> a[i];\n \
    \   }\n\n    suisen::ProjectSelection<Cost> psp(n + 1);\n\n    for (int x = 1;\
    \ x <= n; ++x) {\n        psp.add_profit_0(x, a[x]);\n        for (int y = 2 *\
    \ x; y <= n; y += x) {\n            psp.add_cost_01(y, x, inf);\n        }\n \
    \   }\n\n    std::cout << psp.max_profit().first << std::endl;\n}"
  dependsOn:
  - library/optimization/project_selection_problem.hpp
  isVerificationFile: true
  path: test/src/optimization/project_selection_problem/arc085_c.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 21:53:51+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/optimization/project_selection_problem/arc085_c.test.cpp
layout: document
redirect_from:
- /verify/test/src/optimization/project_selection_problem/arc085_c.test.cpp
- /verify/test/src/optimization/project_selection_problem/arc085_c.test.cpp.html
title: test/src/optimization/project_selection_problem/arc085_c.test.cpp
---
