#ifndef SUISEN_BFS_COMPLEMENT
#define SUISEN_BFS_COMPLEMENT

#include <algorithm>
#include <cstdint>
#include <deque>
#include <numeric>
#include <utility>
#include <vector>

namespace suisen {
    struct ComplementBFS {
        static constexpr int unreachable = -1;

        ComplementBFS(int n = 0) : n(n), g(n) {}
        template <typename Edges>
        ComplementBFS(int n, const Edges &edges) : ComplementBFS(n) {
            for (const auto &[u, v] : edges) add_edge(u, v);
        }
        ComplementBFS(const std::vector<std::vector<int>>& g) : n(g.size()), g(g) {}

        void add_edge(int u, int v) {
            g[u].push_back(v);
            g[v].push_back(u);
        }

        std::vector<int> distance(const std::vector<int>& src) const {
            std::vector<int> s = [&] {
                std::vector<int8_t> is_src(n);
                for (int v : src) is_src[v] = true;
                std::vector<int> s;
                for (int i = 0; i < n; ++i) if (not is_src[i]) s.push_back(i);
                return s;
            }();

            std::vector<int> dist(n, unreachable);
            for (int v : src) dist[v] = 0;

            std::vector<int8_t> adj(n);
            std::deque<int> dq(src.begin(), src.end());
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int v : g[u]) adj[v] = true;
                std::size_t nsiz = std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; }) - s.begin();
                for (; s.size() > nsiz; s.pop_back()) {
                    int v = s.back();
                    dist[v] = dist[u] + 1, dq.push_back(v);
                }
                for (int v : g[u]) adj[v] = false;
            }
            return dist;
        }
        std::vector<int> distance(int s) const {
            return distance(std::vector<int>{ s });
        }

        std::vector<std::vector<int>> connected_components() const {
            std::vector<std::vector<int>> res;

            std::vector<int8_t> vis(n, false);

            std::vector<int> s(n);
            std::iota(s.begin(), s.end(), 0);

            std::vector<int8_t> adj(n);
            for (int i = 0; i < n; ++i) if (not vis[i]) {
                s.erase(std::find(s.begin(), s.end(), i));
                auto& cmp = res.emplace_back();
                std::deque<int> dq{ i };
                while (dq.size()) {
                    int u = dq.front();
                    dq.pop_front();
                    cmp.push_back(u);
                    vis[u] = true;
                    for (int v : g[u]) adj[v] = true;
                    auto it = std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; });
                    std::move(it, s.end(), std::back_inserter(dq));
                    s.erase(it, s.end());
                    for (int v : g[u]) adj[v] = false;
                }
            }
            return res;
        }
    private:
        int n;
        std::vector<std::vector<int>> g;
    };
} // namespace suisen


#endif // SUISEN_BFS_COMPLEMENT
