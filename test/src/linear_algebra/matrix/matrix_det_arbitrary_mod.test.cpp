#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include <iostream>
#include <atcoder/modint>

#include "library/linear_algebra/matrix.hpp"

using mint = atcoder::modint;
using suisen::Matrix;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    mint::set_mod(m);
    Matrix<mint> A(n);
    for (int i = 0; i < n; ++i) for (int j = 0, val; j < n; ++j) {
        std::cin >> val, A[i][j] = val;
    }
    std::cout << A.det_arbitrary_mod().val() << '\n';
    return 0;
}