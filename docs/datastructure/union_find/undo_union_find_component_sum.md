---
title: 連結成分の可換モノイド和を取得できる undo 可能 Union Find
documentation_of: //library/datastructure/union_find/undo_union_find_component_sum.hpp
---
## 連結成分の可換モノイド和を取得できる undo 可能 Union Find

連結成分毎に可換モノイドの元を持つ Union Find に undo 機能を付けたもの。[Dynamic Graph Vertex Add Component Sum](https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum) を offline で解く場合などで使用。

経路圧縮を諦めることで undo 操作を可能にしており、weighted union heuristic による集合の併合のみを行うので、各種操作の計算量は $O(\log N)$ である。
