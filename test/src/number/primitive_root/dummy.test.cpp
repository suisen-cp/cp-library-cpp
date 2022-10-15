#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include <atcoder/modint>

#include "library/number/primitive_root.hpp"
#include "library/number/sieve_of_eratosthenes.hpp"

using mint = atcoder::modint;

void test() {
    suisen::Sieve<100000> sieve;

    for (int i = 2; i < 100000; ++i) if (sieve.is_prime(i)) {
        int g = suisen::primitive_root(i);

        mint::set_mod(i);
        for (int d : sieve.divisors(i - 1)) if (d != i - 1) {
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
