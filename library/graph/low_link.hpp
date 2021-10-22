#ifndef SUISEN_LOW_LINK
#define SUISEN_LOW_LINK

#include <vector>

namespace suisen {
    struct LowLink {
        using Graph = std::vector<std::vector<std::pair<int, int>>>;

        int n, m;
        // vertex -> list of (adjacent vertex, edge id)
        Graph g;
        // vertex -> pre order
        std::vector<int> pre_order;
        std::vector<int> low_link;
        // list of ids of bridges
        std::vector<int> bridges;
        std::vector<int> articulation_points;

        LowLink() : LowLink(0, {}) {}
        LowLink(const int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n, edges.size(), [&edges](int i) { return edges[i]; }) {}
        template <typename EdgeGenerator>
        LowLink(const int n, const int m, EdgeGenerator edge_gen) : n(n), m(m), g(n), pre_order(n, -1), low_link(n) {
            build_graph(edge_gen);
            dfs_for_all_connected_components();
        }
    private:
        template <typename EdgeGenerator>
        void build_graph(EdgeGenerator edge_gen) {
            for (int i = 0; i < m; ++i) {
                auto&& [u, v] = edge_gen(i);
                g[u].emplace_back(v, i);
                g[v].emplace_back(u, i);
            }
        }

        void dfs(int u, int id, int& ord) {
            bool is_root = id < 0;
            bool is_articulation_point = false;
            int ch_cnt = 0;
            pre_order[u] = low_link[u] = ord++;
            for (const auto& [v, id2] : g[u]) {
                if (id == id2) continue;
                if (pre_order[v] < 0) {
                    ++ch_cnt;
                    dfs(v, id2, ord);
                    low_link[u] = std::min(low_link[u], low_link[v]);
                    if (pre_order[u] <= low_link[v]) {
                        is_articulation_point = not is_root;
                        if (pre_order[u] != low_link[v]) bridges.push_back(id2);
                    }
                } else {
                    low_link[u] = std::min(low_link[u], pre_order[v]);
                }
            }
            if (is_articulation_point or (is_root and ch_cnt > 1)) articulation_points.push_back(u);
        }

        void dfs_for_all_connected_components() {
            for (int i = 0, ord = 0; i < n; ++i) {
                if (pre_order[i] < 0) dfs(i, -1, ord);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_LOW_LINK
