#define PROBLEM "https://atcoder.jp/contests/arc069/tasks/arc069_f"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <atcoder/twosat>

#include "library/graph/segment_tree_graph.hpp"
using namespace suisen;

int main() {
    int n;
    std::cin >> n;

    std::vector xys(2, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        std::cin >> xys[0][i] >> xys[1][i];
    }

    SegmentTreeGraph g(n);

    std::vector ps(2, std::vector<int>(n));
    for (int t = 0; t < 2; ++t) {
        std::iota(ps[t].begin(), ps[t].end(), 0);
        std::sort(ps[t].begin(), ps[t].end(), [&](int i, int j) { return xys[t][i] < xys[t][j]; });
        g.add_order(ps[t]);
    }

    auto get_range = [&](int order_id, long long c, long long d) -> std::pair<int, int> {
        const auto &p = ps[order_id];
        const auto &a = xys[order_id];
        auto bs = [&](long long x) {
            int l = -1, r = n;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                (a[p[m]] < x ? l : r) = m;
            }
            return r;
        };
        return { bs(c - d + 1), bs(c + d) };
    };

    auto check = [&](const long long d) -> bool {
        atcoder::two_sat sat(g.size());

        g.add_edges_to_children(
            [&](int p, int c) {
                assert(g.is_segment_node(p));
                bool b = g.get_segment_node(p).order_id == 0;
                sat.add_clause(c, b, p, not b);
            }
        );

        for (int i = 0; i < n; ++i) {
            for (auto jk : std::vector<std::pair<int, int>> { { 0, 0 }, { 0, 1 }, { 1, 1 } }) {
                const int j = jk.first, k = jk.second, p = ps[j][i];
                auto [l, r] = get_range(k, xys[j][p], d);
                if (j == k) r = i;
                g.add_edge(p, { k, l, r }, [&](int fr, int to) { sat.add_clause(fr, j ^ 1, to, k ^ 1); });
            }
        }

        return sat.satisfiable();
    };

    long long l = 0, r = 1000000001;
    while (r - l > 1) {
        long long d = (l + r) >> 1;
        (check(d) ? l : r) = d;
    }
    std::cout << l << std::endl;

    return 0;
}