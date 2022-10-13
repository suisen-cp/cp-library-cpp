---
title: Binomial Coefficient Small Prime Mod
documentation_of: //library/sequence/binomial_coefficient_small_prime_mod.hpp
---
## Binomial Coefficient Small Prime Mod

以下に示す Lucas の定理を用いる。

> $p$ が素数のとき、非負整数 $n, r$ に対して次が成り立つ:
> $$\binom{n}{r} \equiv \prod_{i=0}^{k-1}\binom{n _ i}{r _ i} \pmod{p}.$$
> ここで、$n$ を $p$ 進表記したときの $i$ 桁目を $n_i$ とした ($r$ についても同様)。

全ての $0\leq n\lt p,0\leq r\lt p$ に対する $\displaystyle \binom{n}{r} \bmod p$ を $O(p ^ 2)$ 時間だけ掛けて前計算しておくことで、クエリあたり $O(\log _ p n)$ で計算できる。
