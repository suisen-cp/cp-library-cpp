#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>
#include <atcoder/modint>

#include "library/math/inv_mods.hpp"
#include "library/convolution/semi_relaxed_convolution_ntt.hpp"

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint& a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint& a) {
    out << a.val();
    return out;
}

namespace suisen {
    template <typename mint>
    std::vector<mint> exp(const std::vector<mint>& f) {
        inv_mods<mint> invs;
        const int n = f.size();
        std::vector<mint> df(n - 1);
        for (int i = 1; i < n; ++i) {
            df[i - 1] = i * f[i];
        }
        SemiRelaxedConvolutionNTT<mint> df_g(df);
        std::vector<mint> g(n);
        g[0] = 1;
        for (int i = 1; i < n; ++i) {
            g[i] = df_g.append(g[i - 1]) * invs[i];
        }
        return g;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> f(n);
    for (auto &e : f) std::cin >> e;

    std::vector<mint> exp_f = suisen::exp(f);
    for (int i = 0; i < n; ++i) {
        std::cout << exp_f[i] << " \n"[i == n - 1];
    }
}