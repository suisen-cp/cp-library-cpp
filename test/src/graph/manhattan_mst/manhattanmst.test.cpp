#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"

#include <iostream>

#include "library/graph/manhattan_mst.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> points(n);
    for (auto &[x, y] : points) std::cin >> x >> y;

    auto mst = suisen::manhattan_mst<long long>(points);
    std::cout << mst.get_weight() << '\n';
    for (auto [i, j, _] : mst.get_mst()) {
        std::cout << i << ' ' << j << '\n';
    }

    return 0;
}
