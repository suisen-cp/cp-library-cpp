#ifndef SUISEN_DIRECTED_EULERIAN_GRAPH
#define SUISEN_DIRECTED_EULERIAN_GRAPH

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace suisen {
    struct DirectedEulerianGraph {
        DirectedEulerianGraph() = default;
        DirectedEulerianGraph(int n) : n(n), g(n), in_deg(n, 0) {}

        void add_edge(int u, int v) {
            g[u].push_back(v);
            ++in_deg[v];
        }

        std::optional<std::vector<int>> eulerian_circuit(int start = 0) {
            std::size_t edge_num = 0;
            std::vector<std::vector<bool>> used(n);
            for (int i = 0; i < n; ++i) {
                const int sz = g[i].size();
                edge_num += sz;
                used[i].resize(sz, false);
                if (in_deg[i] != sz) return std::nullopt;
            }
            std::vector<int> res;
            std::vector<std::size_t> iter(n);
            auto dfs = [&](auto dfs, int u) -> void {
                for (std::size_t &i = iter[u]; i < g[u].size(); ++i) {
                    if (used[u][i]) continue;
                    const int v = g[u][i];
                    used[u][i] = true;
                    dfs(dfs, v);
                }
                res.push_back(u);
            };
            dfs(dfs, start);
            std::reverse(res.begin(), res.end());
            if (res.size() != edge_num + 1) return std::nullopt;
            return res;
        }
        std::optional<std::vector<int>> eulerian_trail() {
            int s = -1, t = -1, invalid = -1;
            for (int i = 0; i < n; ++i) {
                int out_deg = g[i].size();
                if (out_deg == in_deg[i] + 1) {
                    (s < 0 ? s : invalid) = i;
                } else if (out_deg == in_deg[i] - 1) {
                    (t < 0 ? t : invalid) = i;
                } else if (out_deg != in_deg[i]) {
                    invalid = i;
                }
            }
            if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;
            add_edge(t, s);
            auto res = *eulerian_circuit(s);
            res.pop_back();
            // remove edge (t, s)
            g[t].pop_back();
            if (res.back() == t) return res;
            auto is_ts_edge = [&](int u, int v) {
                return u == t and v == s;
            };
            std::rotate(res.begin(), std::adjacent_find(res.begin(), res.end(), is_ts_edge) + 1, res.end());
            return res;
        }
        
        const std::vector<int>& operator[](int u) const {
            return g[u];
        }
    private:
        int n;
        std::vector<std::vector<int>> g;
        std::vector<int> in_deg;
    };
}

#endif // SUISEN_DIRECTED_EULERIAN_GRAPH
