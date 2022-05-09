---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: library/type_traits/type_traits.hpp
    title: Type Traits
  - icon: ':question:'
    path: library/util/update_proxy_object.hpp
    title: Update Proxy Object
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/datastructure/segment_tree/sparse_segment_tree.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1\
    \ \"library/type_traits/type_traits.hpp\"\n\n\n\n#include <limits>\n#include <type_traits>\n\
    \nnamespace suisen {\n// ! utility\ntemplate <typename ...Types>\nusing constraints_t\
    \ = std::enable_if_t<std::conjunction_v<Types...>, std::nullptr_t>;\ntemplate\
    \ <bool cond_v, typename Then, typename OrElse>\nconstexpr decltype(auto) constexpr_if(Then&&\
    \ then, OrElse&& or_else) {\n    if constexpr (cond_v) {\n        return std::forward<Then>(then);\n\
    \    } else {\n        return std::forward<OrElse>(or_else);\n    }\n}\n\n// !\
    \ function\ntemplate <typename ReturnType, typename Callable, typename ...Args>\n\
    using is_same_as_invoke_result = std::is_same<std::invoke_result_t<Callable, Args...>,\
    \ ReturnType>;\ntemplate <typename F, typename T>\nusing is_uni_op = is_same_as_invoke_result<T,\
    \ F, T>;\ntemplate <typename F, typename T>\nusing is_bin_op = is_same_as_invoke_result<T,\
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
    \ = typename safely_multipliable<T>::type;\n\n} // namespace suisen\n\n\n#line\
    \ 1 \"library/util/update_proxy_object.hpp\"\n\n\n\n#line 5 \"library/util/update_proxy_object.hpp\"\
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
    #line 10 \"library/datastructure/segment_tree/sparse_segment_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <\n        typename index_t,  // type of index (integral:\
    \ int, long long, etc.)\n        typename T,        // type of element\n     \
    \   T(*op)(T, T),      // binary operator\n        T(*e)(),           // identity\
    \ element\n        T(*init)(int, int) // initializer of the product of segment\
    \ [l, r)\n    >\n    class SparseSegmentTree {\n        using unsigned_index_t\
    \ = typename std::make_unsigned_t<index_t>;\n\n        struct Node {\n       \
    \     Node* ch[2]{ nullptr, nullptr };\n            T dat;\n            Node(const\
    \ T& dat) : dat(dat) {}\n            ~Node() {\n                delete ch[0];\n\
    \                delete ch[1];\n            }\n        };\n\n    public:\n   \
    \     SparseSegmentTree() : SparseSegmentTree(0) {}\n        SparseSegmentTree(index_t\
    \ n) : n(n), root(new Node(nullptr, init(0, n))) {}\n        ~SparseSegmentTree()\
    \ {\n            delete root;\n        }\n\n        auto operator[](unsigned_index_t\
    \ i) {\n            assert(i < n);\n            std::vector<Node*> tmp_path =\
    \ get_or_create_leaf(i);\n            T& val = tmp_path.back()->dat;\n       \
    \     tmp_path.pop_back();\n            std::reverse(tmp_path.begin(), tmp_path.end());\n\
    \            auto update_func = [path = std::move(tmp_path)] { for (Node *node\
    \ : path) update(node); };\n            return UpdateProxyObject{ val, update_func\
    \ };\n        }\n        T get(unsigned_index_t i) { return (*this)[i]; }\n  \
    \      void set(unsigned_index_t i, const T& val) { (*this)[i] = val; }\n\n  \
    \      T operator()(unsigned_index_t l, unsigned_index_t r) {\n            assert(l\
    \ <= r and r <= n);\n            return query(root, l, r, 0, n);\n        }\n\
    \        T prod(unsigned_index_t l, unsigned_index_t r) { return (*this)(l, r);\
    \ }\n        T all_prod() const { return root->dat; }\n    private:\n        unsigned_index_t\
    \ n;\n        Node* root;\n\n        Node* get_or_create_child(Node* node, unsigned\
    \ int index, unsigned_index_t tl, unsigned_index_t tr) {\n            if (node->ch[index])\
    \ node->ch[index];\n            return node->ch[index] = new Node(init(tl, tr));\n\
    \        }\n\n        std::vector<Node*> get_or_create_leaf(unsigned_index_t i,\
    \ unsigned_index_t tl, unsigned_index_t tr) {\n            Node* cur = root;\n\
    \            std::vector<Node*> nodes { cur };\n            while (tr - tl > 1)\
    \ {\n                if (unsigned_index_t tm = (tl + tr) >> 1; i < tm) {\n   \
    \                 cur = get_or_create_child(cur, 0, tl, tm);\n               \
    \ } else {\n                    cur = get_or_create_child(cur, 1, tm, tr);\n \
    \               }\n                nodes.push_back(cur);\n            }\n    \
    \        return nodes;\n        }\n\n        void update(Node* node) {\n     \
    \       node->dat = op(get_or_create_child(node, 0)->dat, get_or_create_child(node,\
    \ 1)->dat);\n        }\n\n        T query(Node* node, unsigned_index_t ql, unsigned_index_t\
    \ qr, unsigned_index_t tl, unsigned_index_t tr) {\n            if (tr <= ql or\
    \ qr <= tl) return e();\n            if (ql <= tl and tr <= qr) return node->dat;\n\
    \            unsigned_index_t tm = (tl + tr) >> 1;\n            Node* lch = get_or_create_child(node,\
    \ 0, tl, tm);\n            Node* rch = get_or_create_child(node, 1, tm, tr);\n\
    \            return op(query(lch, ql, qr, tl, tm), query(rch, ql, qr, tm, tr));\n\
    \        }\n    };\n\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_SPARSE_SEGTREE\n#define SUISEN_SPARSE_SEGTREE\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\n#include \"library/type_traits/type_traits.hpp\"\
    \n#include \"library/util/update_proxy_object.hpp\"\n\nnamespace suisen {\n  \
    \  template <\n        typename index_t,  // type of index (integral: int, long\
    \ long, etc.)\n        typename T,        // type of element\n        T(*op)(T,\
    \ T),      // binary operator\n        T(*e)(),           // identity element\n\
    \        T(*init)(int, int) // initializer of the product of segment [l, r)\n\
    \    >\n    class SparseSegmentTree {\n        using unsigned_index_t = typename\
    \ std::make_unsigned_t<index_t>;\n\n        struct Node {\n            Node* ch[2]{\
    \ nullptr, nullptr };\n            T dat;\n            Node(const T& dat) : dat(dat)\
    \ {}\n            ~Node() {\n                delete ch[0];\n                delete\
    \ ch[1];\n            }\n        };\n\n    public:\n        SparseSegmentTree()\
    \ : SparseSegmentTree(0) {}\n        SparseSegmentTree(index_t n) : n(n), root(new\
    \ Node(nullptr, init(0, n))) {}\n        ~SparseSegmentTree() {\n            delete\
    \ root;\n        }\n\n        auto operator[](unsigned_index_t i) {\n        \
    \    assert(i < n);\n            std::vector<Node*> tmp_path = get_or_create_leaf(i);\n\
    \            T& val = tmp_path.back()->dat;\n            tmp_path.pop_back();\n\
    \            std::reverse(tmp_path.begin(), tmp_path.end());\n            auto\
    \ update_func = [path = std::move(tmp_path)] { for (Node *node : path) update(node);\
    \ };\n            return UpdateProxyObject{ val, update_func };\n        }\n \
    \       T get(unsigned_index_t i) { return (*this)[i]; }\n        void set(unsigned_index_t\
    \ i, const T& val) { (*this)[i] = val; }\n\n        T operator()(unsigned_index_t\
    \ l, unsigned_index_t r) {\n            assert(l <= r and r <= n);\n         \
    \   return query(root, l, r, 0, n);\n        }\n        T prod(unsigned_index_t\
    \ l, unsigned_index_t r) { return (*this)(l, r); }\n        T all_prod() const\
    \ { return root->dat; }\n    private:\n        unsigned_index_t n;\n        Node*\
    \ root;\n\n        Node* get_or_create_child(Node* node, unsigned int index, unsigned_index_t\
    \ tl, unsigned_index_t tr) {\n            if (node->ch[index]) node->ch[index];\n\
    \            return node->ch[index] = new Node(init(tl, tr));\n        }\n\n \
    \       std::vector<Node*> get_or_create_leaf(unsigned_index_t i, unsigned_index_t\
    \ tl, unsigned_index_t tr) {\n            Node* cur = root;\n            std::vector<Node*>\
    \ nodes { cur };\n            while (tr - tl > 1) {\n                if (unsigned_index_t\
    \ tm = (tl + tr) >> 1; i < tm) {\n                    cur = get_or_create_child(cur,\
    \ 0, tl, tm);\n                } else {\n                    cur = get_or_create_child(cur,\
    \ 1, tm, tr);\n                }\n                nodes.push_back(cur);\n    \
    \        }\n            return nodes;\n        }\n\n        void update(Node*\
    \ node) {\n            node->dat = op(get_or_create_child(node, 0)->dat, get_or_create_child(node,\
    \ 1)->dat);\n        }\n\n        T query(Node* node, unsigned_index_t ql, unsigned_index_t\
    \ qr, unsigned_index_t tl, unsigned_index_t tr) {\n            if (tr <= ql or\
    \ qr <= tl) return e();\n            if (ql <= tl and tr <= qr) return node->dat;\n\
    \            unsigned_index_t tm = (tl + tr) >> 1;\n            Node* lch = get_or_create_child(node,\
    \ 0, tl, tm);\n            Node* rch = get_or_create_child(node, 1, tm, tr);\n\
    \            return op(query(lch, ql, qr, tl, tm), query(rch, ql, qr, tm, tr));\n\
    \        }\n    };\n\n} // namespace suisen\n\n#endif // SUISEN_SPARSE_SEGTREE\n"
  dependsOn:
  - library/type_traits/type_traits.hpp
  - library/util/update_proxy_object.hpp
  isVerificationFile: false
  path: library/datastructure/segment_tree/sparse_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-05-09 17:42:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/datastructure/segment_tree/sparse_segment_tree.hpp
layout: document
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u6DFB\u5B57\u96C6\u5408\u304C\u758E\
  \u306A\u5834\u5408)"
---
## セグメント木 (添字集合が疎な場合)

予め添字集合が分かっている場合は座標圧縮により通常のセグメント木で対応できるが、そうでない場合は本ライブラリを用いる。
