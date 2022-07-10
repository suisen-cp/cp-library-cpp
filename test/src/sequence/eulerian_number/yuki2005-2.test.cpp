#define PROBLEM "https://yukicoder.me/problems/no/2005"

#include <iostream>
#include <atcoder/convolution>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

std::istream& operator>>(std::istream& in, mint &a) {
    long long e; in >> e; a = e;
    return in;
}

std::ostream& operator<<(std::ostream& out, const mint &a) {
    out << a.val();
    return out;
}

#include "library/sequence/eulerian_number.hpp"
#include "library/datastructure/deque_aggregation.hpp"

mint op(mint x, mint y) {
    return x * y;
}
mint e() {
    return 1;
}

constexpr uint32_t K_MAX = 5000;

int main() {
    suisen::FPS<mint>::set_multiplication([](const auto &a, const auto &b) { return atcoder::convolution(a, b); });

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t n;
    uint64_t m;
    std::cin >> n >> m;

    std::vector<mint> c(K_MAX + 1);
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t k;
        std::cin >> k;
        ++c[k];
    }
    suisen::factorial<mint> fac(n + K_MAX);

    mint ans = 0;

    suisen::DequeAggregation<mint, op, e> dq;
    for (uint32_t d = 0; d < n; ++d) dq.push_front(m + d);
    for (uint32_t k = 1; k <= K_MAX; ++k) {
        std::vector<mint> e = suisen::eulerian_number<mint>(k);
        dq.push_front(m + n + k - 1);
        mint sum = 0;
        const uint32_t p = std::min(uint64_t(k), m);
        for (uint32_t i = 0; i < p; ++i) {
            sum += e[i] * dq.prod();
            dq.pop_front();
            dq.push_back(m - i - 1);
        }
        ans += c[k] * sum * fac.fac_inv(n + k);
        for (uint32_t i = p; i --> 0;) {
            dq.push_front(m - i + n + k - 1);
            dq.pop_back();
        }
    }
    std::cout << ans.val() << std::endl;

    return 0;
}