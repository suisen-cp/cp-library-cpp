---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':heavy_check_mark:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
    title: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n#line 1 \"library/util/update_proxy_object.hpp\"\
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
    \ type = __int128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned int>\
    \ { using type = unsigned long long; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long int> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<unsigned\
    \ long long> { using type = __uint128_t; };\ntemplate <>\nstruct safely_multipliable<float>\
    \ { using type = float; };\ntemplate <>\nstruct safely_multipliable<double> {\
    \ using type = double; };\ntemplate <>\nstruct safely_multipliable<long double>\
    \ { using type = long double; };\ntemplate <typename T>\nusing safely_multipliable_t\
    \ = typename safely_multipliable<T>::type;\n\ntemplate <typename T, typename =\
    \ void>\nstruct rec_value_type {\n    using type = T;\n};\ntemplate <typename\
    \ T>\nstruct rec_value_type<T, std::void_t<typename T::value_type>> {\n    using\
    \ type = typename rec_value_type<typename T::value_type>::type;\n};\ntemplate\
    \ <typename T>\nusing rec_value_type_t = typename rec_value_type<T>::type;\n\n\
    } // namespace suisen\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\n\n\
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
    \        template <typename F, constraints_t<is_uni_op<F, T>> = nullptr>\n   \
    \     auto& apply(F f) && { v = f(v), update(); return *this; }\n    private:\n\
    \        T &v;\n        UpdateFunc update;\n};\n\n} // namespace suisen\n\n\n\
    #line 7 \"library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\"\n\n\
    namespace suisen {\n    template <\n        typename index_t,      // type of\
    \ index (integral: int, long long, etc.)\n        typename T,            // type\
    \ of element\n        T(*op)(T, T),          // type of binary operator on T\n\
    \        T(*e)(),               //\n        typename F,            // type of\
    \ operator which acts on T\n        T(*mapping)(F, T),     // type of action F\
    \ on T\n        F(*composition)(F, F), // type of binary operator on F\n     \
    \   F(*id)(),              //\n        T(*init)(int, int)     // type of function\
    \ which initializes product of segment [l, r)\n    >\n    class SparseLazySegmentTree\
    \ {\n        using unsigned_index_t = typename std::make_unsigned_t<index_t>;\n\
    \n        struct Node {\n            Node* par;\n            Node* ch[2]{ nullptr,\
    \ nullptr };\n            T dat;\n            F laz;\n            Node(Node* par,\
    \ const T& dat) : par(par), dat(dat), laz(id()) {}\n            ~Node() {\n  \
    \              delete ch[0];\n                delete ch[1];\n            }\n \
    \       };\n\n    public:\n        SparseLazySegmentTree() : SparseLazySegmentTree(0)\
    \ {}\n        SparseLazySegmentTree(index_t n) : n(n), root(new Node(nullptr,\
    \ init(0, n))) {}\n\n        ~SparseLazySegmentTree() {\n            delete root;\n\
    \        }\n\n        auto operator[](unsigned_index_t i) {\n            assert(i\
    \ < n);\n            Node* leaf = get_or_create_leaf(i);\n            return UpdateProxyObject{\
    \ leaf->dat, [this, leaf] { update_from(leaf); } };\n        }\n\n        T get(unsigned_index_t\
    \ i) {\n            return (*this)[i];\n        }\n        void set(unsigned_index_t\
    \ i, const T& val) {\n            (*this)[i] = val;\n        }\n        void apply(unsigned_index_t\
    \ i, const F& f) {\n            (*this)[i].apply([this, f](const T& dat) { return\
    \ mapping(f, dat); });\n        }\n\n        T operator()(unsigned_index_t l,\
    \ unsigned_index_t r) {\n            assert(l <= r and r <= n);\n            return\
    \ query(root, l, r);\n        }\n        T prod(unsigned_index_t l, unsigned_index_t\
    \ r) {\n            return (*this)(l, r);\n        }\n        T prod_all() {\n\
    \            return root->dat;\n        }\n\n        void apply(unsigned_index_t\
    \ l, unsigned_index_t r, const F& f) {\n            assert(l <= r and r <= n);\n\
    \            apply(root, f, l, r, 0, n);\n        }\n        void apply_all(const\
    \ F& f) {\n            apply_all(root, f);\n        }\n\n    private:\n      \
    \  unsigned_index_t n;\n        Node* root;\n\n        Node* get_or_create_leaf(unsigned_index_t\
    \ i) {\n            Node* cur = root;\n            while (cur->r - cur->l > 1)\
    \ {\n                push(cur);\n                cur = cur->ch[i >= (cur->l +\
    \ cur->r) >> 1];\n            }\n            return cur;\n        }\n        Node*\
    \ get_or_create_child(Node* node, int index, unsigned_index_t tl, unsigned_index_t\
    \ tr) {\n            if (node->ch[index]) return node->ch[index];\n          \
    \  return node->ch[index] = new Node(node, init(tl, tr));\n        }\n\n     \
    \   void apply_all(Node* node, const F& f) {\n            node->dat = mapping(f,\
    \ node->dat);\n            node->laz = composition(f, node->laz);\n        }\n\
    \        void push(Node* node, unsigned_index_t tl, unsigned_index_t tr) {\n \
    \           unsigned_index_t tm = (tl + tr) >> 1;\n            apply_all(get_or_create_child(node,\
    \ 0, tl, tm), node->laz);\n            apply_all(get_or_create_child(node, 1,\
    \ tm, tr), node->laz);\n            node->laz = id();\n        }\n\n        void\
    \ update(Node* node) {\n            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);\n\
    \        }\n        void update_from(Node* leaf) {\n            while (leaf->par)\
    \ update(leaf = leaf->par);\n        }\n\n        T query(Node* node, unsigned_index_t\
    \ ql, unsigned_index_t qr, unsigned_index_t tl, unsigned_index_t tr) {\n     \
    \       if (tr <= ql or qr <= tl) return e();\n            if (ql <= tl and tr\
    \ <= qr) return node->dat;\n            push(node, tl, tr);\n            unsigned_index_t\
    \ tm = (tl + tr) >> 1;\n            return op(query(node->ch[0], ql, qr, tl, tm),\
    \ query(node->ch[1], ql, qr, tm, tr));\n        }\n\n        void apply(Node*\
    \ node, const F& f, unsigned_index_t ql, unsigned_index_t qr, unsigned_index_t\
    \ tl, unsigned_index_t tr) {\n            if (tr <= ql or qr <= tl) return;\n\
    \            if (ql <= tl and tr <= qr) return apply_all(node, f);\n         \
    \   unsigned_index_t tm = (tl + tr) >> 1;\n            push(node, tl, tr);\n \
    \           apply(node->ch[0], f, ql, qr, tl, tm);\n            apply(node->ch[1],\
    \ f, ql, qr, tm, tr);\n            update(node);\n        }\n    };\n}\n\n\n"
  code: "#ifndef SUISEN_SPARSE_LAZY_SEGTREE\n#define SUISEN_SPARSE_LAZY_SEGTREE\n\n\
    #include <cassert>\n#include <vector>\n#include \"library/util/update_proxy_object.hpp\"\
    \n\nnamespace suisen {\n    template <\n        typename index_t,      // type\
    \ of index (integral: int, long long, etc.)\n        typename T,            //\
    \ type of element\n        T(*op)(T, T),          // type of binary operator on\
    \ T\n        T(*e)(),               //\n        typename F,            // type\
    \ of operator which acts on T\n        T(*mapping)(F, T),     // type of action\
    \ F on T\n        F(*composition)(F, F), // type of binary operator on F\n   \
    \     F(*id)(),              //\n        T(*init)(int, int)     // type of function\
    \ which initializes product of segment [l, r)\n    >\n    class SparseLazySegmentTree\
    \ {\n        using unsigned_index_t = typename std::make_unsigned_t<index_t>;\n\
    \n        struct Node {\n            Node* par;\n            Node* ch[2]{ nullptr,\
    \ nullptr };\n            T dat;\n            F laz;\n            Node(Node* par,\
    \ const T& dat) : par(par), dat(dat), laz(id()) {}\n            ~Node() {\n  \
    \              delete ch[0];\n                delete ch[1];\n            }\n \
    \       };\n\n    public:\n        SparseLazySegmentTree() : SparseLazySegmentTree(0)\
    \ {}\n        SparseLazySegmentTree(index_t n) : n(n), root(new Node(nullptr,\
    \ init(0, n))) {}\n\n        ~SparseLazySegmentTree() {\n            delete root;\n\
    \        }\n\n        auto operator[](unsigned_index_t i) {\n            assert(i\
    \ < n);\n            Node* leaf = get_or_create_leaf(i);\n            return UpdateProxyObject{\
    \ leaf->dat, [this, leaf] { update_from(leaf); } };\n        }\n\n        T get(unsigned_index_t\
    \ i) {\n            return (*this)[i];\n        }\n        void set(unsigned_index_t\
    \ i, const T& val) {\n            (*this)[i] = val;\n        }\n        void apply(unsigned_index_t\
    \ i, const F& f) {\n            (*this)[i].apply([this, f](const T& dat) { return\
    \ mapping(f, dat); });\n        }\n\n        T operator()(unsigned_index_t l,\
    \ unsigned_index_t r) {\n            assert(l <= r and r <= n);\n            return\
    \ query(root, l, r);\n        }\n        T prod(unsigned_index_t l, unsigned_index_t\
    \ r) {\n            return (*this)(l, r);\n        }\n        T prod_all() {\n\
    \            return root->dat;\n        }\n\n        void apply(unsigned_index_t\
    \ l, unsigned_index_t r, const F& f) {\n            assert(l <= r and r <= n);\n\
    \            apply(root, f, l, r, 0, n);\n        }\n        void apply_all(const\
    \ F& f) {\n            apply_all(root, f);\n        }\n\n    private:\n      \
    \  unsigned_index_t n;\n        Node* root;\n\n        Node* get_or_create_leaf(unsigned_index_t\
    \ i) {\n            Node* cur = root;\n            while (cur->r - cur->l > 1)\
    \ {\n                push(cur);\n                cur = cur->ch[i >= (cur->l +\
    \ cur->r) >> 1];\n            }\n            return cur;\n        }\n        Node*\
    \ get_or_create_child(Node* node, int index, unsigned_index_t tl, unsigned_index_t\
    \ tr) {\n            if (node->ch[index]) return node->ch[index];\n          \
    \  return node->ch[index] = new Node(node, init(tl, tr));\n        }\n\n     \
    \   void apply_all(Node* node, const F& f) {\n            node->dat = mapping(f,\
    \ node->dat);\n            node->laz = composition(f, node->laz);\n        }\n\
    \        void push(Node* node, unsigned_index_t tl, unsigned_index_t tr) {\n \
    \           unsigned_index_t tm = (tl + tr) >> 1;\n            apply_all(get_or_create_child(node,\
    \ 0, tl, tm), node->laz);\n            apply_all(get_or_create_child(node, 1,\
    \ tm, tr), node->laz);\n            node->laz = id();\n        }\n\n        void\
    \ update(Node* node) {\n            node->dat = op(node->ch[0]->dat, node->ch[1]->dat);\n\
    \        }\n        void update_from(Node* leaf) {\n            while (leaf->par)\
    \ update(leaf = leaf->par);\n        }\n\n        T query(Node* node, unsigned_index_t\
    \ ql, unsigned_index_t qr, unsigned_index_t tl, unsigned_index_t tr) {\n     \
    \       if (tr <= ql or qr <= tl) return e();\n            if (ql <= tl and tr\
    \ <= qr) return node->dat;\n            push(node, tl, tr);\n            unsigned_index_t\
    \ tm = (tl + tr) >> 1;\n            return op(query(node->ch[0], ql, qr, tl, tm),\
    \ query(node->ch[1], ql, qr, tm, tr));\n        }\n\n        void apply(Node*\
    \ node, const F& f, unsigned_index_t ql, unsigned_index_t qr, unsigned_index_t\
    \ tl, unsigned_index_t tr) {\n            if (tr <= ql or qr <= tl) return;\n\
    \            if (ql <= tl and tr <= qr) return apply_all(node, f);\n         \
    \   unsigned_index_t tm = (tl + tr) >> 1;\n            push(node, tl, tr);\n \
    \           apply(node->ch[0], f, ql, qr, tl, tm);\n            apply(node->ch[1],\
    \ f, ql, qr, tm, tr);\n            update(node);\n        }\n    };\n}\n\n#endif\
    \ // SUISEN_SPARSE_LAZY_SEGTREE\n"
  dependsOn:
  - library/util/update_proxy_object.hpp
  - library/type_traits/type_traits.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-05-31 16:25:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/datastructure/segment_tree/sparse_lazy_segment_tree/arc115_e.test.cpp
documentation_of: library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
layout: document
title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u6DFB\u5B57\
  \u96C6\u5408\u304C\u758E\u306A\u5834\u5408)"
---
## 遅延伝播セグメント木 (添字集合が疎な場合)

予め添字集合が分かっている場合は座標圧縮により通常の遅延伝播セグメント木で対応できるが、そうでない場合は本ライブラリを用いる。
