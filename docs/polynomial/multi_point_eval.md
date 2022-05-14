---
title: Multi Point Evaluation
documentation_of: //library/polynomial/multi_point_eval.hpp
---
## Multi Point Evaluation

多項式 $f(x)$ に対して、$f(t _ 0), \ldots, f(t _ {N - 1})$ の値を求める。

## アルゴリズム

任意の $t$ に対して、$f(t) = f(x) \bmod (x - t)$ が成り立つ。

<details>
<summary>証明</summary>

(多項式としての除算で) $f(x)$ を $x - t$ で割った商を $Q _ t(x)$, 余りを $R _ t$ とすると、以下が成り立つ。

$$f(x) = Q _ t(x) (x - t _ i) + R _ t.$$

$x = t$ を代入することで、次を得る。

$$f(t) = Q _ t(t) (t - t) + R _ t = R _ t.$$

$R _ t = f(x) \bmod (x - t)$ であるから、示された。(証明終)

</details>

$0\leq l\lt r\lt N$ を満たす整数 $l, r$ に対して、(多項式としての除算で) $f(x)$ を $\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ で割った商を $Q _ {l, r}(x)$, 余りを $R _ {l, r}(x)$ とおく。求めたいのは、全ての $i=0,\ldots,N-1$ に対する $R _ {i, i + 1}(x)$ である。

$l\leq m \leq r$ を満たす任意の整数 $m$ に対して、

$$\begin{aligned}
f(x)
&= Q _ {l, r}(x) (x - t _ l) \cdots (x - t _ {m - 1}) (x - t _ m) \cdots (x - t _ {r - 1}) + R _ {l, r}(x) \\
&= Q _ {l, m}(x) (x - t _ l) \cdots (x - t _ {m - 1})                                      + R _ {l, m}(x) \\
&= Q _ {m, r}(x)                                      (x - t _ m) \cdots (x - t _ {r - 1}) + R _ {m, r}(x).
\end{aligned}$$

より、次が成り立つ。

$$\begin{aligned}
R _ {l, m}(x) &= R _ {l, r}(x) \bmod ((x - t _ l) \cdots (x - t _ {m - 1})), \\
R _ {m, r}(x) &= R _ {l, r}(x) \bmod ((x - t _ m) \cdots (x - t _ {r - 1})). \\
\end{aligned}$$

従って、$R _ {0, N}(x) = f(x) \bmod ((x - t _ 0) \cdots (x - t _ {N - 1}))$ から始めて再帰的に計算することで、全ての $i=0,\ldots,N-1$ に対する $R _ {i, i + 1}(x)$ を求めることが出来る。

必要な $\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ が既に得られていると仮定する。$m = \left\lfloor \dfrac{l + r}{2} \right\rfloor$ として再帰することにすれば、再帰の部分の時間計算量は 

$$T(N) = \begin{cases} 2T(N / 2) + \Theta(N \log N) & \text{if}\ N \gt 1 \\ O(1) & \text{otherwise} \end{cases}$$

を満たす $T$ を用いて $\Theta(T(N))$ と書ける。$T(N) = \Theta(N (\log N) ^ 2)$ である (★) から、この部分の時間計算量は $\Theta(N (\log N) ^ 2)$ である。

<details>
<summary> (★) の補足 </summary>

http://homepages.math.uic.edu/~leon/cs-mcs401-s08/handouts/extended_master_theorem.pdf の $(3')$ で $a = b = 2, \alpha = 1$ とすることで、$T(N) = \Theta(N (\log N) ^ 2)$ を得る。(補足終)

</details>

$\displaystyle \prod _ {i = l} ^ {r - 1} (x - t _ i)$ に関しては、再帰の終端から根に向かって求めることで全体 $\Theta(N (\log N) ^ 2)$ 時間で計算可能である (マージテク)。

$R _ {0, N}(x)$ は $\Theta((d + N) \log (d + N))$ 時間で計算可能である。ここで、$d$ は $f$ の次数である。

結局、全体 $\Theta(N (\log N) ^ 2 + (d + N) \log (d + N))$ 時間でこのアルゴリズムは動作する。
