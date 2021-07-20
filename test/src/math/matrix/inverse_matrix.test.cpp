#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include <iostream>
#include <atcoder/modint>

#include "library/math/matrix.hpp"

using mint = atcoder::modint998244353;
using suisen::SquareMatrix;

int main() {
    int n;
    std::cin >> n;
    SquareMatrix<mint> A(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            std::cin >> val;
            A[i][j] = val;
        }
    }
    auto inv = SquareMatrix<mint>::inv(std::move(A));
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