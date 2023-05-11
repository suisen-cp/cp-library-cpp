#ifndef SUISEN_GRID_CONNECTIVITY
#define SUISEN_GRID_CONNECTIVITY

#include <atcoder/dsu>

namespace suisen::grid_connectivity {
    struct Result {
        std::vector<int> next_state;
        int frontier_comp_num;
        int forget_comp_num;
    };
    // -1: None
    // 0, 1, ...: component ID
    Result transition(const std::vector<int> &state, int next_row) {
        const int m = state.size();
        std::vector<int> state2(m, -1);
        for (int i = 0, nid = -1; i < m; ++i) {
            if ((next_row >> i) & 1) {
                state2[i] = i > 0 and state2[i - 1] >= 0 ? state2[i - 1] : ++nid;
            }
        }
        const int V1 = *std::max_element(state.begin(), state.end()) + 1;
        const int V2 = *std::max_element(state2.begin(), state2.end()) + 1;
        const int V = V1 + V2;
        atcoder::dsu uf(V);
        for (int i = 0; i < m; ++i) if (state[i] >= 0 and state2[i] >= 0) {
            uf.merge(state[i], V1 + state2[i]);
        }
        std::vector<int> comp_ids(V);
        std::vector<std::vector<int>> groups = uf.groups();
        const int k = groups.size();
        for (int comp_id = 0; comp_id < k; ++comp_id) {
            for (int v : groups[comp_id]) comp_ids[v] = comp_id;
        }
        std::vector<int> normalize(k, -1);
        for (int i = 0, nid = 0; i < m; ++i) if (state2[i] >= 0) {
            int comp_id = comp_ids[V1 + state2[i]];
            if (normalize[comp_id] == -1) {
                normalize[comp_id] = nid++;
            }
            state2[i] = normalize[comp_id];
        }
        const int frontier_comp_num = *std::max_element(state2.begin(), state2.end()) + 1;
        const int forget_comp_num = k - frontier_comp_num;
        return Result{ state2, frontier_comp_num, forget_comp_num };
    }
} // namespace suisen


#endif // SUISEN_GRID_CONNECTIVITY
