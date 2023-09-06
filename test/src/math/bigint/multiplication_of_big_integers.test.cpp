#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include <iostream>

#include "library/math/bigint.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t --> 0) {
        using suisen::bigint;

        bigint a, b;
        std::cin >> a >> b;
        std::cout << a * b << '\n';
    }
}