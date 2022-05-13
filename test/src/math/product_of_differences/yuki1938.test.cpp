#define PROBLEM "https://yukicoder.me/problems/no/1938"

#include <iostream>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

#include "library/math/product_of_differences.hpp"

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    int n;
    mint x;
    std::cin >> n >> x;

    std::vector<mint> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> xs[i] >> ys[i];
    }

    std::vector<mint> w = suisen::product_of_differences(xs);

    mint s = 0;
    for (int i = 0; i < n; ++i) {
        s += ys[i] / w[i];
    }

    mint p = 1;
    for (int i = 0; i < n; ++i) {
        p *= x - xs[i];
    }

    mint ans = 0;
    for (int i = 0; i < n; ++i) {
        if (x == xs[i]) {
            ans += n * ys[i] - s * w[i];
        } else {
            ans += n * ys[i] * p / (w[i] * (x - xs[i])) - s * p / (x - xs[i]);
        }
    }

    std::cout << ans.val() << std::endl;

    return 0;
}