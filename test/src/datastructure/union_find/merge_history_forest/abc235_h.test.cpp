#define PROBLEM "https://atcoder.jp/contests/abc235/tasks/abc235_h"

#include <iostream>
#include <map>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include <atcoder/dsu>
#include <algorithm>
#include <deque>
#include <numeric>
#include <optional>
#include <queue>

#include "library/datastructure/union_find/merge_history_forest.hpp"
using suisen::MergeHistoryForest;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n, m, k;
    std::cin >> n >> m >> k;
 
    std::map<int, std::vector<std::pair<int, int>>> edges;
    while (m --> 0) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[w].emplace_back(u - 1, v - 1);
    }
 
    MergeHistoryForest uf(n);
    for (const auto &e : edges) {
        const auto &es = e.second;
        if (es.size() == 1) {
            uf.merge(es.front());
        } else {
            uf.merge_simultaneously(e.second);
        }
    }
 
    const auto &g = uf.get_forest();
 
    auto merge = [&](auto &f, auto &g) {
        int szf = f.size(), szg = g.size();
        std::vector<mint> nf(std::min(szf + szg - 1, k + 1), 0);
        for (int i = 0; i < szf; ++i) for (int j = 0; j < szg; ++j) {
            if (i + j > k) break;
            nf[i + j] += f[i] * g[j];
        }
        return nf;
    };
 
    std::vector dp(g.size(), std::vector<mint>{});
    auto dfs = [&](auto dfs, int u) -> void {
        if (g[u].empty()) {
            dp[u] = { 1, 1 };
            return;
        }
        dp[u] = { 1 };
        for (int v : g[u]) {
            dfs(dfs, v);
            dp[u] = merge(dp[u], dp[v]);
        }
        dp[u][1] += 1;
        if (int c = g[u].size(); c <= k) dp[u][c] -= 1;
    };
 
    std::vector<mint> f { 1 };
    for (int root : uf.tree_roots()) {
        dfs(dfs, root);
        f = merge(f, dp[root]);
    }
 
    std::cout << std::accumulate(f.begin(), f.end(), mint(0)).val() << std::endl;
 
    return 0;
}