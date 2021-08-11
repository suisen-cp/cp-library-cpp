#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <iostream>

#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "library/datastructure/lazy_eval_dynamic_sequence.hpp"
using suisen::LazyEvalDynamicSequence;

struct F {
    mint a, b;
    F compose(F g) {
        return F { a * g.a, a * g.b + b };
    }
};

std::pair<mint, int> op(std::pair<mint, int> x, std::pair<mint, int> y) {
    auto [xs, xl] = x;
    auto [ys, yl] = y;
    return { xs + ys, xl + yl };
}
std::pair<mint, int> e() {
    return { 0, 0 };
}

std::pair<mint, int> mapping(F f, std::pair<mint, int> x) {
    return { f.a * x.first + f.b * x.second, x.second };
}
F composition(F f, F g) {
    return f.compose(g);
}
F id() {
    return { 1, 0 };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    LazyEvalDynamicSequence<std::pair<mint, int>, op, e, F, mapping, composition, id> seq;

    int n, q;
    std::cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        seq.insert(i, { a, 1 });
    }
    while (q --> 0) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int i, x;
            std::cin >> i >> x;
            seq.insert(i, { x, 1 });
        } else if (t == 1) {
            int i;
            std::cin >> i;
            seq.erase(i);
        } else if (t == 2) {
            int l, r;
            std::cin >> l >> r;
            seq.reverse(l, r);
        } else if (t == 3) {
            int l, r, a, b;
            std::cin >> l >> r >> a >> b;
            seq.apply(l, r, { a, b });
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seq(l, r).first.val() << '\n';
        }
    }
    return 0;
}