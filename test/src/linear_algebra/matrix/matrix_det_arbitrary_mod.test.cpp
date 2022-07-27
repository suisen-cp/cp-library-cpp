#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/matrix.hpp"

using mint = atcoder::modint;
using suisen::SquareMatrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    mint::set_mod(m);
    SquareMatrix<mint> A(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int val;
        std::cin >> val;
        A[i][j] = val;
    }
    std::cout << SquareMatrix<mint>::det_arbitrary_mod(A).val() << '\n';
    return 0;
}