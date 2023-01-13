#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include "library/number/util.hpp"
#include "library/number/mod_sqrt.hpp"

void test_small() {
    for (int m = 1; m <= 700; ++m) {
        for (int a = 0; a < m; ++a) {
            auto x = suisen::composite_mod_sqrt(a, suisen::factorize(m));
            if (x) {
                int x0 = *x;
                assert(x0 * x0 % m == a);
            } else {
                for (int b = 0; b < m; ++b) {
                    assert(b * b % m != a);
                }
            }
        }
    }
}

void test_large() {
    std::mt19937 rng{ 0 };
    std::uniform_int_distribution<long long> dist_m(1, 1000000000000);
    
    for (int q = 0; q < 100; ++q) {
        long long m = dist_m(rng);
        std::uniform_int_distribution<long long> dist_a(0, m - 1);
        auto factorized = suisen::factorize(m);

        for (int inner_q = 0; inner_q < 10000; ++inner_q) {
            long long a = dist_a(rng);

            auto x = suisen::composite_mod_sqrt(a, factorized);
            if (x) {
                __int128_t x0 = *x;
                assert(x0 * x0 % m == a);
            }
        }
    }
}

void test() {
    test_small();
    test_large();
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
