#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include <iostream>

#include "library/number/util.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t --> 0) {
        uint64_t a;
        int k;
        std::cin >> a >> k;
        std::cout << suisen::floor_kth_root(a, k) << '\n';
    }
    return 0;
}