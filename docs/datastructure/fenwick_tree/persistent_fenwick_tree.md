---
title: Persistent Fenwick Tree
documentation_of: //library/datastructure/fenwick_tree/persistent_fenwick_tree.hpp
---
## Persistent Fenwick Tree

Fenwick Tree の値を二分木における in-order で配置すると，`add`, `sum` の操作が根から (葉とは限らない) ある節点までのパス上で完結する．即ち，Segment Tree 等と同様にして永続化することが出来る．

永続セグメント木よりも定数倍がよいか?

例. [Rectangle Sum](https://judge.yosupo.jp/problem/rectangle_sum) での速度比較

- [永続 Fenwick Tree, 886ms](https://judge.yosupo.jp/submission/91009)
- [永続 Segment Tree, 1322ms](https://judge.yosupo.jp/submission/91011)
