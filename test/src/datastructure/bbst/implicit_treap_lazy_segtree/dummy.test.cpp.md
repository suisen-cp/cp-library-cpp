---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_base.hpp
    title: Implicit Treap Base
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
    title: Implicit Treap Lazy Segtree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#line 1 \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\n\n\n\
    #include <cassert>\n#include <cstdint>\n#include <optional>\n#include <string>\n\
    #include <random>\n#include <tuple>\n#line 11 \"library/datastructure/bbst/implicit_treap_base.hpp\"\
    \n#include <utility>\n\nnamespace suisen::internal::implicit_treap {\n    template\
    \ <typename T, typename Derived>\n    struct Node {\n        using random_engine\
    \ = std::mt19937;\n        static inline random_engine rng{ std::random_device{}()\
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
    \ null };\n            }\n            node_type::push(t);\n            if (k ==\
    \ 0) {\n                return { null, t };\n            }\n            if (k\
    \ == size(t)) {\n                return { t, null };\n            }\n        \
    \    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n         \
    \       auto [ll, lr] = split(child0(t), k);\n                set_child0(t, lr);\n\
    \                return { ll, node_type::update(t) };\n            } else {\n\
    \                auto [rl, rr] = split(child1(t), k - (lsiz + 1));\n         \
    \       set_child1(t, rl);\n                return { node_type::update(t), rr\
    \ };\n            }\n        }\n        static std::tuple<node_pointer, node_pointer,\
    \ node_pointer> split(node_pointer t, size_type l, size_type r) {\n          \
    \  auto [tlm, tr] = split(t, r);\n            auto [tl, tm] = split(tlm, l);\n\
    \            return { tl, tm, tr };\n        }\n        // Split immediately before\
    \ the first element that satisfies the condition.\n        template <typename\
    \ Predicate>\n        static std::pair<node_pointer, node_pointer> split_binary_search(node_pointer\
    \ t, const Predicate& f) {\n            if (t == null) {\n                return\
    \ { null, null };\n            }\n            node_type::push(t);\n          \
    \  if (f(value(t))) {\n                auto [ll, lr] = split_binary_search(child0(t),\
    \ f);\n                set_child0(t, lr);\n                return { ll, node_type::update(t)\
    \ };\n            } else {\n                auto [rl, rr] = split_binary_search(child1(t),\
    \ f);\n                set_child1(t, rl);\n                return { node_type::update(t),\
    \ rr };\n            }\n        }\n\n        template <typename Compare = std::less<>>\n\
    \        static std::pair<node_pointer, node_pointer> split_lower_bound(node_pointer\
    \ t, const value_type& target, const Compare& comp) {\n            return split_binary_search(t,\
    \ [&](const value_type& v) { return not comp(v, target); });\n        }\n    \
    \    template <typename Compare = std::less<>>\n        static std::pair<node_pointer,\
    \ node_pointer> split_upper_bound(node_pointer t, const value_type& target, const\
    \ Compare& comp) {\n            return split_binary_search(t, [&](const value_type&\
    \ v) { return comp(target, v); });\n        }\n\n        static node_pointer merge(node_pointer\
    \ tl, node_pointer tr) {\n            if (tl == null or tr == null) {\n      \
    \          return tl ^ tr ^ null;\n            }\n            if (priority(tl)\
    \ < priority(tr)) {\n                node_type::push(tr);\n                set_child0(tr,\
    \ merge(tl, child0(tr)));\n                return node_type::update(tr);\n   \
    \         } else {\n                node_type::push(tl);\n                set_child1(tl,\
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
    \ node_pointer insert(node_pointer t, size_type k, Args &&...args) {\n       \
    \     return insert_impl(t, k, create_node(std::forward<Args>(args)...));\n  \
    \      }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        // Insert a new node immediately before the first element\
    \ that satisfies the condition.\n        // Returns { node, position to insert\
    \ }\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer\
    \ new_node) {\n            if (t == null) {\n                return { new_node,\
    \ 0 };\n            }\n            if (priority(new_node) > priority(t)) {\n \
    \               auto [tl, tr] = split_binary_search(t, f);\n                set_child0(new_node,\
    \ tl);\n                set_child1(new_node, tr);\n                return { node_type::update(new_node),\
    \ safe_size(tl) };\n            } else {\n                node_type::push(t);\n\
    \                if (f(value(t))) {\n                    auto [c0, pos] = insert_binary_search_impl(child0(t),\
    \ f, new_node);\n                    set_child0(t, c0);\n                    return\
    \ { node_type::update(t), pos };\n                } else {\n                 \
    \   auto [c1, pos] = insert_binary_search_impl(child1(t), f, new_node);\n    \
    \                set_child1(t, c1);\n                    return { node_type::update(t),\
    \ pos + safe_size(child0(t)) + 1 };\n                }\n            }\n      \
    \  }\n        template <typename Predicate, typename ...Args>\n        static\
    \ std::pair<node_pointer, size_type> insert_binary_search(node_pointer t, const\
    \ Predicate& f, Args &&...args) {\n            return insert_binary_search_impl(t,\
    \ f, create_node(std::forward<Args>(args)...));\n        }\n        template <typename\
    \ Compare = std::less<>>\n        static std::pair<node_pointer, size_type> insert_lower_bound(node_pointer\
    \ t, const value_type& v, Compare comp) {\n            return insert_binary_search(t,\
    \ [&](const value_type& x) { return not comp(x, v); }, v);\n        }\n      \
    \  template <typename Compare = std::less<>>\n        static std::pair<node_pointer,\
    \ size_type> insert_upper_bound(node_pointer t, const value_type& v, Compare comp)\
    \ {\n            return insert_binary_search(t, [&](const value_type& x) { return\
    \ comp(v, x); }, v);\n        }\n\n        static std::pair<node_pointer, value_type>\
    \ erase(node_pointer t, size_type k) {\n            node_type::push(t);\n    \
    \        if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n     \
    \           delete_node(t);\n                return { merge(child0(t), child1(t)),\
    \ std::move(value(t)) };\n            } else if (k < lsiz) {\n               \
    \ auto [c0, v] = erase(child0(t), k);\n                set_child0(t, c0);\n  \
    \              return { node_type::update(t), std::move(v) };\n            } else\
    \ {\n                auto [c1, v] = erase(child1(t), k - (lsiz + 1));\n      \
    \          set_child1(t, c1);\n                return { node_type::update(t),\
    \ std::move(v) };\n            }\n        }\n        static std::pair<node_pointer,\
    \ value_type> pop_front(node_pointer t) { return erase(t, 0); }\n        static\
    \ std::pair<node_pointer, value_type> pop_back(node_pointer t) { return erase(t,\
    \ safe_size(t) - 1); }\n\n        // Erase the first element that satisfies the\
    \ condition f if it also satisfies the condition g.\n        // returns { node,\
    \ optional(position, value) }\n        template <typename Predicate, typename\
    \ RemovePredicate>\n        static std::pair<node_pointer, std::optional<std::pair<size_type,\
    \ value_type>>> erase_binary_search(node_pointer t, const Predicate& f, const\
    \ RemovePredicate& g) {\n            if (t == null) return { null, std::nullopt\
    \ };\n            node_type::push(t);\n            if (f(value(t))) {\n      \
    \          auto [c0, erased] = erase_binary_search(child0(t), f, g);\n       \
    \         if (erased) {\n                    set_child0(t, c0);\n            \
    \        return { node_type::update(t), std::move(erased) };\n               \
    \ } else if (g(value(t))) {\n                    delete_node(t);\n           \
    \         std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)),\
    \ std::move(value(t)) };\n                    return { merge(child0(t), child1(t)),\
    \ std::move(erased_entry) };\n                } else {\n                    return\
    \ { t, std::nullopt };\n                }\n            } else {\n            \
    \    auto [c1, erased] = erase_binary_search(child1(t), f, g);\n             \
    \   if (erased) {\n                    set_child1(t, c1);\n                  \
    \  size_type &pos = erased->first;\n                    pos += safe_size(child0(t))\
    \ + 1;\n                    return { node_type::update(t), std::move(erased) };\n\
    \                } else {\n                    return { t, std::nullopt };\n \
    \               }\n            }\n        }\n        template <typename Compare\
    \ = std::less<>>\n        static std::pair<node_pointer, std::optional<std::pair<size_type,\
    \ value_type>>> erase_lower_bound(node_pointer t, const value_type& v, Compare\
    \ comp) {\n            return erase_binary_search(\n                t,\n     \
    \           [&](const value_type& x) { return not comp(x, v); },\n           \
    \     [] { return true; }\n            );\n        }\n        template <typename\
    \ Compare = std::less<>>\n        static std::pair<node_pointer, std::optional<std::pair<size_type,\
    \ value_type>>> erase_upper_bound(node_pointer t, const value_type& v, Compare\
    \ comp) {\n            return erase_binary_search(\n                t,\n     \
    \           [&](const value_type& x) { return comp(v, x); },\n               \
    \ [] { return true; }\n            );\n        }\n        template <typename Compare\
    \ = std::less<>>\n        static std::pair<node_pointer, std::optional<std::pair<size_type,\
    \ value_type>>> erase_if_exists(node_pointer t, const value_type& v, Compare comp)\
    \ {\n            return erase_binary_search(\n                t,\n           \
    \     [&](const value_type& x) { return not comp(x, v); },\n                [&](const\
    \ value_type& x) { return not comp(v, x); }\n            );\n        }\n\n   \
    \     static node_pointer rotate(node_pointer t, size_type k) {\n            auto\
    \ [tl, tr] = split(t, k);\n            return merge(tr, tl);\n        }\n    \
    \    static node_pointer rotate(node_pointer t, size_type l, size_type m, size_type\
    \ r) {\n            auto [tl, tm, tr] = split(t, l, r);\n            return merge(tl,\
    \ rotate(tm, m - l), tr);\n        }\n\n        static value_type& get(node_pointer\
    \ t, size_type k) {\n            while (true) {\n                node_type::push(t);\n\
    \                if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {\n\
    \                    return value(t);\n                } else if (k < lsiz) {\n\
    \                    t = child0(t);\n                } else {\n              \
    \      k -= lsiz + 1;\n                    t = child1(t);\n                }\n\
    \            }\n        }\n\n        template <typename Func>\n        static\
    \ node_pointer set_update(node_pointer t, size_type k, const Func& f) {\n    \
    \        node_type::push(t);\n            if (const size_type lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                value_type& val = value(t);\n                val\
    \ = f(const_cast<const value_type&>(val));\n            } else if (k < lsiz) {\n\
    \                set_child0(t, set_update(child0(t), k, f));\n            } else\
    \ {\n                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));\n\
    \            }\n            return node_type::update(t);\n        }\n\n      \
    \  static node_pointer reverse_all(node_pointer t) {\n            if (t != null)\
    \ {\n                reversed(t) ^= true;\n                std::swap(child0(t),\
    \ child1(t));\n            }\n            return t;\n        }\n        static\
    \ node_pointer reverse(node_pointer t, size_type l, size_type r) {\n         \
    \   auto [tl, tm, tr] = split(t, l, r);\n            return merge(tl, Derived::reverse_all(tm),\
    \ tr);\n        }\n\n        static std::vector<value_type> dump(node_pointer\
    \ t) {\n            std::vector<value_type> res;\n            res.reserve(safe_size(t));\n\
    \            auto rec = [&](auto rec, node_pointer t) -> void {\n            \
    \    if (t == null) return;\n                node_type::push(t);\n           \
    \     rec(rec, child0(t));\n                res.push_back(value(t));\n       \
    \         rec(rec, child1(t));\n            };\n            rec(rec, t);\n   \
    \         return res;\n        }\n\n        // Find the first element that satisfies\
    \ the condition f : (value, index) -> { false, true }.\n        // Returns { optional(value),\
    \ position }\n        template <typename Predicate>\n        static std::pair<size_type,\
    \ std::optional<value_type>> binary_search(node_pointer t, const Predicate& f)\
    \ {\n            node_pointer res = null;\n            int ng = -1, ok = safe_size(t);\n\
    \            while (ok - ng > 1) {\n                node_type::push(t);\n    \
    \            if (const int root = ng + safe_size(child0(t)) + 1; f(value(t), root))\
    \ {\n                    res = t;\n                    ok = root, t = child0(t);\n\
    \                } else {\n                    ng = root, t = child1(t);\n   \
    \             }\n            }\n            if (res == null) {\n             \
    \   return { ok, std::nullopt };\n            } else {\n                return\
    \ { ok, value(res) };\n            }\n        }\n\n        // comp(T t, U u) =\
    \ (t < u)\n        template <typename U, typename Compare = std::less<>>\n   \
    \     static std::pair<size_type, std::optional<value_type>> lower_bound(node_pointer\
    \ t, const U& target, Compare comp) {\n            return binary_search(t, [&](const\
    \ value_type& v, int) { return not comp(v, target); });\n        }\n        //\
    \ comp(T u, U t) = (u < t)\n        template <typename U, typename Compare = std::less<>>\n\
    \        static std::pair<size_type, std::optional<value_type>> upper_bound(node_pointer\
    \ t, const U& target, Compare comp) {\n            return binary_search(t, [&](const\
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
    } // namespace suisen::internal::implicit_treap\n\n\n#line 5 \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F,\
    \ T, int), F(*composition)(F, F), F(*id)()>\n        struct RangeOperateRangeProductNode:\
    \ Node<T, RangeOperateRangeProductNode<T, op, e, toggle, F, mapping, composition,\
    \ id>> {\n            using base = Node<T, RangeOperateRangeProductNode<T, op,\
    \ e, toggle, F, mapping, composition, id>>;\n            using node_pointer =\
    \ typename base::node_pointer;\n            using value_type = typename base::value_type;\n\
    \            using operator_type = F;\n\n            value_type _sum;\n      \
    \      operator_type _laz;\n            RangeOperateRangeProductNode(const value_type&\
    \ val): base(val), _sum(val), _laz(id()) {}\n\n            // ----- override -----\
    \ //\n            static node_pointer update(node_pointer t) {\n             \
    \   base::update(t);\n                prod_all(t) = op(op(safe_prod(base::child0(t)),\
    \ base::value(t)), safe_prod(base::child1(t)));\n                return t;\n \
    \           }\n            static void push(node_pointer t) {\n              \
    \  base::push(t);\n                operator_type& laz = lazy(t);\n           \
    \     apply_all(base::child0(t), laz);\n                apply_all(base::child1(t),\
    \ laz);\n                laz = id();\n            }\n            static node_pointer\
    \ reverse_all(node_pointer t) {\n                if (t != base::null) {\n    \
    \                base::reversed(t) ^= true;\n                    std::swap(base::child0(t),\
    \ base::child1(t));\n                    value_type& sum = prod_all(t);\n    \
    \                sum = toggle(sum);\n                }\n                return\
    \ t;\n            }\n\n            // ----- new features ----- //\n          \
    \  static value_type& prod_all(node_pointer t) {\n                return base::node(t)._sum;\n\
    \            }\n            static value_type safe_prod(node_pointer t) {\n  \
    \              return t == base::null ? e() : prod_all(t);\n            }\n  \
    \          static std::pair<node_pointer, value_type> prod(node_pointer t, size_t\
    \ l, size_t r) {\n                auto [tl, tm, tr] = base::split(t, l, r);\n\
    \                value_type res = safe_prod(tm);\n                return { base::merge(tl,\
    \ tm, tr), res };\n            }\n\n            static operator_type& lazy(node_pointer\
    \ t) {\n                return base::node(t)._laz;\n            }\n          \
    \  static node_pointer apply_all(node_pointer t, const operator_type& f) {\n \
    \               if (t != base::null) {\n                    operator_type& laz\
    \ = lazy(t);\n                    laz = composition(f, laz);\n               \
    \     value_type& val = base::value(t);\n                    val = mapping(f,\
    \ val, 1);\n                    value_type& sum = prod_all(t);\n             \
    \       sum = mapping(f, sum, base::size(t));\n                }\n           \
    \     return t;\n            }\n            static node_pointer apply(node_pointer\
    \ t, size_t l, size_t r, const operator_type& f) {\n                auto [tl,\
    \ tm, tr] = base::split(t, l, r);\n                return base::merge(tl, apply_all(tm,\
    \ f), tr);\n            }\n\n            template <typename Func>\n          \
    \  static node_pointer set(node_pointer t, size_t k, const Func& f) {\n      \
    \          return base::set_update(t, k, f);\n            }\n\n            template\
    \ <typename Predicate>\n            static uint32_t max_right(node_pointer t,\
    \ const Predicate& f) {\n                value_type sum = e();\n             \
    \   assert(f(sum));\n\n                uint32_t r = 0;\n                while\
    \ (t != base::null) {\n                    push(t);\n\n                    node_pointer\
    \ lch = base::child0(t);\n\n                    value_type nxt_sum = op(sum, safe_prod(lch));\n\
    \                    if (f(nxt_sum)) {\n                        r += base::safe_size(lch);\n\
    \                        sum = op(nxt_sum, base::value(t));\n                \
    \        if (f(sum)) {\n                            ++r;\n                   \
    \         t = base::child1(t);\n                        } else {\n           \
    \                 break;\n                        }\n                    } else\
    \ {\n                        t = lch;\n                    }\n               \
    \ }\n                return r;\n            }\n            template <typename\
    \ Predicate>\n            static std::pair<node_pointer, uint32_t> max_right(node_pointer\
    \ t, uint32_t l, const Predicate& f) {\n                auto [tl, tr] = base::split(t,\
    \ l);\n                size_t w = max_right(tr, f);\n                t = base::merge(tl,\
    \ tr);\n                return { t, l + w };\n            }\n            template\
    \ <typename Predicate>\n            static uint32_t min_left(node_pointer t, const\
    \ Predicate& f) {\n                value_type sum = e();\n                assert(f(sum));\n\
    \n                uint32_t l = base::safe_size(t);\n                while (t !=\
    \ base::null) {\n                    push(t);\n\n                    node_pointer\
    \ rch = base::child1(t);\n\n                    value_type nxt_sum = op(safe_prod(rch),\
    \ sum);\n                    if (f(nxt_sum)) {\n                        l -= base::safe_size(rch);\n\
    \                        sum = op(base::value(t), nxt_sum);\n                \
    \        if (f(sum)) {\n                            --l;\n                   \
    \         t = base::child0(t);\n                        } else {\n           \
    \                 break;\n                        }\n                    } else\
    \ {\n                        t = rch;\n                    }\n               \
    \ }\n                return l;\n            }\n            template <typename\
    \ Predicate>\n            static std::pair<node_pointer, uint32_t> min_left(node_pointer\
    \ t, uint32_t r, const Predicate& f) {\n                auto [tl, tr] = base::split(t,\
    \ r);\n                size_t l = min_left(tl, f);\n                t = base::merge(tl,\
    \ tr);\n                return { t, l };\n            }\n        };\n    }\n\n\
    \    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F,\
    \ T, int), F(*composition)(F, F), F(*id)()>\n    class DynamicLazySegmentTree\
    \ {\n        using node_type = internal::implicit_treap::RangeOperateRangeProductNode<T,\
    \ op, e, toggle, F, mapping, composition, id>;\n        using node_pointer = typename\
    \ node_type::node_pointer;\n\n        node_pointer _root;\n\n        struct node_pointer_construct\
    \ {};\n        DynamicLazySegmentTree(node_pointer root, node_pointer_construct):\
    \ _root(root) {}\n\n    public:\n        using value_type = typename node_type::value_type;\n\
    \        using operator_type = typename node_type::operator_type;\n\n        DynamicLazySegmentTree():\
    \ _root(node_type::empty_node()) {}\n        explicit DynamicLazySegmentTree(size_t\
    \ n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value))\
    \ {}\n        template <typename U>\n        DynamicLazySegmentTree(const std::vector<U>&\
    \ dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n        void free()\
    \ {\n            node_type::delete_tree(_root);\n            _root = node_type::empty_node();\n\
    \        }\n        void clear() { free(); }\n\n        static void reserve(size_t\
    \ capacity) { node_type::reserve(capacity); }\n\n        bool empty() const {\
    \ return node_type::empty(_root); }\n        int size() const { return node_type::safe_size(_root);\
    \ }\n\n        const value_type& operator[](size_t k) const { return get(k); }\n\
    \        const value_type& get(size_t k) const {\n            assert(k < size_t(size()));\n\
    \            return node_type::get(_root, k);\n        }\n        const value_type&\
    \ front() const { return get(0); }\n        const value_type& back() const { return\
    \ get(size() - 1); }\n        void set(size_t k, const value_type& val) {\n  \
    \          assert(k < size_t(size()));\n            _root = node_type::set(_root,\
    \ k, [&](const value_type&) { return val; });\n        }\n        template <typename\
    \ Func>\n        void apply(size_t k, const Func& f) {\n            assert(k <\
    \ size_t(size()));\n            _root = node_type::set(_root, k, [&](const value_type&\
    \ val) { return f(val); });\n        }\n\n        value_type prod_all() const\
    \ { return node_type::safe_prod(_root); }\n        value_type prod(size_t l, size_t\
    \ r) {\n            value_type res;\n            std::tie(_root, res) = node_type::prod(_root,\
    \ l, r);\n            return res;\n        }\n\n        void apply_all(const operator_type&\
    \ f) { _root = node_type::apply_all(_root, f); }\n        void apply(size_t l,\
    \ size_t r, const operator_type& f) { _root = node_type::apply(_root, l, r, f);\
    \ }\n\n        void insert(size_t k, const value_type& val) {\n            assert(k\
    \ <= size_t(size()));\n            _root = node_type::insert(_root, k, val);\n\
    \        }\n        void push_front(const value_type& val) { _root = node_type::push_front(_root,\
    \ val); }\n        void push_back(const value_type& val) { _root = node_type::push_back(_root,\
    \ val); }\n\n        // Insert a new value immediately before the first element\
    \ that satisfies the condition f.\n        // Returns: the inserted position\n\
    \        // Requirements: f(A[i]) must be monotonic\n        template <typename\
    \ Predicate>\n        int insert_binary_search(const value_type& val, const Predicate\
    \ &f) {\n            int pos;\n            std::tie(_root, pos) = node_type::insert_binary_search(_root,\
    \ f, val);\n            return pos;\n        }\n        // Insert a new value\
    \ immediately before the first element that is greater than or equal to the new\
    \ value.\n        // Returns: the inserted position\n        // Requirements:\
    \ sequence is sorted\n        template <typename Compare = std::less<>>\n    \
    \    int insert_lower_bound(const value_type& val, const Compare &comp = {}) {\n\
    \            int pos;\n            std::tie(_root, pos) = node_type::insert_lower_bound(_root,\
    \ val, comp);\n            return pos;\n        }\n        // Insert a new value\
    \ immediately before the first element that is greater than the new value.\n \
    \       // Returns: the inserted position\n        // Requirements: sequence is\
    \ sorted\n        template <typename Compare = std::less<>>\n        int insert_upper_bound(const\
    \ value_type& val, const Compare &comp = {}) {\n            int pos;\n       \
    \     std::tie(_root, pos) = node_type::insert_upper_bound(_root, val, comp);\n\
    \            return pos;\n        }\n\n        value_type erase(size_t k) {\n\
    \            assert(k <= size_t(size()));\n            value_type v;\n       \
    \     std::tie(_root, v) = node_type::erase(_root, k);\n            return v;\n\
    \        }\n        value_type pop_front() { return erase(0); }\n        value_type\
    \ pop_back() { return erase(size() - 1); }\n\n        // Erase the first element\
    \ that satisfies the condition f if it also satisfies the condition g.\n     \
    \   // returns optional(position, value)\n        // Requirements: sequence is\
    \ sorted\n        template <typename Predicate, typename RemovePredicate>\n  \
    \      std::optional<std::pair<int, value_type>> erase_binary_search(const Predicate\
    \ &f, const RemovePredicate& g) {\n            auto [root, erased] = node_type::erase_binary_search(_root,\
    \ f, g);\n            _root = root;\n            if (erased) {\n             \
    \   return std::pair<int, value_type>{ erased->first, erased->second };\n    \
    \        } else {\n                return std::nullopt;\n            }\n     \
    \   }\n        // Erase the first element that is greater than or equal to val.\n\
    \        // returns optional(position, value)\n        // Requirements: sequence\
    \ is sorted\n        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_lower_bound(const value_type &val, const Compare &comp =\
    \ {}) {\n            auto [root, erased] = node_type::erase_lower_bound(_root,\
    \ val, comp);\n            _root = root;\n            if (erased) {\n        \
    \        return std::pair<int, value_type>{ erased->first, erased->second };\n\
    \            } else {\n                return std::nullopt;\n            }\n \
    \       }\n        // Erase the first element that is greater than val.\n    \
    \    // returns optional(position, value)\n        // Requirements: sequence is\
    \ sorted\n        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_upper_bound(const value_type &val, const Compare &comp =\
    \ {}) {\n            auto [root, erased] = node_type::erase_upper_bound(_root,\
    \ val, comp);\n            _root = root;\n            if (erased) {\n        \
    \        return std::pair<int, value_type>{ erased->first, erased->second };\n\
    \            } else {\n                return std::nullopt;\n            }\n \
    \       }\n        // Erase the first element that is equal to val.\n        //\
    \ returns optional(position, value)\n        // Requirements: sequence is sorted\n\
    \        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_if_exists(const value_type &val, const Compare &comp = {})\
    \ {\n            auto [root, erased] = node_type::erase_if_exists(_root, val,\
    \ comp);\n            _root = root;\n            if (erased) {\n             \
    \   return std::pair<int, value_type>{ erased->first, erased->second };\n    \
    \        } else {\n                return std::nullopt;\n            }\n     \
    \   }\n\n        // Split immediately before the k-th element.\n        DynamicLazySegmentTree\
    \ split(size_t k) {\n            assert(k <= size_t(size()));\n            node_pointer\
    \ root_r;\n            std::tie(_root, root_r) = node_type::split(_root, k);\n\
    \            return DynamicLazySegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        // Split immediately before the first element that satisfies\
    \ the condition.\n        // Requirements: f(A[i]) must be monotonic\n       \
    \ template <typename Predicate>\n        DynamicLazySegmentTree split_binary_search(const\
    \ Predicate &f) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_binary_search(_root, f);\n            return DynamicLazySegmentTree(root_r,\
    \ node_pointer_construct{});\n        }\n        // Split immediately before the\
    \ first element that is greater than or equal to val.\n        // Requirements:\
    \ sequence is sorted\n        template <typename Compare = std::less<>>\n    \
    \    DynamicLazySegmentTree split_lower_bound(const value_type &val, const Compare\
    \ &comp = {}) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_lower_bound(_root, val, comp);\n            return\
    \ DynamicLazySegmentTree(root_r, node_pointer_construct{});\n        }\n     \
    \   // Split immediately before the first element that is greater than val.\n\
    \        // Requirements: sequence is sorted\n        template <typename Compare\
    \ = std::less<>>\n        DynamicLazySegmentTree split_upper_bound(const value_type\
    \ &val, const Compare &comp = {}) {\n            node_pointer root_r;\n      \
    \      std::tie(_root, root_r) = node_type::split_upper_bound(_root, val, comp);\n\
    \            return DynamicLazySegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        void merge(DynamicLazySegmentTree r) { _root = node_type::merge(_root,\
    \ r._root); }\n\n        void rotate(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, k);\n        }\n        void rotate(size_t\
    \ l, size_t m, size_t r) {\n            assert(l <= m and m <= r and r <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, l, m, r);\n        }\n\n       \
    \ void reverse(size_t l, size_t r) {\n            assert(l <= r and r <= size_t(size()));\n\
    \            if (r - l >= 2) _root = node_type::reverse(_root, l, r);\n      \
    \  }\n        void reverse_all() { _root = node_type::reverse_all(_root); }\n\n\
    \        std::vector<value_type> dump() const { return node_type::dump(_root);\
    \ }\n\n        // Find the first element that satisfies the condition f.\n   \
    \     // Returns { position, optional(value) }\n        // Requirements: f(A[i])\
    \ must be monotonic\n        template <typename Predicate>\n        std::pair<int,\
    \ std::optional<value_type>> binary_search(const Predicate& f) const {\n     \
    \       auto [pos, val] = node_type::binary_search(_root, f);\n            return\
    \ { pos, std::move(val) };\n        }\n        // comp(T t, U u) = (t < u)\n \
    \       // Requirements: sequence is sorted\n        template <typename U, typename\
    \ Compare = std::less<>>\n        std::pair<int, std::optional<value_type>> lower_bound(const\
    \ U& target, Compare comp = {}) const {\n            auto [pos, val] = node_type::lower_bound(_root,\
    \ target, comp);\n            return { pos, std::move(val) };\n        }\n   \
    \     // comp(T u, U t) = (u < t)\n        // Requirements: sequence is sorted\n\
    \        template <typename U, typename Compare = std::less<>>\n        std::pair<int,\
    \ std::optional<value_type>> upper_bound(const U& target, Compare comp = {}) const\
    \ {\n            auto [pos, val] = node_type::upper_bound(_root, target, comp);\n\
    \            return { pos, std::move(val) };\n        }\n\n        // Returns\
    \ max{ r | f(op(A[l], ..., A[r-1])) = true }\n        template <typename Predicate>\n\
    \        int max_right(size_t l, const Predicate& f) {\n            size_t res;\n\
    \            std::tie(_root, res) = node_type::max_right(_root, l, f);\n     \
    \       return res;\n        }\n        // Returns min{ l | f(op(A[l], ..., A[r-1]))\
    \ = true }\n        template <typename Predicate>\n        int min_left(size_t\
    \ r, const Predicate& f) {\n            size_t res;\n            std::tie(_root,\
    \ res) = node_type::min_left(_root, r, f);\n            return res;\n        }\n\
    \n        using iterator = typename node_type::const_iterator;\n        using\
    \ reverse_iterator = typename node_type::const_reverse_iterator;\n        using\
    \ const_iterator = typename node_type::const_iterator;\n        using const_reverse_iterator\
    \ = typename node_type::const_reverse_iterator;\n\n        iterator begin() const\
    \ { return cbegin(); }\n        iterator end() const { return cend(); }\n    \
    \    iterator kth_iterator(size_t k) const { return kth_const_iterator(k); }\n\
    \        reverse_iterator rbegin() const { return crbegin(); }\n        reverse_iterator\
    \ rend() const { return crend(); }\n        reverse_iterator kth_reverse_iterator(size_t\
    \ k) const { return kth_const_reverse_iterator(k); }\n        const_iterator cbegin()\
    \ const { return node_type::cbegin(_root); }\n        const_iterator cend() const\
    \ { return node_type::cend(_root); }\n        const_iterator kth_const_iterator(size_t\
    \ k) const { return node_type::kth_const_iterator(_root, k); }\n        const_reverse_iterator\
    \ crbegin() const { return node_type::crbegin(_root); }\n        const_reverse_iterator\
    \ crend() const { return node_type::crend(_root); }\n        const_reverse_iterator\
    \ kth_const_reverse_iterator(size_t k) const { return node_type::kth_const_reverse_iterator(_root,\
    \ k); }\n    };\n} // namespace suisen\n\n\n\n#line 16 \"test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T,\
    \ int)>\nstruct NaiveSolutionForLazySegmentTree {\n    NaiveSolutionForLazySegmentTree()\
    \ = default;\n    NaiveSolutionForLazySegmentTree(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const {\n        assert(0 <=\
    \ i and i < _n);\n        return _dat[i];\n    }\n    void set(int i, const T&\
    \ val) {\n        assert(0 <= i and i < _n);\n        _dat[i] = val;\n    }\n\n\
    \    void insert(int i, const T& val) {\n        assert(0 <= i and i <= _n);\n\
    \        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n    }\n    void erase(int\
    \ i) {\n        assert(0 <= i and i < _n);\n        --_n;\n        _dat.erase(_dat.begin()\
    \ + i);\n    }\n\n    T prod_all() const {\n        return prod(0, _n);\n    }\n\
    \    T prod(int l, int r) const {\n        assert(0 <= l and l <= r and r <= _n);\n\
    \        T res = e();\n        for (int i = l; i < r; ++i) res = op(res, _dat[i]);\n\
    \        return res;\n    }\n\n    void apply_all(const F &f) {\n        apply(0,\
    \ _n, f);\n    }\n    void apply(int l, int r, const F &f) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (int i = l; i < r; ++i) _dat[i] =\
    \ mapping(f, _dat[i], 1);\n    }\n\n    void reverse_all() {\n        reverse(0,\
    \ _n);\n    }\n    void reverse(int l, int r) {\n        assert(0 <= l and l <=\
    \ r and r <= _n);\n        for (--r; l < r; ++l, --r) {\n            std::swap(_dat[l],\
    \ _dat[r]);\n        }\n    }\n\n    void rotate(int i) {\n        assert(0 <=\
    \ i and i <= _n);\n        std::rotate(_dat.begin(), _dat.begin() + i, _dat.end());\n\
    \    }\n\n    template <typename Pred>\n    int max_right(int l, Pred &&pred)\
    \ const {\n        assert(0 <= l and l <= _n);\n        T sum = e();\n       \
    \ for (int r = l; r < _n; ++r) {\n            T next_sum = op(sum, _dat[r]);\n\
    \            if (not pred(next_sum)) return r;\n            sum = std::move(next_sum);\n\
    \        }\n        return _n;\n    }\n\n    template <typename Pred>\n    int\
    \ min_left(int r, Pred &&pred) const {\n        assert(0 <= r and r <= _n);\n\
    \        T sum = e();\n        for (int l = r; l > 0; --l) {\n            T next_sum\
    \ = op(_dat[l - 1], sum);\n            if (not pred(next_sum)) return l;\n   \
    \         sum = std::move(next_sum);\n        }\n        return 0;\n    }\n\n\
    \    std::vector<T> dump() { return _dat; }\nprivate:\n    int _n;\n    std::vector<T>\
    \ _dat;\n};\n\n/**\n * Range Update Range Sum\n */\n\nusing S = long long;\n\n\
    struct F {\n    static constexpr int identity = std::numeric_limits<int>::max();\n\
    \n    int val;\n    F() : val(identity) {}\n    F(int val) : val(val) {}\n};\n\
    \nS op(S x, S y) {\n    return x + y;\n}\nS e() {\n    return 0;\n}\nS toggle(S\
    \ x) {\n    return x;\n}\nS mapping(F f, S x, int len) {\n    return f.val ==\
    \ F::identity ? x : (long long) f.val * len;\n}\nF composition(F f, F g) {\n \
    \   return f.val == F::identity ? g : f;\n}\nF id() {\n    return F{};\n}\n\n\
    using Tree = suisen::DynamicLazySegmentTree<S, op, e, toggle, F, mapping, composition,\
    \ id>;\nusing Naive = NaiveSolutionForLazySegmentTree<S, op, e, F, mapping>;\n\
    \n#line 143 \"test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp\"\
    \n\nconstexpr int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_insert\
    \ = 10;\nconstexpr int Q_erase = 11;\nconstexpr int Q_rotate = 12;\nconstexpr\
    \ int Q_prod = 2;\nconstexpr int Q_prod_all = 3;\nconstexpr int Q_apply = 4;\n\
    constexpr int Q_apply_all = 5;\nconstexpr int Q_reverse = 6;\nconstexpr int Q_reverse_all\
    \ = 7;\nconstexpr int Q_max_right = 8;\nconstexpr int Q_min_left = 9;\nconstexpr\
    \ int QueryTypeNum = 13;\n\nvoid test() {\n    int N = 3000, Q = 3000, MAX_VAL\
    \ = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\n    std::vector<S>\
    \ init(N);\n    for (int i = 0; i < N; ++i) init[i] = rng() % MAX_VAL;\n    \n\
    \    Tree t1(init);\n    Naive t2(init);\n\n    for (int i = 0; i < Q; ++i) {\n\
    \        const int query_type = rng() % QueryTypeNum;\n        if (query_type\
    \ == Q_get) {\n            const int i = rng() % N;\n            assert(t1.get(i)\
    \ == t2.get(i));\n        } else if (query_type == Q_set) {\n            const\
    \ int i = rng() % N;\n            const S v = rng() % MAX_VAL;\n            t1.set(i,\
    \ v);\n            t2.set(i, v);\n        } else if (query_type == Q_insert) {\n\
    \            const int i = rng() % (N + 1);\n            const S v = rng() % MAX_VAL;\n\
    \            t1.insert(i, v);\n            t2.insert(i, v);\n            ++N;\n\
    \        } else if (query_type == Q_erase) {\n            const int i = rng()\
    \ % N;\n            t1.erase(i);\n            t2.erase(i);\n            --N;\n\
    \        } else if (query_type == Q_rotate) {\n            const int i = rng()\
    \ % (N + 1);\n            t1.rotate(i);\n            t2.rotate(i);\n        }\
    \ else if (query_type == Q_prod) {\n            const int l = rng() % (N + 1);\n\
    \            const int r = l + rng() % (N - l + 1);\n            assert(t1.prod(l,\
    \ r) == t2.prod(l, r));\n        } else if (query_type == Q_prod_all) {\n    \
    \        assert(t1.prod_all() == t2.prod_all());\n        } else if (query_type\
    \ == Q_apply) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            const int f = rng() % MAX_VAL;\n\
    \            t1.apply(l, r, f);\n            t2.apply(l, r, f);\n        } else\
    \ if (query_type == Q_apply_all) {\n            const int f = rng() % MAX_VAL;\n\
    \            t1.apply_all(f);\n            t2.apply_all(f);\n        } else if\
    \ (query_type == Q_reverse) {\n            const int l = rng() % (N + 1);\n  \
    \          const int r = l + rng() % (N - l + 1);\n            t1.reverse(l, r);\n\
    \            t2.reverse(l, r);\n        } else if (query_type == Q_reverse_all)\
    \ {\n            t1.reverse_all();\n            t2.reverse_all();\n        } else\
    \ if (query_type == Q_max_right) {\n            const int l = rng() % (N + 1);\n\
    \            const int r = l + rng() % (N - l + 1);\n            long long sum\
    \ = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);\n     \
    \       auto pred = [&](const S &x) { return x <= sum; };\n            assert(t1.max_right(l,\
    \ pred) == t2.max_right(l, pred));\n        } else if (query_type == Q_min_left)\
    \ {\n            const int l = rng() % (N + 1);\n            const int r = l +\
    \ rng() % (N - l + 1);\n            long long sum = std::max(0LL, t2.prod(l, r)\
    \ + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred = [&](const S\
    \ &x) { return x <= sum; };\n            assert(t1.min_left(r, pred) == t2.min_left(r,\
    \ pred));\n        } else {\n            assert(false);\n        }\n    }\n}\n\
    \nvoid test2() {\n    std::mt19937 rng{ std::random_device{}() };\n    Tree seq;\n\
    \    const int n = 300, k = 20;\n\n    std::vector<S> q(n * k);\n    for (int\
    \ i = 0; i < n * k; ++i) {\n        q[i] = i % n;\n    }\n    std::shuffle(q.begin(),\
    \ q.end(), rng);\n\n    for (int v : q) {\n        if (rng() % 2) {\n        \
    \    int k = seq.insert_lower_bound(v);\n            assert(k == 0 or seq[k -\
    \ 1] < v);\n            assert(k == seq.size() - 1 or seq[k + 1] >= v);\n    \
    \    } else {\n            int k = seq.insert_upper_bound(v);\n            assert(k\
    \ == 0 or seq[k - 1] <= v);\n            assert(k == seq.size() - 1 or seq[k +\
    \ 1] > v);\n        }\n    }\n\n    for (int v : q) {\n        int k = seq.erase_if_exists(v)->first;\n\
    \        assert(k == 0 or seq[k - 1] < v);\n        assert(k == seq.size() or\
    \ seq[k] >= v);\n    }\n\n    std::vector<S> sorted = q;\n    std::sort(sorted.begin(),\
    \ sorted.end());\n\n    seq = sorted;\n\n    assert(std::equal(sorted.begin(),\
    \ sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(), sorted.rend(),\
    \ seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n        assert(*seq.kth_iterator(i)\
    \ == i / k);\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int a =\
    \ rng() % (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int d =\
    \ b - a;\n        assert(seq.kth_iterator(a) + d == seq.kth_iterator(b));\n  \
    \      assert(seq.kth_iterator(a) == seq.kth_iterator(b) - d);\n    }\n\n    std::vector<S>\
    \ naive = sorted;\n\n    for (int q = 0; q < 500; ++q) {\n        if (rng() %\
    \ 2) {\n            int l = rng() % (n * k + 1);\n            int r = rng() %\
    \ (n * k + 1);\n            if (l > r) std::swap(l, r);\n            seq.reverse(l,\
    \ r);\n            std::reverse(naive.begin() + l, naive.begin() + r);\n     \
    \   } else {\n            assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n\
    \            assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));\n\
    \            std::vector<S> dump = seq.dump();\n            assert(std::equal(naive.begin(),\
    \ naive.end(), dump.begin()));\n        }\n    }\n\n    // for (S& e : seq) --e;\
    \ // Compile Error \n    // for (S& e : naive) --e;\n    // assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n    // assert(std::equal(naive.rbegin(), naive.rend(),\
    \ seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const Tree&>(seq);\n\
    \    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n    assert(std::equal(naive.rbegin(),\
    \ naive.rend(), const_seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n\
    \        assert(const_seq[i] == naive[i]);\n    }\n}\n\nint main() {\n    test();\n\
    \    test2();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#include \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T,\
    \ int)>\nstruct NaiveSolutionForLazySegmentTree {\n    NaiveSolutionForLazySegmentTree()\
    \ = default;\n    NaiveSolutionForLazySegmentTree(const std::vector<T> &dat) :\
    \ _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const {\n        assert(0 <=\
    \ i and i < _n);\n        return _dat[i];\n    }\n    void set(int i, const T&\
    \ val) {\n        assert(0 <= i and i < _n);\n        _dat[i] = val;\n    }\n\n\
    \    void insert(int i, const T& val) {\n        assert(0 <= i and i <= _n);\n\
    \        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n    }\n    void erase(int\
    \ i) {\n        assert(0 <= i and i < _n);\n        --_n;\n        _dat.erase(_dat.begin()\
    \ + i);\n    }\n\n    T prod_all() const {\n        return prod(0, _n);\n    }\n\
    \    T prod(int l, int r) const {\n        assert(0 <= l and l <= r and r <= _n);\n\
    \        T res = e();\n        for (int i = l; i < r; ++i) res = op(res, _dat[i]);\n\
    \        return res;\n    }\n\n    void apply_all(const F &f) {\n        apply(0,\
    \ _n, f);\n    }\n    void apply(int l, int r, const F &f) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (int i = l; i < r; ++i) _dat[i] =\
    \ mapping(f, _dat[i], 1);\n    }\n\n    void reverse_all() {\n        reverse(0,\
    \ _n);\n    }\n    void reverse(int l, int r) {\n        assert(0 <= l and l <=\
    \ r and r <= _n);\n        for (--r; l < r; ++l, --r) {\n            std::swap(_dat[l],\
    \ _dat[r]);\n        }\n    }\n\n    void rotate(int i) {\n        assert(0 <=\
    \ i and i <= _n);\n        std::rotate(_dat.begin(), _dat.begin() + i, _dat.end());\n\
    \    }\n\n    template <typename Pred>\n    int max_right(int l, Pred &&pred)\
    \ const {\n        assert(0 <= l and l <= _n);\n        T sum = e();\n       \
    \ for (int r = l; r < _n; ++r) {\n            T next_sum = op(sum, _dat[r]);\n\
    \            if (not pred(next_sum)) return r;\n            sum = std::move(next_sum);\n\
    \        }\n        return _n;\n    }\n\n    template <typename Pred>\n    int\
    \ min_left(int r, Pred &&pred) const {\n        assert(0 <= r and r <= _n);\n\
    \        T sum = e();\n        for (int l = r; l > 0; --l) {\n            T next_sum\
    \ = op(_dat[l - 1], sum);\n            if (not pred(next_sum)) return l;\n   \
    \         sum = std::move(next_sum);\n        }\n        return 0;\n    }\n\n\
    \    std::vector<T> dump() { return _dat; }\nprivate:\n    int _n;\n    std::vector<T>\
    \ _dat;\n};\n\n/**\n * Range Update Range Sum\n */\n\nusing S = long long;\n\n\
    struct F {\n    static constexpr int identity = std::numeric_limits<int>::max();\n\
    \n    int val;\n    F() : val(identity) {}\n    F(int val) : val(val) {}\n};\n\
    \nS op(S x, S y) {\n    return x + y;\n}\nS e() {\n    return 0;\n}\nS toggle(S\
    \ x) {\n    return x;\n}\nS mapping(F f, S x, int len) {\n    return f.val ==\
    \ F::identity ? x : (long long) f.val * len;\n}\nF composition(F f, F g) {\n \
    \   return f.val == F::identity ? g : f;\n}\nF id() {\n    return F{};\n}\n\n\
    using Tree = suisen::DynamicLazySegmentTree<S, op, e, toggle, F, mapping, composition,\
    \ id>;\nusing Naive = NaiveSolutionForLazySegmentTree<S, op, e, F, mapping>;\n\
    \n#include <random>\n#include <algorithm>\n\nconstexpr int Q_get = 0;\nconstexpr\
    \ int Q_set = 1;\nconstexpr int Q_insert = 10;\nconstexpr int Q_erase = 11;\n\
    constexpr int Q_rotate = 12;\nconstexpr int Q_prod = 2;\nconstexpr int Q_prod_all\
    \ = 3;\nconstexpr int Q_apply = 4;\nconstexpr int Q_apply_all = 5;\nconstexpr\
    \ int Q_reverse = 6;\nconstexpr int Q_reverse_all = 7;\nconstexpr int Q_max_right\
    \ = 8;\nconstexpr int Q_min_left = 9;\nconstexpr int QueryTypeNum = 13;\n\nvoid\
    \ test() {\n    int N = 3000, Q = 3000, MAX_VAL = 1000000000;\n\n    std::mt19937\
    \ rng{std::random_device{}()};\n\n    std::vector<S> init(N);\n    for (int i\
    \ = 0; i < N; ++i) init[i] = rng() % MAX_VAL;\n    \n    Tree t1(init);\n    Naive\
    \ t2(init);\n\n    for (int i = 0; i < Q; ++i) {\n        const int query_type\
    \ = rng() % QueryTypeNum;\n        if (query_type == Q_get) {\n            const\
    \ int i = rng() % N;\n            assert(t1.get(i) == t2.get(i));\n        } else\
    \ if (query_type == Q_set) {\n            const int i = rng() % N;\n         \
    \   const S v = rng() % MAX_VAL;\n            t1.set(i, v);\n            t2.set(i,\
    \ v);\n        } else if (query_type == Q_insert) {\n            const int i =\
    \ rng() % (N + 1);\n            const S v = rng() % MAX_VAL;\n            t1.insert(i,\
    \ v);\n            t2.insert(i, v);\n            ++N;\n        } else if (query_type\
    \ == Q_erase) {\n            const int i = rng() % N;\n            t1.erase(i);\n\
    \            t2.erase(i);\n            --N;\n        } else if (query_type ==\
    \ Q_rotate) {\n            const int i = rng() % (N + 1);\n            t1.rotate(i);\n\
    \            t2.rotate(i);\n        } else if (query_type == Q_prod) {\n     \
    \       const int l = rng() % (N + 1);\n            const int r = l + rng() %\
    \ (N - l + 1);\n            assert(t1.prod(l, r) == t2.prod(l, r));\n        }\
    \ else if (query_type == Q_prod_all) {\n            assert(t1.prod_all() == t2.prod_all());\n\
    \        } else if (query_type == Q_apply) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ const int f = rng() % MAX_VAL;\n            t1.apply(l, r, f);\n           \
    \ t2.apply(l, r, f);\n        } else if (query_type == Q_apply_all) {\n      \
    \      const int f = rng() % MAX_VAL;\n            t1.apply_all(f);\n        \
    \    t2.apply_all(f);\n        } else if (query_type == Q_reverse) {\n       \
    \     const int l = rng() % (N + 1);\n            const int r = l + rng() % (N\
    \ - l + 1);\n            t1.reverse(l, r);\n            t2.reverse(l, r);\n  \
    \      } else if (query_type == Q_reverse_all) {\n            t1.reverse_all();\n\
    \            t2.reverse_all();\n        } else if (query_type == Q_max_right)\
    \ {\n            const int l = rng() % (N + 1);\n            const int r = l +\
    \ rng() % (N - l + 1);\n            long long sum = std::max(0LL, t2.prod(l, r)\
    \ + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred = [&](const S\
    \ &x) { return x <= sum; };\n            assert(t1.max_right(l, pred) == t2.max_right(l,\
    \ pred));\n        } else if (query_type == Q_min_left) {\n            const int\
    \ l = rng() % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n \
    \           long long sum = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL)\
    \ - MAX_VAL / 2);\n            auto pred = [&](const S &x) { return x <= sum;\
    \ };\n            assert(t1.min_left(r, pred) == t2.min_left(r, pred));\n    \
    \    } else {\n            assert(false);\n        }\n    }\n}\n\nvoid test2()\
    \ {\n    std::mt19937 rng{ std::random_device{}() };\n    Tree seq;\n    const\
    \ int n = 300, k = 20;\n\n    std::vector<S> q(n * k);\n    for (int i = 0; i\
    \ < n * k; ++i) {\n        q[i] = i % n;\n    }\n    std::shuffle(q.begin(), q.end(),\
    \ rng);\n\n    for (int v : q) {\n        if (rng() % 2) {\n            int k\
    \ = seq.insert_lower_bound(v);\n            assert(k == 0 or seq[k - 1] < v);\n\
    \            assert(k == seq.size() - 1 or seq[k + 1] >= v);\n        } else {\n\
    \            int k = seq.insert_upper_bound(v);\n            assert(k == 0 or\
    \ seq[k - 1] <= v);\n            assert(k == seq.size() - 1 or seq[k + 1] > v);\n\
    \        }\n    }\n\n    for (int v : q) {\n        int k = seq.erase_if_exists(v)->first;\n\
    \        assert(k == 0 or seq[k - 1] < v);\n        assert(k == seq.size() or\
    \ seq[k] >= v);\n    }\n\n    std::vector<S> sorted = q;\n    std::sort(sorted.begin(),\
    \ sorted.end());\n\n    seq = sorted;\n\n    assert(std::equal(sorted.begin(),\
    \ sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(), sorted.rend(),\
    \ seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n        assert(*seq.kth_iterator(i)\
    \ == i / k);\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int a =\
    \ rng() % (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int d =\
    \ b - a;\n        assert(seq.kth_iterator(a) + d == seq.kth_iterator(b));\n  \
    \      assert(seq.kth_iterator(a) == seq.kth_iterator(b) - d);\n    }\n\n    std::vector<S>\
    \ naive = sorted;\n\n    for (int q = 0; q < 500; ++q) {\n        if (rng() %\
    \ 2) {\n            int l = rng() % (n * k + 1);\n            int r = rng() %\
    \ (n * k + 1);\n            if (l > r) std::swap(l, r);\n            seq.reverse(l,\
    \ r);\n            std::reverse(naive.begin() + l, naive.begin() + r);\n     \
    \   } else {\n            assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n\
    \            assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));\n\
    \            std::vector<S> dump = seq.dump();\n            assert(std::equal(naive.begin(),\
    \ naive.end(), dump.begin()));\n        }\n    }\n\n    // for (S& e : seq) --e;\
    \ // Compile Error \n    // for (S& e : naive) --e;\n    // assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n    // assert(std::equal(naive.rbegin(), naive.rend(),\
    \ seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const Tree&>(seq);\n\
    \    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n    assert(std::equal(naive.rbegin(),\
    \ naive.rend(), const_seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n\
    \        assert(const_seq[i] == naive[i]);\n    }\n}\n\nint main() {\n    test();\n\
    \    test2();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }"
  dependsOn:
  - library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/implicit_treap_base.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 10:47:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
- /verify/test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp.html
title: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dummy.test.cpp
---
