---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: Commutative Dual Segment Tree
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/segment_tree/commutative_dual_segment_tree.hpp: line 6:\
    \ unable to process #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_DUAL_SEGTREE\n#define SUISEN_DUAL_SEGTREE\n\n#include \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
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
    \ F, mapping, composition, id>;\n} // namespace suisen\n\n\n#endif // SUISEN_DUAL_SEGTREE\n"
  dependsOn:
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-02-25 23:20:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
  - test/src/datastructure/segment_tree/dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_E.test.cpp
documentation_of: library/datastructure/segment_tree/dual_segment_tree.hpp
layout: document
title: Dual Segment Tree
---
## Dual Segment Tree