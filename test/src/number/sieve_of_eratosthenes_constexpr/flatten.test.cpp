#define PROBLEM "https://atcoder.jp/contests/abc152/tasks/abc152_e"

#include <iostream>
#include <unordered_map>
#include <vector>

#include <atcoder/modint>

#include "library/number/sieve_of_eratosthenes_constexpr.hpp"

constexpr suisen::SieveConstexpr<suisen::CONSTEXPR_SIEVE_MAX> sieve;

template <typename T>
void chmax(T &x, const T &y) {
    if (x < y) x = y;
}

using mint = atcoder::modint1000000007;

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::unordered_map<int, int> factors;
    for (int &e : a) {
        std::cin >> e;
        for (int x = e; x != 1;) {
            int p = sieve.prime_factor(x);
            int cnt = 0;
            while (x % p == 0) x /= p, ++cnt;
            chmax(factors[p], cnt);
        }
    }
    mint ans = 0;
    for (int &e : a) {
        ans += mint(e).inv();
    }
    for (auto [p, c] : factors) {
        ans *= mint(p).pow(c);
    }
    std::cout << ans.val() << std::endl;
    return 0;
}