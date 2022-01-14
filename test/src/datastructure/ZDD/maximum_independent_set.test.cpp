#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include <iostream>

#include "library/datastructure/ZDD.hpp"
using namespace suisen;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> lvl(n);
    for (int i = 0; i < n; ++i) {
        lvl[i] = ZDD::new_level();
    }

    auto F = [&](int u, int v) {
        if (u > v) std::swap(u, v);
        ZDD f = ZDD::create_zdd(ZDD::create_zdd(ZDD::terminal1(), ZDD::terminal1(), lvl[u]), ZDD::terminal1(), lvl[v]);
        for (int i = 0; i < n; ++i) {
            if (i == u or i == v) continue;
            f = ZDD::change(f, lvl[i]) + f;
        }
        return f;
    };

    ZDD U = ZDD::terminal1();
    for (int i = 0; i < n; ++i) U = ZDD::change(U, lvl[i]) + U;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        auto Fuv = F(u, v);
        U = U & Fuv;
    }

    auto ans = *ZDD::max_len_item(U);

    std::cout << ans.size() << std::endl;
    for (int e : ans) std::cout << e - 1 << ' ';
    std::cout << std::endl;
    return 0;
}