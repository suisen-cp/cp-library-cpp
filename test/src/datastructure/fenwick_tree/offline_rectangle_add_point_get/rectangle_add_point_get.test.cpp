#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"

#include "library/datastructure/fenwick_tree/offline_rectangle_add_point_get.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    suisen::OfflineRectangleAddPointGet<long long> processor;

    for (int i = 0; i < n; ++i) {
        int l, d, r, u, w;
        std::cin >> l >> d >> r >> u >> w;
        processor.add(l, r, d, u, w);
    }
    for (int i = 0; i < q; ++i) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int l, d, r, u, w;
            std::cin >> l >> d >> r >> u >> w;
            processor.add(l, r, d, u, w);
        } else {
            int x, y;
            std::cin >> x >> y;
            processor.get(x, y);
        }
    }

    for (long long ans : processor.solve()) {
        std::cout << ans << '\n';
    }
}