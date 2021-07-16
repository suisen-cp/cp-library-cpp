---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/tree/HeavyLightDecomposition.hpp
    title: library/tree/HeavyLightDecomposition.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450
  bundledCode: "#line 1 \"test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n#include <atcoder/lazysegtree>\n#include <library/tree/HeavyLightDecomposition.hpp>\n\
    \nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450\"\
    \n\n#include <iostream>\n#include <atcoder/lazysegtree>\n#include <library/tree/HeavyLightDecomposition.hpp>\n\
    \nstruct S {\n    int len;\n    long long pref, max, suff, sum;\n    S(int len,\
    \ long long pref, long long max, long long suff, long long sum) : len(len), pref(pref),\
    \ max(max), suff(suff), sum(sum) {}\n};\n\nconstexpr long long INF = std::numeric_limits<int>::max();\n\
    \nS op1(const S s1, const S s2) {\n    int len = s1.len + s2.len;\n    long long\
    \ pref = std::max(s1.pref, s1.sum + s2.pref);\n    long long max  = std::max({s1.max,\
    \ s2.max, s1.suff + s2.pref});\n    long long suff = std::max(s1.suff + s2.sum,\
    \ s2.suff);\n    long long sum  = s1.sum + s2.sum;\n    return {len, pref, max,\
    \ suff, sum};\n}\nS op2(const S s1, const S s2) {\n    return op1(s2, s1);\n}\n\
    S e() { \n    return {0, -INF, -INF, -INF, 0};\n}\nS mapping(long long f, S x)\
    \ {\n    int len = x.len;\n    if (f == -INF or len == 0) return x;\n    long\
    \ long max = f >= 0 ? f * len : f;\n    return {len, max, max, max, f * len};\n\
    }\nlong long composition(long long f, long long g) {\n    return f == -INF ? g\
    \ : f;\n}\nlong long id() {\n    return -INF;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> w(n);\n    for (long long &e : w) {\n        std::cin >> e;\n    }\n \
    \   std::vector<std::vector<int>> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    suisen::HeavyLightDecomposition hld(g);\n\
    \    atcoder::lazy_segtree<S, op1, e, long long, mapping, composition, id> seg1(n);\n\
    \    atcoder::lazy_segtree<S, op2, e, long long, mapping, composition, id> seg2(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        hld.update_point(i, [&](int j) {\n\
    \            seg1.set(j, {1, w[i], w[i], w[i], w[i]});\n            seg2.set(j,\
    \ {1, w[i], w[i], w[i], w[i]});\n        });\n    }\n    for (int i = 0; i < q;\
    \ ++i) {\n        int t, a, b, c;\n        std::cin >> t >> a >> b >> c;\n   \
    \     --a, --b;\n        if (t == 1) {\n            hld.update_path(a, b, [&](int\
    \ l, int r) {\n                seg1.apply(l, r, c);\n                seg2.apply(l,\
    \ r, c);\n            });\n        } else {\n            std::cout << hld.fold_path_noncommutative(\n\
    \                a, b, e(), op1,\n                [&](int l, int r) { return seg1.prod(l,\
    \ r); },\n                [&](int l, int r) { return seg2.prod(l, r); }\n    \
    \        ).max << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/tree/HeavyLightDecomposition.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
layout: document
redirect_from:
- /library/test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
- /library/test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp.html
title: test/src/tree/HeavyLightDecomposition/do_use_segment_tree.cpp
---
