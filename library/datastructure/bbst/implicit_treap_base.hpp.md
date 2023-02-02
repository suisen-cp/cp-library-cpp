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
    #include <tuple>\n#include <vector>\n#include <utility>\n\nnamespace suisen::internal::implicit_treap\
    \ {\n    template <typename T, typename Derived>\n    struct Node {\n        using\
    \ random_engine = std::mt19937;\n        static inline random_engine rng{ std::random_device{}()\
    \ };\n\n        using node_type = Derived;\n        using node_pointer = uint32_t;\n\
    \        using priority_type = std::invoke_result_t<random_engine>;\n\n      \
    \  using size_type = uint32_t;\n\n        using difference_type = int32_t;\n \
    \       using value_type = T;\n        using pointer = value_type*;\n        using\
    \ const_pointer = const value_type*;\n        using reference = value_type&;\n\
    \        using const_reference = const value_type&;\n\n        static inline std::vector<node_type>\
    \ _nodes{};\n        static inline std::vector<node_pointer> _erased{};\n\n  \
    \      static constexpr node_pointer null = ~node_pointer(0);\n\n        node_pointer\
    \ _ch[2]{ null, null };\n        value_type _val;\n        size_type _size;\n\
    \        priority_type _priority;\n\n        bool _rev = false;\n\n        Node(const\
    \ value_type val = {}): _val(val), _size(1), _priority(rng()) {}\n\n        static\
    \ void reserve(size_type capacity) { _nodes.reserve(capacity); }\n\n        static\
    \ node_type& node(node_pointer t) { return _nodes[t]; }\n        static const\
    \ node_type& const_node(node_pointer t) { return _nodes[t]; }\n\n        static\
    \ value_type& value(node_pointer t) { return node(t)._val; }\n        static value_type\
    \ set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t),\
    \ new_val); }\n\n        static bool empty(node_pointer t) { return t == null;\
    \ }\n        static size_type& size(node_pointer t) { return node(t)._size; }\n\
    \        static size_type safe_size(node_pointer t) { return empty(t) ? 0 : size(t);\
    \ }\n\n        static priority_type priority(node_pointer t) { return const_node(t)._priority;\
    \ }\n\n        static node_pointer& child0(node_pointer t) { return node(t)._ch[0];\
    \ }\n        static node_pointer& child1(node_pointer t) { return node(t)._ch[1];\
    \ }\n        static node_pointer child(node_pointer t, bool b) { return node(t)._ch[b];\
    \ }\n        static node_pointer set_child0(node_pointer t, node_pointer cid)\
    \ { return std::exchange(child0(t), cid); }\n        static node_pointer set_child1(node_pointer\
    \ t, node_pointer cid) { return std::exchange(child1(t), cid); }\n\n        static\
    \ bool& reversed(node_pointer t) { return node(t)._rev; }\n\n        static node_pointer\
    \ update(node_pointer t) { // t : not null\n            size(t) = safe_size(child0(t))\
    \ + safe_size(child1(t)) + 1;\n            return t;\n        }\n        static\
    \ bool push(node_pointer t) { // t : not null\n            bool rev = t != null\
    \ and std::exchange(reversed(t), false);\n            if (rev) {\n           \
    \     reverse_all(child0(t));\n                reverse_all(child1(t));\n     \
    \       }\n            return rev;\n        }\n\n        static node_pointer empty_node()\
    \ { return null; }\n        template <typename ...Args>\n        static node_pointer\
    \ create_node(Args &&...args) {\n            if (_erased.size()) {\n         \
    \       node_pointer res = _erased.back();\n                _erased.pop_back();\n\
    \                node(res) = node_type(std::forward<Args>(args)...);\n       \
    \         return res;\n            } else {\n                node_pointer res\
    \ = _nodes.size();\n                _nodes.emplace_back(std::forward<Args>(args)...);\n\
    \                return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) { _erased.push_back(t); }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (t == null) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            node_pointer res = empty_node();\n            for\
    \ (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {\n      \
    \          res = push_back(res, std::move(e));\n            }\n            return\
    \ res;\n        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, size_type k) {\n            if (t == null) {\n                return { null,\
    \ null };\n            }\n            node_type::push(t);\n            if (const\
    \ size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n                auto [ll,\
    \ lr] = split(child0(t), k);\n                set_child0(t, lr);\n           \
    \     return { ll, node_type::update(t) };\n            } else {\n           \
    \     auto [rl, rr] = split(child1(t), k - (lsiz + 1));\n                set_child1(t,\
    \ rl);\n                return { node_type::update(t), rr };\n            }\n\
    \        }\n        static std::tuple<node_pointer, node_pointer, node_pointer>\
    \ split(node_pointer t, size_type l, size_type r) {\n            auto [tlm, tr]\
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
    \   }\n        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer\
    \ new_node) {\n            if (t == null) {\n                return new_node;\n\
    \            }\n            if (priority(new_node) > priority(t)) {\n        \
    \        auto [tl, tr] = split(t, k);\n                set_child0(new_node, tl);\n\
    \                set_child1(new_node, tr);\n                return node_type::update(new_node);\n\
    \            } else {\n                node_type::push(t);\n                if\
    \ (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n               \
    \     set_child0(t, insert_impl(child0(t), k, new_node));\n                } else\
    \ {\n                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1),\
    \ new_node));\n                }\n                return node_type::update(t);\n\
    \            }\n        }\n        template <typename ...Args>\n        static\
    \ node_pointer insert(node_pointer t, size_type k, Args &&...args) { return insert_impl(t,\
    \ k, create_node(std::forward<Args>(args)...)); }\n        template <typename\
    \ ...Args>\n        static node_pointer push_front(node_pointer t, Args &&...args)\
    \ { return insert(t, 0, std::forward<Args>(args)...); }\n        template <typename\
    \ ...Args>\n        static node_pointer push_back(node_pointer t, Args &&...args)\
    \ { return insert(t, safe_size(t), std::forward<Args>(args)...); }\n\n       \
    \ static node_pointer erase(node_pointer t, size_type k) {\n            node_type::push(t);\n\
    \            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n \
    \               delete_node(t);\n                return merge(child0(t), child1(t));\n\
    \            } else if (k < lsiz) {\n                set_child0(t, erase(child0(t),\
    \ k));\n                return node_type::update(t);\n            } else {\n \
    \               set_child1(t, erase(child1(t), k - (lsiz + 1)));\n           \
    \     return node_type::update(t);\n            }\n        }\n        static node_pointer\
    \ pop_front(node_pointer t) { return erase(t, 0); }\n        static node_pointer\
    \ pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }\n\n        static\
    \ node_pointer rotate(node_pointer t, size_type k) {\n            auto [tl, tr]\
    \ = split(t, k);\n            return merge(tr, tl);\n        }\n\n        static\
    \ value_type& get(node_pointer t, size_type k) {\n            while (true) {\n\
    \                node_type::push(t);\n                if (const size_type lsiz\
    \ = safe_size(child0(t)); k == lsiz) {\n                    return value(t);\n\
    \                } else if (k < lsiz) {\n                    t = child0(t);\n\
    \                } else {\n                    k -= lsiz + 1;\n              \
    \      t = child1(t);\n                }\n            }\n        }\n\n       \
    \ template <typename Func>\n        static node_pointer set_update(node_pointer\
    \ t, size_type k, const Func& f) {\n            node_type::push(t);\n        \
    \    if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n         \
    \       value_type& val = value(t);\n                val = f(const_cast<const\
    \ value_type&>(val));\n            } else if (k < lsiz) {\n                set_child0(t,\
    \ set_update(child0(t), k, f));\n            } else {\n                set_child1(t,\
    \ set_update(child1(t), k - (lsiz + 1), f));\n            }\n            return\
    \ node_type::update(t);\n        }\n\n        static node_pointer reverse_all(node_pointer\
    \ t) {\n            if (t != null) {\n                reversed(t) ^= true;\n \
    \               std::swap(child0(t), child1(t));\n            }\n            return\
    \ t;\n        }\n        static node_pointer reverse(node_pointer t, size_type\
    \ l, size_type r) {\n            auto [tl, tm, tr] = split(t, l, r);\n       \
    \     return merge(tl, Derived::reverse_all(tm), tr);\n        }\n\n        static\
    \ std::vector<value_type> dump(node_pointer t) {\n            std::vector<value_type>\
    \ res;\n            res.reserve(safe_size(t));\n            auto rec = [&](auto\
    \ rec, node_pointer t) -> void {\n                if (t == null) return;\n   \
    \             node_type::push(t);\n                rec(rec, child0(t));\n    \
    \            res.push_back(value(t));\n                rec(rec, child1(t));\n\
    \            };\n            rec(rec, t);\n            return res;\n        }\n\
    \n        // Predicate : (value, index) -> { false, true }\n        template <typename\
    \ Predicate>\n        static size_type binary_search(node_pointer t, const Predicate&\
    \ f) {\n            int ng = -1, ok = safe_size(t);\n            while (ok - ng\
    \ > 1) {\n                node_type::push(t);\n                if (const int root\
    \ = ng + safe_size(child0(t)) + 1; f(value(t), root)) {\n                    ok\
    \ = root, t = child0(t);\n                } else {\n                    ng = root,\
    \ t = child1(t);\n                }\n            }\n            return ok;\n \
    \       }\n\n        // comp(T t, U u) = (t < u)\n        template <typename U,\
    \ typename Compare = std::less<>>\n        static size_type lower_bound(node_pointer\
    \ t, const U& target, Compare comp = {}) {\n            return binary_search(t,\
    \ [&](const value_type& v, int) { return not comp(v, target); });\n        }\n\
    \        // comp(T u, U t) = (u < t)\n        template <typename U, typename Compare\
    \ = std::less<>>\n        static size_type upper_bound(node_pointer t, const U&\
    \ target, Compare comp = {}) {\n            return binary_search(t, [&](const\
    \ value_type& v, int) { return comp(target, v); });\n        }\n\n        template\
    \ <bool reversed_, bool constant_>\n        struct NodeIterator {\n          \
    \  static constexpr bool constant = constant_;\n            static constexpr bool\
    \ reversed = reversed_;\n\n            using difference_type = Node::difference_type;\n\
    \            using value_type = Node::value_type;\n            using pointer =\
    \ std::conditional_t<constant, Node::const_pointer, Node::pointer>;\n        \
    \    using reference = std::conditional_t<constant, Node::const_reference, Node::reference>;\n\
    \            using iterator_cateogory = std::random_access_iterator_tag;\n\n \
    \           NodeIterator(): root(null), index(0) {}\n            NodeIterator(node_pointer\
    \ root, size_type index): root(root), index(index) {}\n\n            reference\
    \ operator*() const { return value(stk.back()); }\n            reference operator[](difference_type\
    \ k) const { return *((*this) + k); }\n\n            NodeIterator& operator++()\
    \ { return *this += 1; }\n            NodeIterator& operator--() { return *this\
    \ -= 1; }\n            NodeIterator& operator+=(difference_type k) { return suc(+k),\
    \ * this; }\n            NodeIterator& operator-=(difference_type k) { return\
    \ suc(-k), * this; }\n            NodeIterator operator++(int) { NodeIterator\
    \ res = *this; ++(*this); return res; }\n            NodeIterator operator--(int)\
    \ { NodeIterator res = *this; --(*this); return res; }\n            friend NodeIterator\
    \ operator+(NodeIterator it, difference_type k) { return it += k; }\n        \
    \    friend NodeIterator operator+(difference_type k, NodeIterator it) { return\
    \ it += k; }\n            friend NodeIterator operator-(NodeIterator it, difference_type\
    \ k) { return it -= k; }\n\n            friend difference_type operator-(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index - rhs.index;\
    \ }\n\n            friend bool operator==(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index == rhs.index; }\n            friend bool operator!=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index != rhs.index;\
    \ }\n            friend bool operator<(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index < rhs.index; }\n            friend bool operator>(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index > rhs.index;\
    \ }\n            friend bool operator<=(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index <= rhs.index; }\n            friend bool operator>=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index >= rhs.index;\
    \ }\n\n            static NodeIterator kth_iter(node_pointer t, size_type k) {\n\
    \                NodeIterator it(t, k);\n                if (k == safe_size(t))\
    \ return it;\n                auto& stk = it.stk;\n                while (t !=\
    \ null) {\n                    node_type::push(t);\n                    stk.push_back(t);\n\
    \                    if (size_type siz = safe_size(child(t, reversed)); k == siz)\
    \ {\n                        break;\n                    } else if (k < siz) {\n\
    \                        t = child(t, reversed);\n                    } else {\n\
    \                        k -= siz + 1;\n                        t = child(t, not\
    \ reversed);\n                    }\n                }\n                return\
    \ it;\n            }\n        private:\n            node_pointer root;\n     \
    \       size_type index;\n            std::vector<node_pointer> stk;\n\n     \
    \       void up(const bool positive) {\n                node_pointer t = stk.back();\n\
    \                do {\n                    stk.pop_back();\n                 \
    \   if (stk.empty() or t == child(stk.back(), not positive)) break;\n        \
    \            t = stk.back();\n                } while (stk.size());\n        \
    \    }\n            void down(node_pointer t, size_type k, const bool positive)\
    \ {\n                while (true) {\n                    node_type::push(t);\n\
    \                    stk.push_back(t);\n\n                    if (size_type siz\
    \ = safe_size(child(t, not positive)); k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not positive);\n                    } else {\n                        k -= siz\
    \ + 1;\n                        t = child(t, positive);\n                    }\n\
    \                }\n            }\n            void suc(difference_type k) {\n\
    \                index += k;\n                const bool positive = k < 0 ? (k\
    \ = -k, reversed) : not reversed;\n                if (k and stk.empty()) {\n\
    \                    for (node_pointer t = root; t != null; t = child(t, not positive))\
    \ {\n                        node_type::push(t);\n                        stk.push_back(t);\n\
    \                    }\n                    --k;\n                }\n        \
    \        while (k) {\n                    node_pointer t = child(stk.back(), positive);\n\
    \                    if (difference_type siz = safe_size(t); k > siz) {\n    \
    \                    up(positive);\n                        k -= siz + 1;\n  \
    \                  } else {\n                        down(t, k - 1, positive);\n\
    \                        break;\n                    }\n                }\n  \
    \          }\n        };\n        using iterator = NodeIterator<false, false>;\n\
    \        using reverse_iterator = NodeIterator<true, false>;\n        using const_iterator\
    \ = NodeIterator<false, true>;\n        using const_reverse_iterator = NodeIterator<true,\
    \ true>;\n\n        static iterator begin(node_pointer t) { return ++iterator(t,\
    \ -1); }\n        static iterator end(node_pointer t) { return iterator(t, safe_size(t));\
    \ }\n        static iterator kth_iterator(node_pointer t, size_type k) { return\
    \ iterator::kth_iter(t, k); }\n        static reverse_iterator rbegin(node_pointer\
    \ t) { return ++reverse_iterator(t, -1); }\n        static reverse_iterator rend(node_pointer\
    \ t) { return reverse_iterator(t, safe_size(t)); }\n        static reverse_iterator\
    \ kth_reverse_iterator(node_pointer t, size_type k) { return reverse_iterator::kth_iter(t,\
    \ k); }\n        static const_iterator cbegin(node_pointer t) { return ++const_iterator(t,\
    \ -1); }\n        static const_iterator cend(node_pointer t) { return const_iterator(t,\
    \ safe_size(t)); }\n        static const_iterator kth_const_iterator(node_pointer\
    \ t, size_type k) { return const_iterator::kth_iter(t, k); }\n        static const_reverse_iterator\
    \ crbegin(node_pointer t) { return ++const_reverse_iterator(t, -1); }\n      \
    \  static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator(t,\
    \ safe_size(t)); }\n        static const_reverse_iterator kth_const_reverse_iterator(node_pointer\
    \ t, size_type k) { return const_reverse_iterator::kth_iter(t, k); }\n    };\n\
    } // namespace suisen::internal::implicit_treap\n\n\n"
  code: "#ifndef SUISEN_IMPLICIT_TREAP_BASE\n#define SUISEN_IMPLICIT_TREAP_BASE\n\n\
    #include <cassert>\n#include <cstdint>\n#include <string>\n#include <random>\n\
    #include <tuple>\n#include <vector>\n#include <utility>\n\nnamespace suisen::internal::implicit_treap\
    \ {\n    template <typename T, typename Derived>\n    struct Node {\n        using\
    \ random_engine = std::mt19937;\n        static inline random_engine rng{ std::random_device{}()\
    \ };\n\n        using node_type = Derived;\n        using node_pointer = uint32_t;\n\
    \        using priority_type = std::invoke_result_t<random_engine>;\n\n      \
    \  using size_type = uint32_t;\n\n        using difference_type = int32_t;\n \
    \       using value_type = T;\n        using pointer = value_type*;\n        using\
    \ const_pointer = const value_type*;\n        using reference = value_type&;\n\
    \        using const_reference = const value_type&;\n\n        static inline std::vector<node_type>\
    \ _nodes{};\n        static inline std::vector<node_pointer> _erased{};\n\n  \
    \      static constexpr node_pointer null = ~node_pointer(0);\n\n        node_pointer\
    \ _ch[2]{ null, null };\n        value_type _val;\n        size_type _size;\n\
    \        priority_type _priority;\n\n        bool _rev = false;\n\n        Node(const\
    \ value_type val = {}): _val(val), _size(1), _priority(rng()) {}\n\n        static\
    \ void reserve(size_type capacity) { _nodes.reserve(capacity); }\n\n        static\
    \ node_type& node(node_pointer t) { return _nodes[t]; }\n        static const\
    \ node_type& const_node(node_pointer t) { return _nodes[t]; }\n\n        static\
    \ value_type& value(node_pointer t) { return node(t)._val; }\n        static value_type\
    \ set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t),\
    \ new_val); }\n\n        static bool empty(node_pointer t) { return t == null;\
    \ }\n        static size_type& size(node_pointer t) { return node(t)._size; }\n\
    \        static size_type safe_size(node_pointer t) { return empty(t) ? 0 : size(t);\
    \ }\n\n        static priority_type priority(node_pointer t) { return const_node(t)._priority;\
    \ }\n\n        static node_pointer& child0(node_pointer t) { return node(t)._ch[0];\
    \ }\n        static node_pointer& child1(node_pointer t) { return node(t)._ch[1];\
    \ }\n        static node_pointer child(node_pointer t, bool b) { return node(t)._ch[b];\
    \ }\n        static node_pointer set_child0(node_pointer t, node_pointer cid)\
    \ { return std::exchange(child0(t), cid); }\n        static node_pointer set_child1(node_pointer\
    \ t, node_pointer cid) { return std::exchange(child1(t), cid); }\n\n        static\
    \ bool& reversed(node_pointer t) { return node(t)._rev; }\n\n        static node_pointer\
    \ update(node_pointer t) { // t : not null\n            size(t) = safe_size(child0(t))\
    \ + safe_size(child1(t)) + 1;\n            return t;\n        }\n        static\
    \ bool push(node_pointer t) { // t : not null\n            bool rev = t != null\
    \ and std::exchange(reversed(t), false);\n            if (rev) {\n           \
    \     reverse_all(child0(t));\n                reverse_all(child1(t));\n     \
    \       }\n            return rev;\n        }\n\n        static node_pointer empty_node()\
    \ { return null; }\n        template <typename ...Args>\n        static node_pointer\
    \ create_node(Args &&...args) {\n            if (_erased.size()) {\n         \
    \       node_pointer res = _erased.back();\n                _erased.pop_back();\n\
    \                node(res) = node_type(std::forward<Args>(args)...);\n       \
    \         return res;\n            } else {\n                node_pointer res\
    \ = _nodes.size();\n                _nodes.emplace_back(std::forward<Args>(args)...);\n\
    \                return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) { _erased.push_back(t); }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (t == null) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            node_pointer res = empty_node();\n            for\
    \ (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {\n      \
    \          res = push_back(res, std::move(e));\n            }\n            return\
    \ res;\n        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, size_type k) {\n            if (t == null) {\n                return { null,\
    \ null };\n            }\n            node_type::push(t);\n            if (const\
    \ size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n                auto [ll,\
    \ lr] = split(child0(t), k);\n                set_child0(t, lr);\n           \
    \     return { ll, node_type::update(t) };\n            } else {\n           \
    \     auto [rl, rr] = split(child1(t), k - (lsiz + 1));\n                set_child1(t,\
    \ rl);\n                return { node_type::update(t), rr };\n            }\n\
    \        }\n        static std::tuple<node_pointer, node_pointer, node_pointer>\
    \ split(node_pointer t, size_type l, size_type r) {\n            auto [tlm, tr]\
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
    \   }\n        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer\
    \ new_node) {\n            if (t == null) {\n                return new_node;\n\
    \            }\n            if (priority(new_node) > priority(t)) {\n        \
    \        auto [tl, tr] = split(t, k);\n                set_child0(new_node, tl);\n\
    \                set_child1(new_node, tr);\n                return node_type::update(new_node);\n\
    \            } else {\n                node_type::push(t);\n                if\
    \ (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n               \
    \     set_child0(t, insert_impl(child0(t), k, new_node));\n                } else\
    \ {\n                    set_child1(t, insert_impl(child1(t), k - (lsiz + 1),\
    \ new_node));\n                }\n                return node_type::update(t);\n\
    \            }\n        }\n        template <typename ...Args>\n        static\
    \ node_pointer insert(node_pointer t, size_type k, Args &&...args) { return insert_impl(t,\
    \ k, create_node(std::forward<Args>(args)...)); }\n        template <typename\
    \ ...Args>\n        static node_pointer push_front(node_pointer t, Args &&...args)\
    \ { return insert(t, 0, std::forward<Args>(args)...); }\n        template <typename\
    \ ...Args>\n        static node_pointer push_back(node_pointer t, Args &&...args)\
    \ { return insert(t, safe_size(t), std::forward<Args>(args)...); }\n\n       \
    \ static node_pointer erase(node_pointer t, size_type k) {\n            node_type::push(t);\n\
    \            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n \
    \               delete_node(t);\n                return merge(child0(t), child1(t));\n\
    \            } else if (k < lsiz) {\n                set_child0(t, erase(child0(t),\
    \ k));\n                return node_type::update(t);\n            } else {\n \
    \               set_child1(t, erase(child1(t), k - (lsiz + 1)));\n           \
    \     return node_type::update(t);\n            }\n        }\n        static node_pointer\
    \ pop_front(node_pointer t) { return erase(t, 0); }\n        static node_pointer\
    \ pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }\n\n        static\
    \ node_pointer rotate(node_pointer t, size_type k) {\n            auto [tl, tr]\
    \ = split(t, k);\n            return merge(tr, tl);\n        }\n\n        static\
    \ value_type& get(node_pointer t, size_type k) {\n            while (true) {\n\
    \                node_type::push(t);\n                if (const size_type lsiz\
    \ = safe_size(child0(t)); k == lsiz) {\n                    return value(t);\n\
    \                } else if (k < lsiz) {\n                    t = child0(t);\n\
    \                } else {\n                    k -= lsiz + 1;\n              \
    \      t = child1(t);\n                }\n            }\n        }\n\n       \
    \ template <typename Func>\n        static node_pointer set_update(node_pointer\
    \ t, size_type k, const Func& f) {\n            node_type::push(t);\n        \
    \    if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n         \
    \       value_type& val = value(t);\n                val = f(const_cast<const\
    \ value_type&>(val));\n            } else if (k < lsiz) {\n                set_child0(t,\
    \ set_update(child0(t), k, f));\n            } else {\n                set_child1(t,\
    \ set_update(child1(t), k - (lsiz + 1), f));\n            }\n            return\
    \ node_type::update(t);\n        }\n\n        static node_pointer reverse_all(node_pointer\
    \ t) {\n            if (t != null) {\n                reversed(t) ^= true;\n \
    \               std::swap(child0(t), child1(t));\n            }\n            return\
    \ t;\n        }\n        static node_pointer reverse(node_pointer t, size_type\
    \ l, size_type r) {\n            auto [tl, tm, tr] = split(t, l, r);\n       \
    \     return merge(tl, Derived::reverse_all(tm), tr);\n        }\n\n        static\
    \ std::vector<value_type> dump(node_pointer t) {\n            std::vector<value_type>\
    \ res;\n            res.reserve(safe_size(t));\n            auto rec = [&](auto\
    \ rec, node_pointer t) -> void {\n                if (t == null) return;\n   \
    \             node_type::push(t);\n                rec(rec, child0(t));\n    \
    \            res.push_back(value(t));\n                rec(rec, child1(t));\n\
    \            };\n            rec(rec, t);\n            return res;\n        }\n\
    \n        // Predicate : (value, index) -> { false, true }\n        template <typename\
    \ Predicate>\n        static size_type binary_search(node_pointer t, const Predicate&\
    \ f) {\n            int ng = -1, ok = safe_size(t);\n            while (ok - ng\
    \ > 1) {\n                node_type::push(t);\n                if (const int root\
    \ = ng + safe_size(child0(t)) + 1; f(value(t), root)) {\n                    ok\
    \ = root, t = child0(t);\n                } else {\n                    ng = root,\
    \ t = child1(t);\n                }\n            }\n            return ok;\n \
    \       }\n\n        // comp(T t, U u) = (t < u)\n        template <typename U,\
    \ typename Compare = std::less<>>\n        static size_type lower_bound(node_pointer\
    \ t, const U& target, Compare comp = {}) {\n            return binary_search(t,\
    \ [&](const value_type& v, int) { return not comp(v, target); });\n        }\n\
    \        // comp(T u, U t) = (u < t)\n        template <typename U, typename Compare\
    \ = std::less<>>\n        static size_type upper_bound(node_pointer t, const U&\
    \ target, Compare comp = {}) {\n            return binary_search(t, [&](const\
    \ value_type& v, int) { return comp(target, v); });\n        }\n\n        template\
    \ <bool reversed_, bool constant_>\n        struct NodeIterator {\n          \
    \  static constexpr bool constant = constant_;\n            static constexpr bool\
    \ reversed = reversed_;\n\n            using difference_type = Node::difference_type;\n\
    \            using value_type = Node::value_type;\n            using pointer =\
    \ std::conditional_t<constant, Node::const_pointer, Node::pointer>;\n        \
    \    using reference = std::conditional_t<constant, Node::const_reference, Node::reference>;\n\
    \            using iterator_cateogory = std::random_access_iterator_tag;\n\n \
    \           NodeIterator(): root(null), index(0) {}\n            NodeIterator(node_pointer\
    \ root, size_type index): root(root), index(index) {}\n\n            reference\
    \ operator*() const { return value(stk.back()); }\n            reference operator[](difference_type\
    \ k) const { return *((*this) + k); }\n\n            NodeIterator& operator++()\
    \ { return *this += 1; }\n            NodeIterator& operator--() { return *this\
    \ -= 1; }\n            NodeIterator& operator+=(difference_type k) { return suc(+k),\
    \ * this; }\n            NodeIterator& operator-=(difference_type k) { return\
    \ suc(-k), * this; }\n            NodeIterator operator++(int) { NodeIterator\
    \ res = *this; ++(*this); return res; }\n            NodeIterator operator--(int)\
    \ { NodeIterator res = *this; --(*this); return res; }\n            friend NodeIterator\
    \ operator+(NodeIterator it, difference_type k) { return it += k; }\n        \
    \    friend NodeIterator operator+(difference_type k, NodeIterator it) { return\
    \ it += k; }\n            friend NodeIterator operator-(NodeIterator it, difference_type\
    \ k) { return it -= k; }\n\n            friend difference_type operator-(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index - rhs.index;\
    \ }\n\n            friend bool operator==(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index == rhs.index; }\n            friend bool operator!=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index != rhs.index;\
    \ }\n            friend bool operator<(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index < rhs.index; }\n            friend bool operator>(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index > rhs.index;\
    \ }\n            friend bool operator<=(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs.index <= rhs.index; }\n            friend bool operator>=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index >= rhs.index;\
    \ }\n\n            static NodeIterator kth_iter(node_pointer t, size_type k) {\n\
    \                NodeIterator it(t, k);\n                if (k == safe_size(t))\
    \ return it;\n                auto& stk = it.stk;\n                while (t !=\
    \ null) {\n                    node_type::push(t);\n                    stk.push_back(t);\n\
    \                    if (size_type siz = safe_size(child(t, reversed)); k == siz)\
    \ {\n                        break;\n                    } else if (k < siz) {\n\
    \                        t = child(t, reversed);\n                    } else {\n\
    \                        k -= siz + 1;\n                        t = child(t, not\
    \ reversed);\n                    }\n                }\n                return\
    \ it;\n            }\n        private:\n            node_pointer root;\n     \
    \       size_type index;\n            std::vector<node_pointer> stk;\n\n     \
    \       void up(const bool positive) {\n                node_pointer t = stk.back();\n\
    \                do {\n                    stk.pop_back();\n                 \
    \   if (stk.empty() or t == child(stk.back(), not positive)) break;\n        \
    \            t = stk.back();\n                } while (stk.size());\n        \
    \    }\n            void down(node_pointer t, size_type k, const bool positive)\
    \ {\n                while (true) {\n                    node_type::push(t);\n\
    \                    stk.push_back(t);\n\n                    if (size_type siz\
    \ = safe_size(child(t, not positive)); k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not positive);\n                    } else {\n                        k -= siz\
    \ + 1;\n                        t = child(t, positive);\n                    }\n\
    \                }\n            }\n            void suc(difference_type k) {\n\
    \                index += k;\n                const bool positive = k < 0 ? (k\
    \ = -k, reversed) : not reversed;\n                if (k and stk.empty()) {\n\
    \                    for (node_pointer t = root; t != null; t = child(t, not positive))\
    \ {\n                        node_type::push(t);\n                        stk.push_back(t);\n\
    \                    }\n                    --k;\n                }\n        \
    \        while (k) {\n                    node_pointer t = child(stk.back(), positive);\n\
    \                    if (difference_type siz = safe_size(t); k > siz) {\n    \
    \                    up(positive);\n                        k -= siz + 1;\n  \
    \                  } else {\n                        down(t, k - 1, positive);\n\
    \                        break;\n                    }\n                }\n  \
    \          }\n        };\n        using iterator = NodeIterator<false, false>;\n\
    \        using reverse_iterator = NodeIterator<true, false>;\n        using const_iterator\
    \ = NodeIterator<false, true>;\n        using const_reverse_iterator = NodeIterator<true,\
    \ true>;\n\n        static iterator begin(node_pointer t) { return ++iterator(t,\
    \ -1); }\n        static iterator end(node_pointer t) { return iterator(t, safe_size(t));\
    \ }\n        static iterator kth_iterator(node_pointer t, size_type k) { return\
    \ iterator::kth_iter(t, k); }\n        static reverse_iterator rbegin(node_pointer\
    \ t) { return ++reverse_iterator(t, -1); }\n        static reverse_iterator rend(node_pointer\
    \ t) { return reverse_iterator(t, safe_size(t)); }\n        static reverse_iterator\
    \ kth_reverse_iterator(node_pointer t, size_type k) { return reverse_iterator::kth_iter(t,\
    \ k); }\n        static const_iterator cbegin(node_pointer t) { return ++const_iterator(t,\
    \ -1); }\n        static const_iterator cend(node_pointer t) { return const_iterator(t,\
    \ safe_size(t)); }\n        static const_iterator kth_const_iterator(node_pointer\
    \ t, size_type k) { return const_iterator::kth_iter(t, k); }\n        static const_reverse_iterator\
    \ crbegin(node_pointer t) { return ++const_reverse_iterator(t, -1); }\n      \
    \  static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator(t,\
    \ safe_size(t)); }\n        static const_reverse_iterator kth_const_reverse_iterator(node_pointer\
    \ t, size_type k) { return const_reverse_iterator::kth_iter(t, k); }\n    };\n\
    } // namespace suisen::internal::implicit_treap\n\n#endif // SUISEN_IMPLICIT_TREAP_BASE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/datastructure/bbst/implicit_treap_base.hpp
  requiredBy:
  - library/datastructure/bbst/implicit_treap_segtree.hpp
  - library/datastructure/bbst/implicit_treap.hpp
  - library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/implicit_treap_dual_segtree.hpp
  timestamp: '2023-02-02 07:52:53+09:00'
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
