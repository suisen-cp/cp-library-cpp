---
title: ラグランジュ補間
documentation_of: //library/polynomial/lagrange_interpolation.hpp
---
## ラグランジュ補間

$\mathbb{F} _ p$ 上の高々 $N - 1$ 次の多項式 $f(x)$ について、次の情報が分かっている。

$$
f(x _ i) = y _ i\ (i = 0, \ldots, N - 1).
$$

$x _ i$ が全て互いに相異なるとき、$f$ は存在して一意であり、次のような表示を持つ。

$$
f(x) = \sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (x - x _ j)}{\prod _ {j \neq i} (x _ i - x _ j)}.
$$

この $f$ を __補間多項式__ と呼ぶ。

$x _ i$ および $y _ i$ に対して定まる補間多項式 $f$ に対して、ある与えられた $t$ に関する $f(t)$ を計算する。

## アルゴリズム (一般の場合)

多項式 $l$ を以下で定義する。

$$l(x) = \prod _ {i = 0} ^ {N - 1} (x - x _ i)$$

このとき、$\displaystyle l'(x _ i) = \prod _ {j \neq i} (x _ i - x _ j)$ が成り立つ。

$l$ はマージテクおよび高速フーリエ変換による畳み込みなどを用いて $\Theta(N (\log N) ^ 2)$ 時間で計算でき、$l$ に対して $l'$ は $\Theta(N)$ 時間で計算できる。

各 $x _ 0, \ldots, x _ {N - 1}$ に対する $l'(x _ i)$ を求めるのは Multipoint Evaluation なので $\Theta(N (\log N) ^ 2)$ 時間で計算できる。

$l'$ を用いれば、求めたい値は次のように書ける。

$$
f(t) = \sum _ {i = 0} ^ {N - 1} \dfrac{y _ i}{l'(x _ i)} \prod _ {j \neq i} (t - x _ j).
$$

$i = 0, \ldots, N - 1$ に対して、次を満たす補助的な配列 $\mathrm{pre}, \mathrm{suf}$ を前計算しておく。

$$\begin{aligned}
\mathrm{pre}(i) &= \prod _ {j = 0} ^ {i - 1} (t - x _ j),\\
\mathrm{suf}(i) &= \prod _ {j = i + 1} ^ {N - 1} (t - x _ j).
\end{aligned}$$

このとき、$\displaystyle \prod _ {j \neq i} (t - x _ j) = \left(\prod _ {j = 0} ^ {i - 1} (t - x _ j)\right)\cdot \left(\prod _ {j = i + 1} ^ {N - 1} (t - x _ j)\right) = \mathrm{pre}(i) \cdot \mathrm{suf}(i)$ として計算できる。

従って、全体 $\Theta(N (\log N) ^ 2)$ 時間で $f(t)$ を計算出来る。

## アルゴリズム ($x _ i$ が等差数列を成す場合)

ある $a, b$ に対して $x _ i = a i + b$ が成り立つと仮定すると、求めたい値は次のように書くことが出来る。ここで、$a = 0$ のときは $x _ i$ が全て互いに相異なるという制約から $N = 1$ となり $0 ^ 0$ が現れるが、ここでは $0 ^ 0 = 1$ と定める。

$$
f(t) = \dfrac{1}{a ^ {N - 1}}\sum _ {i = 0} ^ {N - 1} y _ i \dfrac{\prod _ {j \neq i} (t - x _ j)}{\prod _ {j \neq i} (i - j)}.
$$

各 $\prod _ {j \neq i} (t - x _ j)$ については、一般の場合と同様にして $\Theta(N)$ 時間で計算できる。

$\prod _ {j \neq i} (i - j)$ に関しては、次のように計算できる。

$$\begin{aligned}
\prod _ {j \neq i} (i - j)
&= \left(\prod _ {j = 0} ^ {i - 1} (i - j)\right) \cdot \left(\prod _ {j = i + 1} ^ {N - 1} (i - j)\right)\\
&= (i\times (i - 1) \times \cdots \times 1) \cdot ((-1) \times (-2) \times \cdots \times (-(N - i - 1)))\\
&= (-1) ^ {N - i - 1} \times i! \times (N - i - 1)!.
\end{aligned}$$

従って、$0!, \ldots, (N - 1)!$ の乗法逆元を前計算しておけば、各 $i$ に対する $y _ i \dfrac{\prod _ {j \neq i} (t - x _ j)}{\prod _ {j \neq i} (i - j)}$ は $O(1)$ 時間で計算することが出来ます。

$0!, \ldots, (N - 1)!$ の乗法逆元の計算は $\Theta(N + \log p)$ で、$\dfrac{1}{a ^ {N - 1}}$ の計算は $\Theta(\log N)$ で計算できるので、全体 $\Theta(N + \log p)$ 時間で $f(t)$ を計算できる。
