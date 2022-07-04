#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include "library/datastructure/union_find/union_find.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    suisen::UnionFind uf(n);
    while (q --> 0) {
        int query_type, u, v;
        std::cin >> query_type >> u >> v;
        if (query_type == 0) {
            uf.merge(u, v);
        } else {
            std::cout << uf.same(u, v) << '\n';
        }
    }
    return 0;
}