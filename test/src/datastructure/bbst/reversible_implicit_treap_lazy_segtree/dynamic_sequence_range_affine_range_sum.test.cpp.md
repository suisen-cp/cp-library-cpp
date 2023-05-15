---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algebra/monoid/affine.hpp
    title: Affine
  - icon: ':question:'
    path: library/datastructure/bbst/reversible_implicit_treap_base.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_base.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
    title: library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  - icon: ':heavy_check_mark:'
    path: library/debug/warning.hpp
    title: library/debug/warning.hpp
  - icon: ':heavy_check_mark:'
    path: library/type_traits/operator.hpp
    title: library/type_traits/operator.hpp
  - icon: ':question:'
    path: library/util/pointer_32bit.hpp
    title: library/util/pointer_32bit.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/reversible_implicit_treap_base.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include\
    \ <cstdint>\n#include <optional>\n#include <string>\n#include <random>\n#include\
    \ <tuple>\n#include <vector>\n#include <utility>\n\n#line 1 \"library/util/pointer_32bit.hpp\"\
    \n\n\n\n#line 5 \"library/util/pointer_32bit.hpp\"\n\nnamespace suisen {\n   \
    \ template <typename Object>\n    struct ptr32 {\n        static constexpr int\
    \ null = -1;\n\n        using object_type = Object;\n        using pool_type =\
    \ std::vector<object_type>;\n\n        constexpr ptr32() : ptr(null) {}\n    \
    \    explicit constexpr ptr32(int ptr) : ptr(ptr) {}\n        constexpr ptr32(std::nullptr_t)\
    \ : ptr(null) {}\n\n        object_type& operator*() const { return pool[ptr];\
    \ }\n        object_type* operator->() const { return &pool[ptr]; }\n\n      \
    \  constexpr operator bool() const { return ptr != null; }\n        constexpr\
    \ operator int() const { return ptr; }\n\n        constexpr bool is_not_null()\
    \ const { return bool(*this); }\n        constexpr bool is_null() const { return\
    \ not bool(*this); }\n\n        friend constexpr bool operator==(const ptr32&\
    \ l, const ptr32& r) { return l.ptr == r.ptr; }\n        friend constexpr bool\
    \ operator!=(const ptr32& l, const ptr32& r) { return l.ptr != r.ptr; }\n    \
    \    friend constexpr bool operator<(const ptr32& l, const ptr32& r) { return\
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
    \ }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n\n#line 5 \"\
    library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp\"\n\n#line\
    \ 1 \"library/type_traits/operator.hpp\"\n\n\n\n#include <type_traits>\n\nnamespace\
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
    \    };\n} // namespace suisen\n\n\n#line 8 \"library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F,\
    \ T, int), F(*composition)(F, F), F(*id)()>\n        struct ReversibleRangeOperateRangeProductNode:\
    \ ReversibleNode<T, ReversibleRangeOperateRangeProductNode<T, op, e, toggle, F,\
    \ mapping, composition, id>> {\n            using base = ReversibleNode<T, ReversibleRangeOperateRangeProductNode<T,\
    \ op, e, toggle, F, mapping, composition, id>>;\n            using node_pointer\
    \ = typename base::node_pointer;\n            using value_type = typename base::value_type;\n\
    \            using operator_type = F;\n\n            value_type _sum;\n      \
    \      operator_type _laz;\n            ReversibleRangeOperateRangeProductNode(const\
    \ value_type& val): base(val), _sum(val), _laz(id()) {}\n\n            // -----\
    \ override ----- //\n            static node_pointer update(node_pointer t) {\n\
    \                base::update(t);\n                prod_all(t) = op(op(safe_prod(base::child0(t)),\
    \ base::value(t)), safe_prod(base::child1(t)));\n                return t;\n \
    \           }\n            static void push(node_pointer t) {\n              \
    \  base::push(t);\n                operator_type& laz = lazy(t);\n           \
    \     if constexpr (has_operator_equal_to<operator_type>::value) {\n         \
    \           if (not (laz == id())) {\n                        operator_type& laz\
    \ = lazy(t);\n                        apply_all(base::child0(t), laz);\n     \
    \                   apply_all(base::child1(t), laz);\n                       \
    \ laz = id();\n                    }\n                } else {\n             \
    \       static warning warning_(\"operator==(F, F) is not defined, so the performance\
    \ maybe worse.\");\n                    apply_all(base::child0(t), laz);\n   \
    \                 apply_all(base::child1(t), laz);\n                    laz =\
    \ id();\n                }\n            }\n            static node_pointer reverse_all(node_pointer\
    \ t) {\n                if (t) {\n                    base::reversed(t) ^= true;\n\
    \                    std::swap(base::child0(t), base::child1(t));\n          \
    \          value_type& sum = prod_all(t);\n                    sum = toggle(sum);\n\
    \                }\n                return t;\n            }\n\n            //\
    \ ----- new features ----- //\n            static value_type& prod_all(node_pointer\
    \ t) {\n                return t->_sum;\n            }\n            static value_type\
    \ safe_prod(node_pointer t) {\n                return t ? t->_sum : e();\n   \
    \         }\n            static std::pair<node_pointer, value_type> prod(node_pointer\
    \ t, size_t l, size_t r) {\n                auto [tl, tm, tr] = base::split(t,\
    \ l, r);\n                value_type res = safe_prod(tm);\n                return\
    \ { base::merge(tl, tm, tr), res };\n            }\n\n            static operator_type&\
    \ lazy(node_pointer t) {\n                return t->_laz;\n            }\n   \
    \         static node_pointer apply_all(node_pointer t, const operator_type& f)\
    \ {\n                if (t) {\n                    operator_type& laz = lazy(t);\n\
    \                    laz = composition(f, laz);\n                    value_type&\
    \ val = base::value(t);\n                    val = mapping(f, val, 1);\n     \
    \               value_type& sum = prod_all(t);\n                    sum = mapping(f,\
    \ sum, base::size(t));\n                }\n                return t;\n       \
    \     }\n            static node_pointer apply(node_pointer t, size_t l, size_t\
    \ r, const operator_type& f) {\n                auto [tl, tm, tr] = base::split(t,\
    \ l, r);\n                return base::merge(tl, apply_all(tm, f), tr);\n    \
    \        }\n\n            template <typename Func>\n            static node_pointer\
    \ set(node_pointer t, size_t k, const Func& f) {\n                return base::set_update(t,\
    \ k, f);\n            }\n\n            template <typename Predicate>\n       \
    \     static uint32_t max_right(node_pointer t, const Predicate& f) {\n      \
    \          value_type sum = e();\n                assert(f(sum));\n\n        \
    \        uint32_t r = 0;\n                while (t) {\n                    push(t);\n\
    \n                    node_pointer lch = base::child0(t);\n\n                \
    \    value_type nxt_sum = op(sum, safe_prod(lch));\n                    if (f(nxt_sum))\
    \ {\n                        r += base::safe_size(lch);\n                    \
    \    sum = op(nxt_sum, base::value(t));\n                        if (f(sum)) {\n\
    \                            ++r;\n                            t = base::child1(t);\n\
    \                        } else {\n                            break;\n      \
    \                  }\n                    } else {\n                        t\
    \ = lch;\n                    }\n                }\n                return r;\n\
    \            }\n            template <typename Predicate>\n            static\
    \ std::pair<node_pointer, uint32_t> max_right(node_pointer t, uint32_t l, const\
    \ Predicate& f) {\n                auto [tl, tr] = base::split(t, l);\n      \
    \          size_t w = max_right(tr, f);\n                t = base::merge(tl, tr);\n\
    \                return { t, l + w };\n            }\n            template <typename\
    \ Predicate>\n            static uint32_t min_left(node_pointer t, const Predicate&\
    \ f) {\n                value_type sum = e();\n                assert(f(sum));\n\
    \n                uint32_t l = base::safe_size(t);\n                while (t)\
    \ {\n                    push(t);\n\n                    node_pointer rch = base::child1(t);\n\
    \n                    value_type nxt_sum = op(safe_prod(rch), sum);\n        \
    \            if (f(nxt_sum)) {\n                        l -= base::safe_size(rch);\n\
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
    \ T, int), F(*composition)(F, F), F(*id)()>\n    class ReversibleDynamicLazySegmentTree\
    \ {\n        using node_type = internal::implicit_treap::ReversibleRangeOperateRangeProductNode<T,\
    \ op, e, toggle, F, mapping, composition, id>;\n        using node_pointer = typename\
    \ node_type::node_pointer;\n\n        node_pointer _root;\n\n        struct node_pointer_construct\
    \ {};\n        ReversibleDynamicLazySegmentTree(node_pointer root, node_pointer_construct):\
    \ _root(root) {}\n\n    public:\n        using value_type = typename node_type::value_type;\n\
    \        using operator_type = typename node_type::operator_type;\n\n        ReversibleDynamicLazySegmentTree():\
    \ _root(node_type::empty_node()) {}\n        explicit ReversibleDynamicLazySegmentTree(size_t\
    \ n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value))\
    \ {}\n        template <typename U>\n        ReversibleDynamicLazySegmentTree(const\
    \ std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n\
    \        void free() {\n            node_type::delete_tree(_root);\n         \
    \   _root = node_type::empty_node();\n        }\n        void clear() { free();\
    \ }\n\n        static void reserve(size_t capacity) { node_type::reserve(capacity);\
    \ }\n\n        bool empty() const { return node_type::empty(_root); }\n      \
    \  int size() const { return node_type::safe_size(_root); }\n\n        const value_type&\
    \ operator[](size_t k) const { return get(k); }\n        const value_type& get(size_t\
    \ k) const {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        const value_type& front() const { return get(0); }\n\
    \        const value_type& back() const { return get(size() - 1); }\n        void\
    \ set(size_t k, const value_type& val) {\n            assert(k < size_t(size()));\n\
    \            _root = node_type::set(_root, k, [&](const value_type&) { return\
    \ val; });\n        }\n        template <typename Func>\n        void apply(size_t\
    \ k, const Func& f) {\n            assert(k < size_t(size()));\n            _root\
    \ = node_type::set(_root, k, [&](const value_type& val) { return f(val); });\n\
    \        }\n\n        value_type prod_all() const { return node_type::safe_prod(_root);\
    \ }\n        value_type prod(size_t l, size_t r) {\n            value_type res;\n\
    \            std::tie(_root, res) = node_type::prod(_root, l, r);\n          \
    \  return res;\n        }\n\n        void apply_all(const operator_type& f) {\
    \ _root = node_type::apply_all(_root, f); }\n        void apply(size_t l, size_t\
    \ r, const operator_type& f) { _root = node_type::apply(_root, l, r, f); }\n\n\
    \        void insert(size_t k, const value_type& val) {\n            assert(k\
    \ <= size_t(size()));\n            _root = node_type::insert(_root, k, val);\n\
    \        }\n        void push_front(const value_type& val) { _root = node_type::push_front(_root,\
    \ val); }\n        void push_back(const value_type& val) { _root = node_type::push_back(_root,\
    \ val); }\n\n        // Insert a new value immediately before the first element\
    \ that satisfies the condition f.\n        // Returns: the inserted position\n\
    \        // Requirements: f(A[i]) must be monotonic\n        template <typename\
    \ Predicate>\n        int insert_binary_search(const value_type& val, const Predicate&\
    \ f) {\n            int pos;\n            std::tie(_root, pos) = node_type::insert_binary_search(_root,\
    \ f, val);\n            return pos;\n        }\n        // Insert a new value\
    \ immediately before the first element that is greater than or equal to the new\
    \ value.\n        // Returns: the inserted position\n        // Requirements:\
    \ sequence is sorted\n        template <typename Compare = std::less<>>\n    \
    \    int insert_lower_bound(const value_type& val, const Compare& comp = {}) {\n\
    \            int pos;\n            std::tie(_root, pos) = node_type::insert_lower_bound(_root,\
    \ val, comp);\n            return pos;\n        }\n        // Insert a new value\
    \ immediately before the first element that is greater than the new value.\n \
    \       // Returns: the inserted position\n        // Requirements: sequence is\
    \ sorted\n        template <typename Compare = std::less<>>\n        int insert_upper_bound(const\
    \ value_type& val, const Compare& comp = {}) {\n            int pos;\n       \
    \     std::tie(_root, pos) = node_type::insert_upper_bound(_root, val, comp);\n\
    \            return pos;\n        }\n\n        value_type erase(size_t k) {\n\
    \            assert(k <= size_t(size()));\n            value_type v;\n       \
    \     std::tie(_root, v) = node_type::erase(_root, k);\n            return v;\n\
    \        }\n        value_type pop_front() { return erase(0); }\n        value_type\
    \ pop_back() { return erase(size() - 1); }\n\n        // Erase the first element\
    \ that satisfies the condition f if it also satisfies the condition g.\n     \
    \   // returns optional(position, value)\n        // Requirements: sequence is\
    \ sorted\n        template <typename Predicate, typename RemovePredicate>\n  \
    \      std::optional<std::pair<int, value_type>> erase_binary_search(const Predicate&\
    \ f, const RemovePredicate& g) {\n            auto [root, erased] = node_type::erase_binary_search(_root,\
    \ f, g);\n            _root = root;\n            if (erased) {\n             \
    \   return std::pair<int, value_type>{ erased->first, erased->second };\n    \
    \        } else {\n                return std::nullopt;\n            }\n     \
    \   }\n        // Erase the first element that is greater than or equal to val.\n\
    \        // returns optional(position, value)\n        // Requirements: sequence\
    \ is sorted\n        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_lower_bound(const value_type& val, const Compare& comp =\
    \ {}) {\n            auto [root, erased] = node_type::erase_lower_bound(_root,\
    \ val, comp);\n            _root = root;\n            if (erased) {\n        \
    \        return std::pair<int, value_type>{ erased->first, erased->second };\n\
    \            } else {\n                return std::nullopt;\n            }\n \
    \       }\n        // Erase the first element that is greater than val.\n    \
    \    // returns optional(position, value)\n        // Requirements: sequence is\
    \ sorted\n        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_upper_bound(const value_type& val, const Compare& comp =\
    \ {}) {\n            auto [root, erased] = node_type::erase_upper_bound(_root,\
    \ val, comp);\n            _root = root;\n            if (erased) {\n        \
    \        return std::pair<int, value_type>{ erased->first, erased->second };\n\
    \            } else {\n                return std::nullopt;\n            }\n \
    \       }\n        // Erase the first element that is equal to val.\n        //\
    \ returns optional(position, value)\n        // Requirements: sequence is sorted\n\
    \        template <typename Compare = std::less<>>\n        std::optional<std::pair<int,\
    \ value_type>> erase_if_exists(const value_type& val, const Compare& comp = {})\
    \ {\n            auto [root, erased] = node_type::erase_if_exists(_root, val,\
    \ comp);\n            _root = root;\n            if (erased) {\n             \
    \   return std::pair<int, value_type>{ erased->first, erased->second };\n    \
    \        } else {\n                return std::nullopt;\n            }\n     \
    \   }\n\n        // Split immediately before the k-th element.\n        ReversibleDynamicLazySegmentTree\
    \ split(size_t k) {\n            assert(k <= size_t(size()));\n            node_pointer\
    \ root_r;\n            std::tie(_root, root_r) = node_type::split(_root, k);\n\
    \            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        // Split immediately before the first element that satisfies\
    \ the condition.\n        // Requirements: f(A[i]) must be monotonic\n       \
    \ template <typename Predicate>\n        ReversibleDynamicLazySegmentTree split_binary_search(const\
    \ Predicate& f) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_binary_search(_root, f);\n            return ReversibleDynamicLazySegmentTree(root_r,\
    \ node_pointer_construct{});\n        }\n        // Split immediately before the\
    \ first element that is greater than or equal to val.\n        // Requirements:\
    \ sequence is sorted\n        template <typename Compare = std::less<>>\n    \
    \    ReversibleDynamicLazySegmentTree split_lower_bound(const value_type& val,\
    \ const Compare& comp = {}) {\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split_lower_bound(_root, val, comp);\n            return\
    \ ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});\n      \
    \  }\n        // Split immediately before the first element that is greater than\
    \ val.\n        // Requirements: sequence is sorted\n        template <typename\
    \ Compare = std::less<>>\n        ReversibleDynamicLazySegmentTree split_upper_bound(const\
    \ value_type& val, const Compare& comp = {}) {\n            node_pointer root_r;\n\
    \            std::tie(_root, root_r) = node_type::split_upper_bound(_root, val,\
    \ comp);\n            return ReversibleDynamicLazySegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        void merge(ReversibleDynamicLazySegmentTree r) { _root = node_type::merge(_root,\
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
    \    reverse_iterator rbegin() const { return crbegin(); }\n        reverse_iterator\
    \ rend() const { return crend(); }\n        const_iterator cbegin() const { return\
    \ node_type::cbegin(_root); }\n        const_iterator cend() const { return node_type::cend(_root);\
    \ }\n        const_reverse_iterator crbegin() const { return node_type::crbegin(_root);\
    \ }\n        const_reverse_iterator crend() const { return node_type::crend(_root);\
    \ }\n\n        // handling internal nodes\n        using internal_node = node_type;\n\
    \        using internal_node_pointer = node_pointer;\n\n        internal_node_pointer&\
    \ root_node() { return _root; }\n        const internal_node_pointer& root_node()\
    \ const { return _root; }\n        void set_root_node(internal_node_pointer new_root)\
    \ { root_node() = new_root; }\n    };\n} // namespace suisen\n\n\n\n#line 1 \"\
    library/algebra/monoid/affine.hpp\"\n\n\n\n#line 6 \"library/algebra/monoid/affine.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    struct Affine {\n     \
    \   T a, b;\n        Affine(const T &a = 1, const T &b = 0) : a(a), b(b) {}\n\n\
    \        static Affine<T> id() { return Affine<T>{}; }\n        static Affine<T>\
    \ compose(const Affine<T>& f, const Affine<T>& g) { return f.compose(g); }\n\n\
    \        Affine<T> compose(const Affine<T>& g) const { return { a * g.a, affine(g.b)\
    \ }; }\n\n        template <typename U = T>\n        U affine(const T &x) const\
    \ { return U(a) * x + b; }\n        T operator()(const T &x) const { return affine<T>(x);\
    \ }\n\n        Affine<T> operator+() const { return *this; }\n        Affine<T>\
    \ operator-() const { return { -a, -b }; }\n\n        Affine<T>& operator++()\
    \ { ++b; return *this; }\n        Affine<T>& operator--() { --b; return *this;\
    \ }\n        Affine<T> operator++(int) { Affine<T> f(*this); ++(*this); return\
    \ f; }\n        Affine<T> operator--(int) { Affine<T> f(*this); --(*this); return\
    \ f; }\n\n        Affine<T>& operator+=(const T& c) { b += c; return *this; }\n\
    \        Affine<T>& operator-=(const T& c) { b -= c; return *this; }\n       \
    \ friend Affine<T> operator+(Affine<T> f, const T &c) { f += c; return f; }\n\
    \        friend Affine<T> operator-(Affine<T> f, const T &c) { f -= c; return\
    \ f; }\n\n        Affine<T>& operator+=(const Affine<T> &g) { a += g.a, b += g.b;\
    \ return *this; }\n        Affine<T>& operator-=(const Affine<T> &g) { a -= g.a,\
    \ b -= g.b; return *this; }\n        friend Affine<T> operator+(Affine<T> f, const\
    \ Affine<T> &g) { f += g; return f; }\n        friend Affine<T> operator-(Affine<T>\
    \ f, const Affine<T> &g) { f -= g; return f; }\n\n        friend bool operator==(const\
    \ Affine<T> &f, const Affine<T> &g) { return f.a == g.a and f.b == g.b; }\n  \
    \      friend bool operator!=(const Affine<T> &f, const Affine<T> &g) { return\
    \ not (f == g); }\n        friend bool operator< (const Affine<T> &f, const Affine<T>\
    \ &g) { return f.a < g.a or (f.a == g.a and f.b < g.b); }\n        friend bool\
    \ operator<=(const Affine<T> &f, const Affine<T> &g) { return not (g < f); }\n\
    \        friend bool operator> (const Affine<T> &f, const Affine<T> &g) { return\
    \ g < f; }\n        friend bool operator>=(const Affine<T> &f, const Affine<T>\
    \ &g) { return not (f < g); }\n\n        template <typename U = T, typename V\
    \ = T>\n        operator std::pair<U, V>() { return std::pair<U, V>{ a, b }; }\n\
    \        template <typename U = T, typename V = T>\n        operator std::tuple<U,\
    \ V>() { return std::tuple<U, V>{ a, b }; }\n\n        friend std::istream& operator<<(std::istream&\
    \ in, Affine<T> &f) { return in >> f.a >> f.b; }\n        friend std::ostream&\
    \ operator>>(std::ostream& out, const Affine<T> &f) { return out << f.a << ' '\
    \ << f.b; }\n    };\n} // namespace suisen\n\n\n#line 20 \"test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n\nusing S = mint;\nusing F = suisen::Affine<mint>;\n\nS op(S x, S y) {\n   \
    \ return x + y;\n}\nS e() {\n    return 0;\n}\nS toggle(S x) {\n    return x;\n\
    }\nS mapping(F f, S x, int len) {\n    return f.a * x + f.b * len;\n}\nF composition(F\
    \ f, F g) {\n    return f.compose(g);\n}\nF id() {\n    return F::id();\n}\n\n\
    using Sequence = suisen::ReversibleDynamicLazySegmentTree<S, op, e, toggle, F,\
    \ mapping, composition, id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S>\
    \ init(n);\n    for (auto &e : init) std::cin >> e;\n\n    Sequence::reserve(1000000);\n\
    \n    Sequence seq(std::move(init));\n\n    for (int qid = 0; qid < q; ++qid)\
    \ {\n        int qtype;\n        std::cin >> qtype;\n\n        if (qtype == 0)\
    \ {\n            int i;\n            mint x;\n            std::cin >> i >> x;\n\
    \            seq.insert(i, x);\n        } else if (qtype == 1) {\n           \
    \ int i;\n            std::cin >> i;\n            seq.erase(i);\n        } else\
    \ if (qtype == 2) {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            seq.reverse(l, r);\n        } else if (qtype == 3) {\n          \
    \  int l, r;\n            mint b, c;\n            std::cin >> l >> r >> b >> c;\n\
    \            seq.apply(l, r, F { b, c });\n        } else {\n            int l,\
    \ r;\n            std::cin >> l >> r;\n            std::cout << seq.prod(l, r)\
    \ << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp\"\
    \n#include \"library/algebra/monoid/affine.hpp\"\n\nusing S = mint;\nusing F =\
    \ suisen::Affine<mint>;\n\nS op(S x, S y) {\n    return x + y;\n}\nS e() {\n \
    \   return 0;\n}\nS toggle(S x) {\n    return x;\n}\nS mapping(F f, S x, int len)\
    \ {\n    return f.a * x + f.b * len;\n}\nF composition(F f, F g) {\n    return\
    \ f.compose(g);\n}\nF id() {\n    return F::id();\n}\n\nusing Sequence = suisen::ReversibleDynamicLazySegmentTree<S,\
    \ op, e, toggle, F, mapping, composition, id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S>\
    \ init(n);\n    for (auto &e : init) std::cin >> e;\n\n    Sequence::reserve(1000000);\n\
    \n    Sequence seq(std::move(init));\n\n    for (int qid = 0; qid < q; ++qid)\
    \ {\n        int qtype;\n        std::cin >> qtype;\n\n        if (qtype == 0)\
    \ {\n            int i;\n            mint x;\n            std::cin >> i >> x;\n\
    \            seq.insert(i, x);\n        } else if (qtype == 1) {\n           \
    \ int i;\n            std::cin >> i;\n            seq.erase(i);\n        } else\
    \ if (qtype == 2) {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            seq.reverse(l, r);\n        } else if (qtype == 3) {\n          \
    \  int l, r;\n            mint b, c;\n            std::cin >> l >> r >> b >> c;\n\
    \            seq.apply(l, r, F { b, c });\n        } else {\n            int l,\
    \ r;\n            std::cin >> l >> r;\n            std::cout << seq.prod(l, r)\
    \ << '\\n';\n        }\n    }\n}"
  dependsOn:
  - library/datastructure/bbst/reversible_implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/reversible_implicit_treap_base.hpp
  - library/util/pointer_32bit.hpp
  - library/type_traits/operator.hpp
  - library/debug/warning.hpp
  - library/algebra/monoid/affine.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2023-05-13 02:46:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/src/datastructure/bbst/reversible_implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
---
