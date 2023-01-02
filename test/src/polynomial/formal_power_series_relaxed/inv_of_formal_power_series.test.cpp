#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include <iostream>
#include <atcoder/modint>
#include "library/polynomial/formal_power_series_relaxed.hpp"

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    
    suisen::RelaxedInv<mint> inv_f;
    for (int i = 0; i < n; ++i) {
        mint v;
        std::cin >> v;
        std::cout << inv_f.append(v) << " \n"[i == n - 1];
    }
}