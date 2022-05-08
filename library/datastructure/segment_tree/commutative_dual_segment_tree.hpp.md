---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
    title: test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/segment_tree/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
    title: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
    title: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/segment_tree/commutative_dual_segment_tree.hpp: line 6:\
    \ unable to process #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_COM_DUAL_SEGTREE\n#define SUISEN_DUAL_SEGTREE\n\n#include\
    \ <cassert>\n#include <vector>\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, typename F, T(*mapping)(F, T),\
    \ F(*composition)(F, F), F(*id)()>\n    struct CommutativeDualSegmentTree {\n\
    \        CommutativeDualSegmentTree() {}\n        CommutativeDualSegmentTree(std::vector<T>&&\
    \ a) : n(a.size()), m(ceil_pow2(a.size())), data(std::move(a)), lazy(m, id())\
    \ {}\n        CommutativeDualSegmentTree(const std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a))\
    \ {}\n        CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n,\
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
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_COM_DUAL_SEGTREE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  requiredBy:
  - library/datastructure/segment_tree/dual_segment_tree.hpp
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
  - test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
  - test/src/datastructure/segment_tree/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
documentation_of: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
layout: document
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u4F5C\u7528\u304C\u53EF\
  \u63DB\u306A\u5834\u5408)"
---
## 双対セグメント木 (作用が可換な場合)

作用の可換性を仮定した場合、作用を伝播させる必要がないため、伝播処理をサボることで定数倍改善を測ることができる。
