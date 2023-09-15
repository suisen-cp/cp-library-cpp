---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: library/number/ext_gcd.hpp
    title: Ext Gcd
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
    document_title: Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime
      each other.
    links: []
  bundledCode: "#line 1 \"library/number/garner.hpp\"\n\n\n\n#include <vector>\n#line\
    \ 1 \"library/number/ext_gcd.hpp\"\n\n\n\n#include <cassert>\n#include <cmath>\n\
    #include <limits>\n#include <optional>\n#include <tuple>\n#include <utility>\n\
    \nnamespace suisen {\n    constexpr long long safe_mod(long long x, long long\
    \ m) {\n        x %= m;\n        return x < 0 ? x + m : x;\n    }\n\n    // returns\
    \ {x,y,g} s.t. ax+by=g=gcd(a,b)>=0. \n    std::tuple<long long, long long, long\
    \ long> ext_gcd(long long a, long long b) {\n        long long x = 1, y = 0;\n\
    \        long long z = 0, w = 1;\n        while (b) {\n            long long p\
    \ = a / b, q = a % b;\n            x -= y * p, std::swap(x, y);\n            z\
    \ -= w * p, std::swap(z, w);\n            a = b, b = q;\n        }\n        if\
    \ (a < 0) {\n            x = -x, z = -z, a = -a;\n        }\n        return {\
    \ x, z, a };\n    }\n\n    // returns {x,g} s.t. a*x=g (mod m)\n    std::pair<long\
    \ long, long long> gcd_inv(long long a, long long m) {\n        auto [x, y, g]\
    \ = ext_gcd(a, m);\n        return { safe_mod(x, m), g };\n    }\n\n    // returns\
    \ x s.t. a*x=1 (mod m) if exists, otherwise throws runtime error.\n    long long\
    \ inv_mod(long long a, long long mod) {\n        auto [inv, y, g] = ext_gcd(a,\
    \ mod);\n        assert(g == 1);\n        return safe_mod(inv, mod);\n    }\n\
    } // namespace suisen\n\n\n#line 6 \"library/number/garner.hpp\"\n\nnamespace\
    \ suisen {\n    /**\n     * @brief Calculates x mod m s.t. x = x_i (mod m_i).\
    \ m_i should be coprime each other.\n     * @param eq vector of { x_i, m_i }\n\
    \     * @return x mod m s.t. x = x_i (mod m_i)\n     */\n    int garner(std::vector<std::pair<int,\
    \ int>> eq, int m) {\n        const int n = eq.size();\n        std::vector<long\
    \ long> a(n);\n\n        auto calc_prefix = [&](int i, long long mod) {\n    \
    \        long long res = 0;\n            long long prd = 1;\n            for (int\
    \ j = 0; j < i; ++j) {\n                (res += a[j] * prd) %= mod;\n        \
    \        (prd *= eq[j].second) %= mod;\n            }\n            return res;\n\
    \        };\n    \n        for (int i = 0; i < n; ++i) {\n            auto [xi,\
    \ mi] = eq[i];\n            a[i] = (xi - calc_prefix(i, mi)) % mi;\n         \
    \   if (a[i] < 0) a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n   \
    \             long long mj = eq[j].second;\n                a[i] *= inv_mod(mj,\
    \ mi);\n                a[i] %= mi;\n            }\n        }\n        return\
    \ calc_prefix(n, m);\n    }\n} // namespace suisen\n\n\n\n"
  code: "#ifndef SUISEN_GARNER\n#define SUISEN_GARNER\n\n#include <vector>\n#include\
    \ \"library/number/ext_gcd.hpp\"\n\nnamespace suisen {\n    /**\n     * @brief\
    \ Calculates x mod m s.t. x = x_i (mod m_i). m_i should be coprime each other.\n\
    \     * @param eq vector of { x_i, m_i }\n     * @return x mod m s.t. x = x_i\
    \ (mod m_i)\n     */\n    int garner(std::vector<std::pair<int, int>> eq, int\
    \ m) {\n        const int n = eq.size();\n        std::vector<long long> a(n);\n\
    \n        auto calc_prefix = [&](int i, long long mod) {\n            long long\
    \ res = 0;\n            long long prd = 1;\n            for (int j = 0; j < i;\
    \ ++j) {\n                (res += a[j] * prd) %= mod;\n                (prd *=\
    \ eq[j].second) %= mod;\n            }\n            return res;\n        };\n\
    \    \n        for (int i = 0; i < n; ++i) {\n            auto [xi, mi] = eq[i];\n\
    \            a[i] = (xi - calc_prefix(i, mi)) % mi;\n            if (a[i] < 0)\
    \ a[i] += mi;\n            for (int j = 0; j < i; ++j) {\n                long\
    \ long mj = eq[j].second;\n                a[i] *= inv_mod(mj, mi);\n        \
    \        a[i] %= mi;\n            }\n        }\n        return calc_prefix(n,\
    \ m);\n    }\n} // namespace suisen\n\n\n#endif // SUISEN_GARNER\n"
  dependsOn:
  - library/number/ext_gcd.hpp
  isVerificationFile: false
  path: library/number/garner.hpp
  requiredBy:
  - library/convolution/multi_variate_convolution_circular.hpp
  timestamp: '2023-09-06 20:35:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/src/convolution/multi_variate_convolution_circular/multivariate_convolution_cyclic.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/bitwise_xor_convolution.test.cpp
  - test/src/convolution/multi_variate_convolution_circular/dummy.test.cpp
