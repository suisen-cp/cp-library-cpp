---
title: Garner's Algorithm
documentation_of: //library/number/garner.hpp
---
## Garner's Algorithm

## 問題

連立合同式 $x \equiv x _ i \pmod{m _ i}\; (i=1,\ldots,n)$ と正整数 $M$ が与えられる。ただし、 $i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ が成り立つ。

連立合同式を満たす整数 $x$ は $0$ 以上 $\displaystyle\prod _ {i = 1} ^ n m _ i$ 未満の範囲に一意存在するので、この $x$ の値を $\mathrm{mod}\; M$ で求めよ。

---

本ライブラリは上記の問題を $O(n ^ 2 \log (\max_i m_i))$ 時間で解く実装である。$\displaystyle\prod _ {i = 1} ^ n m _ i$ が非常に大きくなりうる場合にもオーバーフローせずに解くことができる。

## アルゴリズム

$0\leq a _ i \lt m _ i$ を満たす整数 $a _ 1, \ldots, a _ n$ を用いて $x$ を以下のように表す。

$$\begin{aligned}
x
&= a _ 1 + a _ 2 m _ 1 + a _ 3 m _ 1 m _ 2 + \cdots + a _ n m _ 1 m _ 2 \cdots m _ {n - 1} \newline
&= \sum _ {i = 1} ^ n a _ i \prod _ {j = 1} ^ {i - 1} m _ j\tag{1}.
\end{aligned}$$

ここで、式 $(1)$ の両辺の $\mathrm{mod}\; m _ k$ を取ることで、次を得る。

$$
x _ k \equiv \sum _ {i = 1} ^ k a _ i \prod _ {j = 1} ^ {i - 1} m _ j \pmod{m _ k}.
$$

これを $a _ k$ について解いて、式 $(2)$ を得る。

$$
a _ k \equiv \Biggl( x _ k - \sum _ {i = 1} ^ {k - 1} a _ i \prod _ {j = 1} ^ {i - 1} m _ j\Biggr) \displaystyle \prod _ {j = 1} ^ {k - 1} m _ j ^ {-1} \pmod{m _ k}. \tag{2}
$$

ここで、$m _ j ^ {-1}$ は $\mathrm{mod}\; m _ k$ における $m _ j$ の乗法逆元を表す。$i \neq j \Rightarrow \gcd(m _ i, m _ j) = 1$ の仮定より、この逆元は必ず存在することに注意する。

式 $(2)$ の右辺を適切に $\mathrm{mod}\; m _ k$ を取りながら計算することで、計算途中の値を小さく保ったまま $a _ k$ の値を計算できる。$m _ j ^ {-1}$ の計算は合計 $O(k\log m _ k)$ 時間、$\sum a _ i\prod m _ j$ の計算は積を差分更新することで合計 $O(k)$ 時間で計算できる。

最後に、得られた $a _ 1,\ldots, a _ n$ を用いて式 $(1)$ の右辺を適切に $\mathrm{mod}\; M$ を取りながら計算することで、計算途中の値を小さく保ったまま $x\bmod M$ の値を得ることができる。

以上より、全体 $O(n ^ 2 \log (\max _ i m _ i))$ 時間で問題を解くことができた。

## 用途

### 任意 mod 畳み込み

NTT-friendly な素数 $p _ 1, \ldots, p _ k$ を用意して各々で畳みこんだ後、Garner のアルゴリズムを用いることで実現できる。

値が $0$ 以上 $L$ 以下で長さが $x, y$ の列を畳みこむ場合は、例えば $p _ 1 p _ 2 \cdots p _ k \gt L ^ 2 \max(x, y)$ を満たすように $p _ 1, \ldots, p _ k$ を選ぶことで、Garner のアルゴリズムにより復元された値が正しいことを保証できる。

## 参考

- https://redirect.cs.umbc.edu/~lomonaco/s08/441/handouts/Garner-Alg-Example.pdf
