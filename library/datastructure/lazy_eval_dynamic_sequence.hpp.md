---
data:
  _extendedDependsOn:
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
    \n\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n#include <utility>\n\
    \n#line 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
    \n\n\n\n#include <limits>\n#include <type_traits>\n\nnamespace suisen {\n// !\
    \ utility\ntemplate <typename ...Types>\nusing constraints_t = std::enable_if_t<std::conjunction_v<Types...>,\
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
    \ update;\n};\n\n} // namespace suisen\n\n\n#line 10 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\
    \n\nnamespace suisen {\nnamespace internal::lazy_eval_dynamic_sequence {\n\nstatic\
    \ constexpr int LOC_LEFT = 0;\nstatic constexpr int LOC_RIGHT = 1;\nstatic constexpr\
    \ int LOC_ROOT = 2;\n\ntemplate <typename T, T (*e)(), T(*op)(T, T), typename\
    \ F, F (*id)(), T(*mapping)(F, T), F(*composition)(F, F)>\nstruct Node {\n   \
    \ T val;\n    T dat;\n    F laz;\n    bool rev;\n    int siz;\n    Node *ch[2]\
    \ {nullptr, nullptr};\n    Node() : val(e()), dat(e()), laz(id()), rev(false),\
    \ siz(1) {}\n    Node(const T &val) : val(val), dat(val), laz(id()), rev(false),\
    \ siz(1) {}\n    ~Node() {\n        delete ch[0];\n        delete ch[1];\n   \
    \ }\n    void update() {\n        siz = 1 + size(ch[0]) + size(ch[1]);\n     \
    \   dat = op(op(prod_subtree(ch[0]), val), prod_subtree(ch[1]));\n    }\n    void\
    \ push() {\n        apply(ch[0], laz), apply_rev(ch[0], rev);\n        apply(ch[1],\
    \ laz), apply_rev(ch[1], rev);\n        laz = id(), rev = false;\n    }\n    static\
    \ T prod_subtree(Node *node) {\n        return node == nullptr ? e() : node->dat;\n\
    \    }\n    static void apply(Node *node, const F &f) {\n        if (node == nullptr)\
    \ return;\n        node->val = mapping(f, node->val);\n        node->dat = mapping(f,\
    \ node->dat);\n        node->laz = composition(f, node->laz);\n    }\n    static\
    \ void apply_rev(Node *node, bool rev = true) {\n        if (node == nullptr)\
    \ return;\n        if (rev) std::swap(node->ch[0], node->ch[1]);\n        node->rev\
    \ ^= rev;\n    }\n    static int size(Node *node) {\n        return node == nullptr\
    \ ? 0 : node->siz;\n    }\n    static Node* rotate(Node *node, int dir) { // dir:\
    \ LEFT = 0, RIGHT = 1\n        assert(node->ch[dir ^ 1] != nullptr);\n       \
    \ Node *par = node->ch[dir ^ 1];\n        node->ch[dir ^ 1] = par->ch[dir];\n\
    \        par->ch[dir] = node;\n        node->update(), par->update();\n      \
    \  return par;\n    }\n    static int locate(Node *node, int index) {\n      \
    \  int siz_l = size(node->ch[0]);\n        return index == siz_l ? LOC_ROOT :\
    \ index > siz_l;\n    }\n    static Node* splay(Node *node, int index) {\n   \
    \     std::vector<Node*> path;\n        Node *work_root = new Node();\n      \
    \  Node *work_leaf[2] {work_root, work_root};\n        while (true) {\n      \
    \      node->push();\n            int loc = locate(node, index);\n           \
    \ if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;\n            if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[0]) + 1;\n            int ch_loc = locate(node->ch[loc],\
    \ index);\n            if (ch_loc == loc) { // zig-zig\n                if (loc\
    \ == LOC_RIGHT) index -= size(node->ch[loc]->ch[0]) + 1;\n                node->ch[loc]->push();\n\
    \                node = rotate(node, loc ^ 1);\n                if (node->ch[loc]\
    \ == nullptr) break;\n            }\n            path.push_back(node);\n     \
    \       work_leaf[loc]->ch[loc] = node;\n            work_leaf[loc] = node;\n\
    \            node = node->ch[loc];\n        }\n        work_leaf[0]->ch[0] = node->ch[1];\n\
    \        work_leaf[1]->ch[1] = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n\
    \        node->ch[1] = work_root->ch[0];\n        work_root->ch[0] = work_root->ch[1]\
    \ = nullptr;\n        delete work_root;\n        while (path.size()) path.back()->update(),\
    \ path.pop_back();\n        node->update();\n        return node;\n    }\n   \
    \ static Node* insert(Node *node, int index, const T &val) {\n        if (node\
    \ == nullptr) return new Node(val);\n        node = splay(node, index);\n    \
    \    Node *new_node = new Node(val);\n        bool loc = index <= size(node->ch[0]);\n\
    \        new_node->ch[loc] = node;\n        new_node->ch[loc ^ 1] = node->ch[loc\
    \ ^ 1];\n        node->ch[loc ^ 1] = nullptr;\n        node->update(), new_node->update();\n\
    \        return new_node;\n    }\n    static Node* erase(Node *node, int index)\
    \ {\n        if (node == nullptr) return node;\n        node = splay(node, index);\n\
    \        if (node->ch[0] != nullptr and node->ch[1] != nullptr) {\n          \
    \  Node *left_max_node = splay(node->ch[0], index);\n            left_max_node->ch[1]\
    \ = node->ch[1];\n            node->ch[0] = node->ch[1] = nullptr;\n         \
    \   delete node;\n            left_max_node->update();\n            return left_max_node;\n\
    \        } else {\n            int choose = node->ch[0] == nullptr;\n        \
    \    Node *res = node->ch[choose];\n            node->ch[choose] = nullptr;\n\
    \            delete node;\n            return res;\n        }\n    }\n    static\
    \ std::pair<Node*, Node*> split(Node *node, int k) {\n        if (node == nullptr)\
    \ return { nullptr, nullptr };\n        if (k == 0) return { nullptr, node };\n\
    \        if (k == size(node)) return { node, nullptr };\n        Node *tree_r\
    \ = splay(node, k);\n        Node *tree_l = tree_r->ch[0];\n        tree_r->ch[0]\
    \ = nullptr;\n        tree_r->update();\n        return { tree_l, tree_r };\n\
    \    }\n    static Node* merge(Node *node_l, Node *node_r) {\n        if (node_l\
    \ == nullptr) return node_r;\n        if (node_r == nullptr) return node_l;\n\
    \        node_r = splay(node_r, 0);\n        node_r->ch[0] = node_l;\n       \
    \ node_r->update();\n        return node_r;\n    }\n    static Node* apply(Node\
    \ *node, const F &f, int l, int r) {\n        auto [node_l, node_mr] = split(node,\
    \ l);\n        auto [node_m, node_r] = split(node_mr, r - l);\n        apply(node_m,\
    \ f);\n        return merge(node_l, merge(node_m, node_r));\n    }\n    static\
    \ Node* reverse(Node *node, int l, int r) {\n        auto [node_l, node_mr] =\
    \ split(node, l);\n        auto [node_m, node_r] = split(node_mr, r - l);\n  \
    \      apply_rev(node_m);\n        return merge(node_l, merge(node_m, node_r));\n\
    \    }\n    static std::pair<Node*, T> prod(Node *node, int l, int r) {\n    \
    \    auto [node_l, node_mr] = split(node, l);\n        auto [node_m, node_r] =\
    \ split(node_mr, r - l);\n        T res = prod_subtree(node_m);\n        return\
    \ { merge(node_l, merge(node_m, node_r)), res };\n    }\n};\n}\n\ntemplate <typename\
    \ T, T (*e)(), T(*op)(T, T), typename F, F (*id)(), T(*mapping)(F, T), F(*composition)(F,\
    \ F)>\nclass LazyEvalDynamicSequence {\n    using Node = internal::lazy_eval_dynamic_sequence::Node<T,\
    \ e, op, F, id, mapping, composition>;\n    public:\n        LazyEvalDynamicSequence()\
    \ : root(nullptr) {}\n        ~LazyEvalDynamicSequence() {\n            delete\
    \ root;\n        }\n        void insert(int k, const T& val) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::insert(root, k, val);\n        }\n  \
    \      void erase(int k) {\n            index_bounds_check(k, size());\n     \
    \       root = Node::erase(root, k);\n        }\n        auto operator[](int k)\
    \ {\n            index_bounds_check(k, size());\n            root = Node::splay(root,\
    \ k);\n            return UpdateProxyObject { root->val, [this]{ root->update();\
    \ } };\n        }\n        int size() {\n            return Node::size(root);\n\
    \        }\n        void apply(const F &f, int l, int r) {\n            assert(0\
    \ <= l and l <= r and r <= size());\n            root = Node::apply(root, f, l,\
    \ r);\n        }\n        T prod(int l, int r) {\n            assert(0 <= l and\
    \ l <= r and r <= size());\n            auto [new_root, res] = Node::prod(root,\
    \ l, r);\n            root = new_root;\n            return res;\n        }\n \
    \       T operator()(int l, int r) {\n            return prod(l, r);\n       \
    \ }\n        void reverse(int l, int r) {\n            assert(0 <= l and l <=\
    \ r and r <= size());\n            root = Node::reverse(root, l, r);\n       \
    \ }\n        LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right)\
    \ {\n            root = Node::merge(root, right.root);\n            return *this;\n\
    \        }\n        void concat(LazyEvalDynamicSequence &&right) {\n         \
    \   *this += std::move(right);\n        }\n        void concat_left(LazyEvalDynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \   }\n        // [0, k), [k, size())\n        std::pair<LazyEvalDynamicSequence,\
    \ LazyEvalDynamicSequence> split(int k) {\n            auto [l, r] = Node::split(root,\
    \ k);\n            return { LazyEvalDynamicSequence(l), LazyEvalDynamicSequence(r)\
    \ };\n        }\n    private:\n        Node *root;\n        LazyEvalDynamicSequence(Node\
    \ *root) : root(root) {}\n        bool index_bounds_check(unsigned int k, unsigned\
    \ int n) {\n            return k < n;\n        }\n};\n}\n\n\n"
  code: "#ifndef SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n#define SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n\
    \n#include <cassert>\n#include <cstddef>\n#include <vector>\n#include <utility>\n\
    \n#include \"library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\nnamespace\
    \ internal::lazy_eval_dynamic_sequence {\n\nstatic constexpr int LOC_LEFT = 0;\n\
    static constexpr int LOC_RIGHT = 1;\nstatic constexpr int LOC_ROOT = 2;\n\ntemplate\
    \ <typename T, T (*e)(), T(*op)(T, T), typename F, F (*id)(), T(*mapping)(F, T),\
    \ F(*composition)(F, F)>\nstruct Node {\n    T val;\n    T dat;\n    F laz;\n\
    \    bool rev;\n    int siz;\n    Node *ch[2] {nullptr, nullptr};\n    Node()\
    \ : val(e()), dat(e()), laz(id()), rev(false), siz(1) {}\n    Node(const T &val)\
    \ : val(val), dat(val), laz(id()), rev(false), siz(1) {}\n    ~Node() {\n    \
    \    delete ch[0];\n        delete ch[1];\n    }\n    void update() {\n      \
    \  siz = 1 + size(ch[0]) + size(ch[1]);\n        dat = op(op(prod_subtree(ch[0]),\
    \ val), prod_subtree(ch[1]));\n    }\n    void push() {\n        apply(ch[0],\
    \ laz), apply_rev(ch[0], rev);\n        apply(ch[1], laz), apply_rev(ch[1], rev);\n\
    \        laz = id(), rev = false;\n    }\n    static T prod_subtree(Node *node)\
    \ {\n        return node == nullptr ? e() : node->dat;\n    }\n    static void\
    \ apply(Node *node, const F &f) {\n        if (node == nullptr) return;\n    \
    \    node->val = mapping(f, node->val);\n        node->dat = mapping(f, node->dat);\n\
    \        node->laz = composition(f, node->laz);\n    }\n    static void apply_rev(Node\
    \ *node, bool rev = true) {\n        if (node == nullptr) return;\n        if\
    \ (rev) std::swap(node->ch[0], node->ch[1]);\n        node->rev ^= rev;\n    }\n\
    \    static int size(Node *node) {\n        return node == nullptr ? 0 : node->siz;\n\
    \    }\n    static Node* rotate(Node *node, int dir) { // dir: LEFT = 0, RIGHT\
    \ = 1\n        assert(node->ch[dir ^ 1] != nullptr);\n        Node *par = node->ch[dir\
    \ ^ 1];\n        node->ch[dir ^ 1] = par->ch[dir];\n        par->ch[dir] = node;\n\
    \        node->update(), par->update();\n        return par;\n    }\n    static\
    \ int locate(Node *node, int index) {\n        int siz_l = size(node->ch[0]);\n\
    \        return index == siz_l ? LOC_ROOT : index > siz_l;\n    }\n    static\
    \ Node* splay(Node *node, int index) {\n        std::vector<Node*> path;\n   \
    \     Node *work_root = new Node();\n        Node *work_leaf[2] {work_root, work_root};\n\
    \        while (true) {\n            node->push();\n            int loc = locate(node,\
    \ index);\n            if (loc == LOC_ROOT or node->ch[loc] == nullptr) break;\n\
    \            if (loc == LOC_RIGHT) index -= size(node->ch[0]) + 1;\n         \
    \   int ch_loc = locate(node->ch[loc], index);\n            if (ch_loc == loc)\
    \ { // zig-zig\n                if (loc == LOC_RIGHT) index -= size(node->ch[loc]->ch[0])\
    \ + 1;\n                node->ch[loc]->push();\n                node = rotate(node,\
    \ loc ^ 1);\n                if (node->ch[loc] == nullptr) break;\n          \
    \  }\n            path.push_back(node);\n            work_leaf[loc]->ch[loc] =\
    \ node;\n            work_leaf[loc] = node;\n            node = node->ch[loc];\n\
    \        }\n        work_leaf[0]->ch[0] = node->ch[1];\n        work_leaf[1]->ch[1]\
    \ = node->ch[0];\n        node->ch[0] = work_root->ch[1];\n        node->ch[1]\
    \ = work_root->ch[0];\n        work_root->ch[0] = work_root->ch[1] = nullptr;\n\
    \        delete work_root;\n        while (path.size()) path.back()->update(),\
    \ path.pop_back();\n        node->update();\n        return node;\n    }\n   \
    \ static Node* insert(Node *node, int index, const T &val) {\n        if (node\
    \ == nullptr) return new Node(val);\n        node = splay(node, index);\n    \
    \    Node *new_node = new Node(val);\n        bool loc = index <= size(node->ch[0]);\n\
    \        new_node->ch[loc] = node;\n        new_node->ch[loc ^ 1] = node->ch[loc\
    \ ^ 1];\n        node->ch[loc ^ 1] = nullptr;\n        node->update(), new_node->update();\n\
    \        return new_node;\n    }\n    static Node* erase(Node *node, int index)\
    \ {\n        if (node == nullptr) return node;\n        node = splay(node, index);\n\
    \        if (node->ch[0] != nullptr and node->ch[1] != nullptr) {\n          \
    \  Node *left_max_node = splay(node->ch[0], index);\n            left_max_node->ch[1]\
    \ = node->ch[1];\n            node->ch[0] = node->ch[1] = nullptr;\n         \
    \   delete node;\n            left_max_node->update();\n            return left_max_node;\n\
    \        } else {\n            int choose = node->ch[0] == nullptr;\n        \
    \    Node *res = node->ch[choose];\n            node->ch[choose] = nullptr;\n\
    \            delete node;\n            return res;\n        }\n    }\n    static\
    \ std::pair<Node*, Node*> split(Node *node, int k) {\n        if (node == nullptr)\
    \ return { nullptr, nullptr };\n        if (k == 0) return { nullptr, node };\n\
    \        if (k == size(node)) return { node, nullptr };\n        Node *tree_r\
    \ = splay(node, k);\n        Node *tree_l = tree_r->ch[0];\n        tree_r->ch[0]\
    \ = nullptr;\n        tree_r->update();\n        return { tree_l, tree_r };\n\
    \    }\n    static Node* merge(Node *node_l, Node *node_r) {\n        if (node_l\
    \ == nullptr) return node_r;\n        if (node_r == nullptr) return node_l;\n\
    \        node_r = splay(node_r, 0);\n        node_r->ch[0] = node_l;\n       \
    \ node_r->update();\n        return node_r;\n    }\n    static Node* apply(Node\
    \ *node, const F &f, int l, int r) {\n        auto [node_l, node_mr] = split(node,\
    \ l);\n        auto [node_m, node_r] = split(node_mr, r - l);\n        apply(node_m,\
    \ f);\n        return merge(node_l, merge(node_m, node_r));\n    }\n    static\
    \ Node* reverse(Node *node, int l, int r) {\n        auto [node_l, node_mr] =\
    \ split(node, l);\n        auto [node_m, node_r] = split(node_mr, r - l);\n  \
    \      apply_rev(node_m);\n        return merge(node_l, merge(node_m, node_r));\n\
    \    }\n    static std::pair<Node*, T> prod(Node *node, int l, int r) {\n    \
    \    auto [node_l, node_mr] = split(node, l);\n        auto [node_m, node_r] =\
    \ split(node_mr, r - l);\n        T res = prod_subtree(node_m);\n        return\
    \ { merge(node_l, merge(node_m, node_r)), res };\n    }\n};\n}\n\ntemplate <typename\
    \ T, T (*e)(), T(*op)(T, T), typename F, F (*id)(), T(*mapping)(F, T), F(*composition)(F,\
    \ F)>\nclass LazyEvalDynamicSequence {\n    using Node = internal::lazy_eval_dynamic_sequence::Node<T,\
    \ e, op, F, id, mapping, composition>;\n    public:\n        LazyEvalDynamicSequence()\
    \ : root(nullptr) {}\n        ~LazyEvalDynamicSequence() {\n            delete\
    \ root;\n        }\n        void insert(int k, const T& val) {\n            index_bounds_check(k,\
    \ size() + 1);\n            root = Node::insert(root, k, val);\n        }\n  \
    \      void erase(int k) {\n            index_bounds_check(k, size());\n     \
    \       root = Node::erase(root, k);\n        }\n        auto operator[](int k)\
    \ {\n            index_bounds_check(k, size());\n            root = Node::splay(root,\
    \ k);\n            return UpdateProxyObject { root->val, [this]{ root->update();\
    \ } };\n        }\n        int size() {\n            return Node::size(root);\n\
    \        }\n        void apply(const F &f, int l, int r) {\n            assert(0\
    \ <= l and l <= r and r <= size());\n            root = Node::apply(root, f, l,\
    \ r);\n        }\n        T prod(int l, int r) {\n            assert(0 <= l and\
    \ l <= r and r <= size());\n            auto [new_root, res] = Node::prod(root,\
    \ l, r);\n            root = new_root;\n            return res;\n        }\n \
    \       T operator()(int l, int r) {\n            return prod(l, r);\n       \
    \ }\n        void reverse(int l, int r) {\n            assert(0 <= l and l <=\
    \ r and r <= size());\n            root = Node::reverse(root, l, r);\n       \
    \ }\n        LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right)\
    \ {\n            root = Node::merge(root, right.root);\n            return *this;\n\
    \        }\n        void concat(LazyEvalDynamicSequence &&right) {\n         \
    \   *this += std::move(right);\n        }\n        void concat_left(LazyEvalDynamicSequence\
    \ &&left) {\n            this->root = (left += std::move(*this)).root;\n     \
    \   }\n        // [0, k), [k, size())\n        std::pair<LazyEvalDynamicSequence,\
    \ LazyEvalDynamicSequence> split(int k) {\n            auto [l, r] = Node::split(root,\
    \ k);\n            return { LazyEvalDynamicSequence(l), LazyEvalDynamicSequence(r)\
    \ };\n        }\n    private:\n        Node *root;\n        LazyEvalDynamicSequence(Node\
    \ *root) : root(root) {}\n        bool index_bounds_check(unsigned int k, unsigned\
    \ int n) {\n            return k < n;\n        }\n};\n}\n\n#endif // SUISEN_LAZY_EVAL_DYNAMIC_SEQUENCE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/lazy_eval_dynamic_sequence.hpp
  requiredBy: []
  timestamp: '2021-08-11 03:03:21+09:00'
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
  template <typename T, T (*e)(), T(*op)(T, T), typename F, F(*id)(), T(*mapping)(F, T), F(*composition)(F, F)>
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
  - `T (*e)()`: モノイド $(T,\cdot)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)
  - `T(*op)(T, T)`: 二項演算 $\cdot$
  - `F`: 区間作用の作用素型
  - `F (*id)()`: モノイド $(F,\circ)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)
  - `T(*mapping)(F, T)`: 一点作用の関数
  - `F(*composition)(F, F)`: 二項演算 $\circ$

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
  T apply(const F &f, int l, int r)
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
  std::pair<LazyEvalDynamicSequence, LazyEvalDynamicSequence> split(int k)
  ```

- 概要

  列を分割します．`split` により分割した後は，分割してできた 2 つの列に対する操作のみが有効です．分割する前の列を保持していたインスタンスに対する操作は全て未定義となります．

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$