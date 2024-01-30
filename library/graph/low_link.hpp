#ifndef SUISEN_LOW_LINK
#define SUISEN_LOW_LINK

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

namespace suisen {
    struct LowLink {
        LowLink() : LowLink(0) {}
        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n, -1), _low_link(n), _built(false), _conn_comp_num(0), _par(n, -1) {}
        LowLink(const int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n) {
            for (const auto &[u, v] : edges) add_edge(u, v);
            build();
        }
        
        // Add an edge and return its ID. IDs are assigned in the order (0,1,2, ...).
        int add_edge(int u, int v) {
            _built = false;
            _edges.emplace_back(u, v);
            _g[u].emplace_back(v, _m);
            _g[v].emplace_back(u, _m);
            return _m++;
        }

        void build() {
            dfs_for_all_connected_components();
            _built = true;
        }

        int vertex_num() const { return _n; }
        int edge_num()   const { return _m; }

        const std::pair<int, int>& edge(int edge_id) const { return _edges[edge_id]; }
        const std::vector<std::pair<int, int>>& edges() const { return _edges; }
        // list of edges { u, edge_id } adjacent to the vertex v.
        const std::vector<std::pair<int, int>>& operator[](int v) const { return _g[v]; }
        
        int pre_order(int v) const {
            assert(_built);
            return _pre_order[v];
        }
        int low_link(int v) const {
            assert(_built);
            return _low_link[v];
        }

        // Returns IDs of bridges.
        const std::vector<int>& bridge_ids() const {
            assert(_built);
            return _bridges;
        }
        const std::vector<int>& articulation_points() const {
            assert(_built);
            return _articulation_points;
        }

        // O(1)
        // Assuming that there exists the edge {u,v}, return whether the edge is a bridge or not.
        bool is_bridge(int u, int v) const {
            assert(_built);
            if (_pre_order[u] > _pre_order[v]) std::swap(u, v);
            // u is an ancestor of v
            return _pre_order[u] < _low_link[v];
        }

        // O(# edges incident with u)
        // Return whether the vertex is a articulation point or not.
        bool is_articulation_point(int u) const {
            assert(_built);
            return connected_component_num_if_removed(u) > connected_component_num();
        }

        // Return the number of connected components
        int connected_component_num() const {
            assert(_built);
            return _conn_comp_num;
        }

        // O(1)
        // Assuming that there exists the edge {u,v}, return the number of connected components of the graph obtained by removing an edge {u,v}.
        // If there are multiple edges {u,v}, consider removing only one of them.
        int connected_component_num_if_removed(int u, int v) const {
            assert(_built);
            return _conn_comp_num + is_bridge(u, v);
        }

        // O(# edges incident with u)
        // Return the number of connected components of the graph obtained by removing an vertex u and edges incident with it.
        int connected_component_num_if_removed(int u) const {
            assert(_built);
            static std::vector<int8_t> seen;
            if (seen.size() < size_t(_n)) seen.resize(_n);
            bool is_root = true;
            int res = 0;
            for (const auto& [v, _] : _g[u]) {
                if (_pre_order[v] < _pre_order[u]) {
                    is_root = false;
                    continue;
                }
                if (_par[v] == u and not std::exchange(seen[v], true)) {
                    res += (_pre_order[u] <= _low_link[v]);
                }
            }
            // rollback
            for (const auto& [v, _] : _g[u]) seen[v] = false;
            return _conn_comp_num - 1 + res + (not is_root);
        }
    protected:
        int _n, _m;
        // list of edges
        std::vector<std::pair<int, int>> _edges;
        // vertex -> list of (adjacent vertex, edge id)
        std::vector<std::vector<std::pair<int, int>>> _g;
        // vertex -> pre order
        std::vector<int> _pre_order;
        std::vector<int> _low_link;
        // list of ids of bridges
        std::vector<int> _bridges;
        std::vector<int> _articulation_points;

        bool _built;

    private:
        // # connected components
        int _conn_comp_num;
        std::vector<int> _par;

        void dfs(const int u, const int prev_id, int& ord) {
            const bool is_root = prev_id < 0;
            bool is_articulation_point = false;
            int ch_cnt = 0;
            _pre_order[u] = _low_link[u] = ord++;
            for (const auto& [v, id] : _g[u]) if (id != prev_id) {
                if (_pre_order[v] < 0) {
                    _par[v] = u;
                    ++ch_cnt;
                    dfs(v, id, ord);
                    _low_link[u] = std::min(_low_link[u], _low_link[v]);
                    if (_pre_order[u] <= _low_link[v]) {
                        is_articulation_point = not is_root;
                        if (_pre_order[u] != _low_link[v]) _bridges.push_back(id);
                    }
                } else {
                    _low_link[u] = std::min(_low_link[u], _pre_order[v]);
                }
            }
            if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);
        }

        void dfs_for_all_connected_components() {
            for (int i = 0, ord = 0; i < _n; ++i) if (_pre_order[i] < 0) {
                dfs(i, -1, ord);
                ++_conn_comp_num;
            }
        }
    };
} // namespace suisen


#endif // SUISEN_LOW_LINK
