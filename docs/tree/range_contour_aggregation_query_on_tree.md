---
title: Range Contour Aggregation Query On Tree (木上の等高線集約クエリ)
documentation_of: //library/tree/point_set_range_contour_product.hpp
---
## Range Contour Aggregation Query On Tree (木上の等高線集約クエリ)

以下のような問題を考えます。

### 問題

$N$ 頂点の木 $T$ の各頂点 $v$ に可換モノイド $(M,\oplus)$ の元 $A _ v$ が書かれている。以下の形式で表されるクエリが $Q$ 個与えられるので、順番に処理せよ。

- `1 v x` : 頂点 $v\in V(T)$ に書かれた値を $x\in M$ に変更する。即ち、$A _ v \leftarrow x$ とする。
- `2 v l r` : 頂点 $v\in V(T)$ からの最短距離が $l$ 以上 $r$ 未満であるような頂点の集合を $S(v,l,r)$ として、$\displaystyle \bigoplus _ { u \in S (v,l,r) } A _ u$ を計算する。

ここで、$T$ の辺の重みは全て $1$ であるとします。

本ライブラリは、$\oplus$ の計算にかかる時間を $O(1)$ と仮定して、上記の問題を前計算 $\Theta(N \log N)$、クエリ $\Theta( (\log N) ^ 2 )$ で解くアルゴリズムの実装です。詳細は [重心分解で 1 点更新区間取得 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2022/03/27/042143) を参照してください。
