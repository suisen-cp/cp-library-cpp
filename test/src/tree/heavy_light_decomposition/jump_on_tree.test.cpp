#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <iostream>

#include "library/tree/heavy_light_decomposition.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    suisen::HeavyLightDecomposition hld(g);

    while (q --> 0) {
        int u, v, d;
        std::cin >> u >> v >> d;
        std::cout << hld.jump(u, v, d) << '\n';
    }

    return 0;
}