documentation_of: library/number/garner.hpp
layout: document
title: Garner's Algorithm
---
## Garner's Algorithm

## 問題

連立合同式 $x \equiv x _ i \pmod{m _ i}\; (i=1,\ldots,n)$ と正整数 $M$ が与えられる。ただし、 $i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ が成り立つ。

連立合同式を満たす整数 $x$ は $0$ 以上 $\displaystyle\prod _ {i = 1} ^ n m _ i$ 未満の範囲に一意存在するので、この $x$ の値を $\mathrm{mod}\; M$ で求めよ。

---

本ライブラリは上記の問題を $O(n ^ 2 \log (\max_i m_i))$ 時間で解く実装である。$\displaystyle\prod _ {i = 1} ^ n m _ i$ が非常に大きくなりうる場合にもオーバーフローせずに解くことができる。

## アルゴリズム

$0\leq a _ i \lt m _ i$ を満たす整数 $a _ 1, \ldots, a _ n$ を用いて $x$ を以下のように表す。

$$\begin{aligned}
x
&= a _ 1 + a _ 2 m _ 1 + a _ 3 m _ 1 m _ 2 + \cdots + a _ n m _ 1 m _ 2 \cdots m _ {n - 1} \newline
&= \sum _ {i = 1} ^ n a _ i \prod _ {j = 1} ^ {i - 1} m _ j\tag{1}.
\end{aligned}$$

ここで、式 $(1)$ の両辺の $\mathrm{mod}\; m _ k$ を取ることで、次を得る。

$$
x _ k \equiv \sum _ {i = 1} ^ k a _ i \prod _ {j = 1} ^ {i - 1} m _ j \pmod{m _ k}.
$$

これを $a _ k$ について解いて、式 $(2)$ を得る。

$$
a _ k \equiv \Biggl( x _ k - \sum _ {i = 1} ^ {k - 1} a _ i \prod _ {j = 1} ^ {i - 1} m _ j\Biggr) \displaystyle \prod _ {j = 1} ^ {k - 1} m _ j ^ {-1} \pmod{m _ k}. \tag{2}
$$

ここで、$m _ j ^ {-1}$ は $\mathrm{mod}\; m _ k$ における $m _ j$ の乗法逆元を表す。$i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ の仮定より、この逆元は必ず存在することに注意する。

式 $(2)$ の右辺を適切に $\mathrm{mod}\; m _ k$ を取りながら計算することで、計算途中の値を小さく保ったまま $a _ k$ の値を計算できる。$m _ j ^ {-1}$ の計算は合計 $O(k\log m _ k)$ 時間、$\sum a _ i\prod m _ j$ の計算は積を差分更新することで合計 $O(k)$ 時間で計算できる。

最後に、得られた $a _ 1,\ldots, a _ n$ を用いて式 $(1)$ の右辺を適切に $\mathrm{mod}\; M$ を取りながら計算することで、計算途中の値を小さく保ったまま $x\bmod M$ の値を得ることができる。

以上より、全体 $O(n ^ 2 \log (\max _ i m _ i))$ 時間で問題を解くことができた。

## 用途

### 任意 mod 畳み込み

NTT-friendly な素数 $p _ 1, \ldots, p _ k$ を用意して各々で畳みこんだ後、Garner のアルゴリズムを用いることで実現できる。

値が $0$ 以上 $L$ 以下で長さが $x, y$ の列を畳みこむ場合は、例えば $p _ 1 p _ 2 \cdots p _ k \gt L ^ 2 \max(x, y)$ を満たすように $p _ 1, \ldots, p _ k$ を選ぶことで、Garner のアルゴリズムにより復元された値が正しいことを保証できる。

## 参考

- https://redirect.cs.umbc.edu/~lomonaco/s08/441/handouts/Garner-Alg-Example.pdf
