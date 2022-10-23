#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#include <iostream>

#include "library/algebra/field/nimber.hpp"

int main() {
    using suisen::nimber64_t;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t --> 0) {
        nimber64_t x, y;
        std::cin >> x >> y;
        std::cout << nimber64_t(x) * y << '\n';
    }

    return 0;
}