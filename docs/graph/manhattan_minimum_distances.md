---
title: マンハッタン距離で最も近い点への距離の列挙
documentation_of: //library/graph/manhattan_minimum_distances.hpp
---
## マンハッタン距離で最も近い点への距離の列挙

$N$ 個の点 $(x_i,y_i)$ が与えられるので，以下で定まる $d _ i$ を全ての $i$ に対して $O(N\log N)$ 時間で計算する．

$$
d _ i = \min _ {j \neq i} |x _ i - x _ j| + |y _ i - y _ j|
$$
