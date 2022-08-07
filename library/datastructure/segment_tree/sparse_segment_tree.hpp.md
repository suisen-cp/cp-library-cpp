---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/sparse_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    namespace\
    \ internal::sparse_segtree {\n        template <typename IndexType, typename T,\
    \ T(*e)()>\n        T default_init(IndexType, IndexType) { return e(); }\n   \
    \ }\n    template <\n        typename IndexType, // type of index\n        typename\
    \ T,         // type of element\n        T(*op)(T, T),       // (x, y) -> x *\
    \ y\n        T(*e)(),            // () -> identity\n        // (l, r) -> init[l]\
    \ * init[l+1] * ... * init[r-1]\n        T(*init)(IndexType, IndexType) = internal::sparse_segtree::default_init<IndexType,\
    \ T, e>\n    >\n    struct SparseSegmentTree {\n        using index_type = IndexType;\n\
    \        using value_type = T;\n    private:\n        using pool_index_type =\
    \ uint32_t;\n\n        struct Node {\n            pool_index_type ch[2]{ 0, 0\
    \ };\n            value_type dat;\n            Node(const value_type& dat) : dat(dat)\
    \ {}\n        };\n\n        static inline std::vector<Node> pool{ Node{ e() }\
    \ };\n\n        static pool_index_type new_node(const value_type& dat) {\n   \
    \         const pool_index_type res = pool.size();\n            return pool.emplace_back(dat),\
    \ res;\n        }\n    public:\n        SparseSegmentTree() : SparseSegmentTree(0)\
    \ {}\n        explicit SparseSegmentTree(IndexType n) : n(n), root(new_node(init(0,\
    \ n))) {}\n\n        static void reserve(int siz) {\n            pool.reserve(siz);\n\
    \        }\n\n        value_type get(index_type i) const {\n            assert(0\
    \ <= i and i < n);\n            pool_index_type cur = root;\n            for (index_type\
    \ l = 0, r = n; cur and r - l > 1;) {\n                index_type m = (l + r)\
    \ >> 1;\n                if (i < m) cur = pool[cur].ch[0], r = m;\n          \
    \      else       cur = pool[cur].ch[1], l = m;\n            }\n            return\
    \ get(cur, i, i + 1);\n        }\n        template <typename Fun>\n        void\
    \ apply_fun(index_type i, Fun &&fun) {\n            assert(0 <= i and i < n);\n\
    \            auto rec = [&](auto rec, pool_index_type cur, index_type l, index_type\
    \ r) -> void {\n                if (r - l == 1) {\n                    pool[cur].dat\
    \ = fun(get(cur, l, r));\n                    return;\n                }\n   \
    \             const index_type m = (l + r) >> 1;\n                if (i < m) rec(rec,\
    \ get_or_create_child(cur, 0, l, m), l, m);\n                else       rec(rec,\
    \ get_or_create_child(cur, 1, m, r), m, r);\n                pool[cur].dat = op(get(pool[cur].ch[0],\
    \ l, m), get(pool[cur].ch[1], m, r));\n            };\n            rec(rec, root,\
    \ 0, n);\n        }\n        void set(index_type i, const value_type& val) {\n\
    \            apply_fun(i, [&val](const value_type&) { return val; });\n      \
    \  }\n\n        value_type operator()(index_type l, index_type r) const {\n  \
    \          assert(0 <= l and l <= r and r <= n);\n            return query(root,\
    \ l, r, 0, n);\n        }\n        value_type prod(index_type l, index_type r)\
    \ const {\n            return (*this)(l, r);\n        }\n        value_type prod_all()\
    \ const {\n            return pool[root].dat;\n        }\n\n    private:\n   \
    \     index_type n;\n        pool_index_type root;\n\n        value_type get(pool_index_type\
    \ node, index_type tl, index_type tr) const {\n            return node ? pool[node].dat\
    \ : init(tl, tr);\n        }\n\n        pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl, index_type tr) {\n            if (pool[node].ch[index])\
    \ return pool[node].ch[index];\n            const pool_index_type ch = new_node(init(tl,\
    \ tr));\n            return pool[node].ch[index] = ch;\n        }\n\n        value_type\
    \ query(pool_index_type node, index_type ql, index_type qr, index_type tl, index_type\
    \ tr) const {\n            if (tr <= ql or qr <= tl) return e();\n           \
    \ if (not node) return init(std::max(ql, tl), std::min(qr, tr));\n           \
    \ if (ql <= tl and tr <= qr) return pool[node].dat;\n            const index_type\
    \ tm = (tl + tr) >> 1;\n            return op(query(pool[node].ch[0], ql, qr,\
    \ tl, tm), query(pool[node].ch[1], ql, qr, tm, tr));\n        }\n    };\n}\n\n\
    \n"
  code: "#ifndef SUISEN_SPARSE_SEGTREE\n#define SUISEN_SPARSE_SEGTREE\n\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace suisen {\n    namespace internal::sparse_segtree\
    \ {\n        template <typename IndexType, typename T, T(*e)()>\n        T default_init(IndexType,\
    \ IndexType) { return e(); }\n    }\n    template <\n        typename IndexType,\
    \ // type of index\n        typename T,         // type of element\n        T(*op)(T,\
    \ T),       // (x, y) -> x * y\n        T(*e)(),            // () -> identity\n\
    \        // (l, r) -> init[l] * init[l+1] * ... * init[r-1]\n        T(*init)(IndexType,\
    \ IndexType) = internal::sparse_segtree::default_init<IndexType, T, e>\n    >\n\
    \    struct SparseSegmentTree {\n        using index_type = IndexType;\n     \
    \   using value_type = T;\n    private:\n        using pool_index_type = uint32_t;\n\
    \n        struct Node {\n            pool_index_type ch[2]{ 0, 0 };\n        \
    \    value_type dat;\n            Node(const value_type& dat) : dat(dat) {}\n\
    \        };\n\n        static inline std::vector<Node> pool{ Node{ e() } };\n\n\
    \        static pool_index_type new_node(const value_type& dat) {\n          \
    \  const pool_index_type res = pool.size();\n            return pool.emplace_back(dat),\
    \ res;\n        }\n    public:\n        SparseSegmentTree() : SparseSegmentTree(0)\
    \ {}\n        explicit SparseSegmentTree(IndexType n) : n(n), root(new_node(init(0,\
    \ n))) {}\n\n        static void reserve(int siz) {\n            pool.reserve(siz);\n\
    \        }\n\n        value_type get(index_type i) const {\n            assert(0\
    \ <= i and i < n);\n            pool_index_type cur = root;\n            for (index_type\
    \ l = 0, r = n; cur and r - l > 1;) {\n                index_type m = (l + r)\
    \ >> 1;\n                if (i < m) cur = pool[cur].ch[0], r = m;\n          \
    \      else       cur = pool[cur].ch[1], l = m;\n            }\n            return\
    \ get(cur, i, i + 1);\n        }\n        template <typename Fun>\n        void\
    \ apply_fun(index_type i, Fun &&fun) {\n            assert(0 <= i and i < n);\n\
    \            auto rec = [&](auto rec, pool_index_type cur, index_type l, index_type\
    \ r) -> void {\n                if (r - l == 1) {\n                    pool[cur].dat\
    \ = fun(get(cur, l, r));\n                    return;\n                }\n   \
    \             const index_type m = (l + r) >> 1;\n                if (i < m) rec(rec,\
    \ get_or_create_child(cur, 0, l, m), l, m);\n                else       rec(rec,\
    \ get_or_create_child(cur, 1, m, r), m, r);\n                pool[cur].dat = op(get(pool[cur].ch[0],\
    \ l, m), get(pool[cur].ch[1], m, r));\n            };\n            rec(rec, root,\
    \ 0, n);\n        }\n        void set(index_type i, const value_type& val) {\n\
    \            apply_fun(i, [&val](const value_type&) { return val; });\n      \
    \  }\n\n        value_type operator()(index_type l, index_type r) const {\n  \
    \          assert(0 <= l and l <= r and r <= n);\n            return query(root,\
    \ l, r, 0, n);\n        }\n        value_type prod(index_type l, index_type r)\
    \ const {\n            return (*this)(l, r);\n        }\n        value_type prod_all()\
    \ const {\n            return pool[root].dat;\n        }\n\n    private:\n   \
    \     index_type n;\n        pool_index_type root;\n\n        value_type get(pool_index_type\
    \ node, index_type tl, index_type tr) const {\n            return node ? pool[node].dat\
    \ : init(tl, tr);\n        }\n\n        pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl, index_type tr) {\n            if (pool[node].ch[index])\
    \ return pool[node].ch[index];\n            const pool_index_type ch = new_node(init(tl,\
    \ tr));\n            return pool[node].ch[index] = ch;\n        }\n\n        value_type\
    \ query(pool_index_type node, index_type ql, index_type qr, index_type tl, index_type\
    \ tr) const {\n            if (tr <= ql or qr <= tl) return e();\n           \
    \ if (not node) return init(std::max(ql, tl), std::min(qr, tr));\n           \
    \ if (ql <= tl and tr <= qr) return pool[node].dat;\n            const index_type\
    \ tm = (tl + tr) >> 1;\n            return op(query(pool[node].ch[0], ql, qr,\
    \ tl, tm), query(pool[node].ch[1], ql, qr, tm, tr));\n        }\n    };\n}\n\n\
    #endif // SUISEN_SPARSE_SEGTREE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/segment_tree/sparse_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-08-07 21:13:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/segment_tree/sparse_segment_tree.hpp
layout: document
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u6DFB\u5B57\u96C6\u5408\u304C\u758E\
  \u306A\u5834\u5408)"
---
## セグメント木 (添字集合が疎な場合)

予め添字集合が分かっている場合は座標圧縮により通常のセグメント木で対応できるが、そうでない場合は本ライブラリを用いる。
