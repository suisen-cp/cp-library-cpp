#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/matrix.hpp"

using mint = atcoder::modint998244353;
using suisen::Matrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix<mint> A(n, m), B(m, k);
    for (int i = 0; i < n; ++i) for (int j = 0, val; j < m; ++j) {
        std::cin >> val, A[i][j] = val;
    }
    for (int i = 0; i < m; ++i) for (int j = 0, val; j < k; ++j) {
        std::cin >> val, B[i][j] = val;
    }
    Matrix<mint> C = A * B;
    for (int i = 0; i < n; ++i) for (int j = 0; j < k; ++j) {
        std::cout << C[i][j].val() << " \n"[j == k - 1];
    }
    return 0;
}