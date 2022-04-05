---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: library/datastructure/bbst/persistent_red_black_lazy_segment_tree.hpp
    title: Persistent Red Black Lazy Segment Tree
  - icon: ':warning:'
    path: library/datastructure/bbst/persistent_red_black_reversible_lazy_segment_tree.hpp
    title: Persistent Red Black Reversible Lazy Segment Tree
  - icon: ':warning:'
    path: library/datastructure/bbst/persistent_red_black_segment_tree.hpp
    title: Persistent Red Black Segment Tree
  - icon: ':warning:'
    path: library/datastructure/bbst/persistent_red_black_tree.hpp
    title: Persistent Red Black Tree
  - icon: ':warning:'
    path: library/datastructure/bbst/persistent_red_black_tree_base.hpp
    title: Persistent Red Black Tree Base
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_lazy_segment_tree.hpp
    title: Red Black Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_reversible_lazy_segment_tree.hpp
    title: Red Black Reversible Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_segment_tree.hpp
    title: Red Black Segment Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_tree.hpp
    title: Red Black Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/red_black_tree_base.hpp
    title: Red Black Tree Base
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
    title: Persistent Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/persistent_segment_tree.hpp
    title: Persistent Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/red_black_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/red_black_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/red_black_reversible_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/red_black_reversible_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
    title: test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/red_black_tree/abc237_d.test.cpp
    title: test/src/datastructure/bbst/red_black_tree/abc237_d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
    title: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/persistent_segment_tree/dummy.test.cpp
    title: test/src/datastructure/segment_tree/persistent_segment_tree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include <deque>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, bool auto_extend\
    \ = false>\n    struct ObjectPool {\n        using value_type = T;\n        using\
    \ value_pointer_type = T*;\n\n        template <typename U>\n        using container_type\
    \ = std::conditional_t<auto_extend, std::deque<U>, std::vector<U>>;\n\n      \
    \  container_type<value_type> pool;\n        container_type<value_pointer_type>\
    \ stock;\n        decltype(stock.begin()) it;\n\n        ObjectPool() : ObjectPool(0)\
    \ {}\n        ObjectPool(int siz) : pool(siz), stock(siz) {\n            clear();\n\
    \        }\n\n        int capacity() const { return pool.size(); }\n        int\
    \ size() const { return it - stock.begin(); }\n\n        value_pointer_type alloc()\
    \ {\n            if constexpr (auto_extend) ensure();\n            return *it++;\n\
    \        }\n\n        void free(value_pointer_type t) {\n            *--it = t;\n\
    \        }\n\n        void clear() {\n            int siz = pool.size();\n   \
    \         it = stock.begin();\n            for (int i = 0; i < siz; i++) stock[i]\
    \ = &pool[i];\n        }\n\n        void ensure() {\n            if (it != stock.end())\
    \ return;\n            int siz = stock.size();\n            for (int i = siz;\
    \ i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n\n"
  code: "#ifndef SUISEN_OBJECT_POOL\n#define SUISEN_OBJECT_POOL\n\n#include <deque>\n\
    #include <vector>\n\nnamespace suisen {\n    template <typename T, bool auto_extend\
    \ = false>\n    struct ObjectPool {\n        using value_type = T;\n        using\
    \ value_pointer_type = T*;\n\n        template <typename U>\n        using container_type\
    \ = std::conditional_t<auto_extend, std::deque<U>, std::vector<U>>;\n\n      \
    \  container_type<value_type> pool;\n        container_type<value_pointer_type>\
    \ stock;\n        decltype(stock.begin()) it;\n\n        ObjectPool() : ObjectPool(0)\
    \ {}\n        ObjectPool(int siz) : pool(siz), stock(siz) {\n            clear();\n\
    \        }\n\n        int capacity() const { return pool.size(); }\n        int\
    \ size() const { return it - stock.begin(); }\n\n        value_pointer_type alloc()\
    \ {\n            if constexpr (auto_extend) ensure();\n            return *it++;\n\
    \        }\n\n        void free(value_pointer_type t) {\n            *--it = t;\n\
    \        }\n\n        void clear() {\n            int siz = pool.size();\n   \
    \         it = stock.begin();\n            for (int i = 0; i < siz; i++) stock[i]\
    \ = &pool[i];\n        }\n\n        void ensure() {\n            if (it != stock.end())\
    \ return;\n            int siz = stock.size();\n            for (int i = siz;\
    \ i <= siz * 2; ++i) {\n                stock.push_back(&pool.emplace_back());\n\
    \            }\n            it = stock.begin() + siz;\n        }\n    };\n} //\
    \ namespace suisen\n\n#endif // SUISEN_OBJECT_POOL\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/object_pool.hpp
  requiredBy:
  - library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
  - library/datastructure/segment_tree/persistent_segment_tree.hpp
  - library/datastructure/bbst/persistent_red_black_lazy_segment_tree.hpp
  - library/datastructure/bbst/red_black_tree.hpp
  - library/datastructure/bbst/red_black_tree_base.hpp
  - library/datastructure/bbst/red_black_reversible_lazy_segment_tree.hpp
  - library/datastructure/bbst/persistent_red_black_reversible_lazy_segment_tree.hpp
  - library/datastructure/bbst/persistent_red_black_segment_tree.hpp
  - library/datastructure/bbst/persistent_red_black_tree.hpp
  - library/datastructure/bbst/red_black_segment_tree.hpp
  - library/datastructure/bbst/red_black_lazy_segment_tree.hpp
  - library/datastructure/bbst/persistent_red_black_tree_base.hpp
  timestamp: '2022-02-13 16:56:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/persistent_segment_tree/dummy.test.cpp
  - test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
  - test/src/datastructure/bbst/red_black_reversible_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/bbst/red_black_tree/abc237_d.test.cpp
  - test/src/datastructure/bbst/red_black_segment_tree/abc238_f.test.cpp
  - test/src/datastructure/bbst/red_black_lazy_segment_tree/dynamic_sequence_range_affine_range_sum.test.cpp
documentation_of: library/util/object_pool.hpp
layout: document
title: Object Pool
---
## Object Pool