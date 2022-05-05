#ifndef SUISEN_BICONNECTED_COMPONENTS
#define SUISEN_BICONNECTED_COMPONENTS

#include <cstdint>
#include "library/graph/low_link.hpp"

namespace suisen {
    struct BiconnectedComponents : public LowLink {
        BiconnectedComponents() 
            : BiconnectedComponents(0) {}
        BiconnectedComponents(const int n) 
            : LowLink(n), _used(_n, false), _comp_id(_m, -1), _comp_num(0) {}
        BiconnectedComponents(const int n, const std::vector<std::pair<int, int>> &edges) 
            : LowLink(n, edges), _used(_n, false), _comp_id(_m, -1), _comp_num(0) {
            dfs_for_all_connected_components();
        }

        void build() {
            LowLink::build();
            dfs_for_all_connected_components();
        }

        int component_num() const {
            assert(_built);
            return _comp_num;
        }

        int operator[](int edge_id) const {
            assert(_built);
            return _comp_id[edge_id];
        }
        
        std::vector<std::vector<int>> edge_groups() const {
            assert(_built);
            std::vector<std::vector<int>> res(component_num());
            for (int i = 0; i < _m; ++i) res[_comp_id[i]].push_back(i);
            return res;
        }

    private:
        std::vector<int8_t> _used;
        std::vector<int> _comp_id;
        int _comp_num;

        void dfs(int u, int par_edge_id) {
            _used[u] = true;
            static std::vector<int> edges;
            for (const auto &[v, edge_id] : _g[u]) if (edge_id != par_edge_id) {
                // edge_id is a new edge
                if (not _used[v] or _pre_order[v] < _pre_order[u]) edges.push_back(edge_id);
                // v is not a new vertex
                if (_used[v]) continue;
                dfs(v, edge_id);
                if (_low_link[v] < _pre_order[u]) continue;
                int e;
                do _comp_id[e = edges.back()] = _comp_num, edges.pop_back(); while (e != edge_id);
                _comp_num++;
            }
        }
        void dfs_for_all_connected_components() {
            _comp_num = 0;
            _comp_id.assign(_m, -1);
            _used.assign(_n, false);
            for (int i = 0; i < _n; ++i) {
                if (not _used[i]) dfs(i, -1);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_BICONNECTED_COMPONENTS
