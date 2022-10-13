#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include <iostream>

#include <atcoder/modint>

#include "library/linear_algebra/hafnian.hpp"

using mint = atcoder::modint998244353;

int main() {
    int n;
    std::cin >> n;
    std::vector mat(n, std::vector<int>(n));
    for (auto &row : mat) for (auto &elm : row) std::cin >> elm;
    std::cout << suisen::hafnian<mint>(mat).val() << std::endl;
}