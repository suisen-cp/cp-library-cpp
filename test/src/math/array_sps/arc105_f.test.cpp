#define PROBLEM "https://atcoder.jp/contests/arc105/tasks/arc105_f"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/math/array_sps.hpp"

using namespace suisen;

int main() {
    int n, m;
    std::cin >> n >> m;
    int k = n;
    std::vector<int> c(1 << k, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        c[(1 << --u) | (1 << --v)] = 1;
    }
    subset_transform::zeta<int>(c);
    mint inv_2 = mint(2).inv();
    std::vector<mint> pow_2(m + 1, 0), pow_inv_2(m + 1, 0);
    pow_2[0] = pow_inv_2[0] = 1;
    for (int i = 1; i <= m ;++i) {
        pow_inv_2[i] = pow_inv_2[i - 1] * inv_2;
        pow_2[i] = pow_2[i - 1] * 2;
    }
    ArraySPS<mint, 18> p(n);
    for (int i = 0; i < 1 << n; ++i) {
        p[i] = pow_inv_2[c[i]];
    }
    ArraySPS<mint, 18> q = p.pow(2);
    for (int i = 0; i < 1 << n; ++i) {
        q[i] *= pow_2[c[i]];
    }
    std::cout << q.zeta().sqrt_inplace().log_inplace().mobius_inplace().back().val() << std::endl;
    return 0;
}