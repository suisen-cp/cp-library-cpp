#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include <iostream>

#include <atcoder/modint>
#include <atcoder/convolution>

#include "library/polynomial/fps.hpp"
#include "library/polynomial/multi_point_eval.hpp"

using mint = atcoder::modint998244353;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });
    
    int n, m;
    std::cin >> n >> m;
    suisen::FPS<mint> f(n);
    for (int i = 0; i < n; ++i) {
        int coef;
        std::cin >> coef;
        f[i] = coef;
    }
    std::vector<mint> xs(m);
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        xs[i] = x;
    }
    auto ys = suisen::multi_point_eval(f, xs);
    for (int i = 0; i < m; ++i) {
        std::cout << ys[i].val() << " \n"[i == m - 1];
    }
    return 0;
}