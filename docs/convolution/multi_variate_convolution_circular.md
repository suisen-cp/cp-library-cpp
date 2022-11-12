---
title: Multi Variate Convolution Circular (多変数巡回畳み込み)
documentation_of: //library/convolution/multi_variate_convolution_circular.hpp
---
## Multi Variate Convolution Circular (多変数巡回畳み込み)

$\mathbb{Z} / m \mathbb{Z}$ 上の多変数の多項式 $f(x _ 1, \ldots, x _ k), g(x _ 1, \ldots, x _ k)$ の巡回畳み込み $fg \bmod (1 - x ^ {n _ 1}, \ldots, 1 - x ^ {n _ k})$ を計算する。

## 概要

多次元 FFT -> 各点積 -> 多次元 IFFT で求めたいが、各次元で次数を 2 冪まで伸ばしてしまうと最悪の場合 $\Omega(2 ^ k N \log N)$ 時間となる。ここで、$N:=\prod _ {i = 1} ^ k n _ i$ である。

次数 $n _ i$ のまま FFT ができればこのようなことを回避できるが、これは $(\mathbb{Z} / m \mathbb{Z}) ^ \ast$ における位数 $n _ i$ の元 ($n _ i$ 乗根) が存在するならば [chirp z-transform](https://suisen-cp.github.io/cp-library-cpp/library/transform/chirp_z_transform.hpp) を用いることで実現される (FFT は等比数列を評価点とする多点評価と見ることができる)。

もし $m$ が素数であり、かつ全ての $i$ に対して $n _ i \mid (m - 1)$ が成り立つならば、原始根 $g$ が存在して $g ^ {(p - 1) / n _ i}$ は位数 $n _ i$ の元であり、上述の方法を適用できる。この場合の計算量は $\Theta(N \log N)$ 時間 (原始根の計算時間は除く) となる。

一般の $m$ に対しては、$\forall i. n _ i \mid (p - 1)$ を満たす大きな素数 $p$ をいくつか選んでそれぞれで畳みこんだ後に [Garner's Algorithm](https://suisen-cp.github.io/cp-library-cpp/library/number/garner.hpp) で復元すればよい。$p$ としては $L := \mathrm{lcm}(n _ 1, \ldots, n _ k)$ として $kL + 1$ と表される素数であればよい。以下の実装では $k$ を適当に探索しているが、実用上は比較的短時間で必要な分だけ選ぶことができている。(素数が偏りなく $1/\log$ の割合で存在していると仮定すると $1$ 個見つけるまでの試行回数の期待値が $\log$ くらいなので良さそう？実装では乱択ではなく $k$ の大きい順に試しているので怪しいかも)
