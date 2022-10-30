#define PROBLEM "https://atcoder.jp/contests/abc266/tasks/abc266_Ex"

#include "library/datastructure/segment_tree/compressed_segment_tree.hpp"

#include <iostream>
#include <limits>
 
long long op(long long x, long long y) {
    return std::max(x, y);
}
long long e() {
    return std::numeric_limits<long long>::min() / 2;
}

using CubeMaxQuery = suisen::CompressedSegmentTree<long long, op, e, 3>;

constexpr int inf = std::numeric_limits<int>::max() / 2;

int main() {
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n;
    std::cin >> n;
 
    std::vector<std::tuple<int, int, int, int>> ps(n);
    for (int i = 0; i < n; ++i) {
        int t, x, y, a;
        std::cin >> t >> x >> y >> a;
        ps[i] = { y, t - y + x, t - y - x, a };
    }
    std::sort(ps.begin(), ps.end());
 
    CubeMaxQuery seg;
    seg.add_point({ 0, 0, 0 });
    for (auto [x, y, z, val] : ps) {
        seg.add_point({ x, y, z });
    }
    seg.build();
 
    seg.set({ 0, 0, 0 }, op(seg.get({ 0, 0, 0 }), 0));
    long long ans = 0;
    for (auto [x, y, z, val] : ps) {
        long long p = seg.query({ std::pair{ -inf, x + 1 }, std::pair{ -inf, y + 1 }, std::pair{ -inf, z + 1 } });
        ans = std::max(ans, p + val);
        seg.set({ x, y, z }, op(seg.get({ x, y, z }), p + val));
    }
 
    std::cout << ans << std::endl;
 
    return 0;
}