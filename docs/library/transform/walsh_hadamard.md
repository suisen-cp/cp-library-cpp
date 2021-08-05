---
title: Walsh Hadamard 変換
documentation_of: //library/transform/walsh_hadamard.hpp
---

### struct WalshHadamard

- シグネチャ

  ```cpp
  template <typename T>
  struct WalshHadamard {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に [アダマール変換](https://ja.wikipedia.org/wiki/%E3%82%A2%E3%83%80%E3%83%9E%E3%83%BC%E3%83%AB%E5%A4%89%E6%8F%9B) を施す関数 `WalshHadamard<T>::transform` およびその逆変換を施す関数 `WalshHadamard<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

- テンプレート引数

  - `T`: 列の要素の型．`operator+`，`operator-`，`operator*=` が定義されている必要があります．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$
