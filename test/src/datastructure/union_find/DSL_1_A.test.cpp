#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include <iostream>

#include "library/datastructure/union_find.hpp"
using suisen::UnionFind;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    UnionFind uf(n);
    for (int i = 0; i < q; ++i) {
        int t, x, y;
        std::cin >> t >> x >> y;
        if (t == 0) {
            uf.merge(x, y);
        } else {
            std::cout << int(uf.same(x, y)) << '\n';
        }
    }
    return 0;
}