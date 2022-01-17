---
title: 列を変数として持つ多項式の評価
documentation_of: //library/convolution/polynomial_eval.hpp
---

### polynomial_eval

- シグネチャ

  ```cpp
  template <typename T, auto transform, auto transform_inv, typename F>
  std::vector<T> polynomial_eval(std::vector<T> &&a, F f) // (1)

  template <typename T, auto transform, auto transform_inv, typename F>
  std::vector<T> polynomial_eval(const std::vector<T> &a, F f) // (2)
  ```

- 概要

  列 $A$ を変数に持つ多項式 $\displaystyle f(A)=\sum_{i=0}^{M-1} C_i \cdot A^i$ を評価します．ここで，$A^i$ はある畳み込み演算 $\ast$ に対して以下で定義されるものとします．

  $$ A^i = \underbrace{A \ast A \ast \cdots \ast A}_{i} $$

  また，$\ast$ に対してある正則な変換行列 $\mathcal{F}$ が存在して，任意の列 $X,Y$ に対して

  $$ \mathcal{F}[X] \odot \mathcal{F}[Y]=\mathcal{F}[X\ast Y]$$

  を満たす必要があります．ここで，$\odot$ は各点積をとる演算です．このとき，$f(A)$ は次のように計算されます．

  $$\begin{aligned}
  f(A)
  &=\mathcal{F}^{-1}\left[\sum_{i=0}^{M-1}C_i\cdot \left(\underbrace{\mathcal{F}[A]\odot\cdots\odot\mathcal{F}[A]}_{i}\right)\right]\\
  &=\mathcal{F}^{-1}\left[\begin{pmatrix}
  f(\mathcal{F}[A]_0)\\
  f(\mathcal{F}[A]_1)\\
  \vdots\\
  f(\mathcal{F}[A]_{\vert A\vert-1})\\
  \end{pmatrix}\right]
  \end{aligned}$$

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `transform` および `transform_inv` であり，$f(\cdot)$ を評価するのが引数 `f` です．

- テンプレート引数

  - `T`: 列の要素の型．
  - `transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を施す関数
  - `transform_inv`: 逆変換 $\mathcal{F}^{-1}$ を施す関数
  - `F`: `T` 型の要素 $x$ に対して $\displaystyle f(x)=\sum_{i=0}^{N-1}C_i \cdot x^i$ を計算する関数の型です．`F` 型のインスタンス `f` は `x` を引数に取る関数呼び出し `f(x)` によって $f(x)$ を計算できなければなりません．

- 引数

  - `a`: 列 $A$
  - `f`: $f(x)$ を評価する関数

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`transform` の計算量を $\Theta(f(N))$, `transform_inv` の計算量を $\Theta(g(N))$，`f` の計算量を $O(h(M))$ として，$\Theta(f(N)+g(N)+N\cdot h(M))$ です．

<!--

- テンプレート引数 `Transform` について

  典型的な畳み込み演算に対応する `Transform` の例を挙げます．

  1. bitwise and convolution

      [上位集合に対する高速ゼータ変換・高速メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/supset.hpp)
  2. bitwise or convolution

      [下位集合に対する高速ゼータ変換・高速メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/subset.hpp)
  3. bitwise xor convolution

      [Walsh Hadamard 変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/walsh_hadamard.hpp)
  4. gcd convolution

      [倍数系ゼータ変換・メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/multiple.hpp)
  5. lcm convolution

      [約数系ゼータ変換・メビウス変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/divisor.hpp)

-->
