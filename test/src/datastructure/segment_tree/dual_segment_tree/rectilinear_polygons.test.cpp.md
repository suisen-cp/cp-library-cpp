---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/dual_segment_tree.hpp
    title: library/datastructure/segment_tree/dual_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc211/tasks/abc211_f
    links:
    - https://atcoder.jp/contests/abc211/tasks/abc211_f
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/segment_tree/commutative_dual_segment_tree.hpp: line 6:\
    \ unable to process #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc211/tasks/abc211_f\"\n\n\
    #include <algorithm>\n#include <iostream>\n#include <tuple>\n\n#include \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \nusing suisen::DualSegmentTree;\n\nconstexpr int M = 100010;\n\nint mapping(int\
    \ f, int x) { return f + x; }\nint composition(int f, int g) { return f + g; }\n\
    int id() { return 0; }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<std::vector<std::tuple<int,\
    \ int, int>>> event(M);\n    DualSegmentTree<int, int, mapping, composition, id>\
    \ seg1(M, 0);\n    for (int i = 0; i < n; ++i) {\n        int m;\n        std::cin\
    \ >> m;\n        std::vector<std::pair<int, int>> polygon(m);\n        for (int\
    \ j = 0; j < m; ++j) {\n            int x, y;\n            std::cin >> x >> y;\n\
    \            polygon[j] = {x, y};\n        }\n        std::vector<std::tuple<int,\
    \ int, int>> t;\n        for (int j = 0; j < m; j += 2) {\n            auto [x,\
    \ y1] = polygon[j];\n            auto [_, y2] = polygon[j + 1];\n            t.emplace_back(x,\
    \ std::min(y1, y2), std::max(y1, y2));\n        }\n        std::sort(t.begin(),\
    \ t.end());\n        for (auto [x, yl, yr] : t) {\n            int sgn = seg1[yl]\
    \ & 1 ? -1 : 1;\n            event[x].emplace_back(yl, yr, sgn);\n           \
    \ seg1.apply(yl, yr, 1);\n        }\n        for (auto [_, yl, yr] : t) {\n  \
    \          seg1.apply(yl, yr, -1);\n        }\n    }\n    int q;\n    std::cin\
    \ >> q;\n    std::vector<std::tuple<int, int, int>> qs(q);\n    for (int i = 0;\
    \ i < q; ++i) {\n        int x, y;\n        std::cin >> x >> y;\n        qs[i]\
    \ = {x, y, i};\n    }\n    std::sort(qs.begin(), qs.end());\n    std::vector<int>\
    \ ans(q);\n    DualSegmentTree<int, int, mapping, composition, id> seg(M, 0);\n\
    \    int prev = 0;\n    for (auto [x, y, id] : qs) {\n        for (; prev <= x;\
    \ ++prev) {\n            for (auto [yl, yr, sgn] : event[prev]) seg.apply(yl,\
    \ yr, sgn);\n        }\n        ans[id] = seg[y];\n    }\n    for (auto v : ans)\
    \ {\n        std::cout << v << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/dual_segment_tree.hpp
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp.html
title: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
---
