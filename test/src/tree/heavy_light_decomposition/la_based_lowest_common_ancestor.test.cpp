#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>

#include "library/tree/heavy_light_decomposition.hpp"
using suisen::HeavyLightDecomposition;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    HeavyLightDecomposition hld(g);

    auto lca = [&](int u, int v) -> int {
        int du = hld.get_depth(u);
        int dv = hld.get_depth(v);
        if (du < dv) {
            std::swap(u, v);
            std::swap(du, dv);
        }

        int l = -1, r = dv;
        while (r - l > 1) {
            int k = (l + r) >> 1;
            (hld.la(u, k + (du - dv)) == hld.la(v, k) ? r : l) = k;
        }
        return hld.la(v, r);
    };

    for (int query_id = 0; query_id < q; ++query_id) {
        int u, v;
        std::cin >> u >> v;
        
        std::cout << lca(u, v) << '\n';
    }

    return 0;
}