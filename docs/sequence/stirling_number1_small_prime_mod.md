---
title: Stirling Number of the First Kind (Small Prime Mod)
documentation_of: //library/sequence/stirling_number1_small_prime_mod.hpp
---
## Stirling Number of the First Kind (Small Prime Mod)

(符号無し) 第一種スターリング数 $\begin{bmatrix} n \newline k \end{bmatrix}$ を以下で定義する:

$$\begin{bmatrix} n \newline k \end{bmatrix} := [x^k] \prod _ {i = 0} ^ {n - 1} (x + i).$$

$\displaystyle \prod _ {i = 0} ^ {p - 1}(x - i)$ の根は $0,\ldots,p-1$ である。一方、Fermat の小定理より $x ^ p \equiv x \pmod{p}$ より $x ^ p - x$ の根も $0,\ldots,p-1$ である。従って、次が成り立つ。

$$\prod _ {i = 0} ^ {p - 1}(x - i) = x ^ p - x.$$

従って、$n=ap+b$ とすれば、次が成り立つ:

$$\prod _ {i = 0} ^ {n - 1} (x + i) = x ^ a (x ^ {p - 1} - 1) ^ a \prod _ {i = 0} ^ {b - 1} (x + i).$$

即ち、$k=a+c(p-1)+d$ とすれば、次が成り立つ:

$$\begin{bmatrix} n \newline k \end{bmatrix} = \sum _ {c,d} (-1) ^ {a - c} \cdot \binom{a}{c} \cdot \begin{bmatrix} b \newline d \end{bmatrix}.$$

$\begin{bmatrix} b \newline d \end{bmatrix}$ が非零になりうるのは $0\leq d\leq b\leq p-1$ の範囲なので、右辺は高々 $2$ 項の和として計算できる。

$\displaystyle \binom{a}{c}$ は Lucas の定理を用いることで $\langle O(p ^ 2),O(\log _p n)\rangle$ で計算できる [[1]](https://suisen-cp.github.io/cp-library-cpp/library/sequence/binomial_coefficient_small_prime_mod.hpp)。また、全ての $0\leq n\lt p,0\leq k\lt p$ に対する $\begin{bmatrix} n \newline k \end{bmatrix}$ も $O(p ^ 2)$ 時間で計算できる [[2]](https://suisen-cp.github.io/cp-library-cpp/library/sequence/stirling_number1.hpp)。

以上より、任意の整数 $n,k$ に対する $\begin{bmatrix} n \newline k \end{bmatrix}$ を $\langle O(p ^ 2),O(\log _p n)\rangle$ で計算できた。
