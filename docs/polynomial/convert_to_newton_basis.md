---
title: Convert To Newton Basis
documentation_of: //library/polynomial/convert_to_newton_basis.hpp
---
## Convert To Newton Basis

多項式 $\displaystyle f(x) = \sum _ {i = 0} ^ {n - 1} a _ i x ^ i$ および長さ $n$ の列 $\lbrace p _ i \rbrace _ {i = 0} ^ {n - 1}$ に対して、次を満たす列 $\lbrace b _ i \rbrace _ {i = 0} ^ {n - 1}$ を $O(n (\log n) ^ 2)$ 時間で計算するライブラリ。

$$f(x) = \sum _ {i = 0} ^ {n - 1} b _ i \prod _ {j = 0} ^ {i - 1} (x - p _ j).$$

## アルゴリズム

分割統治法による。$0\leq l \lt r\leq n$ なる整数組 $(l, r)$ に対して $\displaystyle f _ {l, r}(x) \coloneqq \sum _ {i = l} ^ {r - 1} b _ i \prod _ {j = l} ^ {i - 1} (x - p _ j)$ と定義すると、整数 $m\in\lbrack l, r)$ に対して次が成り立つ。

$$\begin{aligned}
f _ {l, r}(x)
&= \sum _ {i = l} ^ {m - 1} b _ i \prod _ {j = l} ^ {i - 1} (x - p _ j) + \left(\prod _ {i = l} ^ {m - 1} (x - p _ i)\right) \sum _ {i = m} ^ {r - 1} b _ i \prod _ {j = m} ^ {i - 1} (x - p _ j) \newline
&= f _ {l, m}(x) + g _ {l, m}(x) f _ {m, r}(x). \quad \left(g _ {l, m}(x) \coloneqq \prod _ {i = l} ^ {m - 1} (x - p _ i)\right)
\end{aligned}$$

ここで $\deg g _ {l, m} = m - l,\ \deg f _ {l, m} = m - l - 1$ に注目すると、$f _ {m, r}(x)$ と $f _ {l, m}(x)$ はそれぞれ $f _ {l, r}(x)$ を $g _ {l, m}(x)$ で割った商と余りに対応することが分かる。

従って、二分木状に $g _ {l, r}$ をボトムアップに計算し (subproduct tree)、トップダウンに $f _ {l, r}$ を計算することで $O(n (\log n) ^ 2)$ 時間で全ての $i = 0, 1, \ldots, n - 1$ に対する $f _ {i, i + 1}(x) \equiv b _ i$ を計算することができる。
