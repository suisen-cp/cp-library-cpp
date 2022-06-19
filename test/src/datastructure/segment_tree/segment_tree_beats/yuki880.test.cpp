#define PROBLEM "https://yukicoder.me/problems/no/880"

#include <iostream>
#include <numeric>

#include "library/datastructure/segment_tree/segment_tree_beats.hpp"

constexpr long long inf = 2000000000;

struct S {
    long long sum_v;
    int max_v;
    long long lcm_v;
    int siz;
    bool fail = false;

    S(long long sum_v, int max_v, long long lcm_v, int siz) : sum_v(sum_v), max_v(max_v), lcm_v(lcm_v), siz(siz) {}
    S(int v) : sum_v(v), max_v(v), lcm_v(v), siz(1) {}
    S() = default;
};

struct F {
    int upd_v = 0;
    int gcd_v = 0;

    F(int upd_v = 0, int gcd_v = 0) : upd_v(upd_v), gcd_v(gcd_v) {}

    static F upd_query(int upd_v) {
        return F { upd_v, 0 };
    }
    static F gcd_query(int gcd_v) {
        return F { 0, gcd_v };
    }
};

S op(S x, S y) {
    return S { x.sum_v + y.sum_v, std::max(x.max_v, y.max_v), std::min(std::lcm(x.lcm_v, y.lcm_v), inf), x.siz + y.siz };
}
S e() {
    return S { 0LL, 0, 1, 0 };
}

S mapping(F f, S x) {
    if (f.upd_v) return S { (long long) f.upd_v * x.siz, f.upd_v , f.upd_v, x.siz };
    if (f.gcd_v) {
        if (x.siz == 1) {
            return S { std::gcd(x.max_v, f.gcd_v) };
        } else if (f.gcd_v % x.lcm_v) {
            x.fail = true;
        }
    }
    return x;
}

F composition(F f, F g) {
    if (f.upd_v) return f;
    if (g.upd_v) return F::upd_query(std::gcd(g.upd_v, f.gcd_v));
    return F::gcd_query(std::gcd(f.gcd_v, g.gcd_v));
}
F id() {
    return F::gcd_query(0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<S> init(n);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        init[i] = S{v};
    }

    suisen::SegmentTreeBeats<S, op, e, F, mapping, composition, id> seg(init);
    while (q --> 0) {
        int qt;
        std::cin >> qt;
        if (qt == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            seg.apply(l, r, F::upd_query(x));
        } else if (qt == 2) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            seg.apply(l, r, F::gcd_query(x));
        } else if (qt == 3) {
            int l, r;
            std::cin >> l >> r;
            --l;
            std::cout << seg.prod(l, r).max_v << '\n';
        } else {
            int l, r;
            std::cin >> l >> r;
            --l;
            std::cout << seg.prod(l, r).sum_v << '\n';
        }
    }

    return 0;
}