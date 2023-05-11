#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"

#include <iostream>

#include <atcoder/modint>

#include "library/tree/rerooting.hpp"

using mint = atcoder::modint998244353;

namespace atcoder {
    std::istream& operator>>(std::istream& in, mint& a) {
        long long e; in >> e; a = e;
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const mint& a) {
        out << a.val();
        return out;
    }
} // namespace atcoder

using DP = std::pair<mint, int>;
using VWeight = mint;
using EWeight = std::pair<mint, mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<VWeight> a(n);
    for (auto& e : a) std::cin >> e;

    suisen::RerootingWeighted<VWeight, EWeight> g(a);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        mint b, c;
        std::cin >> b >> c;

        g.add_edge(u, v, EWeight{ b, c });
    }

    std::vector ans = g.run_dp(
        [](const DP& x, const DP& y) {
            return DP{ x.first + y.first, x.second + y.second };
        },
        []() {
            return DP{ 0, 0 };
        },
        [](const DP& x, const VWeight& a, const EWeight& f) {
            return DP{ f.first * (x.first + a) + f.second * (x.second + 1), (x.second + 1) };
        },
        [](const DP& x, const VWeight& a) {
            return DP{ x.first + a, x.second + 1 };
        }
    );

    for (const DP& v : ans) {
        std::cout << v.first << ' ';
    }
    std::cout << '\n';
}