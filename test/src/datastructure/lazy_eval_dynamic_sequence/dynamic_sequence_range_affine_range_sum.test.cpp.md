---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/lazy_eval_dynamic_sequence.hpp
    title: library/datastructure/lazy_eval_dynamic_sequence.hpp
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: library/util/update_proxy_object.hpp
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
  bundledCode: "#line 1 \"test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include <iostream>\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/datastructure/lazy_eval_dynamic_sequence.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n#include <utility>\n\n#line\
    \ 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 1 \"library/type_traits/type_traits.hpp\"\
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
    \ LazyEvalDynamicSequence> split(int k) {\n            auto [l, r] = Node::split(k);\n\
    \            return { LazyEvalDynamicSequence(l), LazyEvalDynamicSequence(r) };\n\
    \        }\n    private:\n        Node *root;\n        LazyEvalDynamicSequence(Node\
    \ *root) : root(root) {}\n        bool index_bounds_check(unsigned int k, unsigned\
    \ int n) {\n            return k < n;\n        }\n};\n}\n\n\n#line 9 \"test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp\"\
    \nusing suisen::LazyEvalDynamicSequence;\n\nstruct F {\n    mint a, b;\n    F\
    \ compose(F g) {\n        return F { a * g.a, a * g.b + b };\n    }\n};\n\nstd::pair<mint,\
    \ int> op(std::pair<mint, int> x, std::pair<mint, int> y) {\n    auto [xs, xl]\
    \ = x;\n    auto [ys, yl] = y;\n    return { xs + ys, xl + yl };\n}\nstd::pair<mint,\
    \ int> e() {\n    return { 0, 0 };\n}\n\nstd::pair<mint, int> mapping(F f, std::pair<mint,\
    \ int> x) {\n    return { f.a * x.first + f.b * x.second, x.second };\n}\nF composition(F\
    \ f, F g) {\n    return f.compose(g);\n}\nF id() {\n    return { 1, 0 };\n}\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    LazyEvalDynamicSequence<std::pair<mint, int>, e, op, F, id, mapping, composition>\
    \ seq;\n\n    int n, q;\n    std::cin >> n >> q;\n    for (int i = 0; i < n; ++i)\
    \ {\n        int a;\n        std::cin >> a;\n        seq.insert(i, { a, 1 });\n\
    \    }\n    while (q --> 0) {\n        int t;\n        std::cin >> t;\n      \
    \  if (t == 0) {\n            int i, x;\n            std::cin >> i >> x;\n   \
    \         seq.insert(i, { x, 1 });\n        } else if (t == 1) {\n           \
    \ int i;\n            std::cin >> i;\n            seq.erase(i);\n        } else\
    \ if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n    \
    \        seq.reverse(l, r);\n        } else if (t == 3) {\n            int l,\
    \ r, a, b;\n            std::cin >> l >> r >> a >> b;\n            seq.apply({\
    \ a, b }, l, r);\n        } else {\n            int l, r;\n            std::cin\
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
    \n    LazyEvalDynamicSequence<std::pair<mint, int>, e, op, F, id, mapping, composition>\
    \ seq;\n\n    int n, q;\n    std::cin >> n >> q;\n    for (int i = 0; i < n; ++i)\
    \ {\n        int a;\n        std::cin >> a;\n        seq.insert(i, { a, 1 });\n\
    \    }\n    while (q --> 0) {\n        int t;\n        std::cin >> t;\n      \
    \  if (t == 0) {\n            int i, x;\n            std::cin >> i >> x;\n   \
    \         seq.insert(i, { x, 1 });\n        } else if (t == 1) {\n           \
    \ int i;\n            std::cin >> i;\n            seq.erase(i);\n        } else\
    \ if (t == 2) {\n            int l, r;\n            std::cin >> l >> r;\n    \
    \        seq.reverse(l, r);\n        } else if (t == 3) {\n            int l,\
    \ r, a, b;\n            std::cin >> l >> r >> a >> b;\n            seq.apply({\
    \ a, b }, l, r);\n        } else {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            std::cout << seq(l, r).first.val() << '\\n';\n     \
    \   }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/lazy_eval_dynamic_sequence.hpp
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: true
  path: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2021-08-11 01:57:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
- /verify/test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp.html
title: test/src/datastructure/lazy_eval_dynamic_sequence/dynamic_sequence_range_affine_range_sum.test.cpp
---
