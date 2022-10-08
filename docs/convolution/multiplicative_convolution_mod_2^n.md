---
title: Multiplicative Convolution Mod 2^n ($c_k = \sum_{i\times j \equiv k \pmod{2 ^ n}} a_i \cdot b_j$)
documentation_of: //library/convolution/multiplicative_convolution_mod_2^n.hpp
---
## Multiplicative Convolution Mod 2^n

列 $A=(a _ 0, a _ 1, \ldots, a _ {2 ^ n - 1}), B = (b _ 0, b _ 1, \ldots, b _ {2 ^ n - 1})$ に対して以下で定義される列 $C=(c _ 0, c _ 1, \ldots, c _ {2 ^ n - 1})$ を $\Theta(n 2 ^ n)$ 時間で計算する。

$$c _ k = \sum _ {i\times j \equiv k \pmod{2 ^ n}} a _ i b _ j.$$

実は、$n \geq 3$ を仮定すると、$(\Z/2 ^ n\Z) ^ \ast$ において $\mathrm{ord}(5) = 2 ^ {n - 2}$ が成り立つ $(\star)$。

<details>

<summary>証明</summary>

$(\Z/2 ^ n\Z) ^ \ast$ の位数は $\varphi(2 ^ n) = 2 ^ {n - 1}$ であるから、$\mathrm{ord}(5) \mid 2 ^ {n - 1}$ である。従って、$\mathrm{ord}(5) = 2 ^ {n - 2}$ を示すには以下の $(1), (2)$ を代わりに示せば十分。

$$5 ^ {2 ^ {n - 3}} \not\equiv 1 \pmod{2 ^ n}, \tag{1}$$
$$5 ^ {2 ^ {n - 2}} \equiv 1 \pmod{2 ^ n}.     \tag{2}$$

- $(1)$ の証明

  以下、$2$ が正整数 $k$ を割り切る回数を $v_2(k)$ と書く。
  
  $$5 ^ {2 ^ {n - 3}} = (1 + 4) ^ {2 ^ {n - 3}} = 1 + 2 ^ {n - 1} + \sum _ {i = 2} ^ {2 ^ {n - 3}} \binom{2 ^ {n - 3}}{i} 2 ^ {2i}$$

  であり、$\displaystyle v_2(i!) = \sum _ {j = 1} ^ \infty \left\lfloor\dfrac{i}{2 ^ j}\right\rfloor \leq \sum _ {j = 1} ^ \infty \dfrac{i}{2 ^ j} \leq i$ を満たすので、$i\geq 3$ において $\displaystyle v_2\left(\binom{2 ^ {n - 3}}{i} 2 ^ {2i}\right)\geq n-3+i\geq n$ が成り立つ。また、実際に計算することで $i=2$ の場合もこれが成り立つことが分かる。従って、次を得る:

  $$5 ^ {2 ^ {n - 3}} \equiv 1 + 2 ^ {n - 1} \not\equiv 1 \pmod{2 ^ n}.$$

- $(2)$ の証明

  $$5 ^ {2 ^ {n - 2}} = (1 + 4) ^ {2 ^ {n - 2}} = 1 +  \sum _ {i = 1} ^ {2 ^ {n - 2}} \binom{2 ^ {n - 2}}{i} 2 ^ {2i}$$

  に対して同様の議論により $i\geq 1$ で $\displaystyle v_2\left(\binom{2 ^ {n - 2}}{i} 2 ^ {2i}\right)\geq n$ が成り立つことが分かり、次を得る:

  $$5 ^ {2 ^ {n - 2}} \equiv 1 \pmod{2 ^ n}.$$

</details>

$n \leq 2$ では $\mathrm{ord}(5) = 1$ であるから、結局 $\mathrm{ord}(5) = 2 ^ {\max(n - 2, 0)}$ となる。

以下、$n \geq 3$ を仮定する。

