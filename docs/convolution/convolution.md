---
title: Convolution
documentation_of: //library/convolution/convolution.hpp
---

### transform_convolution

- シグネチャ

  ```cpp
  template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
  std::vector<T> transform_convolution(std::vector<T> a, std::vector<T> b) // (1)
  template <typename T, auto transform, auto inv_transform, auto mul = default_operator::mul<T>>
  std::vector<T> transform_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \oplus j = k } A _ i \cdot B _ j $$

  ここで，$\oplus$ は $\mathbb{Z}$ 上の二項演算です．
  
  この関数は $\odot$ を列の各点積を取る演算として，$\mathcal{F}[A]\odot \mathcal{F}[B]=\mathcal{F}[C]$ を満たす変換行列 $\mathcal{F}$ とその逆行列 $\mathcal{F}^{-1}$ が存在することが必要であり，この条件の下で $C=\mathcal{F}^{-1}\left[\mathcal{F}[A]\odot \mathcal{F}[B]\right]$ として畳み込みを計算します．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を作用させる関数
  - `transform_inv`: 列に対して inplace に線形変換 $\mathcal{F}^{-1}$ を作用させる関数
  - `mul`: 各点積 $\odot$ を計算するための `T` 上の乗算．デフォルトでは `operator*` が呼ばれるようになっています．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 時間計算量

  `transform` の計算量を $\Theta(f(N))$, `transform_inv` の計算量を $\Theta(g(N))$ として

  1. $\Theta(f(N)+g(N))$
  2. 列の数を $K$ として，$\Theta(K\cdot(f(N)+g(N)))$
