#define PROBLEM "https://atcoder.jp/contests/abc127/tasks/abc127_f"

#include <iostream>
#include "library/datastructure/slope_trick.hpp"

void solve() {
    suisen::SlopeTrick<long long> f;
    int q;
    std::cin >> q;
    while (q --> 0) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int a, b;
            std::cin >> a >> b;
            f.add_abs(a), f.add_const(b);
        } else {
            std::cout << f.argmin_range().first << ' ' << f.min() << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();        
    return 0;
}