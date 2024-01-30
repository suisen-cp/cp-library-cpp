#define PROBLEM "https://atcoder.jp/contests/arc168/tasks/arc168_e"

#include "library/optimization/alien_dp.hpp"


#include <algorithm>
#include <iostream>
#include <vector>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    long long s;
    std::cin >> n >> k >> s;

    std::vector<long long> a(n);
    for (auto& e : a) {
        std::cin >> e;
    }

    std::vector<long long> sa(n + 1);
    for (int i = 0; i < n; ++i) {
        sa[i + 1] = sa[i] + a[i];
    }

    std::vector<int> max_l(n + 1);
    for (int r = 0; r <= n; ++r) {
        max_l[r] = int(std::upper_bound(sa.begin(), sa.end(), sa[r] - s) - sa.begin()) - 1;
    }

    constexpr long long inf = 1LL << 60;

    auto solve = [&](int p) {
        std::vector<std::pair<long long, int>> dp(n + 1, { inf, n + 1 });
        dp[0] = { 0LL, 0 };
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            if (int j = max_l[i]; j >= 0) {
                dp[i] = std::min(dp[i], std::pair{ dp[j].first + (i - j - 1) - p, dp[j].second + 1 });
            }
        }
        return dp[n].first;
    };

    int ok = 0, ng = k + 1;
    while (ng - ok > 1) {
        int x = (ok + ng) / 2;
        (suisen::alien_convex<long long>(x, 0, n, solve) <= n - k ? ok : ng) = x;
    }
    std::cout << ok << std::endl;
}