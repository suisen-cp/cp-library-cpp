---
title: $\displaystyle \sum _ i i ^ d r ^ i$
documentation_of: //library/math/sum_i^d_r^i.hpp
---
## $\displaystyle \sum _ {i = 0} ^ {n - 1} i ^ d r ^ i$

$\displaystyle \dfrac{1}{(1 - x) ^ {k + 1}} = \sum _ {i = 0} ^ \infty \binom{i + k}{k} x ^ i$ を思い出すと、$\displaystyle \sum _ {i = 0} ^ \infty i ^ d (rx) ^ i = \dfrac{f}{(1 - rx) ^ {d + 1}}$ なる高々 $d$ 次の $f$ が存在することが分かる。いま計算したいのは $[x ^ {n - 1}] \dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}}$ である。

以下のような、定数 $c$ と高々 $d$ 次の $g$ による部分分数分解を考える。

$$\dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}} = \dfrac{c}{1 - x} + \dfrac{g}{(1 - rx) ^ {d + 1}}.$$

両辺に $(1 - rx) ^ {d + 1}$ を掛けて次を得る。

$$(1 - rx) ^ {d + 1}\cdot \dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}} = c\cdot \dfrac{(1 - rx) ^ {d + 1}}{1 - x} + g.$$

$g$ は高々 $d$ 次であるから、両辺の $d + 1$ 次の項を比較することで $c$ を得ることができる。

左辺の $d + 1$ 次の項の係数の計算に関しては、$\dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}}$ の $d + 1$ 次以下の項は実際に $\displaystyle \sum _ {i = 0} ^ j i ^ d r ^ i$ を計算することで得られ、$(1 - rx) ^ {d + 1}$ に関しては二項定理で展開すればよいので、$O(d)$ 時間。

右辺の $d + 1$ 次の項の係数の計算に関しても、$\dfrac{1}{1 - x}$ を掛けることが累積和を取る操作と対応しているため $(1 - rx) ^ {d + 1}$ を同様に二項定理で展開することで $O(d)$ 時間。

以上で定数 $c$ を $O(d)$ 時間で得ることができた。また、これにより $\dfrac{g}{(1 - rx) ^ {d + 1}} = \dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}} - \dfrac{c}{1 - x}$ の $d + 1$ 次以下の係数を求めることができる。

$g$ の $i$ 次の項の係数を $g _ i$ とおくと、$g$ は高々 $d$ 次であるから、次が成り立つ。

$$\begin{aligned}
\dfrac{g}{(1 - rx) ^ {d + 1}}
&= \sum _ {i = 0} ^ \infty x ^ i \sum _ {j = 0} ^ {d}g _ j \cdot \binom{i - j + d}{d} \cdot r ^ {i - j} \newline
&= \sum _ {i = 0} ^ \infty x ^ i r ^ i\sum _ {j = 0} ^ d \dfrac{g _ j}{r ^ j \cdot d!} \prod _ {k = 1} ^ d (i - j + k).
\end{aligned}$$

即ち、$\displaystyle h(x) = \sum _ {j = 0} ^ d \dfrac{g _ j}{r ^ j \cdot d!} \prod _ {k = 1} ^ d (x - j + k)$ とおくと、$[x ^ i] \dfrac{g}{(1 - rx) ^ {d + 1}} = r ^ i \cdot h(i)$ が成り立つ。いま $h(0),\ldots,h(d)$ の値は既知であるから、ラグランジュの補間公式により $h(n - 1)$ を $O(d)$ 時間で計算することができる。計算すべき値は $[x ^ {n - 1}] \dfrac{f}{(1 - x)(1 - rx) ^ {d + 1}} = c + r ^ {n - 1} h(n - 1)$ であるから、結局全体 $O(d + \log n)$ 時間で $\displaystyle \sum _ {i = 0} ^ {n - 1} i ^ d r ^ i$ を計算することができた。

## $\displaystyle \sum _ {i = 0} ^ \infty i ^ d r ^ i$

($r\neq 1$ の仮定の下で) 上で求めた $c$ が答えになるらしいが理解していない。

## 参考

- https://maspypy.com/%E5%A4%9A%E9%A0%85%E5%BC%8F%E3%83%BB%E5%BD%A2%E5%BC%8F%E7%9A%84%E3%81%B9%E3%81%8D%E7%B4%9A%E6%95%B0-%E9%AB%98%E9%80%9F%E3%81%AB%E8%A8%88%E7%AE%97%E3%81%A7%E3%81%8D%E3%82%8B%E3%82%82%E3%81%AE#toc36