#define PROBLEM "https://atcoder.jp/contests/abc266/tasks/abc266_Ex"

#include "library/datastructure/fenwick_tree/compressed_fenwick_tree_prefix.hpp"

#include <iostream>
#include <limits>
 
long long op(long long x, long long y) {
    return std::max(x, y);
}
long long e() {
    return std::numeric_limits<long long>::min() / 2;
}
 
using PrefixMaxQuery3D = suisen::CompressedFenwickTreePrefix<long long, op, e, 3>;
 
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
 
    PrefixMaxQuery3D ft;
    ft.add_point({ 0, 0, 0 });
    for (auto [x, y, z, val] : ps) {
        ft.add_point({ x, y, z });
    }
    ft.build();
 
    ft.apply({ 0, 0, 0 }, 0);
    long long ans = 0;
    for (auto [x, y, z, val] : ps) {
        long long p = ft.prefix_query({ x + 1, y + 1, z + 1 });
        ans = std::max(ans, p + val);
        ft.apply({ x, y, z }, p + val);
    }
 
    std::cout << ans << std::endl;
 
    return 0;
}