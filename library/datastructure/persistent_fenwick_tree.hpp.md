---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/persistent_fenwick_tree/abc253_f.test.cpp
    title: test/src/datastructure/persistent_fenwick_tree/abc253_f.test.cpp
  - icon: ':x:'
    path: test/src/datastructure/persistent_fenwick_tree/rectangle_sum.test.cpp
    title: test/src/datastructure/persistent_fenwick_tree/rectangle_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/persistent_fenwick_tree.hpp\"\n\n\n\
    \n#include <cassert>\n\n#line 1 \"library/util/object_pool.hpp\"\n\n\n\n#include\
    \ <deque>\n#include <vector>\n\nnamespace suisen {\n    template <typename T,\
    \ bool auto_extend = false>\n    struct ObjectPool {\n        using value_type\
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
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/persistent_fenwick_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct PersistentFenwickTree\
    \ {\n        struct Node;\n\n        using value_type = T;\n\n        using node_type\
    \ = Node;\n        using node_pointer_type = node_type*;\n\n        struct Node\
    \ {\n            static inline ObjectPool<node_type> _pool;\n\n            node_pointer_type\
    \ _ch[2]{ nullptr, nullptr };\n            value_type _dat;\n\n            Node()\
    \ : _dat{} {}\n\n            static node_pointer_type clone(node_pointer_type\
    \ node) {\n                return &(*_pool.alloc() = *node);\n            }\n\n\
    \            static node_pointer_type build(const std::vector<value_type> &dat,\
    \ int p) {\n                const int n = dat.size();\n                std::vector<node_pointer_type>\
    \ nodes(n + 1);\n                auto rec = [&](auto rec, int p, int id) -> node_pointer_type\
    \ {\n                    if (p == 0) return nullptr;\n                    const\
    \ int np = p >> 1;\n                    node_pointer_type res = _pool.alloc();\n\
    \                    res->_ch[0] = rec(rec, np, id - np);\n                  \
    \  if (id + 1 <= n) res->_ch[1] = rec(rec, np, id + np);\n                   \
    \ if (id <= n) nodes[id] = res;\n                    return res;\n           \
    \     };\n                node_pointer_type res = rec(rec, p, p);\n          \
    \      for (int i = 1; i <= n; ++i) {\n                    int par = i + (i &\
    \ -i);\n                    if (par <= n) nodes[par]->_dat += nodes[i]->_dat;\n\
    \                }\n                return res;\n            }\n\n           \
    \ static value_type sum(node_pointer_type node, int p, int l, int r) {\n     \
    \           return sum(node, p, r) - sum(node, p, l);\n            }\n\n     \
    \       static node_pointer_type add(node_pointer_type node, int p, int i, const\
    \ value_type& val) {\n                ++i;\n                node_pointer_type\
    \ res = clone(node);\n                for (node_pointer_type cur = res;; p >>=\
    \ 1) {\n                    if (i & p) {\n                        if (i ^= p)\
    \ {\n                            cur = cur->_ch[1] = clone(cur->_ch[1]);\n   \
    \                     } else {\n                            cur->_dat += val;\n\
    \                            return res;\n                        }\n        \
    \            } else {\n                        cur->_dat += val;\n           \
    \             cur = cur->_ch[0] = clone(cur->_ch[0]);\n                    }\n\
    \                }\n            }\n        private:\n            static value_type\
    \ sum(node_pointer_type node, int p, int r) {\n                value_type res{};\n\
    \                for (; r; p >>= 1) {\n                    if (r & p) {\n    \
    \                    r ^= p;\n                        res += node->_dat;\n   \
    \                     node = node->_ch[1];\n                    } else {\n   \
    \                     node = node->_ch[0];\n                    }\n          \
    \      }\n                return res;\n            }\n        };\n\n        PersistentFenwickTree()\
    \ : _p(0), _root(nullptr) {}\n        explicit PersistentFenwickTree(int n) :\
    \ PersistentFenwickTree(std::vector<value_type>(n, T{})) {}\n        PersistentFenwickTree(const\
    \ std::vector<value_type>& dat) : _p(floor_pow2(dat.size())), _root(node_type::build(dat,\
    \ _p)) {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type sum(int\
    \ l, int r) {\n            return node_type::sum(_root, _p, l, r);\n        }\n\
    \        PersistentFenwickTree add(int i, const value_type &val) {\n         \
    \   return PersistentFenwickTree(_p, node_type::add(_root, _p, i, val));\n   \
    \     }\n\n    private:\n        int _p;\n        node_pointer_type _root;\n \
    \       PersistentFenwickTree(int p, node_pointer_type root) : _p(p), _root(root)\
    \ {}\n\n        static constexpr int floor_pow2(int n) {\n            int x =\
    \ 31 - __builtin_clz(n);\n            return x < 0 ? 0 : 1 << x;\n        }\n\
    \    };\n}\n\n\n"
  code: "#ifndef SUISEN_PERSISTENT_FENWICK_TREE\n#define SUISEN_PERSISTENT_FENWICK_TREE\n\
    \n#include <cassert>\n\n#include \"library/util/object_pool.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T>\n    struct PersistentFenwickTree {\n  \
    \      struct Node;\n\n        using value_type = T;\n\n        using node_type\
    \ = Node;\n        using node_pointer_type = node_type*;\n\n        struct Node\
    \ {\n            static inline ObjectPool<node_type> _pool;\n\n            node_pointer_type\
    \ _ch[2]{ nullptr, nullptr };\n            value_type _dat;\n\n            Node()\
    \ : _dat{} {}\n\n            static node_pointer_type clone(node_pointer_type\
    \ node) {\n                return &(*_pool.alloc() = *node);\n            }\n\n\
    \            static node_pointer_type build(const std::vector<value_type> &dat,\
    \ int p) {\n                const int n = dat.size();\n                std::vector<node_pointer_type>\
    \ nodes(n + 1);\n                auto rec = [&](auto rec, int p, int id) -> node_pointer_type\
    \ {\n                    if (p == 0) return nullptr;\n                    const\
    \ int np = p >> 1;\n                    node_pointer_type res = _pool.alloc();\n\
    \                    res->_ch[0] = rec(rec, np, id - np);\n                  \
    \  if (id + 1 <= n) res->_ch[1] = rec(rec, np, id + np);\n                   \
    \ if (id <= n) nodes[id] = res;\n                    return res;\n           \
    \     };\n                node_pointer_type res = rec(rec, p, p);\n          \
    \      for (int i = 1; i <= n; ++i) {\n                    int par = i + (i &\
    \ -i);\n                    if (par <= n) nodes[par]->_dat += nodes[i]->_dat;\n\
    \                }\n                return res;\n            }\n\n           \
    \ static value_type sum(node_pointer_type node, int p, int l, int r) {\n     \
    \           return sum(node, p, r) - sum(node, p, l);\n            }\n\n     \
    \       static node_pointer_type add(node_pointer_type node, int p, int i, const\
    \ value_type& val) {\n                ++i;\n                node_pointer_type\
    \ res = clone(node);\n                for (node_pointer_type cur = res;; p >>=\
    \ 1) {\n                    if (i & p) {\n                        if (i ^= p)\
    \ {\n                            cur = cur->_ch[1] = clone(cur->_ch[1]);\n   \
    \                     } else {\n                            cur->_dat += val;\n\
    \                            return res;\n                        }\n        \
    \            } else {\n                        cur->_dat += val;\n           \
    \             cur = cur->_ch[0] = clone(cur->_ch[0]);\n                    }\n\
    \                }\n            }\n        private:\n            static value_type\
    \ sum(node_pointer_type node, int p, int r) {\n                value_type res{};\n\
    \                for (; r; p >>= 1) {\n                    if (r & p) {\n    \
    \                    r ^= p;\n                        res += node->_dat;\n   \
    \                     node = node->_ch[1];\n                    } else {\n   \
    \                     node = node->_ch[0];\n                    }\n          \
    \      }\n                return res;\n            }\n        };\n\n        PersistentFenwickTree()\
    \ : _p(0), _root(nullptr) {}\n        explicit PersistentFenwickTree(int n) :\
    \ PersistentFenwickTree(std::vector<value_type>(n, T{})) {}\n        PersistentFenwickTree(const\
    \ std::vector<value_type>& dat) : _p(floor_pow2(dat.size())), _root(node_type::build(dat,\
    \ _p)) {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type sum(int\
    \ l, int r) {\n            return node_type::sum(_root, _p, l, r);\n        }\n\
    \        PersistentFenwickTree add(int i, const value_type &val) {\n         \
    \   return PersistentFenwickTree(_p, node_type::add(_root, _p, i, val));\n   \
    \     }\n\n    private:\n        int _p;\n        node_pointer_type _root;\n \
    \       PersistentFenwickTree(int p, node_pointer_type root) : _p(p), _root(root)\
    \ {}\n\n        static constexpr int floor_pow2(int n) {\n            int x =\
    \ 31 - __builtin_clz(n);\n            return x < 0 ? 0 : 1 << x;\n        }\n\
    \    };\n}\n\n#endif // SUISEN_PERSISTENT_FENWICK_TREE\n"
  dependsOn:
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/datastructure/persistent_fenwick_tree.hpp
  requiredBy: []
  timestamp: '2022-05-29 02:47:47+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/persistent_fenwick_tree/rectangle_sum.test.cpp
  - test/src/datastructure/persistent_fenwick_tree/abc253_f.test.cpp
documentation_of: library/datastructure/persistent_fenwick_tree.hpp
layout: document
title: Persistent Fenwick Tree
---
## Persistent Fenwick Tree

Fenwick Tree の値を二分木における in-order で配置すると，`add`, `sum` の操作が根から (葉とは限らない) ある節点までのパス上で完結する．即ち，Segment Tree 等と同様にして永続化することが出来る．

サイズ $N$ の列を管理するために必要なノードは $N + O(\log N)$ 個であり，$2 N - 1$ 個必要である永続 Segment Tree よりも空間効率がよい．

`add`, `sum` を非再帰で書けるので，定数倍の面でも有利?

例. [Rectangle Sum](https://judge.yosupo.jp/problem/rectangle_sum) での速度比較

- [永続 Fenwick Tree, 886ms](https://judge.yosupo.jp/submission/91009)
- [永続 Segment Tree, 1322ms](https://judge.yosupo.jp/submission/91011)
