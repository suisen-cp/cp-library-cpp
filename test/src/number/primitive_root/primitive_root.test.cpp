#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include <iostream>

#include "library/number/primitive_root.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while (q --> 0) {
        long long p;
        std::cin >> p;
        std::cout << suisen::primitive_root(p) << '\n';
    }

    return 0;
}