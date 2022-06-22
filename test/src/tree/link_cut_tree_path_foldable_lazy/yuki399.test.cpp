#define PROBLEM "https://yukicoder.me/problems/no/399"

#include <iostream>

#include "library/tree/link_cut_tree_path_foldable_lazy.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}
long long mapping(long long f, long long x, int len) {
    return x + f * len;
}
long long composition(long long f, long long g) {
    return f + g;
}
long long id() {
    return 0;
}
long long toggle(long long x) {
    return x;
}

using DynamicTree = suisen::LinkCutTreePathFoldableLazy<long long, op, e, long long, mapping, composition, id, toggle>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    DynamicTree::init_pool(n);

    auto nodes = DynamicTree::make_nodes(std::vector<long long>(n));
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        DynamicTree::link(nodes[u], nodes[v]);
    }

    long long ans = 0;
    int q;
    std::cin >> q;
    while (q --> 0) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        DynamicTree::apply(nodes[u], nodes[v], 1);
        ans += DynamicTree::prod(nodes[u], nodes[v]);
    }
    std::cout << ans << '\n';
    return 0;
}