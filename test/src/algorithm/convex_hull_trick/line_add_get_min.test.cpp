#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <iostream>
#include <tuple>
#include <vector>

#include "library/algorithm/convex_hull_trick.hpp"
using suisen::ConvexHullTrick;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    ConvexHullTrick<long long> cht;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        cht.add_line(a, b);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            long long a, b;
            std::cin >> a >> b;
            cht.add_line(a, b);
        } else {
            int x;
            std::cin >> x;
            std::cout << (long long) cht.query(x) << '\n';
        }
    }
    return 0;
}