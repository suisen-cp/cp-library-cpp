---
title: $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$
documentation_of: //library/polynomial/prod_f(r^k_x).hpp
---
## $\left(\prod_{k=0}^{m-1} f(r^k x)\right) \bmod x^N$

$\displaystyle F(x) := \prod_{k=0}^{m-1} f(r^k x)$ とする。形式的冪級数 $f$ の $i$ 次の係数を $f_i$ と書く。

$f(x)=0$ の場合は自明なので、$f(x)\neq 0$ を仮定する。また、$f _ 0=1$ と仮定する。

$f _ 0\neq 1$ の場合は $f = c\cdot x ^ a\cdot f'\; (f' _ 0 = 1)$ とすれば、次のようにして定数項が $1$ のケースに帰着できる。

$$F(x)=c ^ m r ^ {\frac{m(m-1)}{2}a} x ^ {\frac{m(m-1)}{2}} \prod _ {k = 0} ^ {m - 1} f'(r ^ k x).$$

$g=\log f$ とおくと、$F = \exp (\log F)$ を用いることで、$F \bmod x ^ N$ を $O(N \log N)$ 時間で計算できる。

$$\begin{aligned}
\log F
&= \sum _ {k = 0} ^ {m - 1} \log f(r ^ k x) \newline
&= \sum _ {k = 0} ^ {m - 1} g(r ^ k x) \newline
&= \sum _ {i = 0} ^ {\infty} g _ i x ^ i\sum _ {k = 0} ^ {m - 1} (r ^ i) ^ k \newline
&= \sum _ {i = 0} ^ {\infty} g _ i x ^ i \cdot \begin{cases}
\displaystyle m \cdot x ^ i & \text {if}\quad r ^ i = 1 \newline
\displaystyle \dfrac{(r ^ m) ^ i - 1}{r ^ i - 1} & \text{otherwise}
\end{cases}.
\end{aligned}$$

<!-- ### $f$ が疎な場合

以下の等式を用いる。

$$F(x) f(r ^ m x) = F(rx) f(x).$$

両辺で $i$ 次の項が等しいことに注目すると、次の等式が得られる。

$$\begin{aligned}
&\sum _ {j = 0} ^ i F _ j f _ {i - j}(r ^ m) ^ {i - j} = \sum _ {j = 0} ^ i F _ j f _ {i - j}r ^ j \newline
\iff &\sum_ {j = 0} ^ i F_j f _ {i - j}(r ^ {m(i - j)} - r ^ j) = 0 \newline
\iff &F _ i f_0(1 - r ^ i) = \sum _ {j = 0} ^ {i - 1} F_j f _ {i - j} (r ^ j - r ^ {m(i - j)})
\end{aligned}$$

$f _ 0 = 1$ より、**$r$ の位数が十分大きいことを仮定すると、** 両辺を $1 - r ^ i$ で割ることで $F _ i$ を得ることができる。$f$ の非零の係数が $K$ 個であれば、$F \bmod x ^ N$ を $O(N(K + \log \mathrm{mod}))$ で計算できる。 -->

## 参考

- https://maspypy.com/%E5%A4%9A%E9%A0%85%E5%BC%8F%E3%83%BB%E5%BD%A2%E5%BC%8F%E7%9A%84%E3%81%B9%E3%81%8D%E7%B4%9A%E6%95%B0-%E9%AB%98%E9%80%9F%E3%81%AB%E8%A8%88%E7%AE%97%E3%81%A7%E3%81%8D%E3%82%8B%E3%82%82%E3%81%AE#toc21