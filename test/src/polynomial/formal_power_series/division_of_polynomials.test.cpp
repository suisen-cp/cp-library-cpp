#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/polynomial/formal_power_series.hpp"
using suisen::FormalPowerSeries;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    FormalPowerSeries<mint> f(n), g(m);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    for (int i = 0; i < m; ++i) {
        int coef;
        std::cin >> coef;
        g[i] = coef;
    }
    auto q = f / g, r = f % g;
    while (q.size() and q.back() == 0) q.pop_back();
    while (r.size() and r.back() == 0) r.pop_back();
    std::cout << q.size() << ' ' << r.size() << '\n';
    for (int i = 0; i < q.size(); ++i) {
        std::cout << q[i].val();
        if (i + 1 < q.size()) std::cout << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < r.size(); ++i) {
        std::cout << r[i].val();
        if (i + 1 < r.size()) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}