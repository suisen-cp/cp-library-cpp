#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A"

#include <iostream>
#include <tuple>

#include "library/util/coordinate_compressor.hpp"
#include "library/datastructure/util/range_set.hpp"
using suisen::CoordinateCompressorBuilder;
using suisen::RangeSet;

constexpr int L = 31;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    CoordinateCompressorBuilder<long long> builder;
    std::vector<std::tuple<long long, long long, long long, long long>> rectangles(n);
    for (int i = 0; i < n; ++i) {
        int xl, yl, xr, yr;
        std::cin >> xl >> yl >> xr >> yr;
        rectangles[i] = { xl, yl, xr, yr };
        builder.push(yl);
        builder.push(yr);
    }
    auto comp_y = builder.build();
    int m = comp_y.size();
    std::vector<RangeSet<long long>> sets(m);
    for (const auto &[xl, yl, xr, yr] : rectangles) {
        int cyl = comp_y[yl], cyr = comp_y[yr];
        for (int i = cyl; i < cyr; ++i) {
            sets[i].insert(xl, xr - 1);
        }
    }
    long long ans = 0;
    for (int i = 0; i < m - 1; ++i) {
        long long hight = comp_y.decomp(i + 1) -comp_y.decomp(i);
        ans += hight * sets[i].size();
    }
    std::cout << ans << std::endl;
    return 0;
}