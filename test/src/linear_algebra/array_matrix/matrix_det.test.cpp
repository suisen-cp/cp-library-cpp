#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/array_matrix.hpp"

using mint = atcoder::modint998244353;
using matrix = suisen::SquareArrayMatrix<mint, 500>;

int main() {
    int n;
    std::cin >> n;
    matrix A = matrix::e1();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            std::cin >> val;
            A[i][j] = val;
        }
    }
    std::cout << A.det().val() << '\n';
    return 0;
}