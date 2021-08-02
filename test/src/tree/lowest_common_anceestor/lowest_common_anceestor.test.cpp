#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>

#include "library/tree/lowest_common_ancestor.hpp"
using suisen::LowestCommonAncestor;

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
    LowestCommonAncestor lca(g);
    for (int i = 0; i < q; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca(u, v) << '\n';
    }
    return 0;
}