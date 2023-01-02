#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

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

    int z = 0;
    std::vector<mint> f;
    
    suisen::RelaxedExp<mint> exp_f;
    for (int i = 0; i < n; ++i) {
        mint v;
        std::cin >> v;
        if (f.empty() and v == 0) {
            ++z;
        } else {
            f.push_back(v);
        }
    }
    if (z == n) z = 2 * n;
    if (z % 2 == 1) {
        std::cout << -1 << '\n';
    } else {
        int k = n - z / 2;
        f.resize(k);
        std::vector<mint> res(z / 2, 0);
        suisen::RelaxedSqrt<mint> sqrt_f;
        for (int i = 0; i < k; ++i) {
            auto opt_gi = sqrt_f.append(f[i]);
            if (not opt_gi) {
                std::cout << -1 << '\n';
                return 0;
            }
            res.push_back(*opt_gi);
        }
        for (int i = 0; i < n; ++i) {
            std::cout << res[i].val() << " \n"[i == n - 1];
        }
    }
}