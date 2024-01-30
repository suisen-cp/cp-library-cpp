---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  _extendedRequiredBy:
  - icon: ':x:'
    path: library/datastructure/lazy_eval_dynamic_sequence.hpp
    title: "\u53CD\u8EE2\u53EF\u80FD\u306A\u9045\u5EF6\u8A55\u4FA1\u4ED8\u304D\u5E73\
      \u8861\u4E8C\u5206\u63A2\u7D22\u6728"
  - icon: ':x:'
    path: library/datastructure/range_foldable_dynamic_sequence.hpp
    title: Range Foldable Dynamic Sequence
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/dynamic_sequence.hpp\"\n\n\n\n#include\
    \ <cstddef>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n#line\
    \ 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <iostream>\n#include <type_traits>\n\nnamespace suisen {\n    template <typename\
    \ ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>,\
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
    } // namespace suisen\n\n#line 10 \"library/datastructure/dynamic_sequence.hpp\"\
    \n\nnamespace suisen {\n\nnamespace internal::dynamic_sequence {\n\ntemplate <typename\
    \ T, typename Derived>\nstruct DynamicSequenceNodeBase {\n    using node_ptr_t\
    \ = Derived *;\n\n    T val;\n    int siz;\n    bool rev;\n    node_ptr_t ch[2]\
    \ {nullptr, nullptr};\n\n    DynamicSequenceNodeBase() : val(), siz(1), rev(false)\
    \ {}\n    DynamicSequenceNodeBase(const T &val) : val(val), siz(1), rev(false)\
    \ {}\n\n    ~DynamicSequenceNodeBase() {\n        delete ch[0];\n        delete\
    \ ch[1];\n    }\n\n    void update() {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n\
    \    }\n    void push() {\n        reverse_all(this->ch[0], rev), reverse_all(this->ch[1],\
    \ rev);\n        rev = false;\n    }\n    static int size(node_ptr_t node) {\n\
    \        return node == nullptr ? 0 : node->siz;\n    }\n\n    static node_ptr_t\
    \ rotate(node_ptr_t node, bool is_right) {\n        node_ptr_t root = node->ch[is_right\
    \ ^ true];\n        node->ch[is_right ^ true] = root->ch[is_right];\n        root->ch[is_right]\
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
    \ }\n};\n\n}\n\n\n"
  code: "#ifndef SUISEN_DYNAMIC_SEQUENCE\n#define SUISEN_DYNAMIC_SEQUENCE\n\n#include\
    \ <cstddef>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n#include\
    \ \"library/type_traits/type_traits.hpp\"\n\nnamespace suisen {\n\nnamespace internal::dynamic_sequence\
    \ {\n\ntemplate <typename T, typename Derived>\nstruct DynamicSequenceNodeBase\
    \ {\n    using node_ptr_t = Derived *;\n\n    T val;\n    int siz;\n    bool rev;\n\
    \    node_ptr_t ch[2] {nullptr, nullptr};\n\n    DynamicSequenceNodeBase() : val(),\
    \ siz(1), rev(false) {}\n    DynamicSequenceNodeBase(const T &val) : val(val),\
    \ siz(1), rev(false) {}\n\n    ~DynamicSequenceNodeBase() {\n        delete ch[0];\n\
    \        delete ch[1];\n    }\n\n    void update() {\n        siz = 1 + size(ch[0])\
    \ + size(ch[1]);\n    }\n    void push() {\n        reverse_all(this->ch[0], rev),\
    \ reverse_all(this->ch[1], rev);\n        rev = false;\n    }\n    static int\
    \ size(node_ptr_t node) {\n        return node == nullptr ? 0 : node->siz;\n \
    \   }\n\n    static node_ptr_t rotate(node_ptr_t node, bool is_right) {\n    \
    \    node_ptr_t root = node->ch[is_right ^ true];\n        node->ch[is_right ^\
    \ true] = root->ch[is_right];\n        root->ch[is_right] = node;\n        node->update(),\
    \ root->update();\n        return root;\n    }\n\n    static node_ptr_t splay(node_ptr_t\
    \ node, int index) {\n        std::vector<node_ptr_t> path;\n        node_ptr_t\
    \ work_root = new Derived();\n        node_ptr_t work_leaf[2] { work_root, work_root\
    \ };\n        while (true) {\n            node->push();\n            int size_l\
    \ = size(node->ch[0]);\n            bool is_right = index > size_l;\n        \
    \    node_ptr_t next_node = node->ch[is_right];\n            if (index == size_l\
    \ or next_node == nullptr) { // found the target node\n                break;\n\
    \            }\n            if (is_right) {\n                index -= size_l +\
    \ 1;\n            }\n            int size_l_ch = size(next_node->ch[0]);\n   \
    \         if (index != size_l_ch) {\n                bool is_right_ch = index\
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
    \ }\n};\n\n}\n\n#endif // SUISEN_DYNAMIC_SEQUENCE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/dynamic_sequence.hpp
  requiredBy:
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  timestamp: '2023-09-15 20:02:25+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
documentation_of: library/datastructure/dynamic_sequence.hpp
layout: document
title: Dynamic Sequence
---
## Dynamic Sequence