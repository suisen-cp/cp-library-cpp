---
title: クロネッカー冪による線形変換 (仮称)
documentation_of: //library/transform/kronecker_power.hpp
---

### kronecker_power_transform

- シグネチャ

  ```cpp
  template <typename T, std::size_t D, auto unit_transform>
  void kronecker_power_transform(std::vector<T> &x) // (1)

  template <typename T, typename UnitTransform>
  void kronecker_power_transform(std::vector<T> &x, const std::size_t D, UnitTransform unit_transform) // (2)

  template <typename T, auto e = default_operator::zero<T>, auto add = default_operator::add<T>, auto mul = default_operator::mul<T>>
  void kronecker_power_transform(std::vector<T> &x, const std::vector<std::vector<T>> &A) // (3)
  ```

- 概要

  $D \times D$ 行列 $A$ のクロネッカー積における $N$ 乗 $A ^ {\otimes N}$ と $D ^ N$ 次元ベクトル $x$ の積を inplace に $\Theta ( N \cdot D ^ N )$ 時間で計算する。

  ゼータ変換・メビウス変換・アダマール変換らはこの具体例であり、以下のように対応付けられる。

  - 上位集合版のゼータ変換
  
    $D=2,A=\begin{pmatrix} 1 & 1 \\\\\\\\ 0 & 1 \end{pmatrix}$
  
  - 上位集合版のメビウス変換

    $D=2,A=\begin{pmatrix} 1 & -1 \\\\\\\\ 0 & 1 \end{pmatrix}$

  - 下位集合版のゼータ変換
  
    $D=2,A=\begin{pmatrix} 1 & 0 \\\\\\\\ 1 & 1 \end{pmatrix}$

  - 下位集合版のメビウス変換

    $D=2,A=\begin{pmatrix} 1 & 0 \\\\\\\\ -1 & 1 \end{pmatrix}$

  - アダマール変換

    $D=2,A=\begin{pmatrix} 1 & 1 \\\\\\\\ 1 & -1 \end{pmatrix}$

  これらは全て $D=2$ の例であるが、例えば $3$ 進ゼータ変換は $D=3,A=\begin{pmatrix} 1 & 0 & 0 \\\\\\\\ 1 & 1 & 0 \\\\\\\\ 1 & 1 & 1 \end{pmatrix}$、メビウス変換は $D=3,A=\begin{pmatrix} 1 & 0 & 0 \\\\\\\\ -1 & 1 & 0 \\\\\\\\ 0 & -1 & 1 \end{pmatrix}$ となる (はず)。

- 使い方

  1. $D$ の値がコンパイル時に分かっている場合はこれを用いるのがパフォーマンス的に最適 (なはず)。テンプレート引数 `unit_transform` は引数に $x _ 1,\ldots, x _ D$ を $A x$ に置き換える関数である。具体的には、$D$ 個の参照 `T &x1, ..., T &xD` を引数に取る関数で、各 $i = 1, \ldots, D$ に対して $x_i \leftarrow (Ax)_i$ という代入が行われなければならない。返り値は捨てられる。
  2. $D$ の値がコンパイル時に分からない場合であって、行列積をそのまま計算すると無駄が多い場合はこれを用いる。`unit_transform` はサイズ `D` の `vector<T> &` を受け取り、1 と同様に中身を $Ax$ で置き換える必要がある。
  3. $D$ の値がコンパイル時に分からない場合であって、行列をそのまま与えてしまいたい場合はこれを用いる。加算や乗算、加法単位元をテンプレート引数に渡すことができる。デフォルトでは加算は `operator+`、乗算は `operator*`、加法単位元は `T{0}` として扱われる。

- 返り値

  1, 2, 3 ともに無し。変換は inplace に行われる。

- 制約

  - 引数 `x` のサイズ $L$ に対してある非負整数 $N$ が存在して $L=D^N$ を満たす。

- 時間計算量

  $\Theta(N\cdot D ^ N)$
