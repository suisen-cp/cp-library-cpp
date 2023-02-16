---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/util/pointer_32bit.hpp
    title: library/util/pointer_32bit.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap.hpp
    title: library/datastructure/bbst/reversible_implicit_treap.hpp
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
  bundledCode: "#line 1 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include\
    \ <cstdint>\n#include <optional>\n#include <string>\n#include <random>\n#include\
    \ <tuple>\n#include <vector>\n#include <utility>\n\n#line 1 \"library/util/pointer_32bit.hpp\"\
    \n\n\n\n#line 5 \"library/util/pointer_32bit.hpp\"\n\nnamespace suisen {\n   \
    \ template <typename Object>\n    struct ptr32 {\n        static constexpr int\
    \ null = -1;\n\n        using object_type = Object;\n        using pool_type =\
    \ std::vector<object_type>;\n\n        constexpr ptr32() : ptr(null) {}\n    \
    \    explicit constexpr ptr32(int ptr) : ptr(ptr) {}\n\n        object_type& operator*()\
    \ const { return pool[ptr]; }\n        object_type* operator->() const { return\
    \ &pool[ptr]; }\n\n        constexpr operator bool() const { return ptr != null;\
    \ }\n        constexpr operator int() const { return ptr; }\n\n        constexpr\
    \ bool is_not_null() const { return bool(*this); }\n        constexpr bool is_null()\
    \ const { return not bool(*this); }\n\n        friend constexpr bool operator==(const\
    \ ptr32& l, const ptr32& r) { return l.ptr == r.ptr; }\n        friend constexpr\
    \ bool operator!=(const ptr32& l, const ptr32& r) { return l.ptr != r.ptr; }\n\
    \        friend constexpr bool operator<(const ptr32& l, const ptr32& r) { return\
    \ l.ptr < r.ptr; }\n        friend constexpr bool operator<=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr <= r.ptr; }\n        friend constexpr bool operator>(const\
    \ ptr32& l, const ptr32& r) { return l.ptr > r.ptr; }\n        friend constexpr\
    \ bool operator>=(const ptr32& l, const ptr32& r) { return l.ptr >= r.ptr; }\n\
    \n        template <typename ...Args>\n        static ptr32 alloc(Args &&...args)\
    \ {\n            if (del.size()) {\n                ptr32 ptr(del.back());\n \
    \               del.pop_back();\n                *ptr = object_type(std::forward<Args>(args)...);\n\
    \                return ptr;\n            } else {\n                ptr32 ptr(pool.size());\n\
    \                pool.emplace_back(std::forward<Args>(args)...);\n           \
    \     return ptr;\n            }\n        }\n        static void dealloc(ptr32\
    \ p) {\n            del.push_back(p);\n        }\n        static void dealloc_all(bool\
    \ shrink) {\n            pool.clear(), del.clear();\n            if (shrink) pool.shrink_to_fit(),\
    \ del.shrink_to_fit();\n        }\n        static void reserve(size_t capacity)\
    \ {\n            pool.reserve(capacity);\n        }\n    private:\n        static\
    \ inline pool_type pool{};\n        static inline std::vector<ptr32> del{};\n\n\
    \        int ptr;\n    };\n} // namespace suisen\n\n\n\n#line 16 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n\nnamespace suisen::internal::implicit_treap {\n    template <typename T, typename\
    \ Derived>\n    struct ReversibleNode {\n        using random_engine = std::mt19937;\n\
    \        static inline random_engine rng{ std::random_device{}() };\n\n      \
    \  using priority_type = uint32_t;\n\n        static priority_type random_priority()\
    \ {\n            return rng();\n        }\n\n        using node_type = Derived;\n\
    \        using node_pointer = ptr32<node_type>;\n\n        using size_type = uint32_t;\n\
    \n        using difference_type = int32_t;\n        using value_type = T;\n  \
    \      using pointer = value_type*;\n        using const_pointer = const value_type*;\n\
    \        using reference = value_type&;\n        using const_reference = const\
    \ value_type&;\n\n        node_pointer _ch[2]{ node_pointer{}, node_pointer{}\
    \ };\n        value_type _val;\n        size_type _size;\n        priority_type\
    \ _priority;\n\n        bool _rev = false;\n\n        ReversibleNode(const value_type\
    \ val = {}): _val(val), _size(1), _priority(random_priority()) {}\n\n        static\
    \ void reserve(size_type capacity) { node_pointer::reserve(capacity); }\n\n  \
    \      static value_type& value(node_pointer t) { return t->_val; }\n        static\
    \ value_type set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t),\
    \ new_val); }\n\n        static constexpr bool empty(node_pointer t) { return\
    \ not t; }\n        static size_type& size(node_pointer t) { return t->_size;\
    \ }\n        static size_type safe_size(node_pointer t) { return t ? t->_size\
    \ : 0; }\n\n        static priority_type& priority(node_pointer t) { return t->_priority;\
    \ }\n        static void set_priority(node_pointer t, priority_type new_priority)\
    \ { priority(t) = new_priority; }\n\n        static node_pointer& child0(node_pointer\
    \ t) { return t->_ch[0]; }\n        static node_pointer& child1(node_pointer t)\
    \ { return t->_ch[1]; }\n        static node_pointer& child(node_pointer t, bool\
    \ b) { return t->_ch[b]; }\n        static node_pointer set_child0(node_pointer\
    \ t, node_pointer cid) { return std::exchange(child0(t), cid); }\n        static\
    \ node_pointer set_child1(node_pointer t, node_pointer cid) { return std::exchange(child1(t),\
    \ cid); }\n        static node_pointer set_child(node_pointer t, bool b, node_pointer\
    \ cid) { return std::exchange(child(t, b), cid); }\n\n        static bool& reversed(node_pointer\
    \ t) { return t->_rev; }\n\n        static node_pointer update(node_pointer t)\
    \ { // t : not null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t))\
    \ + 1;\n            return t;\n        }\n        static void push(node_pointer\
    \ t) { // t : not null\n            if (std::exchange(reversed(t), false)) {\n\
    \                reverse_all(child0(t));\n                reverse_all(child1(t));\n\
    \            }\n        }\n\n        static constexpr node_pointer empty_node()\
    \ { return node_pointer{}; }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (not t) return;\n            delete_tree(child0(t));\n   \
    \         delete_tree(child1(t));\n            node_pointer::dealloc(t);\n   \
    \     }\n\n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            std::vector<value_type> dat(std::forward<Args>(args)...);\n\
    \n            const size_t n = dat.size();\n\n            if (n == 0) return empty_node();\n\
    \n            std::vector<priority_type> priorities(n);\n            std::generate(priorities.begin(),\
    \ priorities.end(), random_priority);\n            std::make_heap(priorities.begin(),\
    \ priorities.end());\n\n            std::vector<node_pointer> nodes(n);\n\n  \
    \          size_t fpow2 = 1;\n            while ((fpow2 << 1) <= n) fpow2 <<=\
    \ 1;\n\n            for (size_t bbst_index = 1, skipped = 0; bbst_index < 2 *\
    \ fpow2; ++bbst_index) {\n                size_t heap_index = (fpow2 | ((bbst_index\
    \ - 1) >> 1)) >> __builtin_ctz(bbst_index);\n                if (heap_index <=\
    \ n) {\n                    size_t index = bbst_index - skipped;\n           \
    \         nodes[heap_index - 1] = node_pointer::alloc(std::move(dat[index - 1]));\n\
    \                    set_priority(nodes[heap_index - 1], priorities[heap_index\
    \ - 1]);\n                } else {\n                    ++skipped;\n         \
    \       }\n            }\n            for (size_t i = fpow2 - 1; i >= 1; --i)\
    \ {\n                size_t li = 2 * i, ri = 2 * i + 1;\n                if (li\
    \ <= n) set_child0(nodes[i - 1], nodes[li - 1]);\n                if (ri <= n)\
    \ set_child1(nodes[i - 1], nodes[ri - 1]);\n                node_type::update(nodes[i\
    \ - 1]);\n            }\n            return nodes[0];\n        }\n\n        static\
    \ std::pair<node_pointer, node_pointer> split(node_pointer t, size_type k) {\n\
    \            if (k == 0) return { empty_node(), t };\n            if (k == size(t))\
    \ return { t, empty_node() };\n\n            static std::vector<node_pointer>\
    \ lp{}, rp{};\n\n            while (true) {\n                node_type::push(t);\n\
    \                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n\
    \                    if (rp.size()) set_child0(rp.back(), t);\n              \
    \      rp.push_back(t);\n                    if (k == lsiz) {\n              \
    \          node_pointer& lch = child0(t);\n                        if (lp.size())\
    \ set_child1(lp.back(), lch);\n\n                        node_pointer lt = std::exchange(lch,\
    \ empty_node()), rt = empty_node();\n                        while (lp.size())\
    \ node_type::update(lt = lp.back()), lp.pop_back();\n                        while\
    \ (rp.size()) node_type::update(rt = rp.back()), rp.pop_back();\n            \
    \            return { lt, rt };\n                    }\n                    t\
    \ = child0(t);\n                } else {\n                    if (lp.size()) set_child1(lp.back(),\
    \ t);\n                    lp.push_back(t);\n                    t = child1(t);\n\
    \                    k -= lsiz + 1;\n                }\n            }\n      \
    \  }\n        static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer\
    \ t, size_type l, size_type r) {\n            auto [tlm, tr] = split(t, r);\n\
    \            auto [tl, tm] = split(tlm, l);\n            return { tl, tm, tr };\n\
    \        }\n        // Split immediately before the first element that satisfies\
    \ the condition.\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ node_pointer> split_binary_search(node_pointer t, const Predicate& f) {\n  \
    \          if (not t) {\n                return { empty_node(), empty_node() };\n\
    \            }\n            node_type::push(t);\n            if (f(value(t)))\
    \ {\n                auto [ll, lr] = split_binary_search(child0(t), f);\n    \
    \            set_child0(t, lr);\n                return { ll, node_type::update(t)\
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
    \ tl, node_pointer tr) {\n            if (not (tl and tr)) {\n               \
    \ return tl ? tl : tr;\n            }\n            if (priority(tl) < priority(tr))\
    \ {\n                node_type::push(tr);\n                set_child0(tr, merge(tl,\
    \ child0(tr)));\n                return node_type::update(tr);\n            }\
    \ else {\n                node_type::push(tl);\n                set_child1(tl,\
    \ merge(child1(tl), tr));\n                return node_type::update(tl);\n   \
    \         }\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer\
    \ new_node) {\n            if (not t) {\n                return new_node;\n  \
    \          }\n            static std::vector<node_pointer> st;\n\n           \
    \ node_pointer* p = nullptr;\n\n            while (true) {\n                if\
    \ ((not t) or priority(new_node) > priority(t)) {\n                    if (t)\
    \ {\n                        auto [tl, tr] = split(t, k);\n                  \
    \      set_child0(new_node, tl);\n                        set_child1(new_node,\
    \ tr);\n                        t = node_type::update(new_node);\n           \
    \         } else {\n                        t = new_node;\n                  \
    \  }\n                    if (p) *p = t;\n                    while (st.size())\
    \ {\n                        t = node_type::update(st.back()), st.pop_back();\n\
    \                    }\n                    return t;\n                } else\
    \ {\n                    node_type::push(t);\n                    st.push_back(t);\n\
    \                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz)\
    \ {\n                        t = *(p = &child0(t));\n                    } else\
    \ {\n                        t = *(p = &child1(t));\n                        k\
    \ -= lsiz + 1;\n                    }\n                }\n            }\n    \
    \    }\n        template <typename ...Args>\n        static node_pointer insert(node_pointer\
    \ t, size_type k, Args &&...args) {\n            return insert_impl(t, k, node_pointer::alloc(std::forward<Args>(args)...));\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        // Insert a new node immediately before the first element\
    \ that satisfies the condition.\n        // Returns { node, position to insert\
    \ }\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer\
    \ new_node) {\n            if (not t) {\n                return { new_node, 0\
    \ };\n            }\n            if (priority(new_node) > priority(t)) {\n   \
    \             auto [tl, tr] = split_binary_search(t, f);\n                set_child0(new_node,\
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
    \ f, node_pointer::alloc(std::forward<Args>(args)...));\n        }\n        template\
    \ <typename Compare = std::less<>>\n        static std::pair<node_pointer, size_type>\
    \ insert_lower_bound(node_pointer t, const value_type& v, Compare comp) {\n  \
    \          return insert_binary_search(t, [&](const value_type& x) { return not\
    \ comp(x, v); }, v);\n        }\n        template <typename Compare = std::less<>>\n\
    \        static std::pair<node_pointer, size_type> insert_upper_bound(node_pointer\
    \ t, const value_type& v, Compare comp) {\n            return insert_binary_search(t,\
    \ [&](const value_type& x) { return comp(v, x); }, v);\n        }\n\n        static\
    \ std::pair<node_pointer, value_type> erase(node_pointer t, size_type k) {\n \
    \           node_type::push(t);\n            if (const size_type lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                node_pointer::dealloc(t);\n                return\
    \ { merge(child0(t), child1(t)), std::move(value(t)) };\n            } else if\
    \ (k < lsiz) {\n                auto [c0, v] = erase(child0(t), k);\n        \
    \        set_child0(t, c0);\n                return { node_type::update(t), std::move(v)\
    \ };\n            } else {\n                auto [c1, v] = erase(child1(t), k\
    \ - (lsiz + 1));\n                set_child1(t, c1);\n                return {\
    \ node_type::update(t), std::move(v) };\n            }\n        }\n        static\
    \ std::pair<node_pointer, value_type> pop_front(node_pointer t) { return erase(t,\
    \ 0); }\n        static std::pair<node_pointer, value_type> pop_back(node_pointer\
    \ t) { return erase(t, safe_size(t) - 1); }\n\n        // Erase the first element\
    \ that satisfies the condition f if it also satisfies the condition g.\n     \
    \   // returns { node, optional(position, value) }\n        template <typename\
    \ Predicate, typename RemovePredicate>\n        static std::pair<node_pointer,\
    \ std::optional<std::pair<size_type, value_type>>> erase_binary_search(node_pointer\
    \ t, const Predicate& f, const RemovePredicate& g) {\n            if (not t) return\
    \ { empty_node(), std::nullopt };\n            node_type::push(t);\n         \
    \   if (f(value(t))) {\n                auto [c0, erased] = erase_binary_search(child0(t),\
    \ f, g);\n                if (erased) {\n                    set_child0(t, c0);\n\
    \                    return { node_type::update(t), std::move(erased) };\n   \
    \             } else if (g(value(t))) {\n                    node_pointer::dealloc(t);\n\
    \                    std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)),\
    \ std::move(value(t)) };\n                    return { merge(child0(t), child1(t)),\
    \ std::move(erased_entry) };\n                } else {\n                    return\
    \ { t, std::nullopt };\n                }\n            } else {\n            \
    \    auto [c1, erased] = erase_binary_search(child1(t), f, g);\n             \
    \   if (erased) {\n                    set_child1(t, c1);\n                  \
    \  size_type& pos = erased->first;\n                    pos += safe_size(child0(t))\
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
    \  static node_pointer reverse_all(node_pointer t) {\n            if (t) {\n \
    \               reversed(t) ^= true;\n                std::swap(child0(t), child1(t));\n\
    \            }\n            return t;\n        }\n        static node_pointer\
    \ reverse(node_pointer t, size_type l, size_type r) {\n            auto [tl, tm,\
    \ tr] = split(t, l, r);\n            return merge(tl, Derived::reverse_all(tm),\
    \ tr);\n        }\n\n        static std::vector<value_type> dump(node_pointer\
    \ t) {\n            std::vector<value_type> res;\n            res.reserve(safe_size(t));\n\
    \            auto rec = [&](auto rec, node_pointer t) -> void {\n            \
    \    if (not t) return;\n                node_type::push(t);\n               \
    \ rec(rec, child0(t));\n                res.push_back(value(t));\n           \
    \     rec(rec, child1(t));\n            };\n            rec(rec, t);\n       \
    \     return res;\n        }\n\n        // Find the first element that satisfies\
    \ the condition f : (value, index) -> { false, true }.\n        // Returns { optional(value),\
    \ position }\n        template <typename Predicate>\n        static std::pair<size_type,\
    \ std::optional<value_type>> binary_search(node_pointer t, const Predicate& f)\
    \ {\n            node_pointer res = empty_node();\n            int ng = -1, ok\
    \ = safe_size(t);\n            while (ok - ng > 1) {\n                node_type::push(t);\n\
    \                if (const int root = ng + safe_size(child0(t)) + 1; f(value(t),\
    \ root)) {\n                    res = t;\n                    ok = root, t = child0(t);\n\
    \                } else {\n                    ng = root, t = child1(t);\n   \
    \             }\n            }\n            if (not res) {\n                return\
    \ { ok, std::nullopt };\n            } else {\n                return { ok, value(res)\
    \ };\n            }\n        }\n\n        // for debug\n        static void check_heap(node_pointer\
    \ t) {\n            if (node_pointer lch = child0(t)) {\n                check_heap(lch);\n\
    \                assert(priority(t) >= priority(lch));\n            }\n      \
    \      if (node_pointer rch = child1(t)) {\n                check_heap(rch);\n\
    \                assert(priority(t) >= priority(rch));\n            }\n      \
    \  }\n\n        // comp(T t, U u) = (t < u)\n        template <typename U, typename\
    \ Compare = std::less<>>\n        static std::pair<size_type, std::optional<value_type>>\
    \ lower_bound(node_pointer t, const U& target, Compare comp) {\n            return\
    \ binary_search(t, [&](const value_type& v, int) { return not comp(v, target);\
    \ });\n        }\n        // comp(T u, U t) = (u < t)\n        template <typename\
    \ U, typename Compare = std::less<>>\n        static std::pair<size_type, std::optional<value_type>>\
    \ upper_bound(node_pointer t, const U& target, Compare comp) {\n            return\
    \ binary_search(t, [&](const value_type& v, int) { return comp(target, v); });\n\
    \        }\n\n        template <bool reversed_, bool constant_>\n        struct\
    \ NodeIterator {\n            static constexpr bool constant = constant_;\n  \
    \          static constexpr bool reversed = reversed_;\n\n            using difference_type\
    \ = ReversibleNode::difference_type;\n            using value_type = ReversibleNode::value_type;\n\
    \            using pointer = std::conditional_t<constant, ReversibleNode::const_pointer,\
    \ ReversibleNode::pointer>;\n            using reference = std::conditional_t<constant,\
    \ ReversibleNode::const_reference, ReversibleNode::reference>;\n            using\
    \ iterator_cateogory = std::random_access_iterator_tag;\n\n            NodeIterator():\
    \ root(empty_node()), index(0) {}\n\n            reference operator*() {\n   \
    \             if (stk.empty() and index != safe_size(root)) down(root, index,\
    \ not reversed);\n                return value(stk.back());\n            }\n \
    \           reference operator[](difference_type k) const { return *((*this) +\
    \ k); }\n\n            NodeIterator& operator++() { return *this += 1; }\n   \
    \         NodeIterator& operator--() { return *this -= 1; }\n            NodeIterator&\
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
    \          node_pointer root;\n            size_type index;\n            std::vector<node_pointer>\
    \ stk;\n\n            NodeIterator(node_pointer root, size_type index): root(root),\
    \ index(index) {}\n\n            void up(const bool positive) {\n            \
    \    node_pointer t = stk.back();\n                while (true) {\n          \
    \          stk.pop_back();\n                    if (t == child(stk.back(), not\
    \ positive)) return;\n                    t = stk.back();\n                }\n\
    \            }\n            void down(node_pointer t, size_type k, const bool\
    \ positive) {\n                while (true) {\n                    node_type::push(t);\n\
    \                    stk.push_back(t);\n\n                    if (size_type siz\
    \ = safe_size(child(t, not positive)); k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not positive);\n                    } else {\n                        k -= siz\
    \ + 1;\n                        t = child(t, positive);\n                    }\n\
    \                }\n            }\n            void suc(difference_type k) {\n\
    \                index += k;\n                if (index == safe_size(root)) stk.clear();\n\
    \                if (stk.empty()) return;\n\n                const bool positive\
    \ = k < 0 ? (k = -k, reversed) : not reversed;\n                while (k) {\n\
    \                    node_pointer t = child(stk.back(), positive);\n         \
    \           if (difference_type siz = safe_size(t); k > siz) {\n             \
    \           up(positive);\n                        k -= siz + 1;\n           \
    \         } else {\n                        down(t, k - 1, positive);\n      \
    \                  break;\n                    }\n                }\n        \
    \    }\n        };\n        using iterator = NodeIterator<false, false>;\n   \
    \     using reverse_iterator = NodeIterator<true, false>;\n        using const_iterator\
    \ = NodeIterator<false, true>;\n        using const_reverse_iterator = NodeIterator<true,\
    \ true>;\n\n        static iterator begin(node_pointer t) { return iterator::begin(t);\
    \ }\n        static iterator end(node_pointer t) { return iterator::end(t); }\n\
    \        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t);\
    \ }\n        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t);\
    \ }\n        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t);\
    \ }\n        static const_iterator cend(node_pointer t) { return const_iterator::end(t);\
    \ }\n        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t);\
    \ }\n        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t);\
    \ }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n\n"
  code: "#ifndef SUISEN_IMPLICIT_TREAP_ERVERSIBLE_BASE\n#define SUISEN_IMPLICIT_TREAP_ERVERSIBLE_BASE\n\
    \n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n\
    #include <optional>\n#include <string>\n#include <random>\n#include <tuple>\n\
    #include <vector>\n#include <utility>\n\n#include \"library/util/pointer_32bit.hpp\"\
    \n\nnamespace suisen::internal::implicit_treap {\n    template <typename T, typename\
    \ Derived>\n    struct ReversibleNode {\n        using random_engine = std::mt19937;\n\
    \        static inline random_engine rng{ std::random_device{}() };\n\n      \
    \  using priority_type = uint32_t;\n\n        static priority_type random_priority()\
    \ {\n            return rng();\n        }\n\n        using node_type = Derived;\n\
    \        using node_pointer = ptr32<node_type>;\n\n        using size_type = uint32_t;\n\
    \n        using difference_type = int32_t;\n        using value_type = T;\n  \
    \      using pointer = value_type*;\n        using const_pointer = const value_type*;\n\
    \        using reference = value_type&;\n        using const_reference = const\
    \ value_type&;\n\n        node_pointer _ch[2]{ node_pointer{}, node_pointer{}\
    \ };\n        value_type _val;\n        size_type _size;\n        priority_type\
    \ _priority;\n\n        bool _rev = false;\n\n        ReversibleNode(const value_type\
    \ val = {}): _val(val), _size(1), _priority(random_priority()) {}\n\n        static\
    \ void reserve(size_type capacity) { node_pointer::reserve(capacity); }\n\n  \
    \      static value_type& value(node_pointer t) { return t->_val; }\n        static\
    \ value_type set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t),\
    \ new_val); }\n\n        static constexpr bool empty(node_pointer t) { return\
    \ not t; }\n        static size_type& size(node_pointer t) { return t->_size;\
    \ }\n        static size_type safe_size(node_pointer t) { return t ? t->_size\
    \ : 0; }\n\n        static priority_type& priority(node_pointer t) { return t->_priority;\
    \ }\n        static void set_priority(node_pointer t, priority_type new_priority)\
    \ { priority(t) = new_priority; }\n\n        static node_pointer& child0(node_pointer\
    \ t) { return t->_ch[0]; }\n        static node_pointer& child1(node_pointer t)\
    \ { return t->_ch[1]; }\n        static node_pointer& child(node_pointer t, bool\
    \ b) { return t->_ch[b]; }\n        static node_pointer set_child0(node_pointer\
    \ t, node_pointer cid) { return std::exchange(child0(t), cid); }\n        static\
    \ node_pointer set_child1(node_pointer t, node_pointer cid) { return std::exchange(child1(t),\
    \ cid); }\n        static node_pointer set_child(node_pointer t, bool b, node_pointer\
    \ cid) { return std::exchange(child(t, b), cid); }\n\n        static bool& reversed(node_pointer\
    \ t) { return t->_rev; }\n\n        static node_pointer update(node_pointer t)\
    \ { // t : not null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t))\
    \ + 1;\n            return t;\n        }\n        static void push(node_pointer\
    \ t) { // t : not null\n            if (std::exchange(reversed(t), false)) {\n\
    \                reverse_all(child0(t));\n                reverse_all(child1(t));\n\
    \            }\n        }\n\n        static constexpr node_pointer empty_node()\
    \ { return node_pointer{}; }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (not t) return;\n            delete_tree(child0(t));\n   \
    \         delete_tree(child1(t));\n            node_pointer::dealloc(t);\n   \
    \     }\n\n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            std::vector<value_type> dat(std::forward<Args>(args)...);\n\
    \n            const size_t n = dat.size();\n\n            if (n == 0) return empty_node();\n\
    \n            std::vector<priority_type> priorities(n);\n            std::generate(priorities.begin(),\
    \ priorities.end(), random_priority);\n            std::make_heap(priorities.begin(),\
    \ priorities.end());\n\n            std::vector<node_pointer> nodes(n);\n\n  \
    \          size_t fpow2 = 1;\n            while ((fpow2 << 1) <= n) fpow2 <<=\
    \ 1;\n\n            for (size_t bbst_index = 1, skipped = 0; bbst_index < 2 *\
    \ fpow2; ++bbst_index) {\n                size_t heap_index = (fpow2 | ((bbst_index\
    \ - 1) >> 1)) >> __builtin_ctz(bbst_index);\n                if (heap_index <=\
    \ n) {\n                    size_t index = bbst_index - skipped;\n           \
    \         nodes[heap_index - 1] = node_pointer::alloc(std::move(dat[index - 1]));\n\
    \                    set_priority(nodes[heap_index - 1], priorities[heap_index\
    \ - 1]);\n                } else {\n                    ++skipped;\n         \
    \       }\n            }\n            for (size_t i = fpow2 - 1; i >= 1; --i)\
    \ {\n                size_t li = 2 * i, ri = 2 * i + 1;\n                if (li\
    \ <= n) set_child0(nodes[i - 1], nodes[li - 1]);\n                if (ri <= n)\
    \ set_child1(nodes[i - 1], nodes[ri - 1]);\n                node_type::update(nodes[i\
    \ - 1]);\n            }\n            return nodes[0];\n        }\n\n        static\
    \ std::pair<node_pointer, node_pointer> split(node_pointer t, size_type k) {\n\
    \            if (k == 0) return { empty_node(), t };\n            if (k == size(t))\
    \ return { t, empty_node() };\n\n            static std::vector<node_pointer>\
    \ lp{}, rp{};\n\n            while (true) {\n                node_type::push(t);\n\
    \                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {\n\
    \                    if (rp.size()) set_child0(rp.back(), t);\n              \
    \      rp.push_back(t);\n                    if (k == lsiz) {\n              \
    \          node_pointer& lch = child0(t);\n                        if (lp.size())\
    \ set_child1(lp.back(), lch);\n\n                        node_pointer lt = std::exchange(lch,\
    \ empty_node()), rt = empty_node();\n                        while (lp.size())\
    \ node_type::update(lt = lp.back()), lp.pop_back();\n                        while\
    \ (rp.size()) node_type::update(rt = rp.back()), rp.pop_back();\n            \
    \            return { lt, rt };\n                    }\n                    t\
    \ = child0(t);\n                } else {\n                    if (lp.size()) set_child1(lp.back(),\
    \ t);\n                    lp.push_back(t);\n                    t = child1(t);\n\
    \                    k -= lsiz + 1;\n                }\n            }\n      \
    \  }\n        static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer\
    \ t, size_type l, size_type r) {\n            auto [tlm, tr] = split(t, r);\n\
    \            auto [tl, tm] = split(tlm, l);\n            return { tl, tm, tr };\n\
    \        }\n        // Split immediately before the first element that satisfies\
    \ the condition.\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ node_pointer> split_binary_search(node_pointer t, const Predicate& f) {\n  \
    \          if (not t) {\n                return { empty_node(), empty_node() };\n\
    \            }\n            node_type::push(t);\n            if (f(value(t)))\
    \ {\n                auto [ll, lr] = split_binary_search(child0(t), f);\n    \
    \            set_child0(t, lr);\n                return { ll, node_type::update(t)\
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
    \ tl, node_pointer tr) {\n            if (not (tl and tr)) {\n               \
    \ return tl ? tl : tr;\n            }\n            if (priority(tl) < priority(tr))\
    \ {\n                node_type::push(tr);\n                set_child0(tr, merge(tl,\
    \ child0(tr)));\n                return node_type::update(tr);\n            }\
    \ else {\n                node_type::push(tl);\n                set_child1(tl,\
    \ merge(child1(tl), tr));\n                return node_type::update(tl);\n   \
    \         }\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer\
    \ new_node) {\n            if (not t) {\n                return new_node;\n  \
    \          }\n            static std::vector<node_pointer> st;\n\n           \
    \ node_pointer* p = nullptr;\n\n            while (true) {\n                if\
    \ ((not t) or priority(new_node) > priority(t)) {\n                    if (t)\
    \ {\n                        auto [tl, tr] = split(t, k);\n                  \
    \      set_child0(new_node, tl);\n                        set_child1(new_node,\
    \ tr);\n                        t = node_type::update(new_node);\n           \
    \         } else {\n                        t = new_node;\n                  \
    \  }\n                    if (p) *p = t;\n                    while (st.size())\
    \ {\n                        t = node_type::update(st.back()), st.pop_back();\n\
    \                    }\n                    return t;\n                } else\
    \ {\n                    node_type::push(t);\n                    st.push_back(t);\n\
    \                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz)\
    \ {\n                        t = *(p = &child0(t));\n                    } else\
    \ {\n                        t = *(p = &child1(t));\n                        k\
    \ -= lsiz + 1;\n                    }\n                }\n            }\n    \
    \    }\n        template <typename ...Args>\n        static node_pointer insert(node_pointer\
    \ t, size_type k, Args &&...args) {\n            return insert_impl(t, k, node_pointer::alloc(std::forward<Args>(args)...));\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_front(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, 0, std::forward<Args>(args)...);\n\
    \        }\n        template <typename ...Args>\n        static node_pointer push_back(node_pointer\
    \ t, Args &&...args) {\n            return insert(t, safe_size(t), std::forward<Args>(args)...);\n\
    \        }\n\n        // Insert a new node immediately before the first element\
    \ that satisfies the condition.\n        // Returns { node, position to insert\
    \ }\n        template <typename Predicate>\n        static std::pair<node_pointer,\
    \ size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer\
    \ new_node) {\n            if (not t) {\n                return { new_node, 0\
    \ };\n            }\n            if (priority(new_node) > priority(t)) {\n   \
    \             auto [tl, tr] = split_binary_search(t, f);\n                set_child0(new_node,\
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
    \ f, node_pointer::alloc(std::forward<Args>(args)...));\n        }\n        template\
    \ <typename Compare = std::less<>>\n        static std::pair<node_pointer, size_type>\
    \ insert_lower_bound(node_pointer t, const value_type& v, Compare comp) {\n  \
    \          return insert_binary_search(t, [&](const value_type& x) { return not\
    \ comp(x, v); }, v);\n        }\n        template <typename Compare = std::less<>>\n\
    \        static std::pair<node_pointer, size_type> insert_upper_bound(node_pointer\
    \ t, const value_type& v, Compare comp) {\n            return insert_binary_search(t,\
    \ [&](const value_type& x) { return comp(v, x); }, v);\n        }\n\n        static\
    \ std::pair<node_pointer, value_type> erase(node_pointer t, size_type k) {\n \
    \           node_type::push(t);\n            if (const size_type lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                node_pointer::dealloc(t);\n                return\
    \ { merge(child0(t), child1(t)), std::move(value(t)) };\n            } else if\
    \ (k < lsiz) {\n                auto [c0, v] = erase(child0(t), k);\n        \
    \        set_child0(t, c0);\n                return { node_type::update(t), std::move(v)\
    \ };\n            } else {\n                auto [c1, v] = erase(child1(t), k\
    \ - (lsiz + 1));\n                set_child1(t, c1);\n                return {\
    \ node_type::update(t), std::move(v) };\n            }\n        }\n        static\
    \ std::pair<node_pointer, value_type> pop_front(node_pointer t) { return erase(t,\
    \ 0); }\n        static std::pair<node_pointer, value_type> pop_back(node_pointer\
    \ t) { return erase(t, safe_size(t) - 1); }\n\n        // Erase the first element\
    \ that satisfies the condition f if it also satisfies the condition g.\n     \
    \   // returns { node, optional(position, value) }\n        template <typename\
    \ Predicate, typename RemovePredicate>\n        static std::pair<node_pointer,\
    \ std::optional<std::pair<size_type, value_type>>> erase_binary_search(node_pointer\
    \ t, const Predicate& f, const RemovePredicate& g) {\n            if (not t) return\
    \ { empty_node(), std::nullopt };\n            node_type::push(t);\n         \
    \   if (f(value(t))) {\n                auto [c0, erased] = erase_binary_search(child0(t),\
    \ f, g);\n                if (erased) {\n                    set_child0(t, c0);\n\
    \                    return { node_type::update(t), std::move(erased) };\n   \
    \             } else if (g(value(t))) {\n                    node_pointer::dealloc(t);\n\
    \                    std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)),\
    \ std::move(value(t)) };\n                    return { merge(child0(t), child1(t)),\
    \ std::move(erased_entry) };\n                } else {\n                    return\
    \ { t, std::nullopt };\n                }\n            } else {\n            \
    \    auto [c1, erased] = erase_binary_search(child1(t), f, g);\n             \
    \   if (erased) {\n                    set_child1(t, c1);\n                  \
    \  size_type& pos = erased->first;\n                    pos += safe_size(child0(t))\
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
    \  static node_pointer reverse_all(node_pointer t) {\n            if (t) {\n \
    \               reversed(t) ^= true;\n                std::swap(child0(t), child1(t));\n\
    \            }\n            return t;\n        }\n        static node_pointer\
    \ reverse(node_pointer t, size_type l, size_type r) {\n            auto [tl, tm,\
    \ tr] = split(t, l, r);\n            return merge(tl, Derived::reverse_all(tm),\
    \ tr);\n        }\n\n        static std::vector<value_type> dump(node_pointer\
    \ t) {\n            std::vector<value_type> res;\n            res.reserve(safe_size(t));\n\
    \            auto rec = [&](auto rec, node_pointer t) -> void {\n            \
    \    if (not t) return;\n                node_type::push(t);\n               \
    \ rec(rec, child0(t));\n                res.push_back(value(t));\n           \
    \     rec(rec, child1(t));\n            };\n            rec(rec, t);\n       \
    \     return res;\n        }\n\n        // Find the first element that satisfies\
    \ the condition f : (value, index) -> { false, true }.\n        // Returns { optional(value),\
    \ position }\n        template <typename Predicate>\n        static std::pair<size_type,\
    \ std::optional<value_type>> binary_search(node_pointer t, const Predicate& f)\
    \ {\n            node_pointer res = empty_node();\n            int ng = -1, ok\
    \ = safe_size(t);\n            while (ok - ng > 1) {\n                node_type::push(t);\n\
    \                if (const int root = ng + safe_size(child0(t)) + 1; f(value(t),\
    \ root)) {\n                    res = t;\n                    ok = root, t = child0(t);\n\
    \                } else {\n                    ng = root, t = child1(t);\n   \
    \             }\n            }\n            if (not res) {\n                return\
    \ { ok, std::nullopt };\n            } else {\n                return { ok, value(res)\
    \ };\n            }\n        }\n\n        // for debug\n        static void check_heap(node_pointer\
    \ t) {\n            if (node_pointer lch = child0(t)) {\n                check_heap(lch);\n\
    \                assert(priority(t) >= priority(lch));\n            }\n      \
    \      if (node_pointer rch = child1(t)) {\n                check_heap(rch);\n\
    \                assert(priority(t) >= priority(rch));\n            }\n      \
    \  }\n\n        // comp(T t, U u) = (t < u)\n        template <typename U, typename\
    \ Compare = std::less<>>\n        static std::pair<size_type, std::optional<value_type>>\
    \ lower_bound(node_pointer t, const U& target, Compare comp) {\n            return\
    \ binary_search(t, [&](const value_type& v, int) { return not comp(v, target);\
    \ });\n        }\n        // comp(T u, U t) = (u < t)\n        template <typename\
    \ U, typename Compare = std::less<>>\n        static std::pair<size_type, std::optional<value_type>>\
    \ upper_bound(node_pointer t, const U& target, Compare comp) {\n            return\
    \ binary_search(t, [&](const value_type& v, int) { return comp(target, v); });\n\
    \        }\n\n        template <bool reversed_, bool constant_>\n        struct\
    \ NodeIterator {\n            static constexpr bool constant = constant_;\n  \
    \          static constexpr bool reversed = reversed_;\n\n            using difference_type\
    \ = ReversibleNode::difference_type;\n            using value_type = ReversibleNode::value_type;\n\
    \            using pointer = std::conditional_t<constant, ReversibleNode::const_pointer,\
    \ ReversibleNode::pointer>;\n            using reference = std::conditional_t<constant,\
    \ ReversibleNode::const_reference, ReversibleNode::reference>;\n            using\
    \ iterator_cateogory = std::random_access_iterator_tag;\n\n            NodeIterator():\
    \ root(empty_node()), index(0) {}\n\n            reference operator*() {\n   \
    \             if (stk.empty() and index != safe_size(root)) down(root, index,\
    \ not reversed);\n                return value(stk.back());\n            }\n \
    \           reference operator[](difference_type k) const { return *((*this) +\
    \ k); }\n\n            NodeIterator& operator++() { return *this += 1; }\n   \
    \         NodeIterator& operator--() { return *this -= 1; }\n            NodeIterator&\
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
    \          node_pointer root;\n            size_type index;\n            std::vector<node_pointer>\
    \ stk;\n\n            NodeIterator(node_pointer root, size_type index): root(root),\
    \ index(index) {}\n\n            void up(const bool positive) {\n            \
    \    node_pointer t = stk.back();\n                while (true) {\n          \
    \          stk.pop_back();\n                    if (t == child(stk.back(), not\
    \ positive)) return;\n                    t = stk.back();\n                }\n\
    \            }\n            void down(node_pointer t, size_type k, const bool\
    \ positive) {\n                while (true) {\n                    node_type::push(t);\n\
    \                    stk.push_back(t);\n\n                    if (size_type siz\
    \ = safe_size(child(t, not positive)); k == siz) {\n                        break;\n\
    \                    } else if (k < siz) {\n                        t = child(t,\
    \ not positive);\n                    } else {\n                        k -= siz\
    \ + 1;\n                        t = child(t, positive);\n                    }\n\
    \                }\n            }\n            void suc(difference_type k) {\n\
    \                index += k;\n                if (index == safe_size(root)) stk.clear();\n\
    \                if (stk.empty()) return;\n\n                const bool positive\
    \ = k < 0 ? (k = -k, reversed) : not reversed;\n                while (k) {\n\
    \                    node_pointer t = child(stk.back(), positive);\n         \
    \           if (difference_type siz = safe_size(t); k > siz) {\n             \
    \           up(positive);\n                        k -= siz + 1;\n           \
    \         } else {\n                        down(t, k - 1, positive);\n      \
    \                  break;\n                    }\n                }\n        \
    \    }\n        };\n        using iterator = NodeIterator<false, false>;\n   \
    \     using reverse_iterator = NodeIterator<true, false>;\n        using const_iterator\
    \ = NodeIterator<false, true>;\n        using const_reverse_iterator = NodeIterator<true,\
    \ true>;\n\n        static iterator begin(node_pointer t) { return iterator::begin(t);\
    \ }\n        static iterator end(node_pointer t) { return iterator::end(t); }\n\
    \        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t);\
    \ }\n        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t);\
    \ }\n        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t);\
    \ }\n        static const_iterator cend(node_pointer t) { return const_iterator::end(t);\
    \ }\n        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t);\
    \ }\n        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t);\
    \ }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n#endif // SUISEN_IMPLICIT_TREAP_ERVERSIBLE_BASE\n"
  dependsOn:
  - library/util/pointer_32bit.hpp
  isVerificationFile: false
  path: library/datastructure/bbst/reversible_implicit_treap_base.hpp
  requiredBy:
  - library/datastructure/bbst/reversible_implicit_treap_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap.hpp
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
documentation_of: library/datastructure/bbst/reversible_implicit_treap_base.hpp
layout: document
redirect_from:
- /library/library/datastructure/bbst/reversible_implicit_treap_base.hpp
- /library/library/datastructure/bbst/reversible_implicit_treap_base.hpp.html
title: library/datastructure/bbst/reversible_implicit_treap_base.hpp
---
