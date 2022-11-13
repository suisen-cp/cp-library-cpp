---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: Multi Variate Convolution Circular
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':x:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: chirp z-transform ($g _ k = f(a r^k)$)
    links: []
  bundledCode: "#line 1 \"library/transform/chirp_z_transform.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include <atcoder/convolution>\n\n/**\n *\
    \ @brief chirp z-transform ($g _ k = f(a r^k)$)\n*/\n\nnamespace suisen {\n  \
    \  namespace internal {\n        const auto default_convolution = [](const auto\
    \ &a, const auto &b) { return atcoder::convolution(a, b); };\n    } // namespace\
    \ internal\n    /**\n     * @brief Calculates f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m)\
    \ time\n     */\n    template <typename T, typename Convolution>\n    std::vector<T>\
    \ chirp_z_transform(std::vector<T> f, T a, T r, int m, Convolution &&convolution\
    \ = internal::default_convolution) {\n        const int n = f.size();\n      \
    \  std::vector<T> g(m);\n        if (n == 0 or m == 0) return g;\n        if (r\
    \ == 0) {\n            for (int i = 0; i < n; ++i) g[0] += f[i];\n           \
    \ for (int k = 1; k < m; ++k) g[k] += f[0];\n            return g;\n        }\n\
    \        T pow_a = 1;\n        for (int i = 0; i < n; ++i, pow_a *= a) f[i] *=\
    \ pow_a;\n\n        const T w_inv = r.inv();\n\n        const int l = n + m -\
    \ 1;\n\n        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);\n        pow_r_tri[0]\
    \ = pow_r_tri_inv[0] = 1;\n\n        T pow_r = 1, pow_r_inv = 1;\n        for\
    \ (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= w_inv) {\n            pow_r_tri[i]\
    \ = pow_r_tri[i - 1] * pow_r;\n            pow_r_tri_inv[i] = pow_r_tri_inv[i\
    \ - 1] * pow_r_inv;\n        }\n\n        std::vector<T> p(n), q(l);\n       \
    \ for (int i = 0; i < n; ++i) p[i] = f[i] * pow_r_tri_inv[i];\n        for (int\
    \ i = 0; i < l; ++i) q[i] = pow_r_tri[i];\n        std::reverse(p.begin(), p.end());\n\
    \        std::vector<T> pq = convolution(p, q);\n        for (int k = 0; k < m;\
    \ ++k) {\n            g[k] = pow_r_tri_inv[k] * pq[n - 1 + k];\n        }\n\n\
    \        return g;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_CHIRP_Z_TRANSFORM\n#define SUISEN_CHIRP_Z_TRANSFORM\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include <atcoder/convolution>\n\n/**\n *\
    \ @brief chirp z-transform ($g _ k = f(a r^k)$)\n*/\n\nnamespace suisen {\n  \
    \  namespace internal {\n        const auto default_convolution = [](const auto\
    \ &a, const auto &b) { return atcoder::convolution(a, b); };\n    } // namespace\
    \ internal\n    /**\n     * @brief Calculates f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m)\
    \ time\n     */\n    template <typename T, typename Convolution>\n    std::vector<T>\
    \ chirp_z_transform(std::vector<T> f, T a, T r, int m, Convolution &&convolution\
    \ = internal::default_convolution) {\n        const int n = f.size();\n      \
    \  std::vector<T> g(m);\n        if (n == 0 or m == 0) return g;\n        if (r\
    \ == 0) {\n            for (int i = 0; i < n; ++i) g[0] += f[i];\n           \
    \ for (int k = 1; k < m; ++k) g[k] += f[0];\n            return g;\n        }\n\
    \        T pow_a = 1;\n        for (int i = 0; i < n; ++i, pow_a *= a) f[i] *=\
    \ pow_a;\n\n        const T w_inv = r.inv();\n\n        const int l = n + m -\
    \ 1;\n\n        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);\n        pow_r_tri[0]\
    \ = pow_r_tri_inv[0] = 1;\n\n        T pow_r = 1, pow_r_inv = 1;\n        for\
    \ (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= w_inv) {\n            pow_r_tri[i]\
    \ = pow_r_tri[i - 1] * pow_r;\n            pow_r_tri_inv[i] = pow_r_tri_inv[i\
    \ - 1] * pow_r_inv;\n        }\n\n        std::vector<T> p(n), q(l);\n       \
    \ for (int i = 0; i < n; ++i) p[i] = f[i] * pow_r_tri_inv[i];\n        for (int\
    \ i = 0; i < l; ++i) q[i] = pow_r_tri[i];\n        std::reverse(p.begin(), p.end());\n\
    \        std::vector<T> pq = convolution(p, q);\n        for (int k = 0; k < m;\
    \ ++k) {\n            g[k] = pow_r_tri_inv[k] * pq[n - 1 + k];\n        }\n\n\
    \        return g;\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_CHIRP_Z_TRANSFORM\n"
  dependsOn: []
  isVerificationFile: false
  path: library/transform/chirp_z_transform.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  timestamp: '2022-11-13 03:53:58+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
documentation_of: library/transform/chirp_z_transform.hpp
layout: document
title: Chirp Z Transform
---
## Chirp Z Transform
