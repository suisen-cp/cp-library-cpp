#define PROBLEM "https://atcoder.jp/contests/abc222/tasks/abc222_f"

#include <iostream>
#include <limits>

#include "library/tree/rerooting.hpp"

using DP = long long;
using VWeight = long long;
using EWeight = long long;

constexpr DP inf = std::numeric_limits<DP>::max() / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    suisen::RerootingWeighted<VWeight, EWeight> g(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        g.add_edge(u, v, w);
    }

    std::vector<VWeight> d(n);
    for (auto &e : d) std::cin >> e;
    g.set_vertex_weights(d);

    std::vector ans = g.run_dp(
        [](const DP& x, const DP& y) {
            return std::max(x, y);
        },
        []() {
            return -inf;
        },
        [](const DP& x, const VWeight& vw, const EWeight& ew) {
            return std::max(x, vw) + ew;
        },
        [](const DP& x, const VWeight&) {
            return x;
        }
    );

    for (const DP& v : ans) {
        std::cout << v << '\n';
    }
}