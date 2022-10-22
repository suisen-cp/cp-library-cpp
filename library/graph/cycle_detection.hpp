#ifndef SUISEN_CYCLE_DETECTION
#define SUISEN_CYCLE_DETECTION

#include <optional>
#include <vector>

#include "library/graph/csr_graph.hpp"

namespace suisen {
    template <typename T>
    std::optional<std::vector<typename Graph<T>::edge_type>> get_cycle_undirected(Graph<T> &g) {
        using edge_type = typename Graph<T>::edge_type;
        using weight_type = typename Graph<T>::weight_type_or_1;

        const int n = g.size();

        std::vector<edge_type> res;

        std::vector<edge_type> stk(n);
        using iterator = typename std::vector<edge_type>::iterator;
        iterator ptr = stk.begin();
        std::vector<iterator> pos(n, stk.end());
        std::vector<int8_t> vis(n);
        auto dfs = [&](auto dfs, int u, int p = -1, const weight_type &w) -> bool {
            int c = 0;
            pos[u] = ptr;
            for (const auto &e : g[u]) {
                const int v = e;
                weight_type we = g.get_weight(e);
                if (v == p and we == w and ++c == 1) continue;
                if (not std::exchange(vis[v], true)) {
                    *ptr++ = e;
                    if (dfs(dfs, v, u, we)) return true;
                    --ptr;
                } else if (pos[v] != stk.end()) {
                    *ptr++ = e;
                    res.resize(ptr - pos[v]);
                    std::move(pos[v], ptr, res.begin());
                    return true;
                }
            }
            pos[u] = stk.end();
            return false;
        };
        for (int i = 0; i < n; ++i) if (not std::exchange(vis[i], true)) {
            if (dfs(dfs, i, -1, {})) return res;
        }
        return std::nullopt;
    }

    template <typename T>
    std::optional<std::vector<typename Graph<T>::edge_type>> get_cycle_directed(Graph<T> &g) {
        using edge_type = typename Graph<T>::edge_type;
        const int n = g.size();

        std::vector<edge_type> res;

        std::vector<edge_type> stk(n);
        using iterator = typename std::vector<edge_type>::iterator;
        iterator ptr = stk.begin();
        std::vector<iterator> pos(n, stk.end());
        std::vector<int8_t> vis(n);
        auto dfs = [&](auto dfs, int u) -> bool {
            pos[u] = ptr;
            for (const auto &e : g[u]) {
                const int v = e;
                if (not std::exchange(vis[v], true)) {
                    *ptr++ = e;
                    if (dfs(dfs, v)) return true;
                    --ptr;
                } else if (pos[v] != stk.end()) {
                    *ptr++ = e;
                    res.resize(ptr - pos[v]);
                    std::move(pos[v], ptr, res.begin());
                    return true;
                }
            }
            pos[u] = stk.end();
            return false;
        };
        for (int i = 0; i < n; ++i) if (not std::exchange(vis[i], true)) {
            if (dfs(dfs, i)) return res;
        }
        return std::nullopt;
    }
} // namespace suisen

#endif // SUISEN_CYCLE_DETECTION
