#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include <atcoder/modint>

#include "library/polynomial/fps.hpp"
#include "library/math/factorial_large.hpp"

template <int MOD>
void test() {
    using mint = atcoder::static_modint<MOD>;

    std::mt19937 rng{};
    constexpr int MAX_N = 10000000;
    std::uniform_int_distribution<int> dist(0, MAX_N);

    const int q = 10000;
    std::vector<int> ns(q);
    for (int& e : ns) e = dist(rng);
    // power of 2
    for (int i = 0; 1 << i < MAX_N; ++i) ns[i] = 1 << i;

    std::vector<mint> res1, res2;
    {
        suisen::factorial_large<mint> fac{};
        fac.threshold = -1;
        res1.resize(q);
        for (int i = 0; i < q; ++i) res1[i] = fac.fac(ns[i]);
    }
    {
        suisen::factorial<mint> fac{};
        res2.resize(q);
        for (int i = 0; i < q; ++i) res2[i] = fac.fac(ns[i]);
    }
    assert(res1 == res2);

}

int main() {
    test<998244353>();
    test<1000000007>();
    test<1000000009>();
    std::cout << "Hello World" << std::endl;
    return 0;
}
