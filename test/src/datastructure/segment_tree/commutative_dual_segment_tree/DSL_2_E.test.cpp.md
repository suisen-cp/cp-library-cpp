---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728 (\u4F5C\u7528\u304C\u53EF\
      \u63DB\u306A\u5834\u5408)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E\"\
    \n\n#include <iostream>\n\n#line 1 \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>\n\
    \    struct CommutativeDualSegmentTree {\n        CommutativeDualSegmentTree()\
    \ = default;\n        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()),\
    \ m(ceil_pow2(a.size())), data(std::move(a)), lazy(m, id()) {}\n        CommutativeDualSegmentTree(const\
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
    \            } else if (k - m < n) {\n                data[k - m] = mapping(f,\
    \ data[k - m]);\n            }\n        }\n    private:\n        static int ceil_pow2(int\
    \ n) {\n            int m = 1;\n            while (m < n) m <<= 1;\n         \
    \   return m;\n        }\n    };\n} // namespace suisen\n\n\n#line 6 \"test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp\"\
    \nusing suisen::CommutativeDualSegmentTree;\n\nint mapping(int f, int x) { return\
    \ f + x; }\nint composition(int f, int g) { return f + g; }\nint id() { return\
    \ 0; }\n\nint main() {\n    int n, q;\n    std::cin >> n >> q;\n    CommutativeDualSegmentTree<int,\
    \ int, mapping, composition, id> seg(n, 0);\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        std::cin >> t;\n        if (t == 0) {\n            int\
    \ s, t, x;\n            std::cin >> s >> t >> x;\n            seg.apply(--s, t,\
    \ x);\n        } else {\n            int i;\n            std::cin >> i;\n    \
    \        std::cout << seg[--i] << '\\n';\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E\"\
    \n\n#include <iostream>\n\n#include \"library/datastructure/segment_tree/commutative_dual_segment_tree.hpp\"\
    \nusing suisen::CommutativeDualSegmentTree;\n\nint mapping(int f, int x) { return\
    \ f + x; }\nint composition(int f, int g) { return f + g; }\nint id() { return\
    \ 0; }\n\nint main() {\n    int n, q;\n    std::cin >> n >> q;\n    CommutativeDualSegmentTree<int,\
    \ int, mapping, composition, id> seg(n, 0);\n    for (int i = 0; i < q; ++i) {\n\
    \        int t;\n        std::cin >> t;\n        if (t == 0) {\n            int\
    \ s, t, x;\n            std::cin >> s >> t >> x;\n            seg.apply(--s, t,\
    \ x);\n        } else {\n            int i;\n            std::cin >> i;\n    \
    \        std::cout << seg[--i] << '\\n';\n        }\n    }\n    return 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/commutative_dual_segment_tree.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
  requiredBy: []
  timestamp: '2023-07-09 04:04:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
- /verify/test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp.html
title: test/src/datastructure/segment_tree/commutative_dual_segment_tree/DSL_2_E.test.cpp
---
