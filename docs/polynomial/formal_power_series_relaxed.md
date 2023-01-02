---
title: Formal Power Series Relaxed
documentation_of: //library/polynomial/formal_power_series_relaxed.hpp
---
## Formal Power Series Relaxed

形式的べき級数 $f\in \mathbb{K}\lbrack\lbrack x\rbrack\rbrack$ の $x ^ i$ の係数を $f_i$ と書く．

以下に示す漸化式に従って Relaxed Convolution を適用することで，$\Theta(N (\log N) ^ 2)$ 時間で $\mathrm{inv},\log,\exp$ などをオンラインで計算できる．

### $h = f / g$ (未実装)

$g _ 0 \in \mathbb{K} ^ {\times}$ を仮定する．

$$
\begin{aligned}
f _ n 
&= \sum _ {i = 0} ^ n h _ i g _ {n - i}\\
&= h _ n g _ 0 + \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i},\\
h _ n 
&= \dfrac{1}{g _ 0}\left(f _ n - \sum _ {i = 0} ^ {n - 1}h _ i g _ {n - i} \right).
\end{aligned}
$$

### $g = 1/f$

$f _ 0 \in \mathbb{K} ^ {\times}$ を仮定する．

$$
g _ n = \begin{cases}
f _ 0 ^ {-1} & \text{if } n = 0\\
\displaystyle -f _ 0 ^ {-1} \sum _ {i = 0} ^ {n - 1} g _ i f _ {n - i} & \text{otherwise}
\end{cases}
$$

### $g = \exp f$

$f _ 0 = 0$ を仮定する．$g' = f' g$ より，

$$
\begin{aligned}
(n + 1) g _ {n + 1}
&= \sum _ {i = 0} ^ n (n - i + 1) f _ {n - i + 1} g _ i,\\
g _ n &= \begin{cases}
1 & \text{if }n = 0 \\
\dfrac{1}{n}\displaystyle\sum _ {i = 0} ^ {n - 1} (n - i) f _ {n - i } g _ i &\text{otherwise}

\end{cases}
\end{aligned}
$$

### $g = \log f$

$g _ 0 = 1$ を仮定する．$fg'=f'$ より，

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i+1) g _ {i + 1} f _ {n - i} &= (n + 1)f _ {n + 1},\\
(n + 1) f _ 0 g _ {n + 1} &= (n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i+1) g _ {i + 1} f _ {n - i},\\
g _ {n + 1} &= \dfrac{1}{(n+1)f_0}\left((n + 1) f _ {n + 1} - \sum _ {i = 0} ^ {n - 1}(i+1) g _ {i + 1} f _ {n - i}\right),\\
g _ n &= \begin{cases}
0 & \text{if }n = 0\\
\displaystyle \dfrac{1}{nf_0}\left(n f _ {n} - \sum _ {i = 1} ^ {n - 1}i g _ i f _ {n - i}\right) & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ k$

$f_0\neq 0$ を仮定する．$f _ 0 = 0$ の場合は，$f = x ^ p \cdot f'\ (f'_0 \neq 0)$ の形に直してから $g = x ^ {pk} f'^ k$  として計算すればよい．$g'=kf^{k-1} f'$ の両辺に $f$ を掛けることで $fg'=kgf'$ が得られるので，

$$
\begin{aligned}
\sum _ {i = 0} ^ n (i + 1) g _ {i + 1} f _ {n - i} 
&= k\sum _ {i = 0} ^ n g _ i\cdot (n-i+1) f _ {n-i+1}, \\
(n+1)f_0g _ {n+1}
&= k\sum _ {i = 0} ^ n g _ i\cdot (n-i+1) f _ {n-i+1} - \sum _ {i = 1} ^ {n} i g _ i f _ {n - i + 1} \\
&=\sum _ {i = 0} ^ {n} (k(n-i+1)-i)g_i f _{n-i+1},\\
g _ {n + 1} &= \dfrac{1}{(n+1)f_0}\sum _ {i = 0} ^ {n} (k(n-i+1)-i)g_i f _{n-i+1},\\
g _ n &= \begin{cases}
f _ 0 ^ k & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k(n-i)-i)g_i f _{n-i} & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ {1/2}$

$f _ 0 \neq 0$ であることおよび $f _ 0 ^ {1/2}$ の存在を仮定する．

$$
\begin{aligned}
f _ {n+1} &= \sum _ {i = 0} ^ {n + 1} g _ i g _ {n + 1 - i},\\
2g _ 0 g _ {n + 1} &= f _ {n + 1} - \sum _ {i = 1} ^ {n} g _ i g _ {n + 1 - i},\\
g _ n &= \begin{cases}
f _ 0 ^ {1/2} & \text{if }n = 0\\
\displaystyle \dfrac{1}{2g_0}\left(f _ {n } - \sum _ {i = 1} ^ {n-1} g _ i g _ {n - i}\right) & \text{otherwise}
\end{cases}
\end{aligned}
$$

### $g = f ^ {1/k}$ (未実装)

$f _ 0 \neq 0$ であることおよび $f _ 0 ^ {1/k}$ の存在を仮定する．$g ^ k = f$ を $\mathrm{pow}$ と同様に微分することで，次を得る．

$$
g _ n = \begin{cases}
f _ 0 ^ {1/k} & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k^{-1}(n-i)-i)g_i f _{n-i} & \text{otherwise}
\end{cases}
$$

より一般には，$g = f ^ {p/q}$ を満たす $g$ を計算できる．
