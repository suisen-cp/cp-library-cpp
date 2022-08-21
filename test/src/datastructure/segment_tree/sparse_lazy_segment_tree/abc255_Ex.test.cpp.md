---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u4F1D\u64AD\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u6DFB\u5B57\
      \u96C6\u5408\u304C\u758E\u306A\u5834\u5408)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://atcoder.jp/contests/abc255/tasks/abc255_Ex
    links:
    - https://atcoder.jp/contests/abc255/tasks/abc255_Ex
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp\"\
    \n#define PROBLEM \"https://atcoder.jp/contests/abc255/tasks/abc255_Ex\"\n\n#include\
    \ <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#line 1 \"library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\"\n\
    \n\n\n#include <array>\n#include <cassert>\n#include <vector>\n\nnamespace suisen\
    \ {\n    template <\n        typename IndexType,                      // type\
    \ of index (integral: bool, long long, etc.)\n        typename T,            \
    \                  // type of element\n        T(*op)(T, T),                 \
    \           // type of binary operator on T\n        T(*e)(),                \
    \                 //\n        typename F,                              // type\
    \ of operator which acts on T\n        T(*mapping)(F, T, IndexType, IndexType),\
    \ // type of action F on T\n        F(*composition)(F, F),                   //\
    \ type of binary operator on F\n        F(*id)(),                            \
    \    //\n        T(*init)(IndexType, IndexType)           // type of function\
    \ which initializes product of segment [l, r)\n    >\n    struct SparseLazySegmentTree\
    \ {\n        using index_type = IndexType;\n        using value_type = T;\n  \
    \      using operator_type = F;\n    private:\n        using pool_index_type =\
    \ uint32_t;\n\n        struct Node {\n            pool_index_type ch[2]{ 0, 0\
    \ };\n            value_type dat;\n            operator_type laz;\n          \
    \  Node(const value_type& dat) : dat(dat), laz(id()) {}\n        };\n\n      \
    \  static inline std::vector<Node> pool{ Node{ e() } };\n\n        static pool_index_type\
    \ new_node(const value_type& dat) {\n            const pool_index_type res = pool.size();\n\
    \            return pool.emplace_back(dat), res;\n        }\n    public:\n   \
    \     SparseLazySegmentTree() : SparseLazySegmentTree(0) {}\n        explicit\
    \ SparseLazySegmentTree(IndexType n) : n(n), root(new_node(init(0, n))) {}\n\n\
    \        static void reserve(int siz) {\n            pool.reserve(siz);\n    \
    \    }\n\n        value_type get(index_type i) const {\n            assert(0 <=\
    \ i and i < n);\n            operator_type f = id();\n            pool_index_type\
    \ cur = root;\n            for (std::array<index_type, 2> lr { 0, n }; cur and\
    \ lr[1] - lr[0] > 1;) {\n                index_type m = (lr[0] + lr[1]) >> 1;\n\
    \                bool b = i >= m;\n                f = composition(f, pool[cur].laz);\n\
    \                cur = pool[cur].ch[b], lr[not b] = m;\n            }\n      \
    \      return mapping(f, cur ? pool[cur].dat : init(i, i + 1), i, i + 1);\n  \
    \      }\n        template <typename Fun>\n        void apply_fun(index_type i,\
    \ Fun &&fun) {\n            assert(0 <= i and i < n);\n            static std::vector<pool_index_type>\
    \ path;\n            pool_index_type cur = root;\n            for (std::array<index_type,\
    \ 2> lr { 0, n }; lr[1] - lr[0] > 1;) {\n                path.push_back(cur);\n\
    \                index_type m = (lr[0] + lr[1]) >> 1;\n                bool b\
    \ = i >= m;\n                push(cur);\n                cur = pool[cur].ch[b],\
    \ lr[not b] = m;\n            }\n            pool[cur].dat = fun(pool[cur].dat);\n\
    \            while (path.size()) update(path.back()), path.pop_back();\n     \
    \   }\n        void set(index_type i, const value_type& val) {\n            apply_fun(i,\
    \ [&val](const value_type&) { return val; });\n        }\n        void apply(index_type\
    \ i, const operator_type& f) {\n            apply_fun(i, [&f, i](const value_type&\
    \ val) { return mapping(f, val, i, i + 1); });\n        }\n\n        value_type\
    \ operator()(index_type l, index_type r) {\n            assert(0 <= l and l <=\
    \ r and r <= n);\n            return query(root, l, r, 0, n);\n        }\n   \
    \     value_type prod(index_type l, index_type r) {\n            return (*this)(l,\
    \ r);\n        }\n        value_type prod_all() {\n            return pool[root].dat;\n\
    \        }\n\n        void apply(index_type l, index_type r, const operator_type&\
    \ f) {\n            assert(0 <= l and l <= r and r <= n);\n            apply(root,\
    \ f, l, r, 0, n);\n        }\n        void apply_all(const operator_type& f) {\n\
    \            apply_all(root, f, 0, n);\n        }\n\n    private:\n        index_type\
    \ n;\n        pool_index_type root;\n\n        pool_index_type get_or_create_child(pool_index_type\
    \ node, int index, index_type tl, index_type tr) {\n            if (pool[node].ch[index])\
    \ return pool[node].ch[index];\n            const pool_index_type ch = new_node(init(tl,\
    \ tr));\n            return pool[node].ch[index] = ch;\n        }\n\n        void\
    \ apply_all(pool_index_type node, const operator_type& f, index_type tl, index_type\
    \ tr) {\n            pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n  \
    \          pool[node].laz = composition(f, pool[node].laz);\n        }\n     \
    \   void push(pool_index_type node, index_type tl, index_type tr) {\n        \
    \    const index_type tm = (tl + tr) >> 1;\n            const operator_type laz\
    \ = pool[node].laz;\n            apply_all(get_or_create_child(node, 0, tl, tm),\
    \ laz, tl, tm);\n            apply_all(get_or_create_child(node, 1, tm, tr), laz,\
    \ tm, tr);\n            pool[node].laz = id();\n        }\n\n        void update(pool_index_type\
    \ node) {\n            pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \            pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n        }\n\n\
    \        value_type query(pool_index_type node, index_type ql, index_type qr,\
    \ index_type tl, index_type tr) {\n            if (tr <= ql or qr <= tl) return\
    \ e();\n            if (ql <= tl and tr <= qr) return pool[node].dat;\n      \
    \      push(node, tl, tr);\n            const index_type tm = (tl + tr) >> 1;\n\
    \            return op(query(pool[node].ch[0], ql, qr, tl, tm), query(pool[node].ch[1],\
    \ ql, qr, tm, tr));\n        }\n\n        void apply(pool_index_type node, const\
    \ operator_type& f, index_type ql, index_type qr, index_type tl, index_type tr)\
    \ {\n            if (tr <= ql or qr <= tl) return;\n            if (ql <= tl and\
    \ tr <= qr) return apply_all(node, f, tl, tr);\n            const index_type tm\
    \ = (tl + tr) >> 1;\n            push(node, tl, tr);\n            apply(pool[node].ch[0],\
    \ f, ql, qr, tl, tm), apply(pool[node].ch[1], f, ql, qr, tm, tr);\n          \
    \  update(node);\n        }\n    };\n}\n\n\n#line 9 \"test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp\"\
    \n\nmint sum_lr(mint l, mint r) {\n    static const mint inv_2 = mint(2).inv();\n\
    \    return (r * (r - 1) - l * (l - 1)) * inv_2;\n}\n\nmint init(long long, long\
    \ long) {\n    return 0;\n}\nmint op(mint x, mint y) {\n    return x + y;\n}\n\
    mint e() {\n    return 0;\n}\nmint mapping(std::pair<bool, mint> f, mint x, long\
    \ long l, long long r) {\n    return f.first ? f.second * sum_lr(l, r) : x;\n\
    }\nstd::pair<bool, mint> composition(std::pair<bool, mint> f, std::pair<bool,\
    \ mint> g) {\n    return not f.first ? g : f;\n}\nstd::pair<bool, mint> id() {\n\
    \    return { false, 0 };\n}\n\nusing SegTree = suisen::SparseLazySegmentTree<long\
    \ long, mint, op, e, std::pair<bool, mint>, mapping, composition, id, init>;\n\
    \nconstexpr long long inf = 1'000'000'000'000'000'010LL;\n\nint main() {\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    long long\
    \ n;\n    int q;\n    std::cin >> n >> q;\n\n    SegTree seg(inf);\n    SegTree::reserve(10000000);\n\
    \n    while (q --> 0) {\n        long long d, l, r;\n        std::cin >> d >>\
    \ l >> r;\n        ++r;\n        std::cout << (d * sum_lr(l, r) - seg.prod(l,\
    \ r)).val() << '\\n';\n        seg.apply(l, r, { true, d });\n    }\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://atcoder.jp/contests/abc255/tasks/abc255_Ex\"\n\n\
    #include <iostream>\n#include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\n\
    \n#include \"library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\"\
    \n\nmint sum_lr(mint l, mint r) {\n    static const mint inv_2 = mint(2).inv();\n\
    \    return (r * (r - 1) - l * (l - 1)) * inv_2;\n}\n\nmint init(long long, long\
    \ long) {\n    return 0;\n}\nmint op(mint x, mint y) {\n    return x + y;\n}\n\
    mint e() {\n    return 0;\n}\nmint mapping(std::pair<bool, mint> f, mint x, long\
    \ long l, long long r) {\n    return f.first ? f.second * sum_lr(l, r) : x;\n\
    }\nstd::pair<bool, mint> composition(std::pair<bool, mint> f, std::pair<bool,\
    \ mint> g) {\n    return not f.first ? g : f;\n}\nstd::pair<bool, mint> id() {\n\
    \    return { false, 0 };\n}\n\nusing SegTree = suisen::SparseLazySegmentTree<long\
    \ long, mint, op, e, std::pair<bool, mint>, mapping, composition, id, init>;\n\
    \nconstexpr long long inf = 1'000'000'000'000'000'010LL;\n\nint main() {\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    long long\
    \ n;\n    int q;\n    std::cin >> n >> q;\n\n    SegTree seg(inf);\n    SegTree::reserve(10000000);\n\
    \n    while (q --> 0) {\n        long long d, l, r;\n        std::cin >> d >>\
    \ l >> r;\n        ++r;\n        std::cout << (d * sum_lr(l, r) - seg.prod(l,\
    \ r)).val() << '\\n';\n        seg.apply(l, r, { true, d });\n    }\n\n    return\
    \ 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
  requiredBy: []
  timestamp: '2022-06-14 00:05:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
- /verify/test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp.html
title: test/src/datastructure/segment_tree/sparse_lazy_segment_tree/abc255_Ex.test.cpp
---
