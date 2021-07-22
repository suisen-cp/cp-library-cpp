#define PROBLEM "https://atcoder.jp/contests/abc149/tasks/abc149_c"

#include <iostream>

#include "library/number/sieve_of_eratosthenes.hpp"

suisen::SimpleSieve<200000> sieve;

int main() {
    int x;
    std::cin >> x;
    for (;; ++x) {
        if (sieve.is_prime(x)) {
            std::cout << x << std::endl;
            return 0;
        }
    }
}