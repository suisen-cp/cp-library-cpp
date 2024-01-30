#define PROBLEM "https://atcoder.jp/contests/abc218/tasks/abc218_h"

#include "library/optimization/alien_dp.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, r;
    std::cin >> n >> r;
    
    std::vector<long long> a(n - 1);
    for (auto &e : a) {
        std::cin >> e;
    }

    // sup f(x)-px
    auto g = [&](long long p) {
        std::vector<std::pair<long long, int>> dp0(n, { -(1LL << 60), -n-1 }), dp1(n, { -(1LL << 60), -n-1 });
        dp0[0] = { 0, 0 };
        dp1[0] = { -p, 1 };
        for (int i = 0; i < n - 1; ++i) {
            dp0[i + 1] = std::max<std::pair<long long, int>>(dp0[i], { dp1[i].first + a[i], dp1[i].second });
            dp1[i + 1] = std::max<std::pair<long long, int>>({ dp1[i].first - p, dp1[i].second + 1 }, { dp0[i].first - p + a[i], dp0[i].second + 1 });
        }
        return std::max(dp0[n - 1], dp1[n - 1]);
    };

    std::cout << suisen::alien_concave<long long>(r, -2'000'000'000LL, +2'000'000'000LL, g) << std::endl;
}

