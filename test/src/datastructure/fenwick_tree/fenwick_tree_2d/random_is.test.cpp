#define PROBLEM "https://atcoder.jp/contests/arc108/tasks/arc108_e"

#include <iostream>
#include <atcoder/modint>

#include "library/math/inv_mods.hpp"
#include "library/datastructure/segment_tree/segment_tree.hpp"
#include "library/datastructure/fenwick_tree/fenwick_tree_2d.hpp"

using namespace suisen;
using mint = atcoder::modint1000000007;

mint op(mint x, mint y) {
    return x + y;
}
mint e() {
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);

    inv_mods<mint> invs(n);

    for (int &e : a) std::cin >> e;
    a.insert(a.begin(), 0);
    a.insert(a.end(), n + 1);

    std::vector dp_segs(n + 2, SegmentTree<mint, op, e>(n + 2));
    std::vector pd_segs(n + 2, SegmentTree<mint, op, e>(n + 2));

    FenwickTree2D<int> ft_point(n + 2, n + 2);
    for (int i = 1; i <= n; ++i) ++ft_point[{i, a[i]}];

    mint ans = 0;
    for (int w = 1; w <= n; ++w) {
        for (int l = 1, r = w; r <= n; ++l, ++r) {
            int vl = a[l - 1], vr = a[r + 1];
            if (vl > vr) continue;
            int k = ft_point(l, r + 1, vl, vr);
            if (k == 0) continue;
            mint val = 1 + ((dp_segs[l](vl, vr) + pd_segs[r](vl, vr)) * invs[k]).val();
            dp_segs[l][a[r + 1]] += val;
            pd_segs[r][a[l - 1]] += val;
            if (w == n) ans = val;
        }
    }
    std::cout << ans.val() << std::endl;
    return 0;
}


