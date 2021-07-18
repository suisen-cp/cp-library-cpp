---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
    title: test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/tree/euler_tour.hpp\"\n\n\n\n#include <limits>\n\
    #include <vector>\n\nnamespace suisen {\n/**\n * ImplicitGraph g : (int u, auto\
    \ f) -> { for (int v : adjacent(u)) f(v); }\n */\nclass EulerTour {\n    public:\n\
    \        template <typename ImplicitGraph>\n        EulerTour(const ImplicitGraph\
    \ g, int n, int root = 0) : n(n), m(ceil_pow2(2 * n)) {\n            dep.resize(n\
    \ + 1), visit.resize(n), leave.resize(n);\n            seg.assign(2 * m, n);\n\
    \            dfs(g, root);\n            for (int k = m - 1; k > 0; --k) seg[k]\
    \ = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);\n        }\n        template\
    \ <typename Edge, typename EdgeToNode>\n        EulerTour(const std::vector<std::vector<Edge>>\
    \ &g, const EdgeToNode eton, int root = 0) :\n            EulerTour([&](int u,\
    \ auto f) { for (const Edge &e : g[u]) f(eton(e)); }, g.size(), root) {}\n   \
    \     EulerTour(const std::vector<std::vector<int>> &g, int root = 0) :\n    \
    \        EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(),\
    \ root) {}\n        int lca(int u, int v) const {\n            if (visit[u] >\
    \ visit[v]) return lca(v, u);\n            int res = n;\n            for (int\
    \ l = m + visit[u], r = m + visit[v] + 1; l < r; l >>= 1, r >>= 1) {\n       \
    \         if (l & 1) res = argmin(res, seg[l++]);\n                if (r & 1)\
    \ res = argmin(res, seg[--r]);\n            }\n            return res;\n     \
    \   }\n        inline int dist(int u, int v) const { return dep[u] + dep[v] -\
    \ 2 * dep[lca(u, v)]; }\n        inline int depth(int u) const { return dep[u];\
    \ }\n        inline int visit_time(int u) const { return visit[u]; }\n       \
    \ inline int leave_time(int u) const { return leave[u]; }\n        inline int\
    \ parent(int u) const {\n            int p = seg[m + leave[u]];\n            return\
    \ p == n ? -1 : p;\n        }\n    private:\n        const int n, m;\n       \
    \ std::vector<int> visit, leave, dep, seg;\n        template <typename ImplicitGraph>\n\
    \        void dfs(ImplicitGraph g, int root) {\n            dep[root] = 0, dep[n]\
    \ = std::numeric_limits<int>::max();\n            int k = 0;\n            auto\
    \ f = [&](auto self, int u, int p) -> void {\n                visit[u] = k, seg[m\
    \ + k++] = u;\n                g(u, [&](int v){ if (v != p) dep[v] = dep[u] +\
    \ 1, self(self, v, u); });\n                leave[u] = k, seg[m + k++] = p;\n\
    \            };\n            f(f, root, n);\n        }\n        inline int argmin(int\
    \ u, int v) const { return dep[u] < dep[v] ? u : v; }\n        static int ceil_pow2(const\
    \ int n) {\n            int k = 1;\n            while (k < n) k <<= 1;\n     \
    \       return k;\n        }\n};\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_EULER_TOUR\n#define SUISEN_EULER_TOUR\n\n#include <limits>\n\
    #include <vector>\n\nnamespace suisen {\n/**\n * ImplicitGraph g : (int u, auto\
    \ f) -> { for (int v : adjacent(u)) f(v); }\n */\nclass EulerTour {\n    public:\n\
    \        template <typename ImplicitGraph>\n        EulerTour(const ImplicitGraph\
    \ g, int n, int root = 0) : n(n), m(ceil_pow2(2 * n)) {\n            dep.resize(n\
    \ + 1), visit.resize(n), leave.resize(n);\n            seg.assign(2 * m, n);\n\
    \            dfs(g, root);\n            for (int k = m - 1; k > 0; --k) seg[k]\
    \ = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);\n        }\n        template\
    \ <typename Edge, typename EdgeToNode>\n        EulerTour(const std::vector<std::vector<Edge>>\
    \ &g, const EdgeToNode eton, int root = 0) :\n            EulerTour([&](int u,\
    \ auto f) { for (const Edge &e : g[u]) f(eton(e)); }, g.size(), root) {}\n   \
    \     EulerTour(const std::vector<std::vector<int>> &g, int root = 0) :\n    \
    \        EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(),\
    \ root) {}\n        int lca(int u, int v) const {\n            if (visit[u] >\
    \ visit[v]) return lca(v, u);\n            int res = n;\n            for (int\
    \ l = m + visit[u], r = m + visit[v] + 1; l < r; l >>= 1, r >>= 1) {\n       \
    \         if (l & 1) res = argmin(res, seg[l++]);\n                if (r & 1)\
    \ res = argmin(res, seg[--r]);\n            }\n            return res;\n     \
    \   }\n        inline int dist(int u, int v) const { return dep[u] + dep[v] -\
    \ 2 * dep[lca(u, v)]; }\n        inline int depth(int u) const { return dep[u];\
    \ }\n        inline int visit_time(int u) const { return visit[u]; }\n       \
    \ inline int leave_time(int u) const { return leave[u]; }\n        inline int\
    \ parent(int u) const {\n            int p = seg[m + leave[u]];\n            return\
    \ p == n ? -1 : p;\n        }\n    private:\n        const int n, m;\n       \
    \ std::vector<int> visit, leave, dep, seg;\n        template <typename ImplicitGraph>\n\
    \        void dfs(ImplicitGraph g, int root) {\n            dep[root] = 0, dep[n]\
    \ = std::numeric_limits<int>::max();\n            int k = 0;\n            auto\
    \ f = [&](auto self, int u, int p) -> void {\n                visit[u] = k, seg[m\
    \ + k++] = u;\n                g(u, [&](int v){ if (v != p) dep[v] = dep[u] +\
    \ 1, self(self, v, u); });\n                leave[u] = k, seg[m + k++] = p;\n\
    \            };\n            f(f, root, n);\n        }\n        inline int argmin(int\
    \ u, int v) const { return dep[u] < dep[v] ? u : v; }\n        static int ceil_pow2(const\
    \ int n) {\n            int k = 1;\n            while (k < n) k <<= 1;\n     \
    \       return k;\n        }\n};\n} // namespace suisen\n\n#endif // SUISEN_EULER_TOUR"
  dependsOn: []
  isVerificationFile: false
  path: library/tree/euler_tour.hpp
  requiredBy: []
  timestamp: '2021-07-18 15:28:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/generated/tree/euler_tour/lowest_common_ancestor.test.cpp
documentation_of: library/tree/euler_tour.hpp
layout: document
redirect_from:
- /library/library/tree/euler_tour.hpp
- /library/library/tree/euler_tour.hpp.html
title: library/tree/euler_tour.hpp
---
