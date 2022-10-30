#ifndef SUISEN_SINGLE_SOURCE_SHORTEST_PATH_DAG
#define SUISEN_SINGLE_SOURCE_SHORTEST_PATH_DAG

#include <deque>
#include <limits>
#include <vector>

#include "library/graph/csr_graph.hpp"

namespace suisen {
    template <typename T>
    std::vector<typename Graph<T>::weight_type_or_1> single_source_shortest_path_dag(const Graph<T>& g, const int s) {
        using cost_type = typename Graph<T>::weight_type_or_1;
        constexpr cost_type inf = std::numeric_limits<cost_type>::max();
        const int n = g.size();
        std::vector<cost_type> res(n, inf);
        res[s] = 0;

        std::vector<int> in(n);
        for (int i = 0; i < n; ++i) for (int j : g[i]) {
            ++in[j];
        }
        assert(in[s] == 0);
        std::deque<int> dq;
        for (int i = 0; i < n; ++i) if (in[i] == 0) {
            dq.push_back(i);
        }
        for (int cnt = 0; cnt < n; ++cnt) {
            assert(dq.size());
            int u = dq.front();
            dq.pop_front();
            for (const auto &e : g[u]) {
                const int v = e;
                if (res[u] != inf) {
                    res[v] = std::min(res[v], res[u] + g.get_weight(e));
                }
                if (--in[v] == 0) {
                    dq.push_back(v);
                }
            }
        }
        return res;
    }
} // namespace suisen


#endif // SUISEN_SINGLE_SOURCE_SHORTEST_PATH_DAG
