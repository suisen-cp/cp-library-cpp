#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include <iostream>

#include "library/tree/link_cut_tree.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}
long long toggle(long long x) {
    return x;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (auto& e : a) std::cin >> e;

    using DynamicTree = suisen::LinkCutTree<long long, op, e, toggle>;

    DynamicTree::init_pool(n);

    auto nodes = DynamicTree::make_nodes(a);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        DynamicTree::link(nodes[u], nodes[v]);
    }

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            DynamicTree::cut(nodes[u], nodes[v]);
            DynamicTree::link(nodes[w], nodes[x]);
        } else if (query_type == 1) {
            int p, x;
            std::cin >> p >> x;
            DynamicTree::apply(nodes[p], [x](long long v) { return v + x; });
        } else {
            int u, v;
            std::cin >> u >> v;
            std::cout << DynamicTree::prod(nodes[u], nodes[v]) << '\n';
        }
    }

    return 0;
}
