---
title: Point Add Range Contour Sum Invertible
documentation_of: //library/tree/point_add_range_contour_sum_invertible.hpp
---
## Point Add Range Contour Sum Invertible

以下のような問題を考えます。

### 問題

$N$ 頂点の木 $T$ の各頂点 $v$ に可換群 $(G,\oplus)$ の元 $A _ v$ が書かれている。以下の形式で表されるクエリが $Q$ 個与えられるので、順番に処理せよ。

- `1 v x` : 頂点 $v\in V(T)$ に書かれた値を $A _ v \oplus x$ に変更する。即ち、$A _ v \leftarrow A _ v \oplus x$ とする。
- `2 v l r` : 頂点 $v\in V(T)$ からの最短距離が $l$ 以上 $r$ 未満であるような頂点の集合を $S(v,l,r)$ として、$\displaystyle \bigoplus _ { u \in S (v,l, r) } A _ u$ を計算する。

ここで、$T$ の辺の重みは全て $1$ であるとします。

本ライブラリは、$\oplus$ の計算にかかる時間を $O(1)$ と仮定して、上記の問題を前計算 $\Theta(N \log N)$、クエリ $\Theta( (\log N) ^ 2 )$ で解くアルゴリズムの実装です。

Point Add 型の更新しか来ないこと、および可逆性を活かして定数倍高速化を図っています。

## 参考

- [重心分解で 1 点更新区間取得 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2022/03/27/042143)