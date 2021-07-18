#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>
#include <vector>
#include <library/tree/euler_tour.hpp>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    suisen::EulerTour et(g);
    for (int i = 0; i < q; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << et.lca(u, v) << '\n';
    }
    return 0;
}