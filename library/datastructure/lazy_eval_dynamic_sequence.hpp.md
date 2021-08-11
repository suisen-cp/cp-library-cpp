---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/dynamic_sequence.hpp
    title: library/datastructure/dynamic_sequence.hpp
  - icon: ':heavy_check_mark:'
    path: library/datastructure/range_foldable_dynamic_sequence.hpp
    title: library/datastructure/range_foldable_dynamic_sequence.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: library/util/update_proxy_object.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\n\
    \n\n\n#include <cassert>\n#include <tuple>\n\n#line 1 \"library/util/update_proxy_object.hpp\"\
    \n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace suisen {\n// ! utility\ntemplate <typename\
    \ ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
    \ std::nullptr_t>;\ntemplate <bool cond_v, typename Then, typename OrElse>\nconstexpr\
    \ decltype(auto) constexpr_if(Then&& then, OrElse&& or_else) {\n    if constexpr\
    \ (cond_v) {\n        return std::forward<Then>(then);\n    } else {\n       \
    \ return std::forward<OrElse>(or_else);\n    }\n}\n\n// ! function\ntemplate <typename\
    \ ReturnType, typename Callable, typename ...Args>\nusing is_same_as_invoke_result\
    \ = std::is_same<std::invoke_result_t<Callable, Args...>, ReturnType>;\ntemplate\
    \ <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T, F, T>;\n\
    template <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
    \ F, T, T>;\n\ntemplate <typename Comparator, typename T>\nusing is_comparator\
    \ = std::is_same<std::invoke_result_t<Comparator, T, T>, bool>;\n\n// ! integral\n\
    template <typename T, typename = constraints_t<std::is_integral<T>>>\nconstexpr\
    \ int bit_num = std::numeric_limits<std::make_unsigned_t<T>>::digits;\ntemplate\
    \ <typename T, unsigned int n>\nstruct is_nbit { static constexpr bool value =\
    \ bit_num<T> == n; };\ntemplate <typename T, unsigned int n>\nstatic constexpr\
    \ bool is_nbit_v = is_nbit<T, n>::value;\n} // namespace suisen\n\n\n#line 5 \"\
    library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\n\ntemplate <typename\
    \ T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>> = nullptr>\n\
    struct UpdateProxyObject {\n    public:\n        UpdateProxyObject(T &v, UpdateFunc\
    \ update) : v(v), update(update) {}\n        operator T() const { return v; }\n\
    \        auto& operator++() && { ++v, update(); return *this; }\n        auto&\
    \ operator--() && { --v, update(); return *this; }\n        auto& operator+=(const\
    \ T &val) && { v += val, update(); return *this; }\n        auto& operator-=(const\
    \ T &val) && { v -= val, update(); return *this; }\n        auto& operator*=(const\
    \ T &val) && { v *= val, update(); return *this; }\n        auto& operator/=(const\
    \ T &val) && { v /= val, update(); return *this; }\n        auto& operator%=(const\
    \ T &val) && { v %= val, update(); return *this; }\n        auto& operator =(const\
    \ T &val) && { v  = val, update(); return *this; }\n        auto& operator<<=(const\
    \ T &val) && { v <<= val, update(); return *this; }\n        auto& operator>>=(const\
    \ T &val) && { v >>= val, update(); return *this; }\n        template <typename\
    \ F, constraints_t<is_uni_op<F, T>> = nullptr>\n        auto& apply(F f) && {\
    \ v = f(v), update(); return *this; }\n    private:\n        T &v;\n        UpdateFunc\
    \ update;\n};\n\n} // namespace suisen\n\n\n#line 1 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\
    \n\n\n\n#line 6 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\n\
    \n#line 1 \"library/datastructure/dynamic_sequence.hpp\"\n\n\n\n#include <cstddef>\n\
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
    \  root = SplayNode::insert(root, k, val);\n        }\n        void erase(int\
    \ k) {\n            index_bounds_check(k, size());\n            root = SplayNode::erase(root,\
    \ k);\n        }\n        int size() {\n            return SplayNode::size(root);\n\
    \        }\n        void reverse(int l, int r) {\n            range_bounds_check(l,\
    \ r, size());\n            root = SplayNode::reverse(root, l, r);\n        }\n\
    \        void reverse_all() {\n            SplayNode::reverese_all(root);\n  \
    \      }\n    protected:\n        node_ptr_t root;\n\n        DynamicSequenceBase(node_ptr_t\
    \ root) : root(root) {}\n    \n        static void index_bounds_check(unsigned\
    \ int k, unsigned int n) {\n            assert(k < n);\n        }\n        static\
    \ void range_bounds_check(unsigned int l, unsigned int r, unsigned int n) {\n\
    \            assert(l <= r and r <= n);\n        }\n};\n\ntemplate <typename T>\n\
    struct DynamicSequence : public DynamicSequenceBase<T, internal::dynamic_sequence::DynamicSequenceNode<T>>\
    \ {\n    using Node = internal::dynamic_sequence::DynamicSequenceNode<T>;\n  \
    \  using Base = DynamicSequenceBase<T, Node>;\n    using node_ptr_t = typename\
    \ Node::node_ptr_t;\n    public:\n        using value_type = T;\n        using\
    \ Base::DynamicSequenceBase;\n\n        DynamicSequence& operator=(const DynamicSequence&)\
    \ = delete;\n        DynamicSequence& operator=(DynamicSequence&& other) {\n \
    \           delete this->root;\n            this->root = other.root;\n       \
    \     other.root = nullptr;\n            return *this;\n        }\n\n        T&\
    \ operator[](int k) {\n            this->index_bounds_check(k, this->size());\n\
    \            this->root = Node::splay(this->root, k);\n            return this->root->val;\n\
    \        }\n\n        DynamicSequence& operator+=(DynamicSequence &&right) {\n\
    \            this->root = Node::merge(this->root, right.root);\n            right.root\
    \ = nullptr;\n            return *this;\n        }\n        void concat(DynamicSequence\
    \ &&right) {\n            *this += std::move(right);\n        }\n        void\
    \ concat_left(DynamicSequence &&left) {\n            this->root = (left += std::move(*this)).root;\n\
    \            left.root = nullptr;\n        }\n        // erases [k, size()) and\
    \ returns [k, size())\n        // template <typename T = decltype(*this), constraints_t<std::is_same<typename\
    \ T::Node, Node>> = nullptr>\n        DynamicSequence split(int k) {\n       \
    \     this->index_bounds_check(k, this->size() + 1);\n            auto [l, r]\
    \ = Node::split(this->root, k);\n            this->root = l;\n            return\
    \ DynamicSequence(r);\n        }\n};\n\n}\n\n\n#line 9 \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\
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
    \ other) {\n            delete this->root;\n            this->root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       RangeFoldableDynamicSequence& operator+=(RangeFoldableDynamicSequence\
    \ &&right) {\n            this->root = Node::merge(this->root, right.root);\n\
    \            right.root = nullptr;\n            return *this;\n        }\n   \
    \     void concat(RangeFoldableDynamicSequence &&right) {\n            *this +=\
    \ std::move(right);\n        }\n        void concat_left(RangeFoldableDynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \       left.root = nullptr;\n        }\n        // erases [k, size()) and returns\
    \ [k, size())\n        RangeFoldableDynamicSequence split(int k) {\n         \
    \   this->index_bounds_check(k, this->size() + 1);\n            auto [l, r] =\
    \ Node::split(this->root, k);\n            this->root = l;\n            return\
    \ RangeFoldableDynamicSequence(r);\n        }\n};\n\n}\n\n\n#line 9 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\
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
    \ other) {\n            delete this->root;\n            this->root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) {\n\
    \            this->root = Node::merge(this->root, right.root);\n            right.root\
    \ = nullptr;\n            return *this;\n        }\n        void concat(LazyEvalDynamicSequence\
    \ &&right) {\n            *this += std::move(right);\n        }\n        void\
    \ concat_left(LazyEvalDynamicSequence &&left) {\n            this->root = (left\
    \ += std::move(*this)).root;\n            left.root = nullptr;\n        }\n  \
    \      // erases [k, size()) and returns [k, size())\n        LazyEvalDynamicSequence\
    \ split(int k) {\n            this->index_bounds_check(k, this->size() + 1);\n\
    \            auto [l, r] = Node::split(this->root, k);\n            this->root\
    \ = l;\n            return LazyEvalDynamicSequence(r);\n        }\n};\n}\n\n\n"
  code: "#ifndef SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n#define SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n\
    \n#include <cassert>\n#include <tuple>\n\n#include \"library/util/update_proxy_object.hpp\"\
    \n#include \"library/datastructure/range_foldable_dynamic_sequence.hpp\"\n\nnamespace\
    \ suisen {\nnamespace internal::lazy_eval_dynamic_sequence {\n\ntemplate <typename\
    \ T, T(*op)(T, T), T (*e)(), typename F, T(*mapping)(F, T), F(*composition)(F,\
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
    \ other) {\n            delete this->root;\n            this->root = other.root;\n\
    \            other.root = nullptr;\n            return *this;\n        }\n\n \
    \       LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) {\n\
    \            this->root = Node::merge(this->root, right.root);\n            right.root\
    \ = nullptr;\n            return *this;\n        }\n        void concat(LazyEvalDynamicSequence\
    \ &&right) {\n            *this += std::move(right);\n        }\n        void\
    \ concat_left(LazyEvalDynamicSequence &&left) {\n            this->root = (left\
    \ += std::move(*this)).root;\n            left.root = nullptr;\n        }\n  \
    \      // erases [k, size()) and returns [k, size())\n        LazyEvalDynamicSequence\
    \ split(int k) {\n            this->index_bounds_check(k, this->size() + 1);\n\
    \            auto [l, r] = Node::split(this->root, k);\n            this->root\
    \ = l;\n            return LazyEvalDynamicSequence(r);\n        }\n};\n}\n\n#endif\
    \ // SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  - library/datastructure/range_foldable_dynamic_sequence.hpp
  - library/datastructure/dynamic_sequence.hpp
  isVerificationFile: false
  path: library/datastructure/lazy_eval_dynamic_sequence.hpp
  requiredBy: []
  timestamp: '2021-08-11 19:49:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
