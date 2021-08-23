---
title: Horn SAT
documentation_of: //library/algorithm/horn_sat.hpp
---

## Horn SAT

以下の形式で表される充足可能性問題を解きます。

$$
\bigwedge_{i} \left(\left(x_{a_{i,1}}\land x_{a_{i,2}}\land\cdots\land x_{a_{i,c_i}}\right)\to y_{b_i}\right)\tag{1}
$$

ここで、$x$ は正リテラルに限ります ($y$ の正負は問いません)。

### コンストラクタ

- シグネチャ

  ```cpp
  HornSAT() // (1)
  HornSAT(int n) // (2)
  ```

- 概要

  論理変数を $n$ 個用意します。(1) は (2) で $n=0$ とした場合と等価です。

- 制約

  - $0\leq n\leq 10^6$

- 時間計算量

  - $O(n)$

### 条件節の追加

- シグネチャ

  ```cpp
  void add_clause(const std::vector<int> &lhs, int rhs, bool val)
  void add_clause(int rhs, bool val)
  ```

- 概要

  式 $(1)$ における $a_i$ と `lhs`、$b_i$ と `rhs` が対応し、`val` は $y$ が負リテラルかどうかを表す `bool` 値です。

  `lhs` を省略すると $a_i$ は空列の場合を、すなわち単項の条件節 $y_{b_i}$ を表します。

- 時間計算量

  $O(\vert a_i\vert)$

### 充足可能性判定

- シグネチャ

  ```cpp
  bool satisfiable()
  ```

- 概要

  今までに与えた条件節たちをすべて満たすような真偽値の割り当て方が存在するかどうかを判定します。内部的には、同時に関数 `answer` の返り値として用いる解を一つ求めます。

- 時間計算量

  条件節の項数の和を $M$ として、$O(N+M)$

### 解の例示

- シグネチャ

  ```cpp
  const std::vector<bool>& answer()
  ```

- 概要

  今までに与えた条件節たちをすべて満たすような真偽値の割り当て方が存在するならば、そのような割り当てを一つ返します。

  __Note__: 必ず先に `satisfiable` を呼んでください。`satisfiable` を呼ばなかった場合、または `satisfiable` を呼んで返り値が `false` だった場合にこのメソッドを呼ぶと assert に引っかかるようになっています。

- 時間計算量

  `satisfiable` 内で解を計算しているので、$O(1)$
  
## 参考

- https://people.eecs.berkeley.edu/~satishr/cs270.06/lecture1.pdf
