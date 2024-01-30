#ifndef SUISEN_PROJECT_SELECTION
#define SUISEN_PROJECT_SELECTION

#include <array>
#include <cassert>
#include <utility>
#include <tuple>
#include <vector>

#include <atcoder/maxflow>

namespace suisen {
    template <typename Cost>
    struct ProjectSelection {
        using Item = std::size_t;

private:
        template <typename T>
        using CostFunc = std::array<T, 2>;
public:

        using CostFunc0 = Cost;
        using CostFunc1 = CostFunc<CostFunc0>;
        using CostFunc2 = CostFunc<CostFunc1>;
        using CostFunc3 = CostFunc<CostFunc2>;

        ProjectSelection() = default;

        explicit ProjectSelection(std::size_t n) : _num(n), _cost1(n) {}

        void add_cost(CostFunc0 cost) { _cost0 += cost; }
        void add_profit(CostFunc0 profit) { add_cost(-profit); }

        void add_cost_0(Item i, Cost cost) { add_cost(i, CostFunc1{ cost, 0 }); }
        void add_cost_1(Item i, Cost cost) { add_cost(i, CostFunc1{ 0, cost }); }
        void add_profit_0(Item i, Cost profit) { add_cost(i, CostFunc1{ -profit, 0 }); }
        void add_profit_1(Item i, Cost profit) { add_cost(i, CostFunc1{ 0, -profit }); }

        void add_cost(Item i, CostFunc1 cost) {
            assert(i < _num);
            _cost1[i][0] += cost[0];
            _cost1[i][1] += cost[1];
        }
        void add_profit(Item i, CostFunc1 profit) { add_cost(i, neg(profit)); }

        void add_cost_01(Item i, Item j, Cost cost) {
            assert(i < _num);
            assert(j < _num);
            assert(i != j);
            add_edge(i, j, cost);
        }

        void add_cost_10(Item i, Item j, Cost cost) { add_cost_01(j, i, cost); }
        void add_cost_not_same(Item i, Item j, Cost cost) { add_cost(i, j, CostFunc2{ 0, cost, cost, 0 }); }
        void add_profit_00(Item i, Item j, Cost profit) { add_cost(i, j, CostFunc2{ -profit, 0, 0, 0 }); }
        void add_profit_11(Item i, Item j, Cost profit) { add_cost(i, j, CostFunc2{ 0, 0, 0, -profit }); }
        void add_profit_same(Item i, Item j, Cost profit) { add_cost(i, j, CostFunc2{ -profit, 0, 0, -profit }); }

        // cost: submodular (i.e., cost[0][1] + cost[1][0] >= cost[0][0] + cost[1][1])
        void add_cost(Item i, Item j, CostFunc2 cost) {
            assert(i < _num);
            assert(j < _num);
            assert(i != j);
            add_cost(cost[0][0]);
            add_cost(i, CostFunc1{ 0, cost[1][0] - cost[0][0] });
            add_cost(j, CostFunc1{ 0, cost[1][1] - cost[1][0] });
            add_cost_01(i, j, (cost[0][1] + cost[1][0]) - (cost[0][0] + cost[1][1]));
        }
        void add_profit(Item i, Item j, const CostFunc2 &profit) { add_cost(i, j, neg(profit)); }

        // cost: submodular (i.e., cost(X) + cost(Y) >= cost(X | Y) + cost(X & Y))
        void add_cost(Item i, Item j, Item k, CostFunc3 cost) {
            assert(i < _num);
            assert(j < _num);
            assert(k < _num);
            assert(i != j);
            assert(j != k);
            assert(k != i);
            const Cost A = cost[0][0][0], B = cost[0][0][1];
            const Cost C = cost[0][1][0], D = cost[0][1][1];
            const Cost E = cost[1][0][0], F = cost[1][0][1];
            const Cost G = cost[1][1][0], H = cost[1][1][1];
            const Cost P = (A + D + F + G) - (B + C + E + H);
            if (P >= 0) {
                const Cost P1 = F - B, P2 = G - E, P3 = D - C;
                const Cost P12 = (C + E) - (A + G), P23 = (B + C) - (A + D), P31 = (B + E) - (A + F);
                add_cost(A);
                add_cost(i, CostFunc1{ 0, P1 });
                add_cost(j, CostFunc1{ 0, P2 });
                add_cost(k, CostFunc1{ 0, P3 });
                add_cost_01(i, j, P12);
                add_cost_01(j, k, P23);
                add_cost_01(k, i, P31);
                add_profit_all_1(std::array<Item, 3>{ i, j, k }, P);
            } else {
                const Cost P1 = C - G, P2 = B - D, P3 = E - F;
                const Cost P21 = (D + F) - (B + H), P32 = (F + G) - (E + H), P13 = (D + G) - (C + H);
                add_cost(H);
                add_cost(i, CostFunc1{ P1, 0 });
                add_cost(j, CostFunc1{ P2, 0 });
                add_cost(k, CostFunc1{ P3, 0 });
                add_cost_01(j, i, P21);
                add_cost_01(k, j, P32);
                add_cost_01(i, k, P13);
                add_profit_all_0(std::array<Item, 3>{ i, j, k }, -P);
            }
        }

