#define PROBLEM "https://atcoder.jp/contests/abc238/tasks/abc238_f"

#include <iostream>
#include "library/datastructure/bbst/implicit_treap_segtree.hpp"

#include <atcoder/modint>
 
using mint = atcoder::modint998244353;
 
mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}
mint toggle(mint x) {
    return x;
}
 
using Sequence = suisen::DynamicSegmentTree<mint, op, e, toggle>;
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n, k;
    std::cin >> n >> k;
 
    std::vector<int> p(n), q(n);
    for (auto& e : p) std::cin >> e, --e;
    for (auto& e : q) std::cin >> e, --e;
 
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[p[i]] = q[i];
    }
 
    std::vector<Sequence> dp(k + 1);
    for (int c = 0; c <= k; ++c) {
        dp[c].push_back(c == 0);
    }
 
    std::vector<int> index(n, 0);
 
    for (int i = 0; i < n; ++i) {
        for (int c = k; c >= 0; --c) {
            Sequence rseq = dp[c].split(index[v[i]]);
            dp[c].push_back(rseq.prod_all());
            if (c < k) {
                dp[c + 1].merge(rseq);
            } else {
                rseq.free();
            }
        }
        dp[0].merge(std::vector<mint>(i + 1 - index[v[i]], 0));
        for (int m = v[i] + 1; m < n; ++m) {
            ++index[m];
        }
    }
 
    std::cout << dp[k].prod_all().val() << std::endl;
 
    return 0;
}