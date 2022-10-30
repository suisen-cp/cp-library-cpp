---
title: Point Get Range Contour Add Invertible
documentation_of: //library/tree/point_get_range_contour_add_invertible.hpp
---
## Point Get Range Contour Add Invertible

以下のような問題を考えます。

### 問題

$N$ 頂点の木 $T$ の各頂点 $v$ に可換群 $(G,\oplus)$ の元 $A _ v$ が書かれている。以下の形式で表されるクエリが $Q$ 個与えられるので、順番に処理せよ。

- `1 v` : 頂点 $v\in V(T)$ に書かれている値を取得する。
- `2 v l r x` : 頂点 $v\in V(T)$ からの最短距離が $l$ 以上 $r$ 未満であるような全ての頂点 $u$ に対して、$A _ u \leftarrow A _ u \oplus x$ と更新する。

ここで、$T$ の辺の重みは全て $1$ であるとします。

本ライブラリは、$\oplus$ の計算にかかる時間を $O(1)$ と仮定して、上記の問題を前計算 $\Theta(N \log N)$、クエリ $\Theta( (\log N) ^ 2 )$ で解くアルゴリズムの実装です。

可逆性を活かして定数倍高速化を図っています。

## 参考

- [重心分解で 1 点更新区間取得 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2022/03/27/042143)