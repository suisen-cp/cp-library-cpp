---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
    title: test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/src/polynomial/compose/dummy.test.cpp
    title: test/src/polynomial/compose/dummy.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"library/polynomial/compose.hpp\"\n\n\n\n#include <cmath>\n\
    #include <vector>\n#include <atcoder/convolution>\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    std::vector<mint> compose(const std::vector<mint>& f, std::vector<mint>\
    \ g, const int n) {\n        std::vector<mint> res(n);\n        if (n == 0) return\
    \ res;\n        if (f.empty()) return res;\n\n        if (std::find_if(g.begin(),\
    \ g.end(), [](mint x) { return x != 0; }) == g.end()) return res[0] = f[0], res;\n\
    \n        // taylor shift f(x + [x^0]g)\n        const std::vector<mint> fa =\
    \ [&]{\n            const mint a = std::exchange(g[0], 0);\n            std::vector<mint>\
    \ fac(n), fac_inv(n);\n            fac[0] = 1;\n            for (int i = 1; i\
    \ <= n - 1; ++i) fac[i] = fac[i - 1] * i;\n            fac_inv[n - 1] = fac[n\
    \ - 1].inv();\n            for (int i = n - 1; i >= 1; --i) fac_inv[i - 1] = fac_inv[i]\
    \ * i;\n\n            std::vector<mint> ec(n), fa(n);\n            mint p = 1;\n\
    \            for (int i = 0; i < n; ++i, p *= a) {\n                ec[i] = p\
    \ * fac_inv[i];\n                fa[n - 1 - i] = (i < int(f.size()) ? f[i] : 0)\
    \ * fac[i];\n            }\n            fa = atcoder::convolution(fa, ec), fa.resize(n);\n\
    \            std::reverse(fa.begin(), fa.end());\n            for (int i = 0;\
    \ i < n; ++i) {\n                fa[i] *= fac_inv[i];\n            }\n       \
    \     return fa;\n        }();\n\n        const int sqn = ::sqrt(f.size()) + 1;\n\
    \n        const int z = [n]{\n            int z = 1;\n            while (z < 2\
    \ * n - 1) z <<= 1;\n            return z;\n        }();\n        const mint iz\
    \ = mint(z).inv();\n\n        g.erase(g.begin());\n        g.resize(z);\n    \
    \    atcoder::internal::butterfly(g);\n\n        auto mult_g = [&](std::vector<mint>\
    \ a) {\n            a.resize(z);\n            atcoder::internal::butterfly(a);\n\
    \            for (int j = 0; j < z; ++j) a[j] *= g[j] * iz;\n            atcoder::internal::butterfly_inv(a);\n\
    \            a.resize(n);\n            return a;\n        };\n\n        std::vector<std::vector<mint>>\
    \ pow_g(sqn, std::vector<mint>(n));\n        pow_g[0][0] = 1;\n        for (int\
    \ i = 1; i < sqn; ++i) {\n            pow_g[i] = mult_g(pow_g[i - 1]);\n     \
    \   }\n\n        std::vector<mint> gl = mult_g(pow_g[sqn - 1]);\n        gl.resize(z);\n\
    \        atcoder::internal::butterfly(gl);\n\n        std::vector<mint> pow_gl(z);\n\
    \        pow_gl[0] = 1;\n\n        for (int i = 0; i < sqn; ++i) {\n         \
    \   const int off_i = i * sqn;\n            const int siz_i = n - off_i;\n   \
    \         if (siz_i < 0) break;\n            std::vector<mint> fg(siz_i);\n  \
    \          for (int j = 0; j < sqn; ++j) {\n                const int ij = i *\
    \ sqn + j;\n                if (ij >= int(fa.size())) break;\n\n             \
    \   const mint c = fa[ij];\n                const std::vector<mint>& gj = pow_g[j];\n\
    \                for (int k = 0; k < siz_i - j; ++k) {\n                    fg[j\
    \ + k] += c * gj[k];\n                }\n            }\n            fg.resize(z);\n\
    \            atcoder::internal::butterfly(pow_gl);\n            atcoder::internal::butterfly(fg);\n\
    \            for (int k = 0; k < z; ++k) {\n                fg[k] *= pow_gl[k]\
    \ * iz;\n                pow_gl[k] *= gl[k] * iz;\n            }\n           \
    \ atcoder::internal::butterfly_inv(pow_gl);\n            atcoder::internal::butterfly_inv(fg);\n\
    \            for (int k = 0; k < siz_i; ++k) {\n                res[off_i + k]\
    \ += fg[k];\n            }\n            std::fill(pow_gl.begin() + n, pow_gl.end(),\
    \ 0);\n        }\n        return res;\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_POLY_COMPOSE\n#define SUISEN_POLY_COMPOSE\n\n#include <cmath>\n\
    #include <vector>\n#include <atcoder/convolution>\n\nnamespace suisen {\n    template\
    \ <typename mint>\n    std::vector<mint> compose(const std::vector<mint>& f, std::vector<mint>\
    \ g, const int n) {\n        std::vector<mint> res(n);\n        if (n == 0) return\
    \ res;\n        if (f.empty()) return res;\n\n        if (std::find_if(g.begin(),\
    \ g.end(), [](mint x) { return x != 0; }) == g.end()) return res[0] = f[0], res;\n\
    \n        // taylor shift f(x + [x^0]g)\n        const std::vector<mint> fa =\
    \ [&]{\n            const mint a = std::exchange(g[0], 0);\n            std::vector<mint>\
    \ fac(n), fac_inv(n);\n            fac[0] = 1;\n            for (int i = 1; i\
    \ <= n - 1; ++i) fac[i] = fac[i - 1] * i;\n            fac_inv[n - 1] = fac[n\
    \ - 1].inv();\n            for (int i = n - 1; i >= 1; --i) fac_inv[i - 1] = fac_inv[i]\
    \ * i;\n\n            std::vector<mint> ec(n), fa(n);\n            mint p = 1;\n\
    \            for (int i = 0; i < n; ++i, p *= a) {\n                ec[i] = p\
    \ * fac_inv[i];\n                fa[n - 1 - i] = (i < int(f.size()) ? f[i] : 0)\
    \ * fac[i];\n            }\n            fa = atcoder::convolution(fa, ec), fa.resize(n);\n\
    \            std::reverse(fa.begin(), fa.end());\n            for (int i = 0;\
    \ i < n; ++i) {\n                fa[i] *= fac_inv[i];\n            }\n       \
    \     return fa;\n        }();\n\n        const int sqn = ::sqrt(f.size()) + 1;\n\
    \n        const int z = [n]{\n            int z = 1;\n            while (z < 2\
    \ * n - 1) z <<= 1;\n            return z;\n        }();\n        const mint iz\
    \ = mint(z).inv();\n\n        g.erase(g.begin());\n        g.resize(z);\n    \
    \    atcoder::internal::butterfly(g);\n\n        auto mult_g = [&](std::vector<mint>\
    \ a) {\n            a.resize(z);\n            atcoder::internal::butterfly(a);\n\
    \            for (int j = 0; j < z; ++j) a[j] *= g[j] * iz;\n            atcoder::internal::butterfly_inv(a);\n\
    \            a.resize(n);\n            return a;\n        };\n\n        std::vector<std::vector<mint>>\
    \ pow_g(sqn, std::vector<mint>(n));\n        pow_g[0][0] = 1;\n        for (int\
    \ i = 1; i < sqn; ++i) {\n            pow_g[i] = mult_g(pow_g[i - 1]);\n     \
    \   }\n\n        std::vector<mint> gl = mult_g(pow_g[sqn - 1]);\n        gl.resize(z);\n\
    \        atcoder::internal::butterfly(gl);\n\n        std::vector<mint> pow_gl(z);\n\
    \        pow_gl[0] = 1;\n\n        for (int i = 0; i < sqn; ++i) {\n         \
    \   const int off_i = i * sqn;\n            const int siz_i = n - off_i;\n   \
    \         if (siz_i < 0) break;\n            std::vector<mint> fg(siz_i);\n  \
    \          for (int j = 0; j < sqn; ++j) {\n                const int ij = i *\
    \ sqn + j;\n                if (ij >= int(fa.size())) break;\n\n             \
    \   const mint c = fa[ij];\n                const std::vector<mint>& gj = pow_g[j];\n\
    \                for (int k = 0; k < siz_i - j; ++k) {\n                    fg[j\
    \ + k] += c * gj[k];\n                }\n            }\n            fg.resize(z);\n\
    \            atcoder::internal::butterfly(pow_gl);\n            atcoder::internal::butterfly(fg);\n\
    \            for (int k = 0; k < z; ++k) {\n                fg[k] *= pow_gl[k]\
    \ * iz;\n                pow_gl[k] *= gl[k] * iz;\n            }\n           \
    \ atcoder::internal::butterfly_inv(pow_gl);\n            atcoder::internal::butterfly_inv(fg);\n\
    \            for (int k = 0; k < siz_i; ++k) {\n                res[off_i + k]\
    \ += fg[k];\n            }\n            std::fill(pow_gl.begin() + n, pow_gl.end(),\
    \ 0);\n        }\n        return res;\n    }\n} // namespace suisen\n\n\n#endif\
    \ // SUISEN_POLY_COMPOSE\n"
  dependsOn: []
  isVerificationFile: false
  path: library/polynomial/compose.hpp
  requiredBy: []
  timestamp: '2023-05-27 18:14:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/polynomial/compose/composition_of_formal_power_series.test.cpp
  - test/src/polynomial/compose/dummy.test.cpp
