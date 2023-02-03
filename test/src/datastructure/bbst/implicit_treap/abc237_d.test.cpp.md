---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap.hpp
    title: Implicit Treap
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_base.hpp
    title: Implicit Treap Base
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc237/tasks/abc237_d
    links:
    - https://atcoder.jp/contests/abc237/tasks/abc237_d
  bundledCode: "#line 1 \"test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc237/tasks/abc237_d\"\n\n#include\
    \ <iostream>\n#line 1 \"library/datastructure/bbst/implicit_treap.hpp\"\n\n\n\n\
    #line 1 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <optional>\n#include <string>\n#include\
    \ <random>\n#include <tuple>\n#include <vector>\n#include <utility>\n\nnamespace\
    \ suisen::internal::implicit_treap {\n    template <typename T, typename Derived>\n\
    \    struct Node {\n        using random_engine = std::mt19937;\n        static\
    \ inline random_engine rng{ std::random_device{}() };\n\n        using node_type\
    \ = Derived;\n        using node_pointer = uint32_t;\n        using priority_type\
    \ = std::invoke_result_t<random_engine>;\n\n        using size_type = uint32_t;\n\
    \n        using difference_type = int32_t;\n        using value_type = T;\n  \
    \      using pointer = value_type*;\n        using const_pointer = const value_type*;\n\
    \        using reference = value_type&;\n        using const_reference = const\
    \ value_type&;\n\n        static inline std::vector<node_type> _nodes{};\n   \
    \     static inline std::vector<node_pointer> _erased{};\n\n        static constexpr\
    \ node_pointer null = ~node_pointer(0);\n\n        node_pointer _ch[2]{ null,\
    \ null };\n        value_type _val;\n        size_type _size;\n        priority_type\
    \ _priority;\n\n        node_pointer _prev = null, _next = null;\n\n        Node(const\
    \ value_type val = {}): _val(val), _size(1), _priority(rng()) {}\n\n        static\
    \ void reserve(size_type capacity) { _nodes.reserve(capacity); }\n\n        static\
    \ bool is_null(node_pointer t) { return t == null; }\n        static bool is_not_null(node_pointer\
    \ t) { return not is_null(t); }\n\n        static node_type& node(node_pointer\
    \ t) { return _nodes[t]; }\n        static const node_type& const_node(node_pointer\
    \ t) { return _nodes[t]; }\n\n        static value_type& value(node_pointer t)\
    \ { return node(t)._val; }\n        static value_type set_value(node_pointer t,\
    \ const value_type& new_val) { return std::exchange(value(t), new_val); }\n\n\
    \        static bool empty(node_pointer t) { return is_null(t); }\n        static\
    \ size_type& size(node_pointer t) { return node(t)._size; }\n        static size_type\
    \ safe_size(node_pointer t) { return empty(t) ? 0 : size(t); }\n\n        static\
    \ priority_type priority(node_pointer t) { return const_node(t)._priority; }\n\
    \n        static node_pointer& prev(node_pointer t) { return node(t)._prev; }\n\
    \        static node_pointer& next(node_pointer t) { return node(t)._next; }\n\
    \        static void link(node_pointer l, node_pointer r) { next(l) = r, prev(r)\
    \ = l; }\n\n        static node_pointer min(node_pointer t) {\n            while\
    \ (true) {\n                node_type::push(t);\n                node_pointer\
    \ nt = child0(t);\n                if (is_null(nt)) return t;\n              \
    \  t = nt;\n            }\n        }\n        static node_pointer max(node_pointer\
    \ t) {\n            while (true) {\n                node_type::push(t);\n    \
    \            node_pointer nt = child1(t);\n                if (is_null(nt)) return\
    \ t;\n                t = nt;\n            }\n        }\n\n        static node_pointer&\
    \ child0(node_pointer t) { return node(t)._ch[0]; }\n        static node_pointer&\
    \ child1(node_pointer t) { return node(t)._ch[1]; }\n        static node_pointer&\
    \ child(node_pointer t, bool b) { return node(t)._ch[b]; }\n        static node_pointer\
    \ set_child0(node_pointer t, node_pointer cid) { return std::exchange(child0(t),\
    \ cid); }\n        static node_pointer set_child1(node_pointer t, node_pointer\
    \ cid) { return std::exchange(child1(t), cid); }\n        static node_pointer\
    \ set_child(node_pointer t, bool b, node_pointer cid) { return std::exchange(child(t,\
    \ b), cid); }\n\n        static node_pointer update(node_pointer t) { // t : not\
    \ null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;\n\
    \            return t;\n        }\n        static void push(node_pointer) {}\n\
    \n        static node_pointer empty_node() { return null; }\n        template\
    \ <typename ...Args>\n        static node_pointer create_node(Args &&...args)\
    \ {\n            if (_erased.size()) {\n                node_pointer res = _erased.back();\n\
    \                _erased.pop_back();\n                node(res) = node_type(std::forward<Args>(args)...);\n\
    \                return res;\n            } else {\n                node_pointer\
    \ res = _nodes.size();\n                _nodes.emplace_back(std::forward<Args>(args)...);\n\
    \                return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) { _erased.push_back(t); }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (is_null(t)) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            node_pointer res = empty_node();\n            for\
    \ (auto&& e : std::vector<value_type>(std::forward<Args>(args)...)) {\n      \
    \          res = push_back(res, std::move(e));\n            }\n            return\
    \ res;\n        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, size_type k) {\n            if (k == 0) return { null, t };\n           \
    \ if (k == size(t)) return { t, null };\n\n            static std::vector<node_pointer>\
    \ lp{}, rp{};\n\n            while (true) {\n                node_type::push(t);\n\
    \                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n\
    \                    if (rp.size()) set_child0(rp.back(), t);\n              \
    \      rp.push_back(t);\n                    if (k == lsiz) {\n              \
    \          if (lp.size()) set_child1(lp.back(), child0(t));\n\n              \
    \          node_pointer lt = set_child0(t, null), rt = null;\n\n             \
    \           while (lp.size()) node_type::update(lt = lp.back()), lp.pop_back();\n\
    \                        while (rp.size()) node_type::update(rt = rp.back()),\
    \ rp.pop_back();\n\n                        return { lt, rt };\n             \
    \       }\n                    t = child0(t);\n                } else {\n    \
    \                if (lp.size()) set_child1(lp.back(), t);\n                  \
    \  lp.push_back(t);\n                    t = child1(t);\n                    k\
    \ -= lsiz + 1;\n                }\n            }\n        }\n        static std::tuple<node_pointer,\
    \ node_pointer, node_pointer> split(node_pointer t, size_type l, size_type r)\
    \ {\n            auto [tlm, tr] = split(t, r);\n            auto [tl, tm] = split(tlm,\
    \ l);\n            return { tl, tm, tr };\n        }\n        // Split immediately\
    \ before the first element that satisfies the condition.\n        template <typename\
    \ Predicate>\n        static std::pair<node_pointer, node_pointer> split_binary_search(node_pointer\
    \ t, const Predicate& f) {\n            if (is_null(t)) {\n                return\
    \ { null, null };\n            }\n            node_type::push(t);\n          \
    \  if (f(value(t))) {\n                auto [l, tl] = split_binary_search(child0(t),\
    \ f);\n                set_child0(t, tl);\n                return { l, node_type::update(t)\
    \ };\n            } else {\n                auto [tr, r] = split_binary_search(child1(t),\
    \ f);\n                set_child1(t, tr);\n                return { node_type::update(t),\
    \ r };\n            }\n        }\n        template <typename Compare = std::less<>>\n\
    \        static std::pair<node_pointer, node_pointer> split_lower_bound(node_pointer\
    \ t, const value_type& target, const Compare& comp) {\n            return split_binary_search(t,\
    \ [&](const value_type& v) { return not comp(v, target); });\n        }\n    \
    \    template <typename Compare = std::less<>>\n        static std::pair<node_pointer,\
    \ node_pointer> split_upper_bound(node_pointer t, const value_type& target, const\
    \ Compare& comp) {\n            return split_binary_search(t, [&](const value_type&\
    \ v) { return comp(target, v); });\n        }\n\n        static node_pointer merge_impl(node_pointer\
    \ tl, node_pointer tr) {\n            if (priority(tl) < priority(tr)) {\n   \
    \             node_type::push(tr);\n                if (node_pointer tm = child0(tr);\
    \ is_null(tm)) {\n                    link(max(tl), tr);\n                   \
    \ set_child0(tr, tl);\n                } else {\n                    set_child0(tr,\
    \ merge(tl, tm));\n                }\n                return node_type::update(tr);\n\
    \            } else {\n                node_type::push(tl);\n                if\
    \ (node_pointer tm = child1(tl); is_null(tm)) {\n                    link(tl,\
    \ min(tr));\n                    set_child1(tl, tr);\n                } else {\n\
    \                    set_child1(tl, merge(tm, tr));\n                }\n     \
    \           return node_type::update(tl);\n            }\n        }\n        static\
    \ node_pointer merge(node_pointer tl, node_pointer tr) {\n            if (is_null(tl))\
    \ return tr;\n            if (is_null(tr)) return tl;\n            return merge_impl(tl,\
    \ tr);\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer\
    \ new_node) {\n            if (is_null(t)) return new_node;\n            static\
    \ std::vector<node_pointer> st;\n            bool b = false;\n\n            while\
    \ (true) {\n                if (is_null(t) or priority(new_node) > priority(t))\
    \ {\n                    if (is_null(t)) {\n                        t = new_node;\n\
    \                    } else {\n                        auto [tl, tr] = split(t,\
    \ k);\n                        if (is_not_null(tl)) link(max(tl), new_node);\n\
    \                        if (is_not_null(tr)) link(new_node, min(tr));\n     \
    \                   set_child0(new_node, tl);\n                        set_child1(new_node,\
    \ tr);\n                        t = node_type::update(new_node);\n           \
    \         }\n                    if (st.size()) {\n                        set_child(st.back(),\
    \ b, t);\n                        do t = node_type::update(st.back()), st.pop_back();\
    \ while (st.size());\n                    }\n                    return t;\n \
    \               } else {\n                    node_type::push(t);\n          \
    \          if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n   \
    \                     if (k == lsiz) link(new_node, t);\n                    \
    \    st.push_back(t), b = false;\n                        t = child0(t);\n   \
    \                 } else {\n                        if (k == lsiz + 1) link(t,\
    \ new_node);\n                        st.push_back(t), b = true;\n           \
    \             t = child1(t);\n                        k -= lsiz + 1;\n       \
    \             }\n                }\n            }\n        }\n        template\
    \ <typename ...Args>\n        static node_pointer insert(node_pointer t, size_type\
    \ k, Args &&...args) {\n            return insert_impl(t, k, create_node(std::forward<Args>(args)...));\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        // Insert a new node immediately before the first element\
    \ that satisfies the condition.\n        // Returns { node, position to insert\
    \ }\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer\
    \ new_node) {\n            if (is_null(t)) {\n                return { new_node,\
    \ 0 };\n            }\n            if (priority(new_node) > priority(t)) {\n \
    \               auto [tl, tr] = split_binary_search(t, f);\n                if\
    \ (is_not_null(tl)) link(max(tl), t);\n                if (is_not_null(tr)) link(min(tr),\
    \ t);\n                set_child0(new_node, tl);\n                set_child1(new_node,\
    \ tr);\n                return { node_type::update(new_node), safe_size(tl) };\n\
    \            } else {\n                node_type::push(t);\n                if\
    \ (f(value(t))) {\n                    auto [c0, pos] = insert_binary_search_impl(child0(t),\
    \ f, new_node);\n                    set_child0(t, c0);\n                    if\
    \ (is_null(next(new_node))) link(new_node, t);\n                    return { node_type::update(t),\
    \ pos };\n                } else {\n                    auto [c1, pos] = insert_binary_search_impl(child1(t),\
    \ f, new_node);\n                    set_child1(t, c1);\n                    if\
    \ (is_null(prev(new_node))) link(t, new_node);\n                    return { node_type::update(t),\
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
    \              if (is_not_null(c0) and k == lsiz - 1) link(max(c0), t);\n    \
    \            return { node_type::update(t), std::move(v) };\n            } else\
    \ {\n                auto [c1, v] = erase(child1(t), k - (lsiz + 1));\n      \
    \          set_child1(t, c1);\n                if (is_not_null(c1) and k == lsiz\
    \ + 1) link(t, min(c1));\n                return { node_type::update(t), std::move(v)\
    \ };\n            }\n        }\n        static std::pair<node_pointer, value_type>\
    \ pop_front(node_pointer t) { return erase(t, 0); }\n        static std::pair<node_pointer,\
    \ value_type> pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }\n\
    \n        // Erase the first element that satisfies the condition f if it also\
    \ satisfies the condition g.\n        // returns { node, optional(position, value)\
    \ }\n        template <typename Predicate, typename RemovePredicate>\n       \
    \ static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>>\
    \ erase_binary_search(node_pointer t, const Predicate& f, const RemovePredicate&\
    \ g) {\n            if (is_null(t)) return { null, std::nullopt };\n         \
    \   node_type::push(t);\n            if (f(value(t))) {\n                auto\
    \ [c0, erased] = erase_binary_search(child0(t), f, g);\n                if (erased)\
    \ {\n                    set_child0(t, c0);\n                    size_type& pos\
    \ = erased->first;\n                    if (is_not_null(c0) and pos == safe_size(c0))\
    \ link(max(c0), t);\n                    return { node_type::update(t), std::move(erased)\
    \ };\n                } else if (g(value(t))) {\n                    delete_node(t);\n\
    \                    std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)),\
    \ std::move(value(t)) };\n                    return { merge(child0(t), child1(t)),\
    \ std::move(erased_entry) };\n                } else {\n                    return\
    \ { t, std::nullopt };\n                }\n            } else {\n            \
    \    auto [c1, erased] = erase_binary_search(child1(t), f, g);\n             \
    \   if (erased) {\n                    set_child1(t, c1);\n                  \
    \  size_type& pos = erased->first;\n                    if (is_not_null(c1) and\
    \ pos == 0) link(t, min(c1));\n                    pos += safe_size(child0(t))\
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
    \  static std::vector<value_type> dump(node_pointer t) {\n            std::vector<value_type>\
    \ res;\n            res.reserve(safe_size(t));\n            auto rec = [&](auto\
    \ rec, node_pointer t) -> void {\n                if (is_null(t)) return;\n  \
    \              node_type::push(t);\n                rec(rec, child0(t));\n   \
    \             res.push_back(value(t));\n                rec(rec, child1(t));\n\
    \            };\n            rec(rec, t);\n            return res;\n        }\n\
    \n        // Find the first element that satisfies the condition f : (value, index)\
    \ -> { false, true }.\n        // Returns { optional(value), position }\n    \
    \    template <typename Predicate>\n        static std::pair<size_type, std::optional<value_type>>\
    \ binary_search(node_pointer t, const Predicate& f) {\n            node_pointer\
    \ res = null;\n            int ng = -1, ok = safe_size(t);\n            while\
    \ (ok - ng > 1) {\n                node_type::push(t);\n                if (const\
    \ int root = ng + safe_size(child0(t)) + 1; f(value(t), root)) {\n           \
    \         res = t;\n                    ok = root, t = child0(t);\n          \
    \      } else {\n                    ng = root, t = child1(t);\n             \
    \   }\n            }\n            if (is_null(res)) {\n                return\
    \ { ok, std::nullopt };\n            } else {\n                return { ok, value(res)\
    \ };\n            }\n        }\n\n        // comp(T t, U u) = (t < u)\n      \
    \  template <typename U, typename Compare = std::less<>>\n        static std::pair<size_type,\
    \ std::optional<value_type>> lower_bound(node_pointer t, const U& target, Compare\
    \ comp) {\n            return binary_search(t, [&](const value_type& v, int) {\
    \ return not comp(v, target); });\n        }\n        // comp(T u, U t) = (u <\
    \ t)\n        template <typename U, typename Compare = std::less<>>\n        static\
    \ std::pair<size_type, std::optional<value_type>> upper_bound(node_pointer t,\
    \ const U& target, Compare comp) {\n            return binary_search(t, [&](const\
    \ value_type& v, int) { return comp(target, v); });\n        }\n\n        template\
    \ <bool reversed_, bool constant_>\n        struct NodeIterator {\n          \
    \  static constexpr bool constant = constant_;\n            static constexpr bool\
    \ reversed = reversed_;\n\n            using difference_type = Node::difference_type;\n\
    \            using value_type = Node::value_type;\n            using pointer =\
    \ std::conditional_t<constant, Node::const_pointer, Node::pointer>;\n        \
    \    using reference = std::conditional_t<constant, Node::const_reference, Node::reference>;\n\
    \            using iterator_cateogory = std::random_access_iterator_tag;\n\n \
    \           NodeIterator(): root(null), index(0) {}\n\n            reference operator*()\
    \ {\n                if (is_null(cur) and index != safe_size(root)) {\n      \
    \              cur = root;\n                    for (size_type k = index;;) {\n\
    \                        node_type::push(cur);\n                        if (size_type\
    \ siz = safe_size(child(cur, reversed)); k == siz) {\n                       \
    \     break;\n                        } else if (k < siz) {\n                \
    \            cur = child(cur, reversed);\n                        } else {\n \
    \                           cur = child(cur, not reversed);\n                \
    \            k -= siz + 1;\n                        }\n                    }\n\
    \                }\n                return value(cur);\n            }\n      \
    \      reference operator[](difference_type k) const { return *((*this) + k);\
    \ }\n\n            NodeIterator& operator++() { return *this += 1; }\n       \
    \     NodeIterator& operator--() { return *this -= 1; }\n            NodeIterator&\
    \ operator+=(difference_type k) { return suc(+k), * this; }\n            NodeIterator&\
    \ operator-=(difference_type k) { return suc(-k), * this; }\n            NodeIterator\
    \ operator++(int) { NodeIterator res = *this; ++(*this); return res; }\n     \
    \       NodeIterator operator--(int) { NodeIterator res = *this; --(*this); return\
    \ res; }\n            friend NodeIterator operator+(NodeIterator it, difference_type\
    \ k) { return it += k; }\n            friend NodeIterator operator+(difference_type\
    \ k, NodeIterator it) { return it += k; }\n            friend NodeIterator operator-(NodeIterator\
    \ it, difference_type k) { return it -= k; }\n\n            friend difference_type\
    \ operator-(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index\
    \ - rhs.index; }\n\n            friend bool operator==(const NodeIterator& lhs,\
    \ const NodeIterator& rhs) { return lhs.index == rhs.index; }\n            friend\
    \ bool operator!=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index\
    \ != rhs.index; }\n            friend bool operator<(const NodeIterator& lhs,\
    \ const NodeIterator& rhs) { return lhs.index < rhs.index; }\n            friend\
    \ bool operator>(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index\
    \ > rhs.index; }\n            friend bool operator<=(const NodeIterator& lhs,\
    \ const NodeIterator& rhs) { return lhs.index <= rhs.index; }\n            friend\
    \ bool operator>=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index\
    \ >= rhs.index; }\n\n            static NodeIterator begin(node_pointer root)\
    \ { return NodeIterator(root, 0); }\n            static NodeIterator end(node_pointer\
    \ root) { return NodeIterator(root, safe_size(root)); }\n        private:\n  \
    \          node_pointer root;\n            size_type index;\n            node_pointer\
    \ cur = null; // it==end() or uninitialized (updates only index)\n\n         \
    \   NodeIterator(node_pointer root, size_type index): root(root), index(index)\
    \ {}\n\n            void suc(difference_type k) {\n                index += k;\n\
    \                if (index == safe_size(root) or std::abs(k) >= 10) cur = null;\n\
    \                if (is_null(cur)) return;\n\n                const bool positive\
    \ = k < 0 ? (k = -k, reversed) : not reversed;\n\n                if (positive)\
    \ {\n                    while (k-- > 0) cur = next(cur);\n                } else\
    \ {\n                    while (k-- > 0) cur = prev(cur);\n                }\n\
    \            }\n        };\n        using iterator = NodeIterator<false, false>;\n\
    \        using reverse_iterator = NodeIterator<true, false>;\n        using const_iterator\
    \ = NodeIterator<false, true>;\n        using const_reverse_iterator = NodeIterator<true,\
    \ true>;\n\n        static iterator begin(node_pointer t) { return iterator::begin(t);\
    \ }\n        static iterator end(node_pointer t) { return iterator::end(t); }\n\
    \        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t);\
    \ }\n        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t);\
    \ }\n        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t);\
    \ }\n        static const_iterator cend(node_pointer t) { return const_iterator::end(t);\
    \ }\n        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t);\
    \ }\n        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t);\
    \ }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n#line 5 \"library/datastructure/bbst/implicit_treap.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T>\n        struct DefaultNode: Node<T, DefaultNode<T>> {\n      \
    \      using base = Node<T, DefaultNode<T>>;\n            using base::base;\n\
    \        };\n    }\n\n    template <typename T>\n    class DynamicArray {\n  \
    \      using node_type = internal::implicit_treap::DefaultNode<T>;\n        using\
    \ node_pointer = typename node_type::node_pointer;\n\n        node_pointer _root;\n\
    \n        struct node_pointer_construct {};\n        DynamicArray(node_pointer\
    \ root, node_pointer_construct): _root(root) {}\n\n    public:\n        using\
    \ value_type = typename node_type::value_type;\n\n        DynamicArray(): _root(node_type::empty_node())\
    \ {}\n        explicit DynamicArray(size_t n, const value_type& fill_value = {}):\
    \ _root(node_type::build(n, fill_value)) {}\n        template <typename U>\n \
    \       DynamicArray(const std::vector<U>& dat) : _root(node_type::build(dat.begin(),\
    \ dat.end())) {}\n\n        void free() {\n            node_type::delete_tree(_root);\n\
    \            _root = node_type::empty_node();\n        }\n        void clear()\
    \ { free(); }\n\n        static void reserve(size_t capacity) { node_type::reserve(capacity);\
    \ }\n\n        bool empty() const { return node_type::empty(_root); }\n      \
    \  int size() const { return node_type::safe_size(_root); }\n\n        value_type&\
    \ operator[](size_t k) {\n            assert(k < size_t(size()));\n          \
    \  return node_type::get(_root, k);\n        }\n        const value_type& operator[](size_t\
    \ k) const {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        value_type& front() { return (*this)[0]; }\n       \
    \ value_type& back() { return (*this)[size() - 1]; }\n        const value_type&\
    \ front() const { return (*this)[0]; }\n        const value_type& back() const\
    \ { return (*this)[size() - 1]; }\n\n        void insert(size_t k, const value_type&\
    \ val) {\n            assert(k <= size_t(size()));\n            _root = node_type::insert(_root,\
    \ k, val);\n        }\n        void push_front(const value_type& val) { _root\
    \ = node_type::push_front(_root, val); }\n        void push_back(const value_type&\
    \ val) { _root = node_type::push_back(_root, val); }\n\n        // Insert a new\
    \ value immediately before the first element that satisfies the condition f.\n\
    \        // Returns: the inserted position\n        // Requirements: f(A[i]) must\
    \ be monotonic\n        template <typename Predicate>\n        int insert_binary_search(const\
    \ value_type& val, const Predicate &f) {\n            int pos;\n            std::tie(_root,\
    \ pos) = node_type::insert_binary_search(_root, f, val);\n            return pos;\n\
    \        }\n        // Insert a new value immediately before the first element\
    \ that is greater than or equal to the new value.\n        // Returns: the inserted\
    \ position\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        int insert_lower_bound(const value_type& val,\
    \ const Compare &comp = {}) {\n            int pos;\n            std::tie(_root,\
    \ pos) = node_type::insert_lower_bound(_root, val, comp);\n            return\
    \ pos;\n        }\n        // Insert a new value immediately before the first\
    \ element that is greater than the new value.\n        // Returns: the inserted\
    \ position\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        int insert_upper_bound(const value_type& val,\
    \ const Compare &comp = {}) {\n            int pos;\n            std::tie(_root,\
    \ pos) = node_type::insert_upper_bound(_root, val, comp);\n            return\
    \ pos;\n        }\n\n        value_type erase(size_t k) {\n            assert(k\
    \ <= size_t(size()));\n            value_type v;\n            std::tie(_root,\
    \ v) = node_type::erase(_root, k);\n            return v;\n        }\n       \
    \ value_type pop_front() { return erase(0); }\n        value_type pop_back() {\
    \ return erase(size() - 1); }\n\n        // Erase the first element that satisfies\
    \ the condition f if it also satisfies the condition g.\n        // returns optional(position,\
    \ value)\n        // Requirements: sequence is sorted\n        template <typename\
    \ Predicate, typename RemovePredicate>\n        std::optional<std::pair<int, value_type>>\
    \ erase_binary_search(const Predicate &f, const RemovePredicate& g) {\n      \
    \      auto [root, erased] = node_type::erase_binary_search(_root, f, g);\n  \
    \          _root = root;\n            if (erased) {\n                return std::pair<int,\
    \ value_type>{ erased->first, erased->second };\n            } else {\n      \
    \          return std::nullopt;\n            }\n        }\n        // Erase the\
    \ first element that is greater than or equal to val.\n        // returns optional(position,\
    \ value)\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        std::optional<std::pair<int, value_type>> erase_lower_bound(const\
    \ value_type &val, const Compare &comp = {}) {\n            auto [root, erased]\
    \ = node_type::erase_lower_bound(_root, val, comp);\n            _root = root;\n\
    \            if (erased) {\n                return std::pair<int, value_type>{\
    \ erased->first, erased->second };\n            } else {\n                return\
    \ std::nullopt;\n            }\n        }\n        // Erase the first element\
    \ that is greater than val.\n        // returns optional(position, value)\n  \
    \      // Requirements: sequence is sorted\n        template <typename Compare\
    \ = std::less<>>\n        std::optional<std::pair<int, value_type>> erase_upper_bound(const\
    \ value_type &val, const Compare &comp = {}) {\n            auto [root, erased]\
    \ = node_type::erase_upper_bound(_root, val, comp);\n            _root = root;\n\
    \            if (erased) {\n                return std::pair<int, value_type>{\
    \ erased->first, erased->second };\n            } else {\n                return\
    \ std::nullopt;\n            }\n        }\n        // Erase the first element\
    \ that is equal to val.\n        // returns optional(position, value)\n      \
    \  // Requirements: sequence is sorted\n        template <typename Compare = std::less<>>\n\
    \        std::optional<std::pair<int, value_type>> erase_if_exists(const value_type\
    \ &val, const Compare &comp = {}) {\n            auto [root, erased] = node_type::erase_if_exists(_root,\
    \ val, comp);\n            _root = root;\n            if (erased) {\n        \
    \        return std::pair<int, value_type>{ erased->first, erased->second };\n\
    \            } else {\n                return std::nullopt;\n            }\n \
    \       }\n\n        // Split immediately before the k-th element.\n        DynamicArray\
    \ split(size_t k) {\n            assert(k <= size_t(size()));\n            node_pointer\
    \ root_r;\n            std::tie(_root, root_r) = node_type::split(_root, k);\n\
    \            return DynamicArray(root_r, node_pointer_construct{});\n        }\n\
    \        // Split immediately before the first element that satisfies the condition.\n\
    \        // Requirements: f(A[i]) must be monotonic\n        template <typename\
    \ Predicate>\n        DynamicArray split_binary_search(const Predicate &f) {\n\
    \            node_pointer root_r;\n            std::tie(_root, root_r) = node_type::split_binary_search(_root,\
    \ f);\n            return DynamicArray(root_r, node_pointer_construct{});\n  \
    \      }\n        // Split immediately before the first element that is greater\
    \ than or equal to val.\n        // Requirements: sequence is sorted\n       \
    \ template <typename Compare = std::less<>>\n        DynamicArray split_lower_bound(const\
    \ value_type &val, const Compare &comp = {}) {\n            node_pointer root_r;\n\
    \            std::tie(_root, root_r) = node_type::split_lower_bound(_root, val,\
    \ comp);\n            return DynamicArray(root_r, node_pointer_construct{});\n\
    \        }\n        // Split immediately before the first element that is greater\
    \ than val.\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        DynamicArray split_upper_bound(const value_type\
    \ &val, const Compare &comp = {}) {\n            node_pointer root_r;\n      \
    \      std::tie(_root, root_r) = node_type::split_upper_bound(_root, val, comp);\n\
    \            return DynamicArray(root_r, node_pointer_construct{});\n        }\n\
    \n        void merge(DynamicArray r) { _root = node_type::merge(_root, r._root);\
    \ }\n\n        void rotate(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, k);\n        }\n        void rotate(size_t\
    \ l, size_t m, size_t r) {\n            assert(l <= m and m <= r and r <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, l, m, r);\n        }\n\n       \
    \ std::vector<value_type> dump() const { return node_type::dump(_root); }\n\n\
    \        // Find the first element that satisfies the condition f.\n        //\
    \ Returns { position, optional(value) }\n        // Requirements: f(A[i]) must\
    \ be monotonic\n        template <typename Predicate>\n        std::pair<int,\
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
    \            return { pos, std::move(val) };\n        }\n\n        using iterator\
    \ = typename node_type::iterator;\n        using reverse_iterator = typename node_type::reverse_iterator;\n\
    \        using const_iterator = typename node_type::const_iterator;\n        using\
    \ const_reverse_iterator = typename node_type::const_reverse_iterator;\n\n   \
    \     iterator begin() { return node_type::begin(_root); }\n        iterator end()\
    \ { return node_type::end(_root); }\n        reverse_iterator rbegin() { return\
    \ node_type::rbegin(_root); }\n        reverse_iterator rend() { return node_type::rend(_root);\
    \ }\n\n        const_iterator begin() const { return cbegin(); }\n        const_iterator\
    \ end() const { return cend(); }\n        const_reverse_iterator rbegin() const\
    \ { return crbegin(); }\n        const_reverse_iterator rend() const { return\
    \ crend(); }\n        const_iterator cbegin() const { return node_type::cbegin(_root);\
    \ }\n        const_iterator cend() const { return node_type::cend(_root); }\n\
    \        const_reverse_iterator crbegin() const { return node_type::crbegin(_root);\
    \ }\n        const_reverse_iterator crend() const { return node_type::crend(_root);\
    \ }\n    };\n} // namespace suisen\n\n\n\n#line 5 \"test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp\"\
    \n\nusing Sequence = suisen::DynamicArray<int>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::string s;\n    std::cin >>\
    \ n >> s;\n\n    Sequence t;\n    t.push_back(0);\n\n    int pos = 0;\n    for\
    \ (int i = 0; i < n; ++i) {\n        if (s[i] == 'L') {\n            t.insert(pos,\
    \ i + 1);\n        } else {\n            t.insert(++pos, i + 1);\n        }\n\
    \    }\n    std::vector<int> res = t.dump();\n\n    for (int i = 0; i <= n; ++i)\
    \ {\n        std::cout << res[i] << \" \\n\"[i == n];\n    }\n\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc237/tasks/abc237_d\"\n\n\
    #include <iostream>\n#include \"library/datastructure/bbst/implicit_treap.hpp\"\
    \n\nusing Sequence = suisen::DynamicArray<int>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::string s;\n    std::cin >>\
    \ n >> s;\n\n    Sequence t;\n    t.push_back(0);\n\n    int pos = 0;\n    for\
    \ (int i = 0; i < n; ++i) {\n        if (s[i] == 'L') {\n            t.insert(pos,\
    \ i + 1);\n        } else {\n            t.insert(++pos, i + 1);\n        }\n\
    \    }\n    std::vector<int> res = t.dump();\n\n    for (int i = 0; i <= n; ++i)\
    \ {\n        std::cout << res[i] << \" \\n\"[i == n];\n    }\n\n    return 0;\n\
    }\n"
  dependsOn:
  - library/datastructure/bbst/implicit_treap.hpp
  - library/datastructure/bbst/implicit_treap_base.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
  requiredBy: []
  timestamp: '2023-02-04 02:55:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
- /verify/test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp.html
title: test/src/datastructure/bbst/implicit_treap/abc237_d.test.cpp
---
