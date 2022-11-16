#ifndef SUISEN_BFS
#define SUISEN_BFS

#include <algorithm>
#include <cstdint>
#include <deque>
#include <numeric>
#include <utility>
#include <vector>

namespace suisen {
    struct BFS {
        static constexpr int unreachable = -1;

        BFS(int n = 0) : n(n), g(n) {}
        template <typename Edges>
        BFS(int n, const Edges& edges) : BFS(n) {
            for (const auto& [u, v] : edges) add_edge(u, v);
        }
        BFS(const std::vector<std::vector<int>>& g) : n(g.size()), g(g) {}

        void add_edge(int u, int v) {
            g[u].push_back(v);
            g[v].push_back(u);
        }

        std::vector<int> distance(const std::vector<int>& src) const {
            std::vector<int> dist(n, unreachable);
            for (int v : dist) dist[v] = 0;

            std::deque<int> dq(src.begin(), src.end());
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : g[u]) if (dist[v] == unreachable) {
                    dist[v] = dist[u] + 1;
                    dq.push_back(v);
                }
            }
            return dist;
        }
        std::vector<int> distance(int s) const {
            return distance(std::vector<int>{ s });
        }

        std::vector<std::vector<int>> connected_components() const {
            std::vector<std::vector<int>> res;

            std::vector<int8_t> vis(n, false);

            for (int i = 0; i < n; ++i) if (not std::exchange(vis[i], true)) {
                auto& cmp = res.emplace_back();
                std::deque<int> dq{ i };
                while (dq.size()) {
                    int u = dq.front();
                    dq.pop_front();
                    cmp.push_back(u);
                    for (int v : g[u]) if (not std::exchange(vis[v], true)) {
                        dq.push_back(v);
                    }
                }
            }
            return res;
        }
    private:
        int n;
        std::vector<std::vector<int>> g;
    };
} // namespace suisen

#endif // SUISEN_BFS
