---
title: 上位集合に対する高速ゼータ変換・高速メビウス変換
documentation_of: //library/transform/supset.hpp
---

- シグネチャ

  ```cpp
  template <typename T, auto add = default_operator::add<T>>
  void zeta(std::vector<T> &a)
  template <typename T, auto sub = default_operator::sub<T>>
  void mobius(std::vector<T> &a)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に上位集合版のゼータ変換を施す関数 `zeta` およびその逆変換 (メビウス変換) を施す関数 `mobius` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  ゼータ変換では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{i\subseteq j} A_j $$
  
  メビウス変換では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{i\subseteq j} B_j $$

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$
