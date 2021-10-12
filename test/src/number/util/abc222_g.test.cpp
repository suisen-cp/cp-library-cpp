#define PROBLEM "https://atcoder.jp/contests/abc222/tasks/abc222_g"

#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint;

#include "library/number/util.hpp"
using suisen::divisors;
using suisen::totient;

int main() {
    int t;
    std::cin >> t;
    while (t --> 0) {
        int k;
        std::cin >> k;
        k = k * 9 / std::gcd(k, 2);
        if (std::gcd(10, k) > 1) {
            std::cout << -1 << std::endl;
        } else {
            int res = totient(k);
            mint::set_mod(k);
            for (int d : divisors(res)) {
                if (mint(10).pow(d) == 1) res = std::min(res, d);
            }
            std::cout << res << std::endl;
        }
    }
    return 0;
}