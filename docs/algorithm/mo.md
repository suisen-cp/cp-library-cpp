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

  クエリに答える順番を計算しておく．

- 引数

  - `n` : 区間の右端の上限値．
  - `queries` : クエリの区間 $[l_i,r_i)$ を $i$ 番目の要素として持つ `std::vector<std::pair<int, int>>`．$0\leq l_i\leq r_i\leq n$ を満たす必要がある．

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

- 制約

  - `eval` は引数を取らず，default constructiveな型の値を返す関数
  - `add_l`, `del_l`, `add_r`, `del_r` は，`int` を 1 つ受け取る関数

- 時間計算量

  `eval` や `add_l` などの計算量を $O(1)$ として，$O(N\sqrt Q)$

- 参考

  - [Mo's algorithm](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
  - [Mo's algorithm とその上位互換の話](https://snuke.hatenablog.com/entry/2016/07/01/000000)
