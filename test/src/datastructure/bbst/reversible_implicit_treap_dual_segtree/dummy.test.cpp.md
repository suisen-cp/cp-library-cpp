---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_base.hpp
    title: Reversible Implicit Treap Base
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
    title: Reversible Implicit Treap Dual Segtree
  - icon: ':heavy_check_mark:'
    path: library/debug/warning.hpp
    title: Warning
  - icon: ':heavy_check_mark:'
    path: library/type_traits/operator.hpp
    title: Operator
  - icon: ':heavy_check_mark:'
    path: library/util/pointer_32bit.hpp
    title: Pointer 32bit
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
  bundledCode: "#line 1 \"test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#line 1 \"library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n\n\n\n#line 5 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <optional>\n\
    #include <string>\n#include <random>\n#include <tuple>\n#line 13 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n#include <utility>\n\n#line 1 \"library/util/pointer_32bit.hpp\"\n\n\n\n#line\
    \ 5 \"library/util/pointer_32bit.hpp\"\n\nnamespace suisen {\n    template <typename\
    \ Object>\n    struct ptr32 {\n        static constexpr int null = -1;\n\n   \
    \     using object_type = Object;\n        using pool_type = std::vector<object_type>;\n\
    \n        constexpr ptr32() : ptr(null) {}\n        explicit constexpr ptr32(int\
    \ ptr) : ptr(ptr) {}\n        constexpr ptr32(std::nullptr_t) : ptr(null) {}\n\
    \n        object_type& operator*() const { return pool[ptr]; }\n        object_type*\
    \ operator->() const { return &pool[ptr]; }\n\n        constexpr operator bool()\
    \ const { return ptr != null; }\n        constexpr operator int() const { return\
    \ ptr; }\n\n        constexpr bool is_not_null() const { return bool(*this); }\n\
    \        constexpr bool is_null() const { return not bool(*this); }\n\n      \
    \  friend constexpr bool operator==(const ptr32& l, const ptr32& r) { return l.ptr\
    \ == r.ptr; }\n        friend constexpr bool operator!=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr != r.ptr; }\n        friend constexpr bool operator<(const\
    \ ptr32& l, const ptr32& r) { return l.ptr < r.ptr; }\n        friend constexpr\
    \ bool operator<=(const ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }\n\
    \        friend constexpr bool operator>(const ptr32& l, const ptr32& r) { return\
    \ l.ptr > r.ptr; }\n        friend constexpr bool operator>=(const ptr32& l, const\
    \ ptr32& r) { return l.ptr >= r.ptr; }\n\n        template <typename ...Args>\n\
    \        static ptr32 alloc(Args &&...args) {\n            if (del.size()) {\n\
    \                ptr32 ptr(del.back());\n                del.pop_back();\n   \
    \             *ptr = object_type(std::forward<Args>(args)...);\n             \
    \   return ptr;\n            } else {\n                ptr32 ptr(pool.size());\n\
    \                pool.emplace_back(std::forward<Args>(args)...);\n           \
    \     return ptr;\n            }\n        }\n        static void dealloc(ptr32\
    \ p) {\n            del.push_back(p);\n        }\n        static void dealloc_all(bool\
    \ shrink) {\n            pool.clear(), del.clear();\n            if (shrink) pool.shrink_to_fit(),\
    \ del.shrink_to_fit();\n        }\n        static void reserve(std::size_t capacity)\
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
    \ }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n\n#line 1 \"\
    library/type_traits/operator.hpp\"\n\n\n\n#include <type_traits>\n\nnamespace\
    \ suisen {\n#define HAS_BINARY_OPERATOR(op, op_name) \\\n    namespace internal::type_traits\
    \ { \\\n        template <typename LHS, typename RHS> \\\n        struct impl_has_operator_##op_name\
    \ { \\\n            template <typename LHS2, typename RHS2> \\\n            static\
    \ auto test(LHS2*) -> decltype(std::declval<LHS2>() op std::declval<RHS2>());\
    \ \\\n            template <typename, typename> \\\n            static auto test(...)\
    \ -> std::false_type; \\\n            using type = typename std::negation<std::is_same<std::false_type,\
    \ decltype(test<LHS, RHS>(nullptr))>>::type; \\\n        }; \\\n    } \\\n   \
    \ template <typename LHS, typename RHS = LHS> \\\n    struct has_operator_##op_name:\
    \ internal::type_traits::impl_has_operator_##op_name<LHS, RHS>::type {}; \\\n\
    \    template <typename LHS, typename RHS = LHS> \\\n    constexpr bool has_operator_##op_name##_v\
    \ = has_operator_##op_name<LHS, RHS>::value;\n\n#define HAS_UNARY_OPERATOR(op,\
    \ op_name) \\\n    namespace internal::type_traits { \\\n        template <typename\
    \ T> \\\n        struct impl_has_operator_##op_name { \\\n            template\
    \ <typename U> \\\n            static auto test(U*) -> decltype(op std::declval<U>());\
    \ \\\n            template <typename> \\\n            static auto test(...) ->\
    \ std::false_type; \\\n            using type = typename std::negation<std::is_same<std::false_type,\
    \ decltype(test<T>(nullptr))>>::type; \\\n        }; \\\n    } \\\n    template\
    \ <typename T> \\\n    struct has_operator_##op_name: internal::type_traits::impl_has_operator_##op_name<T>::type\
    \ {}; \\\n    template <typename T> \\\n    constexpr bool has_operator_##op_name##_v\
    \ = has_operator_##op_name<T>::value;\n\n    HAS_UNARY_OPERATOR(-, negate)\n \
    \   HAS_BINARY_OPERATOR(+, plus)\n    HAS_BINARY_OPERATOR(-, minus)\n    HAS_BINARY_OPERATOR(*,\
    \ multiplies)\n    HAS_BINARY_OPERATOR(/ , divides)\n    HAS_BINARY_OPERATOR(%,\
    \ modulus)\n\n    HAS_UNARY_OPERATOR(~, bit_not)\n    HAS_BINARY_OPERATOR(&, bit_and)\n\
    \    HAS_BINARY_OPERATOR(| , bit_or)\n    HAS_BINARY_OPERATOR(^, bit_xor)\n\n\
    \    HAS_UNARY_OPERATOR(!, logical_not)\n    HAS_BINARY_OPERATOR(&&, logical_and)\n\
    \    HAS_BINARY_OPERATOR(|| , logical_or)\n\n    HAS_BINARY_OPERATOR(==, equal_to)\n\
    \    HAS_BINARY_OPERATOR(!=, not_equal_to)\n    HAS_BINARY_OPERATOR(<, less)\n\
    \    HAS_BINARY_OPERATOR(<=, less_equal)\n    HAS_BINARY_OPERATOR(>, greater)\n\
    \    HAS_BINARY_OPERATOR(>=, greater_equal)\n\n#undef HAS_UNARY_OPERATOR\n#undef\
    \ HAS_BINARY_OPERATOR\n} // namespace suisen\n\n\n#line 1 \"library/debug/warning.hpp\"\
    \n\n\n\n#line 5 \"library/debug/warning.hpp\"\n\nnamespace suisen {\n    struct\
    \ warning {\n        warning(const std::string &msg) {\n            std::cerr\
    \ << \"\\033[33m[WARNING] \" << msg << \"\\033[0m\" << std::endl;\n        }\n\
    \    };\n} // namespace suisen\n\n\n#line 7 \"library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n\
    \        struct ReversibleRangeOperateNode: ReversibleNode<T, ReversibleRangeOperateNode<T,\
    \ F, mapping, composition, id>> {\n            using base = ReversibleNode<T,\
    \ ReversibleRangeOperateNode<T, F, mapping, composition, id>>;\n            using\
    \ node_pointer = typename base::node_pointer;\n            using value_type =\
    \ typename base::value_type;\n            using operator_type = F;\n\n       \
    \     operator_type _laz;\n            ReversibleRangeOperateNode(const value_type&\
    \ val): base(val), _laz(id()) {}\n\n            // ----- override ----- //\n \
    \           static void push(node_pointer t) {\n                base::push(t);\n\
    \                operator_type& laz = lazy(t);\n                if constexpr (has_operator_equal_to<operator_type>::value)\
    \ {\n                    if (not (laz == id())) {\n                        operator_type&\
    \ laz = lazy(t);\n                        apply_all(base::child0(t), laz);\n \
    \                       apply_all(base::child1(t), laz);\n                   \
    \     laz = id();\n                    }\n                } else {\n         \
    \           static warning warning_(\"operator==(F, F) is not defined, so the\
    \ performance maybe worse.\");\n                    apply_all(base::child0(t),\
    \ laz);\n                    apply_all(base::child1(t), laz);\n              \
    \      laz = id();\n                }\n            }\n\n            // ----- new\
    \ features ----- //\n            static operator_type& lazy(node_pointer t) {\n\
    \                return t->_laz;\n            }\n            static node_pointer\
    \ apply_all(node_pointer t, const operator_type& f) {\n                if (t)\
    \ {\n                    operator_type& laz = lazy(t);\n                    laz\
    \ = composition(f, laz);\n                    value_type& val = base::value(t);\n\
    \                    val = mapping(f, val);\n                }\n             \
    \   return t;\n            }\n            static node_pointer apply(node_pointer\
    \ t, size_t l, size_t r, const operator_type& f) {\n                auto [tl,\
    \ tm, tr] = base::split(t, l, r);\n                return base::merge(tl, apply_all(tm,\
    \ f), tr);\n            }\n        };\n    }\n\n    template <typename T, typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    class ReversibleDynamicDualSegmentTree\
    \ {\n        using node_type = internal::implicit_treap::ReversibleRangeOperateNode<T,\
    \ F, mapping, composition, id>;\n        using node_pointer = typename node_type::node_pointer;\n\
    \n        node_pointer _root;\n\n        struct node_pointer_construct {};\n \
    \       ReversibleDynamicDualSegmentTree(node_pointer root, node_pointer_construct):\
    \ _root(root) {}\n\n    public:\n        using value_type = typename node_type::value_type;\n\
    \        using operator_type = typename node_type::operator_type;\n\n        ReversibleDynamicDualSegmentTree():\
    \ _root(node_type::empty_node()) {}\n        explicit ReversibleDynamicDualSegmentTree(size_t\
    \ n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value))\
    \ {}\n        template <typename U>\n        ReversibleDynamicDualSegmentTree(const\
    \ std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n\
    \        void free() {\n            node_type::delete_tree(_root);\n         \
    \   _root = node_type::empty_node();\n        }\n        void clear() { free();\
    \ }\n\n        static void reserve(size_t capacity) { node_type::reserve(capacity);\
    \ }\n\n        bool empty() const { return node_type::empty(_root); }\n      \
    \  int size() const { return node_type::safe_size(_root); }\n\n        value_type&\
    \ operator[](size_t k) {\n            assert(k < size_t(size()));\n          \
    \  return node_type::get(_root, k);\n        }\n        const value_type& operator[](size_t\
    \ k) const {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        value_type& front() { return (*this)[0]; }\n       \
    \ value_type& back() { return (*this)[size() - 1]; }\n        const value_type&\
    \ front() const { return (*this)[0]; }\n        const value_type& back() const\
    \ { return (*this)[size() - 1]; }\n\n        void apply_all(const operator_type&\
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
    \   }\n\n        // Split immediately before the k-th element.\n        ReversibleDynamicDualSegmentTree\
    \ split(size_t k) {\n            assert(k <= size_t(size()));\n            node_pointer\
    \ root_r;\n            std::tie(_root, root_r) = node_type::split(_root, k);\n\
    \            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        // Split immediately before the first element that satisfies\
    \ the condition.\n        // Requirements: f(A[i]) must be monotonic\n       \
    \ template <typename Predicate>\n        ReversibleDynamicDualSegmentTree split_binary_search(const\
    \ Predicate &f) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_binary_search(_root, f);\n            return ReversibleDynamicDualSegmentTree(root_r,\
    \ node_pointer_construct{});\n        }\n        // Split immediately before the\
    \ first element that is greater than or equal to val.\n        // Requirements:\
    \ sequence is sorted\n        template <typename Compare = std::less<>>\n    \
    \    ReversibleDynamicDualSegmentTree split_lower_bound(const value_type &val,\
    \ const Compare &comp = {}) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_lower_bound(_root, val, comp);\n            return\
    \ ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});\n      \
    \  }\n        // Split immediately before the first element that is greater than\
    \ val.\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        ReversibleDynamicDualSegmentTree split_upper_bound(const\
    \ value_type &val, const Compare &comp = {}) {\n            node_pointer root_r;\n\
    \            std::tie(_root, root_r) = node_type::split_upper_bound(_root, val,\
    \ comp);\n            return ReversibleDynamicDualSegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n\n        void merge(ReversibleDynamicDualSegmentTree r) { _root =\
    \ node_type::merge(_root, r._root); }\n\n        void rotate(size_t k) {\n   \
    \         assert(k <= size_t(size()));\n            _root = node_type::rotate(_root,\
    \ k);\n        }\n        void rotate(size_t l, size_t m, size_t r) {\n      \
    \      assert(l <= m and m <= r and r <= size_t(size()));\n            _root =\
    \ node_type::rotate(_root, l, m, r);\n        }\n\n        void reverse(size_t\
    \ l, size_t r) {\n            assert(l <= r and r <= size_t(size()));\n      \
    \      if (r - l >= 2) _root = node_type::reverse(_root, l, r);\n        }\n \
    \       void reverse_all() { _root = node_type::reverse_all(_root); }\n\n    \
    \    std::vector<value_type> dump() const { return node_type::dump(_root); }\n\
    \n        // Find the first element that satisfies the condition f.\n        //\
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
    \ }\n\n        // handling internal nodes\n        using internal_node = node_type;\n\
    \        using internal_node_pointer = node_pointer;\n\n        internal_node_pointer&\
    \ root_node() { return _root; }\n        const internal_node_pointer& root_node()\
    \ const { return _root; }\n        void set_root_node(internal_node_pointer new_root)\
    \ { root_node() = new_root; }\n    };\n} // namespace suisen\n\n\n\n#line 16 \"\
    test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp\"\
    \n\ntemplate <typename T, typename F, T(*mapping)(F, T)>\nstruct NaiveSolutionForDualSegmentTree\
    \ {\n    NaiveSolutionForDualSegmentTree() = default;\n    NaiveSolutionForDualSegmentTree(const\
    \ std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const\
    \ {\n        assert(0 <= i and i < _n);\n        return _dat[i];\n    }\n    void\
    \ set(int i, const T& val) {\n        assert(0 <= i and i < _n);\n        _dat[i]\
    \ = val;\n    }\n\n    void insert(int i, const T& val) {\n        assert(0 <=\
    \ i and i <= _n);\n        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n\
    \    }\n    void erase(int i) {\n        assert(0 <= i and i < _n);\n        --_n;\n\
    \        _dat.erase(_dat.begin() + i);\n    }\n\n    void apply_all(const F &f)\
    \ {\n        apply(0, _n, f);\n    }\n    void apply(int l, int r, const F &f)\
    \ {\n        assert(0 <= l and l <= r and r <= _n);\n        for (int i = l; i\
    \ < r; ++i) _dat[i] = mapping(f, _dat[i]);\n    }\n\n    void reverse_all() {\n\
    \        reverse(0, _n);\n    }\n    void reverse(int l, int r) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (--r; l < r; ++l, --r) {\n      \
    \      std::swap(_dat[l], _dat[r]);\n        }\n    }\n\n    void rotate(int i)\
    \ {\n        assert(0 <= i and i <= _n);\n        std::rotate(_dat.begin(), _dat.begin()\
    \ + i, _dat.end());\n    }\n\n    std::vector<T> dump() { return _dat; }\nprivate:\n\
    \    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Range Update Point Get\n\
    \ */\n\nusing S = int;\n\nstruct F {\n    static constexpr int identity = std::numeric_limits<int>::max();\n\
    \n    int val;\n    F() : val(identity) {}\n    F(int val) : val(val) {}\n};\n\
    \nS mapping(F f, S x) {\n    return f.val == F::identity ? x : f.val;\n}\nF composition(F\
    \ f, F g) {\n    return f.val == F::identity ? g : f.val;\n}\nF id() {\n    return\
    \ F{};\n}\n\nusing Tree = suisen::ReversibleDynamicDualSegmentTree<S, F, mapping,\
    \ composition, id>;\nusing Naive = NaiveSolutionForDualSegmentTree<S, F, mapping>;\n\
    \n#line 100 \"test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp\"\
    \n\nconstexpr int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_insert\
    \ = 2;\nconstexpr int Q_erase = 3;\nconstexpr int Q_rotate = 8;\nconstexpr int\
    \ Q_apply = 4;\nconstexpr int Q_apply_all = 5;\nconstexpr int Q_reverse = 6;\n\
    constexpr int Q_reverse_all = 7;\nconstexpr int QueryTypeNum = 9;\n\nvoid test()\
    \ {\n    int N = 3000, Q = 3000, MAX_VAL = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\
    \n    std::vector<S> init(N);\n    for (int i = 0; i < N; ++i) init[i] = rng()\
    \ % MAX_VAL;\n    \n    Tree t1(init);\n    Naive t2(init);\n\n    for (int i\
    \ = 0; i < Q; ++i) {\n        const int query_type = rng() % QueryTypeNum;\n \
    \       if (query_type == Q_get) {\n            const int i = rng() % N;\n   \
    \         assert(t1[i] == t2.get(i));\n        } else if (query_type == Q_set)\
    \ {\n            const int i = rng() % N;\n            const S v = rng() % MAX_VAL;\n\
    \            t1[i] = v;\n            t2.set(i, v);\n        } else if (query_type\
    \ == Q_insert) {\n            const int i = rng() % (N + 1);\n            const\
    \ S v = rng() % MAX_VAL;\n            t1.insert(i, v);\n            t2.insert(i,\
    \ v);\n            ++N;\n        } else if (query_type == Q_erase) {\n       \
    \     const int i = rng() % N;\n            t1.erase(i);\n            t2.erase(i);\n\
    \            --N;\n        } else if (query_type == Q_rotate) {\n            const\
    \ int i = rng() % (N + 1);\n            t1.rotate(i);\n            t2.rotate(i);\n\
    \        } else if (query_type == Q_apply) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ const int f = rng() % MAX_VAL;\n            t1.apply(l, r, f);\n           \
    \ t2.apply(l, r, f);\n        } else if (query_type == Q_apply_all) {\n      \
    \      const int f = rng() % MAX_VAL;\n            t1.apply_all(f);\n        \
    \    t2.apply_all(f);\n        } else if (query_type == Q_reverse) {\n       \
    \     const int l = rng() % (N + 1);\n            const int r = l + rng() % (N\
    \ - l + 1);\n            t1.reverse(l, r);\n            t2.reverse(l, r);\n  \
    \      } else if (query_type == Q_reverse_all) {\n            t1.reverse_all();\n\
    \            t2.reverse_all();\n        } else {\n            assert(false);\n\
    \        }\n    }\n}\n\nvoid test2() {\n    std::mt19937 rng{ std::random_device{}()\
    \ };\n    Tree seq;\n    const int n = 300, k = 20;\n\n    std::vector<int> q(n\
    \ * k);\n    for (int i = 0; i < n * k; ++i) {\n        q[i] = i % n;\n    }\n\
    \    std::shuffle(q.begin(), q.end(), rng);\n\n    for (int v : q) {\n       \
    \ if (rng() % 2) {\n            int k = seq.insert_lower_bound(v);\n         \
    \   assert(k == 0 or seq[k - 1] < v);\n            assert(k == seq.size() - 1\
    \ or seq[k + 1] >= v);\n        } else {\n            int k = seq.insert_upper_bound(v);\n\
    \            assert(k == 0 or seq[k - 1] <= v);\n            assert(k == seq.size()\
    \ - 1 or seq[k + 1] > v);\n        }\n    }\n\n    for (int v : q) {\n       \
    \ int k = seq.erase_if_exists(v)->first;\n        assert(k == 0 or seq[k - 1]\
    \ < v);\n        assert(k == seq.size() or seq[k] >= v);\n    }\n\n    std::vector<int>\
    \ sorted = q;\n    std::sort(sorted.begin(), sorted.end());\n\n    seq = sorted;\n\
    \n    assert(std::equal(sorted.begin(), sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(),\
    \ sorted.rend(), seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n  \
    \      assert(seq.begin()[i] == i / k);\n    }\n\n    {\n        auto it = seq.begin();\n\
    \        for (int q = 0; q < 100000; ++q) {\n            int a = rng() % (n *\
    \ k + 1);\n            auto it2 = seq.begin() + a;\n            it += it2 - it;\n\
    \            if (a < n * k) {\n                assert(*it == a / k);\n       \
    \     }\n        }\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int\
    \ a = rng() % (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int\
    \ d = b - a;\n        assert((seq.begin() + a) + d == seq.begin() + b);\n    \
    \    assert(seq.begin() + a == (seq.begin() + b) - d);\n\n        auto it1 = seq.begin()\
    \ + a;\n        auto it2 = seq.begin() + b;\n\n        if (d > 0) {\n        \
    \    assert(not (it1 == it2));\n            assert(it1 != it2);\n            assert(not\
    \ (it1 > it2));\n            assert(not (it1 >= it2));\n            assert(it1\
    \ < it2);\n            assert(it1 <= it2);\n        } else if (d < 0) {\n    \
    \        assert(not (it1 == it2));\n            assert(it1 != it2);\n        \
    \    assert(not (it1 < it2));\n            assert(not (it1 <= it2));\n       \
    \     assert(it1 > it2);\n            assert(it1 >= it2);\n        } else {\n\
    \            assert(not (it1 != it2));\n            assert(it1 == it2);\n    \
    \        assert(not (it1 > it2));\n            assert(not (it1 < it2));\n    \
    \        assert(it1 <= it2);\n            assert(it1 >= it2);\n        }\n\n \
    \       if (a != n * k and b != n * k) {\n            assert(*it1 == a / k);\n\
    \            assert(*it2 == b / k);\n\n            it1 += d;\n\n            assert(not\
    \ (it1 != it2));\n            assert(it1 == it2);\n            assert(not (it1\
    \ < it2));\n            assert(not (it1 > it2));\n            assert(it1 <= it2);\n\
    \            assert(it1 >= it2);\n            assert(*it1 == *it2);\n        }\n\
    \    }\n\n    std::vector<int> naive = sorted;\n    assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n\n    for (int q = 0; q < 500; ++q) {\n       \
    \ if (rng() % 2) {\n            int l = rng() % (n * k + 1);\n            int\
    \ r = rng() % (n * k + 1);\n            if (l > r) std::swap(l, r);\n        \
    \    seq.reverse(l, r);\n            std::reverse(naive.begin() + l, naive.begin()\
    \ + r);\n        } else {\n            assert(naive == seq.dump());\n        \
    \    assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n          \
    \  assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));\n        }\n\
    \    }\n\n    for (int& e : seq) --e;\n    for (int& e : naive) --e;\n    assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n    assert(std::equal(naive.rbegin(), naive.rend(),\
    \ seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const Tree&>(seq);\n\
    \    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n    assert(std::equal(naive.rbegin(),\
    \ naive.rend(), const_seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n\
    \        assert(const_seq[i] == naive[i]);\n    }\n}\n\n\nint main() {\n    test();\n\
    \    test2();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#include \"library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp\"\
    \n\ntemplate <typename T, typename F, T(*mapping)(F, T)>\nstruct NaiveSolutionForDualSegmentTree\
    \ {\n    NaiveSolutionForDualSegmentTree() = default;\n    NaiveSolutionForDualSegmentTree(const\
    \ std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const\
    \ {\n        assert(0 <= i and i < _n);\n        return _dat[i];\n    }\n    void\
    \ set(int i, const T& val) {\n        assert(0 <= i and i < _n);\n        _dat[i]\
    \ = val;\n    }\n\n    void insert(int i, const T& val) {\n        assert(0 <=\
    \ i and i <= _n);\n        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n\
    \    }\n    void erase(int i) {\n        assert(0 <= i and i < _n);\n        --_n;\n\
    \        _dat.erase(_dat.begin() + i);\n    }\n\n    void apply_all(const F &f)\
    \ {\n        apply(0, _n, f);\n    }\n    void apply(int l, int r, const F &f)\
    \ {\n        assert(0 <= l and l <= r and r <= _n);\n        for (int i = l; i\
    \ < r; ++i) _dat[i] = mapping(f, _dat[i]);\n    }\n\n    void reverse_all() {\n\
    \        reverse(0, _n);\n    }\n    void reverse(int l, int r) {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        for (--r; l < r; ++l, --r) {\n      \
    \      std::swap(_dat[l], _dat[r]);\n        }\n    }\n\n    void rotate(int i)\
    \ {\n        assert(0 <= i and i <= _n);\n        std::rotate(_dat.begin(), _dat.begin()\
    \ + i, _dat.end());\n    }\n\n    std::vector<T> dump() { return _dat; }\nprivate:\n\
    \    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Range Update Point Get\n\
    \ */\n\nusing S = int;\n\nstruct F {\n    static constexpr int identity = std::numeric_limits<int>::max();\n\
    \n    int val;\n    F() : val(identity) {}\n    F(int val) : val(val) {}\n};\n\
    \nS mapping(F f, S x) {\n    return f.val == F::identity ? x : f.val;\n}\nF composition(F\
    \ f, F g) {\n    return f.val == F::identity ? g : f.val;\n}\nF id() {\n    return\
    \ F{};\n}\n\nusing Tree = suisen::ReversibleDynamicDualSegmentTree<S, F, mapping,\
    \ composition, id>;\nusing Naive = NaiveSolutionForDualSegmentTree<S, F, mapping>;\n\
    \n#include <random>\n#include <algorithm>\n\nconstexpr int Q_get = 0;\nconstexpr\
    \ int Q_set = 1;\nconstexpr int Q_insert = 2;\nconstexpr int Q_erase = 3;\nconstexpr\
    \ int Q_rotate = 8;\nconstexpr int Q_apply = 4;\nconstexpr int Q_apply_all = 5;\n\
    constexpr int Q_reverse = 6;\nconstexpr int Q_reverse_all = 7;\nconstexpr int\
    \ QueryTypeNum = 9;\n\nvoid test() {\n    int N = 3000, Q = 3000, MAX_VAL = 1000000000;\n\
    \n    std::mt19937 rng{std::random_device{}()};\n\n    std::vector<S> init(N);\n\
    \    for (int i = 0; i < N; ++i) init[i] = rng() % MAX_VAL;\n    \n    Tree t1(init);\n\
    \    Naive t2(init);\n\n    for (int i = 0; i < Q; ++i) {\n        const int query_type\
    \ = rng() % QueryTypeNum;\n        if (query_type == Q_get) {\n            const\
    \ int i = rng() % N;\n            assert(t1[i] == t2.get(i));\n        } else\
    \ if (query_type == Q_set) {\n            const int i = rng() % N;\n         \
    \   const S v = rng() % MAX_VAL;\n            t1[i] = v;\n            t2.set(i,\
    \ v);\n        } else if (query_type == Q_insert) {\n            const int i =\
    \ rng() % (N + 1);\n            const S v = rng() % MAX_VAL;\n            t1.insert(i,\
    \ v);\n            t2.insert(i, v);\n            ++N;\n        } else if (query_type\
    \ == Q_erase) {\n            const int i = rng() % N;\n            t1.erase(i);\n\
    \            t2.erase(i);\n            --N;\n        } else if (query_type ==\
    \ Q_rotate) {\n            const int i = rng() % (N + 1);\n            t1.rotate(i);\n\
    \            t2.rotate(i);\n        } else if (query_type == Q_apply) {\n    \
    \        const int l = rng() % (N + 1);\n            const int r = l + rng() %\
    \ (N - l + 1);\n            const int f = rng() % MAX_VAL;\n            t1.apply(l,\
    \ r, f);\n            t2.apply(l, r, f);\n        } else if (query_type == Q_apply_all)\
    \ {\n            const int f = rng() % MAX_VAL;\n            t1.apply_all(f);\n\
    \            t2.apply_all(f);\n        } else if (query_type == Q_reverse) {\n\
    \            const int l = rng() % (N + 1);\n            const int r = l + rng()\
    \ % (N - l + 1);\n            t1.reverse(l, r);\n            t2.reverse(l, r);\n\
    \        } else if (query_type == Q_reverse_all) {\n            t1.reverse_all();\n\
    \            t2.reverse_all();\n        } else {\n            assert(false);\n\
    \        }\n    }\n}\n\nvoid test2() {\n    std::mt19937 rng{ std::random_device{}()\
    \ };\n    Tree seq;\n    const int n = 300, k = 20;\n\n    std::vector<int> q(n\
    \ * k);\n    for (int i = 0; i < n * k; ++i) {\n        q[i] = i % n;\n    }\n\
    \    std::shuffle(q.begin(), q.end(), rng);\n\n    for (int v : q) {\n       \
    \ if (rng() % 2) {\n            int k = seq.insert_lower_bound(v);\n         \
    \   assert(k == 0 or seq[k - 1] < v);\n            assert(k == seq.size() - 1\
    \ or seq[k + 1] >= v);\n        } else {\n            int k = seq.insert_upper_bound(v);\n\
    \            assert(k == 0 or seq[k - 1] <= v);\n            assert(k == seq.size()\
    \ - 1 or seq[k + 1] > v);\n        }\n    }\n\n    for (int v : q) {\n       \
    \ int k = seq.erase_if_exists(v)->first;\n        assert(k == 0 or seq[k - 1]\
    \ < v);\n        assert(k == seq.size() or seq[k] >= v);\n    }\n\n    std::vector<int>\
    \ sorted = q;\n    std::sort(sorted.begin(), sorted.end());\n\n    seq = sorted;\n\
    \n    assert(std::equal(sorted.begin(), sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(),\
    \ sorted.rend(), seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n  \
    \      assert(seq.begin()[i] == i / k);\n    }\n\n    {\n        auto it = seq.begin();\n\
    \        for (int q = 0; q < 100000; ++q) {\n            int a = rng() % (n *\
    \ k + 1);\n            auto it2 = seq.begin() + a;\n            it += it2 - it;\n\
    \            if (a < n * k) {\n                assert(*it == a / k);\n       \
    \     }\n        }\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int\
    \ a = rng() % (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int\
    \ d = b - a;\n        assert((seq.begin() + a) + d == seq.begin() + b);\n    \
    \    assert(seq.begin() + a == (seq.begin() + b) - d);\n\n        auto it1 = seq.begin()\
    \ + a;\n        auto it2 = seq.begin() + b;\n\n        if (d > 0) {\n        \
    \    assert(not (it1 == it2));\n            assert(it1 != it2);\n            assert(not\
    \ (it1 > it2));\n            assert(not (it1 >= it2));\n            assert(it1\
    \ < it2);\n            assert(it1 <= it2);\n        } else if (d < 0) {\n    \
    \        assert(not (it1 == it2));\n            assert(it1 != it2);\n        \
    \    assert(not (it1 < it2));\n            assert(not (it1 <= it2));\n       \
    \     assert(it1 > it2);\n            assert(it1 >= it2);\n        } else {\n\
    \            assert(not (it1 != it2));\n            assert(it1 == it2);\n    \
    \        assert(not (it1 > it2));\n            assert(not (it1 < it2));\n    \
    \        assert(it1 <= it2);\n            assert(it1 >= it2);\n        }\n\n \
    \       if (a != n * k and b != n * k) {\n            assert(*it1 == a / k);\n\
    \            assert(*it2 == b / k);\n\n            it1 += d;\n\n            assert(not\
    \ (it1 != it2));\n            assert(it1 == it2);\n            assert(not (it1\
    \ < it2));\n            assert(not (it1 > it2));\n            assert(it1 <= it2);\n\
    \            assert(it1 >= it2);\n            assert(*it1 == *it2);\n        }\n\
    \    }\n\n    std::vector<int> naive = sorted;\n    assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n\n    for (int q = 0; q < 500; ++q) {\n       \
    \ if (rng() % 2) {\n            int l = rng() % (n * k + 1);\n            int\
    \ r = rng() % (n * k + 1);\n            if (l > r) std::swap(l, r);\n        \
    \    seq.reverse(l, r);\n            std::reverse(naive.begin() + l, naive.begin()\
    \ + r);\n        } else {\n            assert(naive == seq.dump());\n        \
    \    assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n          \
    \  assert(std::equal(naive.rbegin(), naive.rend(), seq.rbegin()));\n        }\n\
    \    }\n\n    for (int& e : seq) --e;\n    for (int& e : naive) --e;\n    assert(std::equal(naive.begin(),\
    \ naive.end(), seq.begin()));\n    assert(std::equal(naive.rbegin(), naive.rend(),\
    \ seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const Tree&>(seq);\n\
    \    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n    assert(std::equal(naive.rbegin(),\
    \ naive.rend(), const_seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n\
    \        assert(const_seq[i] == naive[i]);\n    }\n}\n\n\nint main() {\n    test();\n\
    \    test2();\n    std::cout << \"Hello World\" << std::endl;\n    return 0;\n\
    }"
  dependsOn:
  - library/datastructure/bbst/reversible_implicit_treap_dual_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_base.hpp
  - library/util/pointer_32bit.hpp
  - library/type_traits/operator.hpp
  - library/debug/warning.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-05-13 02:46:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
- /verify/test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp.html
title: test/src/datastructure/bbst/reversible_implicit_treap_dual_segtree/dummy.test.cpp
---