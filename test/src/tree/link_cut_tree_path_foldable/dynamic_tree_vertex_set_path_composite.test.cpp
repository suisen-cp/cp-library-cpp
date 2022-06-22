#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

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

#include "library/tree/link_cut_tree_path_foldable.hpp"

struct S {
    mint a, b;
    mint ra, rb;

    S() = default;
    S(mint a, mint b) : a(a), b(b), ra(a), rb(b) {}
    S(mint a, mint b, mint ra, mint rb) : a(a), b(b), ra(ra), rb(rb) {}

    S compose(const S &g) const {
        return S { a * g.a, a * g.b + b, g.ra * ra, g.ra * rb + g.rb };
    }
    S toggle() const {
        return S { ra, rb, a, b };
    }
    mint eval(mint x) const {
        return a * x + b;
    }
};

S op(S x, S y) {
    return y.compose(x);
}
S e() {
    return S{ 1, 0 };
}
S toggle(S x) {
    return x.toggle();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<S> a(n);
    for (int i = 0; i < n; ++i) {
        mint c, d;
        std::cin >> c >> d;
        a[i] = S { c, d };
    }

    using DynamicTree = suisen::LinkCutTreePathFoldable<S, op, e, toggle>;

    DynamicTree::init_pool(n);

    auto nodes = DynamicTree::make_nodes(a);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        DynamicTree::link(nodes[u], nodes[v]);
    }

    while (q-- > 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            DynamicTree::cut(nodes[u], nodes[v]);
            DynamicTree::link(nodes[w], nodes[x]);
        } else if (query_type == 1) {
            int p;
            mint c, d;
            std::cin >> p >> c >> d;
            DynamicTree::set(nodes[p], S { c, d });
        } else {
            int u, v;
            mint x;
            std::cin >> u >> v >> x;
            std::cout << DynamicTree::prod(nodes[u], nodes[v]).eval(x) << '\n';
        }
    }

    return 0;
}
