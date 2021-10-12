#define PROBLEM "https://atcoder.jp/contests/abc160/tasks/abc160_f"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint1000000007;

#include "library/tree/rerooting.hpp"
using suisen::ReRooting;

int n;
std::vector<int> sub;
std::vector<int> par;

mint op(mint x, mint y) {
    return x * y;
}
mint e() {
    return 1;
}
mint add_subtree_root(mint val, int u, int p) {
    return val / (p == par[u] ? sub[u] : n - (p < 0 ? 0 : sub[p]));
}
mint trans_to_par(mint val, int, int, int) {
    return val;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    ReRooting<mint, op, e, add_subtree_root, int, trans_to_par> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g.add_edge(u, v, 0);
    }
    sub.resize(n, 1);
    par.resize(n, -1);
    auto dfs = [&](auto dfs, int u, int p) -> void {
        par[u] = p;
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            dfs(dfs, v, u);
            sub[u] += sub[v];
        }
    };
    dfs(dfs, 0, -1);
    mint fac = 1;
    for (int i = 1; i <= n; ++i) {
        fac *= i;
    }
    for (mint e : g.rerooting()) {
        std::cout << (e * fac).val() << '\n';
    }
    return 0;
}