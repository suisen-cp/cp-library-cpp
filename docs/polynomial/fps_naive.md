---
title: Fps Naive
documentation_of: //library/polynomial/fps_naive.hpp
---
## Fps Naive

積や乗法逆元 $\mathrm{inv}$，指数関数 $\exp$，対数関数 $\log$，べき乗 $\mathrm{pow}$，平方根 $\mathrm{sqrt}$ を $\Theta(N ^ 2)$ で計算する形式的べき級数ライブラリ．Set Power Series など，最大次数が十分小さいことが分かっている場合にこちらを用いることで高速化が期待できる．

FFT や NTT を必要としない点も特徴的?

## 概要

形式的べき級数 $f$ の $i$ 次の係数を $f_i$ と書く．

### 積

$h = fg$ を満たす $h$ を求める．これは，以下のように計算される．

$$
h _ n = \sum _ {i = 0} ^ n f _ i g _ {n - i}.
$$

### FPS としての除算

$h = \dfrac{f}{g}$ を満たす $h$ を求める．ただし，$g _ 0 \neq 0$ を仮定する．$f = gh$ であるから，次のように計算される．

$$
\begin{aligned}
f _ n 
&= \sum _ {i = 0} ^ n h _ i g _ {n - i}\\
&= h _ n g _ 0 + \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i},\\
h _ n 
&= \dfrac{1}{g _ 0}\left(f _ n - \sum _ {i = 0} ^ {n - 1}h _ i g _ {n - i} \right).
\end{aligned}
$$

### $\mathrm{inv}$

$gh=1$ を満たす $h$ を求める．ただし，$g _ 0 \neq 0$ を仮定する．形式的べき級数としての除算において $f\equiv 1$ とすればよいので，次のように計算される．

$$
h _ n = \begin{cases}
\dfrac{1}{g _ 0} & \text{if } n = 0\\
\displaystyle -\dfrac{1}{g _ 0}  \sum _ {i = 0} ^ {n - 1} h _ i g _ {n - i} & \text{otherwise}
\end{cases}.
$$

### $\exp$

$g = \exp f$ を満たす $g$ を求める．ただし，$f _ 0 = 0$ を仮定する．$g' = f' g$ より，次のように計算される．

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

### $\log$

$g = \log f$ を満たす $g$ を求める．ただし，$f _ 0 = 1$ を仮定する．$fg'=f'$ より，次のように計算される．

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

### $\mathrm{pow}$

$g = f ^ k$ を満たす $g$ を求める．ただし，$k \gt 0$ および $f_0\neq 0$ を仮定する．$g'=kf^{k-1} f'$ の両辺に $f$ を掛けることで $fg'=kgf'$ が得られるので，以下のように計算される．

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

$k=0$ の場合は，$g\equiv 1$ として計算される．

$k\gt 0$ かつ $f _ 0 = 0$ の場合は，$f = x ^ p \cdot f'\ (f'_0 \neq 0)$ の形に直してから $g = x ^ {pk} f'^ k$  として計算すればよい．そのような $f'$ が存在しない場合，即ち $f\equiv 0$ の場合は $g \equiv 0$ である．

### $\mathrm{sqrt}$

$g ^ 2 = f$ を満たす $g$ を $1$ つ求める (存在しても一意とは限らない)．ただし，$g _ 0 \neq 0$ および $v ^ 2 = f _ 0$ を満たす $v$ (これを $f _ 0 ^ {1/2}$ と書く) が存在することを仮定する．これは，以下のように計算できる．

$$
\begin{aligned}
f _ {n+1} &= \sum _ {i = 0} ^ {n + 1} g _ i g _ {n + 1 - i},\\
2g _ 0 g _ {n + 1} &= f _ {n + 1} - \sum _ {i = 1} ^ {n} g _ i g _ {n + 1 - i},\\
g _ n &= \begin{cases}
f _ 0 ^ {1/2} & \text{if }n = 0\\
\displaystyle \dfrac{1}{2g_0}\left(f _ {n } - \sum _ {i = 1} ^ {n-1} g _ i g _ {n - i}\right) & \text{otherwise}
\end{cases}.
\end{aligned}
$$

$f _ i \neq 0$ となる最小の $i$ が偶数であれば，上式で計算される $g$ に対して $g' = x ^ {i/2} g$ が ${g'} ^ 2 = f$ を満たす．$i$ が奇数であれば，条件を満たす $g$ は存在しない．

### $k$ th root (__未実装__)

$g ^ k = f$ を満たす $g$ を求める．$\mathrm{pow}$ と同様の計算により，次を得る．

$$
g _ n = \begin{cases}
f _ 0 ^ {1/k} & \text{if }n = 0\\
\displaystyle\dfrac{1}{nf_0}\sum _ {i = 0} ^ {n-1} (k^{-1}(n-i)-i)g_i f _{n-i} & \text{otherwise}
\end{cases}
$$

$\mathrm{pow}$ と組み合わせることで，より一般に $g = f ^ {p/q}$ を満たす $g$ を計算できる．
