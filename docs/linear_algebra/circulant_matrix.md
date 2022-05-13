---
title: Circulant Matrix (巡回行列)
documentation_of: //library/linear_algebra/circulant_matrix.hpp
---
## Circulant Matrix (巡回行列)

積を高速に計算できる行列の一種。

列 $a = ( a _ 0 , \ldots , a _ { n - 1 } )$ に対して、$n\times n$ 行列 $\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1})$ を以下で定義すると、これは巡回行列である。

$$
\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1}) \coloneqq (a _ {i - j \bmod n}) _ {0\leq i,j\lt n} =\begin{pmatrix}
a _ 0 & a _ {n - 1} & a _ {n - 3} & \cdots & a _ 1\\
a _ 1 & a _ 0 & a _ {n - 2} & \cdots & a _ 2\\
a _ 2 & a _ 1 & a _ 0 & \cdots & a _ 3\\
\vdots & \vdots & \vdots & \ddots & \vdots \\
a _ {n - 1} & a _ {n - 2} & a _ {n - 3} & \cdots & a _ 0
\end{pmatrix}
$$

$2$ つの巡回行列 $A\coloneqq\mathrm{Cir}(a _ 0, \ldots, a _ {n - 1}),\; B \coloneqq \mathrm{Cir}(b _ 0, \ldots, b _ {n - 1})$ に対して $C\coloneqq AB$ とすれば、次が成り立つ。

$$
C _ {i,j} = \sum _ {k = 0} ^ {n - 1} a _ {i - k \bmod n} b _ {k - j \bmod n} = \sum _ {k+l\equiv i-j\pmod{n}} a _ k b _ l
$$

右辺は $i-j\bmod n$ の値にのみ依存するから、$\displaystyle c _ i \coloneqq \sum _ {k+l\equiv i\pmod{n}} a _ k b _ l$ に対して $C=\mathrm{Cir}(c _ 0, \ldots, c _ {n - 1})$ である。これは、巡回行列の積はまた巡回行列となることを表している。更に、$c$ は $a,b$ の巡回畳み込みであるから、FFT などを用いることで $C$ は $\Theta(n\log n)$ 時間で計算可能である。
