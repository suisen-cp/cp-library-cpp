---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/graph/min_cost_flow.hpp
    title: library/graph/min_cost_flow.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/practice2/tasks/practice2_e
    links:
    - https://atcoder.jp/contests/practice2/tasks/practice2_e
  bundledCode: "#line 1 \"test/src/graph/min_cost_flow/practice2_e.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/practice2/tasks/practice2_e\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/min_cost_flow.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <limits>\n#include <vector>\n\n\
    namespace suisen {\n\nenum MinCostFlowInitializeMethod {\n    DAG, BELLMAN_FORD,\
    \ DIJKSTRA\n};\n\ntemplate <typename Cap, typename Cost, MinCostFlowInitializeMethod\
    \ init_method = MinCostFlowInitializeMethod::BELLMAN_FORD>\nclass MinCostFlow\
    \ {\n    struct InternalEdge { int to; Cap cap; Cost cost; int rev; };\n    public:\n\
    \        MinCostFlow() : MinCostFlow(0) {}\n        MinCostFlow(int n) : n(n),\
    \ g(n), potential(n, 0), dist(n), prev_vid(n), prev_eid(n) {}\n\n        // Returns\
    \ the id of created edge.\n        int add_edge(int u, int v, Cap cap, Cost cost)\
    \ {\n            int edge_id = edges.size();\n            edges.emplace_back(u,\
    \ g[u].size());\n            g[u].push_back({ v, cap,  cost, int(g[v].size())\
    \     });\n            g[v].push_back({ u,   0, -cost, int(g[u].size()) - 1 });\n\
    \            return edge_id;\n        }\n\n        /**\n         * Returns { flow,\
    \ cost } (flow = min(max_flow, f))\n         */\n        auto min_cost_max_flow(const\
    \ int s, const int t, const Cap f) {\n            return min_cost_max_flow_slope(s,\
    \ t, f).back();\n        }\n        /**\n         * Returns { flow, cost } (flow\
    \ = max_flow)\n         */\n        auto min_cost_max_flow(const int s, const\
    \ int t) {\n            return min_cost_max_flow_slope(s, t).back();\n       \
    \ }\n        /**\n         * Returns { flow, cost }\n         * amount of flow\
    \ is arbitrary.\n         */\n        auto min_cost_arbitrary_flow(const int s,\
    \ const int t) {\n            return min_cost_arbitrary_flow_slope(s, t).back();\n\
    \        }\n\n        auto min_cost_max_flow_slope(const int s, const int t, const\
    \ Cap f) {\n            return min_cost_flow_slope(s, t, f, [](Cap, Cost){ return\
    \ true; });\n        }\n        auto min_cost_max_flow_slope(const int s, const\
    \ int t) {\n            return min_cost_flow_slope(s, t, INF_FLOW);\n        }\n\
    \        auto min_cost_arbitrary_flow_slope(const int s, const int t) {\n    \
    \        return min_cost_flow_slope(s, t, INF_FLOW, [this, t](Cap, Cost){ return\
    \ potential[t] < 0; });\n        }\n\n        struct Edge {\n            int from,\
    \ to;\n            Cap cap, flow;\n            Cost cost;\n        };\n\n    \
    \    Edge get_edge(int edge_id) const {\n            const auto &e  = g[edges[edge_id].first][edges[edge_id].second];\n\
    \            const auto &re = g[e.to][e.rev];\n            return Edge { re.to,\
    \ e.to, e.cap + re.cap, re.cap, e.cost };\n        }\n        std::vector<Edge>\
    \ get_edges() const {\n            std::vector<Edge> res(edges.size());\n    \
    \        for (std::size_t i = 0; i < edges.size(); ++i) res[i] = get_edge(i);\n\
    \            return res;\n        }\n\n    private:\n        static constexpr\
    \ Cost INF_COST = std::numeric_limits<Cost>::max();\n        static constexpr\
    \ Cost INF_FLOW = std::numeric_limits<Cap>::max();\n    \n        int n;\n   \
    \     std::vector<std::vector<InternalEdge>> g;\n        std::vector<Cost> potential;\n\
    \        std::vector<Cost> dist;\n        std::vector<int> prev_vid, prev_eid;\n\
    \n        std::vector<std::pair<int, int>> edges;\n\n        template <typename\
    \ Predicate>\n        std::pair<Cap, Cost> min_cost_flow(const int s, const int\
    \ t, const Cap upper_flow, Predicate pred) {\n            return min_cost_flow_slope(s,\
    \ t, upper_flow, pred).back();\n        }\n\n        template <typename Predicate>\n\
    \        std::vector<std::pair<Cap, Cost>> min_cost_flow_slope(const int s, const\
    \ int t, const Cap upper_flow, Predicate pred) {\n            switch (init_method)\
    \ {\n                case BELLMAN_FORD: bellman_ford(s); break;\n            \
    \    case DIJKSTRA:     dijkstra(s);     break;\n                case DAG:   \
    \       dag_dp(s);       break;\n            }\n            update_potential();\n\
    \            std::vector<std::pair<Cap, Cost>> slope;\n            Cap flow =\
    \ 0;\n            Cost cost = 0;\n            slope.emplace_back(flow, cost);\n\
    \            while (dist[t] != INF_COST and flow < upper_flow and pred(flow, cost))\
    \ {\n                Cap df = upper_flow - flow;\n                for (int v =\
    \ t; v != s; v = prev_vid[v]) {\n                    df = std::min(df, g[prev_vid[v]][prev_eid[v]].cap);\n\
    \                }\n                assert(df != 0);\n                flow +=\
    \ df;\n                cost += df * potential[t];\n                if (slope.size()\
    \ >= 2) {\n                    auto [f0, c0] = *std::next(slope.rbegin());\n \
    \                   auto [f1, c1] = *slope.rbegin();\n                    if ((f1\
    \ - f0) * (cost - c1) == (flow - f1) * (c1 - c0)) slope.pop_back();\n        \
    \        }\n                slope.emplace_back(flow, cost);\n                for\
    \ (int v = t; v != s; v = prev_vid[v]) {\n                    auto &e = g[prev_vid[v]][prev_eid[v]];\n\
    \                    e.cap -= df;\n                    g[v][e.rev].cap += df;\n\
    \                }\n                dijkstra(s);\n                update_potential();\n\
    \            }\n            return slope;\n        }\n\n        void update_potential()\
    \ {\n            for (int u = 0; u < n; ++u) {\n                if (potential[u]\
    \ != INF_COST) potential[u] += dist[u];\n            }\n        }\n\n        bool\
    \ update_dist(int u, int eid) {\n            if (dist[u] == INF_COST) return false;\n\
    \            const auto &e = g[u][eid];\n            if (e.cap == 0) return false;\n\
    \            const int v = e.to;\n            Cost cost = e.cost + potential[u]\
    \ - potential[v];\n            if constexpr (init_method == DIJKSTRA) {\n    \
    \            assert(cost >= 0);\n            }\n            if (dist[u] + cost\
    \ < dist[v]) {\n                dist[v] = dist[u] + cost;\n                prev_vid[v]\
    \ = u;\n                prev_eid[v] = eid;\n                return true;\n   \
    \         }\n            return false;\n        }\n\n        void dijkstra(int\
    \ s) {\n            using State = std::pair<Cost, int>;\n            std::priority_queue<State,\
    \ std::vector<State>, std::greater<State>> pq;\n            dist.assign(n, INF_COST);\n\
    \            pq.emplace(dist[s] = 0, s);\n            while (pq.size()) {\n  \
    \              auto [du, u] = pq.top();\n                pq.pop();\n         \
    \       if (du != dist[u]) continue;\n                for (int i = 0; i < int(g[u].size());\
    \ ++i) {\n                    int v = g[u][i].to;\n                    if (update_dist(u,\
    \ i)) {\n                        pq.emplace(dist[v], v);\n                   \
    \ }\n                }\n            }\n        }\n\n        void dag_dp(int s)\
    \ {\n            std::vector<int> in(n, 0);\n            for (int u = 0; u < n;\
    \ ++u) {\n                for (const auto &e : g[u]) {\n                    if\
    \ (e.cap == 0) continue;\n                    ++in[e.to];\n                }\n\
    \            }\n            std::deque<int> dq;\n            for (int u = 0; u\
    \ < n; ++u) {\n                if (in[u] == 0) dq.push_back(u);\n            }\n\
    \            dist.assign(n, INF_COST);\n            dist[s] = 0;\n           \
    \ while (dq.size()) {\n                int u = dq.front();\n                dq.pop_front();\n\
    \                for (int i = 0; i < int(g[u].size()); ++i) {\n              \
    \      const auto &e = g[u][i];\n                    if (e.cap == 0) continue;\n\
    \                    update_dist(u, i);\n                    if (--in[e.to] ==\
    \ 0) {\n                        dq.push_back(e.to);\n                    }\n \
    \               }\n            }\n            assert(std::all_of(in.begin(), in.end(),\
    \ [](int in_deg) { return in_deg == 0; }));\n        }\n\n        void bellman_ford(int\
    \ s) {\n            dist.assign(n, INF_COST);\n            dist[s] = 0;\n    \
    \        for (bool has_update = true; has_update;) {\n                has_update\
    \ = false;\n                for (int u = 0; u < n; ++u) {\n                  \
    \  if (dist[u] == INF_COST) continue;\n                    for (int i = 0; i <\
    \ int(g[u].size()); ++i) {\n                        has_update |= update_dist(u,\
    \ i);\n                    }\n                }\n            }\n        }\n};\n\
    } // namespace suisen\n\n\n\n#line 6 \"test/src/graph/min_cost_flow/practice2_e.test.cpp\"\
    \nusing namespace suisen;\n\nconstexpr long long INF = 1LL << 50;\n\nint main()\
    \ {\n    int n, k;\n    std::cin >> n >> k;\n    std::vector a(n, std::vector(n,\
    \ 0LL));\n    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {\n    \
    \    std::cin >> a[i][j];\n    }\n    MinCostFlow<int, long long, DIJKSTRA> mcf(n\
    \ + n + 2);\n    int src = n + n, dst = src + 1;\n\n    mcf.add_edge(src, dst,\
    \ n * k, INF);\n    for (int i = 0; i < n; ++i) {\n        mcf.add_edge(src, i,\
    \ k, 0);\n        mcf.add_edge(i + n, dst, k, 0);\n    }\n    for (int i = 0;\
    \ i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n            mcf.add_edge(i,\
    \ j + n, 1, INF - a[i][j]);\n        }\n    }\n\n    auto [flow, cost] = mcf.min_cost_max_flow(src,\
    \ dst, n * k);\n    long long ans = INF * flow - cost;\n    std::vector g(n, std::string(n,\
    \ '.'));\n    for (auto e : mcf.get_edges()) {\n        if (e.flow == 1 and e.from\
    \ != src and e.to != dst) {\n            g[e.from][e.to - n] = 'X';\n        }\n\
    \    }\n\n    std::cout << ans << '\\n';\n    for (const auto &row : g) {\n  \
    \      std::cout << row << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/practice2/tasks/practice2_e\"\
    \n\n#include <iostream>\n\n#include \"library/graph/min_cost_flow.hpp\"\nusing\
    \ namespace suisen;\n\nconstexpr long long INF = 1LL << 50;\n\nint main() {\n\
    \    int n, k;\n    std::cin >> n >> k;\n    std::vector a(n, std::vector(n, 0LL));\n\
    \    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {\n        std::cin\
    \ >> a[i][j];\n    }\n    MinCostFlow<int, long long, DIJKSTRA> mcf(n + n + 2);\n\
    \    int src = n + n, dst = src + 1;\n\n    mcf.add_edge(src, dst, n * k, INF);\n\
    \    for (int i = 0; i < n; ++i) {\n        mcf.add_edge(src, i, k, 0);\n    \
    \    mcf.add_edge(i + n, dst, k, 0);\n    }\n    for (int i = 0; i < n; ++i) {\n\
    \        for (int j = 0; j < n; ++j) {\n            mcf.add_edge(i, j + n, 1,\
    \ INF - a[i][j]);\n        }\n    }\n\n    auto [flow, cost] = mcf.min_cost_max_flow(src,\
    \ dst, n * k);\n    long long ans = INF * flow - cost;\n    std::vector g(n, std::string(n,\
    \ '.'));\n    for (auto e : mcf.get_edges()) {\n        if (e.flow == 1 and e.from\
    \ != src and e.to != dst) {\n            g[e.from][e.to - n] = 'X';\n        }\n\
    \    }\n\n    std::cout << ans << '\\n';\n    for (const auto &row : g) {\n  \
    \      std::cout << row << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/graph/min_cost_flow.hpp
  isVerificationFile: true
  path: test/src/graph/min_cost_flow/practice2_e.test.cpp
  requiredBy: []
  timestamp: '2021-08-16 00:10:02+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/graph/min_cost_flow/practice2_e.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/min_cost_flow/practice2_e.test.cpp
- /verify/test/src/graph/min_cost_flow/practice2_e.test.cpp.html
title: test/src/graph/min_cost_flow/practice2_e.test.cpp
---
