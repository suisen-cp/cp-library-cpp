---
title: Walsh Hadamard 変換
documentation_of: //library/transform/walsh_hadamard.hpp
---

- シグネチャ

  ```cpp
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>>
  void walsh_hadamard_transform(std::vector<T>&)
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto div = default_operator::div<T>>
  void walsh_walsh_hadamard_transform_inv(std::vector<T>&) // std::is_integral_v<T> が true となる型
  template <typename T, auto add = default_operator::add<T>, auto sub = default_operator::sub<T>, auto mul = default_operator::mul<T>, auto inv = default_operator::inv<T>>
  void walsh_hadamard_transform_inv(std::vector<T>&) // std::is_integral_v<T> が false となる型
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に [アダマール変換](https://ja.wikipedia.org/wiki/%E3%82%A2%E3%83%80%E3%83%9E%E3%83%BC%E3%83%AB%E5%A4%89%E6%8F%9B) を施す関数 `walsh_hadamard_transform` およびその逆変換を施す関数 `walsh_walsh_hadamard_transform_inv` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．
  - `mul`: 二項演算 (乗算)．デフォルトでは `operator*` が呼ばれるようになっています．
  - `div`: 二項演算 (除算)．デフォルトでは `operator/` が呼ばれるようになっています．
  - `inv`: 単項演算 (乗法逆元)．デフォルトでは `x` に対して `T{1}/x` と計算されます．

  `walsh_walsh_hadamard_transform_inv` に関して，`T` が `int` や `long long` などの型に対しては除算 `div` が要求され，`double` や `atcoder::modint` などの型に対しては乗法逆元 `inv` および乗算 `mul` が要求されます (あとで設計を見直す可能性が高いです)．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$
