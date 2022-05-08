#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_2_64"

#include <iostream>
#include "library/convolution/convolution_2_64.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned long long> a(n), b(m);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;

    std::vector<unsigned long long> c = suisen::internal::convolution_2_64::convolution_6mod(a, b);
    for (std::size_t i = 0; i < n + m - 1; ++i) {
        std::cout << c[i] << " \n"[i == n + m - 2];
    }
    return 0;
}