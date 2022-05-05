#ifndef SUISEN_TWO_EDGE_CONNECTED_COMPONENTS
#define SUISEN_TWO_EDGE_CONNECTED_COMPONENTS

#include "library/graph/low_link.hpp"

namespace suisen {
    struct TwoEdgeConnectedComponents : public LowLink {
        TwoEdgeConnectedComponents()
            : TwoEdgeConnectedComponents(0) {}
        TwoEdgeConnectedComponents(const int n)
            : LowLink(n), _comp_id(_n, -1), _comp_num(0) {}
        TwoEdgeConnectedComponents(const int n, const std::vector<std::pair<int, int>> &edges)
            : LowLink(n, edges), _comp_id(_n, -1), _comp_num(0) {
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

        int operator[](int v) const {
            assert(_built);
            return _comp_id[v];
        }
        
        std::vector<std::vector<int>> groups() const {
            assert(_built);
            std::vector<std::vector<int>> res(component_num());
            for (int i = 0; i < _n; ++i) res[_comp_id[i]].push_back(i);
            return res;
        }

        // v -> list of (adjacent_vertex, edge_id)
        std::vector<std::vector<std::pair<int, int>>> reduced_forest() const {
            assert(_built);
            std::vector<std::vector<std::pair<int, int>>> reduced(_comp_num);
            for (int u = 0; u < _n; ++u) {
                for (const auto &[v, edge_id] : _g[u]) {
                    const int comp_u = (*this)[u], comp_v = (*this)[v];
                    if (comp_u != comp_v) reduced[comp_u].emplace_back(comp_v, edge_id);
                }
            }
            return reduced;
        }

    private:
        std::vector<int> _comp_id;
        int _comp_num;

        void dfs(int u, int p) {
            if (p >= 0 and _low_link[u] <= _pre_order[p]) {
                _comp_id[u] = _comp_id[p];
            } else {
                _comp_id[u] = _comp_num++;
            }
            for (const auto &e : _g[u]) {
                const int v = e.first;
                if (_comp_id[v] < 0) dfs(v, u);
            }
        }
        void dfs_for_all_connected_components() {
            _comp_num = 0;
            for (int i = 0; i < _n; ++i) {
                if (_comp_id[i] < 0) dfs(i, -1);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_TWO_EDGE_CONNECTED_COMPONENTS
