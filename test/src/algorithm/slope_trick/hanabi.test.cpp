#define PROBLEM "https://atcoder.jp/contests/dwango2016-prelims/tasks/dwango2016qual_e"

#include <iostream>

#include "library/algorithm/slope_trick.hpp"

long long solve() {
    int n, l;
    std::cin >> n >> l;
    suisen::SlopeTrick<long long> f;
    for (long long p, curr, prev = 0; n --> 0; prev = curr) {
        std::cin >> curr >> p;
        if (prev < curr) f.cumulative_min_left();
        f.add_abs(p);
    }
    return f.min();
}

int main() {
    std::cout << solve() << '\n';
    return 0;
}