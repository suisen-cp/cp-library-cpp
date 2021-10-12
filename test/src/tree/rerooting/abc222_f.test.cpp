#define PROBLEM "https://atcoder.jp/contests/abc222/tasks/abc222_f"

#include <iostream>
#include "library/tree/rerooting.hpp"
using suisen::ReRooting;

constexpr long long inf = std::numeric_limits<long long>::max();

std::vector<long long> d;

long long op(long long x, long long y) {
    return x > y ? x : y;
}
long long e() {
    return -inf;
}
long long add_subtree_root(long long val, int, int) {
    return val;
}
long long trans_to_par(long long val, int v, int, long long w) {
    return op(d[v], val) + w;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    ReRooting<long long, op, e, add_subtree_root, long long, trans_to_par> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        g.add_edge(--u, --v, c);
    }
    d.resize(n);
    for (auto& e : d) std::cin >> e;
    for (const auto& e : g.rerooting()) {
        std::cout << e << '\n';
    }
    return 0;
}