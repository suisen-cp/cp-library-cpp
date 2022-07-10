#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3277"

#include <iostream>

#include "library/linear_algebra/xor_base.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k;
    std::cin >> k;

    std::vector<int> siz(k);
    for (auto& e : siz) std::cin >> e;

    std::vector<suisen::XorBase<uint64_t>> dp(1 << k);
    for (int i = 0; i < 60; ++i) {
        dp[0] += uint64_t(1) << i;
    }
    for (int i = 0; i < k; ++i) {
        suisen::XorBase<uint64_t> b;
        for (int j = 0; j < siz[i]; ++j) {
            uint64_t v;
            std::cin >> v;
            b += v;
        }
        dp[1 << i] = b;
    }

    uint64_t ans = 0;
    for (int s = 1; s < 1 << k; ++s) {
        int pc = __builtin_popcount(s);
        if (pc > 1) {
            int l = s & -s, t = s ^ l;
            dp[s] = dp[t] & dp[l];
        }
        if (pc & 1) {
            ans += uint64_t(1) << dp[s].dim();
        } else {
            ans -= uint64_t(1) << dp[s].dim();
        }
    }
    std::cout << ans << std::endl;

    return 0;
}