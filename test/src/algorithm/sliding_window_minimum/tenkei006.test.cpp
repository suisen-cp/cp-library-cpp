#define PROBLEM "https://atcoder.jp/contests/typical90/tasks/typical90_f"

#include <iostream>
#include <string>

#include "library/algorithm/sliding_window_minimum.hpp"
using namespace suisen;

int main() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    sliding_window_minimum<char, prioritizing_mode::left_most_min<char>> swm(n, [&](int i) { return s[i]; });
    std::string ans;
    for (int rest = k - 1, l = 0; rest >= 0; --rest, ++l) {
        swm.proc(l, n - rest);
        l = swm.arg_query();
        ans += s[l];
    }
    std::cout << ans << '\n';
    return 0;
}