---
title: $a\uparrow\uparrow b \bmod m$
documentation_of: //library/number/tetration_mod.hpp
---
## $a\uparrow\uparrow b \bmod m$

まず、$m=1$ の場合の答えは $0$ である。

$\gcd\left(\dfrac{m}{\gcd(m,a ^ i)}, a\right) = 1$ となる最小の非負整数 $i$ を $i _ 0$ とおく。また、$m _ 0 = \dfrac{m}{\gcd(m, a ^ {i _ 0})}$ とおく。

- $a\uparrow\uparrow (b - 1) \geq i _ 0$ の場合: $x\equiv a\uparrow\uparrow (b - 1) \bmod \varphi(m _ 0)$ かつ $x \geq i _ 0$ なる整数 $x$ に対して以下が成り立つので、$a\uparrow\uparrow (b - 1) \bmod \varphi(m _ 0)$ を再帰的に計算する。

$$a\uparrow\uparrow b \equiv a ^ x \pmod{m}.$$

- $a\uparrow\uparrow (b - 1) \lt i _ 0$ の場合: 愚直に $a\uparrow\uparrow b = a ^ {a\uparrow\uparrow (b - 1)} \bmod m$ を計算する。

$m \geq 2 \Rightarrow \varphi(\varphi(m)) \leq \dfrac{1}{2}m$ および $d \mid m \Rightarrow \varphi(d) \mid \varphi(m)$ より、2 回再帰するたびに $m$ は半分以下になるので、再帰の深さは $O(\log m)$ である。