documentation_of: library/datastructure/lazy_eval_dynamic_sequence.hpp
layout: document
title: "\u53CD\u8EE2\u53EF\u80FD\u306A\u9045\u5EF6\u8A55\u4FA1\u4ED8\u304D\u5E73\u8861\
  \u4E8C\u5206\u63A2\u7D22\u6728"
---

### コンストラクタ

- シグネチャ

  ```cpp
  template <typename T, T(*op)(T, T), T(*e)(), typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
  LazyEvalDynamicSequence()
  ```

- 概要

  空の列で初期化します．

  以下で用いる表記について先に説明しておきます．

  - $T$ 上の二項演算 $\mathrm{op}(x,y)$ を $x\cdot y$ と書きます
  - $F$ 上の二項演算 $\mathrm{composition}(f,g)$ を $f\circ g$ と書きます
  - $f\in F:T\to T$ を $x\in T$ に作用させる演算 $\mathrm{mapping}(f,x)$ を $f(x)$ と書きます

- テンプレート引数 (`<atcoder/lazysegtree>` と同じです)

  - `T`: 列の要素の型
  - `T(*op)(T, T)`: 二項演算 $\cdot$
  - `T (*e)()`: モノイド $(T,\cdot)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)
  - `F`: 区間作用の作用素型
  - `T(*mapping)(F, T)`: 一点作用の関数
  - `F(*composition)(F, F)`: 二項演算 $\circ$
  - `F (*id)()`: モノイド $(F,\circ)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)

