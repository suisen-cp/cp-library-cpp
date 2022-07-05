---
title: SWAG を Deque に拡張したやつ
documentation_of: //library/datastructure/deque_sum.hpp
---
## SWAG を Deque に拡張したやつ

モノイドの元を要素に持つ deque に対する操作と総和取得を効率的に行うデータ構造。

## サポートする関数

二項演算の計算量を $O(X)$ とする。

- `push_back` : deque の末尾に要素を追加。$O(X)$
- `push_front` : deque の先頭に要素を追加。$O(X)$
- `pop_back` : deque の末尾の要素を削除。amortized $O(X)$
- `pop_front` : deque の先頭の要素を削除。amortized $O(X)$
- `sum` : deque の要素を先頭から $v_1,\ldots,v_k$ として、二項演算 `op` で畳み込んだ結果 $op(v_1,op(v_2, op(\ldots, v_k)))$ を計算する。$O(X)$
- `operator[]` : ランダムアクセス。$O(1)$

## 参考

- https://motsu-xe.hatenablog.com/entry/2021/05/13/224016 : SWAG を deque に拡張するアイデア
- https://www.slideshare.net/catupper/amortize-analysis-of-deque-with-2-stack : stack 2 つで deque をシミュレートする方法
