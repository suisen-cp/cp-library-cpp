#define PROBLEM "https://atcoder.jp/contests/abc255/tasks/abc255_Ex"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp"

mint sum_lr(mint l, mint r) {
    static const mint inv_2 = mint(2).inv();
    return (r * (r - 1) - l * (l - 1)) * inv_2;
}

mint init(long long, long long) {
    return 0;
}
mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}
mint mapping(std::pair<bool, mint> f, mint x, long long l, long long r) {
    return f.first ? f.second * sum_lr(l, r) : x;
}
std::pair<bool, mint> composition(std::pair<bool, mint> f, std::pair<bool, mint> g) {
    return not f.first ? g : f;
}
std::pair<bool, mint> id() {
    return { false, 0 };
}

using SegTree = suisen::SparseLazySegmentTree<long long, mint, op, e, std::pair<bool, mint>, mapping, composition, id, init>;

constexpr long long inf = 1'000'000'000'000'000'010LL;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    int q;
    std::cin >> n >> q;

    SegTree seg(inf);
    SegTree::reserve(10000000);

    while (q --> 0) {
        long long d, l, r;
        std::cin >> d >> l >> r;
        ++r;
        std::cout << (d * sum_lr(l, r) - seg.prod(l, r)).val() << '\n';
        seg.apply(l, r, { true, d });
    }

    return 0;
}