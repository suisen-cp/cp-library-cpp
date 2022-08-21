#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_cliques"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/graph/enumerate_cliques.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> x(n);
    for (int &e : x) std::cin >> e;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    mint ans = 0;
    suisen::enumerate_cliques(
        g,
        [&ans, &x](const std::vector<int> &clique) {
            mint prod = 1;
            for (int i : clique) prod *= mint::raw(x[i]);
            ans += prod;
        }
    );
    std::cout << ans.val() << '\n';

    return 0;
}