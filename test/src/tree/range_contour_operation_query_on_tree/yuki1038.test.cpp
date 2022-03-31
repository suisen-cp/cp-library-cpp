#define PROBLEM "https://yukicoder.me/problems/no/1038"

#include <iostream>

#include "library/tree/range_contour_operation_query_on_tree.hpp"

long long mapping(long long f, long long x) {
    return f + x;
}
long long composition(long long x, long long y) {
    return x + y;
}
long long id() {
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    suisen::RangeContourOperationQueryOnTree<long long, long long, mapping, composition, id> g(n, 0LL);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g.add_edge(u, v);
    }
    g.build();

    for (int i = 0; i < q; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        --x, ++y;
        std::cout << g.get(x) << '\n';
        g.apply(x, 0, y, z);
    }

    return 0;
}