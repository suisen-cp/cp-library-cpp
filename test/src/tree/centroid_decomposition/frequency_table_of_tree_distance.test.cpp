#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include <iostream>
#include <queue>
#include <atcoder/convolution>

#include "library/tree/centroid_decomposition.hpp"
using suisen::CentroidDecomposition;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;
    CentroidDecomposition g(n);
    for (size_t i = 0; i < n - 1; ++i) {
        size_t u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<long long> ans(n, 0);

    auto f = [&](const size_t c, const size_t) {
        std::vector<long long> sum { 1 };
        for (size_t r : g[c]) {
            std::vector<long long> d;
            auto dfs = [&](auto dfs, size_t u, size_t p, size_t dep) -> void {
                if (dep >= d.size()) d.resize(dep + 1);
                ++d[dep];
                for (size_t v : g[u]) {
                    if (v == p) continue;
                    dfs(dfs, v, u, dep + 1);
                }
            };
            dfs(dfs, r, c, 1);
            auto dmap = atcoder::convolution_ll(sum, d);
            for (size_t i = 0; i < dmap.size(); ++i) {
                ans[i] += dmap[i];
            }
            if (sum.size() < d.size()) sum.swap(d);
            for (size_t i = 0; i < d.size(); ++i) {
                sum[i] += d[i];
            }
        }
    };
    g.decomp(f);

    for (size_t d = 1; d < n; ++d) {
        std::cout << ans[d] << " \n"[d == n - 1];
    }
    return 0;
}