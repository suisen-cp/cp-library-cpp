#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>
#include <numeric>

#include "library/tree/link_cut_tree.hpp"

constexpr int op(int, int) { return {}; }
constexpr int e() { return {}; }
constexpr int toggle(int) { return {}; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using DynamicTree = suisen::LinkCutTree<int, op, e, toggle>;

    int n, q;
    std::cin >> n >> q;

    DynamicTree::init_pool(n);

    std::vector<int> ids(n);
    std::iota(ids.begin(), ids.end(), 0);
    auto nodes = DynamicTree::make_nodes(ids);

    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        DynamicTree::link(nodes[i], nodes[p]);
    }
    DynamicTree::evert(nodes[0]);
    
    while (q --> 0) {
        int u, v;
        std::cin >> u >> v;
        std::cout << DynamicTree::get(DynamicTree::lca(nodes[u], nodes[v])) << '\n';
    }

    return 0;
}