---
title: 有名な数列たち
documentation_of: //library/polynomial/common_sequences.hpp
---

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

### stirling_number2

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> stirling_number2(int n)
  ```

- 概要

  第二種スターリング数 $\\\{\mathrm{S2}(n,i)\\\} _ {i=0} ^ n$ を計算します．$\mathrm{S2}(n,i)$ は，ラベル付けされた $n$ 個の玉を $i$ 個のグループに分割する方法の数と一致します．ここで，$\\\{\\\{1,2\\\},\\\{3,4\\\}\\\}$ と $\\\{\\\{3,4\\\},\\\{1,2\\\}\\\}$ のような分け方は区別しません．

- テンプレート引数
  
  - `mint`: modint 型を想定

- 返り値

  第二種スターリング数 $\\\{\mathrm{S2}(n,i)\\\} _ {i=0} ^ n$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$

- 参考
  
  - [スターリング数 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%AA%E3%83%B3%E3%82%B0%E6%95%B0)
  - [FFT (NTT) 関連](https://min-25.hatenablog.com/entry/2015/04/07/160154)

### bernoulli_number

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> bernoulli_number(int n)
  ```

- 概要

  ベルヌーイ数 $B_0,\ldots,B_N$ を計算します．

  $$\sum_{i=0} ^ \infty\dfrac{B_i}{i!}x ^ i=\dfrac{x}{e ^ x-1}$$

  より，

  $$B_i=i!\cdot [x ^ i]\left(\sum_{i=0} ^ \infty \dfrac{x ^ i}{(i+1)!}\right) ^ {-1}$$

  に従って計算します．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  ベルヌーイ数 $\\\{B_i\\\} _ {i=0} ^ N$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$

### partition_number

- シグネチャ

  ```cpp
  template <typename mint>
  std::vector<mint> partition_number(int n)
  ```

- 概要

  分割数 $P_0,\ldots,P_N$ を計算します．ここで，$P_i$ は，正整数を要素とする多重集合であって，総和が $i$ であるようなものの個数と一致します．

  母関数は $\displaystyle \sum_{i=0} ^ \infty P_i x ^ i=\prod_{k=1} ^ \infty \dfrac{1}{1-x ^ k}$ で表され，オイラーの五角数定理 :

  $$\prod_{k=1} ^ \infty(1-x ^ k)=\sum_{k=-\infty} ^ \infty(-1) ^ k x ^ {k(3k-1)/2}$$

  を用いることで，

  $$
  \begin{aligned}
  \sum_{i=0} ^ n P_i x ^ i
  &=\left(1+\sum_{k=1} ^ n (-1) ^ k \Bigl(x ^ {k(3k-1)/2}+x ^ {k(3k+1)/2}\Bigr)\right) ^ {-1}\bmod x ^ {n+1}
  \end{aligned}
  $$

  により計算できます．

- テンプレート引数

  - `mint`: modint 型を想定

- 返り値

  分割数 $\\\{P_i\\\} _ {i=0} ^ N$

- 制約

  - $0\leq n\leq 10 ^ 6$

- 時間計算量

  $O(n\log n)$

- 参考

  - [(形式的)べき級数と数え上げの写像12相との関係性　後編](https://sen-comp.hatenablog.com/entry/2019/12/11/110958)
