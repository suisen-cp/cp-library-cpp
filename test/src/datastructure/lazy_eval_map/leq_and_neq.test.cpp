#define PROBLEM "https://atcoder.jp/contests/arc115/tasks/arc115_e"

#include <algorithm>
#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;

#include "library/util/coordinate_compressor.hpp"
#include "library/datastructure/lazy_eval_map.hpp"

using suisen::CoordinateCompressorBuilder;
using suisen::LazyEvalMap;

struct S {
    mint sum;
    int len;
};
struct F {
    mint a, b;
};

S op(S x, S y) {
    return { x.sum + y.sum, x.len + y.len };
}
S e() {
    return { 0, 0 };
}
S mapping(F f, S x) {
    return { x.sum * f.a + x.len * f.b, x.len };
}
F composition(F f, F g) {
    return { f.a * g.a, f.a * g.b + f.b };
}
F id() {
    return { 1, 0 };
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    CoordinateCompressorBuilder<int> builder(a);
    builder.push(0);
    auto comp = builder.build();
    int m = comp.size();
    LazyEvalMap<int, S, op, e, F, mapping, composition, id> mp;
    for (int i = 1; i < m; ++i) {
        int len = comp.decomp(i) - comp.decomp(i - 1);
        mp[i - 1] = { 0, len };
    }
    mint sum = 1;
    for (int v : a) {
        mp.apply_all({ -1, sum });
        mp.apply_by_key(comp[v], m, { 0, 0 });
        sum = mp.prod_all().sum;
    }
    std::cout << mp.prod_all().sum.val() << '\n';
    return 0;
}