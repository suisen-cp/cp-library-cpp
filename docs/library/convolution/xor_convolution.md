---
title: Bitwise Xor Convolution
documentation_of: //library/convolution/xor_convolution.hpp
---

### xor_convolution

- シグネチャ

  ```cpp
  template <
      typename T,
      auto add = default_operator::add<T>,
      auto sub = default_operator::sub<T>,
      auto mul = default_operator::mul<T>,
      auto div = default_operator::div<T>
  >
  std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b)

  template <
      typename T,
      auto add = default_operator::add<T>,
      auto sub = default_operator::sub<T>,
      auto mul = default_operator::mul<T>,
      auto inv = default_operator::inv<T>
  >
  std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b)
  ```

- 概要

  長さ $N=2^L$ の列 $(A_0,A_1,\ldots,A_{N-1})$ および $(B_0,B_1,\ldots,B_{N-1})$ を添字 bitwise xor で畳み込みます．即ち，長さ $N$ の列 $(C_0,C_1,\ldots,C_{N-1})$ であって，各 $k=0,\ldots,N-1$ に対して以下を満たす列を計算します．

  $$ C _ k = \sum _ { i \oplus j = k } A _ i \cdot B _ j $$

  以下，この畳み込みを $C=A\ast B$ と表記します．

- テンプレート引数

  - `T`: 列の要素の型．
  - `add`: 二項演算 (加算)．デフォルトでは `operator+` が呼ばれるようになっています．
  - `sub`: 二項演算 (減算)．デフォルトでは `operator-` が呼ばれるようになっています．
  - `mul`: 二項演算 (乗算)．デフォルトでは `operator*` が呼ばれるようになっています．
  - `div`: 二項演算 (除算)．デフォルトでは `operator/` が呼ばれるようになっています．
  - `inv`: 単項演算 (乗法逆元)．デフォルトでは `x` に対して `T{1}/x` と計算されます．

  内部で用いている Walsh Hadamard 変換が原因で実装が 2 通りに分かれています．詳しくは [Walsh Hadamard 変換](https://suisen-cp.github.io/cp-library-cpp/library/transform/walsh_hadamard.hpp) のページを参照してください．

- 返り値
  
  $A\ast B$

- 制約

  - ある非負整数 $L$ が存在して $\vert A \vert=\vert B \vert= 2 ^ L$ を満たす
  - $0\leq L\leq 20$

- 時間計算量

  $\Theta(N\log N)$，あるいは $\Theta(L\cdot 2^L)$