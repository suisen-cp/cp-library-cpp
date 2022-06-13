---
title: Fenwick Tree Prefix
documentation_of: //library/datastructure/fenwick_tree/fenwick_tree_prefix.hpp
---
## Fenwick Tree Prefix

一般のモノイド $(\oplus,M)$ が乗る代わりに，処理できるクエリは以下の 2 つに制限される．

- $\mathrm{apply}(i,v)$: $A _ i \leftarrow A _ i \oplus v$ と更新する
- $\mathrm{prefix\\_query}(r)$: $\displaystyle \bigoplus _ {i = 0} ^ {r - 1} A _ i$ を計算する
