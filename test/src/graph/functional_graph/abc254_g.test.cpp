#define PROBLEM "https://atcoder.jp/contests/abc254/tasks/abc254_g"

#include <iostream>

#include "library/datastructure/util/range_set.hpp"
#include "library/graph/functional_graph.hpp"
#include "library/util/coordinate_compressor.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<suisen::RangeSet<int, false>> range_sets(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a, --b, --c;
        range_sets[a].insert(b, c);
    }

    suisen::CoordinateCompressorBuilder<int> comp_builder;
    std::vector<std::tuple<int, int, int, int>> queries(q);
    for (auto& [x, y, z, w] : queries) {
        std::cin >> x >> y >> z >> w;
        --x, --y, --z, --w;
        if (y > w) std::swap(x, z), std::swap(y, w);
        comp_builder.push(y);
    }

    std::vector<std::pair<int, int>> ranges;
    for (const auto& st : range_sets) for (const auto& [l, r] : st) {
        ranges.emplace_back(l, r);
        comp_builder.push(r);
    }
    std::sort(ranges.begin(), ranges.end());
    const int range_num = ranges.size();

    const auto comp = comp_builder.build();
    const int k = comp.size();

    suisen::FunctionalGraph g(k);
    {
        int i = 0, max_r = -1;
        for (int j = 0; j < k; ++j) {
            const int pos = comp.decomp(j);
            while (i < range_num and ranges[i].first <= pos) max_r = std::max(max_r, ranges[i++].second);
            g[j] = max_r < pos ? j : comp[max_r];
        }
    }
    const auto doubling = g.doubling(range_num);

    for (auto& [x, y, z, w] : queries) {
        const int ans = w - y;
        if (const auto itx = range_sets[x].find_range(y); itx != range_sets[x].end()) y = itx->second;
        if (const auto itz = range_sets[z].find_range(w); itz != range_sets[z].end()) w = itz->first;
        if (y >= w) {
            std::cout << ans + (x != z) << '\n';
        } else {
            const int w_ = w;
            const auto opt_res = doubling.step_until(comp[y], [&](int v) { return comp.decomp(v) >= w_; });
            std::cout << (opt_res.has_value() ? ans + opt_res->step + 1 : -1) << '\n';
        }
    }
    return 0;
}