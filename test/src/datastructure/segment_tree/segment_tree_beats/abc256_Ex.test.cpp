#define PROBLEM "https://atcoder.jp/contests/abc256/tasks/abc256_Ex"

#include <iostream>

#include "library/datastructure/segment_tree/segment_tree_beats.hpp"

constexpr int inf = 200000;

struct S {
    long long sum;
    int len;
    bool same;
    bool fail = false;

    S() : S(0, 0, true) {}
    S(int v, int len = 1) : S((long long) v * len, len, true) {}
    S(long long sum, int len, bool same) : sum(sum), len(len), same(same) {}
};

S op(S x, S y) {
    if (x.len == 0) return y;
    if (y.len == 0) return x;
    return S { x.sum + y.sum, x.len + y.len, x.same and y.same and x.sum / x.len == y.sum / y.len };
}
S e() {
    return S{};
}
S mapping(int f, S x) {
    if (x.len == 0 or f == -1) return x;
    if (f >= 0) return S { f, x.len };
    if (x.same) return S { int((x.sum / x.len) / -f), x.len };
    x.fail = true;
    return x;
}
int composition(int f, int g) {
    if (f >= 0) return f;
    if (g >= 0) return g / -f;
    return -((long long) f * g <= inf ? f * g : inf);
}
int id() {
    return -1;
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
        init[i] = v; 
    }

    suisen::SegmentTreeBeats<S, op, e, int, mapping, composition, id> seg(init);

    while (q --> 0) {
        int query_type, l, r;
        std::cin >> query_type >> l >> r;
        --l;
        if (query_type == 1) {
            int x;
            std::cin >> x;
            seg.apply(l, r, -x);
        } else if (query_type == 2) {
            int y;
            std::cin >> y;
            seg.apply(l, r, y);
        } else if (query_type == 3) {
            std::cout << seg.prod(l, r).sum << '\n';
        } else {
            assert(false);
        }
    }

    return 0;
}