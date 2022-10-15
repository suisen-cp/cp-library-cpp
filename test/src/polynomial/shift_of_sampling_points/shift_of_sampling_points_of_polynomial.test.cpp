#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include <iostream>
#include <atcoder/modint>
#include "library/polynomial/shift_of_sampling_points.hpp"

int main() {
    using mint = atcoder::modint998244353;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, c;
    std::cin >> n >> m >> c;

    std::vector<mint> ys(n);
    for (int i = 0, v; i < n; ++i) std::cin >> v, ys[i] = v;

    std::vector<mint> ans = suisen::shift_of_sampling_points<mint>(ys, c, m);
    for (int i = 0; i < m; ++i) {
        std::cout << ans[i].val();
        if (i + 1 != m) std::cout << ' ';
    }
    std::cout << '\n';
    return 0;
}