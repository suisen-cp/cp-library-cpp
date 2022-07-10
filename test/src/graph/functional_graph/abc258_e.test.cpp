#define PROBLEM "https://atcoder.jp/contests/abc258/tasks/abc258_e"

#include <iostream>

#include "library/graph/functional_graph.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}

constexpr long long M = 1000000010;
constexpr long long L = 1000000000010LL;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    long long x;
    std::cin >> n >> q >> x;

    std::vector<long long> w(n);
    for (auto& e : w) std::cin >> e;

    std::vector<long long> num(n);
    std::vector<int> nxt(n);
    {
        std::vector<int> tmp_nxt(n);
        for (int i = 0; i < n; ++i) tmp_nxt[i] = (i + 1) % n;
        auto d = suisen::FunctionalGraph{ tmp_nxt }.doubling<long long, op, e>(M, w);
        for (int i = 0; i < n; ++i) {
            auto res = *d.step_until(i, [&](long long v) { return v >= x; });
            nxt[i] = res.v;
            num[i] = res.step;
        }
    }

    auto d = suisen::FunctionalGraph{ nxt }.doubling(L);
    while (q --> 0) {
        long long k;
        std::cin >> k;
        std::cout << num[d.query(0, k - 1)] << '\n';
    }
    return 0;
}