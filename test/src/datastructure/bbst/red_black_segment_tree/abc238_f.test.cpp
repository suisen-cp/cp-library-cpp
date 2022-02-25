#define PROBLEM "https://atcoder.jp/contests/abc238/tasks/abc238_f"

#include <iostream>
#include "library/datastructure/bbst/red_black_segment_tree.hpp"

#include <atcoder/modint>
 
using mint = atcoder::modint998244353;
 
mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}
 
using Node = suisen::bbst::segtree::RedBlackTreeNode<mint, op, e>;
using Tree = Node::tree_type;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node::init_pool(200000);
 
    int n, k;
    std::cin >> n >> k;
 
    std::vector<int> p(n), q(n);
    for (auto& e : p) std::cin >> e, --e;
    for (auto& e : q) std::cin >> e, --e;
 
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[p[i]] = q[i];
    }
 
    std::vector<Tree> dp(k + 1, Node::empty_tree());
    for (int c = 0; c <= k; ++c) {
        dp[c] = Node::push_back(dp[c], c == 0);
    }
 
    std::vector<int> index(n, 0);
 
    for (int i = 0; i < n; ++i) {
        for (int c = k; c >= 0; --c) {
            Tree rseq;
            std::tie(dp[c], rseq) = Node::split(dp[c], index[v[i]]);
            dp[c] = Node::push_back(dp[c], Node::prod_all(rseq));
            if (c < k) {
                dp[c + 1] = Node::merge(dp[c + 1], rseq);
            } else {
                Node::free(rseq);
            }
        }
        dp[0] = Node::merge(dp[0], Node::build(std::vector<mint>(i + 1 - index[v[i]], 0)));
        for (int m = v[i] + 1; m < n; ++m) {
            ++index[m];
        }
    }
 
    std::cout << Node::prod_all(dp[k]).val() << std::endl;
 
    return 0;
}