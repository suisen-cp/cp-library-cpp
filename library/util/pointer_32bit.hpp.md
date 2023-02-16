---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap.hpp
    title: library/datastructure/bbst/reversible_implicit_treap.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_base.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_base.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_segtree.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_segtree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap/abc237_d.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap/abc237_d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap/yuki649.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap/yuki649.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_segtree/abc238_f.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_segtree/abc238_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/reversible_implicit_treap_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/reversible_implicit_treap_segtree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/util/pointer_32bit.hpp\"\n\n\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename Object>\n    struct ptr32 {\n   \
    \     static constexpr int null = -1;\n\n        using object_type = Object;\n\
    \        using pool_type = std::vector<object_type>;\n\n        constexpr ptr32()\
    \ : ptr(null) {}\n        explicit constexpr ptr32(int ptr) : ptr(ptr) {}\n\n\
    \        object_type& operator*() const { return pool[ptr]; }\n        object_type*\
    \ operator->() const { return &pool[ptr]; }\n\n        constexpr operator bool()\
    \ const { return ptr != null; }\n        constexpr operator int() const { return\
    \ ptr; }\n\n        constexpr bool is_not_null() const { return bool(*this); }\n\
    \        constexpr bool is_null() const { return not bool(*this); }\n\n      \
    \  friend constexpr bool operator==(const ptr32& l, const ptr32& r) { return l.ptr\
    \ == r.ptr; }\n        friend constexpr bool operator!=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr != r.ptr; }\n        friend constexpr bool operator<(const\
    \ ptr32& l, const ptr32& r) { return l.ptr < r.ptr; }\n        friend constexpr\
    \ bool operator<=(const ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }\n\
    \        friend constexpr bool operator>(const ptr32& l, const ptr32& r) { return\
    \ l.ptr > r.ptr; }\n        friend constexpr bool operator>=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr >= r.ptr; }\n\n        template <typename ...Args>\n\
    \        static ptr32 alloc(Args &&...args) {\n            if (del.size()) {\n\
    \                ptr32 ptr(del.back());\n                del.pop_back();\n   \
    \             *ptr = object_type(std::forward<Args>(args)...);\n             \
    \   return ptr;\n            } else {\n                ptr32 ptr(pool.size());\n\
    \                pool.emplace_back(std::forward<Args>(args)...);\n           \
    \     return ptr;\n            }\n        }\n        static void dealloc(ptr32\
    \ p) {\n            del.push_back(p);\n        }\n        static void dealloc_all(bool\
    \ shrink) {\n            pool.clear(), del.clear();\n            if (shrink) pool.shrink_to_fit(),\
    \ del.shrink_to_fit();\n        }\n        static void reserve(size_t capacity)\
    \ {\n            pool.reserve(capacity);\n        }\n    private:\n        static\
    \ inline pool_type pool{};\n        static inline std::vector<ptr32> del{};\n\n\
    \        int ptr;\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_32BIT_POINTER\n#define SUISEN_32BIT_POINTER\n\n#include <vector>\n\
    \nnamespace suisen {\n    template <typename Object>\n    struct ptr32 {\n   \
    \     static constexpr int null = -1;\n\n        using object_type = Object;\n\
    \        using pool_type = std::vector<object_type>;\n\n        constexpr ptr32()\
    \ : ptr(null) {}\n        explicit constexpr ptr32(int ptr) : ptr(ptr) {}\n\n\
    \        object_type& operator*() const { return pool[ptr]; }\n        object_type*\
    \ operator->() const { return &pool[ptr]; }\n\n        constexpr operator bool()\
    \ const { return ptr != null; }\n        constexpr operator int() const { return\
    \ ptr; }\n\n        constexpr bool is_not_null() const { return bool(*this); }\n\
    \        constexpr bool is_null() const { return not bool(*this); }\n\n      \
    \  friend constexpr bool operator==(const ptr32& l, const ptr32& r) { return l.ptr\
    \ == r.ptr; }\n        friend constexpr bool operator!=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr != r.ptr; }\n        friend constexpr bool operator<(const\
    \ ptr32& l, const ptr32& r) { return l.ptr < r.ptr; }\n        friend constexpr\
    \ bool operator<=(const ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }\n\
    \        friend constexpr bool operator>(const ptr32& l, const ptr32& r) { return\
    \ l.ptr > r.ptr; }\n        friend constexpr bool operator>=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr >= r.ptr; }\n\n        template <typename ...Args>\n\
    \        static ptr32 alloc(Args &&...args) {\n            if (del.size()) {\n\
    \                ptr32 ptr(del.back());\n                del.pop_back();\n   \
    \             *ptr = object_type(std::forward<Args>(args)...);\n             \
    \   return ptr;\n            } else {\n                ptr32 ptr(pool.size());\n\
    \                pool.emplace_back(std::forward<Args>(args)...);\n           \
    \     return ptr;\n            }\n        }\n        static void dealloc(ptr32\
    \ p) {\n            del.push_back(p);\n        }\n        static void dealloc_all(bool\
    \ shrink) {\n            pool.clear(), del.clear();\n            if (shrink) pool.shrink_to_fit(),\
    \ del.shrink_to_fit();\n        }\n        static void reserve(size_t capacity)\
    \ {\n            pool.reserve(capacity);\n        }\n    private:\n        static\
    \ inline pool_type pool{};\n        static inline std::vector<ptr32> del{};\n\n\
    \        int ptr;\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_32BIT_POINTER\n"
  dependsOn: []
  isVerificationFile: false
  path: library/util/pointer_32bit.hpp
  requiredBy:
  - library/datastructure/bbst/reversible_implicit_treap_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap.hpp
  - library/datastructure/bbst/reversible_implicit_treap_base.hpp
  timestamp: '2023-02-16 17:36:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap/dummy.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap/yuki649.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap/abc237_d.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_segtree/abc238_f.test.cpp
  - test/src/datastructure/bbst/reversible_implicit_treap_segtree/dummy.test.cpp
documentation_of: library/util/pointer_32bit.hpp
layout: document
redirect_from:
- /library/library/util/pointer_32bit.hpp
- /library/library/util/pointer_32bit.hpp.html
title: library/util/pointer_32bit.hpp
---
