---
title: chirp z-transform (評価点が等差数列を成す場合の Multipoint Evaluation)
documentation_of: //library/transform/chirp_z_transform.hpp
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