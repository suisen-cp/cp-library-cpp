#define PROBLEM "https://atcoder.jp/contests/abc253/tasks/abc253_f"

#include <iostream>

#include "library/datastructure/segment_tree/persistent_segment_tree.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}
 
using Tree = suisen::PersistentSegmentTree<long long, op, e>;
 
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
            segs[t] = segs[t].apply(l, [x](long long e) { return e + x; }).apply(r, [x](long long e) { return e - x; });
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
            std::cout << x + segs[t - 1].prod(0, j + 1) - segs[tl].prod(0, j + 1) << '\n';
        }
    }
    return 0;
}