#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <iostream>

#include "library/datastructure/compressed_wavelet_matrix.hpp"

using suisen::CompressedWaveletMatrix;

constexpr int MAX_LOG = 18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    CompressedWaveletMatrix<int, MAX_LOG> wm(a);
    while (q --> 0) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << wm.range_kth_smallest(l, r, k) << '\n';
    }
    return 0;
}