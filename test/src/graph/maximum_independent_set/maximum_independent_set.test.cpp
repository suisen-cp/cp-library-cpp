#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include <iostream>

#include "library/graph/maximum_independent_set.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    const auto I = suisen::maximum_independent_set(g);
    const int k = I.size();
    std::cout << k << '\n';
    for (int i = 0; i < k; ++i) {
        std::cout << I[i];
        if (i + 1 != k) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}