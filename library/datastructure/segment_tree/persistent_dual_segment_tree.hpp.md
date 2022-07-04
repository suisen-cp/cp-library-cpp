---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/persistent_dual_segment_tree/abc253.test.cpp
    title: test/src/datastructure/segment_tree/persistent_dual_segment_tree/abc253.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/persistent_dual_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n\
    #include <deque>\n#include <vector>\n\nnamespace suisen {\n    template <typename\
    \ T, bool auto_extend = false>\n    struct ObjectPool {\n        using value_type\
    \ = T;\n        using value_pointer_type = T*;\n\n        template <typename U>\n\
    \        using container_type = std::conditional_t<auto_extend, std::deque<U>,\
    \ std::vector<U>>;\n\n        container_type<value_type> pool;\n        container_type<value_pointer_type>\
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
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/segment_tree/persistent_dual_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename F, F(*composition)(F, F), F(*id)()>\n\
    \    struct PersistentDualSegmentTree {\n        struct Node;\n\n        using\
    \ operator_type = F;\n\n        using node_type = Node;\n        using node_pointer_type\
    \ = node_type*;\n\n        struct Node {\n            static inline ObjectPool<node_type>\
    \ _pool;\n\n            node_pointer_type _ch[2]{ nullptr, nullptr };\n      \
    \      operator_type _laz;\n\n            Node() : _laz(id()) {}\n\n         \
    \   static node_pointer_type clone(node_pointer_type node) {\n               \
    \ return &(*_pool.alloc() = *node);\n            }\n\n            template <bool\
    \ do_clone = true>\n            static auto push(node_pointer_type node) {\n \
    \               node_pointer_type res = node;\n                if (not is_leaf(res))\
    \ {\n                    if constexpr (do_clone) res = clone(res);\n         \
    \           res->_ch[0] = apply_all(res->_ch[0], res->_laz);\n               \
    \     res->_ch[1] = apply_all(res->_ch[1], res->_laz);\n                    res->_laz\
    \ = id();\n                }\n                if constexpr (do_clone) {\n    \
    \                return res;\n                } else {\n                    return;\n\
    \                }\n            }\n\n            static bool is_leaf(node_pointer_type\
    \ node) {\n                return not node->_ch[0];\n            }\n\n       \
    \     static node_pointer_type build(const int n) {\n                auto rec\
    \ = [&](auto rec, int l, int r) -> node_pointer_type {\n                    node_pointer_type\
    \ res = _pool.alloc();\n                    res->_laz = id();\n              \
    \      if (r - l > 1) {\n                        int m = (l + r) >> 1;\n     \
    \                   res->_ch[0] = rec(rec, l, m), res->_ch[1] = rec(rec, m, r);\n\
    \                    }\n                    return res;\n                };\n\
    \                return rec(rec, 0, n);\n            }\n\n            static node_pointer_type\
    \ apply_all(node_pointer_type node, const operator_type& f) {\n              \
    \  if (not node) return nullptr;\n                node_pointer_type res = clone(node);\n\
    \                res->_laz = composition(f, res->_laz);\n                return\
    \ res;\n            }\n            static node_pointer_type apply(node_pointer_type\
    \ node, int tl, int tr, int ql, int qr, const operator_type& f) {\n          \
    \      if (tr <= ql or qr <= tl) return node;\n                if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f);\n                node_pointer_type res\
    \ = push(node);\n                int tm = (tl + tr) >> 1;\n                res->_ch[0]\
    \ = apply(res->_ch[0], tl, tm, ql, qr, f);\n                res->_ch[1] = apply(res->_ch[1],\
    \ tm, tr, ql, qr, f);\n                return res;\n            }\n\n        \
    \    static operator_type get(node_pointer_type node, int siz, int i) {\n    \
    \            operator_type f = id();\n                node_pointer_type cur =\
    \ node;\n                for (int l = 0, r = siz; r - l > 1;) {\n            \
    \        f = composition(f, cur->_laz);\n                    int m = (l + r) >>\
    \ 1;\n                    if (i < m) {\n                        cur = cur->_ch[0];\n\
    \                        r = m;\n                    } else {\n              \
    \          cur = cur->_ch[1];\n                        l = m;\n              \
    \      }\n                }\n                return composition(f, cur->_laz);\n\
    \            }\n        };\n\n        PersistentDualSegmentTree() : _n(0), _root(nullptr)\
    \ {}\n        explicit PersistentDualSegmentTree(int n) : _n(n), _root(node_type::build(n))\
    \ {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        PersistentDualSegmentTree\
    \ apply_all(const operator_type& f) {\n            return PersistentDualSegmentTree(_n,\
    \ node_type::apply_all(_root, f));\n        }\n        PersistentDualSegmentTree\
    \ apply(int l, int r, const operator_type& f) {\n            return PersistentDualSegmentTree(_n,\
    \ node_type::apply(_root, 0, _n, l, r, f));\n        }\n\n        operator_type\
    \ get(int i) {\n            assert(0 <= i and i < _n);\n            return node_type::get(_root,\
    \ _n, i);\n        }\n        operator_type operator[](int i) {\n            return\
    \ get(i);\n        }\n\n    private:\n        int _n;\n        node_pointer_type\
    \ _root;\n        PersistentDualSegmentTree(int n, node_pointer_type root) : _n(n),\
    \ _root(root) {}\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_PERSISTENT_DUAL_SEGMENT_TREE\n#define SUISEN_PERSISTENT_DUAL_SEGMENT_TREE\n\
    \n#include <cassert>\n\n#include \"library/util/object_pool.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename F, F(*composition)(F, F), F(*id)()>\n    struct\
    \ PersistentDualSegmentTree {\n        struct Node;\n\n        using operator_type\
    \ = F;\n\n        using node_type = Node;\n        using node_pointer_type = node_type*;\n\
    \n        struct Node {\n            static inline ObjectPool<node_type> _pool;\n\
    \n            node_pointer_type _ch[2]{ nullptr, nullptr };\n            operator_type\
    \ _laz;\n\n            Node() : _laz(id()) {}\n\n            static node_pointer_type\
    \ clone(node_pointer_type node) {\n                return &(*_pool.alloc() = *node);\n\
    \            }\n\n            template <bool do_clone = true>\n            static\
    \ auto push(node_pointer_type node) {\n                node_pointer_type res =\
    \ node;\n                if (not is_leaf(res)) {\n                    if constexpr\
    \ (do_clone) res = clone(res);\n                    res->_ch[0] = apply_all(res->_ch[0],\
    \ res->_laz);\n                    res->_ch[1] = apply_all(res->_ch[1], res->_laz);\n\
    \                    res->_laz = id();\n                }\n                if\
    \ constexpr (do_clone) {\n                    return res;\n                } else\
    \ {\n                    return;\n                }\n            }\n\n       \
    \     static bool is_leaf(node_pointer_type node) {\n                return not\
    \ node->_ch[0];\n            }\n\n            static node_pointer_type build(const\
    \ int n) {\n                auto rec = [&](auto rec, int l, int r) -> node_pointer_type\
    \ {\n                    node_pointer_type res = _pool.alloc();\n            \
    \        res->_laz = id();\n                    if (r - l > 1) {\n           \
    \             int m = (l + r) >> 1;\n                        res->_ch[0] = rec(rec,\
    \ l, m), res->_ch[1] = rec(rec, m, r);\n                    }\n              \
    \      return res;\n                };\n                return rec(rec, 0, n);\n\
    \            }\n\n            static node_pointer_type apply_all(node_pointer_type\
    \ node, const operator_type& f) {\n                if (not node) return nullptr;\n\
    \                node_pointer_type res = clone(node);\n                res->_laz\
    \ = composition(f, res->_laz);\n                return res;\n            }\n \
    \           static node_pointer_type apply(node_pointer_type node, int tl, int\
    \ tr, int ql, int qr, const operator_type& f) {\n                if (tr <= ql\
    \ or qr <= tl) return node;\n                if (ql <= tl and tr <= qr) return\
    \ apply_all(node, f);\n                node_pointer_type res = push(node);\n \
    \               int tm = (tl + tr) >> 1;\n                res->_ch[0] = apply(res->_ch[0],\
    \ tl, tm, ql, qr, f);\n                res->_ch[1] = apply(res->_ch[1], tm, tr,\
    \ ql, qr, f);\n                return res;\n            }\n\n            static\
    \ operator_type get(node_pointer_type node, int siz, int i) {\n              \
    \  operator_type f = id();\n                node_pointer_type cur = node;\n  \
    \              for (int l = 0, r = siz; r - l > 1;) {\n                    f =\
    \ composition(f, cur->_laz);\n                    int m = (l + r) >> 1;\n    \
    \                if (i < m) {\n                        cur = cur->_ch[0];\n  \
    \                      r = m;\n                    } else {\n                \
    \        cur = cur->_ch[1];\n                        l = m;\n                \
    \    }\n                }\n                return composition(f, cur->_laz);\n\
    \            }\n        };\n\n        PersistentDualSegmentTree() : _n(0), _root(nullptr)\
    \ {}\n        explicit PersistentDualSegmentTree(int n) : _n(n), _root(node_type::build(n))\
    \ {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        PersistentDualSegmentTree\
    \ apply_all(const operator_type& f) {\n            return PersistentDualSegmentTree(_n,\
    \ node_type::apply_all(_root, f));\n        }\n        PersistentDualSegmentTree\
    \ apply(int l, int r, const operator_type& f) {\n            return PersistentDualSegmentTree(_n,\
    \ node_type::apply(_root, 0, _n, l, r, f));\n        }\n\n        operator_type\
    \ get(int i) {\n            assert(0 <= i and i < _n);\n            return node_type::get(_root,\
    \ _n, i);\n        }\n        operator_type operator[](int i) {\n            return\
    \ get(i);\n        }\n\n    private:\n        int _n;\n        node_pointer_type\
    \ _root;\n        PersistentDualSegmentTree(int n, node_pointer_type root) : _n(n),\
    \ _root(root) {}\n    };\n}\n\n#endif // SUISEN_PERSISTENT_DUAL_SEGMENT_TREE\n"
  dependsOn:
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/persistent_dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-05-29 02:47:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/persistent_dual_segment_tree/abc253.test.cpp
documentation_of: library/datastructure/segment_tree/persistent_dual_segment_tree.hpp
layout: document
title: Persistent Dual Segment Tree
---
## Persistent Dual Segment Tree