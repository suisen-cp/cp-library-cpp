#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <iostream>
#include <atcoder/modint>

#include "library/polynomial/berlekamp_massey.hpp"

using mint = atcoder::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::cin >> n;
    std::vector<mint> s(n);
    for (auto &e : s) {
        int v;
        std::cin >> v, e = v;
    }
    std::vector<mint> C = suisen::find_linear_recuurence(s);
    std::cout << C.size() - 1 << '\n';
    for (std::size_t i = 1; i < C.size(); ++i) {
        std::cout << C[i].val();
        if (i + 1 != C.size()) std::cout << ' ';
    }
    std::cout << '\n';

    return 0;
}