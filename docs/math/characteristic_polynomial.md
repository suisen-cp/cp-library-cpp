---
title: Characteristic Polynomial
documentation_of: //library/math/characteristic_polynomial.hpp
---

## Characteristic Polynomial

$N\times N$ 行列 $A$ の特性多項式 $p_A(\lambda) := \det(\lambda E _ N - A)$ を $\Theta(N ^ 3)$ 時間で計算するアルゴリズムの実装です．

### 概要

特性多項式に関する重要な性質として，__相似変換により不変__ ということが挙げられる．

<details>
<summary>証明</summary>

$N\times N$ 行列 $A$ と正則な $N\times N$ 行列 $P$ を任意に取る．任意の $\lambda$ に対して $\det(\lambda E _ N - A) = \det(\lambda E_N - P ^ {-1} A P)$ を示せばよいが，これは次のようにして示される．

$$\begin{aligned}
\det(\lambda E _ N - A)
&= \det(\lambda E_N - A) \det(E _ N) \\
&= \det(\lambda E_N - A) \det(P ^ {-1} P) \\
&= \det(P ^ {-1}) \det(\lambda E_N - A) \det(P) \\
&= \det(P ^ {-1} (\lambda E_N - A) P) \\
&= \det(\lambda E_N - P ^ {-1} A P) \\
\end{aligned}$$

</details>

そこで，$A$ に相似変換を施して特性多項式を求めやすい行列 $B$ を得，代わりに $B$ の特性多項式を計算することを考える．

ここでは，特性多項式を求めやすい行列として __上 Hessenberg 行列__ を用いる．上 Hessenberg 行列とは，以下のような形をした行列をいう．

$$
\begin{bmatrix}
\alpha _ 0 & \ast & \ast & \ast & \ast \\
\beta _ 1  & \alpha _ 1 & \ast & \ast & \ast \\
0 & \beta _ 2 & \alpha _ 2 & \ast & \ast \\
\vdots & \ddots & \ddots & \ddots & \vdots \\
0 & \cdots & 0 & \beta _ {N - 1} & \alpha _ {N - 1}
\end{bmatrix}
$$

$H$ を上 Hessenberg 行列として，$H$ の特性多項式 $p _ H(\lambda)$ は以下に示すアルゴリズムにより $\Theta(N ^ 3)$ 時間で計算できる．

#### 上 Hessenberg 行列 $H$ の特性多項式を計算するアルゴリズム

Reference : https://ipsen.math.ncsu.edu/ps/charpoly3.pdf

__方針__

$H ^ {(k)} := (H _ {i, j}) _ {0 \leq i, j \lt k}$ および $p _ H ^ {(k)} (\lambda) := p _ {H ^ {(k)} }(\lambda)$ と定義する．

多項式の列 $\\\{ p _ H ^ {(k)}\\\} _ {k = 0} ^ N$ に対して成り立つ漸化式を導出することで $k = 0, \ldots, N$ の順に $p _ H ^ {(k)} (\lambda)$ を計算する．$p _ H(\lambda) = p _ H ^ {(N)} (\lambda)$ が求めたい多項式である．

__アルゴリズム__

$N = 0$ の場合は自明なので，$N \gt 0$ を仮定する．

$H$ は以下のように表されるとする．

$$
H =
\begin{bmatrix}
\alpha _ 0 & \ast & \ast & \ast & \ast \\
\beta _ 1  & \alpha _ 1 & \ast & \ast & \ast \\
0 & \beta _ 2 & \alpha _ 2 & \ast & \ast \\
\vdots & \ddots & \ddots & \ddots & \vdots \\
0 & \cdots & 0 & \beta _ {N - 1} & \alpha _ {N - 1}
\end{bmatrix}
$$

まず，明らかに $p _ H ^ {(0)} (\lambda) = 1, \; p _ H ^ {(1)} (\lambda) = \lambda - \alpha _ 0$ である．$k \geq 2$ に対して，$p _ H ^ {(k)}$ を $p _ H ^ {(0)}, \ldots, p _ H ^ {(k - 1)}$ から計算することを考える．

