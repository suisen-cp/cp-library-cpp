#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <numeric>

#include "library/tree/contour_aggregation_query_on_tree.hpp"

int op(int x, int y) {
    return x + y;
}
int e() {
    return 0;
}

void test() {
    std::vector<std::vector<int>> g {
        { 1, 8, 16 },       // 0
        { 0, 2, 3 },        // 1
        { 1 },              // 2
        { 1, 4, 7 },        // 3
        { 3, 5, 6 },        // 4
        { 4 },              // 5
        { 4 },              // 6
        { 3 },              // 7
        { 0, 9, 10 },       // 8
        { 8 },              // 9
        { 8, 11, 15 },      // 10
        { 10, 12, 13, 14 }, // 11
        { 11 },             // 12
        { 11 },             // 13
        { 11 },             // 14
        { 10 },             // 15
        { 0, 17, 18, 20 },  // 16
        { 16 },             // 17
        { 16, 19 },         // 18
        { 18 },             // 19
        { 16, 21, 24 },     // 20
        { 20, 22, 23 },     // 21
        { 21 },             // 22
        { 21 },             // 23
        { 20 }              // 24
    };

    const int n = g.size();
    suisen::ContourAggregationQueryOnTree<int, op, e> contour_aggregator(n);
    for (int i = 0; i < n; ++i) {
        for (int j : g[i]) if (i < j) {
            contour_aggregator.add_edge(i, j);
        }
    }
    std::vector<int> dat(n);
    std::iota(dat.begin(), dat.end(), 0);
    contour_aggregator.build(dat);

    auto naive = [&](int k, int d) {
        int res = 0;
        auto dfs = [&](auto dfs, int u, int p, int dep) -> void {
            if (dep == d) res += dat[u];
            for (int v : g[u]) {
                if (v == p) continue;
                dfs(dfs, v, u, dep + 1);
            }
        };
        dfs(dfs, k, -1, 0);
        return res;
    };

    for (int i = 0; i < n; ++i) {
        for (int d = 0; d <= n; ++d) {
            int sum1 = contour_aggregator.prod(i, d);
            int sum2 = naive(i, d);
            if (sum1 != sum2) {
                std::cout << "failed in the cese (" << i << ", " << d << "):" << std::endl;
                std::cout << "  expected : " << sum2 << std::endl;
                std::cout << "  actual   : " << sum1 << std::endl;
            }
        }
    }
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}