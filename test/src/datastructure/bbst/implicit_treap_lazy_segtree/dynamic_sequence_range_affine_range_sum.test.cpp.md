---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algebra/monoid/affine.hpp
    title: Affine
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#line 1 \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\n\n\n\
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
    \ suisen::internal::implicit_treap\n\n\n#line 5 \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T), typename F, T(*mapping)(F,\
    \ T), F(*composition)(F, F), F(*id)()>\n        struct RangeOperateRangeProductNode:\
    \ Node<T, RangeOperateRangeProductNode<T, op, e, toggle, F, mapping, composition,\
    \ id>> {\n            using base = Node<T, RangeOperateRangeProductNode<T, op,\
    \ e, toggle, F, mapping, composition, id>>;\n            using node_pointer =\
    \ typename base::node_pointer;\n            using value_type = typename base::value_type;\n\
    \n            value_type _sum;\n            F _laz;\n            RangeOperateRangeProductNode(const\
    \ value_type& val): base(val), _sum(val), _laz(id()) {}\n\n            // -----\
    \ override ----- //\n            static node_pointer update(node_pointer t) {\n\
    \                base::update(t);\n                prod_all(t) = op(op(safe_prod(base::child0(t)),\
    \ base::value(t)), safe_prod(base::child1(t)));\n                return t;\n \
    \           }\n            static void push(node_pointer t) {\n              \
    \  base::push(t);\n                F& laz = lazy(t);\n                apply_all(base::child0(t),\
    \ laz);\n                apply_all(base::child1(t), laz);\n                laz\
    \ = id();\n            }\n            static node_pointer reverse_all(node_pointer\
    \ t) {\n                if (t != base::null) {\n                    base::reversed(t)\
    \ ^= true;\n                    std::swap(base::child0(t), base::child1(t));\n\
    \                    value_type& sum = prod_all(t);\n                    sum =\
    \ toggle(sum);\n                }\n                return t;\n            }\n\n\
    \            // ----- new features ----- //\n            static value_type& prod_all(node_pointer\
    \ t) {\n                return base::node(t)._sum;\n            }\n          \
    \  static value_type safe_prod(node_pointer t) {\n                return t ==\
    \ base::null ? e() : prod_all(t);\n            }\n            static std::pair<node_pointer,\
    \ value_type> prod(node_pointer t, size_t l, size_t r) {\n                auto\
    \ [tl, tm, tr] = base::split(t, l, r);\n                value_type res = safe_prod(tm);\n\
    \                return { base::merge(tl, tm, tr), res };\n            }\n\n \
    \           static F& lazy(node_pointer t) {\n                return base::node(t)._laz;\n\
    \            }\n            static node_pointer apply_all(node_pointer t, const\
    \ F& f) {\n                if (t != base::null) {\n                    F& laz\
    \ = lazy(t);\n                    laz = composition(f, laz);\n               \
    \     value_type& val = base::value(t);\n                    val = mapping(f,\
    \ val);\n                    value_type& sum = prod_all(t);\n                \
    \    sum = mapping(f, sum);\n                }\n                return t;\n  \
    \          }\n            static node_pointer apply(node_pointer t, size_t l,\
    \ size_t r, const F& f) {\n                auto [tl, tm, tr] = base::split(t,\
    \ l, r);\n                return base::merge(tl, apply_all(tm, f), tr);\n    \
    \        }\n\n            template <typename Func>\n            static node_pointer\
    \ set(node_pointer t, size_t k, const Func& f) {\n                return base::set_update(t,\
    \ k, f);\n            }\n\n            template <typename Predicate>\n       \
    \     static uint32_t max_right(node_pointer t, const Predicate& f) {\n      \
    \          value_type sum = e();\n                assert(f(sum));\n\n        \
    \        uint32_t r = 0;\n                while (t != base::null) {\n        \
    \            push(t);\n\n                    node_pointer lch = base::child0(t);\n\
    \n                    value_type nxt_sum = op(sum, safe_prod(lch));\n        \
    \            if (f(nxt_sum)) {\n                        r += base::safe_size(lch);\n\
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
    \ T), F(*composition)(F, F), F(*id)()>\n    class DynamicLazySegmentTree {\n \
    \       using node_type = internal::implicit_treap::RangeOperateRangeProductNode<T,\
    \ op, e, toggle, F, mapping, composition, id>;\n        using node_pointer = typename\
    \ node_type::node_pointer;\n        using value_type = typename node_type::value_type;\n\
    \n        node_pointer _root;\n\n        struct node_pointer_construct {};\n \
    \       DynamicLazySegmentTree(node_pointer root, node_pointer_construct): _root(root)\
    \ {}\n\n    public:\n        DynamicLazySegmentTree(): _root(node_type::empty_node())\
    \ {}\n        explicit DynamicLazySegmentTree(size_t n, const value_type& fill_value\
    \ = {}): _root(node_type::build(n, fill_value)) {}\n        template <typename\
    \ U>\n        DynamicLazySegmentTree(const std::vector<U>& dat) : _root(node_type::build(dat.begin(),\
    \ dat.end())) {}\n\n        void free() {\n            node_type::delete_tree(_root);\n\
    \            _root = node_type::empty_node();\n        }\n        void clear()\
    \ {\n            free();\n        }\n\n        static void reserve(size_t capacity)\
    \ {\n            node_type::reserve(capacity);\n        }\n\n        bool empty()\
    \ const {\n            return node_type::empty(_root);\n        }\n        int\
    \ size() const {\n            return node_type::safe_size(_root);\n        }\n\
    \n        const value_type& operator[](size_t k) const {\n            return get(k);\n\
    \        }\n        const value_type& get(size_t k) const {\n            assert(k\
    \ < size_t(size()));\n            return node_type::get(_root, k);\n        }\n\
    \        const value_type& front() const {\n            return get(0);\n     \
    \   }\n        const value_type& back() const {\n            return get(size()\
    \ - 1);\n        }\n        void set(size_t k, const value_type& val) {\n    \
    \        assert(k < size_t(size()));\n            _root = node_type::set(_root,\
    \ k, [&](const value_type&) { return val; });\n        }\n        template <typename\
    \ Func>\n        void apply(size_t k, const Func& f) {\n            assert(k <\
    \ size_t(size()));\n            _root = node_type::set(_root, k, [&](const value_type&\
    \ val) { return f(val); });\n        }\n\n        value_type prod_all() const\
    \ {\n            return node_type::safe_prod(_root);\n        }\n        value_type\
    \ prod(size_t l, size_t r) {\n            value_type res;\n            std::tie(_root,\
    \ res) = node_type::prod(_root, l, r);\n            return res;\n        }\n\n\
    \        void apply_all(const F& f) {\n            _root = node_type::apply_all(_root,\
    \ f);\n        }\n        void apply(size_t l, size_t r, const F& f) {\n     \
    \       _root = node_type::apply(_root, l, r, f);\n        }\n\n        void insert(size_t\
    \ k, const value_type& val) {\n            assert(k <= size_t(size()));\n    \
    \        _root = node_type::insert(_root, k, val);\n        }\n        void push_front(const\
    \ value_type& val) {\n            _root = node_type::push_front(_root, val);\n\
    \        }\n        void push_back(const value_type& val) {\n            _root\
    \ = node_type::push_back(_root, val);\n        }\n\n        void erase(size_t\
    \ k) {\n            assert(k <= size_t(size()));\n            _root = node_type::erase(_root,\
    \ k);\n        }\n        void pop_front() {\n            _root = node_type::pop_front(_root);\n\
    \        }\n        void pop_back() {\n            _root = node_type::pop_back(_root);\n\
    \        }\n\n        DynamicLazySegmentTree split(size_t k) {\n            assert(k\
    \ <= size_t(size()));\n            node_pointer root_r;\n            std::tie(_root,\
    \ root_r) = node_type::split(_root, k);\n            return DynamicLazySegmentTree(root_r,\
    \ node_pointer_construct{});\n        }\n        void merge(DynamicLazySegmentTree\
    \ r) {\n            _root = node_type::merge(_root, r._root);\n        }\n\n \
    \       void rotate(size_t k) {\n            assert(k <= size_t(size()));\n  \
    \          _root = node_type::rotate(_root, k);\n        }\n\n        void reverse(size_t\
    \ l, size_t r) {\n            assert(l <= r and r <= size_t(size()));\n      \
    \      if (r - l >= 2) {\n                _root = node_type::reverse(_root, l,\
    \ r);\n            }\n        }\n        void reverse_all() {\n            _root\
    \ = node_type::reverse_all(_root);\n        }\n\n        std::vector<value_type>\
    \ dump() const {\n            return node_type::dump(_root);\n        }\n\n  \
    \      // Returns the first i s.t. f(A[i]) = true by binary search.\n        //\
    \ Requirement: f(A[i]) is monotonic.\n        template <typename Predicate>\n\
    \        int binary_search_find_first(const Predicate& f) const {\n          \
    \  return node_type::binary_search(_root, f);\n        }\n\n        // Returns\
    \ max{ r | f(op(A[l], ..., A[r-1])) = true }\n        template <typename Predicate>\n\
    \        int max_right(size_t l, const Predicate& f) {\n            size_t res;\n\
    \            std::tie(_root, res) = node_type::max_right(_root, l, f);\n     \
    \       return res;\n        }\n        // Returns min{ l | f(op(A[l], ..., A[r-1]))\
    \ = true }\n        template <typename Predicate>\n        int min_left(size_t\
    \ r, const Predicate& f) {\n            size_t res;\n            std::tie(_root,\
    \ res) = node_type::min_left(_root, r, f);\n            return res;\n        }\n\
    \n        auto begin() {\n            return node_type::begin(_root);\n      \
    \  }\n        auto end() {\n            return node_type::end(_root);\n      \
    \  }\n        auto kth_iterator(size_t k) {\n            return node_type::kth_iterator(_root,\
    \ k);\n        }\n    };\n} // namespace suisen\n\n\n\n#line 1 \"library/algebra/monoid/affine.hpp\"\
    \n\n\n\n#line 6 \"library/algebra/monoid/affine.hpp\"\n\nnamespace suisen {\n\
    \    template <typename T>\n    struct Affine {\n        T a, b;\n        Affine(const\
    \ T &a = 1, const T &b = 0) : a(a), b(b) {}\n\n        static Affine<T> id() {\
    \ return Affine<T>{}; }\n        static Affine<T> compose(const Affine<T>& f,\
    \ const Affine<T>& g) { return f.compose(g); }\n\n        Affine<T> compose(const\
    \ Affine<T>& g) const { return { a * g.a, affine(g.b) }; }\n\n        template\
    \ <typename U = T>\n        U affine(const T &x) const { return U(a) * x + b;\
    \ }\n        T operator()(const T &x) const { return affine<T>(x); }\n\n     \
    \   Affine<T> operator+() const { return *this; }\n        Affine<T> operator-()\
    \ const { return { -a, -b }; }\n\n        Affine<T>& operator++() { ++b; return\
    \ *this; }\n        Affine<T>& operator--() { --b; return *this; }\n        Affine<T>\
    \ operator++(int) { Affine<T> f(*this); ++(*this); return f; }\n        Affine<T>\
    \ operator--(int) { Affine<T> f(*this); --(*this); return f; }\n\n        Affine<T>&\
    \ operator+=(const T& c) { b += c; return *this; }\n        Affine<T>& operator-=(const\
    \ T& c) { b -= c; return *this; }\n        friend Affine<T> operator+(Affine<T>\
    \ f, const T &c) { f += c; return f; }\n        friend Affine<T> operator-(Affine<T>\
    \ f, const T &c) { f -= c; return f; }\n\n        Affine<T>& operator+=(const\
    \ Affine<T> &g) { a += g.a, b += g.b; return *this; }\n        Affine<T>& operator-=(const\
    \ Affine<T> &g) { a -= g.a, b -= g.b; return *this; }\n        friend Affine<T>\
    \ operator+(Affine<T> f, const Affine<T> &g) { f += g; return f; }\n        friend\
    \ Affine<T> operator-(Affine<T> f, const Affine<T> &g) { f -= g; return f; }\n\
    \n        template <typename U = T, typename V = T>\n        operator std::pair<U,\
    \ V>() { return std::pair<U, V>{ a, b }; }\n        template <typename U = T,\
    \ typename V = T>\n        operator std::tuple<U, V>() { return std::tuple<U,\
    \ V>{ a, b }; }\n\n        friend std::istream& operator<<(std::istream& in, Affine<T>\
    \ &f) { return in >> f.a >> f.b; }\n        friend std::ostream& operator>>(std::ostream&\
    \ out, const Affine<T> &f) { return out << f.a << ' ' << f.b; }\n    };\n} //\
    \ namespace suisen\n\n\n#line 20 \"test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n\nstruct S {\n    mint sum;\n    int len;\n};\nusing F = suisen::Affine<mint>;\n\
    \nS op(S x, S y) {\n    return { x.sum + y.sum, x.len + y.len };\n}\nS e() {\n\
    \    return { 0, 0 };\n}\nS toggle(S x) {\n    return x;\n}\nS mapping(F f, S\
    \ x) {\n    return { f.a * x.sum + f.b * x.len, x.len };\n}\nF composition(F f,\
    \ F g) {\n    return f.compose(g);\n}\nF id() {\n    return F::id();\n}\n\nusing\
    \ Sequence = suisen::DynamicLazySegmentTree<S, op, e, toggle, F, mapping, composition,\
    \ id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S> init(n, S { 0,\
    \ 1 });\n    for (int i = 0; i < n; ++i) {\n        std::cin >> init[i].sum;\n\
    \    }\n\n    Sequence seq(init);\n    for (int qid = 0; qid < q; ++qid) {\n \
    \       int qtype;\n        std::cin >> qtype;\n\n        if (qtype == 0) {\n\
    \            int i;\n            mint x;\n            std::cin >> i >> x;\n  \
    \          seq.insert(i, { x, 1 });\n        } else if (qtype == 1) {\n      \
    \      int i;\n            std::cin >> i;\n            seq.erase(i);\n       \
    \ } else if (qtype == 2) {\n            int l, r;\n            std::cin >> l >>\
    \ r;\n            seq.reverse(l, r);\n        } else if (qtype == 3) {\n     \
    \       int l, r;\n            mint b, c;\n            std::cin >> l >> r >> b\
    \ >> c;\n            seq.apply(l, r, F { b, c });\n        } else {\n        \
    \    int l, r;\n            std::cin >> l >> r;\n            std::cout << seq.prod(l,\
    \ r).sum << '\\n';\n        }\n    }\n\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \nstd::istream& operator>>(std::istream& in, mint &a) {\n    long long e; in >>\
    \ e; a = e;\n    return in;\n}\n\nstd::ostream& operator<<(std::ostream& out,\
    \ const mint &a) {\n    out << a.val();\n    return out;\n}\n\n#include \"library/datastructure/bbst/implicit_treap_lazy_segtree.hpp\"\
    \n#include \"library/algebra/monoid/affine.hpp\"\n\nstruct S {\n    mint sum;\n\
    \    int len;\n};\nusing F = suisen::Affine<mint>;\n\nS op(S x, S y) {\n    return\
    \ { x.sum + y.sum, x.len + y.len };\n}\nS e() {\n    return { 0, 0 };\n}\nS toggle(S\
    \ x) {\n    return x;\n}\nS mapping(F f, S x) {\n    return { f.a * x.sum + f.b\
    \ * x.len, x.len };\n}\nF composition(F f, F g) {\n    return f.compose(g);\n\
    }\nF id() {\n    return F::id();\n}\n\nusing Sequence = suisen::DynamicLazySegmentTree<S,\
    \ op, e, toggle, F, mapping, composition, id>;\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<S>\
    \ init(n, S { 0, 1 });\n    for (int i = 0; i < n; ++i) {\n        std::cin >>\
    \ init[i].sum;\n    }\n\n    Sequence seq(init);\n    for (int qid = 0; qid <\
    \ q; ++qid) {\n        int qtype;\n        std::cin >> qtype;\n\n        if (qtype\
    \ == 0) {\n            int i;\n            mint x;\n            std::cin >> i\
    \ >> x;\n            seq.insert(i, { x, 1 });\n        } else if (qtype == 1)\
    \ {\n            int i;\n            std::cin >> i;\n            seq.erase(i);\n\
    \        } else if (qtype == 2) {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            seq.reverse(l, r);\n        } else if (qtype == 3) {\n\
    \            int l, r;\n            mint b, c;\n            std::cin >> l >> r\
    \ >> b >> c;\n            seq.apply(l, r, F { b, c });\n        } else {\n   \
    \         int l, r;\n            std::cin >> l >> r;\n            std::cout <<\
    \ seq.prod(l, r).sum << '\\n';\n        }\n    }\n\n}"
  dependsOn:
  - library/datastructure/bbst/implicit_treap_lazy_segtree.hpp
  - library/datastructure/bbst/implicit_treap_base.hpp
  - library/algebra/monoid/affine.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/src/datastructure/bbst/implicit_treap_lazy_segtree/dynamic_sequence_range_affine_range_sum.test.cpp
---
