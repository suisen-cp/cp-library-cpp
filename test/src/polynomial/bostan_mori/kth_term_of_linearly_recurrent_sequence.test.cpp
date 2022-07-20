#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <iostream>
#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/polynomial/fps.hpp"
#include "library/polynomial/bostan_mori.hpp"
using suisen::FPS;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    std::size_t d;
    unsigned long long k;
    std::cin >> d >> k;

    FPS<mint> a(d), c(d);
    for (std::size_t i = 0; i < d; ++i) {
        unsigned int v;
        std::cin >> v;
        a[i] = v;
    }
    for (std::size_t i = 0; i < d; ++i) {
        unsigned int v;
        std::cin >> v;
        c[i] = v;
    }
    
    std::cout << suisen::nth_term_of_linearly_recurrent_sequence(a, c, k).val() << std::endl;
    
    return 0;
}