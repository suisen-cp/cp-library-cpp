#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <iostream>

#include "library/algorithm/mo.hpp"
#include "library/datastructure/deque_aggregation.hpp"

int op(int x, int y) {
    return std::min(x, y);
}
int e() {
    return 1000000000;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;

    std::vector<std::pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries[i] = { l, r };
    }

    suisen::DequeAggregation<int, op, e> dq;
    
    auto ans = suisen::Mo{ n, queries }.solve(
        [&] { return dq.prod(); },
        [&](int l) { dq.push_front(a[l]); },
        [&](int) { dq.pop_front(); },
        [&](int r) { dq.push_back(a[r]); },
        [&](int) { dq.pop_back(); }
    );
    for (int v : ans) std::cout << v << '\n';

    return 0;
}