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

#include <chrono>

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

    std::vector<std::tuple<int, int, int>> qs(q);
    for (auto &[x, y, z] : qs) {
        std::cin >> x >> y >> z;
        --x, ++y;
    }
    std::vector<long long> ans(q);

    auto t1 = std::chrono::system_clock::now();
    g.build();
    auto t2 = std::chrono::system_clock::now();
    for (int i = 0; i < q; ++i) {
        const auto &[x, y, z] = qs[i];
        ans[i] = g.get(x);
        g.apply(x, 0, y, z);
    }
    auto t3 = std::chrono::system_clock::now();

    for (auto &e : ans) std::cout << e << '\n';

    auto build_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    auto query_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();

    std::cerr << "build : " << build_time_ms << " ms" << std::endl;
    std::cerr << "query : " << query_time_ms << " ms" << std::endl;

    return 0;
}