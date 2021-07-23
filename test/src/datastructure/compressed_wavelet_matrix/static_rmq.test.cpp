#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <iostream>

#include "library/datastructure/compressed_wavelet_matrix.hpp"

using suisen::CompressedWaveletMatrix;

constexpr int MAX_LOG = 19;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    CompressedWaveletMatrix<int, MAX_LOG> wm(a);
    while (q --> 0) {
        int l, r;
        std::cin >> l >> r;
        std::cout << wm.range_min(l, r) << '\n';
    }
    return 0;
}