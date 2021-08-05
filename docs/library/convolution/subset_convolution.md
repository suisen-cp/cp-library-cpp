---
title: Subset Convolution
documentation_of: //library/convolution/subset_convolution.hpp
---

### subset_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> subset_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の直和演算で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．
  $$C_k=\sum_{i\sqcup j=k} A_i\cdot B_j$$
  ここで，$i\sqcup j=k$ は $i\And j=0$ かつ $i\mid j=k$ と等価です．

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - 列 $A$ の長さを $N$，$B$ の長さを $M$ として，ある非負整数 $L$ が存在して $N=M=2^L$ を満たす
     - $0\leq L\leq 20$
  2. - 列 $\mathcal{A}^i$ の長さを $N_i$ として，ある非負整数 $L$ が存在して $N_0=N_1=\cdots=2^L$ を満たす
     - $0\leq L\leq 20$

- 時間計算量

  1. $\Theta(N(\log N)^2)$，あるいは $\Theta(L^2\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N(\log N)^2)$，あるいは $\Theta(K\cdot L^2\cdot 2^L)$
