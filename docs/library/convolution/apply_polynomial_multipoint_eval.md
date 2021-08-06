---
title: 列を変数として持つ多項式の評価 (多点評価版)
documentation_of: //library/convolution/apply_polynomial_multipoint_eval.hpp
---

### apply_polynomial

- シグネチャ

  ```cpp
  template <typename mint, template <typename T> class Transform>
  std::vector<mint> apply_polynomial(std::vector<mint> &&a, const FPS<mint> &f) // (1)

  template <typename mint, template <typename T> class Transform>
  std::vector<mint> apply_polynomial(const std::vector<mint> &a, const FPS<mint> &f) // (2)
  ```

- 概要

  列 $A$ を変数に持つ多項式 $\displaystyle f(A)=\sum_{i=0}^{M-1} C_i \cdot A^i$ を評価します．ここで，$A^i$ はある畳み込み演算 $\ast$ に対して以下で定義されるものとします．

  $$ A^i = \underbrace{A \ast A \ast \cdots \ast A}_{i} $$

  また，$\ast$ に対してある可逆な線形変換 $\mathcal{F}$ が存在して，任意の列 $X,Y$ に対して

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

  上式における $\mathcal{F}$ と $\mathcal{F}^{-1}$ による変換を与えるのがテンプレート引数 `Transform` の静的メンバ関数 `Transform<T>::transform` と `Transform<T>::inverse_transform` で，$f(\cdot)$ を評価するのが引数 `f` です．

  このライブラリでは $f(\cdot)$ たちの計算に多点評価のアルゴリズムを用いることで高速化を図ります．従って，引数として与える多項式 $f$ を形式的冪級数型 `FPS` に制限し，値型は `atcoder::modint` であることを想定しています．

- テンプレート引数

  - `mint`: 列の要素の型．`atcoder::modint` 型を想定しています．
  - `Transform`: 列に対して inplace に線形変換 $\mathcal{F}$ を施す `static` 関数 `Transform<T>::transform(std::vector<T>&)` およびその逆変換 $\mathcal{F}^{-1}$ を施す `static` 関数 `Transform<T>::inverse_transform(std::vector<T>&)` を持つクラス．

- 引数

  - `a`: 列 $A$
  - `f`: 多項式 $f$

- 返り値
  
  $f(A)$

- 時間計算量

  列 $A$ の長さを $N$，`Transform<T>::transform` の計算量を $\Theta(f(N))$, `Transform<T>::inverse_transform` の計算量を $\Theta(g(N))$ として，$\Theta(f(N)+g(N)+N (\log N) ^ 2)$ です．

