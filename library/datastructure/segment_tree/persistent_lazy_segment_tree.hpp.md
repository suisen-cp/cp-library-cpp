---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/object_pool.hpp
    title: Object Pool
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
    title: test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp\"\
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
    \ namespace suisen\n\n\n#line 7 \"library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    struct PersistentLazySegmentTree\
    \ {\n        struct Node;\n\n        using value_type = T;\n        using operator_type\
    \ = F;\n\n        using node_type = Node;\n        using node_pointer_type = node_type*;\n\
    \n        struct Node {\n            static inline ObjectPool<node_type> _pool;\n\
    \n            node_pointer_type _ch[2]{ nullptr, nullptr };\n            value_type\
    \ _dat;\n            operator_type _laz;\n\n            Node() : _dat(e()), _laz(id())\
    \ {}\n\n            static node_pointer_type clone(node_pointer_type node) {\n\
    \                return &(*_pool.alloc() = *node);\n            }\n\n        \
    \    static void update(node_pointer_type node) {\n                node->_dat\
    \ = op(node->_ch[0]->_dat, node->_ch[1]->_dat);\n            }\n            template\
    \ <bool do_clone = true>\n            static auto push(node_pointer_type node)\
    \ {\n                node_pointer_type res = node;\n                if constexpr\
    \ (do_clone) res = clone(res);\n                res->_ch[0] = apply_all(res->_ch[0],\
    \ res->_laz);\n                res->_ch[1] = apply_all(res->_ch[1], res->_laz);\n\
    \                res->_laz = id();\n                if constexpr (do_clone) {\n\
    \                    return res;\n                } else {\n                 \
    \   return;\n                }\n            }\n\n            static bool is_leaf(node_pointer_type\
    \ node) {\n                return not node->_ch[0];\n            }\n\n       \
    \     static node_pointer_type build(const std::vector<value_type>& dat) {\n \
    \               auto rec = [&](auto rec, int l, int r) -> node_pointer_type {\n\
    \                    node_pointer_type res = _pool.alloc();\n                \
    \    if (r - l == 1) {\n                        res->_dat = dat[l];\n        \
    \                res->_laz = id();\n                    } else {\n           \
    \             int m = (l + r) >> 1;\n                        res->_ch[0] = rec(rec,\
    \ l, m), res->_ch[1] = rec(rec, m, r);\n                        update(res);\n\
    \                        res->_laz = id();\n                    }\n          \
    \          return res;\n                };\n                return rec(rec, 0,\
    \ dat.size());\n            }\n\n            static value_type prod_all(node_pointer_type\
    \ node) {\n                return node ? node->_dat : e();\n            }\n  \
    \          static value_type prod(node_pointer_type node, int tl, int tr, int\
    \ ql, int qr, const operator_type &f = id()) {\n                if (tr <= ql or\
    \ qr <= tl) return e();\n                if (ql <= tl and tr <= qr) return mapping(f,\
    \ node->_dat);\n                int tm = (tl + tr) >> 1;\n                operator_type\
    \ g = composition(f, node->_laz);\n                return op(prod(node->_ch[0],\
    \ tl, tm, ql, qr, g), prod(node->_ch[1], tm, tr, ql, qr, g));\n            }\n\
    \n            static node_pointer_type apply_all(node_pointer_type node, const\
    \ operator_type &f) {\n                if (not node) return nullptr;\n       \
    \         node_pointer_type res = clone(node);\n                res->_dat = mapping(f,\
    \ res->_dat);\n                res->_laz = composition(f, res->_laz);\n      \
    \          return res;\n            }\n            static node_pointer_type apply(node_pointer_type\
    \ node, int tl, int tr, int ql, int qr, const operator_type &f) {\n          \
    \      if (tr <= ql or qr <= tl) return node;\n                if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f);\n                node_pointer_type res\
    \ = push(node);\n                int tm = (tl + tr) >> 1;\n                res->_ch[0]\
    \ = apply(res->_ch[0], tl, tm, ql, qr, f);\n                res->_ch[1] = apply(res->_ch[1],\
    \ tm, tr, ql, qr, f);\n                update(res);\n                return res;\n\
    \            }\n\n            template <typename Func>\n            static auto\
    \ update_leaf(node_pointer_type node, int siz, int i, Func &&f) {\n          \
    \      static std::vector<node_pointer_type> path;\n\n                node_pointer_type\
    \ res = clone(node);\n                node_pointer_type cur = res;\n\n       \
    \         for (int l = 0, r = siz; r - l > 1;) {\n                    path.push_back(cur);\n\
    \                    push</*do_clone = */false>(cur);\n                    int\
    \ m = (l + r) >> 1;\n                    if (i < m) {\n                      \
    \  cur = cur->_ch[0];\n                        r = m;\n                    } else\
    \ {\n                        cur = cur->_ch[1];\n                        l = m;\n\
    \                    }\n                }\n                cur->_dat = f(cur->_dat);\n\
    \                while (path.size()) update(path.back()), path.pop_back();\n \
    \               return res;\n            }\n\n            static value_type get(node_pointer_type\
    \ node, int siz, int i) {\n                operator_type f = id();\n         \
    \       node_pointer_type cur = node;\n                for (int l = 0, r = siz;\
    \ r - l > 1;) {\n                    f = composition(f, cur->_laz);\n        \
    \            int m = (l + r) >> 1;\n                    if (i < m) {\n       \
    \                 cur = cur->_ch[0];\n                        r = m;\n       \
    \             } else {\n                        cur = cur->_ch[1];\n         \
    \               l = m;\n                    }\n                }\n           \
    \     return mapping(f, cur->_dat);\n            }\n            template <typename\
    \ Func>\n            static node_pointer_type apply(node_pointer_type node, int\
    \ siz, int i, Func&& f) {\n                return update_leaf(node, siz, i, [&](const\
    \ value_type &v) { return f(v); });\n            }\n            static node_pointer_type\
    \ set(node_pointer_type node, int siz, int i, const value_type& dat) {\n     \
    \           return apply(node, siz, i, [&](const value_type&) { return dat; });\n\
    \            }\n\n            template <typename Pred>\n            static int\
    \ max_right(node_pointer_type node, int siz, int l, Pred&& pred) {\n         \
    \       assert(pred(e()));\n                auto rec = [&](auto rec, node_pointer_type\
    \ cur, int tl, int tr, value_type& sum, const operator_type &f) -> int {\n   \
    \                 if (tr <= l) return tr;\n                    if (l <= tl) {\n\
    \                        value_type nxt_sum = op(sum, mapping(f, cur->_dat));\n\
    \                        if (pred(nxt_sum)) {\n                            sum\
    \ = std::move(nxt_sum);\n                            return tr;\n            \
    \            }\n                        if (tr - tl == 1) return tl;\n       \
    \             }\n                    int tm = (tl + tr) >> 1;\n              \
    \      operator_type g = composition(f, cur->_laz);\n                    int res_l\
    \ = rec(rec, cur->_ch[0], tl, tm, sum, g);\n                    return res_l !=\
    \ tm ? res_l : rec(rec, cur->_ch[1], tm, tr, sum, g);\n                };\n  \
    \              value_type sum = e();\n                return rec(rec, node, 0,\
    \ siz, sum, id());\n            }\n            template <typename Pred>\n    \
    \        static int min_left(node_pointer_type node, int siz, int r, Pred&& pred)\
    \ {\n                assert(pred(e()));\n                auto rec = [&](auto rec,\
    \ node_pointer_type cur, int tl, int tr, value_type& sum, const operator_type\
    \ &f) -> int {\n                    if (r <= tl) return tl;\n                \
    \    if (tr <= r) {\n                        value_type nxt_sum = op(mapping(f,\
    \ cur->_dat), sum);\n                        if (pred(nxt_sum)) {\n          \
    \                  sum = std::move(nxt_sum);\n                            return\
    \ tl;\n                        }\n                        if (tr - tl == 1) return\
    \ tr;\n                    }\n                    int tm = (tl + tr) >> 1;\n \
    \                   operator_type g = composition(f, cur->_laz);\n           \
    \         int res_r = rec(rec, cur->_ch[1], tm, tr, sum, g);\n               \
    \     return res_r != tm ? res_r : rec(rec, cur->_ch[0], tl, tm, sum, g);\n  \
    \              };\n                value_type sum = e();\n                return\
    \ rec(rec, node, 0, siz, sum, id());\n            }\n\n            template <typename\
    \ OutputIterator>\n            static void dump(node_pointer_type node, OutputIterator\
    \ it) {\n                if (not node) return;\n                auto rec = [&](auto\
    \ rec, node_pointer_type cur, const operator_type &f) -> void {\n            \
    \        if (is_leaf(cur)) {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                    } else {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                        rec(rec, cur->_ch[0], composition(cur->_laz, f)), rec(rec,\
    \ cur->_ch[1], composition(cur->_laz, f));\n                    }\n          \
    \      };\n                rec(rec, node, id());\n            }\n            static\
    \ std::vector<value_type> dump(node_pointer_type node) {\n                std::vector<value_type>\
    \ res;\n                dump(node, std::back_inserter(res));\n               \
    \ return res;\n            }\n        };\n\n        PersistentLazySegmentTree()\
    \ : _n(0), _root(nullptr) {}\n        explicit PersistentLazySegmentTree(int n)\
    \ : PersistentLazySegmentTree(std::vector<value_type>(n, e())) {}\n        PersistentLazySegmentTree(const\
    \ std::vector<value_type>& dat) : _n(dat.size()), _root(node_type::build(dat))\
    \ {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type prod_all()\
    \ {\n            return node_type::prod_all(_root);\n        }\n        value_type\
    \ prod(int l, int r) {\n            assert(0 <= l and l <= r and r <= _n);\n \
    \           return node_type::prod(_root, 0, _n, l, r);\n        }\n        value_type\
    \ operator()(int l, int r) {\n            return prod(l, r);\n        }\n\n  \
    \      PersistentLazySegmentTree apply_all(const operator_type &f) {\n       \
    \     return PersistentLazySegmentTree(_n, node_type::apply_all(_root, f));\n\
    \        }\n        PersistentLazySegmentTree apply(int l, int r, const operator_type\
    \ &f) {\n            return PersistentLazySegmentTree(_n, node_type::apply(_root,\
    \ 0, _n, l, r, f));\n        }\n\n        value_type get(int i) {\n          \
    \  assert(0 <= i and i < _n);\n            return node_type::get(_root, _n, i);\n\
    \        }\n        value_type operator[](int i) {\n            return get(i);\n\
    \        }\n\n        template <typename Func>\n        PersistentLazySegmentTree\
    \ apply(int i, Func&& f) {\n            assert(0 <= i and i < _n);\n         \
    \   return PersistentLazySegmentTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));\n\
    \        }\n        PersistentLazySegmentTree set(int i, const value_type& v)\
    \ {\n            assert(0 <= i and i < _n);\n            return PersistentLazySegmentTree(_n,\
    \ node_type::set(_root, _n, i, v));\n        }\n\n        template <typename Pred>\n\
    \        int max_right(int l, Pred&& pred) {\n            assert(0 <= l and l\
    \ <= _n);\n            return node_type::max_right(_root, _n, l, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int max_right(int\
    \ l) {\n            return max_right(l, pred);\n        }\n        template <typename\
    \ Pred>\n        int min_left(int r, Pred&& pred) {\n            assert(0 <= r\
    \ and r <= _n);\n            return node_type::min_left(_root, _n, r, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int min_left(int\
    \ r) {\n            return min_left(r, pred);\n        }\n\n        template <typename\
    \ OutputIterator>\n        void dump(OutputIterator it) {\n            node_type::dump(_root,\
    \ it);\n        }\n        std::vector<value_type> dump() {\n            return\
    \ node_type::dump(_root);\n        }\n\n    private:\n        int _n;\n      \
    \  node_pointer_type _root;\n        PersistentLazySegmentTree(int n, node_pointer_type\
    \ root) : _n(n), _root(root) {}\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_PERSISTENT_LAZYSEGMENT_TREE\n#define SUISEN_PERSISTENT_LAZYSEGMENT_TREE\n\
    \n#include <cassert>\n\n#include \"library/util/object_pool.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n    struct PersistentLazySegmentTree {\n\
    \        struct Node;\n\n        using value_type = T;\n        using operator_type\
    \ = F;\n\n        using node_type = Node;\n        using node_pointer_type = node_type*;\n\
    \n        struct Node {\n            static inline ObjectPool<node_type> _pool;\n\
    \n            node_pointer_type _ch[2]{ nullptr, nullptr };\n            value_type\
    \ _dat;\n            operator_type _laz;\n\n            Node() : _dat(e()), _laz(id())\
    \ {}\n\n            static node_pointer_type clone(node_pointer_type node) {\n\
    \                return &(*_pool.alloc() = *node);\n            }\n\n        \
    \    static void update(node_pointer_type node) {\n                node->_dat\
    \ = op(node->_ch[0]->_dat, node->_ch[1]->_dat);\n            }\n            template\
    \ <bool do_clone = true>\n            static auto push(node_pointer_type node)\
    \ {\n                node_pointer_type res = node;\n                if constexpr\
    \ (do_clone) res = clone(res);\n                res->_ch[0] = apply_all(res->_ch[0],\
    \ res->_laz);\n                res->_ch[1] = apply_all(res->_ch[1], res->_laz);\n\
    \                res->_laz = id();\n                if constexpr (do_clone) {\n\
    \                    return res;\n                } else {\n                 \
    \   return;\n                }\n            }\n\n            static bool is_leaf(node_pointer_type\
    \ node) {\n                return not node->_ch[0];\n            }\n\n       \
    \     static node_pointer_type build(const std::vector<value_type>& dat) {\n \
    \               auto rec = [&](auto rec, int l, int r) -> node_pointer_type {\n\
    \                    node_pointer_type res = _pool.alloc();\n                \
    \    if (r - l == 1) {\n                        res->_dat = dat[l];\n        \
    \                res->_laz = id();\n                    } else {\n           \
    \             int m = (l + r) >> 1;\n                        res->_ch[0] = rec(rec,\
    \ l, m), res->_ch[1] = rec(rec, m, r);\n                        update(res);\n\
    \                        res->_laz = id();\n                    }\n          \
    \          return res;\n                };\n                return rec(rec, 0,\
    \ dat.size());\n            }\n\n            static value_type prod_all(node_pointer_type\
    \ node) {\n                return node ? node->_dat : e();\n            }\n  \
    \          static value_type prod(node_pointer_type node, int tl, int tr, int\
    \ ql, int qr, const operator_type &f = id()) {\n                if (tr <= ql or\
    \ qr <= tl) return e();\n                if (ql <= tl and tr <= qr) return mapping(f,\
    \ node->_dat);\n                int tm = (tl + tr) >> 1;\n                operator_type\
    \ g = composition(f, node->_laz);\n                return op(prod(node->_ch[0],\
    \ tl, tm, ql, qr, g), prod(node->_ch[1], tm, tr, ql, qr, g));\n            }\n\
    \n            static node_pointer_type apply_all(node_pointer_type node, const\
    \ operator_type &f) {\n                if (not node) return nullptr;\n       \
    \         node_pointer_type res = clone(node);\n                res->_dat = mapping(f,\
    \ res->_dat);\n                res->_laz = composition(f, res->_laz);\n      \
    \          return res;\n            }\n            static node_pointer_type apply(node_pointer_type\
    \ node, int tl, int tr, int ql, int qr, const operator_type &f) {\n          \
    \      if (tr <= ql or qr <= tl) return node;\n                if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f);\n                node_pointer_type res\
    \ = push(node);\n                int tm = (tl + tr) >> 1;\n                res->_ch[0]\
    \ = apply(res->_ch[0], tl, tm, ql, qr, f);\n                res->_ch[1] = apply(res->_ch[1],\
    \ tm, tr, ql, qr, f);\n                update(res);\n                return res;\n\
    \            }\n\n            template <typename Func>\n            static auto\
    \ update_leaf(node_pointer_type node, int siz, int i, Func &&f) {\n          \
    \      static std::vector<node_pointer_type> path;\n\n                node_pointer_type\
    \ res = clone(node);\n                node_pointer_type cur = res;\n\n       \
    \         for (int l = 0, r = siz; r - l > 1;) {\n                    path.push_back(cur);\n\
    \                    push</*do_clone = */false>(cur);\n                    int\
    \ m = (l + r) >> 1;\n                    if (i < m) {\n                      \
    \  cur = cur->_ch[0];\n                        r = m;\n                    } else\
    \ {\n                        cur = cur->_ch[1];\n                        l = m;\n\
    \                    }\n                }\n                cur->_dat = f(cur->_dat);\n\
    \                while (path.size()) update(path.back()), path.pop_back();\n \
    \               return res;\n            }\n\n            static value_type get(node_pointer_type\
    \ node, int siz, int i) {\n                operator_type f = id();\n         \
    \       node_pointer_type cur = node;\n                for (int l = 0, r = siz;\
    \ r - l > 1;) {\n                    f = composition(f, cur->_laz);\n        \
    \            int m = (l + r) >> 1;\n                    if (i < m) {\n       \
    \                 cur = cur->_ch[0];\n                        r = m;\n       \
    \             } else {\n                        cur = cur->_ch[1];\n         \
    \               l = m;\n                    }\n                }\n           \
    \     return mapping(f, cur->_dat);\n            }\n            template <typename\
    \ Func>\n            static node_pointer_type apply(node_pointer_type node, int\
    \ siz, int i, Func&& f) {\n                return update_leaf(node, siz, i, [&](const\
    \ value_type &v) { return f(v); });\n            }\n            static node_pointer_type\
    \ set(node_pointer_type node, int siz, int i, const value_type& dat) {\n     \
    \           return apply(node, siz, i, [&](const value_type&) { return dat; });\n\
    \            }\n\n            template <typename Pred>\n            static int\
    \ max_right(node_pointer_type node, int siz, int l, Pred&& pred) {\n         \
    \       assert(pred(e()));\n                auto rec = [&](auto rec, node_pointer_type\
    \ cur, int tl, int tr, value_type& sum, const operator_type &f) -> int {\n   \
    \                 if (tr <= l) return tr;\n                    if (l <= tl) {\n\
    \                        value_type nxt_sum = op(sum, mapping(f, cur->_dat));\n\
    \                        if (pred(nxt_sum)) {\n                            sum\
    \ = std::move(nxt_sum);\n                            return tr;\n            \
    \            }\n                        if (tr - tl == 1) return tl;\n       \
    \             }\n                    int tm = (tl + tr) >> 1;\n              \
    \      operator_type g = composition(f, cur->_laz);\n                    int res_l\
    \ = rec(rec, cur->_ch[0], tl, tm, sum, g);\n                    return res_l !=\
    \ tm ? res_l : rec(rec, cur->_ch[1], tm, tr, sum, g);\n                };\n  \
    \              value_type sum = e();\n                return rec(rec, node, 0,\
    \ siz, sum, id());\n            }\n            template <typename Pred>\n    \
    \        static int min_left(node_pointer_type node, int siz, int r, Pred&& pred)\
    \ {\n                assert(pred(e()));\n                auto rec = [&](auto rec,\
    \ node_pointer_type cur, int tl, int tr, value_type& sum, const operator_type\
    \ &f) -> int {\n                    if (r <= tl) return tl;\n                \
    \    if (tr <= r) {\n                        value_type nxt_sum = op(mapping(f,\
    \ cur->_dat), sum);\n                        if (pred(nxt_sum)) {\n          \
    \                  sum = std::move(nxt_sum);\n                            return\
    \ tl;\n                        }\n                        if (tr - tl == 1) return\
    \ tr;\n                    }\n                    int tm = (tl + tr) >> 1;\n \
    \                   operator_type g = composition(f, cur->_laz);\n           \
    \         int res_r = rec(rec, cur->_ch[1], tm, tr, sum, g);\n               \
    \     return res_r != tm ? res_r : rec(rec, cur->_ch[0], tl, tm, sum, g);\n  \
    \              };\n                value_type sum = e();\n                return\
    \ rec(rec, node, 0, siz, sum, id());\n            }\n\n            template <typename\
    \ OutputIterator>\n            static void dump(node_pointer_type node, OutputIterator\
    \ it) {\n                if (not node) return;\n                auto rec = [&](auto\
    \ rec, node_pointer_type cur, const operator_type &f) -> void {\n            \
    \        if (is_leaf(cur)) {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                    } else {\n                        *it++ = mapping(f, cur->_dat);\n\
    \                        rec(rec, cur->_ch[0], composition(cur->_laz, f)), rec(rec,\
    \ cur->_ch[1], composition(cur->_laz, f));\n                    }\n          \
    \      };\n                rec(rec, node, id());\n            }\n            static\
    \ std::vector<value_type> dump(node_pointer_type node) {\n                std::vector<value_type>\
    \ res;\n                dump(node, std::back_inserter(res));\n               \
    \ return res;\n            }\n        };\n\n        PersistentLazySegmentTree()\
    \ : _n(0), _root(nullptr) {}\n        explicit PersistentLazySegmentTree(int n)\
    \ : PersistentLazySegmentTree(std::vector<value_type>(n, e())) {}\n        PersistentLazySegmentTree(const\
    \ std::vector<value_type>& dat) : _n(dat.size()), _root(node_type::build(dat))\
    \ {}\n\n        static void init_pool(int siz) {\n            node_type::_pool\
    \ = ObjectPool<node_type>(siz);\n        }\n        static void clear_pool() {\n\
    \            node_type::_pool.clear();\n        }\n\n        value_type prod_all()\
    \ {\n            return node_type::prod_all(_root);\n        }\n        value_type\
    \ prod(int l, int r) {\n            assert(0 <= l and l <= r and r <= _n);\n \
    \           return node_type::prod(_root, 0, _n, l, r);\n        }\n        value_type\
    \ operator()(int l, int r) {\n            return prod(l, r);\n        }\n\n  \
    \      PersistentLazySegmentTree apply_all(const operator_type &f) {\n       \
    \     return PersistentLazySegmentTree(_n, node_type::apply_all(_root, f));\n\
    \        }\n        PersistentLazySegmentTree apply(int l, int r, const operator_type\
    \ &f) {\n            return PersistentLazySegmentTree(_n, node_type::apply(_root,\
    \ 0, _n, l, r, f));\n        }\n\n        value_type get(int i) {\n          \
    \  assert(0 <= i and i < _n);\n            return node_type::get(_root, _n, i);\n\
    \        }\n        value_type operator[](int i) {\n            return get(i);\n\
    \        }\n\n        template <typename Func>\n        PersistentLazySegmentTree\
    \ apply(int i, Func&& f) {\n            assert(0 <= i and i < _n);\n         \
    \   return PersistentLazySegmentTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));\n\
    \        }\n        PersistentLazySegmentTree set(int i, const value_type& v)\
    \ {\n            assert(0 <= i and i < _n);\n            return PersistentLazySegmentTree(_n,\
    \ node_type::set(_root, _n, i, v));\n        }\n\n        template <typename Pred>\n\
    \        int max_right(int l, Pred&& pred) {\n            assert(0 <= l and l\
    \ <= _n);\n            return node_type::max_right(_root, _n, l, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int max_right(int\
    \ l) {\n            return max_right(l, pred);\n        }\n        template <typename\
    \ Pred>\n        int min_left(int r, Pred&& pred) {\n            assert(0 <= r\
    \ and r <= _n);\n            return node_type::min_left(_root, _n, r, std::forward<Pred>(pred));\n\
    \        }\n        template <bool(*pred)(value_type)>\n        static int min_left(int\
    \ r) {\n            return min_left(r, pred);\n        }\n\n        template <typename\
    \ OutputIterator>\n        void dump(OutputIterator it) {\n            node_type::dump(_root,\
    \ it);\n        }\n        std::vector<value_type> dump() {\n            return\
    \ node_type::dump(_root);\n        }\n\n    private:\n        int _n;\n      \
    \  node_pointer_type _root;\n        PersistentLazySegmentTree(int n, node_pointer_type\
    \ root) : _n(n), _root(root) {}\n    };\n}\n\n#endif // SUISEN_PERSISTENT_LAZYSEGMENT_TREE\n"
  dependsOn:
  - library/util/object_pool.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-04-05 23:32:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/persistent_lazy_segment_tree/dummy.test.cpp
documentation_of: library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
layout: document
title: Persistent Lazy Segment Tree
---
## Persistent Lazy Segment Tree