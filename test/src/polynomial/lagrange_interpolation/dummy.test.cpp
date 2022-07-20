#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>
#include <set>
#include <random>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/polynomial/fps.hpp"
#include "library/polynomial/lagrange_interpolation.hpp"

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

    [&] {
        std::set<int> st;
        for (int i = 0; i < N; ++i) {
            do xs[i] = dist(rng); while (st.count(xs[i].val()));
            st.insert(xs[i].val());
            ys[i] = eval(xs[i]);
        }
    }();

    auto check = [&](mint t) {
        mint expected = eval(t);
        mint actual_fast = suisen::lagrange_interpolation<suisen::FPS<mint>>(xs, ys, t);
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

template <int N>
void test_arithmetic_progression() {
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

    auto do_test = [&](mint a, mint b) {
        std::vector<mint> xs(N), ys(N);

        for (int i = 0; i < N; ++i) {
            xs[i] = a * i + b;
            ys[i] = eval(xs[i]);
        }

        auto check = [&](mint t) {
            mint expected = eval(t);
            mint actual_arith = suisen::lagrange_interpolation_arithmetic_progression(a, b, ys, t);
            mint actual_fast = suisen::lagrange_interpolation<suisen::FPS<mint>>(xs, ys, t);
            mint actual_naive = suisen::lagrange_interpolation_naive(xs, ys, t);
            assert(expected == actual_arith);
            assert(expected == actual_naive);
            assert(expected == actual_fast);
        };

        for (int i = 0; i < N; ++i) {
            check(xs[i]);
        }
        for (int i = 0; i < N; ++i) {
            check(dist(rng));
        }
    };

    mint a = dist(rng);
    while (a == 0) a = dist(rng);
    do_test(a, dist(rng));
}

void test_arithmetic_progression_zero() {
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, mint::mod() - 1);

    mint a = 0, b = dist(rng), y = dist(rng), t = dist(rng);

    mint expected = y;
    mint actual = suisen::lagrange_interpolation_arithmetic_progression(a, b, { y }, t);
    assert(expected == actual);
}

int main() {
    test<100>();
    test_arithmetic_progression<100>();
    test_arithmetic_progression_zero();
    std::cout << "Hello World" << std::endl;
    return 0;
}