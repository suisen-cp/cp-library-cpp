#define PROBLEM "https://atcoder.jp/contests/abc240/tasks/abc240_g"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/math/util.hpp"

int main() {
    int n, x, y, z;
    std::cin >> n >> x >> y >> z;

    suisen::factorial<mint> fac(n);

    mint ans = 0;
    for (int i = 0; i <= n; ++i) {
        int j = i - z;
        ans += fac.binom(n, i) * fac.binom(n - i, j) * suisen::random_walk_2d<mint>(n - i - j, x, y);
    }
    std::cout << ans.val() << std::endl;

    return 0;
}