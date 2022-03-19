#ifndef SUISEN_UNDIRECTED_EULERIAN_GRAPH
#define SUISEN_UNDIRECTED_EULERIAN_GRAPH

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace suisen {
    struct UndirectedEulerianGraph {
        UndirectedEulerianGraph() {}
        UndirectedEulerianGraph(int n) : n(n), g(n), inv(n) {}

        void add_edge(int u, int v) {
            const int su = g[u].size();
            g[u].push_back(v);
            const int sv = g[v].size();
            g[v].push_back(u);
            inv[u].push_back(sv);
            inv[v].push_back(su);
        }

        std::optional<std::vector<int>> eulerian_circuit(int start = 0) {
            std::size_t edge_num = 0;
            std::vector<std::vector<bool>> used(n);
            for (int i = 0; i < n; ++i) {
                const std::size_t sz = g[i].size();
                edge_num += sz;
                used[i].resize(sz, false);
                if (sz & 1) return std::nullopt;
            }
            edge_num /= 2;
            std::vector<int> res;
            auto dfs = [&](auto dfs, int u) -> void {
                for (std::size_t i = 0; i < g[u].size(); ++i) {
                    if (used[u][i]) continue;
                    const int v = g[u][i];
                    used[u][i] = true;
                    assert(not used[v][inv[u][i]]);
                    used[v][inv[u][i]] = true;
                    dfs(dfs, v);
                }
                res.push_back(u);
            };
            dfs(dfs, start);
            if (res.size() != edge_num + 1) return std::nullopt;
            return res;
        }
        std::optional<std::vector<int>> eulerian_trail() {
            int s = -1, t = -1, invalid = -1;
            for (int i = 0; i < n; ++i) if (g[i].size() & 1) (s < 0 ? s : t < 0 ? t : invalid) = i;
            if (s < 0 or t < 0 or invalid >= 0) return std::nullopt;
            add_edge(s, t);
            auto opt_res = eulerian_circuit(s);
            if (not opt_res.has_value()) return std::nullopt;
            auto res = *opt_res;
            res.pop_back();
            // remove edge (s, t)
            g[s].pop_back(), inv[s].pop_back();
            g[t].pop_back(), inv[t].pop_back();
            if (res.back() == t) return res;
            auto is_st_edge = [&](int u, int v) {
                return (u == s and v == t) or (u == t and v == s);
            };
            std::rotate(res.begin(), std::adjacent_find(res.begin(), res.end(), is_st_edge) + 1, res.end());
            return res;
        }
        
        const std::vector<int>& operator[](int u) const {
            return g[u];
        }
        std::pair<int, int> rev_edge(int u, int i) const {
            return { g[u][i], inv[u][i] };
        }
    private:
        int n;
        std::vector<std::vector<int>> g;
        std::vector<std::vector<int>> inv;

    };
}

#endif // SUISEN_UNDIRECTED_EULERIAN_GRAPH
