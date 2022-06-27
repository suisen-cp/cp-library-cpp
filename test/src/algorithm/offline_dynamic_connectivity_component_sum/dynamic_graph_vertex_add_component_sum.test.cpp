#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"

#include <iostream>

#include "library/algorithm/offline_dynamic_connectivity_component_sum.hpp"

using S = std::pair<long long, std::vector<long long>>;

void merge(S &pd, const S &cd) {
    pd.second.push_back(std::exchange(pd.first, pd.first + cd.first));
}
void undo(S &d) {
    d.first = d.second.back();
    d.second.pop_back();
}
long long get_value(const S& d) {
    return d.first;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;

    std::vector<S> init_values(n);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        init_values[i] = { v, {} };
    }

    suisen::OfflineDynamicConnectivityComponentSum dyn_con{};
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int u, v;
            std::cin >> u >> v;
            dyn_con.add_query(u, v);
        } else if (query_type == 1) {
            int u, v;
            std::cin >> u >> v;
            dyn_con.del_query(u, v);
        } else if (query_type == 2) {
            int u, p;
            std::cin >> u >> p;
            dyn_con.add_query(u, init_values.size());
            init_values.push_back({ p, {} });
        } else {
            int u;
            std::cin >> u;
            dyn_con.component_sum_query(u);
        }
    }

    auto ans = dyn_con.answer<S, merge, undo, long long, get_value>(std::move(init_values));
    for (const auto &v : ans) {
        std::cout << std::get<1>(v) << '\n';
    }

    return 0;
}
