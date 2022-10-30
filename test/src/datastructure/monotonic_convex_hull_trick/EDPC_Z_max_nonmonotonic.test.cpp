#define PROBLEM "https://atcoder.jp/contests/dp/tasks/dp_z"

#include <iostream>

#include "library/datastructure/monotonic_convex_hull_trick.hpp"

using suisen::MaxMonotonicCHT;
using suisen::non_monotonic_query_tag;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    long long c;
    std::cin >> n >> c;
    std::vector<long long> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
    }
    std::vector<long long> dp(n, 0);
    MaxMonotonicCHT<long long, non_monotonic_query_tag> cht;
    for (int i = 1; i < n; ++i) {
        cht.add_line(2 * h[i - 1], -(dp[i - 1] + h[i - 1] * h[i - 1]));
        dp[i] = -cht.query(h[i]) + h[i] * h[i] + c;
    }
    std::cout << dp[n - 1] << std::endl;
    return 0;
}