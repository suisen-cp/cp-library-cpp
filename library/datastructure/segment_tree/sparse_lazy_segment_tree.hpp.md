---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
    title: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
    title: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <vector>\n\nnamespace suisen\
    \ {\n    template <\n        typename IndexType,                      // type\
    \ of index (integral: bool, long long, etc.)\n        typename T,            \
    \                  // type of element\n        T(*op)(T, T),                 \
    \           // type of binary operator on T\n        T(*e)(),                \
    \                 //\n        typename F,                              // type\
    \ of operator which acts on T\n        T(*mapping)(F, T, IndexType, IndexType),\
    \ // type of action F on T\n        F(*composition)(F, F),                   //\
    \ type of binary operator on F\n        F(*id)(),                            \
    \    //\n        T(*init)(IndexType, IndexType)           // type of function\
    \ which initializes product of segment [l, r)\n    >\n    struct SparseLazySegmentTree\
    \ {\n        using index_type = IndexType;\n        using value_type = T;\n  \
    \      using operator_type = F;\n    private:\n        using pool_index_type =\
    \ uint32_t;\n\n        struct Node {\n            pool_index_type ch[2]{ 0, 0\
    \ };\n            value_type dat;\n            operator_type laz;\n          \
    \  Node(const value_type& dat) : dat(dat), laz(id()) {}\n        };\n\n      \
    \  static inline std::vector<Node> pool{ Node{ e() } };\n\n        static pool_index_type\
    \ new_node(const value_type& dat) {\n            const pool_index_type res = pool.size();\n\
    \            return pool.emplace_back(dat), res;\n        }\n    public:\n   \
    \     SparseLazySegmentTree() : SparseLazySegmentTree(0) {}\n        explicit\
    \ SparseLazySegmentTree(IndexType n) : n(n), root(new_node(init(0, n))) {}\n\n\
    \        static void reserve(int siz) {\n            pool.reserve(siz);\n    \
    \    }\n\n        value_type get(index_type i) const {\n            assert(0 <=\
    \ i and i < n);\n            operator_type f = id();\n            pool_index_type\
    \ cur = root;\n            for (std::array<index_type, 2> lr { 0, n }; cur and\
    \ lr[1] - lr[0] > 1;) {\n                index_type m = (lr[0] + lr[1]) >> 1;\n\
    \                bool b = i >= m;\n                f = composition(f, pool[cur].laz);\n\
    \                cur = pool[cur].ch[b], lr[not b] = m;\n            }\n      \
    \      return mapping(f, cur ? pool[cur].dat : init(i, i + 1), i, i + 1);\n  \
    \      }\n        template <typename Fun>\n        void apply_fun(index_type i,\
    \ Fun &&fun) {\n            assert(0 <= i and i < n);\n            static std::vector<pool_index_type>\
    \ path;\n            pool_index_type cur = root;\n            for (std::array<index_type,\
    \ 2> lr { 0, n }; lr[1] - lr[0] > 1;) {\n                path.push_back(cur);\n\
    \                index_type m = (lr[0] + lr[1]) >> 1;\n                bool b\
    \ = i >= m;\n                push(cur);\n                cur = pool[cur].ch[b],\
    \ lr[not b] = m;\n            }\n            pool[cur].dat = fun(pool[cur].dat);\n\
    \            while (path.size()) update(path.back()), path.pop_back();\n     \
    \   }\n        void set(index_type i, const value_type& val) {\n            apply_fun(i,\
    \ [&val](const value_type&) { return val; });\n        }\n        void apply(index_type\
    \ i, const operator_type& f) {\n            apply_fun(i, [&f, i](const value_type&\
    \ val) { return mapping(f, val, i, i + 1); });\n        }\n\n        value_type\
    \ operator()(index_type l, index_type r) {\n            assert(0 <= l and l <=\
    \ r and r <= n);\n            return query(root, l, r, 0, n);\n        }\n   \
    \     value_type prod(index_type l, index_type r) {\n            return (*this)(l,\
    \ r);\n        }\n        value_type prod_all() {\n            return pool[root].dat;\n\
    \        }\n\n        void apply(index_type l, index_type r, const operator_type&\
    \ f) {\n            assert(0 <= l and l <= r and r <= n);\n            apply(root,\
    \ f, l, r, 0, n);\n        }\n        void apply_all(const operator_type& f) {\n\
    \            apply_all(root, f, 0, n);\n        }\n\n    private:\n        index_type\
    \ n;\n        pool_index_type root;\n\n        pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl, index_type tr) {\n            if (pool[node].ch[index])\
    \ return pool[node].ch[index];\n            const pool_index_type ch = new_node(init(tl,\
    \ tr));\n            return pool[node].ch[index] = ch;\n        }\n\n        void\
    \ apply_all(pool_index_type node, const operator_type& f, index_type tl, index_type\
    \ tr) {\n            pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n  \
    \          pool[node].laz = composition(f, pool[node].laz);\n        }\n     \
    \   void push(pool_index_type node, index_type tl, index_type tr) {\n        \
    \    const index_type tm = (tl + tr) >> 1;\n            const operator_type laz\
    \ = pool[node].laz;\n            apply_all(get_or_create_child(node, 0, tl, tm),\
    \ laz, tl, tm);\n            apply_all(get_or_create_child(node, 1, tm, tr), laz,\
    \ tm, tr);\n            pool[node].laz = id();\n        }\n\n        void update(pool_index_type\
    \ node) {\n            pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \            pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n        }\n\n\
    \        value_type query(pool_index_type node, index_type ql, index_type qr,\
    \ index_type tl, index_type tr) {\n            if (tr <= ql or qr <= tl) return\
    \ e();\n            if (ql <= tl and tr <= qr) return pool[node].dat;\n      \
    \      push(node, tl, tr);\n            const index_type tm = (tl + tr) >> 1;\n\
    \            return op(query(pool[node].ch[0], ql, qr, tl, tm), query(pool[node].ch[1],\
    \ ql, qr, tm, tr));\n        }\n\n        void apply(pool_index_type node, const\
    \ operator_type& f, index_type ql, index_type qr, index_type tl, index_type tr)\
    \ {\n            if (tr <= ql or qr <= tl) return;\n            if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f, tl, tr);\n            const index_type tm\
    \ = (tl + tr) >> 1;\n            push(node, tl, tr);\n            apply(pool[node].ch[0],\
    \ f, ql, qr, tl, tm), apply(pool[node].ch[1], f, ql, qr, tm, tr);\n          \
    \  update(node);\n        }\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_SPARSE_LAZY_SEGTREE\n#define SUISEN_SPARSE_LAZY_SEGTREE\n\n\
    #include <array>\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n\
    \    template <\n        typename IndexType,                      // type of index\
    \ (integral: bool, long long, etc.)\n        typename T,                     \
    \         // type of element\n        T(*op)(T, T),                          \
    \  // type of binary operator on T\n        T(*e)(),                         \
    \        //\n        typename F,                              // type of operator\
    \ which acts on T\n        T(*mapping)(F, T, IndexType, IndexType), // type of\
    \ action F on T\n        F(*composition)(F, F),                   // type of binary\
    \ operator on F\n        F(*id)(),                                //\n       \
    \ T(*init)(IndexType, IndexType)           // type of function which initializes\
    \ product of segment [l, r)\n    >\n    struct SparseLazySegmentTree {\n     \
    \   using index_type = IndexType;\n        using value_type = T;\n        using\
    \ operator_type = F;\n    private:\n        using pool_index_type = uint32_t;\n\
    \n        struct Node {\n            pool_index_type ch[2]{ 0, 0 };\n        \
    \    value_type dat;\n            operator_type laz;\n            Node(const value_type&\
    \ dat) : dat(dat), laz(id()) {}\n        };\n\n        static inline std::vector<Node>\
    \ pool{ Node{ e() } };\n\n        static pool_index_type new_node(const value_type&\
    \ dat) {\n            const pool_index_type res = pool.size();\n            return\
    \ pool.emplace_back(dat), res;\n        }\n    public:\n        SparseLazySegmentTree()\
    \ : SparseLazySegmentTree(0) {}\n        explicit SparseLazySegmentTree(IndexType\
    \ n) : n(n), root(new_node(init(0, n))) {}\n\n        static void reserve(int\
    \ siz) {\n            pool.reserve(siz);\n        }\n\n        value_type get(index_type\
    \ i) const {\n            assert(0 <= i and i < n);\n            operator_type\
    \ f = id();\n            pool_index_type cur = root;\n            for (std::array<index_type,\
    \ 2> lr { 0, n }; cur and lr[1] - lr[0] > 1;) {\n                index_type m\
    \ = (lr[0] + lr[1]) >> 1;\n                bool b = i >= m;\n                f\
    \ = composition(f, pool[cur].laz);\n                cur = pool[cur].ch[b], lr[not\
    \ b] = m;\n            }\n            return mapping(f, cur ? pool[cur].dat :\
    \ init(i, i + 1), i, i + 1);\n        }\n        template <typename Fun>\n   \
    \     void apply_fun(index_type i, Fun &&fun) {\n            assert(0 <= i and\
    \ i < n);\n            static std::vector<pool_index_type> path;\n           \
    \ pool_index_type cur = root;\n            for (std::array<index_type, 2> lr {\
    \ 0, n }; lr[1] - lr[0] > 1;) {\n                path.push_back(cur);\n      \
    \          index_type m = (lr[0] + lr[1]) >> 1;\n                bool b = i >=\
    \ m;\n                push(cur);\n                cur = pool[cur].ch[b], lr[not\
    \ b] = m;\n            }\n            pool[cur].dat = fun(pool[cur].dat);\n  \
    \          while (path.size()) update(path.back()), path.pop_back();\n       \
    \ }\n        void set(index_type i, const value_type& val) {\n            apply_fun(i,\
    \ [&val](const value_type&) { return val; });\n        }\n        void apply(index_type\
    \ i, const operator_type& f) {\n            apply_fun(i, [&f, i](const value_type&\
    \ val) { return mapping(f, val, i, i + 1); });\n        }\n\n        value_type\
    \ operator()(index_type l, index_type r) {\n            assert(0 <= l and l <=\
    \ r and r <= n);\n            return query(root, l, r, 0, n);\n        }\n   \
    \     value_type prod(index_type l, index_type r) {\n            return (*this)(l,\
    \ r);\n        }\n        value_type prod_all() {\n            return pool[root].dat;\n\
    \        }\n\n        void apply(index_type l, index_type r, const operator_type&\
    \ f) {\n            assert(0 <= l and l <= r and r <= n);\n            apply(root,\
    \ f, l, r, 0, n);\n        }\n        void apply_all(const operator_type& f) {\n\
    \            apply_all(root, f, 0, n);\n        }\n\n    private:\n        index_type\
    \ n;\n        pool_index_type root;\n\n        pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl, index_type tr) {\n            if (pool[node].ch[index])\
    \ return pool[node].ch[index];\n            const pool_index_type ch = new_node(init(tl,\
    \ tr));\n            return pool[node].ch[index] = ch;\n        }\n\n        void\
    \ apply_all(pool_index_type node, const operator_type& f, index_type tl, index_type\
    \ tr) {\n            pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n  \
    \          pool[node].laz = composition(f, pool[node].laz);\n        }\n     \
    \   void push(pool_index_type node, index_type tl, index_type tr) {\n        \
    \    const index_type tm = (tl + tr) >> 1;\n            const operator_type laz\
    \ = pool[node].laz;\n            apply_all(get_or_create_child(node, 0, tl, tm),\
    \ laz, tl, tm);\n            apply_all(get_or_create_child(node, 1, tm, tr), laz,\
    \ tm, tr);\n            pool[node].laz = id();\n        }\n\n        void update(pool_index_type\
    \ node) {\n            pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \            pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n        }\n\n\
    \        value_type query(pool_index_type node, index_type ql, index_type qr,\
    \ index_type tl, index_type tr) {\n            if (tr <= ql or qr <= tl) return\
    \ e();\n            if (ql <= tl and tr <= qr) return pool[node].dat;\n      \
    \      push(node, tl, tr);\n            const index_type tm = (tl + tr) >> 1;\n\
    \            return op(query(pool[node].ch[0], ql, qr, tl, tm), query(pool[node].ch[1],\
    \ ql, qr, tm, tr));\n        }\n\n        void apply(pool_index_type node, const\
    \ operator_type& f, index_type ql, index_type qr, index_type tl, index_type tr)\
    \ {\n            if (tr <= ql or qr <= tl) return;\n            if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f, tl, tr);\n            const index_type tm\
    \ = (tl + tr) >> 1;\n            push(node, tl, tr);\n            apply(pool[node].ch[0],\
    \ f, ql, qr, tl, tm), apply(pool[node].ch[1], f, ql, qr, tm, tr);\n          \
    \  update(node);\n        }\n    };\n}\n\n#endif // SUISEN_SPARSE_LAZY_SEGTREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-06-14 00:05:08+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
  - test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
documentation_of: library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
layout: document
title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u6DFB\u5B57\
  \u96C6\u5408\u304C\u758E\u306A\u5834\u5408)"
---
## 遅延伝播セグメント木 (添字集合が疎な場合)

予め添字集合が分かっている場合は座標圧縮により通常の遅延伝播セグメント木で対応できるが、そうでない場合は本ライブラリを用いる。
