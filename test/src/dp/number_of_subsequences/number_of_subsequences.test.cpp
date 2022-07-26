#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"

#include <iostream>
#include <atcoder/modint>

#include "library/dp/number_of_subsequences.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;

    std::cout << suisen::number_of_nonempty_subsequences<atcoder::modint998244353>(a).val() << '\n';

    return 0;
}