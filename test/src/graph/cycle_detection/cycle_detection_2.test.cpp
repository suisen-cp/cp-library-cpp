#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include <algorithm>
#include <iostream>

#include "library/graph/cycle_detection.hpp"
using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        long long u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v, i);
    }

    const auto optional_cycle = get_cycle_values<GraphType::DIRECTED>(g);
    if (optional_cycle.has_value()) {
        const auto &cycle = *optional_cycle;
        const int sz = cycle.size();
        std::cout << sz << '\n';
        for (int i = 0; i < sz; ++i) {
            std::cout << cycle[i] << '\n';
        }
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}