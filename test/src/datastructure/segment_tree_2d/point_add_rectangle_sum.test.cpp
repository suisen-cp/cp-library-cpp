#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include <iostream>
#include <tuple>

#include "library/datastructure/segment_tree_2d.hpp"
#include "library/util/coordinate_compressor.hpp"

using namespace suisen;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    CoordinateCompressorBuilder<int> builder;
    builder.reserve(n + q);

    std::vector<std::tuple<int, int, int>> init(n);
    for (int i = 0; i < n; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        init[i] = { x, y, w };
        builder.push(x);
    }
    std::vector<std::tuple<int, int, int, int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            queries[i] = { t, x, y, w, 0 };
            builder.push(x);
        } else {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            queries[i] = { t, l, r, d, u };
        }
    }

    auto comp_x = builder.build();

    SegmentTree2D seg(comp_x.size(), 0LL, std::plus<long long>());
    for (auto &p : init) {
        seg.add_point(std::get<0>(p), std::get<1>(p));
    }
    for (auto &q : queries) {
        if (std::get<0>(q) == 0) {
            seg.add_point(std::get<1>(q), std::get<2>(q));
        }
    }
    seg.build();

    for (auto [x, y, w] : init) {
        seg[{x, y}] += w;
    }

    for (const auto &q : queries) {
        if (std::get<0>(q) == 0) {
            seg[{std::get<1>(q), std::get<2>(q)}] += std::get<3>(q);
        } else {
            std::cout << seg(std::get<1>(q), std::get<2>(q), std::get<3>(q), std::get<4>(q)) << '\n';
        }
    }

    return 0;
}