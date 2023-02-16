#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

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

#include "library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp"
#include "library/algebra/monoid/affine.hpp"

using S = mint;
using F = suisen::Affine<mint>;

S op(S x, S y) {
    return x + y;
}
S e() {
    return 0;
}
S toggle(S x) {
    return x;
}
S mapping(F f, S x, int len) {
    return f.a * x + f.b * len;
}
F composition(F f, F g) {
    return f.compose(g);
}
F id() {
    return F::id();
}

using Sequence = suisen::ReversibleDynamicLazySegmentTree<S, op, e, toggle, F, mapping, composition, id>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<S> init(n);
    for (auto &e : init) std::cin >> e;

    Sequence::reserve(1000000);

    Sequence seq(std::move(init));

    for (int qid = 0; qid < q; ++qid) {
        int qtype;
        std::cin >> qtype;

        if (qtype == 0) {
            int i;
            mint x;
            std::cin >> i >> x;
            seq.insert(i, x);
        } else if (qtype == 1) {
            int i;
            std::cin >> i;
            seq.erase(i);
        } else if (qtype == 2) {
            int l, r;
            std::cin >> l >> r;
            seq.reverse(l, r);
        } else if (qtype == 3) {
            int l, r;
            mint b, c;
            std::cin >> l >> r >> b >> c;
            seq.apply(l, r, F { b, c });
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seq.prod(l, r) << '\n';
        }
    }
}