---
title: 上位集合に対する高速ゼータ変換・高速メビウス変換
documentation_of: //library/transform/supset.hpp
---

### struct SupsetTransform

- シグネチャ

  ```cpp
  template <typename T>
  struct SupsetTransform {
      static void transform(std::vector<T> &a)
      static void inverse_transform(std::vector<T> &a)
  };
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0=0,A_1,\ldots,A_{N-1})$ に上位集合版のゼータ変換を施す関数 `SupsetTransform<T>::transform` およびその逆変換 (メビウス変換) を施す関数 `SupsetTransform<T>::inverse_transform` を提供します．各変換は inplace に行われ，引数として渡した列は書き換えられます．

  ゼータ変換 (`SupsetTransform<T>::transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ B_i = \sum_{i\subseteq j} A_j $$
  
  メビウス変換 (`SupsetTransform<T>::inverse_transform`) では，引数として与えた列 $A$ に対して，以下を満たす列 $B$ を計算します．

    $$ A_i = \sum_{i\subseteq j} B_j $$

- テンプレート引数

  - `T`: 列の要素の型．`operator+=`，`operator-=` が定義されている必要があります．

- 制約

  - ある非負整数 $L$ が存在して，$\vert A\vert = 2 ^ L$
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$

### struct SupsetTransformGeneral

- シグネチャ

  ```cpp
  template <typename T, typename AddAssign, typename SubAssign, AddAssign add_assign, SubAssign sub_assign>
  struct SupsetTransformGeneral {
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
