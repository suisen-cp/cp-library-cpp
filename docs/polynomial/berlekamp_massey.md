---
title: Berlekamp Massey (線形回帰数列の係数計算)
documentation_of: //library/polynomial/berlekamp_massey.hpp
---
## Berlekamp Massey (線形回帰数列の係数の計算)

体 $F$ 上の数列 $s=(s_0,s_1,\ldots,s_{n-1})$ に対して、

$$s_i=\sum_{j=1}^L c_j\cdot s_{i-j}\quad (\forall i\geq L)$$

を満たす数列 $c=(c_1,\ldots,c_L)$ のうち長さ $L$ が最小のものを $\Theta(n ^ 2)$ 時間で計算する。

## Reference

[1] J. Massey, "Shift-register synthesis and BCH decoding," in IEEE Transactions on Information Theory, vol. 15, no. 1, pp. 122-127, January 1969, doi: 10.1109/TIT.1969.1054260.
