#define PROBLEM "https://atcoder.jp/contests/abc253/tasks/abc253_f"

#include <iostream>

#include "library/datastructure/persistent_fenwick_tree.hpp"

using Tree = suisen::PersistentFenwickTree<long long>;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
 
    std::vector<std::pair<int, int>> last(n);
 
    Tree::init_pool(10000000);
 
    std::vector<Tree> segs(q + 1);
    segs[0] = Tree(m + 1);
 
    for (int t = 1; t <= q; ++t) {
        int query_type;
        std::cin >> query_type;
        segs[t] = segs[t - 1];
        if (query_type == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            segs[t] = segs[t].add(l, x).add(r, -x);
        } else if (query_type == 2) {
            int i, x;
            std::cin >> i >> x;
            --i;
            last[i] = { t - 1, x };
        } else {
            int i, j;
            std::cin >> i >> j;
            --i, --j;
            auto [tl, x] = last[i];
            std::cout << x + segs[t - 1].sum(0, j + 1) - segs[tl].sum(0, j + 1) << '\n';
        }
    }
    return 0;
}