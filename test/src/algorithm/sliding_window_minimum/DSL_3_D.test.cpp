#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <iostream>

#include "library/algorithm/sliding_window_minimum.hpp"
using suisen::sliding_window_minimum;

int main() {
    int n, l;
    std::cin >> n >> l;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    sliding_window_minimum<int> swm(n, [&a](int i) { return a[i]; });
    for (int r = l; r <= n; ++r) {
        swm.proc(r - l, r);
        std::cout << swm.query() << " \n"[r == n];
    }
    return 0;
}