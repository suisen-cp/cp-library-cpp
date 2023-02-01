---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_base.hpp
    title: Implicit Treap Base
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_segtree.hpp
    title: Implicit Treap Segtree
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
  bundledCode: "#line 1 \"test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#line 1 \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\
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
    \ suisen::internal::implicit_treap\n\n\n#line 5 \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\
    \n\nnamespace suisen {\n    namespace internal::implicit_treap {\n        template\
    \ <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n        struct RangeProductNode:\
    \ Node<T, RangeProductNode<T, op, e, toggle>> {\n            using base = Node<T,\
    \ RangeProductNode<T, op, e, toggle>>;\n            using node_pointer = typename\
    \ base::node_pointer;\n            using value_type = typename base::value_type;\n\
    \n            value_type _sum;\n            RangeProductNode(const value_type&\
    \ val): base(val), _sum(val) {}\n\n            // ----- override ----- //\n  \
    \          static node_pointer update(node_pointer t) {\n                base::update(t);\n\
    \                prod_all(t) = op(op(safe_prod(base::child0(t)), base::value(t)),\
    \ safe_prod(base::child1(t)));\n                return t;\n            }\n   \
    \         static node_pointer reverse_all(node_pointer t) {\n                if\
    \ (t != base::null) {\n                    base::reversed(t) ^= true;\n      \
    \              std::swap(base::child0(t), base::child1(t));\n                \
    \    value_type& sum = prod_all(t);\n                    sum = toggle(sum);\n\
    \                }\n                return t;\n            }\n\n            //\
    \ ----- new features ----- //\n            static value_type& prod_all(node_pointer\
    \ t) {\n                return base::node(t)._sum;\n            }\n          \
    \  static value_type safe_prod(node_pointer t) {\n                return t ==\
    \ base::null ? e() : prod_all(t);\n            }\n            static std::pair<node_pointer,\
    \ value_type> prod(node_pointer t, size_t l, size_t r) {\n                auto\
    \ [tl, tm, tr] = base::split(t, l, r);\n                value_type res = safe_prod(tm);\n\
    \                return { base::merge(tl, tm, tr), res };\n            }\n   \
    \         template <typename Func>\n            static node_pointer set(node_pointer\
    \ t, size_t k, const Func& f) {\n                return base::set_update(t, k,\
    \ f);\n            }\n\n            template <typename Predicate>\n          \
    \  static uint32_t max_right(node_pointer t, const Predicate& f) {\n         \
    \       value_type sum = e();\n                assert(f(sum));\n\n           \
    \     uint32_t r = 0;\n                while (t != base::null) {\n           \
    \         base::push(t);\n\n                    node_pointer lch = base::child0(t);\n\
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
    \ base::null) {\n                    base::push(t);\n\n                    node_pointer\
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
    \    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n    class DynamicSegmentTree\
    \ {\n        using node_type = internal::implicit_treap::RangeProductNode<T, op,\
    \ e, toggle>;\n        using node_pointer = typename node_type::node_pointer;\n\
    \        using value_type = typename node_type::value_type;\n\n        node_pointer\
    \ _root;\n\n        struct node_pointer_construct {};\n        DynamicSegmentTree(node_pointer\
    \ root, node_pointer_construct): _root(root) {}\n\n    public:\n        DynamicSegmentTree():\
    \ _root(node_type::empty_node()) {}\n        explicit DynamicSegmentTree(size_t\
    \ n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value))\
    \ {}\n        template <typename U>\n        DynamicSegmentTree(const std::vector<U>&\
    \ dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n        void free()\
    \ {\n            node_type::delete_tree(_root);\n            _root = node_type::empty_node();\n\
    \        }\n        void clear() {\n            free();\n        }\n\n       \
    \ static void reserve(size_t capacity) {\n            node_type::reserve(capacity);\n\
    \        }\n\n        bool empty() const {\n            return node_type::empty(_root);\n\
    \        }\n        int size() const {\n            return node_type::safe_size(_root);\n\
    \        }\n\n        const value_type& operator[](size_t k) const {\n       \
    \     return get(k);\n        }\n        const value_type& get(size_t k) const\
    \ {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        const value_type& front() const {\n            return\
    \ get(0);\n        }\n        const value_type& back() const {\n            return\
    \ get(size() - 1);\n        }\n        void set(size_t k, const value_type& val)\
    \ {\n            assert(k < size_t(size()));\n            _root = node_type::set(_root,\
    \ k, [&](const value_type&) { return val; });\n        }\n        template <typename\
    \ Func>\n        void apply(size_t k, const Func& f) {\n            assert(k <\
    \ size_t(size()));\n            _root = node_type::set(_root, k, [&](const value_type&\
    \ val) { return f(val); });\n        }\n\n        value_type prod_all() const\
    \ {\n            return node_type::safe_prod(_root);\n        }\n        value_type\
    \ prod(size_t l, size_t r) {\n            value_type res;\n            std::tie(_root,\
    \ res) = node_type::prod(_root, l, r);\n            return res;\n        }\n\n\
    \        void insert(size_t k, const value_type& val) {\n            assert(k\
    \ <= size_t(size()));\n            _root = node_type::insert(_root, k, val);\n\
    \        }\n        void push_front(const value_type& val) {\n            _root\
    \ = node_type::push_front(_root, val);\n        }\n        void push_back(const\
    \ value_type& val) {\n            _root = node_type::push_back(_root, val);\n\
    \        }\n\n        void erase(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::erase(_root, k);\n        }\n        void pop_front()\
    \ {\n            _root = node_type::pop_front(_root);\n        }\n        void\
    \ pop_back() {\n            _root = node_type::pop_back(_root);\n        }\n\n\
    \        DynamicSegmentTree split(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            node_pointer root_r;\n            std::tie(_root, root_r) = node_type::split(_root,\
    \ k);\n            return DynamicSegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        void merge(DynamicSegmentTree r) {\n            _root = node_type::merge(_root,\
    \ r._root);\n        }\n\n        void rotate(size_t k) {\n            assert(k\
    \ <= size_t(size()));\n            _root = node_type::rotate(_root, k);\n    \
    \    }\n\n        void reverse(size_t l, size_t r) {\n            assert(l <=\
    \ r and r <= size_t(size()));\n            if (r - l >= 2) {\n               \
    \ _root = node_type::reverse(_root, l, r);\n            }\n        }\n       \
    \ void reverse_all() {\n            _root = node_type::reverse_all(_root);\n \
    \       }\n\n        std::vector<value_type> dump() const {\n            return\
    \ node_type::dump(_root);\n        }\n\n        // Returns the first i s.t. f(A[i])\
    \ = true by binary search.\n        // Requirement: f(A[i]) is monotonic.\n  \
    \      template <typename Predicate>\n        int binary_search_find_first(const\
    \ Predicate& f) const {\n            return node_type::binary_search(_root, f);\n\
    \        }\n\n        // Returns max{ r | f(op(A[l], ..., A[r-1])) = true }\n\
    \        template <typename Predicate>\n        int max_right(size_t l, const\
    \ Predicate& f) {\n            size_t res;\n            std::tie(_root, res) =\
    \ node_type::max_right(_root, l, f);\n            return res;\n        }\n   \
    \     // Returns min{ l | f(op(A[l], ..., A[r-1])) = true }\n        template\
    \ <typename Predicate>\n        int min_left(size_t r, const Predicate& f) {\n\
    \            size_t res;\n            std::tie(_root, res) = node_type::min_left(_root,\
    \ r, f);\n            return res;\n        }\n\n        auto begin() {\n     \
    \       return node_type::begin(_root);\n        }\n        auto end() {\n   \
    \         return node_type::end(_root);\n        }\n        auto kth_iterator(size_t\
    \ k) {\n            return node_type::kth_iterator(_root, k);\n        }\n   \
    \ };\n} // namespace suisen\n\n\n\n#line 16 \"test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)()>\nstruct NaiveSolutionForSegmentTree\
    \ {\n    NaiveSolutionForSegmentTree() = default;\n    NaiveSolutionForSegmentTree(const\
    \ std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const\
    \ {\n        assert(0 <= i and i < _n);\n        return _dat[i];\n    }\n    void\
    \ set(int i, const T& val) {\n        assert(0 <= i and i < _n);\n        _dat[i]\
    \ = val;\n    }\n\n    void insert(int i, const T& val) {\n        assert(0 <=\
    \ i and i <= _n);\n        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n\
    \    }\n    void erase(int i) {\n        assert(0 <= i and i < _n);\n        --_n;\n\
    \        _dat.erase(_dat.begin() + i);\n    }\n\n    T prod_all() const {\n  \
    \      return prod(0, _n);\n    }\n    T prod(int l, int r) const {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        T res = e();\n        for (int i = l;\
    \ i < r; ++i) res = op(res, _dat[i]);\n        return res;\n    }\n\n    void\
    \ reverse_all() {\n        reverse(0, _n);\n    }\n    void reverse(int l, int\
    \ r) {\n        assert(0 <= l and l <= r and r <= _n);\n        for (--r; l <\
    \ r; ++l, --r) {\n            std::swap(_dat[l], _dat[r]);\n        }\n    }\n\
    \n    void rotate(int i) {\n        assert(0 <= i and i <= _n);\n        std::rotate(_dat.begin(),\
    \ _dat.begin() + i, _dat.end());\n    }\n\n    template <typename Pred>\n    int\
    \ max_right(int l, Pred &&pred) const {\n        assert(0 <= l and l <= _n);\n\
    \        T sum = e();\n        for (int r = l; r < _n; ++r) {\n            T next_sum\
    \ = op(sum, _dat[r]);\n            if (not pred(next_sum)) return r;\n       \
    \     sum = std::move(next_sum);\n        }\n        return _n;\n    }\n\n   \
    \ template <typename Pred>\n    int min_left(int r, Pred &&pred) const {\n   \
    \     assert(0 <= r and r <= _n);\n        T sum = e();\n        for (int l =\
    \ r; l > 0; --l) {\n            T next_sum = op(_dat[l - 1], sum);\n         \
    \   if (not pred(next_sum)) return l;\n            sum = std::move(next_sum);\n\
    \        }\n        return 0;\n    }\n\n    std::vector<T> dump() { return _dat;\
    \ }\nprivate:\n    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Point Set\
    \ Range Sum\n */\n\nusing S = long long;\n\nS op(S x, S y) {\n    return x + y;\n\
    }\nS e() {\n    return 0;\n}\nS toggle(S x) {\n    return x;\n}\n\nusing Tree\
    \ = suisen::DynamicSegmentTree<S, op, e, toggle>;\nusing Naive = NaiveSolutionForSegmentTree<S,\
    \ op, e>;\n\n#line 118 \"test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp\"\
    \n\nconstexpr int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_insert\
    \ = 4;\nconstexpr int Q_erase = 5;\nconstexpr int Q_rotate = 10;\nconstexpr int\
    \ Q_prod = 2;\nconstexpr int Q_prod_all = 3;\nconstexpr int Q_reverse = 6;\nconstexpr\
    \ int Q_reverse_all = 7;\nconstexpr int Q_max_right = 8;\nconstexpr int Q_min_left\
    \ = 9;\nconstexpr int QueryTypeNum = 11;\n\nvoid test() {\n    int N = 3000, Q\
    \ = 3000, MAX_VAL = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\
    \n    std::vector<S> init(N);\n    for (int i = 0; i < N; ++i) init[i] = rng()\
    \ % MAX_VAL;\n    \n    Tree t1(init);\n    Naive t2(init);\n\n    for (int i\
    \ = 0; i < Q; ++i) {\n        const int query_type = rng() % QueryTypeNum;\n \
    \       if (query_type == Q_get) {\n            const int i = rng() % N;\n   \
    \         assert(t1.get(i) == t2.get(i));\n        } else if (query_type == Q_set)\
    \ {\n            const int i = rng() % N;\n            const S v = rng() % MAX_VAL;\n\
    \            t1.set(i, v);\n            t2.set(i, v);\n        } else if (query_type\
    \ == Q_insert) {\n            const int i = rng() % (N + 1);\n            const\
    \ S v = rng() % MAX_VAL;\n            t1.insert(i, v);\n            t2.insert(i,\
    \ v);\n            ++N;\n        } else if (query_type == Q_erase) {\n       \
    \     const int i = rng() % N;\n            t1.erase(i);\n            t2.erase(i);\n\
    \            --N;\n        } else if (query_type == Q_rotate) {\n            const\
    \ int i = rng() % (N + 1);\n            t1.rotate(i);\n            t2.rotate(i);\n\
    \        } else if (query_type == Q_prod) {\n            const int l = rng() %\
    \ (N + 1);\n            const int r = l + rng() % (N - l + 1);\n            assert(t1.prod(l,\
    \ r) == t2.prod(l, r));\n        } else if (query_type == Q_prod_all) {\n    \
    \        assert(t1.prod_all() == t2.prod_all());\n        } else if (query_type\
    \ == Q_reverse) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            t1.reverse(l, r);\n          \
    \  t2.reverse(l, r);\n        } else if (query_type == Q_reverse_all) {\n    \
    \        t1.reverse_all();\n            t2.reverse_all();\n        } else if (query_type\
    \ == Q_max_right) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            long long sum = std::max(0LL,\
    \ t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred\
    \ = [&](const S &x) { return x <= sum; };\n            assert(t1.max_right(l,\
    \ pred) == t2.max_right(l, pred));\n        } else if (query_type == Q_min_left)\
    \ {\n            const int l = rng() % (N + 1);\n            const int r = l +\
    \ rng() % (N - l + 1);\n            long long sum = std::max(0LL, t2.prod(l, r)\
    \ + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred = [&](const S\
    \ &x) { return x <= sum; };\n            assert(t1.min_left(r, pred) == t2.min_left(r,\
    \ pred));\n        } else {\n            assert(false);\n        }\n    }\n}\n\
    \nint main() {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstd::ostream& operator<<(std::ostream &out, const std::vector<T>\
    \ &a) {\n    out << '{';\n    for (auto &e : a) out << e << ',';\n    return out\
    \ << '}';\n}\n\n#include \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\
    \n\ntemplate <typename T, T(*op)(T, T), T(*e)()>\nstruct NaiveSolutionForSegmentTree\
    \ {\n    NaiveSolutionForSegmentTree() = default;\n    NaiveSolutionForSegmentTree(const\
    \ std::vector<T> &dat) : _n(dat.size()), _dat(dat) {}\n\n    T get(int i) const\
    \ {\n        assert(0 <= i and i < _n);\n        return _dat[i];\n    }\n    void\
    \ set(int i, const T& val) {\n        assert(0 <= i and i < _n);\n        _dat[i]\
    \ = val;\n    }\n\n    void insert(int i, const T& val) {\n        assert(0 <=\
    \ i and i <= _n);\n        ++_n;\n        _dat.insert(_dat.begin() + i, val);\n\
    \    }\n    void erase(int i) {\n        assert(0 <= i and i < _n);\n        --_n;\n\
    \        _dat.erase(_dat.begin() + i);\n    }\n\n    T prod_all() const {\n  \
    \      return prod(0, _n);\n    }\n    T prod(int l, int r) const {\n        assert(0\
    \ <= l and l <= r and r <= _n);\n        T res = e();\n        for (int i = l;\
    \ i < r; ++i) res = op(res, _dat[i]);\n        return res;\n    }\n\n    void\
    \ reverse_all() {\n        reverse(0, _n);\n    }\n    void reverse(int l, int\
    \ r) {\n        assert(0 <= l and l <= r and r <= _n);\n        for (--r; l <\
    \ r; ++l, --r) {\n            std::swap(_dat[l], _dat[r]);\n        }\n    }\n\
    \n    void rotate(int i) {\n        assert(0 <= i and i <= _n);\n        std::rotate(_dat.begin(),\
    \ _dat.begin() + i, _dat.end());\n    }\n\n    template <typename Pred>\n    int\
    \ max_right(int l, Pred &&pred) const {\n        assert(0 <= l and l <= _n);\n\
    \        T sum = e();\n        for (int r = l; r < _n; ++r) {\n            T next_sum\
    \ = op(sum, _dat[r]);\n            if (not pred(next_sum)) return r;\n       \
    \     sum = std::move(next_sum);\n        }\n        return _n;\n    }\n\n   \
    \ template <typename Pred>\n    int min_left(int r, Pred &&pred) const {\n   \
    \     assert(0 <= r and r <= _n);\n        T sum = e();\n        for (int l =\
    \ r; l > 0; --l) {\n            T next_sum = op(_dat[l - 1], sum);\n         \
    \   if (not pred(next_sum)) return l;\n            sum = std::move(next_sum);\n\
    \        }\n        return 0;\n    }\n\n    std::vector<T> dump() { return _dat;\
    \ }\nprivate:\n    int _n;\n    std::vector<T> _dat;\n};\n\n/**\n * Point Set\
    \ Range Sum\n */\n\nusing S = long long;\n\nS op(S x, S y) {\n    return x + y;\n\
    }\nS e() {\n    return 0;\n}\nS toggle(S x) {\n    return x;\n}\n\nusing Tree\
    \ = suisen::DynamicSegmentTree<S, op, e, toggle>;\nusing Naive = NaiveSolutionForSegmentTree<S,\
    \ op, e>;\n\n#include <random>\n#include <algorithm>\n\nconstexpr int Q_get =\
    \ 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_insert = 4;\nconstexpr int Q_erase\
    \ = 5;\nconstexpr int Q_rotate = 10;\nconstexpr int Q_prod = 2;\nconstexpr int\
    \ Q_prod_all = 3;\nconstexpr int Q_reverse = 6;\nconstexpr int Q_reverse_all =\
    \ 7;\nconstexpr int Q_max_right = 8;\nconstexpr int Q_min_left = 9;\nconstexpr\
    \ int QueryTypeNum = 11;\n\nvoid test() {\n    int N = 3000, Q = 3000, MAX_VAL\
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
    \ == Q_reverse) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            t1.reverse(l, r);\n          \
    \  t2.reverse(l, r);\n        } else if (query_type == Q_reverse_all) {\n    \
    \        t1.reverse_all();\n            t2.reverse_all();\n        } else if (query_type\
    \ == Q_max_right) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            long long sum = std::max(0LL,\
    \ t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred\
    \ = [&](const S &x) { return x <= sum; };\n            assert(t1.max_right(l,\
    \ pred) == t2.max_right(l, pred));\n        } else if (query_type == Q_min_left)\
    \ {\n            const int l = rng() % (N + 1);\n            const int r = l +\
    \ rng() % (N - l + 1);\n            long long sum = std::max(0LL, t2.prod(l, r)\
    \ + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred = [&](const S\
    \ &x) { return x <= sum; };\n            assert(t1.min_left(r, pred) == t2.min_left(r,\
    \ pred));\n        } else {\n            assert(false);\n        }\n    }\n}\n\
    \nint main() {\n    test();\n    std::cout << \"Hello World\" << std::endl;\n\
    \    return 0;\n}"
  dependsOn:
  - library/datastructure/bbst/implicit_treap_segtree.hpp
  - library/datastructure/bbst/implicit_treap_base.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-02-02 02:15:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
- /verify/test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp.html
title: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
---
