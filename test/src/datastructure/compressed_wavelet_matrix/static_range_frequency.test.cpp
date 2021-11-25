#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include <iostream>

#include "library/datastructure/compressed_wavelet_matrix.hpp"
using suisen::CompressedWaveletMatrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int &e : a) {
        std::cin >> e;
    }
    CompressedWaveletMatrix<int, 19> wm(a);
    while (q --> 0) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << wm.rank(x, r) - wm.rank(x, l) << '\n';
    }
    return 0;
}