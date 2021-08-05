#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <iostream>

#include "library/datastructure/cartesian_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    suisen::CartesianTree<int, std::less<int>> t(a);
    for (int i = 0; i < n; ++i) {
        int p = t.parent(i);
        std::cout << (p < 0 ? i : p) << " \n"[i == n - 1];
    }
    return 0;
}