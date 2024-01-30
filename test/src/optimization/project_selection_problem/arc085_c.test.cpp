#define PROBLEM "https://atcoder.jp/contests/arc085/tasks/arc085_c"

#include "library/optimization/project_selection_problem.hpp"

#include <iostream>

int main() {
    int n;
    std::cin >> n;

    using Cost = long long;

    Cost inf = std::numeric_limits<Cost>::max() / 2;

    std::vector<Cost> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    suisen::ProjectSelection<Cost> psp(n + 1);

    for (int x = 1; x <= n; ++x) {
        psp.add_profit_0(x, a[x]);
        for (int y = 2 * x; y <= n; y += x) {
            psp.add_cost_01(y, x, inf);
        }
    }

    std::cout << psp.max_profit().first << std::endl;
}