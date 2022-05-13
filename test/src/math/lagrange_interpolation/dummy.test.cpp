#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <random>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/math/lagrange_interpolation.hpp"

template <int N>
void test() {
    suisen::FPS<mint>::set_multiplication([](const auto& a, const auto& b) { return atcoder::convolution(a, b); });

    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, mint::mod() - 1);

    std::vector<mint> f(N);
    for (int i = 0; i < N; ++i) f[i] = dist(rng);

    auto eval = [&f](mint x) -> mint {
        mint y = 0;
        for (int i = N - 1; i >= 0; --i) y = y * x + f[i];
        return y;
    };

    std::vector<mint> xs(N), ys(N);

    for (int i = 0; i < N; ++i) {
        auto is_valid = [&] {
            for (int j = 0; j < i; ++j) if (xs[i] == xs[j]) return false;
            return true;
        };
        do xs[i] = dist(rng); while (not is_valid());
        ys[i] = eval(xs[i]);
    }

    auto check = [&](mint t) {
        mint expected = eval(t);
        mint actual_fast = suisen::lagrange_interpolation(xs, ys, t);
        mint actual_naive = suisen::lagrange_interpolation_naive(xs, ys, t);
        assert(expected == actual_naive);
        assert(expected == actual_fast);
    };

    for (int i = 0; i < N; ++i) {
        check(xs[i]);
    }
    for (int i = 0; i < N; ++i) {
        check(dist(rng));
    }
}

int main() {
    test<100>();
    std::cout << "Hello World" << std::endl;
    return 0;
}