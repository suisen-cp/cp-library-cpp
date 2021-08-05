---
title: GCD Convolution
documentation_of: //library/convolution/gcd_convolution.hpp
---

### gcd_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> gcd_convolution(std::vector<T> a, std::vector<T> b) // (1)

  template <typename T>
  std::vector<T> gcd_convolution(std::vector<std::vector<T>> a) // (2)
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ および $(B_0=0,B_1,\ldots,B_{N-1})$ を添字 gcd で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=1,\ldots,2^N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { \gcd (i, j) = k } A _ i \cdot B _ j $$

  __ここで，$A_0=0$ かつ $B_0=0$ であることが要求されます__．
  
  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=`，`operator*=` が定義されている必要があります．

- 返り値
  
  1. $A\ast B$
  2. $\mathcal{A}^0\ast \mathcal{A}^1\ast \cdots$ (ここで，$\mathcal{A}^i$ は列 $(A_0^i,\ldots,A_{N-1}^i)$ を表す)

- 制約

  1. - $\vert A\vert =\vert B\vert$
     - $A_0=B_0=0$
  2. - $\vert \mathcal{A} ^ i\vert$ は全て等しい
     - $\forall i.\; \mathcal{A} ^ i _ 0 = 0$

- 時間計算量

  1. $\Theta(N\log\log N)$
  2. 列の数を $K$ として，$\Theta(K\cdot N\log\log N)$
