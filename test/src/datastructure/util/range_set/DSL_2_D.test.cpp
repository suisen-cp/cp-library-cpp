#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_D"

#include <array>
#include <iostream>

#include "library/datastructure/util/range_set.hpp"
using suisen::RangeSet;

constexpr int L = 31;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::array<RangeSet<int>, L> bits;
    for (int i = 0; i < L; ++i) {
        bits[i].insert(0, n - 1);
    }

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int s, t, x;
            std::cin >> s >> t >> x;
            for (int bit = 0; bit < L; ++bit) {
                if ((x >> bit) & 1) {
                    bits[bit].insert(s, t);
                } else {
                    bits[bit].erase(s, t);
                }
            }
        } else {
            int i;
            std::cin >> i;
            int res = 0;
            for (int bit = 0; bit < L; ++bit) {
                res |= bits[bit].contains(i) << bit;
            }
            std::cout << res << '\n';
        }
    }
    return 0;
}