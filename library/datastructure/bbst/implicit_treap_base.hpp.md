---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap.hpp
    title: Implicit Treap
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_dual_segtree.hpp
    title: Implicit Treap Dual Segtree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
    title: Implicit Treap Lazy Segtree
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_segtree.hpp
    title: Implicit Treap Segtree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
    title: test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap/dummy.test.cpp
    title: test/src/datastructure/bbst/implicit_treap/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap_dual_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/implicit_treap_dual_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap_segtree/abc238_f.test.cpp
    title: test/src/datastructure/bbst/implicit_treap_segtree/abc238_f.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
    title: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstdint>\n#include <string>\n#include <random>\n\
    #include <tuple>\n#include <utility>\n\nnamespace suisen::internal::implicit_treap\
    \ {\n    template <typename T, typename Derived>\n    struct Node {\n        using\
    \ value_type = T;\n        using node_type = Derived;\n        using node_pointer\
    \ = uint32_t;\n\n        static inline std::mt19937 rng{ std::random_device{}()\
    \ };\n        static inline std::vector<node_type> _nodes{};\n        static inline\
    \ std::vector<node_pointer> _erased{};\n\n        static constexpr node_pointer\
    \ null = ~node_pointer(0);\n\n        node_pointer _ch[2]{ null, null };\n   \
    \     value_type _val;\n        uint32_t _size;\n        uint32_t _priority;\n\
    \n        bool _rev = false;\n\n        Node(const value_type val = {}): _val(val),\
    \ _size(1), _priority(rng()) {}\n\n        static void reserve(uint32_t capacity)\
    \ {\n            _nodes.reserve(capacity);\n        }\n\n        static node_type&\
    \ node(node_pointer t) {\n            return _nodes[t];\n        }\n        static\
    \ const node_type& const_node(node_pointer t) {\n            return _nodes[t];\n\
    \        }\n\n        static value_type& value(node_pointer t) {\n           \
    \ return node(t)._val;\n        }\n        static value_type set_value(node_pointer\
    \ t, const value_type& new_val) {\n            return std::exchange(value(t),\
    \ new_val);\n        }\n\n        static bool empty(node_pointer t) {\n      \
    \      return t == null;\n        }\n        static uint32_t& size(node_pointer\
    \ t) {\n            return node(t)._size;\n        }\n        static uint32_t\
    \ safe_size(node_pointer t) {\n            return empty(t) ? 0 : size(t);\n  \
    \      }\n\n        static uint32_t priority(node_pointer t) {\n            return\
    \ const_node(t)._priority;\n        }\n\n        static node_pointer& child0(node_pointer\
    \ t) {\n            return node(t)._ch[0];\n        }\n        static node_pointer&\
    \ child1(node_pointer t) {\n            return node(t)._ch[1];\n        }\n  \
    \      static node_pointer child(node_pointer t, bool b) {\n            return\
    \ node(t)._ch[b];\n        }\n        static node_pointer set_child0(node_pointer\
    \ t, node_pointer cid) {\n            return std::exchange(child0(t), cid);\n\
    \        }\n        static node_pointer set_child1(node_pointer t, node_pointer\
    \ cid) {\n            return std::exchange(child1(t), cid);\n        }\n\n   \
    \     static bool& reversed(node_pointer t) {\n            return node(t)._rev;\n\
    \        }\n\n        static node_pointer update(node_pointer t) { // t : not\
    \ null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;\n\
    \            return t;\n        }\n        static bool push(node_pointer t) {\
    \ // t : not null\n            bool rev = t != null and std::exchange(reversed(t),\
    \ false);\n            if (rev) {\n                reverse_all(child0(t));\n \
    \               reverse_all(child1(t));\n            }\n            return rev;\n\
    \        }\n\n        static node_pointer empty_node() {\n            return null;\n\
    \        }\n        template <typename ...Args>\n        static node_pointer create_node(Args\
    \ &&...args) {\n            if (_erased.size()) {\n                node_pointer\
    \ res = _erased.back();\n                _erased.pop_back();\n               \
    \ node(res) = node_type(std::forward<Args>(args)...);\n                return\
    \ res;\n            } else {\n                node_pointer res = _nodes.size();\n\
    \                _nodes.emplace_back(std::forward<Args>(args)...);\n         \
    \       return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) {\n            _erased.push_back(t);\n        }\n        static void delete_tree(node_pointer\
    \ t) {\n            if (t == null) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            node_pointer res = empty_node();\n            for\
    \ (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {\n      \
    \          res = push_back(res, std::move(e));\n            }\n            return\
    \ res;\n        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, uint32_t k) {\n            if (t == null) {\n                return { null,\
    \ null };\n            }\n            node_type::push(t);\n            if (const\
    \ uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {\n                auto [ll,\
    \ lr] = split(child0(t), k);\n                set_child0(t, lr);\n           \
    \     return { ll, node_type::update(t) };\n            } else {\n           \
    \     auto [rl, rr] = split(child1(t), k - (lsiz + 1));\n                set_child1(t,\
    \ rl);\n                return { node_type::update(t), rr };\n            }\n\
    \        }\n        static std::tuple<node_pointer, node_pointer, node_pointer>\
    \ split(node_pointer t, uint32_t l, uint32_t r) {\n            auto [tlm, tr]\
    \ = split(t, r);\n            auto [tl, tm] = split(tlm, l);\n            return\
    \ { tl, tm, tr };\n        }\n        static node_pointer merge(node_pointer tl,\
    \ node_pointer tr) {\n            if (tl == null or tr == null) {\n          \
    \      return tl ^ tr ^ null;\n            }\n            if (priority(tl) < priority(tr))\
    \ {\n                node_type::push(tr);\n                set_child0(tr, merge(tl,\
    \ child0(tr)));\n                return node_type::update(tr);\n            }\
    \ else {\n                node_type::push(tl);\n                set_child1(tl,\
    \ merge(child1(tl), tr));\n                return node_type::update(tl);\n   \
    \         }\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n        static node_pointer insert_impl(node_pointer t, uint32_t k, node_pointer\
    \ new_node) {\n            if (t == null) {\n                return new_node;\n\
    \            }\n            if (priority(new_node) > priority(t)) {\n        \
    \        auto [tl, tr] = split(t, k);\n                set_child0(new_node, tl);\n\
    \                set_child1(new_node, tr);\n                return node_type::update(new_node);\n\
    \            } else {\n                node_type::push(t);\n                if\
    \ (const uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {\n                \
    \    set_child0(t, insert_impl(child0(t), k, new_node));\n                } else\
    \ {\n                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1),\
    \ new_node));\n                }\n                return node_type::update(t);\n\
    \            }\n        }\n        template <typename ...Args>\n        static\
    \ node_pointer insert(node_pointer t, uint32_t k, Args &&...args) {\n        \
    \    return insert_impl(t, k, create_node(std::forward<Args>(args)...));\n   \
    \     }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        static node_pointer erase(node_pointer t, uint32_t k) {\n\
    \            node_type::push(t);\n            if (const uint32_t lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                delete_node(t);\n                return merge(child0(t),\
    \ child1(t));\n            } else if (k < lsiz) {\n                set_child0(t,\
    \ erase(child0(t), k));\n                return node_type::update(t);\n      \
    \      } else {\n                set_child1(t, erase(child1(t), k - (lsiz + 1)));\n\
    \                return node_type::update(t);\n            }\n        }\n    \
    \    static node_pointer pop_front(node_pointer t) {\n            return erase(t,\
    \ 0);\n        }\n        static node_pointer pop_back(node_pointer t) {\n   \
    \         return erase(t, safe_size(t) - 1);\n        }\n\n        static node_pointer\
    \ rotate(node_pointer t, uint32_t k) {\n            auto [tl, tr] = split(t, k);\n\
    \            return merge(tr, tl);\n        }\n\n        static value_type& get(node_pointer\
    \ t, uint32_t k) {\n            while (true) {\n                node_type::push(t);\n\
    \                if (const uint32_t lsiz = safe_size(child0(t)); k == lsiz) {\n\
    \                    return value(t);\n                } else if (k < lsiz) {\n\
    \                    t = child0(t);\n                } else {\n              \
    \      k -= lsiz + 1;\n                    t = child1(t);\n                }\n\
    \            }\n        }\n\n        template <typename Func>\n        static\
    \ node_pointer set_update(node_pointer t, uint32_t k, const Func& f) {\n     \
    \       node_type::push(t);\n            if (const uint32_t lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                value_type& val = value(t);\n                val\
    \ = f(const_cast<const value_type&>(val));\n            } else if (k < lsiz) {\n\
    \                set_child0(t, set_update(child0(t), k, f));\n            } else\
    \ {\n                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));\n\
    \            }\n            return node_type::update(t);\n        }\n\n      \
    \  static node_pointer reverse_all(node_pointer t) {\n            if (t != null)\
    \ {\n                reversed(t) ^= true;\n                std::swap(child0(t),\
    \ child1(t));\n            }\n            return t;\n        }\n        static\
    \ node_pointer reverse(node_pointer t, uint32_t l, uint32_t r) {\n           \
    \ auto [tl, tm, tr] = split(t, l, r);\n            return merge(tl, Derived::reverse_all(tm),\
    \ tr);\n        }\n\n        static std::vector<value_type> dump(node_pointer\
    \ t) {\n            std::vector<value_type> res;\n            res.reserve(safe_size(t));\n\
    \            auto rec = [&](auto rec, node_pointer t) -> void {\n            \
    \    if (t == null) return;\n                node_type::push(t);\n           \
    \     rec(rec, child0(t));\n                res.push_back(value(t));\n       \
    \         rec(rec, child1(t));\n            };\n            rec(rec, t);\n   \
    \         return res;\n        }\n\n        // Predicate : (value, index) -> {\
    \ false, true }\n        template <typename Predicate>\n        static uint32_t\
    \ binary_search(node_pointer t, const Predicate& f) {\n            int ng = -1,\
    \ ok = safe_size(t);\n            while (ok - ng > 1) {\n                node_type::push(t);\n\
    \                const int lsiz = safe_size(child0(t));\n                if (f(value(t),\
    \ ng + lsiz + 1)) {\n                    ok = ng + lsiz + 1;\n               \
    \     t = child0(t);\n                } else {\n                    ng += lsiz\
    \ + 1;\n                    t = child1(t);\n                }\n            }\n\
    \            return ok;\n        }\n\n        struct NodeIterator {\n        \
    \    std::vector<node_pointer> stk;\n\n            value_type& operator*() const\
    \ {\n                return value(stk.back());\n            }\n\n            NodeIterator&\
    \ operator++() {\n                node_pointer t = stk.back();\n             \
    \   if (child1(t) == null) {\n                    up</*suc = */true>();\n    \
    \            } else {\n                    down</*suc = */true>(child1(t), 0);\n\
    \                }\n                return *this;\n            }\n           \
    \ NodeIterator operator++(int) {\n                NodeIterator res = *this;\n\
    \                ++(*this);\n                return res;\n            }\n\n  \
    \          NodeIterator& operator--() {\n                node_pointer t = stk.back();\n\
    \                if (child0(t) == null) {\n                    up</*suc = */false>();\n\
    \                } else {\n                    down</*suc = */false>(child0(t),\
    \ 0);\n                }\n                return *this;\n            }\n     \
    \       NodeIterator operator--(int) {\n                NodeIterator res = *this;\n\
    \                --(*this);\n                return res;\n            }\n    \
    \    \n            NodeIterator& operator+=(int k) {\n                if (k >=\
    \ 0) suc(k);\n                else pre(-k);\n                return *this;\n \
    \           }\n            NodeIterator operator+(int k) {\n                NodeIterator\
    \ res = *this;\n                res += k;\n                return res;\n     \
    \       }\n\n            NodeIterator& operator-=(int k) {\n                return\
    \ *this += -k;\n            }\n            NodeIterator operator-(int k) {\n \
    \               return *this + (-k);\n            }\n\n            bool operator==(NodeIterator&\
    \ other) const {\n                return stk.empty() ? other.stk.empty() : other.stk.size()\
    \ and stk.back() == other.stk.back();\n            }\n        private:\n     \
    \       template <bool suc>\n            void up() {\n                node_pointer\
    \ t = stk.back();\n                do {\n                    stk.pop_back();\n\
    \                    if (t == child(stk.back(), not suc)) {\n                \
    \        break;\n                    }\n                    t = stk.back();\n\
    \                } while (stk.size());\n            }\n            template <bool\
    \ suc>\n            void down(node_pointer t, size_t k) {\n                while\
    \ (true) {\n                    node_type::push(t);\n                    stk.push_back(t);\n\
    \                    \n                    node_pointer siz = safe_size(child(t,\
    \ not suc));\n                    if (k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not suc);\n                    } else {\n                        k -= siz +\
    \ 1;\n                        t = child(t, suc);\n                    }\n    \
    \            }\n            }\n            void suc(size_t k) {\n            \
    \    while (k) {\n                    node_pointer t = stk.back();\n         \
    \           node_pointer rsiz = safe_size(child1(t));\n                    if\
    \ (k > rsiz) {\n                        up</*suc = */true>();\n              \
    \          k -= rsiz + 1;\n                    } else {\n                    \
    \    down</*suc = */true>(child1(t), k - 1);\n                        break;\n\
    \                    }\n                }\n            }\n            void pre(size_t\
    \ k) {\n                while (k) {\n                    node_pointer t = stk.back();\n\
    \                    node_pointer lsiz = safe_size(child0(t));\n             \
    \       if (k > lsiz) {\n                        up</*suc = */false>();\n    \
    \                    k -= lsiz + 1;\n                    } else {\n          \
    \              down</*suc = */false>(child0(t), k - 1);\n                    \
    \    break;\n                    }\n                }\n            }\n       \
    \ };\n\n        static NodeIterator begin(node_pointer t) {\n            std::vector<node_pointer>\
    \ stk;\n            while (t != null) {\n                node_type::push(t);\n\
    \                stk.push_back(t);\n                t = child0(t);\n         \
    \   }\n            return NodeIterator{ stk };\n        }\n        static NodeIterator\
    \ end(node_pointer t) {\n            return NodeIterator{};\n        }\n     \
    \   static NodeIterator kth_iterator(node_pointer t, uint32_t k) {\n         \
    \   std::vector<node_pointer> stk;\n            while (t != null) {\n        \
    \        node_type::push(t);\n                stk.push_back(t);\n            \
    \    uint32_t siz = safe_size(child0(t));\n                if (k == siz) {\n \
    \                   break;\n                } else if (k < siz) {\n          \
    \          t = child0(t);\n                } else {\n                    k -=\
    \ siz + 1;\n                    t = child1(t);\n                }\n          \
    \  }\n            return NodeIterator{ stk };\n        }\n    };\n} // namespace\
    \ suisen::internal::implicit_treap\n\n\n"
  code: "#ifndef SUISEN_IMPLICIT_TREAP_BASE\n#define SUISEN_IMPLICIT_TREAP_BASE\n\n\
    #include <cassert>\n#include <cstdint>\n#include <string>\n#include <random>\n\
    #include <tuple>\n#include <utility>\n\nnamespace suisen::internal::implicit_treap\
    \ {\n    template <typename T, typename Derived>\n    struct Node {\n        using\
    \ value_type = T;\n        using node_type = Derived;\n        using node_pointer\
    \ = uint32_t;\n\n        static inline std::mt19937 rng{ std::random_device{}()\
    \ };\n        static inline std::vector<node_type> _nodes{};\n        static inline\
    \ std::vector<node_pointer> _erased{};\n\n        static constexpr node_pointer\
    \ null = ~node_pointer(0);\n\n        node_pointer _ch[2]{ null, null };\n   \
    \     value_type _val;\n        uint32_t _size;\n        uint32_t _priority;\n\
    \n        bool _rev = false;\n\n        Node(const value_type val = {}): _val(val),\
    \ _size(1), _priority(rng()) {}\n\n        static void reserve(uint32_t capacity)\
    \ {\n            _nodes.reserve(capacity);\n        }\n\n        static node_type&\
    \ node(node_pointer t) {\n            return _nodes[t];\n        }\n        static\
    \ const node_type& const_node(node_pointer t) {\n            return _nodes[t];\n\
    \        }\n\n        static value_type& value(node_pointer t) {\n           \
    \ return node(t)._val;\n        }\n        static value_type set_value(node_pointer\
    \ t, const value_type& new_val) {\n            return std::exchange(value(t),\
    \ new_val);\n        }\n\n        static bool empty(node_pointer t) {\n      \
    \      return t == null;\n        }\n        static uint32_t& size(node_pointer\
    \ t) {\n            return node(t)._size;\n        }\n        static uint32_t\
    \ safe_size(node_pointer t) {\n            return empty(t) ? 0 : size(t);\n  \
    \      }\n\n        static uint32_t priority(node_pointer t) {\n            return\
    \ const_node(t)._priority;\n        }\n\n        static node_pointer& child0(node_pointer\
    \ t) {\n            return node(t)._ch[0];\n        }\n        static node_pointer&\
    \ child1(node_pointer t) {\n            return node(t)._ch[1];\n        }\n  \
    \      static node_pointer child(node_pointer t, bool b) {\n            return\
    \ node(t)._ch[b];\n        }\n        static node_pointer set_child0(node_pointer\
    \ t, node_pointer cid) {\n            return std::exchange(child0(t), cid);\n\
    \        }\n        static node_pointer set_child1(node_pointer t, node_pointer\
    \ cid) {\n            return std::exchange(child1(t), cid);\n        }\n\n   \
    \     static bool& reversed(node_pointer t) {\n            return node(t)._rev;\n\
    \        }\n\n        static node_pointer update(node_pointer t) { // t : not\
    \ null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;\n\
    \            return t;\n        }\n        static bool push(node_pointer t) {\
    \ // t : not null\n            bool rev = t != null and std::exchange(reversed(t),\
    \ false);\n            if (rev) {\n                reverse_all(child0(t));\n \
    \               reverse_all(child1(t));\n            }\n            return rev;\n\
    \        }\n\n        static node_pointer empty_node() {\n            return null;\n\
    \        }\n        template <typename ...Args>\n        static node_pointer create_node(Args\
    \ &&...args) {\n            if (_erased.size()) {\n                node_pointer\
    \ res = _erased.back();\n                _erased.pop_back();\n               \
    \ node(res) = node_type(std::forward<Args>(args)...);\n                return\
    \ res;\n            } else {\n                node_pointer res = _nodes.size();\n\
    \                _nodes.emplace_back(std::forward<Args>(args)...);\n         \
    \       return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) {\n            _erased.push_back(t);\n        }\n        static void delete_tree(node_pointer\
    \ t) {\n            if (t == null) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            node_pointer res = empty_node();\n            for\
    \ (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {\n      \
    \          res = push_back(res, std::move(e));\n            }\n            return\
    \ res;\n        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, uint32_t k) {\n            if (t == null) {\n                return { null,\
    \ null };\n            }\n            node_type::push(t);\n            if (const\
    \ uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {\n                auto [ll,\
    \ lr] = split(child0(t), k);\n                set_child0(t, lr);\n           \
    \     return { ll, node_type::update(t) };\n            } else {\n           \
    \     auto [rl, rr] = split(child1(t), k - (lsiz + 1));\n                set_child1(t,\
    \ rl);\n                return { node_type::update(t), rr };\n            }\n\
    \        }\n        static std::tuple<node_pointer, node_pointer, node_pointer>\
    \ split(node_pointer t, uint32_t l, uint32_t r) {\n            auto [tlm, tr]\
    \ = split(t, r);\n            auto [tl, tm] = split(tlm, l);\n            return\
    \ { tl, tm, tr };\n        }\n        static node_pointer merge(node_pointer tl,\
    \ node_pointer tr) {\n            if (tl == null or tr == null) {\n          \
    \      return tl ^ tr ^ null;\n            }\n            if (priority(tl) < priority(tr))\
    \ {\n                node_type::push(tr);\n                set_child0(tr, merge(tl,\
    \ child0(tr)));\n                return node_type::update(tr);\n            }\
    \ else {\n                node_type::push(tl);\n                set_child1(tl,\
    \ merge(child1(tl), tr));\n                return node_type::update(tl);\n   \
    \         }\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n        static node_pointer insert_impl(node_pointer t, uint32_t k, node_pointer\
    \ new_node) {\n            if (t == null) {\n                return new_node;\n\
    \            }\n            if (priority(new_node) > priority(t)) {\n        \
    \        auto [tl, tr] = split(t, k);\n                set_child0(new_node, tl);\n\
    \                set_child1(new_node, tr);\n                return node_type::update(new_node);\n\
    \            } else {\n                node_type::push(t);\n                if\
    \ (const uint32_t lsiz = safe_size(child0(t)); k <= lsiz) {\n                \
    \    set_child0(t, insert_impl(child0(t), k, new_node));\n                } else\
    \ {\n                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1),\
    \ new_node));\n                }\n                return node_type::update(t);\n\
    \            }\n        }\n        template <typename ...Args>\n        static\
    \ node_pointer insert(node_pointer t, uint32_t k, Args &&...args) {\n        \
    \    return insert_impl(t, k, create_node(std::forward<Args>(args)...));\n   \
    \     }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        static node_pointer erase(node_pointer t, uint32_t k) {\n\
    \            node_type::push(t);\n            if (const uint32_t lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                delete_node(t);\n                return merge(child0(t),\
    \ child1(t));\n            } else if (k < lsiz) {\n                set_child0(t,\
    \ erase(child0(t), k));\n                return node_type::update(t);\n      \
    \      } else {\n                set_child1(t, erase(child1(t), k - (lsiz + 1)));\n\
    \                return node_type::update(t);\n            }\n        }\n    \
    \    static node_pointer pop_front(node_pointer t) {\n            return erase(t,\
    \ 0);\n        }\n        static node_pointer pop_back(node_pointer t) {\n   \
    \         return erase(t, safe_size(t) - 1);\n        }\n\n        static node_pointer\
    \ rotate(node_pointer t, uint32_t k) {\n            auto [tl, tr] = split(t, k);\n\
    \            return merge(tr, tl);\n        }\n\n        static value_type& get(node_pointer\
    \ t, uint32_t k) {\n            while (true) {\n                node_type::push(t);\n\
    \                if (const uint32_t lsiz = safe_size(child0(t)); k == lsiz) {\n\
    \                    return value(t);\n                } else if (k < lsiz) {\n\
    \                    t = child0(t);\n                } else {\n              \
    \      k -= lsiz + 1;\n                    t = child1(t);\n                }\n\
    \            }\n        }\n\n        template <typename Func>\n        static\
    \ node_pointer set_update(node_pointer t, uint32_t k, const Func& f) {\n     \
    \       node_type::push(t);\n            if (const uint32_t lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                value_type& val = value(t);\n                val\
    \ = f(const_cast<const value_type&>(val));\n            } else if (k < lsiz) {\n\
    \                set_child0(t, set_update(child0(t), k, f));\n            } else\
    \ {\n                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));\n\
    \            }\n            return node_type::update(t);\n        }\n\n      \
    \  static node_pointer reverse_all(node_pointer t) {\n            if (t != null)\
    \ {\n                reversed(t) ^= true;\n                std::swap(child0(t),\
    \ child1(t));\n            }\n            return t;\n        }\n        static\
    \ node_pointer reverse(node_pointer t, uint32_t l, uint32_t r) {\n           \
    \ auto [tl, tm, tr] = split(t, l, r);\n            return merge(tl, Derived::reverse_all(tm),\
    \ tr);\n        }\n\n        static std::vector<value_type> dump(node_pointer\
    \ t) {\n            std::vector<value_type> res;\n            res.reserve(safe_size(t));\n\
    \            auto rec = [&](auto rec, node_pointer t) -> void {\n            \
    \    if (t == null) return;\n                node_type::push(t);\n           \
    \     rec(rec, child0(t));\n                res.push_back(value(t));\n       \
    \         rec(rec, child1(t));\n            };\n            rec(rec, t);\n   \
    \         return res;\n        }\n\n        // Predicate : (value, index) -> {\
    \ false, true }\n        template <typename Predicate>\n        static uint32_t\
    \ binary_search(node_pointer t, const Predicate& f) {\n            int ng = -1,\
    \ ok = safe_size(t);\n            while (ok - ng > 1) {\n                node_type::push(t);\n\
    \                const int lsiz = safe_size(child0(t));\n                if (f(value(t),\
    \ ng + lsiz + 1)) {\n                    ok = ng + lsiz + 1;\n               \
    \     t = child0(t);\n                } else {\n                    ng += lsiz\
    \ + 1;\n                    t = child1(t);\n                }\n            }\n\
    \            return ok;\n        }\n\n        struct NodeIterator {\n        \
    \    std::vector<node_pointer> stk;\n\n            value_type& operator*() const\
    \ {\n                return value(stk.back());\n            }\n\n            NodeIterator&\
    \ operator++() {\n                node_pointer t = stk.back();\n             \
    \   if (child1(t) == null) {\n                    up</*suc = */true>();\n    \
    \            } else {\n                    down</*suc = */true>(child1(t), 0);\n\
    \                }\n                return *this;\n            }\n           \
    \ NodeIterator operator++(int) {\n                NodeIterator res = *this;\n\
    \                ++(*this);\n                return res;\n            }\n\n  \
    \          NodeIterator& operator--() {\n                node_pointer t = stk.back();\n\
    \                if (child0(t) == null) {\n                    up</*suc = */false>();\n\
    \                } else {\n                    down</*suc = */false>(child0(t),\
    \ 0);\n                }\n                return *this;\n            }\n     \
    \       NodeIterator operator--(int) {\n                NodeIterator res = *this;\n\
    \                --(*this);\n                return res;\n            }\n    \
    \    \n            NodeIterator& operator+=(int k) {\n                if (k >=\
    \ 0) suc(k);\n                else pre(-k);\n                return *this;\n \
    \           }\n            NodeIterator operator+(int k) {\n                NodeIterator\
    \ res = *this;\n                res += k;\n                return res;\n     \
    \       }\n\n            NodeIterator& operator-=(int k) {\n                return\
    \ *this += -k;\n            }\n            NodeIterator operator-(int k) {\n \
    \               return *this + (-k);\n            }\n\n            bool operator==(NodeIterator&\
    \ other) const {\n                return stk.empty() ? other.stk.empty() : other.stk.size()\
    \ and stk.back() == other.stk.back();\n            }\n        private:\n     \
    \       template <bool suc>\n            void up() {\n                node_pointer\
    \ t = stk.back();\n                do {\n                    stk.pop_back();\n\
    \                    if (t == child(stk.back(), not suc)) {\n                \
    \        break;\n                    }\n                    t = stk.back();\n\
    \                } while (stk.size());\n            }\n            template <bool\
    \ suc>\n            void down(node_pointer t, size_t k) {\n                while\
    \ (true) {\n                    node_type::push(t);\n                    stk.push_back(t);\n\
    \                    \n                    node_pointer siz = safe_size(child(t,\
    \ not suc));\n                    if (k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not suc);\n                    } else {\n                        k -= siz +\
    \ 1;\n                        t = child(t, suc);\n                    }\n    \
    \            }\n            }\n            void suc(size_t k) {\n            \
    \    while (k) {\n                    node_pointer t = stk.back();\n         \
    \           node_pointer rsiz = safe_size(child1(t));\n                    if\
    \ (k > rsiz) {\n                        up</*suc = */true>();\n              \
    \          k -= rsiz + 1;\n                    } else {\n                    \
    \    down</*suc = */true>(child1(t), k - 1);\n                        break;\n\
    \                    }\n                }\n            }\n            void pre(size_t\
    \ k) {\n                while (k) {\n                    node_pointer t = stk.back();\n\
    \                    node_pointer lsiz = safe_size(child0(t));\n             \
    \       if (k > lsiz) {\n                        up</*suc = */false>();\n    \
    \                    k -= lsiz + 1;\n                    } else {\n          \
    \              down</*suc = */false>(child0(t), k - 1);\n                    \
    \    break;\n                    }\n                }\n            }\n       \
    \ };\n\n        static NodeIterator begin(node_pointer t) {\n            std::vector<node_pointer>\
    \ stk;\n            while (t != null) {\n                node_type::push(t);\n\
    \                stk.push_back(t);\n                t = child0(t);\n         \
    \   }\n            return NodeIterator{ stk };\n        }\n        static NodeIterator\
    \ end(node_pointer t) {\n            return NodeIterator{};\n        }\n     \
    \   static NodeIterator kth_iterator(node_pointer t, uint32_t k) {\n         \
    \   std::vector<node_pointer> stk;\n            while (t != null) {\n        \
    \        node_type::push(t);\n                stk.push_back(t);\n            \
    \    uint32_t siz = safe_size(child0(t));\n                if (k == siz) {\n \
    \                   break;\n                } else if (k < siz) {\n          \
    \          t = child0(t);\n                } else {\n                    k -=\
    \ siz + 1;\n                    t = child1(t);\n                }\n          \
    \  }\n            return NodeIterator{ stk };\n        }\n    };\n} // namespace\
    \ suisen::internal::implicit_treap\n\n#endif // SUISEN_IMPLICIT_TREAP_BASE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/bbst/implicit_treap_base.hpp
  requiredBy:
  - library/datastructure/bbst/implicit_treap_segtree.hpp
  - library/datastructure/bbst/implicit_treap.hpp
  - library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/implicit_treap_dual_segtree.hpp
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/bbst/implicit_treap_dual_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/implicit_treap/dummy.test.cpp
  - test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
  - test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
  - test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/src/datastructure/bbst/implicit_treap_segtree/abc238_f.test.cpp
  - test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
documentation_of: library/datastructure/bbst/implicit_treap_base.hpp
layout: document
title: Implicit Treap Base
---
## Implicit Treap Base
