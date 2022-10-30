#define PROBLEM "https://atcoder.jp/contests/arc070/tasks/arc070_e"

#include <iostream>

#include "library/datastructure/slope_trick.hpp"

long long solve() {
    int n;
    std::cin >> n;
    suisen::SlopeTrick<long long> f;
    for (long long prev = 0, curr; n --> 0; prev = curr) {
        long long l, r;
        std::cin >> l >> r;
        curr = r - l;
        f.sliding_window_minimum(-curr, prev).add_abs(l);
    }
    return f.min();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << solve() << '\n';
    return 0;
}