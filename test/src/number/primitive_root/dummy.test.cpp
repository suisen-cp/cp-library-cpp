#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include <atcoder/modint>

#include "library/number/primitive_root.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"
#include "library/number/util.hpp"

using mint = atcoder::modint;

void test() {
    constexpr int n = 100000;
    suisen::Sieve<n> sieve;
    std::vector<int> totient = suisen::totient_table(n);

    for (int i = 2; i <= 100; ++i) {
        auto f = sieve.factorize(i);
        if (f.size() == 1) {
            if (f[0].first == 2 and f[0].second >= 3) continue;
        } else if (f.size() == 2) {
            if (f[0].first != 2 or f[0].second != 1) continue;
        } else {
            continue;
        }
        const int t = totient[i];
        int g = suisen::primitive_root(i);
        mint::set_mod(i);
        for (int d : sieve.divisors(t)) if (d != t) {
            if (mint(g).pow(d).val() == 1) {
                std::cout << "p = " << i << ", g = " << g << ", d = " << d << std::endl;
            }
        }
    }
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
