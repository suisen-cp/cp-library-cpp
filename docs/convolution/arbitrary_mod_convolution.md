---
title: 任意 $\mathrm{mod}$ 畳み込み
documentation_of: //library/convolution/arbitrary_mod_convolution.hpp
---
## 任意 $\mathrm{mod}$ 畳み込み

以下の $3$ つの NTT-friendly な素数を法として畳み込んだ後、Garner のアルゴリズムにより復元する。

1. $p _ 1 = 754974721=45\times 2 ^ {24}+1$
2. $p _ 2 = 167772161=5\times 2 ^ {25}+1$
3. $p _ 3 = 469762049=7\times 2 ^ {26}+1$

即ち、列 $A,B$ を畳み込む場合、$\vert A\vert +\vert B\vert -1\leq 2 ^ {24}=16777216\simeq 1.68\times 10 ^ 7$ を満たす必要がある。

また、正しい値を復元するためには畳み込んだ後の各係数が $p _ 1 \times p _ 2 \times p _ 3$ 未満でなければならないが、$\mathrm{mod}$ が $2 ^ {31}$ 以下と仮定すれば、$(2 ^ {31} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {24} + 1}{2}\right\rceil \leq p _ 1 \times p _ 2 \times p _ 3$ が成り立つため、$\vert A\vert +\vert B\vert -1\leq 2^{24}$ の下では必ず正しい値を復元することが出来る。
