---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: library/datastructure/segment_tree/segment_tree_2d.hpp
    title: library/datastructure/segment_tree/segment_tree_2d.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
    #include <iostream>\n\n#line 1 \"library/datastructure/segment_tree/segment_tree_2d.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\nnamespace suisen {\n    template\
    \ <typename T, T(*op)(T, T), T(*e)()>\n    struct SegmentTree2D {\n        SegmentTree2D()\
    \ {}\n        SegmentTree2D(int n, int m) : SegmentTree2D(std::vector(2 * n, std::vector(2\
    \ * m, e()))) {}\n        SegmentTree2D(const std::vector<std::vector<T>> &a)\
    \ : n(a.size()), m(n == 0 ? 0 : a[0].size()), dat(2 * n, std::vector<T>(2 * m,\
    \ e())) {\n            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)\
    \ {\n                dat[n + i][m + j] = a[i][j];\n            }\n           \
    \ for (int i = 1; i < 2 * n; ++i) for (int j = m - 1; j > 0; --j) {\n        \
    \        dat[i][j] = op(dat[i][2 * j + 0], dat[i][2 * j + 1]);\n            }\n\
    \            for (int i = n - 1; i > 0; --i) for (int j = 1; j < 2 * m; ++j) {\n\
    \                dat[i][j] = op(dat[2 * i + 0][j], dat[2 * i + 1][j]);\n     \
    \       }\n        }\n\n        T operator()(int u, int d, int l, int r) const\
    \ {\n            assert(0 <= u and u <= d and d <= n and 0 <= l and l <= r and\
    \ r <= m);\n            auto inner_query = [&](const auto &seg) {\n          \
    \      T res_l = e(), res_r = e();\n                for (int tl = l + m, tr =\
    \ r + m; tl < tr; tl >>= 1, tr >>= 1) {\n                    if (tl & 1) res_l\
    \ = op(res_l, seg[tl++]);\n                    if (tr & 1) res_r = op(seg[--tr],\
    \ res_r);\n                }\n                return op(res_l, res_r);\n     \
    \       };\n            T res_u = e(), res_d = e();\n            for (int tu =\
    \ u + n, td = d + n; tu < td; tu >>= 1, td >>= 1) {\n                if (tu &\
    \ 1) res_u = op(res_u, inner_query(dat[tu++]));\n                if (td & 1) res_d\
    \ = op(inner_query(dat[--td]), res_d);\n            }\n            return op(res_u,\
    \ res_d);\n        }\n\n        T get(int i, int j) const {\n            assert(0\
    \ <= i and i < n and 0 <= j and j < m);\n            return dat[n + i][m + j];\n\
    \        }\n\n        void set(int i, int j, const T &val) {\n            assert(0\
    \ <= i and i < n and 0 <= j and j < m);\n            dat[n + i][m + j] = val;\n\
    \            for (int tj = (m + j) >> 1; tj; tj >>= 1) {\n                dat[n\
    \ + i][tj] = op(dat[n + i][2 * tj + 0], dat[n + i][2 * tj + 1]);\n           \
    \ }\n            for (int ti = (n + i) >> 1; ti; ti >>= 1) {\n               \
    \ for (int tj = m + j; tj; tj >>= 1) {\n                    dat[ti][tj] = op(dat[2\
    \ * ti + 0][tj], dat[2 * ti + 1][tj]);\n                }\n            }\n   \
    \     }\n\n    private:\n        int n, m;\n        std::vector<std::vector<T>>\
    \ dat;\n    };\n}\n\n\n#line 6 \"test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp\"\
    \nusing suisen::SegmentTree2D;\n\nlong long op(long long x, long long y) {\n \
    \   return x + y;\n}\nlong long e() {\n    return 0;\n}\n\nconstexpr int L = 25;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<long long>>\
    \ a(L, std::vector<long long>(n));\n    for (int i = 0; i < n; ++i) {\n      \
    \  long long v;\n        std::cin >> v;\n        for (int j = 0; j < L; ++j) a[j][i]\
    \ = v & (3LL << (2 * j));\n    }\n\n    SegmentTree2D<long long, op, e> seg(a);\n\
    \    while (q --> 0) {\n        int t;\n        std::cin >> t;\n        if (t\
    \ == 0) {\n            int p, x;\n            std::cin >> p >> x;\n          \
    \  long long val = seg(0, L, p, p + 1) + x;\n            for (int j = 0; j < L;\
    \ ++j) {\n                seg.set(j, p, val & (3LL << (2 * j)));\n           \
    \ }\n        } else {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            std::cout << seg(0, L, l, r) << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n\n#include \"library/datastructure/segment_tree/segment_tree_2d.hpp\"\
    \nusing suisen::SegmentTree2D;\n\nlong long op(long long x, long long y) {\n \
    \   return x + y;\n}\nlong long e() {\n    return 0;\n}\n\nconstexpr int L = 25;\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::vector<long long>>\
    \ a(L, std::vector<long long>(n));\n    for (int i = 0; i < n; ++i) {\n      \
    \  long long v;\n        std::cin >> v;\n        for (int j = 0; j < L; ++j) a[j][i]\
    \ = v & (3LL << (2 * j));\n    }\n\n    SegmentTree2D<long long, op, e> seg(a);\n\
    \    while (q --> 0) {\n        int t;\n        std::cin >> t;\n        if (t\
    \ == 0) {\n            int p, x;\n            std::cin >> p >> x;\n          \
    \  long long val = seg(0, L, p, p + 1) + x;\n            for (int j = 0; j < L;\
    \ ++j) {\n                seg.set(j, p, val & (3LL << (2 * j)));\n           \
    \ }\n        } else {\n            int l, r;\n            std::cin >> l >> r;\n\
    \            std::cout << seg(0, L, l, r) << '\\n';\n        }\n    }\n    return\
    \ 0;\n}"
  dependsOn:
  - library/datastructure/segment_tree/segment_tree_2d.hpp
  isVerificationFile: true
  path: test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2022-01-17 22:14:37+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp
- /verify/test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp.html
title: test/src/datastructure/segment_tree/segment_tree_2d/point_add_range_sum.test.cpp
---
