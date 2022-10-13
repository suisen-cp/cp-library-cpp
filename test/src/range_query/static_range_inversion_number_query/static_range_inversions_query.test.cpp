#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <iostream>

#include "library/range_query/static_range_inversion_number_query.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto& e : a) std::cin >> e;

    suisen::StaticRangeInversionNumberQuery riq(a);

    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        std::cin >> l >> r;
        std::cout << riq(l, r) << '\n';
    }

    return 0;
}