$N\times N$ 行列 $A$ に対して，行列式 $\det(A)$ は次で定義される．ここで，$\mathfrak{S} _ N$ は $N$ 次の置換全体の集合，$\mathrm{sgn}: \mathfrak{S} _ N \to \\\{ -1, +1 \\\}$ は引数の置換 $\sigma$ が偶置換なら $+1$，奇置換なら $-1$ を取る関数である．

$$
\det (A) := \sum _ {\sigma \in \mathfrak{S} _ N} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {N - 1} A _ {i, \sigma(i)}
$$

$p _ H ^ {(k)} (\lambda) = \det (\lambda E _ k - H ^ {(k)})$ を上記の式を用いて計算する．$\sigma (i) = k - 1$ を満たす $i$ によって場合分けをする．

- $\sigma(k - 1) = k - 1$ の場合

  以下が成立する．

  $$\begin{aligned}
  & \sum _ {\sigma \in \{\sigma \in \mathfrak{S} _ k \mid \sigma(k - 1) = k - 1\}} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) \sum _ {\sigma' \in \mathfrak{S} _ {k - 1}} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {k - 2} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma'(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) \sum _ {\sigma' \in \mathfrak{S} _ {k - 1}} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {k - 2} (\lambda E _ {k - 1} - H ^ {(k - 1)}) _ {i, \sigma'(i)} \\
  =\ & (\lambda - \alpha _ {k - 1}) p _ H ^ {(k - 1)}
  \end{aligned}$$

- $\sigma(l) = k - 1,\; l \neq k - 1$ の場合

  $\displaystyle \prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \neq 0$ を満たすためには，全ての $i = l + 1, \ldots, k - 1$ に対して $\sigma(i) = i - 1$ を満たす必要がある．従って，以下が成り立つ．

  $$\begin{aligned}
  & \sum _ {\sigma \in \{\sigma \in \mathfrak{S} _ k \mid \sigma(l) = k - 1\land l \neq k - 1\}} \mathrm{sgn}(\sigma)\prod _ {i = 0} ^ {k - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma(i)} \\
  =\ & \Bigl(-H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} -\beta _ i\Bigr) \cdot (-1) ^ {k - l - 1} \sum _ {\sigma' \in \mathfrak{S} _ l} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {l - 1} (\lambda E _ k - H ^ {(k)}) _ {i, \sigma'(i)} \\
  =\ & -\Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) \sum _ {\sigma' \in \mathfrak{S} _ l} \mathrm{sgn}(\sigma')\prod _ {i = 0} ^ {l - 1} (\lambda E _ l - H ^ {(l)}) _ {i, \sigma'(i)} \\
  =\ & -\Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) p _ H ^ {(l)}
  \end{aligned}$$

以上より，$k\geq 2$ に対して次が成立する．

$$
p _ H ^ {(k)} = (\lambda - \alpha _ {k - 1}) p _ H ^ {(k - 1)} - \sum _ {l = 0} ^ {k - 2} \Bigl(H _ {l, k - 1} \prod _ {i = l + 1} ^ {k - 1} \beta _ i\Bigr) p _ H ^ {(l)}
$$

右辺は $\Theta(N ^ 2)$ 時間で計算できるので，結局全ての $p _ H ^ {(k)}$ を $\Theta(N ^ 3)$ 時間で計算することが出来る．

上 Hessenberg 行列 $H$ の特性多項式を $\Theta(N ^ 3)$ で計算することができたので，あとは任意の $N \times N$ 行列 $A$ を相似変換により上 Hessenberg 行列へと変換することができればよいが，[Hessenberg Reduction](https://suisen-cp.github.io/cp-library-cpp/library/math/hessenberg_reduction.hpp) に示したように，これは $\Theta(N ^ 3)$ 時間で行うことが出来る．