documentation_of: library/polynomial/compose.hpp
layout: document
title: "\u5408\u6210"
---
## 合成

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ i,\ g(x) = \sum _ {i = 0} ^ {M - 1} b _ i x ^ i$ に対して合成 $(f\circ g)(x) \pmod{x ^ K}$ を $O(NK + \sqrt{N}K\log K + M)$ 時間で計算するライブラリ。

## アルゴリズム

$a:= \lbrack x ^ 0\rbrack g$ とする。

まず、$g\leftarrow g \bmod x ^ K$ とする。この部分の計算量は $O(M + K)$ である。

$\displaystyle f\circ g = \sum _ {i = 0} ^ {N - 1} a _ i g ^ i$ を計算したい。$B \coloneqq \lceil \sqrt{N} \rceil$ とすれば $\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} (g ^ B) ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} g ^ j$ と表せる。ただし $i \geq N$ に対して $a _ i = 0$ とする。

$g ^ 0, g ^ 1, \ldots, g ^ {B - 1}$ および $G\coloneqq g ^ B$ に対して $G ^ 0, G ^ 1, \ldots, G ^ {B - 1}$ を全て ($\mathrm{mod}\ x ^ K$ で) 前計算する。この前計算は $O(\sqrt N K \log K)$ 時間で可能である。

