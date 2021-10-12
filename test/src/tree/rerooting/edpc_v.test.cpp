#define PROBLEM "https://atcoder.jp/contests/dp/tasks/dp_v"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint;

#include "library/tree/rerooting.hpp"
using suisen::ReRooting;

mint op(mint x, mint y) {
    return x * y;
}
mint e() {
    return 1;
}
mint add_subtree_root(mint val, int, int) {
    return val;
}
mint trans_to_par(mint val, int, int, std::nullptr_t) {
    return val + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    mint::set_mod(m);

    ReRooting<mint, op, e, add_subtree_root, std::nullptr_t, trans_to_par> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        g.add_edge(x, y, nullptr);
    }

    for (mint e : g.rerooting()) {
        std::cout << e.val() << '\n';
    }
    return 0;
}