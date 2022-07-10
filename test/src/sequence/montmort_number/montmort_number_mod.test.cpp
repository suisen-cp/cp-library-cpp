#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint;

#include "library/sequence/montmort_number.hpp"
using suisen::montmort_number;

int main() {
    int n, m;
    std::cin >> n >> m;
    mint::set_mod(m);
    std::vector<mint> res = montmort_number<mint>(n);
    for (int i = 1; i <= n; ++i) {
        std::cout << res[i].val() << " \n"[i == n];
    }
    return 0;
}