        template <typename Container>
        auto add_profit_all_0(const Container& is, Cost profit) -> decltype(static_cast<Item>(*is.begin()), is.end(), void()) {
            assert(profit >= 0);
            if (is.size() == 0) {
                return add_profit(profit);
            } else if (is.size() == 1) {
                return add_profit(is[0], CostFunc1{ profit, 0 });
            } else if (is.size() == 2) {
                return add_profit_00(is[0], is[1], profit);
            }
            add_profit(profit);
            const Item aux = _num + _num_aux++;
            add_edge(S, aux, profit);
            for (Item i : is) {
                add_edge(aux, i, profit);
            }
        }
        template <typename Container>
        auto add_profit_all_1(const Container& is, Cost profit) -> decltype(static_cast<Item>(*is.begin()), is.end(), void()) {
            assert(profit >= 0);
            if (is.size() == 0) {
                return add_profit(profit);
            } else if (is.size() == 1) {
                return add_profit(is[0], CostFunc1{ 0, profit });
            } else if (is.size() == 2) {
                return add_profit_11(is[0], is[1], profit);
            }
            add_profit(profit);
            const Item aux = _num + _num_aux++;
            for (Item i : is) {
                add_edge(i, aux, profit);
            }
            add_edge(aux, T, profit);
        }

        auto min_cost() {
            atcoder::mf_graph<Cost> g(_num + _num_aux + 2);
            const std::size_t s = _num + _num_aux, t = s + 1;
            make_edges_for_cost1();
            for (const auto &[i, j, cost] : _edges) {
                std::size_t u = (i == S) ? s : (i == T) ? t : i;
                std::size_t v = (j == S) ? s : (j == T) ? t : j;
                g.add_edge(u, v, cost);
            }
            Cost ans = _cost0 + g.flow(s, t);
            auto x = g.min_cut(s);
            x.resize(_num);
            for (std::size_t i = 0; i < _num; ++i) {
                x[i] = not x[i];
            }
            return std::make_pair(ans, x);
        }
        auto max_profit() {
            auto res = min_cost();
            res.first = -res.first;
            return res;
        }
    private:
        static constexpr std::size_t S = ~0;
        static constexpr std::size_t T = ~1;

        std::size_t _num;
        std::size_t _num_aux = 0;
        Cost _cost0 = 0;
        std::vector<CostFunc1> _cost1;
        std::vector<std::tuple<Item, Item, Cost>> _edges{};

        void make_edges_for_cost1() {
            for (std::size_t i = 0; i < _num; ++i) {
                CostFunc1& cost = _cost1[i];
                if (cost[0] <= cost[1]) {
                    add_cost(cost[0]);
                    add_edge(S, i, cost[1] - cost[0]);
                } else {
                    add_cost(cost[1]);
                    add_edge(i, T, cost[0] - cost[1]);
                }
                cost = { 0, 0 };
            }
        }
        void add_edge(std::size_t i, std::size_t j, Cost cost) {
            assert(cost >= 0);
            assert(i == S or i == T or i < _num + _num_aux);
            assert(j == S or j == T or j < _num + _num_aux);
            assert(i != j);
            if (cost == 0) return;
            _edges.emplace_back(i, j, cost);
        }

        static constexpr Cost neg(Cost cost) { return -cost; }
        template <typename T>
        static constexpr CostFunc<T> neg(const CostFunc<T> &cost) { return { neg(cost[0]), neg(cost[1]) }; }
    };
} // namespace suisen


#endif // SUISEN_PROJECT_SELECTION
