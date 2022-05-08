---
title: 任意 mod での二項係数列挙
documentation_of: //library/number/anymod_binom.hpp
---
## 任意 mod での二項係数列挙

$$
\binom{n}{k} \bmod M = \dfrac{n!}{k!(n-k)!} \bmod M
$$

を全ての $k=0,\ldots,n$ に対して $\Theta\left(\dfrac{N \log M}{\log \log M}\right)$ 時間で求める。$M$ は合成数でも $M \leq n$ でもよい。