#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <iostream>

#include "library/datastructure/union_find/persistent_union_find.hpp"

using suisen::PersistentUnionFind;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;

    PersistentUnionFind::init_pool(1400000);

    std::vector<PersistentUnionFind> ufs;
    ufs.push_back(PersistentUnionFind(n));

    for (int time = 1; time <= q; ++time) {
        int query_type, k, u, v;
        std::cin >> query_type >> k >> u >> v;
        ++k;
        if (query_type == 0) {
            ufs.push_back(ufs[k].merge(u, v).first);
        } else {
            ufs.push_back(ufs[time - 1]);
            std::cout << ufs[k].same(u, v) << '\n';
        }
    }

    return 0;
}