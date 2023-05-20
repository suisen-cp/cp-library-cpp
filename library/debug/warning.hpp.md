---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
    title: Reversible Implicit Treap Dual Segtree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
    title: Reversible Implicit Treap Lazy Segtree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/debug/warning.hpp\"\n\n\n\n#include <iostream>\n\
    \nnamespace suisen {\n    struct warning {\n        warning(const std::string\
    \ &msg) {\n            std::cerr << \"\\033[33m[WARNING] \" << msg << \"\\033[0m\"\
    \ << std::endl;\n        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_WARNING\n#define SUISEN_WARNING\n\n#include <iostream>\n\n\
    namespace suisen {\n    struct warning {\n        warning(const std::string &msg)\
    \ {\n            std::cerr << \"\\033[33m[WARNING] \" << msg << \"\\033[0m\" <<\
    \ std::endl;\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_WARNING\n"
  dependsOn: []
  isVerificationFile: false
  path: library/debug/warning.hpp
  requiredBy:
  - library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  timestamp: '2023-02-16 17:01:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
documentation_of: library/debug/warning.hpp
layout: document
title: Warning
---
## Warning
