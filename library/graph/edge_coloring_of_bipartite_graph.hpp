#ifndef SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH
#define SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH

#include <algorithm>
#include <array>
#include <cassert>
#include <queue>
#include <utility>

#include <atcoder/dsu>

#include "library/graph/bipartite_matching.hpp"

namespace suisen {
    struct EdgeColoringOfBipartiteGraph {
        EdgeColoringOfBipartiteGraph(int l = 0, int r = 0) : l(l), r(r) {}
        void add_edge(int u, int v) {
            assert(0 <= u and u < l);
            assert(0 <= v and v < r);
            edges.emplace_back(u, v);
        }

        std::pair<int, std::vector<int>> solve() {
            if (edges.empty()) return {};
            std::vector<int> degl(l), degr(r);
            for (const auto& [u, v] : edges) {
                ++degl[u], ++degr[v];
            }
            const int k = std::max(
                *std::max_element(degl.begin(), degl.end()),
                *std::max_element(degr.begin(), degr.end())
            );
            auto [numl, idl] = contract(degl, k);
            auto [numr, idr] = contract(degr, k);
            const int n = std::max(numl, numr);
            degl.assign(n, 0);
            degr.assign(n, 0);
            std::vector<std::pair<int, int>> new_edges;

            new_edges.reserve(n * k);
            for (auto [u, v] : edges) {
                u = idl[u], v = idr[v];
                new_edges.emplace_back(u, v);
                ++degl[u], ++degr[v];
            }
            for (int i = 0, j = 0; i < n; ++i) {
                while (degl[i] < k) {
                    while (degr[j] == k) ++j;
                    new_edges.emplace_back(i, j);
                    ++degl[i], ++degr[j];
                }
            }
            std::vector<int> color = solve_regular(n, k, new_edges);
            color.resize(edges.size());
            return { k, color };
        }

    private:
        int l, r;
        std::vector<std::pair<int, int>> edges;

        template <typename T>
        using priority_queue_greater = std::priority_queue<T, std::vector<T>, std::greater<T>>;

        static std::vector<int> solve_regular(const int n, const int k, const std::vector<std::pair<int, int>>& edges, const int color_offset = 0) {
            assert(n * k == int(edges.size()));
            if (k == 0) {
                return {};
            } else if (k == 1) {
                return std::vector<int>(edges.size(), color_offset);
            } else if ((k & 1) == 0) {
                const int m = edges.size();
                const int hm = m / 2;
                std::vector<std::vector<std::pair<int, int>>> g(n + n);
                for (int i = 0; i < m; ++i) {
                    const auto [u, v] = edges[i];
                    g[u].emplace_back(n + v, i);
                    g[n + v].emplace_back(u, i);
                }
                std::vector<int> circuit;
                std::vector<int8_t> used(m, false), vis(n + n, false);
                std::vector<std::size_t> iter(n + n);
                for (int i = 0; i < n + n; ++i) if (not vis[i]) {
                    auto dfs = [&](auto dfs, int u, int id) -> void {
                        vis[u] = true;
                        for (std::size_t &i = iter[u]; i < g[u].size(); ++i) {
                            auto [v, nid] = g[u][i];
                            if (std::exchange(used[nid], true)) continue;
                            dfs(dfs, v, nid);
                        }
                        if (id >= 0) circuit.push_back(id);
                    };
                    dfs(dfs, i, -1);
                }
                std::array<std::vector<int>, 2> id;
                id[0].reserve(hm), id[1].reserve(hm);
                std::array<std::vector<std::pair<int, int>>, 2> nxt_edges;
                assert(int(circuit.size()) == m);
                for (int i = 0; i < m; ++i) {
                    nxt_edges[i & 1].push_back(edges[circuit[i]]);
                    id[i & 1].push_back(circuit[i]);
                }
                std::array<std::vector<int>, 2> rec_res;
                rec_res[0] = solve_regular(n, k / 2, nxt_edges[0], color_offset);
                rec_res[1] = solve_regular(n, k / 2, nxt_edges[1], color_offset + k / 2);
                std::vector<int> res(m);
                for (int p = 0; p < 2; ++p) {
                    for (int i = 0; i < hm; ++i) {
                        res[id[p][i]] = rec_res[p][i];
                    }
                }
                return res;
            } else {
                BipartiteMatching bimatch(n, n);
                for (const auto& [u, v] : edges) bimatch.add_edge(u, v);
                const int matching_size = bimatch.solve();
                assert(matching_size == n);
                std::vector<std::pair<int, int>> nxt_edges;
                const int m = edges.size();
                std::vector<int> res(m);
                std::vector<int> id(m - n);
                std::vector<int8_t> used(n, false);
                for (int i = 0; i < m; ++i) {
                    auto [u, v] = edges[i];
                    if (bimatch.right(u) == v and not std::exchange(used[u], true)) {
                        res[i] = color_offset;
                    } else {
                        id[nxt_edges.size()] = i;
                        nxt_edges.emplace_back(u, v);
                    }
                }
                std::vector<int> rec_res = solve_regular(n, k - 1, nxt_edges, color_offset + 1);
                assert(rec_res.size() == nxt_edges.size());
                for (int i = 0; i < m - n; ++i) res[id[i]] = rec_res[i];
                return res;
            }
        }

        static std::pair<int, std::vector<int>> contract(const std::vector<int>& deg, const int k) {
            const int n = deg.size();
            atcoder::dsu uf(n);
            priority_queue_greater<std::pair<int, int>> pq{};
            for (int i = 0; i < n; ++i) pq.emplace(deg[i], i);
            while (pq.size() >= 2) {
                auto [di, i] = pq.top();
                pq.pop();
                auto [dj, j] = pq.top();
                pq.pop();
                if (di + dj <= k) {
                    uf.merge(i, j);
                    pq.emplace(di + dj, uf.leader(i));
                } else break;
            }
            auto groups = uf.groups();
            const int m = groups.size();
            std::vector<int> cmp_id(n);
            for (int i = 0; i < m; ++i) for (int v : groups[i]) {
                cmp_id[v] = i;
            }
            return { m, cmp_id };
        }
    };
} // namespace suisen


#endif // SUISEN_EDGE_COLORING_OF_BIPARTITE_GRAPH
