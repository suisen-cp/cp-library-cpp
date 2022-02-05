---
title: Mo
documentation_of: //library/algorithm/mo.hpp
---

## Mo's Algorithm

### コンストラクタ

- シグネチャ

  ```cpp
  Mo(const int n, const std::vector<std::pair<int, int>> &queries)
  ```

- 概要

  内部でクエリに答える順番を並び替える．並び替え方は [Mo's algorithm](https://ei1333.hateblo.jp/entry/2017/09/11/211011) の「おまけ その 1: 定数倍改善」の項を参照．

- 引数

  - `n` : 区間の右端の上限値．
  - `queries` : 半開区間 $[l_i,r_i)$ で表されるクエリを $i$ 番目の要素として持つ `std::vector<std::pair<int, int>>`．$0\leq l_i\leq r_i\leq n$ を満たす必要がある．

- 時間計算量

  $Q$ をクエリの数として，$O(Q\log Q)$

### solve

- シグネチャ

  ```cpp
  // (1)
  template <typename Eval, typename AddL, typename DelL, typename AddR, typename DelR>
  auto solve(Eval eval, AddL add_l, DelL del_l, AddR add_r, DelR del_r)
  // (2)
  template <typename Eval, typename Add, typename Del>
  auto solve(Eval eval, Add add, Del del)
  ```

- 概要

  $i$ 番目のクエリの答えを $i$ 番目の要素として持つ `std::vector` を返す．クエリの答えを求めるのに必要な状態を外に置いて，引数の `add_l` や `del_l` の中で追加処理や削除処理に応じて状態を更新する．(2) は (1) において `add_l = add_r` かつ `del_l = del_r` の場合に用いる．

  具体的な使用法に関してはテストファイルを参照．

- 引数

  - `eval : () -> T` : 現時点の答えを返す関数
  - `add_l : int -> any` : 現時点の区間を $[l+1,r)$ として，$l$ を追加する関数．返り値は捨てられる．
  - `del_l : int -> any` : 現時点の区間を $[l,r)$ として，$l$ を削除する関数．返り値は捨てられる．
  - `add_r : int -> any` : 現時点の区間を $[l,r)$ として，$r$ を追加する関数．返り値は捨てられる．
  - `del_r : int -> any` : 現時点の区間を $[l,r+1)$ として，$r$ を削除する関数．返り値は捨てられる．

- 返り値

  $i$ 番目のクエリの答えを $i$ 番目の要素として持つ `std::vector<decltype(eval())>`．つまり，`std::vector` の要素の型は `eval()` が返す型．

  ここでいう $i$ 番目は，クエリの並べ替え前の順番を指す．即ち，外部からは内部の並び替えについては一切意識しなくてもよい．

- 制約

  - `eval` は引数を取らない関数 (返り値の型はデフォルト構築可能であることを要求する)
  - `add_l`, `del_l`, `add_r`, `del_r` は，引数として `int` 型の値を 1 つ受け取る関数

- 時間計算量

  `eval` や `add_l` などの計算量を $O(1)$ として，$O(N\sqrt Q)$

### get_left, get_right, get_range

- シグネチャ

  ```cpp
  // (1)
  int get_left()
  // (2)
  int get_right()
  // (3)
  std::pair<int, int> get_range()
  ```

- 概要

  [solve](#solve) に渡す `add_l` などの関数内で，現時点の区間を取得したい場合に用いる関数．

- 返り値

  現時点の区間は半開区間で $[l,r)$ と表されるとする．

  1. `l` を返す
  2. `r` を返す
  3. `std::pair<int, int> { l, r }` を返す

- 制約

  無し

- 時間計算量

  いずれも $O(1)$

## 参考

  - [Mo's algorithm](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
  - [Mo's algorithm とその上位互換の話](https://snuke.hatenablog.com/entry/2016/07/01/000000)
