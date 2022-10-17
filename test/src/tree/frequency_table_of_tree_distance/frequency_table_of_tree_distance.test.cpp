#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include <iostream>

#include "library/tree/frequency_table_of_tree_distance.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<int, int>> edges(n - 1);
    for (size_t i = 0; i < n - 1; ++i) {
        size_t u, v;
        std::cin >> u >> v;
        edges[i] = { u, v };
    }

    std::vector<long long> ans = suisen::frequency_table_of_tree_distance(n, edges);

    for (size_t d = 1; d < n; ++d) {
        std::cout << ans[d];
        if (d + 1 != n) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}