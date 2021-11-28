---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/type_traits/type_traits.hpp
    title: library/type_traits/type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: library/util/update_proxy_object.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
    title: test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/sparse_lazy_segment_tree.hpp\"\n\n\
    \n\n#include <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
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
    \ bool is_nbit_v = is_nbit<T, n>::value;\n\n// ?\ntemplate <typename T>\nstruct\
    \ safely_multipliable {};\ntemplate <>\nstruct safely_multipliable<int> { using\
    \ type = long long; };\ntemplate <>\nstruct safely_multipliable<long long> { using\
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<float> { using\
    \ type = float; };\ntemplate <>\nstruct safely_multipliable<double> { using type\
    \ = double; };\ntemplate <>\nstruct safely_multipliable<long double> { using type\
    \ = long double; };\ntemplate <typename T>\nusing safely_multipliable_t = typename\
    \ safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\
    \n\nnamespace suisen {\n\ntemplate <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>>\
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
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 7 \"library/datastructure/sparse_lazy_segment_tree.hpp\"\n\nnamespace suisen\
    \ {\ntemplate <\n    typename index_t,               // type of index (integral:\
    \ int, long long, etc.)\n    typename T,                     // type of element\n\
    \    typename OpTT,                  // type of binary operator on T\n    typename\
    \ F,                     // type of operator which acts on T\n    typename OpFT,\
    \                  // type of action F on T\n    typename OpFF,              \
    \    // type of binary operator on F\n    typename ProductInitializer,    // type\
    \ of function which initializes product of segment [l, r)\n    constraints_t<\n\
    \        std::is_integral<index_t>,                                          //\
    \ index_t is integral\n        is_bin_op<OpTT, T>,                           \
    \                      // OpTT is (T, T) -> T\n        is_same_as_invoke_result<T,\
    \ OpFT, F, T>,                            // OpFT is (F, T) -> T\n        is_bin_op<OpFF,\
    \ F>,                                                 // OpFF is (F, F) -> F\n\
    \        is_same_as_invoke_result<T, ProductInitializer, index_t, index_t>   //\
    \ ProductInitializer is (index_t, index_t) -> T\n    > = nullptr\n>\nclass SparseLazySegmentTree\
    \ {\n    using unsigned_index_t = typename std::make_unsigned_t<index_t>;\n\n\
    \    struct Node {\n        Node *par;\n        Node *ch[2] { nullptr, nullptr\
    \ };\n        unsigned_index_t l, r;\n        T dat;\n        F laz;\n       \
    \ Node(Node *par, unsigned_index_t l, unsigned_index_t r, const T &dat, const\
    \ F &laz) : par(par), l(l), r(r), dat(dat), laz(laz) {}\n        ~Node() {\n \
    \           delete ch[0];\n            delete ch[1];\n        }\n    };\n\n  \
    \  public:\n        SparseLazySegmentTree() : SparseLazySegmentTree(0, T{}, OpTT{},\
    \ F{}, OpFT{}, OpFF{}, ProductInitializer{}) {}\n        /**\n         * 1. number\
    \ of element\n         * 2. id of \uFF65. \u2200x:T, x\uFF65e=e\uFF65x=x .\n \
    \        * 3. (x,y) -> x\uFF65y\n         * 4. id of \u25E6. \u2200f:F, f\u25E6\
    id=id\u25E6f=f, \u2200x:T, id(x)=x.\n         * 5. (f,x) -> f(x). \u2200x,y:T,\
    \ \u2200f,g:F, f(x)\uFF65g(y)=(f\u25E6g)(x\uFF65y).\n         * 6. (f,g) -> f\u25E6\
    g\n         * 7. (l,r) -> initial product of segment [l,r).\n         */\n   \
    \     SparseLazySegmentTree(index_t n, T e, OpTT op, F id, OpFT mapping, OpFF\
    \ composition, ProductInitializer init) : n(n), e(e), op(op), id(id), mapping(mapping),\
    \ composition(composition), init(init), root(new Node(nullptr, 0, n, init(0, n),\
    \ id)) {}\n\n        ~SparseLazySegmentTree() {\n            delete root;\n  \
    \      }\n\n        auto operator[](unsigned_index_t i) {\n            assert(i\
    \ < n);\n            Node* leaf = get_or_create_leaf(i);\n            return UpdateProxyObject\
    \ { leaf->dat, [this, leaf]{ update_from(leaf); } };\n        }\n\n        T get(unsigned_index_t\
    \ i) {\n            return (*this)[i];\n        }\n        void set(unsigned_index_t\
    \ i, const T& val) {\n            (*this)[i] = val;\n        }\n        void apply(unsigned_index_t\
    \ i, const F &f) {\n            (*this)[i].apply([this, f](const T &dat) { return\
    \ mapping(f, dat); });\n        }\n\n        T operator()(unsigned_index_t l,\
    \ unsigned_index_t r) {\n            assert(l <= r and r <= n);\n            return\
    \ query(root, l, r);\n        }\n        T prod(unsigned_index_t l, unsigned_index_t\
    \ r) {\n            return (*this)(l, r);\n        }\n        T prod_all() {\n\
    \            return root->dat;\n        }\n\n        void apply(unsigned_index_t\
    \ l, unsigned_index_t r, const F &f) {\n            assert(l <= r and r <= n);\n\
    \            apply(root, l, r, f);\n        }\n        void apply_all(const F\
    \ &f) {\n            apply_all(root, f);\n        }\n\n    private:\n        unsigned_index_t\
    \ n;\n        T e;\n        OpTT op;\n        F id;\n        OpFT mapping;\n \
    \       OpFF composition;\n        ProductInitializer init;\n        Node* root;\n\
    \n        Node* get_or_create_leaf(unsigned_index_t i) {\n            Node *cur\
    \ = root;\n            while (cur->r - cur->l > 1) {\n                push(cur);\n\
    \                cur = cur->ch[i >= (cur->l + cur->r) >> 1];\n            }\n\
    \            return cur;\n        }\n        Node* get_or_create_child(Node* node,\
    \ int index) {\n            if (not node->ch[index]) {\n                unsigned_index_t\
    \ l = node->l, r = node->r, m = (l + r) >> 1;\n                unsigned_index_t\
    \ cl = index ? m : l;\n                unsigned_index_t cr = index ? r : m;\n\
    \                node->ch[index] = new Node(node, cl, cr, init(cl, cr), id);\n\
    \            }\n            return node->ch[index];\n        }\n    \n       \
    \ void apply_all(Node* node, const F &f) {\n            node->dat = mapping(f,\
    \ node->dat);\n            node->laz = composition(f, node->laz);\n        }\n\
    \        void push(Node* node) {\n            apply_all(get_or_create_child(node,\
    \ 0), node->laz);\n            apply_all(get_or_create_child(node, 1), node->laz);\n\
    \            node->laz = id;\n        }\n\n        void update(Node* node) {\n\
    \            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);\n        }\n\
    \        void update_from(Node* leaf) {\n            while (leaf->par) update(leaf\
    \ = leaf->par);\n        }\n\n        T query(Node *node, unsigned_index_t ql,\
    \ unsigned_index_t qr) {\n            unsigned_index_t tl = node->l, tr = node->r;\n\
    \            if (tr <= ql or qr <= tl) return e;\n            if (ql <= tl and\
    \ tr <= qr) return node->dat;\n            push(node);\n            return op(query(node->ch[0],\
    \ ql, qr), query(node->ch[1], ql, qr));\n        }\n\n        void apply(Node\
    \ *node, unsigned_index_t ql, unsigned_index_t qr, const F &f) {\n           \
    \ unsigned_index_t tl = node->l, tr = node->r;\n            if (tr <= ql or qr\
    \ <= tl) return;\n            if (ql <= tl and tr <= qr) return apply_all(node,\
    \ f);\n            push(node);\n            apply(node->ch[0], ql, qr, f);\n \
    \           apply(node->ch[1], ql, qr, f);\n            update(node);\n      \
    \  }\n};\n\n}\n\n\n"
  code: "#ifndef SUISEN_SPARSE_LAZY_SEGTREE\n#define SUISEN_SPARSE_LAZY_SEGTREE\n\n\
    #include <cassert>\n#include <vector>\n#include \"library/util/update_proxy_object.hpp\"\
    \n\nnamespace suisen {\ntemplate <\n    typename index_t,               // type\
    \ of index (integral: int, long long, etc.)\n    typename T,                 \
    \    // type of element\n    typename OpTT,                  // type of binary\
    \ operator on T\n    typename F,                     // type of operator which\
    \ acts on T\n    typename OpFT,                  // type of action F on T\n  \
    \  typename OpFF,                  // type of binary operator on F\n    typename\
    \ ProductInitializer,    // type of function which initializes product of segment\
    \ [l, r)\n    constraints_t<\n        std::is_integral<index_t>,             \
    \                             // index_t is integral\n        is_bin_op<OpTT,\
    \ T>,                                                 // OpTT is (T, T) -> T\n\
    \        is_same_as_invoke_result<T, OpFT, F, T>,                            //\
    \ OpFT is (F, T) -> T\n        is_bin_op<OpFF, F>,                           \
    \                      // OpFF is (F, F) -> F\n        is_same_as_invoke_result<T,\
    \ ProductInitializer, index_t, index_t>   // ProductInitializer is (index_t, index_t)\
    \ -> T\n    > = nullptr\n>\nclass SparseLazySegmentTree {\n    using unsigned_index_t\
    \ = typename std::make_unsigned_t<index_t>;\n\n    struct Node {\n        Node\
    \ *par;\n        Node *ch[2] { nullptr, nullptr };\n        unsigned_index_t l,\
    \ r;\n        T dat;\n        F laz;\n        Node(Node *par, unsigned_index_t\
    \ l, unsigned_index_t r, const T &dat, const F &laz) : par(par), l(l), r(r), dat(dat),\
    \ laz(laz) {}\n        ~Node() {\n            delete ch[0];\n            delete\
    \ ch[1];\n        }\n    };\n\n    public:\n        SparseLazySegmentTree() :\
    \ SparseLazySegmentTree(0, T{}, OpTT{}, F{}, OpFT{}, OpFF{}, ProductInitializer{})\
    \ {}\n        /**\n         * 1. number of element\n         * 2. id of \uFF65\
    . \u2200x:T, x\uFF65e=e\uFF65x=x .\n         * 3. (x,y) -> x\uFF65y\n        \
    \ * 4. id of \u25E6. \u2200f:F, f\u25E6id=id\u25E6f=f, \u2200x:T, id(x)=x.\n \
    \        * 5. (f,x) -> f(x). \u2200x,y:T, \u2200f,g:F, f(x)\uFF65g(y)=(f\u25E6\
    g)(x\uFF65y).\n         * 6. (f,g) -> f\u25E6g\n         * 7. (l,r) -> initial\
    \ product of segment [l,r).\n         */\n        SparseLazySegmentTree(index_t\
    \ n, T e, OpTT op, F id, OpFT mapping, OpFF composition, ProductInitializer init)\
    \ : n(n), e(e), op(op), id(id), mapping(mapping), composition(composition), init(init),\
    \ root(new Node(nullptr, 0, n, init(0, n), id)) {}\n\n        ~SparseLazySegmentTree()\
    \ {\n            delete root;\n        }\n\n        auto operator[](unsigned_index_t\
    \ i) {\n            assert(i < n);\n            Node* leaf = get_or_create_leaf(i);\n\
    \            return UpdateProxyObject { leaf->dat, [this, leaf]{ update_from(leaf);\
    \ } };\n        }\n\n        T get(unsigned_index_t i) {\n            return (*this)[i];\n\
    \        }\n        void set(unsigned_index_t i, const T& val) {\n           \
    \ (*this)[i] = val;\n        }\n        void apply(unsigned_index_t i, const F\
    \ &f) {\n            (*this)[i].apply([this, f](const T &dat) { return mapping(f,\
    \ dat); });\n        }\n\n        T operator()(unsigned_index_t l, unsigned_index_t\
    \ r) {\n            assert(l <= r and r <= n);\n            return query(root,\
    \ l, r);\n        }\n        T prod(unsigned_index_t l, unsigned_index_t r) {\n\
    \            return (*this)(l, r);\n        }\n        T prod_all() {\n      \
    \      return root->dat;\n        }\n\n        void apply(unsigned_index_t l,\
    \ unsigned_index_t r, const F &f) {\n            assert(l <= r and r <= n);\n\
    \            apply(root, l, r, f);\n        }\n        void apply_all(const F\
    \ &f) {\n            apply_all(root, f);\n        }\n\n    private:\n        unsigned_index_t\
    \ n;\n        T e;\n        OpTT op;\n        F id;\n        OpFT mapping;\n \
    \       OpFF composition;\n        ProductInitializer init;\n        Node* root;\n\
    \n        Node* get_or_create_leaf(unsigned_index_t i) {\n            Node *cur\
    \ = root;\n            while (cur->r - cur->l > 1) {\n                push(cur);\n\
    \                cur = cur->ch[i >= (cur->l + cur->r) >> 1];\n            }\n\
    \            return cur;\n        }\n        Node* get_or_create_child(Node* node,\
    \ int index) {\n            if (not node->ch[index]) {\n                unsigned_index_t\
    \ l = node->l, r = node->r, m = (l + r) >> 1;\n                unsigned_index_t\
    \ cl = index ? m : l;\n                unsigned_index_t cr = index ? r : m;\n\
    \                node->ch[index] = new Node(node, cl, cr, init(cl, cr), id);\n\
    \            }\n            return node->ch[index];\n        }\n    \n       \
    \ void apply_all(Node* node, const F &f) {\n            node->dat = mapping(f,\
    \ node->dat);\n            node->laz = composition(f, node->laz);\n        }\n\
    \        void push(Node* node) {\n            apply_all(get_or_create_child(node,\
    \ 0), node->laz);\n            apply_all(get_or_create_child(node, 1), node->laz);\n\
    \            node->laz = id;\n        }\n\n        void update(Node* node) {\n\
    \            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);\n        }\n\
    \        void update_from(Node* leaf) {\n            while (leaf->par) update(leaf\
    \ = leaf->par);\n        }\n\n        T query(Node *node, unsigned_index_t ql,\
    \ unsigned_index_t qr) {\n            unsigned_index_t tl = node->l, tr = node->r;\n\
    \            if (tr <= ql or qr <= tl) return e;\n            if (ql <= tl and\
    \ tr <= qr) return node->dat;\n            push(node);\n            return op(query(node->ch[0],\
    \ ql, qr), query(node->ch[1], ql, qr));\n        }\n\n        void apply(Node\
    \ *node, unsigned_index_t ql, unsigned_index_t qr, const F &f) {\n           \
    \ unsigned_index_t tl = node->l, tr = node->r;\n            if (tr <= ql or qr\
    \ <= tl) return;\n            if (ql <= tl and tr <= qr) return apply_all(node,\
    \ f);\n            push(node);\n            apply(node->ch[0], ql, qr, f);\n \
    \           apply(node->ch[1], ql, qr, f);\n            update(node);\n      \
    \  }\n};\n\n}\n\n#endif // SUISEN_SPARSE_LAZY_SEGTREE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/sparse_lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-09-03 01:54:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/sparse_lazy_segment_tree/arc115_e.test.cpp
documentation_of: library/datastructure/sparse_lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/library/datastructure/sparse_lazy_segment_tree.hpp
- /library/library/datastructure/sparse_lazy_segment_tree.hpp.html
title: library/datastructure/sparse_lazy_segment_tree.hpp
---
