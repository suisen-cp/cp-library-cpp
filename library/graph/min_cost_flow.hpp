#ifndef SUISEN_MIN_COST_FLOW
#define SUISEN_MIN_COST_FLOW

#include <algorithm>
#include <cassert>
#include <queue>
#include <limits>
#include <vector>

namespace suisen {

enum MCFPotentialInitializer {
    DAG, BELLMAN_FORD, DIJKSTRA
};

template <typename Cap, typename Cost, MCFPotentialInitializer init_method = MCFPotentialInitializer::BELLMAN_FORD>
class MinCostFlow {
    struct InternalEdge { int to; Cap cap; Cost cost; int rev; };
    public:
        MinCostFlow() : MinCostFlow(0) {}
        MinCostFlow(int n) : n(n), g(n), potential(n, 0), dist(n), prev_vid(n), prev_eid(n) {}

        // Returns the id of created edge.
        int add_edge(int u, int v, Cap cap, Cost cost) {
            int edge_id = edges.size();
            edges.emplace_back(u, g[u].size());
            g[u].push_back({ v, cap,  cost, int(g[v].size())     });
            g[v].push_back({ u,   0, -cost, int(g[u].size()) - 1 });
            return edge_id;
        }

        /**
         * Returns { flow, cost } (flow = min(max_flow, f))
         */
        auto min_cost_max_flow(const int s, const int t, const Cap f) {
            return min_cost_max_flow_slope(s, t, f).back();
        }
        /**
         * Returns { flow, cost } (flow = max_flow)
         */
        auto min_cost_max_flow(const int s, const int t) {
            return min_cost_max_flow_slope(s, t).back();
        }
        /**
         * Returns { flow, cost }
         * amount of flow is arbitrary.
         */
        auto min_cost_arbitrary_flow(const int s, const int t) {
            return min_cost_arbitrary_flow_slope(s, t).back();
        }

        auto min_cost_max_flow_slope(const int s, const int t, const Cap f) {
            return min_cost_flow_slope(s, t, f, [](Cap, Cost){ return true; });
        }
        auto min_cost_max_flow_slope(const int s, const int t) {
            return min_cost_max_flow_slope(s, t, INF_FLOW);
        }
        auto min_cost_arbitrary_flow_slope(const int s, const int t) {
            return min_cost_flow_slope(s, t, INF_FLOW, [this, t](Cap, Cost){ return potential[t] < 0; });
        }

        struct Edge {
            int from, to;
            Cap cap, flow;
            Cost cost;
        };

        Edge get_edge(int edge_id) const {
            const auto &e  = g[edges[edge_id].first][edges[edge_id].second];
            const auto &re = g[e.to][e.rev];
            return Edge { re.to, e.to, e.cap + re.cap, re.cap, e.cost };
        }
        std::vector<Edge> get_edges() const {
            std::vector<Edge> res(edges.size());
            for (std::size_t i = 0; i < edges.size(); ++i) res[i] = get_edge(i);
            return res;
        }

    private:
        static constexpr Cost INF_COST = std::numeric_limits<Cost>::max() / 2;
        static constexpr Cost INF_FLOW = std::numeric_limits<Cap>::max() / 2;
    
        int n;
        std::vector<std::vector<InternalEdge>> g;
        std::vector<Cost> potential;
        std::vector<Cost> dist;
        std::vector<int> prev_vid, prev_eid;

        std::vector<std::pair<int, int>> edges;

        template <typename Predicate>
        std::pair<Cap, Cost> min_cost_flow(const int s, const int t, const Cap upper_flow, Predicate pred) {
            return min_cost_flow_slope(s, t, upper_flow, pred).back();
        }

        template <typename Predicate>
        std::vector<std::pair<Cap, Cost>> min_cost_flow_slope(const int s, const int t, const Cap upper_flow, Predicate pred) {
            if constexpr (init_method == BELLMAN_FORD) {
                bellman_ford(s);
            } else if constexpr (init_method == DIJKSTRA) {
                dijkstra(s);
            } else {
                dag_dp(s);
            }
            update_potential();
            std::vector<std::pair<Cap, Cost>> slope;
            Cap flow = 0;
            Cost cost = 0;
            slope.emplace_back(flow, cost);
            while (dist[t] != INF_COST and flow < upper_flow and pred(flow, cost)) {
                Cap df = upper_flow - flow;
                for (int v = t; v != s; v = prev_vid[v]) {
                    df = std::min(df, g[prev_vid[v]][prev_eid[v]].cap);
                }
                assert(df != 0);
                flow += df;
                cost += df * potential[t];
                if (slope.size() >= 2) {
                    auto [f0, c0] = *std::next(slope.rbegin());
                    auto [f1, c1] = *slope.rbegin();
                    if ((f1 - f0) * (cost - c1) == (flow - f1) * (c1 - c0)) slope.pop_back();
                }
                slope.emplace_back(flow, cost);
                for (int v = t; v != s; v = prev_vid[v]) {
                    auto &e = g[prev_vid[v]][prev_eid[v]];
                    e.cap -= df;
                    g[v][e.rev].cap += df;
                }
                dijkstra(s);
                update_potential();
            }
            return slope;
        }

        void update_potential() {
            for (int u = 0; u < n; ++u) {
                if (potential[u] != INF_COST) potential[u] += dist[u];
            }
        }

        bool update_dist(int u, int eid) {
            if (dist[u] == INF_COST) return false;
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
            dist.assign(n, INF_COST);
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
            dist.assign(n, INF_COST);
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
            dist.assign(n, INF_COST);
            dist[s] = 0;
            for (bool has_update = true; has_update;) {
                has_update = false;
                for (int u = 0; u < n; ++u) {
                    if (dist[u] == INF_COST) continue;
                    for (int i = 0; i < int(g[u].size()); ++i) {
                        has_update |= update_dist(u, i);
                    }
                }
            }
        }
};
} // namespace suisen


#endif // SUISEN_MIN_COST_FLOW
