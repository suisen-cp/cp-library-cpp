---
title: 有名な数列たち
documentation_of: //library/math/common_sequences.hpp
---

### stirling_number1_reversed

```cpp
template <typename mint>
std::vector<mint> stirling_number1_reversed(int n) 
```

(符号なし) 第一種スターリング数 $\mathrm{S1}(N,\cdot)$ を逆順に並べた列を $O(N\log N)$ で計算します．つまり，返り値の `vector` の $k$ 番目の要素を $A_k$ とすると，$A_k$ は集合 $\{0,\ldots,N-1\}$ から $k$ 個の要素を選んで積を取ったものの総和となります．数式で書けば，次が成り立ちます．

$$
A_k=\sum_{\overset{\scriptstyle S\subset\{0,\ldots,N-1\},}{|S|=k}}\prod_{v\in S} v
$$

```cpp
template <typename mint>
std::vector<mint> stirling_number1_reversed(const long long n, const int k)
```

(符号なし) 第一種スターリング数 $\mathrm{S1}(N,\cdot)$ を逆順に並べた列の前から $K+1$ 項を $O(K^2\log N)$ で計算します．
