---
title: Convolution $(\mathrm{mod}\ 2 ^ {64})$
documentation_of: //library/convolution/convolution_2_64.hpp
---
## Convolution $(\mathrm{mod}\ 2 ^ {64})$

以下の $6$ つの NTT-friendly な素数を法として畳み込んだ後、Garner のアルゴリズムにより復元する。

1. $p _ 1 = 754974721=45\times 2 ^ {24}+1$
2. $p _ 2 = 167772161=5\times 2 ^ {25}+1$
3. $p _ 3 = 469762049=7\times 2 ^ {26}+1$
4. $p _ 4 = 377487361=45\times 2 ^ {23}+1$
5. $p _ 5 = 595591169=71\times 2 ^ {23}+1$
6. $p _ 6 = 645922817=77\times 2 ^ {23}+1$

即ち、列 $A,B$ を畳み込む場合、$\vert A\vert +\vert B\vert -1\leq 2 ^ {23}=8388608\simeq 8.39\times 10 ^ 6$ を満たす必要がある。

また、正しい値を復元するためには畳み込んだ後の各係数が $p _ 1 \times p _ 2 \times p _ 3\times p _ 4\times p _ 5\times p _ 6$ 未満でなければならないが、$(2 ^ {64} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {23} + 1}{2}\right\rceil \leq p _ 1 \times p _ 2 \times p _ 3\times p _ 4\times p _ 5\times p _ 6$ が成り立つため、$\vert A\vert +\vert B\vert -1\leq 2 ^ {23}$ の下では必ず正しい値を復元することが出来る。

一方で、$\vert A\vert +\vert B\vert -1\leq 2 ^ {22} = 4194304 \simeq 4.2\times 10 ^ 6$ を仮定すれば、$5$ つの NTT-friendly な素数を以下のように選ぶことで、

1. $p _ 1 ' = 998244353=119\times 2 ^ {23}+1$
2. $p _ 2 ' = 985661441=235\times 2 ^ {22}+1$
3. $p _ 3 ' = 943718401=225\times 2 ^ {22}+1$
4. $p _ 4 ' = 935329793=223\times 2 ^ {22}+1$
5. $p _ 5 ' = 918552577=219\times 2 ^ {22}+1$

$(2 ^ {64} - 1) ^ 2 \times \left\lceil\dfrac{2 ^ {22} + 1}{2}\right\rceil \leq p _ 1 ' \times p _ 2 ' \times p _ 3 ' \times p _ 4 ' \times p _ 5 ' $ を満たす。

本実装では、$\vert A\vert +\vert B\vert -1\leq 2 ^ {22} = 4194304$ を満たすならば $\mathrm{mod}$ を $5$ つ取る解法を、$2 ^ {22} \lt \vert A\vert +\vert B\vert -1 \leq 2 ^ {23}$ を満たすならば $\mathrm{mod}$ を $6$ つ取る解法を選択する。
