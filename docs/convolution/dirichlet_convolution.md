---
title: Dirichlet Convolution
documentation_of: //library/convolution/dirichlet_convolution.hpp
---

### dirichlet_convolution

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> dirichlet_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の積で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \times j = k } A _ i \cdot B _ j $$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator*=` が定義されている必要があります．

- 返り値
  
  $A\ast B$

- 制約

  - $0 \leq \vert A \vert, \vert B \vert \leq 10 ^ 6$

- 時間計算量

  $\Theta(N\log N)$

### dirichlet_convolution_coprime

- シグネチャ

  ```cpp
  template <typename T>
  std::vector<T> dirichlet_convolution_coprime(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字の互いに素な積で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { \overset{ \scriptstyle i \times j = k, }{ \gcd (i, j) = 1} } A _ i \cdot B _ j $$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator*=` が定義されている必要があります．

- 返り値
  
  $A\ast B$

- 制約

  - $0 \leq \vert A \vert, \vert B \vert \leq 10 ^ 6$

- 時間計算量

  $\Theta(N\log N)$