---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.6/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.6/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.6/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.6/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: library/tree/point_set_range_contour_product.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <iostream>\n#include <numeric>\n#include <random>\n\n#include \"\
    library/tree/point_set_range_contour_product.hpp\"\n\nint op(int x, int y) {\n\
    \    return std::max(x, y);\n}\nint e() {\n    return 0;\n}\n\nusing Solution\
    \ = suisen::PointSetRangeContourProduct<int, op, e>;\n\nstruct NaiveSolution {\n\
    \    NaiveSolution(std::vector<std::vector<int>> g, std::vector<int> dat) : g(g),\
    \ dat(dat) {}\n\n    void set(int u, int val) {\n        dat[u] = val;\n    }\n\
    \    int prod(int k, int dl, int dr) {\n        int res = e();\n        auto dfs\
    \ = [&](auto dfs, int u, int p, int dep) -> void {\n            if (dl <= dep\
    \ and dep < dr) res = op(res, dat[u]);\n            for (int v : g[u]) {\n   \
    \             if (v == p) continue;\n                dfs(dfs, v, u, dep + 1);\n\
    \            }\n        };\n        dfs(dfs, k, -1, 0);\n        return res;\n\
    \    }\nprivate:\n    std::vector<std::vector<int>> g;\n    std::vector<int> dat;\n\
    };\n\nvoid random_queries(int n, int q, Solution& t1, NaiveSolution& t2) {\n \
    \   auto check = [&](int k, int dl, int dr) {\n        int sum1 = t1.prod(k, dl,\
    \ dr);\n        int sum2 = t2.prod(k, dl, dr);\n        assert(sum1 == sum2);\n\
    \    };\n\n    std::mt19937 rng{ std::random_device{}() };\n    while (q-- > 0)\
    \ {\n        int qt = rng();\n        if (qt == 1) {\n            int i = rng()\
    \ % n;\n            int v = rng() % 10000;\n            t1.set(i, v);\n      \
    \      t2.set(i, v);\n        } else {\n            int i = rng() % n;\n     \
    \       int l = rng() % n;\n            int r = l + rng() % (n - l);\n       \
    \     check(i, l, r);\n        }\n    }\n}\n\n#include <atcoder/dsu>\n\nstd::vector<std::vector<int>>\
    \ random_tree(int n) {\n    std::mt19937 rng{ std::random_device{}() };\n\n  \
    \  std::vector<std::pair<int, int>> edges;\n    for (int i = 0; i < n; ++i) for\
    \ (int j = 0; j < i; ++j) {\n        edges.emplace_back(i, j);\n    }\n    std::shuffle(edges.begin(),\
    \ edges.end(), rng);\n\n    std::vector<std::vector<int>> g(n);\n\n    atcoder::dsu\
    \ uf(n);\n    int con = n;\n    while (con > 1) {\n        auto [u, v] = edges.back();\n\
    \        edges.pop_back();\n        if (uf.same(u, v)) continue;\n        uf.merge(u,\
    \ v);\n        --con;\n        g[u].push_back(v);\n        g[v].push_back(u);\n\
    \    }\n    return g;\n}\n\nvoid test1(int q = 100000) {\n    std::vector<std::vector<int>>\
    \ g{\n        { 1, 8, 16 },       // 0\n        { 0, 2, 3 },        // 1\n   \
    \     { 1 },              // 2\n        { 1, 4, 7 },        // 3\n        { 3,\
    \ 5, 6 },        // 4\n        { 4 },              // 5\n        { 4 },      \
    \        // 6\n        { 3 },              // 7\n        { 0, 9, 10 },       //\
    \ 8\n        { 8 },              // 9\n        { 8, 11, 15 },      // 10\n   \
    \     { 10, 12, 13, 14 }, // 11\n        { 11 },             // 12\n        {\
    \ 11 },             // 13\n        { 11 },             // 14\n        { 10 },\
    \             // 15\n        { 0, 17, 18, 20 },  // 16\n        { 16 },      \
    \       // 17\n        { 16, 19 },         // 18\n        { 18 },            \
    \ // 19\n        { 16, 21, 24 },     // 20\n        { 20, 22, 23 },     // 21\n\
    \        { 21 },             // 22\n        { 21 },             // 23\n      \
    \  { 20 }              // 24\n    };\n\n    const int n = g.size();\n    std::vector<int>\
    \ dat(n);\n    std::iota(dat.begin(), dat.end(), 1);\n\n    suisen::PointSetRangeContourProduct<int,\
    \ op, e> contour_aggregator(dat);\n    for (int i = 0; i < n; ++i) for (int j\
    \ : g[i]) if (i < j) {\n        contour_aggregator.add_edge(i, j);\n    }\n\n\
    \    contour_aggregator.build();\n    NaiveSolution naive(g, dat);\n\n    random_queries(n,\
    \ q, contour_aggregator, naive);\n}\n\nvoid test2(int n = 1000, int q = 10000)\
    \ {\n    auto g = random_tree(n);\n    std::vector<int> dat(n);\n    std::iota(dat.begin(),\
    \ dat.end(), 1);\n\n    suisen::PointSetRangeContourProduct<int, op, e> contour_aggregator(dat);\n\
    \    for (int i = 0; i < n; ++i) for (int j : g[i]) if (i < j) {\n        contour_aggregator.add_edge(i,\
    \ j);\n    }\n\n    contour_aggregator.build();\n    NaiveSolution naive(g, dat);\n\
    \n    random_queries(n, q, contour_aggregator, naive);\n}\n\nint main() {\n  \
    \  test1();\n    test2();\n    std::cout << \"Hello World\" << std::endl;\n  \
    \  return 0;\n}"
  dependsOn: []
  isVerificationFile: true
  path: test/src/tree/point_set_range_contour_sum/dummy.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/tree/point_set_range_contour_sum/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/tree/point_set_range_contour_sum/dummy.test.cpp
- /verify/test/src/tree/point_set_range_contour_sum/dummy.test.cpp.html
title: test/src/tree/point_set_range_contour_sum/dummy.test.cpp
---
