#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"

#include <iostream>

#include "library/datastructure/weighted_union_find.hpp"
using suisen::WeightedUnionFind;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    WeightedUnionFind<long long, std::plus<long long>, std::negate<long long>> uf(n);
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x, y, z;
            std::cin >> x >> y >> z;
            uf.merge(x, y, z);
        } else {
            int x, y;
            std::cin >> x >> y;
            if (uf.same(x, y)) {
                std::cout << uf.diff(x, y) << '\n';
            } else {
                std::cout << '?' << '\n';
            }
        }
    }
    return 0;
}