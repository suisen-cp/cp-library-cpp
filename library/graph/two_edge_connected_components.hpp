#ifndef SUISEN_TWO_EDGE_CONNECTED_COMPONENTS
#define SUISEN_TWO_EDGE_CONNECTED_COMPONENTS

#include "library/graph/low_link.hpp"

namespace suisen {
    struct TwoEdgeConnectedComponents : LowLink {
        std::vector<int> comp_id;
        int comp_num;

        TwoEdgeConnectedComponents() : 
            TwoEdgeConnectedComponents(0, {}) {}

        TwoEdgeConnectedComponents(const int n, const std::vector<std::pair<int, int>> &edges) : 
            TwoEdgeConnectedComponents(n, edges.size(), [&edges](int i) { return edges[i]; }) {}

        template <typename EdgeGenerator>
        TwoEdgeConnectedComponents(const int n, const int m, EdgeGenerator edge_gen) : 
            LowLink(n, m, edge_gen), comp_id(n, -1), comp_num(0) { dfs_for_all_connected_components(); }
        
        int operator[](int v) const {
            return comp_id[v];
        }

        Graph reduced_forest() const {
            Graph reduced(comp_num);
            for (int u = 0; u < n; ++u) {
                for (const auto &[v, edge_id] : g[u]) {
                    const int comp_u = (*this)[u], comp_v = (*this)[v];
                    if (comp_u != comp_v) reduced[comp_u].emplace_back(comp_v, edge_id);
                }
            }
            return reduced;
        }

    private:
        void dfs(int u, int p) {
            if (p >= 0 and low_link[u] <= pre_order[p]) {
                comp_id[u] = comp_id[p];
            } else {
                comp_id[u] = comp_num++;
            }
            for (const auto &e : g[u]) {
                const int v = e.first;
                if (comp_id[v] < 0) dfs(v, u);
            }
        }
        void dfs_for_all_connected_components() {
            for (int i = 0; i < n; ++i) {
                if (comp_id[i] < 0) dfs(i, -1);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_TWO_EDGE_CONNECTED_COMPONENTS
