#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <algorithm>
#include <iostream>

#include "library/number/fast_factorize.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    while (q --> 0) {
        long long a;
        std::cin >> a;
        auto fac = suisen::fast_factorize::factorize(a);
        std::sort(fac.begin(), fac.end());
        int pf_num = 0;
        for (const auto &pq : fac) pf_num += pq.second;
        std::cout << pf_num;
        for (const auto &[p, q] : fac) for (int i = 0; i < q; ++i) std::cout << ' ' << p;
        std::cout << '\n';
    }

    return 0;
}