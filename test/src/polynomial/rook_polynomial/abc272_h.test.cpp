#define PROBLEM "https://atcoder.jp/contests/abc272/tasks/abc272_h"

#include <iostream>

#include "library/polynomial/rook_polynomial.hpp"
#include "library/polynomial/formal_power_series.hpp"
#include "library/math/factorial.hpp"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

namespace atcoder {
    std::istream& operator>>(std::istream& in, mint &a) {
        long long e; in >> e; a = e;
        return in;
    }
    
    std::ostream& operator<<(std::ostream& out, const mint &a) {
        out << a.val();
        return out;
    }
} // namespace atcoder

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> h(n);
    for (auto &e : h) std::cin >> e, e = n - 1 - e;
    std::sort(h.begin(), h.end());

    suisen::factorial<mint> fac(n);

    using fps = suisen::FormalPowerSeries<mint>;

    fps g = suisen::rook_polynomial_young_tableau<fps>(h);
    for (int i = 0; i <= n; ++i) {
        g[i] *= fac.fac(n - i);
    }
    fps a(n + 1), ie(n + 1);
    for (int i = 0; i <= n; ++i) {
        a[i] = g[n - i] * fac.fac(n - i);
        ie[i] = (i & 1 ? -1 : 1) * fac.fac_inv(i);
    }
    fps b = a * ie;

    fps f(n + 1);
    for (int i = 0; i <= n; ++i) {
        f[n - i] = b[n - i] * fac.fac_inv(i);
    }

    mint ans = 0;
    for (int i = 0; i <= n; i += 2) ans += f[i];

    ans *= n;

    std::cout << (ans * fac.fac_inv(n)).val() << '\n';
}