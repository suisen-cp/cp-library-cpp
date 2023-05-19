---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/util/pointer_32bit.hpp
    title: library/util/pointer_32bit.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/segment_tree/sortable_segment_tree/abc237_g.test.cpp
    title: test/src/datastructure/segment_tree/sortable_segment_tree/abc237_g.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/sortable_segment_tree/point_set_range_sort_range_composite.test.cpp
    title: test/src/datastructure/segment_tree/sortable_segment_tree/point_set_range_sort_range_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/sortable_segment_tree.hpp\"\
    \n\n\n\n#line 1 \"library/util/pointer_32bit.hpp\"\n\n\n\n#include <vector>\n\n\
    namespace suisen {\n    template <typename Object>\n    struct ptr32 {\n     \
    \   static constexpr int null = -1;\n\n        using object_type = Object;\n \
    \       using pool_type = std::vector<object_type>;\n\n        constexpr ptr32()\
    \ : ptr(null) {}\n        explicit constexpr ptr32(int ptr) : ptr(ptr) {}\n  \
    \      constexpr ptr32(std::nullptr_t) : ptr(null) {}\n\n        object_type&\
    \ operator*() const { return pool[ptr]; }\n        object_type* operator->() const\
    \ { return &pool[ptr]; }\n\n        constexpr operator bool() const { return ptr\
    \ != null; }\n        constexpr operator int() const { return ptr; }\n\n     \
    \   constexpr bool is_not_null() const { return bool(*this); }\n        constexpr\
    \ bool is_null() const { return not bool(*this); }\n\n        friend constexpr\
    \ bool operator==(const ptr32& l, const ptr32& r) { return l.ptr == r.ptr; }\n\
    \        friend constexpr bool operator!=(const ptr32& l, const ptr32& r) { return\
    \ l.ptr != r.ptr; }\n        friend constexpr bool operator<(const ptr32& l, const\
    \ ptr32& r) { return l.ptr < r.ptr; }\n        friend constexpr bool operator<=(const\
    \ ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }\n        friend constexpr\
    \ bool operator>(const ptr32& l, const ptr32& r) { return l.ptr > r.ptr; }\n \
    \       friend constexpr bool operator>=(const ptr32& l, const ptr32& r) { return\
    \ l.ptr >= r.ptr; }\n\n        template <typename ...Args>\n        static ptr32\
    \ alloc(Args &&...args) {\n            if (del.size()) {\n                ptr32\
    \ ptr(del.back());\n                del.pop_back();\n                *ptr = object_type(std::forward<Args>(args)...);\n\
    \                return ptr;\n            } else {\n                ptr32 ptr(pool.size());\n\
    \                pool.emplace_back(std::forward<Args>(args)...);\n           \
    \     return ptr;\n            }\n        }\n        static void dealloc(ptr32\
    \ p) {\n            del.push_back(p);\n        }\n        static void dealloc_all(bool\
    \ shrink) {\n            pool.clear(), del.clear();\n            if (shrink) pool.shrink_to_fit(),\
    \ del.shrink_to_fit();\n        }\n        static void reserve(std::size_t capacity)\
    \ {\n            pool.reserve(capacity);\n        }\n    private:\n        static\
    \ inline pool_type pool{};\n        static inline std::vector<ptr32> del{};\n\n\
    \        int ptr;\n    };\n} // namespace suisen\n\n\n\n#line 5 \"library/datastructure/segment_tree/sortable_segment_tree.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <random>\n#include <tuple>\n\
    #include <utility>\n#line 12 \"library/datastructure/segment_tree/sortable_segment_tree.hpp\"\
    \n\nnamespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T),\
    \ typename Key = int>\n    struct SortableSegmentTree {\n    private:\n      \
    \  static constexpr bool use_32bit_pointer = true;\n\n        struct InnerNode;\n\
    \        struct OuterNode;\n        using inner_node = InnerNode;\n        using\
    \ outer_node = OuterNode;\n        using inner_node_pointer = std::conditional_t<use_32bit_pointer,\
    \ ptr32<inner_node>, inner_node*>;\n        using outer_node_pointer = std::conditional_t<use_32bit_pointer,\
    \ ptr32<outer_node>, outer_node*>;\n    public:\n        using size_type = int;\n\
    \        using key_type = Key;\n        using value_type = T;\n    private:\n\
    \        using random_engine = std::mt19937;\n\n        using priority_type =\
    \ std::invoke_result_t<random_engine>;\n\n        static priority_type random_priority()\
    \ {\n            static random_engine engine{ std::random_device{}() };\n    \
    \        return engine();\n        }\n\n        struct InnerNode {\n         \
    \   priority_type _priority;\n\n            size_type _siz;\n            key_type\
    \ _key;\n            key_type _kmin, _kmax;\n\n            value_type _val;\n\
    \            value_type _sum;\n\n            inner_node_pointer _ch[2]{ nullptr,\
    \ nullptr };\n\n            InnerNode(const key_type& key, const value_type& val)\
    \ : _priority(random_priority()), _siz(1), _key(key), _kmin(key), _kmax(key),\
    \ _val(val), _sum(val) {}\n\n            static size_type& size(inner_node_pointer\
    \ t) { return t->_siz; }\n            static size_type safe_size(inner_node_pointer\
    \ t) { return t ? size(t) : 0; }\n\n            static const key_type& const_key(inner_node_pointer\
    \ t) { return t->_key; }\n            static key_type& key(inner_node_pointer\
    \ t) { return t->_key; }\n            static key_type& min_key(inner_node_pointer\
    \ t) { return t->_kmin; }\n            static key_type& max_key(inner_node_pointer\
    \ t) { return t->_kmax; }\n\n            static const value_type& const_value(inner_node_pointer\
    \ t) { return t->_val; }\n            static value_type& value(inner_node_pointer\
    \ t) { return t->_val; }\n            static std::pair<key_type, value_type> set(inner_node_pointer\
    \ t, const key_type& new_key, const value_type& new_val) {\n                return\
    \ { std::exchange(key(t), new_key), std::exchange(value(t), new_val) };\n    \
    \        }\n\n            static value_type& sum(inner_node_pointer t) { return\
    \ t->_sum; }\n            static value_type safe_sum(inner_node_pointer t) { return\
    \ t ? sum(t) : e(); }\n\n            static priority_type& priority(inner_node_pointer\
    \ t) { return t->_priority; }\n\n            static inner_node_pointer& child0(inner_node_pointer\
    \ t) { return t->_ch[0]; }\n            static inner_node_pointer& child1(inner_node_pointer\
    \ t) { return t->_ch[1]; }\n            static inner_node_pointer set_child0(inner_node_pointer\
    \ t, inner_node_pointer ct) { return std::exchange(child0(t), ct); }\n       \
    \     static inner_node_pointer set_child1(inner_node_pointer t, inner_node_pointer\
    \ ct) { return std::exchange(child1(t), ct); }\n\n            static inner_node_pointer\
    \ update(inner_node_pointer t) {\n                size(t) = safe_size(child0(t))\
    \ + safe_size(child1(t)) + 1;\n                sum(t) = op(op(safe_sum(child0(t)),\
    \ value(t)), safe_sum(child1(t)));\n                min_key(t) = child0(t) ? min_key(child0(t))\
    \ : key(t);\n                max_key(t) = child1(t) ? max_key(child1(t)) : key(t);\n\
    \                return t;\n            }\n\n            static inner_node_pointer\
    \ alloc_node(const key_type& key, const value_type& val) {\n                if\
    \ constexpr (use_32bit_pointer) {\n                    return inner_node_pointer::alloc(key,\
    \ val);\n                } else {\n                    return new inner_node(key,\
    \ val);\n                }\n            }\n            static void dealloc_node(inner_node_pointer\
    \ t) {\n                if constexpr (use_32bit_pointer) {\n                 \
    \   inner_node_pointer::dealloc(t);\n                } else {\n              \
    \      delete t;\n                }\n            }\n            static void dealloc_all(inner_node_pointer\
    \ t) {\n                if (not t) return;\n                dealloc_all(child0(t));\n\
    \                dealloc_all(child1(t));\n                dealloc_node(t);\n \
    \           }\n\n            static value_type get_at(inner_node_pointer t, size_type\
    \ k) {\n                assert(0 <= k and k < safe_size(t));\n               \
    \ while (true) {\n                    if (const size_type lsiz = safe_size(child0(t));\
    \ k <= lsiz) {\n                        if (k == lsiz) return value(t);\n    \
    \                    t = child0(t);\n                    } else {\n          \
    \              t = child1(t);\n                        k -= lsiz + 1;\n      \
    \              }\n                }\n            }\n            static value_type\
    \ set_at(inner_node_pointer t, size_type k, const value_type& val) {\n       \
    \         assert(0 <= k and k < safe_size(t));\n                static std::vector<inner_node_pointer>\
    \ stack{};\n                while (true) {\n                    stack.push_back(t);\n\
    \                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz)\
    \ {\n                        if (k == lsiz) {\n                            value_type\
    \ old_val = value(t);\n                            value(t) = val;\n         \
    \                   while (stack.size()) update(stack.back()), stack.pop_back();\n\
    \                            return old_val;\n                        }\n    \
    \                    t = child0(t);\n                    } else {\n          \
    \              t = child1(t);\n                        k -= lsiz + 1;\n      \
    \              }\n                }\n            }\n            static value_type\
    \ prod_at_range(inner_node_pointer t, size_type l, size_type r) {\n          \
    \      if (not t) return e();\n                if (l <= 0 and r >= size(t)) return\
    \ sum(t);\n                size_type lsiz = safe_size(child0(t));\n          \
    \      if (r <= lsiz) return prod_at_range(child0(t), l, r);\n               \
    \ if (l > lsiz) return prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz + 1));\n\
    \                value_type sum_l = prod_at_range(child0(t), l, r);\n        \
    \        value_type sum_r = prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz\
    \ + 1));\n                return op(op(sum_l, value(t)), sum_r);\n           \
    \ }\n\n            static std::pair<inner_node_pointer, inner_node_pointer> split_at(inner_node_pointer\
    \ t, size_type k) {\n                if (k == 0) return { nullptr, t };\n    \
    \            if (k == safe_size(t)) return { t, nullptr };\n\n               \
    \ static std::vector<inner_node_pointer> lp{}, rp{};\n\n                while\
    \ (true) {\n                    if (const size_type lsiz = safe_size(child0(t));\
    \ k <= lsiz) {\n                        if (rp.size()) set_child0(rp.back(), t);\n\
    \                        rp.push_back(t);\n                        if (k == lsiz)\
    \ {\n                            if (lp.size()) set_child1(lp.back(), child0(t));\n\
    \n                            inner_node_pointer lt = set_child0(t, nullptr),\
    \ rt = nullptr;\n\n                            while (lp.size()) update(lt = lp.back()),\
    \ lp.pop_back();\n                            while (rp.size()) update(rt = rp.back()),\
    \ rp.pop_back();\n\n                            return { lt, rt };\n         \
    \               }\n                        t = child0(t);\n                  \
    \  } else {\n                        if (lp.size()) set_child1(lp.back(), t);\n\
    \                        lp.push_back(t);\n                        t = child1(t);\n\
    \                        k -= lsiz + 1;\n                    }\n             \
    \   }\n            }\n            static std::pair<inner_node_pointer, inner_node_pointer>\
    \ split_key(inner_node_pointer t, key_type k) {\n                if (not t) return\
    \ { nullptr, nullptr };\n                if (k <= min_key(t)) return { nullptr,\
    \ t };\n                if (k > max_key(t)) return { t, nullptr };\n\n       \
    \         static std::vector<inner_node_pointer> lp{}, rp{};\n\n             \
    \   while (t) {\n                    if (k <= key(t)) {\n                    \
    \    if (rp.size()) set_child0(rp.back(), t);\n                        rp.push_back(t);\n\
    \                        inner_node_pointer nt = child0(t);\n                \
    \        if (not nt or max_key(nt) < k) break;\n                        t = nt;\n\
    \                    } else {\n                        if (lp.size()) set_child1(lp.back(),\
    \ t);\n                        lp.push_back(t);\n                        t = child1(t);\n\
    \                    }\n                }\n\n                inner_node_pointer\
    \ lt = nullptr, rt = nullptr;\n                if (t) {\n                    if\
    \ (lp.size()) set_child1(lp.back(), child0(t));\n                    lt = set_child0(t,\
    \ nullptr);\n                } else {\n                    if (lp.size()) set_child1(lp.back(),\
    \ nullptr);\n                }\n\n                while (lp.size()) update(lt\
    \ = lp.back()), lp.pop_back();\n                while (rp.size()) update(rt =\
    \ rp.back()), rp.pop_back();\n\n                return { lt, rt };\n         \
    \   }\n\n            static inner_node_pointer concat(inner_node_pointer tl, inner_node_pointer\
    \ tr) {\n                if (not tl) return tr;\n                if (not tr) return\
    \ tl;\n                assert(max_key(tl) < min_key(tr));\n                if\
    \ (priority(tl) < priority(tr)) {\n                    set_child0(tr, concat(tl,\
    \ child0(tr)));\n                    return update(tr);\n                } else\
    \ {\n                    set_child1(tl, concat(child1(tl), tr));\n           \
    \         return update(tl);\n                }\n            }\n            static\
    \ inner_node_pointer merge(inner_node_pointer t1, inner_node_pointer t2) {\n \
    \               if (not t1) return t2;\n                if (not t2) return t1;\n\
    \                if (key(t1) > key(t2)) std::swap(t1, t2);\n                if\
    \ (max_key(t1) <= min_key(t2)) return concat(t1, t2);\n                if (key(t1)\
    \ <= min_key(t2)) {\n                    inner_node_pointer tr = set_child1(t1,\
    \ nullptr);\n                    return concat(update(t1), merge(t2, tr));\n \
    \               } else if (max_key(t1) <= key(t2)) {\n                    inner_node_pointer\
    \ tl = set_child0(t2, nullptr);\n                    return concat(merge(t1, tl),\
    \ update(t2));\n                } else {\n                    auto [t2_l, t2_r]\
    \ = split_key(t2, key(t1));\n                    assert(t2_l and t2_r);\n    \
    \                inner_node_pointer tr = set_child1(t1, nullptr);\n          \
    \          inner_node_pointer tl = update(t1);\n                    return concat(merge(tl,\
    \ t2_l), merge(tr, t2_r));\n                }\n            }\n\n            template\
    \ <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate,\
    \ value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> max_right(inner_node_pointer t, const Predicate& f, const value_type&\
    \ init_sum = e()) {\n                size_type r = 0;\n                value_type\
    \ s = init_sum;\n                while (t) {\n                    if (value_type\
    \ nxt_s = op(s, safe_sum(child0(t))); f(nxt_s)) {\n                        s =\
    \ std::move(nxt_s);\n                        r += safe_size(child0(t));\n    \
    \                    if (nxt_s = op(s, value(t)); f(nxt_s)) {\n              \
    \              s = std::move(nxt_s);\n                            r += 1;\n  \
    \                          t = child1(t);\n                        } else break;\n\
    \                    } else {\n                        t = child0(t);\n      \
    \              }\n                }\n                return { r, s };\n      \
    \      }\n            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> min_left(inner_node_pointer t, const Predicate& f, const value_type&\
    \ init_sum = e()) {\n                size_type l = safe_size(t);\n           \
    \     value_type s = init_sum;\n                while (t) {\n                \
    \    if (value_type nxt_s = op(safe_sum(child1(t)), s); f(nxt_s)) {\n        \
    \                s = std::move(nxt_s);\n                        l -= safe_size(child1(t));\n\
    \                        if (nxt_s = op(value(t), s); f(nxt_s)) {\n          \
    \                  s = std::move(nxt_s);\n                            l -= 1;\n\
    \                            t = child0(t);\n                        } else break;\n\
    \                    } else {\n                        t = child1(t);\n      \
    \              }\n                }\n                return { l, s };\n      \
    \      }\n\n            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n            static\
    \ void foreach(inner_node_pointer t, bool rev, const Func& f) {\n            \
    \    if (not t) return;\n                if (rev) {\n                    foreach(child1(t),\
    \ rev, f), f(const_key(t), const_value(t)), foreach(child0(t), rev, f);\n    \
    \            } else {\n                    foreach(child0(t), rev, f), f(const_key(t),\
    \ const_value(t)), foreach(child1(t), rev, f);\n                }\n          \
    \  }\n        };\n\n        struct OuterNode {\n            priority_type _priority;\n\
    \n            size_type _siz;\n            value_type _sum;\n\n            bool\
    \ _rev;\n            inner_node_pointer _inner_node;\n\n            outer_node_pointer\
    \ _ch[2]{ nullptr, nullptr };\n\n            OuterNode(inner_node_pointer inner_node,\
    \ bool rev = false) : _priority(random_priority()), _siz(inner_node::size(inner_node)),\
    \ _sum(inner_node::sum(inner_node)), _rev(rev), _inner_node(inner_node) {\n  \
    \              if (rev) _sum = toggle(std::move(_sum));\n            }\n\n   \
    \         static size_type& size(outer_node_pointer t) { return t->_siz; }\n \
    \           static size_type safe_size(outer_node_pointer t) { return t ? size(t)\
    \ : 0; }\n            static size_type inner_size(outer_node_pointer t) { return\
    \ inner_node::size(inner(t)); }\n\n            static value_type& sum(outer_node_pointer\
    \ t) { return t->_sum; }\n            static value_type safe_sum(outer_node_pointer\
    \ t) { return t ? sum(t) : e(); };\n            static value_type inner_sum(outer_node_pointer\
    \ t) {\n                value_type res = inner_node::sum(inner(t));\n        \
    \        return reversed(t) ? toggle(std::move(res)) : res;\n            }\n\n\
    \            static bool& reversed(outer_node_pointer t) { return t->_rev; }\n\
    \n            static priority_type& priority(outer_node_pointer t) { return t->_priority;\
    \ }\n\n            static outer_node_pointer& child0(outer_node_pointer t) { return\
    \ t->_ch[0]; }\n            static outer_node_pointer& child1(outer_node_pointer\
    \ t) { return t->_ch[1]; }\n            static outer_node_pointer set_child0(outer_node_pointer\
    \ t, outer_node_pointer ct) { return std::exchange(child0(t), ct); }\n       \
    \     static outer_node_pointer set_child1(outer_node_pointer t, outer_node_pointer\
    \ ct) { return std::exchange(child1(t), ct); }\n\n            static inner_node_pointer&\
    \ inner(outer_node_pointer t) { return t->_inner_node; }\n\n            static\
    \ outer_node_pointer update(outer_node_pointer t) { // t : not nullptr\n     \
    \           size(t) = safe_size(child0(t)) + safe_size(child1(t)) + inner_size(t);\n\
    \                sum(t) = op(op(safe_sum(child0(t)), inner_sum(t)), safe_sum(child1(t)));\n\
    \                return t;\n            }\n\n            static outer_node_pointer\
    \ alloc_node(inner_node_pointer inner_node, bool rev = false) {\n            \
    \    if (not inner_node) return nullptr;\n                if constexpr (use_32bit_pointer)\
    \ {\n                    return outer_node_pointer::alloc(inner_node, rev);\n\
    \                } else {\n                    return new outer_node(inner_node,\
    \ rev);\n                }\n            }\n            static void dealloc_node(outer_node_pointer\
    \ t) {\n                if (not t) return;\n                inner_node::dealloc_all(inner(t));\n\
    \                if constexpr (use_32bit_pointer) {\n                    outer_node_pointer::dealloc(t);\n\
    \                } else {\n                    delete t;\n                }\n\
    \            }\n            static void dealloc_all(outer_node_pointer t) {\n\
    \                if (not t) return;\n                dealloc_all(child0(t));\n\
    \                dealloc_all(child1(t));\n                dealloc_node(t);\n \
    \           }\n\n            static outer_node_pointer build(const std::vector<std::pair<key_type,\
    \ value_type>>& dat) {\n                const size_t n = dat.size();\n\n     \
    \           if (n == 0) return nullptr;\n\n                std::vector<priority_type>\
    \ priorities(n);\n                std::generate(priorities.begin(), priorities.end(),\
    \ random_priority);\n                std::make_heap(priorities.begin(), priorities.end());\n\
    \n                std::vector<outer_node_pointer> nodes(n);\n\n              \
    \  size_t fpow2 = 1;\n                while ((fpow2 << 1) <= n) fpow2 <<= 1; //\
    \ 2^floor(log_2(n))\n\n                if constexpr (use_32bit_pointer) {\n  \
    \                  inner_node_pointer::reserve(n);\n                    outer_node_pointer::reserve(n);\n\
    \                }\n\n                for (size_t bbst_index = 1, skipped = 0;\
    \ bbst_index < 2 * fpow2; ++bbst_index) {\n                    size_t heap_index\
    \ = (fpow2 | ((bbst_index - 1) >> 1)) >> __builtin_ctz(bbst_index);\n        \
    \            if (heap_index <= n) {\n                        size_t index = bbst_index\
    \ - skipped;\n                        inner_node_pointer inner = inner_node::alloc_node(dat[index\
    \ - 1].first, dat[index - 1].second);\n                        nodes[heap_index\
    \ - 1] = outer_node::alloc_node(inner);\n                        inner_node::priority(inner)\
    \ = priorities[heap_index - 1];\n                    } else {\n              \
    \          ++skipped;\n                    }\n                }\n            \
    \    for (size_t i = fpow2 - 1; i >= 1; --i) {\n                    size_t li\
    \ = 2 * i, ri = 2 * i + 1;\n                    if (li <= n) set_child0(nodes[i\
    \ - 1], nodes[li - 1]);\n                    if (ri <= n) set_child1(nodes[i -\
    \ 1], nodes[ri - 1]);\n                    update(nodes[i - 1]);\n           \
    \     }\n                return nodes[0];\n            }\n\n            static\
    \ value_type get_at(outer_node_pointer t, size_type k) {\n                assert(0\
    \ <= k and k < safe_size(t));\n                while (true) {\n              \
    \      if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               size_type k_inner = k - lsiz;\n                            return\
    \ inner_node::get_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t)) -\
    \ k_inner - 1 : k_inner);\n                        }\n                       \
    \ t = child0(t);\n                    } else {\n                        t = child1(t);\n\
    \                        k -= lsiz + msiz;\n                    }\n          \
    \      }\n            }\n            static value_type set_at(outer_node_pointer\
    \ t, size_type k, const value_type& val) {\n                assert(0 <= k and\
    \ k < safe_size(t));\n                static std::vector<outer_node_pointer> stack{};\n\
    \                while (true) {\n                    stack.push_back(t);\n   \
    \                 if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               size_type k_inner = k - lsiz;\n                            value_type\
    \ old_val = inner_node::set_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t))\
    \ - k_inner - 1 : k_inner, val);\n                            while (stack.size())\
    \ update(stack.back()), stack.pop_back();\n                            return\
    \ old_val;\n                        }\n                        t = child0(t);\n\
    \                    } else {\n                        t = child1(t);\n      \
    \                  k -= lsiz + msiz;\n                    }\n                }\n\
    \            }\n            static value_type prod(outer_node_pointer t, size_type\
    \ l, size_type r) {\n                if (not t) return e();\n                if\
    \ (l <= 0 and r >= size(t)) return sum(t);\n                size_type lsiz = safe_size(child0(t));\n\
    \                if (r <= lsiz) return prod(child0(t), l, r);\n              \
    \  size_type msiz = inner_size(t);\n                if (l >= lsiz + msiz) return\
    \ prod(child1(t), l - (lsiz + msiz), r - (lsiz + msiz));\n                value_type\
    \ sum_l = prod(child0(t), l, r);\n                value_type sum_r = prod(child1(t),\
    \ l - (lsiz + msiz), r - (lsiz + msiz));\n                if (reversed(t)) {\n\
    \                    value_type sum_m = inner_node::prod_at_range(inner(t), msiz\
    \ - (r - lsiz), msiz - (l - lsiz));\n                    return op(op(sum_l, toggle(sum_m)),\
    \ sum_r);\n                } else {\n                    value_type sum_m = inner_node::prod_at_range(inner(t),\
    \ l - lsiz, r - lsiz);\n                    return op(op(sum_l, sum_m), sum_r);\n\
    \                }\n            }\n\n            static std::pair<outer_node_pointer,\
    \ outer_node_pointer> split_at(outer_node_pointer t, size_type k) {\n        \
    \        if (k == 0) return { nullptr, t };\n                if (k == safe_size(t))\
    \ return { t, nullptr };\n\n                static std::vector<outer_node_pointer>\
    \ lp{}, rp{};\n\n                while (true) {\n                    if (const\
    \ size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               outer_node_pointer tl, tr;\n                            if (reversed(t))\
    \ {\n                                size_type k_inner = inner_node::safe_size(inner(t))\
    \ - (k - lsiz);\n                                auto [inner_tr, inner_tl] = inner_node::split_at(inner(t),\
    \ k_inner);\n                                tl = outer_node::alloc_node(inner_tl,\
    \ true);\n                                tr = outer_node::alloc_node(inner_tr,\
    \ true);\n                            } else {\n                             \
    \   size_type k_inner = k - lsiz;\n                                auto [inner_tl,\
    \ inner_tr] = inner_node::split_at(inner(t), k_inner);\n                     \
    \           tl = outer_node::alloc_node(inner_tl, false);\n                  \
    \              tr = outer_node::alloc_node(inner_tr, false);\n               \
    \             }\n\n                            tl = concat(std::exchange(child0(t),\
    \ nullptr), tl);\n                            tr = concat(tr, std::exchange(child1(t),\
    \ nullptr));\n\n                            inner(t) = nullptr;\n            \
    \                dealloc_node(t);\n\n                            if (rp.size())\
    \ set_child0(rp.back(), tr);\n                            if (lp.size()) set_child1(lp.back(),\
    \ tl);\n\n                            outer_node_pointer lt = tl, rt = tr;\n\n\
    \                            while (lp.size()) update(lt = lp.back()), lp.pop_back();\n\
    \                            while (rp.size()) update(rt = rp.back()), rp.pop_back();\n\
    \n                            return { lt, rt };\n                        }\n\
    \                        if (rp.size()) set_child0(rp.back(), t);\n          \
    \              rp.push_back(t);\n                        t = child0(t);\n    \
    \                } else {\n                        if (lp.size()) set_child1(lp.back(),\
    \ t);\n                        lp.push_back(t);\n                        t = child1(t);\n\
    \                        k -= lsiz + msiz;\n                    }\n          \
    \      }\n            }\n            static std::tuple<outer_node_pointer, outer_node_pointer,\
    \ outer_node_pointer> split_at_range(outer_node_pointer t, size_type l, size_type\
    \ r) {\n                auto [tlm, tr] = split_at(t, r);\n                auto\
    \ [tl, tm] = split_at(tlm, l);\n                return { tl, tm, tr };\n     \
    \       }\n\n            static outer_node_pointer concat(outer_node_pointer tl,\
    \ outer_node_pointer tr) {\n                if (not tl) return tr;\n         \
    \       if (not tr) return tl;\n                if (priority(tl) < priority(tr))\
    \ {\n                    set_child0(tr, concat(tl, child0(tr)));\n           \
    \         return update(tr);\n                } else {\n                    set_child1(tl,\
    \ concat(child1(tl), tr));\n                    return update(tl);\n         \
    \       }\n            }\n            static outer_node_pointer concat(outer_node_pointer\
    \ tl, outer_node_pointer tm, outer_node_pointer tr) {\n                return\
    \ concat(concat(tl, tm), tr);\n            }\n\n            static inner_node_pointer\
    \ merge_all(outer_node_pointer t) {\n                if (not t) return nullptr;\n\
    \                inner_node_pointer res = inner_node::merge(inner_node::merge(merge_all(child0(t)),\
    \ inner(t)), merge_all(child1(t)));\n                inner(t) = nullptr;\n   \
    \             dealloc_node(t);\n                return res;\n            }\n\n\
    \            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> max_right_prefix(outer_node_pointer t, const Predicate& f) {\n \
    \               size_type r = 0;\n                value_type s = e();\n      \
    \          while (t) {\n                    if (value_type nxt_s = op(s, safe_sum(child0(t)));\
    \ f(nxt_s)) {\n                        s = std::move(nxt_s);\n               \
    \         r += safe_size(child0(t));\n                        if (nxt_s = op(s,\
    \ inner_sum(t)); f(nxt_s)) {\n                            s = std::move(nxt_s);\n\
    \                            r += inner_size(t);\n                           \
    \ t = child1(t);\n                        } else {\n                         \
    \   size_type r_inner;\n                            std::tie(r_inner, s) = inner_node::max_right(inner(t),\
    \ f, s);\n                            r += r_inner;\n                        \
    \    break;\n                        }\n                    } else {\n       \
    \                 t = child0(t);\n                    }\n                }\n \
    \               return { r, s };\n            }\n            template <typename\
    \ Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>,\
    \ std::nullptr_t> = nullptr>\n            static std::tuple<outer_node_pointer,\
    \ size_type, value_type> max_right(outer_node_pointer t, size_type l, const Predicate&\
    \ f) {\n                auto [tl, tr] = split_at(t, l);\n                auto\
    \ [r, s] = max_right_prefix(tr, f);\n                return { concat(tl, tr),\
    \ l + r, s };\n            }\n\n            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> min_left_suffix(outer_node_pointer t, const Predicate& f) {\n  \
    \              size_type l = safe_size(t);\n                value_type s = e();\n\
    \                while (t) {\n                    if (value_type nxt_s = op(safe_sum(child1(t)),\
    \ s); f(nxt_s)) {\n                        s = std::move(nxt_s);\n           \
    \             l -= safe_size(child1(t));\n                        if (nxt_s =\
    \ op(inner_sum(t), s); f(nxt_s)) {\n                            s = std::move(nxt_s);\n\
    \                            l -= inner_size(t);\n                           \
    \ t = child0(t);\n                        } else {\n                         \
    \   size_type l_inner;\n                            std::tie(l_inner, s) = inner_node::min_left(inner(t),\
    \ f, s);\n                            l -= inner_size(t) - l_inner;\n        \
    \                    break;\n                        }\n                    }\
    \ else {\n                        t = child1(t);\n                    }\n    \
    \            }\n                return { l, s };\n            }\n            template\
    \ <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate,\
    \ value_type>, std::nullptr_t> = nullptr>\n            static std::tuple<outer_node_pointer,\
    \ size_type, value_type> min_left(outer_node_pointer t, size_type r, const Predicate&\
    \ f) {\n                auto [tl, tr] = split_at(t, r);\n                auto\
    \ [l, s] = min_left_suffix(tl, f);\n                return { concat(tl, tr), l,\
    \ s };\n            }\n\n            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n            static\
    \ void foreach(outer_node_pointer t, bool rev, const Func& f) {\n            \
    \    if (not t) return;\n                if (rev) {\n                    foreach(child1(t),\
    \ rev, f);\n                    inner_node::foreach(inner(t), not reversed(t),\
    \ f);\n                    foreach(child0(t), rev, f);\n                } else\
    \ {\n                    foreach(child0(t), rev, f);\n                    inner_node::foreach(inner(t),\
    \ reversed(t), f);\n                    foreach(child1(t), rev, f);\n        \
    \        }\n            }\n        };\n\n        outer_node_pointer _root;\n \
    \       SortableSegmentTree(outer_node_pointer root) : _root(root) {}\n    public:\n\
    \        SortableSegmentTree() : SortableSegmentTree(nullptr) {}\n        SortableSegmentTree(const\
    \ std::vector<std::pair<key_type, value_type>>& dat) : SortableSegmentTree(outer_node::build(dat))\
    \ {}\n\n        ~SortableSegmentTree() {\n            outer_node::dealloc_all(_root);\n\
    \        }\n\n        size_type size() {\n            return outer_node::safe_size(_root);\n\
    \        }\n\n        auto operator[](size_type k) {\n            struct proxy\
    \ {\n                outer_node_pointer root;\n                size_type k;\n\
    \                operator value_type()&& { return outer_node::get_at(root, k);\
    \ }\n                value_type operator=(const value_type& val)&& { return outer_node::set_at(root,\
    \ k, val), val; }\n            };\n            return proxy{ _root, k };\n   \
    \     }\n        value_type get(size_type k) {\n            assert(0 <= k and\
    \ k < size());\n            return outer_node::get_at(_root, k);\n        }\n\
    \        // returns old value\n        value_type set_value(size_type k, const\
    \ value_type& val) {\n            assert(0 <= k and k < size());\n           \
    \ return outer_node::set_at(_root, k, val);\n        }\n        // returns old\
    \ {key, value}\n        std::pair<key_type, value_type> set_key_value(size_type\
    \ i, const key_type& key, const value_type& val) {\n            assert(0 <= i\
    \ and i < size());\n            auto [tl, tm, tr] = outer_node::split_at_range(_root,\
    \ i, i + 1);\n            inner_node_pointer tm_inner = outer_node::inner(tm);\n\
    \            std::pair<key_type, value_type> res = inner_node::set(tm_inner, key,\
    \ val);\n            inner_node::update(tm_inner);\n            _root = outer_node::concat(tl,\
    \ outer_node::update(tm), tr);\n            return res;\n        }\n\n       \
    \ void insert(size_type i, const key_type& key, const value_type& val) {\n   \
    \         assert(0 <= i and i <= size());\n            auto [tl, tr] = outer_node::split_at(_root,\
    \ i);\n            auto tm = outer_node::alloc_node(inner_node::alloc_node(key,\
    \ val));\n            _root = outer_node::concat(tl, tm, tr);\n        }\n   \
    \     void push_front(const key_type& key, const value_type& val) { insert(0,\
    \ key, val); }\n        void push_back(const key_type& key, const value_type&\
    \ val) { insert(size(), key, val); }\n\n        std::pair<key_type, value_type>\
    \ erase(size_type i) {\n            assert(0 <= i and i < size());\n         \
    \   auto [tl, tm, tr] = outer_node::split_at_range(_root, i, i + 1);\n       \
    \     _root = outer_node::concat(tl, tr);\n            inner_node_pointer tm_inner\
    \ = outer_node::inner(tm);\n            std::pair<key_type, value_type> res {\
    \ std::move(inner_node::key(tm_inner)), std::move(inner_node::value(tm_inner))\
    \ };\n            outer_node::dealloc_node(tm);\n            return res;\n   \
    \     }\n        std::pair<key_type, value_type> pop_front() { erase(0); }\n \
    \       std::pair<key_type, value_type> pop_back() { erase(size() - 1); }\n\n\
    \        SortableSegmentTree split(size_type i) {\n            assert(0 <= i and\
    \ i <= size());\n            auto [root_l, root_r] = outer_node::split_at(_root,\
    \ i);\n            _root = root_l;\n            return SortableSegmentTree{ root_r\
    \ };\n        }\n        void concat(SortableSegmentTree tr) {\n            _root\
    \ = outer_node::concat(_root, tr->_root);\n        }\n\n        value_type prod(size_type\
    \ l, size_type r) {\n            assert(0 <= l and l <= r and r <= size());\n\
    \            if (l == r) return e();\n            if (r - l == 1) return (*this)[l];\n\
    \            return outer_node::prod(_root, l, r);\n        }\n\n        enum\
    \ struct SortingPolicy { ascending, descending };\n        void sort(size_type\
    \ l, size_type r, SortingPolicy policy = SortingPolicy::ascending) {\n       \
    \     assert(0 <= l and l <= r and r <= size());\n            if (l == r) return;\n\
    \            auto [tl, tm, tr] = outer_node::split_at_range(_root, l, r);\n  \
    \          _root = outer_node::concat(tl, outer_node::alloc_node(outer_node::merge_all(tm),\
    \ policy == SortingPolicy::descending), tr);\n        }\n        void sort_asc(size_type\
    \ l, size_type r) { sort(l, r, SortingPolicy::ascending); }\n        void sort_dsc(size_type\
    \ l, size_type r) { sort(l, r, SortingPolicy::descending); }\n\n        // returns\
    \ { r := max{ r' | f(prod(l, r')) = true }, prod(l, r) }\n        template <typename\
    \ Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>,\
    \ std::nullptr_t> = nullptr>\n        std::pair<size_type, value_type> max_right(size_type\
    \ l, const Predicate& f) {\n            assert(0 <= l and l <= size());\n    \
    \        assert(f(e()));\n            auto [new_root, r, s] = outer_node::max_right(_root,\
    \ l, f);\n            _root = new_root;\n            return { r, s };\n      \
    \  }\n        // returns { l := min{ l' | f(prod(l', r)) = true }, prod(l, r)\
    \ }\n        template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n        std::pair<size_type,\
    \ value_type> min_left(size_type r, const Predicate& f) {\n            assert(0\
    \ <= r and r <= size());\n            assert(f(e()));\n            auto [new_root,\
    \ l, s] = outer_node::min_left(_root, r, f);\n            _root = new_root;\n\
    \            return { l, s };\n        }\n\n        template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n        void foreach(const\
    \ Func& f, bool reversed = false) {\n            outer_node::foreach(_root, reversed,\
    \ f);\n        }\n        std::vector<key_type> dump_keys() {\n            std::vector<key_type>\
    \ res(size());\n            auto it = res.begin();\n            foreach([&it](const\
    \ key_type& key, const value_type&) { *it++ = key; });\n            return res;\n\
    \        }\n        std::vector<value_type> dump_values() {\n            std::vector<value_type>\
    \ res(size());\n            auto it = res.begin();\n            foreach([&it](const\
    \ key_type&, const value_type& val) { *it++ = val; });\n            return res;\n\
    \        }\n        std::vector<std::pair<key_type, value_type>> dump_entries()\
    \ {\n            std::vector<std::pair<key_type, value_type>> res(size());\n \
    \           auto it = res.begin();\n            foreach([&it](const key_type&\
    \ key, const value_type& val) { *it++ = std::pair{ key, val }; });\n         \
    \   return res;\n        }\n    };\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SORTABLE_SEGTREE\n#define SUISEN_SORTABLE_SEGTREE\n\n#include\
    \ \"library/util/pointer_32bit.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <random>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    namespace suisen {\n    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T),\
    \ typename Key = int>\n    struct SortableSegmentTree {\n    private:\n      \
    \  static constexpr bool use_32bit_pointer = true;\n\n        struct InnerNode;\n\
    \        struct OuterNode;\n        using inner_node = InnerNode;\n        using\
    \ outer_node = OuterNode;\n        using inner_node_pointer = std::conditional_t<use_32bit_pointer,\
    \ ptr32<inner_node>, inner_node*>;\n        using outer_node_pointer = std::conditional_t<use_32bit_pointer,\
    \ ptr32<outer_node>, outer_node*>;\n    public:\n        using size_type = int;\n\
    \        using key_type = Key;\n        using value_type = T;\n    private:\n\
    \        using random_engine = std::mt19937;\n\n        using priority_type =\
    \ std::invoke_result_t<random_engine>;\n\n        static priority_type random_priority()\
    \ {\n            static random_engine engine{ std::random_device{}() };\n    \
    \        return engine();\n        }\n\n        struct InnerNode {\n         \
    \   priority_type _priority;\n\n            size_type _siz;\n            key_type\
    \ _key;\n            key_type _kmin, _kmax;\n\n            value_type _val;\n\
    \            value_type _sum;\n\n            inner_node_pointer _ch[2]{ nullptr,\
    \ nullptr };\n\n            InnerNode(const key_type& key, const value_type& val)\
    \ : _priority(random_priority()), _siz(1), _key(key), _kmin(key), _kmax(key),\
    \ _val(val), _sum(val) {}\n\n            static size_type& size(inner_node_pointer\
    \ t) { return t->_siz; }\n            static size_type safe_size(inner_node_pointer\
    \ t) { return t ? size(t) : 0; }\n\n            static const key_type& const_key(inner_node_pointer\
    \ t) { return t->_key; }\n            static key_type& key(inner_node_pointer\
    \ t) { return t->_key; }\n            static key_type& min_key(inner_node_pointer\
    \ t) { return t->_kmin; }\n            static key_type& max_key(inner_node_pointer\
    \ t) { return t->_kmax; }\n\n            static const value_type& const_value(inner_node_pointer\
    \ t) { return t->_val; }\n            static value_type& value(inner_node_pointer\
    \ t) { return t->_val; }\n            static std::pair<key_type, value_type> set(inner_node_pointer\
    \ t, const key_type& new_key, const value_type& new_val) {\n                return\
    \ { std::exchange(key(t), new_key), std::exchange(value(t), new_val) };\n    \
    \        }\n\n            static value_type& sum(inner_node_pointer t) { return\
    \ t->_sum; }\n            static value_type safe_sum(inner_node_pointer t) { return\
    \ t ? sum(t) : e(); }\n\n            static priority_type& priority(inner_node_pointer\
    \ t) { return t->_priority; }\n\n            static inner_node_pointer& child0(inner_node_pointer\
    \ t) { return t->_ch[0]; }\n            static inner_node_pointer& child1(inner_node_pointer\
    \ t) { return t->_ch[1]; }\n            static inner_node_pointer set_child0(inner_node_pointer\
    \ t, inner_node_pointer ct) { return std::exchange(child0(t), ct); }\n       \
    \     static inner_node_pointer set_child1(inner_node_pointer t, inner_node_pointer\
    \ ct) { return std::exchange(child1(t), ct); }\n\n            static inner_node_pointer\
    \ update(inner_node_pointer t) {\n                size(t) = safe_size(child0(t))\
    \ + safe_size(child1(t)) + 1;\n                sum(t) = op(op(safe_sum(child0(t)),\
    \ value(t)), safe_sum(child1(t)));\n                min_key(t) = child0(t) ? min_key(child0(t))\
    \ : key(t);\n                max_key(t) = child1(t) ? max_key(child1(t)) : key(t);\n\
    \                return t;\n            }\n\n            static inner_node_pointer\
    \ alloc_node(const key_type& key, const value_type& val) {\n                if\
    \ constexpr (use_32bit_pointer) {\n                    return inner_node_pointer::alloc(key,\
    \ val);\n                } else {\n                    return new inner_node(key,\
    \ val);\n                }\n            }\n            static void dealloc_node(inner_node_pointer\
    \ t) {\n                if constexpr (use_32bit_pointer) {\n                 \
    \   inner_node_pointer::dealloc(t);\n                } else {\n              \
    \      delete t;\n                }\n            }\n            static void dealloc_all(inner_node_pointer\
    \ t) {\n                if (not t) return;\n                dealloc_all(child0(t));\n\
    \                dealloc_all(child1(t));\n                dealloc_node(t);\n \
    \           }\n\n            static value_type get_at(inner_node_pointer t, size_type\
    \ k) {\n                assert(0 <= k and k < safe_size(t));\n               \
    \ while (true) {\n                    if (const size_type lsiz = safe_size(child0(t));\
    \ k <= lsiz) {\n                        if (k == lsiz) return value(t);\n    \
    \                    t = child0(t);\n                    } else {\n          \
    \              t = child1(t);\n                        k -= lsiz + 1;\n      \
    \              }\n                }\n            }\n            static value_type\
    \ set_at(inner_node_pointer t, size_type k, const value_type& val) {\n       \
    \         assert(0 <= k and k < safe_size(t));\n                static std::vector<inner_node_pointer>\
    \ stack{};\n                while (true) {\n                    stack.push_back(t);\n\
    \                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz)\
    \ {\n                        if (k == lsiz) {\n                            value_type\
    \ old_val = value(t);\n                            value(t) = val;\n         \
    \                   while (stack.size()) update(stack.back()), stack.pop_back();\n\
    \                            return old_val;\n                        }\n    \
    \                    t = child0(t);\n                    } else {\n          \
    \              t = child1(t);\n                        k -= lsiz + 1;\n      \
    \              }\n                }\n            }\n            static value_type\
    \ prod_at_range(inner_node_pointer t, size_type l, size_type r) {\n          \
    \      if (not t) return e();\n                if (l <= 0 and r >= size(t)) return\
    \ sum(t);\n                size_type lsiz = safe_size(child0(t));\n          \
    \      if (r <= lsiz) return prod_at_range(child0(t), l, r);\n               \
    \ if (l > lsiz) return prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz + 1));\n\
    \                value_type sum_l = prod_at_range(child0(t), l, r);\n        \
    \        value_type sum_r = prod_at_range(child1(t), l - (lsiz + 1), r - (lsiz\
    \ + 1));\n                return op(op(sum_l, value(t)), sum_r);\n           \
    \ }\n\n            static std::pair<inner_node_pointer, inner_node_pointer> split_at(inner_node_pointer\
    \ t, size_type k) {\n                if (k == 0) return { nullptr, t };\n    \
    \            if (k == safe_size(t)) return { t, nullptr };\n\n               \
    \ static std::vector<inner_node_pointer> lp{}, rp{};\n\n                while\
    \ (true) {\n                    if (const size_type lsiz = safe_size(child0(t));\
    \ k <= lsiz) {\n                        if (rp.size()) set_child0(rp.back(), t);\n\
    \                        rp.push_back(t);\n                        if (k == lsiz)\
    \ {\n                            if (lp.size()) set_child1(lp.back(), child0(t));\n\
    \n                            inner_node_pointer lt = set_child0(t, nullptr),\
    \ rt = nullptr;\n\n                            while (lp.size()) update(lt = lp.back()),\
    \ lp.pop_back();\n                            while (rp.size()) update(rt = rp.back()),\
    \ rp.pop_back();\n\n                            return { lt, rt };\n         \
    \               }\n                        t = child0(t);\n                  \
    \  } else {\n                        if (lp.size()) set_child1(lp.back(), t);\n\
    \                        lp.push_back(t);\n                        t = child1(t);\n\
    \                        k -= lsiz + 1;\n                    }\n             \
    \   }\n            }\n            static std::pair<inner_node_pointer, inner_node_pointer>\
    \ split_key(inner_node_pointer t, key_type k) {\n                if (not t) return\
    \ { nullptr, nullptr };\n                if (k <= min_key(t)) return { nullptr,\
    \ t };\n                if (k > max_key(t)) return { t, nullptr };\n\n       \
    \         static std::vector<inner_node_pointer> lp{}, rp{};\n\n             \
    \   while (t) {\n                    if (k <= key(t)) {\n                    \
    \    if (rp.size()) set_child0(rp.back(), t);\n                        rp.push_back(t);\n\
    \                        inner_node_pointer nt = child0(t);\n                \
    \        if (not nt or max_key(nt) < k) break;\n                        t = nt;\n\
    \                    } else {\n                        if (lp.size()) set_child1(lp.back(),\
    \ t);\n                        lp.push_back(t);\n                        t = child1(t);\n\
    \                    }\n                }\n\n                inner_node_pointer\
    \ lt = nullptr, rt = nullptr;\n                if (t) {\n                    if\
    \ (lp.size()) set_child1(lp.back(), child0(t));\n                    lt = set_child0(t,\
    \ nullptr);\n                } else {\n                    if (lp.size()) set_child1(lp.back(),\
    \ nullptr);\n                }\n\n                while (lp.size()) update(lt\
    \ = lp.back()), lp.pop_back();\n                while (rp.size()) update(rt =\
    \ rp.back()), rp.pop_back();\n\n                return { lt, rt };\n         \
    \   }\n\n            static inner_node_pointer concat(inner_node_pointer tl, inner_node_pointer\
    \ tr) {\n                if (not tl) return tr;\n                if (not tr) return\
    \ tl;\n                assert(max_key(tl) < min_key(tr));\n                if\
    \ (priority(tl) < priority(tr)) {\n                    set_child0(tr, concat(tl,\
    \ child0(tr)));\n                    return update(tr);\n                } else\
    \ {\n                    set_child1(tl, concat(child1(tl), tr));\n           \
    \         return update(tl);\n                }\n            }\n            static\
    \ inner_node_pointer merge(inner_node_pointer t1, inner_node_pointer t2) {\n \
    \               if (not t1) return t2;\n                if (not t2) return t1;\n\
    \                if (key(t1) > key(t2)) std::swap(t1, t2);\n                if\
    \ (max_key(t1) <= min_key(t2)) return concat(t1, t2);\n                if (key(t1)\
    \ <= min_key(t2)) {\n                    inner_node_pointer tr = set_child1(t1,\
    \ nullptr);\n                    return concat(update(t1), merge(t2, tr));\n \
    \               } else if (max_key(t1) <= key(t2)) {\n                    inner_node_pointer\
    \ tl = set_child0(t2, nullptr);\n                    return concat(merge(t1, tl),\
    \ update(t2));\n                } else {\n                    auto [t2_l, t2_r]\
    \ = split_key(t2, key(t1));\n                    assert(t2_l and t2_r);\n    \
    \                inner_node_pointer tr = set_child1(t1, nullptr);\n          \
    \          inner_node_pointer tl = update(t1);\n                    return concat(merge(tl,\
    \ t2_l), merge(tr, t2_r));\n                }\n            }\n\n            template\
    \ <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate,\
    \ value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> max_right(inner_node_pointer t, const Predicate& f, const value_type&\
    \ init_sum = e()) {\n                size_type r = 0;\n                value_type\
    \ s = init_sum;\n                while (t) {\n                    if (value_type\
    \ nxt_s = op(s, safe_sum(child0(t))); f(nxt_s)) {\n                        s =\
    \ std::move(nxt_s);\n                        r += safe_size(child0(t));\n    \
    \                    if (nxt_s = op(s, value(t)); f(nxt_s)) {\n              \
    \              s = std::move(nxt_s);\n                            r += 1;\n  \
    \                          t = child1(t);\n                        } else break;\n\
    \                    } else {\n                        t = child0(t);\n      \
    \              }\n                }\n                return { r, s };\n      \
    \      }\n            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> min_left(inner_node_pointer t, const Predicate& f, const value_type&\
    \ init_sum = e()) {\n                size_type l = safe_size(t);\n           \
    \     value_type s = init_sum;\n                while (t) {\n                \
    \    if (value_type nxt_s = op(safe_sum(child1(t)), s); f(nxt_s)) {\n        \
    \                s = std::move(nxt_s);\n                        l -= safe_size(child1(t));\n\
    \                        if (nxt_s = op(value(t), s); f(nxt_s)) {\n          \
    \                  s = std::move(nxt_s);\n                            l -= 1;\n\
    \                            t = child0(t);\n                        } else break;\n\
    \                    } else {\n                        t = child1(t);\n      \
    \              }\n                }\n                return { l, s };\n      \
    \      }\n\n            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n            static\
    \ void foreach(inner_node_pointer t, bool rev, const Func& f) {\n            \
    \    if (not t) return;\n                if (rev) {\n                    foreach(child1(t),\
    \ rev, f), f(const_key(t), const_value(t)), foreach(child0(t), rev, f);\n    \
    \            } else {\n                    foreach(child0(t), rev, f), f(const_key(t),\
    \ const_value(t)), foreach(child1(t), rev, f);\n                }\n          \
    \  }\n        };\n\n        struct OuterNode {\n            priority_type _priority;\n\
    \n            size_type _siz;\n            value_type _sum;\n\n            bool\
    \ _rev;\n            inner_node_pointer _inner_node;\n\n            outer_node_pointer\
    \ _ch[2]{ nullptr, nullptr };\n\n            OuterNode(inner_node_pointer inner_node,\
    \ bool rev = false) : _priority(random_priority()), _siz(inner_node::size(inner_node)),\
    \ _sum(inner_node::sum(inner_node)), _rev(rev), _inner_node(inner_node) {\n  \
    \              if (rev) _sum = toggle(std::move(_sum));\n            }\n\n   \
    \         static size_type& size(outer_node_pointer t) { return t->_siz; }\n \
    \           static size_type safe_size(outer_node_pointer t) { return t ? size(t)\
    \ : 0; }\n            static size_type inner_size(outer_node_pointer t) { return\
    \ inner_node::size(inner(t)); }\n\n            static value_type& sum(outer_node_pointer\
    \ t) { return t->_sum; }\n            static value_type safe_sum(outer_node_pointer\
    \ t) { return t ? sum(t) : e(); };\n            static value_type inner_sum(outer_node_pointer\
    \ t) {\n                value_type res = inner_node::sum(inner(t));\n        \
    \        return reversed(t) ? toggle(std::move(res)) : res;\n            }\n\n\
    \            static bool& reversed(outer_node_pointer t) { return t->_rev; }\n\
    \n            static priority_type& priority(outer_node_pointer t) { return t->_priority;\
    \ }\n\n            static outer_node_pointer& child0(outer_node_pointer t) { return\
    \ t->_ch[0]; }\n            static outer_node_pointer& child1(outer_node_pointer\
    \ t) { return t->_ch[1]; }\n            static outer_node_pointer set_child0(outer_node_pointer\
    \ t, outer_node_pointer ct) { return std::exchange(child0(t), ct); }\n       \
    \     static outer_node_pointer set_child1(outer_node_pointer t, outer_node_pointer\
    \ ct) { return std::exchange(child1(t), ct); }\n\n            static inner_node_pointer&\
    \ inner(outer_node_pointer t) { return t->_inner_node; }\n\n            static\
    \ outer_node_pointer update(outer_node_pointer t) { // t : not nullptr\n     \
    \           size(t) = safe_size(child0(t)) + safe_size(child1(t)) + inner_size(t);\n\
    \                sum(t) = op(op(safe_sum(child0(t)), inner_sum(t)), safe_sum(child1(t)));\n\
    \                return t;\n            }\n\n            static outer_node_pointer\
    \ alloc_node(inner_node_pointer inner_node, bool rev = false) {\n            \
    \    if (not inner_node) return nullptr;\n                if constexpr (use_32bit_pointer)\
    \ {\n                    return outer_node_pointer::alloc(inner_node, rev);\n\
    \                } else {\n                    return new outer_node(inner_node,\
    \ rev);\n                }\n            }\n            static void dealloc_node(outer_node_pointer\
    \ t) {\n                if (not t) return;\n                inner_node::dealloc_all(inner(t));\n\
    \                if constexpr (use_32bit_pointer) {\n                    outer_node_pointer::dealloc(t);\n\
    \                } else {\n                    delete t;\n                }\n\
    \            }\n            static void dealloc_all(outer_node_pointer t) {\n\
    \                if (not t) return;\n                dealloc_all(child0(t));\n\
    \                dealloc_all(child1(t));\n                dealloc_node(t);\n \
    \           }\n\n            static outer_node_pointer build(const std::vector<std::pair<key_type,\
    \ value_type>>& dat) {\n                const size_t n = dat.size();\n\n     \
    \           if (n == 0) return nullptr;\n\n                std::vector<priority_type>\
    \ priorities(n);\n                std::generate(priorities.begin(), priorities.end(),\
    \ random_priority);\n                std::make_heap(priorities.begin(), priorities.end());\n\
    \n                std::vector<outer_node_pointer> nodes(n);\n\n              \
    \  size_t fpow2 = 1;\n                while ((fpow2 << 1) <= n) fpow2 <<= 1; //\
    \ 2^floor(log_2(n))\n\n                if constexpr (use_32bit_pointer) {\n  \
    \                  inner_node_pointer::reserve(n);\n                    outer_node_pointer::reserve(n);\n\
    \                }\n\n                for (size_t bbst_index = 1, skipped = 0;\
    \ bbst_index < 2 * fpow2; ++bbst_index) {\n                    size_t heap_index\
    \ = (fpow2 | ((bbst_index - 1) >> 1)) >> __builtin_ctz(bbst_index);\n        \
    \            if (heap_index <= n) {\n                        size_t index = bbst_index\
    \ - skipped;\n                        inner_node_pointer inner = inner_node::alloc_node(dat[index\
    \ - 1].first, dat[index - 1].second);\n                        nodes[heap_index\
    \ - 1] = outer_node::alloc_node(inner);\n                        inner_node::priority(inner)\
    \ = priorities[heap_index - 1];\n                    } else {\n              \
    \          ++skipped;\n                    }\n                }\n            \
    \    for (size_t i = fpow2 - 1; i >= 1; --i) {\n                    size_t li\
    \ = 2 * i, ri = 2 * i + 1;\n                    if (li <= n) set_child0(nodes[i\
    \ - 1], nodes[li - 1]);\n                    if (ri <= n) set_child1(nodes[i -\
    \ 1], nodes[ri - 1]);\n                    update(nodes[i - 1]);\n           \
    \     }\n                return nodes[0];\n            }\n\n            static\
    \ value_type get_at(outer_node_pointer t, size_type k) {\n                assert(0\
    \ <= k and k < safe_size(t));\n                while (true) {\n              \
    \      if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               size_type k_inner = k - lsiz;\n                            return\
    \ inner_node::get_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t)) -\
    \ k_inner - 1 : k_inner);\n                        }\n                       \
    \ t = child0(t);\n                    } else {\n                        t = child1(t);\n\
    \                        k -= lsiz + msiz;\n                    }\n          \
    \      }\n            }\n            static value_type set_at(outer_node_pointer\
    \ t, size_type k, const value_type& val) {\n                assert(0 <= k and\
    \ k < safe_size(t));\n                static std::vector<outer_node_pointer> stack{};\n\
    \                while (true) {\n                    stack.push_back(t);\n   \
    \                 if (const size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               size_type k_inner = k - lsiz;\n                            value_type\
    \ old_val = inner_node::set_at(inner(t), reversed(t) ? inner_node::safe_size(inner(t))\
    \ - k_inner - 1 : k_inner, val);\n                            while (stack.size())\
    \ update(stack.back()), stack.pop_back();\n                            return\
    \ old_val;\n                        }\n                        t = child0(t);\n\
    \                    } else {\n                        t = child1(t);\n      \
    \                  k -= lsiz + msiz;\n                    }\n                }\n\
    \            }\n            static value_type prod(outer_node_pointer t, size_type\
    \ l, size_type r) {\n                if (not t) return e();\n                if\
    \ (l <= 0 and r >= size(t)) return sum(t);\n                size_type lsiz = safe_size(child0(t));\n\
    \                if (r <= lsiz) return prod(child0(t), l, r);\n              \
    \  size_type msiz = inner_size(t);\n                if (l >= lsiz + msiz) return\
    \ prod(child1(t), l - (lsiz + msiz), r - (lsiz + msiz));\n                value_type\
    \ sum_l = prod(child0(t), l, r);\n                value_type sum_r = prod(child1(t),\
    \ l - (lsiz + msiz), r - (lsiz + msiz));\n                if (reversed(t)) {\n\
    \                    value_type sum_m = inner_node::prod_at_range(inner(t), msiz\
    \ - (r - lsiz), msiz - (l - lsiz));\n                    return op(op(sum_l, toggle(sum_m)),\
    \ sum_r);\n                } else {\n                    value_type sum_m = inner_node::prod_at_range(inner(t),\
    \ l - lsiz, r - lsiz);\n                    return op(op(sum_l, sum_m), sum_r);\n\
    \                }\n            }\n\n            static std::pair<outer_node_pointer,\
    \ outer_node_pointer> split_at(outer_node_pointer t, size_type k) {\n        \
    \        if (k == 0) return { nullptr, t };\n                if (k == safe_size(t))\
    \ return { t, nullptr };\n\n                static std::vector<outer_node_pointer>\
    \ lp{}, rp{};\n\n                while (true) {\n                    if (const\
    \ size_type lsiz = safe_size(child0(t)), msiz = inner_node::safe_size(inner(t));\
    \ k < lsiz + msiz) {\n                        if (k >= lsiz) {\n             \
    \               outer_node_pointer tl, tr;\n                            if (reversed(t))\
    \ {\n                                size_type k_inner = inner_node::safe_size(inner(t))\
    \ - (k - lsiz);\n                                auto [inner_tr, inner_tl] = inner_node::split_at(inner(t),\
    \ k_inner);\n                                tl = outer_node::alloc_node(inner_tl,\
    \ true);\n                                tr = outer_node::alloc_node(inner_tr,\
    \ true);\n                            } else {\n                             \
    \   size_type k_inner = k - lsiz;\n                                auto [inner_tl,\
    \ inner_tr] = inner_node::split_at(inner(t), k_inner);\n                     \
    \           tl = outer_node::alloc_node(inner_tl, false);\n                  \
    \              tr = outer_node::alloc_node(inner_tr, false);\n               \
    \             }\n\n                            tl = concat(std::exchange(child0(t),\
    \ nullptr), tl);\n                            tr = concat(tr, std::exchange(child1(t),\
    \ nullptr));\n\n                            inner(t) = nullptr;\n            \
    \                dealloc_node(t);\n\n                            if (rp.size())\
    \ set_child0(rp.back(), tr);\n                            if (lp.size()) set_child1(lp.back(),\
    \ tl);\n\n                            outer_node_pointer lt = tl, rt = tr;\n\n\
    \                            while (lp.size()) update(lt = lp.back()), lp.pop_back();\n\
    \                            while (rp.size()) update(rt = rp.back()), rp.pop_back();\n\
    \n                            return { lt, rt };\n                        }\n\
    \                        if (rp.size()) set_child0(rp.back(), t);\n          \
    \              rp.push_back(t);\n                        t = child0(t);\n    \
    \                } else {\n                        if (lp.size()) set_child1(lp.back(),\
    \ t);\n                        lp.push_back(t);\n                        t = child1(t);\n\
    \                        k -= lsiz + msiz;\n                    }\n          \
    \      }\n            }\n            static std::tuple<outer_node_pointer, outer_node_pointer,\
    \ outer_node_pointer> split_at_range(outer_node_pointer t, size_type l, size_type\
    \ r) {\n                auto [tlm, tr] = split_at(t, r);\n                auto\
    \ [tl, tm] = split_at(tlm, l);\n                return { tl, tm, tr };\n     \
    \       }\n\n            static outer_node_pointer concat(outer_node_pointer tl,\
    \ outer_node_pointer tr) {\n                if (not tl) return tr;\n         \
    \       if (not tr) return tl;\n                if (priority(tl) < priority(tr))\
    \ {\n                    set_child0(tr, concat(tl, child0(tr)));\n           \
    \         return update(tr);\n                } else {\n                    set_child1(tl,\
    \ concat(child1(tl), tr));\n                    return update(tl);\n         \
    \       }\n            }\n            static outer_node_pointer concat(outer_node_pointer\
    \ tl, outer_node_pointer tm, outer_node_pointer tr) {\n                return\
    \ concat(concat(tl, tm), tr);\n            }\n\n            static inner_node_pointer\
    \ merge_all(outer_node_pointer t) {\n                if (not t) return nullptr;\n\
    \                inner_node_pointer res = inner_node::merge(inner_node::merge(merge_all(child0(t)),\
    \ inner(t)), merge_all(child1(t)));\n                inner(t) = nullptr;\n   \
    \             dealloc_node(t);\n                return res;\n            }\n\n\
    \            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> max_right_prefix(outer_node_pointer t, const Predicate& f) {\n \
    \               size_type r = 0;\n                value_type s = e();\n      \
    \          while (t) {\n                    if (value_type nxt_s = op(s, safe_sum(child0(t)));\
    \ f(nxt_s)) {\n                        s = std::move(nxt_s);\n               \
    \         r += safe_size(child0(t));\n                        if (nxt_s = op(s,\
    \ inner_sum(t)); f(nxt_s)) {\n                            s = std::move(nxt_s);\n\
    \                            r += inner_size(t);\n                           \
    \ t = child1(t);\n                        } else {\n                         \
    \   size_type r_inner;\n                            std::tie(r_inner, s) = inner_node::max_right(inner(t),\
    \ f, s);\n                            r += r_inner;\n                        \
    \    break;\n                        }\n                    } else {\n       \
    \                 t = child0(t);\n                    }\n                }\n \
    \               return { r, s };\n            }\n            template <typename\
    \ Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>,\
    \ std::nullptr_t> = nullptr>\n            static std::tuple<outer_node_pointer,\
    \ size_type, value_type> max_right(outer_node_pointer t, size_type l, const Predicate&\
    \ f) {\n                auto [tl, tr] = split_at(t, l);\n                auto\
    \ [r, s] = max_right_prefix(tr, f);\n                return { concat(tl, tr),\
    \ l + r, s };\n            }\n\n            template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n            static std::pair<size_type,\
    \ value_type> min_left_suffix(outer_node_pointer t, const Predicate& f) {\n  \
    \              size_type l = safe_size(t);\n                value_type s = e();\n\
    \                while (t) {\n                    if (value_type nxt_s = op(safe_sum(child1(t)),\
    \ s); f(nxt_s)) {\n                        s = std::move(nxt_s);\n           \
    \             l -= safe_size(child1(t));\n                        if (nxt_s =\
    \ op(inner_sum(t), s); f(nxt_s)) {\n                            s = std::move(nxt_s);\n\
    \                            l -= inner_size(t);\n                           \
    \ t = child0(t);\n                        } else {\n                         \
    \   size_type l_inner;\n                            std::tie(l_inner, s) = inner_node::min_left(inner(t),\
    \ f, s);\n                            l -= inner_size(t) - l_inner;\n        \
    \                    break;\n                        }\n                    }\
    \ else {\n                        t = child1(t);\n                    }\n    \
    \            }\n                return { l, s };\n            }\n            template\
    \ <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate,\
    \ value_type>, std::nullptr_t> = nullptr>\n            static std::tuple<outer_node_pointer,\
    \ size_type, value_type> min_left(outer_node_pointer t, size_type r, const Predicate&\
    \ f) {\n                auto [tl, tr] = split_at(t, r);\n                auto\
    \ [l, s] = min_left_suffix(tl, f);\n                return { concat(tl, tr), l,\
    \ s };\n            }\n\n            template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n            static\
    \ void foreach(outer_node_pointer t, bool rev, const Func& f) {\n            \
    \    if (not t) return;\n                if (rev) {\n                    foreach(child1(t),\
    \ rev, f);\n                    inner_node::foreach(inner(t), not reversed(t),\
    \ f);\n                    foreach(child0(t), rev, f);\n                } else\
    \ {\n                    foreach(child0(t), rev, f);\n                    inner_node::foreach(inner(t),\
    \ reversed(t), f);\n                    foreach(child1(t), rev, f);\n        \
    \        }\n            }\n        };\n\n        outer_node_pointer _root;\n \
    \       SortableSegmentTree(outer_node_pointer root) : _root(root) {}\n    public:\n\
    \        SortableSegmentTree() : SortableSegmentTree(nullptr) {}\n        SortableSegmentTree(const\
    \ std::vector<std::pair<key_type, value_type>>& dat) : SortableSegmentTree(outer_node::build(dat))\
    \ {}\n\n        ~SortableSegmentTree() {\n            outer_node::dealloc_all(_root);\n\
    \        }\n\n        size_type size() {\n            return outer_node::safe_size(_root);\n\
    \        }\n\n        auto operator[](size_type k) {\n            struct proxy\
    \ {\n                outer_node_pointer root;\n                size_type k;\n\
    \                operator value_type()&& { return outer_node::get_at(root, k);\
    \ }\n                value_type operator=(const value_type& val)&& { return outer_node::set_at(root,\
    \ k, val), val; }\n            };\n            return proxy{ _root, k };\n   \
    \     }\n        value_type get(size_type k) {\n            assert(0 <= k and\
    \ k < size());\n            return outer_node::get_at(_root, k);\n        }\n\
    \        // returns old value\n        value_type set_value(size_type k, const\
    \ value_type& val) {\n            assert(0 <= k and k < size());\n           \
    \ return outer_node::set_at(_root, k, val);\n        }\n        // returns old\
    \ {key, value}\n        std::pair<key_type, value_type> set_key_value(size_type\
    \ i, const key_type& key, const value_type& val) {\n            assert(0 <= i\
    \ and i < size());\n            auto [tl, tm, tr] = outer_node::split_at_range(_root,\
    \ i, i + 1);\n            inner_node_pointer tm_inner = outer_node::inner(tm);\n\
    \            std::pair<key_type, value_type> res = inner_node::set(tm_inner, key,\
    \ val);\n            inner_node::update(tm_inner);\n            _root = outer_node::concat(tl,\
    \ outer_node::update(tm), tr);\n            return res;\n        }\n\n       \
    \ void insert(size_type i, const key_type& key, const value_type& val) {\n   \
    \         assert(0 <= i and i <= size());\n            auto [tl, tr] = outer_node::split_at(_root,\
    \ i);\n            auto tm = outer_node::alloc_node(inner_node::alloc_node(key,\
    \ val));\n            _root = outer_node::concat(tl, tm, tr);\n        }\n   \
    \     void push_front(const key_type& key, const value_type& val) { insert(0,\
    \ key, val); }\n        void push_back(const key_type& key, const value_type&\
    \ val) { insert(size(), key, val); }\n\n        std::pair<key_type, value_type>\
    \ erase(size_type i) {\n            assert(0 <= i and i < size());\n         \
    \   auto [tl, tm, tr] = outer_node::split_at_range(_root, i, i + 1);\n       \
    \     _root = outer_node::concat(tl, tr);\n            inner_node_pointer tm_inner\
    \ = outer_node::inner(tm);\n            std::pair<key_type, value_type> res {\
    \ std::move(inner_node::key(tm_inner)), std::move(inner_node::value(tm_inner))\
    \ };\n            outer_node::dealloc_node(tm);\n            return res;\n   \
    \     }\n        std::pair<key_type, value_type> pop_front() { erase(0); }\n \
    \       std::pair<key_type, value_type> pop_back() { erase(size() - 1); }\n\n\
    \        SortableSegmentTree split(size_type i) {\n            assert(0 <= i and\
    \ i <= size());\n            auto [root_l, root_r] = outer_node::split_at(_root,\
    \ i);\n            _root = root_l;\n            return SortableSegmentTree{ root_r\
    \ };\n        }\n        void concat(SortableSegmentTree tr) {\n            _root\
    \ = outer_node::concat(_root, tr->_root);\n        }\n\n        value_type prod(size_type\
    \ l, size_type r) {\n            assert(0 <= l and l <= r and r <= size());\n\
    \            if (l == r) return e();\n            if (r - l == 1) return (*this)[l];\n\
    \            return outer_node::prod(_root, l, r);\n        }\n\n        enum\
    \ struct SortingPolicy { ascending, descending };\n        void sort(size_type\
    \ l, size_type r, SortingPolicy policy = SortingPolicy::ascending) {\n       \
    \     assert(0 <= l and l <= r and r <= size());\n            if (l == r) return;\n\
    \            auto [tl, tm, tr] = outer_node::split_at_range(_root, l, r);\n  \
    \          _root = outer_node::concat(tl, outer_node::alloc_node(outer_node::merge_all(tm),\
    \ policy == SortingPolicy::descending), tr);\n        }\n        void sort_asc(size_type\
    \ l, size_type r) { sort(l, r, SortingPolicy::ascending); }\n        void sort_dsc(size_type\
    \ l, size_type r) { sort(l, r, SortingPolicy::descending); }\n\n        // returns\
    \ { r := max{ r' | f(prod(l, r')) = true }, prod(l, r) }\n        template <typename\
    \ Predicate, std::enable_if_t<std::is_invocable_r_v<bool, Predicate, value_type>,\
    \ std::nullptr_t> = nullptr>\n        std::pair<size_type, value_type> max_right(size_type\
    \ l, const Predicate& f) {\n            assert(0 <= l and l <= size());\n    \
    \        assert(f(e()));\n            auto [new_root, r, s] = outer_node::max_right(_root,\
    \ l, f);\n            _root = new_root;\n            return { r, s };\n      \
    \  }\n        // returns { l := min{ l' | f(prod(l', r)) = true }, prod(l, r)\
    \ }\n        template <typename Predicate, std::enable_if_t<std::is_invocable_r_v<bool,\
    \ Predicate, value_type>, std::nullptr_t> = nullptr>\n        std::pair<size_type,\
    \ value_type> min_left(size_type r, const Predicate& f) {\n            assert(0\
    \ <= r and r <= size());\n            assert(f(e()));\n            auto [new_root,\
    \ l, s] = outer_node::min_left(_root, r, f);\n            _root = new_root;\n\
    \            return { l, s };\n        }\n\n        template <typename Func, std::enable_if_t<std::is_invocable_r_v<void,\
    \ Func, key_type, value_type>, std::nullptr_t> = nullptr>\n        void foreach(const\
    \ Func& f, bool reversed = false) {\n            outer_node::foreach(_root, reversed,\
    \ f);\n        }\n        std::vector<key_type> dump_keys() {\n            std::vector<key_type>\
    \ res(size());\n            auto it = res.begin();\n            foreach([&it](const\
    \ key_type& key, const value_type&) { *it++ = key; });\n            return res;\n\
    \        }\n        std::vector<value_type> dump_values() {\n            std::vector<value_type>\
    \ res(size());\n            auto it = res.begin();\n            foreach([&it](const\
    \ key_type&, const value_type& val) { *it++ = val; });\n            return res;\n\
    \        }\n        std::vector<std::pair<key_type, value_type>> dump_entries()\
    \ {\n            std::vector<std::pair<key_type, value_type>> res(size());\n \
    \           auto it = res.begin();\n            foreach([&it](const key_type&\
    \ key, const value_type& val) { *it++ = std::pair{ key, val }; });\n         \
    \   return res;\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_SORTABLE_SEGTREE\n"
  dependsOn:
  - library/util/pointer_32bit.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/sortable_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-05-18 22:35:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/datastructure/segment_tree/sortable_segment_tree/abc237_g.test.cpp
  - test/src/datastructure/segment_tree/sortable_segment_tree/point_set_range_sort_range_composite.test.cpp
documentation_of: library/datastructure/segment_tree/sortable_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/segment_tree/sortable_segment_tree.hpp
- /library/library/datastructure/segment_tree/sortable_segment_tree.hpp.html
title: library/datastructure/segment_tree/sortable_segment_tree.hpp
---
