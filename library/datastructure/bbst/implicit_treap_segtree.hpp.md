---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/bbst/implicit_treap_base.hpp
    title: Implicit Treap Base
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\n\
    \n\n\n#line 1 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <string>\n#include <random>\n#include\
    \ <tuple>\n#include <vector>\n#include <utility>\n\nnamespace suisen::internal::implicit_treap\
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
    } // namespace suisen::internal::implicit_treap\n\n\n#line 5 \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\
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
    \n        node_pointer _root;\n\n        struct node_pointer_construct {};\n \
    \       DynamicSegmentTree(node_pointer root, node_pointer_construct): _root(root)\
    \ {}\n\n    public:\n        using value_type = typename node_type::value_type;\n\
    \n        DynamicSegmentTree(): _root(node_type::empty_node()) {}\n        explicit\
    \ DynamicSegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n,\
    \ fill_value)) {}\n        template <typename U>\n        DynamicSegmentTree(const\
    \ std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n\
    \        void free() {\n            node_type::delete_tree(_root);\n         \
    \   _root = node_type::empty_node();\n        }\n        void clear() { free();\
    \ }\n\n        static void reserve(size_t capacity) { node_type::reserve(capacity);\
    \ }\n\n        bool empty() const { return node_type::empty(_root); }\n      \
    \  int size() const { return node_type::safe_size(_root); }\n\n        const value_type&\
    \ operator[](size_t k) const { return get(k); }\n        const value_type& get(size_t\
    \ k) const {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        const value_type& front() const { return get(0); }\n\
    \        const value_type& back() const { return get(size() - 1); }\n\n      \
    \  void set(size_t k, const value_type& val) {\n            assert(k < size_t(size()));\n\
    \            _root = node_type::set(_root, k, [&](const value_type&) { return\
    \ val; });\n        }\n        template <typename Func>\n        void apply(size_t\
    \ k, const Func& f) {\n            assert(k < size_t(size()));\n            _root\
    \ = node_type::set(_root, k, [&](const value_type& val) { return f(val); });\n\
    \        }\n\n        value_type prod_all() const { return node_type::safe_prod(_root);\
    \ }\n        value_type prod(size_t l, size_t r) {\n            value_type res;\n\
    \            std::tie(_root, res) = node_type::prod(_root, l, r);\n          \
    \  return res;\n        }\n\n        void insert(size_t k, const value_type& val)\
    \ {\n            assert(k <= size_t(size()));\n            _root = node_type::insert(_root,\
    \ k, val);\n        }\n        void push_front(const value_type& val) { _root\
    \ = node_type::push_front(_root, val); }\n        void push_back(const value_type&\
    \ val) { _root = node_type::push_back(_root, val); }\n\n        void erase(size_t\
    \ k) {\n            assert(k <= size_t(size()));\n            _root = node_type::erase(_root,\
    \ k);\n        }\n        void pop_front() { _root = node_type::pop_front(_root);\
    \ }\n        void pop_back() { _root = node_type::pop_back(_root); }\n\n     \
    \   DynamicSegmentTree split(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            node_pointer root_r;\n            std::tie(_root, root_r) = node_type::split(_root,\
    \ k);\n            return DynamicSegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        void merge(DynamicSegmentTree r) { _root = node_type::merge(_root,\
    \ r._root); }\n\n        void rotate(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, k);\n        }\n\n        void reverse(size_t\
    \ l, size_t r) {\n            assert(l <= r and r <= size_t(size()));\n      \
    \      if (r - l >= 2) _root = node_type::reverse(_root, l, r);\n        }\n \
    \       void reverse_all() { _root = node_type::reverse_all(_root); }\n\n    \
    \    std::vector<value_type> dump() const { return node_type::dump(_root); }\n\
    \n        // Returns the first i s.t. f(A[i]) = true by binary search.\n     \
    \   // Requirement: f(A[i]) is monotonic.\n        template <typename Predicate>\n\
    \        int binary_search_find_first(const Predicate& f) const { return node_type::binary_search(_root,\
    \ f); }\n        // comp(T t, U u) = (t < u)\n        template <typename U, typename\
    \ Compare = std::less<>>\n        int lower_bound(const U& target, Compare comp\
    \ = {}) { return node_type::lower_bound(_root, target, comp); }\n        // comp(T\
    \ u, U t) = (u < t)\n        template <typename U, typename Compare = std::less<>>\n\
    \        int upper_bound(const U& target, Compare comp = {}) { return node_type::upper_bound(_root,\
    \ target, comp); }\n\n        // Returns max{ r | f(op(A[l], ..., A[r-1])) = true\
    \ }\n        template <typename Predicate>\n        int max_right(size_t l, const\
    \ Predicate& f) {\n            size_t res;\n            std::tie(_root, res) =\
    \ node_type::max_right(_root, l, f);\n            return res;\n        }\n   \
    \     // Returns min{ l | f(op(A[l], ..., A[r-1])) = true }\n        template\
    \ <typename Predicate>\n        int min_left(size_t r, const Predicate& f) {\n\
    \            size_t res;\n            std::tie(_root, res) = node_type::min_left(_root,\
    \ r, f);\n            return res;\n        }\n\n        using iterator = typename\
    \ node_type::const_iterator;\n        using reverse_iterator = typename node_type::const_reverse_iterator;\n\
    \        using const_iterator = typename node_type::const_iterator;\n        using\
    \ const_reverse_iterator = typename node_type::const_reverse_iterator;\n\n   \
    \     iterator begin() const { return cbegin(); }\n        iterator end() const\
    \ { return cend(); }\n        iterator kth_iterator(size_t k) const { return kth_const_iterator(k);\
    \ }\n        reverse_iterator rbegin() const { return crbegin(); }\n        reverse_iterator\
    \ rend() const { return crend(); }\n        reverse_iterator kth_reverse_iterator(size_t\
    \ k) const { return kth_const_reverse_iterator(k); }\n        const_iterator cbegin()\
    \ const { return node_type::cbegin(_root); }\n        const_iterator cend() const\
    \ { return node_type::cend(_root); }\n        const_iterator kth_const_iterator(size_t\
    \ k) const { return node_type::kth_const_iterator(_root, k); }\n        const_reverse_iterator\
    \ crbegin() const { return node_type::crbegin(_root); }\n        const_reverse_iterator\
    \ crend() const { return node_type::crend(_root); }\n        const_reverse_iterator\
    \ kth_const_reverse_iterator(size_t k) const { return node_type::kth_const_reverse_iterator(_root,\
    \ k); }\n    };\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_IMPLICIT_TREAP_SEGTREE\n#define SUISEN_IMPLICIT_TREAP_SEGTREE\n\
    \n#include \"library/datastructure/bbst/implicit_treap_base.hpp\"\n\nnamespace\
    \ suisen {\n    namespace internal::implicit_treap {\n        template <typename\
    \ T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>\n        struct RangeProductNode: Node<T,\
    \ RangeProductNode<T, op, e, toggle>> {\n            using base = Node<T, RangeProductNode<T,\
    \ op, e, toggle>>;\n            using node_pointer = typename base::node_pointer;\n\
    \            using value_type = typename base::value_type;\n\n            value_type\
    \ _sum;\n            RangeProductNode(const value_type& val): base(val), _sum(val)\
    \ {}\n\n            // ----- override ----- //\n            static node_pointer\
    \ update(node_pointer t) {\n                base::update(t);\n               \
    \ prod_all(t) = op(op(safe_prod(base::child0(t)), base::value(t)), safe_prod(base::child1(t)));\n\
    \                return t;\n            }\n            static node_pointer reverse_all(node_pointer\
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
    \n        node_pointer _root;\n\n        struct node_pointer_construct {};\n \
    \       DynamicSegmentTree(node_pointer root, node_pointer_construct): _root(root)\
    \ {}\n\n    public:\n        using value_type = typename node_type::value_type;\n\
    \n        DynamicSegmentTree(): _root(node_type::empty_node()) {}\n        explicit\
    \ DynamicSegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n,\
    \ fill_value)) {}\n        template <typename U>\n        DynamicSegmentTree(const\
    \ std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}\n\n\
    \        void free() {\n            node_type::delete_tree(_root);\n         \
    \   _root = node_type::empty_node();\n        }\n        void clear() { free();\
    \ }\n\n        static void reserve(size_t capacity) { node_type::reserve(capacity);\
    \ }\n\n        bool empty() const { return node_type::empty(_root); }\n      \
    \  int size() const { return node_type::safe_size(_root); }\n\n        const value_type&\
    \ operator[](size_t k) const { return get(k); }\n        const value_type& get(size_t\
    \ k) const {\n            assert(k < size_t(size()));\n            return node_type::get(_root,\
    \ k);\n        }\n        const value_type& front() const { return get(0); }\n\
    \        const value_type& back() const { return get(size() - 1); }\n\n      \
    \  void set(size_t k, const value_type& val) {\n            assert(k < size_t(size()));\n\
    \            _root = node_type::set(_root, k, [&](const value_type&) { return\
    \ val; });\n        }\n        template <typename Func>\n        void apply(size_t\
    \ k, const Func& f) {\n            assert(k < size_t(size()));\n            _root\
    \ = node_type::set(_root, k, [&](const value_type& val) { return f(val); });\n\
    \        }\n\n        value_type prod_all() const { return node_type::safe_prod(_root);\
    \ }\n        value_type prod(size_t l, size_t r) {\n            value_type res;\n\
    \            std::tie(_root, res) = node_type::prod(_root, l, r);\n          \
    \  return res;\n        }\n\n        void insert(size_t k, const value_type& val)\
    \ {\n            assert(k <= size_t(size()));\n            _root = node_type::insert(_root,\
    \ k, val);\n        }\n        void push_front(const value_type& val) { _root\
    \ = node_type::push_front(_root, val); }\n        void push_back(const value_type&\
    \ val) { _root = node_type::push_back(_root, val); }\n\n        void erase(size_t\
    \ k) {\n            assert(k <= size_t(size()));\n            _root = node_type::erase(_root,\
    \ k);\n        }\n        void pop_front() { _root = node_type::pop_front(_root);\
    \ }\n        void pop_back() { _root = node_type::pop_back(_root); }\n\n     \
    \   DynamicSegmentTree split(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            node_pointer root_r;\n            std::tie(_root, root_r) = node_type::split(_root,\
    \ k);\n            return DynamicSegmentTree(root_r, node_pointer_construct{});\n\
    \        }\n        void merge(DynamicSegmentTree r) { _root = node_type::merge(_root,\
    \ r._root); }\n\n        void rotate(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, k);\n        }\n\n        void reverse(size_t\
    \ l, size_t r) {\n            assert(l <= r and r <= size_t(size()));\n      \
    \      if (r - l >= 2) _root = node_type::reverse(_root, l, r);\n        }\n \
    \       void reverse_all() { _root = node_type::reverse_all(_root); }\n\n    \
    \    std::vector<value_type> dump() const { return node_type::dump(_root); }\n\
    \n        // Returns the first i s.t. f(A[i]) = true by binary search.\n     \
    \   // Requirement: f(A[i]) is monotonic.\n        template <typename Predicate>\n\
    \        int binary_search_find_first(const Predicate& f) const { return node_type::binary_search(_root,\
    \ f); }\n        // comp(T t, U u) = (t < u)\n        template <typename U, typename\
    \ Compare = std::less<>>\n        int lower_bound(const U& target, Compare comp\
    \ = {}) { return node_type::lower_bound(_root, target, comp); }\n        // comp(T\
    \ u, U t) = (u < t)\n        template <typename U, typename Compare = std::less<>>\n\
    \        int upper_bound(const U& target, Compare comp = {}) { return node_type::upper_bound(_root,\
    \ target, comp); }\n\n        // Returns max{ r | f(op(A[l], ..., A[r-1])) = true\
    \ }\n        template <typename Predicate>\n        int max_right(size_t l, const\
    \ Predicate& f) {\n            size_t res;\n            std::tie(_root, res) =\
    \ node_type::max_right(_root, l, f);\n            return res;\n        }\n   \
    \     // Returns min{ l | f(op(A[l], ..., A[r-1])) = true }\n        template\
    \ <typename Predicate>\n        int min_left(size_t r, const Predicate& f) {\n\
    \            size_t res;\n            std::tie(_root, res) = node_type::min_left(_root,\
    \ r, f);\n            return res;\n        }\n\n        using iterator = typename\
    \ node_type::const_iterator;\n        using reverse_iterator = typename node_type::const_reverse_iterator;\n\
    \        using const_iterator = typename node_type::const_iterator;\n        using\
    \ const_reverse_iterator = typename node_type::const_reverse_iterator;\n\n   \
    \     iterator begin() const { return cbegin(); }\n        iterator end() const\
    \ { return cend(); }\n        iterator kth_iterator(size_t k) const { return kth_const_iterator(k);\
    \ }\n        reverse_iterator rbegin() const { return crbegin(); }\n        reverse_iterator\
    \ rend() const { return crend(); }\n        reverse_iterator kth_reverse_iterator(size_t\
    \ k) const { return kth_const_reverse_iterator(k); }\n        const_iterator cbegin()\
    \ const { return node_type::cbegin(_root); }\n        const_iterator cend() const\
    \ { return node_type::cend(_root); }\n        const_iterator kth_const_iterator(size_t\
    \ k) const { return node_type::kth_const_iterator(_root, k); }\n        const_reverse_iterator\
    \ crbegin() const { return node_type::crbegin(_root); }\n        const_reverse_iterator\
    \ crend() const { return node_type::crend(_root); }\n        const_reverse_iterator\
    \ kth_const_reverse_iterator(size_t k) const { return node_type::kth_const_reverse_iterator(_root,\
    \ k); }\n    };\n} // namespace suisen\n\n\n#endif // SUISEN_IMPLICIT_TREAP_SEGTREE\n"
  dependsOn:
  - library/datastructure/bbst/implicit_treap_base.hpp
  isVerificationFile: false
  path: library/datastructure/bbst/implicit_treap_segtree.hpp
  requiredBy: []
  timestamp: '2023-02-02 07:52:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/bbst/implicit_treap_segtree/abc238_f.test.cpp
  - test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
documentation_of: library/datastructure/bbst/implicit_treap_segtree.hpp
layout: document
title: Implicit Treap Segtree
---
## Implicit Treap Segtree
