---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: library/convolution/multi_variate_convolution_circular.hpp
    title: "Multi Variate Convolution Circular (\u591A\u5909\u6570\u5DE1\u56DE\u7573\
      \u307F\u8FBC\u307F)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
    title: test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: chirp z-transform ($g _ k = f(a r^k)$)
    links: []
  bundledCode: "#line 1 \"library/transform/chirp_z_transform.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <vector>\n\n#include <atcoder/convolution>\n\n/**\n *\
    \ @brief chirp z-transform ($g _ k = f(a r^k)$)\n*/\n\nnamespace suisen {\n  \
    \  namespace internal {\n        const auto default_convolution = [](const auto&\
    \ a, const auto& b) { return atcoder::convolution(a, b); };\n\n        template\
    \ <typename T>\n        std::vector<T> chirp_z_transform_naive(const std::vector<T>\
    \ &f, T a, T r, int m) {\n            const int n = f.size();\n            std::vector<T>\
    \ g(m);\n            T pow_r = 1;\n            for (int k = 0; k < m; ++k) {\n\
    \                T ark = a * pow_r, pow_ark = 1;\n                for (int i =\
    \ 0; i < n; ++i) {\n                    g[k] += f[i] * pow_ark;\n            \
    \        pow_ark *= ark;\n                }\n                pow_r *= r;\n   \
    \         }\n            return g;\n        }\n    } // namespace internal\n \
    \   /**\n     * @brief Calculates f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m) time\n\
    \     */\n    template <typename T, typename Convolution>\n    std::vector<T>\
    \ chirp_z_transform(std::vector<T> f, T a, T r, int m, Convolution&& convolution\
    \ = internal::default_convolution) {\n        const int n = f.size();\n      \
    \  std::vector<T> g(m);\n        if (n == 0 or m == 0) return g;\n        T pow_a\
    \ = 1;\n        for (int i = 0; i < n; ++i, pow_a *= a) f[i] *= pow_a;\n     \
    \   if (r == 0) {\n            for (int i = 0; i < n; ++i) g[0] += f[i];\n   \
    \         for (int k = 1; k < m; ++k) g[k] += f[0];\n            return g;\n \
    \       }\n        if (n < 60) return internal::chirp_z_transform_naive(f, a,\
    \ r, m);\n        const T r_inv = r.inv();\n\n        const int l = n + m - 1;\n\
    \n        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);\n        pow_r_tri[0]\
    \ = pow_r_tri_inv[0] = 1;\n\n        T pow_r = 1, pow_r_inv = 1;\n        for\
    \ (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= r_inv) {\n            pow_r_tri[i]\
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
    \  namespace internal {\n        const auto default_convolution = [](const auto&\
    \ a, const auto& b) { return atcoder::convolution(a, b); };\n\n        template\
    \ <typename T>\n        std::vector<T> chirp_z_transform_naive(const std::vector<T>\
    \ &f, T a, T r, int m) {\n            const int n = f.size();\n            std::vector<T>\
    \ g(m);\n            T pow_r = 1;\n            for (int k = 0; k < m; ++k) {\n\
    \                T ark = a * pow_r, pow_ark = 1;\n                for (int i =\
    \ 0; i < n; ++i) {\n                    g[k] += f[i] * pow_ark;\n            \
    \        pow_ark *= ark;\n                }\n                pow_r *= r;\n   \
    \         }\n            return g;\n        }\n    } // namespace internal\n \
    \   /**\n     * @brief Calculates f(ar^k) for k=0,...,m-1 in O(M(n+m-1)+n+m) time\n\
    \     */\n    template <typename T, typename Convolution>\n    std::vector<T>\
    \ chirp_z_transform(std::vector<T> f, T a, T r, int m, Convolution&& convolution\
    \ = internal::default_convolution) {\n        const int n = f.size();\n      \
    \  std::vector<T> g(m);\n        if (n == 0 or m == 0) return g;\n        T pow_a\
    \ = 1;\n        for (int i = 0; i < n; ++i, pow_a *= a) f[i] *= pow_a;\n     \
    \   if (r == 0) {\n            for (int i = 0; i < n; ++i) g[0] += f[i];\n   \
    \         for (int k = 1; k < m; ++k) g[k] += f[0];\n            return g;\n \
    \       }\n        if (n < 60) return internal::chirp_z_transform_naive(f, a,\
    \ r, m);\n        const T r_inv = r.inv();\n\n        const int l = n + m - 1;\n\
    \n        std::vector<T> pow_r_tri(l), pow_r_tri_inv(l);\n        pow_r_tri[0]\
    \ = pow_r_tri_inv[0] = 1;\n\n        T pow_r = 1, pow_r_inv = 1;\n        for\
    \ (int i = 1; i < l; ++i, pow_r *= r, pow_r_inv *= r_inv) {\n            pow_r_tri[i]\
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
  timestamp: '2022-11-16 20:35:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
documentation_of: library/transform/chirp_z_transform.hpp
layout: document
title: "chirp z-transform (\u8A55\u4FA1\u70B9\u304C\u7B49\u5DEE\u6570\u5217\u3092\u6210\
  \u3059\u5834\u5408\u306E Multipoint Evaluation)"
---
## chirp z-transform (評価点が等差数列を成す場合の Multipoint Evaluation)

## 問題

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {n - 1} f _ i x ^ i$ と評価点の初項 $a$ および公比 $r$ 与えられるので、$k = 0,\ldots, m - 1$ に対する $F _ k := f(a r ^ k)$ の値を求めよ。

---

## 概要

三角数 $t _ i = \dfrac{i(i - 1)}{2}$ に関して、以下が成り立つ。

$$
ki = t _ {i + k} - t _ i - t _ k.
$$

即ち、次が成り立つ。

$$\begin{aligned}
F _ k
&= r ^ {-t _ k} \sum _ {i = 0} ^ {n - 1} (f _ i a ^ i r ^ {-t _ i}) r ^ {t _ {i + k}}.
\end{aligned}$$

$x _ i := f _ {n - 1 - i} a ^ {n - i - 1} r ^ {-t _ {n - i - 1}}, y _ i := r ^ {t _ i}$ とすると

$$
F _ k = r ^ {-t _ k} \sum _ {i = 0} ^ {n - 1} x _ {n - 1 - i} y _ {k + i},
$$

であるから、$F _ k$ は $x$ と $y$ の畳み込みで計算できる。

## 参考

- https://github.com/noshi91/algorithm-encyclopedia/blob/gh-pages/_algorithms/chirp-z-transform.md