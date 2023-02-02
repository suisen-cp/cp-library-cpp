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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_point_get
    links:
    - https://judge.yosupo.jp/problem/range_affine_point_get
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\n\
    \n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\n\n\n\n\
    #line 1 \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
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
    \ F, mapping, composition, id>;\n} // namespace suisen\n\n\n\n#line 9 \"test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp\"\
    \n\nmint mapping(std::pair<mint, mint> f, mint x) {\n    return f.first * x +\
    \ f.second;\n}\nstd::pair<mint, mint> composition(std::pair<mint, mint> f, std::pair<mint,\
    \ mint> g) {\n    return { f.first * g.first, f.first * g.second + f.second };\n\
    }\nstd::pair<mint, mint> id() {\n    return { 1, 0 };\n}\nusing Segtree = suisen::DualSegmentTree<mint,\
    \ std::pair<mint, mint>, mapping, composition, id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<mint>\
    \ a(n);\n    for (auto &e : a) {\n        int v;\n        std::cin >> v;\n   \
    \     e = v;\n    }\n\n    Segtree seg(a);\n    while (q --> 0) {\n        int\
    \ query_type;\n        std::cin >> query_type;\n        if (query_type == 0) {\n\
    \            int l, r, b, c;\n            std::cin >> l >> r >> b >> c;\n    \
    \        seg.apply(l, r, { b, c });\n        } else {\n            int x;\n  \
    \          std::cin >> x;\n            std::cout << seg.get(x).val() << '\\n';\n\
    \        }\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\n\nmint\
    \ mapping(std::pair<mint, mint> f, mint x) {\n    return f.first * x + f.second;\n\
    }\nstd::pair<mint, mint> composition(std::pair<mint, mint> f, std::pair<mint,\
    \ mint> g) {\n    return { f.first * g.first, f.first * g.second + f.second };\n\
    }\nstd::pair<mint, mint> id() {\n    return { 1, 0 };\n}\nusing Segtree = suisen::DualSegmentTree<mint,\
    \ std::pair<mint, mint>, mapping, composition, id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<mint>\
    \ a(n);\n    for (auto &e : a) {\n        int v;\n        std::cin >> v;\n   \
    \     e = v;\n    }\n\n    Segtree seg(a);\n    while (q --> 0) {\n        int\
    \ query_type;\n        std::cin >> query_type;\n        if (query_type == 0) {\n\
    \            int l, r, b, c;\n            std::cin >> l >> r >> b >> c;\n    \
    \        seg.apply(l, r, { b, c });\n        } else {\n            int x;\n  \
    \          std::cin >> x;\n            std::cout << seg.get(x).val() << '\\n';\n\
    \        }\n    }\n\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/dual_segment_tree.hpp
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 10:47:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp.html
title: test/src/datastructure/segment_tree/dual_segment_tree/range_affine_point_get.test.cpp
---
