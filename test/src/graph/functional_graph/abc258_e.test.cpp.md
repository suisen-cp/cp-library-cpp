---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/graph/functional_graph.hpp
    title: Functional Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc258/tasks/abc258_e
    links:
    - https://atcoder.jp/contests/abc258/tasks/abc258_e
  bundledCode: "#line 1 \"test/src/graph/functional_graph/abc258_e.test.cpp\"\n#define\
    \ PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_e\"\n\n#include <iostream>\n\
    \n#line 1 \"library/graph/functional_graph.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <optional>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace suisen {\n    struct FunctionalGraph {\n        struct\
    \ Doubling;\n        template <typename T, T(*)(T, T), T(*)()>\n        struct\
    \ DoublingSum;\n        friend struct Doubling;\n        template <typename T,\
    \ T(*op)(T, T), T(*e)()>\n        friend struct DoublingSum;\n\n        FunctionalGraph()\
    \ : FunctionalGraph(0) {}\n        FunctionalGraph(int n) : _n(n), _nxt(n) {}\n\
    \        FunctionalGraph(const std::vector<int>& nxt) : _n(nxt.size()), _nxt(nxt)\
    \ {}\n\n        const int& operator[](int u) const {\n            return _nxt[u];\n\
    \        }\n        int& operator[](int u) {\n            return _nxt[u];\n  \
    \      }\n\n        struct Doubling {\n            friend struct FunctionalGraph;\n\
    \n            int query(int u, long long d) const {\n                for (int\
    \ l = _log; l >= 0; --l) if ((d >> l) & 1) u = _nxt[l][u];\n                return\
    \ u;\n            }\n\n            struct BinarySearchResult {\n             \
    \   int v;\n                long long step;\n                operator std::pair<int,\
    \ long long>() const { return std::pair<int, long long>{ v, step }; }\n      \
    \      };\n\n            template <typename Pred>\n            auto max_step(int\
    \ u, Pred &&f) const {\n                assert(f(u));\n                long long\
    \ step = 0;\n                for (int l = _log; l >= 0; --l) if (int nxt_u = _nxt[l][u];\
    \ f(nxt_u)) {\n                    u = nxt_u, step |= 1LL << l;\n            \
    \    }\n                return BinarySearchResult{ u, step };\n            }\n\
    \n            template <typename Pred>\n            std::optional<BinarySearchResult>\
    \ step_until(int u, Pred &&f) const {\n                if (f(u)) return BinarySearchResult\
    \ { u, 0 };\n                auto [v, step] = max_step(u, [&](int v) { return\
    \ not f(v); });\n                v = _nxt[0][v], ++step;\n                if (not\
    \ f(v)) return std::nullopt;\n                return BinarySearchResult{ v, step\
    \ };\n            }\n\n        private:\n            int _n, _log;\n         \
    \   std::vector<std::vector<int>> _nxt;\n\n            Doubling(const std::vector<int>&\
    \ nxt, long long max_step) : _n(nxt.size()), _log(floor_log2(max_step)), _nxt(_log\
    \ + 1, std::vector<int>(_n)) {\n                _nxt[0] = nxt;\n             \
    \   for (int i = 1; i <= _log; ++i) for (int j = 0; j < _n; ++j) {\n         \
    \           _nxt[i][j] = _nxt[i - 1][_nxt[i - 1][j]];\n                }\n   \
    \         }\n        };\n\n        template <typename T, T(*op)(T, T), T(*e)()>\n\
    \        struct DoublingSum : private Doubling {\n            friend struct FunctionalGraph;\n\
    \n            struct Result {\n                int v;\n                T sum;\n\
    \                operator std::pair<int, T>() const { return std::pair<int, T>{\
    \ v, sum }; }\n            };\n\n            auto query(int u, long long d) const\
    \ {\n                T sum = e();\n                for (int l = _log; l >= 0;\
    \ --l) if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u, _nxt[l][u])]);\n\
    \                return Result{ u, sum };\n            }\n\n            struct\
    \ BinarySearchResult {\n                int v;\n                T sum;\n     \
    \           long long step;\n                operator std::tuple<int, T, long\
    \ long>() const { return std::tuple<int, T, long long>{ v, sum, step }; }\n  \
    \          };\n\n            template <typename Pred>\n            auto max_step(int\
    \ u, Pred &&f) const {\n                assert(f(e()));\n                long\
    \ long step = 0;\n                T sum = e();\n                for (int l = _log;\
    \ l >= 0; --l) {\n                    if (T nxt_sum = op(sum, _dat[l][u]); f(nxt_sum))\
    \ {\n                        sum = std::move(nxt_sum), u = _nxt[l][u], step |=\
    \ 1LL << l;\n                    }\n                }\n                return\
    \ BinarySearchResult{ u, sum, step };\n            }\n            template <typename\
    \ Pred>\n            std::optional<BinarySearchResult> step_until(int u, Pred\
    \ &&f) const {\n                if (f(e())) return BinarySearchResult { u, e(),\
    \ 0 };\n                auto [v, sum, step] = max_step(u, [&](const T& v) { return\
    \ not f(v); });\n                sum = op(sum, _dat[0][v]), v = _nxt[0][v], ++step;\n\
    \                if (not f(sum)) return std::nullopt;\n                return\
    \ BinarySearchResult{ v, sum, step };\n            }\n\n        private:\n   \
    \         std::vector<std::vector<T>> _dat;\n\n            DoublingSum(const std::vector<int>&\
    \ nxt, long long max_step, const std::vector<T>& dat) : Doubling(nxt, max_step),\
    \ _dat(_log + 1, std::vector<T>(_n, e())) {\n                _dat[0] = dat;\n\
    \                for (int i = 1; i <= _log; ++i) for (int j = 0; j < _n; ++j)\
    \ {\n                    _dat[i][j] = op(_dat[i - 1][j], _dat[i - 1][_nxt[i -\
    \ 1][j]]);\n                }\n            }\n        };\n\n        Doubling doubling(long\
    \ long max_step) const {\n            return Doubling(_nxt, max_step);\n     \
    \   }\n\n        template <typename T, T(*op)(T, T), T(*e)()>\n        DoublingSum<T,\
    \ op, e> doubling(long long max_step, const std::vector<T>& dat) const {\n   \
    \         return DoublingSum<T, op, e>(_nxt, max_step, dat);\n        }\n\n  \
    \      struct InfinitePath {\n            int head_v;\n            int head_len;\n\
    \            int loop_v;\n            int loop_len;\n            InfinitePath()\
    \ = default;\n            InfinitePath(int head_v, int head_len, int loop_v, int\
    \ loop_len) : head_v(head_v), head_len(head_len), loop_v(loop_v), loop_len(loop_len)\
    \ {}\n        };\n\n        std::vector<InfinitePath> infinite_paths() const {\n\
    \            std::vector<InfinitePath> res(_n);\n\n            std::vector<int>\
    \ vis(_n, _n);\n            std::vector<int> dep(_n, 0);\n\n            int time\
    \ = 0;\n            auto dfs = [&](auto dfs, int u) -> int {\n               \
    \ vis[u] = time;\n                int v = _nxt[u];\n                if (vis[v]\
    \ == vis[u]) { // found cycle\n                    int loop_len = dep[u] - dep[v]\
    \ + 1;\n                    res[u] = { u, 0, u, loop_len };\n                \
    \    return loop_len - 1;\n                } else if (vis[v] < vis[u]) {\n   \
    \                 res[u] = { u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len\
    \ };\n                    return 0;\n                } else {\n              \
    \      dep[v] = dep[u] + 1;\n                    int c = dfs(dfs, v);\n      \
    \              if (c > 0) { // in cycle\n                        res[u] = { u,\
    \ 0, u, res[v].loop_len };\n                        return c - 1;\n          \
    \          } else { // out of cycle\n                        res[u] = { u, res[v].head_len\
    \ + 1, res[v].loop_v, res[v].loop_len };\n                        return 0;\n\
    \                    }\n                }\n            };\n            for (int\
    \ i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);\n            return\
    \ res;\n        }\n\n        /**\n         * Calculates k'th iterate: f(f(f(...f(i))))\
    \ for all 0 <= i < N in O(N) time.\n         * Reference: https://noshi91.hatenablog.com/entry/2019/09/22/114149\n\
    \         */\n        std::vector<int> kth_iterate(const long long k) const {\n\
    \            assert(k >= 0);\n            std::vector<int> res(_n);\n        \
    \    std::vector<int> forest_roots;\n            std::vector<std::vector<int>>\
    \ forest(_n);\n            std::vector<std::vector<std::pair<long long, int>>>\
    \ qs(_n);\n            for (const auto& path : infinite_paths()) {\n         \
    \       const int v = path.head_v;\n                (path.head_len == 0 ? forest_roots\
    \ : forest[_nxt[v]]).push_back(v);\n                if (path.head_len >= k) continue;\n\
    \                qs[path.loop_v].emplace_back(k - path.head_len, v);\n       \
    \     }\n            std::vector<int> dfs_path(_n);\n            auto dfs = [&](auto\
    \ dfs, int u, int d) -> void {\n                dfs_path[d] = u;\n           \
    \     if (d >= k) res[u] = dfs_path[d - k];\n                for (int v : forest[u])\
    \ dfs(dfs, v, d + 1);\n            };\n            for (int root : forest_roots)\
    \ dfs(dfs, root, 0);\n            std::vector<int8_t> seen(_n, false);\n     \
    \       for (int root : forest_roots) {\n                if (seen[root]) continue;\n\
    \                std::vector<int> cycle{ root };\n                for (int v =\
    \ _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);\n                const\
    \ int len = cycle.size();\n                for (int i = 0; i < len; ++i) {\n \
    \                   const int s = cycle[i];\n                    seen[s] = true;\n\
    \                    for (const auto& [rem, res_index] : qs[s]) {\n          \
    \              res[res_index] = cycle[(i + rem) % len];\n                    }\n\
    \                }\n            }\n            return res;\n        }\n\n    private:\n\
    \        int _n;\n        std::vector<int> _nxt;\n\n        static int floor_log2(long\
    \ long v) {\n            int l = 0;\n            while (1LL << (l + 1) <= v) ++l;\n\
    \            return l;\n        }\n    };\n} // namespace suisen\n\n\n\n#line\
    \ 6 \"test/src/graph/functional_graph/abc258_e.test.cpp\"\n\nlong long op(long\
    \ long x, long long y) {\n    return x + y;\n}\nlong long e() {\n    return 0;\n\
    }\n\nconstexpr long long M = 1000000010;\nconstexpr long long L = 1000000000010LL;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    long long x;\n    std::cin >> n >> q >> x;\n\n    std::vector<long\
    \ long> w(n);\n    for (auto& e : w) std::cin >> e;\n\n    std::vector<long long>\
    \ num(n);\n    std::vector<int> nxt(n);\n    {\n        std::vector<int> tmp_nxt(n);\n\
    \        for (int i = 0; i < n; ++i) tmp_nxt[i] = (i + 1) % n;\n        auto d\
    \ = suisen::FunctionalGraph{ tmp_nxt }.doubling<long long, op, e>(M, w);\n   \
    \     for (int i = 0; i < n; ++i) {\n            auto res = *d.step_until(i, [&](long\
    \ long v) { return v >= x; });\n            nxt[i] = res.v;\n            num[i]\
    \ = res.step;\n        }\n    }\n\n    auto d = suisen::FunctionalGraph{ nxt }.doubling(L);\n\
    \    while (q --> 0) {\n        long long k;\n        std::cin >> k;\n       \
    \ std::cout << num[d.query(0, k - 1)] << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc258/tasks/abc258_e\"\n\n\
    #include <iostream>\n\n#include \"library/graph/functional_graph.hpp\"\n\nlong\
    \ long op(long long x, long long y) {\n    return x + y;\n}\nlong long e() {\n\
    \    return 0;\n}\n\nconstexpr long long M = 1000000010;\nconstexpr long long\
    \ L = 1000000000010LL;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    long long x;\n    std::cin >>\
    \ n >> q >> x;\n\n    std::vector<long long> w(n);\n    for (auto& e : w) std::cin\
    \ >> e;\n\n    std::vector<long long> num(n);\n    std::vector<int> nxt(n);\n\
    \    {\n        std::vector<int> tmp_nxt(n);\n        for (int i = 0; i < n; ++i)\
    \ tmp_nxt[i] = (i + 1) % n;\n        auto d = suisen::FunctionalGraph{ tmp_nxt\
    \ }.doubling<long long, op, e>(M, w);\n        for (int i = 0; i < n; ++i) {\n\
    \            auto res = *d.step_until(i, [&](long long v) { return v >= x; });\n\
    \            nxt[i] = res.v;\n            num[i] = res.step;\n        }\n    }\n\
    \n    auto d = suisen::FunctionalGraph{ nxt }.doubling(L);\n    while (q --> 0)\
    \ {\n        long long k;\n        std::cin >> k;\n        std::cout << num[d.query(0,\
    \ k - 1)] << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/graph/functional_graph.hpp
  isVerificationFile: true
  path: test/src/graph/functional_graph/abc258_e.test.cpp
  requiredBy: []
  timestamp: '2022-07-10 15:07:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/graph/functional_graph/abc258_e.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/functional_graph/abc258_e.test.cpp
- /verify/test/src/graph/functional_graph/abc258_e.test.cpp.html
title: test/src/graph/functional_graph/abc258_e.test.cpp
---
