---
title: undo 可能 Union Find
documentation_of: //library/datastructure/union_find/undo_union_find.hpp
---
## undo 可能 Union Find

経路圧縮を諦めることで undo 操作を可能にした Union Find。weighted union heuristic による集合の併合のみを行うので、各種操作の計算量は $O(\log N)$ である。
