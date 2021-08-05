---
title: Convolution
documentation_of: //library/convolution/convolution.hpp
---

### convolution

- シグネチャ

  ```cpp
  template <typename T, template <typename> class Transform>
  struct Convolution {
      std::vector<T> convolution(std::vector<T> a, std::vector<T> b) // (1)
      std::vector<T> convolution(std::vector<std::vector<T>> a) // (2)
  }
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．
  $$C_k=\sum_{i\oplus j=k} A_i\cdot B_j$$
  ここで，$\oplus$ は $\mathbb{Z}$ 上の二項演算です．
  
  $\odot$ を列の各点積を取る演算として，$\mathcal{F}[A]\odot \mathcal{F}[B]=\mathcal{F}[C]$ を満たす線形変換 $\mathcal{F}$ とその逆変換 $\mathcal{F}^{-1}$ を計算する静的関数を持つ `Transform` クラスをテンプレート引数に取ります．

  ここでは，上記の $\mathcal{F}$ および $\mathcal{F}^{-1}$ を用いて $C$ を次のように計算します．

  $$\mathcal{F}^{-1}\left[\mathcal{F}[A]\odot \mathcal{F}[B]\right]=C$$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator*=` が定義されている必要があります．
  - `Transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を施す `static` 関数 `Transform<T>::transform(std::vector<T>&)` およびその逆変換 $\mathcal{F}^{-1}$ を施す `static` 関数 `Transform<T>::inverse_transform(std::vector<T>&)` を持つクラスです．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 時間計算量

  ここでは，`Transform<T>::transform` の計算量を $\Theta(f(N))$, `Transform<T>::inverse_transform` の計算量を $\Theta(g(N))$ とします．

  1. $\Theta(f(N)+g(N))$
  2. 列の数を $K$ として，$\Theta(K\cdot(f(N)+g(N)))$
