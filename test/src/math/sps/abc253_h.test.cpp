#define PROBLEM "https://atcoder.jp/contests/abc253/tasks/abc253_Ex"

#include <iostream>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/util/subset_iterator.hpp"
#include "library/linear_algebra/count_spanning_trees.hpp"
#include "library/math/factorial.hpp"
#include "library/math/sps.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> edges(m);

    for (auto& [u, v] : edges) {
        std::cin >> u >> v;
        --u, --v;
    }

    suisen::FPSNaive<mint>::set_max_size(n + 1);

    suisen::SPS<suisen::FPSNaive<mint>> f(n, suisen::FPSNaive<mint>(n));
    for (int s = 1; s < 1 << n; ++s) {
        std::vector<int> ids(n, -1);
        int id = 0;
        for (int i : suisen::all_setbit(s)) ids[i] = id++;
        std::vector<std::pair<int, int>> Es;
        for (const auto& [u, v] : edges) if (ids[u] >= 0 and ids[v] >= 0) {
            Es.emplace_back(ids[u], ids[v]);
        }
        f[s] = { 0, suisen::count_spanning_trees<mint>(id, Es) };
    }

    suisen::factorial<mint> fac(n);

    auto g = f.exp().back();

    for (int k = 1; k < n; ++k) {
        std::cout << (fac.fac(k) * g[n - k] / mint(m).pow(k)).val() << std::endl;
    }

    return 0;
}

