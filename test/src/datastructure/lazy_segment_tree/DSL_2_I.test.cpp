#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I"

#include <iostream>

#include "library/datastructure/lazy_segment_tree.hpp"
using suisen::LazySegmentTree;

constexpr std::pair<long long, int> e { 0LL, 0 };
std::pair<long long, int> op(const std::pair<long long, int> &p1, const std::pair<long long, int> &p2) {
    auto [s1, l1] = p1;
    auto [s2, l2] = p2;
    return { s1 + s2, l1 + l2 };
}
constexpr long long id = std::numeric_limits<long long>::min();
std::pair<long long, int> mapping(long long f, const std::pair<long long, int> &p) {
    int l = p.second;
    return f == id ? p : std::make_pair(f * l, l);
}
long long composition(long long f, long long g) {
    return f == id ? g : f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    LazySegmentTree seg(std::vector<std::pair<long long, int>>(n, { 0LL, 1 }), e, op, id, mapping, composition);
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        std::cin >> t >> l >> r;
        ++r;
        if (t == 0) {
            long long x;
            std::cin >> x;
            seg.apply(l, r, x);
        } else {
            std::cout << seg(l, r).first << '\n';
        }
    }
    return 0;
}