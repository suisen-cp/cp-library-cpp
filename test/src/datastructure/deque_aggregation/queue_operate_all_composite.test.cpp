#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include <iostream>
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

#include "library/datastructure/deque_aggregation.hpp"

std::pair<mint, mint> op(std::pair<mint, mint> g, std::pair<mint, mint> f) {
    return { f.first * g.first, f.first * g.second + f.second };
}
std::pair<mint, mint> e() {
    return { 1, 0 };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    suisen::DequeAggregation<std::pair<mint, mint>, op, e> dq;

    int q;
    std::cin >> q;

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            mint a, b;
            std::cin >> a >> b;
            dq.push_back({ a, b });
        } else if (query_type == 1) {
            dq.pop_front();
        } else {
            mint x;
            std::cin >> x;
            auto [a, b] = dq.prod();
            std::cout << a * x + b << '\n';
        }
    }
    return 0;
}