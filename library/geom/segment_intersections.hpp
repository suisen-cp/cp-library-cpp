#ifndef SUISEN_SEGMENT_INTERSECTIONS
#define SUISEN_SEGMENT_INTERSECTIONS

#include <iostream>

#include "library/util/coordinate_compressor.hpp"
#include "library/datastructure/fenwick_tree/fenwick_tree.hpp"

namespace suisen::geometry {

template <typename T>
long long segment_intersections(std::vector<std::pair<T, std::pair<T, T>>> vertical, std::vector<std::pair<std::pair<T, T>, T>> horizontal) {
    CoordinateCompressorBuilder<T> bx, by;
    for (const auto &[x, range_y] : vertical) bx.push(x);
    for (const auto &[range_x, y] : horizontal) by.push(y);
    const auto cx = bx.build();
    const auto cy = by.build();
    const int n = cx.size(), m = cy.size();
    std::vector<std::vector<std::pair<int, int>>> queries(n);
    for (const auto &[x, range_y] : vertical) {
        auto [yl, yr] = range_y;
        if (yl > yr) std::swap(yl, yr);
        queries[cx[x]].emplace_back(cy.min_geq_index(yl), cy.min_gt_index(yr));
    }
    std::vector<std::vector<int>> in(n + 1), out(n + 1);
    for (const auto &[range_x, y] : horizontal) {
        auto [xl, xr] = range_x;
        if (xl > xr) std::swap(xl, xr);
        in[cx.min_geq_index(xl)].push_back(cy[y]);
        out[cx.min_gt_index(xr)].push_back(cy[y]);
    }
    FenwickTree<int> ft(m);
    long long ans = 0;
    for (int x = 0; x < n; ++x) {
        for (int y : in[x])  ++ft[y];
        for (int y : out[x]) --ft[y];
        for (auto [yl, yr] : queries[x]) ans += ft(yl, yr);
    }
    return ans;
}

} // namespace suisen::geometry

#endif // SUISEN_SEGMENT_INTERSECTIONS
