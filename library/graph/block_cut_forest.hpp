#ifndef SUISEN_BLOCK_CUT_FOREST
#define SUISEN_BLOCK_CUT_FOREST

#include "library/graph/remove_multiedges.hpp"
#include "library/graph/biconnected_components.hpp"

namespace suisen {
    struct BlockCutForest {
        BlockCutForest() = default;
        BlockCutForest(const BiconnectedComponents &bcc)
            : _bcc_num(bcc.component_num()), _art_num(bcc.articulation_points().size()), _g(_bcc_num + _art_num), _vertex_num(_bcc_num + _art_num) {
            std::vector<int> art_id(bcc.vertex_num(), -1);
            int next_id = _bcc_num;
            for (int v : bcc.articulation_points()) art_id[v] = next_id++;

            std::vector<int> comp_id(bcc.vertex_num());
            for (int edge_id = 0; edge_id < bcc.edge_num(); ++edge_id) {
                const int cid = bcc[edge_id];
                const auto &[u, v] = bcc.edge(edge_id);
                comp_id[u] = comp_id[v] = cid;
                if (int vid = art_id[u]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);
                if (int vid = art_id[v]; vid >= 0) _g[vid].push_back(cid), _g[cid].push_back(vid);
            }
            remove_multiedges(_g);

            for (int v = 0; v < bcc.vertex_num(); ++v) {
                if (int vid = art_id[v]; vid < 0) {
                    ++_vertex_num[comp_id[v]];
                } else {
                    _vertex_num[vid] = 1;
                    for (int cid : _g[vid]) ++_vertex_num[cid];
                }
            }
        }

        int size() const { return _bcc_num + _art_num; }
        
        bool is_articulation_point(int id)    const { return id >= _bcc_num; }
        bool is_biconnected_component(int id) const { return not is_articulation_point(id); }

        const std::vector<int>& operator[](int id) const { return _g[id]; }
        std::vector<int>& operator[](int id) { return _g[id]; }

        int vertex_num(int id) const { return _vertex_num[id]; }

    private:
        int _bcc_num;
        int _art_num;
        std::vector<std::vector<int>> _g;
        std::vector<int> _vertex_num;
    };
} // namespace suisen


#endif // SUISEN_BLOCK_CUT_FOREST
