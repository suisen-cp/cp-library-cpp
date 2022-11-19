#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

#include "library/linear_algebra/array_matrix.hpp"

constexpr int N = 500;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using matrix = suisen::SquareArrayMatrix<mint, N>;

    matrix A = matrix::e1();

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        std::cin >> A[i][j];
    }
    auto opt_inv = A.safe_inv();
    if (not opt_inv.has_value()) {
        std::cout << -1 << std::endl;
    } else {
        auto B = std::move(*opt_inv);
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            std::cout << B[i][j] << " \n"[j == n - 1];
        }
    }

    return 0;
}