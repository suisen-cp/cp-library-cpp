---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/optimization/project_selection_problem.hpp
    title: Project Selection Problem
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/optimization/k_project_selection_problem/arc129_e.test.cpp
    title: test/src/optimization/k_project_selection_problem/arc129_e.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/optimization/k_project_selection_problem.hpp\"\n\
    \n\n\n#include <type_traits>\n#include <vector>\n\n#line 1 \"library/optimization/project_selection_problem.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <utility>\n#include <tuple>\n\
    #line 9 \"library/optimization/project_selection_problem.hpp\"\n\n#include <atcoder/maxflow>\n\
    \nnamespace suisen {\n    template <typename Cost>\n    struct ProjectSelection\
    \ {\n        using Item = std::size_t;\n\nprivate:\n        template <typename\
    \ T>\n        using CostFunc = std::array<T, 2>;\npublic:\n\n        using CostFunc0\
    \ = Cost;\n        using CostFunc1 = CostFunc<CostFunc0>;\n        using CostFunc2\
    \ = CostFunc<CostFunc1>;\n        using CostFunc3 = CostFunc<CostFunc2>;\n\n \
    \       ProjectSelection() = default;\n\n        explicit ProjectSelection(std::size_t\
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
    \n\n\n#line 8 \"library/optimization/k_project_selection_problem.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename Cost>\n    struct KProjectSelection {\n   \
    \     using Item = std::size_t;\n        using CostFunc0 = Cost;\n        using\
    \ CostFunc1 = std::vector<CostFunc0>;\n        using CostFunc2 = std::vector<CostFunc1>;\n\
    \n        KProjectSelection() = default;\n\n        template <typename Container,\
    \ std::enable_if_t<std::is_integral_v<typename Container::value_type>, std::nullptr_t>\
    \ = nullptr>\n        explicit KProjectSelection(const Container& ks) : _num(ks.size()),\
    \ _ks(ks.begin(), ks.end()), _x(_num) {\n            std::size_t id = 0;\n   \
    \         for (std::size_t i = 0; i < _num; ++i) {\n                assert(_ks[i]\
    \ >= 1);\n                _x[i].resize(_ks[i]);\n                _x[i][0] = ~0;\n\
    \                for (std::size_t d = 1; d < _ks[i]; ++d) {\n                \
    \    _x[i][d] = id++;\n                }\n            }\n            // [x_i <\
    \ d] <===> _x[i][d]\n            // [x_i = d] <===> ~_x[i][1] & ~_x[i][2] & ...\
    \ & ~_x[i][d] & _x[i][d+1] & _x[i][d+2] & ... & _x[i][k_i]\n            _psp =\
    \ ProjectSelection<Cost>(id);\n            for (std::size_t i = 0; i < _num; ++i)\
    \ {\n                for (std::size_t d = 1; d < _ks[i] - 1; ++d) {\n        \
    \            _psp.add_cost_10(_x[i][d], _x[i][d + 1], INF);\n                }\n\
    \            }\n        }\n        KProjectSelection(std::size_t n, std::size_t\
    \ k) : KProjectSelection(std::vector<std::size_t>(n, k)) {}\n\n        void add_cost(CostFunc0\
    \ cost) { _psp.add_cost(cost); }\n        void add_profit(CostFunc0 profit) {\
    \ _psp.add_profit(profit); }\n\n        void add_cost(Item i, const CostFunc1&\
    \ cost) {\n            assert(i < _num);\n            assert(cost.size() == _ks[i]);\n\
    \            _psp.add_cost(cost[_ks[i] - 1]);\n            for (std::size_t d\
    \ = 1; d < _ks[i]; ++d) {\n                _psp.add_cost(_x[i][d], { 0, cost[d\
    \ - 1] - cost[d] });\n            }\n        }\n        void add_profit(Item i,\
    \ CostFunc1 profit) {\n            for (auto &p : profit) p = -p;\n          \
    \  add_cost(i, profit);\n        }\n\n        // cost: Monge (i.e., cost[i][j]+cost[i+1][j+1]\
    \ <= cost[i+1][j]+cost[i][j+1])\n        void add_cost(Item i, Item j, CostFunc2\
    \ cost) {\n            assert(i < _num);\n            assert(j < _num);\n    \
    \        assert(i != j);\n\n            assert(cost.size() == _ks[i]);\n\n   \
    \         CostFunc1 cost_i(_ks[i]), cost_j(_ks[j]);\n            for (std::size_t\
    \ di = 0; di < _ks[i]; ++di) {\n                assert(cost[di].size() == _ks[j]);\n\
    \                cost_i[di] = cost[di][0];\n                for (std::size_t dj\
    \ = 0; dj < _ks[j]; ++dj) {\n                    cost[di][dj] -= cost_i[di];\n\
    \                }\n            }\n            for (std::size_t dj = 0; dj < _ks[j];\
    \ ++dj) {\n                cost_j[dj] = cost[0][dj];\n                for (std::size_t\
    \ di = 0; di < _ks[i]; ++di) {\n                    cost[di][dj] -= cost_j[dj];\n\
    \                }\n            }\n            add_cost(i, cost_i);\n        \
    \    add_cost(j, cost_j);\n\n            for (std::size_t di = 0; di < _ks[i];\
    \ ++di) assert(cost[di][0] == 0);\n            for (std::size_t dj = 0; dj < _ks[j];\
    \ ++dj) assert(cost[0][dj] == 0);\n\n            for (std::size_t di = 1; di <\
    \ _ks[i]; ++di) {\n                for (std::size_t dj = 1; dj < _ks[j]; ++dj)\
    \ {\n                    Cost cost_00 = cost[di][dj] - cost[di][dj - 1] - cost[di\
    \ - 1][dj] + cost[di - 1][dj - 1];\n                    // Monge\n           \
    \         assert(cost_00 <= 0);\n                    _psp.add_profit_00(_x[i][di],\
    \ _x[j][dj], -cost_00);\n                }\n            }\n        }\n\n     \
    \   std::pair<Cost, std::vector<int>> min_cost() {\n            auto [ans, x_bin]\
    \ = _psp.min_cost();\n            std::vector<int> x(_num);\n            for (std::size_t\
    \ i = 0; i < _num; ++i) for (std::size_t di = 1; di < _ks[i]; ++di) {\n      \
    \          x[i] += not x_bin[_x[i][di]];\n            }\n            return {\
    \ ans, x };\n        }\n\n        std::pair<Cost, std::vector<int>> max_profit()\
    \ {\n            auto res = min_cost();\n            res.first = -res.first;\n\
    \            return res;\n        }\n\n    private:\n        static constexpr\
    \ Cost INF = std::numeric_limits<Cost>::max() / 2;\n\n        std::size_t _num;\n\
    \        std::vector<std::size_t> _ks;\n        std::vector<std::vector<std::size_t>>\
    \ _x;\n        ProjectSelection<Cost> _psp;\n    };\n} // namespace suisen\n\n\
    \n\n"
  code: "#ifndef SUISEN_K_PROJECT_SELECTION\n#define SUISEN_K_PROJECT_SELECTION\n\n\
    #include <type_traits>\n#include <vector>\n\n#include \"library/optimization/project_selection_problem.hpp\"\
    \n\nnamespace suisen {\n    template <typename Cost>\n    struct KProjectSelection\
    \ {\n        using Item = std::size_t;\n        using CostFunc0 = Cost;\n    \
    \    using CostFunc1 = std::vector<CostFunc0>;\n        using CostFunc2 = std::vector<CostFunc1>;\n\
    \n        KProjectSelection() = default;\n\n        template <typename Container,\
    \ std::enable_if_t<std::is_integral_v<typename Container::value_type>, std::nullptr_t>\
    \ = nullptr>\n        explicit KProjectSelection(const Container& ks) : _num(ks.size()),\
    \ _ks(ks.begin(), ks.end()), _x(_num) {\n            std::size_t id = 0;\n   \
    \         for (std::size_t i = 0; i < _num; ++i) {\n                assert(_ks[i]\
    \ >= 1);\n                _x[i].resize(_ks[i]);\n                _x[i][0] = ~0;\n\
    \                for (std::size_t d = 1; d < _ks[i]; ++d) {\n                \
    \    _x[i][d] = id++;\n                }\n            }\n            // [x_i <\
    \ d] <===> _x[i][d]\n            // [x_i = d] <===> ~_x[i][1] & ~_x[i][2] & ...\
    \ & ~_x[i][d] & _x[i][d+1] & _x[i][d+2] & ... & _x[i][k_i]\n            _psp =\
    \ ProjectSelection<Cost>(id);\n            for (std::size_t i = 0; i < _num; ++i)\
    \ {\n                for (std::size_t d = 1; d < _ks[i] - 1; ++d) {\n        \
    \            _psp.add_cost_10(_x[i][d], _x[i][d + 1], INF);\n                }\n\
    \            }\n        }\n        KProjectSelection(std::size_t n, std::size_t\
    \ k) : KProjectSelection(std::vector<std::size_t>(n, k)) {}\n\n        void add_cost(CostFunc0\
    \ cost) { _psp.add_cost(cost); }\n        void add_profit(CostFunc0 profit) {\
    \ _psp.add_profit(profit); }\n\n        void add_cost(Item i, const CostFunc1&\
    \ cost) {\n            assert(i < _num);\n            assert(cost.size() == _ks[i]);\n\
    \            _psp.add_cost(cost[_ks[i] - 1]);\n            for (std::size_t d\
    \ = 1; d < _ks[i]; ++d) {\n                _psp.add_cost(_x[i][d], { 0, cost[d\
    \ - 1] - cost[d] });\n            }\n        }\n        void add_profit(Item i,\
    \ CostFunc1 profit) {\n            for (auto &p : profit) p = -p;\n          \
    \  add_cost(i, profit);\n        }\n\n        // cost: Monge (i.e., cost[i][j]+cost[i+1][j+1]\
    \ <= cost[i+1][j]+cost[i][j+1])\n        void add_cost(Item i, Item j, CostFunc2\
    \ cost) {\n            assert(i < _num);\n            assert(j < _num);\n    \
    \        assert(i != j);\n\n            assert(cost.size() == _ks[i]);\n\n   \
    \         CostFunc1 cost_i(_ks[i]), cost_j(_ks[j]);\n            for (std::size_t\
    \ di = 0; di < _ks[i]; ++di) {\n                assert(cost[di].size() == _ks[j]);\n\
    \                cost_i[di] = cost[di][0];\n                for (std::size_t dj\
    \ = 0; dj < _ks[j]; ++dj) {\n                    cost[di][dj] -= cost_i[di];\n\
    \                }\n            }\n            for (std::size_t dj = 0; dj < _ks[j];\
    \ ++dj) {\n                cost_j[dj] = cost[0][dj];\n                for (std::size_t\
    \ di = 0; di < _ks[i]; ++di) {\n                    cost[di][dj] -= cost_j[dj];\n\
    \                }\n            }\n            add_cost(i, cost_i);\n        \
    \    add_cost(j, cost_j);\n\n            for (std::size_t di = 0; di < _ks[i];\
    \ ++di) assert(cost[di][0] == 0);\n            for (std::size_t dj = 0; dj < _ks[j];\
    \ ++dj) assert(cost[0][dj] == 0);\n\n            for (std::size_t di = 1; di <\
    \ _ks[i]; ++di) {\n                for (std::size_t dj = 1; dj < _ks[j]; ++dj)\
    \ {\n                    Cost cost_00 = cost[di][dj] - cost[di][dj - 1] - cost[di\
    \ - 1][dj] + cost[di - 1][dj - 1];\n                    // Monge\n           \
    \         assert(cost_00 <= 0);\n                    _psp.add_profit_00(_x[i][di],\
    \ _x[j][dj], -cost_00);\n                }\n            }\n        }\n\n     \
    \   std::pair<Cost, std::vector<int>> min_cost() {\n            auto [ans, x_bin]\
    \ = _psp.min_cost();\n            std::vector<int> x(_num);\n            for (std::size_t\
    \ i = 0; i < _num; ++i) for (std::size_t di = 1; di < _ks[i]; ++di) {\n      \
    \          x[i] += not x_bin[_x[i][di]];\n            }\n            return {\
    \ ans, x };\n        }\n\n        std::pair<Cost, std::vector<int>> max_profit()\
    \ {\n            auto res = min_cost();\n            res.first = -res.first;\n\
    \            return res;\n        }\n\n    private:\n        static constexpr\
    \ Cost INF = std::numeric_limits<Cost>::max() / 2;\n\n        std::size_t _num;\n\
    \        std::vector<std::size_t> _ks;\n        std::vector<std::vector<std::size_t>>\
    \ _x;\n        ProjectSelection<Cost> _psp;\n    };\n} // namespace suisen\n\n\
    \n#endif // SUISEN_K_PROJECT_SELECTION\n"
  dependsOn:
  - library/optimization/project_selection_problem.hpp
  isVerificationFile: false
  path: library/optimization/k_project_selection_problem.hpp
  requiredBy: []
  timestamp: '2024-01-30 21:53:51+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/optimization/k_project_selection_problem/arc129_e.test.cpp
documentation_of: library/optimization/k_project_selection_problem.hpp
layout: document
title: K Project Selection Problem
---
## K Project Selection Problem
