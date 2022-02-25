#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <iostream>

#include "library/number/sieve_of_eratosthenes.hpp"

suisen::SimpleSieve<500000000> sieve;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a, b;
    std::cin >> n >> a >> b;

    auto primes = sieve.prime_list(n);
    int prime_num = primes.size();
    std::vector<int> out;
    for (int i = b; i < prime_num; i += a) {
        out.push_back(primes[i]);
    }
    int output_num = out.size();

    std::cout << prime_num << ' ' << output_num << '\n';
    for (int i = 0; i < output_num; ++i) {
        std::cout << out[i] << '\n';
    }

    return 0;
}