---
title: Polynomial Taylor Shift
documentation_of: //library/polynomial/polynomial_taylor_shift.hpp
---
## Polynomial Taylor Shift

$\mathbb{F} _ p$ 上の $n$ 次多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {n} a _ i x ^ i$ および $c\in \mathbb{F} _ p$ に対して、多項式 $g(x) = f(x + c)$ を計算します。

## アルゴリズム

$$\begin{aligned}
f(x + c)
&=\sum _ {i = 0} ^ {n} a _ i (x + c) ^ i \\
&=\sum _ {i = 0} ^ {n} \sum _{j = 0} ^ i a _ i \cdot \binom{i}{j}\cdot c ^ {i - j} \cdot x ^ j \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {i = j} ^ {n} (a _ i \cdot i!) \cdot \dfrac{c ^ {i - j}}{(i - j)!} \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {k = 0} ^ {n - j} (a _ {j + k} \cdot (j + k)!) \cdot \dfrac{c ^ k}{k!} \\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ j}{j!} \sum _ {k = 0} ^ {n - j} b _ {(n - j) - k} \cdot \dfrac{c ^ k}{k!} \quad (b _ i := a _ {n - i} \cdot (n - i)! )\\
&=\sum _ {j = 0} ^ {n} \dfrac{x ^ {n - j}}{(n - j)!} \sum _ {k = 0} ^ {j} b _ {j - k} \cdot \dfrac{c ^ k}{k!}
\end{aligned}$$

で、各 $j = 0, \ldots, n$ に対する $\displaystyle \sum _ {k = 0} ^ {j} b _ {j - k} \cdot \dfrac{c ^ k}{k!}$ は高速フーリエ変換等を用いた畳み込みにより $\Theta(n \log n)$ 時間で計算できます。

従って、$0!,\ldots,n!$ の乗法逆元の前計算の下で、$f(x + c)$ も $\Theta(n \log n)$ 時間で計算できます。

なお、$0!,\ldots,n!$ の乗法逆元が存在すること、即ち $n \lt p$ を仮定していることに注意します。
