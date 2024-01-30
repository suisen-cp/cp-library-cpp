#define PROBLEM "https://atcoder.jp/contests/arc129/tasks/arc129_e"

#include "library/optimization/k_project_selection_problem.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    suisen::KProjectSelection<long long> k_psp(n, m);

    std::vector a(n, std::vector<long long>(m));
    std::vector c(n, std::vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j] >> c[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        k_psp.add_cost(i, c[i]);

        for (int j = i + 1; j < n; ++j) {
            long long w;
            std::cin >> w;

            std::vector cij(m, std::vector<long long>(m));
            for (int xi = 0; xi < m; ++xi) for (int xj = 0; xj < m; ++xj) {
                cij[xi][xj] = w * std::abs(a[i][xi] - a[j][xj]);
            }

            k_psp.add_cost(i, j, cij);
        }
    }

    std::cout << k_psp.min_cost().first << std::endl;
}
