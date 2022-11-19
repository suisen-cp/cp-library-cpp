#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/matrix.hpp"

using mint = atcoder::modint998244353;
using suisen::Matrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    Matrix<mint> A(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0, val; j < n; ++j) {
            std::cin >> val, A[i][j] = val;
        }
    }
    auto inv = A.safe_inv();
    if (inv.has_value()) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << (*inv)[i][j].val() << " \n"[j == n - 1];
            }
        }
    } else {
        std::cout << -1 << '\n';
    }
    return 0;
}