#define PROBLEM "https://atcoder.jp/contests/abc228/tasks/abc228_h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "library/datastructure/convex_hull_trick.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;

    std::vector<std::pair<long long, long long>> ps(n);
    for (auto &[a, c] : ps) std::cin >> a >> c;
    std::sort(ps.begin(), ps.end());

    suisen::ConvexHullTrick<long long> cht;
    
    long long ans = 0;
    long long s = 0, t = 0;
    cht.add_line(-s, t);
    for (const auto &[a, c] : ps) {
        s += c, t += a * c;
        ans = cht.query(a) + x + a * s - t;
        cht.add_line(-s, ans + t);
    }

    std::cout << ans << std::endl;
    return 0;
}