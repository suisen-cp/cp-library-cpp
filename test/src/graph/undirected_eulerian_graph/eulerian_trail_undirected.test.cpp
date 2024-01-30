#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"

#include <map>
#include <iostream>
#include "library/graph/undirected_eulerian_graph.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    for (int tc = 0; tc < t; ++tc) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::map<int, std::vector<int>>> mps(n);
        suisen::UndirectedEulerianGraph g(n);
        for (int e = 0; e < m; ++e) {
            int u, v;
            std::cin >> u >> v;
            g.add_edge(u, v);
            if (u > v) std::swap(u, v);
            mps[u][v].push_back(e);
        }
        auto p = g.eulerian_trail();
        if (p) {
            std::cout << "Yes\n";
            for (int i = 0; i < m; ++i) {
                std::cout << (*p)[i] << ' ';
            }
            std::cout << p->back() << '\n';
            for (int i = 0; i < m; ++i) {
                int u = (*p)[i], v = (*p)[i + 1];
                if (u > v) std::swap(u, v);
                auto &es = mps[u][v];
                if (i) std::cout << ' ';
                std::cout << es.back();
                es.pop_back();
            }
            std::cout << '\n';
        } else {
            std::cout << "No\n";
        }
    }
}
