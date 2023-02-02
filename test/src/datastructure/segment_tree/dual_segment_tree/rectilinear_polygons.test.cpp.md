---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u4F5C\u7528\u304C\u53EF\
      \u63DB\u306A\u5834\u5408)"
  - icon: ':question:'
    path: library/datastructure/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc211/tasks/abc211_f\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#include <tuple>\n\n#line 1 \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n\
    \    struct CommutativeDualSegmentTree {\n        CommutativeDualSegmentTree()\
    \ {}\n        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()), m(ceil_pow2(a.size())),\
    \ data(std::move(a)), lazy(m, id()) {}\n        CommutativeDualSegmentTree(const\
    \ std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a)) {}\n    \
    \    CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n,\
    \ fill_value)) {}\n\n        T operator[](int i) const {\n            assert(0\
    \ <= i and i < n);\n            T res = data[i];\n            for (i = (i + m)\
    \ >> 1; i; i >>= 1) res = mapping(lazy[i], res);\n            return res;\n  \
    \      }\n        T get(int i) const {\n            return (*this)[i];\n     \
    \   }\n        void apply(int l, int r, const F& f) {\n            assert(0 <=\
    \ l and r <= n);\n            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n\
    \                if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r,\
    \ f);\n            }\n        }\n    protected:\n        int n, m;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F& f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else if (k - m < n) {\n                data[k - m] = mapping(f,\
    \ data[k - m]);\n            }\n        }\n    private:\n        static int ceil_pow2(int\
    \ n) {\n            int m = 1;\n            while (m < n) m <<= 1;\n         \
    \   return m;\n        }\n    };\n} // namespace suisen\n\n\n#line 5 \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, typename F, T(*mapping)(F, T),\
    \ F(*composition)(F, F), F(*id)()>\n    struct DualSegmentTree : public CommutativeDualSegmentTree<T,\
    \ F, mapping, composition, id> {\n        using base_type = CommutativeDualSegmentTree<T,\
    \ F, mapping, composition, id>;\n        using base_type::base_type;\n       \
    \ void apply(int l, int r, const F& f) {\n            push(l, r);\n          \
    \  base_type::apply(l, r, f);\n        }\n    private:\n        void push(int\
    \ k) {\n            base_type::apply(2 * k, this->lazy[k]), base_type::apply(2\
    \ * k + 1, this->lazy[k]);\n            this->lazy[k] = id();\n        }\n   \
    \     void push(int l, int r) {\n            static const int log = __builtin_ctz(this->m);\n\
    \            l += this->m, r += this->m;\n            for (int i = log; (l >>\
    \ i) << i != l; --i) push(l >> i);\n            for (int i = log; (r >> i) <<\
    \ i != r; --i) push(r >> i);\n        }\n    };\n\n    template <typename T, typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    DualSegmentTree(int,\
    \ T)->DualSegmentTree<T, F, mapping, composition, id>;\n\n    template <typename\
    \ T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    DualSegmentTree(std::vector<T>)->DualSegmentTree<T,\
    \ F, mapping, composition, id>;\n} // namespace suisen\n\n\n\n#line 8 \"test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp\"\
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
    \ {\n        std::cout << v << '\\n';\n    }\n    return 0;\n}\n"
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
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 10:47:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp.html
title: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
---
