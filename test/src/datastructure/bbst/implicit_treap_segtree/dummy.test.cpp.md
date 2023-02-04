---
data:
  _extendedDependsOn:
  - icon: ':question:'
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
    #line 5 \"library/datastructure/bbst/implicit_treap_base.hpp\"\n#include <cassert>\n\
    #include <cstdint>\n#include <optional>\n#include <string>\n#include <random>\n\
    #include <tuple>\n#line 12 \"library/datastructure/bbst/implicit_treap_base.hpp\"\
    \n#include <utility>\n\nnamespace suisen::internal::implicit_treap {\n    template\
    \ <typename T, typename Derived>\n    struct Node {\n        using random_engine\
    \ = std::mt19937;\n        static inline random_engine rng{ std::random_device{}()\
    \ };\n\n        using priority_type = std::invoke_result_t<random_engine>;\n\n\
    \        static priority_type random_priority() { return rng(); }\n\n        using\
    \ node_type = Derived;\n        using node_pointer = uint32_t;\n\n        using\
    \ size_type = uint32_t;\n\n        using difference_type = int32_t;\n        using\
    \ value_type = T;\n        using pointer = value_type*;\n        using const_pointer\
    \ = const value_type*;\n        using reference = value_type&;\n        using\
    \ const_reference = const value_type&;\n\n        static inline std::vector<node_type>\
    \ _nodes{};\n        static inline std::vector<node_pointer> _erased{};\n\n  \
    \      static constexpr node_pointer null = ~node_pointer(0);\n\n        node_pointer\
    \ _ch[2]{ null, null };\n        value_type _val;\n        size_type _size;\n\
    \        priority_type _priority;\n\n        node_pointer _prev = null, _next\
    \ = null;\n\n        Node(const value_type val = {}): _val(val), _size(1), _priority(random_priority())\
    \ {}\n\n        static void reserve(size_type capacity) { _nodes.reserve(capacity);\
    \ }\n\n        static bool is_null(node_pointer t) { return t == null; }\n   \
    \     static bool is_not_null(node_pointer t) { return not is_null(t); }\n\n \
    \       static node_type& node(node_pointer t) { return _nodes[t]; }\n       \
    \ static const node_type& const_node(node_pointer t) { return _nodes[t]; }\n\n\
    \        static value_type& value(node_pointer t) { return node(t)._val; }\n \
    \       static value_type set_value(node_pointer t, const value_type& new_val)\
    \ { return std::exchange(value(t), new_val); }\n\n        static bool empty(node_pointer\
    \ t) { return is_null(t); }\n        static size_type& size(node_pointer t) {\
    \ return node(t)._size; }\n        static size_type safe_size(node_pointer t)\
    \ { return empty(t) ? 0 : size(t); }\n\n        static priority_type& priority(node_pointer\
    \ t) { return node(t)._priority; }\n        static void set_priority(node_pointer\
    \ t, priority_type new_priority) { priority(t) = new_priority; }\n\n        static\
    \ node_pointer& prev(node_pointer t) { return node(t)._prev; }\n        static\
    \ node_pointer& next(node_pointer t) { return node(t)._next; }\n        static\
    \ void link(node_pointer l, node_pointer r) { next(l) = r, prev(r) = l; }\n\n\
    \        static node_pointer min(node_pointer t) {\n            while (true) {\n\
    \                node_pointer nt = child0(t);\n                if (is_null(nt))\
    \ return t;\n                t = nt;\n            }\n        }\n        static\
    \ node_pointer max(node_pointer t) {\n            while (true) {\n           \
    \     node_pointer nt = child1(t);\n                if (is_null(nt)) return t;\n\
    \                t = nt;\n            }\n        }\n\n        static node_pointer&\
    \ child0(node_pointer t) { return node(t)._ch[0]; }\n        static node_pointer&\
    \ child1(node_pointer t) { return node(t)._ch[1]; }\n        static node_pointer&\
    \ child(node_pointer t, bool b) { return node(t)._ch[b]; }\n        static node_pointer\
    \ set_child0(node_pointer t, node_pointer cid) { return std::exchange(child0(t),\
    \ cid); }\n        static node_pointer set_child1(node_pointer t, node_pointer\
    \ cid) { return std::exchange(child1(t), cid); }\n        static node_pointer\
    \ set_child(node_pointer t, bool b, node_pointer cid) { return std::exchange(child(t,\
    \ b), cid); }\n\n        static node_pointer update(node_pointer t) { // t : not\
    \ null\n            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;\n\
    \            return t;\n        }\n\n        static node_pointer empty_node()\
    \ { return null; }\n        template <typename ...Args>\n        static node_pointer\
    \ create_node(Args &&...args) {\n            if (_erased.size()) {\n         \
    \       node_pointer res = _erased.back();\n                _erased.pop_back();\n\
    \                node(res) = node_type(std::forward<Args>(args)...);\n       \
    \         return res;\n            } else {\n                node_pointer res\
    \ = _nodes.size();\n                _nodes.emplace_back(std::forward<Args>(args)...);\n\
    \                return res;\n            }\n        }\n        static void delete_node(node_pointer\
    \ t) { _erased.push_back(t); }\n        static void delete_tree(node_pointer t)\
    \ {\n            if (is_null(t)) return;\n            delete_tree(child0(t));\n\
    \            delete_tree(child1(t));\n            delete_node(t);\n        }\n\
    \n        template <typename ...Args>\n        static node_pointer build(Args\
    \ &&... args) {\n            std::vector<value_type> dat(std::forward<Args>(args)...);\n\
    \n            const size_t n = dat.size();\n\n            std::vector<priority_type>\
    \ priorities(n);\n            std::generate(priorities.begin(), priorities.end(),\
    \ random_priority);\n            std::make_heap(priorities.begin(), priorities.end());\n\
    \n            std::vector<node_pointer> nodes(n);\n\n            auto rec = [&](auto\
    \ rec, size_t heap_index, size_t dat_index_offset) -> std::pair<size_t, node_pointer>\
    \ {\n                if (heap_index >= n) return { 0, null };\n              \
    \  auto [lsiz, lch] = rec(rec, 2 * heap_index + 1, dat_index_offset);\n      \
    \          dat_index_offset += lsiz;\n                node_pointer root = create_node(std::move(dat[dat_index_offset]));\n\
    \                nodes[dat_index_offset] = root;\n                set_priority(root,\
    \ priorities[heap_index]);\n                if (dat_index_offset) {\n        \
    \            link(nodes[dat_index_offset - 1], root);\n                }\n   \
    \             dat_index_offset += 1;\n                auto [rsiz, rch] = rec(rec,\
    \ 2 * heap_index + 2, dat_index_offset);\n                set_child0(root, lch);\n\
    \                set_child1(root, rch);\n                return { lsiz + 1 + rsiz,\
    \ node_type::update(root) };\n            };\n            return rec(rec, 0, 0).second;\n\
    \        }\n\n        static std::pair<node_pointer, node_pointer> split(node_pointer\
    \ t, size_type k) {\n            if (k == 0) return { null, t };\n           \
    \ if (k == size(t)) return { t, null };\n\n            static std::vector<node_pointer>\
    \ lp{}, rp{};\n\n            while (true) {\n                if (const size_type\
    \ lsiz = safe_size(child0(t)); k <= lsiz) {\n                    if (rp.size())\
    \ set_child0(rp.back(), t);\n                    rp.push_back(t);\n          \
    \          if (k == lsiz) {\n                        if (lp.size()) set_child1(lp.back(),\
    \ child0(t));\n\n                        node_pointer lt = set_child0(t, null),\
    \ rt = null;\n\n                        while (lp.size()) node_type::update(lt\
    \ = lp.back()), lp.pop_back();\n                        while (rp.size()) node_type::update(rt\
    \ = rp.back()), rp.pop_back();\n\n                        return { lt, rt };\n\
    \                    }\n                    t = child0(t);\n                }\
    \ else {\n                    if (lp.size()) set_child1(lp.back(), t);\n     \
    \               lp.push_back(t);\n                    t = child1(t);\n       \
    \             k -= lsiz + 1;\n                }\n            }\n        }\n  \
    \      static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer\
    \ t, size_type l, size_type r) {\n            auto [tlm, tr] = split(t, r);\n\
    \            auto [tl, tm] = split(tlm, l);\n            return { tl, tm, tr };\n\
    \        }\n\n        static node_pointer merge_impl(node_pointer tl, node_pointer\
    \ tr) {\n            if (priority(tl) < priority(tr)) {\n                if (node_pointer\
    \ tm = child0(tr); is_null(tm)) {\n                    link(max(tl), tr);\n  \
    \                  set_child0(tr, tl);\n                } else {\n           \
    \         set_child0(tr, merge(tl, tm));\n                }\n                return\
    \ node_type::update(tr);\n            } else {\n                if (node_pointer\
    \ tm = child1(tl); is_null(tm)) {\n                    link(tl, min(tr));\n  \
    \                  set_child1(tl, tr);\n                } else {\n           \
    \         set_child1(tl, merge(tm, tr));\n                }\n                return\
    \ node_type::update(tl);\n            }\n        }\n        static node_pointer\
    \ merge(node_pointer tl, node_pointer tr) {\n            if (is_null(tl)) return\
    \ tr;\n            if (is_null(tr)) return tl;\n            return merge_impl(tl,\
    \ tr);\n        }\n        static node_pointer merge(node_pointer tl, node_pointer\
    \ tm, node_pointer tr) {\n            return merge(merge(tl, tm), tr);\n     \
    \   }\n\n        static node_pointer insert_impl(node_pointer t, size_type k,\
    \ node_pointer new_node) {\n            if (is_null(t)) return new_node;\n   \
    \         static std::vector<node_pointer> st;\n            bool b = false;\n\n\
    \            while (true) {\n                if (is_null(t) or priority(new_node)\
    \ > priority(t)) {\n                    if (is_null(t)) {\n                  \
    \      t = new_node;\n                    } else {\n                        auto\
    \ [tl, tr] = split(t, k);\n                        if (is_not_null(tl)) link(max(tl),\
    \ new_node);\n                        if (is_not_null(tr)) link(new_node, min(tr));\n\
    \                        set_child0(new_node, tl);\n                        set_child1(new_node,\
    \ tr);\n                        t = node_type::update(new_node);\n           \
    \         }\n                    if (st.size()) {\n                        set_child(st.back(),\
    \ b, t);\n                        do t = node_type::update(st.back()), st.pop_back();\
    \ while (st.size());\n                    }\n                    return t;\n \
    \               } else {\n                    if (const size_type lsiz = safe_size(child0(t));\
    \ k <= lsiz) {\n                        if (k == lsiz) link(new_node, t);\n  \
    \                      st.push_back(t), b = false;\n                        t\
    \ = child0(t);\n                    } else {\n                        if (k ==\
    \ lsiz + 1) link(t, new_node);\n                        st.push_back(t), b = true;\n\
    \                        t = child1(t);\n                        k -= lsiz + 1;\n\
    \                    }\n                }\n            }\n        }\n        template\
    \ <typename ...Args>\n        static node_pointer insert(node_pointer t, size_type\
    \ k, Args &&...args) {\n            return insert_impl(t, k, create_node(std::forward<Args>(args)...));\n\
    \        }\n\n        static std::pair<node_pointer, value_type> erase(node_pointer\
    \ t, size_type k) {\n            if (const size_type lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                delete_node(t);\n                return { merge(child0(t),\
    \ child1(t)), std::move(value(t)) };\n            } else if (k < lsiz) {\n   \
    \             auto [c0, v] = erase(child0(t), k);\n                set_child0(t,\
    \ c0);\n                if (is_not_null(c0) and k == lsiz - 1) link(max(c0), t);\n\
    \                return { node_type::update(t), std::move(v) };\n            }\
    \ else {\n                auto [c1, v] = erase(child1(t), k - (lsiz + 1));\n \
    \               set_child1(t, c1);\n                if (is_not_null(c1) and k\
    \ == lsiz + 1) link(t, min(c1));\n                return { node_type::update(t),\
    \ std::move(v) };\n            }\n        }\n\n        static node_pointer rotate(node_pointer\
    \ t, size_type k) {\n            auto [tl, tr] = split(t, k);\n            return\
    \ merge(tr, tl);\n        }\n        static node_pointer rotate(node_pointer t,\
    \ size_type l, size_type m, size_type r) {\n            auto [tl, tm, tr] = split(t,\
    \ l, r);\n            return merge(tl, rotate(tm, m - l), tr);\n        }\n\n\
    \        template <typename Func>\n        static node_pointer set_update(node_pointer\
    \ t, size_type k, const Func& f) {\n            if (const size_type lsiz = safe_size(child0(t));\
    \ k == lsiz) {\n                value_type& val = value(t);\n                val\
    \ = f(const_cast<const value_type&>(val));\n            } else if (k < lsiz) {\n\
    \                set_child0(t, set_update(child0(t), k, f));\n            } else\
    \ {\n                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));\n\
    \            }\n            return node_type::update(t);\n        }\n\n      \
    \  static std::vector<value_type> dump(node_pointer t) {\n            std::vector<value_type>\
    \ res;\n            res.reserve(safe_size(t));\n            auto rec = [&](auto\
    \ rec, node_pointer t) -> void {\n                if (is_null(t)) return;\n  \
    \              rec(rec, child0(t));\n                res.push_back(value(t));\n\
    \                rec(rec, child1(t));\n            };\n            rec(rec, t);\n\
    \            return res;\n        }\n\n        template <bool reversed_, bool\
    \ constant_>\n        struct NodeIterator {\n            static constexpr bool\
    \ constant = constant_;\n            static constexpr bool reversed = reversed_;\n\
    \n            friend Node;\n            friend Derived;\n\n            using difference_type\
    \ = Node::difference_type;\n            using value_type = Node::value_type;\n\
    \            using pointer = std::conditional_t<constant, Node::const_pointer,\
    \ Node::pointer>;\n            using reference = std::conditional_t<constant,\
    \ Node::const_reference, Node::reference>;\n            using iterator_category\
    \ = std::random_access_iterator_tag;\n\n            NodeIterator(): NodeIterator(null)\
    \ {}\n            explicit NodeIterator(node_pointer root): NodeIterator(root,\
    \ 0, null) {}\n            NodeIterator(const NodeIterator<reversed, not constant>&\
    \ it): NodeIterator(it._root, it._index, it._cur) {}\n\n            reference\
    \ operator*() const {\n                if (is_null(_cur) and _index != safe_size(_root))\
    \ {\n                    _cur = _root;\n                    for (size_type k =\
    \ _index;;) {\n                        if (size_type siz = safe_size(child(_cur,\
    \ reversed)); k == siz) {\n                            break;\n              \
    \          } else if (k < siz) {\n                            _cur = child(_cur,\
    \ reversed);\n                        } else {\n                            _cur\
    \ = child(_cur, not reversed);\n                            k -= siz + 1;\n  \
    \                      }\n                    }\n                }\n         \
    \       return value(_cur);\n            }\n            reference operator[](difference_type\
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
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index - rhs._index;\
    \ }\n\n            friend bool operator==(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs._index == rhs._index; }\n            friend bool operator!=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index != rhs._index;\
    \ }\n            friend bool operator<(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs._index < rhs._index; }\n            friend bool operator>(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index > rhs._index;\
    \ }\n            friend bool operator<=(const NodeIterator& lhs, const NodeIterator&\
    \ rhs) { return lhs._index <= rhs._index; }\n            friend bool operator>=(const\
    \ NodeIterator& lhs, const NodeIterator& rhs) { return lhs._index >= rhs._index;\
    \ }\n\n            static NodeIterator begin(node_pointer root) { return NodeIterator(root,\
    \ 0, null); }\n            static NodeIterator end(node_pointer root) { return\
    \ NodeIterator(root, safe_size(root), null); }\n\n            int size() const\
    \ { return safe_size(_root); }\n            int index() const { return _index;\
    \ }\n        private:\n            node_pointer _root;\n            size_type\
    \ _index;\n            mutable node_pointer _cur; // it==end() or uninitialized\
    \ (updates only index)\n\n            NodeIterator(node_pointer root, size_type\
    \ index, node_pointer cur): _root(root), _index(index), _cur(cur) {}\n\n     \
    \       void suc(difference_type k) {\n                _index += k;\n        \
    \        if (_index == safe_size(_root) or std::abs(k) >= 20) _cur = null;\n \
    \               if (is_null(_cur)) return;\n\n                const bool positive\
    \ = k < 0 ? (k = -k, reversed) : not reversed;\n\n                if (positive)\
    \ {\n                    while (k-- > 0) _cur = next(_cur);\n                }\
    \ else {\n                    while (k-- > 0) _cur = prev(_cur);\n           \
    \     }\n            }\n\n            node_pointer root() const { return _root;\
    \ }\n            void set_root(node_pointer new_root, size_type new_index) { _root\
    \ = new_root, _index = new_index; }\n\n            node_pointer get_child0() const\
    \ { return child0(_cur); }\n            node_pointer get_child1() const { return\
    \ child1(_cur); }\n\n            template <typename Predicate>\n            static\
    \ NodeIterator binary_search(node_pointer t, const Predicate& f) {\n         \
    \       NodeIterator res(t, safe_size(t), null);\n                if (is_null(t))\
    \ return res;\n\n                NodeIterator it(t, safe_size(child0(t)), t);\n\
    \                while (is_not_null(it._cur)) {\n                    if (f(it))\
    \ {\n                        res = it;\n                        it._cur = it.get_child0();\n\
    \                        it._index -= is_null(it._cur) ? 1 : safe_size(it.get_child1())\
    \ + 1;\n                    } else {\n                        it._cur = it.get_child1();\n\
    \                        it._index += is_null(it._cur) ? 1 : safe_size(it.get_child0())\
    \ + 1;\n                    }\n                }\n                return res;\n\
    \            }\n\n            size_type get_gap_index_left() const {\n       \
    \         if constexpr (reversed) return size() - index();\n                else\
    \ return index();\n            }\n            size_type get_element_index_left()\
    \ const {\n                if constexpr (reversed) return size() - index() - 1;\n\
    \                else return index();\n            }\n        };\n        using\
    \ iterator = NodeIterator<false, false>;\n        using reverse_iterator = NodeIterator<true,\
    \ false>;\n        using const_iterator = NodeIterator<false, true>;\n       \
    \ using const_reverse_iterator = NodeIterator<true, true>;\n\n        template\
    \ <typename>\n        struct is_node_iterator: std::false_type {};\n        template\
    \ <bool reversed_, bool constant_>\n        struct is_node_iterator<NodeIterator<reversed_,\
    \ constant_>>: std::true_type {};\n        template <typename X>\n        static\
    \ constexpr bool is_node_iterator_v = is_node_iterator<X>::value;\n\n        static\
    \ iterator begin(node_pointer t) { return iterator::begin(t); }\n        static\
    \ iterator end(node_pointer t) { return iterator::end(t); }\n        static reverse_iterator\
    \ rbegin(node_pointer t) { return reverse_iterator::begin(t); }\n        static\
    \ reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t); }\n\
    \        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t);\
    \ }\n        static const_iterator cend(node_pointer t) { return const_iterator::end(t);\
    \ }\n        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t);\
    \ }\n        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t);\
    \ }\n\n        // Find the first element that satisfies the condition f : iterator\
    \ -> { false, true }.\n        // Returns const_iterator\n        template <typename\
    \ Iterator, typename Predicate, std::enable_if_t<is_node_iterator_v<Iterator>,\
    \ std::nullptr_t> = nullptr>\n        static Iterator binary_search(node_pointer\
    \ t, const Predicate& f) {\n            return Iterator::binary_search(t, f);\n\
    \        }\n        // comp(T t, U u) = (t < u)\n        template <typename Iterator,\
    \ typename U, typename Compare = std::less<>, std::enable_if_t<is_node_iterator_v<Iterator>,\
    \ std::nullptr_t> = nullptr>\n        static Iterator lower_bound(node_pointer\
    \ t, const U& target, Compare comp) {\n            return binary_search<Iterator>(t,\
    \ [&](Iterator it) { return not comp(*it, target); });\n        }\n        //\
    \ comp(T u, U t) = (u < t)\n        template <typename Iterator, typename U, typename\
    \ Compare = std::less<>, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t>\
    \ = nullptr>\n        static Iterator upper_bound(node_pointer t, const U& target,\
    \ Compare comp) {\n            return binary_search<Iterator>(t, [&](Iterator\
    \ it) { return comp(target, *it); });\n        }\n\n        template <typename\
    \ Iterator, std::enable_if_t<is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>\n\
    \        static node_pointer insert(Iterator it, const value_type& val) {\n  \
    \          return insert(it.root(), it.get_gap_index_left(), val);\n        }\n\
    \        template <typename Iterator, std::enable_if_t<is_node_iterator_v<Iterator>,\
    \ std::nullptr_t> = nullptr>\n        static std::pair<node_pointer, value_type>\
    \ erase(Iterator it) {\n            return erase(it.root(), it.get_element_index_left());\n\
    \        }\n        template <typename Iterator, std::enable_if_t<is_node_iterator_v<Iterator>,\
    \ std::nullptr_t> = nullptr>\n        static std::pair<node_pointer, node_pointer>\
    \ split(Iterator it) {\n            return split(it.root(), it.get_gap_index_left());\n\
    \        }\n    };\n} // namespace suisen::internal::implicit_treap\n\n\n#line\
    \ 5 \"library/datastructure/bbst/implicit_treap_segtree.hpp\"\n\nnamespace suisen\
    \ {\n    namespace internal::implicit_treap {\n        template <typename T, T(*op)(T,\
    \ T), T(*e)()>\n        struct RangeProductNode: Node<T, RangeProductNode<T, op,\
    \ e>> {\n            using base = Node<T, RangeProductNode<T, op, e>>;\n     \
    \       using node_pointer = typename base::node_pointer;\n            using value_type\
    \ = typename base::value_type;\n\n            value_type _sum;\n            RangeProductNode(const\
    \ value_type& val): base(val), _sum(val) {}\n\n            // ----- override -----\
    \ //\n            static node_pointer update(node_pointer t) {\n             \
    \   base::update(t);\n                prod_all(t) = op(op(safe_prod(base::child0(t)),\
    \ base::value(t)), safe_prod(base::child1(t)));\n                return t;\n \
    \           }\n\n            // ----- new features ----- //\n            static\
    \ value_type& prod_all(node_pointer t) {\n                return base::node(t)._sum;\n\
    \            }\n            static value_type safe_prod(node_pointer t) {\n  \
    \              return base::is_null(t) ? e() : prod_all(t);\n            }\n \
    \           static std::pair<node_pointer, value_type> prod(node_pointer t, size_t\
    \ l, size_t r) {\n                auto [tl, tm, tr] = base::split(t, l, r);\n\
    \                value_type res = safe_prod(tm);\n                return { base::merge(tl,\
    \ tm, tr), res };\n            }\n            template <typename Func>\n     \
    \       static node_pointer set(node_pointer t, size_t k, const Func& f) {\n \
    \               return base::set_update(t, k, f);\n            }\n\n         \
    \   using const_iterator = typename base::const_iterator;\n\n            template\
    \ <typename Predicate>\n            static std::pair<node_pointer, const_iterator>\
    \ max_right(node_pointer t, size_t l, const Predicate& f) {\n                auto\
    \ [tl, tr] = base::split(t, l);\n                value_type sum = e();\n     \
    \           assert(f(sum));\n                const_iterator it = base::template\
    \ binary_search<const_iterator>(\n                    tr, [&](const_iterator it)\
    \ {\n                        value_type nxt_sum = op(op(sum, safe_prod(it.get_child0())),\
    \ *it);\n                        return f(nxt_sum) ? (sum = std::move(nxt_sum),\
    \ false) : true;\n                    }\n                );\n                it.set_root(t\
    \ = base::merge(tl, tr), l + it.index());\n                return { t, it };\n\
    \            }\n            template <typename Predicate>\n            static\
    \ std::pair<node_pointer, const_iterator> min_left(node_pointer t, size_t r, const\
    \ Predicate& f) {\n                auto [tl, tr] = base::split(t, r);\n      \
    \          value_type sum = e();\n                assert(f(sum));\n          \
    \      const_iterator it = base::template binary_search<const_iterator>(\n   \
    \                 tl, [&](const_iterator it) {\n                        value_type\
    \ nxt_sum = op(*it, op(safe_prod(it.get_child1()), sum));\n                  \
    \      return f(nxt_sum) ? (sum = std::move(nxt_sum), true) : false;\n       \
    \             }\n                );\n                it.set_root(t = base::merge(tl,\
    \ tr), it.index());\n                return { t, it };\n            }\n      \
    \  };\n    }\n\n    template <typename T, T(*op)(T, T), T(*e)()>\n    class DynamicSegmentTree\
    \ {\n        using node_type = internal::implicit_treap::RangeProductNode<T, op,\
    \ e>;\n        using node_pointer = typename node_type::node_pointer;\n\n    \
    \    node_pointer _root;\n\n        struct node_pointer_construct {};\n      \
    \  DynamicSegmentTree(node_pointer root, node_pointer_construct): _root(root)\
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
    \ k) const {\n            assert(k < size_t(size()));\n            return cbegin()[k];\n\
    \        }\n        const value_type& front() const { return *cbegin(); }\n  \
    \      const value_type& back() const { return *crbegin(); }\n\n        void set(size_t\
    \ k, const value_type& val) {\n            assert(k < size_t(size()));\n     \
    \       _root = node_type::set(_root, k, [&](const value_type&) { return val;\
    \ });\n        }\n        template <typename Func>\n        void apply(size_t\
    \ k, const Func& f) {\n            assert(k < size_t(size()));\n            _root\
    \ = node_type::set(_root, k, [&](const value_type& val) { return f(val); });\n\
    \        }\n\n        value_type prod_all() const { return node_type::safe_prod(_root);\
    \ }\n        value_type prod(size_t l, size_t r) {\n            value_type res;\n\
    \            std::tie(_root, res) = node_type::prod(_root, l, r);\n          \
    \  return res;\n        }\n\n        void insert(size_t k, const value_type& val)\
    \ {\n            assert(k <= size_t(size()));\n            _root = node_type::insert(_root,\
    \ k, val);\n        }\n        void push_front(const value_type& val) { insert(0,\
    \ val); }\n        void push_back(const value_type& val) { insert(size(), val);\
    \ }\n\n        value_type erase(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            value_type v;\n            std::tie(_root, v) = node_type::erase(_root,\
    \ k);\n            return v;\n        }\n        value_type pop_front() { return\
    \ erase(0); }\n        value_type pop_back() { return erase(size() - 1); }\n\n\
    \        // Split immediately before the k-th element.\n        DynamicSegmentTree\
    \ split(size_t k) {\n            assert(k <= size_t(size()));\n            node_pointer\
    \ root_r;\n            std::tie(_root, root_r) = node_type::split(_root, k);\n\
    \            return DynamicSegmentTree(root_r, node_pointer_construct{});\n  \
    \      }\n\n        void merge(DynamicSegmentTree r) { _root = node_type::merge(_root,\
    \ r._root); }\n\n        void rotate(size_t k) {\n            assert(k <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, k);\n        }\n        void rotate(size_t\
    \ l, size_t m, size_t r) {\n            assert(l <= m and m <= r and r <= size_t(size()));\n\
    \            _root = node_type::rotate(_root, l, m, r);\n        }\n\n       \
    \ std::vector<value_type> dump() const { return node_type::dump(_root); }\n\n\
    \        using iterator = typename node_type::const_iterator;\n        using reverse_iterator\
    \ = typename node_type::const_reverse_iterator;\n        using const_iterator\
    \ = typename node_type::const_iterator;\n        using const_reverse_iterator\
    \ = typename node_type::const_reverse_iterator;\n\n        iterator begin() const\
    \ { return cbegin(); }\n        iterator end() const { return cend(); }\n    \
    \    reverse_iterator rbegin() const { return crbegin(); }\n        reverse_iterator\
    \ rend() const { return crend(); }\n        const_iterator cbegin() const { return\
    \ node_type::cbegin(_root); }\n        const_iterator cend() const { return node_type::cend(_root);\
    \ }\n        const_reverse_iterator crbegin() const { return node_type::crbegin(_root);\
    \ }\n        const_reverse_iterator crend() const { return node_type::crend(_root);\
    \ }\n\n        // Returns the iterator with index max{ r | f(op(A[l], ..., A[r-1]))\
    \ = true } (0 <= r <= size())\n        template <typename Predicate>\n       \
    \ iterator max_right(size_t l, const Predicate& f) {\n            assert(l <=\
    \ size_t(size()));\n            iterator it;\n            std::tie(_root, it)\
    \ = node_type::max_right(_root, l, f);\n            return it;\n        }\n  \
    \      // Returns the iterator with index min{ l | f(op(A[l], ..., A[r-1])) =\
    \ true } (0 <= l <= size())\n        template <typename Predicate>\n        iterator\
    \ min_left(size_t r, const Predicate& f) {\n            assert(r <= size_t(size()));\n\
    \            iterator it;\n            std::tie(_root, it) = node_type::min_left(_root,\
    \ r, f);\n            return it;\n        }\n\n        // Find the first element\
    \ that satisfies the condition f.\n        // Returns { position, optional(value)\
    \ }\n        // Requirements: f(A[i]) must be monotonic\n        template <typename\
    \ Predicate>\n        iterator binary_search(const Predicate& f) {\n         \
    \   return node_type::template binary_search<iterator>(_root, f);\n        }\n\
    \        // comp(T t, U u) = (t < u)\n        // Requirements: sequence is sorted\n\
    \        template <typename U, typename Compare = std::less<>>\n        iterator\
    \ lower_bound(const U& target, Compare comp = {}) {\n            return node_type::template\
    \ lower_bound<iterator>(_root, target, comp);\n        }\n        // comp(T u,\
    \ U t) = (u < t)\n        // Requirements: sequence is sorted\n        template\
    \ <typename U, typename Compare = std::less<>>\n        iterator upper_bound(const\
    \ U& target, Compare comp = {}) {\n            return node_type::template upper_bound<iterator>(_root,\
    \ target, comp);\n        }\n        // Find the first element that satisfies\
    \ the condition f.\n        // Returns { position, optional(value) }\n       \
    \ // Requirements: f(A[i]) must be monotonic\n        template <typename Predicate>\n\
    \        const_iterator binary_search(const Predicate& f) const {\n          \
    \  return node_type::template binary_search<const_iterator>(_root, f);\n     \
    \   }\n        // comp(T t, U u) = (t < u)\n        // Requirements: sequence\
    \ is sorted\n        template <typename U, typename Compare = std::less<>>\n \
    \       const_iterator lower_bound(const U& target, Compare comp = {}) const {\n\
    \            return node_type::template lower_bound<const_iterator>(_root, target,\
    \ comp);\n        }\n        // comp(T u, U t) = (u < t)\n        // Requirements:\
    \ sequence is sorted\n        template <typename U, typename Compare = std::less<>>\n\
    \        const_iterator upper_bound(const U& target, Compare comp = {}) const\
    \ {\n            return node_type::template upper_bound<const_iterator>(_root,\
    \ target, comp);\n        }\n \n        template <typename Iterator, std::enable_if_t<node_type::template\
    \ is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>\n        void insert(Iterator\
    \ it, const value_type &val) {\n            _root = node_type::insert(it, val);\n\
    \        }\n        template <typename Iterator, std::enable_if_t<node_type::template\
    \ is_node_iterator_v<Iterator>, std::nullptr_t> = nullptr>\n        value_type\
    \ erase(Iterator it) {\n            value_type erased;\n            std::tie(_root,\
    \ erased) = node_type::erase(it);\n            return erased;\n        }\n   \
    \     template <typename Iterator, std::enable_if_t<node_type::template is_node_iterator_v<Iterator>,\
    \ std::nullptr_t> = nullptr>\n        DynamicSegmentTree split(Iterator it) {\n\
    \            node_pointer root_r;\n            std::tie(_root, root_r) = node_type::split(it);\n\
    \            return DynamicSegmentTree(root_r, node_pointer_construct{});\n  \
    \      }\n\n        // handling internal nodes\n        using internal_node =\
    \ node_type;\n        using internal_node_pointer = node_pointer;\n\n        internal_node_pointer&\
    \ root_node() { return _root; }\n        const internal_node_pointer& root_node()\
    \ const { return _root; }\n        void set_root_node(internal_node_pointer new_root)\
    \ { root_node() = new_root; }\n    };\n} // namespace suisen\n\n\n\n#line 16 \"\
    test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp\"\n\ntemplate\
    \ <typename T, T(*op)(T, T), T(*e)()>\nstruct NaiveSolutionForSegmentTree {\n\
    \    NaiveSolutionForSegmentTree() = default;\n    NaiveSolutionForSegmentTree(const\
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
    }\nS e() {\n    return 0;\n}\n\nusing Tree = suisen::DynamicSegmentTree<S, op,\
    \ e>;\nusing Naive = NaiveSolutionForSegmentTree<S, op, e>;\n\n#line 115 \"test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp\"\
    \n\nconstexpr int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr int Q_insert\
    \ = 4;\nconstexpr int Q_erase = 5;\nconstexpr int Q_rotate = 8;\nconstexpr int\
    \ Q_prod = 2;\nconstexpr int Q_prod_all = 3;\nconstexpr int Q_max_right = 6;\n\
    constexpr int Q_min_left = 7;\nconstexpr int QueryTypeNum = 9;\n\nvoid test()\
    \ {\n    int N = 3000, Q = 3000, MAX_VAL = 1000000000;\n\n    std::mt19937 rng{std::random_device{}()};\n\
    \n    std::vector<S> init(N);\n    for (int i = 0; i < N; ++i) init[i] = rng()\
    \ % MAX_VAL;\n    \n    Tree t1(init);\n    Naive t2(init);\n\n    for (int i\
    \ = 0; i < Q; ++i) {\n        const int query_type = rng() % QueryTypeNum;\n\n\
    \        if (query_type == Q_get) {\n            const int i = rng() % N;\n  \
    \          assert(t1.get(i) == t2.get(i));\n        } else if (query_type == Q_set)\
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
    \ == Q_max_right) {\n            const int l = rng() % (N + 1);\n            const\
    \ int r = l + rng() % (N - l + 1);\n            long long sum = std::max(0LL,\
    \ t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred\
    \ = [&](const S &x) { return x <= sum; };\n\n            int r1 = t1.max_right(l,\
    \ pred).index();\n            int r2 = t2.max_right(l, pred);\n\n            assert(r1\
    \ == r2);\n        } else if (query_type == Q_min_left) {\n            const int\
    \ l = rng() % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n \
    \           long long sum = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL)\
    \ - MAX_VAL / 2);\n            auto pred = [&](const S &x) { return x <= sum;\
    \ };\n\n            int l1 = t1.min_left(r, pred).index();\n            int l2\
    \ = t2.min_left(r, pred);\n\n            assert(l1 == l2);\n        } else {\n\
    \            assert(false);\n        }\n    }\n}\n\nvoid test2() {\n    std::mt19937\
    \ rng{ std::random_device{}() };\n    Tree seq;\n    const int n = 300, k = 20;\n\
    \n    std::vector<S> q(n * k);\n    for (int i = 0; i < n * k; ++i) {\n      \
    \  q[i] = i % n;\n    }\n    std::shuffle(q.begin(), q.end(), rng);\n\n    for\
    \ (int v : q) {\n        if (rng() % 2) {\n            auto it = seq.lower_bound(v);\n\
    \            seq.insert(it, v);\n            int k = it.index();\n           \
    \ assert(k == 0 or seq[k - 1] < v);\n            assert(k == seq.size() - 1 or\
    \ seq[k + 1] >= v);\n        } else {\n            auto it = seq.upper_bound(v);\n\
    \            seq.insert(it, v);\n            int k = it.index();\n           \
    \ assert(k == 0 or seq[k - 1] <= v);\n            assert(k == seq.size() - 1 or\
    \ seq[k + 1] > v);\n        }\n    }\n\n    for (int v : q) {\n        auto it\
    \ = seq.lower_bound(v);\n        int k = it.index();\n        seq.erase(it);\n\
    \        assert(k == 0 or seq[k - 1] < v);\n        assert(k == seq.size() or\
    \ seq[k] >= v);\n    }\n\n    std::vector<S> sorted = q;\n    std::sort(sorted.begin(),\
    \ sorted.end());\n\n    seq = sorted;\n\n    assert(std::equal(sorted.begin(),\
    \ sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(), sorted.rend(),\
    \ seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n        assert(seq.begin()[i]\
    \ == i / k);\n    }\n\n    {\n        auto it = seq.begin();\n        for (int\
    \ q = 0; q < 100000; ++q) {\n            int a = rng() % (n * k + 1);\n      \
    \      auto it2 = seq.begin() + a;\n            it += it2 - it;\n            if\
    \ (a < n * k) {\n                assert(*it == a / k);\n            }\n      \
    \  }\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int a = rng() %\
    \ (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int d = b - a;\n\
    \        assert((seq.begin() + a) + d == seq.begin() + b);\n        assert(seq.begin()\
    \ + a == (seq.begin() + b) - d);\n\n        auto it1 = seq.begin() + a;\n    \
    \    auto it2 = seq.begin() + b;\n\n        if (d > 0) {\n            assert(not\
    \ (it1 == it2));\n            assert(it1 != it2);\n            assert(not (it1\
    \ > it2));\n            assert(not (it1 >= it2));\n            assert(it1 < it2);\n\
    \            assert(it1 <= it2);\n        } else if (d < 0) {\n            assert(not\
    \ (it1 == it2));\n            assert(it1 != it2);\n            assert(not (it1\
    \ < it2));\n            assert(not (it1 <= it2));\n            assert(it1 > it2);\n\
    \            assert(it1 >= it2);\n        } else {\n            assert(not (it1\
    \ != it2));\n            assert(it1 == it2);\n            assert(not (it1 > it2));\n\
    \            assert(not (it1 < it2));\n            assert(it1 <= it2);\n     \
    \       assert(it1 >= it2);\n        }\n\n        if (a != n * k and b != n *\
    \ k) {\n            assert(*it1 == a / k);\n            assert(*it2 == b / k);\n\
    \n            it1 += d;\n\n            assert(not (it1 != it2));\n           \
    \ assert(it1 == it2);\n            assert(not (it1 < it2));\n            assert(not\
    \ (it1 > it2));\n            assert(it1 <= it2);\n            assert(it1 >= it2);\n\
    \            assert(*it1 == *it2);\n        }\n    }\n\n    std::vector<S> naive\
    \ = sorted;\n    assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n\
    \n    // for (S& e : seq) --e; // Compile Error \n    // for (S& e : naive) --e;\n\
    \    // assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n    // assert(std::equal(naive.rbegin(),\
    \ naive.rend(), seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const\
    \ Tree&>(seq);\n    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n\
    \    assert(std::equal(naive.rbegin(), naive.rend(), const_seq.rbegin()));\n\n\
    \    for (int i = 0; i < n * k; ++i) {\n        assert(const_seq[i] == naive[i]);\n\
    \    }\n}\n\nint main() {\n    test();\n    test2();\n    std::cout << \"Hello\
    \ World\" << std::endl;\n    return 0;\n}\n"
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
    }\nS e() {\n    return 0;\n}\n\nusing Tree = suisen::DynamicSegmentTree<S, op,\
    \ e>;\nusing Naive = NaiveSolutionForSegmentTree<S, op, e>;\n\n#include <random>\n\
    #include <algorithm>\n\nconstexpr int Q_get = 0;\nconstexpr int Q_set = 1;\nconstexpr\
    \ int Q_insert = 4;\nconstexpr int Q_erase = 5;\nconstexpr int Q_rotate = 8;\n\
    constexpr int Q_prod = 2;\nconstexpr int Q_prod_all = 3;\nconstexpr int Q_max_right\
    \ = 6;\nconstexpr int Q_min_left = 7;\nconstexpr int QueryTypeNum = 9;\n\nvoid\
    \ test() {\n    int N = 3000, Q = 3000, MAX_VAL = 1000000000;\n\n    std::mt19937\
    \ rng{std::random_device{}()};\n\n    std::vector<S> init(N);\n    for (int i\
    \ = 0; i < N; ++i) init[i] = rng() % MAX_VAL;\n    \n    Tree t1(init);\n    Naive\
    \ t2(init);\n\n    for (int i = 0; i < Q; ++i) {\n        const int query_type\
    \ = rng() % QueryTypeNum;\n\n        if (query_type == Q_get) {\n            const\
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
    \        } else if (query_type == Q_max_right) {\n            const int l = rng()\
    \ % (N + 1);\n            const int r = l + rng() % (N - l + 1);\n           \
    \ long long sum = std::max(0LL, t2.prod(l, r) + int(rng() % MAX_VAL) - MAX_VAL\
    \ / 2);\n            auto pred = [&](const S &x) { return x <= sum; };\n\n   \
    \         int r1 = t1.max_right(l, pred).index();\n            int r2 = t2.max_right(l,\
    \ pred);\n\n            assert(r1 == r2);\n        } else if (query_type == Q_min_left)\
    \ {\n            const int l = rng() % (N + 1);\n            const int r = l +\
    \ rng() % (N - l + 1);\n            long long sum = std::max(0LL, t2.prod(l, r)\
    \ + int(rng() % MAX_VAL) - MAX_VAL / 2);\n            auto pred = [&](const S\
    \ &x) { return x <= sum; };\n\n            int l1 = t1.min_left(r, pred).index();\n\
    \            int l2 = t2.min_left(r, pred);\n\n            assert(l1 == l2);\n\
    \        } else {\n            assert(false);\n        }\n    }\n}\n\nvoid test2()\
    \ {\n    std::mt19937 rng{ std::random_device{}() };\n    Tree seq;\n    const\
    \ int n = 300, k = 20;\n\n    std::vector<S> q(n * k);\n    for (int i = 0; i\
    \ < n * k; ++i) {\n        q[i] = i % n;\n    }\n    std::shuffle(q.begin(), q.end(),\
    \ rng);\n\n    for (int v : q) {\n        if (rng() % 2) {\n            auto it\
    \ = seq.lower_bound(v);\n            seq.insert(it, v);\n            int k = it.index();\n\
    \            assert(k == 0 or seq[k - 1] < v);\n            assert(k == seq.size()\
    \ - 1 or seq[k + 1] >= v);\n        } else {\n            auto it = seq.upper_bound(v);\n\
    \            seq.insert(it, v);\n            int k = it.index();\n           \
    \ assert(k == 0 or seq[k - 1] <= v);\n            assert(k == seq.size() - 1 or\
    \ seq[k + 1] > v);\n        }\n    }\n\n    for (int v : q) {\n        auto it\
    \ = seq.lower_bound(v);\n        int k = it.index();\n        seq.erase(it);\n\
    \        assert(k == 0 or seq[k - 1] < v);\n        assert(k == seq.size() or\
    \ seq[k] >= v);\n    }\n\n    std::vector<S> sorted = q;\n    std::sort(sorted.begin(),\
    \ sorted.end());\n\n    seq = sorted;\n\n    assert(std::equal(sorted.begin(),\
    \ sorted.end(), seq.begin()));\n    assert(std::equal(sorted.rbegin(), sorted.rend(),\
    \ seq.rbegin()));\n\n    for (int i = 0; i < n * k; ++i) {\n        assert(seq.begin()[i]\
    \ == i / k);\n    }\n\n    {\n        auto it = seq.begin();\n        for (int\
    \ q = 0; q < 100000; ++q) {\n            int a = rng() % (n * k + 1);\n      \
    \      auto it2 = seq.begin() + a;\n            it += it2 - it;\n            if\
    \ (a < n * k) {\n                assert(*it == a / k);\n            }\n      \
    \  }\n    }\n\n    for (int q = 0; q < 10000; ++q) {\n        int a = rng() %\
    \ (n * k + 1);\n        int b = rng() % (n * k + 1);\n        int d = b - a;\n\
    \        assert((seq.begin() + a) + d == seq.begin() + b);\n        assert(seq.begin()\
    \ + a == (seq.begin() + b) - d);\n\n        auto it1 = seq.begin() + a;\n    \
    \    auto it2 = seq.begin() + b;\n\n        if (d > 0) {\n            assert(not\
    \ (it1 == it2));\n            assert(it1 != it2);\n            assert(not (it1\
    \ > it2));\n            assert(not (it1 >= it2));\n            assert(it1 < it2);\n\
    \            assert(it1 <= it2);\n        } else if (d < 0) {\n            assert(not\
    \ (it1 == it2));\n            assert(it1 != it2);\n            assert(not (it1\
    \ < it2));\n            assert(not (it1 <= it2));\n            assert(it1 > it2);\n\
    \            assert(it1 >= it2);\n        } else {\n            assert(not (it1\
    \ != it2));\n            assert(it1 == it2);\n            assert(not (it1 > it2));\n\
    \            assert(not (it1 < it2));\n            assert(it1 <= it2);\n     \
    \       assert(it1 >= it2);\n        }\n\n        if (a != n * k and b != n *\
    \ k) {\n            assert(*it1 == a / k);\n            assert(*it2 == b / k);\n\
    \n            it1 += d;\n\n            assert(not (it1 != it2));\n           \
    \ assert(it1 == it2);\n            assert(not (it1 < it2));\n            assert(not\
    \ (it1 > it2));\n            assert(it1 <= it2);\n            assert(it1 >= it2);\n\
    \            assert(*it1 == *it2);\n        }\n    }\n\n    std::vector<S> naive\
    \ = sorted;\n    assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n\
    \n    // for (S& e : seq) --e; // Compile Error \n    // for (S& e : naive) --e;\n\
    \    // assert(std::equal(naive.begin(), naive.end(), seq.begin()));\n    // assert(std::equal(naive.rbegin(),\
    \ naive.rend(), seq.rbegin()));\n\n    const Tree& const_seq = const_cast<const\
    \ Tree&>(seq);\n    assert(std::equal(naive.begin(), naive.end(), const_seq.begin()));\n\
    \    assert(std::equal(naive.rbegin(), naive.rend(), const_seq.rbegin()));\n\n\
    \    for (int i = 0; i < n * k; ++i) {\n        assert(const_seq[i] == naive[i]);\n\
    \    }\n}\n\nint main() {\n    test();\n    test2();\n    std::cout << \"Hello\
    \ World\" << std::endl;\n    return 0;\n}"
  dependsOn:
  - library/datastructure/bbst/implicit_treap_segtree.hpp
  - library/datastructure/bbst/implicit_treap_base.hpp
  isVerificationFile: true
  path: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
  requiredBy: []
  timestamp: '2023-02-04 08:57:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
- /verify/test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp.html
title: test/src/datastructure/bbst/implicit_treap_segtree/dummy.test.cpp
---
