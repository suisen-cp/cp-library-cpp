#define PROBLEM "https://atcoder.jp/contests/abc230/tasks/abc230_h"

#include <iostream>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/math/inv_mods.hpp"
#include "library/convolution/relaxed_convolution.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<mint> c(n + 1);
    for (int i = 0; i < m; ++i) {
        int w;
        std::cin >> w;
        c[w] = 1;
    }
    suisen::inv_mods<mint> invs(n);

    suisen::RelaxedConvolution<mint> h{ [](const auto& f, const auto &g) { return atcoder::convolution(f, g); } };

    std::vector<mint> f(n), g(n);
    for (int w = 1; w < n; ++w) {
        for (int i = 1; i * w - 1 < n; ++i) {
            g[i * w - 1] += w * (f[w - 1] + c[w]);
        }
        f[w] = h.append((w == 1) + f[w - 1], g[w - 1]) * invs[w];
    }
    f.erase(f.begin());

    for (const auto &e : f) {
        std::cout << e.val() << '\n';
    }

    return 0;
}