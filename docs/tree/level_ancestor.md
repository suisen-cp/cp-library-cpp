---
title: Level Ancestor
documentation_of: //library/tree/level_ancestor.hpp
---
## Level Ancestor

根付き木において頂点 $u$ から親方向の辺をちょうど $k$ 回辿って到達する頂点を $v$ (存在しない場合は $-1$) として、$\mathrm{LA}(u,k)=v$ と定義する。

オンラインで与えられる $u,k$ に対して $\mathrm{LA}(u,k)$ を求めるクエリに前計算 $\Theta(N)$、クエリ $\Theta(\log N)$ で答えるアルゴリズムの実装である。

同じ計算量オーダーを達成する方法として Heavy Light Decomposition (HLD) を用いたアルゴリズムが存在する。速度はやや本実装の方が速いか？(要検証)

提出比較

- HLD:
  https://judge.yosupo.jp/submission/88623
- 本実装:
  https://judge.yosupo.jp/submission/88629

## 参考文献

- [そらで書ける <Θ(N), Θ(log N)> Level Ancestor](https://suisen-kyopro.hatenablog.com/entry/2022/04/04/043452)
