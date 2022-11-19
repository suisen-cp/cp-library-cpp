#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

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

#include "library/linear_algebra/characteristic_polynomial.hpp"

using suisen::Matrix;
using suisen::characteristic_polynomial;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;

    Matrix<mint> A(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) std::cin >> A[i][j];

    std::vector<mint> p = characteristic_polynomial(A);
    for (int i = 0; i <= n; ++i) std::cout << p[i] << " \n"[i == n];

    return 0;
}