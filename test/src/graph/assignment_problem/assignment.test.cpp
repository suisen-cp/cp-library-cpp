#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include <iostream>

#include "library/graph/assignment_problem.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector a(n, std::vector<long long>(n));
    for (auto &row : a) for (auto &e : row) std::cin >> e;

    auto [cost, assignment] = suisen::assignment_problem(a);
    std::cout << cost << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << assignment[i] << " \n"[i == n - 1];
    }
}