$(\star)$ より、$5$ によって生成される部分群 $\langle 5 \rangle = \lbrace 5 ^ n \mid n \in \Z \rbrace$ の位数は $2 ^ {n - 2}$ である。簡単な計算により $a \in \langle 5 \rangle \Rightarrow a \equiv 1 \pmod{4}$ が分かるが、$a \equiv 1 \pmod{4}$ を満たす $a\in (\Z/2 ^ n\Z) ^ \ast$ の個数はちょうど $2 ^ {n - 2}$ であるから、$\langle 5 \rangle=\lbrace4k+1 \mid k\in \Z\rbrace$ である。同様にして、$\langle -5\rangle = \lbrace4k-1 \mid k\in \Z\rbrace$ も分かる。

以上より、任意の $a\in \Z/2^n\Z$ に対して $a \equiv (-1) ^ {s _ a} \cdot 2 ^ {p _ a} \cdot 5 ^ {q _ a}$ を満たす整数 $s _ a, p _ a, q _ a$ が存在する。そこで、$a = (s _ a, p _ a, q _ a)$ と書くことにすると、$a\in \Z/2^n\Z$ 上の乗算 $a\times b$ は次のように指数の加算へと変換される。

$$a\times b = (s _ a + s _ b, p _ a + p _ b, q _ a + q _ b)$$

さて、$a\in \Z/2 ^ n\Z$ に対して、$a\equiv 0$ の場合を除いて $p_a$ は一意に定まり、$0$ 以上 $n-1$ 以下の値をとる。ここでは、$0$ については $0=(0, n, 0)$ と扱うことにする。

$P _ x := \lbrace i \in \Z/2 ^ n\Z \mid p _ i = x \rbrace$ として、列 $C ^ {x,y} = (c ^ {x, y} _ 0, c ^ {x, y} _ 1, \ldots, c ^ {x, y} _ {2 ^ n - 1})$ を以下で定義する。

$$
c ^ {x, y} _ k = \sum _ {\overset{\scriptsize i \in P _ x, j \in P _ y,}{i \times j \equiv k \pmod{2 ^ n}}} a _ i b _ j
$$

このとき、$\displaystyle C = \sum _ {x = 0} ^ n \sum _ {y = 0} ^ n C ^ {x, y}$ が成り立つ。以降、$C ^ {x, y}$ の計算を考える。

$x,y$ を固定すると、$i\in P _ x, j \in P _ y$ に対して $p _ {i \times j} = \min(n, x+y)=:p$ は一定の値を取る。従って、$i \times j$ の値を追うにあたって必要な情報は $s _ i, q _ i, s _ j, q _ j$ の値のみである。$s$ は $-1$ の指数であるから、$\bmod\; 2$ で同一視してよい。$q$ に関しては、

$$
2 ^ p 5 ^ q \equiv 2 ^ p 5 ^ {q'} \pmod{2 ^ n} \iff 5 ^ q \equiv 5 ^ {q'} \pmod{2 ^ {n - p}}
$$

より $l _ p :=\max(n - p - 2, 0)$ として $\bmod\; 2 ^ {l _ p}$ で同一視してよい。即ち、$2 \times 2 ^ {l _ p}$ の $2$ 次元 FFT により $C ^ {x, y}$ を $\Theta(l _ p \cdot 2 ^ {l _ p})$ 時間で計算できる。ただし、畳み込みに用いる列を元の $A$ や $B$ から計算すると $\Theta(l _ p \cdot 2 ^ {l _ p} + 2 ^ n)$ となってしまうため、組 $(x,y)$ を適切な順番で走査して差分更新を行う必要がある。

計算量を考える。$x + y \geq n - 2$ の各ケースは $\Theta(1)$ で処理できるので、全体への寄与は $\Theta(n ^ 2)$ である。$x + y \lt n - 2$ の場合については $l _ p = n - 2 - (x + y)$ なので、(定数倍を無視して見積もると) 次のように抑えられる。

$$
\sum _ {z = 0} ^ {n - 3} \sum _ {x + y = z} (n - 2 - z) 2 ^ {n - 2 - z} \leq \sum _ {z = 0} ^ {n - 3} (z + 1) (n - 2 - z) 2 ^ {n - 2 - z} = \Theta(n\cdot 2 ^ n)
$$

以上で、全体 $\Theta(n 2 ^ n)$ 時間で動作するアルゴリズムが構築できた。

## 参考

- https://twitter.com/maspy_stars/status/1447511544053469187
- https://twitter.com/tatyam_prime/status/1447533034396217354
