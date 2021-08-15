#ifndef SUISEN_MIN_COST_FLOW
#define SUISEN_MIN_COST_FLOW

#include <cassert>
#include <limits>
#include <vector>

namespace suisen {

enum MinCostFlowInitializeMethod {
    DAG, BELLMAN_FORD, DIJKSTRA
};

template <typename Cap, typename Cost, MinCostFlowInitializeMethod init_method = MinCostFlowInitializeMethod::BELLMAN_FORD>
class MinCostFlow {
    struct Edge { int to; Cap cap; Cost cost; int rev; };
    public:
        MinCostFlow() : MinCostFlow(0) {}
        MinCostFlow(int n) : n(n), g(n), potential(n, 0), dist(n), prev_vid(n), prev_eid(n) {}

        void add_edge(int u, int v, Cap cap, Cost cost) {
            g[u].push_back({ v, cap,  cost, int(g[v].size())     });
            g[v].push_back({ u,   0, -cost, int(g[u].size()) - 1 });
        }

        std::pair<Cap, Cost> min_cost_max_flow(const int s, const int t, const Cap f) {
            return min_cost_flow(s, t, [this, f](Cap flow, Cost){ return flow < f; });
        }
        std::pair<Cap, Cost> min_cost_max_flow(const int s, const int t) {
            return min_cost_max_flow(s, t, std::numeric_limits<Cap>::max());
        }
        // amount of flow is arbitrary.
        std::pair<Cap, Cost> min_cost_flow(const int s, const int t) {
            return min_cost_flow(s, t, [this, t](Cap, Cost){ return potential[t] < 0; });
        }
    private:
        static constexpr Cost INF = std::numeric_limits<Cost>::max();
    
        int n;
        std::vector<std::vector<Edge>> g;
        std::vector<Cost> potential;
        std::vector<Cost> dist;
        std::vector<int> prev_vid, prev_eid;

        template <typename Predicate>
        std::pair<Cap, Cost> min_cost_flow(const int s, const int t, Predicate pred) {
            switch (init_method) {
                case BELLMAN_FORD: bellman_ford(s); break;
                case DIJKSTRA:     dijkstra(s);     break;
                case DAG:          dag_dp(s);       break;
            }
            update_potential();
            Cap flow = 0;
            Cost cost = 0;
            while (dist[t] != INF and pred(flow, cost)) {
                Cap df = std::numeric_limits<Cap>::max();
                for (int v = t; v != s; v = prev_vid[v]) {
                    df = std::min(df, g[prev_vid[v]][prev_eid[v]].cap);
                }
                assert(df != 0);
                flow += df;
                cost += df * potential[t];
                for (int v = t; v != s; v = prev_vid[v]) {
                    auto &e = g[prev_vid[v]][prev_eid[v]];
                    e.cap -= df;
                    g[v][e.rev].cap += df;
                }
                dijkstra(s);
                update_potential();
            }
            return { flow, cost };
        }

        void update_potential() {
            for (int u = 0; u < n; ++u) {
                if (potential[u] != INF) potential[u] += dist[u];
            }
        }

        bool update_dist(int u, int eid) {
            if (dist[u] == INF) return false;
            const auto &e = g[u][eid];
            if (e.cap == 0) return false;
            const int v = e.to;
            Cost cost = e.cost + potential[u] - potential[v];
            if constexpr (init_method == DIJKSTRA) {
                assert(cost >= 0);
            }
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                prev_vid[v] = u;
                prev_eid[v] = eid;
                return true;
            }
            return false;
        }

        void dijkstra(int s) {
            using State = std::pair<Cost, int>;
            std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
            dist.assign(n, INF);
            pq.emplace(dist[s] = 0, s);
            while (pq.size()) {
                auto [du, u] = pq.top();
                pq.pop();
                if (du != dist[u]) continue;
                for (int i = 0; i < int(g[u].size()); ++i) {
                    int v = g[u][i].to;
                    if (update_dist(u, i)) {
                        pq.emplace(dist[v], v);
                    }
                }
            }
        }

        void dag_dp(int s) {
            std::vector<int> in(n, 0);
            for (int u = 0; u < n; ++u) {
                for (const auto &e : g[u]) {
                    if (e.cap == 0) continue;
                    ++in[e.to];
                }
            }
            std::deque<int> dq;
            for (int u = 0; u < n; ++u) {
                if (in[u] == 0) dq.push_back(u);
            }
            dist.assign(n, INF);
            dist[s] = 0;
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                for (int i = 0; i < int(g[u].size()); ++i) {
                    const auto &e = g[u][i];
                    if (e.cap == 0) continue;
                    update_dist(u, i);
                    if (--in[e.to] == 0) {
                        dq.push_back(e.to);
                    }
                }
            }
            assert(std::all_of(in.begin(), in.end(), [](int in_deg) { return in_deg == 0; }));
        }

        void bellman_ford(int s) {
            dist.assign(n, INF);
            dist[s] = 0;
            for (bool has_update = true; has_update;) {
                has_update = false;
                for (int u = 0; u < n; ++u) {
                    if (dist[u] == INF) continue;
                    for (int i = 0; i < int(g[u].size()); ++i) {
                        has_update |= update_dist(u, i);
                    }
                }
            }
        }
};
} // namespace suisen


#endif // SUISEN_MIN_COST_FLOW
