#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include "library/convolution/min_plus_convolution.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;

    std::vector<int> c = suisen::min_plus_convolution_convex_arbitrary(a, b);
    for (int i = 0; i < n + m - 1; ++i) {
        std::cout << c[i];
        if (i + 1 != n + m - 1) std::cout << ' ';
    }
    std::cout << '\n';
}