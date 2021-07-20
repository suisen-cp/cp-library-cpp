#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include <iostream>
#include <atcoder/modint>

#include "library/math/gaussian_elimination.hpp"

using mint = atcoder::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector A(n, std::vector(m, mint(0)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val;
            std::cin >> val;
            A[i][j] = val;
        }
    }
    std::vector<mint> b(n);
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        b[i] = val;
    }
    suisen::GaussianEliminationArithmetic<mint> solution(A, b);
    if (solution.has_solution()) {
        int r = solution.dimension();
        const auto c = *solution.get_solution();
        const auto &basis = solution.get_basis();
        std::cout << r << '\n';
        for (int i = 0; i < m; ++i) {
            std::cout << c[i].val() << " \n"[i == m - 1];
        }
        for (const auto &x : basis) {
            for (int i = 0; i < m; ++i) {
                std::cout << x[i].val() << " \n"[i == m - 1];
            }
        }
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}