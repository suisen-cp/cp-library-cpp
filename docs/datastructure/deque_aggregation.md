---
title: SWAG を Deque に拡張したやつ
documentation_of: //library/datastructure/deque_aggregation.hpp
---
## SWAG を Deque に拡張したやつ

モノイドの元を要素に持つ deque に対する操作と総和取得を効率的に行うデータ構造。

## サポートする関数

二項演算の計算量を $O(X)$ とする。

- `push_back` : 末尾に要素を追加。$O(X)$
- `push_front` : 先頭に要素を追加。$O(X)$
- `pop_back` : 末尾の要素を削除。amortized $O(X)$
- `pop_front` : 先頭の要素を削除。amortized $O(X)$
- `prod` : 要素を先頭から $v_1,\ldots,v_k$ として、二項演算 `op` で畳み込んだ結果 $op(v_1,op(v_2, op(\ldots, v_k)))$ を計算。$O(X)$
- `operator[]` : ランダムアクセス。$O(1)$
- `back` : 末尾の要素を取得。$O(1)$
- `front` : 先頭の要素を取得。$O(1)$
- `size` : 要素数を取得。$O(1)$
- `clear` : コンテナを空にする。内部的に確保されている capacity は変更しない。$O(1)$
- `shrink_to_fit` : capacity を size まで縮小。$O(1)$
- `begin` : 先頭の要素を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `end` : 末尾の次を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `cbegin` : 先頭の要素を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$
- `cend` : 末尾の次を指す読み取り専用イテレータを取得 (即ち、要素の変更は不可能)。$O(1)$

## 参考

- https://motsu-xe.hatenablog.com/entry/2021/05/13/224016 : SWAG を deque に拡張するアイデア
- https://www.slideshare.net/catupper/amortize-analysis-of-deque-with-2-stack : stack 2 つで deque をシミュレートする方法
