#include <iostream>
#include <limits>
#include <tuple>

#include "library/graph/tree_decomposition_tw2.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string waste_input;
    std::cin >> waste_input >> waste_input;

    int n, m;
    std::cin >> n >> m;

    suisen::TreeDecompositionTW2 td(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        td.add_edge(u, v);
    }

    const auto opt_res = td.nice_decomp();
    if (not opt_res.has_value()) {
        std::cout << -1 << '\n';
    } else {
        const auto& [bag, edges] = *opt_res;
        const int k = bag.size();
        suisen::TreeDecompositionTW2::assert_nice(bag, edges, 0);
        assert(k <= 3 * n + m + 10);
        std::cout << "s td " << k << ' ' << 2 << ' ' << n << '\n';
        for (int i = 0; i < k; ++i) {
            std::cout << "b " << i + 1;
            for (int v : bag[i]) std::cout << ' ' << v + 1;
            std::cout << '\n';
        }
        for (auto [u, v] : edges) {
            std::cout << u + 1 << ' ' << v + 1 << '\n';
        }
    }

    return 0;
}