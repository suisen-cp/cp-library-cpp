---
title: 合成
documentation_of: //library/polynomial/compose.hpp
---
## 合成

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {N - 1} a _ i x ^ i,\ g(x) = \sum _ {i = 0} ^ {M - 1} b _ i x ^ i$ に対して合成 $(f\circ g)(x) \pmod{x ^ K}$ を $O(NK + \sqrt{N}K\log K + M)$ 時間で計算するライブラリ。

## アルゴリズム

まず、$g\leftarrow g \bmod x ^ K$ とする。この部分の計算量は $O(M + K)$ である。

$\displaystyle f\circ g = \sum _ {i = 0} ^ {N - 1} a _ i g ^ i$ を計算したい。$B \coloneqq \lceil \sqrt{N} \rceil$ とすれば $\displaystyle f\circ g = \sum _ {i = 0} ^ {B - 1} G ^ i \sum _ {j = 0} ^ {B - 1} a _ {iB + j} g ^ j$ と表せる。ただし $i \geq N$ に対して $a _ i = 0$ とする。

$g ^ 0, g ^ 1, \ldots, g ^ {B - 1}$ および $G\coloneqq g ^ B$ に対して $G ^ 0, G ^ 1, \ldots, G ^ {B - 1}$ を全て ($\mathrm{mod}\ x ^ K$ で) 前計算する。この前計算は $O(\sqrt N K \log K)$ 時間で可能である。

この前計算の結果を用いれば、各 $i=0,1,\ldots,B-1$ に対して、$\displaystyle \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j \bmod x ^ K$ を $O(\sqrt{N} K)$ 時間で計算できる。従って、$\displaystyle \left(G ^ i \sum _ {j = 0} ^ {B - 1}a _ {iB + j} g ^ j\right) \bmod x ^ K$ の計算は $O(\sqrt{N} K + K \log K)$ 時間で可能である。

以上をまとめると、全体の計算量は $O(NK + \sqrt{N}K\log K + M)$ 時間となる。
