---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/graph/assignment_problem.hpp
    title: library/graph/assignment_problem.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/assignment
    links:
    - https://judge.yosupo.jp/problem/assignment
  bundledCode: "#line 1 \"test/src/graph/assignment_problem/assignment.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#include <iostream>\n\
    \n#line 1 \"library/graph/assignment_problem.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <limits>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T>\n    std::pair<T, std::vector<int>>\
    \ assignment_problem(const std::vector<std::vector<T>>& a) {\n        static constexpr\
    \ T INF_COST = std::numeric_limits<T>::max() / 2;\n\n        const int n = a.size(),\
    \ k = 2 * n + 2;\n        const int s = 2 * n, t = s + 1;\n\n        struct Edge\
    \ {\n            int to;\n            int cap;\n            T cost;\n        \
    \    int rev;\n        };\n\n        std::vector<std::vector<Edge>> g(k);\n  \
    \      std::vector<T> potential(k);\n        std::vector<T> dist(k);\n       \
    \ std::vector<int> prev_vid(k), prev_eid(k);\n\n        std::vector<std::pair<int,\
    \ int>> edges;\n\n        auto add_edge = [&](int u, int v, int cap, T cost) {\n\
    \            edges.emplace_back(u, g[u].size());\n            g[u].push_back(Edge\
    \ { v, cap,  cost, int(g[v].size())     });\n            g[v].push_back(Edge {\
    \ u,   0, -cost, int(g[u].size()) - 1 });\n        };\n\n        for (int i =\
    \ 0; i < n; ++i) {\n            add_edge(s, i, 1, 0);\n            for (int j\
    \ = 0; j < n; ++j) {\n                add_edge(i, n + j, 1, a[i][j]);\n      \
    \      }\n            add_edge(n + i, t, 1, 0);\n        }\n\n        auto update_dist\
    \ = [&](int u, int eid) {\n            if (dist[u] == INF_COST) return false;\n\
    \            const auto& e = g[u][eid];\n            if (e.cap == 0) return false;\n\
    \            const int v = e.to;\n            T cost = e.cost + potential[u] -\
    \ potential[v];\n            if (dist[u] + cost < dist[v]) {\n               \
    \ dist[v] = dist[u] + cost;\n                prev_vid[v] = u;\n              \
    \  prev_eid[v] = eid;\n                return true;\n            }\n         \
    \   return false;\n        };\n\n        auto sssp_dijkstra = [&]() {\n      \
    \      std::vector<int8_t> used(k, false);\n            dist.assign(k, INF_COST);\n\
    \            dist[s] = 0;\n            while (true) {\n                T min_dist\
    \ = INF_COST;\n                int arg_min = -1;\n                for (int i =\
    \ 0; i < k; ++i) if (not used[i]) {\n                    if (dist[i] < min_dist)\
    \ {\n                        min_dist = dist[i];\n                        arg_min\
    \ = i;\n                    }\n                }\n                const int u\
    \ = arg_min;\n                if (u == -1) return;\n                for (int i\
    \ = 0; i < int(g[u].size()); ++i) {\n                    const auto& e = g[u][i];\n\
    \                    if (e.cap == 0) continue;\n                    update_dist(u,\
    \ i);\n                }\n                used[u] = true;\n            }\n   \
    \     };\n\n        auto sssp_dag = [&]() {\n            std::vector<int> in(k,\
    \ 0);\n            for (int u = 0; u < k; ++u) {\n                for (const auto&\
    \ e : g[u]) {\n                    if (e.cap == 0) continue;\n               \
    \     ++in[e.to];\n                }\n            }\n            std::deque<int>\
    \ dq;\n            for (int u = 0; u < k; ++u) {\n                if (in[u] ==\
    \ 0) dq.push_back(u);\n            }\n            dist.assign(k, INF_COST);\n\
    \            dist[s] = 0;\n            while (dq.size()) {\n                int\
    \ u = dq.front();\n                dq.pop_front();\n                for (int i\
    \ = 0; i < int(g[u].size()); ++i) {\n                    const auto& e = g[u][i];\n\
    \                    if (e.cap == 0) continue;\n                    update_dist(u,\
    \ i);\n                    if (--in[e.to] == 0) {\n                        dq.push_back(e.to);\n\
    \                    }\n                }\n            }\n        };\n\n     \
    \   auto update_potential = [&]() {\n            for (int u = 0; u < k; ++u) {\n\
    \                if (potential[u] != INF_COST) potential[u] += dist[u];\n    \
    \        }\n        };\n\n        sssp_dag();\n        update_potential();\n \
    \       T cost = 0;\n        while (dist[t] != INF_COST) {\n            int df\
    \ = n;\n            for (int v = t; v != s; v = prev_vid[v]) {\n             \
    \   df = std::min(df, g[prev_vid[v]][prev_eid[v]].cap);\n            }\n     \
    \       cost += df * potential[t];\n            for (int v = t; v != s; v = prev_vid[v])\
    \ {\n                auto& e = g[prev_vid[v]][prev_eid[v]];\n                e.cap\
    \ -= df;\n                g[v][e.rev].cap += df;\n            }\n            sssp_dijkstra();\n\
    \            update_potential();\n        }\n\n        std::vector<int> assignment(n);\n\
    \n        for (int i = 0; i < n; ++i) {\n            for (const Edge &e : g[i])\
    \ {\n                int j = e.to - n;\n                if (j >= n or e.cap ==\
    \ 1) continue;\n                assignment[i] = j;\n            }\n        }\n\
    \n        return { cost, assignment };\n    };\n} // namespace suisen\n\n\n\n\
    #line 6 \"test/src/graph/assignment_problem/assignment.test.cpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n\n    std::vector a(n, std::vector<long long>(n));\n\
    \    for (auto &row : a) for (auto &e : row) std::cin >> e;\n\n    auto [cost,\
    \ assignment] = suisen::assignment_problem(a);\n    std::cout << cost << '\\n';\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cout << assignment[i] << \" \\\
    n\"[i == n - 1];\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#include\
    \ <iostream>\n\n#include \"library/graph/assignment_problem.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n\n    std::vector a(n, std::vector<long long>(n));\n\
    \    for (auto &row : a) for (auto &e : row) std::cin >> e;\n\n    auto [cost,\
    \ assignment] = suisen::assignment_problem(a);\n    std::cout << cost << '\\n';\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cout << assignment[i] << \" \\\
    n\"[i == n - 1];\n    }\n}"
  dependsOn:
  - library/graph/assignment_problem.hpp
  isVerificationFile: true
  path: test/src/graph/assignment_problem/assignment.test.cpp
  requiredBy: []
  timestamp: '2023-01-02 17:33:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/assignment_problem/assignment.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/assignment_problem/assignment.test.cpp
- /verify/test/src/graph/assignment_problem/assignment.test.cpp.html
title: test/src/graph/assignment_problem/assignment.test.cpp
---
