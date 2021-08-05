---
title: Bitwise And Convolution
documentation_of: //library/convolution/and_convolution.hpp
---

### and_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> and_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> and_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字 bitwise and で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \And j = k } A _ i \cdot B _ j $$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
     - $0\leq L\leq 20$
  2. - ある非負整数 $L$ が存在して $\vert\mathcal{A}^0\vert=\vert\mathcal{A}^1\vert=\cdots=2^L$ を満たす
     - $0\leq L\leq 20$

- 時間計算量

  1. $\Theta(N\log N)$，あるいは $\Theta(L\cdot 2^L)$
  2. 列の数を $K$ として，$\Theta(K\cdot N\log N)$，あるいは $\Theta(K\cdot L\cdot 2^L)$
