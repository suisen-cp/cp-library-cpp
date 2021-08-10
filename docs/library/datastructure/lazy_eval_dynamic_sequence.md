---
title: 反転可能な遅延評価付き平衡二分探索木
documentation_of: //library/datastructure/lazy_eval_dynamic_sequence.hpp
---

### コンストラクタ

- シグネチャ

  ```cpp
  template <typename T, T (*e)(), T(*op)(T, T), typename F, F(*id)(), T(*mapping)(F, T), F(*composition)(F, F)>
  LazyEvalDynamicSequence()
  ```

- 概要

  空の列で初期化します．

  以下で用いる表記について先に説明しておきます．

  - $T$ 上の二項演算 $\mathrm{op}(x,y)$ を $x\cdot y$ と書きます
  - $F$ 上の二項演算 $\mathrm{composition}(f,g)$ を $f\circ g$ と書きます
  - $f\in F:T\to T$ を $x\in T$ に作用させる演算 $\mathrm{mapping}(f,x)$ を $f(x)$ と書きます

- テンプレート引数 (`<atcoder/lazysegtree>` と同じです)

  - `T`: 列の要素の型
  - `T (*e)()`: モノイド $(T,\cdot)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)
  - `T(*op)(T, T)`: 二項演算 $\cdot$
  - `F`: 区間作用の作用素型
  - `F (*id)()`: モノイド $(F,\circ)$ の単位元を生成する関数 (区間反転を用いる場合は，可換モノイド)
  - `T(*mapping)(F, T)`: 一点作用の関数
  - `F(*composition)(F, F)`: 二項演算 $\circ$

- 制約

  - $\forall x\in T.\;e\cdot x=x\cdot e=x$
  - $\forall f\in F.\;f\circ \mathrm{id}=\mathrm{id}\circ f=f$
  - $\forall x\in T.\;\mathrm{id}(x)=x$
  - $\forall x,y\in T,\;\forall f\in F.\;f(x\cdot y)=f(x)\cdot f(y)$

- 時間計算量

  $O(1)$

### 要素の挿入

- シグネチャ

  ```cpp
  void insert(int k, const T& val)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素の前に値 `val` を挿入します．ただし，$k$ が列の長さと等しい場合は列の末尾に `val` を追加します．

  つまり，変更前の列を $(A_0,\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,\mathrm{val},A_k,\ldots,A_{N-1})$ となります．

- 制約

  要素を挿入する前の列の長さを $N$ として，$0\leq k\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 要素の削除

- シグネチャ

  ```cpp
  void erase(int k)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素を削除します．

  つまり，変更前の列を $(A_0,\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,A_{k-1},A_{k+1},\ldots,A_{N-1})$ となります．

- 制約

  要素を挿入する前の列の長さを $N$ として，$0\leq k\lt N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 要素の取得

- シグネチャ

  ```cpp
  auto operator[](int k)
  ```

- 概要

  列の $k$ 番目 (0-indexed) の要素を取得します．返り値は `library/util/update_proxy_object` で定義されている `UpdateProxyObject<T, ...>` 型ですが，

    ```cpp
    // a: LazyEvalDynamicSequence<int, ...>
    a[0] += 2;    // 更新
    int x = a[1]; // 取得
    ```

  のように `std::vector` と基本的には同じような使い方が出来ます．
  
  `UpdateProxyObject<T, ...>` 型を返すのは，値の更新後に区間積を更新する必要があるためです．

- 制約

  列の長さを $N$ として，$0\leq k\lt N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間積取得

- シグネチャ

  ```cpp
  T prod(int l, int r) // (1)
  T operator()(int l, int r) // (2)
  ```

- 概要

  (1) と (2) は等価であり，どちらも区間積 $A_l\cdot A_{l+1}\cdot\cdots\cdot A_{r-1}$ を計算します．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間作用

- シグネチャ

  ```cpp
  T apply(const F &f, int l, int r)
  ```

- 概要

  $A_l,\ldots,A_{r-1}$ を $f(A_l),\ldots,f(A_{r-1})$ で更新します．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 区間反転

- シグネチャ

  ```cpp
  T reverse(int l, int r)
  ```

- 概要

  $A_l,\ldots,A_{r-1}$ を反転します．

  つまり，変更前の列を $(A_0,\ldots,A_{l-1},\underline{A_l,\ldots,A_{r-1}},A_{r},\ldots,A_{N-1})$ として，変更後の列は $(A_0,\ldots,A_{l-1},\underline{A_{r-1},\ldots,A_{l+1},A_{l}},A_{r},\ldots,A_{N-1})$ となります．

- 制約

  列の長さを $N$ として，$0\leq l\leq r\leq N$

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$

### 列の連結

- シグネチャ

  ```cpp
  LazyEvalDynamicSequence& operator+=(LazyEvalDynamicSequence &&right) // (1)
  void concat(LazyEvalDynamicSequence &&right) // (2)
  void concat_left(LazyEvalDynamicSequence &&left) // (3)
  ```

- 概要

  列を連結します．(1) と (2) では後ろに連結し，(3) では前に連結します．

  コピーを避けるために，引数として与える列は右辺値であることを要求します．

- 時間計算量

  $\mathrm{amortized}\; O(\log \max(L,R))$

### 列の分割

- シグネチャ

  ```cpp
  std::pair<LazyEvalDynamicSequence, LazyEvalDynamicSequence> split(int k)
  ```

- 概要

  列を分割します．`split` により分割した後は，分割してできた 2 つの列に対する操作のみが有効です．分割する前の列を保持していたインスタンスに対する操作は全て未定義となります．

- 時間計算量

  $\mathrm{amortized}\; O(\log N)$