#define PROBLEM "https://judge.yosupo.jp/problem/tree_decomposition_width_2"

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

    const auto opt_res = td.decomp();
    if (not opt_res.has_value()) {
        std::cout << -1 << '\n';
    } else {
        const auto& nodes = *opt_res;
        const int k = nodes.size();
        std::cout << "s td " << k << ' ' << 2 << ' ' << n << '\n';
        for (int i = 0; i < k; ++i) {
            std::cout << "b " << i + 1;
            for (int v : nodes[i].bag) std::cout << ' ' << v + 1;
            std::cout << '\n';
        }
        for (int i = 0; i < k; ++i) for (int j : nodes[i].adj) if (i < j) {
            std::cout << i + 1 << ' ' << j + 1 << '\n';
        }
    }

    return 0;
}