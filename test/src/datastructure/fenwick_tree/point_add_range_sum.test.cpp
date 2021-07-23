#include <iostream>

#include "library/datastructure/fenwick_tree.hpp"

using suisen::FenwickTree;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;
    FenwickTree<long long> ft(std::move(a));
    while (q --> 0) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int p, x;
            std::cin >> p >> x;
            ft[p] += x;
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << ft(l, r) << '\n';
        }
    }
    return 0;
}