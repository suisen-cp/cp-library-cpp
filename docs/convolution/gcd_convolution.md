---
title: GCD Convolution
documentation_of: //library/convolution/gcd_convolution.hpp
---

### gcd_convolution

- シグネチャ

  ```cpp
  template <
      typename T,
      auto add = default_operator::add<T>,
      auto sub = default_operator::sub<T>,
      auto mul = default_operator::mul<T>
  >
  std::vector<T> gcd_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ および $(B_0=0,B_1,\ldots,B_{N-1})$ を添字 gcd で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { \gcd (i, j) = k } A _ i \cdot B _ j $$

  __ここで，$A_0=0$ かつ $B_0=0$ であることが要求されます__．
  
  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．
  - `mul`: 二項演算 (乗算)．デフォルトでは `operator*` が呼ばれるようになっています．

- 返り値
  
  $A\ast B$

- 制約

  - $\vert A\vert =\vert B\vert$
  - $A_0=B_0=0$

- 時間計算量

  $\Theta(N\log\log N)$
