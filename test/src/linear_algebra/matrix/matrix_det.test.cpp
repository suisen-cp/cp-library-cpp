#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/matrix.hpp"

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
    std::cout << SquareMatrix<mint>::det(A).val() << '\n';
    return 0;
}