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

## アルゴリズム

多項式 $l$ を以下で定義する。

$$l(x) = \prod _ {i = 0} ^ {N - 1} (x - x _ i)$$

このとき、$\displaystyle l'(x _ i) = \prod _ {j \neq i} (x _ i - x _ j)$ が成り立つ。

$l$ はマージテクおよび高速フーリエ変換による畳み込みなどを用いて $\Theta(N (\log N) ^ 2)$ 時間で計算でき、$l$ に対して $l'$ は $\Theta(N)$ 時間で計算できる。

各 $x _ 0, \ldots, x _ {N - 1}$ に対する $l'(x _ i)$ を求めるのは Multipoint Evaluation なので $\Theta(N (\log N) ^ 2)$ 時間で計算できる。

$l'$ を用いれば、補間多項式は次のように書ける。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {j \neq i} (x - x _ j).
$$

ここで、$0\leq l\lt r\leq N$ を満たす整数 $l, r$ に対して、多項式 $f _ {l, r}$ を以下で定義する。求めたいのは $f _ {0, N}(x)$ である。

$$
f _ {l, r} (x) = \sum _ {i = l} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {\scriptstyle l \leq j \lt r,j\neq i} (x - x _ j).
$$

$l\leq m\leq r$ を満たす整数 $m$ に対して、次が成り立つ。

$$\begin{aligned}
f _ {l, r} (x)
&= \sum _ {i = l} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {l \leq j \lt r,j\neq i} (x - x _ j) \\
&= \sum _ {i = l} ^ {m - 1} \dfrac{y _ i}{l'(x _ i)} \Biggl(\prod _ {l \leq j \lt m,j\neq i} (x - x _ j)\Biggr)\Biggl(\prod _ {m \leq j \lt r} (x - x _ j)\Biggr) \\
&+ \sum _ {i = m} ^ {r - 1} \dfrac{y _ i}{l'(x _ i)} \Biggl(\prod _ {l \leq j \lt m} (x - x _ j)\Biggr)\Biggl(\prod _ {m \leq j \lt r,j\neq i} (x - x _ j)\Biggr) \\
&= \Biggl(\prod _ {m \leq j \lt r} (x - x _ j)\Biggr) f _ {l, m}(x) + \Biggl(\prod _ {l \leq j \lt m} (x - x _ j)\Biggr) f _ {m, r}(x)
\end{aligned}$$

従って、$f _ {l, r}(x)$ や $\prod _ {i = l} ^ {r - 1} (x - x _ i)$ を $m=\left\lfloor\dfrac{l+r}{2}\right\rfloor$ として再帰的に計算すると、$f _ {0, N}(x)$ の計算に掛かる時間計算量 $T(N)$ は次を満たす。

$$
T(N) = \begin{cases} 2T(N / 2) + \Theta(N \log N) & \text{if}\ N \gt 1 \\ O(1) & \text{otherwise} \end{cases}.
$$

即ち、$T(N) = \Theta(N (\log N) ^ 2)$ である (★)。

<details>
<summary> (★) の補足 </summary>

http://homepages.math.uic.edu/~leon/cs-mcs401-s08/handouts/extended_master_theorem.pdf の $(3')$ で $a = b = 2, \alpha = 1$ とすることで、$T(N) = \Theta(N (\log N) ^ 2)$ を得る。(補足終)

</details>

以上より、$\Theta(N (\log N) ^ 2)$ 時間で補間多項式を計算することが出来た。なお、$\prod _ {i = l} ^ {r - 1} (x - x _ i)$ については、Multipoint Evaluation で計算したものを再利用すると定数倍高速化が可能である。
