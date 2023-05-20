#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series"

#include <iostream>

#include "library/polynomial/compose.hpp"

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

    std::vector<mint> a(n), b(n);
    for (auto &e : a) std::cin >> e;
    for (auto &e : b) std::cin >> e;

    std::vector<mint> c = suisen::compose(a, b, n);
    for (int i = 0; i < n; ++i) {
        std::cout << c[i];
        if (i + 1 != n) std::cout << ' ';
    }
    std::cout << '\n';
}