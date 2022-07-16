#ifndef SUISEN_LOW_LINK
#define SUISEN_LOW_LINK

#include <cassert>
#include <vector>

namespace suisen {
    struct LowLink {
        LowLink() : LowLink(0) {}
        LowLink(const int n) : _n(n), _m(0), _g(n), _pre_order(n, -1), _low_link(n), _built(false) {}
        LowLink(const int n, const std::vector<std::pair<int, int>> &edges) : LowLink(n) {
            for (const auto &[u, v] : edges) add_edge(u, v);
            build();
        }
        
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

        const std::vector<int>& bridge_ids() const {
            assert(_built);
            return _bridges;
        }
        const std::vector<int>& articulation_points() const {
            assert(_built);
            return _articulation_points;
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
        void dfs(int u, int id, int& ord) {
            bool is_root = id < 0;
            bool is_articulation_point = false;
            int ch_cnt = 0;
            _pre_order[u] = _low_link[u] = ord++;
            for (const auto& [v, id2] : _g[u]) {
                if (id == id2) continue;
                if (_pre_order[v] < 0) {
                    ++ch_cnt;
                    dfs(v, id2, ord);
                    _low_link[u] = std::min(_low_link[u], _low_link[v]);
                    if (_pre_order[u] <= _low_link[v]) {
                        is_articulation_point = not is_root;
                        if (_pre_order[u] != _low_link[v]) _bridges.push_back(id2);
                    }
                } else {
                    _low_link[u] = std::min(_low_link[u], _pre_order[v]);
                }
            }
            if (is_articulation_point or (is_root and ch_cnt > 1)) _articulation_points.push_back(u);
        }

        void dfs_for_all_connected_components() {
            for (int i = 0, ord = 0; i < _n; ++i) {
                if (_pre_order[i] < 0) dfs(i, -1, ord);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_LOW_LINK
