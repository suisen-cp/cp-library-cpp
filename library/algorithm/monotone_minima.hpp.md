---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/min_plus_convolution.hpp
    title: Min Plus Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_arbitrary.test.cpp
    title: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
    title: test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/algorithm/monotone_minima.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace suisen {\n   \
    \ /**\n     * @param n # rows\n     * @param m # cols\n     * @param compare (row,\
    \ col1, col2 (> col1)) -> bool (= A(row, col1) <= A(row, col2))\n     * @return\
    \ std::vector<int> res s.t. res[i] = argmin_j f(i,j)\n     */\n    template <typename\
    \ Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, size_t, size_t,\
    \ size_t>, std::nullptr_t> = nullptr>\n    std::vector<int> monotone_minima(size_t\
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
    } // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_MONOTONE_MINIMA\n#define SUISEN_MONOTONE_MINIMA\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace suisen {\n   \
    \ /**\n     * @param n # rows\n     * @param m # cols\n     * @param compare (row,\
    \ col1, col2 (> col1)) -> bool (= A(row, col1) <= A(row, col2))\n     * @return\
    \ std::vector<int> res s.t. res[i] = argmin_j f(i,j)\n     */\n    template <typename\
    \ Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, size_t, size_t,\
    \ size_t>, std::nullptr_t> = nullptr>\n    std::vector<int> monotone_minima(size_t\
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
    } // namespace suisen\n\n\n#endif // SUISEN_MONOTONE_MINIMA\n"
  dependsOn: []
  isVerificationFile: false
  path: library/algorithm/monotone_minima.hpp
  requiredBy:
  - library/convolution/min_plus_convolution.hpp
  timestamp: '2023-09-06 20:32:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/min_plus_convolution/min_plus_convolution_convex_convex.test.cpp
  - test/src/convolution/min_plus_convolution/min_plus_convolution_convex_arbitrary.test.cpp
documentation_of: library/algorithm/monotone_minima.hpp
layout: document
title: Monotone Minima
---
## Monotone Minima
