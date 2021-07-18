---
data:
  _extendedDependsOn:
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
  bundledCode: "#line 1 \"library/math/interpolation.hpp\"\n\n\n\n#include <vector>\n\
    #include <library/math/fps.hpp>\n\nnamespace suisen {\ntemplate <typename T>\n\
    T lagrange_interpolation(const std::vector<T> &ys, const T t) {\n    const int\
    \ n = ys.size();\n    T fac = 1;\n    for (int i = 1; i < n; ++i) fac *= i;\n\
    \    std::vector<T> fci(n), suf(n);\n    fci[n - 1] = T(1) / fac;\n    suf[n -\
    \ 1] = 1;\n    for (int i = n - 1; i > 0; --i) {\n        fci[i - 1] = fci[i]\
    \ * i;\n        suf[i - 1] = suf[i] * (t - i);\n    }\n    T prf = 1, res = 0;\n\
    \    for (int i = 0; i < n; ++i) {\n        T val = ys[i] * prf * suf[i] * fci[i]\
    \ * fci[n - i - 1];\n        if ((n - 1 - i) & 1) {\n            res -= val;\n\
    \        } else {\n            res += val;\n        }\n        prf *= t - i;\n\
    \    }\n    return res;\n}\n\ntemplate <typename mint>\nFPS<mint> polynomial_interpolation(const\
    \ std::vector<mint> &xs, const std::vector<mint> &ys) {\n    assert(xs.size()\
    \ == ys.size());\n    int n = xs.size();\n    int k = 1;\n    while (k < n) k\
    \ <<= 1;\n    std::vector<FPS<mint>> seg(k << 1), g(k << 1);\n    for (int i =\
    \ 0; i < n; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};\n    for (int i = n; i <\
    \ k; ++i) seg[k + i] = FPS<mint> {1};\n    for (int i = k - 1; i > 0; --i) {\n\
    \        seg[i] = seg[i * 2] * seg[i * 2 + 1];\n    }\n    g[1] = std::move(seg[1].diff_inplace());\n\
    \    for (int i = 1; i < k; ++i) {\n        int l = 2 * i, r = l + 1;\n      \
    \  g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];\n    }\n    for (int i = 0; i <\
    \ n; ++i) g[k + i] = FPS<mint> {ys[i] / g[k + i][0]};\n    for (int i = n; i <\
    \ k; ++i) g[k + i] = FPS<mint> {0};\n    for (int i = k - 1; i > 0; --i) {\n \
    \       int l = 2 * i, r = l + 1;\n        g[i] = g[l] * seg[r] + g[r] * seg[l];\n\
    \    }\n    return g[1];\n}\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_INTERPOLATION\n#define SUISEN_INTERPOLATION\n\n#include <vector>\n\
    #include <library/math/fps.hpp>\n\nnamespace suisen {\ntemplate <typename T>\n\
    T lagrange_interpolation(const std::vector<T> &ys, const T t) {\n    const int\
    \ n = ys.size();\n    T fac = 1;\n    for (int i = 1; i < n; ++i) fac *= i;\n\
    \    std::vector<T> fci(n), suf(n);\n    fci[n - 1] = T(1) / fac;\n    suf[n -\
    \ 1] = 1;\n    for (int i = n - 1; i > 0; --i) {\n        fci[i - 1] = fci[i]\
    \ * i;\n        suf[i - 1] = suf[i] * (t - i);\n    }\n    T prf = 1, res = 0;\n\
    \    for (int i = 0; i < n; ++i) {\n        T val = ys[i] * prf * suf[i] * fci[i]\
    \ * fci[n - i - 1];\n        if ((n - 1 - i) & 1) {\n            res -= val;\n\
    \        } else {\n            res += val;\n        }\n        prf *= t - i;\n\
    \    }\n    return res;\n}\n\ntemplate <typename mint>\nFPS<mint> polynomial_interpolation(const\
    \ std::vector<mint> &xs, const std::vector<mint> &ys) {\n    assert(xs.size()\
    \ == ys.size());\n    int n = xs.size();\n    int k = 1;\n    while (k < n) k\
    \ <<= 1;\n    std::vector<FPS<mint>> seg(k << 1), g(k << 1);\n    for (int i =\
    \ 0; i < n; ++i) seg[k + i] = FPS<mint> {-xs[i], 1};\n    for (int i = n; i <\
    \ k; ++i) seg[k + i] = FPS<mint> {1};\n    for (int i = k - 1; i > 0; --i) {\n\
    \        seg[i] = seg[i * 2] * seg[i * 2 + 1];\n    }\n    g[1] = std::move(seg[1].diff_inplace());\n\
    \    for (int i = 1; i < k; ++i) {\n        int l = 2 * i, r = l + 1;\n      \
    \  g[l] = g[i] % seg[l], g[r] = g[i] % seg[r];\n    }\n    for (int i = 0; i <\
    \ n; ++i) g[k + i] = FPS<mint> {ys[i] / g[k + i][0]};\n    for (int i = n; i <\
    \ k; ++i) g[k + i] = FPS<mint> {0};\n    for (int i = k - 1; i > 0; --i) {\n \
    \       int l = 2 * i, r = l + 1;\n        g[i] = g[l] * seg[r] + g[r] * seg[l];\n\
    \    }\n    return g[1];\n}\n} // namespace suisen\n\n#endif // SUISEN_INTERPOLATION\n\
    \n"
  dependsOn:
  - library/math/fps.hpp
  - library/math/inv_mods.hpp
  isVerificationFile: false
  path: library/math/interpolation.hpp
  requiredBy: []
  timestamp: '2021-07-18 16:47:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: library/math/interpolation.hpp
layout: document
redirect_from:
- /library/library/math/interpolation.hpp
- /library/library/math/interpolation.hpp.html
title: library/math/interpolation.hpp
---
