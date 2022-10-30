#define PROBLEM "https://atcoder.jp/contests/abc228/tasks/abc228_h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "library/datastructure/monotonic_convex_hull_trick.hpp"

constexpr int M = 1000000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x;
    std::cin >> n >> x;

    std::array<long long, M + 1> cs{};
    for (int i = 0; i < n; ++i) {
        int a, c;
        std::cin >> a >> c;
        cs[a] += c;
    }

    suisen::MinMonotonicCHT<long long, suisen::inc_query_tag> cht;
    
    long long ans = 0;
    long long s = 0, t = 0;
    cht.add_line(-s, t);
    for (long long a = 0; a <= M; ++a) if (long long c = cs[a]; c) {
        s += c, t += a * c;
        ans = cht.query(a) + x + a * s - t;
        cht.add_line(-s, ans + t);
    }
    std::cout << ans << std::endl;
    
    return 0;
}