---
title: Stirling Number2
documentation_of: //library/sequence/stirling_number2.hpp
---
## Stirling Number2

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