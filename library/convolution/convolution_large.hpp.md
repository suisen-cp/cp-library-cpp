---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/convolution/convolution_naive.hpp
    title: Naive Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/convolution_large/convolution_large.test.cpp
    title: test/src/convolution/convolution_large/convolution_large.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/convolution/convolution_large.hpp\"\n\n\n\n#include\
    \ <atcoder/convolution>\n\n#line 1 \"library/convolution/convolution_naive.hpp\"\
    \n\n\n\n#include <vector>\n\nnamespace suisen::internal {\n    template <typename\
    \ T>\n    std::vector<T> convolution_naive(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\n        const int n = a.size(), m = b.size();\n        std::vector<T>\
    \ c(n + m - 1);\n        if (n < m) {\n            for (int j = 0; j < m; j++)\
    \ for (int i = 0; i < n; i++) c[i + j] += a[i] * b[j];\n        } else {\n   \
    \         for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] +=\
    \ a[i] * b[j];\n        }\n        return c;\n    }\n} // namespace suisen\n\n\
    \n\n#line 7 \"library/convolution/convolution_large.hpp\"\n\nnamespace suisen\
    \ {\n    template <typename mint, atcoder::internal::is_static_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> convolution_large(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        static constexpr int max_size = (mint::mod()\
    \ - 1) & -(mint::mod() - 1);\n        static constexpr int half_size = max_size\
    \ >> 1;\n        static constexpr int inv_max_size = atcoder::internal::inv_gcd(max_size,\
    \ mint::mod()).second;\n\n        const int n = int(a.size()), m = int(b.size());\n\
    \        if (n + m - 1 <= max_size) return atcoder::convolution(a, b);\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 60) return\
    \ internal::convolution_naive(a, b);\n\n        const int dn = (n + half_size\
    \ - 1) / half_size;\n        const int dm = (m + half_size - 1) / half_size;\n\
    \n        std::vector<std::vector<mint>> as(dn), bs(dm);\n        for (int i =\
    \ 0; i < dn; ++i) {\n            const int offset = half_size * i;\n         \
    \   as[i] = std::vector<mint>(a.begin() + offset, a.begin() + std::min(n, offset\
    \ + half_size));\n            as[i].resize(max_size);\n            atcoder::internal::butterfly(as[i]);\n\
    \        }\n        for (int j = 0; j < dm; ++j) {\n            const int offset\
    \ = half_size * j;\n            bs[j] = std::vector<mint>(b.begin() + offset,\
    \ b.begin() + std::min(m, offset + half_size));\n            bs[j].resize(max_size);\n\
    \            atcoder::internal::butterfly(bs[j]);\n        }\n        std::vector<std::vector<mint>>\
    \ cs(dn + dm - 1, std::vector<mint>(max_size));\n        for (int i = 0; i < dn;\
    \ ++i) for (int j = 0; j < dm; ++j) {\n            for (int k = 0; k < max_size;\
    \ ++k) cs[i + j][k] += as[i][k] * bs[j][k];\n        }\n        std::vector<mint>\
    \ res(n + m - 1);\n        for (int i = 0; i < dn + dm - 1; ++i) {\n         \
    \   atcoder::internal::butterfly_inv(cs[i]);\n            const int offset = half_size\
    \ * i;\n            const int jmax = std::min(n + m - 1 - offset, max_size);\n\
    \            for (int j = 0; j < jmax; ++j) {\n                res[offset + j]\
    \ += cs[i][j] * mint::raw(inv_max_size);\n            }\n        }\n        return\
    \ res;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CONVOLTION_LARGE\n#define SUISEN_CONVOLTION_LARGE\n\n#include\
    \ <atcoder/convolution>\n\n#include \"library/convolution/convolution_naive.hpp\"\
    \n\nnamespace suisen {\n    template <typename mint, atcoder::internal::is_static_modint_t<mint>*\
    \ = nullptr>\n    std::vector<mint> convolution_large(const std::vector<mint>&\
    \ a, const std::vector<mint>& b) {\n        static constexpr int max_size = (mint::mod()\
    \ - 1) & -(mint::mod() - 1);\n        static constexpr int half_size = max_size\
    \ >> 1;\n        static constexpr int inv_max_size = atcoder::internal::inv_gcd(max_size,\
    \ mint::mod()).second;\n\n        const int n = int(a.size()), m = int(b.size());\n\
    \        if (n + m - 1 <= max_size) return atcoder::convolution(a, b);\n     \
    \   if (n == 0 or m == 0) return {};\n        if (std::min(n, m) <= 60) return\
    \ internal::convolution_naive(a, b);\n\n        const int dn = (n + half_size\
    \ - 1) / half_size;\n        const int dm = (m + half_size - 1) / half_size;\n\
    \n        std::vector<std::vector<mint>> as(dn), bs(dm);\n        for (int i =\
    \ 0; i < dn; ++i) {\n            const int offset = half_size * i;\n         \
    \   as[i] = std::vector<mint>(a.begin() + offset, a.begin() + std::min(n, offset\
    \ + half_size));\n            as[i].resize(max_size);\n            atcoder::internal::butterfly(as[i]);\n\
    \        }\n        for (int j = 0; j < dm; ++j) {\n            const int offset\
    \ = half_size * j;\n            bs[j] = std::vector<mint>(b.begin() + offset,\
    \ b.begin() + std::min(m, offset + half_size));\n            bs[j].resize(max_size);\n\
    \            atcoder::internal::butterfly(bs[j]);\n        }\n        std::vector<std::vector<mint>>\
    \ cs(dn + dm - 1, std::vector<mint>(max_size));\n        for (int i = 0; i < dn;\
    \ ++i) for (int j = 0; j < dm; ++j) {\n            for (int k = 0; k < max_size;\
    \ ++k) cs[i + j][k] += as[i][k] * bs[j][k];\n        }\n        std::vector<mint>\
    \ res(n + m - 1);\n        for (int i = 0; i < dn + dm - 1; ++i) {\n         \
    \   atcoder::internal::butterfly_inv(cs[i]);\n            const int offset = half_size\
    \ * i;\n            const int jmax = std::min(n + m - 1 - offset, max_size);\n\
    \            for (int j = 0; j < jmax; ++j) {\n                res[offset + j]\
    \ += cs[i][j] * mint::raw(inv_max_size);\n            }\n        }\n        return\
    \ res;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_CONVOLTION_LARGE\n"
  dependsOn:
  - library/convolution/convolution_naive.hpp
  isVerificationFile: false
  path: library/convolution/convolution_large.hpp
  requiredBy: []
  timestamp: '2022-05-05 17:36:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/convolution_large/convolution_large.test.cpp
documentation_of: library/convolution/convolution_large.hpp
layout: document
title: Convolution (Large)
---
## Convolution (Large)

$\mathrm{mod}\ p$ における $1$ の $2 ^ k$ 乗根が存在しない場合に、列を分割して畳み込む。
