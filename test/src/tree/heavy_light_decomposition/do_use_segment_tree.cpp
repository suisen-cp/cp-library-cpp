#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"

#include <iostream>
#include <atcoder/lazysegtree>
#include <library/tree/heavy_light_decomposition.hpp>

struct S {
    int len;
    long long pref, max, suff, sum;
    S(int len, long long pref, long long max, long long suff, long long sum) : len(len), pref(pref), max(max), suff(suff), sum(sum) {}
};

constexpr long long INF = std::numeric_limits<int>::max();

S op1(const S s1, const S s2) {
    int len = s1.len + s2.len;
    long long pref = std::max(s1.pref, s1.sum + s2.pref);
    long long max  = std::max({s1.max, s2.max, s1.suff + s2.pref});
    long long suff = std::max(s1.suff + s2.sum, s2.suff);
    long long sum  = s1.sum + s2.sum;
    return {len, pref, max, suff, sum};
}
S op2(const S s1, const S s2) {
    return op1(s2, s1);
}
S e() { 
    return {0, -INF, -INF, -INF, 0};
}
S mapping(long long f, S x) {
    int len = x.len;
    if (f == -INF or len == 0) return x;
    long long max = f >= 0 ? f * len : f;
    return {len, max, max, max, f * len};
}
long long composition(long long f, long long g) {
    return f == -INF ? g : f;
}
long long id() {
    return -INF;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> w(n);
    for (long long &e : w) {
        std::cin >> e;
    }
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    suisen::HeavyLightDecomposition hld(g);
    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);
    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);
    for (int i = 0; i < n; ++i) {
        hld.update_point(i, [&](int j) {
            seg1.set(j, {1, w[i], w[i], w[i], w[i]});
            seg2.set(j, {1, w[i], w[i], w[i], w[i]});
        });
    }
    for (int i = 0; i < q; ++i) {
        int t, a, b, c;
        std::cin >> t >> a >> b >> c;
        --a, --b;
        if (t == 1) {
            hld.update_path(a, b, [&](int l, int r) {
                seg1.apply(l, r, c);
                seg2.apply(l, r, c);
            });
        } else {
            std::cout << hld.fold_path_noncommutative(
                a, b, e(), op1,
                [&](int l, int r) { return seg1.prod(l, r); },
                [&](int l, int r) { return seg2.prod(l, r); }
            ).max << '\n';
        }
    }
    return 0;
}