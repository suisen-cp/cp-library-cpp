#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/util/coordinate_compressor.hpp"
#include "library/datastructure/segment_tree/persistent_segment_tree.hpp"

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}

using suisen::CoordinateCompressorBuilder;
using suisen::PersistentSegmentTree;

using Tree = PersistentSegmentTree<long long, op, e>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::tuple<int, int, int>> points(n);
    CoordinateCompressorBuilder<int> bx, by;

    for (auto &[x, y, w] : points) {
        std::cin >> x >> y >> w;
        bx.push(x);
        by.push(y);
    }
    auto cmp_x = bx.build(), cmp_y = by.build();

    const int h = cmp_x.size(), w = cmp_y.size();

    std::vector<std::vector<std::pair<int, int>>> buckets(h);
    for (auto &[x, y, w] : points) {
        x = cmp_x[x];
        y = cmp_y[y];
        buckets[x].emplace_back(y, w);
    }

    Tree::init_pool(5000000);

    std::vector<Tree> fts(h + 1);
    fts[0] = Tree(w);

    for (int x = 0; x < h; ++x) {
        fts[x + 1] = fts[x];
        for (const auto yw : buckets[x]) {
            const int y = yw.first, w = yw.second;
            fts[x + 1] = fts[x + 1].apply(y, [w](long long e) { return e + w; });
        }
    }

    for (int query_id = 0; query_id < q; ++query_id) {
        int l, r, d, u;
        std::cin >> l >> d >> r >> u;

        l = cmp_x.min_geq_index(l);
        r = cmp_x.min_geq_index(r);
        d = cmp_y.min_geq_index(d);
        u = cmp_y.min_geq_index(u);

        std::cout << fts[r].prod(d, u) - fts[l].prod(d, u) << '\n';
    }

    return 0;
}