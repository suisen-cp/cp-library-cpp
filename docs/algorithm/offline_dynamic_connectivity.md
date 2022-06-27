---
title: Offline Dynamic Connectivity
documentation_of: //library/algorithm/offline_dynamic_connectivity.hpp
---
## Offline Dynamic Connectivity

Dynamic Conectivity Problem をクエリ先読みにより $O(Q \log Q \log N)$ 時間で解く。時間軸を添字とした双対セグ木のノードに辺を乗せ、セグ木を dfs しながら Union Find を更新する。dfs の帰りがけで undo 操作をする必要があるので、Undo 可能 Union Find を用いる。

各辺は $O(\log Q)$ 個のノードに存在するので、Union Find の操作回数は $O(Q\log Q)$ 回である。Undo 可能 Union Find の各種操作の計算量は経路圧縮を行わないため $O(\log N)$ であるから、全体の計算量は $O(Q \log Q \log N)$ となる。
