#define PROBLEM "https://atcoder.jp/contests/abc287/tasks/abc287_h"

#include <iostream>

#include "library/graph/minmax_floyd_warshall.hpp"

constexpr int inf = std::numeric_limits<int>::max() / 2;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n, m;
    std::cin >> n >> m;
 
    std::vector<std::vector<int>> g(n, std::vector<int>(n, inf));
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u][v] = std::max(u, v) + 1;
    }
 
    std::vector<std::vector<int>> ans = suisen::minmax_floyd_warshall(g);
 
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int s, t;
        std::cin >> s >> t;
        --s, --t;
        std::cout << (ans[s][t] == inf ? -1 : ans[s][t]) << '\n';
    }
}