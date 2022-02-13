#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/datastructure/bbst/red_black_reversible_lazy_segment_tree.hpp"

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

using Node = suisen::bbst::reversible_lazy_segtree::RedBlackTreeNode<mint, op, e, std::pair<mint, mint>, mapping, composition, id>;
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

    Node::init_pool(2000100);

    Tree t = Node::build(init);

    while (q-- > 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == INSERT) {
            int i, x;
            std::cin >> i >> x;
            t = Node::insert(t, i, x);
        } else if (query_type == ERASE) {
            int i;
            std::cin >> i;
            t = Node::erase(t, i).first;
        } else if (query_type == REVERSE) {
            int l, r;
            std::cin >> l >> r;
            t = Node::reverse(t, l, r);
        } else if (query_type == APPLY) {
            int l, r, a, b;
            std::cin >> l >> r >> a >> b;
            t = Node::apply(t, l, r, { a, b });
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