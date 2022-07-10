#define PROBLEM "https://atcoder.jp/contests/abc259/tasks/abc259_d"

#include <iostream>
#include <atcoder/dsu>

#include "library/integral_geom/geometry.hpp"
using namespace suisen::integral_geometry;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    Point s, t;
    std::cin >> s >> t;

    std::vector<Circle> cs(n + 2);
    cs[0] = { s, 0 }, cs[n + 1] = { t, 0 };
    for (int i = 1; i <= n; ++i) {
        Point c;
        long long r;
        std::cin >> c >> r;
        cs[i] = { c, r };
    }
    
    atcoder::dsu uf(n + 2);
    for (int i = 0; i < n + 2; ++i) for (int j = 0; j < i; ++j) {
        if (has_common_point(cs[i], cs[j])) uf.merge(i, j);
    }
    std::cout << (uf.same(0, n + 1) ? "Yes" : "No") << std::endl;
    
    return 0;
}