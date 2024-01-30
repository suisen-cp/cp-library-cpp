#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

#include <iostream>

#include "library/polynomial/rook_polynomial.hpp"
#include "library/polynomial/formal_power_series.hpp"

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

using fps = suisen::FormalPowerSeries<mint>;

#include <map>

fps naive(const std::vector<int> &h) {
    std::map<int, fps> pd;
    pd[0] = { 1 };
    for (int k : h) {
        std::map<int, fps> dp;
        for (auto [mask, f] : pd) {
            const int nxt_mask = mask ^ ((mask >> k) << k);
            dp[nxt_mask] += f;
            for (int pos = 0; pos < k; ++pos) if (not ((nxt_mask >> pos) & 1)) {
                dp[nxt_mask | (1 << pos)] += f << 1;
            }
        }
        pd.swap(dp);
    }
    fps res(h.size() + 1);
    for (auto [_, f] : pd) res += f;
    return res;
}

#include <cassert>

void test() {
    const std::vector<int> h { 6, 2, 5, 3, 2, 4, 5, 2, 3 };
    const int n = h.size();
    fps f = suisen::rook_polynomial_skyline_board<fps>(h);
    fps g = naive(h);
    std::cout << (f == g ? "AC" : "WA") << std::endl;
    for (int i = 0; i <= n; ++i) std::cout << f[i] << " \n"[i == n];
    for (int i = 0; i <= n; ++i) std::cout << g[i] << " \n"[i == n];
}

int main() {
    test();
    std::cout << "Hello World" << std::endl;
    return 0;
}
