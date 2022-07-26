#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include <iostream>

#include "library/dp/longest_increasing_subsequence.hpp"

using suisen::longest_decreasing_subsequence;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e, e = -e;

    std::vector<int> lis = longest_decreasing_subsequence(a);
    
    const int k = lis.size();
    std::cout << k << std::endl;
    for (int i = 0; i < k; ++i) {
        std::cout << lis[i];
        if (i + 1 != k) std::cout << ' ';
    }
    std::cout << std::endl;

    return 0;
}