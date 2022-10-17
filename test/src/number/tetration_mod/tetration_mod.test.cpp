#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"

#include <iostream>

#include "library/number/tetration_mod.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int a, b, m;
        std::cin >> a >> b >> m;
        std::cout << suisen::tetration_mod(a, b, m) << '\n';
    }

    return 0;
}