---
title: Stirling Number1
documentation_of: //library/sequence/stirling_number1.hpp
---
## Stirling Number1

### stirling_number1_reversed

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number1_reversed(int n) // (1)
  template <typename mint>
  std::vector<mint> stirling_number1_reversed(const long long n, const int k) // (2)
  ```

- 概要
  
  (符号なし) 第一種スターリング数 $\mathrm{S1}(n,\cdot)$ を逆順に並べた列 $A=(\mathrm{S1}(n,n),\mathrm{S1}(n,n-1),\ldots)$ を計算します．つまり，$A_i$ は集合 $\\\{0,\ldots,n-1\\\}$ から $i$ 個の要素を選んで積を取ったものの総和となります．形式的には，以下が成り立ちます．

  $$A_i=\sum_{\overset{\scriptstyle S\subset\{0,\ldots,n-1\},}{|S|=i}}\prod_{j\in S} j$$

  組合せ的には，$\mathrm{S1}(n,i)$ はラベル付けされた $n$ 個の玉を $i$ 個の円環 (巡回列) に分割する方法の個数と一致します．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  1. $\\\{A_i\\\} _ {i=0} ^ n=\\\{\mathrm{S1}(n,n-i)\\\} _ {i=0} ^ {n}$
  2. $\\\{A_i\\\} _ {i=0} ^ k=\\\{\mathrm{S1}(n,n-i)\\\} _ {i=0} ^ {k}$

      Note. $k>n$ の場合は $A_{n+1}=\cdots=A_{k}=0$ が保証される．

- 制約

  1. - $0\leq n\leq 10 ^ 6$
  2. - $0\leq n\leq 10 ^ {18}$
     - $0\leq k\leq 5000$
     - $k\lt \mathrm{mod}$

- 時間計算量

  1. $O(n\log n)$
  2. $O(k ^ 2\log n)$

- 参考

  - [スターリング数 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%AA%E3%83%B3%E3%82%B0%E6%95%B0)
  - [第一種スターリング数の末尾項を計算する](https://suisen-kyopro.hatenablog.com/entry/2021/06/02/225932)

### stirling_number1

- シグネチャ
  
  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number1(int n)
  ```

- 概要
  
  [stirling number1 reversed](#stirling_number1_reversed) (1) の列を逆順にしたもの，つまり (符号なし) 第一種スターリング数の列 $\\\{\mathrm{S1}(n,i)\\\} _ {i=0} ^ n$ を計算します．