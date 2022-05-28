---
title: Subset Iterator
documentation_of: //library/util/subset_iterator.hpp
---
## Subset Iterator

- `all_subset(s)` : $T\subseteq S$ を満たす $T$ を列挙する
- `all_subset_k(s, k)` : $T\subseteq S, \vert T\vert = k$ を満たす $T$ を列挙する

## 計算量

$n = \vert S\vert$ とする．

- `all_subset(s)`
  - 前計算 $O(1)$
  - 次の要素の計算 $O(1)$
  - 全体 $O(2 ^ n)$
- `all_subset_k(s, k)`
  - 前計算 $O(\log s)$
  - 次の要素の計算 $O(1)$ (ただし，`popcount` は $O(1)$ で計算できると仮定)
  - 全体 $O({} _ n C _ k)$

## 使い方

```cpp
uint32_t s = 0b1011;
for (uint32_t t : suisen::all_subset(s)) {
    std::cout << t << std::endl;
}
/**
 * 11 (= 1011)
 * 10 (= 1010)
 *  9 (= 1001)
 *  8 (= 1000)
 *  3 (= 0011)
 *  2 (= 0010)
 *  1 (= 0001)
 */

for (uint32_t t : suisen::all_subset_k(s, 2)) {
    std::cout << t << std::endl;
}
/**
 *  3 (= 0011)
 *  9 (= 1001)
 * 10 (= 1010)
 */
```