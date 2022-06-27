#define PROBLEM "https://atcoder.jp/contests/abc183/tasks/abc183_f"

#include <iostream>
#include <map>

#include "library/datastructure/union_find/union_find_component_sum.hpp"

using sum_type = std::map<int, int>;

void merge(sum_type &par_data, sum_type &ch_data) {
    for (auto &[k, v] : ch_data) par_data[k] += v;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) std::cin >> c[i];

    std::vector<sum_type> init_data(n);
    for (int i = 0; i < n; ++i) {
        ++init_data[i][c[i]];
    }
    suisen::UnionFindComponentSum<sum_type, merge> uf(init_data);

    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 1) {
            int a, b;
            std::cin >> a >> b;
            --a, --b;
            uf.merge(a, b);
        } else {
            int x, y;
            std::cin >> x >> y;
            --x;
            const auto& sum = uf.sum(x);
            if (auto it = sum.find(y); it == sum.end()) {
                std::cout << 0 << '\n';
            } else {
                std::cout << it->second << '\n';
            }
        }
    }

    return 0;
}