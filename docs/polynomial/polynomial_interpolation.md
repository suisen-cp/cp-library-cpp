---
title: 補間多項式
documentation_of: //library/polynomial/polynomial_interpolation.hpp
---
## 補間多項式


$\mathbb{F} _ p$ 上の高々 $N - 1$ 次の多項式 $f(x)$ について、次の情報が分かっている。

$$
f(x _ i) = y _ i\ (i = 0, \ldots, N - 1).
$$

$x _ i$ が全て互いに相異なるとき、$f$ は存在して一意であり、次のような表示を持つ。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (x - x _ j)}{\prod _ {j \neq i} (x _ i - x _ j)}.
$$

この $f$ を __補間多項式__ と呼ぶ。

$x _ i$ および $y _ i$ に対して定まる補間多項式 $f$ を計算する。

