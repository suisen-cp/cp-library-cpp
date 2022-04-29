---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/graph/functional_graph/dummy.test.cpp
    title: test/src/graph/functional_graph/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.hatenablog.com/entry/2019/09/22/114149
  bundledCode: "#line 1 \"library/graph/functional_graph.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\nnamespace suisen {\n    struct FunctionalGraph\
    \ {\n        struct Doubling;\n        template <typename T, T(*)(T, T), T(*)()>\n\
    \        struct DoublingSum;\n        friend struct Doubling;\n        template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n        friend struct DoublingSum;\n\n\
    \        FunctionalGraph() : FunctionalGraph(0) {}\n        FunctionalGraph(int\
    \ n) : _n(n), _nxt(n) {}\n        FunctionalGraph(const std::vector<int>& nxt)\
    \ : _n(nxt.size()), _nxt(nxt) {}\n\n        const int& operator[](int u) const\
    \ {\n            return _nxt[u];\n        }\n        int& operator[](int u) {\n\
    \            return _nxt[u];\n        }\n\n        struct Doubling {\n       \
    \     friend struct FunctionalGraph;\n\n            int query(int u, long long\
    \ d) {\n                for (int l = _log; l >= 0; --l) if ((d >> l) & 1) u =\
    \ _nxt[l][u];\n                return u;\n            }\n\n        private:\n\
    \            int _n, _log;\n            std::vector<std::vector<int>> _nxt;\n\n\
    \            Doubling(const std::vector<int>& nxt, long long max_step) : _n(nxt.size()),\
    \ _log(floor_log2(max_step)), _nxt(_log + 1, std::vector<int>(_n)) {\n       \
    \         _nxt[0] = nxt;\n                for (int i = 1; i <= _log; ++i) for\
    \ (int j = 0; j < _n; ++j) {\n                    _nxt[i][j] = _nxt[i - 1][_nxt[i\
    \ - 1][j]];\n                }\n            }\n        };\n\n        template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n        struct DoublingSum : private Doubling\
    \ {\n            friend struct FunctionalGraph;\n\n            struct Result {\n\
    \                int v;\n                T sum;\n                operator std::pair<int,\
    \ T>() { return std::pair<int, T>{ v, sum }; }\n            };\n\n           \
    \ Result query(int u, long long d) {\n                T sum = e();\n         \
    \       for (int l = _log; l >= 0; --l) if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u,\
    \ _nxt[l][u])]);\n                return Result{ u, sum };\n            }\n\n\
    \        private:\n            std::vector<std::vector<T>> _dat;\n\n         \
    \   DoublingSum(const std::vector<int>& nxt, long long max_step, const std::vector<T>&\
    \ dat) : Doubling(nxt, max_step), _dat(_log + 1, std::vector<T>(_n, e())) {\n\
    \                _dat[0] = dat;\n                for (int i = 1; i <= _log; ++i)\
    \ for (int j = 0; j < _n; ++j) {\n                    _dat[i][j] = op(_dat[i -\
    \ 1][j], _dat[i - 1][_nxt[i - 1][j]]);\n                }\n            }\n   \
    \     };\n\n        Doubling doubling(long long max_step) const {\n          \
    \  return Doubling(_nxt, max_step);\n        }\n\n        template <typename T,\
    \ T(*op)(T, T), T(*e)()>\n        DoublingSum<T, op, e> doubling(long long max_step,\
    \ std::vector<T>& dat) const {\n            return DoublingSum<T, op, e>(_nxt,\
    \ max_step, dat);\n        }\n\n        struct InfinitePath {\n            int\
    \ head_v;\n            int head_len;\n            int loop_v;\n            int\
    \ loop_len;\n            InfinitePath() = default;\n            InfinitePath(int\
    \ head_v, int head_len, int loop_v, int loop_len) : head_v(head_v), head_len(head_len),\
    \ loop_v(loop_v), loop_len(loop_len) {}\n        };\n\n        std::vector<InfinitePath>\
    \ infinite_paths() const {\n            std::vector<InfinitePath> res(_n);\n\n\
    \            std::vector<int> vis(_n, _n);\n            std::vector<int> dep(_n,\
    \ 0);\n\n            int time = 0;\n            auto dfs = [&](auto dfs, int u)\
    \ -> int {\n                vis[u] = time;\n                int v = _nxt[u];\n\
    \                if (vis[v] == vis[u]) { // found cycle\n                    int\
    \ loop_len = dep[u] - dep[v] + 1;\n                    res[u] = { u, 0, u, loop_len\
    \ };\n                    return loop_len - 1;\n                } else if (vis[v]\
    \ < vis[u]) {\n                    res[u] = { u, res[v].head_len + 1, res[v].loop_v,\
    \ res[v].loop_len };\n                    return 0;\n                } else {\n\
    \                    dep[v] = dep[u] + 1;\n                    int c = dfs(dfs,\
    \ v);\n                    if (c > 0) { // in cycle\n                        res[u]\
    \ = { u, 0, u, res[v].loop_len };\n                        return c - 1;\n   \
    \                 } else { // out of cycle\n                        res[u] = {\
    \ u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };\n                \
    \        return 0;\n                    }\n                }\n            };\n\
    \            for (int i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);\n\
    \            return res;\n        }\n\n        /**\n         * Calculates k'th\
    \ iterate: f(f(f(...f(i)))) for all 0 <= i < N in O(N) time.\n         * Reference:\
    \ https://noshi91.hatenablog.com/entry/2019/09/22/114149\n         */\n      \
    \  std::vector<int> kth_iterate(const long long k) {\n            assert(k >=\
    \ 0);\n            std::vector<int> res(_n);\n            std::vector<int> forest_roots;\n\
    \            std::vector<std::vector<int>> forest(_n);\n            std::vector<std::vector<std::pair<long\
    \ long, int>>> qs(_n);\n            for (const auto& path : infinite_paths())\
    \ {\n                const int v = path.head_v;\n                (path.head_len\
    \ == 0 ? forest_roots : forest[_nxt[v]]).push_back(v);\n                if (path.head_len\
    \ >= k) continue;\n                qs[path.loop_v].emplace_back(k - path.head_len,\
    \ v);\n            }\n            std::vector<int> dfs_path(_n);\n           \
    \ auto dfs = [&](auto dfs, int u, int d) -> void {\n                dfs_path[d]\
    \ = u;\n                if (d >= k) res[u] = dfs_path[d - k];\n              \
    \  for (int v : forest[u]) dfs(dfs, v, d + 1);\n            };\n            for\
    \ (int root : forest_roots) dfs(dfs, root, 0);\n            std::vector<int8_t>\
    \ seen(_n, false);\n            for (int root : forest_roots) {\n            \
    \    if (seen[root]) continue;\n                std::vector<int> cycle{ root };\n\
    \                for (int v = _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);\n\
    \                const int len = cycle.size();\n                for (int i = 0;\
    \ i < len; ++i) {\n                    const int s = cycle[i];\n             \
    \       seen[s] = true;\n                    for (const auto& [rem, res_index]\
    \ : qs[s]) {\n                        res[res_index] = cycle[(i + rem) % len];\n\
    \                    }\n                }\n            }\n            return res;\n\
    \        }\n\n    private:\n        int _n;\n        std::vector<int> _nxt;\n\n\
    \        static int floor_log2(long long v) {\n            int l = 0;\n      \
    \      while (1LL << (l + 1) <= v) ++l;\n            return l;\n        }\n  \
    \  };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_DOUBLING\n#define SUISEN_DOUBLING\n\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\nnamespace suisen {\n    struct FunctionalGraph\
    \ {\n        struct Doubling;\n        template <typename T, T(*)(T, T), T(*)()>\n\
    \        struct DoublingSum;\n        friend struct Doubling;\n        template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n        friend struct DoublingSum;\n\n\
    \        FunctionalGraph() : FunctionalGraph(0) {}\n        FunctionalGraph(int\
    \ n) : _n(n), _nxt(n) {}\n        FunctionalGraph(const std::vector<int>& nxt)\
    \ : _n(nxt.size()), _nxt(nxt) {}\n\n        const int& operator[](int u) const\
    \ {\n            return _nxt[u];\n        }\n        int& operator[](int u) {\n\
    \            return _nxt[u];\n        }\n\n        struct Doubling {\n       \
    \     friend struct FunctionalGraph;\n\n            int query(int u, long long\
    \ d) {\n                for (int l = _log; l >= 0; --l) if ((d >> l) & 1) u =\
    \ _nxt[l][u];\n                return u;\n            }\n\n        private:\n\
    \            int _n, _log;\n            std::vector<std::vector<int>> _nxt;\n\n\
    \            Doubling(const std::vector<int>& nxt, long long max_step) : _n(nxt.size()),\
    \ _log(floor_log2(max_step)), _nxt(_log + 1, std::vector<int>(_n)) {\n       \
    \         _nxt[0] = nxt;\n                for (int i = 1; i <= _log; ++i) for\
    \ (int j = 0; j < _n; ++j) {\n                    _nxt[i][j] = _nxt[i - 1][_nxt[i\
    \ - 1][j]];\n                }\n            }\n        };\n\n        template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n        struct DoublingSum : private Doubling\
    \ {\n            friend struct FunctionalGraph;\n\n            struct Result {\n\
    \                int v;\n                T sum;\n                operator std::pair<int,\
    \ T>() { return std::pair<int, T>{ v, sum }; }\n            };\n\n           \
    \ Result query(int u, long long d) {\n                T sum = e();\n         \
    \       for (int l = _log; l >= 0; --l) if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u,\
    \ _nxt[l][u])]);\n                return Result{ u, sum };\n            }\n\n\
    \        private:\n            std::vector<std::vector<T>> _dat;\n\n         \
    \   DoublingSum(const std::vector<int>& nxt, long long max_step, const std::vector<T>&\
    \ dat) : Doubling(nxt, max_step), _dat(_log + 1, std::vector<T>(_n, e())) {\n\
    \                _dat[0] = dat;\n                for (int i = 1; i <= _log; ++i)\
    \ for (int j = 0; j < _n; ++j) {\n                    _dat[i][j] = op(_dat[i -\
    \ 1][j], _dat[i - 1][_nxt[i - 1][j]]);\n                }\n            }\n   \
    \     };\n\n        Doubling doubling(long long max_step) const {\n          \
    \  return Doubling(_nxt, max_step);\n        }\n\n        template <typename T,\
    \ T(*op)(T, T), T(*e)()>\n        DoublingSum<T, op, e> doubling(long long max_step,\
    \ std::vector<T>& dat) const {\n            return DoublingSum<T, op, e>(_nxt,\
    \ max_step, dat);\n        }\n\n        struct InfinitePath {\n            int\
    \ head_v;\n            int head_len;\n            int loop_v;\n            int\
    \ loop_len;\n            InfinitePath() = default;\n            InfinitePath(int\
    \ head_v, int head_len, int loop_v, int loop_len) : head_v(head_v), head_len(head_len),\
    \ loop_v(loop_v), loop_len(loop_len) {}\n        };\n\n        std::vector<InfinitePath>\
    \ infinite_paths() const {\n            std::vector<InfinitePath> res(_n);\n\n\
    \            std::vector<int> vis(_n, _n);\n            std::vector<int> dep(_n,\
    \ 0);\n\n            int time = 0;\n            auto dfs = [&](auto dfs, int u)\
    \ -> int {\n                vis[u] = time;\n                int v = _nxt[u];\n\
    \                if (vis[v] == vis[u]) { // found cycle\n                    int\
    \ loop_len = dep[u] - dep[v] + 1;\n                    res[u] = { u, 0, u, loop_len\
    \ };\n                    return loop_len - 1;\n                } else if (vis[v]\
    \ < vis[u]) {\n                    res[u] = { u, res[v].head_len + 1, res[v].loop_v,\
    \ res[v].loop_len };\n                    return 0;\n                } else {\n\
    \                    dep[v] = dep[u] + 1;\n                    int c = dfs(dfs,\
    \ v);\n                    if (c > 0) { // in cycle\n                        res[u]\
    \ = { u, 0, u, res[v].loop_len };\n                        return c - 1;\n   \
    \                 } else { // out of cycle\n                        res[u] = {\
    \ u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };\n                \
    \        return 0;\n                    }\n                }\n            };\n\
    \            for (int i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);\n\
    \            return res;\n        }\n\n        /**\n         * Calculates k'th\
    \ iterate: f(f(f(...f(i)))) for all 0 <= i < N in O(N) time.\n         * Reference:\
    \ https://noshi91.hatenablog.com/entry/2019/09/22/114149\n         */\n      \
    \  std::vector<int> kth_iterate(const long long k) {\n            assert(k >=\
    \ 0);\n            std::vector<int> res(_n);\n            std::vector<int> forest_roots;\n\
    \            std::vector<std::vector<int>> forest(_n);\n            std::vector<std::vector<std::pair<long\
    \ long, int>>> qs(_n);\n            for (const auto& path : infinite_paths())\
    \ {\n                const int v = path.head_v;\n                (path.head_len\
    \ == 0 ? forest_roots : forest[_nxt[v]]).push_back(v);\n                if (path.head_len\
    \ >= k) continue;\n                qs[path.loop_v].emplace_back(k - path.head_len,\
    \ v);\n            }\n            std::vector<int> dfs_path(_n);\n           \
    \ auto dfs = [&](auto dfs, int u, int d) -> void {\n                dfs_path[d]\
    \ = u;\n                if (d >= k) res[u] = dfs_path[d - k];\n              \
    \  for (int v : forest[u]) dfs(dfs, v, d + 1);\n            };\n            for\
    \ (int root : forest_roots) dfs(dfs, root, 0);\n            std::vector<int8_t>\
    \ seen(_n, false);\n            for (int root : forest_roots) {\n            \
    \    if (seen[root]) continue;\n                std::vector<int> cycle{ root };\n\
    \                for (int v = _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);\n\
    \                const int len = cycle.size();\n                for (int i = 0;\
    \ i < len; ++i) {\n                    const int s = cycle[i];\n             \
    \       seen[s] = true;\n                    for (const auto& [rem, res_index]\
    \ : qs[s]) {\n                        res[res_index] = cycle[(i + rem) % len];\n\
    \                    }\n                }\n            }\n            return res;\n\
    \        }\n\n    private:\n        int _n;\n        std::vector<int> _nxt;\n\n\
    \        static int floor_log2(long long v) {\n            int l = 0;\n      \
    \      while (1LL << (l + 1) <= v) ++l;\n            return l;\n        }\n  \
    \  };\n} // namespace suisen\n\n\n#endif // SUISEN_DOUBLING\n"
  dependsOn: []
  isVerificationFile: false
  path: library/graph/functional_graph.hpp
  requiredBy: []
  timestamp: '2022-04-30 04:34:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/graph/functional_graph/dummy.test.cpp
documentation_of: library/graph/functional_graph.hpp
layout: document
title: Functional Graph
---
## Functional Graph