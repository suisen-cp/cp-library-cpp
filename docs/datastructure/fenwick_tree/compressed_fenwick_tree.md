---
title: 任意次元 Fenwick Tree
documentation_of: //library/datastructure/fenwick_tree/compressed_fenwick_tree.hpp
---
## 任意次元 Fenwick Tree

空間 $O(q(\log q) ^ {d - 1})$、クエリ $O((\log q) ^ d)$ の $d$ 次元 Fenwick Tree。計算量は $d$ を定数とみなした場合である。クエリの定数倍として $2 ^ d$ が付くので注意 (prefix クエリの場合を除く)。
