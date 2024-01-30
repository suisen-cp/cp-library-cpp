---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/dynamic_sequence.hpp
    title: Dynamic Sequence
  - icon: ':x:'
    path: library/datastructure/lazy_eval_dynamic_sequence.hpp
    title: "\u53CD\u8EE2\u53EF\u80FD\u306A\u9045\u5EF6\u8A55\u4FA1\u4ED8\u304D\u5E73\
      \u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':x:'
    path: library/datastructure/range_foldable_dynamic_sequence.hpp
    title: Range Foldable Dynamic Sequence
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':x:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <tuple>\n\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #line 6 \"library/type_traits/type_traits.hpp\"\n#include <type_traits>\n\nnamespace\
    \ suisen {\n    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
    \ std::nullptr_t>;\n\n    template <typename T, typename = std::nullptr_t> struct\
    \ bitnum { static constexpr int value = 0; };\n    template <typename T> struct\
    \ bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value =\
    \ std::numeric_limits<std::make_unsigned_t<T>>::digits; };\n    template <typename\
    \ T> static constexpr int bitnum_v = bitnum<T>::value;\n    template <typename\
    \ T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n;\
    \ };\n    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T,\
    \ n>::value;\n\n    template <typename T, typename = std::nullptr_t> struct safely_multipliable\
    \ { using type = T; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long;\
    \ };\n    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>,\
    \ is_nbit<T, 64>>> { using type = __int128_t; };\n    template <typename T> struct\
    \ safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {\
    \ using type = unsigned long long; };\n    template <typename T> struct safely_multipliable<T,\
    \ constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t;\
    \ };\n    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;\n\
    \n    template <typename T, typename = void> struct rec_value_type { using type\
    \ = T; };\n    template <typename T> struct rec_value_type<T, std::void_t<typename\
    \ T::value_type>> {\n        using type = typename rec_value_type<typename T::value_type>::type;\n\
    \    };\n    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;\n\
    \n    template <typename T> class is_iterable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;\n\
    \    template <typename T> class is_writable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_writable_v = is_writable<T>::value;\n\
    \    template <typename T> class is_readable {\n        template <typename T_>\
    \ static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});\n\
    \        static std::false_type test(...);\n    public:\n        static constexpr\
    \ bool value = decltype(test(std::declval<T>()))::value;\n    };\n    template\
    \ <typename T> static constexpr bool is_readable_v = is_readable<T>::value;\n\
    } // namespace suisen\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
    namespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
    \ = nullptr>\nstruct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T\
    \ &v, UpdateFunc update) : v(v), update(update) {}\n        operator T() const\
    \ { return v; }\n        auto& operator++() && { ++v, update(); return *this;\
    \ }\n        auto& operator--() && { --v, update(); return *this; }\n        auto&\
    \ operator+=(const T &val) && { v += val, update(); return *this; }\n        auto&\
    \ operator-=(const T &val) && { v -= val, update(); return *this; }\n        auto&\
    \ operator*=(const T &val) && { v *= val, update(); return *this; }\n        auto&\
    \ operator/=(const T &val) && { v /= val, update(); return *this; }\n        auto&\
    \ operator%=(const T &val) && { v %= val, update(); return *this; }\n        auto&\
    \ operator =(const T &val) && { v  = val, update(); return *this; }\n        auto&\
    \ operator<<=(const T &val) && { v <<= val, update(); return *this; }\n      \
    \  auto& operator>>=(const T &val) && { v >>= val, update(); return *this; }\n\
    \        template <typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr>\n\
    \        auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 1 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\n\n\n\n\
    #line 6 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\n\n#line\
    \ 1 \"library/datastructure/dynamic_sequence.hpp\"\n\n\n\n#include <cstddef>\n\
    #line 7 \"library/datastructure/dynamic_sequence.hpp\"\n#include <vector>\n\n\
    #line 10 \"library/datastructure/dynamic_sequence.hpp\"\n\nnamespace suisen {\n\
    \nnamespace internal::dynamic_sequence {\n\ntemplate <typename T, typename Derived>\n\
    struct DynamicSequenceNodeBase {\n    using node_ptr_t = Derived *;\n\n    T val;\n\
    \    int siz;\n    bool rev;\n    node_ptr_t ch[2] {nullptr, nullptr};\n\n   \
    \ DynamicSequenceNodeBase() : val(), siz(1), rev(false) {}\n    DynamicSequenceNodeBase(const\
    \ T &val) : val(val), siz(1), rev(false) {}\n\n    ~DynamicSequenceNodeBase()\
    \ {\n        delete ch[0];\n        delete ch[1];\n    }\n\n    void update()\
    \ {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n    }\n    void push() {\n\
    \        reverse_all(this->ch[0], rev), reverse_all(this->ch[1], rev);\n     \
    \   rev = false;\n    }\n    static int size(node_ptr_t node) {\n        return\
    \ node == nullptr ? 0 : node->siz;\n    }\n\n    static node_ptr_t rotate(node_ptr_t\
    \ node, bool is_right) {\n        node_ptr_t root = node->ch[is_right ^ true];\n\
    \        node->ch[is_right ^ true] = root->ch[is_right];\n        root->ch[is_right]\
    \ = node;\n        node->update(), root->update();\n        return root;\n   \
    \ }\n\n    static node_ptr_t splay(node_ptr_t node, int index) {\n        std::vector<node_ptr_t>\
    \ path;\n        node_ptr_t work_root = new Derived();\n        node_ptr_t work_leaf[2]\
    \ { work_root, work_root };\n        while (true) {\n            node->push();\n\
    \            int size_l = size(node->ch[0]);\n            bool is_right = index\
    \ > size_l;\n            node_ptr_t next_node = node->ch[is_right];\n        \
    \    if (index == size_l or next_node == nullptr) { // found the target node\n\
    \                break;\n            }\n            if (is_right) {\n        \
    \        index -= size_l + 1;\n            }\n            int size_l_ch = size(next_node->ch[0]);\n\
    \            if (index != size_l_ch) {\n                bool is_right_ch = index\
    \ > size_l_ch;\n                if (is_right_ch == is_right) { // zig-zig\n  \
    \                  if (is_right_ch) {\n                        index -= size_l_ch\
    \ + 1;\n                    }\n                    next_node->push();\n      \
    \              node = rotate(node, is_right ^ true);\n                    next_node\
    \ = node->ch[is_right];\n                    if (next_node == nullptr) { // found\
    \ the target node\n                        break;\n                    }\n   \
    \             }\n            }\n            path.push_back(node);\n          \
    \  work_leaf[is_right]->ch[is_right] = node;\n            work_leaf[is_right]\
    \ = node;\n            node = next_node;\n        }\n        work_leaf[0]->ch[0]\
    \ = node->ch[1];\n        work_leaf[1]->ch[1] = node->ch[0];\n        node->ch[0]\
    \ = work_root->ch[1];\n        node->ch[1] = work_root->ch[0];\n    \n       \
    \ work_root->ch[0] = work_root->ch[1] = nullptr;\n        delete work_root;\n\n\
    \        while (path.size()) {\n            path.back()->update(), path.pop_back();\n\
    \        }\n        node->update();\n\n        return node;\n    }\n\n    static\
    \ std::pair<node_ptr_t, node_ptr_t> split(node_ptr_t node, int k) {\n        if\
    \ (k == 0) return { nullptr, node };\n        if (k == size(node)) return { node,\
    \ nullptr };\n        node_ptr_t r = splay(node, k);\n        node_ptr_t l = r->ch[0];\n\
    \        r->ch[0] = nullptr;\n        r->update();\n        return { l, r };\n\
    \    }\n    static std::tuple<node_ptr_t, node_ptr_t, node_ptr_t> split(node_ptr_t\
    \ node, int l, int r) {\n        auto [tl, tmr] = split(node, l);\n        auto\
    \ [tm, tr] = split(tmr, r - l);\n        return { tl, tm, tr };\n    }\n    static\
    \ node_ptr_t merge(node_ptr_t l, node_ptr_t r) {\n        if (l == nullptr) return\
    \ r;\n        if (r == nullptr) return l;\n        node_ptr_t new_root = splay(r,\
    \ 0);\n        new_root->ch[0] = l;\n        new_root->update();\n        return\
    \ new_root;\n    }\n    static node_ptr_t merge(node_ptr_t tl, node_ptr_t tm,\
    \ node_ptr_t tr) {\n        return merge(merge(tl, tm), tr);\n    }\n    static\
    \ node_ptr_t insert(node_ptr_t node, int index, const T &val) {\n        node_ptr_t\
    \ new_node = new Derived(val);\n        if (index == 0) {\n            new_node->ch[1]\
    \ = node;\n            new_node->update();\n            return new_node;\n   \
    \     } else if (index == size(node)) {\n            new_node->ch[0] = node;\n\
    \            new_node->update();\n            return new_node;\n        } else\
    \ {\n            auto [l, r] = split(node, index);\n            new_node->ch[0]\
    \ = l;\n            new_node->update();\n            r->ch[0] = new_node;\n  \
    \          r->update();\n            return r;\n        }\n    }\n    static node_ptr_t\
    \ erase(node_ptr_t node, int index) {\n        auto [l, r] = split(index ? node\
    \ : splay(node, 0), index);\n        node_ptr_t res = merge(l, r->ch[1]);\n  \
    \      r->ch[1] = nullptr;\n        delete r;\n        return res;\n    }\n\n\
    \    static void reverse_all(node_ptr_t node, bool rev = true) {\n        if (node\
    \ != nullptr and rev) {\n            std::swap(node->ch[0], node->ch[1]);\n  \
    \          node->rev ^= true;\n        }\n    }\n    static node_ptr_t reverse(node_ptr_t\
    \ node, int l, int r) {\n        auto [tl, tm, tr] = split(node, l, r);\n    \
    \    reverse_all(tm);\n        return merge(tl, tm, tr);\n    }\n};\n\ntemplate\
    \ <typename T>\nstruct DynamicSequenceNode : public DynamicSequenceNodeBase<T,\
    \ DynamicSequenceNode<T>> {\n    using Base = DynamicSequenceNodeBase<T, DynamicSequenceNode<T>>;\n\
    \    using Base::DynamicSequenceNodeBase;\n    using node_ptr_t = typename Base::node_ptr_t;\n\
    };\n}\n\ntemplate <typename T, typename SplayNode>\nstruct DynamicSequenceBase\
    \ {\n    using node_ptr_t = typename SplayNode::node_ptr_t;\n    public:\n   \
    \     using value_type = T;\n\n        DynamicSequenceBase() : root(nullptr) {}\n\
    \        ~DynamicSequenceBase() { delete root; }\n\n        void insert(int k,\
    \ const T& val) {\n            index_bounds_check(k, size() + 1);\n          \
    \  root = SplayNode::insert(root, k, val);\n        }\n        void push_front(const\
    \ T &val) {\n            insert(0, val);\n        }\n        void push_back(const\
    \ T &val) {\n            insert(size(), val);\n        }\n        void erase(int\
    \ k) {\n            index_bounds_check(k, size());\n            root = SplayNode::erase(root,\
    \ k);\n        }\n        void pop_back() {\n            erase(size() - 1);\n\
    \        }\n        void pop_front() {\n            erase(0);\n        }\n   \
    \     int size() const {\n            return SplayNode::size(root);\n        }\n\
    \        void reverse(int l, int r) {\n            range_bounds_check(l, r, size());\n\
    \            root = SplayNode::reverse(root, l, r);\n        }\n        void reverse_all()\
    \ {\n            SplayNode::reverese_all(root);\n        }\n    protected:\n \
    \       mutable node_ptr_t root;\n\n        DynamicSequenceBase(node_ptr_t root)\
    \ : root(root) {}\n    \n        static void index_bounds_check(unsigned int k,\
    \ unsigned int n) {\n            assert(k < n);\n        }\n        static void\
    \ range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {\n     \
    \       assert(l <= r and r <= n);\n        }\n};\n\ntemplate <typename T>\nstruct\
    \ DynamicSequence : public DynamicSequenceBase<T, internal::dynamic_sequence::DynamicSequenceNode<T>>\
    \ {\n    using Node = internal::dynamic_sequence::DynamicSequenceNode<T>;\n  \
    \  using Base = DynamicSequenceBase<T, Node>;\n    using node_ptr_t = typename\
    \ Node::node_ptr_t;\n    public:\n        using value_type = T;\n        using\
    \ Base::DynamicSequenceBase;\n\n        DynamicSequence& operator=(const DynamicSequence&)\
    \ = delete;\n        DynamicSequence& operator=(DynamicSequence&& other) {\n \
    \           delete this->root;\n            this->root = other.root;\n       \
    \     other.root = nullptr;\n            return *this;\n        }\n\n        T&\
    \ operator[](int k) {\n            this->index_bounds_check(k, this->size());\n\
    \            this->root = Node::splay(this->root, k);\n            return this->root->val;\n\
    \        }\n        const T& operator[](int k) const {\n            this->index_bounds_check(k,\
    \ this->size());\n            this->root = Node::splay(this->root, k);\n     \
    \       return this->root->val;\n        }\n        T& front() {\n           \
    \ return (*this)[0];\n        }\n        const T& front() const {\n          \
    \  return (*this)[0];\n        }\n        T& back() {\n            return (*this)[this->size()\
    \ - 1];\n        }\n        const T& back() const {\n            return (*this)[this->size()\
    \ - 1];\n        }\n\n        DynamicSequence& operator+=(DynamicSequence &&right)\
    \ {\n            this->root = Node::merge(this->root, right.root);\n         \
    \   right.root = nullptr;\n            return *this;\n        }\n        void\
    \ concat(DynamicSequence &&right) {\n            *this += std::move(right);\n\
    \        }\n        void concat_left(DynamicSequence &&left) {\n            this->root\
    \ = (left += std::move(*this)).root;\n            left.root = nullptr;\n     \
    \   }\n        // erases [k, size()) and returns [k, size())\n        // template\
    \ <typename T = decltype(*this), constraints_t<std::is_same<typename T::Node,\
    \ Node>> = nullptr>\n        DynamicSequence split(int k) {\n            this->index_bounds_check(k,\
    \ this->size() + 1);\n            auto [l, r] = Node::split(this->root, k);\n\
    \            this->root = l;\n            return DynamicSequence(r);\n       \
    \ }\n};\n\n}\n\n\n#line 9 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::range_foldable_dynamic_sequence {\n\
    \ntemplate <typename T, T(*op)(T, T), T (*e)(), typename Derived>\nstruct RangeFoldableDynamicSequenceNodeBase\
    \ : public internal::dynamic_sequence::DynamicSequenceNodeBase<T, Derived> {\n\
    \    using Base = internal::dynamic_sequence::DynamicSequenceNodeBase<T, Derived>;\n\
    \    using node_ptr_t = typename Base::node_ptr_t;\n    T dat;\n    RangeFoldableDynamicSequenceNodeBase()\
    \ : RangeFoldableDynamicSequenceNodeBase(e()) {}\n    RangeFoldableDynamicSequenceNodeBase(const\
    \ T &val) : Base::DynamicSequenceNodeBase(val), dat(val) {}\n    void update()\
    \ {\n        Base::update();\n        dat = op(op(prod_all(this->ch[0]), this->val),\
    \ prod_all(this->ch[1]));\n    }\n    static T prod_all(node_ptr_t node) {\n \
    \       return node == nullptr ? e() : node->dat;\n    }\n    static std::pair<node_ptr_t,\
    \ T> prod(node_ptr_t node, int l, int r) {\n        auto [tl, tm, tr] = Base::split(node,\
    \ l, r);\n        T res = prod_all(tm);\n        return { Base::merge(tl, tm,\
    \ tr), res };\n    }\n};\n\ntemplate <typename T, T(*op)(T, T), T (*e)()>\nstruct\
    \ RangeFoldableDynamicSequenceNode : public RangeFoldableDynamicSequenceNodeBase<T,\
    \ op, e, RangeFoldableDynamicSequenceNode<T, op, e>> {\n    using Base = RangeFoldableDynamicSequenceNodeBase<T,\
    \ op, e, RangeFoldableDynamicSequenceNode<T, op, e>>;\n    using Base::RangeFoldableDynamicSequenceNodeBase;\n\
    \    using node_ptr_t = typename Base::node_ptr_t;\n};\n}\n\ntemplate <typename\
    \ T, T(*op)(T, T), T (*e)(), typename SplayNode>\nclass RangeFoldableDynamicSequenceBase\
    \ : public DynamicSequenceBase<T, SplayNode> {\n    using Base = DynamicSequenceBase<T,\
    \ SplayNode>;\n    using node_ptr_t = typename SplayNode::node_ptr_t;\n    public:\n\
    \        using value_type = T;\n        using Base::DynamicSequenceBase;\n   \
    \     auto operator[](int k) {\n            this->index_bounds_check(k, this->size());\n\
    \            this->root = SplayNode::splay(this->root, k);\n            return\
    \ UpdateProxyObject { this->root->val, [this]{ this->root->update(); } };\n  \
    \      }\n        T operator()(int l, int r) {\n            return prod(l, r);\n\
    \        }\n        T prod(int l, int r) {\n            this->range_bounds_check(l,\
    \ r, this->size());\n            auto [new_root, res] = SplayNode::prod(this->root,\
    \ l, r);\n            this->root = new_root;\n            return res;\n      \
    \  }\n        T prod_all() {\n            return SplayNode::prod_all(this->root);\n\
    \        }\n};\n\ntemplate <typename T, T(*op)(T, T), T (*e)()>\nclass RangeFoldableDynamicSequence\
    \ : public RangeFoldableDynamicSequenceBase<T, op, e, internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNode<T,\
    \ op, e>> {\n    using Node = internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNode<T,\
    \ op, e>;\n    using Base = RangeFoldableDynamicSequenceBase<T, op, e, Node>;\n\
    \    using node_ptr_t = typename Node::node_ptr_t;\n    public:\n        using\
    \ value_type = T;\n        using Base::RangeFoldableDynamicSequenceBase;\n\n \
    \       RangeFoldableDynamicSequence& operator=(RangeFoldableDynamicSequence&\
    \  other) = delete;\n        RangeFoldableDynamicSequence& operator=(RangeFoldableDynamicSequence&&\
    \ other) {\n            if (other.root == this->root) return *this;\n        \
    \    delete this->root;\n            this->root = other.root;\n            other.root\
    \ = nullptr;\n            return *this;\n        }\n\n        RangeFoldableDynamicSequence&\
    \ operator+=(RangeFoldableDynamicSequence &&right) {\n            this->root =\
    \ Node::merge(this->root, right.root);\n            right.root = nullptr;\n  \
    \          return *this;\n        }\n        void concat(RangeFoldableDynamicSequence\
    \ &&right) {\n            *this += std::move(right);\n        }\n        void\
    \ concat_left(RangeFoldableDynamicSequence &&left) {\n            this->root =\
    \ (left += std::move(*this)).root;\n            left.root = nullptr;\n       \
    \ }\n        // erases [k, size()) and returns [k, size())\n        RangeFoldableDynamicSequence\
    \ split(int k) {\n            this->index_bounds_check(k, this->size() + 1);\n\
    \            auto [l, r] = Node::split(this->root, k);\n            this->root\
    \ = l;\n            return RangeFoldableDynamicSequence(r);\n        }\n     \
    \   void swap(RangeFoldableDynamicSequence &r) {\n            std::swap(this->root,\
    \ r.root);\n        }\n};\n\n}\n\n\n#line 9 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::lazy_eval_dynamic_sequence {\n\ntemplate\
    \ <typename T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F,\
    \ F), F(*id)(), typename Derived>\nstruct LazyEvalDynamicSequenceNodeBase : public\
    \ internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNodeBase<T,\
    \ op, e, Derived> {\n    using Base = internal::range_foldable_dynamic_sequence::RangeFoldableDynamicSequenceNodeBase<T,\
    \ op, e, Derived>;\n    using node_ptr_t = typename Base::node_ptr_t;\n    F laz;\n\
    \n    LazyEvalDynamicSequenceNodeBase() : LazyEvalDynamicSequenceNodeBase(e())\
    \ {}\n    LazyEvalDynamicSequenceNodeBase(const T &val) : Base::RangeFoldableDynamicSequenceNodeBase(val),\
    \ laz(id()) {}\n\n    void push() {\n        Base::push();\n        apply_all(this->ch[0],\
    \ laz), apply_all(this->ch[1], laz);\n        laz = id();\n    }\n    static void\
    \ apply_all(node_ptr_t node, const F &f) {\n        if (node == nullptr) return;\n\
    \        node->val = mapping(f, node->val);\n        node->dat = mapping(f, node->dat);\n\
    \        node->laz = composition(f, node->laz);\n    }\n    static node_ptr_t\
    \ apply(node_ptr_t node, int l, int r, const F &f) {\n        auto [tl, tm, tr]\
    \ = Base::split(node, l, r);\n        apply_all(tm, f);\n        return Base::merge(tl,\
    \ tm, tr);\n    }\n};\n\ntemplate <typename T, T(*op)(T, T), T (*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\nstruct LazyEvalDynamicSequenceNode\
    \ : public LazyEvalDynamicSequenceNodeBase<T, op, e, F, mapping, composition,\
    \ id, LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>> {\n\
    \    using Base = LazyEvalDynamicSequenceNodeBase<T, op, e, F, mapping, composition,\
    \ id, LazyEvalDynamicSequenceNode<T, op, e, F, mapping, composition, id>>;\n \
    \   using Base::LazyEvalDynamicSequenceNodeBase;\n    using node_ptr_t = typename\
    \ Base::node_ptr_t;\n};\n}\n\ntemplate <typename T, T(*op)(T, T), T (*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)(), typename SplayNode>\n\
    class LazyEvalDynamicSequenceBase : public RangeFoldableDynamicSequenceBase<T,\
    \ op, e, SplayNode> {\n    using Base = RangeFoldableDynamicSequenceBase<T, op,\
    \ e, SplayNode>;\n    using node_ptr_t = typename SplayNode::node_ptr_t;\n   \
    \ public:\n        using value_type = T;\n        using Base::RangeFoldableDynamicSequenceBase;\n\
    \        void apply(int l, int r, const F &f) {\n            this->range_bounds_check(l,\
    \ r, this->size());\n            this->root = SplayNode::apply(this->root, l,\
    \ r, f);\n        }\n        void apply_all(const F &f) {\n            SplayNode::apply_all(this->root,\
    \ f);\n        }\n};\n\ntemplate <typename T, T(*op)(T, T), T (*e)(), typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\nclass LazyEvalDynamicSequence\
    \ : public LazyEvalDynamicSequenceBase<T, op, e, F, mapping, composition, id,\
    \ internal::lazy_eval_dynamic_sequence::LazyEvalDynamicSequenceNode<T, op, e,\
    \ F, mapping, composition, id>> {\n    using Node = internal::lazy_eval_dynamic_sequence::LazyEvalDynamicSequenceNode<T,\
    \ op, e, F, mapping, composition, id>;\n    using Base = LazyEvalDynamicSequenceBase<T,\
    \ op, e, F, mapping, composition, id, Node>;\n    using node_ptr_t = typename\
    \ Node::node_ptr_t;\n    public:\n        using value_type = T;\n        using\
    \ Base::LazyEvalDynamicSequenceBase;\n\n        LazyEvalDynamicSequence& operator=(LazyEvalDynamicSequence&\
    \  other) = delete;\n        LazyEvalDynamicSequence& operator=(LazyEvalDynamicSequence&&\
    \ other) {\n            if (other.root == this->root) return *this;\n        \
    \    delete this->root;\n            this->root = other.root;\n            other.root\
    \ = nullptr;\n            return *this;\n        }\n\n        LazyEvalDynamicSequence&\
    \ operator+=(LazyEvalDynamicSequence &&right) {\n            this->root = Node::merge(this->root,\
    \ right.root);\n            right.root = nullptr;\n            return *this;\n\
    \        }\n        void concat(LazyEvalDynamicSequence &&right) {\n         \
    \   *this += std::move(right);\n        }\n        void concat_left(LazyEvalDynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \       left.root = nullptr;\n        }\n        // erases [k, size()) and returns\
    \ [k, size())\n        LazyEvalDynamicSequence split(int k) {\n            this->index_bounds_check(k,\
    \ this->size() + 1);\n            auto [l, r] = Node::split(this->root, k);\n\
    \            this->root = l;\n            return LazyEvalDynamicSequence(r);\n\
    \        }\n        void swap(LazyEvalDynamicSequence &r) {\n            std::swap(this->root,\
    \ r.root);\n        }\n};\n}\n\n\n#line 9 \"test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \nusing suisen::LazyEvalDynamicSequence;\n\nstruct F {\n    mint a, b;\n    F\
    \ compose(F g) {\n        return F { a * g.a, a * g.b + b };\n    }\n};\n\nstd::pair<mint,\
    \ int> op(std::pair<mint, int> x, std::pair<mint, int> y) {\n    auto [xs, xl]\
    \ = x;\n    auto [ys, yl] = y;\n    return { xs + ys, xl + yl };\n}\nstd::pair<mint,\
    \ int> e() {\n    return { 0, 0 };\n}\n\nstd::pair<mint, int> mapping(F f, std::pair<mint,\
    \ int> x) {\n    return { f.a * x.first + f.b * x.second, x.second };\n}\nF composition(F\
    \ f, F g) {\n    return f.compose(g);\n}\nF id() {\n    return { 1, 0 };\n}\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    LazyEvalDynamicSequence<std::pair<mint, int>, op, e, F, mapping, composition,\
    \ id> seq;\n\n    int n, q;\n    std::cin >> n >> q;\n    for (int i = 0; i <\
    \ n; ++i) {\n        int a;\n        std::cin >> a;\n        seq.insert(i, { a,\
    \ 1 });\n    }\n    while (q --> 0) {\n        int t;\n        std::cin >> t;\n\
    \        if (t == 0) {\n            int i, x;\n            std::cin >> i >> x;\n\
    \            seq.insert(i, { x, 1 });\n        } else if (t == 1) {\n        \
    \    int i;\n            std::cin >> i;\n            seq.erase(i);\n        }\
    \ else if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            seq.reverse(l, r);\n        } else if (t == 3) {\n            int\
    \ l, r, a, b;\n            std::cin >> l >> r >> a >> b;\n            seq.apply(l,\
    \ r, { a, b });\n        } else {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            std::cout << seq(l, r).first.val() << '\\n';\n     \
    \   }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\nusing suisen::LazyEvalDynamicSequence;\n\
    \nstruct F {\n    mint a, b;\n    F compose(F g) {\n        return F { a * g.a,\
    \ a * g.b + b };\n    }\n};\n\nstd::pair<mint, int> op(std::pair<mint, int> x,\
    \ std::pair<mint, int> y) {\n    auto [xs, xl] = x;\n    auto [ys, yl] = y;\n\
    \    return { xs + ys, xl + yl };\n}\nstd::pair<mint, int> e() {\n    return {\
    \ 0, 0 };\n}\n\nstd::pair<mint, int> mapping(F f, std::pair<mint, int> x) {\n\
    \    return { f.a * x.first + f.b * x.second, x.second };\n}\nF composition(F\
    \ f, F g) {\n    return f.compose(g);\n}\nF id() {\n    return { 1, 0 };\n}\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    LazyEvalDynamicSequence<std::pair<mint, int>, op, e, F, mapping, composition,\
    \ id> seq;\n\n    int n, q;\n    std::cin >> n >> q;\n    for (int i = 0; i <\
    \ n; ++i) {\n        int a;\n        std::cin >> a;\n        seq.insert(i, { a,\
    \ 1 });\n    }\n    while (q --> 0) {\n        int t;\n        std::cin >> t;\n\
    \        if (t == 0) {\n            int i, x;\n            std::cin >> i >> x;\n\
    \            seq.insert(i, { x, 1 });\n        } else if (t == 1) {\n        \
    \    int i;\n            std::cin >> i;\n            seq.erase(i);\n        }\
    \ else if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            seq.reverse(l, r);\n        } else if (t == 3) {\n            int\
    \ l, r, a, b;\n            std::cin >> l >> r >> a >> b;\n            seq.apply(l,\
    \ r, { a, b });\n        } else {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            std::cout << seq(l, r).first.val() << '\\n';\n     \
    \   }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/dynamic_sequence.hpp
  isVerificationFile: true
  path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2024-01-30 22:04:45+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
---
