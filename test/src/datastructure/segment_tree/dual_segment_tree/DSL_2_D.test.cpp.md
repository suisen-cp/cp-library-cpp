---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u4F5C\u7528\u304C\u53EF\
      \u63DB\u306A\u5834\u5408)"
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \n\n\n\n#line 1 \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
    \n\n#define SUISEN_DUAL_SEGTREE\n\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ suisen {\n    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F,\
    \ F), F(*id)()>\n    struct CommutativeDualSegmentTree {\n        CommutativeDualSegmentTree()\
    \ {}\n        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()), m(ceil_pow2(a.size())),\
    \ data(std::move(a)), lazy(m, id()) {}\n        CommutativeDualSegmentTree(const\
    \ std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a)) {}\n    \
    \    CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n,\
    \ fill_value)) {}\n\n        T operator[](int i) const {\n            assert(0\
    \ <= i and i < n);\n            T res = data[i];\n            for (i = (i + m)\
    \ >> 1; i; i >>= 1) res = mapping(lazy[i], res);\n            return res;\n  \
    \      }\n        T get(int i) const {\n            return (*this)[i];\n     \
    \   }\n        void apply(int l, int r, const F& f) {\n            assert(0 <=\
    \ l and r <= n);\n            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {\n\
    \                if (l & 1) apply(l++, f);\n                if (r & 1) apply(--r,\
    \ f);\n            }\n        }\n    protected:\n        int n, m;\n        std::vector<T>\
    \ data;\n        std::vector<F> lazy;\n\n        void apply(int k, const F& f)\
    \ {\n            if (k < m) {\n                lazy[k] = composition(f, lazy[k]);\n\
    \            } else {\n                data[k - m] = mapping(f, data[k - m]);\n\
    \            }\n        }\n    private:\n        static int ceil_pow2(int n) {\n\
    \            int m = 1;\n            while (m < n) m <<= 1;\n            return\
    \ m;\n        }\n    };\n} // namespace suisen\n\n#endif // SUISEN_COM_DUAL_SEGTREE\n\
    #line 5 \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\n\nnamespace\
    \ suisen {\n    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F,\
    \ F), F(*id)()>\n    struct DualSegmentTree : public CommutativeDualSegmentTree<T,\
    \ F, mapping, composition, id> {\n        using base_type = CommutativeDualSegmentTree<T,\
    \ F, mapping, composition, id>;\n        using base_type::base_type;\n       \
    \ void apply(int l, int r, const F& f) {\n            push(l, r);\n          \
    \  base_type::apply(l, r, f);\n        }\n    private:\n        void push(int\
    \ k) {\n            base_type::apply(2 * k, this->lazy[k]), base_type::apply(2\
    \ * k + 1, this->lazy[k]);\n            this->lazy[k] = id();\n        }\n   \
    \     void push(int l, int r) {\n            static const int log = __builtin_ctz(this->m);\n\
    \            l += this->m, r += this->m;\n            for (int i = log; (l >>\
    \ i) << i != l; --i) push(l >> i);\n            for (int i = log; (r >> i) <<\
    \ i != r; --i) push(r >> i);\n        }\n    };\n\n    template <typename T, typename\
    \ F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    DualSegmentTree(int,\
    \ T)->DualSegmentTree<T, F, mapping, composition, id>;\n\n    template <typename\
    \ T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n    DualSegmentTree(std::vector<T>)->DualSegmentTree<T,\
    \ F, mapping, composition, id>;\n} // namespace suisen\n\n\n\n#line 6 \"test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp\"\
    \nusing suisen::DualSegmentTree;\n\nint mapping(int f, int x) {\n    return f\
    \ < 0 ? x : f;\n}\nint composition(int f, int g) {\n    return f < 0 ? g : f;\n\
    }\nint id() {\n    return -1;\n}\n\nint main() {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    DualSegmentTree<int, int, mapping, composition, id> seg(n, std::numeric_limits<int>::max());\n\
    \    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n \
    \       if (t == 0) {\n            int s, t, x;\n            std::cin >> s >>\
    \ t >> x;\n            seg.apply(s, ++t, x);\n        } else {\n            int\
    \ i;\n            std::cin >> i;\n            std::cout << seg[i] << '\\n';\n\
    \        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree/dual_segment_tree.hpp\"\
    \nusing suisen::DualSegmentTree;\n\nint mapping(int f, int x) {\n    return f\
    \ < 0 ? x : f;\n}\nint composition(int f, int g) {\n    return f < 0 ? g : f;\n\
    }\nint id() {\n    return -1;\n}\n\nint main() {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    DualSegmentTree<int, int, mapping, composition, id> seg(n, std::numeric_limits<int>::max());\n\
    \    for (int i = 0; i < q; ++i) {\n        int t;\n        std::cin >> t;\n \
    \       if (t == 0) {\n            int s, t, x;\n            std::cin >> s >>\
    \ t >> x;\n            seg.apply(s, ++t, x);\n        } else {\n            int\
    \ i;\n            std::cin >> i;\n            std::cout << seg[i] << '\\n';\n\
    \        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/dual_segment_tree.hpp
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
  requiredBy: []
  timestamp: '2022-07-16 03:53:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
- /verify/test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp.html
title: test/src/datastructure/segment_tree/dual_segment_tree/DSL_2_D.test.cpp
---
