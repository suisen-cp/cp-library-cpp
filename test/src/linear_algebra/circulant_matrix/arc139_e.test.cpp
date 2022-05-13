#include <iostream>
#include <vector>

#include <atcoder/modint>
#include <atcoder/convolution>

using mint = atcoder::modint998244353;

#include "library/math/factorial.hpp"
#include "library/linear_algebra/circulant_matrix.hpp"

using suisen::factorial;
using suisen::CirculantMatrix;

void solve(long long n, long long m) {
    if (n % 2 == 0 and m % 2 == 0) {
        std::cout << 2 << std::endl;
    } else if (n % 2 == 0) {
        factorial<mint> fac(n + 1);
        mint ans = 0;
        for (int k = 0; k <= n; ++k) if ((n - 2 * k) % m == 0) ans += fac.binom(n, k);
        std::cout << (ans * m).val() << std::endl;
    } else {
        CirculantMatrix<mint>::set_multiplication([](const std::vector<mint>& a, const std::vector<mint>& b) { return atcoder::convolution(a, b); });
        if (m % 2 == 1 and n > m) std::swap(n, m);
        std::vector<mint> dat(n);
        dat[1] = dat[n - 1] = 1;
        std::vector<mint> x(n);
        x[0] = 1;
        std::cout << ((CirculantMatrix<mint>{dat}.pow(m) * x)[0] * n).val() << std::endl;
    }
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    solve(n, m);
    return 0;
}