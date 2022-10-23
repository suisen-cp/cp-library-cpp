#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include <iostream>

#include "library/tree/tree_isomorphism_classification.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        g[p].push_back(i);
    }

    auto ids = suisen::RootedTreeClassifier<>{}.classify_subtrees(g, 0);
    const int k = *std::max_element(ids.begin(), ids.end()) + 1;
    std::cout << k << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << ids[i];
        if (i + 1 != n) std::cout << ' ';
    }
    std::cout << '\n';

    return 0;
}