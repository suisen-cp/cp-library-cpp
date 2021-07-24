---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/dual_segment_tree.hpp
    title: library/datastructure/dual_segment_tree.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc211/tasks/abc211_f
    links:
    - https://atcoder.jp/contests/abc211/tasks/abc211_f
  bundledCode: "#line 1 \"test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc211/tasks/abc211_f\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#include <tuple>\n\n#line 1 \"library/datastructure/dual_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\n\n// ! function\ntemplate <typename ReturnType, typename Callable,\
    \ typename ...Args>\nusing is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable,\
    \ Args...>, ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op =\
    \ is_same_as_invoke_result<T, F, T>;\ntemplate <typename F, typename T>\nusing\
    \ is_bin_op = is_same_as_invoke_result<T, F, T, T>;\n\ntemplate <typename Comparator,\
    \ typename T>\nusing is_comparator = std::is_same<std::invoke_result_t<Comparator,\
    \ T, T>, bool>;\n\n// ! integral\ntemplate <typename T, typename = constraints_t<std::is_integral<T>>>\n\
    constexpr int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\n\
    template <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool\
    \ value = bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 7 \"\
    library/datastructure/dual_segment_tree.hpp\"\n\nnamespace suisen {\ntemplate\
    \ <\n    typename T, typename F, typename Mapping, typename Composition,\n   \
    \ constraints_t<std::is_same<T, std::invoke_result_t<Mapping, F, T>>, std::is_same<F,\
    \ std::invoke_result_t<Composition, F, F>>> = nullptr\n>\nclass CommutativeDualSegmentTree\
    \ {\n    public:\n        CommutativeDualSegmentTree() {}\n        CommutativeDualSegmentTree(int\
    \ n, const T &fill_value, const F &id, Mapping mapping, Composition composition)\
    \ :\n            n(n), m(ceil_pow2(n)), id(id), mapping(mapping), composition(composition),\
    \ data(n, fill_value), lazy(m, id) {}\n        CommutativeDualSegmentTree(std::vector<T>\
    \ &&a, const F &id, Mapping mapping, Composition composition) :\n            n(a.size()),\
    \ m(ceil_pow2(a.size())), id(id), mapping(mapping), composition(composition),\
    \ data(std::move(a)), lazy(m, id) {}\n        CommutativeDualSegmentTree(const\
    \ std::vector<T> &a, const F &id, Mapping mapping, Composition composition) :\n\
    \            CommutativeDualSegmentTree(std::vector<T>(a), id, mapping, composition)\
    \ {}\n\n        T operator[](int i) const {\n            assert(0 <= i and i <\
    \ n);\n            T res = data[i];\n            for (i = (i + m) >> 1; i; i >>=\
    \ 1) res = mapping(lazy[i], res);\n            return res;\n        }\n      \
    \  T get(int i) const {\n            return (*this)[i];\n        }\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= n);\n\
    \            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n               \
    \ if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r, f);\n     \
    \       }\n        }\n    protected:\n        int n, m;\n        F id;\n     \
    \   Mapping mapping;\n        Composition composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F &f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n};\n\ntemplate <\n    typename T, typename F, typename Mapping,\
    \ typename Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass DualSegmentTree : public CommutativeDualSegmentTree<T, F, Mapping, Composition>\
    \ {\n    using BaseType = CommutativeDualSegmentTree<T, F, Mapping, Composition>;\n\
    \    public:\n        using BaseType::CommutativeDualSegmentTree;\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= this->n);\n\
    \            for (int lk = l + this->m, rk = r + this->m, i = 1; lk >> i; ++i)\
    \ {\n                if (((lk >> i) << i) != lk) push(lk >> i);\n            \
    \    if (((rk >> i) << i) != rk) push((rk - 1) >> i);\n            }\n       \
    \     BaseType::apply(l, r, f);\n        }\n    private:\n        void push(int\
    \ k) {\n            if (this->lazy[k] != this->id) {\n                BaseType::apply(2\
    \ * k, this->lazy[k]), BaseType::apply(2 * k + 1, this->lazy[k]);\n          \
    \      this->lazy[k] = this->id;\n            }\n        }\n};\n\ntemplate <typename\
    \ T, typename F, typename Mapping, typename Composition>\nDualSegmentTree(int,\
    \ T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;\n\
    \ntemplate <typename T, typename F, typename Mapping, typename Composition>\n\
    DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T,\
    \ F, Mapping, Composition>;\n\n} // namespace suisen\n\n\n\n#line 8 \"test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp\"\
    \nusing suisen::CommutativeDualSegmentTree;\n\nconstexpr int M = 100010;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<std::vector<std::tuple<int, int,\
    \ int>>> event(M);\n    CommutativeDualSegmentTree seg1(M, 0, 0, std::plus<int>(),\
    \ std::plus<int>());\n    for (int i = 0; i < n; ++i) {\n        int m;\n    \
    \    std::cin >> m;\n        std::vector<std::pair<int, int>> polygon(m);\n  \
    \      for (int j = 0; j < m; ++j) {\n            int x, y;\n            std::cin\
    \ >> x >> y;\n            polygon[j] = {x, y};\n        }\n        std::vector<std::tuple<int,\
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
    \ ans(q);\n    CommutativeDualSegmentTree seg(M, 0, 0, std::plus<int>(), std::plus<int>());\n\
    \    int prev = 0;\n    for (auto [x, y, id] : qs) {\n        for (; prev <= x;\
    \ ++prev) {\n            for (auto [yl, yr, sgn] : event[prev]) seg.apply(yl,\
    \ yr, sgn);\n        }\n        ans[id] = seg[y];\n    }\n    for (auto v : ans)\
    \ {\n        std::cout << v << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc211/tasks/abc211_f\"\n\n\
    #include <algorithm>\n#include <iostream>\n#include <tuple>\n\n#include \"library/datastructure/dual_segment_tree.hpp\"\
    \nusing suisen::CommutativeDualSegmentTree;\n\nconstexpr int M = 100010;\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<std::vector<std::tuple<int, int,\
    \ int>>> event(M);\n    CommutativeDualSegmentTree seg1(M, 0, 0, std::plus<int>(),\
    \ std::plus<int>());\n    for (int i = 0; i < n; ++i) {\n        int m;\n    \
    \    std::cin >> m;\n        std::vector<std::pair<int, int>> polygon(m);\n  \
    \      for (int j = 0; j < m; ++j) {\n            int x, y;\n            std::cin\
    \ >> x >> y;\n            polygon[j] = {x, y};\n        }\n        std::vector<std::tuple<int,\
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
    \ ans(q);\n    CommutativeDualSegmentTree seg(M, 0, 0, std::plus<int>(), std::plus<int>());\n\
    \    int prev = 0;\n    for (auto [x, y, id] : qs) {\n        for (; prev <= x;\
    \ ++prev) {\n            for (auto [yl, yr, sgn] : event[prev]) seg.apply(yl,\
    \ yr, sgn);\n        }\n        ans[id] = seg[y];\n    }\n    for (auto v : ans)\
    \ {\n        std::cout << v << '\\n';\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
  requiredBy: []
  timestamp: '2021-07-25 00:38:38+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
- /verify/test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp.html
title: test/src/datastructure/dual_segment_tree/rectilinear_polygons_commmutative.test.cpp
---
