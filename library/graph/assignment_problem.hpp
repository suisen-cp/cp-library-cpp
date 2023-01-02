#ifndef SUISEN_MIN_COST_FLOW
#define SUISEN_MIN_COST_FLOW

#include <algorithm>
#include <cassert>
#include <queue>
#include <limits>
#include <vector>

namespace suisen {
    template <typename T>
    std::pair<T, std::vector<int>> assignment_problem(const std::vector<std::vector<T>>& a) {
        static constexpr T INF_COST = std::numeric_limits<T>::max() / 2;

        const int n = a.size(), k = 2 * n + 2;
        const int s = 2 * n, t = s + 1;

        struct Edge {
            int to;
            int cap;
            T cost;
            int rev;
        };

        std::vector<std::vector<Edge>> g(k);
        std::vector<T> potential(k);
        std::vector<T> dist(k);
        std::vector<int> prev_vid(k), prev_eid(k);

        std::vector<std::pair<int, int>> edges;

        auto add_edge = [&](int u, int v, int cap, T cost) {
            edges.emplace_back(u, g[u].size());
            g[u].push_back(Edge { v, cap,  cost, int(g[v].size())     });
            g[v].push_back(Edge { u,   0, -cost, int(g[u].size()) - 1 });
        };

        for (int i = 0; i < n; ++i) {
            add_edge(s, i, 1, 0);
            for (int j = 0; j < n; ++j) {
                add_edge(i, n + j, 1, a[i][j]);
            }
            add_edge(n + i, t, 1, 0);
        }

        auto update_dist = [&](int u, int eid) {
            if (dist[u] == INF_COST) return false;
            const auto& e = g[u][eid];
            if (e.cap == 0) return false;
            const int v = e.to;
            T cost = e.cost + potential[u] - potential[v];
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                prev_vid[v] = u;
                prev_eid[v] = eid;
                return true;
            }
            return false;
        };

        auto sssp_dijkstra = [&]() {
            std::vector<int8_t> used(k, false);
            dist.assign(k, INF_COST);
            dist[s] = 0;
            while (true) {
                T min_dist = INF_COST;
                int arg_min = -1;
                for (int i = 0; i < k; ++i) if (not used[i]) {
                    if (dist[i] < min_dist) {
                        min_dist = dist[i];
                        arg_min = i;
                    }
                }
                const int u = arg_min;
                if (u == -1) return;
                for (int i = 0; i < int(g[u].size()); ++i) {
                    const auto& e = g[u][i];
                    if (e.cap == 0) continue;
                    update_dist(u, i);
                }
                used[u] = true;
            }
        };

        auto sssp_dag = [&]() {
            std::vector<int> in(k, 0);
            for (int u = 0; u < k; ++u) {
                for (const auto& e : g[u]) {
                    if (e.cap == 0) continue;
                    ++in[e.to];
                }
            }
            std::deque<int> dq;
            for (int u = 0; u < k; ++u) {
                if (in[u] == 0) dq.push_back(u);
            }
            dist.assign(k, INF_COST);
            dist[s] = 0;
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int i = 0; i < int(g[u].size()); ++i) {
                    const auto& e = g[u][i];
                    if (e.cap == 0) continue;
                    update_dist(u, i);
                    if (--in[e.to] == 0) {
                        dq.push_back(e.to);
                    }
                }
            }
        };

        auto update_potential = [&]() {
            for (int u = 0; u < k; ++u) {
                if (potential[u] != INF_COST) potential[u] += dist[u];
            }
        };

        sssp_dag();
        update_potential();
        T cost = 0;
        while (dist[t] != INF_COST) {
            int df = n;
            for (int v = t; v != s; v = prev_vid[v]) {
                df = std::min(df, g[prev_vid[v]][prev_eid[v]].cap);
            }
            cost += df * potential[t];
            for (int v = t; v != s; v = prev_vid[v]) {
                auto& e = g[prev_vid[v]][prev_eid[v]];
                e.cap -= df;
                g[v][e.rev].cap += df;
            }
            sssp_dijkstra();
            update_potential();
        }

        std::vector<int> assignment(n);

        for (int i = 0; i < n; ++i) {
            for (const Edge &e : g[i]) {
                int j = e.to - n;
                if (j >= n or e.cap == 1) continue;
                assignment[i] = j;
            }
        }

        return { cost, assignment };
    };
} // namespace suisen


#endif // SUISEN_MIN_COST_FLOW