- 制約

  - $\forall x\in T.\;e\cdot x=x\cdot e=x$
  - $\forall f\in F.\;f\circ \mathrm{id}=\mathrm{id}\circ f=f$
  - $\forall x\in T.\;\mathrm{id}(x)=x$
  - $\forall x,y\in T,\;\forall f\in F.\;f(x\cdot y)=f(x)\cdot f(y)$

- 時間計算量

  $O(1)$

### 要素の挿入

- シグネチャ

  ```cpp
  void insert(int k, const T& val)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素の前に値 `val` を挿入します．ただし，$k$ が列の長さと等しい場合は列の末尾に `val` を追加します．

  つまり，変更前の列を $(A_0,\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,\mathrm{val},A_k,\ldots,A_{N-1})$ となります．

- 制約

  要素を挿入する前の列の長さを $N$ として，$0\leq k\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 要素の削除

- シグネチャ

  ```cpp
  void erase(int k)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素を削除します．

  つまり，変更前の列を $(A_0,\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,A_{k-1},A_{k+1},\ldots,A_{N-1})$ となります．

- 制約

  要素を挿入する前の列の長さを $N$ として，$0\leq k\lt N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 要素の取得

- シグネチャ

  ```cpp
  auto operator[](int k)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素を取得します．返り値は `library/util/update_proxy_object` で定義されている `UpdateProxyObject<T, ...>` 型ですが，

    ```cpp
    // a: LazyEvalDynamicSequence<int, ...>
    a[0] += 2;    // 更新
    int x = a[1]; // 取得
    ```

  のように `std::vector` と基本的には同じような使い方が出来ます．
  
  `UpdateProxyObject<T, ...>` 型を返すのは，値の更新後に区間積を更新する必要があるためです．

- 制約

  列の長さを $N$ として，$0\leq k\lt N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間積取得

- シグネチャ

  ```cpp
  T prod(int l, int r) // (1)
  T operator()(int l, int r) // (2)
  ```

- 概要

  (1) と (2) は等価であり，どちらも区間積 $A_l\cdot A_{l+1}\cdot\cdots\cdot A_{r-1}$ を計算します．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間作用

- シグネチャ

  ```cpp
  T apply(int l, int r, const F &f)
  ```

- 概要

  $A_l,\ldots,A_{r-1}$ を $f(A_l),\ldots,f(A_{r-1})$ で更新します．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間反転

- シグネチャ

  ```cpp
  T reverse(int l, int r)
  ```

- 概要

  $A_l,\ldots,A_{r-1}$ を反転します．

  つまり，変更前の列を $(A_0,\ldots,A_{l-1},\underline{A_l,\ldots,A_{r-1}},A_{r},\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,A_{l-1},\underline{A_{r-1},\ldots,A_{l+1},A_{l}},A_{r},\ldots,A_{N-1})$ となります．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 列の連結

- シグネチャ

  ```cpp
  LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) // (1)
  void concat(LazyEvalDynamicSequence &&right) // (2)
  void concat_left(LazyEvalDynamicSequence &&left) // (3)
  ```

- 概要

  列を連結します．(1) と (2) では後ろに連結し，(3) では前に連結します．

  コピーを避けるために，引数として与える列は右辺値であることを要求します．

- 時間計算量

  $\mathrm{amortized}\; O(\log \max(L,R))$

### 列の分割

- シグネチャ

  ```cpp
  LazyEvalDynamicSequence split(int k)
  ```

- 概要

  列を分割します．分割前の列を $(A_0,\ldots,A_{k-1},A_{k},\ldots,A_{N-1})$ とすると，分割後は $(A_0,\ldots,A_{k-1})$ となり，$(A_k,\ldots,A_{N-1})$ を返します．

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$