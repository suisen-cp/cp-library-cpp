---
title: Persistent Fenwick Tree
documentation_of: //library/datastructure/persistent_fenwick_tree.hpp
---
## Persistent Fenwick Tree

Fenwick Tree の値を二分木における in-order で配置すると，`add`, `sum` の操作が根から (葉とは限らない) ある節点までのパス上で完結する．即ち，Segment Tree 等と同様にして永続化することが出来る．

サイズ $N$ の列を管理するために必要なノードは $N + O(\log N)$ 個であり，$2 N - 1$ 個必要である永続 Segment Tree よりも空間効率がよい．

`add`, `sum` を非再帰で書けるので，定数倍の面でも有利?

例. [Rectangle Sum](https://judge.yosupo.jp/problem/rectangle_sum) での速度比較

- [永続 Fenwick Tree, 886ms](https://judge.yosupo.jp/submission/91009)
- [永続 Segment Tree, 1322ms](https://judge.yosupo.jp/submission/91011)
