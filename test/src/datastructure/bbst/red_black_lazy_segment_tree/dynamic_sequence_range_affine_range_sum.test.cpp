#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <algorithm>
#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/bbst/red_black_lazy_segment_tree.hpp"

mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}
mint mapping(std::pair<mint, mint> f, mint x, int len) {
    return f.first * x + f.second * len;
}
std::pair<mint, mint> composition(std::pair<mint, mint> f, std::pair<mint, mint> g) {
    return { f.first * g.first, f.first * g.second + f.second };
}
std::pair<mint, mint> id() {
    return { 1, 0 };
}

using Node = suisen::bbst::lazy_segtree::RedBlackTreeNode<mint, op, e, std::pair<mint, mint>, mapping, composition, id>;
using Tree = Node::tree_type;

constexpr int INSERT = 0;
constexpr int ERASE = 1;
constexpr int REVERSE = 2;
constexpr int APPLY = 3;
constexpr int PROD = 4;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> init(n);
    for (auto& v : init) std::cin >> v;

    Node::init_pool(4000100);

    Tree t = Node::build(init);
    std::reverse(init.begin(), init.end());
    Tree rt = Node::build(init);

    while (q-- > 0) {
        int query_type;
        std::cin >> query_type;
        int siz = Node::size(t);
        if (query_type == INSERT) {
            int i, x;
            std::cin >> i >> x;
            t = Node::insert(t, i, x);
            rt = Node::insert(rt, siz - i, x);
        } else if (query_type == ERASE) {
            int i;
            std::cin >> i;
            t = Node::erase(t, i).first;
            rt = Node::erase(rt, siz - i - 1).first;
        } else if (query_type == REVERSE) {
            int l, r;
            std::cin >> l >> r;
            auto [tl, tm, tr] = Node::split_range(t, l, r);
            auto [rl, rm, rr] = Node::split_range(rt, siz - r, siz - l);
            t = Node::merge(Node::merge(tl, rm), tr);
            rt = Node::merge(Node::merge(rl, tm), rr);
        } else if (query_type == APPLY) {
            int l, r, a, b;
            std::cin >> l >> r >> a >> b;
            t = Node::apply(t, l, r, { a, b });
            rt = Node::apply(rt, siz - r, siz - l, { a, b });
        } else if (query_type == PROD) {
            int l, r;
            std::cin >> l >> r;
            mint res;
            std::tie(t, res) = Node::prod(t, l, r);
            std::cout << res.val() << '\n';
        } else {
            assert(false);
        }
    }
    return 0;
}