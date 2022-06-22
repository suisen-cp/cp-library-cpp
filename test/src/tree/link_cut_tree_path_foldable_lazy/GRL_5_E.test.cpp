#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E"

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
    for (int p = 0; p < n; ++p) {
        int k;
        std::cin >> k;
        while (k --> 0) {
            int v;
            std::cin >> v;
            DynamicTree::link(nodes[p], nodes[v]);
        }
    }
    const int root = 0;

    long long wsum = 0;
    int q;
    std::cin >> q;
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int v, w;
            std::cin >> v >> w;
            wsum += w;
            DynamicTree::apply(nodes[v], nodes[root], w);
        } else {
            int v;
            std::cin >> v;
            std::cout << DynamicTree::prod(nodes[v], nodes[root]) - wsum << '\n';
        }
    }
    return 0;
}