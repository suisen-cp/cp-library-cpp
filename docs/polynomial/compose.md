---
title: 合成
documentation_of: //library/polynomial/compose.hpp
---
## 合成

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ i,\ g(x) = \sum _ {i = 0} ^ {M - 1} b _ i x ^ i$ に対して合成 $(f\circ g)(x) \pmod{x ^ K}$ を $O(NK + \sqrt{N}K\log K)$ 時間で計算するライブラリ。

## アルゴリズム

以下は全て $\mathrm{mod}\ x ^ K$ で計算する。

$\displaystyle f\circ g = \sum _ {i = 0} ^ {N - 1} a _ i g ^ i$ を計算したい。$B \coloneqq \lceil \sqrt{N} \rceil$ とすれば $\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} (g ^ B) ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} g ^ j$ と表せる。ただし $i \geq N$ に対して $a _ i = 0$ とする。

$g ^ 0, g ^ 1, \ldots, g ^ {B - 1}$ および $G\coloneqq g ^ B$ に対して $G ^ 0, G ^ 1, \ldots, G ^ {B - 1}$ を全て ($\mathrm{mod}\ x ^ K$ で) 前計算する。この前計算は $O(\sqrt N K \log K)$ 時間で可能である。

この前計算の結果を用いれば、各 $i=0,1,\ldots,B-1$ に対して、$\displaystyle \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j \bmod x ^ K$ を $O(\sqrt{N} K)$ 時間で計算できる。従って、$\displaystyle \left(G ^ i \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j\right) \bmod x ^ K$ の計算は $O(\sqrt{N} K + K \log K)$ 時間で可能である。

以上をまとめると、全体の計算量は $O(NK + \sqrt{N}K\log K)$ 時間となる。

## 高速化 (1)

$g ^ i,G ^ i$ の前計算において、$\mathbf{FFT}(g)$ や $\mathbf{FFT}(G)$ を $1$ 回しか計算しないことで定数倍高速化を図ることができる。

## 高速化 (2)

$\lbrack x ^ 0 \rbrack g = 0$ が成り立つ場合、$\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} x ^ {Bi} ((g / x) ^ B) ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} x ^ j (g / x) ^ j$ において $\displaystyle \sum _ {j = 0} ^ {B - 1} a _ {iB + j} x ^ j (g / x) ^ j$ は $\mathrm{mod}\ x ^ {N - iB}$ で求めれば十分である。従って、$NK$ に付く係数をおよそ $1/2$ 倍に削減できる。またこの場合は $f\leftarrow f \bmod x ^ K$ としてもよいので、計算量は本質的に改善されて $O(\min(N,K)K + \sqrt{\min(N,K)}K\log K)$ 時間となる。

$\lbrack x ^ 0 \rbrack g \neq 0$ の場合は $f$ を taylor shift して $f \leftarrow f(x + \lbrack x ^ 0 \rbrack g)$ とおき直すことで $\lbrack x ^ 0 \rbrack g = 0$ の場合に帰着できる。帰着に掛かる計算量は $O(N\log N)$ であり、計算量は $O(\min(N,K)K + \sqrt{\min(N,K)}K\log K + N \log N)$ である。なお、$K \leq \log N$ など $K$ が極端に小さい場合は、$N\log N$ の項が支配的になるため帰着を行わない方が高速となる可能性がある。

