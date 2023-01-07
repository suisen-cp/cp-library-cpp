#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include <iostream>

#include "library/sequence/binomial_coefficient.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, m;
    std::cin >> t >> m;
    
    using suisen::BinomialCoefficient;

    BinomialCoefficient binom(m);
    for (int qid = 0; qid < t; ++qid) {
        long long n, k;
        std::cin >> n >> k;
        std::cout << binom(n, k) << '\n';
    }
}