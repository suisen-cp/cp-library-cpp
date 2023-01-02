#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"

#include <iostream>

#include "library/number/min_of_mod_of_linear.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (int test_case_id = 0; test_case_id < t; ++test_case_id) {
        int n, m, a, b;
        std::cin >> n >> m >> a >> b;
        
        std::cout << suisen::min_of_mod_of_linear(n, m, a, b) << std::endl;
    }
}