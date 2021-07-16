---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: library/math/factorial.hpp
    title: library/math/factorial.hpp
  - icon: ':warning:'
    path: library/math/fps.hpp
    title: library/math/fps.hpp
  - icon: ':warning:'
    path: library/math/inv_mods.hpp
    title: library/math/inv_mods.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/math/common_sequences.hpp\"\n\n\n\n#include <library/math/fps.hpp>\n\
    #include <library/math/factorial.hpp>\n\nnamespace suisen {\n/**\n * return:\n\
    \ *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k (unsigned)\n * constraints:\n\
    \ *   0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint> stirling_number1_reversed(int\
    \ n) {\n    factorial<mint> fac(n);\n    int l = 0;\n    while ((n >> l) != 0)\
    \ ++l;\n    FPS<mint> a {1};\n    int m = 0;\n    while (l --> 0) {\n        FPS<mint>\
    \ f(m + 1), g(m + 1);\n        mint powm = 1;\n        for (int i = 0; i <= m;\
    \ ++i, powm *= m) {\n            f[i] = powm * fac.fac_inv(i);\n            g[i]\
    \ = a[i] * fac.fac(m - i);\n        }\n        f *= g, f.pre_inplace(m);\n   \
    \     for (int i = 0; i <= m; ++i) f[i] *= fac.fac_inv(m - i);\n        a *= f,\
    \ m *= 2, a.pre_inplace(m);\n        if ((n >> l) & 1) {\n            a.push_back(0);\n\
    \            for (int i = m; i > 0; --i) a[i] += m * a[i - 1];\n            ++m;\n\
    \        }\n    }\n    return a;\n}\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1(int n) {\n    auto a(stirling_number1_reversed<mint>(n));\n\
    \    std::reverse(a.begin(), a.end());\n    return a;\n}\n/**\n * return:\n *\
    \   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling\
    \ number of the first kind (unsigned).\n * constraints:\n * - 0 <= n <= 10^18\n\
    \ * - 0 <= k <= 5000\n * - k < mod\n */\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1_reversed(const long long n, const int k) {\n    inv_mods<mint>\
    \ invs(k + 1);\n    std::vector<mint> a(k + 1, 0);\n    a[0] = 1;\n    int l =\
    \ 0;\n    while (n >> l) ++l;\n    mint m = 0;\n    while (l --> 0) {\n      \
    \  std::vector<mint> b(k + 1, 0);\n        for (int j = 0; j <= k; ++j) {\n  \
    \          mint tmp = 1;\n            for (int i = j; i <= k; ++i) {\n       \
    \         b[i] += a[j] * tmp;\n                tmp *= (m - i) * invs[i - j + 1]\
    \ * m;\n            }\n        }\n        for (int i = k + 1; i --> 0;) {\n  \
    \          mint sum = 0;\n            for (int j = 0; j <= i; ++j) sum += a[j]\
    \ * b[i - j];\n            a[i] = sum;\n        }\n        m *= 2;\n        if\
    \ ((n >> l) & 1) {\n            for (int i = k; i > 0; --i) a[i] += m * a[i -\
    \ 1];\n            ++m;\n        }\n    }\n    return a;\n}\n\n/**\n * return:\n\
    \ *   vector<mint> v s.t. v[i] = S2[n,i] for i=0,...,k\n * constraints:\n *  \
    \ 0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint> stirling_number2(int\
    \ n) {\n    factorial<mint> fac(n);\n    FPS<mint> a(n + 1), b(n + 1);\n    for\
    \ (int i = 0; i <= n; ++i) {\n        a[i] = mint(i).pow(n) * fac.fac_inv(i);\n\
    \        b[i] = i & 1 ? -fac.fac_inv(i) : fac.fac_inv(i);\n    }\n    a *= b,\
    \ a.pre_inplace(n);\n    return a;\n}\n\ntemplate <typename mint>\nstd::vector<mint>\
    \ bernoulli_number(int n) {\n    factorial<mint> fac(n);\n    FPS<mint> a(n +\
    \ 1);\n    for (int i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);\n    a.inv_inplace(n),\
    \ a.resize(n + 1);\n    for (int i = 2; i <= n; ++i) a[i] *= fac.fac(i);\n   \
    \ return a;\n}\n\ntemplate <typename mint>\nstd::vector<mint> partition_number(int\
    \ n) {\n    FPS<mint> inv(n + 1);\n    inv[0] = 1;\n    for (int i = 1, k = 1;\
    \ k <= n; k += 3 * i + 1, i++) {\n        if (i & 1) --inv[k];\n        else ++inv[k];\n\
    \    }\n    for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {\n        if\
    \ (i & 1) --inv[k];\n        else ++inv[k];\n    }\n    inv.inv_inplace(n), inv.resize(n\
    \ + 1);\n    return inv;\n}\n} // namespace suisen\n\n\n"
  code: "#ifndef SUISEN_COMMON_SEQ\n#define SUISEN_COMMON_SEQ\n\n#include <library/math/fps.hpp>\n\
    #include <library/math/factorial.hpp>\n\nnamespace suisen {\n/**\n * return:\n\
    \ *   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k (unsigned)\n * constraints:\n\
    \ *   0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint> stirling_number1_reversed(int\
    \ n) {\n    factorial<mint> fac(n);\n    int l = 0;\n    while ((n >> l) != 0)\
    \ ++l;\n    FPS<mint> a {1};\n    int m = 0;\n    while (l --> 0) {\n        FPS<mint>\
    \ f(m + 1), g(m + 1);\n        mint powm = 1;\n        for (int i = 0; i <= m;\
    \ ++i, powm *= m) {\n            f[i] = powm * fac.fac_inv(i);\n            g[i]\
    \ = a[i] * fac.fac(m - i);\n        }\n        f *= g, f.pre_inplace(m);\n   \
    \     for (int i = 0; i <= m; ++i) f[i] *= fac.fac_inv(m - i);\n        a *= f,\
    \ m *= 2, a.pre_inplace(m);\n        if ((n >> l) & 1) {\n            a.push_back(0);\n\
    \            for (int i = m; i > 0; --i) a[i] += m * a[i - 1];\n            ++m;\n\
    \        }\n    }\n    return a;\n}\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1(int n) {\n    auto a(stirling_number1_reversed<mint>(n));\n\
    \    std::reverse(a.begin(), a.end());\n    return a;\n}\n/**\n * return:\n *\
    \   vector<mint> v s.t. v[i] = S1[n,n-i] for i=0,...,k, where S1 is the stirling\
    \ number of the first kind (unsigned).\n * constraints:\n * - 0 <= n <= 10^18\n\
    \ * - 0 <= k <= 5000\n * - k < mod\n */\ntemplate <typename mint>\nstd::vector<mint>\
    \ stirling_number1_reversed(const long long n, const int k) {\n    inv_mods<mint>\
    \ invs(k + 1);\n    std::vector<mint> a(k + 1, 0);\n    a[0] = 1;\n    int l =\
    \ 0;\n    while (n >> l) ++l;\n    mint m = 0;\n    while (l --> 0) {\n      \
    \  std::vector<mint> b(k + 1, 0);\n        for (int j = 0; j <= k; ++j) {\n  \
    \          mint tmp = 1;\n            for (int i = j; i <= k; ++i) {\n       \
    \         b[i] += a[j] * tmp;\n                tmp *= (m - i) * invs[i - j + 1]\
    \ * m;\n            }\n        }\n        for (int i = k + 1; i --> 0;) {\n  \
    \          mint sum = 0;\n            for (int j = 0; j <= i; ++j) sum += a[j]\
    \ * b[i - j];\n            a[i] = sum;\n        }\n        m *= 2;\n        if\
    \ ((n >> l) & 1) {\n            for (int i = k; i > 0; --i) a[i] += m * a[i -\
    \ 1];\n            ++m;\n        }\n    }\n    return a;\n}\n\n/**\n * return:\n\
    \ *   vector<mint> v s.t. v[i] = S2[n,i] for i=0,...,k\n * constraints:\n *  \
    \ 0 <= n <= 10^6\n */\ntemplate <typename mint>\nstd::vector<mint> stirling_number2(int\
    \ n) {\n    factorial<mint> fac(n);\n    FPS<mint> a(n + 1), b(n + 1);\n    for\
    \ (int i = 0; i <= n; ++i) {\n        a[i] = mint(i).pow(n) * fac.fac_inv(i);\n\
    \        b[i] = i & 1 ? -fac.fac_inv(i) : fac.fac_inv(i);\n    }\n    a *= b,\
    \ a.pre_inplace(n);\n    return a;\n}\n\ntemplate <typename mint>\nstd::vector<mint>\
    \ bernoulli_number(int n) {\n    factorial<mint> fac(n);\n    FPS<mint> a(n +\
    \ 1);\n    for (int i = 0; i <= n; ++i) a[i] = fac.fac_inv(i + 1);\n    a.inv_inplace(n),\
    \ a.resize(n + 1);\n    for (int i = 2; i <= n; ++i) a[i] *= fac.fac(i);\n   \
    \ return a;\n}\n\ntemplate <typename mint>\nstd::vector<mint> partition_number(int\
    \ n) {\n    FPS<mint> inv(n + 1);\n    inv[0] = 1;\n    for (int i = 1, k = 1;\
    \ k <= n; k += 3 * i + 1, i++) {\n        if (i & 1) --inv[k];\n        else ++inv[k];\n\
    \    }\n    for (int i = 1, k = 2; k <= n; k += 3 * i + 2, i++) {\n        if\
    \ (i & 1) --inv[k];\n        else ++inv[k];\n    }\n    inv.inv_inplace(n), inv.resize(n\
    \ + 1);\n    return inv;\n}\n} // namespace suisen\n\n#endif // SUISEN_COMMON_SEQ\n"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  - library/math/factorial.hpp
  isVerificationFile: false
  path: library/math/common_sequences.hpp
  requiredBy: []
  timestamp: '2021-07-17 02:33:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/common_sequences.hpp
layout: document
title: "\u6709\u540D\u306A\u6570\u5217\u305F\u3061"
---

### stirling_number1_reversed

$A_i:=\mathrm{S1}\begin{vmatrix}N\\ N-i\end{vmatrix}$ を $O(N\log N)$ で計算します．
