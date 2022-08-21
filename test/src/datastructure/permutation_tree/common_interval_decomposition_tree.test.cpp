#define PROBLEM "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"

#include <iostream>
#include <tuple>

#include "library/datastructure/permutation_tree.hpp"

void solve(std::vector<int> p) {
    std::vector<std::tuple<int, int, int, bool>> nodes;
    auto dfs = [&](auto dfs, const suisen::PermutationTree& cur, int par) -> void {
        auto [l, r] = cur.get_index_range_closed();
        const int new_node = nodes.size();
        nodes.emplace_back(par, l, r, cur.is_join_node());
        for (const suisen::PermutationTree& ch : cur) {
            dfs(dfs, ch, new_node);
        }
    };
    suisen::PermutationTree t{ p };
    dfs(dfs, t, -1);

    std::cout << nodes.size() << '\n';
    for (const auto& [par, l, r, is_join_node] : nodes) {
        std::cout << par << ' ' << l << ' ' << r << ' ' << (is_join_node ? "linear" : "prime") << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (auto& e : p) std::cin >> e;

    solve(p);
    return 0;
}
