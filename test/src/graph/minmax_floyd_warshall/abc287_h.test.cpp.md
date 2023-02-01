---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/graph/minmax_floyd_warshall.hpp
    title: Minmax Floyd Warshall
  - icon: ':question:'
    path: library/util/subset_iterator.hpp
    title: Subset Iterator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc287/tasks/abc287_h
    links:
    - https://atcoder.jp/contests/abc287/tasks/abc287_h
  bundledCode: "#line 1 \"test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc287/tasks/abc287_h\"\n\n#include\
    \ <iostream>\n\n#line 1 \"library/graph/minmax_floyd_warshall.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cstdint>\n#include <functional>\n#include <tuple>\n#include\
    \ <vector>\n\n#line 1 \"library/util/subset_iterator.hpp\"\n\n\n\n#ifdef _MSC_VER\n\
    #  include <intrin.h>\n#else\n#  include <x86intrin.h>\n#endif\n\n#include <cassert>\n\
    #line 13 \"library/util/subset_iterator.hpp\"\n#include <limits>\n\nnamespace\
    \ suisen {\n    template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ std::nullptr_t> = nullptr>\n    struct all_subset {\n        struct all_subset_iter\
    \ {\n            const T s; T t;\n            constexpr all_subset_iter(T s) :\
    \ s(s), t(s + 1) {}\n            constexpr auto operator*() const { return t;\
    \ }\n            constexpr auto operator++() {}\n            constexpr auto operator!=(std::nullptr_t)\
    \ { return t ? (--t &= s, true) : false; }\n        };\n        T s;\n       \
    \ constexpr all_subset(T s) : s(s) {}\n        constexpr auto begin() { return\
    \ all_subset_iter(s); }\n        constexpr auto end() { return nullptr; }\n  \
    \  };\n\n    // iterator over T s.t. T is subset of S and |T| = k\n    struct\
    \ all_subset_k {\n        struct all_subset_k_iter {\n            const uint32_t\
    \ n, k, s;\n            uint32_t t;\n            __attribute__((target(\"avx2\"\
    )))\n            all_subset_k_iter(uint32_t s, uint32_t k) : n(uint32_t(1) <<\
    \ _mm_popcnt_u32(s)), k(k), s(s), t((uint32_t(1) << k) - 1) {}\n            __attribute__((target(\"\
    bmi2\")))\n            auto operator*() const { return _pdep_u32(t, s); }\n  \
    \          __attribute__((target(\"bmi\")))\n            auto operator++() {\n\
    \                if (k == 0) {\n                    t = std::numeric_limits<uint32_t>::max();\n\
    \                } else {\n                    uint32_t y = t + _blsi_u32(t);\
    \ // t + (-t & t)\n                    t = y | ((y ^ t) >> _tzcnt_u32(t << 2));\n\
    \                }\n            }\n            auto operator!=(std::nullptr_t)\
    \ const { return t < n; }\n        };\n        uint32_t s, k;\n        all_subset_k(uint32_t\
    \ s, uint32_t k) : s(s), k(k) {\n            assert(s != std::numeric_limits<uint32_t>::max());\n\
    \        }\n        static all_subset_k nCk(uint32_t n, uint32_t k) { return all_subset_k((uint32_t(1)\
    \ << n) - 1, k); }\n        auto begin() { return all_subset_k_iter(s, k); }\n\
    \        auto end() { return nullptr; }\n    };\n\n    struct all_subset_k_64\
    \ {\n        struct all_subset_k_iter_64 {\n            const uint64_t n, s;\n\
    \            const uint32_t k;\n            uint64_t t;\n            __attribute__((target(\"\
    avx2\")))\n            all_subset_k_iter_64(uint64_t s, uint32_t k) : n(uint64_t(1)\
    \ << _mm_popcnt_u64(s)), s(s), k(k), t((uint64_t(1) << k) - 1) {}\n          \
    \  __attribute__((target(\"bmi2\")))\n            auto operator*() const { return\
    \ _pdep_u64(t, s); }\n            __attribute__((target(\"bmi\")))\n         \
    \   auto operator++() {\n                if (k == 0) {\n                    t\
    \ = std::numeric_limits<uint64_t>::max();\n                } else {\n        \
    \            uint64_t y = t + _blsi_u64(t);\n                    t = y | ((y ^\
    \ t) >> _tzcnt_u64(t << 2));\n                }\n            }\n            auto\
    \ operator!=(std::nullptr_t) const { return t < n; }\n        };\n        uint64_t\
    \ s;\n        uint32_t k;\n        all_subset_k_64(uint64_t s, uint32_t k) : s(s),\
    \ k(k) {\n            assert(s != std::numeric_limits<uint64_t>::max());\n   \
    \     }\n        auto begin() { return all_subset_k_iter_64(s, k); }\n       \
    \ auto end() { return nullptr; }\n    };\n\n    struct all_setbit {\n        struct\
    \ all_setbit_iter {\n            uint32_t s;\n            all_setbit_iter(uint32_t\
    \ s) : s(s) {}\n            __attribute__((target(\"bmi\")))\n            auto\
    \ operator*() { return _tzcnt_u32(s); }\n            __attribute__((target(\"\
    bmi\")))\n            auto operator++() { s = __blsr_u32(s); }\n            auto\
    \ operator!=(std::nullptr_t) { return s; }\n        };\n        uint32_t s;\n\
    \        all_setbit(uint32_t s) : s(s) {}\n        auto begin() { return all_setbit_iter(s);\
    \ }\n        auto end() { return nullptr; }\n    };\n\n    struct all_setbit_64\
    \ {\n        struct all_setbit_iter_64 {\n            uint64_t s;\n          \
    \  all_setbit_iter_64(uint64_t s) : s(s) {}\n            __attribute__((target(\"\
    bmi\")))\n            auto operator*() { return _tzcnt_u64(s); }\n           \
    \ __attribute__((target(\"bmi\")))\n            auto operator++() { s = __blsr_u64(s);\
    \ }\n            auto operator!=(std::nullptr_t) { return s; }\n        };\n \
    \       uint64_t s;\n        all_setbit_64(uint64_t s) : s(s) {}\n        auto\
    \ begin() { return all_setbit_iter_64(s); }\n        auto end() { return nullptr;\
    \ }\n    };\n} // namespace suisen\n\n\n#line 11 \"library/graph/minmax_floyd_warshall.hpp\"\
    \n\nnamespace suisen {\n    // Calculates D[i][j] := min{ max{ cost(e) | e in\
    \ p } | p is an i-j path } in O(N^3/w) time.\n    template <typename T, typename\
    \ Compare = std::less<T>>\n    std::vector<std::vector<T>> minmax_floyd_warshall(const\
    \ std::vector<std::vector<T>>& cost_matrix, Compare comp = {}) {\n        constexpr\
    \ int B = 64;\n        constexpr int LOG_B = 6;\n        constexpr int MASK_B\
    \ = B - 1;\n \n        const int n = cost_matrix.size(), m = (n + B - 1) >> LOG_B;\n\
    \        std::vector G(n, std::vector<uint64_t>(m)), rG(n, std::vector<uint64_t>(m));\n\
    \        std::vector res(n, std::vector<T>(n));\n \n        using E = std::tuple<T,\
    \ int, int>;\n        std::vector<E> edges(n * n);\n        for (int i = 0; i\
    \ < n; ++i) for (int j = 0; j < n; ++j) {\n            edges[i * n + j] = { cost_matrix[i][j],\
    \ i, j };\n        }\n        std::sort(edges.begin(), edges.end(), [&comp](const\
    \ E& e1, const E& e2) { return comp(std::get<0>(e1), std::get<0>(e2)); });\n \n\
    \        // Add edges in ascending order of their costs.\n        for (const auto&\
    \ [cost_, u, v] : edges) {\n            const T& cost = cost_;\n            auto\
    \ add_edge = [&](int u, int v) {\n                const int u_hi = u >> LOG_B,\
    \ u_lo = u & MASK_B;\n                const int v_hi = v >> LOG_B, v_lo = v &\
    \ MASK_B;\n                if ((G[u][v_hi] >> v_lo) & 1) {\n                 \
    \   // already reachable\n                    return false; \n               \
    \ }\n                res[u][v] = cost;\n                G[u][v_hi] |= uint64_t(1)\
    \ << v_lo;\n                rG[v][u_hi] |= uint64_t(1) << u_lo;\n            \
    \    return true;\n            };\n \n            auto rec = [&](auto rec, int\
    \ u, int v) -> void {\n                for (int i = 0; i < m; ++i) {\n       \
    \             // if (u ---> v) and (v ---> w) and (u -/-> w): add (u ---> w)\n\
    \                    if (uint64_t s = G[v][i] & ~G[u][i]) {\n                \
    \        const int w_hi = i << LOG_B;\n                        for (const int\
    \ j : all_setbit_64(s)) add_edge(u, w_hi | j);\n                        for (const\
    \ int j : all_setbit_64(s)) rec(rec, u, w_hi | j);\n                    }\n  \
    \                  // if (w ---> u) and (u ---> v) and (w -/-> v): add (w --->\
    \ v)\n                    if (uint64_t s = rG[u][i] & ~rG[v][i]) {\n         \
    \               const int w_hi = i << LOG_B;\n                        for (const\
    \ int j : all_setbit_64(s)) add_edge(w_hi | j, v);\n                        for\
    \ (const int j : all_setbit_64(s)) rec(rec, w_hi | j, v);\n                  \
    \  }\n                }\n            };\n            if (add_edge(u, v)) {\n \
    \               rec(rec, u, v);\n            }\n        }\n \n        return res;\n\
    \    }\n} // namespace suisen\n\n\n\n#line 6 \"test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp\"\
    \n\nconstexpr int inf = std::numeric_limits<int>::max() / 2;\n \nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n \n    int\
    \ n, m;\n    std::cin >> n >> m;\n \n    std::vector<std::vector<int>> g(n, std::vector<int>(n,\
    \ inf));\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        --u, --v;\n        g[u][v] = std::max(u, v) + 1;\n    }\n\
    \ \n    std::vector<std::vector<int>> ans = suisen::minmax_floyd_warshall(g);\n\
    \ \n    int q;\n    std::cin >> q;\n    for (int i = 0; i < q; ++i) {\n      \
    \  int s, t;\n        std::cin >> s >> t;\n        --s, --t;\n        std::cout\
    \ << (ans[s][t] == inf ? -1 : ans[s][t]) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc287/tasks/abc287_h\"\n\n\
    #include <iostream>\n\n#include \"library/graph/minmax_floyd_warshall.hpp\"\n\n\
    constexpr int inf = std::numeric_limits<int>::max() / 2;\n \nint main() {\n  \
    \  std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n \n    int n,\
    \ m;\n    std::cin >> n >> m;\n \n    std::vector<std::vector<int>> g(n, std::vector<int>(n,\
    \ inf));\n    for (int i = 0; i < m; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        --u, --v;\n        g[u][v] = std::max(u, v) + 1;\n    }\n\
    \ \n    std::vector<std::vector<int>> ans = suisen::minmax_floyd_warshall(g);\n\
    \ \n    int q;\n    std::cin >> q;\n    for (int i = 0; i < q; ++i) {\n      \
    \  int s, t;\n        std::cin >> s >> t;\n        --s, --t;\n        std::cout\
    \ << (ans[s][t] == inf ? -1 : ans[s][t]) << '\\n';\n    }\n}"
  dependsOn:
  - library/graph/minmax_floyd_warshall.hpp
  - library/util/subset_iterator.hpp
  isVerificationFile: true
  path: test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp
layout: document
redirect_from:
- /verify/test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp
- /verify/test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp.html
title: test/src/graph/minmax_floyd_warshall/abc287_h.test.cpp
---
