#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <iostream>

#include "library/tree/lowest_common_ancestor.hpp"
#include "library/tree/level_ancestor.hpp"

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

    suisen::LowestCommonAncestor lca(g);
    suisen::LevelAncestor la(g);

    while (q --> 0) {
        int u, v, d;
        std::cin >> u >> v >> d;

        const int a = lca(u, v);
        const int du = la.get_depth(u) - la.get_depth(a);
        const int dv = la.get_depth(v) - la.get_depth(a);
        if (d <= du) {
            std::cout << la(u, d) << '\n';
        } else if (d <= du + dv) {
            std::cout << la(v, du + dv - d) << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
    
    return 0;
}