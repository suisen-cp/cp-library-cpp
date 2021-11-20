---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/dual_segment_tree.hpp
    title: library/datastructure/dual_segment_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/commutative_dual_segment_tree/DSL_2_E.test.cpp
    title: test/src/datastructure/commutative_dual_segment_tree/DSL_2_E.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
    title: test/src/datastructure/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ library/datastructure/commutative_dual_segment_tree.hpp: line 6: unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifndef SUISEN_COM_DUAL_SEGTREE\n#define SUISEN_DUAL_SEGTREE\n\n#include\
    \ <cassert>\n#include <vector>\n#include \"library/type_traits/type_traits.hpp\"\
    \n\nnamespace suisen {\ntemplate <\n    typename T, typename F, typename Mapping,\
    \ typename Composition,\n    constraints_t<std::is_same<T, std::invoke_result_t<Mapping,\
    \ F, T>>, std::is_same<F, std::invoke_result_t<Composition, F, F>>> = nullptr\n\
    >\nclass CommutativeDualSegmentTree {\n    public:\n        CommutativeDualSegmentTree()\
    \ {}\n        CommutativeDualSegmentTree(int n, const T &fill_value, const F &id,\
    \ Mapping mapping, Composition composition) :\n            n(n), m(ceil_pow2(n)),\
    \ id(id), mapping(mapping), composition(composition), data(n, fill_value), lazy(m,\
    \ id) {}\n        CommutativeDualSegmentTree(std::vector<T> &&a, const F &id,\
    \ Mapping mapping, Composition composition) :\n            n(a.size()), m(ceil_pow2(a.size())),\
    \ id(id), mapping(mapping), composition(composition), data(std::move(a)), lazy(m,\
    \ id) {}\n        CommutativeDualSegmentTree(const std::vector<T> &a, const F\
    \ &id, Mapping mapping, Composition composition) :\n            CommutativeDualSegmentTree(std::vector<T>(a),\
    \ id, mapping, composition) {}\n\n        T operator[](int i) const {\n      \
    \      assert(0 <= i and i < n);\n            T res = data[i];\n            for\
    \ (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);\n            return\
    \ res;\n        }\n        T get(int i) const {\n            return (*this)[i];\n\
    \        }\n        void apply(int l, int r, const F &f) {\n            assert(0\
    \ <= l and r <= n);\n            for (l += m, r += m; l < r; l >>= 1, r >>= 1)\
    \ {\n                if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r,\
    \ f);\n            }\n        }\n    protected:\n        int n, m;\n        F\
    \ id;\n        Mapping mapping;\n        Composition composition;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F &f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n};\n} // namespace suisen\n\n#endif // SUISEN_COM_DUAL_SEGTREE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/commutative_dual_segment_tree.hpp
  requiredBy:
  - library/datastructure/dual_segment_tree.hpp
  timestamp: '2021-09-02 19:44:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/dual_segment_tree/DSL_2_D.test.cpp
  - test/src/datastructure/dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/dual_segment_tree/DSL_2_E.test.cpp
  - test/src/datastructure/commutative_dual_segment_tree/rectilinear_polygons.test.cpp
  - test/src/datastructure/commutative_dual_segment_tree/DSL_2_E.test.cpp
documentation_of: library/datastructure/commutative_dual_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/commutative_dual_segment_tree.hpp
- /library/library/datastructure/commutative_dual_segment_tree.hpp.html
title: library/datastructure/commutative_dual_segment_tree.hpp
---
