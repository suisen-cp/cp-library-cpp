#define PROBLEM "https://judge.yosupo.jp/problem/primarity_test"

#include <iostream>

#include "library/number/deterministic_miller_rabin.hpp"

// Compile-time calculation
static_assert(not suisen::miller_rabin::is_prime(0));
static_assert(not suisen::miller_rabin::is_prime(1));
static_assert(suisen::miller_rabin::is_prime(2));
static_assert(suisen::miller_rabin::is_prime(3));
static_assert(not suisen::miller_rabin::is_prime(4));
static_assert(suisen::miller_rabin::is_prime(5));
static_assert(not suisen::miller_rabin::is_prime(6));
static_assert(suisen::miller_rabin::is_prime(7));
static_assert(not suisen::miller_rabin::is_prime(8));
static_assert(not suisen::miller_rabin::is_prime(9));
static_assert(not suisen::miller_rabin::is_prime(10));

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while (q --> 0) {
        long long n;
        std::cin >> n;
        
        std::cout << (suisen::miller_rabin::is_prime(n) ? "Yes" : "No") << '\n';
    }
}