この前計算の結果を用いれば、各 $i=0,1,\ldots,B-1$ に対して、$\displaystyle \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j \bmod x ^ K$ を $O(\sqrt{N} K)$ 時間で計算できる。従って、$\displaystyle \left(G ^ i \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j\right) \bmod x ^ K$ の計算は $O(\sqrt{N} K + K \log K)$ 時間で可能である。

以上をまとめると、全体の計算量は $O(NK + \sqrt{N}K\log K + M)$ 時間となる。

## 定数倍高速化 (1)

$g ^ i,G ^ i$ の前計算において、$\mathbf{FFT}(g)$ や $\mathbf{FFT}(G)$ を $1$ 回しか計算しないことで定数倍高速化を図ることができる。

## 定数倍高速化 (2)

$\lbrack x ^ 0 \rbrack g = 0$ が成り立つ場合、$\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} x ^ {Bi} ((g / x) ^ B) ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} x ^ j (g / x) ^ j$ において $\displaystyle \sum _ {j = 0} ^ {B - 1} a _ {iB + j} x ^ j (g / x) ^ j$ は $\mathrm{mod}\ x ^ {N - iB}$ で求めれば十分である。従って、$NK$ に付く係数をおよそ $1/2$ 倍に削減できる。

$\lbrack x ^ 0 \rbrack g \neq 0$ の場合は $f$ を taylor shift して $f(x) \leftarrow f(x + \lbrack x ^ 0 \rbrack g)$ とおき直すことで $\lbrack x ^ 0 \rbrack g = 0$ の場合に帰着できる。帰着に掛かる計算量は $O(N\log N)$ であり、サイズ $N$ の畳み込み $1$ 回が支配的であるから全体の実行時間と比較して十分短い時間実行可能である。
