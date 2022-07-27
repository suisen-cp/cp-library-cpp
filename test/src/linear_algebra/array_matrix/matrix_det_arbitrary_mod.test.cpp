#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/array_matrix.hpp"

using mint = atcoder::modint;
using matrix = suisen::SquareArrayMatrix<mint, 500>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    mint::set_mod(m);

    matrix A = matrix::e1();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            std::cin >> val;
            A[i][j] = val;
        }
    }
    std::cout << A.det_arbitrary_mod().val() << '\n';
    return 0;
}