---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/commutative_dual_segment_tree.hpp
    title: library/datastructure/commutative_dual_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/dual_segment_tree/DSL_2_D.test.cpp
    title: test/src/datastructure/dual_segment_tree/DSL_2_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
    title: test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/commutative_dual_segment_tree.hpp: line 6: unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_DUAL_SEGTREE\n#define SUISEN_DUAL_SEGTREE\n\n#include \"library/datastructure/commutative_dual_segment_tree.hpp\"\
    \n\nnamespace suisen {\ntemplate <\n    typename T, typename F, typename Mapping,\
    \ typename Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass DualSegmentTree : public CommutativeDualSegmentTree<T, F, Mapping, Composition>\
    \ {\n    using BaseType = CommutativeDualSegmentTree<T, F, Mapping, Composition>;\n\
    \    public:\n        using BaseType::CommutativeDualSegmentTree;\n        void\
    \ apply(int l, int r, const F &f) {\n            assert(0 <= l and r <= this->n);\n\
    \            push(l, r);\n            BaseType::apply(l, r, f);\n        }\n \
    \   private:\n        void push(int k) {\n            if (this->lazy[k] != this->id)\
    \ {\n                BaseType::apply(2 * k, this->lazy[k]), BaseType::apply(2\
    \ * k + 1, this->lazy[k]);\n                this->lazy[k] = this->id;\n      \
    \      }\n        }\n        void push(int l, int r) {\n            const int\
    \ log = __builtin_ctz(this->m);\n            l += this->m, r += this->m;\n   \
    \         for (int i = log; (l >> i) << i != l; --i) push(l >> i);\n         \
    \   for (int i = log; (r >> i) << i != r; --i) push(r >> i);\n        }\n};\n\n\
    template <typename T, typename F, typename Mapping, typename Composition>\nDualSegmentTree(int,\
    \ T, F, Mapping, Composition) -> DualSegmentTree<T, F, Mapping, Composition>;\n\
    \ntemplate <typename T, typename F, typename Mapping, typename Composition>\n\
    DualSegmentTree(std::vector<T>, F, Mapping, Composition) -> DualSegmentTree<T,\
    \ F, Mapping, Composition>;\n\n} // namespace suisen\n\n\n#endif // SUISEN_DUAL_SEGTREE\n"
  dependsOn:
  - library/datastructure/commutative_dual_segment_tree.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
  - test/src/datastructure/dual_segment_tree/DSL_2_D.test.cpp
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
documentation_of: library/datastructure/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/dual_segment_tree.hpp
- /library/library/datastructure/dual_segment_tree.hpp.html
title: library/datastructure/dual_segment_tree.hpp
---
