#define PROBLEM "https://atcoder.jp/contests/arc123/tasks/arc123_d"

#include <iostream>

#include "library/algorithm/slope_trick.hpp"

constexpr long long inf = std::numeric_limits<long long>::max();

long long solve() {
    int n;
    std::cin >> n;
    suisen::SlopeTrick<long long> f;
    for (long long prev = inf, curr; n --> 0; prev = curr) {
        std::cin >> curr;
        f.translate(std::max(0LL, curr - prev)).cumulative_min_left().add_abs(0).add_abs(curr);
    }
    return f.min();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << solve() << '\n';
    return 0;
}