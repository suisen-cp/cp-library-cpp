#ifndef SUISEN_K_PROJECT_SELECTION
#define SUISEN_K_PROJECT_SELECTION

#include <type_traits>
#include <vector>

#include "library/optimization/project_selection_problem.hpp"

namespace suisen {
    template <typename Cost>
    struct KProjectSelection {
        using Item = std::size_t;
        using CostFunc0 = Cost;
        using CostFunc1 = std::vector<CostFunc0>;
        using CostFunc2 = std::vector<CostFunc1>;

        KProjectSelection() = default;

        template <typename Container, std::enable_if_t<std::is_integral_v<typename Container::value_type>, std::nullptr_t> = nullptr>
        explicit KProjectSelection(const Container& ks) : _num(ks.size()), _ks(ks.begin(), ks.end()), _x(_num) {
            std::size_t id = 0;
            for (std::size_t i = 0; i < _num; ++i) {
                assert(_ks[i] >= 1);
                _x[i].resize(_ks[i]);
                _x[i][0] = ~0;
                for (std::size_t d = 1; d < _ks[i]; ++d) {
                    _x[i][d] = id++;
                }
            }
            // [x_i < d] <===> _x[i][d]
            // [x_i = d] <===> ~_x[i][1] & ~_x[i][2] & ... & ~_x[i][d] & _x[i][d+1] & _x[i][d+2] & ... & _x[i][k_i]
            _psp = ProjectSelection<Cost>(id);
            for (std::size_t i = 0; i < _num; ++i) {
                for (std::size_t d = 1; d < _ks[i] - 1; ++d) {
                    _psp.add_cost_10(_x[i][d], _x[i][d + 1], INF);
                }
            }
        }
        KProjectSelection(std::size_t n, std::size_t k) : KProjectSelection(std::vector<std::size_t>(n, k)) {}

        void add_cost(CostFunc0 cost) { _psp.add_cost(cost); }
        void add_profit(CostFunc0 profit) { _psp.add_profit(profit); }

        void add_cost(Item i, const CostFunc1& cost) {
            assert(i < _num);
            assert(cost.size() == _ks[i]);
            _psp.add_cost(cost[_ks[i] - 1]);
            for (std::size_t d = 1; d < _ks[i]; ++d) {
                _psp.add_cost(_x[i][d], { 0, cost[d - 1] - cost[d] });
            }
        }
        void add_profit(Item i, CostFunc1 profit) {
            for (auto &p : profit) p = -p;
            add_cost(i, profit);
        }

        // cost: Monge (i.e., cost[i][j]+cost[i+1][j+1] <= cost[i+1][j]+cost[i][j+1])
        void add_cost(Item i, Item j, CostFunc2 cost) {
            assert(i < _num);
            assert(j < _num);
            assert(i != j);

            assert(cost.size() == _ks[i]);

            CostFunc1 cost_i(_ks[i]), cost_j(_ks[j]);
            for (std::size_t di = 0; di < _ks[i]; ++di) {
                assert(cost[di].size() == _ks[j]);
                cost_i[di] = cost[di][0];
                for (std::size_t dj = 0; dj < _ks[j]; ++dj) {
                    cost[di][dj] -= cost_i[di];
                }
            }
            for (std::size_t dj = 0; dj < _ks[j]; ++dj) {
                cost_j[dj] = cost[0][dj];
                for (std::size_t di = 0; di < _ks[i]; ++di) {
                    cost[di][dj] -= cost_j[dj];
                }
            }
            add_cost(i, cost_i);
            add_cost(j, cost_j);

            for (std::size_t di = 0; di < _ks[i]; ++di) assert(cost[di][0] == 0);
            for (std::size_t dj = 0; dj < _ks[j]; ++dj) assert(cost[0][dj] == 0);

            for (std::size_t di = 1; di < _ks[i]; ++di) {
                for (std::size_t dj = 1; dj < _ks[j]; ++dj) {
                    Cost cost_00 = cost[di][dj] - cost[di][dj - 1] - cost[di - 1][dj] + cost[di - 1][dj - 1];
                    // Monge
                    assert(cost_00 <= 0);
                    _psp.add_profit_00(_x[i][di], _x[j][dj], -cost_00);
                }
            }
        }

        std::pair<Cost, std::vector<int>> min_cost() {
            auto [ans, x_bin] = _psp.min_cost();
            std::vector<int> x(_num);
            for (std::size_t i = 0; i < _num; ++i) for (std::size_t di = 1; di < _ks[i]; ++di) {
                x[i] += not x_bin[_x[i][di]];
            }
            return { ans, x };
        }

        std::pair<Cost, std::vector<int>> max_profit() {
            auto res = min_cost();
            res.first = -res.first;
            return res;
        }

    private:
        static constexpr Cost INF = std::numeric_limits<Cost>::max() / 2;

        std::size_t _num;
        std::vector<std::size_t> _ks;
        std::vector<std::vector<std::size_t>> _x;
        ProjectSelection<Cost> _psp;
    };
} // namespace suisen


#endif // SUISEN_K_PROJECT_SELECTION
