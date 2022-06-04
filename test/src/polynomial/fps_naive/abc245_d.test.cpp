#define PROBLEM "https://atcoder.jp/contests/abc245/tasks/abc245_d"

#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/polynomial/fps_naive.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    suisen::FPSNaive<mint> a(n + 1), c(n + m + 1);

    for (auto &e : a) {
        int v;
        std::cin >> v;
        e = v;
    }
    for (auto &e : c) {
        int v;
        std::cin >> v;
        e = v;
    }

    auto [b, r] = div_mod(c, a);
    assert(r == suisen::FPSNaive<mint>{});

    for (auto &e : b) {
        int v = e.val();
        if (v > 100) {
            std::cout << v - mint::mod() << '\n';
        } else {
            std::cout << +v << '\n';
        }
    }
}