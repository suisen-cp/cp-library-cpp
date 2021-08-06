---
title: 約数系ゼータ変換・メビウス変換
documentation_of: //library/transform/divisor.hpp
---

### struct DivisorTransform

- シグネチャ

  ```cpp
  template <typename T>
  struct DivisorTransform {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に約数系ゼータ変換を施す関数 `DivisorTransform<T>::transform` およびその逆変換 (メビウス変換) を施す関数 `DivisorTransform<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  1. ゼータ変換 (`DivisorTransform<T>::transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{j \mid i} A_j $$
  
  2. メビウス変換 (`DivisorTransform<T>::inverse_transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{j \mid i} B_j $$
  
  ここで，$j\mid i$ は $j$ が $i$ を割り切ること，言い換えれば $j$ が $i$ の約数であることを表します．

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=` が定義されている必要があります．

- 制約

  - $1\leq N \leq 10^7$

- 時間計算量

  $\Theta(N\log\log N)$

### struct DivisorTransformGeneral

- シグネチャ

  ```cpp
  template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
  struct DivisorTransformGeneral {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  型 `T` に `operator+=`，`operator-=` が定義されていない場合にはこちらを使用します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `AddAssign`: 複合代入演算 `operator+=` に相当する関数の型です．
  - `SubAssign`: 複合代入演算 `operator-=` に相当する関数の型です．
  - `AddAssign add_assign`: `AddAssign` 型のインスタンスです．関数呼び出し `add_assign(T &a, T b)` が意味的に `a += b` と等価であることを期待します．ただし，返り値は捨てられます．
  - `SubAssign sub_assign`: `SubAssign` 型のインスタンスです．関数呼び出し `sub_assign(T &a, T b)` が意味的に `a -= b` と等価であることを期待します．ただし，返り値は捨てられます．
