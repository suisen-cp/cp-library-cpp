---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/algorithm/monotone_minima.hpp
    title: library/algorithm/monotone_minima.hpp
  - icon: ':heavy_check_mark:'
    path: library/convolution/min_plus_convolution.hpp
    title: library/convolution/min_plus_convolution.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
  bundledCode: "#line 1 \"test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#line 1 \"library/convolution/min_plus_convolution.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <vector>\n\n#line 1 \"library/algorithm/monotone_minima.hpp\"\
    \n\n\n\n#line 7 \"library/algorithm/monotone_minima.hpp\"\n\nnamespace suisen\
    \ {\n    /**\n     * @param n # rows\n     * @param m # cols\n     * @param compare\
    \ (row, col1, col2 (> col1)) -> bool (= A(row, col1) <= A(row, col2))\n     *\
    \ @return std::vector<int> res s.t. res[i] = argmin_j f(i,j)\n     */\n    template\
    \ <typename Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, size_t,\
    \ size_t, size_t>, std::nullptr_t> = nullptr>\n    std::vector<int> monotone_minima(size_t\
    \ n, size_t m, const Compare &compare) {\n        std::vector<int> res(n);\n \
    \       auto rec = [&](auto rec, size_t u, size_t d, size_t l, size_t r) -> void\
    \ {\n            if (u == d) return;\n            assert(l < r);\n           \
    \ const size_t row = (u + d) >> 1;\n            size_t argmin = l;\n         \
    \   for (size_t col = l + 1; col < r; ++col) if (not compare(row, argmin, col))\
    \ argmin = col;\n            res[row] = argmin;\n            rec(rec, u, row,\
    \ l, argmin + 1);\n            rec(rec, row + 1, d, argmin, r);\n        };\n\
    \        rec(rec, 0, n, 0, m);\n        return res;\n    }\n\n    /**\n     *\
    \ @param n # rows\n     * @param m # cols\n     * @param matrix (row, col) ->\
    \ value\n     * @return std::vector<int> res s.t. res[i] = argmin_j f(i,j)\n \
    \    */\n    template <typename Matrix, std::enable_if_t<std::is_invocable_v<Matrix,\
    \ size_t, size_t>, std::nullptr_t> = nullptr>\n    std::vector<int> monotone_minima(size_t\
    \ n, size_t m, const Matrix &matrix) {\n        return monotone_minima(n, m, [&matrix](size_t\
    \ i, size_t j1, size_t j2) { return matrix(i, j1) <= matrix(i, j2); });\n    }\n\
    } // namespace suisen\n\n\n\n#line 10 \"library/convolution/min_plus_convolution.hpp\"\
    \n\nnamespace suisen {\n    template <typename T>\n    std::vector<T> min_plus_convolution_convex_convex(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n        const int n = a.size(),\
    \ m = b.size();\n        assert(n and m);\n        // check if convex\n      \
    \  for (int i = 2; i < n; ++i) assert(a[i - 1] - a[i - 2] <= a[i] - a[i - 1]);\n\
    \        // check if convex\n        for (int j = 2; j < m; ++j) assert(b[j -\
    \ 1] - b[j - 2] <= b[j] - b[j - 1]);\n\n        std::vector<T> c(n + m - 1);\n\
    \        c[0] = a[0] + b[0];\n        for (int k = 0, i = 0; k < n + m - 2; ++k)\
    \ {\n            int j = k - i;\n            if (j == m - 1 or (i < n - 1 and\
    \ a[i + 1] + b[j] < a[i] + b[j + 1])) {\n                c[k + 1] = a[++i] + b[j];\n\
    \            } else {\n                c[k + 1] = a[i] + b[++j];\n           \
    \ }\n        }\n        return c;\n    }\n\n    template <typename T>\n    std::vector<T>\
    \ min_plus_convolution_convex_arbitrary(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n        const int n = a.size(), m = b.size();\n        assert(n and m);\n\
    \        // check if convex\n        for (int i = 2; i < n; ++i) assert(a[i -\
    \ 1] - a[i - 2] <= a[i] - a[i - 1]);\n\n        std::vector<int> argmin = monotone_minima(\n\
    \            n + m - 1, m,\n            [&](int k, int j1, int j2) {\n       \
    \         const int i1 = k - j1, i2 = k - j2;\n                // upper right\
    \ triangle\n                if (i2 < 0) return true;\n                // lower\
    \ left triangle\n                if (i1 >= n) return false;\n                return\
    \ a[i1] + b[j1] < a[i2] + b[j2];\n            }\n        );\n        std::vector<T>\
    \ c(n + m - 1);\n        for (int k = 0; k < n + m - 1; ++k) {\n            const\
    \ int j = argmin[k], i = k - j;\n            c[k] = a[i] + b[j];\n        }\n\
    \        return c;\n    }\n} // namespace suisen\n\n\n#line 4 \"test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<int>\
    \ a(n), b(m);\n    for (auto &e : a) std::cin >> e;\n    for (auto &e : b) std::cin\
    \ >> e;\n\n    std::vector<int> c = suisen::min_plus_convolution_convex_convex(a,\
    \ b);\n    for (int i = 0; i < n + m - 1; ++i) {\n        std::cout << c[i];\n\
    \        if (i + 1 != n + m - 1) std::cout << ' ';\n    }\n    std::cout << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n\n#include \"library/convolution/min_plus_convolution.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n\n    std::vector<int> a(n), b(m);\n\
    \    for (auto &e : a) std::cin >> e;\n    for (auto &e : b) std::cin >> e;\n\n\
    \    std::vector<int> c = suisen::min_plus_convolution_convex_convex(a, b);\n\
    \    for (int i = 0; i < n + m - 1; ++i) {\n        std::cout << c[i];\n     \
    \   if (i + 1 != n + m - 1) std::cout << ' ';\n    }\n    std::cout << '\\n';\n\
    }"
  dependsOn:
  - library/convolution/min_plus_convolution.hpp
  - library/algorithm/monotone_minima.hpp
  isVerificationFile: true
  path: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
  requiredBy: []
  timestamp: '2023-09-06 20:32:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
layout: document
redirect_from:
- /verify/test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
- /verify/test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp.html
title: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
---
