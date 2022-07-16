#ifndef SUISEN_BICONNECTED_COMPONENTS
#define SUISEN_BICONNECTED_COMPONENTS

#include <cstdint>
#include <utility>
#include "library/graph/low_link.hpp"

namespace suisen {
    struct BiconnectedComponents : public LowLink {
        BiconnectedComponents() 
            : BiconnectedComponents(0) {}
        BiconnectedComponents(const int n) 
            : LowLink(n), _used(_n, false), _edge_comp_id(_m, -1), _edge_comp_num(0) {}
        BiconnectedComponents(const int n, const std::vector<std::pair<int, int>> &edges) 
            : LowLink(n, edges), _used(_n, false), _edge_comp_id(_m, -1), _edge_comp_num(0) {
            dfs_for_all_connected_components();
        }

        void build() {
            LowLink::build();
            dfs_for_all_connected_components();
        }

        // # of component (including isolated vertices)
        int component_num() const {
            assert(_built);
            return _edge_comp_num + _isolated_vertices.size();
        }
        // component_num() - # of isolated vertices
        int edge_component_num() const {
            assert(_built);
            return _edge_comp_num;
        }
        int isolated_vertex_num() const {
            assert(_built);
            return _isolated_vertices.size();
        }
        bool is_isolated_component(int component_id) const {
            return component_id >= _edge_comp_num;
        } 

        int operator[](int edge_id) const {
            assert(_built);
            return _edge_comp_id[edge_id];
        }

        const std::vector<int>& isolated_vertices() const {
            assert(_built);
            return _isolated_vertices;
        }

        struct Subgraph {
            std::vector<int> vids, eids;
            int vertex_num() const { return vids.size(); }
            int edge_num()   const { return eids.size(); }
            const std::vector<int>& vertex_set() const { return vids; }
            const std::vector<int>& edge_set()   const { return eids; }
            bool operator==(const Subgraph &rhs) const { return vids == rhs.vids and eids == rhs.eids; }
            bool operator!=(const Subgraph &rhs) const { return not (*this == rhs); }
        };
        
        // vector of biconnected components. [0:edge_component_num()) has edges, [edge_component_num(),component_num()) are isolated vertices.
        std::vector<Subgraph> components() const {
            assert(_built);
            std::vector<Subgraph> res(component_num());
            for (int i = 0; i < _m; ++i) {
                res[_edge_comp_id[i]].eids.push_back(i);
            }
            std::vector<int8_t> seen(vertex_num(), false);
            for (int id = 0; id < _edge_comp_num; ++id) {
                for (int eid : res[id].eids) {
                    const auto &[u, v] = edge(eid);
                    if (not std::exchange(seen[u], true)) res[id].vids.push_back(u);
                    if (not std::exchange(seen[v], true)) res[id].vids.push_back(v);
                }
                for (int eid : res[id].eids) {
                    const auto &[u, v] = edge(eid);
                    seen[u] = seen[v] = false;
                }
            }
            int id = _edge_comp_num;
            for (int v : _isolated_vertices) {
                res[id++].vids = { v };
            }
            return res;
        }

    private:
        std::vector<int8_t> _used;
        std::vector<int> _edge_comp_id;
        int _edge_comp_num;
        std::vector<int> _isolated_vertices;

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
                do _edge_comp_id[e = edges.back()] = _edge_comp_num, edges.pop_back(); while (e != edge_id);
                _edge_comp_num++;
            }
        }
        void dfs_for_all_connected_components() {
            _edge_comp_num = 0;
            _edge_comp_id.assign(_m, -1);
            _used.assign(_n, false);
            for (int i = 0; i < _n; ++i) if (not _used[i]) {
                dfs(i, -1);
                if (_g[i].empty()) _isolated_vertices.push_back(i);
            }
        }
    };
} // namespace suisen


#endif // SUISEN_BICONNECTED_COMPONENTS
